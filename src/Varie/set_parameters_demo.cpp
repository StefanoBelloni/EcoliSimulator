//
//  set_default_par.cpp
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 26/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include "GlobalVariables.h"

#include "ErrorsDefinition.h"

using std::cout;
using std::endl;
using std::ofstream;

bool is_file_exist(const char* fileName);

/**
 * THis function set the parameters of the answer for the demo/validating routine ...
 */

void set_parameters_DEMO(){
 
/*
//    **************************************************
//    ************
//    * 1a ROUTINE
//    ************
//    
//    // kind program
//    vettore_risposte.push_back(1);
//    // indip
//    vettore_risposte.push_back(1);
//    // comparazione
//    vettore_risposte.push_back(0);
//    //
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(2);
//    //
//    vettore_risposte.push_back(3);
//    //
//    vettore_risposte.push_back(4);
//    //
//    vettore_risposte.push_back(5);
//    //
//    vettore_risposte.push_back(6);
//    //
//    vettore_risposte.push_back(7);
//    //
//    vettore_risposte.push_back(8);
//    //
//    vettore_risposte.push_back(9);
//    // Fine
//    vettore_risposte.push_back(0);
//    // vettore Preview
//    vettore_risposte.push_back(1);
//    // x_M
//    vettore_risposte.push_back(5);
//    // y_M
//    vettore_risposte.push_back(5);
//    // x_m
//    vettore_risposte.push_back(-5);
//    // y_m
//    vettore_risposte.push_back(-5);
//    // Sombrero
//    vettore_risposte.push_back(2);
//    // Par fc
//    vettore_risposte.push_back(1);
//    // Tf
//    vettore_risposte.push_back(100);
//    // dt
//    vettore_risposte.push_back(.01);
//    // x0
//    vettore_risposte.push_back(2);
//    // y0
//    vettore_risposte.push_back(2);
//    // n_c
//    vettore_risposte.push_back(1);
//    // Dt save
//    vettore_risposte.push_back(0.5);
//    //Par Ecoli 1
//    vettore_risposte.push_back(0);
//    //2
//    vettore_risposte.push_back(0);
//    //3
//    vettore_risposte.push_back(0);
//    //4
//    vettore_risposte.push_back(0);
//    //5
//    vettore_risposte.push_back(0);
//    //6
//    vettore_risposte.push_back(0);
//    //7
//    vettore_risposte.push_back(0);
//    //8
//    vettore_risposte.push_back(0);
//    //9
//    vettore_risposte.push_back(0);
//    // Film 1
//    vettore_risposte.push_back(1);
//    // Dt
//    vettore_risposte.push_back(5);
//    //2
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //3
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //4
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //5
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //6
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //7
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //8
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    //9
//    vettore_risposte.push_back(1);
//    //
//    vettore_risposte.push_back(5);
//    // un'altra?
//    vettore_risposte.push_back(1);
//    **************************************************
//    ***********
//    ** 2a ROUTINE
//    ***********
//    // Sim & Stat
//    vettore_risposte.push_back(3);
//    // non interact
//    vettore_risposte.push_back(1);
//    // tipo Model
//    vettore_risposte.push_back(1);
//    // FC_View
//    vettore_risposte.push_back(1);
//    //xM ...
//    vettore_risposte.push_back(5);
//    //yM
//    vettore_risposte.push_back(5);
//    //xm
//    vettore_risposte.push_back(-5);
//    //ym
//    vettore_risposte.push_back(-5);
//    // Fc
//    vettore_risposte.push_back(0);
//    // Par Change
//    vettore_risposte.push_back(1);
//    // Tf
//    vettore_risposte.push_back(10);
//    // dt
//    vettore_risposte.push_back(.01);
//    // x0
//    vettore_risposte.push_back(2);
//    //y0
//    vettore_risposte.push_back(2);
//    // n_c
//    vettore_risposte.push_back(1000);
//    // distr.
//    vettore_risposte.push_back(1);
//    // Dt save
//    vettore_risposte.push_back(1);
//    // Par Ecoli
//    vettore_risposte.push_back(0);
//    // See Film
//    vettore_risposte.push_back(1);
//    // T_j fotograms
//    vettore_risposte.push_back(0);
//    // j
//    vettore_risposte.push_back(4);
//    // Another One?
//    vettore_risposte.push_back(1);
//    ***********
//    ** STAT PART
//     Model to Fit
//    vettore_risposte.push_back(1);
//    // Do you want to set the parameter for the step of the Q-variable? 0 Ora è dentro le funzioni e non si vede ...
//    vettore_risposte.push_back(1);
//    //Film
//    vettore_risposte.push_back(1);
//    //Tj
//    vettore_risposte.push_back(0);
//    //j
//    vettore_risposte.push_back(4);
//    //Another One?
//    vettore_risposte.push_back(1);
//    ***********************************
//    ***********
//    ** 3a ROUTINE
//    ***********
//    // Sim
//    vettore_risposte.push_back(1);
//    // Interact
//    vettore_risposte.push_back(2);
//    // Model
//    vettore_risposte.push_back(1);
//    //xM
//    vettore_risposte.push_back(3);
//    //yM
//    vettore_risposte.push_back(3);
//    //xm
//    vettore_risposte.push_back(1);
//    //ym
//    vettore_risposte.push_back(1);
//    // Fc 9-const
//    vettore_risposte.push_back(0);
//    // Par Fc
//    vettore_risposte.push_back(1);
//    // dx
//    vettore_risposte.push_back(.01);
//    // degradation
//    vettore_risposte.push_back(.05);
//    // Diff Coef.
//    vettore_risposte.push_back(.001);
//    // Tf
//    vettore_risposte.push_back(50);
//    // dt
//    vettore_risposte.push_back(.01);
//    //x0
//    vettore_risposte.push_back(2);
//    //y0
//    vettore_risposte.push_back(2);
//    // n_c
//    vettore_risposte.push_back(5000);
//    // distr.
//    vettore_risposte.push_back(1);
////    // R
////    vettore_risposte.push_back(.5);
//    // Dt save
//    vettore_risposte.push_back(.5);
//    // production rate
//    vettore_risposte.push_back(12);
//    // Film
//    vettore_risposte.push_back(1);
//    // Tj
//    vettore_risposte.push_back(0);
//    // j
//    vettore_risposte.push_back(4);
////    //
////    vettore_risposte.push_back();
//
//    
//
//    ******************************************************************
//    ** Quit
//    ******************************************************************
//    vettore_risposte.push_back(0);
    
   */
    
    // Con un file
    
if(is_file_exist("EcoliRisposteDEMO.Ecoli"))
    return;
    
ofstream EcoliRisp("EcoliRisposteDEMO.Ecoli");
    
    
    EcoliRisp<<"#" << VERSION <<endl;
    // What kind of program
EcoliRisp<<"#What kind of program do you want to perform?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#same seed for the random generator"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Simulation independent/interacting"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Which kind of Model do you want to simulate"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"3"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"6"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"7"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"8"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"9"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#diffusive time-scale parameters:"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to try and visualize different Ligands landscapes"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#x_max"<<endl;
EcoliRisp<<"10"<<endl;
EcoliRisp<<"#y_max"<<endl;
EcoliRisp<<"10"<<endl;
EcoliRisp<<"#x_min"<<endl;
EcoliRisp<<"-10"<<endl;
EcoliRisp<<"#y_min"<<endl;
EcoliRisp<<"-10"<<endl;
EcoliRisp<<"#Which form of the function c(t,x) you want to use"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#Do you want to change the parameters of the profile of the ligand concentration?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the duration in sec. of the simulation: T_f(Diffusive-scale)"<<endl;
EcoliRisp<<"50"<<endl;
EcoliRisp<<"#time-step of the simulation: dt"<<endl;
EcoliRisp<<"0.01"<<endl;
EcoliRisp<<"#x0"<<endl;
    EcoliRisp<<"2"<<endl;
EcoliRisp<<"#y0"<<endl;
EcoliRisp<<"3"<<endl;
EcoliRisp<<"#n_c"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#How often do you want to save the data"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to reproduce now the film of the trajectory? 0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#insert the time (in sec) between two frames"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#Do you want to simulate another trajectory? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
    // What kind of program
EcoliRisp<<"#What kind of program do you want to perform?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#same seed for the random generator"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Simulation independent/interacting"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Which kind of Model do you want to simulate"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#Insert the simulation that do you want to compare. 0 to finish insert simulations"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#diffusive time-scale parameters:"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#diffusive time-scale parameters:"<<endl;
EcoliRisp<<"0.1"<<endl;
EcoliRisp<<"#Do you want to try and visualize different Ligands landscapes"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#x_max"<<endl;
EcoliRisp<<"3"<<endl;
EcoliRisp<<"#y_max"<<endl;
EcoliRisp<<"3"<<endl;
EcoliRisp<<"#x_min"<<endl;
EcoliRisp<<"-3"<<endl;
EcoliRisp<<"#y_min"<<endl;
EcoliRisp<<"-3"<<endl;
EcoliRisp<<"#Which form of the function c(t,x) you want to use"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters of the profile of the ligand concentration?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the duration in sec. of the simulation: T_f(Diffusive-scale)"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#time-step of the simulation: dt"<<endl;
EcoliRisp<<"0.01"<<endl;
EcoliRisp<<"#x0"<<endl;
EcoliRisp<<"1.5"<<endl;
EcoliRisp<<"#y0"<<endl;
EcoliRisp<<"1.5"<<endl;
EcoliRisp<<"#n_c"<<endl;
EcoliRisp<<"5000"<<endl;
EcoliRisp<<"#Which distribution around the initial position"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#How often do you want to save the data"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#speed of the bacterium:"<<endl;
EcoliRisp<<"0.16"<<endl;
EcoliRisp<<"#Insert the response function phi(c):"<<endl;
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Change the mean of tumble and run? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Change the diffusion coefficient? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Change the new theta? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters of the function Q(t)? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the function 'lambda(Q)'? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#speed of the bacterium:"<<endl;
EcoliRisp<<"0.16"<<endl;
EcoliRisp<<"#Insert the response function phi(c):"<<endl;
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Change the mean of tumble and run? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Change the diffusion coefficient? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Change the new theta? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters of the function Q(t)? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the function 'lambda(Q)'? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the function 'sigma'? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#all domain of the experiment"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to see the movie of the evolution of the density? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, "<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#How many n? 4, 9, 16 ..."<<endl;
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#all domain of the experiment"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to see the movie of the evolution of the density? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, "<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#How many n? 4, 9, 16 ..."<<endl;
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Do you want to simulate another trajectory? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
    // What kind of program
EcoliRisp<<"#What kind of program do you want to perform?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#same seed for the random generator"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Simulation independent/interacting"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#Which kind of Model do you want to simulate"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#diffusive time-scale parameters:"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#x_max"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#y_max"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#x_min"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#y_min"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Which form of the function c(t,x) you want to use"<<endl;
EcoliRisp<<"9"<<endl;
EcoliRisp<<"#Do you want to change parameters of the function? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#What dx do you want to applay to the mesh? (dx=dy)"<<endl;
EcoliRisp<<"0.01"<<endl;
EcoliRisp<<"#Which is the degradation rate of the PDE model of the Evolution of Ligand"<<endl;
EcoliRisp<<"0.05"<<endl;
EcoliRisp<<"#Insert the diffusion coefficient D"<<endl;
EcoliRisp<<"0.05"<<endl;
EcoliRisp<<"#Insert the duration in sec. of the simulation: T_f(Diffusive-scale)"<<endl;
EcoliRisp<<"30"<<endl;
EcoliRisp<<"#time-step of the simulation: dt"<<endl;
EcoliRisp<<"0.01"<<endl;
EcoliRisp<<"#x0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#y0"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#n_c"<<endl;
EcoliRisp<<"5000"<<endl;
EcoliRisp<<"#Which distribution around the initial position"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#Radius of the distribution: R"<<endl;
EcoliRisp<<"0.5"<<endl;
EcoliRisp<<"#How often do you want to save the data"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the rate of production of Ligand of a bacterium (default value 10.0)"<<endl;
EcoliRisp<<"12"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;    
EcoliRisp<<"#Do you want to see the movie of the evolution of the density? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, "<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#How many n? 4, 9, 16 ..."<<endl;
EcoliRisp<<"4"<<endl;
//EcoliRisp<<"#Do you want to simulate another trajectory? press 0 for yes, "<<endl;
//EcoliRisp<<"1"<<endl;
    // What kind of program
EcoliRisp<<"#What kind of program do you want to perform?"<<endl;
EcoliRisp<<"3"<<endl;
EcoliRisp<<"#same seed for the random generator"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Simulation independent/interacting"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Which kind of Model do you want to simulate"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#diffusive time-scale parameters:"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to try and visualize different Ligands landscapes"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#x_max"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#y_max"<<endl;
EcoliRisp<<"5"<<endl;
EcoliRisp<<"#x_min"<<endl;
EcoliRisp<<"-5"<<endl;
EcoliRisp<<"#y_min"<<endl;
EcoliRisp<<"-5"<<endl;
EcoliRisp<<"#Which form of the function c(t,x) you want to use"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to change the parameters of the profile of the ligand concentration?"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Insert the duration in sec. of the simulation: T_f(Diffusive-scale)"<<endl;
EcoliRisp<<"10"<<endl;
EcoliRisp<<"#time-step of the simulation: dt"<<endl;
EcoliRisp<<"0.01"<<endl;
EcoliRisp<<"#x0"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#y0"<<endl;
EcoliRisp<<"2"<<endl;
EcoliRisp<<"#n_c"<<endl;
EcoliRisp<<"1000"<<endl;
EcoliRisp<<"#Which distribution around the initial position"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#How often do you want to save the data"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to change the parameters?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#all domain of the experiment"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to see the movie of the evolution of the density? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, "<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#How many n? 4, 9, 16 ..."<<endl; 
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Do you want to simulate another trajectory? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Which kind of Model do you want to simulate"<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#all domain of the experiment"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#Do you want to see the movie of the evolution of the density? press 0 for yes, "<<endl; 
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#Do you want to plot the density at time T=j*T_f/n, j=0...n? press 0 for yes, "<<endl; 
EcoliRisp<<"0"<<endl;
EcoliRisp<<"#How many n? 4, 9, 16 ..."<<endl; 
EcoliRisp<<"4"<<endl;
EcoliRisp<<"#Do you want to simulate another trajectory? press 0 for yes, "<<endl;
EcoliRisp<<"1"<<endl;
EcoliRisp<<"#What kind of program do you want to perform?"<<endl;
EcoliRisp<<"0"<<endl;
EcoliRisp<<"end"<<endl;
    
EcoliRisp.close();

}





