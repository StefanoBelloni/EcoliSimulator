//
//  Name_jumps.cpp
//  E_Coli2.2
//
//  Created by Stefano Belloni on 29/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>

using namespace std;



//void Name_jumps(std::string name_file_read, std::string names[],std::string names_hist[], int delete_){

/**
 * This function set the names for the file with data on run/tumble. It takes a basic name and up the suffix with the indication of the type (up/down etc. gradient)
 * @paramas if delete ==0 we delete the files with these names
 */

void Name_jumps(std::string name_file_read, std::string names[], int delete_){
    // delete_ == 0 delete the files
    
    name_file_read.erase(name_file_read.end()-4, name_file_read.end());
       
    names[0]=name_file_read+"_up.dat";
    names[1]=name_file_read+"_down.dat";
    names[2]=name_file_read+"_const.dat";
    names[3]=name_file_read+"_mix.dat";
    names[4]=name_file_read+"_all.dat";

//    names_hist[0]=name_file_read+"_hist_up.dat";
//    names_hist[1]=name_file_read+"_hist_down.dat";
//    names_hist[2]=name_file_read+"_hist_const.dat";
//    names_hist[3]=name_file_read+"_hist_mix.dat";
//    names_hist[4]=name_file_read+"_hist_all.dat";
    
    if (delete_==0) {
        const char *c; 
        
        for (int i=0; i<5; i++) {
//            cout << names[i] << endl;
            c = names[i].c_str();            
            remove(c);
//            c = names_hist[i].c_str();
//            remove(c);
        } 

    }
    
    
    
}
