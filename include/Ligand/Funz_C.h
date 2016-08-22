//
//  Funz_C.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 19/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_0_Funz_C_h
#define E_Coli2_0_Funz_C_h

#include <vector>
#include <array>

/** \brief Base class for the function describing the ligand concentration.
 
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
         $$ = 1+2*(t<=6)+7*(t>6)*(t<=6+1)*pow(t-6,2)+7*(t>6+1)$$
 
 - case 4:
 
    4- Type Function:
    --------> Maybe we should change this function Cambiare la funzione !!
	$$c(t,x):= 1+C_14*(t<C_04)+(t>=C_14)*(t<C_24)+C_34*(t>C_24)$$

 
 - case 5:
 
    5- Type Function: Half-plane-Linear
    $$c(t,x):= C_05*(1+max(C_15,x[0])/C_15) = 3*(1+max(R,x[0])/2)$$
 
 break;
 
 - case 6:
    6- Type Function: Half-plane-Exponential
    $$c(t,x):= C_06*exp(x[0]/C_16) = 18.2*exp(10*x[0])$$
 
 - case 7:
 
	7- Type Function: time-Exponential
    $$c(t,x):= C_07*exp(C_27*t) = 18.2*exp(0.2*t)$$
 
 - default:
 
    Otherwise Type Function:
    $$c(t,x):= Const = 3$$
 

 The are of the experiment is <br>
    \f$(x_{min},x_{max})\f$ <br>
    \f$(y_{min},y_{max})\f$
 
 */

class Funz_C{
  
    public:
    
    Funz_C();
    Funz_C(const Funz_C& f);
    
//    static int num_funz;   // Usi sempre una sola funzione C per volta ha senso avere static variables
//    static int change_par;
//
//    static long double D_c;
//
//    static long double max_x,min_x,max_y,min_y;
//
//    static long double degradation_rate;
//
//    static int n_x;
//    static int n_y;
//    static long double dx;
//    static long double dy;
//    static int interact;   // == 0 se program interacting particles
    
    
    /** type of function c in the avaliable list*/
    static int num_funz;   // Usi sempre una sola funzione C per volta ha senso avere static variables
    /** variable which track if the parameters has been changed: one might change int into boolean, 1 = change*/
    int change_par;
    /** Diffusion coefficient: used in the interacting model*/
    long double D_c;
    /** size of the area of the experiment*/
    long double max_x,min_x,max_y,min_y;
    /** degradation rate of ligand see model in the  population interacting with the ligand case*/
    long double degradation_rate;
    /** number od point in the mesh in the x direction (for interacting case)*/
    int n_x;
    /** number od point in the mesh in the y direction (for interacting case)*/
	int n_y;
    /** size-step mesh x direction*/
    long double dx;
    /** size-step mesh y direction*/
    long double dy;
    /** == 0 se program interacting particles */
    int interact;   // == 0 se program interacting particles
    
    /** pointer to a matrix(n_x,n_y) with the value of the function: it is used to solve the PDE in the interacting case*/
    long double **f_c;  // pointer to a matrix(n_x,n_y) with the value of the function
    /** pointer to a matrix(n_x,n_y) with the value of the sorce: it is used to solve the PDE in the interacting case */
    long double **q_c;  // pointer to a matrix(n_x,n_y) with the value of the sorce
    
    /** return the value of Ligand concentration in the point x */
    virtual long double new_F_C(long double t, std::array<long double,2> x);
    /** reset parameters to the default*/
    void reset_parameter();
    /** set parameters of the ligand concentration 
       in the Funz_C, you can choose the type of function and the dimantion of the rectangular area of the experiment
      - in the function set_funz_c(vector<Funz_C*> &f, int interacting) you actually change the parameters of the function.
     */
    virtual void set_parameter();
    /** set in which the rectangle (dx_n,dy_n) of the mesh of the domain the point x fells
     * @param n is the array where the "coordinate" of the rectangle are saved
     */
    virtual void get_coordinate(std::array<long double,2> x, int *n);
    virtual void get_coordinate1(std::array<long double,2> x, int *n);
    /** save information for the report
     */
    virtual void all_informations(std::ofstream &file_save);
    /** save info for the statistical analysis*/
    virtual void info_stat(std::ofstream &file_stat);
    /** read parameters from file */
    virtual void read_info_stat(int fchange_par, std::ifstream &file_stat, std::streampos &posizion);
    /** save the mesh and relative value of Ligand in a file to draw with gnuplot*/
    virtual void print_fc(std::ofstream &file_save, long double t);
    /** similar to all_information */
    virtual void print_info(std::ofstream &file_save);
    /** previw of the dynamics of the ligand concentration (non-interacting case)*/
    virtual void preview_F_C();
    /** draw function c */
    void gnuplotFunC(long double max_fc, long double dt, int n_frames);
    /** create hystogram for the preview*/
    friend long double Histogram_3D_FunzC(Funz_C *f, long double dt, int n_frame_max);
};


#endif
