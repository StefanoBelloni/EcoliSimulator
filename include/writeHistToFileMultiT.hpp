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

void writeHistToFileMultiT(double delta_y_p, double delta_x_p, int dim_col_t, int n_salti_colonne,
                           const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                           const double& min_x, const double& min_y,
                           const double& dx, const double& dy,
                           std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y,
                           const int& n_x_min, const int& n_x_max,
                           const int& n_y_min, const int& n_y_max,
                           int &max_z, int n_thread = 0);


void startThred_writeHist(const int start_for, const int end_for, const int update_for,
                          const int cont_sim, const int n_c, const int n_dx, const int n_dy,
                          const double dx, const double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const double min_x, const double min_y,
                          double delta_y_p, double delta_x_p,
                          const double delta_y_p_init,
                          const double delta_x_p_init,
                          std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y,
                          int& max_z_local, bool display = false);


//***********************
// FUNZIONE C
//***********************


void writeFunzCToFileMultiT(double delta_y_p, double delta_x_p, int dim_col_t, int n_salti_colonn,
                            const int cont_sim, const int n_dx, const int n_dy,
                            const double min_x, const double min_y,
                            const double dx, const double dy,
                            const int n_x_min, const int n_x_max,
                            const int n_y_min, const int n_y_max,
                            double& maxC,
                            const double Dt,
                            Funz_C *f,
                            int n_thread);

void startThred_writeFunC(const int start_for, const int end_for, const int update_for,
                          const int cont_sim,
                          const double dx, const double dy,
                          const int n_x_min, const int n_x_max,
                          const int n_y_min, const int n_y_max,
                          const double min_x, const double min_y,
                          double delta_y_p, double delta_x_p,
                          const double delta_y_p_init,
                          const double delta_x_p_init,
                          double Dt, Funz_C* f, double& maxC);


#endif /* writeHistToFileMultiT_hpp */
