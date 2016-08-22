//
//  Funz_C_Par.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 24/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <cmath>
#include <fstream>
#include <array>

#include "GlobalVariables.h"
#include "sssr.h"
#include "Colori.h"
#include "Funz_C_Par.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462

using namespace std;

long double Funz_C_Par::new_F_C(long double t, std::array<long double,2> x)
{
    
    long double c=1;
    long double R = sqrt(pow(x[0], 2) + pow(x[1], 2));
    
    if (x[0]>max_x || x[0]<min_x || x[1]>max_y || x[1]<min_y) {
        return 0;
    }
    
    switch (num_funz) 
    {
        case 0:
            
            c = C_1*exp(-pow(R,2)/C_0)*(R<=C_2);                
            
            
            break;
            
        case 1:
            c = C_0+C_1*(t>C_2);
            
            break;
            
            
        case 2:
            
            c = 1+(R<C_0)*1.2*fabs((1+(t)/C_1)*sin(2*pi*(C_0+2*(t)/C_1)/2)/(R+(t)/C_0))+C_2*(R>=C_0)*(R<C_3)*fabs(cos(atan(sin(R)+t/C_1)))+(R>=C_3)*.1*fabs((1+(t)/C_0)*cos(sqrt(fabs(x[1])))*atan((pow(x[0], 2)))*sin(R+1.1*pi*((t)/C_1)));              
            
            break;
            
        case 3:
            
            c = 1+C_1*(t<=C_0)+C_2*(t>C_0)*(t<=C_0+1)*pow(t-C_0,2)+C_2*(t>C_0+1);
            
            break;
            
        case 4:
            
            c = 1+C_1*(t<C_0)+(t>=C_1)*(t<C_2)+C_3*(t>C_2);
            
            break;
            
        case 5:
            
            c = C_0*(1+max(C_1,x[0])/C_1);
            
            break;
            
        case 6:
            
            c = C_0*exp(x[0]/C_1);
            
            break;
            
        case 7:
            
            c = C_0*exp(C_2*t);
            
            break;
            
        default:
            
            c = C_0;
            
            break;
    }
 
    return c;
    
}

void Funz_C_Par::set_parameter(){
    
    interact=1;
    change_par=1;
    
    cout << BOLDRED << "*************************************\n"
    << " ADVANCED LIGAND CONCENTRATION MENU\n"
    << "*************************************\n" << RESET;
    
    switch (num_funz)
    {
        case 0:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= C_01*exp(-x^2/C_00)*(R<=C_02)\n";
            
            cout << "C_00: ";
            sssr(C_0,"C_00: ");;
            cout << "C_01: ";
            sssr(C_1,"C_01: ");;
            cout << "C_02: ";
            sssr(C_2,"C_02: ");;
            
            break;
            
        case 1:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= C_01+C_11*(t>C_21)\n";                
            
            cout << "C_01: ";
            sssr(C_0,"C_01: ");;
            cout << "C_11: ";
            sssr(C_1,"C_11: ");;
            cout << "C_21: ";
            sssr(C_2,"C_21: ");;
            
            break;
            
            
        case 2:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= 1+(R<C_02)*1.2*fabs((1+(t)/C_12)*sin(2*pi*(C_02+2*(t)/C_12)/2)/(R+(t)/C_02))...\n";
            cout << "+C_22*(R>=C_02)*(R<C_32)*fabs(cos(atan(sin(R)+t/C_12)))+...";
            cout << "+(R>=C_32)*.1*fabs((1+(t)/C_02)*cos(sqrt(fabs(x[1])))*atan((pow(x[0], 2)))*sin(R+1.1*pi*((t)/C_12))); ";                
            cout << "\nwhere R=||x||\n";
            
            cout << "C_02: ";
            sssr(C_0,"C_02: ");;
            
            cout << "C_12: ";
            sssr(C_1,"C_12: ");;
            
            cout << "C_22: ";
            sssr(C_2,"C_22: ");;
            
            cout << "C_32: ";
            sssr(C_3,"C_32: ");;
            
            break;
            
        case 3:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= 1+C_13*(t<=C_03)+C_23*(t>C_03)*(t<=C_03+1)*pow(t-C_03,2)+C_23*(t>C_03+1)";
            
            cout << "C_03: ";
            sssr(C_0,"C_03: ");;
            
            cout << "C_13: ";
            sssr(C_1,"C_13: ");;
            
            cout << "C_23: ";
            sssr(C_2,"C_23: ");;
            
            break;
            
        case 4:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= 1+C_14*(t<C_04)+(t>=C_14)*(t<C_24)+C_34*(t>C_24)";
            
            cout << "C_04: ";
            sssr(C_0,"C_04: ");;
            
            cout << "C_14: ";
            sssr(C_1,"C_14: ");;
            
            cout << "C_24: ";
            sssr(C_2,"C_24: ");;
            
            cout << "C_34: ";
            sssr(C_3,"C_034: ");;
            
            break;
            
        case 5:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= C_05*(1+max(C_15,x[0])/C_15)";                
            
            cout << "C_05: ";
            sssr(C_0,"C_05: ");;
            
            cout << "C_15: ";
            sssr(C_1,"C_15: ");;
            
            break;
            
        case 6:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= C_06*exp(x[0]/C_16)\n";                
            
            cout << "C_06: ";
            sssr(C_0,"C_06: ");;
            
            cout << "C_16: ";
            sssr(C_1,"C_16: ");;
            
            break;
            
        case 7:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):= C_07*exp(C_27*t)";                
            
            cout << "C_07: ";
            sssr(C_0,"C_07: ");;
            cout << "C_17: ";
            sssr(C_1,"C_17: ");;
            
            
            break;
            
        default:
            cout << "//***********************************************************\n//\n";
            cout << "\n\n c(t,x):=C_08\n";                
            
            cout << "C_08: ";
            sssr(C_0,"C_08: ");;
            
            
            break;
    }
    
}

Funz_C_Par::Funz_C_Par(){
    
//    cout << "Creato!! "<< endl;
    
}


Funz_C_Par::Funz_C_Par(const Funz_C_Par& f):Funz_C(f){
    
    C_0=f.C_0;
    C_1=f.C_1;
    C_2=f.C_2;
    C_3=f.C_3;
    
}

void Funz_C_Par::info_stat(std::ofstream &file_stat){
    
    Funz_C::info_stat(file_stat);
    
    file_stat << C_0 << endl  
              << C_1 << endl
              << C_2 << endl
              << C_3 << endl;
}

void Funz_C_Par::read_info_stat(int fchange_par, std::ifstream &file_stat, std::streampos &position){
    
    file_stat.clear();
    file_stat.seekg(position);
    
    Funz_C::read_info_stat(fchange_par, file_stat, position);
    
    file_stat   >> C_0
                >> C_1
                >> C_2
                >> C_3;
    
}

//void Funz_C_Par::print_info(ofstream &file_save){
//    
//    Funz_C::print_info(file_save);
//    
//    if (change_par==1) {
//        file_save << "Where the parameters are :"<<endl;
//        file_save << "C_0 = " << C_0 << endl;
//        file_save << "C_1 = " << C_1 << endl;
//        file_save << "C_2 = " << C_2 << endl;
//        file_save << "C_3 = " << C_3 << endl;
//    }
//    
//    
//}

