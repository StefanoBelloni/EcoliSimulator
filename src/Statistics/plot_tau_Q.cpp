//
//  plot_tau_Q.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 03/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Q_tau_stat.h"
#include "s_lambda.h"
#include <vector>
#include <fstream>
#include "GnuplotGlobal.h"

void lunch_gnuplot(std::string name_file_gnu);
bool is_file_exist(const char *fileName);

int plot_tau_Q(std::string title_, std::vector<Q_tau_stat> &vet_stat, int save_, int iterate){
    
    // save_!=0 salvo
    
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
    
    
    
    double mean_Poisson=0;
    
    int dim_vet=(int)vet_stat.size();
    
    if (!is_file_exist("statistical_data.dat")) {
    
        statistics_data.open("statistical_data.dat");
        if (!statistics_data.is_open()) {
            std::cout << "ERROR OPENING FILES STATISTICAL DATA ...\n";
            return -1;
        }

        for (int i=0; i<dim_vet; i++) {
            mean_Poisson = (vet_stat[i].n_rec==0)?-1.0:vet_stat[i].max_tau/vet_stat[i].n_rec;
//            statistics_data << vet_stat[i].Q << " "<< vet_stat[i].mean << " " << vet_stat[i].invX << " " << vet_stat[i].V_IG() << " " << mean_Poisson << std::endl;
            
            statistics_data << vet_stat[i].Q << " "<< vet_stat[i].mean << " " << vet_stat[i].invX << " " << vet_stat[i].n_rec << " " << mean_Poisson << std::endl;
        }
        
        statistics_data.close();
    }
    
    // PLOT ******
    
    statistics_plot << "set multiplot layout 2,2 title \"Plot Statistics "<< title_ << "\" font \",14\""<< std::endl;
    
    
    // MEAN
    //********************************************************************************************
    {
        

        std::cout << "* Position " << std::endl;
        if (save_==0) {
            statistics_plot << "stats \"statistical_data.dat\" u 1:2 name 'LigandConcentration'"<<std::endl;
        }
        
        statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
        statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
                        << "set xlabel 'Q' "<< std::endl
                        << "set ylabel 'mean' "<< std::endl;
        statistics_plot << "set title \" Mean \" font \",14\""<< std::endl;
        statistics_plot << "plot \"statistical_data.dat\" u 1:2 w l title 'mean(Q)'" << std::endl;
        
    }
    // 1/X
    //********************************************************************************************    
    {
        
        std::cout << "** 1/X " << std::endl;
        if (save_==0) {            
            statistics_plot << "stats \"statistical_data.dat\" u 1:3 name 'InvMean'"<<std::endl;
        }
        statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
        statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
                        << "set xlabel 'Q' "<< std::endl
                        << "set ylabel 'InvMean' "<< std::endl;
        
        statistics_plot << "set title \" Mean(1/X) \" font \",14\""<< std::endl;
        statistics_plot << "plot \"statistical_data.dat\" u 1:3 w l title 'InvMean(Q)'" << std::endl;
        
    }    
    // N_rec
    //********************************************************************************************
    {
        
        std::cout << "*** N_rec " << std::endl;
        statistics_plot << "set title \"N_rec\" "<< std::endl;
        if (save_==0) {
            statistics_plot << "stats \"statistical_data.dat\" u 4 name 'Vn'"<<std::endl;
        }
        statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
        statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
                        << "set xlabel 'Q' "<< std::endl
                        << "set ylabel 'N_rec' "<< std::endl;
        
        statistics_plot << "set title \" N_rec \" font \",14\""<< std::endl;
        statistics_plot << "plot \"statistical_data.dat\" u 1:4 w l title 'N_rec(Q)'" << std::endl;
        
    }
    // Poisson Mean
    //********************************************************************************************
    {
        
        std::cout << "**** Poisson mean " << std::endl;
        statistics_plot << "set title \"maxT/n\" "<< std::endl;
        if (save_==0) {
            statistics_plot << "stats \"statistical_data.dat\" u 1:5 name 'maxTn'"<<std::endl;
        }
        statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
        statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
        << "set xlabel 'Q' "<< std::endl
        << "set ylabel 'PossMean' "<< std::endl;
        
        statistics_plot << "set title \" maxT/n \" font \",14\""<< std::endl;
        statistics_plot << "plot \"statistical_data.dat\" u 1:5 w l title 'PossMean(Q)'" << std::endl;
        
    }
    
    statistics_plot << "unset multiplot" << std::endl;
    
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
        snprintf(buffer1, sizeof(char) * 32,"-stat-iterate-%03d.eps",iterate);
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
        plot_tau_Q(title_, vet_stat, 1,iterate);
    }
    
    return 0;
    
}

//*******************************************

int plot_lambda(std::string title_, s_lambda &lambda, int save_, int iterate){

    // save_!=0 salvo
    
    std::ofstream statistics_plot;
    std::ofstream statistics_data; 
    std::ofstream file_gnu("file_gnu.gnu");
    // Statistical data is so strucured:
    // Q | mean | 1/X | sum 1/X-1/mean | mean_Poisson/-1
    
    statistics_plot.open("MLQ_plot.gnu");
    
    if ((!statistics_plot.is_open())) {
        std::cout << "ERROR OPENING FILES STATISTICAL PLOT...\n";
        return -1;
    }

    
    int dim_vet=(int)lambda.lambda.size();
    
    if (!is_file_exist("MLQ_data.dat")) {
        
        statistics_data.open("MLQ_data.dat");
        if (!statistics_data.is_open()) {
            std::cout << "ERROR OPENING FILES STATISTICAL DATA ...\n";
            return -1;
        }
        
        if (lambda.sigma.size()<lambda.lambda.size()) {
            for (int i=0; i<dim_vet; i++) {
                
                statistics_data <<lambda.syntetic_indeX[i] << " " << lambda.lambda[i] << std::endl;
            }
        }else {
            for (int i=0; i<dim_vet; i++) {
                
                statistics_data <<lambda.syntetic_indeX[i] << " " << lambda.lambda[i] << " " << lambda.sigma[i]<< std::endl;
            }
        }
        

        
        statistics_data.close();
    }
    
    
    
    //*************************************************************************************************
    // PLOT LAMBDA
    //*************************************************************************************************
    
    if (lambda.sigma.size()<lambda.lambda.size()) {
    
        // PLOT ******
        
        statistics_plot << "set title \"Smooth Lambda "<< title_ <<"-It-"<< iterate <<"\" font \",14\""<< std::endl;

        // MEAN
        {
            
            
            std::cout << "* Position " << std::endl;
            if (save_==0) {
                statistics_plot << "stats \"MLQ_data.dat\" u 1:2 name 'MLQ'"<<std::endl;
            }
            
            statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
            statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
            << "set xlabel 'Q' "<< std::endl
            << "set ylabel 'mean' "<< std::endl;
            
            statistics_plot << "plot \"MLQ_data.dat\" u 1:2 w l title 'l_s(Q)',"
                            << " (1-2/pi*atan(pi*x/2))/.8 w l title 'l(Q)"<< std::endl;
            
        }
        
        //*************************************************************************************************
    
    }else {
        
        //*************************************************************************************************
        // PLOT LAMBDA + SIGMA
        //*************************************************************************************************
        
        // PLOT ******
        
        statistics_plot << "set multiplot layout 2,1 title \"Smooth Lambda sigma "<< title_ <<"-It-"<< iterate <<"\" font \",14\""<< std::endl;
        
        // MEAN + SIGMA
        {
            
            
            std::cout << "* Position " << std::endl;
            if (save_==0) {
                statistics_plot << "stats \"MLQ_data.dat\" u 1:2 name 'lMLQ'"<<std::endl;
                statistics_plot << "stats \"MLQ_data.dat\" u 1:3 name 'sMLQ'"<<std::endl;
            }
            
            statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
            statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
            << "set xlabel 'Q' "<< std::endl
            << "set ylabel 'mean' "<< std::endl;
            statistics_plot << "set title 'lambda'"<< std::endl;
            statistics_plot << "plot \"MLQ_data.dat\" u 1:2 w l title 'l_s(Q)',"
            << " (1-2/pi*atan(pi*x/2))/.8 w l title 'l(Q)"<< std::endl;
            
            statistics_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl;
            statistics_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << std::endl
            << "set xlabel 'Q' "<< std::endl
            << "set ylabel 'sigma' "<< std::endl;
            statistics_plot << "set title 'sigma'"<< std::endl; 
            statistics_plot << "plot \"MLQ_data.dat\" u 1:3 w l title 's_s(Q)'" << std::endl;
            statistics_plot << "unset multiplot" << std::endl;
            
        }
        
        //*************************************************************************************************
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
        snprintf(buffer1, sizeof(char) * 32,"-MLQ-It-%03d.eps",iterate);
        buffer.erase(buffer.end()-4,buffer.end());
        std::cout << buffer << std::endl;
        buffer=buffer+buffer1;
        file_gnu << "set output \""<< buffer <<std::endl;
        
    }
    
    file_gnu << "b=1;" << std::endl
    << "load \"MLQ_plot.gnu\""<< std::endl;
    
    if (save_!=0) {
        file_gnu << "set output" << std::endl;
        file_gnu << " " << std::endl;
    }
    
    file_gnu << "quit" <<std::endl;
    
    file_gnu.close();
    
    
    lunch_gnuplot("file_gnu.gnu");
    
    if (save_==0) {
        plot_lambda(title_, lambda, 1,iterate);
    }

    return 0;
}
