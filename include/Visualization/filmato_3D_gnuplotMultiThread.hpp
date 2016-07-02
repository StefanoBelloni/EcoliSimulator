//
//  filmato_3D_gnuplotMultiThread.hpp
//  Ecoli_4.1.5
//
//  Created by Stefano Belloni on 21/05/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef filmato_3D_gnuplotMultiThread_hpp
#define filmato_3D_gnuplotMultiThread_hpp

#include <stdio.h>
#include <iostream>
#include <vector>

#include "Funz_C.h"

void funz_clear();

void filmato_3D_gnuplotMultiT(std::string names_info[],double max_x, double max_y, double min_x,double min_y, double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, double max_fc);

int scriptFilmato3DgnuplotMultiT(double Dt/*dt*(epsilon*epsilon)*/, double maxX, double maxY, double minX, double minY, double max_z, double max_fc, int dim_col_t, int save_, int cont_sim,int i = 0, int n_threadTot = 1);

int scriptFilmato3Dgnuplot(double Dt/*dt*(epsilon*epsilon)*/, double maxX, double maxY, double minX, double minY, double max_z, double max_fc, int dim_col_t, int save_, int cont_sim);

//int scriptMultiPlot(int risp_n, std::string title, double min_x, double max_x, double min_y, double max_y, double max_z, std::vector<int> frame_n, double Dt/*dt*(epsilon*epsilon)*/, int n_iter, int save_, int con_gen, int smaller = 0);
void lunch_gnuplot(std::string name_file_gnu);

//int scriptUpDownPer(std::string title, double T, int save, int smaller);

int lunchMultiThread3Dgnuplot(int n_thread, int cont_sim, bool last = false, int n_max = 0, int n_thread_tot = 1);
std::string setNamescript3DMultiT(int cont_sim, int nthread);

void deleteSCRIPT_GNUPLOTplay_videoMultiT(int cont_sim, int n_thread_tot);

int checkFrames(int n_thread_tot, int cont_sim, int n_max);

void filmato_3D_gnuplot_gif(std::string names_info[],double max_x, double max_y, double min_x,double min_y, double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, double max_fc);
#endif /* filmato_3D_gnuplotMultiThread_hpp */
