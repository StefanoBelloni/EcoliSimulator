//****************************************************************************
//
//  main.cpp
//  Ecoli_4.1.5
//  Versione 4.1.5
//
//  Created by Stefano Belloni on 24/10/15.

/* This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA
02110-1301, USA. */
//
//  sudo port install gnuplot
//
//
//****************************************************************************


// contare linee progetto:
// find . "(" -name "*.m" -or -name "*.mm" -or -name "*.cpp" -or -name "*.swift" ")" -print0 | xargs -0 wc -l

// NOTE: to have equal axis one has to pass to gnuplot:
// set size ratio -1
//  ------------------------------------------------------
// |    to activate it in the film decomment              |
// |          filmato_3D_gnuplot.cpp: linie 286 and 436   |
//  ------------------------------------------------------

#include <iostream>
#include <vector>
#include <fstream>
#include <string.h>
#include <limits>
#include <ctime>
#include <cstdlib>
#include <cstring>

#include <thread>

#include "FunzRand.h"
#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "MATLAB_Global.h"
#include "apngasm_Global.h"
#include "Q_tau_stat.h"
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "Funz_C.h"
#include "Funz_C_Par.h"
#include "CV_rIG_tExp.h"
#include "CV_rExpIG_tExp.h"
#include "Molecular_rExp_tExp.h"
#include "Colori.h"
#include "Declar_funz.h"
#include "Funz_C_Inter.h"
#include "LoadBar.hpp"
#include "GlobalRandomVariables.h"
#include "ErrorsDefinition.h"
#include <sstream>
#include "mainFunctions.h"
#include <unistd.h>
using namespace std;

int Funz_C::num_funz = 9;

//********************************************************************************************************************
// GLOBAL VARIABLES ...
//********************************************************************************************************************

std::mutex my_mutex;
bool save_data;
vector<long double> vettore_risposte;
vector<std::string> vettore_text;
int contatore_risposte = -1;
int automatic_ = 100;
long double epsilon = 1.0;
bool multithread = false;
bool colors = true;
bool show_bars = true;
unsigned int n_thread_available = 1;

//string fileEcoliRisp = "EcoliTest.Ecoli";
string fileEcoliRisp = "EcoliRisposte.Ecoli";
const string nameLog = "LogEcoli.LogEcoli";
const string EcoliPath = "EcoliPath.Ecoli";
unsigned int seed_ ;
unsigned int seed_r;
bool same_seed = false;
// automatic: 0 -> step by step version
//            1 -> setting parameters
//            2 -> running simulation 

randomObj rnd_ecoli;

//unsigned long int cont_rand = 0;

//  GLOBAL GNUPLOT
string gnuplotOpen;
string gnuplotSetTerminalPlot;
string gnuplotSetTerminalSave_eps;
string gnuplotSetTerminalSave_png;
std::string firefox_path;
std::string gnuplotSetTerminalSave_gif;

//  MATLAB GLOBAL
string MATLAB_loc;
string MATLAB_call;

//  APNGAS GLOBAL
string apngas_lunch;
string apngas_opt;
bool no_apngams;

//lunch+name_out+name_frame+opt;   WIN
//lunch + name_frame " -o "+ name_out + opt.  MAC/LINUX(?)

//   GLOBAL DIRECTORY

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
const char* homeDir = getenv ("HOMEPATH");
#elif __CYGWIN__
const char* homeDir = getenv ("HOMEPATH");
#else
const char* homeDir = getenv ("HOME");
#endif

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
string MainFolder;
#elif __CYGWIN__
string MainFolder;
#else
string MainFolder;
#endif

string Location = homeDir;


//********************************************************************************************************************
//                      MAIN FUNCTION (RIPULITA in Versione 0.0.1a)
//********************************************************************************************************************
int createMakeFile();
void setDefoultGlobalVar();
/**
 * Main version 4.1.5. <- when change version and the file is no more compatible, change in function 
 * read_file_par() and save_risposte().
 */
int main(int argc, const char * argv[])
{
    //createMakeFile();
    setDefoultGlobalVar();
    
    seed_ = (unsigned int) time(NULL);
    seed_r = seed_;
    n_thread_available = fmax(1,std::thread::hardware_concurrency()/2);
    if (n_thread_available>1) {
        multithread = true;
    }
    seed();
    if (argc>1 && strcmp(argv[1],"--help")==0) {
        helpMenu();
        return 0;
    }
    
    //****************************************************************************
    //                           VARIABILI VARIE
    //****************************************************************************
    string versione_Matlab="n";      // Versione Matlab
    vector<string> name_file_satistics;
    vector<string> name_info_satistics;
    vector<string> *pt_name_file_satistics=&name_file_satistics;  // pointer to names and info stat, so that we can pass default argument = 0(= null)
    vector<string> *pt_name_info_satistics=&name_info_satistics;
    
    // general counter for the simulation: it is used to set the name univocally of the files
    int cont_gen_sim=0;
    int stat_sim=-1;    // save which kind of simulation: simulation, statistic analy. or both
    int demo_mode=1;    // if demo_mode == 1  demo_mode
    int BiginEnd=0;     // variable to check if exit from BeginEnd loop, set in ConditionEnd, if ==1 repeat
    int read_from_file = -1; // if I want just to read from file ...
    int error_imporing_file = import_path(versione_Matlab)+GestioneArgvV2(argc,argv,versione_Matlab,read_from_file);
//    ;
    // set the color to defount
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    system("COLOR 0F");
    cout << RESET;
#else
//    printf("\e[97m\e[40m");//"\e[37m\e[41m" blue and red
//    system("COLOR 0F");
//    printf("\033[45;37mGrey on purple.\033[0m");
    cout << RESET;
#endif

    if (error_imporing_file!=0)
        ErrorImportPath(versione_Matlab);
    
    int number_routine;
    auto start = chrono::steady_clock::now();
    
    // initialize max engine to be used ...
    for (unsigned int i=0; i< n_thread_available; i++) {
        rnd_ecoli.random_engines.push_back(*new std::mt19937_64(clock()));
        rnd_ecoli.random_engine_saved.push_back(rnd_ecoli.random_engines[i]);
        rnd_ecoli.random_engines_barrier.push_back(*new std::mt19937_64(clock())); // da migliorare ...
        rnd_ecoli.random_engines_barrier_saved.push_back(rnd_ecoli.random_engines_barrier[i]); // da migliorare ...
        rnd_ecoli.random_engines_theta.push_back(*new std::mt19937_64(clock()));   //
        rnd_ecoli.random_engines_theta_saved.push_back(rnd_ecoli.random_engines_theta[i]);   //
        rnd_ecoli.random_engines_seeded.push_back(false);
    }
    seedRandomObj(0,this_thread::get_id());
    
    int read_par_file = set_MODE_Program(versione_Matlab, demo_mode,read_from_file);
    
//    if (read_par_file!=121) {
        if(SetMainFolder(demo_mode)!=0) {
            timestamp();
            cout << BOLDRED<< "FATAL ERROR CREATING FOLDER ON THE DESKTOP\n" << RESET;
            writeLog("ERROR", "fatal error creating main folder");            
            return ERROR_CREATING_MAIN_FOLDER;
        }
//    }

    contatore_risposte=0;
    
    if (read_par_file==0){
        ReadableFileRisp(stat_sim, demo_mode);
    }

    if (save_path(versione_Matlab)!=0) {
        return ERROR_SAVING_PATH_TO_FILE;
    }
    // main loop of the program.
    do{
        BiginEnd=0;
        FunzBiginEnd(number_routine,cont_gen_sim,read_par_file,versione_Matlab,pt_name_file_satistics,pt_name_info_satistics,demo_mode,stat_sim);
        ConditionEnd(read_par_file,stat_sim,BiginEnd);
    }while (BiginEnd==1);
    
    last_deleting();
    funz_clear();
    timestamp();
    
    // Salvo global Variables in un file, da poter usare in futuro ...
    if (save_path(versione_Matlab)!=0) {        
        return ERROR_SAVING_PATH_TO_FILE;
    }else{
        CopyEcoliFiles();
    }
    
    // LOG FILE
    stringstream msg;
    auto end = chrono::steady_clock::now();
    auto diff = end - start;
    msg << chrono::duration <long double, milli> (diff).count()/1000 << " seconds" << endl;
    msg << "::::::::::::::::::::::::::::::::::::::::::::::::::::::::::" << endl;
    string topic("Time to complete the program: ");
    writeLog(topic, msg.str());
    
    return Congedo(number_routine);
}

//TODO:
/*
 * [...] - controllare salvataggio/solo visualizzazione film.
 * [x] - aggiungere nella documentazione oppure final reoprt the methods.
 * [x] - check DEMO with the new changes.
 * [x] - allow agnpasm as optional, in this case do not delete the files *.png ...
 * [no] - if I therad gnuplot_film didn't work return a parameter ...
 * [...] - save figure from matlab.
 * [x] - sistemare il video di theta ... --> "::1::b" b non è sincronizzato ...
 * move the files to tmpEcoli ... create also the directory ./tmpEcoli
 */
