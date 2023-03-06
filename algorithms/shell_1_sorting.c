//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include <math.h>
#include <stdlib.h>
#include "shell_1_sorting.h"
#include "common_array.h"

// turn off optimization for this file
#pragma GCC optimize ("O0")

/**
 * Алгоритм №1 методу сортування Шелла (класичний варіант
 * на основі прямої вставки №2).
 * Для 3Д масиву.
 * @return Час сортування clock_t.
 */
clock_t SortingShell_1_3D() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    int ***array_3d = GetPointer_3DArray();

    int P = GetDimension('P');
    int M = GetDimension('M');
    int N = GetDimension('N');
    int t, j, k, p, i, slice, m;

    if (N < 4) t = 1;
    else t = (int) log2f((float) N) - 1;

    int *Stages = malloc(t * sizeof(int));
    int *coll = malloc(M * sizeof(int));

    start_measure = clock();
    for (slice = 0; slice < P; ++slice) {
        Stages[t - 1] = 1;
        for (i = t - 2; i >= 0; i--)
            Stages[i] = 2 * Stages[i + 1] + 1;
        for (p = 0; p < t; p++) {
            k = Stages[p];
            for (i = k; i < N; i++) {
                for (m = 0; m < M; ++m) {
                    coll[m] = array_3d[slice][m][i];
                }
                j = i;
                while (j >= k && coll[0] < array_3d[slice][0][j - k]) {
                    for (m = 0; m < M; ++m) {
                        array_3d[slice][m][j] = array_3d[slice][m][j - k];
                    }
                    j = j - k;
                }
                for (m = 0; m < M; ++m) {
                    array_3d[slice][m][j] = coll[m];
                }
            }
        }
    }
    end_measure = clock();

    free(coll);
    free(Stages);

    return end_measure - start_measure;
}

/**
 * Алгоритм №1 методу сортування Шелла (класичний варіант
 * на основі прямої вставки №2).
 * Для вектору
 * @return Час сортування clock_t.
 */
clock_t SortingShell_1_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');
    int Elem, t, k, p, i, j;

    if (N < 4) t = 1;
    else t = (int) log2f((float) N) - 1;
    int *Stages = malloc(t * sizeof(int));

    start_measure = clock();
    Stages[t - 1] = 1;
    for (i = t - 2; i >= 0; i--)
        Stages[i] = 2 * Stages[i + 1] + 1;
    for (p = 0; p < t; p++) {
        k = Stages[p];
        for (i = k; i < N; i++) {
            Elem = array_vector[i];
            j = i;
            while (j >= k && Elem < array_vector[j - k]) {
                array_vector[j] = array_vector[j - k];
                j = j - k;
            }
            array_vector[j] = Elem;
        }
    }
    end_measure = clock();
    free(Stages);
    return end_measure - start_measure;
}

// turn optimization back on for the rest of the program
#pragma GCC optimize ("O3")