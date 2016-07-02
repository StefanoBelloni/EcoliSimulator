//
//  last_deleting.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 27/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>

void last_deleting(){
    
#if defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(_WIN64) || defined(WIN64)
    
    std::string command_line_txt_rem = "del *.txt ";
    
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.eps ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.m ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.dat ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.gnu ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.avi ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.tex ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del *.png ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del -Rf *.fit ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "del -Rf *.gif ";
    system(command_line_txt_rem.c_str());
    
#else
    std::string command_line_txt_rem = "rm -Rf *.txt ";
    
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.eps ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.m ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.dat ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.gnu ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.avi ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.tex ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.png ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.fit ";
    system(command_line_txt_rem.c_str());
    command_line_txt_rem = "rm -Rf *.gif ";
    system(command_line_txt_rem.c_str());
    
#endif
    
    
}