cmake_minimum_required(VERSION 3.10)
project(cpp_chess)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(cpp_chess uci.cpp chess_rules.cpp)
