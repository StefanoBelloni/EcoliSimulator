cmake_minimum_required(VERSION 2.8.9)
project(directory_test)
# set the executable in {source}/bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#Bring the headers, 
include_directories(include)
include_directories(include/Ecoli)
include_directories(include/Global)
include_directories(include/Ligand)
include_directories(include/Visualization)

#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp" "src/*/*.cpp")
 
add_executable(EcoliSimulator ${SOURCES})

install(TARGETS EcoliSimulator DESTINATION ${CMAKE_SOURCE_DIR}/bin)

# allow c++11
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
