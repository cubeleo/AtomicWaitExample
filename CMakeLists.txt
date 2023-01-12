cmake_minimum_required(VERSION 3.18)
project(CPPExamples C CXX)

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

set(CMAKE_CXX_STANDARD 20)

add_executable(AtomicWaitExample AtomicWaitExample.cpp)
