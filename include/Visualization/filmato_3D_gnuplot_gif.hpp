//
//  filmato_3D_gnuplot_gif.hpp
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 14/06/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//

#ifndef filmato_3D_gnuplot_gif_hpp
#define filmato_3D_gnuplot_gif_hpp

#include <iostream>
#include <vector>

void funz_clear();
void funz_clearAll();
int scriptMultiPlot_gif(int risp_n, std::string title, long double min_x, long double max_x, long double min_y, long double max_y, long double max_z, std::vector<int> frame_n, long double Dt/*dt*(epsilon*epsilon)*/, int n_iter, int save_, int con_gen, int smaller = 0);
void lunch_gnuplot(std::string name_file_gnu);
int scriptUpDownPer_gif(std::string title, long double T, int save, int smaller = 0);
int scriptFilmato3Dgnuplot_gif(long double Dt/*dt*(epsilon*epsilon)*/, long double maxX, long double maxY, long double minX, long double minY, long double max_z, long double max_fc, int dim_col_t, int save_, int cont_sim);
int writeLog(std::string what, std::string msg);


#endif /* filmato_3D_gnuplot_gif_hpp */
