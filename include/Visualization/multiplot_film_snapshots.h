//
//  multiplot_film_snapshots.h
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 13/06/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef multiplot_film_snapshots_h
#define multiplot_film_snapshots_h

#include <iostream>

#include "sssr.h"
#include "Colori.h"
#include "Funz_C.h"

void gnuplot_Multiplot(Funz_C *f, int dim_col_t, int cont_gen_sim, std::string names_info,
                       double min_x, double max_x, double min_y, double max_y, double max_z, double max_fc);
int scriptMultiPlot(int risp_n, std::string title, double min_x, double max_x, double min_y, double max_y, double max_z, std::vector<int> frame_n, double Dt/*dt*(epsilon*epsilon)*/, int n_iter, int save_, int con_gen, int smaller = 0);
int scriptUpDownPer(std::string title, double T, int save, int smaller = 0);
void lunch_gnuplot(std::string name_file_gnu);

#endif /* multiplot_film_snapshots_h */
