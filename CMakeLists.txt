cmake_minimum_required(VERSION 3.0)
project(Coursework C)

set(CMAKE_C_STANDARD 11)

SET(CMAKE_CXX_FLAGS "-O0")
SET(CMAKE_C_FLAGS "-O0")

add_executable(Coursework main.c time_measurement/time_measurement_processing.c
        time_measurement/time_measurement_processing.h settings.h user_interface/menu.c
        user_interface/menu.h user_interface/spreadsheet.c user_interface/spreadsheet.h
        time_measurement/measure_options.c time_measurement/measure_options.h algorithms/select_6_sorting.c
        algorithms/select_6_sorting.h algorithms/common_array.c algorithms/common_array.h algorithms/hybrid_select_1_exchange.c
        algorithms/hybrid_select_1_exchange.h algorithms/shell_1_sorting.c algorithms/shell_1_sorting.h algorithms/memory_access_test.c algorithms/memory_access_test.h)
#math lib for linux
target_link_libraries(Coursework m)
