
cmake_minimum_required (VERSION 3.0)

project (FPCODE)

include (../cmake-flags.cmake)

include_directories ("../md5")

add_library(fpcode STATIC fpcode.c)

add_library(fpcodex STATIC fpcodex.c)
