//
//  Implementatiuon_Statistical_Analysis.cpp
//  Ecoli_4.1.1
//
//  Created by Stefano Belloni on 28/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

//**********************************************
//**********************************************

/*   WHICH STATISICAL ANALYSIS IS PERFORMED ?
 *   Q_tau_vect è così strutturato:
 *      
 *   Q       q_min q_min+dq q_min+2*dq ... 
 *   m        m_1    m_2       m_3     ...
 *   var      var_1  var_2     var_3   ...
 *   X-       X-_1   X-_2      X-_3    ...     <---(pag 7)   
 *   n_rec    N_1    N_2       N_3     ...
 */


//**********************************************
//**********************************************

#include <iostream>
#include "E_Coli.h"
#include <vector>
#include <cmath>
#include <iomanip>

#include "Q_tau_stat.h"
#include "Declar_funz.h"
#include "GlobalVariables.h"
#include "StatisticalAnalysis.h"
#include "Colori.h"

#include "ParameterEstimation_E_Coli.h"
#include "ParameterEstimation_CV_rIG_tExp.h"
#include "ParameterEstimation_CV_rExp_tExp.h"

using namespace std;

/** 
 *  Base function to the statistical analysis.
 *  It is used to set the object Bacteria that are suited for the parameter estimation: i.e. instead of claculating lambda(Q(t))
 *  we have the vector [lambda(Q_min) ... lambda(0) ... lambda(Q_max)] calculate the index of the current lambda and return the proper value for lambda.
 *  The parameter are used in the different function to simulate or take the data from file whose name is passed as string
 *  MODIFIE IT IF YOU ADD NEW MODEL, at least add as many component as the number of new model as new ParameterEstimation_E_coli if  the ParameterEstimation class is not implemented
 */

int Statistical_Analysis(string name_file_dati, string name_info_file, vector<int> which_compare, int n_compare, int &cont_gen_sim, string &versione_Matlab, int n_c)
/*   WHICH STATISICAL ANALYSIS IS PERFORMED ?
 *   Q_tau_vect è così strutturato:
 *      
 *   Q       q_min q_min+dq q_min+2*dq ... 
 *   m        m_1    m_2       m_3     ...
 *   var      var_1  var_2     var_3   ...
 *   X-       X-_1   X-_2      X-_3    ...     <---(pag 7)   
 *   n_rec    N_1    N_2       N_3     ...
 */
{

    
    vector<Q_tau_stat> Q_tau_vect;
    long double tau_0_t_stima = 0.0L;
    vector<Funz_C* > f;
    vector<E_coli*> batteri_stimati;

    //****************************************************************************
    //  SET BATTERI & FUNZ_C & NAME FILES
    //****************************************************************************
    
    // MODIFIE IT IF YOU ADD NEW MODEL, at least add as many component as the number of new model as new ParameterEstimation_E_coli if  the ParameterEstimation class is not implemented
    
    batteri_stimati.push_back(new ParameterEstimation_E_coli);
    batteri_stimati.push_back(new ParameterEstimation_CV_rExp_tExp);
    batteri_stimati.push_back(new ParameterEstimation_CV_rIG_tExp);
    batteri_stimati.push_back(new ParameterEstimation_E_coli);
    batteri_stimati.push_back(new ParameterEstimation_E_coli);
    batteri_stimati.push_back(new ParameterEstimation_E_coli);
    batteri_stimati.push_back(new ParameterEstimation_E_coli);
    
    f.push_back(new Funz_C);
    f.push_back(new Funz_C_Par);
    f.push_back(new Funz_C_Inter);
    
    string names_Ecoli_mod[3]; 
    string names_indice_mod;
    string names_tau_mod[2];
    string names_file_dyn_mod;
    string names_info_mod[4];
    string names_jumps[5];
    
    //****************************************************************************
    //                VARIABILI PER INIZIALIZZARE I PARAMETRI
    //****************************************************************************
    
    long double dt=0.01L;                       // Time steps
    long double T_f=1.0L;                         // Tempo finale
    long double x0[2]={0.0L,0.0L};                   // Valori deterministici iniziali
    int num_dist=1;                       // Numero distribuzione iniziale
    long double Raggio=0.0L;                      // Raggio distribuzioni
    int delta_dist=1;                     // Numero sorgente
    int const_salv=1;                     // Ogni quanto tempo (cont_salv*dt) salvo
    int sel_prog=1;
    int tipo_funz_c_class=0;
    int ftipo_response_c=1;
    long double fRC_0=1.0L;
    long double fRC_1=1.0L;
    int fRC_q=0;
    
    GoodFit Test;
    long double D_n=0.0L;
    long double cumD_n=0.0L;
    int goodnessFit=0;
    s_lambda lambda;

    for (int i=0; i<n_compare; i++) {
        
        // AUTOMATIC
        
        if (automatic_==2)
            goodnessFit = DynFitting(name_file_dati, tau_0_t_stima, lambda, which_compare[i], D_n, cumD_n);
            
        // MANUALLY ADAPTED 
            
        if (automatic_==0)
            goodnessFit = ManualFitting(name_file_dati,tau_0_t_stima,lambda,which_compare[i],D_n,cumD_n);
            
        
        if (automatic_!=1) { 
            
            // To simulate the population of bacteria whose parameter are estimated I read from the file with this function
            
            inizializzazione_parametri(sel_prog,T_f,n_c,x0,num_dist,Raggio,delta_dist,const_salv,dt,name_info_file, f, tipo_funz_c_class,ftipo_response_c,fRC_0,fRC_1,fRC_q);
            
            // I set the other parameter
            
            string buffer=name_file_dati;
            buffer.erase(buffer.end()-4, buffer.end());
            batteri_stimati[which_compare[i]]->Tipo_batterio+=buffer;
            batteri_stimati[which_compare[i]]->statF_lambda_r(lambda);
            MovingLeastSquares(batteri_stimati[which_compare[i]]->s_lambda_r);
            batteri_stimati[which_compare[i]]->set_response(ftipo_response_c, fRC_0, fRC_1, fRC_q);
            batteri_stimati[which_compare[i]]->Tau_t(tau_0_t_stima);
            batteri_stimati[which_compare[i]]->set_GoodnessFit(goodnessFit, D_n, cumD_n);

        }
    }

    // simulate idipendent population ... normally
  
	cout << "Implementatiuon_Statistical_Analysis: Simulation independent l. 152\n";   
    int error_indep_pop = independent_population(f[tipo_funz_c_class], n_compare, names_Ecoli_mod, names_indice_mod, names_tau_mod, names_file_dyn_mod, names_info_mod,  sel_prog, which_compare, batteri_stimati,  T_f, x0,  dt,  n_c,  Raggio,  delta_dist,  num_dist,  const_salv, versione_Matlab, names_jumps,cont_gen_sim, 0 /*=stat_*/);
    
    if (error_indep_pop==-1) {
        cout << BOLDRED << "Error in the simulation (error_indep_pop) " << RESET << endl;
        string msg("Error in the simulation.");
        //            msg+=read;
        writeLog("ERROR",msg);
        return -1;
    }

    // clean the new ...
    for (unsigned int i=0; i < batteri_stimati.size(); i++)
        delete batteri_stimati[i];
   
    for (unsigned int i = 0; i < f.size(); i++)
        delete f[i];

    return 0;
    
}

//**********************************

/**
 * THis function take the vector_lambda of the statistics related to Q and retun the proper value for the extimated response function lambda
 * According to which model I choose, if run is exponentially distributed or is Inverse gaussian
 * @param s_lambda_r estimated value for lambda
 * @param vector_lambda vector of the statistic generated
 * @param n_vect number of discrete value for Q
 * @param tipo_sim model to be used
 */

void create_lambda(s_lambda &s_lambda_r, vector<Q_tau_stat> &vector_lambda, int n_vect, int tipo_sim)
{
    long double Q_,dQ_;
    
    s_lambda_r.lambda.resize(n_vect);
    s_lambda_r.syntetic_indeX.resize(n_vect);
    s_lambda_r.n_data.resize(n_vect);
    
    s_lambda_r.dQ=vector_lambda[1].Q-vector_lambda[0].Q;
    dQ_=s_lambda_r.dQ;
    s_lambda_r.Q_max=vector_lambda[n_vect-1].Q;
    s_lambda_r.Q_min=vector_lambda[0].Q;
    Q_=s_lambda_r.Q_min;
    s_lambda_r.n_records=n_vect;
    
    switch (tipo_sim) {
        {
            case 2:

            s_lambda_r.sigma.resize(n_vect);
            
            for (int i=0; i<n_vect; i++) {
                
                s_lambda_r.syntetic_indeX[i]=Q_;
                
                // If no record we use a default function
                
                if (vector_lambda[i].n_rec==0) {
                    s_lambda_r.sigma[i] = 1.6;
                    s_lambda_r.lambda[i] = (1-2/3.141592654*atan(3.141592654*Q_/2)/.8);
                }else {
                    
                    s_lambda_r.n_data[i] = vector_lambda[i].n_rec;
                    s_lambda_r.lambda[i]=1/vector_lambda[i].mean;    

                    if (s_lambda_r.n_data[i]>3) {
                        s_lambda_r.sigma[i] = vector_lambda[i].V_IG();
                    }else {
                        s_lambda_r.sigma[i]=1.6;
                    }                    
                }
                
                if (Q_>=-dQ_ && Q_<=dQ_) {
                    s_lambda_r.pos_steady=i;                
                }
                
                Q_+=dQ_;
                
            }
            
            
            break;
            
        }
            
            
            
        {
        case 1:
            
//            cout << "s_lambda_r giusta ...\n";
            
            s_lambda_r.sigma.resize(n_vect);
            
            for (int i=0; i<n_vect; i++) {
                
                s_lambda_r.syntetic_indeX[i]=Q_;
                s_lambda_r.sigma[i]=0.0;
                
//                s_lambda_r.lambda[i]=(1-2/3.141592654*atan(3.141592654*Q_/2))/.8;
                
                // If no record we use a default function
                
                if (vector_lambda[i].n_rec==0) {
//                    index_Zero_Rec.push_back(i);
                    
                    s_lambda_r.lambda[i]=(1-2/3.141592654*atan(3.141592654*Q_/2)/.8);
//                    s_lambda_r.lambda[i]=                    
                    
                }else{
                    
                    s_lambda_r.n_data[i] = vector_lambda[i].n_rec;
//                    cout << "Q = " << Q_ << "n_rec = " << s_lambda_r.n_data[i] << endl;
//                    s_lambda_r.lambda[i]=1/vector_lambda[i].mean;            
//                    s_lambda_r.lambda[i]=vector_lambda[i].max_tau/vector_lambda[i].n_rec;
                    s_lambda_r.lambda[i]=vector_lambda[i].n_rec/vector_lambda[i].max_tau;
                    
                }
                
                if (Q_>=-dQ_ && Q_<=dQ_) {
                    s_lambda_r.pos_steady=i;                
                }
                
                Q_+=dQ_;
                
            }
            
            break;
    }
        default:
            break;
    }
    
    
    
    
    
}

//**********************************

/**
 * This function update the result of the test if the new parameters chosen improve it.
 */

void updateTest(GoodFit &Test, long double cumD_n, long double D_n, long double q_max, long double q_min, long double dq){
    
    if (cumD_n<Test.cumD_n && D_n<Test.D_n) {
        Test.cumD_n=cumD_n;
        Test.D_n=D_n;
        Test.Q_max=q_max;
        Test.Q_min=q_min;
        Test.dQ = dq;
    }else if (cumD_n==Test.cumD_n){
        if (D_n<Test.D_n) {
            Test.cumD_n=cumD_n;
            Test.D_n=D_n;
            Test.Q_max=q_max;
            Test.Q_min=q_min;
            Test.dQ = dq;
        }
    }
    
    
}


//***********************************

/**
 * Function that perform the fitting and creation of the statistic related to the file name_file_dati.
 * Dyn fitting produce a series of step to determin a good balance for the parameters, such as the number of discrete value of Q
 * its range, how much leave out (95% of the values) etc.
*/

int DynFitting(string &name_file_dati, long double &tau_0_t_stima, s_lambda &lambda, int which_compare, long double &D_n, long double &cumD_n) {
    int noch_eine=0;
    int n_iterate=0;
    int n_stat_tamb=0;
    long double dq=0.01L;
    int q_0=0;
    vector<Q_tau_stat> Q_tau_vect;
    long double q_max=-1000L, q_min=1000L;
    
    GoodFit Test;
    
    long double q_max_s=-10000L;
    long double q_min_s= 10000L;
    long double q_max_95=-10000L;
    long double q_min_95= 10000L;
    long double quantile_95=0.0;
    int q_95=0;
    
    int tot=0;
    int i_q=0;
    int j_q=0;
    
    int error_plot=0;
    int goodnessFit=0;
    int n_q=set_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,q_0);
    
//    bool if_cond=0;
    
    cout << "Adapt dinamically the statistical fitting ... \n";
    while (noch_eine==0) {

        funz_clear();
        
        lambda.reset_lambda();

        cout <<BOLDRED<<"\n****************************\n";
        cout << "Statistical_Analysis \n";
        cout << "Iterata n." << n_iterate << endl;
        timestamp();
        cout <<"****************************\n"<<RESET;
        
        cout << "n_q = " << n_q << endl;
        
        constract_Q_tau_vect(dq,q_max,q_min,Q_tau_vect,name_file_dati, n_stat_tamb,n_q,tau_0_t_stima, q_max_s, q_min_s);
        tau_0_t_stima=tau_0_t_stima/n_stat_tamb;
        
        if (n_iterate==6) 
			error_plot= plot_tau_Q(name_file_dati, Q_tau_vect, automatic_, n_iterate);
        
        if (error_plot!=0) {
            cout << "Error opening the Files\n";
            string msg("Error opening the Files.");
            //            msg+=read;
            writeLog("ERROR",msg);
            return -1;
        }else {
            remove("statistical_data.dat");
            remove("statistical_plot.gnu");
            remove("file_gnu.gnu");
        }
        
        cout << "The calculated max und min value for Q are: [Q_m,Q_M] = ["<<q_min_s <<","<<q_max_s<<"]"<< endl;
        
        
        i_q=0;
        j_q=0;
        tot=0;
        q_95=Q_tau_vect[q_0].n_rec;
        quantile_95=n_stat_tamb*(100-(5-n_iterate))/100;
        
        while (q_95<=quantile_95 && tot<n_stat_tamb) {
            if (i_q*dq<q_max_s) {
                if (i_q+q_0<n_q) {
                    q_95 += Q_tau_vect[i_q+q_0].n_rec;
                    i_q++;
                }
            }
            
            if (-j_q*dq>q_min_s) {
                if (j_q+n_q>=0) {
                    q_95 += Q_tau_vect[i_q+q_0].n_rec;
                    j_q++;
                }
            }
            tot++;
        }
        
        q_max_95=i_q*dq;
        q_min_95=-j_q*dq;
        
        cout << "The calculated 95% max und min value for Q are: [Q_m,Q_M] = ["<<q_min_95 <<","<<q_max_95<<"]"<< endl;
        
        //funz_clear();
        
        create_lambda(lambda, Q_tau_vect, n_q,which_compare);
        
        cout << "lambda n_rec = " << lambda.n_records << endl;
        cout << "lambda pos steady = "<< lambda.pos_steady << endl;
        
        if (n_iterate==6) {
            plot_lambda(name_file_dati, lambda, automatic_, n_iterate+6);
            remove("MLQ_data.dat");
            remove("MLQ_plot.gnu");
        }
        
        
        //                MovingLeastSquares(automatic_, lambda);     // moving
        //                MovingLeastSquares(automatic_, lambda,0);   // not moving
        MovingLeastSquares(lambda);                 // n_data-weight
        
        if (n_iterate==6) {
            error_plot= plot_lambda(name_file_dati, lambda, automatic_, n_iterate);
        }
        
        
        D_n=0.0L;
        cumD_n=0.0L;
        goodnessFit = GoodnessFit_PP(name_file_dati, lambda , n_stat_tamb, n_iterate, D_n, cumD_n);
        
        if (goodnessFit==0) {
            n_iterate=6;
            //noch_eine=1;
        }else {
            
            updateTest(Test, cumD_n, D_n, q_max, q_min, dq);
        }
        
//        if_cond = (goodnessFit!=0);
        
        
        //***************************************************************************
        // max, max:dq*10, max:dq/50, max95, max95:dq*10 0,1,2,3,4 -> 5 beste!!!
        
        switch (n_iterate) {
        
            case 0:
            {
                cout << "MAX ... "<< endl;
                
                q_max = q_max_s;
                q_min = q_min_s;
                
                n_iterate++;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,6, n_stat_tamb,q_0);
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
            
            case 1:
            {
                cout << "MAX:dQ*10 ... "<< endl;
                
                q_max = q_max_s;
                q_min = q_min_s;
                dq=dq*10;
                n_iterate++;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,7, n_stat_tamb,q_0);
                
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
                
            case 2:
            {
                cout << "MAX:dQ/2 ... "<< endl;
                
                q_max = q_max_s;
                q_min = q_min_s;
                
                dq=dq/20.0L;
                n_iterate++;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,7, n_stat_tamb,q_0);
                
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
                
            case 3:
            {
                q_max = q_max_95;
                q_min = q_min_95;
                
                cout << "MAX95 ... "<< endl;
                
                n_iterate++;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,6, n_stat_tamb,q_0);
                
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
        
            case 4:
            {
                cout << "MAX95:dQ*10 ... "<< endl;
                
                q_max = q_max_95;
                q_min = q_min_95;
                n_iterate++;
                dq=dq*10.0L;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,7, n_stat_tamb,q_0);
                
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
                
            case 5:
            {
                cout << "BEST TEST ... "<< endl;
                
                q_max = Test.Q_max;
                q_min = Test.Q_min;
                dq=Test.dQ;
                
                n_iterate++;
                n_q=reset_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,7, n_stat_tamb,q_0);
                
                n_stat_tamb=0;
                tau_0_t_stima=0.0L;
                noch_eine=0;
            }
                break;
                
            default:
            {
                noch_eine=1;
            }
                break;
        }
        
        cout << "Iteration : " << n_iterate << endl;
    }
    
    return goodnessFit;
}

//***********************************

/**
 * Function that perform the fitting and creation of the statistic related to the file name_file_dati.
 * ManualFitting allows you to chose the parameters, such as the number of discrete value of Q
 * its range, how much leave out (95% of the values) etc.
 */

int ManualFitting(string &name_file_dati, long double &tau_0_t_stima, s_lambda &lambda, int which_compare, long double &D_n, long double &cumD_n) {
    
    
    int noch_eine=0;
    int n_iterate=0;
    int n_stat_tamb=0;
    long double dq=0.01L;
    int q_0=0;
    vector<Q_tau_stat> Q_tau_vect;
    long double q_max=-1000L, q_min=1000L;
    
    GoodFit Test;
    
    long double q_max_s=-10000L;
    long double q_min_s= 10000L;
    
    //    long double D_n=0.0;
    //    long double cumD_n=0.0;
    
    long double q_max_95=-10000L;
    long double q_min_95= 10000L;
    long double quantile_95=0.0L;
    int q_95=0;
    
    int tot=0;
    int i_q=0;
    int j_q=0;
    
    int error_plot=0;
    int goodnessFit=0;
    int n_q=set_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,q_0);
    
    bool if_cond=0;
    
    // Adapt dinamically the statistical fitting
    cout << "\nAdapt manually the statistical fitting ... \n";
    
    while (noch_eine==0) {
        constract_Q_tau_vect(dq,q_max,q_min,Q_tau_vect,name_file_dati, n_stat_tamb,n_q,tau_0_t_stima, q_max_s, q_min_s);
        tau_0_t_stima=tau_0_t_stima/n_stat_tamb;
        
        error_plot= plot_tau_Q(name_file_dati, Q_tau_vect, automatic_, n_iterate);
        
        if (error_plot!=0) {
            cout << "Error Plotting tau_Q\n";
            string msg("Error Plotting tau_Q.");
//            msg+=read;
            writeLog("ERROR",msg);
        }
        
        funz_clear();
        
        create_lambda(lambda, Q_tau_vect, n_q,which_compare);
        plot_lambda(name_file_dati, lambda, automatic_, n_iterate+6);
        remove("MLQ_data.dat");
        remove("MLQ_plot.gnu");
        MovingLeastSquares(lambda);                 // n_data-weight
        error_plot= plot_lambda(name_file_dati, lambda, automatic_, n_iterate);
        goodnessFit = GoodnessFit_PP(name_file_dati, lambda , n_stat_tamb, n_iterate, D_n, cumD_n);
        
        if (error_plot!=0){
            cout << "Error opening the Files\n";
            string msg("Error openeing file for data fitting:");
            writeLog("ERROR",msg);
        }
        else {
            remove("statistical_data.dat");
            remove("statistical_plot.gnu");
            remove("file_gnu.gnu");
            
            remove("MLQ_data.dat");
            remove("MLQ_plot.gnu");
        }
        
        if (goodnessFit==0) {
            n_iterate=6;
            if_cond=1;
            
        }else{
            
            cout << "The calculated max und min value for Q are: [Q_m,Q_M] = ["<<q_min_s <<","<<q_max_s<<"]"<< endl;
            
            i_q=0;
            j_q=0;
            tot=0;
            q_95=Q_tau_vect[q_0].n_rec;
            quantile_95=n_stat_tamb*(100-(5-n_iterate))/100;
            
            while (q_95<=quantile_95 && tot<n_stat_tamb) {
                if (i_q*dq<=q_max_s) {
                    if (i_q+q_0<n_q) {
                        q_95 += Q_tau_vect[i_q+q_0].n_rec;
                        i_q++;
                    }
                }
                
                if (-j_q*dq>=q_min_s) {
                    if (j_q+n_q>=0) {
                        q_95 += Q_tau_vect[i_q+q_0].n_rec;
                        j_q++;
                    }
                }
                tot++;
            }
            
            q_max_95=i_q*dq;
            q_min_95=-j_q*dq;
            
            cout << "The calculated 95% max und min value for Q are: [Q_m,Q_M] = ["<<q_min_95 <<","<<q_max_95<<"]"<< endl;
            
            cout << "Do you want to try other setting for Q,dQ etc ...? \npress 0 for yes, 1 for no ";
            cin >> if_cond;
            
        }
        if (if_cond==0) {
            n_iterate++;
            n_q=set_parameter_Q_tau(dq,q_max,q_min,Q_tau_vect,q_0);
            n_stat_tamb=0;
            tau_0_t_stima=0.0;
            noch_eine=0;
        }else noch_eine=1;
        
        cout << "Iteration : " << n_iterate << endl;
        
    }
    
    return goodnessFit;
    
}

//***********************************
