//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include "hybrid_select_1_exchange.h"
#include "common_array.h"

// turn off optimization for this file
#pragma GCC optimize ("O0")
/**
 * Гібридний алгоритм "вибір№1 – обмін"
 * @return Час сортування clock_t.
 */
clock_t SortingHybrid_1_exchange() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    volatile int ***array_3d = (volatile int ***) GetPointer_3DArray();
    volatile int p = GetDimension('P');
    volatile int m = GetDimension('M');
    volatile int n = GetDimension('N');

    //
    start_measure = clock();

    end_measure = clock();

    return end_measure - start_measure;
}

/**
 * Гібридний алгоритм "вибір№1 – обмін"
 * @return Час сортування clock_t.
 */
clock_t SortingHybrid_1_exchange_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    int ***array_3d = GetPointer_3DArray();
    int p = GetDimension('P');
    int m = GetDimension('M');
    int n = GetDimension('N');

    //
    start_measure = clock();

    end_measure = clock();

    return end_measure - start_measure;
}
// turn optimization back on for the rest of the program
#pragma GCC optimize ("O3")