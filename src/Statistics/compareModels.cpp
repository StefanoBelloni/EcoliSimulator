//
//  compareModels.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 08/03/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include <stdio.h>
#include <vector>
#include <fstream>

#include "E_Coli.h"
#include "GnuplotGlobal.h"
#include "ErrorsDefinition.h"
#include "GlobalVariables.h"

#define SAVE 0

int writeScriptCompare(string namefile1, string namefile2, string nameFileScript);
string setBaricenterName(int cont_gen_sim);
void lunch_gnuplot(string name_file_gnu);

//! This function compares the different models which we simulate: basically it imitate the quantity in Samaey's Article
/*!
 *  This function calculates and displays \f$\epsilon_{i,j}(t):=\frac{1}{\epsilon}\|\mathbf{E}[X_j(t)] - \mathbf{E}[X_i(t)]\|$\f and \f$\epsilon_{i,j}(t):=\frac{1}{\epsilon^2}\|Var[X_j(t)] - Var[X_i(t)]\|^2$
 *  I cannot really calculate like in Samaey since I have different values for theta!!
 */

// TODO:
// save and not save: to implement the save part ...
int compareModels(std::vector<E_coli* > &batteri, std::vector<int> &which_compare, int cont_gen_sim, int save_)
{
    
    std::ofstream MainScriptCompare("SCRIPT-GNUPLOT-mainScriptCompare.gnu");

    // The way gnuplot_luch works, imposes us to write b=1. ??
    //    MainScriptCompare << "b=1;" << endl;
    
    // All the names of files we're going to use to plot
    std::vector<string> namefile;
    cont_gen_sim+=1;
    for (int i=0;i<(int)which_compare.size();i++){
        namefile.push_back(setBaricenterName(cont_gen_sim+i));
    }
    
    // I write the script for gnuplot
    // For every plot I compare only two models, i.e. (i,j) s.t. j>i.
    
    for (int i=0;i<(int)which_compare.size();i++){
        for (int j=i+1;j<(int)which_compare.size();j++){
            
            char buffer_sim[36];
            snprintf(buffer_sim, sizeof(char) * 36,"sim%03d-compareM%02d-%02d.dat",cont_gen_sim,i,j);
            
            writeScriptCompare(namefile[i], namefile[j], buffer_sim);
            
            if (save_==SAVE) {
                
                string buffer = buffer_sim;
                buffer.erase(buffer.end()-4, buffer.end());
                
                MainScriptCompare << gnuplotSetTerminalSave_eps << endl;
                MainScriptCompare << "set output \""<< buffer <<".eps\""<<endl;
                
            }else{
                string buffer = buffer_sim;
                buffer.erase(buffer.end()-4, buffer.end());
                MainScriptCompare << gnuplotSetTerminalPlot <<" " << i+j<< endl;
                MainScriptCompare << "#" << gnuplotSetTerminalSave_eps << endl;
                MainScriptCompare << "#set output \""<< buffer <<".eps\""<<endl;
            }
            
            MainScriptCompare << "set multiplot layout 2,1 title 'Comparison "
                              << batteri[which_compare[i]]->Tipo_batterio << " and "
                              << batteri[which_compare[j]]->Tipo_batterio << "'" << endl;
            MainScriptCompare << "load \""<< buffer_sim <<"\""  << endl;
            MainScriptCompare << "unset multiplot" << endl;
        }
    }
    
    // If I don't save, I weit for keys of mouse to be pressed ...
    if (save_!=SAVE) {
        MainScriptCompare << "pause mouse any" << endl
                          << "quit" <<endl;
    }
    
    MainScriptCompare.close();
    
    lunch_gnuplot("SCRIPT-GNUPLOT-mainScriptCompare.gnu");
    // TODO: I should eliminate the temporyt files I created ...

    return 0;
}

//! This function writes the script for the comparison of two models.

int writeScriptCompare(string namefile1, string namefile2, string nameFileScript)
{
    std::ofstream file_compare;
    file_compare.open(nameFileScript.c_str());
    
    char calculationMean[] = "sqrt(($5-$11)**2+($6-$12)**2)/";
    char calculationVar[] = "(($4-$10)**2)/";
    
    file_compare << "set grid ytics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                 << "set grid xtics lc rgb \"#bbbbbb\" lw 1 lt 0" << endl
                 << "set xlabel 't(sec)/eps^2' "<< endl
                 << "set ylabel 'E|X(t,i)-X(t,j)|' "<< endl
                 << "plot '< paste " << namefile1 << " " << namefile2
                 << "' u 1:( " << calculationMean << epsilon<<") w l title 'eps = "<< epsilon << "'"<< endl
                 << "set ylabel 'Var|X(t,i)-X(t,j)|' "<< endl
                 << "plot '< paste " << namefile1 << " " << namefile2
                 << "' u 1:("  << calculationVar  << epsilon*epsilon<<") w l title 'eps = "<< epsilon << "'" << endl;
//                 << "unset multiplot 2,1"<< endl;
    
    
    file_compare.close();
    
       return 0;
    
}