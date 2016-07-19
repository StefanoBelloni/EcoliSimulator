##########################################
# 	         PLATFORM		   #		
##########################################

ifeq ($(shell echo "check_quotes"),"check_quotes")
   OS = win
   UNZIP = 7z.exe
   OPT_UNZIP = x
   c_URL = curl
   OPT_cURL = -k -L -o
   CXX = g++.exe
   MAKE = make.exe
   COPY = copy
   MKDIR = mkdir
   DEL = del
   Division = \\
else
ifeq ($(shell uname -s), Darwin)
   OS = osx
   UNZIP = unzip
   OPT_UNZIP = 
   c_URL = curl
   OPT_cURL = -L -o
   CXX = clang++
   MAKE = make
   COPY = cp -f 
   MKDIR = mkdir -p
   DEL = rm -rf
   Division = /
else
   OS = linux
   UNZIP = unzip
   OPT_UNZIP = 
   c_URL = curl
   OPT_cURL = -L -o
   CXX = g++
   MAKE = make
   COPY = cp -f
   MKDIR = mkdir -p
   DEL = rm -rf
   Division = /
endif
endif

##########################################
# 	         DEFINITIONS		   #	
##########################################

# name
TARGET = EcoliSimulator

CFLAGS= -g -std=c++11 -Wall -pedantic
LDFLAGS =

# folders
SRC_DIR=src
HEAD_DIR=include
HEAD_DIR1 = include/Ecoli
HEAD_DIR2 = include/Global
HEAD_DIR3 = include/Ligand
HEAD_DIR4 = include/Visualization

BUILD_DIR=build
BIN_DIR=bin

INCLUDE_HEADS = -I$(HEAD_DIR) -I$(HEAD_DIR1) -I$(HEAD_DIR2) -I$(HEAD_DIR3) -I$(HEAD_DIR4)


BIN=$(TARGET)
SRC=$(wildcard $(SRC_DIR)/*.cpp) $(wildcard $(SRC_DIR)/*/*.cpp)	# sources

TMP=$(subst $(SRC_DIR),$(BUILD_DIR), $(SRC))
OBJ=$(patsubst %.cpp,%.o,$(TMP))					# objects

# include files (.h, .hpp)
dip_includes = $(wildcard $(HEAD_DIR)/*/*.h)
dip_includes_hpp = $(wildcard $(HEAD_DIR)/*/*.hpp)

##########################################
# 	         RULES			   #	
##########################################
                     
all: $(BIN)

apngasm: apngasm_bin 

gnuplot: gnuplot_bin

apngasm_src: apngasm_src

gnuplot_src: gnuplot_scr

install: $(BIN) apngasm_bin gnuplot_bin 

install_src: $(BIN) apngasm_src gnuplot_bin  

help: 
	@echo options for make:
	@echo make ............... Install EcoliSimulator
	@echo make install ....... Intsall EcoliSimulatorm gnuplot and apngasm - it downloads the binary or the installer
	@echo make intsall_src ... Install EcoliSimulator gnuplot and apngasm - you need cmake. 
	@echo make apngasm ....... to download the binary
	@echo make apngasm_src ... to download the surce: you need cmake in order to compile it automatically
	@echo make gnuplot ... ... to download the binary - for osx the .dmg file, for windows the 64-bit binary
	@echo make clean ......... eliminate all the objects .o

############################################
# Create a directory, if it does not exist #
############################################


# create a directory, if it does not exist
$(OBJ): | $(BUILD_DIR)

$(BUILD_DIR) $(BUILD_DIR)/Analysis_Runs $(BUILD_DIR)/Ecoli $(BUILD_DIR)/LateX $(BUILD_DIR)/Ligand $(BUILD_DIR)/MATLAB $(BUILD_DIR)/Simulations $(BUILD_DIR)/Varie $(BUILD_DIR)/Visualization:

	$(MKDIR) $(BUILD_DIR)
	$(MKDIR) $(BUILD_DIR)$(Division)Analysis_Runs
	$(MKDIR) $(BUILD_DIR)$(Division)Ecoli
	$(MKDIR) $(BUILD_DIR)$(Division)LateX
	$(MKDIR) $(BUILD_DIR)$(Division)Ligand
	$(MKDIR) $(BUILD_DIR)$(Division)MATLAB
	$(MKDIR) $(BUILD_DIR)$(Division)Simulations
	$(MKDIR) $(BUILD_DIR)$(Division)Statistics
	$(MKDIR) $(BUILD_DIR)$(Division)Varie
	$(MKDIR) $(BUILD_DIR)$(Division)Visualization

$(BIN) apngasm_bin gnuplot_bin apngasm_src gnuplot_src: | $(BIN_DIR)

$(BIN_DIR):
	$(MKDIR) $(BIN_DIR)

###################################
# 	   Build and Link	    #
###################################

# create the exeguible in the folder BINFOLDER
$(TARGET): $(OBJ)
	$(CXX) -o $(BIN_DIR)/$@ $^ $(LDFLAGS)

# create the objects .o in the folder BUILD_DIR           
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Analysis_Runs/%.o: $(SRC_DIR)/Analysis_Runs/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Ecoli/%.o: $(SRC_DIR)/Ecoli/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/LateX/%.o: $(SRC_DIR)/LateX/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Ligand/%.o: $(SRC_DIR)/Ligand/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/MATLAB/%.o: $(SRC_DIR)/MATLAB/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Simulations/%.o: $(SRC_DIR)/Simulations/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Varie/%.o: $(SRC_DIR)/Varie/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
$(BUILD_DIR)/Visualization/%.o: $(SRC_DIR)/Visualization/%.cpp ${dip_includes} ${dip_includes_hpp}
	$(CXX) $(INCLUDE_HEADS) -o $@ -c $< $(CFLAGS)
   

###################################################
# 	DOWNLOAD AND INSTALLATION OF APNGASM 	     #	
##################################################

#########
#  SRC  #
#########

apngasm_src.zip:
	$(c_URL) $(OPT_cURL) apngasm_src.zip "https://github.com/apngasm/apngasm/archive/master.zip"

apngasm_src: apngasm_src.zip
	$(UNZIP) $(OPT_UNZIP) apngasm_src.zip && cd apngasm-master && $(MKDIR) build && cd build && cmake .. && $(MAKE) && cd .. && cd .. && $(COPY) apngasm-master/build/cli/apngasm bin

##########
# BINARY #	
##########

ifeq ($(OS),win)

apngasm_bin: 
	$(c_URL) $(OPT_cURL) apngasm.exe "https://github.com/apngasm/apngasm/releases/download/3.1.1/apngasm_3.1-0_AMD64.exe"

else

# installing .pkg -> .dmg format.
ifeq ($(OS),osx)
apngasm_bin.dmg:
	$(c_URL) $(OPT_cURL) apngasm.dmg "https://github.com/apngasm/apngasm/releases/download/3.1.1/apngasm_3.1-0_i386.dmg"
apngasm_bin: apngasm_bin.dmg
	open apngasm.dmg
else
apngasm_bin:
	sudo apt-get update && sudo apt-get install apngasm
endif
endif	

###################################################
#      DOWNLOAD AND INSTALLATION OF GNUPLOT       #
###################################################

gnuplot_bin.zip:
ifeq ($(OS),osx)
	$(c_URL) $(OPT_cURL) gnuplot.dmg "http://ricardo.ecn.wfu.edu/pub/gnuplot/gnuplot-5.0.3-quartz.dmg"	
else	
ifeq ($(OS),win)
	$(c_URL) $(OPT_cURL) gnuplot.zip "http://www.tatsuromatsuoka.com/gnuplot/Eng/winbin/gp510-20160619-win64-mingw.zip"
else
	@echo "Download  gnuplot: raccomanded version is 5.0.0"
endif
endif

# installing .pkg -> .dmg format.
ifeq ($(OS),osx)
gnuplot_bin: gnuplot_bin.zip
	open gnuplot.dmg 
else
ifeq ($(OS),win)
gnuplot_bin: gnuplot_bin.zip
	$(COPY) gnuplot.zip bin && cd bin && $(UNZIP) $(OPT_UNZIP) gnuplot.zip && cd .. && $(DEL) gnuplot.zip 
else
gnuplot_bin:
	@echo "Install gnuplot for Ubuntu:"
	sudo apt-get install gnuplot gnuplot-x11 gnuplot-doc
endif

endif

###################################
#	       CLEAN		    #
###################################
                      
.PHONY = clean
.PHONY = clean_apngasm
.PHONY = clean_gnuplot

clean:
	$(DEL) $(BUILD_DIR)$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Analysis_Runs$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Ecoli$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)LateX$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Ligand$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)MATLAB$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Simulations$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Statistics$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Varie$(Division)*.o
	$(DEL) $(BUILD_DIR)$(Division)Visualization$(Division)*.o

clean_apngasm:
	$(DEL) apngasm-master
	$(DEL) apngasm_src.zip
	$(DEL) apngasm.dmg

clean_gnuplot:	
	cd bin && $(DEL) gnuplot.zip
	$(DEL) gnuplot.dmg
