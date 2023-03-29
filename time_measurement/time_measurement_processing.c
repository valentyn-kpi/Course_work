//
// Created by Valentyn Valentiev on 2/14/2023.
//
/*
 * Модуль збереження та обробки вимірів.
 */

#include "time_measurement_processing.h"
#include <stdlib.h>
#include "../settings.h"
#include "../algorithms/common_array.h"
#include <stdio.h>

static float *values = NULL; //вказівник на масив значень
static int next_index = -1;    //довжина масиву значень

/**
 * Ініціалізація вимірів. (виділення пам'яті для масиву значень)
 */
void InitializeTimeMeasurement() {
    if (next_index == -1) {
        values = malloc(0);
        next_index = 0;
    } else {
        //already initialised
#ifndef SUP_DEBUG
        printf("Tried to re-init!\n");
#endif
    }
}

/**
 * Додати значення для подальшої обробки.
 * @param value - отримане значення виміру часу.
 */
void AddValue(float value) {
    if (next_index > -1) {
        values = realloc(values, (next_index + 1) * sizeof(float));

        values[next_index] = value;
        next_index++;
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized value lost!\n");
#endif
    }
}

/**
 * Звільнення ресурсів після завершення вимірів та їх обробки.
 */
void DeallocTimeMeasurement() {
    if (next_index > -1) {
        free(values);
        values = NULL;
        next_index = -1;
    } else {
        //already deallocated
#ifndef SUP_DEBUG
        printf("Tried to re-dealloc!\n");
#endif
    }
}

/**
 * Функція відкидання значень масиву.
 * @param begin - кількість відкинутих значень з початку.
 * @param end   - кількість відкинутих значень з кінця
 */
static void reject_values(int begin, int end) {
    float *tmp_pointer = malloc((next_index - begin - end) * sizeof(float));

    for (int i = begin; i < next_index - end; ++i) {
        tmp_pointer[i - begin] = values[i];
    }

    free(values);
    values = tmp_pointer;
    next_index = next_index - begin - end;
}

/**
 * Вивід для налагодження.
 */
static void print_values() {
#ifndef SUP_DEBUG
    printf("clock_t values: ");
    for (int i = 0; i < next_index; ++i) {
        printf("%.1f ", values[i]);
    }
    printf("\n");
#endif
}

/**
* Функія сортування масиву методом вибору.
*/
static void sort_values() {
    for (int i = 0; i < next_index - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < next_index; j++) {
            if (values[j] < values[min_idx]) {
                min_idx = j;
            }
        }
        float temp = values[i];
        values[i] = values[min_idx];
        values[min_idx] = temp;
    }
}


/**
 * Розрахунок середнього серед значень масиву.
 * @return середнє значення масиву.
 */
static float calculate_average() {
    long double sum = 0;

    for (int i = 0; i < next_index; ++i) {
        sum += values[i];
    }

    return (float) (sum / next_index);
}

/**
 * Обробка вимірів часу.
 * @return результат обробки.
 */
float ProcessValues() {
    if (next_index > -1) {
        print_values();
        reject_values(REJECTED_NUMBER, 0);           //відкинути перші виміри
        print_values();

        sort_values();                                           //сортування масиву
        print_values();

        reject_values(MIN_MAX_NUMBER, MIN_MAX_NUMBER);//відкинути перші та останні min_max_number елементи
        print_values();

        printf("");//навіщо?

        return calculate_average();                              //пошук середнього
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized!\n");
#endif
        return -1;
    }
}

/**
 * Вивід 3Д масиву для налагодження.
 * @param arr масив.
 * @param P кількість перерізів
 * @param M кількість рядків
 * @param N кількість стовпчиків
 */
static void print_3d_array(int ***arr, int P, int M, int N) {
    int p, m, n;
    printf("\n\n");
    for (p = 0; p < P; p++) {
        printf("Slice %d:\n", p + 1);
        for (m = 0; m < M; m++) {
            for (n = 0; n < N; n++) {
                printf("%5d", arr[p][m][n]);
            }
            printf("\n");
        }
        printf("\n");
    }
    printf("\n\n");
}

/**
 * Вивід вектора.
 * @param arr масив.
 * @param size довжина масиву.
 */
static void printArray(int *arr, int size) {
    printf("\n\n");
    for (int i = 0; i < size; i++) {
        printf("%5d", arr[i]);
    }
    printf("\n\n");
}

/**
 * Функція відсікання двох послідовних вимірів з великою різницею.
 * @param fnc - функція, що повертає вимір часу.
 * @return Повертає середнє арифметичне перших двох послідовних вимірів, що відрізняються менше ніж на 0.1%, у випадку успіху.
 *         Повертає -1, якщо досягнуто максимальну кількість ітерацій або функція fnc повернула помилку.
 */
float lowDiffAvgTimeMeasure(clock_t (*fnc)(), int scase, int array_type) {
    clock_t temp, temp2, diff;
    unsigned int seed = time(NULL);//отримання сіду для генератора псевдорандомних чисел
    // (обидва виміри з однаковим сідом - однакові псевдорандомні значення)

#ifndef SUP_ARRAY_PRINT
    if (array_type == ARRAY_VECTOR) {
        FillVector(scase, seed);
        printArray(GetPointer_Vector(), GetDimension('N'));
        fnc();
        printArray(GetPointer_Vector(), GetDimension('N'));
    } else {
        Fill3DArray(scase, seed);
        print_3d_array(GetPointer_3DArray(), GetDimension('P'), GetDimension('M'), GetDimension('N'));
        fnc();
        print_3d_array(GetPointer_3DArray(), GetDimension('P'), GetDimension('M'), GetDimension('N'));
    }
#endif

    int iterCount = 0;
    do {//поки різниця більша за бажану та кількість ітерацій менше за максимальну
        if (array_type == ARRAY_VECTOR) {
            FillVector(scase, seed);
            temp = fnc();
            FillVector(scase, seed);
            temp2 = fnc();
        } else {
            Fill3DArray(scase, seed);
            temp = fnc();
            Fill3DArray(scase, seed);
            temp2 = fnc();
        }
        diff = labs(temp - temp2);
#ifndef SUP_DEBUG
        printf("\nCurrent time difference: %ld\n", diff);
#endif
    } while ((diff > temp2 * MAX_DIFFERENCE) && iterCount++ < MAX_ITERATIONS);
    //поки різниця більша за бажану та кількість ітерацій менше за максимальну

    if (iterCount >= MAX_ITERATIONS) {//перевіряємо, чи досягнуто максимальну кількість ітерацій
        printf("\n\nFATAL: System unstable!\n"
               "Cannot perform precise measurements!\n"
               "Please try one or more of the following:\n"
               " - Lock the CPU speed to 50%% of the base speed\n"
               " - Increase the MAX_ITERATIONS value in settings.h\n"
               " - Increase array dimensions\n"
               " - Increase process priority and reduce running processes count\n"
               " - Run program on isolated cpu(core).\n\n");

        fflush(stdout);
        fflush(stdin);
        getchar();
        exit(-1);
    }
    return (float) ((temp + temp2) / 2.0);
}

