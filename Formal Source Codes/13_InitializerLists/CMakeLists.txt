#
# Middle East Technical University
# Dept. of Computer Engineering
#
# CENG 213 - Data Structures
# Dr. Hakan YILDIZ
# hakan@ceng.metu.edu.tr
#
# Not to be reshared without permission.
#
cmake_minimum_required(VERSION 3.22)

set(PROJECT 13_InitializerLists)

file(GLOB ALL_SOURCES "*.cpp")
file(GLOB ALL_HEADERS "*.h")

set(SOURCES ${ALL_SOURCES})
set(HEADERS ${ALL_HEADERS})

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

project(${PROJECT} LANGUAGES CXX)
add_executable(${PROJECT} ${SOURCES} ${HEADERS})

target_compile_options(${PROJECT} PRIVATE
                       $<$<CXX_COMPILER_ID:MSVC>:/W4>
                       $<$<NOT:$<CXX_COMPILER_ID:MSVC>>:-Wall -Wextra -Wpedantic>)
