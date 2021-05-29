
cmake_minimum_required (VERSION 3.0)

project (FP)

include (../cmake-flags.cmake)

include_directories ("../klib")
include_directories ("../cJSON")
include_directories ("../mxml")
include_directories ("../fpcode")
include_directories ("../md5")

aux_source_directory(. SRC_FP)

add_library(fp STATIC ${SRC_FP})
