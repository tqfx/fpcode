
cmake_minimum_required (VERSION 3.0)

project (FP)

if (NOT CMAKE_BUILD_TYPE)
set (CMAKE_BUILD_TYPE "Debug")
endif (NOT CMAKE_BUILD_TYPE)

include (cmake-flags.cmake)

include_directories (
    "${PROJECT_SOURCE_DIR}"
    "${PROJECT_SOURCE_DIR}/klib"
    "${PROJECT_SOURCE_DIR}/cJSON"
    "${PROJECT_SOURCE_DIR}/mxml"
    "${PROJECT_SOURCE_DIR}/fpcode"
    "${PROJECT_SOURCE_DIR}/fp"
    "${PROJECT_SOURCE_DIR}/app"
)

add_subdirectory (klib)
add_subdirectory (cJSON)
add_subdirectory (fpcode)
add_subdirectory (fp)
add_subdirectory (app)
add_subdirectory (mxml)

add_executable (key main.c)
target_link_libraries (key
    app
    fpcodex
    fp
    mxml
    cjson
    klib
)
if (MINGW AND HAVE_PTHREAD_H)
target_link_libraries (key -static winpthread)
endif (MINGW AND HAVE_PTHREAD_H)

add_executable (tqfx main.c)
target_link_libraries (tqfx
    app
    fpcode
    fp
    mxml
    cjson
    klib
)
if (MINGW AND HAVE_PTHREAD_H)
target_link_libraries (tqfx -static winpthread)
endif (MINGW AND HAVE_PTHREAD_H)

if (WIN32 OR ANDROID)
install (TARGETS key RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install (TARGETS tqfx RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
endif (WIN32 OR ANDROID)

# termux
if (ANDROID)

include_directories (
    "${PROJECT_SOURCE_DIR}/tapi"
    "${PROJECT_SOURCE_DIR}/app-termux"
)

add_subdirectory (tapi)
add_subdirectory (app-termux)

add_executable (key-t main-termux.c)
target_link_libraries (key-t
    app_termux
    tapi
    fpcodex
    fp
    klib
    cjson
    mxml
)

add_executable (tqfx-t main-termux.c)
target_link_libraries (tqfx-t
    app_termux
    tapi
    fpcode
    fp
    klib
    cjson
    mxml
)

install (TARGETS key-t RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})
install (TARGETS tqfx-t RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR})

endif (ANDROID)
