//algorithms\memory_access_test.c
//
// Created by Valentyn Valentiev on 4/5/2023.
//

/*
 * Модуль виміру часу читання/запису/обміну елементів 3Д масиву та вектору.
 */

#include "memory_access_test.h"
#include "common_array.h"

#pragma GCC optimize ("O0")

int abc(int a) {
    return a;
}

/**
 * Читання (сміття) з 3Д масиву в локальну змінну
 * @return час читання
 */
clock_t Array3DTime_r() {
    clock_t start_measure, end_measure, withloop, loop;
    int ***array_3d = GetPointer_3DArray();

    int N = GetDimension('N');

    int i, a;

    start_measure = clock();
    //read
    for (i = 0; i < N; ++i) {
        a = array_3d[0][0][i];
    }
    end_measure = clock();

    withloop = end_measure - start_measure;

    start_measure = clock();
    for (i = 0; i < N; ++i) {
    }
    end_measure = clock();

    loop = end_measure - start_measure;

    abc(a);

    return withloop - loop;
}

/**
 * Запис (5) в 3Д масив з локальної змінної
 * @return час запису
 */
clock_t Array3DTime_w() {
    clock_t start_measure, end_measure, withloop, loop;
    int ***array_3d = GetPointer_3DArray();

    int N = GetDimension('N');

    int i, a = 5;

    start_measure = clock();
    //write
    for (i = 0; i < N; ++i) {
        array_3d[0][0][i] = a;
    }
    end_measure = clock();

    withloop = end_measure - start_measure;

    start_measure = clock();
    for (i = 0; i < N; ++i) {
    }
    end_measure = clock();

    loop = end_measure - start_measure;

    return withloop - loop;
}

/**
 * Обмін елементів (сміття) 3Д масиву через локальну змінну.
 * @return час обміну.
 */
clock_t Array3DTime_s() {
    clock_t start_measure, end_measure, withloop;
    int ***array_3d = GetPointer_3DArray();

    int N = GetDimension('N');

    int i, a, b = 5;

    start_measure = clock();
    //swap
    for (i = 0; i < N; ++i) {
        a = array_3d[0][0][i];
        array_3d[0][0][i] = array_3d[0][0][b];
        array_3d[0][0][b] = a;
    }
    end_measure = clock();

    withloop = end_measure - start_measure;

    return withloop;
}

/**
 * Читання (сміття) з вектору в локальну змінну.
 * @return час читання.
 */
clock_t VectorTime_r() {
    clock_t start_measure, end_measure, withloop, loop;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');

    int i, a;

    start_measure = clock();
    //read
    for (i = 0; i < N; ++i) {
        a = array_vector[i];
    }
    end_measure = clock();

    abc(a);

    withloop = end_measure - start_measure;

    start_measure = clock();
    for (i = 0; i < N; ++i) {
    }
    end_measure = clock();

    loop = end_measure - start_measure;

    return withloop - loop;
}

/**
 * Запис (5) в вектор з локальної змінної.
 * @return час запису.
 */
clock_t VectorTime_w() {
    clock_t start_measure, end_measure, withloop, loop;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');

    int i, a = 5;

    start_measure = clock();
    //write
    for (i = 0; i < N; ++i) {
        array_vector[i] = a;
    }
    end_measure = clock();

    withloop = end_measure - start_measure;

    start_measure = clock();
    for (i = 0; i < N; ++i) {
    }
    end_measure = clock();

    loop = end_measure - start_measure;

    return withloop - loop;
}

/**
 * Обмін елементів (сміття) вектору через локальну змінну.
 * @return час обміну.
 */
clock_t VectorTime_s() {
    clock_t start_measure, end_measure, withloop;
    int *array_vector = GetPointer_Vector();
    int N = GetDimension('N');

    int i, a, b = 5;

    start_measure = clock();
    //swap
    for (i = 0; i < N; ++i) {
        a = array_vector[i];
        array_vector[i] = array_vector[b];
        array_vector[b] = a;
    }
    end_measure = clock();
    withloop = end_measure - start_measure;

    return withloop;
}
