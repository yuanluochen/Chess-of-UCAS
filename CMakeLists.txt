cmake_minimum_required(VERSION 3.22)
project(chess)
# clangd
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
# gdb
set(CMAKE_BUILD_TYPE Debug)  
set(CMAKE_CXX_FLAGS_DEBUG "-g")
# build file
include_directories(include)
add_executable(chess.out source/chessGame.cpp source/main.cpp)
