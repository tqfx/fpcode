# compiler is gnu
if (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

# C/C++ standard 11
set (CMAKE_C_FLAGS "-std=gnu11 ${CMAKE_C_FLAGS}")
set (CMAKE_CXX_FLAGS "-std=gnu++11 ${CMAKE_CXX_FLAGS}")

# C/C++ build debug
set (CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -g -ggdb")
set (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAGS} -O0 -g -ggdb")

# C/C++ build release
set (CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3")
set (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3")

# C/C++ compile options
add_compile_options (
    -Wall
    -Wextra
    -pedantic
    -Wimplicit-fallthrough
    -Wsequence-point
    -Wswitch-default
    -Wswitch-enum
    -Wtautological-compare
    -Wfloat-equal
    -Wpointer-arith
    -Wpointer-compare
    -Wcast-align
    -Wcast-qual
    -Wwrite-strings
    -Wdangling-else
    -Wconversion
)

else () #(CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)

# C/C++ standard
set (CMAKE_CXX_STANDARD 11)
set (CMAKE_C_STANDARD 11)

endif (CMAKE_COMPILER_IS_GNUCC OR CMAKE_COMPILER_IS_GNUCXX)
