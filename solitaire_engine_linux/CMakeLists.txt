cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project(solitaire)
 
#Bring the headers
include_directories(${CMAKE_SOURCE_DIR}/include)
 
#However, the file(GLOB...) allows for wildcard additions:
file(GLOB SOURCES "src/*.cpp")
 
add_executable(solitaire ${SOURCES})