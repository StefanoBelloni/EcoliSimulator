//
//  GnuplotGlobal.h
//  Ecoli_3.1.4
//
//  Created by Stefano Belloni on 09/07/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <string>

/** string pass to system to open gnuplot*/
extern std::string gnuplotOpen;
/** string pass to system to set terminal just to plot*/
extern std::string gnuplotSetTerminalPlot;
/** string pass to system to set terminal to save .eps*/
extern std::string gnuplotSetTerminalSave_eps;
/** string pass to system to set terminal to save .png and create to movie*/
extern std::string gnuplotSetTerminalSave_png;
/** string pass to system to set terminal to save .gif and create to movie*/
extern std::string gnuplotSetTerminalSave_gif;
//extern std::string apngas_;

extern const char* homeDir;

extern std::string firefox_path;