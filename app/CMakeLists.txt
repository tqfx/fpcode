
cmake_minimum_required(VERSION 3.10)

project(APP)

include(../cmake-flags.cmake)

include_directories("../klib")
include_directories("../cJSON")
include_directories("../mxml")
include_directories("../fpcode")
include_directories("../fp")

aux_source_directory(. SOURCE_APP)

add_library(app STATIC ${SOURCE_APP})

target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../klib)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../fpcode)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../cJSON)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../mxml)
target_include_directories(fp INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/../fp)
