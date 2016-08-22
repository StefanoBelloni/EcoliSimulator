//
//  File_statistics.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 25/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>

#include "GlobalVariables.h"
#include "sssr.h"

#include "CV_rExp_tExp.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rIG_tExp.h"
#include "Funz_C.h"
#include <vector>
#include <fstream>
#include "Colori.h"

#include <iomanip>



// In questa versione parto dai dati .dat e creo statistical data .dat ...

int set_statistical_types(vector<int> &tipo_statistical_file);
void set_statistical_names(string names_info_mod, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics, int tipo_statistical_file, int j);
int set_statistical_file(string name_file_satistics, int tipo_statistical_file,
                         string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod);
void funz_clear();

void set_statistical_file_info(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string name_info_satistics);

int writeLog(string what, string msg);

//**********************************************************************
//       File_statistics
//**********************************************************************

/**
 * this function set the names of the statistics via the function set_statistical_names, the info to process the data, and prepare the statistical data after a simulation
 */

void File_statistics(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv,string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod, string *names_info_mod, int i, int &cont_gen_sim, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics){
    
    vector<int> tipo_statistical_file;

    int n_stat_file = set_statistical_types(tipo_statistical_file);

    
    // Se sono nella fase esecutiva, faccio effettivaemnte qualche cosa ... 
    if (automatic_!=1) {
        
        for (int j=0; j<n_stat_file; j++) {
            
            // CREO I NOMI
            set_statistical_names(names_info_mod[0], pt_name_file_satistics, pt_name_info_satistics, tipo_statistical_file[j],j);
            
            // CREO I FILES
            set_statistical_file_info(batterio,T_f,f,x0,dt,n_c,Raggio,delta_dist,num_dist,const_salv, (*pt_name_info_satistics)[j]);
//            cout << "STATISTICAL INFO FILE\nPress Invio\n";
//            cin.ignore();
//            cin.ignore();            
            set_statistical_file((*pt_name_file_satistics)[j], tipo_statistical_file[j], names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod);
            
            
        }
        
    
    }
    
}


//**********************************************************************
//      set_statistical_types
//**********************************************************************

/**
 * This function should allow to decide which kind of statisical data produce. Now only the first is implemented
 */

int set_statistical_types(vector<int> &tipo_statistical_file){
    
    funz_clear();
    
    int risp=0;
    int stat_=0;
    int n_stat_files=0;
    
    cout << "Select now which kind of statistical file du you wnat to create.\n";
    cout <<"From the present dataset it is possible to create more different statistical files ...\n\n";
    
    while (risp==0) {
        cout << BOLDRED<< "Which kind of statistical file du you want to create? Press \n";
        cout << BOLDBLUE << "1 - data at the tumble:\n";
        cout              << "________________________________________________________________\n"; 
        cout << BOLDBLACK << "|  t    |  c(start run) | c(start tumble) |  t_run  | t_tumble |\n";
        cout              << "________________________________________________________________\n"; 
        cout     << RESET << "|  t_1  |     c_1_r     |    c_1_t        |  t_1_r  |  t_1_t     |\n";        
        cout              << "|  ...  |      ...      |     ...         |  ...    |  ...       |\n";        
        cout              << "|  t_i  |     c_i_r     |    c_i_t        |  t_i_r  |  t_i_t     |\n\n";        
        cout << BOLDGREEN << "2 - runs up/down/const gradient :\n";       
        cout              << "________________________________________________________ \n"; 
        cout << BOLDBLACK << "|   t   | t_run     |    up/down/const/mix | t_tumble   |\n";
        cout              << "________________________________________________________\n";
        cout << RESET     << "|   t_1 |  t_1_r    |        index_t_r_1   |   t_t_1    |\n";   
        cout              << "|   ... |  ...      |        ...           |   ...      |\n";   
        cout              << "|   t_i |  t_r      |        index_t_r_i   |   t_t_i    |\n";   
        cout << BOLDMAGENTA << "...\n";        
        cout << RESET << "...\n";        
//        sssr(stat_);
        
        stat_=1;
        
        if (stat_<=0||stat_>1) {
            stat_=1;
        }
        
        tipo_statistical_file.push_back(stat_);
        
        cout << "Do you want to produce another type of statistical file? \npress 0 for yes, 1 for no ";
//        sssr(risp);
        risp =1; 
        n_stat_files++;
        
        funz_clear();
        
    }

    return n_stat_files;
    
}

//**********************************************************************
//      set_statistical_names
//**********************************************************************

/** Set the names of the statistical files: it takee the base name and modified to add -stat, type of statistic and number of simulation
 */

void set_statistical_names(string names_info_mod, vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics, int tipo_statistical_file, int j){
    
    string name_base=names_info_mod;
    string name_stat = ".dat";
    string name_opt = "-opt.dat";
    name_base.erase(name_base.end()-4, name_base.end());
    
    char buffer_sim[16];
    snprintf(buffer_sim, sizeof(char) * 16,"-stat%d-n%d",tipo_statistical_file,j);
    
    name_base+=buffer_sim;
    
    (*pt_name_file_satistics).push_back(name_base+name_stat);
    (*pt_name_info_satistics).push_back(name_base+name_opt);
    
}

//**********************************************************************
//      set_statistical_file
//**********************************************************************

/** This function write the file with the data to be analysed:
 * the first line has to be something like this: statistical_file << "t c delta_c tau tumble EOC";
 */

int set_statistical_file(string name_file_satistics, int tipo_statistical_file,
    string *names_Ecoli_mod, string names_indice_mod, string *names_tau_mod, string names_file_dyn_mod                     )
{
    
    cout << "\nPreparation Statistical File ... \n";
    
    ofstream statistical_file;

    ifstream data_sets[7];
    int cont_gen=0;
    // data_sets così strutturati: [0,1,2,3,4,5,6]=[X,theta,c,run,tumb,Q,indeX]
    
    //Apro i files    
    statistical_file.open(name_file_satistics.c_str());
    
    for (int i=0; i<3; i++) {
        data_sets[cont_gen].open(names_Ecoli_mod[i].c_str());
        cont_gen++;
    }
    for (int i=0; i<2; i++) {
        data_sets[cont_gen].open(names_tau_mod[i].c_str());
        cont_gen++;
    }
    
    data_sets[cont_gen].open(names_file_dyn_mod.c_str());
    cont_gen++;
    data_sets[cont_gen].open(names_indice_mod.c_str());
    
    
//    cout << "Press invio ";
//    cin.ignore();
//    cin.ignore();
    
    switch (tipo_statistical_file) {
        // case 1:
        {
        case 1:
            
            statistical_file << "t c delta_c tau tumble EOC";
//            cout << "t c delta_c tau tumble EOC" << endl;
            long double t_run=0.0L;
            long double t_tam=0.0L;
            long double last_t=0.0L;
            long double last_tau_r=0.0L;
            long double last_tau_t=0.0L;
            long double c_prec=1.0L;
            long double c_new=0.0L;
            long double last_t_run=1000000000000000.0L;
            int c;

//            cout << "*******************************************************************" << endl;
//            cout << "* Statistical file " << endl;
//            cout << "*******************************************************************" << endl << endl;
            while (data_sets[3] >> t_run >> last_tau_r >> c && data_sets[4] >> t_tam >> last_tau_t >> c_new) // I read the lines of the two files
            {
//                cout << "::::::::::: r: " << t_run << " "<< last_tau_r << " "<< c << endl;
//                cout << "::::::::::: t: "<< t_tam << " "<< last_tau_t << " "<< c_new << endl;
                if ( t_tam < last_t_run && t_run > last_t_run){ // if tumble new and run old, I ignore this last run ...
//                    cout << "???????????????????????????????????????????????????????????????" <<endl;
                    if (!(data_sets[3] >> t_run >> last_tau_r >> c)) {
                        break; // if I cannot read it I'm done
                    }
//                    cout << ".....................> r: " << t_run << " "<< last_tau_r << " "<< c << " <...................."<< endl;
                }
                if ( t_run < last_t_run /*||  // the run time
                        t_tam < last_t_run*/)    // or tumble time jumps in the past ... new bacterium.
                {
//                    cout << "#################################################################" << endl;
                    c_prec = c_new;
                    last_t=0.00L;
                    if (t_tam < t_run) { // if I strated with a tumble, I skip it
                        if (!(data_sets[4] >> t_tam >> last_tau_t >> c_new)) {
                            break; // if I cannot read it I'm done
                        }
//                        cout << "------------------> t: "<< t_tam << " "<< last_tau_t << " "<< c_new << " <------------------ "<< endl;
                    }
//                    else{
//                        cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@" << endl;
//                    }
                    // if I'm here I'm starting processing a new bacterium
                }
                statistical_file << endl << last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t;
//                cout << "--------------------------------------------------------------------> " <<  last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t << endl;
                c_prec=c_new;
                last_t=t_tam;
                last_t_run=t_run;
            }
//            cout << endl;
//            exit(1);
/*
            while (!data_sets[3].eof() && !data_sets[4].eof()) {    // till I didn't reach the end of the files ...
                data_sets[3] >> t_run >> last_tau_r >> c ;  // save data for the runs: time of run, duration run, up/down
                if (t_run<last_t_run) {                     // if the time of eun is smaller the the last one, I have a new bacterium
                    last_t=0.0;
                    c_prec=1;
                }else {
                    data_sets[4] >> t_tam >> last_tau_t >> c_new;
                }

                statistical_file << endl << last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t;
                
                c_prec=c_new;
                last_t=t_tam;
                last_t_run=t_run;
            }
 */
            
            break;
        }
        // case 2:
        { 
            case 2:
            
            
            statistical_file << "t tau kind tumble EOC";
            
            long double t_run=0.0L;
            long double last_t=0.0L;
            long double last_tau_r=0.0L;
            long double last_tau_t=0.0L;
            long double c_prec=1.0L;
            long double c_new=0.0L;
            long double last_t_run=0.0L;
            int c;
            long double t=0.0L;
            
            while (!data_sets[3].eof() && !data_sets[4].eof()) {
                
                data_sets[3] >> t_run >> last_tau_r >> c ;
                
                if (t_run<last_t_run) {
                    last_t=0.0L;
                    c_prec=1;
                }else {
                    data_sets[4] >> t >> last_tau_t >> c_new;
                }
                
                statistical_file << endl << last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t;

                c_prec=c_new;
                last_t=t;
                last_t_run=t_run;
            }
            
            break;
        }  
        // default :    
        {
        default:
            
            cout << "Error producting statistical data\n";
            
            string msg("Error producting statistical data.");
            //                msg+=name_script_baricenter;
            writeLog("ERROR",msg);
            
            break;
        }
    }
    
    
    
    
    //Chiudo i files
    statistical_file.close();
    for (int i=0; i<=cont_gen; i++) {
        data_sets[i].close();
    }
    
    
    return 0;
}

//*********************************************************************************************
// IMPLEMENTAZIONE 1  tipo_statistical_file, case 1
/*
 // i=0;
 // i*=0;
 // j=0;
 // c_prec = 1; // per come è fatta la simulazione ...
 // leggo: file_run, riga i;
 // salvo file_run(2) = last_tau_r
 // salvo file_run(1) = last_t
 // i++;
 // leggo file_c riga i* fino a riga j*, fino a che file_c(1)<=file_run=0.
 // i*=j*;
 // salvo file_c(2) =  c_new;
 // leggo file_tumble fino a che file_tumble(1)<=last_tau_t
 // salvo last_tau_t
 
 // Quello che ho ora è last_t c_prec c_new last_tau_r last_tau_t 
 
 if c(t) è salvato meno frequentemente di tau, allora uso molto spesso lo stesso valore di c ...
 
 */
/*
 
 switch (tipo_statistical_file) {
 {
 case 1: 
 
statistical_file << "t c delta_c tau tumble EOC";
cout << "t c delta_c tau tumble EOC" << endl;



long double c_prec=1;
long double c_new=0;
long double last_tau_t=0;
long double last_tau_r=0;
long double last_t=0;
long double t_run=0;
long double t=0;
long double t_c=-1;

int found_c=0;
int found_t=0;

while (!data_sets[3].eof()) {
    
    data_sets[3] >> t_run >> last_tau_r >> t ;
    
    if (t_run<last_t) {
        last_t=0;
        c_prec=1;                    
    }
    
    if (t_c<t_run) {                    
        while (!data_sets[2].eof() && found_c==0) {
            data_sets[2] >> t_c >> c_new;
            if (t_c>=t_run) {                                            
                found_c=1;
            }
        }
    }
    
    
    // non è detto che sia partito con un run, però il file statistico parte sempre da un run ...
    
    while (!data_sets[4].eof() && found_t==0) {
        data_sets[4] >> t >> last_tau_t;
        if (t>=t_run) {                        
            found_t=1;
        }
    }
    
    found_t=0;                
    found_c=0;
    
    // devo fare << endl << per l;a nuova linea per non creare una linea extra nel file!! 
    
    statistical_file << endl << last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t;
    
    cout << last_t << " " << c_prec << " " << c_new << " " << last_tau_r << " " << last_tau_t << endl;
    
    c_prec=c_new;
    last_t=t;
    }
    */
//*********************************************************************************************

//#include <fstream>
//#include <cstring>

#include "Funz_C_Par.h"

using namespace std;

/**
 * save the info to be pass to the statistical section, such ligand concentration function, initial distribution etc ...
 * the parameters are selfunderstandable 
 */

void set_statistical_file_info(E_coli *batterio, long double T_f,Funz_C *f,long double *x0,long double dt,int n_c,long double Raggio,int delta_dist, int num_dist,int const_salv, string name_info_satistics){
    
    ofstream file_statistical_info;
    
    file_statistical_info.open(name_info_satistics.c_str());

    
    file_statistical_info << T_f << endl
                          << dt << endl
                          << x0[0] << endl
                          << x0[1]  << endl
                          << n_c << endl
                          << num_dist << endl
                          << Raggio  << endl
                          << delta_dist  << endl
                          << const_salv << endl
                          << batterio->F_tipo_response_c() << endl
                          << batterio->F_RC_0() << endl
                          << batterio->F_RC_1() << endl
                          << batterio->F_RC_q() << endl;
    
    // DEVO AGGIUNGERE LE INDICAZIONI PER Funz_c !!

    f->Funz_C::info_stat(file_statistical_info);
    
    file_statistical_info.close();
    
}
















