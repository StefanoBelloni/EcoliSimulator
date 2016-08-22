//
//  gnuplotFunzInternalDynalmic.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 29/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <iomanip>
#include <fstream>
#include <cmath>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "sssr.h"

#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rIG_tExp.h"
#include "CV_rExp_tExp.h"
#include "EO_rExp_tExp.h"
#include "EO_rIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "ParameterEstimation_CV_rExp_tExp.h"
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "Funz_C.h"

#include "setSizesTitles.hpp"


enum tipoResponse{
    EXP = 0,
    IG = 1
};

void lunch_gnuplot(string name_file_gnu);
void writeScriptInternalDyn(int save_conform, string title, string fileDati, int ig, int cont_sim);
string setNameScriptIntDyn(int gen_con_sim, int save_conform);


// Check if a file exists!!
bool is_file_exist(const char* fileName);


//***************************************************************************************************

void E_coli::gnuplotFunzInternalDynalmic(string title, int save_, int gen_cont_sim){

//    cout << "The response function is the inverse of the mean run tumble: " << 1/tau_r << endl;
    
    title.erase(title.end()-4, title.end());
    

    std::ofstream file_gnu;
    
    
    int save_conform = (save_==1)?0:1;
    
    char buffer[8];
    snprintf(buffer, sizeof(char)*8, "sim-%03d",gen_cont_sim);
    
    string dynFile(buffer);
    dynFile+="dynamic.dat";

    
    int tipo = saveIntDyn(dynFile);
    
    writeScriptInternalDyn(sizeTitle::SAVE, title, dynFile, tipo, gen_cont_sim);
    writeScriptInternalDyn(sizeTitle::NO_SAVE, title, dynFile, tipo, gen_cont_sim);
    
    if (save_conform==sizeTitle::NO_SAVE) {
        lunch_gnuplot(setNameScriptIntDyn(gen_cont_sim, sizeTitle::NO_SAVE));
    }

    lunch_gnuplot(setNameScriptIntDyn(gen_cont_sim, sizeTitle::SAVE));

}


/*! \brief Write the script for the internal dynamics
 */

void writeScriptInternalDyn(int save_conform, string title, string fileDati, int ig, int cont_sim){
    
    string nameFile = setNameScriptIntDyn(cont_sim, save_conform);
    
    std::ofstream file_single_plot;
    
    file_single_plot.open(nameFile.c_str());
    
    if (save_conform==sizeTitle::NO_SAVE) {
        file_single_plot << gnuplotSetTerminalPlot << endl;
    } else {
        file_single_plot << gnuplotSetTerminalSave_eps << endl;
//        file_single_plot << "set size ratio 0.71" << endl;
        string buffer = "_FunzRisp.eps";
        string title_out=title+buffer;
        file_single_plot << "set output \""<< title_out <<"\"" << endl;
        
    }

    // EXPONENTIAL DISTRIBUTION
    
    if (ig == EXP) {
    
        file_single_plot << "set title \"Response Functions "<< title << "\""
                         << setSizesTitles(sizeTitle::HUGE_, save_conform) << endl;
        file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
        file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 'memory variable' "<< setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "set ylabel 'inverse probability rate to tumble g(Q)' "<< setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "#set size number axis" << endl
                        << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "set key" << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl;
        
        file_single_plot << "plot \""<< fileDati <<"\" u 1:2 w l title 'g(Q)',"
                         << " (1-2/pi*atan(pi*x/2))/.8 w l title '(1-2/{/Symbol p}atan({/Symbol p}/2 x))/0.8"<< std::endl;

//        {/Symbol p}
        
    }else{
        
        // WITH NON ZERO DIFFUSION COEFFICIENT
        
        file_single_plot << "set multiplot layout 2,1 title \"Response Functions "<< title << "\""
                         << setSizesTitles(sizeTitle::HUGE_, save_conform)<< endl
                         << "set key" << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl;
        file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
        file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 'memory term' "
                        << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "set ylabel 'inverse probability rate to tumble g(Q)' "
                         << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl;
        file_single_plot << "plot \""<< fileDati << "\" u 1:2 w l title 'g(Q)'" << endl;
        file_single_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
        file_single_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                        << "set xlabel 'memory variable' "
                        << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl
                        << "set ylabel 'diffusion coefficient SDE (sigma)' "
                        << setSizesTitles(sizeTitle::MEDIUM, save_conform)<< endl;
        file_single_plot << "plot \""<< fileDati <<"\" u 1:3 w l title 'sigma(Q)'" << endl;
        file_single_plot << "unset multiplot" << endl;
        
    }
    
    if (save_conform==sizeTitle::NO_SAVE) {
        file_single_plot << "pause mouse any" << endl;
    }
    
    
    file_single_plot.close();
    
    
}

/*! \brief the modify name for 'plot_batterium.gnu'
 */

string setNameScriptIntDyn(int gen_con_sim, int save_conform){
    
    char buffer[8];
    snprintf(buffer, sizeof(char)*8, "sim-%03d",gen_con_sim);
    
    string file_gnuName = "SCRIPT-GNUPLOT-";
    file_gnuName+=buffer;
    file_gnuName+=(save_conform==sizeTitle::SAVE)?"-save-int_dyn.gnu":"-visual-int_dyn.gnu";
    
    return file_gnuName;
    
}


//[x]*******************************************************

int E_coli::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        long double Q_min=-2;
        long double Q_max=2;
        long double dQ= 0.01;
        
        file_dat.open(dynFile.c_str());
        
        while (Q_min<=Q_max) {
            
            file_dat << Q_min << " " << 1/tau_r << endl;
            Q_min+=dQ;
        }
        
        file_dat.close();
    }
    
    return EXP;
}

//[x]*******************************************************

int CV_rExp_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        long double Q_min=-2;
        long double Q_max=2;
        long double dQ= 0.01;
        
        file_dat.open(dynFile.c_str());
        
        while (Q_min<=Q_max) {
            Q=Q_min;
            file_dat << Q_min << " " << f_lambda() << endl;
            Q_min+=dQ;
        }
        
        file_dat.close();
    }
    
    return EXP;
}

//[x]*******************************************************

int CV_rIG_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        long double Q_min=-2;
        long double Q_max=2;
        long double dQ= 0.01;
        
        file_dat.open(dynFile.c_str());
        
        while (Q_min<=Q_max) {
            Q=Q_min;
            file_dat << Q_min << " " << f_lambda() << " " << f_sigma() << endl;
            //cout << Q_min << " " << f_lambda() << " " << f_sigma() << endl;
            //file_dat << Q_min << " " << 1/tau_r << endl;
            Q_min+=dQ;
        }
        
        file_dat.close();
    }
    
    return IG;
}

//[x]*******************************************************

int EO_rExp_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        long double Q_min=-2;
        long double Q_max=2;
        long double dQ= 0.01;
        
        file_dat.open(dynFile.c_str());
        
        while (Q_min<=Q_max) {
            m[0]=Q_min;
            file_dat << Q_min << " " << f_lambda() << endl;
            Q_min+=dQ;
        }
        
        file_dat.close();
    }
    
    return EXP;
}

//[x]*******************************************************

int EO_rIG_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        long double Q_min=-2;
        long double Q_max=2;
        long double dQ= 0.01;
        
        file_dat.open(dynFile.c_str());
        
        while (Q_min<=Q_max) {
            m[0]=Q_min;
            file_dat << Q_min << " " << f_lambda() << " " << f_sigma() << endl;
            Q_min+=dQ;
        }
        
        file_dat.close();
    }
    
    return IG;
}

//[x]*******************************************************

int ParameterEstimation_CV_rExp_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        
        file_dat.open(dynFile.c_str());
        
        file_dat.open("dynamic.dat");
        
        int n_r = (int)s_lambda_r.lambda.size();
        
        cout << "ParameterEstimation_CV_rExp_tExp\n";
        cout << "n_r = " << n_r << endl;
        for (int i=0; i<n_r; i++) {
            file_dat << s_lambda_r.syntetic_indeX[i] << " " << s_lambda_r.lambda[i] << endl;
        }
        
        file_dat.close();
    }
    
    return EXP;
}

//[x]*******************************************************

int ParameterEstimation_CV_rIG_tExp::saveIntDyn(string dynFile){
    
    // QUESTA DEVE DIVENTARE UNA FUNZIONE ...
    
    ofstream file_dat;
    
    if (!is_file_exist(dynFile.c_str())) {
        
        file_dat.open(dynFile.c_str());
        
        int n_r = (int)s_lambda_r.lambda.size();
        
        for (int i=0; i<n_r; i++) {
            
            file_dat << s_lambda_r.syntetic_indeX[i] << " " << s_lambda_r.lambda[i] << " " << s_lambda_r.sigma[i] << endl;
            
        }
        
        file_dat.close();
    }
    
    return IG;
}

//[x]*******************************************************
