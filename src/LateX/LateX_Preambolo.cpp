//
//  LateX_Preambolo.cpp
//  Ecoli_3.1.1
//
//  Created by Stefano Belloni on 26/06/15.
/*This program is free software - GNU General Public License Verison 2*/
//

#include <iostream>
#include <fstream>
#include "Colori.h"

using namespace std;

/** This function write the preamble (packages, initial page)
*/

void LateX_Preambolo(ofstream &file1){
    
    
    //**************************************************************************************
    // TeX_Preambolo.txt
    //**************************************************************************************
    
    
    {
        file1 << "% !TEX TS-program = pdflatex " << endl 
        << "% !TEX encoding = UTF-8 Unicode " << endl 
        << " " << endl 
        << "% This is a simple template for a LaTeX document using the \"article\" class. " << endl 
        << "% See \"book\", \"report\", \"letter\" for other types of document. " << endl 
        << " " << endl 
        << "\\documentclass[11pt]{article} % use larger type; default would be 10pt " << endl 
        << " " << endl 
        << "\\usepackage[utf8]{inputenc} % set input encoding (not needed with XeLaTeX) " << endl 
        << " " << endl 
        << "%%% Examples of Article customizations " << endl 
        << "% These packages are optional, depending whether you want the features they provide. " << endl 
        << "% See the LaTeX Companion or other references for full information. " << endl 
        << " " << endl 
        << "%%% PAGE DIMENSIONS " << endl 
        << "\\usepackage{geometry} % to change the page dimensions " << endl 
        << "\\geometry{a4paper} % or letterpaper (US) or a5paper or.... " << endl
        << "\\usepackage{amsmath} " << endl
        << "% \\geometry{margin=2in} % for example, change the margins to 2 inches all round " << endl 
        << "% \\geometry{landscape} % set up the page for landscape " << endl 
        << "%   read geometry.pdf for detailed page layout information " << endl 
        << " " << endl 
        << "\\usepackage{graphicx} % support the \\includegraphics command and options " << endl 
        << " " << endl 
        << "% \\usepackage[parfill]{parskip} % Activate to begin paragraphs with an empty line rather than an indent " << endl 
        << " " << endl 
        << "%%% PACKAGES " << endl 
        << "\\usepackage{booktabs} % for much better looking tables " << endl 
        << "\\usepackage{array} % for better arrays (eg matrices) in maths " << endl 
        << "\\usepackage{paralist} % very flexible & customisable lists (eg. enumerate/itemize, etc.) " << endl 
        << "\\usepackage{verbatim} % adds environment for commenting out blocks of text & for better verbatim " << endl 
        << "\\usepackage[nomarkers,figuresonly]{endfloat}" << endl
        << "\\usepackage{subfig} % make it possible to include more than one captioned figure/table in a single float " << endl 
        << "% These packages are all incorporated in the memoir class to one degree or another... " << endl 
        << " " << endl 
        << "%%% HEADERS & FOOTERS " << endl 
        << "\\usepackage{fancyhdr} % This should be set AFTER setting up the page geometry " << endl 
        << "\\pagestyle{fancy} % options: empty , plain , fancy " << endl 
        << "\\renewcommand{\\headrulewidth}{0pt} % customise the layout... " << endl 
        << "\\lhead{}\\chead{}\\rhead{} " << endl 
        << "\\lfoot{}\\cfoot{\\thepage}\\rfoot{} " << endl 
        << " " << endl 
        << "%%% SECTION TITLE APPEARANCE " << endl 
        << "\\usepackage{sectsty} " << endl 
        << "\\allsectionsfont{\\sffamily\\mdseries\\upshape} % (See the fntguide.pdf for font help) " << endl 
        << "% (This matches ConTeXt defaults) " << endl 
        << " " << endl 
        << "%%% ToC (table of contents) APPEARANCE " << endl 
        << "\\usepackage[nottoc,notlof,notlot]{tocbibind} % Put the bibliography in the ToC " << endl 
        << "\\usepackage[titles,subfigure]{tocloft} % Alter the style of the Table of Contents " << endl 
        << "\\renewcommand{\\cftsecfont}{\\rmfamily\\mdseries\\upshape} " << endl 
        << "\\renewcommand{\\cftsecpagefont}{\\rmfamily\\mdseries\\upshape} % No bold! " << endl 
        << " " << endl 
        << "%%% END Article customizations " << endl 
        << " " << endl 
        << "%%% The \"real\" document content comes below... " << endl 
        << " " << endl 
        << "\\title{Summary Simulation E.coli} " << endl 
        << " " << endl 
        << "%\\date{} % Activate to display a given date or no date (if empty), " << endl 
        << "         % otherwise the current date is printed  " << endl 
        << " " << endl 
        << "\\begin{document} " << endl 
        << "\\maketitle " << endl 
        << " " << endl;
        
        
        
        //************************
        //         LOGO
        //************************
        
        //        file1 <<"\\newpage" << endl;
        file1 <<"\\tiny" << endl;
        
        file1 << "\\begin{verbatim}" << endl;
        
        file1 << "***********************************************************************************************************************************"<<endl
        <<"                                                                                .:"<<endl
        <<"                                                                               / )"<<endl
        <<"                                                                              ( ("<<endl
        <<"                         E.COLI - SIMULATOR                                    \\ )"<<endl
        <<"                               o                                             ._(/_."<<endl
        <<"                                o                                            |___%|"<<endl
        <<"                              ___              ___  ___  ___  ___             | %|"<<endl
        <<"                              | |        ._____|_|__|_|__|_|__|_|_____.       | %|"<<endl
        <<"                              | |        |__________________________|%|       | %|"<<endl
        <<"                              |o|          | | |%|  | |  | |  |~| | |        .|_%|."<<endl
        <<"                             .' '.         | | |%|  | |  |~|  |#| | |        | ()%|"<<endl
        <<"                            /  o  \\        | | :%:  :~:  : :  :#: | |     .__|___%|__."<<endl
        <<"                           :____o__:     ._|_|_."    "    "    "._|_|_.   |      ___%|_"<<endl
        <<"                           '._____.'     |___|%|                |___|%|   |_____(____  )"<<endl
        <<"                                                                             ( ("<<endl
        <<"                                                                              \\ '._____.-"<<endl
        <<"                                                                    grp        '._______.-"<<endl
        
        << "\n***********************************************************************************************************************************"<<endl
        << "***********************************************************************************************************************************\n"<<endl
        <<"                                       _______     _______  _______  _       _________ "<<endl
        <<"                                      (  ____ \\   (  ____ \\(  ___  )( \\      \\__   __/"<<endl
        <<"                                      | (    \\/   | (    \\/| (   ) || (         ) (   "<<endl
        <<"                                      | (__       | |      | |   | || |         | |   "<<endl
        <<"                                      |  __)      | |      | |   | || |         | |   "<<endl
        <<"                                      | (         | |      | |   | || |         | |   "<<endl
        <<"                                      | (____/\\ _ | (____/\\| (___) || (____/\\___) (___"<<endl
        <<"                                      (_______/(_)(_______/(_______)(_______/\\_______/"<<endl
        <<"                        _______ _________ _______           _        _______ _________ _______  _______ "<<endl
        <<"                       (  ____ \\\\__   __/(       )|\\     /|( \\      (  ___  )\\__   __/(  ___  )(  ____ )"<<endl
        <<"                       | (    \\/   ) (   | () () || )   ( || (      | (   ) |   ) (   | (   ) || (    )|"<<endl
        <<"                       | (_____    | |   | || || || |   | || |      | (___) |   | |   | |   | || (____)|"<<endl
        <<"                       (_____  )   | |   | |(_)| || |   | || |      |  ___  |   | |   | |   | ||     __)"<<endl
        <<"                             ) |   | |   | |   | || |   | || |      | (   ) |   | |   | |   | || (\\ (   "<<endl
        <<"                       /\\____) |___) (___| )   ( || (___) || (____/\\| )   ( |   | |   | (___) || ) \\ \\__"<<endl
        <<"                       \\_______)\\_______/|/     \\|(_______)(_______/|/     \\|   )_(   (_______)|/   \\__/\n\n"<<endl
        
        << "***********************************************************************************************************************************"<<endl
        <<"***********************************************************************************************************************************"<< endl
        
        
        
        
        <<"                                                  | 1"<<endl
        <<"                                               ,--|--."<<endl
        <<"                                            ,-'   |   `-.           "<<endl
        <<"                                          ,'      |      `. " <<endl
        <<"                                        ,'        |        `. " <<endl
        <<"                                       /          |          \\  " <<endl
        <<"                                      /           |       E.COLI-SIMULATOR                /"<<endl
        <<"                                 ----+------------+------------\\------------+------------/---"<<endl
        <<"                                    __            |0         __ \\          __           /  __"<<endl
        <<"                                    ||            |          ||  \\         ||          /  3||  "<<endl
        <<"                                  - ---           |          ---  `.                 ,'   --- "<<endl
        <<"                                     2            |           2     `.             ,'      2"<<endl
        <<"                                                  |                   `-.       ,-'"<<endl
        <<"                                                  | -1                   `--,--'          "<< "A program by S.Belloni."<<endl
        <<"***********************************************************************************************************************************"<<endl;    
        
        file1 << "\\end{verbatim}" << endl;
        file1 << "\\normalsize" << endl;
        file1 <<"\\newpage" << endl; 
        
    }
    
    
    
}
