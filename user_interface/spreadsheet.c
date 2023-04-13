//spreadsheet.c
//
// Created by Valentyn Valentiev on 2/18/2023.
//

/*
 * Модуль збереження результатів виміру
 * Вивід таблиць у файл та у консоль.
 */

#include "spreadsheet.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct row {
    const char *name;
    float sorted;
    float random;
    float back_sorted;
} ROW;
//алгоритм, час сортування впорядкованого, час сортування невпорядкованого, час сортування обернено впорядкованого

static ROW *rows = NULL;
static int next_index = -1;
static char *headers[3];// = {"Sorted", "Random", "Back-sorted"};

/**
 * Ініціалізація таблиці.
 * @param header - масив з трьома елементами, які будуть використані як заголовки стовпців
 */
void InitSpreadsheet(char *header[]) {
    if (next_index == -1) {
        rows = malloc(0);
        next_index = 0;
        headers[0] = header[0];
        headers[1] = header[1];
        headers[2] = header[2];
    } else {
        //already initialised
#ifndef SUP_DEBUG
        printf("Tried to re-init!\n");
        fflush(stdout);
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
        fflush(stdout);
#endif
    }
}

/**
 * Вивід таблиці
 * @param description опис таблиці
 */
void PintRows(const char *description) {
    // Print the table header
    printf("\n%s\n\n", description);
    printf("%-30s", "Algorithm");

    const int num_cols = sizeof(headers) / sizeof(headers[0]);
    for (int i = 0; i < num_cols; ++i) {
        printf("%-30s", headers[i]);
    }
    printf("\n\n");
    // Print the table body
    for (int i = 0; i < next_index; ++i) {
        printf("%-30s", rows[i].name);
        printf("%30.3f", rows[i].sorted);
        printf("%30.3f", rows[i].random);
        printf("%30.3f", rows[i].back_sorted);
        printf("\n");
    }

    // Print some blank lines to separate the table from any other output
    printf("\n\n");

    fflush(stdout);
    fflush(stdin);
}

/**
 * Вивід таблиці у файл.
 * @param description опис таблиці
 * @param filename ім'я файлу.
 */
void PrintRowsToFile(const char *description, const char *filename) {
    // Open the file in append mode
    FILE *fp = fopen(filename, "a");
    if (fp == NULL) {
        perror("Error opening file");
        return;
    }

    // Print the table header to the file
    fprintf(fp, "\n%s\n\n", description);
    fprintf(fp, "%-30s", "Algorithm");

    const int num_cols = sizeof(headers) / sizeof(headers[0]);
    for (int i = 0; i < num_cols; ++i) {
        fprintf(fp, "%30s", headers[i]);
    }
    fprintf(fp, "\n\n");

    // Print the table body to the file
    for (int i = 0; i < next_index; ++i) {
        fprintf(fp, "%-30s", rows[i].name);
        fprintf(fp, "%30.3f", rows[i].sorted);
        fprintf(fp, "%30.3f", rows[i].random);
        fprintf(fp, "%30.3f", rows[i].back_sorted);
        fprintf(fp, "\n");
    }

    // Close the file
    fclose(fp);
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
        fflush(stdout);
#endif
    }
}