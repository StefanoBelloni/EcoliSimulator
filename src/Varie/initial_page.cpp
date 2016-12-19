//
//  initial_page.cpp
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 06/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "Colori.h"
#include "ErrorsDefinition.h"
#include "GlobalRandomVariables.h"
#include "apngasm_Global.h"
#include "GnuplotGlobal.h"
#include "Dir_Global.h"
#include "MATLAB_Global.h"
#include <unistd.h>

using namespace std;

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)

#include <windows.h>	//This is for the console code
// Below is the code to set the size of the console window

void SetWindow(int Width = 60, int Height = 98)
{
    _COORD coord;
    coord.X = Width;
    coord.Y = Height;
    
    _SMALL_RECT Rect;
    Rect.Top = 0;
    Rect.Left = 0;
    Rect.Bottom = Height - 1;
    Rect.Right = Width - 1;
    
    HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle
    SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size
    SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size
    
    
}

void FullWindows(){
    HWND hWnd = GetConsoleWindow();
    ShowWindow(hWnd,SW_SHOWMAXIMIZED);
}

#else
void SetWindow(int Width = 60, int Height = 98){
    
    string command =string("printf '\\e[8;");
    command+=to_string(Width)+string(";");
    command+=to_string(Height)+string("t'");
    
    system(command.c_str()); // metà
}

void FullWindows(){
    SetWindow();
//	SetWindow(100000000,1000000000);
    
}

#endif

void funz_clear();
void funz_clearAll();

/**
 * This function drow the initial page for the command line program.
 * note: for windows it is without colors.
 */


void initial_page(){
    
    funz_clearAll();
    
//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
////    system("mode 650");
//    system("mode 100,100");
//#else
//    system("printf '\e[8;60;98t'"); // metà
//    
//#endif

//    SetWindow();
    FullWindows();
    
    cout << BOLDBLUE<<"******************************************************************************"<<endl;
    cout <<"                                                             .:"<<endl;
    cout <<"                                                            / )"<<endl;
    cout <<"                                                           ( ("<<endl;
    cout <<"      E.COLI - SIMULATOR                                    \\ )"<<endl;
    cout <<"            o                                             ._(/_."<<endl;
    cout <<"             o                                            |___%|"<<endl;
    cout <<"           ___              ___  ___  ___  ___             | %|"<<endl;
    cout <<"           | |        ._____|_|__|_|__|_|__|_|_____.       | %|"<<endl;
    cout <<"           | |        |__________________________|%|       | %|"<<endl;
    cout <<"           |o|          | | |%|  | |  | |  |~| | |        .|_%|."<<endl;
    cout <<"          .' '.         | | |%|  | |  |~|  |#| | |        | ()%|"<<endl;
    cout <<"         /  o  \\        | | :%:  :~:  : :  :#: | |     .__|___%|__."<<endl;
    cout <<"        :____o__:     ._|_|_."    "    "    "._|_|_.   |      ___%|_"<<endl;
    cout <<"        '._____.'     |___|%|                |___|%|   |_____(____  )"<<endl;
    cout <<"                                                          ( ("<<endl;
    cout <<"                                                           \\ '._____.-"<<endl;
    cout <<"                                                 grp        '._______.-"<<endl;
    
    //    cout << BOLDRED<<"\n\n\n\n**********************************************************************************************"<<endl;
    //    cout << BOLDRED<<"**********************************************************************************************\n"<< BOLDBLUE<<endl;
    //    cout <<"        //////       /////    ///////    //       //         ///////   //    //        //  "<<endl;
    //    cout <<"       //           //       //   //    //                  //              ////    ////   "<<endl;
    //    cout <<"      ////         //       //   //    //       //  ////   ///////    //   // //  // //    "<<endl;
    //    cout <<"     //           //       //   //    //       //              //    //   //   //   //     "<<endl;
    //    cout <<"    //////// //  //////   ///////    ///////  //        ////////    //   //        //  //    \n"<<endl;
    //    cout << BOLDRED<<"**********************************************************************************************"<<endl;
    //    cout <<"*********************************************************************************************\n\n\n "<<RESET<< endl;
    
    
    cout << BOLDRED<<"\n******************************************************************************"<<endl;
    cout << BOLDRED<<"*******************************************************************************\n"<< BOLDBLUE<<endl;
    cout <<"                _______     _______  _______  _       _________ "<<endl;
    cout <<"               (  ____ \\   (  ____ \\(  ___  )( \\      \\__   __/"<<endl;
    cout <<"               | (    \\/   | (    \\/| (   ) || (         ) (   "<<endl;
    cout <<"               | (__       | |      | |   | || |         | |   "<<endl;
    cout <<"               |  __)      | |      | |   | || |         | |   "<<endl;
    cout <<"               | (         | |      | |   | || |         | |   "<<endl;
    cout <<"               | (____/\\ _ | (____/\\| (___) || (____/\\___) (___"<<endl;
    cout <<"               (_______/(_)(_______/(_______)(_______/\\_______/  "<<endl;
    
    #if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    	cout << "\n";
	#else 
    
    cout <<" _______ _________ _______           _        _______ _________ _______  _______ "<<endl;
    cout <<"(  ____ \\\\__   __/(       )|\\     /|( \\      (  ___  )\\__   __/(  ___  )(  ____ )"<<endl;
    cout <<"| (    \\/   ) (   | () () || )   ( || (      | (   ) |   ) (   | (   ) || (    )|"<<endl;
    cout <<"| (_____    | |   | || || || |   | || |      | (___) |   | |   | |   | || (____)|"<<endl;
    cout <<"(_____  )   | |   | |(_)| || |   | || |      |  ___  |   | |   | |   | ||     __)"<<endl;
    cout <<"      ) |   | |   | |   | || |   | || |      | (   ) |   | |   | |   | || (\\ (   "<<endl;
    cout <<"/\\____) |___) (___| )   ( || (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__"<<endl;
    cout <<"\\_______)\\_______/|/     \\|(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/\n"<<endl;
    
    #endif
	
	cout << BOLDRED <<"*******************************************************************************"<<endl;
    cout            <<"*******************************************************************************"<<RESET<< endl;
    
    
    
    
    cout << BOLDBLUE <<"                               | 1"<<endl;
    cout <<"                            ,--|--."<<endl;
    cout <<"                         ,-'   |   `-.           "<<endl;
    cout <<"                       ,'      |      `. " <<endl;
    cout <<"                     ,'        |        `. " <<endl;
    cout <<"                    /          |          \\  " <<endl;
    cout <<"                   /           |       E.COLI-SIMULATOR                /"<<endl;
    cout <<"              ----+------------+------------\\------------+------------/---"<<endl;
    cout <<"                 __            |0         __ \\          __           /  __"<<endl;
    cout <<"                 ||            |          ||  \\         ||          /  3||  "<<endl;
    cout <<"               - ---           |          ---  `.                 ,'   --- "<<endl;
    cout <<"                  2            |           2     `.             ,'      2"<<endl;
    cout <<"                               |                   `-.       ,-'"<<endl;
    cout <<"                               | -1                   `--,--'"<<endl
         <<"                                    " << BLACK <<"A program by S.Belloni."<<RESET<<endl;
    cout << BOLDBLUE<<"***********************************************"<< VERSION <<endl;

    
    cout << "press Enter to continue ... " << RESET << endl;
    cin.ignore();
    funz_clear();    
    
    
}

/*! This function set the global variables to their default values ...*/

void setDefoultGlobalVar(){
    
    // TODO: remove tmpDir ... 
    //******************************************************************************************
    //                                      GLOBAL GNUPLOT
    //******************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    //string gnuplotOpen = "C:\\gnuplot\\binary\\wgnuplot.exe ";
//    string gnuplotOpen = "C:\\\"Program Files (x86)\"\\gnuplot\\bin\\gnuplot ";
    gnuplotOpen = getcwd(NULL,0)+string("\\gnuplot\\bin\\gnuplot.exe ");
    system("del tmpEcoli/*");
#elif defined(__linux__) || defined(__linux) || defined(linux) 
    gnuplotOpen = "gnuplot ";
    system("rm tmpEcoli/*");
#else
    gnuplotOpen = "/opt/local/bin/gnuplot ";
    system("rm tmpEcoli/*");
    //string gnuplotOpen = "gnuplot ";
    //string gnuplotOpen = "/usr/bin/gnuplot ";
#endif
    
//#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
//    gnuplotSetTerminalPlot= "set terminal windows size 1250,750";
//#elif __CYGWIN__
//    gnuplotSetTerminalPlot = "set terminal windows size 1250,750";
//#else
//    //string gnuplotSetTerminalPlot = "set terminal x11 size 1400,900";// size 600, 400\nset size 1, 1";
//#endif
    
    gnuplotSetTerminalPlot = "set terminal wxt size 1200,700 position 20,20"; // enhanced font 'Verdana,10' persist";
    
    //string gnuplotSetTerminalSave_eps = "set terminal postscript eps color blacktext \"Helvetica\" 20";
    //string gnuplotSetTerminalSave_eps = "set terminal postscript default";
    //string gnuplotSetTerminalSave_eps = "set term postscript enhanced color";
    gnuplotSetTerminalSave_eps = "set terminal postscript eps enhanced colour size 10in,8in font 'Helvetica,20'";
    //string gnuplotSetTerminalSave_eps = "set terminal epslatex colour size 10in,8in font 'Helvetica,20'";
    
    //string gnuplotSetTerminalSave_eps = "set terminal postscript eps size 3.5,2.62 enhanced color font 'Helvetica,20' linewidth 2";
    //string gnuplotSetTerminalSave_png = "set terminal pngcairo size 900,500"; // enhanced font 'Verdana,10' ";
    gnuplotSetTerminalSave_png = "set terminal pngcairo size 1380,840";// size 350,262 enhanced font 'Verdana,20'";
    
    gnuplotSetTerminalSave_gif = "set term gif animate size 1380,840";
    //******************************************************************************************
    //                                      MATLAB GLOBAL
    //******************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    MATLAB_loc  = "/Applications/MATLAB_R";
    MATLAB_call = ".app/bin/matlab -nodesktop -r ";
    //string MATLAB_program = "Movie_Matlab_from_cpp";
#else
    MATLAB_loc  = "/Applications/MATLAB_R";
    MATLAB_call = ".app/bin/matlab -nodesktop -r ";
    //Movie_Matlab_from_cpp";
#endif
    //******************************************************************************************
    //                                      APNGAS GLOBAL
    //******************************************************************************************
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    apngas_lunch= "apngasm.exe ";
#else
    apngas_lunch= "apngasm ";
#endif
    apngas_opt = " 1 10 -l1";
    no_apngams = true;
    //            string apngas_opt =" 1 10 -l1 ";
    
    //lunch+name_out+name_frame+opt;   WIN
    //lunch + name_frame " -o "+ name_out + opt.  MAC/LINUX(?)
    
    //******************************************************************************************
    //                                      GLOBAL DIRECTORY
    //******************************************************************************************

//    Location = homeDir;
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    //        Location=Location+"\\Desktop";
    Location = getcwd(NULL,0);
    firefox_path = "firefox "; // TODO: open firefox from cmd
#elif defined(__linux__) ||defined(__linux) || defined(linux) 
    firefox_path ="firefox ";
    Location = getcwd(NULL,0);
#else
    //        Location=Location+"/Desktop";
    Location = getcwd(NULL,0);
    firefox_path ="open -a firefox ";
#endif

  // set the Log file where the bin was lunched , so I can delete inside tmpEcoli without worry
   nameLog = Location + std::string("/") + nameLog;

   save_data = false;
    
}
