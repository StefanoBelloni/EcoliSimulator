// IL PROGRAMMA PRENDE IN INGRESSO FILES E DA IN USCITA UN FILE CHE PERMETTE A C++ DI RISCRIVERE INDIPENDENTEMENTE LO STESSO FILE.
// DA controllare nelle fprintf \n; sostiture con : \\n

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

#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>

using namespace std;

/**
 * This function accept a list of .m files, and produed a file that allows a c program to write the m-files
 * NOTE in the fprintf \\n; substitute with : \\\\n (one slash n with long double slash n)
 */

int from_m_files_to_cpp(int argc, char *argv[]){

    ofstream file("output.m");
    ofstream file2("output2.m");
    ifstream file_m;
    string lineafile="a";
    //    int t=0;

    int n_files=argc;

    for (int i=1; i<n_files; i++) {

    file << "ofstream file"<<i<<"(\"" << argv[i] << "\");" << endl;

    }
    file << "//**************************************************************************************" << endl;
    file << "//**************************************************************************************\n\n" << endl;

    for (int i=1; i<n_files; i++) {
        
    //        t=0;
        
        file_m.open(argv[i]);
        
        file << "//**************************************************************************************" << endl;
        file << "// " << argv[i] << endl;
        file << "//**************************************************************************************\n\n" << endl;    
        file << "{" << endl;

        file << "file" << i << " "; 
        
        cout << "Processo il file" << i<< endl;
        
        while (!file_m.eof()) {
    //            t++;
    //            cout << "Linea " << t << endl;
            
            getline(file_m,lineafile);
            file << "<< \"" << lineafile << " \" << endl " << endl; 
        }
        
        cout << "termine file"<< i << endl; 
        
        file << "<< \" \" << endl; " << endl;
        file << "}" << endl;
        file << "\n\n//**************************************************************************************\n\n" << endl;
        
        file_m.close();
        
    //        remove(argv[i]);        
        
    }

    for (int i=1; i<n_files; i++) {
        
        file2 << "remove(\"" << argv[i] << "\");" << endl;
        
    }


    file.close();
    file2.close();

    return 0;
}
//*******************************************************************************************
//                                          COMPILAZIONE
//*******************************************************************************************

/*
 g++ mintocpp.cpp -o mintocpp

./mintocpp Caricamento_filmato_hist.m Movie_Matlab_from_cpp.m functionC.m hist3.m Evolution_Mass_center.m Movie_Matlab_from_cpp_and_single.m functionC1.m traiettorie_singole.m Filmatohist.m Save_Movie_avi.m function_c.m MovieCpp2matlab.m distribuzione_tempi.m getkey.m
 
 */