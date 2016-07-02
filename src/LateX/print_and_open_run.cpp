//
//  print_and_open_run.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 07/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <iomanip>

#include "FunzRunUndTumble.h"

using namespace std;

/**
 * This function produce a general summary for the LateX file of the analysis of RUN and Tumbles.
 */

void print_and_open_run(std::string name, int cont_gen_sim){
    
    
    name.erase(name.end()-4, name.end());    
    string buffer = "_info.txt";    
    string titolo=name+buffer;
    ofstream file_info;
    file_info.open (titolo.c_str(), std::ofstream::out | std::ofstream::app);
    
    ifstream file_lettura;
    
    file_info << "\\begin{verbatim}" << endl;
    file_info << "********************************************" << endl;
    file_info << "**            ANALYSIS RUNS            **" << endl;
    file_info << "********************************************" << endl;
    file_info << "\\end{verbatim}" << endl;


    file_lettura.open("r_a.txt");
    file_info << "\\textbf{Analysis of all runs}" << endl;
    while (getline(file_lettura,buffer)) {
        
        file_info << buffer << endl;
    }
    file_lettura.close();
    
    file_lettura.open("r_u.txt");
    file_info << "\n\\textbf{Runs up the gradients:}\n " << endl;
    while (getline(file_lettura,buffer)) {
        
        file_info << buffer << endl;
    }
    
    file_lettura.close();
    
    file_lettura.open("r_d.txt");
    file_info << "\n\\textbf{Runs down the gradients:}\n " << endl;
    while (getline(file_lettura,buffer)) {
        
        file_info << buffer << endl;
    }
    file_lettura.close();
    
    file_lettura.open("r_c.txt");
    file_info << "\n\\textbf{Runs along constant the gradients:}\n " << endl;
    while (getline(file_lettura,buffer)) {
        
        file_info << buffer << endl;
    }
    file_lettura.close();
    
    file_lettura.open("r_m.txt");
    file_info << "\n\\textbf{Runs through differents signs of the gradients:}\n " << endl;
    while (getline(file_lettura,buffer)) {
        
        file_info << buffer << endl;
    }
    file_lettura.close();
    

    file_info << "\\begin{verbatim}" << endl;
    file_info << "********************************************" << endl;
    file_info << "**            ANALYSIS TUMBLES            **" << endl;
    file_info << "********************************************" << endl;
    file_info << "\\end{verbatim}" << endl;
    
    file_lettura.open("t_a.txt");
    file_info << "\\textbf{Analysis of all tumbles:}\n" << endl;
    while (getline(file_lettura,buffer)) {        
        file_info << buffer << endl;
    }
    file_lettura.close();
    
}



void print_and_open_run2V(std::string name, int cont_gen_sim){
    
//    name.erase(name.end()-4, name.end());
//    string buffer = "_info.txt";
//    string titolo=name+buffer;
//    ofstream file_info;
//    file_info.open (titolo.c_str(), std::ofstream::out | std::ofstream::app);
//    
//    ifstream file_lettura;
//    
//    file_info << "\\begin{center}"<<endl;
//    \begin{tabular}{| l || c | c | r |}
//    \hline
//    run/tumble & $\MExp[\tau_{i}] $& $\textrm{var}[\tau_{i}]$ & $\sqrt{\textrm{var}[\tau_{i}]}$\\ \hline \hline
//    $\tau_{r}$: $\langle\theta,\nabla c\rangle=0$ & 0.809631 & 0.639319 &0.799574\\ \hline \hline
//    $\tau_{t}$ & 0.107593 & 0.00999627 & 0.0999814\\
//    \hline
//    \end{tabular}
//    \captionof{table}{{\bf CV-rExp-tExp} constant environment: there are $13\,183\,128$ runs and $13\,181\,992$ tumbles: $\tau_{r}$ means duration of a \emph{run} and $\tau_{r}$ stands for the duration of a \emph{tumble}. We write $\langle\theta,\nabla c\rangle$ to indicate the sign of the measured gradient of $c(x,t)$ during a run.}
//    \label{Table6.1}
//    \end{center}
    
    
}