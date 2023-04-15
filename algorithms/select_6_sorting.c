//algorithms/select_6_sorting.c
//
// Created by Valentyn Valentiev on 2/18/2023.
//

/*
 * Модуль сортування вибором вектора та 3Д масиву.
 */

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
    int ***array_3d = GetPointer_3DArray();

    int P = GetDimension('P');
    int M = GetDimension('M');
    int N = GetDimension('N');
    int p, s, i_min, i, tmp, j;


    start_measure = clock();//початок вимірів
    for (p = 0; p < P; ++p) {//для всіх перерізів
        for (s = 0; s < N - 1; s++) {
            i_min = s;

            for (i = s + 1; i < N; i++)
                if (array_3d[p][0][i] < array_3d[p][0][i_min]) i_min = i;

            if (i_min != s) {
                for (j = 0; j < M; ++j) {//для всіх рядків i_min стовпчика
                    tmp = array_3d[p][j][i_min];
                    array_3d[p][j][i_min] = array_3d[p][j][s];
                    array_3d[p][j][s] = tmp;
                }
            }
        }
    }
    end_measure = clock();//кінець вимірів

    return end_measure - start_measure;
}

/**
 * Алгоритм сортування №6 методу прямого вибору.
 * @return Час сортування clock_t.
 */
clock_t SortingSelect_6_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');
    int i_min, tmp, s, i;

    start_measure = clock(); //початок вимірів
    for (s = 0; s < N - 1; s++) {
        i_min = s;
        for (i = s + 1; i < N; i++)
            if (array_vector[i] < array_vector[i_min]) i_min = i;
        if (i_min != s) {
            tmp = array_vector[i_min];
            array_vector[i_min] = array_vector[s];
            array_vector[s] = tmp;
        }
    }
    end_measure = clock(); //кінець вимірів

    return end_measure - start_measure;
}