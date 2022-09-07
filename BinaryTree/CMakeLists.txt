cmake_minimum_required(VERSION 3.16.3 FATAL_ERROR)

project(vector VERSION 0.1.0 LANGUAGES CXX C)

set(LANGUAGES CXX 17)
set(-Wall)

add_executable(binTree BinTree_test.cc)
