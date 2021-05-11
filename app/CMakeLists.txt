
cmake_minimum_required (VERSION 3.0)

project (APP)

include (../cmake_flags.cmake)

include_directories ("../klib")
include_directories ("../cJSON")
include_directories ("../mxml")
include_directories ("../fpcode")
include_directories ("../fp")

aux_source_directory(. SRC_APP)

add_library(app STATIC ${SRC_APP})
