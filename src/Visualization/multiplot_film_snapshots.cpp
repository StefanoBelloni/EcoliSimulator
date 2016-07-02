//
//  multiplot_film_snapshots.cpp
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 13/06/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <cmath>
#include <fstream>

#include "multiplot_film_snapshots.h"
//#include "filmato_3D_gnuplotMultiThread.hpp"
#include "GnuplotGlobal.h"

#define SAVE_multi 0
#define NO_SAVE_multi 1
#define DENSITY_multi 0
#define FUNZC_multi   1

using namespace std;

/*! \brief gnuplot Multiplot
 */
void gnuplot_Multiplot(Funz_C *f, int dim_col_t, int cont_gen_sim, string names_info,
                       double min_x, double max_x, double min_y, double max_y, double max_z, double max_fc)
//*************************
// MULTIPLOT ...
{
    
    int risp=0;
    
    
    int risp_n=4;
    cout << "How many n? 4, 9, 16 ... ";
    sssr(risp_n,"How many n? 4, 9, 16 ... ");

    if (automatic_==1) {
        return;
    }
    
    // gather informations ...
    std::ifstream file_info;
    file_info.open(names_info.c_str());
    string title;
    int n_data=1;
    double dt;
    cout << "names_info[0] = " << names_info[0] << endl;
    
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    file_info >> n_data; // const_salv
    
    dt=dt*n_data;
    file_info.close();
//    
//    cout << "###################### (void gnuplot_Multiplot ... )" << endl;
//    cout << "dt:= " << dt << endl;
    
    ofstream file_play_video;
    char buffer[32];
    char bufferSim[8]; // buffer for prefix
    snprintf(bufferSim, sizeof(char)*8, "sim%03d",cont_gen_sim);

    
    if (automatic_!=1) {
        
        cout << BOLDRED << "Take care that there are two windows: they might be overlapping ... \n" << RESET;
        if (!(risp_n==4||risp_n==9||risp_n==16)) {
            cout << "Default n = 4 ";
            risp_n=4;
        }
        vector<int> frame_n;
        frame_n.resize(risp_n);
        // if interact I start from the first frame, otherwise no, sinse the delta concentartion is not displayed properly ...
        frame_n[0]=(f->interact==0)?1:2;
        for (int j=1; j<risp_n-1; j++) {
            frame_n[j]=frame_n[j-1]+floor(dim_col_t/(risp_n-1));
        }
        frame_n[risp_n-1]=dim_col_t-1;
        
        // visualizzazione
        string multiplot_hist(bufferSim);
        multiplot_hist="SCRIPT-GNUPLOT-"+multiplot_hist;
        multiplot_hist+="visual-multi_plot_hist.gnu";
        //********************************************
        // SCRIPT MULTI_PLOT DENSITY AND C(t,x)
        file_play_video.open(multiplot_hist.c_str());
        file_play_video << gnuplotSetTerminalPlot << endl;
        file_play_video << "b = 1" << endl;
        snprintf(buffer, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 0);
        file_play_video << "load \""<< buffer <<"\"" << endl;
        file_play_video << gnuplotSetTerminalPlot << " 1" << endl;
        snprintf(buffer, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 1);
        file_play_video << "load \""<< buffer <<"\"" << endl;
        file_play_video << gnuplotSetTerminalPlot << " 2" << endl;
        file_play_video << "set size noratio" << endl;
        string fileNamePerc = title+"_percentage.gnu";
        file_play_video << "load \""<< fileNamePerc << "\"" << endl;
        file_play_video << "pause mouse any" << endl
        << "quit" <<endl;
        file_play_video.close();
        
        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_z, frame_n, dt*epsilon*epsilon, DENSITY_multi, NO_SAVE_multi,cont_gen_sim);
        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_fc, frame_n, dt*epsilon*epsilon, FUNZC_multi, NO_SAVE_multi,cont_gen_sim);
        scriptUpDownPer(title,dim_col_t*dt*epsilon*epsilon,NO_SAVE_multi);
        
        if (automatic_==0) {
            lunch_gnuplot(multiplot_hist.c_str());
        }
        risp=0;
        
        // One might save while showing the plot, using replot ... or just in th same script ...
//        string multiplot_hist;
        char buffer[32];
        
        //***********************************
        //DENSITY MULTIPLOT
        multiplot_hist=bufferSim;
        multiplot_hist+="save-multi_plot_histDensity.gnu";
        file_play_video.open(multiplot_hist.c_str());
        
        if (!file_play_video.is_open()) {
            cout << "Error opening files ... " <<endl;
        }
        
        file_play_video << gnuplotSetTerminalSave_eps << endl;
        snprintf(buffer, sizeof(char) * 32,"sim-%03d_density.eps", cont_gen_sim);
        file_play_video << "set output \""<< buffer << "\"" <<endl;
        file_play_video << "b = 1" << endl;
        char bufferTitle0[32];
        snprintf(bufferTitle0, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 0);
        file_play_video << "load \""<< bufferTitle0 <<"\"" << endl;
        file_play_video << "set output " << endl;
        file_play_video.close();
        
        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_z, frame_n, dt*epsilon*epsilon, DENSITY_multi, SAVE_multi,cont_gen_sim);
        lunch_gnuplot(multiplot_hist.c_str());
        
        //***********************
        //FUNZC MULTIPLOT
        char bufferTitle1[32];
        snprintf(bufferTitle1, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 1);
        multiplot_hist=bufferSim;
        multiplot_hist+="save-multi_plot_histLigand.gnu";
        file_play_video.open(multiplot_hist.c_str());
        file_play_video << gnuplotSetTerminalSave_eps << endl;
        snprintf(buffer, sizeof(char) * 32,"sim-%03d_dLigand.eps", cont_gen_sim);
        file_play_video << "set output \""<< buffer <<"\""<<endl;
        file_play_video << "b = 1" << endl;
        file_play_video << "load \""<< bufferTitle1 <<"\"" << endl;
        file_play_video << "set output" <<endl;
        file_play_video << "quit" <<endl;
        file_play_video.close();
        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_fc, frame_n, dt*epsilon*epsilon, FUNZC_multi, SAVE_multi,cont_gen_sim);
        lunch_gnuplot(multiplot_hist.c_str());
        
        //***********************
        // PERCENTUALE ...
        multiplot_hist=bufferSim;
        multiplot_hist+="save-multi_plot_histUpD.gnu";
        file_play_video.open(multiplot_hist.c_str());
        file_play_video << gnuplotSetTerminalSave_eps << endl;
        snprintf(buffer, sizeof(char) * 32,"sim-%03d_dPerc.eps", cont_gen_sim);
        /*string */fileNamePerc = title+"_percentage.gnu";
        file_play_video << "set output \""<< buffer <<"\""<<endl;
        file_play_video << "b = 1" << endl;
        file_play_video << "load \""<< fileNamePerc << "\"" << endl;
        file_play_video << "set output" <<endl;
        file_play_video << "quit" <<endl;
        file_play_video.close();
        scriptUpDownPer(title,dim_col_t*dt*epsilon*epsilon,SAVE_multi);
        
        if (risp==0) {
            lunch_gnuplot(multiplot_hist.c_str());
        }
    }
    
    //        // SCRIPT ...
    //        char buffer[32];
    //        snprintf(buffer, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 0);
    //        string multiplot_hist(bufferSim);
    //        multiplot_hist+="visual-multi_plot_hist.gnu";
    //
    //        file_play_video.open(multiplot_hist.c_str());
    //        file_play_video << gnuplotSetTerminalPlot << endl;
    //        file_play_video << "b = 1" << endl;
    //        file_play_video << "load \""<< buffer <<"\"" << endl;
    //        file_play_video << gnuplotSetTerminalPlot << " 1" << endl;
    //        snprintf(buffer, sizeof(char) * 32,"sim%03d3D_hist%d.gnu",cont_gen_sim, 1);
    //        file_play_video << "load \""<< buffer <<"\"" << endl;
    //        file_play_video << gnuplotSetTerminalPlot << " 2" << endl;
    //        file_play_video << "set size noratio" << endl;
    //        string fileNamePerc = title+"_percentage.gnu";
    //        file_play_video << "load \""<< fileNamePerc << "\"" << endl;
    //        file_play_video << "pause mouse any" << endl
    //                        << "quit" <<endl;
    //        file_play_video.close();
    //        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_z, frame_n, dt*epsilon*epsilon, DENSITY, NO_SAVE,cont_gen_sim,1);
    //        scriptMultiPlot(risp_n, title, min_x, max_x, min_y, max_y, max_fc, frame_n, dt*epsilon*epsilon, FUNZC, NO_SAVE,cont_gen_sim,1);
    //        scriptUpDownPer(title,dim_col_t*dt*epsilon*epsilon,NO_SAVE,1);
        
    
    
}