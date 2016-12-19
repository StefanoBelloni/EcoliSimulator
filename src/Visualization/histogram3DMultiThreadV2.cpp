//
//  histogram3DMultiThreadV2.cpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 22/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#include "histogram3DMultiThreadV2.hpp"
#include <vector>
#include "Funz_C.h"
#include <fstream>
#include "Colori.h"
#include <cmath>
#include <iostream>

#ifndef NO_M_THREAD
#include <thread>
#endif

#include "writeHistToFileMultiT.hpp"
#include "GlobalVariables.h"

#include <system_error>

#ifndef min
#define min_( a, b ) ( ((a) < (b)) ? (a) : (b) )
#endif

using namespace std;

// SISTEMARE MULTI-THREAD ...
#ifndef NO_M_THREAD

long double histogram_3D_gnuplotV2MultiThreadV2(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, vector<vector<long double> >& x,vector<vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int risp_Max, int cont_sim, string name_file_info)
{
    if (f->interact!=0){
        maxC=0.0;
    }
    long double maxC_temp = maxC;
    long double delta_x_p=dx; // estremi intervallo x histogram
    //    long double delta_y=0;
    long double delta_y_p=dy; // estremi intervallo y histogram
    //    int found=0; // se ho sistemato il batterio considerato --> setto la variabile pari a 1.
    int max_z=0;
    long double Dt=0.1;
//    long double T_f=1.0;
    int num_funz=0;
    int n_x_min=0;
    int n_y_min = 0;
    int n_x_max = 0;
    int n_y_max = 0;
    // Non è il file con le informazione richieste questo file!!!
    ifstream file_info(name_file_info.c_str());
//    ofstream file3D_hist;
//    ofstream file3D_c;
    cout << BOLDBLACK << "\nELABOAZIONE DATI FILMATO" << RESET<< endl;
//    cout << "Matrix for z created" << endl;
    // Recupero i dati dal file sulle caratteristiche tecniche.
    if (!file_info.is_open()) {
        cout << "Error opeining file ... \n";
        return -1;
    }
//    file_info >> Dt;
//    file_info >> num_funz;
//    file_info >> T_f;
    string title;
    int n_data = 1;
    
    file_info >> title;
    file_info >> num_funz;
    file_info >> Dt;
    file_info >> n_data; // const_salv
    Dt=Dt*n_data;
    file_info.close();
    
    cout << "Number Frames "<< dim_col_t << endl;
    if (risp_Max == 0){
        n_x_min = floor((min_x-f->min_x)/dx);
        n_y_min = floor((min_y-f->min_y)/dx);
        n_x_max = floor((f->max_x-min_x)/dx);
        n_y_max = floor((f->max_y-min_y)/dx);
        delta_x_p=f->min_x+dx/2;
        delta_y_p=f->min_y+dy/2;
    }else{
        delta_x_p=min_x+dx/2;
        delta_y_p=min_y+dy/2;
    }
#ifndef NO_M_THREAD
    int n_thread = min_(n_thread_available,std::thread::hardware_concurrency());
#else
    int n_thread = 1;
#endif 

    n_thread=n_thread/2;
    bool no_multithread;
    if (n_thread>1) {
        no_multithread = dim_col_t/n_thread<25;
    }else{
        no_multithread=true;
    }
    cout << "n_thread:= " << n_thread << endl;
    // solo Hist multi-Th
#if NO_M_THREAD
            writeFunC_andHist(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,min_x,min_y,dx,dy,n_x_min,n_x_max,n_y_min,n_y_max,std::ref(maxC_temp),Dt,f,n_thread,x,y,n_c,max_z,maxC_temp);
            maxC = maxC_temp;            
#else

    if (f->interact==0) {
        writeHistToFileMultiT(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,n_c,min_x,min_y,dx,dy,x,y,n_x_min,n_x_max,n_y_min,n_y_max,max_z,n_thread);
    }
    // posso avere diversi scenari:
    // 1 - one thread for function
    // 2 - many thread for every function.
    else{
        // 1 - one thread for function
        if (no_multithread) {
//            cout << "1 - one thread for function\n";
            std::thread th;
            th=std::thread(writeFunzCToFile,delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,min_x,min_y,dx,dy,n_x_min,n_x_max,n_y_min,n_y_max,std::ref(maxC_temp),Dt,f);
            writeHistToFileMultiT(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,n_c,min_x,min_y,dx,dy,x,y,n_x_min,n_x_max,n_y_min,n_y_max,max_z,n_thread);
            try {
                th.join();
            }catch (std::system_error &e) {
                cout << "join writeFunzCToFile" << endl;
                cout << "std::system_error: " << e.code().message() << endl;
                return -1;
            }
            maxC = maxC_temp;
        }
        // 2 - many thread for every function.
        else{
//            cout << "1 - many threads for every function\n";
            writeFunC_andHist(delta_y_p,delta_x_p,dim_col_t,n_salti_colonne,cont_sim,n_dx,n_dy,min_x,min_y,dx,dy,n_x_min,n_x_max,n_y_min,n_y_max,std::ref(maxC_temp),Dt,f,n_thread,x,y,n_c,max_z,maxC_temp);
            maxC = maxC_temp;            
        }
    }

#endif

//    maxC = maxC_temp;
    cout << "maxC = " << maxC << endl;
    cout << "\ncreation file 3D histograms terminated ... \n";
//    cout << "Press a key (long double) ... ";
//    cin >> maxC_temp;
//    cin >> maxC_temp;
    //    cout << "max_z = " << max_z << endl;
    
    return max_z;
}



//use all threads

/*! \brief write funz and hist to File using all the threads available
 */

void writeFunC_andHist(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                       const int cont_sim, const int n_dx, const int n_dy,
                       const long double min_x, const long double min_y,
                       const long double dx, const long double dy,
                       const int n_x_min, const int n_x_max,
                       const int n_y_min, const int n_y_max,
                       long double& maxC,
                       const long double Dt,
                       Funz_C *f, int n_thread,
                       vector<vector<long double> >& x,vector<vector<long double> >& y,
                       int n_c, int& max_z, long double& maxC_temp){

    
    //*************************************************************************************
    //
    //                  STRAT FROM HERE
    //
    //*************************************************************************************
    
    
    //*************************************************************************************
    // FUNZ HIST
    //*************************************************************************************
    
    //            cout << "writeHistToFileMultiThread thread ...\n";
    
    vector<std::thread> th;
    
    bool display = false;
    
    if (n_thread==0) {
        n_thread=1;
        display = true;
    }
    
    const long double delta_y_p_init = delta_y_p;
    const long double delta_x_p_init = delta_x_p;
    
    
    vector<int> max_z_local(n_thread);
    
    
    int start_for=0, end_for = 0, update_for=n_salti_colonne;
    int increaseThread;
    
    increaseThread = dim_col_t/n_thread;
    
    if (increaseThread==0) {
        cout << BOLDRED <<"Error ... something went wrong ... sorry" << RESET << endl;
        return ;
    }
    
    for (int i=0; i<n_thread-1; i++) {
        end_for+=increaseThread;
        
        //                cout << "**************************************" << endl
        //                << " funz h" << endl
        //                << "thread n. " << i << endl
        //                << "start_for = " << start_for << endl
        //                << "end_for = " << end_for << endl
        //                << "**************************************" << endl;
        
        th.push_back(std::thread(startThred_writeHist,start_for,end_for,update_for,cont_sim, n_c, n_dx, n_dy,
                                 dx, dy,
                                 n_x_min, n_x_max,
                                 n_y_min, n_y_max,
                                 min_x, min_y,
                                 delta_y_p, delta_x_p,
                                 delta_y_p_init,
                                 delta_x_p_init,
                                 std::ref(x),std::ref(y),
                                 std::ref(max_z_local[i]),(i==0)));
        start_for=end_for;
        
        
    }
    
    //            cout << "**************************************" << endl
    //            << " funz h" << endl
    //            << "thread main " << endl
    //            << "start_for = " << start_for << endl
    //            << "end_for = " << dim_col_t-1 << endl
    //            << "**************************************" << endl;
    
    
    
    
    th.push_back(std::thread(startThred_writeHist,start_for,dim_col_t-1,update_for,cont_sim, n_c, n_dx, n_dy,dx, dy,
                             n_x_min, n_x_max,
                             n_y_min, n_y_max,
                             min_x, min_y,
                             delta_y_p, delta_x_p,
                             delta_y_p_init,
                             delta_x_p_init,
                             std::ref(x),std::ref(y),
                             std::ref(max_z_local[n_thread-1]), display));
    
    
    
    
    
    //*************************************************************************************
    // FUNZ C
    //*************************************************************************************
    
    //            cout << "writeHistToFileMultiThread thread ...\n";
    //
    //    if (n_thread==0) {
    //        n_thread=1;
    //    }
    
    //             const long double delta_y_p_init = delta_y_p;
    //             const long double delta_x_p_init = delta_x_p;
    
    
    vector<long double> max_C_local(n_thread);
    //             vector<thread> th;
    
    
    start_for=0; end_for = 0; update_for=n_salti_colonne;
    //             int increaseThread;
    
    increaseThread = dim_col_t/n_thread;
    
    if (increaseThread==0) {
        cout << BOLDRED <<"Error ... something went wrong ... sorry" << RESET << endl;
        return;
    }
    
    for (int i=0; i<n_thread-1; i++) {
        end_for+=increaseThread;
        
        //                cout << "**************************************" << endl
        //                << " funz c" << endl
        //                << "thread n. " << i << endl
        //                << "start_for = " << start_for << endl
        //                << "end_for = " << end_for << endl
        //                << "**************************************" << endl;
        
        th.push_back(std::thread(startThred_writeFunC,start_for, end_for, update_for, cont_sim, dx, dy, n_x_min, n_dx+n_x_max, n_dy+n_y_min, n_y_max, min_x, min_y, delta_y_p, delta_x_p, delta_y_p_init, delta_x_p_init, Dt, f, std::ref(max_C_local[i])));
        
        start_for=end_for;
        
        
    }
    
    //            cout << "**************************************" << endl
    //            << " funz c" << endl
    //            << "thread main " << endl
    //            << "start_for = " << start_for << endl
    //            << "end_for = " << dim_col_t-1 << endl
    //            << "**************************************" << endl;
    
    
    startThred_writeFunC(start_for, dim_col_t-1, update_for, cont_sim, dx, dy, n_x_min, n_dx+n_x_max, n_dy+n_y_min, n_y_max, min_x, min_y, delta_y_p, delta_x_p, delta_y_p_init, delta_x_p_init, Dt, std::ref(f), std::ref(max_C_local[n_thread-1]));
    
    //****************************************
    // JOIN ...
    
    for (unsigned int i = 0; i<th.size(); i++) {
        //                cout << "funz ... " << endl;
        //                cout << "th["<<i<<"].join();" << endl;
        try{
            th[i].join();
        }catch (std::system_error &e) {
            cout << "funz ... " << endl;
            cout << "th["<<i<<"].join();" << endl;
            cout << "error:" << endl;
            cout << "std::system_error: " << e.code().message() << endl;
            return;
        }
    }
    
//    cout << "Ho finito gli istogrammi !" << endl;
    
    max_z=0;
    
    for (int i=0; i<n_thread; i++) {
        max_z=max(max_z, max_z_local[i]);
    }
    
    maxC_temp = 0.0;
    
    for (int i=0; i<n_thread; i++) {
        maxC_temp=max(maxC_temp, max_C_local[i]);
    }
    
}

#endif
