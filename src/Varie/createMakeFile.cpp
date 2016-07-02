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

#include "dirent.h"

int createMakeFile(){

    std::ofstream filemake("Makefile");
    
//*****************************************************************************************************************************
//*****************************************************************************************************************************
//
//
//    std::string s_cwd(/*getcwd(NULL,0)*/"/Users/stefanobelloni/Documents/cpp_programs/XCodeProjects/Ecoli_X/EcoliSimulator_0.0.1a/EcoliSimulator_0.0.1a");
//    std::vector<std::string> names_files;
//
//    
//    DIR *dir;
//    struct dirent *ent;
//    
//    int n_files = 0;
//    
//    
//    // Secondo Passo scrivere i dati!
//    if ((dir = opendir (s_cwd.c_str())) != NULL) {
//        /* print all the files and directories within directory */
//        while ((ent = readdir (dir)) != NULL) {
//            std::string temp = std::string(ent->d_name);
//            
//            std::cout << "temp: " << temp << std::endl;
//            
//            if (temp.size()>4) {
//                std::string extension = temp;
//                extension.erase(extension.begin(), extension.end()-3);
//                temp.erase(temp.end()-4,temp.end());
//                if (extension=="cpp"){
//                    names_files.push_back(temp);
//                    
//                }
//            }
//            n_files++;
//            
//        }
//        closedir (dir);
//    } else {
//        /* could not open directory */
//        perror ("");
//        return EXIT_FAILURE;
//    }
//    
//    
//    filemake << "# Project: MacWinEcoliSimulation" << std::endl
//             << "# Makefile created by Dev-C++ 5.11" << std::endl
//             << "CPP      = clang++" << std::endl
//             << "CC       = gcc" << std::endl
//             << "# WINDRES  = windres.exe" << std::endl
//             << "OBJ      = ";
//    
//    for (int i=0;i<names_files.size();i++){
//        filemake << " " <<  names_files[i] << ".o";
//    }
//    
//    filemake << std::endl
//             << "LINKOBJ = ";
//    
//    for (int i=0;i<names_files.size();i++){
//        filemake << " " <<  names_files[i] << ".o";
//    }
//    
//    filemake << std::endl;
//    filemake << "#LIBS     =  -static-libgc " << std::endl
//             << "#INCS     = -std=c++11" << std::endl
//             << "CXXINCS  = -g -std=c++11 -Wall -pedantic" << std::endl << std::endl;
//    
//    filemake << "BIN      = MacWinEcoliSimulator" << std::endl;
//    filemake << "CXXFLAGS = $(CXXINCS)" << std::endl;
//    filemake << "#CFLAGS   = $(INCS)" << std::endl;
//    filemake << "RM       = rm -f" << std::endl << std::endl;
//    filemake << ".PHONY: all all-before all-after clean clean-custom" << std::endl << std::endl;
//    
//    filemake << "all: all-before $(BIN) all-after" << std::endl << std::endl;
//    filemake << "$(BIN): $(OBJ)" << std::endl;
//    filemake << "\t$(CPP) $(LINKOBJ) -o $(BIN) $(LIBS)" << std::endl << std::endl;
//    
//    for (int i=0; i<names_files.size(); i++) {
//        filemake << names_files[i] << ".o: " << names_files[i]<<".cpp" << std::endl
//                 << "\t$(CPP) -c " <<names_files[i]<<".cpp -o "<<names_files[i]<<".o $(CXXFLAGS)" << std::endl<<std::endl;
//    }
//
//    
//    filemake << "clean: clean-custom" << std::endl;
//    filemake << "#I$(RM) $(OBJ) $(BIN)" << std::endl;
//    filemake << "#rm -rf *.o" << std::endl;
//    filemake << "\trm -rf $(wildcard *.o)" << std::endl;
//
//*****************************************************************************************************************************
//*****************************************************************************************************************************

    
    
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
    
    
    
//# Compiler
//    CC = g++
//#OPTS = -c -Wall
//    OPTS = -g -std=c++11 -Wall -pedantic
//#CXXFLAGS=-g -std=c++11 -Wall -pedantic
//# Project name
//    PROJECT = MacWinEcoliSimulation_NEW
//    
//# Directories
//    OBJDIR = obj
//    SRCDIR = src
//    
//# Libraries
//    LIBS =
//    
//# Files and folders
//    SRCS    = $(shell find $(SRCDIR) -name '*.cpp')
//    SRCDIRS = $(shell find . -name '*.cpp' | dirname {} | sort | uniq | sed 's/\/$(SRCDIR)//g' )
//# the SRCDIRS did not work if there were more than one directory.
//#SRCDIRS = $(shell find $(SRCDIR) -type d | sed 's/$(SRCDIR)/./g' )
//    OBJS    = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(SRCS))
//    
//# Targets
//    $(PROJECT): buildrepo $(OBJS)
//    $(CC) $(OBJS) $(LIBS) -o $@
//    
//    $(OBJDIR)/%.o: $(SRCDIR)/%.cpp
//    $(CC) $(OPTS) -c $< -o $@
//    
//clean:
//    rm $(PROJECT) $(OBJDIR) -Rf
//    
//buildrepo:
//    @$(call make-repo)
//    
//# Create obj directory structure
//    define make-repo
//    mkdir -p $(OBJDIR)
//    for dir in $(SRCDIRS); \
//    do \
//        mkdir -p $(OBJDIR)/$$dir; \
//    done
//    endef
    
    
    
//CC=g++
//CFLAGS= -g -std=c++11 -Wall -pedantic
//LDFLAGS =
//
//SRCDIR=src
//HEADDIR=include
//LIBDIR=build
//BINDIR=bin
//
//BIN=LTN
//SRC=$(wildcard $(SRCDIR)/*.cpp)
//                         TMP=$(subst $(SRCDIR),$(LIBDIR), $(SRC))
//                         OBJ=$(patsubst %.cpp,%.o,$(TMP))
//                         
//                         all: $(BIN)
//                         
//                         LTN: $(OBJ)
//                         @[ ! -d $(BINDIR) ] & mkdir -p $(BINDIR)
//                         $(CC) -o $(BINDIR)/$@ $^ $(LDFLAGS)
//                         
//                         $(LIBDIR)/%.o: $(SRCDIR)/%.cpp  
//                         @[ ! -d $(dir $@) ] & mkdir -p $(dir $@)
//                         $(CC) -I$(HEADDIR) -o $@ -c $< $(CFLAGS)
//                         
//                         .PHONY = clean
    
    return 0;
    
}


