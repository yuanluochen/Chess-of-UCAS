cmake_minimum_required(VERSION 3.22)
project(chess)
# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# gdb
set(CMAKE_BUILD_TYPE Debug)  
set(CMAKE_CXX_FLAGS_DEBUG "-g")
# build file
include_directories(include)

set(LIB_FILE source/chessGame.cpp  source/decisionTree.cpp)
set(SRC source/main.cpp)

add_executable(chess.out ${SRC} ${LIB_FILE})
