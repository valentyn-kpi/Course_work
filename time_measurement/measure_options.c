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
        printf("Measurements in progress... %d/%d done\t\r", i, MEASUREMENT_NUMBER);
        fflush(stdout);
        float result = lowDiffAvgTimeMeasure(fnc, scase, ARRAY_3D);

        if (result <= 0) {//результат виміру 0 або менше.
            printf("\nFATAL: measurements failed!\n");
            fflush(stdout);
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

/**
 * Отримання усереднених вимірів.
 * @param fnc Функція сортування вектора.
 * @param scase Випадок початкового заповнення.
 * @param n Довжина масиву.
 * @return Повертає оброблене значення вимірів часу.
 */
static float do_measuring_vector(clock_t (*fnc)(), int scase, int n) {
    InitializeTimeMeasurement();
    AllocateVector(n);

    for (int i = 0; i < MEASUREMENT_NUMBER; ++i) {

        printf("Measurements in progress... %d/%d done\t\r", i, MEASUREMENT_NUMBER);
        fflush(stdout);
        float result = lowDiffAvgTimeMeasure(fnc, scase, ARRAY_VECTOR);

        if (result <= 0) {
            printf("\nFATAL: measurements failed!\n");
            fflush(stdout);
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

/**
 * Повне налагодження всіх алгоритмів.
 */
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

    fflush(stdout);
    fflush(stdin);
}

/**
 * Налагодження алгоритму сортування вибором.
 */
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
    PrintRowsToFile(c, "Spreadsheets.txt");
    DealocSpreadsheet();

    fflush(stdout);
    fflush(stdin);
}

/**
 * Налагодження алгоритму сортування Шелла.
 */
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
    PrintRowsToFile(c, "Spreadsheets.txt");
    DealocSpreadsheet();

    fflush(stdout);
    fflush(stdin);
}

/**
 * Налагодження алгоритму гібридного алгоритму сортування.
 */
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
    AddRow("Hybrid sorting", sorted_time, random_time, back_sorted_time);
    char c[64];

    if (t)
        sprintf(c, "Hybrid sorting (select #1 - exchange) results for vector sized %d:", n);
    else
        sprintf(c, "Hybrid sorting (select #1 - exchange) results for 3D array sized %d x %d x %d:", p, m, n);

    PintRows(c);
    PrintRowsToFile(c, "Spreadsheets.txt");
    DealocSpreadsheet();

    fflush(stdout);
    fflush(stdin);
}


/**
 * Налагодження всіх алгоритмів.
 */
void All_debug() {
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
    float select_sorted_time, select_random_time, select_back_sorted_time;
    float shell_sorted_time, shell_random_time, shell_back_sorted_time;
    float hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time;

    if (t) {
        // Vector case
        select_sorted_time = do_measuring_vector(SortingSelect_6_vector, SORTED_CASE, n);
        select_random_time = do_measuring_vector(SortingSelect_6_vector, RANDOM_CASE, n);
        select_back_sorted_time = do_measuring_vector(SortingSelect_6_vector, BACK_SORTED_CASE, n);

        shell_sorted_time = do_measuring_vector(SortingShell_1_vector, SORTED_CASE, n);
        shell_random_time = do_measuring_vector(SortingShell_1_vector, RANDOM_CASE, n);
        shell_back_sorted_time = do_measuring_vector(SortingShell_1_vector, BACK_SORTED_CASE, n);

        hybrid_sorted_time = do_measuring_vector(SortingHybrid_1_exchange_vector, SORTED_CASE, n);
        hybrid_random_time = do_measuring_vector(SortingHybrid_1_exchange_vector, RANDOM_CASE, n);
        hybrid_back_sorted_time = do_measuring_vector(SortingHybrid_1_exchange_vector, BACK_SORTED_CASE, n);
    } else {
        // 3D array case
        select_sorted_time = do_measuring_3d(SortingSelect_6, SORTED_CASE, p, m, n);
        select_random_time = do_measuring_3d(SortingSelect_6, RANDOM_CASE, p, m, n);
        select_back_sorted_time = do_measuring_3d(SortingSelect_6, BACK_SORTED_CASE, p, m, n);

        shell_sorted_time = do_measuring_3d(SortingShell_1_3D, SORTED_CASE, p, m, n);
        shell_random_time = do_measuring_3d(SortingShell_1_3D, RANDOM_CASE, p, m, n);
        shell_back_sorted_time = do_measuring_3d(SortingShell_1_3D, BACK_SORTED_CASE, p, m, n);

        hybrid_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, SORTED_CASE, p, m, n);
        hybrid_random_time = do_measuring_3d(SortingHybrid_1_exchange, RANDOM_CASE, p, m, n);
        hybrid_back_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, BACK_SORTED_CASE, p, m, n);
    }

    // Add the results to the spreadsheet
    InitSpreadsheet();
    AddRow("Selection sort #10", select_sorted_time, select_random_time, select_back_sorted_time);
    AddRow("Hybrid sorting #18", hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time);
    AddRow("Shell sorting  #22", shell_sorted_time, shell_random_time, shell_back_sorted_time);
    char c[64];

    if (t)
        sprintf(c, "Full results for vector sized %d:", n);
    else
        sprintf(c, "Full results for 3D array sized %d x %d x %d:", p, m, n);

    PintRows(c);
    PrintRowsToFile(c, "Spreadsheets.txt");
    DealocSpreadsheet();

    fflush(stdout);
    fflush(stdin);
}

/**
 * Перший випадок дослідження.
 */
void FirstResearchCase() {
    const int P = CASE_P; // constant
    const int N = FIRST_CASE_N; // constant
    const int m_list[11] = {1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024};

    // Measure the sorting time for different cases
    float select_sorted_time, select_random_time, select_back_sorted_time;
    float shell_sorted_time, shell_random_time, shell_back_sorted_time;
    float hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time;

    // 3D array case
    for (int i = 0; i < 11; i++) {
        int m = m_list[i];
        select_sorted_time = do_measuring_3d(SortingSelect_6, SORTED_CASE, P, m, N);
        select_random_time = do_measuring_3d(SortingSelect_6, RANDOM_CASE, P, m, N);
        select_back_sorted_time = do_measuring_3d(SortingSelect_6, BACK_SORTED_CASE, P, m, N);

        shell_sorted_time = do_measuring_3d(SortingShell_1_3D, SORTED_CASE, P, m, N);
        shell_random_time = do_measuring_3d(SortingShell_1_3D, RANDOM_CASE, P, m, N);
        shell_back_sorted_time = do_measuring_3d(SortingShell_1_3D, BACK_SORTED_CASE, P, m, N);

        hybrid_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, SORTED_CASE, P, m, N);
        hybrid_random_time = do_measuring_3d(SortingHybrid_1_exchange, RANDOM_CASE, P, m, N);
        hybrid_back_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, BACK_SORTED_CASE, P, m, N);

        // Add the results to the spreadsheet
        InitSpreadsheet();

        AddRow("Selection sort #10", select_sorted_time, select_random_time, select_back_sorted_time);
        AddRow("Hybrid sorting #18", hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time);
        AddRow("Shell sorting  #22", shell_sorted_time, shell_random_time, shell_back_sorted_time);

        char c[64];
        sprintf(c, "Full results for 3D array sized %d x %d x %d:", P, m, N);
        PintRows(c);
        PrintRowsToFile(c, "Spreadsheets.txt");

        fflush(stdout);

        DealocSpreadsheet();
    }

    // Vector case
    select_sorted_time = (float) P * do_measuring_vector(SortingSelect_6_vector, SORTED_CASE, N);
    select_random_time = (float) P * do_measuring_vector(SortingSelect_6_vector, RANDOM_CASE, N);
    select_back_sorted_time = (float) P * do_measuring_vector(SortingSelect_6_vector, BACK_SORTED_CASE, N);

    shell_sorted_time = (float) P * do_measuring_vector(SortingShell_1_vector, SORTED_CASE, N);
    shell_random_time = (float) P * do_measuring_vector(SortingShell_1_vector, RANDOM_CASE, N);
    shell_back_sorted_time = (float) P * do_measuring_vector(SortingShell_1_vector, BACK_SORTED_CASE, N);

    hybrid_sorted_time = (float) P * do_measuring_vector(SortingHybrid_1_exchange_vector, SORTED_CASE, N);
    hybrid_random_time = (float) P * do_measuring_vector(SortingHybrid_1_exchange_vector, RANDOM_CASE, N);
    hybrid_back_sorted_time = (float) P * do_measuring_vector(SortingHybrid_1_exchange_vector, BACK_SORTED_CASE, N);

    // Add the results to the spreadsheet
    InitSpreadsheet();

    AddRow("Selection sort #10", select_sorted_time, select_random_time, select_back_sorted_time);
    AddRow("Hybrid sorting #18", hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time);
    AddRow("Shell sorting  #22", shell_sorted_time, shell_random_time, shell_back_sorted_time);

    char c[64];
    sprintf(c, "Full multiplied by %d results for vector sized %d:", P, N);
    PintRows(c);
    PrintRowsToFile(c, "Spreadsheets.txt");
    DealocSpreadsheet();

    fflush(stdout);
    fflush(stdin);
}

/**
 * Другий випадок дослідження.
 */
void SecondResearchCase() {
    const int P = CASE_P; // constant
    int M_values[5] = {10, 100, 1000, 10000, 100000};
    int N_values[5] = {100000, 10000, 1000, 100, 10};

// Measure the sorting time for different cases
    float select_sorted_time, select_random_time, select_back_sorted_time;
    float shell_sorted_time, shell_random_time, shell_back_sorted_time;
    float hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time;

    for (int i = 0; i < 5; i++) {
        int m = M_values[i];
        int n = N_values[i];
        select_sorted_time = do_measuring_3d(SortingSelect_6, SORTED_CASE, P, m, n);
        select_random_time = do_measuring_3d(SortingSelect_6, RANDOM_CASE, P, m, n);
        select_back_sorted_time = do_measuring_3d(SortingSelect_6, BACK_SORTED_CASE, P, m, n);

        shell_sorted_time = do_measuring_3d(SortingShell_1_3D, SORTED_CASE, P, m, n);
        shell_random_time = do_measuring_3d(SortingShell_1_3D, RANDOM_CASE, P, m, n);
        shell_back_sorted_time = do_measuring_3d(SortingShell_1_3D, BACK_SORTED_CASE, P, m, n);

        hybrid_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, SORTED_CASE, P, m, n);
        hybrid_random_time = do_measuring_3d(SortingHybrid_1_exchange, RANDOM_CASE, P, m, n);
        hybrid_back_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, BACK_SORTED_CASE, P, m, n);

        // Add the results to the spreadsheet
        InitSpreadsheet();

        AddRow("Selection sort #10", select_sorted_time, select_random_time, select_back_sorted_time);
        AddRow("Hybrid sorting #18", hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time);
        AddRow("Shell sorting  #22", shell_sorted_time, shell_random_time, shell_back_sorted_time);

        char c[64];
        sprintf(c, "Full results for 3D array sized %d x %d x %d:", P, m, n);
        PintRows(c);
        PrintRowsToFile(c, "Spreadsheets.txt");

        fflush(stdout);

        DealocSpreadsheet();
    }
}

/**
 * Третій випадок дослідження.
 */
void ThirdResearchCase() {
    const int M = CASE_M;
    int P_values[5] = {10, 100, 1000, 10000, 100000};
    int N_values[5] = {100000, 10000, 1000, 100, 10};

    // Measure the sorting time for different cases
    float select_sorted_time, select_random_time, select_back_sorted_time;
    float shell_sorted_time, shell_random_time, shell_back_sorted_time;
    float hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time;

    for (int i = 0; i < 5; i++) {
        int p = P_values[i];
        int n = N_values[i];
        select_sorted_time = do_measuring_3d(SortingSelect_6, SORTED_CASE, p, M, n);
        select_random_time = do_measuring_3d(SortingSelect_6, RANDOM_CASE, p, M, n);
        select_back_sorted_time = do_measuring_3d(SortingSelect_6, BACK_SORTED_CASE, p, M, n);

        shell_sorted_time = do_measuring_3d(SortingShell_1_3D, SORTED_CASE, p, M, n);
        shell_random_time = do_measuring_3d(SortingShell_1_3D, RANDOM_CASE, p, M, n);
        shell_back_sorted_time = do_measuring_3d(SortingShell_1_3D, BACK_SORTED_CASE, p, M, n);

        hybrid_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, SORTED_CASE, p, M, n);
        hybrid_random_time = do_measuring_3d(SortingHybrid_1_exchange, RANDOM_CASE, p, M, n);
        hybrid_back_sorted_time = do_measuring_3d(SortingHybrid_1_exchange, BACK_SORTED_CASE, p, M, n);

        // Add the results to the spreadsheet
        InitSpreadsheet();

        AddRow("Selection sort #10", select_sorted_time, select_random_time, select_back_sorted_time);
        AddRow("Hybrid sorting #18", hybrid_sorted_time, hybrid_random_time, hybrid_back_sorted_time);
        AddRow("Shell sorting  #22", shell_sorted_time, shell_random_time, shell_back_sorted_time);

        char c[64];
        sprintf(c, "Full results for 3D array sized %d x %d x %d:", p, M, n);
        PintRows(c);
        PrintRowsToFile(c, "Spreadsheets.txt");

        fflush(stdout);

        DealocSpreadsheet();
    }
}

void AllResearchCases() {
    FirstResearchCase();
    SecondResearchCase();
    ThirdResearchCase();
}