//
//  gnuplot_3D.h
//  EColi_2.4
//
//  Created by Stefano Belloni on 22/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//


#include <vector>
#include "Funz_C.h"


long double histogram_3D_gnuplot(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, std::vector<std::vector<long double> > x,std::vector<std::vector<long double> > y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, std::string name_file);
long double histogram_3D_gnuplotV2(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int MaxDom, int cont_sim, std::string name_file);
long double histogram_3D_gnuplotV2MultiThread(long double max_x, long double max_y, long double min_x,long double min_y, int n_dx, int n_dy, long double dx, long double dy, std::vector<std::vector<long double> >& x,std::vector<std::vector<long double> >& y, int n_c, int dim_col_t, int n_salti_colonne, Funz_C *f, long double &maxC, int MaxDom, int cont_sim, std::string name_file);

void filmato_3D_gnuplot(std::string file_info[], long double max_x, long double max_y, long double min_x,long double min_y, long double max_z, int dim_col_t, Funz_C *f, int cont_gen_sim, long double MaxC);
void baricentro_plot(std::string name,std::vector<std::vector<long double> > &x_t,std::vector<std::vector<long double> > &y_t,int n_c,int dim_col_t, int cont_gen_sim = 0);
void gnuplot_large_population_interacting(std::string file_info[], std::string name_dyn, long double T_f, int n_c, int dim_col_t, std::string names, Funz_C *f, int cont_gen_sim, long double maxC);
void lunch_gnuplot(std::string name_file_gnu);
void Histogram_Dynamic(std::string name, std::string name_dynamic, int sim_cont);
void funz_clear();
int percSignFunzC(std::vector< std::vector<long double> > c_t, int n_c, int dim_col_t, std::string nameInfo);


