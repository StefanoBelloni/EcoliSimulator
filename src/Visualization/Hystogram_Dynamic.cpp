//
//  Hystogram_Dynamic.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 03/08/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cmath>

#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "ErrorsDefinition.h"


#include "setSizesTitles.hpp"

using std::cout;
using std::endl;
using std::string;

//using namespace std;

int writeLog(string what, string msg);
void funz_clear();
string setNameScriptDyn(int con_sim, int save_);
int scriptInternalDynamics(const double& Q_m, const double& Q_M,const string name_dynamic, double width, int save_, int cont_sim, string name);
void lunch_gnuplot(string name_file_gnu);

/**
 * Function to plot the internal dynamic histogram: it in never actually used, its use it's commented.
 * It was useful to set the max and min of the memory parameter Q in the statistical analysis
 */


void Histogram_Dynamic(std::string name, std::string name_dynamic, int cont_sim)
{
    
    //    int tipo_molecular=1; //if tipo molecular == 0, ho molecular file
    
    
    std::ofstream file_dyn_plot;    
    std::ifstream file_info;
    
    std::string str_Molecular ("-4-");
    
    // different member versions of find in the same order as above:
    std::size_t found = name_dynamic.find(str_Molecular);
    if (found!=std::string::npos){
//        tipo_molecular=0;
        std::cout << "Molecular Simulation: no histogram for internal dynamic available ...\n";
    }else {
        
        cout << "plot of the histogram for internal dynamic available:\n";

        std::ifstream file_dynamics;
        file_dynamics.open(name_dynamic.c_str());
        std::string command;
        
        double t=0;
        double Q=0;
        double Q_M=-10000.0;
        double Q_m=10000.0;
        int n_dati=0;
        double width=0;
        while (!file_dynamics.eof()) {
            file_dynamics >> t >> t >> t >> Q;
            Q_M = fmax(Q,Q_M);
            Q_m = fmin(Q,Q_m);
            n_dati++;
        }
        
        Q_M = fmin(10.0,Q_M);
        Q_m = fmax(-10.0, Q_m);
        
        width = (Q_M-Q_m)/sqrt(n_dati);
        
        if (width<0.00001) {
            width=0.01;
        }
        if (width>1.0) {
            width=0.1;
        }
        
        file_dynamics.close();
        
        
        //***************************************
        //SCRIPTS ...
        

        scriptInternalDynamics(Q_m,Q_M,name_dynamic,width,sizeTitle::NO_SAVE,cont_sim,name);
        scriptInternalDynamics(Q_m,Q_M,name_dynamic,width,sizeTitle::SAVE,cont_sim,name);
        
        
        if (automatic_==0) {
            
/*
//            file_dyn_plot.open("dynamic.gnu");
//            
//            if (!file_dyn_plot.is_open()){
//                std::cout << "Error opening file";
//                
//            
//            
//            file_dyn_plot << gnuplotSetTerminalPlot << endl;
//            file_dyn_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
//            file_dyn_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
//                          << "set title 'Distribution of the memory term Q'"<< setSizesTitles(sizeTitle::HUGE_, sizeTitle::NO_SAVE) << endl;
//            file_dyn_plot << "set xrange ["<<Q_m<<":"<<Q_M<<"]" << endl;
//            file_dyn_plot << "stats \""<< name_dynamic  <<"\" u 4 name 'Dynamics'"<<endl;
//            file_dyn_plot <<  "Min = "<< Q_m << endl
//            << "Max = " << Q_M << endl
//            << "set xlabel 'run(sec)' "<< endl        
//            << "set ylabel 'freq' "<< endl
//            << "width = "<< width << endl
//            << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl                            
//            << "plot \""<< name_dynamic  <<"\" using (bin($4)):(1.0) smooth freq with boxes lc rgb \"blue\" notitle" << endl
//            << "pause mouse any" << endl
//            << "quit" <<endl;
            
//            file_dyn_plot.close();
            
            funz_clear();
            
//                command = gnuplotOpen + "dynamic.gnu";
//            
//                cout << "\nPLOT GNUPOLT" << endl;
//            
//                system(command.c_str());
*/
            //***************************************
            // VISUALIZZO
            //***************************************
            
            lunch_gnuplot(setNameScriptDyn(cont_sim,sizeTitle::NO_SAVE));
            
        }
        
        //***************************************
        // Salvo
        //***************************************
        
        lunch_gnuplot(setNameScriptDyn(cont_sim,sizeTitle::SAVE));
        
    }
   

/*
//        file_dyn_plot.open("dynamic.gnu");
//        
//        if (!file_dyn_plot.is_open()){
//            std::cout << "Error opening file";
//            return;
//        }
//            
//        std::string buffer = name;
//        buffer.erase(buffer.end()-4, buffer.end());
//        file_dyn_plot << gnuplotSetTerminalSave_eps << endl;
//        file_dyn_plot << "set output \""<< buffer <<"dyn.eps\""<<endl
//                      << "set title 'Distribution of the memory term Q'"<< setSizesTitles(sizeTitle::HUGE_, sizeTitle::SAVE) << endl;
//        file_dyn_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
//        file_dyn_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
//        file_dyn_plot << "set xrange ["<<Q_m<<":"<<Q_M<<"]" << endl;
////        file_dyn_plot << "stats \""<< name_dynamic  <<"\" u 4 name 'Dynamics'"<<endl;
//        file_dyn_plot <<  "Min = "<< Q_m << endl
//        << "Max = " << Q_M << endl
//        << "set xlabel 'Q' "<< setSizesTitles(sizeTitle::MEDIUM, sizeTitle::SAVE)<< endl
//        << "set ylabel 'freq' "<< setSizesTitles(sizeTitle::MEDIUM, sizeTitle::SAVE)<< endl
//        << "width = "<< (Q_M-Q_m)/sqrt(n_dati) << endl
//        << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl                            
//        << "plot \""<< name_dynamic  <<"\" using (bin($4)):(1.0) smooth freq with boxes lc rgb \"blue\" notitle" << endl
//        << "quit" <<endl;
//        
//        file_dyn_plot.close();
//        
//        funz_clear();
//        
//        command = gnuplotOpen + "dynamic.gnu";
//        
//        cout << "PLOT GNUPOLT" << endl;
//        cout << "name_dynamic: " << name_dynamic << endl;
//        cout << command << endl;
//        system(command.c_str());
*/

    
}


/*! \brief write script for the internal Dynamic histogram
 */

int scriptInternalDynamics(const double& Q_m, const double& Q_M,const string name_dynamic, double width, int save_, int cont_sim, string name){
    
    std::ofstream file_dyn_plot;
    
    file_dyn_plot.open(setNameScriptDyn(cont_sim,save_));
    
    if (!file_dyn_plot.is_open()){
        std::cout << "Error opening file";
        string msg("Error in the simulation.");
        msg+=setNameScriptDyn(cont_sim,save_);
        writeLog("ERROR",msg);
        return ERROR_OPENING_FILE;
    }
    
    if (save_==sizeTitle::SAVE) {
        std::string buffer = name;
        buffer.erase(buffer.end()-4, buffer.end());
        file_dyn_plot << gnuplotSetTerminalSave_eps << endl;
        file_dyn_plot << "set output \""<< buffer <<"dyn.eps\""<<endl;

    }else{
        std::string buffer = name;
        buffer.erase(buffer.end()-4, buffer.end());
        file_dyn_plot <<"#" << gnuplotSetTerminalSave_eps << endl;
        file_dyn_plot << "#set output \""<< buffer <<"dyn.eps\""<<endl;

        file_dyn_plot << gnuplotSetTerminalPlot << endl;
    }

    
    file_dyn_plot << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl;
    file_dyn_plot << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
    << "set title 'Distribution of the memory term Q'"<< setSizesTitles(sizeTitle::HUGE_, save_) << endl;
    file_dyn_plot << "set xrange ["<<Q_m<<":"<<Q_M<<"]" << endl;
    file_dyn_plot << "stats \""<< name_dynamic  <<"\" u 4 name 'Dynamics'"<<endl;
    file_dyn_plot <<  "Min = "<< Q_m << endl
                << "Max = " << Q_M << endl
                << "set xlabel 'run(sec)' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "set ylabel 'freq' "<< setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "#set size number axis" << endl
                << "set xtics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "set ytics " << setSizesTitles(sizeTitle::MEDIUM, save_)<< endl
                << "width = "<< width << endl
                << "bin(x) = width*(floor((x-Min)/width)+0.5) + Min" << endl
                << "plot \""<< name_dynamic  <<"\" using (bin($4)):(1.0) smooth freq with boxes lc rgb \"blue\" notitle" << endl;
    
    if (save_!=sizeTitle::SAVE) {
        file_dyn_plot << "pause mouse any" << endl;
    }

    file_dyn_plot << "quit" <<endl;
    
    file_dyn_plot.close();
    
    
    return 0;
}


/*! \brief set name of the file of the script for the internal dynamic.
 */

string setNameScriptDyn(int con_sim, int save_){
    
    string name("SCRIPT-GNUPLOT");
    char buffer[8];
    
    snprintf(buffer, sizeof(char)*8, "sim%03d",con_sim);
    name+=buffer;
    
    name+=(save_==sizeTitle::SAVE)?"save-dynamic.gnu":"visual-dynamic.gnu";
    
    return name;
}

