//
//  plot_goodness_fit.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 05/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

/*
  Aggiungere up and down bounds !!  []
  Calcolare il fit                  []
 */

#include <iostream>
#include <fstream>
#include <cmath>

#include "GnuplotGlobal.h"

using namespace std;

void lunch_gnuplot(std::string name_file_gnu);

/**
 * This function plots the goodness of fitness, comparing the data obtain with the diagonal and its upper and lower bound,
 * It visualize the goodness_fit test, it gives more insight in it.
 */

int plot_goodness_fit(std::string title_, int n_data, int save_, int n_iterata){
    
    std::ofstream statistics_plot;
    std::ofstream statistics_data; 
    std::ofstream file_gnu("file_gnu.gnu");
    // Statistical data is so strucured:
    // Q | mean | 1/X | sum 1/X-1/mean | mean_Poisson/-1
    
    statistics_plot.open("statistical_plot.gnu");
    
    if ((!statistics_plot.is_open())) {
        std::cout << "ERROR OPENING FILES STATISTICAL PLOT...\n";
        return -1;
    }

    
    // PLOT ******
    
    statistics_plot << "set title \"Goodness-of-Fit "<< title_ << "\" font \",14\""<< std::endl;
    
    
    // FIT OF GOODNESS
    //********************************************************************************************
    {
        

        std::cout << "* Goodness of Fit " << std::endl;
        if (save_==0) {
            statistics_plot << "stats \"dati_goodness.dat\" u 1:2 name 'GooodF'"<<std::endl;
        }
        
        statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
        statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
        << "set xlabel 'u' "<< std::endl
        << "set ylabel 'F(u)' "<< std::endl;
        statistics_plot << "plot \"dati_goodness.dat\" u 1:2 w l title 'Fit(U)', x w l title 'Uniform'" 
                        << ",x+1.358/"<<sqrt(n_data) <<" w l title 'Up'"
                        << ",x-1.358/"<<sqrt(n_data) <<" w l title 'Up'"<< std::endl;
        
    }
    
    if (save_==0) {
        statistics_plot << "pause mouse any" << std::endl;
        statistics_plot << "quit" << std::endl;        
    }
    
    
    statistics_plot.close();
    
    if (save_==0) {
        file_gnu << gnuplotSetTerminalPlot << std::endl;
    } else {
        file_gnu << gnuplotSetTerminalSave_eps << std::endl; 
        //        file_gnu << "set size ratio 0.71" << std::endl;
        
        char buffer1[32];
        std::string buffer=title_;
        snprintf(buffer1, sizeof(char) * 32,"-goodFit-It-%03d.eps",n_iterata);
        buffer.erase(buffer.end()-4,buffer.end());
        std::cout << buffer << std::endl;
        buffer=buffer+buffer1;
        file_gnu << "set output \""<< buffer <<std::endl;
        
    }
    
    file_gnu << "b=1;" << std::endl
    << "load \"statistical_plot.gnu\""<< std::endl;
    
    if (save_!=0) {
        file_gnu << "set output" << std::endl;
        file_gnu << " " << std::endl;
    }
    
    file_gnu << "quit" <<std::endl;
    
    file_gnu.close();
    
    
    lunch_gnuplot("file_gnu.gnu");
    
    if (save_==0) {
        plot_goodness_fit(title_, n_data, 1,n_iterata);
    }
    
    return 0;  
    
    
    
}