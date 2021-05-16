
cmake_minimum_required (VERSION 3.0)

project (TERMUX_API)

include (cmake-flags.cmake)

include_directories ("../klib")
include_directories ("../cJSON")

aux_source_directory(. SRC_TERMUX_API)

add_library(termux_api STATIC ${SRC_TERMUX_API})
