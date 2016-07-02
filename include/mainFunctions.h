//
//  mainFunctions.h
//  Ecoli_4.1.4c
//
//  Created by Stefano Belloni on 24/02/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

//#ifndef mainFunctions_h
//#define mainFunctions_h


#include <thread>

/**
 * This function drow the initial page for the command line program.
 * note: for windows it is without colors. To change modify the definition of color in Color.h
 * It set the initial page size: if it doesn't fit, work on it.
 * There's one definition for Windows, one for Mac (it should works also for Unix system, but I didn't test it)
 */

void initial_page();

/**
 * This function set the seed of the pseudo-random variable
 * in the file FunzRand.h in the uniform distribution function it is written a possible reseed when enough random number are generated: check variable con_rand.
 */
void seed();


/**
 * It take possible input from command line and deals with it
 * It also set the Desktop as location for the folder.
 * if you pass "file", only the simulation is guided by the file "EcoliRisposte.Ecoli" in the same folder
 * @param versione_Matlab: save whioch version of matlab the program, when asked, has to lunch
 * @param argv[] can be of the following: clear, delete all file .dat, .gnu, .eps, .txt, .avi, .png (see void last_deleting())
 *                it can be followed by versione_Matlab, otherwise versione_Matlab is the first argument
 *                to pass no versione_Matlab, pass 'n'. the 3nd argument can be the location of gnuplot. You can always set it afterwords, or read it from file

 */
void GestioneArgv(int argc, const char * argv[], string &versione_Matlab);

int GestioneArgvV2(int argc, const char * argv[], string &versione_Matlab, int &readfromfile);

/**
 * The function read the file 'EcoliPath.Ecoli', where there are saved path and option for the programs gnuplot, agapng and matlab
 */
int import_path(string versione_MATLAB);

/**
 * If a problem occued while reading the file 'EcoliPath.Ecoli', it display the path and relative information of default: you can modify them afterwords
 */

void ErrorImportPath();

/**
 * This function set the MODE of the program: read from file, step-by-step or DEMO
 * pressing 121 you can enter the menu to set the parameters of the ausiliary programs
 * see function: set_gnuplot_Matlab_apngas(versione_Matlab)
 */

int set_MODE_Program(string &versione_Matlab, int &demo_mode, int readfromfile);


/** This function create  MAIN_FOLDER
 * - create Folder in the desired location where we save and collect all the data.
 * @param demo_mode == 1, the folder name is DEMO_etc...
 * the name is obtain from the current data.
 */

int SetMainFolder(int demo_mode);


/** If we open the file of the answer ok, otherwise we have to insert input manually
 * see func. int read_file_par()
 */

void ReadableFileRisp(int &stat_sim, int demo_mode);


/** This function makes more readable the main: it contains all the internal part from the beginning of a routine of simulation to its end
 * it pass all the parameers we set.
 * @param the parameters stat_sim is used to check if we want to perform another routine or not: it is used in the function
 * int ConditionEnd(int &read_par_file, int &stat_sim, int &BiginEnd)
 */

int FunzBiginEnd(int &number_routine, int &cont_gen_sim, int &read_par_file, string &versione_Matlab,vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics, int &demo_mode, int &stat_sim);

/**
 * This function check if we quit from the routine loop.
 * @param read_par_file==121 we just save the answer.
 * We can decide if we want to save the parameters.
 * @return an int !=0 if an error occured, otherwise 0
 
 */

int ConditionEnd(int &read_par_file, int &stat_sim, int &BiginEnd);


/**
 * delete all file .dat, .gnu, .eps, .txt, .avi, .png
 */

void last_deleting();

/** The function saves in "EcoliPath.Ecoli" the parameters and path about the program Matlab, gnuplot etc.
 */

int save_path(string versione_MATLAB);


/**
 * The function save the file .Ecoli (which are .txt files) in the main folder. 
 * In Windows, the main folder is on the Desktop: Modify it following the Unix version
 */

void CopyEcoliFiles();


/**
 * This function tells you where you find the results of the simulation: the folder and its organization.
 */

int Congedo(int number_routine);

//#endif /* mainFunctions_h */


//void seedRandomObj(int n_this_thread, long hash_code);
void seedRandomObj(int n_this_thread, std::thread::id hash_code);


int writeLog(string topic, string message);