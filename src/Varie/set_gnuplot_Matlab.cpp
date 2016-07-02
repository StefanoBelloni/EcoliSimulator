//
//  set_gnuplot_Matlab.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 10/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <cstring>
#include <limits>
#include <sstream>
#include "Declar_funz.h"

#include "Colori.h"
#include "GnuplotGlobal.h"
#include "MATLAB_Global.h"
#include "apngasm_Global.h"
#include "Dir_Global.h"

#include "setSizesTitles.hpp"

using namespace std;

void funz_clear();
void funz_clearAll();
void lunch_gnuplot(string name_file_gnu);

void set_gnuplot();
void set_matlab(string &versione_Matlab);
void set_apngasm();
void set_Location();
void set_gif();
void set_lunch_firefox();
void general_settings();
/**
 * This function set all the parameters to call the external program and set The location of the summary folder
 */

void set_gnuplot_Matlab_apngas(string &versione_Matlab)
{

    general_settings();
    set_lunch_firefox();
    set_Location();
    set_gnuplot();
    set_matlab(versione_Matlab);
    if (no_apngams) {
        set_gif();
    }else{
        set_apngasm();
    }
}

/*! \brief Settings of n. cores and the use or not of the program apngasm.*/
void general_settings(){
    int risp_=1;
    cout << BOLDBLUE <<"##############################################################\n";
    cout << BOLDBLUE << "Actual number of cores in use: " << n_thread_available << endl;
    cout << "Maximum number of cores available: " << std::thread::hardware_concurrency() << endl;
    cout << BOLDBLUE << "How many cores do you want to use to perform\nthe simulations and analysis of independent population?\n"<< RESET;
    cout << "n. cores: ";
    getInput( risp_);
    n_thread_available = fmin(std::thread::hardware_concurrency(), risp_);
    cout << BOLDBLUE <<"\n##############################################################\n";
    cout << BOLDBLUE << "Do you want to use apngams?\n"<< RESET;
    cout << "press 0 for yes, 1 for no: ";
    getInput( risp_);
    if (risp_==0) {
        no_apngams = false;
    }
}

//*************************
// set_Location()
//*************************
void set_Location()
{
    int risp_=0;
    
    while (risp_==0){
        funz_clear();
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        cout << BOLDRED << "#    SETTING PATH" << RESET << endl;
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        cout << BLUE << "\nThe current path where the program is going to save the summaries and plot is :\n";
        cout << RESET << Location << endl;
        cout << BLUE << "#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set a different path?\n"<< RESET;
        cout << "This new path will be used for all files in the current session.\n" << RESET;
        cout << "press 0 for yes, 1 for no ";
        getInput( risp_);
        if (risp_==0) {
            cout << BLUE << "insert the path (without \\ at the end): \n" << RESET;
            
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "if in the path there is a Folder with spaces, please use the following formattation:\n" ;
            cout << "use dopple slash (//) between two folder, / and \" to wrap a folder with spaces in the name:\n" ;
    #else
            
    #endif
            cout << homeDir;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::getline (std::cin,Location);
            Location=homeDir+Location;
            cout << RED << "\nthe path is : \n" << RESET;
            cout << Location << endl;
            
            cout << BLUE << "\nThe new path where the program is going to save the summaries and plot is :\n";
            cout << RESET << Location << endl;
            cout << BOLDRED << "\nDo you conferm it? Press 0 to correct the path\n" << RESET;
            
            getInput( risp_);
            
        }
        
        

    }
    
}

//*************************
// SET GNUPLOT
//*************************
void set_gnuplot()
{
    int risp_=0;
    int demo_=0;
    
    ofstream file_prova;
    
    while (risp_==0){
        
        funz_clear();
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        cout << BOLDRED << "# GNUPLOT SETTING" << RESET << endl;
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        

        cout << BLUE << "The command pass to the terminal to open gnuplot is " << endl;
        cout << RESET << gnuplotOpen << endl;
        
        //**************************************************
        //PATH
        //**************************************************
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set a different path? \npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        
        if (risp_==0) {
            cout << BLUE << "insert the path (with / (\\) at the end): \n" << RESET;
            
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "if in the path there is a Folder with spaces, please use the following formattation:\n" ;
            cout << "use dopple slash (//) between two folder, / and \" to wrap a folder with spaces in the name:" ;
            string gnuplot_ = "gnuplot ";
#else
            string gnuplot_ = "gnuplot ";
            
#endif
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::getline (std::cin,gnuplotOpen);
            cout << RED << "\nthe path is : \n" << RESET;
            cout << gnuplotOpen << endl;
            gnuplotOpen+=gnuplot_;
            
            cout << "specificcally, through the terminal to open it it is lunche the command " << endl;
            cout << gnuplotOpen << endl;
        }
        
        //**************************************************
        //TERMINAL
        //**************************************************
        
        string term = gnuplotSetTerminalPlot;
        term.erase(0, 13);
        size_t position = term.find(" ");
        if (position != std::string::npos){
            term.erase(position);
        }
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to change the terminal used by gnuplot\n";
        cout << "The terminal in used is " << term << "\npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        if  (risp_==0){
            cout << "give the name of the terminal, for example x11, qt, etc...  : ";
            cin >> term;
        }
        string cmd_term=string("set terminal ")+term+string (" size ");
        
        //**************************************************
        //SIZE
        //**************************************************
        int w = 1440;
        int h = 900;
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set the size (in pixel) of the immages (default 1440,900)\nproduced by gnuplot\npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        if (risp_==0) {
            cout << "heigh: " << RESET << endl;
            getInput( h);
            cout << "width: " << RESET << endl;
            getInput( w);
            
            risp_=1;
        }
        stringstream msg;
        msg.str("");
        msg << cmd_term << w << "," << h ;
        gnuplotSetTerminalPlot = msg.str();
        
        // position windows ...
        int p_w = 10;
        int p_h = 10;
        cout << BLUE << "\n\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set the position (top-left corner) of the windows (default 10,10)\nused by gnuplot to plot\npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        if (risp_==0) {
            cout << "heigh: " << RESET << endl;
            getInput( p_h);
            cout << "width: " << RESET << endl;
            getInput( p_w);
            risp_=1;
        }
//        stringstream msg;
        msg.str("");
        msg << " position " << p_w << "," << p_h ;
        gnuplotSetTerminalPlot += msg.str();
        
        
        //**************************************************
        //DEMO
        //**************************************************
        funz_clearAll();
        
        cout << BOLDRED << "##############################" << RESET << endl;
        cout << BOLDRED << "#       GNUPLOT SETTING      #" << RESET << endl;
        cout << BOLDRED << "##############################" << RESET << endl;
        
        cout << RED << "Do you want to try a demo program? \npress 0 for yes, 1 for no " << RESET;
        getInput( demo_);
        
        if (demo_==0) {
            
            funz_clear();
            cout << BOLDRED << "GNUPLOT DEMO PROGRAM" << RESET << endl;
            
            file_prova.open("prova_gnuplot.gnu");
            
            file_prova << gnuplotSetTerminalPlot << endl <<
            
            "set view 75, 230, 1, 1" << endl <<
            "set samples 20, 20" << endl <<
            "set isosamples 20, 20" << endl <<
            "set contour base"<< endl <<
            "set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover"<< endl <<
            "set title \"Hidden line removal of explicit surfaces\" "<< endl <<
            "set xrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl <<
            "set yrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl <<
            "set zrange [ -1.00000 : 1.00000 ] noreverse nowriteback"<< endl <<
            "splot sin(x) * cos(y)"<< endl
            
            << "pause mouse any" << endl
            << "quit" <<endl;
            
            file_prova.close();
            
            lunch_gnuplot("prova_gnuplot.gnu");
            
            
        }
        
        cout << RED << "\nTo save the changes press 1, to set new setting press 0: " << RESET;
        getInput( risp_);
        
        
    }
    
    remove("prova_gnuplot.gnu");
    
}

//*************************
// SET MATLAB
//*************************
void set_matlab(string &versione_Matlab)
{
    int risp_=0;
    int demo_=0;
    
    ofstream file_prova;
    
    
    do{
        
        if (risp_==0) {
            
            funz_clear();
            cout << BOLDRED << "#######################################################################" << RESET << endl;
            cout << BOLDRED << "# MATLAB_SETTING" << RESET << endl;
            cout << BOLDRED << "#######################################################################" << RESET << endl;
            
            file_prova.open("matlab_gnuplot.m");
            
            file_prova << "[X,Y,Z] = peaks(25);" << endl
                       << "figure" << endl
                       << "surf(X,Y,Z);" << endl
                       << "pause(3);" << endl
                       << "quit" << endl;   
            file_prova.close();
            
            string command = MATLAB_loc+versione_Matlab+MATLAB_call+"matlab_gnuplot";
            system(command.c_str());
            
            
        }
        
        
        cout << BLUE << "\nThe current version of Matlab is: ";
        cout << RESET<< versione_Matlab << endl;
        cout << BLUE << "The call of the program is done via: \n:";
        cout << RESET << MATLAB_loc << versione_Matlab << MATLAB_call;
        
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set a different path? \npress 0 for yes, 1 for no " << RESET ;
        getInput( risp_);
        
        if (risp_==0) {
            cout << BLUE << "insert the path (up to the folder where 'MATLAB_Rxxx.app' is located. without \\ at the end): \n" << RESET ;
            
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "if in the path there is a Folder with spaces, please use the following formattation:\n" ;   
            cout << "use dopple slash (//) between two folder, / and \" to wrap a folder with spaces in the name:" ;                
            #endif
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::getline (std::cin,MATLAB_loc);
            cout << BLUE << "\nthe path is : \n" << RESET;
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            MATLAB_loc+="//MATLAB_R";
            #else
            MATLAB_loc+="/MATLAB_R";
            #endif  
                
            cout << MATLAB_loc << endl;
            
        }
        
        
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set a different version of Matlab? \npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        
        if (risp_==0) {

            
            cout << BLUE << "insert the version of Matlab: \n" << RESET;
            
            #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
                cout << "if in the path there is a Folder with spaces, please use the following formattation:\n" ;   
                cout << "use dopple slash (//) between two folder, / and \" to wrap a folder with spaces in the name:" ;                
            #endif
            
//            cin.clear();
//            cin.ignore(numeric_limits<streamsize>::max(), '\n');
//            std::getline (std::cin,versione_Matlab);
            cin >> versione_Matlab;
            cout << "\nthe Matlab version is : \n";
            cout << versione_Matlab << endl;
            
            
            cout << "specifically, through the terminal to open it, it is lunche the command " << endl;
            cout << MATLAB_loc << versione_Matlab << MATLAB_call;
        }
        funz_clearAll();
        
        cout << BOLDRED << "#########################" << RESET << endl;
        cout << BOLDRED << "#    MATLAB_SETTING     #" << RESET << endl;
        cout << BOLDRED << "#########################" << RESET << endl;
        
        cout << RED << "Do you want to try a demo program? \npress 0 for yes, 1 for no ";
        getInput( demo_);
        if (demo_==0) {
            risp_=0;
        }
        
        
    }while (demo_==0);
    remove("matlab_gnuplot.m");
}

//*************************
// SET APNGASM
//*************************
void set_apngasm(){

    int risp_=0;
    int demo_=0;
    string name;
//    string name_out="name_out.png";
    string command;
    ofstream file_prova;
    
    do{
        if (risp_==0) {
            funz_clear();
            
            file_prova.open("prova_gnuplot.gnu");
            file_prova << gnuplotSetTerminalSave_png << endl;
            for (int i=0; i<10; i++) {
                file_prova << "set output \"name_file"<<i<<".png\" # output=fileout"<< endl <<             
                "set view 75, 230, 1, 1" << endl <<
                "set samples 20, 20" << endl <<
                "set isosamples 20, 20" << endl <<
                "set contour base"<< endl <<
                "set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover"<< endl <<
                "set title \"Hidden line removal of explicit surfaces\" "<< setSizesTitles(sizeTitle::LARGE, 1)<< endl <<
                "set xlabel 'x'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl <<
                "set ylabel 'y'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl <<
                "set zlabel 'z'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl <<
                "set xrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl <<
                "set yrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl <<
                "set zrange [ -1.00000 : 1.00000 ] noreverse nowriteback"<< endl <<
                "splot sin("<<i+1 <<"*pi/20*x) * cos(y)"<< endl;
            }
            file_prova.close();
            lunch_gnuplot("prova_gnuplot.gnu");
            cout << BOLDRED << "######################" << RESET << endl;
            cout << BOLDRED << "#   APNGASM_SETTING  #" << RESET << endl;
            cout << BOLDRED << "######################" << RESET << endl;
            string name="name_file*.png";
            
//*****************************************************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            command= apngas_lunch+" name_out.png "+ name + apngas_opt;            
#else
            command= apngas_lunch+name+" -o name_out.png "+apngas_opt;                                               
#endif
//*****************************************************************************************************************************
            system(command.c_str());
//*****************************************************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "no automatic visalization ...\n";            
#else
            string command_call= "open -a firefox name_out.png";
            system(command_call.c_str());
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "press Enter to continue ... " << endl;
            cin.ignore();
#endif
//*****************************************************************************************************************************
            remove("output.png");
            remove("name_out.png");
            remove("prova_gnuplot.gnu");
            remove("name_file0.png");
            remove("name_file1.png");
            remove("name_file2.png");
            remove("name_file3.png");
            remove("name_file4.png");
            remove("name_file5.png");
            remove("name_file6.png");
            remove("name_file7.png");
            remove("name_file8.png");
            remove("name_file9.png");
            
            
        }
        
        cout << BLUE << "The call of the program is done via: \n:";
        cout << RESET << command;
        
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED <<"Do you want to set a different path? \npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        
        if (risp_==0) {
            cout << BLUE << "insert the path (up to the folder where '\apngasm.exe' is located. without \\ at the end): \n";
            
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "if in the path there is a Folder with spaces, please use the following formattation:\n" ;   
            cout << "use dopple slash (//) between two folder, / and \" to wrap a folder with spaces in the name:" ;                
#endif
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            std::getline (std::cin,apngas_lunch);
            cout << "\nthe path is : \n";
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            apngas_lunch+="\\apngasm.exe";
#else
            apngas_lunch+="/apngasm.exe";
#endif  
      
        }
        
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set different options for apngas? \npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        
        if (risp_==0) {
            
            command = apngas_lunch + "--help";
            
            system(command.c_str());
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << BOLDBLUE << "\nInsert the options: with an empty space as first character\n";
            cout << BOLDRED << "The default options are: " << RESET << apngas_opt << endl; 
            std::getline(std::cin,apngas_opt) ;
        }
        
        int w = 1440;
        int h = 900;
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set the size (in pixel) of the immages\nproduced by gnuplot and assamble by apngasm\npress 0 for yes, 1 for no " << RESET;;
        getInput( risp_);
        if (risp_==0) {
            cout << "heigh: " << RESET << endl;
            getInput( h);
            cout << "width: " << RESET << endl;
            getInput( w);
            stringstream msg;
            msg.str("");
            msg << "set terminal pngcairo size " << w << "," << h ;
            gnuplotSetTerminalSave_png = msg.str();
            risp_=1;
        }
        funz_clearAll();
        cout << BOLDRED << "###########################" << RESET << endl;
        cout << BOLDRED << "#     APNGASM_SETTING     #" << RESET << endl;
        cout << BOLDRED << "###########################" << RESET << endl;
        cout << BOLDRED << "Do you want to try a demo program? \npress 0 for yes, 1 for no " << RESET;
        getInput( demo_);
        
        if (demo_==0) {
            risp_=0;
        }
        
    }while (demo_==0);
}

//*************************
// SET GIF
//*************************
void set_gif(){
    
    int risp_=0;
    int demo_=0;
    string name;
    //    string name_out="name_out.png";
    string command;
    ofstream file_prova;
    
    funz_clearAll();
    
    do{
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        cout << BOLDRED << "# GNUPLOT .gif SETTING" << RESET << endl;
        cout << BOLDRED << "#######################################################################" << RESET << endl;
        if (risp_==0) {
            file_prova.open("prova_gnuplot.gnu");
            file_prova << gnuplotSetTerminalSave_gif << endl
                        << "set output \"name_out.gif\" # output=fileout"<< endl
                        << "i=1" << endl
                        << "set view 75, 230, 1, 1" << endl
                        << "set samples 20, 20" << endl
                        << "set isosamples 20, 20" << endl
                        << "set contour base"<< endl
                        << "set hidden3d back offset 1 trianglepattern 3 undefined 1 altdiagonal bentover"<< endl
                        << "set title \"Hidden line removal of explicit surfaces\" "<< setSizesTitles(sizeTitle::LARGE, 1)<< endl
                        << "set xlabel 'x'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl
                        << "set ylabel 'y'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl
                        << "set zlabel 'z'"<< setSizesTitles(sizeTitle::MEDIUM, 1)<< endl
                        << "set xrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl
                        << "set yrange [ -3.00000 : 3.00000 ] noreverse nowriteback "<< endl
                        << "set zrange [ -1.00000 : 1.00000 ] noreverse nowriteback"<< endl
                        << "load 'animate.gnu'" << endl
                        << "set output" << endl;
            file_prova.close();
            
            file_prova.open("animate.gnu");
            file_prova << "splot sin(i*pi/20*x) * cos(y)"<< endl
                       << "i=i+1" << endl
                       << "if (i < 10) reread" << endl;
            file_prova.close();
            
            lunch_gnuplot("prova_gnuplot.gnu");
            
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
            cout << "no automatic visalization ...\n";
#else
            string command_call= "open -a firefox name_out.gif";
            system(command_call.c_str());
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "press Enter to continue ... " << endl;
            cin.ignore();
#endif
            remove("name_out.gif");
            remove("prova_gnuplot.gnu");
            remove("animate.gnu");
        }
        
        int w = 1440;
        int h = 900;
        cout << BLUE << "\n#######################################################################" << RESET << endl;
        cout << RED << "Do you want to set the size (in pixel) of the .gif immages\nproduced by gnuplot\npress 0 for yes, 1 for no " << RESET;
        getInput( risp_);
        if (risp_==0) {
            cout << "heigh: " << RESET << endl;
            getInput( h);
            cout << "width: " << RESET << endl;
            getInput( w);
            stringstream msg;
            msg.str("");
            msg << "set term gif animate size " << w << "," << h ;
            gnuplotSetTerminalSave_png = msg.str();
            risp_=1;
        }
        funz_clearAll();
        cout << BOLDRED << "#############################" << RESET << endl;
        cout << BOLDRED << "#     GNUPLOT .gif SETTING  #" << RESET << endl;
        cout << BOLDRED << "#############################" << RESET << endl;
        cout << RED << "Do you want to try a demo program? \npress 0 for yes, 1 for no " << RESET;
        getInput( demo_);
        
        if (demo_==0) {
            risp_=0;
        }
        
    }while (demo_==0);
    
}

/*! \brief setting for the .png/.gif reader*/
void set_lunch_firefox(){
    
    int input = 0;
    int demo_=0;
    
    while (input==0) {
        funz_clear();
        cout << BOLDRED << "###############################" << RESET << endl;
        cout << BOLDRED << "#  SETTINGS .png .gif READER  #" << RESET << endl;
        cout << BOLDRED << "###############################" << RESET << endl;
        cout << "Actual command to lunch the reader of .png and/or .gif format\n: " << firefox_path << endl;
        cout << RED << "Do you want to change the command and/or program  to open the reader of .png and/or .gif format?\n0 for yes, 1 for no " << RESET;
        getInput(input);
        if (input==0) {
            cout << "You have to pass the command to lunch it from the terminal/DOS:\n";
            cout << "command: ";
            getInput(firefox_path);
            firefox_path+=" ";
        }
        cout << RED << "Do you want to try the program? \npress 0 for yes, 1 for no " << RESET;
        getInput( demo_);
       
        if (demo_==0) {
            size_t position = firefox_path.find("firefox");
            string command = firefox_path;
            if (position != std::string::npos) {
                command+="https://stefanobelloni.github.io/EcoliSimulator/";
            }
            system(command.c_str());
        }
        
        cout << RED << "Do you want to change the command? \npress 0 for yes, 1 for no " << RESET;
        getInput(input);
        
    }
    
    
    
}