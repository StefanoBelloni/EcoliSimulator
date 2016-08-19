//
//  Write_LateX_file.cpp
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 26/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <sstream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/**
 * This function actually write the text and insert the figure in the LateX report.
 */

void Write_LateX_file(std::string name_file, std::ofstream &file_teX){
    
    string extension;
    ifstream temporary_file;
    string linea_file;
    
    extension = name_file;
    // check the extention and treat it as a text or a figure.
    extension.erase(extension.begin(), extension.end()-3);
    
//    cout << "extention ... " << extension << endl;
    
//    cout << "if ending == eps 'include graphics teX'" << endl;
    
    // .EPS
    if (extension=="eps") {
        file_teX << "****" << endl;
        file_teX << "\\begin{figure}[h!] " << endl
                 << "\\centering" << endl
                 << "\\includegraphics[width=.95\\linewidth]{"<<name_file<<"}" << endl
                 << "\\end{figure}" << endl;
    }
    
    
//    cout << "if ending == txt 'include text teX'" << endl;    

    
    // .TXT
    if (extension=="txt") {
        file_teX << "\\newpage" << endl;
//        file_teX << "\\begin{verbatim}" << endl;
        
        temporary_file.open(name_file.c_str());
        while (!temporary_file.eof()) {
            getline(temporary_file, linea_file);
            file_teX << linea_file << endl;
        }
        
//        file_teX << "\\end{verbatim}" << endl;
    }
    
    
    // .FIT
    if (extension=="fit") {
        file_teX << "\\begin{verbatim}" << endl;
        file_teX << name_file << endl;
        
        temporary_file.open(name_file.c_str());
        while (!temporary_file.eof()) {
            getline(temporary_file, linea_file);
            file_teX << linea_file << endl;
        }
        
        
        file_teX << "\\end{verbatim}" << endl;
    }
}
