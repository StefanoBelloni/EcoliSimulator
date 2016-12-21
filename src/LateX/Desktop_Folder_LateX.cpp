//
//  Desktop_Folder_LateX.cpp
//  Ecoli_4.1.4
//
//  Created by Stefano Belloni on 27/10/15.
//  Copyright © 2015 Stefano Belloni. All rights reserved.
//

#include <iostream>
#include <fstream>
#include "dirent.h"
#include <sys/stat.h>
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    #include <direct.h>
    #define getcwd _getcwd // stupid MSFT "deprecation" warning
#else
    #include <unistd.h>
#endif
#include <limits>
#include <ctime>

#include "GlobalVariables.h"
#include "Dir_Global.h"
#include "Colori.h"
#include "ErrorsDefinition.h"

using std::cout;
using std::endl;
using std::ofstream;
using std::string;

void LateX_Preambolo(std::ofstream &file_teX);
int LateX_Corpo(ofstream &file_teX, const char final[]);
int SetFolderData(string mainFolder);
int writeLog(string what, string msg);

//*****************************************************************************************************
//                  SET MAIN FOLDER
//*****************************************************************************************************


int SetMainFolder(int demo_mode)
/***********************************************
 *      MAIN_FOLDER DESKTOP
 - create Folder on the desktop dove andremo 
    a salvare tutti i dati
 ************************************************/
{
    
    cout << "set main folder " << endl;
    
    static char time_buffer[40];
    const struct std::tm *tm_ptr;
    //size_t len;
    std::time_t now;
    int err_dir=1;
    
    
    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );
    
    //len = std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    
    MainFolder = (demo_mode==1)?"E_coli_":"DEMO_E_coli_";
    
    MainFolder = MainFolder+time_buffer;
    
    std::string tmpDir = getcwd(NULL,0);

    //const char* homeDir = getenv ("HOME");
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    tmpDir+=std::string("\\tmpEcoli");
    char final_dir [256];
    sprintf (final_dir, "%s\\%s",Location.c_str(),MainFolder.c_str());
    err_dir = mkdir(final_dir);
    
#else
    
    tmpDir+=std::string("/tmpEcoli");
    char final_dir [256];
    sprintf (final_dir, "%s/%s",Location.c_str(),MainFolder.c_str());
    err_dir = mkdir(final_dir,0775);
    // make tempdir if not exists

#endif
    

    ofstream file_temp_log;
    file_temp_log.open(nameLog, std::ios_base::binary | std::ios_base::app|std::ios_base::ate);
    file_temp_log << endl << "#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!" << endl;
    file_temp_log << "                 ECOLI SIMULATOR" << endl;
    file_temp_log << "#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!#!" << endl;
    file_temp_log << "** Version: " << VERSION << " **" << endl;
    file_temp_log << "** Maximum number thread to be used: " << n_thread_available << " **" << endl << endl;
    std::strftime ( time_buffer, 40, "%d %B %Y %I:%M.%S %p", tm_ptr);
    file_temp_log << "* Program started: " << endl
                  << "  --> " << time_buffer << endl;
    file_temp_log << "* Directory where to save the files: " << endl;
    file_temp_log << "  --> " << final_dir << endl;

    file_temp_log.close();
    
    //const char* homeDir = getenv ("HOME");
   int existDir = system("cd tmpEcoli");
    if (existDir){
        cout << "tmpDir: " << tmpDir << endl;
        sprintf (final_dir, "%s",tmpDir.c_str());
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
        // make dir is different
        err_dir += mkdir(final_dir,0775);
#else
        err_dir += mkdir(final_dir,0775);
#endif
    }
    
    return err_dir;
    
}


//*****************************************************************************************************
//                  SET FOLDER LATEX
//*****************************************************************************************************

/** Set in which subfolder we save the routine.
 * with this function we create a folder whose name is the time when the sim finished,
 * it copies all file in the folder, prepared the lateX file and compile it (on Unix systems, on windows you have to do manually) (this function is system dependent!)
 * @param number_routine in other words, it is the number of the loop begin end we're in
 * @param demo_mode if demo_mode!=1 name of the folder start with DEMO_E_coli_
 */

int SetFolder_LateX(int demo_mode, int number_routine)
/***********************************************
 *      Folder in MainFolder for the Session
    [] - 1 Potrei togliere l'ora nelle cartelle routine.
 
 ************************************************/
{
    
    
    static char time_buffer[40];
    char buffer_routine[16];
    const struct std::tm *tm_ptr;
    string name_folder;
    //size_t len;
    std::time_t now;
    
    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );
    
    //len = std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    
    std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    snprintf(buffer_routine, sizeof(char) * 16,"Routine-%03d-",number_routine);
    name_folder = (demo_mode==1)?"E_coli_":"DEMO_E_coli_";
    name_folder = name_folder+buffer_routine+time_buffer;
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    char final_dir [256];
    sprintf (final_dir, "%s\\%s\\%s",Location.c_str(),MainFolder.c_str(),name_folder.c_str());
    mkdir(final_dir);
    
    string str_final_dir = final_dir;
    
    cout << "copying the data to " << final_dir << endl;
    
    string command_line_txt = "copy *.txt "+str_final_dir;
    string command_line_eps = "copy *.eps "+str_final_dir;
    string command_line_avi = "copy *.avi "+str_final_dir;
    string command_line_tex = "copy *.tex "+str_final_dir;
    string command_line_png = "copy *.png "+str_final_dir;
    string command_line_pth = "copy *.Ecoli "+str_final_dir;
    string command_line_fit = "copy *.fit "+str_final_dir;
    string command_line_gif = "copy *.gif "+str_final_dir;
    
    system(command_line_eps.c_str());
    system(command_line_txt.c_str());
    system(command_line_avi.c_str());
//    system(command_line_tex.c_str());
    system(command_line_png.c_str());
    system(command_line_pth.c_str());
    system(command_line_fit.c_str());
    system(command_line_gif.c_str());
    
#else
    
    char final_dir [256];
    sprintf (final_dir, "%s/%s/%s",Location.c_str(),MainFolder.c_str(),name_folder.c_str());
    mkdir(final_dir,0775);
    
    string str_final_dir = final_dir;
    
    cout << "copying the data to " << final_dir << endl;
    
    string command_line_txt = "cp *.txt " + str_final_dir;
    string command_line_eps = "cp *.eps " + str_final_dir;
    string command_line_avi = "cp *.avi " + str_final_dir;
    string command_line_tex = "cp *.tex " + str_final_dir;
    string command_line_png = "cp *.png " + str_final_dir;
    string command_line_pth = "cp *.Ecoli " + str_final_dir;
    string command_line_fit = "cp *.fit " + str_final_dir;
    string command_line_gif = "cp *.gif "+str_final_dir;
    

    system(command_line_eps.c_str());
    system(command_line_txt.c_str());
    system(command_line_avi.c_str());
    system(command_line_png.c_str());
    system(command_line_pth.c_str());
    system(command_line_fit.c_str());
    system(command_line_gif.c_str());

    
#endif
   
    if (save_data)
		SetFolderData(final_dir);
    
    //************************
    // CREAZIONE FILE LATEX
    
    ofstream file_teX;
    string name_teX = name_folder+".tex";
    file_teX.open(name_teX.c_str());
    
    LateX_Preambolo(file_teX);
    
    int error_=LateX_Corpo(file_teX, str_final_dir.c_str());
    
    if (error_!=0) {
        cout << BOLDRED<<"ERROR LateX_Corpo: " << RESET << error_ << endl;
        
        
        string msg("Error generating the lateX file.");
//        msg+=name_script_baricenter;
        writeLog("ERROR",msg);
        
        
        return 1;
    }
    
    file_teX << "\\end{document} " << endl;
    
    file_teX.close();
    
    system(command_line_tex.c_str());
        
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
        cout << "lateX file created ... to be compiled manually\n";
#else
    
    cout << "lateX file created ... to be compiled manually\n";
   // TODO: give the possibility to set if outo compilation tex file ... 
    //cout<<BOLDRED<<"\n*****************************************\n";
    //cout         <<" the LateX File is going to be compiled ...\n";
    //cout         <<"\n*****************************************\n"<< RESET << endl;
    //sprintf (final_dir, "cd %s",str_final_dir.c_str());
    
    //string command_maketex=final_dir;
    //command_maketex +=" && latexmk -pdf *.tex";
    //system(command_maketex.c_str());
    
#endif

    return 0;
    
}

//*****************************************************************************************************
//                  COPIA FILE .ECOLI
//*****************************************************************************************************

void CopyEcoliFiles(){
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    char final_dir [256];
    sprintf (final_dir, "%s\\%s",Location.c_str(),MainFolder.c_str());
    
    string str_final_dir = final_dir;
    
    string command_line_pth = "copy *.Ecoli "+str_final_dir;
    system(command_line_pth.c_str());
    
#else
    
    char final_dir [256];
    sprintf (final_dir, "%s/%s",Location.c_str(),MainFolder.c_str());
    
    string str_final_dir = final_dir;
    
    string command_line_pth = "cp *.Ecoli " + str_final_dir;

    system(command_line_pth.c_str());
    
#endif
    
    
}


/**
 * The following function save the data in a sub directory of the
 */


int SetFolderData(int demo_mode, int number_routine)
/***********************************************
 *      Folder in MainFolder for the Session
 [] - 1 Potrei togliere l'ora nelle cartelle routine.
 
 ************************************************/
{
    static char time_buffer[40];
    char buffer_routine[16];
    const struct std::tm *tm_ptr;
    string name_folder;
    //size_t len;
    std::time_t now;
    
    now = std::time ( NULL );
    tm_ptr = std::localtime ( &now );
    
    //len = std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    
    std::strftime ( time_buffer, 40, "%d%B%Y_%I_%M_%S_%p", tm_ptr);
    snprintf(buffer_routine, sizeof(char) * 16,"DATA_Routine-%03d-",number_routine);
    name_folder = (demo_mode==1)?"E_coli_":"DEMO_E_coli_";
    name_folder = name_folder+buffer_routine+time_buffer;
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)


    char final_dir [256];
    sprintf (final_dir, "%s\\%s\\%s",Location.c_str(),MainFolder.c_str(),name_folder.c_str());
    mkdir(final_dir);
    
    string str_final_dir = final_dir;
    
    string command_line_dat = "copy *.dat " + str_final_dir;
    string command_line_gnu = "copy *.gnu " + str_final_dir;

    system(command_line_dat.c_str());
    system(command_line_gnu.c_str());
    
#else
    
    char final_dir [256];
    sprintf (final_dir, "%s/%s/%s",Location.c_str(),MainFolder.c_str(),name_folder.c_str());
    mkdir(final_dir,0775);
    
    string str_final_dir = final_dir;
    
    string command_line_dat = "cp *.dat " + str_final_dir;
    string command_line_gnu = "cp *.gnu " + str_final_dir;

    system(command_line_dat.c_str());
    system(command_line_gnu.c_str());

    
    
#endif
    
    
    return 0;
    
}

int SetFolderData(string baseFolder)
/***********************************************
 *      Folder in MainFolder for the Session
 [] - 1 Potrei togliere l'ora nelle cartelle routine.
 
 ************************************************/
{

    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    char final_dir [256];
    sprintf (final_dir, "%s\\%s",baseFolder.c_str(),"DATA");
    mkdir(final_dir);
    
    string str_final_dir = final_dir;
    
    string command_line_dat = "copy *.dat " + str_final_dir;
    string command_line_gnu = "copy *.gnu " + str_final_dir;
    
    system(command_line_dat.c_str());
    system(command_line_gnu.c_str());
    
#else
    
    char final_dir [256];
    sprintf (final_dir, "%s/%s",baseFolder.c_str(),"DATA");
    mkdir(final_dir,0775);
    
    string str_final_dir = final_dir;
    
    string command_line_dat = "cp *.dat " + str_final_dir;
    string command_line_gnu = "cp *.gnu " + str_final_dir;

    system(command_line_dat.c_str());
    system(command_line_gnu.c_str());
    
#endif
    
    
    return 0;
    
}

