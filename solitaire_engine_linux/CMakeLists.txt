cmake_minimum_required(VERSION 2.8.9)
set(CMAKE_CXX_STANDARD 11)
project(solitaire_engine)
 
#Bring the headers
include_directories(${CMAKE_SOURCE_DIR}/include)
 
#The file(GLOB...) allows for wildcard additions:
file(GLOB_RECURSE SRCS src/*.cpp)
file(GLOB_RECURSE HDRS include/*.h)
 
add_executable(solitaire_engine ${SRCS} ${HDRS})
