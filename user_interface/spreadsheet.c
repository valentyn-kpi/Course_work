//
// Created by Valentyn Valentiev on 2/18/2023.
//

#include "spreadsheet.h"
#include "stdlib.h"
#include "stdio.h"

typedef struct row {
    const char *name;
    float sorted;
    float random;
    float back_sorted;
} ROW;

static ROW *rows = NULL;
static int next_index = -1;

/**
 * Ініціалізація таблиці.
 */
void InitSpreadsheet() {
    if (next_index == -1) {
        rows = malloc(0);
        next_index = 0;
    } else {
        //already initialised
#ifndef SUP_DEBUG
        printf("Tried to re-init!\n");
#endif
    }
}

/**
 * Додавання рядку до таблиці.
 * @param name - назва алгоритму
 * @param sorted - час сортування впорядкованого
 * @param random - час сортування невпорядкованого
 * @param back_sorted - час сортування обернено впорядкованого
 */
void AddRow(const char *name, float sorted, float random, float back_sorted) {
    if (next_index > -1) {
        rows = realloc(rows, (next_index + 1) * sizeof(ROW));

        rows[next_index].name = name;
        rows[next_index].sorted = sorted;
        rows[next_index].random = random;
        rows[next_index].back_sorted = back_sorted;

        next_index++;
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized values lost!\n");
#endif
    }
}

/**
 * Вивід таблиці
 * @param description опис таблиці
 */
void PintRows(const char* description) {
    const char* headers[] = {"Sorted", "Random", "Back-sorted"};
    // Print the table header
    printf("\n%s\n\n", description);
    printf("%-30s", "Algorithm");

    const int num_cols = sizeof(headers) / sizeof(headers[0]);
    for (int i = 0; i < num_cols; ++i) {
        printf("%-15s", headers[i]);
    }
    printf("\n");

    // Print the table body
    for (int i = 0; i < next_index; ++i) {
        printf("%-30s", rows[i].name);
        printf("%-15.3f", rows[i].sorted);
        printf("%-15.3f", rows[i].random);
        printf("%-15.3f", rows[i].back_sorted);
        printf("\n");
    }

    // Print some blank lines to separate the table from any other output
    printf("\n\n");
}

/**
 * Звільнення пам'яті зайнятої таблицею.
 */
void DealocSpreadsheet() {
    if (next_index > -1) {
        free(rows);
        rows = NULL;
        next_index = -1;
    } else {
        //already deallocated
#ifndef SUP_DEBUG
        printf("Tried to re-dealloc!\n");
#endif
    }
}