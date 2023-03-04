//
// Created by Valentyn Valentiev on 2/17/2023.
//

#ifndef COURSE_WORK_SETTINGS_H
#define COURSE_WORK_SETTINGS_H

/**
 * Максимально допустима різниця у частинах від
 * одиниці(аналогічно 0.2% по дефолту - один тік на 500) між двома послідовним вимірами.
 **/
#define MAX_DIFFERENCE  0.002


/**
 * Максимально допустима кількість ітерацій.
 **/
#define MAX_ITERATIONS 30

/**
 * Кількість ітерацій виміру часу (кількість ітерацій сортування залежить
 * від стабільності комп'ютера та попереднього налаштування MAX_DIFFERENCE).
 */
#define MEASUREMENT_NUMBER 14

/**
 * Кількість відкинутих вимірів
 * з мінімальним та максимальним значенням.
 **/
#define MIN_MAX_NUMBER 2

/**
 * Кількість відкинутих початкових вимірів.
 **/
#define REJECTED_NUMBER 2

/**
 * Перевірити відсортованість після сортування.
 */
#define VERIFY_SORT

#define ARRAY_3D 1

#define ARRAY_VECTOR 0

#define WARM_UP_RUNS 1000000

/**
 * Кількість ключів для першого випадку дослідження.
 */
#define FIRST_CASE_N 50000

/**
 *Кількість перерізів для першого та другого випадку дослідження.
 */
#define FS_CASE_P 3

/**
 *Кількість рядків для третього випадку дослідження.
 */
#define THIRD_CASE_M 100

/**
 * Не виводити сміття в консоль.
 */
//#define SUP_DEBUG

#define BACK_SORTED_CASE (-1)
#define SORTED_CASE 1
#define RANDOM_CASE 0

#endif //COURSE_WORK_SETTINGS_H
