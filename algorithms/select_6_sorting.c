//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include <stdio.h>
#include "select_6_sorting.h"
#include "common_array.h"

// turn off optimization for this file
#pragma GCC optimize ("O0")

/**
 * Алгоритм сортування №6 методу прямого вибору.
 * @return Час сортування clock_t.
 */
clock_t SortingSelect_6() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    volatile int ***array_3d = GetPointer_3DArray();
    volatile int p = GetDimension('P');
    volatile int m = GetDimension('M');
    volatile int n = GetDimension('N');

    //початок вимірів
    start_measure = clock();

    end_measure = clock();

    return end_measure - start_measure;
}

clock_t SortingSelect_6_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    volatile int *array_vector = GetPointer_Vector();
    volatile int n = GetDimension('N');
    volatile int i_min, tmp, s;
    //початок вимірів
    start_measure = clock();
    for (s = 0; s < n - 1; s++) {
        i_min = s;
        for (int i = s + 1; i < n; i++)
            if (array_vector[i] < array_vector[i_min]) i_min = i;
        if (i_min != s) {
            tmp = array_vector[i_min];
            array_vector[i_min] = array_vector[s];
            array_vector[s] = tmp;
        }
    }
    end_measure = clock();
    //кінець вимірів

    return end_measure - start_measure;
}
// turn optimization back on for the rest of the program
#pragma GCC optimize ("O3")