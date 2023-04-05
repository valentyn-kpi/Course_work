//
// Created by Valentyn Valentiev on 2/17/2023.
//

/*
 * Модуль додавання пунктів меню, його виведення
 * обробка команд користувача.
 */

#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "../settings.h"

typedef struct menu_option {
    const char *name;

    void (*onEnter)();
} MenuOption;

static MenuOption *menu_options = NULL;
static short next_index = -1;


/**
 * Ініціалізація меню.
 */
void InitialiseMenu() {
    if (next_index == -1) {
        menu_options = malloc(0);
        next_index = 0;
    } else {
        //already initialised
#ifndef SUP_DEBUG
        printf("Tried to re-init!\n");
#endif
    }
}

/**
 * Додати опцію до меню.
 * @param name - назва та/або короткий опис опції.
 * @param onEnter - функція, що викликається при виборі даної опції.
 */
void AddOption(const char *name, void (*onEnter)()) {
    if (next_index > -1) {
        menu_options = realloc(menu_options, (next_index + 1) * sizeof(MenuOption));

        menu_options[next_index].name = name;
        menu_options[next_index].onEnter = onEnter;

        next_index++;
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized values lost!\n");
#endif
    }
}

/**
 * Звільнення ресурсів зайнятих меню.
 */
void DeallocateMenu() {
    if (next_index > -1) {
        free(menu_options);
        menu_options = NULL;
        next_index = -1;
    } else {
        //already deallocated
#ifndef SUP_DEBUG
        printf("Tried to re-dealloc!\n");
#endif
    }
}

/**
 * Вивід меню.
 */
void PrintMenu() {
    if (next_index > -1) {
        printf("Select one option:\n");
        for (int i = 0; i < next_index; ++i) {
            printf("\t- Option %d: %s\n", i + 1, menu_options[i].name);
        }
        printf("\t- Option -1: Exit\n\n");
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized!\n");
#endif
    }
    fflush(stdout);
    fflush(stdin);
}

/**
 * Обробка вводу.
 */
void ProcessInput() {
    if (next_index < 0) {
#ifndef SUP_DEBUG
        printf("Error: menu not initialized!\n");
#endif
        return;
    }

    int d;
    while (1) {
        fflush(stdout);
        fflush(stdin);

        printf("> ");
        if (scanf("%d", &d) != 1) {
            printf("Error: invalid input!\n");
            fflush(stdout);
            fflush(stdin);
            continue;
        }

        // Handle user input
        if (d > 0 && d <= next_index) {

            menu_options[d - 1].onEnter();
            PrintMenu();
        } else if (d == -1) {
            break;
        } else {
            printf("Error: invalid option selected!\n");
        }
    }
}
