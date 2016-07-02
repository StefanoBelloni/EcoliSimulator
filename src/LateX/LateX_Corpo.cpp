//
//  LateX_Corpo.cpp
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 28/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include "Colori.h"

#include <cstdlib>

#include "dirent.h"

void Write_LateX_file(std::string name_file, std::ofstream &file_teX);

using namespace std;

/**
 * This function save in file_teX the different text part saved (in lateX form) or the pictures.
 * It add it to the preamble, with initial page pakages etc.
 */

int LateX_Corpo(ofstream &file_teX, const char final[]){
    
    DIR *dir;
    struct dirent *ent;
    int cont_files=0;
    // primo passo sistemare i 
    
    
    // Secondo Passo scrivere i dati!
    if ((dir = opendir (final)) != NULL) {
        /* print all the files and directories within directory */
        while ((ent = readdir (dir)) != NULL) {
            
//            printf ("%s\n", ent->d_name);
            if (cont_files>1){
                Write_LateX_file(ent->d_name, file_teX);
            }
            cont_files++;
        }
        closedir (dir);
    } else {
        /* could not open directory */
        perror ("");
        return EXIT_FAILURE;
    }
    
    return 0;
    
}
