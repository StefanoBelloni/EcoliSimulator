//
//  Funz_C.cpp
//  E_Coli2.1
//
//  Created by Stefano Belloni on 24/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include <limits>
#include <ctime>
#include <array>

#include <cmath>
#include "Funz_C.h"
#include "Colori.h"


#include "GlobalVariables.h"
#include "sssr.h"

#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462

using namespace std;

// Inizializzazione static variables

void funz_clear();


Funz_C::Funz_C()
{
    num_funz=9;
    max_x=20;
    min_x=-20;
    max_y=20;
    min_y=-20;
    D_c=0.01;
}


Funz_C::Funz_C(const Funz_C& f)
{
    num_funz=f.num_funz;
    max_x=f.max_x;
    min_x=f.min_x;
    max_y=f.max_y;
    min_y=f.min_y;
    D_c=f.D_c;
    change_par=f.change_par;
    degradation_rate=f.degradation_rate;
    n_x=f.n_x;
    n_y=f.n_y;
    dx=f.dx;
    dy=f.dy;
    interact = f.interact;
}

void Funz_C::get_coordinate1(array<double,2> x, int *n){
    
    n[0]=min(n_x-2,max(1,floor((x[0]-min_x)/dx))); // Non voglio andare sul bordo
    n[1]=min(n_y-2,max(1,floor((x[1]-min_y)/dy)));
    n[2]=min(n_x-2,n[0]+1); // Non voglio andare sul bordo
    n[3]=min(n_y-2,n[1]+1);
}

void Funz_C::get_coordinate(array<double,2> x, int *n)
{
    n[0]=min(n_x-2,max(1,floor((x[0]-min_x)/dx))); // Non voglio andare sul bordo
    n[1]=min(n_y-2,max(1,floor((x[1]-min_y)/dy)));
}
                                

double Funz_C::new_F_C(double t, std::array<double,2> x){
    
    double R = sqrt(pow(x[0], 2) + pow(x[1], 2));
    double T=50;
    
    if (x[0]>max_x || x[0]<min_x || x[1]>max_y || x[1]<min_y) {
        return 0;
    }
    
    switch (num_funz) 
    {
        case 0:
            
            
            return 18.2*exp(-pow(R,2)/7)*(R<=100);
            
            
            break;
            
        case 1:
            return 1+2*(t>15);
            
            break;
            
            
        case 2:
            
            T=150;
            
            R=1+(R<8)*1.2*fabs((1+(t)/T)*sin(2*pi*(R+2*(t)/T)/2)/(R+(t)/T))+.8*(R>=8)*(R<16)*fabs(cos(atan(sin(R)+t/T)))+(R>=16)*.1*fabs((1+(t)/T)*cos(sqrt(fabs(x[1])))*atan((pow(x[0], 2)))*sin(R+1.1*pi*((t)/T)));
            if (std::isnan(R)) {
                return 0;
            }
            
            
            return  R;      
            
            break;
            
        case 3:
            
            return 1+2*(t<=6)+2*(t>6)*(t<=6+3)*pow(t-5,2)+32*(t>6+3);
            
            break;
            
        case 4:
            
            return 1+7*(t<8)+(t>=15)*(t<25)+3*(t>25);
            
            break;
            
        case 5:
            
            return 3*(1+max(R,x[0])/2);
            
            break;
            
        case 6:
            
            //cout << "18.2*exp(10*x[0])=" <<18.2*exp(10*x[0]) << endl;
            
            return 18.2*exp(1*x[0]);
            
            break;
            
        case 7:
            
            return 18.2*exp(0.2*t);
            
            break;
            
        default:
            
            return 3;
            
            break;
    }
    
    return 1;
    
}

void Funz_C::set_parameter(){
    
    interact=1;
    
    funz_clear();

    
    cout << BOLDRED << "*************************************\n"
                    << " LIGAND CONCENTRATION MENU\n"
                    << "*************************************\n" << RESET;

        cout << "How big is the area of the experiment?\n" << endl;
        cout << BOLDRED<< "NOTE:\n" << BLUE << "The default value for the speed of a bacteria is 0,016 mm/s" << endl;
        cout << "The unit of measurement for the space is the same as\n";
        cout << "to the one for the speed of a bacterium (default mm).\n" << endl;
        cout << "speed_Diff = epsilon*speed and time_Diff=t/epsilon^2\n";
        cout << "with epsilon = " << epsilon << RESET<< endl;
        cout << "\nx_max ";
        sssr(max_x,"x_max ");
        cout << "y_max ";
        sssr(max_y,"y_max ");
        cout << "x_min ";
        sssr(min_x,"x_min ");
        cout << "y_min ";
        sssr(min_y,"y_min ");
        

    while (max_x<=min_x) {
        cout << BOLDRED << "\nINVALID PARAMETERS FOR THE X AXIS OF THE DOMAIN:\n";
        cout << "Insert again:\n";

        cout << "\nx_max ";
        sssr(max_x,"x_max ");
        cout << "x_min ";
        sssr(min_x,"x_min ");

    }
    
    while (max_y<=min_y) {
        cout << BOLDRED << "\nINVALID PARAMETERS FOR THE X AXIS OF THE DOMAIN:\n";
        cout << "Insert again:\n";

        cout << "y_max ";
        sssr(max_y,"y_max ");
        cout << "y_min ";
        sssr(min_y,"y_min ");
    }
    
        
        cout << "\n\nWhich form of the function c(t,x) you want to use (type the number )" << endl;
        cout << "The default parameters are given: "<< endl;
        cout << "0- Type Function: Gaussian" << endl;
        cout << " c(t,x):= C_10*exp(-x^2/C_00)*(R<=C_20)"<<endl
             << "        = 6*exp(-x^2/10)*(R<=100)" << endl;
        cout << "1- Type Function: smoothed Jump" << endl;
        cout << " c(t,x):= C_01+C_11*(t>C_21)"<<endl
             << "        = 1+2*(t>15)" << endl;
        cout << "2- Type Function: Dancing Sombrero" << endl;
        cout << " c(t,x):= 1+(R<8)*1.2*fabs((1+t/T)*sin(2*pi*(R+2*(t)/T)/2)/(R+(t)/T))"<<endl
             << "         +.8*(R>=8)*(R<16)*fabs(cos(atan(sin(R)+t/T)))"<<endl
             << "         +(R>=16)*.1*fabs((1+(t)/T)*cos(sqrt(fabs(x[1])))"<<endl
             << "         *atan((pow(x[0], 2)))*sin(R+1.1*pi*((t)/T)))"<<endl;
        cout << "3- Type Function: Jump up/down" << endl;
        cout << " c(t,x):= 1+C_13*(t<=C_03)+C_23*(t>C_03)*(t<=C_03+1)*pow(t-C_03,2)+C_23*(t>C_03+1) \n       = 1+2*(t<=6)+2*(t>6)*(t<=6+3)*pow(t-5,2)+32*(t>6+3);" << endl;
        cout << "4- Type Function:" << endl;
        //--->   Cambiare la funzione !!  
        cout << " c(t,x):= 1+C_14*(t<C_04)+(t>=C_14)*(t<C_24)+C_34*(t>C_24)" << endl;    
        cout << "5- Type Function: Half-plane-Linear " << endl;
        cout << " c(t,x):= C_05*(1+max(C_15,x[0])/C_15) = 3*(1+max(R,x[0])/2)" << endl;
        cout << "6- Type Function: Half-plane-Exponential " << endl;
        cout << " c(t,x):= C_06*exp(x[0]/C_16) = 18.2*exp(x[0]/10)" << endl;
        cout << "7- Type Function: time-Exponential " << endl;
        cout << " c(t,x):= C_07*exp(C_27*t) = 18.2*exp(0.2*t)" << endl;
        cout << "Otherwise Type Function:" << endl;
        cout << " c(t,x):= Const = 3" << endl;
        sssr(num_funz,"Which form of the function c(t,x) you want to use");

    
}

void Funz_C::all_informations(std::ofstream &file_save){
  
    cout << "stampo informazioni " << endl;
    
}

void Funz_C::print_fc(std::ofstream &file_save, double t){
    
    array<double,2> x;
    
    int n=max(1,floor(.1/dx));
    
    for (int i=0; i<n_x; i=i+n) {
        for (int j=0; j<n_y; j=j+n){
            x[0]=i*dx;
            x[1]=j*dy;
            file_save << x[0] << " " << x[1] << " " << new_F_C(t, x) << endl;
            
        }
        
        file_save << endl;
    }
    
}

void Funz_C::reset_parameter(){
    
    num_funz=9;
    
    max_x=20;
    min_x=-20;
    max_y=20;
    min_y=-20;
    
    D_c=0.01; 
    degradation_rate=0.05;
    
}

void Funz_C::info_stat(std::ofstream &file_stat){
    
    file_stat << change_par << endl
              << interact << endl
              << num_funz << endl
              << max_x << endl
              << max_y << endl
              << min_x << endl
              << min_y << endl;
    
}

void Funz_C::read_info_stat(int fchange_par,std::ifstream &file_stat, std::streampos &posizion){
    
    change_par = fchange_par;
    file_stat   >> interact
                >> num_funz 
                >> max_x
                >> max_y
                >> min_x
                >> min_y; 
    
    posizion = file_stat.tellg();
    
}
//+++++++++++++++++++++++++++++++++

