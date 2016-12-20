//
//  Funz_C_Par.h
//  E_Coli2.1
//
//  Created by Stefano Belloni on 24/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_1_Funz_C_Par_h
#define E_Coli2_1_Funz_C_Par_h

#include "Funz_C.h"

/** \brief  Class for the Ligand that allows change of the parameters
 
 * It's like Funz_C, but allows to change the parameter of the function
 NOTE: If you add new functions, you should add the same in Funz_C::print_info
 
 - case 0:
 
 0- Type Function: Gaussian
 $$c(t,x):= C_10*exp(-x^2/C_00)*(R<=C_20) = 6*exp(-pow(R,2)/10)*(R<=100)$$"
 - case 1:
 
 1- Type Function: smoothed Jump
 $$c(t,x):= C_01+C_11*(t>C_21) = 1+2*(t>15)$$
 
 - case 2:
 
 2- Type Function: Dancing Sombrero
 $$c(t,x):= ... $$
 
 break;
 
 - case 3:
 
 3- Type Function: Jump up/down
 $$c(t,x):= 1+C_13*(t<=C_03)+C_23*(t>C_03)*(t<=C_03+1)*pow(t-C_03,2)+C_23*(t>C_03+1)$$
 
 - case 4:
 
 4- Type Function:
 --------> Maybe we should change this function Cambiare la funzione !!
	$$c(t,x):= 1+C_14*(t<C_04)+(t>=C_14)*(t<C_24)+C_34*(t>C_24)$$
 
 
 - case 5:
 
 5- Type Function: Half-plane-Linear
 $$c(t,x):= C_05*(1+max(C_15,x[0])/C_15) $$
 
 break;
 
 - case 6:
 6- Type Function: Half-plane-Exponential
 $$c(t,x):= C_06*exp(x[0]/C_16)$$
 
 - case 7:
 
	7- Type Function: time-Exponential
 $$c(t,x):= C_07*exp(C_27*t)$$
 
 - default:
 
 Otherwise Type Function:
 $$c(t,x):= C_01
 
 
 The are of the experiment is <br>
 \f$(x_{min},x_{max})\f$ <br>
 \f$(y_{min},y_{max})\f$
 
 
 */

class Funz_C_Par:public Funz_C{
    
public:
    
    Funz_C_Par();
    
    Funz_C_Par(const Funz_C_Par& f);
    
    /** parameters in the model: see general information*/
    long double C_0;
    /** parameters in the model: see general information*/
    long double C_1;
    /** parameters in the model: see general information*/
    long double C_2;
    /** parameters in the model: see general information*/    
    long double C_3;

#if NO_M_THREAD    
    long double new_F_C(long double t, long double* x);
#else
    long double new_F_C(long double t, std::array<long double,2> x);
#endif    

    /** set parameters of the ligand concentration
     It call the base function <br>
     if the user wants to change parameters, the 
     */
    void set_parameter();
    
    void print_info(std::ofstream &file_save);
    void info_stat(std::ofstream &file_stat);
    void read_info_stat(int fchange_par, std::ifstream &file_stat, std::streampos &posizion);
    
};

#endif
