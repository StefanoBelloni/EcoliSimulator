//
//  Stima_tempo.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 22/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//
// return 1 quando è stata usata ...

#include <iostream>
#include <cmath>
#include <cstring>
#include <ctime>

using namespace std;

/**This function extimate the time to finish the simulation*/

int Stima_tempo(int n_c, int n_val_termine, int &j_cel_finale, int &j_cel_inizio, time_t timer1)
{
    
    time_t timer2=time(&timer2);
    
    int hour,min,sec = floor((n_c-n_val_termine)*difftime(timer2,timer1)/n_val_termine);    
    char buf[256];
    
    timer2=time(&timer1)+sec;
    strcpy(buf,ctime(&timer2));
    buf[strlen(buf)-1]='\0';
    
    hour=sec/3600;
    sec=sec%3600;
    min=sec/60;
    sec=sec%60;
//    sec=sec;

    
    j_cel_inizio=j_cel_finale;
    j_cel_finale=n_c;

    // TODO se si ha 1h 00m ritorna subito
    if (min<1 && hour <1) {
        // If not noo long I don't dsiplay the expected time
        return 1;
    }
    
//    std::cout << "\n-----------------------------------------------------\n" << std::endl;
    
    
    std::cout<<"The simulation should finish in : \n          "<<hour<<" h "<<min<<" min "<<sec<<"sec,\nthat is (circa) " << buf << "\n";
    
    std::cout << "\n-----------------------------------------------------\n" << std::endl;
    std::cout << "\nTill now completed: \n" << std::endl;
    //std::cout << " ... ";
    
    
    return 1;
    
}

    // TODO se si ha 1h 00m ritorna subito
/**This function extimate the time to finish the simulation*/
int Stima_tempo(int n_c, int n_val_termine, time_t timer1)
{
    
    time_t timer2=time(&timer2);
    
    int hour,min,sec = floor((n_c-n_val_termine)*difftime(timer2,timer1)/n_val_termine);
    char buf[256];
    
    timer2=time(&timer1)+sec;
    strcpy(buf,ctime(&timer2));
    buf[strlen(buf)-1]='\0';
    
    hour=sec/3600;
    sec=sec%3600;
    min=sec/60;
    sec=sec%60;
    //sec=sec;
    
//    std::cout << "\n-------------------------------------------\n" << std::endl;
    
    if (min<1 && hour <1) {
        // If not noo long I don't dsiplay the expected time
        return 1;
    }
    
    std::cout<<"The Analysis should finish in : \n          "<<hour<<" h "<<min<<" min "<<sec<<"sec,\nthat is (circa) " << buf << "\n";
    
    std::cout << "\n-------------------------------------------\n" << std::endl;
    std::cout << "\nTill now completed: \n" << std::endl;    
    //std::cout << " ... ";

    return 1;
    
}
