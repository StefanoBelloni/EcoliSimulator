//
//  GlobalVariables.h
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 25/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <vector>
#include <string>
#if NO_M_THREAD
#include "MyMutex.h"
#else
#include <mutex>
#endif

extern std::vector<long double> vettore_risposte;
extern std::vector<std::string> vettore_text;
extern int contatore_risposte;

extern bool multithread;
extern unsigned int n_thread_available;

extern std::string fileEcoliRisp;
extern const std::string EcoliPath;
extern std::string nameLog;
extern bool verbose;


extern bool colors;
extern bool show_bars;

/**
 * Variable to keep track of the MODE of simulation ... in otherwords, how to get the imput,
 * from keybord and run the imput (0)
 * from keybord and save the imput in std::vector<long double> vettore_risposte; contatore_risposte keep track of the answer we read from the std::vector of answers (1)
 * read from std::vector<long double> vettore_risposte (2)
 automatic: 0 -> step by step version
            1 -> setting parameters
            2 -> running simulation
 */
extern int automatic_;

/** variable used to study the Diffusive limit*/
extern long double epsilon;

/** Variable used to reseed the random generator to allow the possibility to use the same random numbers in one Routine */
extern unsigned int seed_;
extern unsigned int seed_r;
extern bool same_seed;
//extern unsigned long int cont_rand;


#ifndef NO_M_THREAD
  extern std::mutex my_mutex;
#else
  extern MyMutex my_mutex;
#endif
/** global variable to save or not the DATA .dat and gnuplot scripts
  * default is false: otherwise too much space is needed */
extern bool save_data;

/*RAM optimization*/
extern unsigned long MAX_SIZE_TMP_FILE;
extern unsigned long SIZE_SINGLE_TMP_FILE;
