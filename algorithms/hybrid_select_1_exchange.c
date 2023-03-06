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
    int ***array_3d = GetPointer_3DArray();
    int P = GetDimension('P');
    int M = GetDimension('M');
    int N = GetDimension('N');
    int p, Min, s, i, j;

    start_measure = clock();//початок вимірів
    for (p = 0; p < P; p++) {
        for (s = 0; s < N - 1; s++) {
            Min = array_3d[p][0][s];
            for (i = s + 1; i < N; i++) {
                if (array_3d[p][0][i] < Min) {
                    for (j = 0; j < M; ++j) {//для всіх рядків i-того стовпчика
                        Min = array_3d[p][j][i];
                        array_3d[p][j][i] = array_3d[p][j][s];
                        array_3d[p][j][s] = Min;
                    }
                }
            }
        }
    }
    end_measure = clock();//кінець вимірів

    return end_measure - start_measure;
}

/**
 * Гібридний алгоритм "вибір№1 – обмін"
 * @return Час сортування clock_t.
 */
clock_t SortingHybrid_1_exchange_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');
    int Min, s, i;
    //
    start_measure = clock();
    for (s = 0; s < N - 1; s++) {
        Min = array_vector[s];
        for (i = s + 1; i < N; i++)
            if (array_vector[i] < Min) {
                Min = array_vector[i];
                array_vector[i] = array_vector[s];
                array_vector[s] = Min;
            }
    }
    end_measure = clock();

    return end_measure - start_measure;
}

// turn optimization back on for the rest of the program
#pragma GCC optimize ("O3")