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
#include <thread>
#include "writeHistToFileMultiT.hpp"


void writeFunzCToFile(double delta_y_p, double delta_x_p, int dim_col_t, int n_salti_colonne,
                      const int cont_sim, const int n_dx, const int n_dy,
                      const double min_x, const double min_y,
                      const double dx, const double dy,
                      const int n_x_min, const int n_x_max,
                      const int n_y_min, const int n_y_max,
                      double& maxC,
                      const double Dt,
                      Funz_C *f);

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
                          int& max_z_local, bool display);

void writeHistToFile(double delta_y_p, double delta_x_p, int dim_col_t, int n_salti_colonne,
                     const int& cont_sim, const int& n_dx, const int& n_dy, const int& n_c,
                     const double& min_x, const double& min_y,
                     const double& dx, const double& dy,
                     std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y,
                     const int& n_x_min, const int& n_x_max,
                     const int& n_y_min, const int& n_y_max,
                     int &max_z);

double histogram_3D_gnuplotV2MultiThreadV2(double max_x, double max_y, double min_x,double min_y, int n_dx, int n_dy, double dx, double dy, std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, double &maxC, int risp_Max, int cont_sim, std::string name_file);


void writeFunC_andHist(double delta_y_p, double delta_x_p, int dim_col_t, int n_salti_colonne,
                       const int cont_sim, const int n_dx, const int n_dy,
                       const double min_x, const double min_y,
                       const double dx, const double dy,
                       const int n_x_min, const int n_x_max,
                       const int n_y_min, const int n_y_max,
                       double& maxC,
                       const double Dt,
                       Funz_C *f, int n_thread,
                       std::vector<std::vector<double> >& x,std::vector<std::vector<double> >& y,
                       int n_c, int& max_z, double& maxC_temp);

#endif /* histogram3DMultiThreadV2_hpp */
