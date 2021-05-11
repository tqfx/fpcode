
cmake_minimum_required (VERSION 3.0)

project (TAPI)

include (../cmake_flags.cmake)

include_directories ("../klib")
include_directories ("../cJSON")

aux_source_directory(. SRC_TAPI)

add_library(tapi STATIC ${SRC_TAPI})
