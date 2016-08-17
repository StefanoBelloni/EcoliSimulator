//
//  E_Coli.cpp
//  E_Coli2.0
//
//  Created by Stefano Belloni on 19/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include "E_Coli.h"
#include "ParameterEstimation_E_Coli.h"
#include "CV_rExp_tExp.h"
#include "CV_rIG_tExp.h"
#include "FunzRand.h"
#include <cmath>
#include <vector>
#include <fstream>

#include "GlobalVariables.h"
#include "GlobalRandomVariables.h"
#include "sssr.h"
#include "Colori.h"


#ifndef max
#define max( a, b ) ( ((a) > (b)) ? (a) : (b) )
#endif
#ifndef min
#define min( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

#include "constants.h" //#define pi 3.141592653589793238462

int writeLog(string what, string msg);

//********************
// E_COLI::functions
//********************

// CREA E_COLI "dinamicamente"


//************************** 
//  UPDATE FUNCTIONS
//**************************
//***************************************************************

//***************************************************************

void E_coli::agg_ligand(double t, Funz_C *f){
    
    c = f->new_F_C(t, x);  
//    cout << "f("<<t<<","<<x[0]<<","<<x[1]<<") = " << c << endl;
    // Relative concentration ...
    
//    c = (c_iniziale>0)?c/c_iniziale:c;
    
//    cout << "c(t) = " << c <<"("<<t<<")\n";
    response_function();
    
};


//*************************************************************** 

//int E_coli::initial_condition(double t, double *x0, Funz_C *f){
//    
//    x[0]=x0[0];
//    x[1]=x0[1];
//    this->agg_ligand(t,f);
//    
//    // parto SEMPRE con un run (così non ho difficoltà con la creazione del file statistico)!!!
//    salto_=1;
//    lambda_r=0.0;
//    lambda_t=0.0;
//    
//    t_t=0.0;
//    t_r=0.0;
//    
//    up_down=2; // indice up/down
//    sign_c=2;
//    
//    reset_par();
//    
//    return 0;
//    
//};



//************************** 
//  VIRTUAL FUNCTIONS
//**************************
//***************************************************************

void E_coli::stationary_dyn(double dt, std::vector<double> &m0, int change_pos){
    
    t_r=0.0;
    t_t=0.0;
    
    c_iniziale=c;
    
//    if (change_pos==0) {
//    
////        cout << "la dinamica stazionaria ... 'un cambia" << endl;
//        
//    }else {
////        cout << "la dinamica stazionaria ... va cambia'a" << endl;
//    }
    
    
    
};


//*************************************************************** 

void E_coli::aggiornamento(double dt,double t, Funz_C *f, int &sign_p , std::ofstream *file_tau, std::ofstream &file_theta){
    
//    double dt=dt_/10;
    
    // many if to check the border!!!
    
    double x_M=f->max_x;
    double x_m=f->min_x;
    double y_M=f->max_y;
    double y_m=f->min_x;
    
    int salto_risp=0;
    
    // Aggiornamento Posizione
    
    if(salto_==1) {
        
        x[0]=x[0]+dt*v*cos(theta);
        x[1]=x[1]+dt*v*sin(theta);
        theta+=D_theta*deltaW_ec(dt);
        
        if (x[0]>= x_M || x[0]<=x_m || x[1]>=y_M || x[1]<=y_m) {        
            salto_risp=3; 
            x[0]=min(x_M-.01,max(x_m+.01,x[0]));
            x[1]=min(y_M-.01,max(y_m+.01,x[1]));
        }
        
    }

    
    // Aggiornamento ligant
    
    double c_p=c;
    agg_ligand(t, f);
    
//----------> up_down index!!!    
    
    // Aggiornamento up_down
    
    // Devo provare che se faccio un salto nel primo dt devo buttarlo via da const
    
    sign_c=signum_f(c-c_p);
    
//    if (sign_c==0) {
//        cout << "**********************************" << t << endl;
//        cout << "t = " << t << endl;
//        cout << "c(t,x) = " << c << ", c(t-dt,x-dx) = " << c_p << endl;
//    }
    
    if (sign_p==2) {
        
//        cout << "*****************************"<< endl;
//        cout << "t = " << t << endl;
//        cout << "c = " << c << ", c_p = " << c_p << endl;
//        cout << "up_down = " << up_down << ", sign_c = " << sign_c << ", sign_p = " << sign_p << endl;
        
        // sign_p==2 -> start of new phase.
        
//        cout << "\ndebug:\n";
//        cout << "t = " << t << endl;
//        cout << "sign_c = " << sign_c << endl;
//        cout << "up_down = " << up_down << endl;
        
        sign_p  = sign_c;
        up_down = sign_c;
        
//        sign_p=-1;
//        up_down=-1;
        
        // up_down: 
        //  1 -> up
        //  2 -> mix
        // -1 -> down 
        
    }else{
        
//        cout << "t = " << t << endl;
//        cout << "c = " << c << ", c_p = " << c_p << endl;
//        cout << "up_down = " << up_down << ", sign_c = " << sign_c << ", sign_p = " << sign_p << endl;
        
        if (up_down!=2) {
            
            // CAMBIO GLI INDICI
            
            if (sign_c!=sign_p) {
//                cout << "mix .. " << endl;
                up_down=2;

            }else{
//                sign_p=sign_c;
                up_down=sign_c;
            } 
        }
        
        sign_p = sign_c;
        
    }

    agg_dyint(dt, t);
    int salto_risp_1=this->agg_dyn(dt,t);
    
    if (salto_risp==3 && salto_risp_1==1) {
        
        {
                
            theta = theta-pi;
            
            x[0]=min(x_M,max(x_m,x[0]+dt*v*cos(theta)));
            x[1]=min(y_M,max(y_m,x[1]+dt*v*sin(theta)));
            theta+=D_theta*deltaW_ec(dt);
            
            while (theta<0){
//                cout << "qui ..." << endl;
                theta = theta+2*pi;
            }
            while (theta>2*pi){
//                cout << "qui ..." << endl;
                theta= theta-2*pi;
            }
            
            salto_=-1;
            up_down=2;
            save_theta(t, theta, file_theta);
            save_run(t,file_tau[0],dt);
            t_t=t;
            sign_p=2;
            lambda_r=0.0;
        }
        
    }else{
        switch (salto_risp_1) {
            {
            case 0:
                
//                if (t_r-t<=2*dt) {
//                    up_down=2;
//                    cout << "Breve:\n";
//                    cout << "t= "<< t <<"\n";
//                }
                
                theta=newtheta_ec(theta);
                salto_=-1;
                save_theta(t, theta, file_theta);
                save_run(t,file_tau[0],dt);
                t_t=t;
                sign_p=2;
                break;
            }
            {
            case 2:
                
//                if (t_t-t<=2*dt) {
//                    up_down=2;
//                    cout << "Breve:\n";
//                    cout << "t= "<< t <<"\n";
//                }

                salto_=1;
                save_tumble(t,file_tau[1],dt);
                t_r=t;
                sign_p=2;            
                break;
            }   

            {
            case 4:
                
                cout << "Error in the simulation (Ecoli::aggiornamento) " << endl;
                
                
                string msg("Error in the simulation (Ecoli::aggiornamento).");
//                msg+=name_script_baricenter;
                my_mutex.lock();
                writeLog("ERROR",msg);
                my_mutex.unlock();
                
                break;
            }   
            default:

                break;

            }
    }
      
    // Se interacting mangio e produco, senza crepare!
    
    if (f->interact==0) {
//        eat(f,dt);
        produce(f,dt);
    }

}

//***************************************************************

int E_coli::agg_dyn(double dt, double t)
// E' il cuore della classe ogni batterio implementa questo in modo diverso.
{

    if (salto_==1) {
        lambda_r+=dt/tau_r;
        if (lambda_r>=barriera_r) {
            barriera_r=reset_barrier();
            lambda_r=0.0;
//            seed();
            return salto_=0;
        }
        
    }else if(salto_==-1){
        lambda_t+=dt/tau_t;
        if (lambda_t>=barriera_t) {
//            barriera_t=min(Exp_dist(),1.5);
            barriera_t=reset_barrier_t();
            lambda_t=0.0;
//            seed();
            return salto_=2;
        }
    }
    
    return salto_;
    
};

//**********************************************************************************


E_coli::E_coli()/*:std_unifRand(0.0,1.0)*/{
    
    Tipo_batterio = "E-Coli";
    codice_batterio = EcoliType::E_COLI;
    tipoNewTheta = 1;
    
    this->engine_altro = &rnd_ecoli.random_engines[0];
    this->engine_barrier = &rnd_ecoli.random_engines[0];
    this->engine_theta = &rnd_ecoli.random_engines[0];
    
//    std::random_device   m_rd;
//    engine_theta = new std::mt19937_64(m_rd());
//    std_unifRand = std::uniform_real_distribution<double>(0.0,1.0);
    
    //***************************  
    
    x[0]=0.0;        // Position
    x[1]=0.0;        // Position
    v = epsilon*0.016;           // Speed bacterium  mm/s
//    v=0.16;           // Speed bacterium  mm/s/100
    theta=0;//2*pi*unifRand_ec();       // Direction
    c=0;           // Ligand concentration
    D_theta=0.25;
    
    //***************************    
    
    lambda_r=0.0;     // internal variable, _t -> tumble process; _r -> run process.
    lambda_t=0.0;    
    tau_r=0.8;
    tau_t=0.1;
    
//    //***************************
    
    barriera_r=0.8;     //reset_barrier();       // tresch-hold
//    barriera_t=min(Exp_dist(),1.5);
    barriera_t=0.1;     //reset_barrier_t();
    salto_=1;             // run_fase == 1, tumble_fase == 2, jump_instant == 0, tumble_fase == -1
    t_t=0.0;             // time began tumble
    t_r=0.0;             // time began run
    
    //***************************
    
    sign_c=2;
    up_down=2;
    n_dyn_var=0;
    
    this->production_rate = 10;
    
    //***************************
    
    tipo_response_c=0;
    RC_0=1;
    RC_1=0;
    RC_q=0;
    
//    cout << "production_rate = " << production_rate << endl;
//    production_rate = 10;
//    cout << "production_rate = " << production_rate << endl;
    
}


E_coli::E_coli(const E_coli& m)/*:std_unifRand(0.0,1.0)*/{
    
    Tipo_batterio = m.Tipo_batterio;
    codice_batterio = m.codice_batterio;
    
    this->engine_altro = m.engine_theta;
    this->engine_barrier = m.engine_barrier;
    this->engine_theta = m.engine_theta;
    this->tipoNewTheta = m.tipoNewTheta;
    this->production_rate = m.production_rate;
    
//    std_unifRand = std::uniform_real_distribution<double>(0.0,1.0);
    
    //***************************
    
    this->x[0]=m.x[0];        // Position
    this->x[1]=m.x[1];        // Position
    this->v = m.v;           // Speed bacterium  mm/s
    //    v=0.16;           // Speed bacterium  mm/s/100
    this->theta=0; //2*pi*unifRand_ec();       // Direction
    this->c=m.c;           // Ligand concentration
    this->D_theta=m.D_theta;
    
    //***************************
    
    this->lambda_r=m.lambda_r;     // internal variable, _t -> tumble process; _r -> run process.
    this->lambda_t=m.lambda_t;
    this->tau_r=m.tau_r;
    this->tau_t=m.tau_t;
    
    //    //***************************
    
    barriera_r=0.8;     //reset_barrier();       // tresch-hold
    //    barriera_t=min(Exp_dist(),1.5);
    barriera_t=0.1;     //reset_barrier_t();
    this->salto_=1;             // run_fase == 1, tumble_fase == 2, jump_instant == 0, tumble_fase == -1
    this->t_t=0.0;             // time began tumble
    this->t_r=0.0;             // time began run
    
    //***************************
    
    this->sign_c=2;
    this->up_down=2;
    this->n_dyn_var=m.n_dyn_var;
    
    //***************************
    
    this->tipo_response_c=m.tipo_response_c;
    this->RC_0=m.RC_0;
    this->RC_1=m.RC_1;
    this->RC_q=m.RC_q;
    
    //    cout << "production_rate = " << production_rate << endl;
    this->production_rate = m.production_rate;
    //    cout << "production_rate = " << production_rate << endl;
    
    this->s_lambda_r = m.s_lambda_r;
    
}

void E_coli::change_par(int change){
    // 0 se cambio i parametri
    if (change==0) {
        
        D_theta=0.25;
        v = 0.016*epsilon;
        
        //***************************    
        
        lambda_r=0.0;     // internal variable, _t -> tumble process; _r -> run process.
        lambda_t=0.0;    
        tau_r=0.8;
        tau_t=0.1;
        
        tipo_response_c=0;
        RC_0=1;
        RC_1=0;
        RC_q=0;
        tipoNewTheta=1;
        
        
        
    }else {
        
        cout << "Insert the speed of a bacterium: " << endl;
        cout << "The default is 0.016 (which is mm/s.)" << endl;
        cout << BOLDRED<< "NOTE:\n"<< RESET << "speed_Diff = epsilon*speed and time_Diff=t/epsilon^2\n";
        cout << "with epsilon = " << epsilon <<endl;
        cout << "v = ";
        sssr(E_coli::v,"speed of the bacterium:");
        
        v=v*epsilon;
        
        //***********************************************************************
        cout << "Insert the response function phi(c): " << endl;
        cout << "0 - phi(c) = C_00*c" << endl;
        cout << "1 - phi(c) = C_01*log(1+C_02*c)" << endl;
        cout << "2 - phi(c) = c = RC_0*(c/(RC_1+c))" << endl; 
        cout << "3 - phi(c) = C_03*pow(c,C_13)/(pow(C_23,C_13)+pow(c,C_13))\n";
        cout << "4 - default phi(c) = c"<< endl;
        cout << "num_phi(c) = ";
        sssr(tipo_response_c,"Insert the response function phi(c):");
        
        switch (tipo_response_c) 
        {
            case 0:
                
                cout << "//***********************************************************\n//\n";
                cout << "0 - phi(c) = C_00*c" << endl;
                
                cout << "C_00= ";
                sssr(RC_0,"C_00");;
                
                
                break;
                
            case 1:
                
                cout << "//***********************************************************\n//\n";
                cout << "0 - phi(c) = C_01*log(1+C_11*c)" << endl;
                
                cout << "C_01= ";
                sssr(RC_0,"C_01");;
                
                cout << "C_11= ";
                sssr(RC_1,"C_11");;
                
                break;
                
            case 2:
                
                cout << "//***********************************************************\n//\n";
                cout << "0 - phi(c) = c = RC_0*(c/(RC_1+c))" << endl;
                
                cout << "RC_0= ";
                sssr(RC_0,"RC_0");;
                
                cout << "RC_1= ";
                sssr(RC_1,"RC_1");;
                
                break;
                
            case 3:
                
                cout << "//***********************************************************\n//\n";
                cout << "0 - phi(c) = C_03*pow(c,C_13)/(pow(C_23,C_13)+pow(c,C_13))" << endl;
                
                cout << "C_03= ";
                sssr(RC_0,"C_03");;
                
                cout << "C_= C_23 ";
                sssr(RC_1,"C_23");;
                
                cout << "integer valued: C_14= ";
                sssr(RC_q,"C_14");;
                
                break;
                
            default:
                
                tipo_response_c=0;
                RC_0=1;
                RC_1=0;
                RC_q=1;
                
                break;
        }
    
    
        int risp=0;
        
        //***********************************************************************
        
        cout << "Change the mean of tumble and run in the steady state? \npress 0 for yes, 1 for no ";
        sssr(risp, "Change the diffusion coefficient? press 0 for yes, 1 for no ");

        if (risp==0) {
            cout << "\nInsert the value of the parameter tau_r, the mean of the run time:\nInsert -1 for default value 0.8\ntau_r:= ";
            sssr(tau_r,"Insert the value of the parameter tau_r");
            if (tau_r==-1) {
                tau_r=0.8;
            }
            cout << "\nInsert the value of the parameter tau_t, the mean of the tumble time:\nInsert -1 for default value 0.1\ntau_t:= ";
            sssr(tau_t,"Insert the value of the parameter tau_t");
            if (tau_r==-1) {
                tau_r=0.1;
            }
        }
        
        //***********************************************************************
        
        cout << "Change the diffusion coefficient of the direction? \npress 0 for yes, 1 for no ";
        sssr(risp, "Change the diffusion coefficient? press 0 for yes, 1 for no ");
        
        if (risp==0) {
            std::cout << "Insert the value of the diffusion coefficient D_theta for the angle ";
            sssr(D_theta,"Insert the value of the diffusion coefficient D_theta for the angle ");
        }
        
        cout << "Change the distribution of the new direction? \npress 0 for yes, 1 for no ";
        sssr(risp, "Change the distribution direction? press 0 for yes, 1 for no ");
        
        if (risp==0) {
            cout << "Which distribution of the new direction do you want to use?" << endl;
            cout << "1- Gamma around the old direction (default):" << endl;
            cout << " theta=theta+/-pi*(4.6+Gamma(4)*18.2)/180;" << endl;
            cout << "2- Uniform on [0,2*pi):" << endl;
            cout << " theta = 2*pi*Uniform(0,1)" << endl;
            cout << "Distribution n.: ";
            sssr(tipoNewTheta,"Which distribution of the new direction");
        }
        
    }

}

void E_coli::reset_par(){

    //***************************  
    
    x[0]=0.0;        // Position
    x[1]=0.0;        // Position
    v=0.016;           // Speed bacterium
//    v=0.16;           // Speed bacterium
    theta=2*pi*unifRand_ec();       // Direction
    c=0;           // Ligand concentration
    D_theta=0.25;
    tipoNewTheta=1;
    production_rate = 10;
    
    //***************************    
    
    lambda_r=0.0;     // internal variable, _t -> tumble process; _r -> run process.
    lambda_t=0.0;    
    tau_r=0.8;
    tau_t=0.1;
    
    //***************************
    
    barriera_r=reset_barrier();       // tresch-hold 
//    barriera_t=min(Exp_dist(),1.5);
    barriera_t=reset_barrier_t();

    salto_=1;             // run_fase == 1, tumble_fase == 2, jump_instant == 0, tumble_fase == -1
    t_t=0.0;             // time began tumble
    t_r=0.0;             // time began run
    
    //***************************
    
    sign_c=2;
    up_down=2;
    n_dyn_var=0;
    
    //***************************
    
    c_iniziale=0;
    
    tipo_response_c=0;
    RC_0=1;
    RC_1=0;
    RC_q=1;

}


//***************************************************************
//***************************************************************


void E_coli::save_run(double t, std::ofstream &file_run, double dt){
   

    file_run << t << " " << t-t_r+ unifRand_ec()*dt<< " " << up_down << endl;
    
//    if (t-t_r>8) {
//        my_mutex.lock();
//        cout << t << " " << t-t_r << " " << up_down << endl;
//        my_mutex.unlock();
//
//    }
    
//    last_tau_r=t-t_r;
    
};

void E_coli::save_tumble(double t, ofstream &file_tumble, double dt){

    double rnd = unifRand_ec();
    file_tumble << t << " " << t-t_t +(rnd<0.5)*rnd*dt << " " << c << endl;

//    file_tumble << t << " " << t-t_t << endl << " " << c << endl;
//    last_tau_r=t-t_t;

};


void E_coli::save_theta(double t, double theta, std::ofstream &file_theta){
    
    file_theta << t << " " << theta << endl;
    
};

void E_coli::save_E_coli_initial(std::ofstream *file_, double t){
    
    my_mutex.lock();
    file_[0] << x[0] << " " << x[1] << " " << up_down << endl;
        cout << "save        (x,y): " << x[0] << " , " << x[1] << " , " << up_down << endl;
//        file_[0] << x[0] << " " << x[1] << " " << sign_c << endl;
    file_[1] << t << " " << theta << endl;
    file_[2] << t << " " << c << endl;
    my_mutex.unlock();
};

void E_coli::save_E_coli(std::ofstream *file_, double t){
    
    // Magari è meglio up/down
    // up_down:
    //  1 -> up
    //  2 -> mix -> sign_c 2->0 !!!!
    //  0 -> const 
    // -1 -> down
//    int val = (up_down==2)?0:up_down;

//    my_mutex.lock();
    file_[0] << x[0] << " " << x[1] << " " << up_down << endl;
//    cout << "save (x,y)" << x[0] << " , " << x[1] << " " << up_down << endl;
//    file_[0] << x[0] << " " << x[1] << " " << sign_c << endl;
    file_[1] << t << " " << theta << endl;
    file_[2] << t << " " << c << endl;
//    my_mutex.unlock();
    
};

void E_coli::save_dyn(ofstream &file_, double t){
    
    file_ << t << " " << lambda_r << " " << lambda_t << endl;
    
};

//************************************************************************************

//#define nahrung 0.05;

//void E_coli::eat(Funz_C* f_i, double dt){
//        
//    int n_x[2];
//    double nahrung=dt*0.05;
//    f_i->get_coordinate(x,n_x);
//    (*(f_i->q_c))[n_x[0]*f_i->n_y+n_x[1]]-=((*(f_i->f_c))[n_x[0]*f_i->n_y+n_x[1]])*nahrung;
//    
////    cout << "f_q = " << ((*(f_i->f_c))[n_x[0]*f_i->n_y+n_x[1]])*nahrung << endl;
//    
//}

void E_coli::produce(Funz_C* f_i, double dt)
{    
    int n_x[4];
//    double product=dt*0.5;
    
    // I spilt in 4.
    
    f_i->get_coordinate1(x,n_x);
    
//    (*(f_i->q_c))[n_x[0]*f_i->n_y+n_x[1]]+=((*(f_i->f_c))[n_x[0]*f_i->n_y+n_x[1]])*product*dt;
    
    (*(f_i->q_c))[n_x[0]*f_i->n_y+n_x[1]]+=(production_rate*dt/4);
    (*(f_i->q_c))[n_x[2]*f_i->n_y+n_x[3]]+=(production_rate*dt/4);
    
//    cout << "(*(f_i->q_c))[n_x[0]*f_i->n_y+n_x[1]] = " << (*(f_i->q_c))[n_x[0]*f_i->n_y+n_x[1]] << endl;
//    cout << "production_rate = " << production_rate << endl;
    
}

void E_coli::response_function(){
    
    switch (tipo_response_c) 
    {
        case 0:
            
            c = RC_0*c;
            
            break;
            
        case 1:
            
            c = RC_0*log(1+RC_1*c);
            
            break;
            
        case 2:
            
            c = RC_0*(c/(RC_1+c));
            
            break;
            
        case 3:
            
            c = RC_0*pow(c,RC_q)/(pow(RC_1,RC_q)+pow(c,RC_q));
            
            break;
            
        default:
            
//            c = c;
            
            break;
    }
    
}

void E_coli::set_response(int ftipo_response_c, double fRC_0, double fRC_1, int fRC_q){
    
    tipo_response_c=ftipo_response_c;
    RC_0=fRC_0;
    RC_1=fRC_1;
    RC_q=fRC_q;
    
    
}

void E_coli::set_GoodnessFit(int Good, double D_n, double cumD_n){
    
    cout << "No fit possible ...\n";
    
}

void ParameterEstimation_E_coli::set_GoodnessFit(int Good, double D_n, double cumD_n){
    
    GoodFit = Good;
    KS_D_n = D_n;
    KS_L1 = cumD_n;
    
}

//void E_coli::print_info(ofstream &file_save){
//    
//    file_save << "In the steady state,"<<endl
//              << "   - the mean time of a run is tau_r = " <<tau_r <<" sec."  << endl
//              << "   - the mean time of a tumble is tau_t" <<tau_t <<" sec." << endl;
//    file_save << "The type of response to the Ligand concentration is: "<< endl <<"      ";
//    
//    switch (tipo_response_c) 
//    {
//        case 0:
//            
//            file_save << " c = "<<RC_0<<"*c"<<endl;
//            
//            break;
//            
//        case 1:
//            
//            file_save << " c = "<< RC_0<<"*log(1+"<<RC_1<<"*c)";
//            
//            break;
//            
//        case 2:
//            
//            file_save << " c = "<<RC_0<<"*(pi/2+atan("<<RC_1<<"*c))"<<endl;
//            
//            break;
//            
//        case 3:
//            
//            file_save << " c = "<< RC_0<<"*c^("<<RC_q<<")/("<<RC_1<<"^("<<RC_q<<")+c^("<<RC_q<<"))"<<endl;
//            
//            break;
//            
//        default:
//            
//            file_save << " c = c "<< endl;
//            
//            break;
//    }
//    
//    file_save << "\nThe diffusion coefficient for the angle theta is D_theta = "<< D_theta << endl;
//    
//    
//};

//int lambda_prod(){}
//
//int lambda_eat(){}
    

void E_coli::statF_lambda_r(s_lambda &vector_lambda){
    
    s_lambda_r = vector_lambda;
    
}

void E_coli::start_simulation(Funz_C *f){
    
//    cout << "start simulation: " << endl;
    
    this->t_t=0.0;
    this->t_r=0.0;
    this->lambda_r=0.0;
    this->lambda_t=0.0;
    
    this->barriera_r=this->reset_barrier();
    this->barriera_t=this->reset_barrier_t();
    this->theta = 2*pi*unifRand_ec();
    

    
    
//    this->agg_ligand(0, f);
    this->agg_ligand(0, f);
    this->c_iniziale = this-> c;
    
//    cout << "Start simulation: c = " << this->c << endl;
    
    this->up_down = 0;
//    this->agg_ligand(0, f);
//    this->agg_ligand(c, f);
    
    this->salto_=1;
    
    // comment this if you don't want 'random internal dynamics'
    
//    std::uniform_int_distribution<int> std_unif_int(1,2);
    std::uniform_real_distribution<double> std_unif_real(0.0,0.1);
    salto_=(std_unif_real(*engine_altro)>0.5)?1:2;
    
    // random lambra_ iniziale:    
    if (salto_==1) //run
        lambda_r =std_unif_real(*engine_altro)*barriera_r*0.8;
    else
        lambda_r =std_unif_real(*engine_altro)*barriera_t*0.8;
    
//    if (salto_!=1){
//        my_mutex.lock();
//        cout << "tumble ... " << endl;
//        my_mutex.unlock();
//    }

}

/*
 * return the position (2D (x,y)) of the bacterium
 */

array<double, 2> E_coli::X(){
    return x;
}

/*
 * return the number of internal dynamic used in the model
 */

int E_coli::N_dyn_var(){
    return n_dyn_var;
}

/*
 * return the current level of Ligand Concentration that the nbacterium hat registered
 */

double E_coli::C(){
    return c;
}

/*
 * return the level of Ligand concentration recorded at the beginning of the simulation
 */

double E_coli::C_iniziale(){
    return c_iniziale;
}

/*
 * Return the production rate of Ligand concentration
 */

double E_coli::Production_rate(){
    return production_rate;
}

void E_coli::setProductionRate(double _proRate){
    production_rate=_proRate;
}

/*
 * set the time the tumble starts
 */

void E_coli::Tau_t(double t){
    tau_t = t;
}

void E_coli::Get_tipo_response_c(int T_r){
    tipo_response_c = T_r;
}
void E_coli::Get_RC_0(double Rc0){
    RC_0 = Rc0;
}
void E_coli::Get_RC_1(double Rc1){
    RC_1 = Rc1;
}
void E_coli::Get_RC_q(int Rcq){
    RC_q =Rcq;
}
int E_coli::F_tipo_response_c(){
    return tipo_response_c;
}
double E_coli::F_RC_0(){
    return RC_0;
}
double E_coli::F_RC_1(){
    return RC_1;
}
double E_coli::F_RC_q(){
    return RC_q;
}



//**********************
// RANDOM
//**********************

double E_coli::Exp_dist_ec(){
    
//    std::uniform_real_distribution<double> std_unifRand_(0.0,1.0);
//    return -log(std_unifRand_(*engine_theta));
    
    std::exponential_distribution<double> std_expRand_(1.0);
    
    return /*double e = */ std_expRand_(*engine_barrier);
    
//    my_mutex.lock();
//    cout << "e/t = " << e/tau_r << endl;
//    my_mutex.unlock();
    
//    return e;
    
};

double E_coli::rand_normal_ec(double stddev){//Box muller method
    
    
    std::normal_distribution<double> norm_Rand_(0.0,stddev);
    return norm_Rand_(*engine_altro);
    
};

double E_coli::gamma_par_double_ec(){
    
    std::uniform_real_distribution<double> std_unifRand_(0.0,1.0);
    
    double x=1;
    
    for(int i=0;i<alpha;i++){
        x=x*std_unifRand_(*engine_theta);
    }
    
    return disp_gamma-log(x)*beta;
};

double E_coli::unifRand_ec(){
    
//    thread_local static std::mt19937 rng(std::random_device{}());
//    thread_local static std::uniform_int_distribution<int> uni;
//    
//    // assuming param_type is lighter weight to construct
//    // than a uniform_int_distribution
//    return uni(rng, decltype(uni)::param_type{min, max});
    
    std::uniform_real_distribution<double> std_unifRand_(0.0,1.0);
    return std_unifRand_(*engine_altro);
//    return rand_r(seed_ecoli) / double(RAND_MAX);
};

double E_coli::deltaW_ec(double dt){
    

    
    double dW=0.0;
    short R=4;
    double stdt=sqrt(dt/R);
    
    std::normal_distribution<double> norm_Rand_(0.0,stdt);
    
    for (int j=0; j<R; j++) {
//        dW+=rand_normal(stdt);
        dW+=norm_Rand_(*engine_altro);
    }
    
    return dW;
};

double E_coli::newtheta_ec(double theta){
    
    std::uniform_real_distribution<double> std_unifRand_(0.0,1.0);

    
    switch (tipoNewTheta) {
        {case 1:
            double s=1;
            double theta_=0;
            if (std_unifRand_(*engine_theta)<=.5) {
                s=-1;
            }
            theta_=theta;
            double x=1;
            for(int i=0;i<alpha;i++){
                x=x*std_unifRand_(*engine_theta);
            }
            x = disp_gamma-log(x)*beta;
            theta=theta+pi*s*x/180;
            if (fabs(theta)>5000) {
                std::cout << "problem generation new_theta: given a default theta=theta+46*Unif[0,1]\n";
                theta=theta_+s*46*std_unifRand_(*engine_theta)*pi/180;
            }
            
            break;
        }
        {default:
            theta=2*pi*std_unifRand_(*engine_theta);
            break;
        }
    }
    
    while (theta<0){
        theta = theta+2*pi;
    }
    while (theta>2*pi){
        theta= theta-2*pi;
    }
    return theta;
};


int E_coli::dist_iniz_ec(array<double,2> x0, double R,unsigned int num_dist)
{
//    cout << "int E_coli::dist_iniz_ec ..." << endl;
    
    switch (num_dist) {
        case 2:
            x[0] = x0[0]+R*sqrt(unifRand_ec())*cos(2*pi*unifRand_ec());
            x[1] = x0[1]+R*sqrt(unifRand_ec())*sin(2*pi*unifRand_ec());
            return 1;
            break;
            
        case 3:
            x[0] = x0[0]-R+2*R*unifRand_ec();
            x[1] = x0[1];
            return 1;
            break;
            
        case 4:
            x[1] = x0[1]-R+2*R*unifRand_ec();
            x[0] = x0[0];
            return 1;
            break;
            
        default:
            x[0]=x0[0];
            x[1]=x0[1];
            return 0;
            
            break;
    }
    
    return 0;

    
}

/**
 * This function set the initial position. What it does is: if the distribution is the n. 5, then update the new center, otherwise it calls dist_iniz(x,x0,Raggio,num_dist).
 * @param x[] position of pacterium (to be set)
 * @param x0[] initial position, set in the menu
 * @param R radius distribution
 * @param type of distribution, see menu
 * @return if the initial position change return 1, otherwise 0. If the position didn't change the initial condition for this bacterium are the same as the previous one, so we don't have to perform initial-condition calculation.
 */

int E_coli::initial_position_ec(int j, array<double,2> x0, double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, double Delta_delta_dist)
{
    int cambiato=0;
    
    
    if (num_dist==5){
        
        if (j>cont_dist_5)
        {
            cont_dist_5=cont_dist_5+delta_dist_cont;
            x0[0]=x0[0]+Delta_delta_dist;
            cambiato=1;
            //            std::cout << "(x,y)_"<<j<<" = " << x0[0] << " , " << x0[1] << std::endl;
            
        }
        
        x[0]=x0[0];
        x[1]=x0[1];
        
    }else{
        
        if (num_dist==1) {
            
            x[0]=x0[0];
            x[1]=x0[1];

//            my_mutex.lock();
//            cout << "num_dist: " << num_dist <<" (x,y) " << x[0] << ", " << x[1] << endl;
//            cout << "            (x0,y0) " << x0[0] << ", " << x0[1] << endl;
//            my_mutex.unlock();
            cambiato=0;
            
        } else {
            return dist_iniz_ec(x0,Raggio,num_dist);
            
        }
    }

//        std::cout << "(x(0),y(0)) = (" << x[0] << "," << x[1] << ")"<< std::endl;
    
    return cambiato;
}
