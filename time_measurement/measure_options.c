//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include "measure_options.h"
#include "time_measurement_processing.h"

#include "../algorithms/select_6_sorting.h"
#include "../algorithms/hybrid_select_1_exchange.h"
#include "../algorithms/shell_1_sorting.h"

#include "../algorithms/common_array.h"
#include "../settings.h"
#include "../user_interface/spreadsheet.h"

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>

/**
 * Отримання усереднених вимірів.
 * @param fnc - функція в якій знаходиться алгоритм, що вимірюється.
 * @param scase - випадок відсортованості.
 * @param p - кількість перерізів.
 * @param m - кількість рядків.
 * @param n - кількість стовпчиків.
 * @return Повертає оброблене значення вимірів часу.
 */
static float do_measuring_3d(clock_t (*fnc)(), int scase, int p, int m, int n) {
    InitializeTimeMeasurement();
    Allocate3DArray(p, m, n);

    for (int i = 0; i < MEASUREMENT_NUMBER; ++i) {
        printf("Measurements in progress... %d/%d done\r", i, MEASUREMENT_NUMBER);
        float result = lowDiffAvgTimeMeasure(fnc, scase, ARRAY_3D);

        if (result <= 0) {
            printf("\nFATAL: measurements failed!\n");
            fflush(stdin);
            getchar();
            exit(EFAULT);
        }

        VerifySorting();
        AddValue(result);
    }
    Deallocate3DArray();

    float processed = ProcessValues();

    DeallocTimeMeasurement();

    return processed;
}

static float do_measuring_vector(clock_t (*fnc)(), int scase, int n) {
    InitializeTimeMeasurement();
    AllocateVector(n);

    for (int i = 0; i < MEASUREMENT_NUMBER; ++i) {

        printf("Measurements in progress... %d/%d done\r", i, MEASUREMENT_NUMBER);

        float result = lowDiffAvgTimeMeasure(fnc, scase, ARRAY_VECTOR);

        if (result <= 0) {
            printf("\nFATAL: measurements failed!\n");
            fflush(stdin);
            getchar();
            exit(EFAULT);
        }

        VerifySortingVector();
        AddValue(result);
    }

    DeallocateVector();

    float processed = ProcessValues();

    DeallocTimeMeasurement();

    return processed;
}


void Debug_f() {
    int p = 0, m = 0, n = 0, t = 0, fill = 0;
    char alg[7];

    printf("Choose sorting algorithm [SELECT, HYBRID, SHELL]: ");
    scanf("%s", alg);

    printf("Choose fill type 1 for ordered 0 for random -1 for back ordered: ");
    scanf("%d", &fill); //magic numbers, див. settings.h також нижче.

    printf("Choose array type 0 for 3D, not 0 for vector: ");
    scanf("%d", &t);

    if (t) {
        printf("Enter vector length: ");
        scanf("%d", &n);
    } else {
        printf("Enter array dimensions (P M N) separated with space: ");
        scanf("%d %d %d", &p, &m, &n);
    }
    // Print the values entered by the user for debugging purposes
    printf("Sorting algorithm: %s\n", alg);
    printf("Array type: %s\n", t ? "vector" : "3D");
    if (t) {
        printf("Array dimensions: %d\n", n);
    } else {
        printf("Array dimensions: %d x %d x %d\n", p, m, n);
    }

    float result;
    switch (toupper(alg[1])) {
        case 'H':
            if (t) {
                result = do_measuring_vector(SortingShell_1_vector, fill, n);
                // Call function to sort vector using Shell sort
            } else {
                result = do_measuring_3d(SortingShell_1_3D, fill, p, m, n);
                // Call function to sort 3D array using Shell sort
            }
            break;
        case 'Y':
            if (t) {
                result = do_measuring_vector(SortingHybrid_1_exchange_vector, fill, n);
                // Call function to sort vector using Hybrid sort
            } else {
                result = do_measuring_3d(SortingHybrid_1_exchange, fill, p, m, n);
                // Call function to sort 3D array using Hybrid sort
            }
            break;
        case 'E':
            if (t) {
                result = do_measuring_vector(SortingSelect_6_vector, fill, n);
                // Call function to sort vector using Selection sort
            } else {
                result = do_measuring_3d(SortingSelect_6, fill, p, m, n);
                // Call function to sort 3D array using Selection sort
            }
            break;
        default:
            printf("Invalid sorting algorithm entered.\n");
            result = -1;
    }
    printf("\nMeasurement result: %f \nPress any key to return to main menu.\n", result);

    fflush(stdin);
    getchar();
}

void SelectSort_debug() {
    int t, p, m, n;

    printf("Choose array type 0 for 3D, not 0 for vector: ");
    scanf("%d", &t);

    if (t) {
        printf("Enter vector length: ");
        scanf("%d", &n);
    } else {
        printf("Enter array dimensions (P M N) separated with space: ");
        scanf("%d %d %d", &p, &m, &n);
    }

    // Measure the sorting time for different cases
    float sorted_time, random_time, back_sorted_time;

    if (t) {
        // Vector case
        sorted_time = do_measuring_vector(SortingSelect_6_vector, SORTED_CASE, n);
        random_time = do_measuring_vector(SortingSelect_6_vector, RANDOM_CASE, n);
        back_sorted_time = do_measuring_vector(SortingSelect_6_vector, BACK_SORTED_CASE, n);
    } else {
        // 3D array case
        sorted_time = do_measuring_3d(SortingSelect_6, SORTED_CASE, p, m, n);
        random_time = do_measuring_3d(SortingSelect_6, RANDOM_CASE, p, m, n);
        back_sorted_time = do_measuring_3d(SortingSelect_6, BACK_SORTED_CASE, p, m, n);
    }

    // Add the results to the spreadsheet
    InitSpreadsheet();
    AddRow("Selection sort #6", sorted_time, random_time, back_sorted_time);

    char c[64];

    if (t)
        sprintf(c, "Selection sorting results for vector sized %d:", n);
    else
        sprintf(c, "Selection sorting results for 3D array sized %d x %d x %d:", p, m, n);

    PintRows(c);
    DealocSpreadsheet();
}


void ShellSort_debug() {
    int t, p, m, n;

    printf("Choose array type 0 for 3D, not 0 for vector: ");
    scanf("%d", &t);

    if (t) {
        printf("Enter vector length: ");
        scanf("%d", &n);
    } else {
        printf("Enter array dimensions (P M N): ");
        scanf("%d %d %d", &p, &m, &n);
    }

    // Measure the sorting time for different cases
    float sorted_time, random_time, back_sorted_time;

    if (t) {
        // Vector case
        sorted_time = do_measuring_vector(SortingShell_1_vector, SORTED_CASE, n);
        random_time = do_measuring_vector(SortingShell_1_vector, RANDOM_CASE, n);
        back_sorted_time = do_measuring_vector(SortingShell_1_vector, BACK_SORTED_CASE, n);
    } else {
        // 3D array case
        sorted_time = do_measuring_3d(SortingShell_1_3D, SORTED_CASE, p, m, n);
        random_time = do_measuring_3d(SortingShell_1_3D, RANDOM_CASE, p, m, n);
        back_sorted_time = do_measuring_3d(SortingShell_1_3D, BACK_SORTED_CASE, p, m, n);
    }

    // Add the results to the spreadsheet
    InitSpreadsheet();
    AddRow("Shell sorting #1", sorted_time, random_time, back_sorted_time);
    char c[64];

    if (t)
        sprintf(c, "Shell sorting results for vector sized %d:", n);
    else
        sprintf(c, "Shell sorting results for 3D array sized %d x %d x %d:", p, m, n);

    PintRows(c);
    DealocSpreadsheet();
}

void HybridSort_exchange_debug() {
    int t, p, m, n;

    printf("Choose array type 0 for 3D, not 0 for vector: ");
    scanf("%d", &t);

    if (t) {
        printf("Enter vector length: ");
        scanf("%d", &n);
    } else {
        printf("Enter array dimensions (P M N): ");
        scanf("%d %d %d", &p, &m, &n);
    }

    // Measure the sorting time for different cases
    float sorted_time, random_time, back_sorted_time;

    if (t) {
        // Vector case
        sorted_time = do_measuring_vector(SortingHybrid_1_exchange_vector, SORTED_CASE, n);
        random_time = do_measuring_vector(SortingHybrid_1_exchange_vector, RANDOM_CASE, n);
        back_sorted_time = do_measuring_vector(SortingHybrid_1_exchange_vector, BACK_SORTED_CASE, n);
    } else {
        // 3D array case
        sorted_time = do_measuring_3d(SortingHybrid_1_exchange, SORTED_CASE, p, m, n);
        random_time = do_measuring_3d(SortingHybrid_1_exchange, RANDOM_CASE, p, m, n);
        back_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, BACK_SORTED_CASE, p, m, n);
    }

    // Add the results to the spreadsheet
    InitSpreadsheet();
    AddRow("Hybrid sorting (select #1 - exchange)", sorted_time, random_time, back_sorted_time);
    char c[64];

    if (t)
        sprintf(c, "Hybrid sorting (select #1 - exchange) results for vector sized %d:", n);
    else
        sprintf(c, "Hybrid sorting (select #1 - exchange) results for 3D array sized %d x %d x %d:", p, m, n);

    PintRows(c);
    DealocSpreadsheet();
}
