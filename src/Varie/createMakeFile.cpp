//
//  createMakeFile.cpp
//  EcoliSimulator_0.0.1a
//
//  Created by Stefano Belloni on 02/06/16.
//  Copyright © 2016 Stefano Belloni. All rights reserved.
//


#include <iostream>
#include <fstream>
#include <vector>
#include <cstdlib>

//#include "dirent.h"

int createMakeFile(){

    std::ofstream filemake("Makefile");
    
    filemake << "CXX=clang++" << std::endl
             << "CXXFLAGS=-g -std=c++11 -Wall -pedantic" << std::endl
             << "BIN=EcoliSimulation" << std::endl << std::endl
            
             << "SRC=$(wildcard *.cpp)"<< std::endl
             << "OBJ=$(SRC:%.cpp=%.o)"<< std::endl << std::endl
            
             << "all: $(OBJ)"<< std::endl
             << "\t$(CXX) -o $(BIN) $^"<< std::endl<< std::endl
            
             << "\t%.o: %.c"<< std::endl
             << "\t$(CXX) $@ -c $<"<< std::endl<< std::endl
            
             << "clean:"<< std::endl
             << "\trm -f *.o"<< std::endl
             << "\trm $(BIN)"<< std::endl;
    
    filemake.close();
    
       return 0;
    
}


