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


void str_row_table(std::ofstream& file, int tipo, int n_records, long double mean, long double var, long double std_);

enum{tip_all = 0,tip_up,tip_down,tip_mix,tip_c,tip_tumble};

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
    
    name.erase(name.end()-4, name.end());
    string buffer = "_info.txt";
    string titolo=name+buffer;
    ofstream file_info;
    file_info.open (titolo.c_str(), std::ofstream::out | std::ofstream::app);
    
    ifstream file_lettura;
	string temp;
    int n_salti;
	long double mean,var,std_;

//enum{tip_all = 0,tip_up,tip_down,tip_mix, tip_c,tip_tumble};
	const char* file_names[] = {"r_a.txt","r_u.txt","r_d.txt","r_m.txt","r_c.txt","t_a.txt"};


	file_info << "\\begin{verbatim}" << endl;
    file_info << "********************************************" << endl;
    file_info << "**       ANALYSIS RUNS AND TUMBLES        **" << endl;
    file_info << "********************************************" << endl;
    file_info << "\\end{verbatim}" << endl;

    file_info << "\\begin{center}" << endl
    		  << "\\begin{tabular}{| l || c | c | c | r |}" << endl
    		  << "\\hline" << endl
    		  << "run/tumble & number data & $\\mathbf{E}[\\tau_{i}] $& $\\textrm{var}[\\tau_{i}]$ & $\\sqrt{\\textrm{var}[\\tau_{i}]}$\\\\ \\hline \\hline" << endl;
	
    for(int i = 0; i<6; i++){
		file_lettura.open(file_names[i]);
		if(file_lettura.is_open()){
			file_lettura >> temp;
			file_lettura >> n_salti;
			std::cout << "n_salti n. " << i << ": " << n_salti << endl;
			if (n_salti>0){
				file_lettura >> mean;
				file_lettura >> var;
				file_lettura >> std_;
				str_row_table(file_info,i,n_salti, mean, var,std_);
			}
			file_lettura.close();
		}else{
			cout << "Error opening file: " << file_names[i] << endl;
		}

	}

	file_info << "\\hline" << endl
			  << "\\end{tabular}" << endl
			  << "\\end{center}" << endl;
	file_info.close();
}


/** this function returns the string of the line of the table of the runs/tumble */
void str_row_table(ofstream& file, int tipo, int n_records, long double mean, long double var, long double std_){
	string kind;

	switch(tipo){
		case tip_all:
			kind = string("all $\\tau_{r}$");
			break;
		case tip_up: 
			kind = string("$\\tau_{r}$: $\\langle\\theta,\\nabla c\\rangle>0$");
			break;
		case tip_down:
			kind = string("$\\tau_{r}$: $\\langle\\theta,\\nabla c\\rangle<0$");
			break;
		case tip_mix:
			kind = string("$\\tau_{r}$: $\\langle\\theta,\\nabla c\\rangle$ mix");
			break;
		case tip_c:
			kind = string("$\\tau_{r}$: $\\langle\\theta,\\nabla c\\rangle$ = 0");
			break;
		case tip_tumble:
			kind = string("$\\tau_{t}$");
			break;
		default:
			kind = string("$\\tau$");
			break;
	}

	file << kind << " & "
		 << n_records << " & " 
		 << mean << " & "
		 << var << " & "
		 << std_ << "\\\\ \\hline" << endl;

}
