cmake_minimum_required(VERSION 3.18)
project(Course_work C)

# Set a default build type if none was specified
set(default_build_type "Release")

if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to '${default_build_type}' as none was specified.")
    set(CMAKE_BUILD_TYPE "${default_build_type}" CACHE
            STRING "Choose the type of build." FORCE)
    # Set the possible values of build type for cmake-gui
    set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS
            "Debug" "Release" "MinSizeRel" "RelWithDebInfo")
endif()

set(CMAKE_C_STANDARD 11)

add_executable(Course_work main.c time_measurement/time_measurement_processing.c time_measurement/time_measurement_processing.h settings.h user_interface/menu.c user_interface/menu.h user_interface/spreadsheet.c user_interface/spreadsheet.h time_measurement/measure_options.c time_measurement/measure_options.h algorithms/select_6_sorting.c algorithms/select_6_sorting.h algorithms/common_array.c algorithms/common_array.h algorithms/hybrid_select_1_exchange.c algorithms/hybrid_select_1_exchange.h algorithms/shell_1_sorting.c algorithms/shell_1_sorting.h)
target_link_libraries(Course_work m)