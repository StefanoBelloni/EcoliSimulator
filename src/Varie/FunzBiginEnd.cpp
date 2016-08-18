//
//  FunzBiginEnd.cpp
//  Ecoli_4.1.4
//
//  Created by Stefano Belloni on 27/10/15.
//  Copyright © 2015 Stefano Belloni. All rights reserved.
//

#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include "GlobalVariables.h"
#include "GnuplotGlobal.h"
#include "Colori.h"
#include "Dir_Global.h"
#include <thread>
#include "apngasm_Global.h"
#include "GlobalRandomVariables.h"

#include "ErrorsDefinition.h"

#include "Declar_funz.h"
#include <unistd.h>


//***************************************************************************************************************************************
//***************************************************************************************************************************************

/** This function makes more readable the main: it contains all the internal part from the beginning of a routine of simulation to its end
 * it pass all the parameers we set.
 * @param the parameters stat_sim is used to check if we want to perform another routine or not: it is used in the function
 * int ConditionEnd(int &read_par_file, int &stat_sim, int &BiginEnd)
 * @return a negative number if something went wrong, otherwise it can return number of bacteria, 0 etc. 
 */


int FunzBiginEnd(int &number_routine, int &cont_gen_sim, int &read_par_file, string &versione_Matlab,vector<string> *pt_name_file_satistics, vector<string> *pt_name_info_satistics, int &demo_mode, int &stat_sim)
{
    // VARIABILI
    
    int MODE_return=0;
   
    // INIZIALIZZAZIONI
    
    number_routine=0;
    cont_gen_sim=0;
    
    // SIMULATION, STATISTICAL ANALYSIS, BOTH
    while (stat_sim!=0) {
        
        // If I use the same seed at the new cycle of simulation I clear the random engines ...
        if (same_seed) {
            cout << BOLDRED << "same seed ... " << endl << RESET;
            for (int i=0; i< n_thread_available; i++) {
                
//                cout << "ri inizialize random engine saved ... " << endl;
                
                rnd_ecoli.random_engines.push_back(*new std::mt19937_64(clock()));
//                rnd_ecoli.random_engine_saved.push_back(rnd_ecoli.random_engines[i]);
                
                rnd_ecoli.random_engines_seeded.push_back(false);
            }
            
            seedRandomObj(0,this_thread::get_id());
        }
        
        if (read_par_file!=0) funz_clear();
        else read_par_file=0;

        stat_sim=menu_simulation();
        
        if (stat_sim>3||stat_sim<=0) return -1;
        
        
        
        
        // SIMULATIONS AND ANALYSIS
        
        switch (stat_sim) {
            {case 1:
                
                MODE_return=MODE_simulation(versione_Matlab, cont_gen_sim);
                
                break;}
            {case 2:
                
                cout << "How many bacteria do you want to simulate ? ";
                cin >> MODE_return;
                
                MODE_return = MODE_statisticalAnalysis(versione_Matlab, cont_gen_sim, pt_name_file_satistics, pt_name_info_satistics, MODE_return);
                
                break;}
            {case 3:
                MODE_return=MODE_simulation(versione_Matlab, cont_gen_sim,pt_name_file_satistics, pt_name_info_satistics);
                MODE_return = MODE_statisticalAnalysis(versione_Matlab, cont_gen_sim,pt_name_file_satistics, pt_name_info_satistics, MODE_return);
                
                break;}
            {default:
                
                cout << "ERROR stat_sim out of range ... \n";
                return ERROR_OVERFLOW_PROGRAM_SELECTOR;
                break;}
        }
        
        // set folder and LateX
        if (automatic_!=1) {
            number_routine++;
            int risp =0;
            
            if (automatic_==0) {
                std::cout<< "Do you want to save the result of the current simulation in the Summarising folder?\n0 for yes, 1 for no: ";
                
                getInput( risp);
				std::cout << "Do you want to save also all the scripts and data? this might take lots of space on the disk\n0 for yes, 1 for no: "; 
				getInput(save_data);
//                getInput(risp);
            }
//            SetFolderData(demo_mode, number_routine);
            if (risp==0) SetFolder_LateX(demo_mode, number_routine);
        }
        
        last_deleting();
    }

    return MODE_return;
    
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

/**
 * This function check if we quit from the routine loop.
 * @param read_par_file==121 we just save the answer.
 * We can decide if we want to save the parameters.
 * @return an int !=0 if an error occured, otherwise 0
 
 */

int ConditionEnd(int &read_par_file, int &stat_sim, int &BiginEnd){
    
    int save_par=-1;
    int save_risposte_err=0;
    
    if (read_par_file==121) {
        cout << "\nThis setting will be saved without simulating anything\n";
        
        save_risposte_err = save_risposte();
        
        if (save_risposte_err!=0) {
            cout << "Error saving the parameters of the simulation ...\n";
            return ERROR_SAVING_PARAMETRS_SIMULATION;
        }
        
        //******************************************
        
    }else{
        if (automatic_==1) {
            
            cout << "\nDo you want to save these parameters in a file? \npress 0 for yes, 1 for no \n";
            getInput( save_par);
            
            
            //******************************************
            
            if(save_par==0){
                save_risposte_err = save_risposte();
                if (save_risposte_err!=0) {
                    cout << "Error saving the parameters of the simulation ...\n";
                    return ERROR_SAVING_PARAMETRS_SIMULATION;
                }
            }
            
            //******************************************
            
            automatic_=2;
            contatore_risposte=0;
            stat_sim=-1;
            
            BiginEnd=1;
        }
    }
    
    return 0;
    
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

void GestioneArgv(int argc, const char * argv[], string &versione_Matlab, int &readfromfile){
    readfromfile=-1;
    
    int n_arg=3;
    
    if (argc>=2) {
        // clear files
        if(strcmp(argv[1],"clear")==0){
            
            last_deleting();
            
            funz_clear();
            
            if (argc>=3) {
                versione_Matlab=argv[2];
                n_arg=4;
            }
            
        // clear settings
        }else if(strcmp(argv[1],"resetAll")==0){
            
            last_deleting();
            
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            string command_line_txt_rem = "del *.Ecoli ";
#else
            string command_line_txt_rem = "rm -Rf *.Ecoli ";
#endif
            system(command_line_txt_rem.c_str());
            
            funz_clear();
            
            if (argc>=3) {
                versione_Matlab=argv[2];
                n_arg=4;
            }
            
        // read file
        }else if (strcmp(argv[1],"file")==0 || strcmp(argv[1],"fileScript")==0){
            // IF I WANT ONLY TO READ FROM FILE
            last_deleting();
            readfromfile=0;
            
            if (argc>=3) {
                versione_Matlab=argv[2];
                
                n_arg=4;
            }
            
            // TODO ... might be useful to use this in the read from file option of the GUI version
            //          or just the GUI version: (The idea I have in mind)
            //        there I'll gather from the main manu the information, make a file and read it
        }else{
            versione_Matlab=argv[1];
        }
    }
    
    if (argc>=n_arg) {
        if (!strcmp(argv[n_arg-1],"n")) {
            string string_ = "/gnuplot ";
            gnuplotOpen = argv[n_arg-1]+string_;
        }
    }
    
//    cout << versione_Matlab << endl;
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    Location=Location+"\\Desktop";
#else
    Location=Location+"/Desktop";
#endif
    

}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

void ErrorImportPath(string &versione_Matlab){
    cout << BOLDBLUE << endl;
    timestamp();
    cout << RED << "Error importing path ...\n";
    cout << RESET << "\nDefault path to search for Matlab, Gnuplot and apngasm\n";
    pritn_path(versione_Matlab);
    
    cout << BOLDBLUE << "\nPress Enter to continue ... " << RESET << endl;
    cin.ignore();
    funz_clear();
    
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

/**
 * This function summarizes where you can find the files and how they are organized.
 */

int Congedo(int number_routine){
 
    std::cout << "\nThe Data have been saved in a Folder on the Desktop, whose name is:\n" << MainFolder <<endl;
    if (number_routine==0) {
        std::cout << "Paths and Preprogramed .Ecoli File have been saved in the Folder"<<endl;
    }else{
        std::cout << "There are " << number_routine << " subfolders with plots and LateX summaries"<<endl;
    }
    std::cout << "\n\n----------------------------------------------" << std::endl;
    std::cout << "\nThe program terminated.\n" << std::endl << RESET;
    
    return 0;
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

void ReadableFileRisp(int &stat_sim, int demo_mode){
    
    if(read_file_par(demo_mode)!=0){
        cout << BOLDRED << "\nNo file readable ... \nInsert value manually.\n\n";
    }else {
        automatic_=2;
        contatore_risposte=0;
        stat_sim=-1;
    }
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************

/*! \brief this function show the option of the menu
 */

void helpMenu(){
    funz_clearAll();
    cout << BOLDRED
         << "#############################################" << endl
         << "#             EcoliSimulator." << endl
         << "#############################################" << endl
        << RESET << VERSION
        << endl << endl;
    //        cout << "*****************************************************" << endl;
    cout << BOLDMAGENTA << "Available options:" << RESET << endl << endl
        << BOLDBLUE << "   --script ..........." << RESET << " there's no initial page:" <<endl
        <<"                            --> useful if you run a script" <<endl
        << BOLDBLUE << "   --clear ............" << RESET << " clear all possible trash data" <<endl
        << BOLDBLUE << "   --qclear ............" << RESET << " clear all possible trash data and exit" <<endl
        << BOLDBLUE << "   --reset ............" << RESET << " reset the program, cleaning all files and settings" <<endl
        << BOLDBLUE << "   --matlab=x  ........" << RESET << " set version matlab 'x'" << endl
        << BOLDBLUE << "   --gnuplot=y ........" << RESET << " set path to gnuplot 'y'" <<endl
        << BOLDBLUE << "   --j=n   ............" << RESET << " max number of cores to use:" << endl
        << "                           --> default is half of the available cores" <<endl << endl<< RESET
        << BOLDBLUE << "   --file=pathtofile .." << RESET << " read file risposte given by pathtofile" <<endl
        << "                           "<<BOLDRED<<"NOTE:"<< RESET << " if you type only '--file'" << endl
        << "                                 is intended the default," << endl
        << "                                 i.e. 'EcoliRisposte.Ecoli'" << endl
        << BOLDBLUE << "   --data ............." << RESET << " save all the data produced in the simulation" <<endl
        << "                       it can take lot of space on the disk." << endl
		<< "                       If you set once --data, it will be valid also" << endl
		<< "                       for future lunch of EcoliSimulator."<<endl
        << "                       " << BOLDRED << "NOTE:"<<RESET << " The default option saves only the summary, video and plots."<<endl
		<< "                       to set it back, type --data=no"<<endl
        << BOLDBLUE << "   --clclog ..........." << RESET << "clear the file Ecoli.LogEcoli" << endl
        << BOLDBLUE << "   --dir=x ..........." << RESET << "specify the path (from the user's root) where to save the data" << endl
        << "                       defoult (for the first lunch) is the working directory."<<endl
        << "                       If you want to restore the defoult pass --dir=cwd"<<endl
        << "                       for example if you want to save on the Desktop, type --dir=Desktop"<<endl
        << BOLDBLUE << "   --apngasm=x ........" << RESET << "x, is the path to apngasm (with / or \\)" << endl
        << "                       if apngasm is in the current directory type: "<<endl
        << "                          --apngasm=./ for Unix , just --apngasm= on Windows" << endl
        << "                       if x is set to no, then the video is not create" << endl
        << "                       with apngasm ('.png' file), but as a '.gif' file." << endl
        << "                       --apngams tells to create multilayer '.png' file. " << endl
        << "                       The defoult (for the first lunch) is '.gif' file." << endl
        << BOLDBLUE << "   --nocolors .........." << RESET << "it uses the default colors of the terminal." << endl << endl << endl
    //        cout << "*****************************************************" << endl;

        << "NOTE: on this computers " << std::thread::hardware_concurrency() << " cores are available. default is " << n_thread_available << " threads." << endl << endl;
    
}

//***************************************************************************************************************************************
//***************************************************************************************************************************************


/*! \brief New version of gestion Arg
 *
 * The new way to give option is --"option=" valore option.
 *      1- --matlab=x           // set version matlab x
 *      2- --gnuplot=y          // set path to gnuplot y, n to set default
 *      3- --file=namefile      // set file risposte to namefile [] TODO
 *             - default, i.e. only --file //EcoliRisposte ...
 *      4- --clear              // clear all possible trash data
 *      5- --reset              // rest cleaning all files and settings
 *      6- --j=n                // max number of core to use, default is all available
 *      7- --clclog             // clear the file Ecoli.LogEcoli
 *      8- --apngasm             // use or not apngasm
 *      9- --script              // if we do not want the initial page
 *      10- --dir=x               // set saving directory
 *
 */

int GestioneArgvV2(int argc, const char * argv[], string &versione_Matlab, int &readfromfile){
    
    // new options:
    readfromfile=-1;
    vector<string> checks;
    checks.push_back("--reset");
    checks.push_back("--clear");
    checks.push_back("--file");
    checks.push_back("--gnuplot=");
    checks.push_back("--matlab=");
    checks.push_back("--j=");
    checks.push_back("--clclog");
    checks.push_back("--nocolors");
    checks.push_back("--apngasm");
    checks.push_back("--script");
    checks.push_back("--dir=");
    checks.push_back("-qclear");
    checks.push_back("--data"); 
    unsigned int j=0;
    bool initial_p = true;
    bool search_more;
    int rtn_v = 0;
    for (unsigned int i=1; i<argc; i++) {
//        cout << "######################"<< endl;
//        cout << ":::::::::::::::::::::: argv: " << argv[i] << endl;
        j=0;
        search_more = true;
        while (j<checks.size() && search_more) {
//            cout << "check: " << checks[j] << endl;
            string temp(argv[i]);
            size_t position = temp.find(checks[j]);
            if (position != std::string::npos) {
                search_more = false;
//                std::cout << "!!!!!!!!!!!!!!!!!!!!" << endl;
//                std::cout << "option " << checks[j] << endl;
                position += checks[j].size();
                
                switch (j) {
                    // reset
                    {
                    case 0:
                        
                        last_deleting();
                        
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                        
                        string command_line_txt_rem = "del *.Ecoli ";
                        string command_line_txt_remLog = string("del ")+nameLog;
                        system(command_line_txt_rem.c_str());
                        system(command_line_txt_remLog.c_str());
                        
#else
                        string command_line_txt_rem = "rm -Rf *.Ecoli ";
                        string command_line_txt_remLog = string("rm -Rf ")+nameLog;
                        system(command_line_txt_rem.c_str());
                        system(command_line_txt_remLog.c_str());
#endif
                        funz_clearAll();
                        rtn_v = 1;
                        break;
                    }
                    // clear
                    {
                    case 1:
                        
                        last_deleting();
                        funz_clear();

                        break;
                    }
                    // file
                    {
                    case 2:
                        last_deleting();
                        readfromfile=0;
                        size_t position = temp.find("--file=");
                        if (position != std::string::npos){
                            temp = temp.substr(position+7);
                            cout << temp << endl;
                            fileEcoliRisp = temp;
                        }
                        break;
                    }
                    // gnuplot
                    {
                    case 3:
                        temp = temp.substr(position);
                        cout << temp << endl;
                        if (!strcmp(temp.c_str(),"n")) {
                            string string_ = "/gnuplot ";
                            gnuplotOpen = temp+string_;
                        }
                        break;
                    }
                    // matlab
                    {
                    case 4:
                        temp = temp.substr(position);
                        cout << temp << endl;
                        versione_Matlab = temp;
                        break;
                    }
                    // multithread
                    {
                    case 5:
                        temp = temp.substr(position);
                        cout << temp << endl;
                        
                        n_thread_available = atoi(temp.c_str());
                        unsigned int maxthread = std::thread::hardware_concurrency();
                        n_thread_available=std::min(n_thread_available,maxthread);
                        cout << "n_thread_available = " << n_thread_available << endl;
                        if (n_thread_available < 2) {
                            multithread = false;
                        }else{
                            multithread = true;
                        }
                        break;
                    }
                    // clear Log
                    {
                    case 6:
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                        string command_line_txt_remLog = string("del ")+nameLog;
                        system(command_line_txt_remLog.c_str());
#else
                        string command_line_txt_remLog = string("rm -Rf ")+nameLog;
                        system(command_line_txt_remLog.c_str());
#endif
                        break;
                    }
                    {// colors yes, no ...
                     case 7:
                        colors = false;
                        break;
                    }
                    { // apngasm yes no ...
                    case 8:
                        
                        size_t position = temp.find("--apngasm=");
//                        cout << "temp:: " << temp << endl;
                        
                        if (position != std::string::npos){
                            temp = temp.substr(position+10);
//                            cout << "temp: "<< temp << endl;
                            if (strcmp(temp.c_str(),"no")==0) {
                                no_apngams = true;
//                                cout << "apngasm(no): " << apngas_lunch << endl;
                            }else{
                                apngas_lunch = temp;
                                
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                                apngas_lunch+= "apngasm.exe ";
#else
                                apngas_lunch += "apngasm ";
#endif
                                no_apngams = false;
//                                cout << "apngasm(yes): " << apngas_lunch << endl;
                            }
                        }
                        else{
//                            cout << "temp: "<< temp << endl;
                            no_apngams = false;
                        }
                        
                        break;
                    }
                    { // script
                    case 9:
                        initial_p = false;
                        break;
                    }
                        // location directory
                    {
                    case 10:
                        size_t position = temp.find("--dir=");
                        if (position != std::string::npos){
                            temp = temp.substr(position+6);
                            if (strcmp(temp.c_str(),"cwd")==0) {
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                                //        Location=Location+"\\Desktop";
                                Location = getcwd(NULL,0);
#else
                                //        Location=Location+"/Desktop";
                                Location = getcwd(NULL,0);
#endif
                            }else{
                                
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                            //        Location=Location+"\\Desktop";
                                Location = "\\"+temp;
#else
                            //        Location=Location+"/Desktop";
                                Location = "/"+temp;
                            
#endif
                            }
                        }
                        break;
                    }
                        // clear
                    {
                    case 11:
                        
                        last_deleting();
                        funz_clear();
                        exit(0);
                        break;
                    }
					{
					case 12:
                        size_t position = temp.find("--data=no");
                        if (position != std::string::npos){
                        	save_data = false;
						}else{
							save_data = true;	
						}
					}
                    {
                    default:
                        break;
                    }
                }
                
            }
            j++;
        }
        
    }
//    string str;
//    cout << "Press a key ";
//    cin >> str;
    //    cout << versione_Matlab << endl;
    
    if (initial_p){
        initial_page();
    }
    
    return rtn_v;
    
}
//***************************************************************************************************************************************
//***************************************************************************************************************************************

/*! \brief seed random object
 */

void seedRandomObj(int n_this_thread, thread::id hash_code){
    
    if (!rnd_ecoli.random_engines_seeded[n_this_thread])
    {
        // seed the engine!
        rnd_ecoli.random_engines[n_this_thread]         = std::mt19937_64(clock()+1000*(1+n_this_thread));
        rnd_ecoli.random_engines_seeded[n_this_thread]  = true;
        rnd_ecoli.random_engines_barrier[n_this_thread] = std::mt19937_64(clock()+2000*(1+n_this_thread));
        rnd_ecoli.random_engines_theta[n_this_thread]   = std::mt19937_64(clock()+3000*(1+n_this_thread));
        rnd_ecoli.random_engine_saved[n_this_thread]          = rnd_ecoli.random_engines[n_this_thread];
        rnd_ecoli.random_engines_barrier_saved[n_this_thread] = rnd_ecoli.random_engines[n_this_thread];
        rnd_ecoli.random_engines_theta_saved[n_this_thread]   = rnd_ecoli.random_engines[n_this_thread];
    }
    else{
        if (same_seed) {
            cout << BOLDRED << "same seed ... " << endl << RESET;
            rnd_ecoli.random_engines[n_this_thread]         = rnd_ecoli.random_engine_saved[n_this_thread];
            rnd_ecoli.random_engines_barrier[n_this_thread] = rnd_ecoli.random_engines_barrier[n_this_thread];
            rnd_ecoli.random_engines_theta[n_this_thread]   = rnd_ecoli.random_engines_theta[n_this_thread];
            //            rnd_ecoli.random_engines_seeded[n_this_thread]=true;
        }
    }
}
//***************************************************************************************************************************************
//***************************************************************************************************************************************

/*! \brief this function write to the Log file.
 */

#include <fstream>

int writeLog(string topic, string message){
    
    ofstream file_temp_log;
    
    file_temp_log.open(nameLog.c_str(), std::ios_base::binary | std::ios_base::app|std::ios_base::ate);
    
    if (file_temp_log.is_open()) {
        
        static char time_buffer[40];
        const struct std::tm *tm_ptr;
        //size_t len;
        std::time_t now;
        
        now = std::time ( NULL );
        tm_ptr = std::localtime ( &now );
        
        //len = std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
        std::strftime ( time_buffer, 40, "%d %B %Y %I:%M.%S %p", tm_ptr);
        file_temp_log << endl << "  ++ " << time_buffer <<" ++" <<endl;
        file_temp_log << "* " << topic << endl;
        file_temp_log << "  --> "<< message << endl;
        file_temp_log.close();
        return 0;
    }
    
    return -1;
}
