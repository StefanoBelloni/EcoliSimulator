//
//  E_Coli.h
//  E_Coli2.0
//
//  Created by Stefano Belloni on 19/05/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#ifndef E_Coli2_0_E_Coli_h
#define E_Coli2_0_E_Coli_h

#include <iostream>
#include <vector>
#include "s_lambda.h"
#include <array>
#include <random>
#include <chrono>

#include "FunzRand.h"
#include "Funz_C.h"
#include "Funz_C_Inter.h"

#include "Q_tau_stat.h"


#include "constants.h" //#define pi 3.141592653589793238462
//#define lim_alpha 2.5327805161251
#define alpha 4.0
#define beta 18.32
#define disp_gamma 4.6

namespace EcoliType {
    
    enum{
    
        E_COLI = 0,
        CV_REXP_TEXP,
        CV_RIG_TEXP,
        CV_RIGEXP_TEXP,
        MOLECULAR_REXP_TEXP,
        MOLECULAR_RIG_TEXP,
        MOLECULAR_RIGEXP_TEXP,
        EO_REXP_REXP_TEXP,
        EO_REXP_RIG_TEXP,
        EO_REXP_RIGEXP_TEXP,
        // parameter estimation ...
        PAR_E_COLI,
        PAR_CV_REXP_TEXP,
        PAR_CV_RIG_TEXP,
        PAR_CV_RIGEXP_TEXP,
        
    };

}


/** \brief Base Class for a bacterium:
 * It implements the virtual function to evolve the dynamic of the bacterium.
 *
 *
 */

class E_coli  {
    
protected:
    
    /** Production rate bacterium*/
    /*static */long double production_rate;
    /** Speed bacterium*/
    //  if you change the default value, please change also in Funz_C.cpp LIGAND CONCENTRATION MENU
    /*static */long double v;
    // Usando un solo batterio alla volta posso fare le variabili della classe base static
    // ma nelle funzioni interacting uso un vettore di copie di Ecoli* !!!

    //***************************
    /** Position*/
    std::array<long double,2> x;
    
    /** Direction */
    long double theta;
    /** Ligand concentration*/
    long double c;
    /** Diffusion coefficient direction */
    long double D_theta;
    
    //***************************    
    
    /** probability rate to tumble*/
    long double lambda_r;     // internal variable, _t -> tumble process; _r -> run process.
    /** probability rate to run*/
    long double lambda_t;
    /** mean of a run in the steady state*/
    long double tau_r;
    /** mean of a tumble in the steady state*/
    long double tau_t;
    
    //***************************
    /** number internal variables*/
    int n_dyn_var;
    /** threshold for lambda_r (when lambda_r crosses it, tumble starts)*/
    long double barriera_r;       // tresch-hold
    /** threshold for lambda_t (when lambda_r crosses it, run starts)*/
    long double barriera_t;
    
//    long double barriera_e;
//    long double barriera_p;
    
    /** variable identifying in which state I'm in
     run_fase == 1, tumble_fase == 2, jump_instant == 0, tumble_fase == -1
     */
    int salto_;             // run_fase == 1, tumble_fase == 2, jump_instant == 0, tumble_fase == -1
    /** time began tumble */
    long double t_t;             // time began tumble
    /** time began run */
    long double t_r;             // time began run
    
    //***************************
    
    /** sign of the "temporal gradient": c(now) - c(now-dt)*/
    int sign_c;
    /** variable that keep track if I'm going up or down the gradient*/
    int up_down;
    /** initial concentration of Ligand*/
    long double c_iniziale;

    /** Type of reponse function between the available */
    int tipo_response_c;
    /** 1st paramter in the response function*/
    long double RC_0;
    /** 2nd paramter in the response function*/
    long double RC_1;
    /** 3rd paramter in the response function: esponent in th Hill function*/
    int RC_q;
    /** This variable take track of the for of the distribution of the new theta */
    int tipoNewTheta;
    
    /************************************************************
     *      RANDOM MULTI-THREAD PART.
     ************************************************************/
    
    /** \brief pointer to a seed
     *
     *  The idea is the following:
     *  At the beginning of every simulation I seed the extra-thread
     *      - if I use a nomal 1-thread then nothing change from the 'basic implmentation', 
     *        I just move the random generation function inside the class E_coli.
     *      - if I use multi-thread, for each thread I create a new seed_ecoli, which I pass to rand_r(&seed_ecoli)
     *        in this case I have independent sereis of Random Numebr for every thread.
     */
    
//    void foo() {
//        std::mt19937_64 engine(static_cast<uint64_t> (system_clock::to_time_t(system_clock::now())));
//        std::uniform_real_distribution<long double> zeroToOne(0.0, 1.0);
//#pragma omp parallel for
//        for (int i = 0; i < 1000; i++) {
//            long double a = zeroToOne(engine);
//        }
//    }
    
    unsigned int* seed_ecoli;
    void setSeed_ec(unsigned int* seed_thread);
    
    /*! write the script for the gnuplot of single bacterium*/
    virtual int writeScriptgnuplotSingle(std::string tipo, std::string *names_files_Ecoli_mod, std::string *names_files_tau_mod, std::string *names_info_mod, std::string &names_file_dyn_mod, long double T_f, int con_gen_sim, int save_);
    virtual int writeScriptLunchgnuplotSingle(std::string tipo, int save_, int con_gen_sim);

    
    
//    std::uniform_real_distribution<long double> std_unifRand; // construct it on (0,1)!
    
    long double Exp_dist_ec();
    long double rand_normal_ec(long double stddev);
    long double gamma_par_double_ec();
    long double unifRand_ec();
    long double deltaW_ec(long double dt);
    long double newtheta_ec(long double theta);
    void setEngine_ec(std::mt19937_64* engine_thread_theta,std::mt19937_64* engine_thread_bar,std::mt19937_64* engine_thread_altro);

    /*************************************************************/
    
public:
    
    /** \brief pointer to a engine (if I want to use std::uniform_real_distribution<long double>) */
    
    std::mt19937_64* engine_theta;
    std::mt19937_64* engine_barrier;
    std::mt19937_64* engine_altro;
    
    /**
     * MODE of simulation:<br>
     * - simulation = 0 -> MODE simulation,
     * - simulation = 1 -> MODE statistical_Simulation ...
     */
    int simulation;         // simulation = 0 -> MODE simulation, = 1 -> MODE statistical_Simulation ...
    /**
     * Name of the model used<br>
     * the format in as follows:
     * [Name Model]_r[Name Distribution run]_t[Name Distribution tumble]
     */
    std::string Tipo_batterio;
    int codice_batterio;
    /**
     * estimated parameter for the function lambda
     */
    s_lambda s_lambda_r;
    
    
    // CONSTRUCTOR & DESTRUCTOR
    virtual ~E_coli();
    E_coli();
    E_coli(const E_coli& modello);
    //***************************  
    // UPDATE FUNCTIONS    
    //***************************    
    
    
//    int initial_condition(long double t, long double *x0, Funz_C *f);
    
    // Funzioni per accedere protected variables ...
    
    int initial_position_ec(int j, std::array<long double,2> x0, long double Raggio, int num_dist, int &cont_dist_5, int delta_dist_cont, long double Delta_delta_dist);
    int dist_iniz_ec(std::array<long double,2>  x0, long double R,unsigned int num_dist);
    /** return position bacterium*/
    std::array<long double,2> X();      // Potrebbe essere una brutta pratica, dacchè viola la classe protetta  !!
    /** return speed bacterium*/
    long double V(){return v;};      // Potrebbe essere una brutta pratica, dacchè viola la classe protetta  !!
    /** return number of internal variables in the current model*/
    int N_dyn_var();
    /** return current ligand concentration*/
    long double C();
    /** return initial ligand concentration*/
    long double C_iniziale();
    /** retun rate of production of new ligand concentration by the bacterium*/
    long double Production_rate();
    /** set production rate (it is a static variable, once for all!)*/
    void setProductionRate(long double _prodRate);
    /** set time start of a tumble
     * @param tt_ time in sec.
     */
    void Tau_t(long double tt_);
    /** set type of response
     * @param tt_ type of response
    */
    void Get_tipo_response_c(int T_r);
    /** set 1st coefficient */
    void Get_RC_0(long double Rc0);
    /** set 2nd coefficient*/
    void Get_RC_1(long double Rc1);
    /** set 3rd coefficient*/
    void Get_RC_q(int Rcq);
    /** return current type of response */
    int F_tipo_response_c();
    /** return 1st coefficient*/
    long double F_RC_0();
    /** return 2nd coefficient*/
    long double F_RC_1();
    /** return 3rd coefficient*/
    long double F_RC_q();
    
    
    /** set response function
     * @param type and coefficient (from 1st to last)
     */
    void set_response(int ftipo_response_c, long double fRC_0, long double fRC_1, int fRC_q);
    
    /** update ligand concentration*/
    void agg_ligand(long double t, Funz_C *f);
    
    /** update all the parameters of the bacterium during the simulation*/
    void aggiornamento(long double dt,long double t, Funz_C *f, int &sign_p , ofstream *file_tau, std::ofstream &file_theta);
    
    /** set initial data for the simulation */
    void start_simulation(Funz_C *f);
    // file_tau[0] = run; file_tau[1] = tumble
    
    
    
    //***************************
    //      SAVE TO FILE
    //***************************    
    
    /** update the current concentration via the response function */
    void response_function();
    
    /** save position, concentration and direction to file*/
    void save_E_coli(ofstream *file, long double t);
    void save_E_coli_initial(std::ofstream *file_, long double t);
    /** save time and duration of a run
     */
    void save_run(long double t, ofstream &file_salto, long double dt);
    
    /** save time and duration of a tumble
     * @param dt time-step in the simulation
     */
    void save_tumble(long double t, ofstream &file_tumble, long double dt);

    /*! function used to save the angle at the moment of a tumble.*/
    void save_theta(long double t, long double theta, std::ofstream &file_run);
    
//    long double lambda_prod();
//    long double lambda_eat();
    
    //*********************************************
    //      VIRTUAL FUNCTIONS DA REIMPLEMENTARE
    //*********************************************
    
    /** set parameters model */
    virtual void change_par(int change);
    
    /** reset defolt parametes model */
    virtual void reset_par();
    
    /** calculate stationary dynamics for the initial condition
      * @param m0 are the initial condition for the internal variables: if changed_pos says that the initial condition are not changed, for example if the initial distribution for the population is a  delta dirac, then we just use the old values, and do not recalculate them
     */
    virtual void stationary_dyn(long double dt, std::vector<long double> &m0, int changed_pos);
    
    /** update dynamic to control run/tumble <br>
     *  It controll the hitting time \f$\tau_{n+1}\f$ of the inernal variable lambda_[...]
     *  Heuristically we have:
     *     - if the distribution is exponential we have <br>
     *          -  \f$\int_{\tau_{n}}^{\tau_{n+1}}\Lambda^*(s)ds\sim Exp(1)\f$
     *     - if the distribution is IG we have <br>
     *          -  \f$\tau_{n+1}=\inf\{s>\tau_n:\Lambda(s)ds\geq const\}\f$
     *     - if the distribution is Exp_IG we have <br>
     *           - \f$\tau_{n+1}=\inf\{s>\tau_n:\Lambda(s)ds\geq Exp(1)\}\f$<br>
     *
     * Where in general we can write: \f$d\Lambda(s)=\lambda(s)dt+\sigma(s)dW(t)\f$.<br>
     * note \f$\sigma(s)=0\f$ in the first case above.
     */
    virtual int agg_dyn(long double dt, long double t);
    
    virtual int saveIntDyn(std::string nameFile);
    
    /** update internal dynamic */
    /* TODO:
        In the code there's the possibility to subdivide the time-step dt, in n_iteration sub-step (now there are 5 iteration)
        you might want to have n_iteration as a variable of Ecoli and allow the user to control it, or write a function which given the parameters of the ODE ives back the number of iteration needed to have stability in the solver.
     */
    virtual void agg_dyint(long double dt, long double t);
    
    //    virtual void eat(Funz_C* f_i, long double dt);
    /** update concentration ligand after production (in interacting mode)*/
    virtual void produce(Funz_C* f_i, long double dt);
    /** reset trashold for the run */
    virtual long double reset_barrier();
    /** reset trashold for the tumble */
    virtual long double reset_barrier_t();
    //---> Aggiorno la dinamica interna{m,Q,lambda_-> salto_}
    
    /** save internal dynamic in a file*/
    virtual void save_dyn(ofstream &file, long double t);
    /** plot via gnuplot trajectory and data for single tracking*/
    virtual void gnuplot_single(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, long double T_f, Funz_C *f, int save_, int con_gen_sim);
    /** save and produce film of single tracking */
    virtual void gnuplot_single_film(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, long double T_f, Funz_C *f, int cont_sim);
    /** save and produce film of single tracking in .gif*/
    virtual void gnuplot_single_film_gif(std::string *names_files_Ecoli_mod, std::string &names_indice_mod, std::string *names_files_tau_mod, std::string &names_file_dyn_mod, std::string *names_info_mod, long double T_f, Funz_C *f, int cont_sim);
    /** print info for LateX report*/
    virtual void print_info(std::ofstream &file_save);
    /** plot internal dynamic*/
    virtual void gnuplotFunzInternalDynalmic(std::string buffer, int save_,  int con_gen_sim);
    /** plot response: empty function ... not yet implemented*/
    virtual void gnuplot_response(std::string names_info_mod, int save_, int con_gen_sim);
    /** save outpot of goodness fit test*/
    virtual void set_GoodnessFit(int Good, long double D_n, long double cumD_n);
    /** initialize and save the empirical satisfaction index (function lambda)*/
    virtual void s_F_lambda_r(std::vector<Q_tau_stat> vector_lambda, int n_vect);
    void statF_lambda_r(s_lambda & vector_lambda);
    
//    friend void Statistical_data_single(E_coli* batterio, long double t, ofstream *file_statistic, int tipo_statistica);
    
    virtual void debugFunction();
    
};

#endif
