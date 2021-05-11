
cmake_minimum_required (VERSION 3.0)

project (FPCODE)

include (../cmake_flags.cmake)

add_library(fpcode STATIC MD5.c fpcode.c)

add_library(fpcode_x STATIC MD5.c fpcode_x.c)
