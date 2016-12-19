//
//  filmato_3D_gnuplotMultiThread.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 21/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "filmato_3D_gnuplotMultiThread.hpp"


//
//  filmato_3D_gnuplot.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 01/06/15.
/* This program is free software; you can redistribute it and/or
 modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 2
 of the License.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; if not, write to the Free Software
 Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
 02110-1301, USA. */
//

#include <iostream>
#include <fstream>
#include <cmath>

#ifndef NO_M_THREAD
#include <thread>
#endif


#include <sys/stat.h>
#include <unistd.h>
#include <chrono>

#include <limits>
#include <ctime>
#include <array>

#include <sys/stat.h>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "apngasm_Global.h"
#include "ErrorsDefinition.h"
#include "Colori.h"
#include "sssr.h"
#include "Declar_funz.h"

#include <sstream>
#include "Funz_C.h"
#include "setSizesTitles.hpp"
#include "filmato_3D_gnuplotMultiThread.hpp"

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
#include <windows.h>
int executeCommandLine(std::string play_video);
int executeCommandLine2(std::string play_video);
#endif

#define SAVE 0
#define NO_SAVE 1
#define DENSITY 0
#define FUNZC   1

//#ifndef max
//#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
//#endif
#ifndef min
#define min_( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

int writeLog(string what, string msg);
void lunch_apngas(string name_out, string name_input);
bool is_file_exist(const char* fileName);

/** This fuction crate the script so save, see save 4,9,16 snapshot of the density and ligand.
 * it is not very well written. there are a lot of if end so on that can be throw away.
 * The fact is that if we save the file and want to see it, then we first save and then play with firefox (better immage)
 * Note: problem lunching firefox with Windows. To be check!
 * note that we have to be careful how to pass the parameters to apngasm if we;re on Unix or Windows (line 213)
 */


void filmato_3D_gnuplotMultiT(string names_info[],long double max_x, long double max_y, long double min_x,long double min_y, long double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, long double max_fc)
{
    
    funz_clear();
    
    cout << BOLDRED
    << "--------------------------------------------------" <<endl
    << "-                    CINE_COLI                   -"   << endl
    << "-                 ... THE FILM ...               -"   << endl
    << "--------------------------------------------------" << RESET <<endl;
    
    cout << "Filmato  3d gnuplot" << endl;
    
    char bufferSim[8]; // buffer for prefix
    snprintf(bufferSim, sizeof(char)*8, "sim%03d",cont_gen_sim);
    int risp=1;
    

////    const char* programPath = "/bin/bash";
////    
////    pid_t pid = fork(); /* Create a child process */
////    
////    switch (pid) {
////        case -1: /* Error */
////            std::cerr << "Uh-Oh! fork() failed.\n";
////            exit(1);
////        case 0: /* Child process */
////            execl(programPath, NULL); /* Execute the program */
////            std::cerr << "Uh-Oh! execl() failed!"; /* execl doesn't return unless there's an error */
////            exit(1);
////        default: /* Parent process */
////            std::cout << "Process created with pid " << pid << "\n";
////            int status;
////            
////            while (!WIFEXITED(status)) {
////                waitpid(pid, &status, 0); /* Wait for the process to complete */
////            }
////            
////            std::cout << "Process exited with " << WEXITSTATUS(status) << "\n";
////            
//////            return 0;
////    }
    int nthread = n_thread_available; //min_(n_thread_available,std::thread::hardware_concurrency());
    
    if (nthread!=0) {
        nthread--;
    }
    ofstream file_3D_hist;
    ofstream file_play_video;
    string title;
    std::ifstream file_info;
    file_info.open(names_info[0].c_str());
    int n_data=1;
    long double dt;
    cout << "names_info[0] = " << names_info[0] << endl;
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    file_info >> n_data; // const_salv
    
    dt=dt*n_data;
    file_info.close();
    
    cout << "Do you want to see the movie of the evolution of the density? \npress 0 for yes, 1 for no ";
    sssr(risp,"Do you want to see the movie of the evolution of the density? press 0 for yes, 1 for no ");
    
    long double maxX,maxY,minX,minY;
    if (f->interact==0){
        maxX=f->max_x; maxY=f->max_y; minX=f->min_x; minY=f->min_y;
        //TODO::::
        //        max_fc = 18.2*exp(1*3);
    }else{
        maxX=max_x; maxY=max_y; minX=min_x; minY=min_y;
    }
    int risp_save=1;
    //********************
    // FILM ...
    if (automatic_!=1) {
        cout << "Do you want to save the film? \n";
        if (maxX-minX >5 || maxY-minY >5) {
            cout << RED << "If you don't save it, the sequence of frames might be very slow\n" << RESET;
        }
        cout << "press 0 for yes, 1 for no ";
        if (automatic_==0) {
            getInput( risp_save);
        }else {
            risp_save=0;
        }
        #if NO_M_THREAD     
        time_t start;     
        time(&start); 
        #else     
        auto start = chrono::steady_clock::now(); 
        #endif
        
        //************************
        //      CREATION FRAMES ...
//        scriptFilmato3Dgnuplot(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, NO_SAVE,cont_gen_sim);
        if (risp==0 && (risp_save!=0)) {
            scriptFilmato3DgnuplotMultiT(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, NO_SAVE,cont_gen_sim);
        }

        if (risp_save==0) {
            cout <<"elaboration and saving of the film ...\n";
            for (int i=0; i<nthread+1; ++i) {
                scriptFilmato3DgnuplotMultiT(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, SAVE,cont_gen_sim,i,nthread+1);
            }
            int error = 0;
            for (int i=0; i<nthread; ++i) {
                error+=lunchMultiThread3Dgnuplot(i+1, cont_gen_sim);
            }
            if(lunchMultiThread3Dgnuplot(0, cont_gen_sim,true,dim_col_t,nthread)!=0) // if something went wrong I check it
            {
                struct stat buf;
                char buffer1[52];
                cout << "nthread = " << nthread << endl;
                for (int i=1; i<nthread+1; i++) {
                    cout << "i:= " << i << endl;
                    snprintf(buffer1, sizeof(char) * 52, "sim%03dfilm3Dh%04d.png",cont_gen_sim,i+1);
                    if ((stat(buffer1, &buf)!=0)) {
                        cout <<BOLDRED<< "\nThread n. "<< i << " had problems\n";
                        cout << "Repeat task from main therad\n"<< RESET;
                        cout << buffer1 << " is not present\n";
                        lunchMultiThread3Dgnuplot(i, cont_gen_sim, true, dim_col_t, nthread);
                    }else{
                        cout << buffer1 << " is present\n";
                        //                    thread_started[i]=true;
                    }
                }
            }
        }
        else{
            
            string hist3D(bufferSim);
            string play_video(bufferSim);
            hist3D+="-3D_hist.gnu";
            play_video+="play_video.gnu";
            play_video="SCRIPT-GNUPLOT-"+play_video;
            file_play_video.open(play_video.c_str());
//            if (risp==0 && (risp_save!=0))
//                file_play_video << gnuplotSetTerminalSave_eps << endl;
            file_play_video << "b=1;" << endl
                            << "load '"<< hist3D<<"'" << endl;
            file_play_video << "pause mouse any" << endl;
            file_play_video<< "quit" <<endl;
            file_play_video.close();
            
            lunch_gnuplot(play_video);
        }

        //***************************
        //      ACTUAL FILM ......
        // CREATE the multilayer .png file for the movie
        if (automatic_!=1) {
            
            if (risp_save==0) {
                
                string name = names_info[0];
                name.erase(name.end()-3, name.end());
                name = name+"png ";
                
                string name_input;
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                
                name_input = bufferSim+std::string("film3Dh0001.png");
#else
                name_input = bufferSim+std::string("film3Dh*.png");
#endif
                
                cout << "saving file \n";
                lunch_apngas(name, name_input);
                string commandRemovePng;
                
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                
                commandRemovePng="del ";
#else
                commandRemovePng="rm -Rf ";
#endif
                commandRemovePng+=bufferSim;
                commandRemovePng+=+"film3Dh*.png";
                system(commandRemovePng.c_str());
                cout << "file saved \n";

                // Guardo il filmato
                if (risp==0) {
                    string command_play_video = firefox_path+std::string(" ")+name;
                    system(command_play_video.c_str());
                }
            }
            
        }
        
        deleteSCRIPT_GNUPLOTplay_videoMultiT(cont_gen_sim, n_thread_available);
        
#if NO_M_THREAD
    time_t end;
    double diff;
    time(&end);
    diff=difftime(start,end); // gives in seconds
#else
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
#endif

        cout <<BOLDBLACK << "***************************************************\n";
        cout << "Seconds needed to complete the creation and saving of the film:\n     ";
#if NO_M_THREAD
        cout << diff << " seconds" << endl;
#else
        cout << chrono::duration <long double, milli> (diff).count()/1000 << " seconds" << endl;
#endif        
        cout << "***************************************************\n"<<RESET;

        // LOG FILE
        if (verbose){
       stringstream msg;
       msg.str("");
#if NO_M_THREAD
        msg << diff << " seconds";
#else
        msg << chrono::duration <long double, milli> (diff).count()/1000 << " seconds";
#endif           
       writeLog("FILM: (multi-thread) created and saved in ",msg.str());
        }
        //****************************
        // OVERWRITE THE SCRITS ... not to save ...
        // TODO: check this ...
        string hist3D(bufferSim);
        string play_video(bufferSim);
        hist3D+="-3D_hist.gnu";
        play_video+="play_video.gnu";
        play_video="SCRIPT-GNUPLOT-"+play_video;
        file_play_video.open(play_video.c_str());
        if (risp==0 && (risp_save!=0))
            file_play_video << gnuplotSetTerminalSave_eps << endl;
        file_play_video << "b=1;" << endl
                        << "load '"<< hist3D<<"'" << endl;
        file_play_video << "pause mouse any" << endl;
        file_play_video<< "quit" <<endl;
        file_play_video.close();
//        scriptFilmato3Dgnuplot(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, NO_SAVE, cont_gen_sim);
    }
    funz_clear();
    
    
    cout << "... PLOT GNUPOLT FILM END ..." << endl;
    cout << "Frames video deleted ... \n\n... \n";
}


/**
 * This function writes the script for the video 3d gnuplot
 */


//***********************************************************************************************
// SCRIPT video without saving, if you decided to save it skeep this, since it produce the "film"
//        .png and then plays it.
//***********************************************************************************************

int scriptFilmato3DgnuplotMultiT(long double Dt/*dt*(epsilon*epsilon)*/, long double maxX, long double maxY, long double minX, long double minY, long double max_z, long double max_fc, int dim_col_t, int save_, int cont_sim,int i, int n_threadTot){
    
    string hist3D = setNamescript3DMultiT(cont_sim,i);
    
    cout << "script thread " << i << endl;
    cout << "         --> name: " <<hist3D << endl;
    
    
    
    char buffer[8];
    snprintf(buffer, sizeof(char)*8, "sim%03d",cont_sim);
    
    ofstream file_3D_hist;
    file_3D_hist.open(hist3D.c_str());
    
    if (!file_3D_hist.is_open()) {
        cout << "Error opening file '3D_hist.gnu'\n";
        return ERROR_OPENING_FILE;
    }
    
    if (save_==SAVE) {
        //NOTE: ora i filmati sono salvati come simYYYfilm3DhXXXX.png
        file_3D_hist << "nome_out = sprintf('sim%03dfilm3Dh%04d.png',"<<cont_sim<<",b)" << endl
                     << gnuplotSetTerminalSave_png << endl
                     << "set output nome_out # output=fileout"<< endl;
    }else{
        file_3D_hist << gnuplotSetTerminalPlot << endl;
        
        file_3D_hist << "#nome_out = sprintf('sim%03dfilm3Dh%04d.png',"<<cont_sim<<",b)" << endl
        << "#"<< gnuplotSetTerminalSave_png << endl
        << "# set output nome_out # output=fileout"<< endl;
        
    }
    if (i==0) {
        file_3D_hist << "num_frame = sprintf('saving frame %d out of %d ... ',b,"<< dim_col_t <<")" << endl;
        file_3D_hist << "print num_frame"<< endl;
    }
    file_3D_hist << "#set size number axis" << endl
                 << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl;
    
    file_3D_hist << "set size 1, 1" << endl;
    
    //*********************************************************
    
    file_3D_hist << "b_num=(b-1)*"<< Dt << endl;
    file_3D_hist << "nome2 = sprintf(\"Density & Ligand Concentration T = %.3f\",b_num)" << endl;
    file_3D_hist << "nome = \""<<buffer<<"film3Dh\".b.\".dat\"" << endl;
    file_3D_hist << "nome1 = \""<<buffer<<"film3Dc\".b.\".dat\"" << endl
                 << "set multiplot layout 3,1 title nome2"<< setSizesTitles(sizeTitle::HUGE_, NO_SAVE) << endl
                 << "set pm3d map" << endl
                 << "set pm3d interpolate 2,2" << endl;
    
    file_3D_hist << "set xrange [ " << minX<<":"<<maxX<< "]" << endl
                 << "set yrange [ " << minY<<":"<<maxY<< "]" << endl;
    // dim.
    file_3D_hist << "set origin 0.0, 0.4\n set size 0.5, 0.6" <<endl;
    
    file_3D_hist << "set zrange [ " << 0 << ":" << max_z << "]" << endl;
    
    file_3D_hist << "# disable colorbar tics" << endl;
    file_3D_hist << "set cbtics scale 0" << endl;
    file_3D_hist << "# matlab palette colors" << endl;
    file_3D_hist << "set palette defined ( 0 \"#000090\",\\" << endl;
    file_3D_hist << "1 \"#000fff\",\\" << endl;
    file_3D_hist << "2 \"#0090ff\",\\" << endl;
    file_3D_hist << "3 \"#0fffee\",\\" << endl;
    file_3D_hist << "4 \"#90ff70\",\\" << endl;
    file_3D_hist << "5 \"#ffee00\",\\" << endl;
    file_3D_hist << "6 \"#ff7000\",\\" << endl;
    file_3D_hist << "7 \"#ee0000\",\\" << endl;
    file_3D_hist << "8 \"#7f0000\")" << endl;
    
    
    
    file_3D_hist << "set title 'Density Population' " << setSizesTitles(sizeTitle::LARGE, NO_SAVE) << endl
                 << "set xlabel 'X(mm)' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ylabel 'Y(mm)' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl;
    
    // film3Dh
    file_3D_hist << "splot nome with pm3d notitle" << endl;
    file_3D_hist << "set origin 0.5, 0.4\n set size 0.5, 0.6" <<endl;
    file_3D_hist << "set xrange [ " << minX<<":"<<maxX<< "]" << endl
                 << "set yrange [ " << minY<<":"<<maxY<< "]" << endl
                 << "#set size number axis" << endl
                 << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl;
    
    
    if (max_fc>100.0) {
        file_3D_hist << "set format z '%e'" << endl;
        file_3D_hist << "set zrange [ " << 1 << ":" << max_fc << "]" << endl;
    }else{
        file_3D_hist << "set zrange [ " << 0 << ":" << max_fc << "]" << endl;
    }
    
    // film3Dc
    
    file_3D_hist <<  "set title 'Ligand Concentration' "<< setSizesTitles(sizeTitle::LARGE, NO_SAVE)  << endl;
    file_3D_hist << "set xlabel 'X(mm)' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ylabel 'Y(mm)' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "#set size number axis" << endl
                 << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl;
    // dim
    
    file_3D_hist << "splot nome1 with pm3d notitle" << endl;
    
    
    // Percentage
    file_3D_hist << "set origin 0.0, 0.0\n set size 1.0, 0.4" <<endl;
    file_3D_hist<< "set xrange [ " << 0<<":"<<Dt*dim_col_t<< "]" << endl
                 << "set yrange [ " << 0<<":"<<1.1<< "]" << endl
                 << "set arrow 1 from b_num,0 to b_num,0.1" << endl // nohead identified arrow 1
                 << "set title 'Percentage up/Down Gradient'" << setSizesTitles(sizeTitle::LARGE, NO_SAVE)<< endl
                 << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                 << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                 << "set xlabel 'time' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "set ylabel 'fraction of bacteria' " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
                 << "#set size legend" <<endl
                 << "set key "<<  setSizesTitles(sizeTitle::MEDIUM, NO_SAVE) << endl
                 << "plot 'PercUpDownh.dat' u 1:2 w l title 'down',\\"<< endl
                 << "'PercUpDownh.dat' u 1:3 w l title 'const',\\"<< endl
                 << "'PercUpDownh.dat' u 1:4 w l title 'up',\\"<< endl
                 << "'PercUpDownh.dat' u 1:5 w l title 'mix'"<< endl
                 << "unset arrow 1" << endl
                 << "unset multiplot" << endl;
    
    if (save_==NO_SAVE) {
        if (maxX-minX >5 || maxY-minY >5) {
            file_3D_hist << "pause .01" << endl;
        }else{
            file_3D_hist << "pause .1" << endl;
        }
    }
    
    file_3D_hist<< "b=b+"<< n_threadTot << endl
    << "if(b<" << dim_col_t << ") reread;"<< endl;
    
    file_3D_hist.close();
    
    return 0;
    //*********************************************************************************************
    
}

/*! \brief This function produce a 'local' script for the multi thread and lunch gnuplot
 */
int lunchMultiThread3Dgnuplot(int n_thread, int cont_sim, bool last, int n_max, int n_thread_tot){

    cout << "lunch thread " << n_thread << endl;
    ofstream file_play_video;
    char buffer[12];
    snprintf(buffer, sizeof(char)*12, "sim%03d-Th%d",cont_sim, n_thread);
    string play_video(buffer);
    play_video+="play_video.gnu";
    play_video="SCRIPT-GNUPLOT-"+play_video;
    
    
    // PLAY_VIDEO ... HISTOGRAMS
    file_play_video.open(play_video.c_str());
    file_play_video << "b=" << n_thread+1 << endl;
    
    if (last) {
        file_play_video << "set print \"-\""<< endl;
    }
    file_play_video << "load '"<< setNamescript3DMultiT(cont_sim,n_thread) <<"'" << endl;
    file_play_video << "quit" <<endl;
    file_play_video.close();
    
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    //last is the main thread
    // I lunch normally gnuplot ...
    if (last) {
        lunch_gnuplot(play_video.c_str());
    }else{
        executeCommandLine(play_video);
//        executeCommandLine2(play_video);
    }
    
#else
    if (!last) {
        play_video+=" &";
    }
    
    lunch_gnuplot(play_video.c_str());
#endif

    if (last)
        return checkFrames(n_thread_tot, cont_sim, n_max);
    
    return 0;
}


/*! \brief set name 3D film script for gnuplot file multi-thread
 */
string setNamescript3DMultiT(int cont_sim, int nthread){
    char buffer[16];
    snprintf(buffer, sizeof(char)*16, "sim%03d-th%d",cont_sim,nthread);
    string hist3D(buffer);
    hist3D+="-3D_hist.gnu";
    
//    cout << "setNamescript3DMultiT: " << hist3D << endl;
    
    return hist3D;
}

/*! \brief delete files SCRIPT-GNUPLOT ... play_video.gnu multitherad.
 */

void deleteSCRIPT_GNUPLOTplay_videoMultiT(int cont_sim, int n_thread_tot){
    
    for (int i=0; i<n_thread_tot; i++) {
    
        cout << "delate file thread: " << i << endl;
        ofstream file_play_video;
        char buffer[12];
        snprintf(buffer, sizeof(char)*12, "sim%03d-Th%d",cont_sim, i);
        string play_video(buffer);
        
        play_video+="play_video.gnu";
        play_video="SCRIPT-GNUPLOT-"+play_video;
        cout << "file: " << play_video << endl;
        
        remove(play_video.c_str());
    }
    
}


/*! \brief this function is used to check if the mulithread creation of the frames had some problems ...*/

int checkFrames(int n_thread_tot, int cont_sim, int n_max){
    std::vector<bool> thread_started(n_thread_tot,true); // vector to verify if the other threads started ...
//    bool something_wrong = false;
    struct stat buf;
    
    char buffer1[52];
    bool aspetta = true;
    int cont_times = 0;
    int i_=0;
    int max_loops = 10;
    int max_iter = 9;  // loops to wait ...
//    int n_files = 0;
    
    cout << "n_thread_tot = " << n_thread_tot << endl;
    for (int i=1; i<=n_thread_tot; i++) { // check if some thread didn't probably started ...<----------------------------------TOGLI IL -1!
        cout << "check Frames, i = " << i << endl;
        snprintf(buffer1, sizeof(char) * 52, "sim%03dfilm3Dh%04d.png",cont_sim,i+1);
        if(stat(buffer1, &buf)!=0){
            cout << "something's missing ...\n";
            return -1;
        }
    }
    
    while(aspetta && cont_times<max_iter && i_<= max_loops){
        cout << "The other processes haven't finished yet attempt "<< cont_times << " out of 9.\r" << std::flush;;
        cont_times++;
        
        bool trovati = true;
        
        for (int i=0; i<n_thread_tot; i++) {
            snprintf(buffer1, sizeof(char) * 52, "sim%03dfilm3Dh%04d.png",cont_sim,n_max-1-i);
            bool temp = stat(buffer1, &buf)==0;
            trovati = trovati && temp;
        }
        
        if (!trovati) {
            trovati = true;
            sleep(1);
        }else{
            cout << endl;
            for (int i=0; i<n_thread_tot; i++)
            {
                snprintf(buffer1, sizeof(char) * 52, "sim%03dfilm3Dh%04d.png",cont_sim,n_max-1-i);
                cout << buffer1 << endl;
                bool temp = is_file_exist(buffer1);
                trovati = trovati && temp;
            }
            sleep(1);
            aspetta=false;
        }
        
        // last attemt, this should never happens, however
        if (cont_times>=max_iter) {
            int n_files=0;
            for (int i=1; i<n_max; i++) {
                snprintf(buffer1, sizeof(char) * 52, "sim%03dfilm3Dh%04d.png",cont_sim,i);
                n_files += (stat(buffer1, &buf)==0)?1:0;
            }
            // if not enough files where not created something went wrong (probably)
            if (n_files<n_max/2+1) {
                cout << BOLDRED << "Time out: Not enough frames of the film were created. There might have been a problem. " << endl << RESET;
                return -1;
            }else{
                aspetta = true;
                i_++;
                cont_times=0;
            }
        }
        if (i_>max_loops) {
            cout << BOLDRED << "Time out: the main thread waited for more then 2 minutes the other threads." << endl
                            << "Not all the frames of the film were created. There might have been a problem. " << endl << RESET;
            return -1;
        }
        
    }
    
    return 0;
}


#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)

//////////////////////////////////////////////////////////////////////////////////////////////////
/*! Executes the given command using CreateProcess() and WaitForSingleObject().
// Returns FALSE if the command could not be executed or if the exit code could not be determined.*/
int executeCommandLine(string play_video)
//VERSION 1: modified from http://www.codeproject.com/Tips/333559/CreateProcess-and-wait-for-result
{
    PROCESS_INFORMATION processInformation = {0};
    STARTUPINFO startupInfo                = {0};
    startupInfo.cb                         = sizeof(startupInfo);
    string cmdLine(gnuplotOpen);
    cmdLine.resize(cmdLine.size()-1);
    // I have to pass cmd.exe /k to tell to use the shell ...
    cmdLine=string("cmd.exe /k \"")+cmdLine+string("\"")+play_video;
    int nStrBuffer                         = cmdLine.size() + 50;
    cmdLine.resize(nStrBuffer);
    // Create the process
    BOOL result = CreateProcess(NULL, &cmdLine[0],
                                NULL, NULL, FALSE,
                                NORMAL_PRIORITY_CLASS | CREATE_NO_WINDOW,
                                NULL, NULL, &startupInfo, &processInformation);
//    std::string s;
//    s.resize(max_length);
//    size_t actual_length = SomeApiCall(&s[0], max_length);
//    s.resize(actual_length);
    
    if (!result)
    {   // CreateProcess() failed
        // Get the error from the system
        LPVOID lpMsgBuf;
        DWORD dw = GetLastError();
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
                      NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL);
        
        // Display the error
        
        cout << "::executeCommandLine() failed at CreateProcess()\nCommand: "<< cmdLine <<endl
             << "Error: "<< lpMsgBuf;
        
        // Free resources created by the system
        LocalFree(lpMsgBuf);
        
        // We failed.
        return -1;
    }else{
        cout << "::executeCommandLine() started CreateProcess()\nCommand: "<< cmdLine <<endl;
    }

    return 0;
}

int executeCommandLine2(string play_video)
// VERSION 2:
{
    //    LPCTSTR lpApplicationName = "C:/Windows/System32/cmd.exe"; /* The program to be executed */
//    LPCTSTR lpApplicationName = gnuplotOpen.c_str();
//    
//    STARTUPINFO lpStartupInfo;
//    PROCESS_INFORMATION lpProcessInfo;
//    
//    memset(&lpStartupInfo, 0, sizeof(lpStartupInfo));
//    memset(&lpProcessInfo, 0, sizeof(lpProcessInfo));
//    lpStartupInfo.cb = sizeof (STARTUPINFO);  // required
//    string command_str = /*gnuplotOpen + */play_video;
//    // from string to TCHAR
//    TCHAR *command=new TCHAR[command_str.size()+1];
//    command[command_str.size()]=0;
//    //As much as we'd love to, we can't use memcpy() because
//    //sizeof(TCHAR)==sizeof(char) may not be true:
//    std::copy(command_str.begin(),command_str.end(),command);
//    
//    //        TCHAR command[ ] = /*TEXT(command_str.c_str());*/
//    /* Create the process */
//    if (!CreateProcess(lpApplicationName,
//                       command, NULL, NULL,
//                       FALSE, NULL, NULL, NULL,
//                       &lpStartupInfo,
//                       &lpProcessInfo)
//        ) {
//        std::cerr << "CreateProcess() failed to start program \"" << lpApplicationName << "\"\n";
//        //        exit(1);
//        return -1;
//        }else{
//            
//            std::cout << "Started program \"" << lpApplicationName << " " << command << " successfully\n";
//            return 0;
//        }
    return 0;
}

#endif
