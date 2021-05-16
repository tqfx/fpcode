
cmake_minimum_required (VERSION 3.0)

project (APP_TERMUX)

include (../cmake-flags.cmake)

include_directories ("../klib")
include_directories ("../cJSON")
include_directories ("../mxml")
include_directories ("../fpcode")
include_directories ("../fp")
include_directories ("../tapi")

aux_source_directory(. SRC_APP_TERMUX)

add_library(app-termux STATIC ${SRC_APP_TERMUX})
