cmake_minimum_required(VERSION 3.29.2)
project( TinoSHader )




set(CMAKE_POSITION_INDEPENDENT_CODE ON)  # Required for shared libraries
set(CMAKE_CXX_VISIBILITY_PRESET hidden)  # Hide symbols by default
set(CMAKE_VISIBILITY_INLINES_HIDDEN ON)

#include_directories( lib/ )
include_directories( src/include/ )
add_executable( main src/main.cpp )
target_link_libraries(main raylib)
