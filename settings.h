//
// Created by Valentyn Valentiev on 2/17/2023.
//

#ifndef COURSE_WORK_SETTINGS_H
#define COURSE_WORK_SETTINGS_H

/**
 * Максимально допустима різниця у частинах від
 * одиниці(аналогічно 0,1% по дефолту - один тік на 1000) між двома послідовним вимірами.
 **/
#define MAX_DIFFERENCE  0.001


/**
 * Максимально допустима кількість ітерацій
 **/
#define MAX_ITERATIONS 10

/**
 * Кількість ітерацій виміру часу (кількість ітерацій сортування залежить
 * від стабільності комп'ютера та попереднього налаштування MAX_DIFFERENCE).
 */
#define MEASUREMENT_NUMBER 10

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
