//
// Created by Valentyn Valentiev on 2/17/2023.
//

#ifndef COURSE_WORK_SETTINGS_H
#define COURSE_WORK_SETTINGS_H

#include <errno.h>

/**
 * Максимально допустима різниця у частинах від
 * одиниці(аналогічно 0.1% по дефолту - один тік на 1000) між двома послідовним вимірами.
 **/
#define MAX_DIFFERENCE  0.001

/**
 * Максимально допустима кількість ітерацій двох послідовних вимірів.
 **/
#define MAX_ITERATIONS 30

/**
 * Кількість ітерацій виміру часу (кількість ітерацій сортування залежить
 * від стабільності комп'ютера та попереднього налаштування MAX_DIFFERENCE).
 */
#define MEASUREMENT_NUMBER 28

/**
 * Кількість відкинутих вимірів
 * з мінімальним та максимальним значенням.
 **/
#define MIN_MAX_NUMBER 3

/**
 * Кількість відкинутих початкових вимірів.
 **/
#define REJECTED_NUMBER 2

/**
 * Перевірити відсортованість після сортування.
 */
#define VERIFY_SORT

/**
 * Кількість ключів для першого випадку дослідження.
 */
#define FIRST_CASE_N 156250

/**
 *Кількість перерізів для першого та другого випадку дослідження.
 */
#define CASE_P 4

/**
 *Кількість рядків для третього випадку дослідження.
 */
#define CASE_M 100

/**
 * Не виводити сміття в консоль.
 */
#define SUP_DEBUG
#define SUP_ARRAY_PRINT


#define BACK_SORTED_CASE (-1)
#define SORTED_CASE 1
#define RANDOM_CASE 0
#define ARRAY_3D 1
#define ARRAY_VECTOR 0

#endif //COURSE_WORK_SETTINGS_H
