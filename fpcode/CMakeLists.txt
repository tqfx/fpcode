
cmake_minimum_required (VERSION 3.0)

project (FPCODE)

include (../cmake-flags.cmake)

add_library(fpcode STATIC MD5.c fpcode.c)

add_library(fpcodex STATIC MD5.c fpcodex.c)
