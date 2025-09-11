
cmake_minimum_required(VERSION 3.30)


project(ct3)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

##############################################################################
## Using standard algorithms
##############################################################################

add_library(Intensity STATIC
        signal_intensity.cpp
        signal_intensity.hpp
        intensity_grid_search.cpp
        intensity_grid_search.hpp
        expanding_search_range.hpp
        expanding_search_range.cpp
)




