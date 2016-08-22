//
//  writeHistToFileMultiT.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 21/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef writeHistToFileMultiT_hpp
#define writeHistToFileMultiT_hpp

#include <stdio.h>
#include <vector>

#include "Funz_C.h"

//***********************
// HISTOGRAM
//***********************

void writeHistToFileMultiT(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonne,
                           const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                           const long double& min_x, const long double& min_y,
                           const long double& dx, const long double& dy,
                           std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y,
                           const int& n_x_min, const int& n_x_max,
                           const int& n_y_min, const int& n_y_max,
                           int &max_z, int n_thread = 0);


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
                          int& max_z_local, bool display = false);


//***********************
// FUNZIONE C
//***********************


void writeFunzCToFileMultiT(long double delta_y_p, long double delta_x_p, int dim_col_t, int n_salti_colonn,
                            const int cont_sim, const int n_dx, const int n_dy,
                            const long double min_x, const long double min_y,
                            const long double dx, const long double dy,
                            const int n_x_min, const int n_x_max,
                            const int n_y_min, const int n_y_max,
                            long double& maxC,
                            const long double Dt,
                            Funz_C *f,
                            int n_thread);

void startThred_writeFunC(const int start_for, const int end_for, const int update_for,
                          const int cont_sim,
                          const long double dx, const long double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const long double min_x, const long double min_y,
                          long double delta_y_p, long double delta_x_p,
                          const long double delta_y_p_init,
                          const long double delta_x_p_init,
                          long double Dt, Funz_C* f, long double& maxC);


#endif /* writeHistToFileMultiT_hpp */
