//
//  Histogram_2D.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 10/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <cmath>

#include "GnuplotGlobal.h"

using namespace std;

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

void lunch_gnuplot(string name_file_gnu);

/**
 * This program produce a 2D histogram
 * @param name_info_mod[] info about title of histogram, n data and dt
 * @param name_files_tau_mod[] index[0] name file where runs are saved, index [1], same for tumbles ....
 */

void Histogram_2D(string name_info_mod[],string name_files_tau_mod[], int save_, int cont_glob_sim){
    
    // if save_ == 1 -> salvo
    // if save_ == 0 -> 'plotto'
    
    std::ofstream file_single_plot("plot_batterium.gnu");
    std::ofstream file_gnu("file_gnu.gnu");
    
    string title;
    int n_data;
    long double dt;
    
    std::ifstream file_info;
    file_info.open(name_info_mod[0].c_str());
    
    file_info >> title;
    file_info >> n_data;
    file_info >> dt;
    
    //******************************************************
    //                      RUN
    //******************************************************
    
    ifstream file_tau(name_files_tau_mod[0].c_str());
    string temp_string;
    int n_salti=0;
    
    while (!file_tau.eof()) {
        getline(file_tau,temp_string); 
        n_salti++;
    }
    file_tau.close();
    
    cout << "Analysis Runs " << endl;
    
    n_salti=max(200,sqrt(n_salti));
    long double a=10.0/n_salti;
    

    //Primo Metodo
    
    //            file_single_plot << "set xrange [0:7]" << endl;
    ////            file_single_plot << "binwidth=5" << endl;
    //            file_single_plot << "width="<<a<<"#interval width ;"<< endl; 
    //            file_single_plot << "hist(x,width)=width*floor(x/width)+width/2.0;" << endl;
    //            file_single_plot <<" set boxwidth width*0.9;" << endl;
    ////            file_single_plot <<" set boxwidth binwidth" << endl;
    //            file_single_plot << "plot \""<< names_files_tau_mod[0]  <<"\" u (hist($2,width)):(2.0) smooth freq w boxes lc rgb \"blue\";" << endl;
    
    //Secondo Metodo
    
    file_single_plot << "set multiplot layout 2,1" << endl;
    
    file_single_plot << "set xrange [0:7]" << endl;
    file_single_plot <<  "Min = 0.0 # where binning starts" << endl
                    << "Max = 7.0 # where binning ends" << endl;

    if(save_==0){
        file_single_plot << "stats \""<< name_files_tau_mod[0]  <<"\" u 2 name 'runDistributions'"<<endl;
    }
    file_single_plot << "width = "<< a << endl
                     << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl
                     << "plot \""<< name_files_tau_mod[0]  <<"\" using (bin($2)):(1.0) smooth freq with boxes lc rgb \"blue\"" << endl;
    
    //            After the first line add a new line "stats 'data.dat' u 1". And modify the last line to "plot "data.dat" u (hist($1,width)):(1.0)/STATS_records smooth freq w boxes lc rgb"green" notitle". Then the relative frequencies is plotted.
    
    //******************************************************
    //                      TUMBLE
    //******************************************************
    
    file_tau.open(name_files_tau_mod[0].c_str());
    n_salti=0;
    
    while (!file_tau.eof()) {
        getline(file_tau,temp_string); 
        n_salti++;
    }
    file_tau.close();
    
    cout << "Analysis Tumbles " << endl;
    
    n_salti=max(50,sqrt(n_salti));
    a=1.6/n_salti;
    
    file_single_plot << "set xrange [0:1.6]" << endl;
    file_single_plot <<  "Min = 0.0 # where binning starts" << endl
                     << "Max = 1.6 # where binning ends" << endl;
    if (save_==0) {
        file_single_plot << "stats \""<< name_files_tau_mod[1]  <<"\" u 2 name 'tumbleDistribution'"<<endl;
    }
    file_single_plot << "width = "<< a << endl
    << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl
    << "plot \""<< name_files_tau_mod[1]  <<"\" using (bin($2)):(1.0) smooth freq with boxes lc rgb \"blue\"" << endl
    <<"unset multiplot"<<endl;
    
    if (save_==0) {
        file_single_plot <<"pause mouse any" << endl;
    }
    
    file_single_plot.close();
    
    if (save_==0) {
        file_gnu << gnuplotSetTerminalPlot << endl;
    }else {
        file_gnu << gnuplotSetTerminalSave_eps << endl;    
        
        char buffer1[16];
        string buffer = "_hist.eps";
        snprintf(buffer1, sizeof(char) * 16,"sim-%03d-", cont_glob_sim);
        title=buffer1+title+buffer;
        file_gnu << "set output \""<< title <<endl;
        
    }
    file_gnu << "b=1;" << endl
    << "load \"plot_batterium.gnu\""<< endl;
    
    if (save_!=0) {
        file_gnu << "set output" << endl;
        file_gnu << " " << endl;
    }

    file_gnu << "quit" << endl;
    
    file_gnu.close();
    
    lunch_gnuplot("file_gnu.gnu");

    
}
