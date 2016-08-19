//
//  Analysis_run.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 29/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include "LoadBar.hpp"

#include "GlobalVariables.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif


using namespace std;

//void loadbar(unsigned int x, unsigned int n, unsigned int w);
void fraction_run_file(string file_write, int cont_salti, vector<int> tau_vector, int n_tau_x, double dx, double tau_max, double somma_tau);

void funz_clear();
int writeLog(string topic, string msg);
void RunUpDownDivision(vector<int> &tau_vector, int &somma_tau, int n_tau_x ,int &n_salto, double tau, double &tau_mean, double &tau_var,double dx);

/**
 * This function analysis the runs and tumbles:
 * the function save temporaly the data in file r_u.txt etc. (see line 73)
 * divide up/down gradient and prepare lateX file for analysis run/tumble
 * @param run==1 run, else analysis tumbles
 * @param name_file_read name where run/tumble are saved.
 *
 ************************/

double Analysis_run(string name_file_read, string names[], int run){
    
    if (run==1) {
        cout <<"Analysis runs ... \n";
    }else {
        cout <<"Analysis tumbles ... \n";
    }

    
    // run ==1 -> file run, run == 0 -> file tumble. 
    // gli indici seguono ->  [0, 1, 2, 3, 4] --> (1 up), (-1 down), (0 const), (2 mix), all
    ifstream file_salti;    
    
    vector<int> n_salto(5,0); // [0, 1, 2, 3, 4] 
    stringstream sstm;       
    string temp_string;
    
//    vector<double> tau_all;
    
    vector<double> tau_mean(5,0);
    vector<double> tau_var(5,0);
    vector<int> somma_tau(5,0);
    
    vector<vector<int> > tau_vector;
    
    // FILE PER SALVARE DATI SUI SALTI ...
    ofstream file_dati[5];
    
    if (run==1) {
        file_dati[0].open("r_u.txt");
        file_dati[1].open("r_d.txt");
        file_dati[2].open("r_c.txt");
        file_dati[3].open("r_m.txt");
        file_dati[4].open("r_a.txt");            
    }else{
        file_dati[4].open("t_a.txt");        
    }
    
    
    const char * read = name_file_read.c_str();
    
    file_salti.open(read);
    
    if (!file_salti.is_open()) {
        cout << "Error reading file: " << read << endl;
        string msg("Error reading file:");
        msg+=read;
        writeLog("ERROR",msg);
        funz_clear();
        return -1.0;
    }
    
    cout << "Nome file da leggere: " << read << endl;
    
    double dx=0.01;
    double tau_x=0.0;
    double tau_max=7.0;
    
    int n_salti_max=0;
    int n_linea=0;
    
    int n_tau_x=0;    

    while (getline(file_salti,temp_string)) {
        n_salto[4]++;   
    }
    
    n_salti_max=n_salto[4];
    
    file_salti.close();
    
    if (run!=1) {
        tau_max=2;
        dx=max(.005,min(0.05,tau_max/sqrt(n_salto[4])));        
    }else {
        dx=max(.005,min(0.1,tau_max/sqrt(n_salto[4])));
    }
    
    while (tau_x<=tau_max) {
        tau_x=tau_x+dx;
        n_tau_x++;
    }
	
    //*******************************
    
    if (automatic_!=1) {        

        n_salto[4]=0;
        tau_vector.resize( 5 , vector<int>( n_tau_x , 0 ) );
        file_salti.open(read);
        double tau=0.0;
        double c=0.0;
        int up_down=2;
        int tipo_tau;
        int n_batterio = 0;
        double t__=0;
        double t__p=0;
        
        cout << "There are " << n_salti_max << " data recorded\nTill now analyzed\n";
        
        while (!file_salti.eof()) {
            // read run/tumble
            loadbar(n_linea,n_salti_max);
            n_linea++;

            if (run==1) {
                file_salti >> t__ >> tau >> up_down;
                //cout << "tau = " << tau << endl;
//                file_salti >> tau >> tau >> up_down;
                if (t__ <= t__p){
                    n_batterio++;
                }
//                if (tau>8) {
//                    cout << "n. " << n_batterio << ": t = " << t__ <<", tau = " << tau << ", up_down = " << up_down << " **************************" << endl;
//                }
//                else{
//                    cout << "t = " << t__ <<", tau = " << tau << ", up_down = " << up_down << endl;
//                }
                t__p=t__;
                
            } else {
                file_salti >> tau >> tau >> c;
            }
// divide which "gradient-case", I'm in up/down etc.
            tipo_tau=4; // all ...
            RunUpDownDivision(tau_vector[tipo_tau], somma_tau[tipo_tau], n_tau_x, n_salto[tipo_tau], tau, tau_mean[tipo_tau], tau_var[tipo_tau], dx);
            
            if (run==1) // Se ho up/down etc ...
            {
                // up_down is the same number as the associated index in the arrays tau_vector, somma_tau etc.
                switch (up_down) {
                    case 1:
                        tipo_tau=0;
                        break;
                    case -1:
                        tipo_tau=1;
                        break;
                    case 0:
                        tipo_tau=2;
                        break;
                    default:
                        tipo_tau=3;    
                        break;
                }
                RunUpDownDivision(tau_vector[tipo_tau], somma_tau[tipo_tau], n_tau_x, n_salto[tipo_tau], tau, tau_mean[tipo_tau], tau_var[tipo_tau], dx);        
            }
    
    }
    
    //  ALL RUNS
    
        cout << "\ncreazione files" << endl;
        
        if (run==1) {
            
            // fraction_run_file: salvo nel file name[0] tau tau_frac tau_hist ...

            for (int i=0; i<=3; i++) {
                
                if(n_salto[i]>=10) 
                {
                    fraction_run_file(names[i],n_salto[i],tau_vector[i],n_tau_x,dx,tau_max, somma_tau[i]);    
                    file_dati[i] << "% " << n_salto[i] << " "
								 		 << tau_mean[i]/n_salto[i] << " "
										 << tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2) << " "
										 << sqrt(tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2)) << endl;
					file_dati[i] << "There are $" << n_salto[i] << "$ records\n\n" << endl
                                << "mean: $$\\mathbf{E}[\\tau]= " << tau_mean[i]/n_salto[i] <<"$$\n" <<endl
                                << "variance $$\\mathbf{Var}[\\tau] = " << tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2) << "$$\n" << endl
                                << "standard deviation $$\\mathbf{std}[\\tau] = " << sqrt(tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2)) << "$$\n" << endl;       

                    file_dati[i].close();
                }
            }
            
        }
            
        if(n_salto[4]>=10) {
            
            int i=4;
            fraction_run_file(names[i],n_salto[i],tau_vector[i],n_tau_x,dx,tau_max, somma_tau[i]);    
                    file_dati[i] << "% " << n_salto[i] << " "
								 		 << tau_mean[i]/n_salto[i] << " "
										 << tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2) << " "
										 << sqrt(tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2)) << endl;            
					file_dati[i] << "\nThere are $" << n_salto[i] << "$ records\n\n" << endl
                         << "mean: $$\\mathbf{E}[\\tau]= " << tau_mean[i]/n_salto[i] <<"$$\n" <<endl
                         << "variance $$\\mathbf{Var}[\\tau] = " << tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2) << "$$\n" << endl
                         << "standard deviation $$\\mathbf{std}[\\tau] = " << sqrt(tau_var[i]/n_salto[i]-pow(tau_mean[i]/n_salto[i],2)) << "$$\n" << endl;
            file_dati[i].close();
        }
    }
    return tau_mean[4]/max(n_salto[4],1);
    
}


void writeLineTable(){
    
    
    
    
    
}

