//
//  lunch_gnuplot.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 26/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <cstdlib>  // to use system function
#include <fstream>
#include <iostream>
#include <string>

#include "apngasm_Global.h"
#include "GnuplotGlobal.h"
using namespace std ;

/**
 * This function lunch the script name_file_gnu via gnuplot
 * It is not used everytime since it has been written not at the beginning of the devopment of the softwer. You might want to substitute other command with this function
 * @param name_file_gnu name of script to pass to gnuplot
 */

void lunch_gnuplot(string name_file_gnu){
    string command = gnuplotOpen + name_file_gnu;
    cout << "Lunch gnuplot: " << command << endl;
    system(command.c_str());
//    cout << "command gnuplot : " << endl;
}

void lunch_apngas(string name_out, string name_input){

	string command_apngas_= apngas_lunch+std::string("-o ")+name_out+std::string(" ")+name_input+apngas_opt;
	system(command_apngas_.c_str());
}
