
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
        find_root.hpp
        function_with_noise.hpp
)


##############################################################################
## When to use functions
##############################################################################

## Creating interfaces based on functions

add_library(summary_statistics STATIC
        summary_statistics.cpp
        summary_statistics.hpp
)



## Functions as building blocks

add_library(find_root INTERFACE find_root.hpp)




## Function-like objects

add_library(function_with_noise INTERFACE
        function_with_noise.hpp)




##############################################################################
## When to use classes
##############################################################################


add_library(address_book_record STATIC
        address_book_record.cpp
        address_book_record.hpp
)




## Classes that represent physical objects[


add_library(temperature_sensors STATIC
        temperature_sensors.cpp
        temperature_sensors.hpp
        concrete_temperature_sensor.cpp
        concrete_temperature_sensor.hpp)


