//
//  histogram3DMultiThreadV2.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 22/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef histogram3DMultiThreadV2_hpp
#define histogram3DMultiThreadV2_hpp

#include <stdio.h>
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


void writeFunzCToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                      const int cont_sim, const int n_dx, const int n_dy,
                      const long double min_x, const long double min_y,
                      const long double dx, const long double dy,
                      const int n_x_min, const int n_x_max,
                      const int n_y_min, const int n_y_max,
                      long double& maxC,
                      const long double Dt,
                      Funz_C *f);

void startThred_writeHist(const int start_for, const int end_for, const int update_for,
                          const int cont_sim, const int n_c, const int n_dx, const int n_dy,
                          const long double dx, const long double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const long double min_x, const long double min_y,
                          long double delta_y_p, long double delta_x_p,
                          const long double delta_y_p_init,
                          const long double delta_x_p_init,
                          std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y,
                          int& max_z_local, bool display);

void writeHistToFile(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                     const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                     const long double& min_x, const long double& min_y,
                     const long double& dx, const long double& dy,
                     std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y,
                     const int& n_x_min, const int& n_x_max,
                     const int& n_y_min, const int& n_y_max,
                     int &max_z);

long double histogram_3D_gnuplotV2MultiThreadV2(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int risp_Max, int cont_sim, std::string name_file);


void writeFunC_andHist(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                       const int cont_sim, const int n_dx, const int n_dy,
                       const long double min_x, const long double min_y,
                       const long double dx, const long double dy,
                       const int n_x_min, const int n_x_max,
                       const int n_y_min, const int n_y_max,
                       long double& maxC,
                       const long double Dt,
                       Funz_C *f, int n_thread,
                       std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y,
                       int n_c, int& max_z, long double& maxC_temp);

#endif /* histogram3DMultiThreadV2_hpp */
