//
//  filmato_3D_gnuplot_gif.cpp
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 14/06/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "filmato_3D_gnuplot_gif.hpp"


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
#include <sstream>
#include <cmath>

#include <limits>
#include <ctime>

#include <sys/stat.h>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "apngasm_Global.h"
#include "ErrorsDefinition.h"
#include "Colori.h"
#include "sssr.h"

#include "Funz_C.h"
#include "setSizesTitles.hpp"
#include "filmato_3D_gnuplotMultiThread.hpp"

#include "Declar_funz.h"

#define SAVE 0
#define NO_SAVE 1
#define DENSITY 0
#define FUNZC   1

using namespace std;



/** This fuction crate the script so save, see save 4,9,16 snapshot of the density and ligand.
 * it is not very well written. there are a lot of if end so on that can be throw away.
 * The fact is that if we save the file and want to see it, then we first save and then play with firefox (better immage)
 * Note: problem lunching firefox with Windows. To be check!
 * note that we have to be careful how to pass the parameters to apngasm if we;re on Unix or Windows (line 213)
 */

void filmato_3D_gnuplot_gif(string names_info[],long double max_x, long double max_y, long double min_x,long double min_y, long double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, long double max_fc)
{
    funz_clearAll();
    
    cout << BOLDRED
    << "--------------------------------------------------" <<endl
    << "-                    CINE_COLI                   -"   << endl
    << "-                     THE FILM               -"   << endl
    << "--------------------------------------------------" << RESET <<endl;

    cout << "Filmato  3d gnuplot" << endl;
    cout << BOLDRED << "no_apngams ... " << endl << RESET;
    char bufferSim[8]; // buffer for prefix
    snprintf(bufferSim, sizeof(char)*8, "sim%03d",cont_gen_sim);
    
    int risp=1;
    
    ofstream file_3D_hist;
    ofstream file_play_video;
    
    
    string title;
    std::ifstream file_info;
    file_info.open(names_info[0].c_str());
    
    int n_data=1;
    //    int j_frame=0;
    long double dt;
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
    }else{
        maxX=max_x; maxY=max_y; minX=min_x; minY=min_y;
    }
    
    int risp_save=1;
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
        
        // CREATION FRAMES ...
        #if NO_M_THREAD     
        time_t start;     
        time(&start); 
        #else     
        auto start = chrono::steady_clock::now(); 
        #endif
        if (risp==0 && (risp_save!=0)) {
            scriptFilmato3Dgnuplot_gif(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, NO_SAVE,cont_gen_sim);
        }
        if (risp_save==0) {
            cout <<"elaboration and saving of the film ...\n";
            scriptFilmato3Dgnuplot_gif(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, SAVE,cont_gen_sim);
        }
        //        string hist3D(bufferSim);
        //        hist3D+="-3D_hist.gnu";
        string play_video(bufferSim);
        play_video+="play_video.gnu";
        play_video="SCRIPT-GNUPLOT-"+play_video;
        
        //    // PLAY_VIDEO ... HISTOGRAMS
        string hist3D = setNamescript3DMultiT(cont_gen_sim,0);
        file_play_video.open(play_video.c_str());
        
        string name_ = names_info[0];
        name_.erase(name_.end()-3, name_.end());
        name_ = name_+"gif";
        
        file_play_video << gnuplotSetTerminalSave_gif << endl
                        << "set print \"-\""<< endl
                        << "set output \""<< name_ << "\""<< endl
                        << "b=1;" << endl
                        << "load '"<< hist3D<<"'" << endl
                        << "set output" << endl;
        
        if (risp==0 && (risp_save!=0)) {
            file_play_video << "pause mouse any" << endl;
        }
        file_play_video<< "quit" <<endl;
        file_play_video.close();
        
        lunch_gnuplot(play_video.c_str());
        
        if (automatic_!=1) {
            
            if (risp_save==0) {
                // Guardo il filmato
                if (risp==0) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                    
                    string command_play_video = firefox_path+std::string(" ")+name_;
                    system(command_play_video.c_str());

#else

                    string command_play_video = firefox_path+std::string(" ")+name_;
//                    cout << "command open .gif: " << command_play_video << endl;
                    system(command_play_video.c_str());


#endif
                }
            }
            
        }
//        cout << "Press a key (int) ";
//        cin >> risp;
        
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
               writeLog("FILM: (single-thread) created and saved in ",msg.str());
        }
        //******************************************************************
        // OVERWRITE THE SCRITS ... not to save ...
        //******************************************************************
        
        file_play_video.open(play_video.c_str());
        
        if (risp==0 && (risp_save!=0))
            file_play_video << gnuplotSetTerminalSave_gif << endl;
        
        file_play_video << "b=1;" << endl
                        << "load '"<< hist3D<<"'" << endl;
        file_play_video << "pause mouse any" << endl;
        file_play_video << "set output" << endl;
        file_play_video<< "quit" <<endl;
        
        file_play_video.close();
        scriptFilmato3Dgnuplot_gif(dt*(epsilon*epsilon), maxX, maxY, minX, minY, max_z, max_fc, dim_col_t, NO_SAVE, cont_gen_sim);
        
        //******************************************************************
        
    }
    

}


/**
 * This function writes the script for the video 3d gnuplot gif version
 */
//***********************************************************************************************
// SCRIPT video without saving, if you decided to save it skeep this, since it produce the "film"
//        .png and then plays it.
//***********************************************************************************************

int scriptFilmato3Dgnuplot_gif(long double Dt/*dt*(epsilon*epsilon)*/, long double maxX, long double maxY, long double minX, long double minY, long double max_z, long double max_fc, int dim_col_t, int save_, int cont_sim){
    
    char buffer[8];
    snprintf(buffer, sizeof(char)*8, "sim%03d",cont_sim);
    
    
    string hist3D = setNamescript3DMultiT(cont_sim,0);
    
    ofstream file_3D_hist;
    file_3D_hist.open(hist3D.c_str());
    
    if (!file_3D_hist.is_open()) {
        cout << "Error opening file '3D_hist.gnu'\n";
        
        string what("ERROR in function: scriptFilmato3Dgnuplot (filmato_3D_gnuplot_gif.cpp, line 259)");
        string msg("Error opening file ");
        msg+=hist3D;
        writeLog(what,msg);
        
        return ERROR_OPENING_FILE;
    }

    if (save_!=SAVE) {
        file_3D_hist << gnuplotSetTerminalPlot << endl;
        
        file_3D_hist << "#nome_out = sprintf('sim%03dfilm3Dh%04d.png',"<<cont_sim<<",b)" << endl
        << "#"<< gnuplotSetTerminalSave_png << endl
        << "# set output nome_out # output=fileout"<< endl;
    }
    file_3D_hist << "num_frame = sprintf('saving frame %d out of %d ... ',b,"<< dim_col_t <<")" << endl;
    file_3D_hist << "print num_frame"<< endl;
    file_3D_hist << "#set size number axis" << endl
    << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl
    << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, NO_SAVE)<< endl;
    
    //    file_3D_hist << "set size 1, 1" << endl;
    
    //*********************************************************
    
    file_3D_hist << "b_num=b*"<< Dt << endl;
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
    
    file_3D_hist<< "b=b+1" << endl
    << "if(b<" << dim_col_t << ") reread;"<< endl;
    
    file_3D_hist.close();
    
    return 0;
    //*********************************************************************************************
    
}


