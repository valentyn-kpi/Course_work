//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include <math.h>
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
 * Алгоритм №1 методу сортування Шелла (класичний варіант
 * на основі прямої вставки №2).
 * Для вектору
 * @return Час сортування clock_t.
 */
clock_t SortingShell_1_vector() {
    // Підготовка сортування, виділення пам'яті
    clock_t start_measure, end_measure;
    volatile int *array_vector = GetPointer_Vector();
    volatile int n = GetDimension('N');
    volatile int Elem, t, j, k;
    //
    start_measure = clock();

    if (n < 4) t = 1;
    else t = (int) log2f((float) n) - 1;

    volatile int Stages[t];
    Stages[t - 1] = 1;
    for (int i = t - 2; i >= 0; i--)
        Stages[i] = 2 * Stages[i + 1] + 1;
    for (int p = 0; p < t; p++) {
        k = Stages[p];
        for (int i = k; i < n; i++) {
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

    return end_measure - start_measure;
}

// turn optimization back on for the rest of the program
#pragma GCC optimize ("O3")