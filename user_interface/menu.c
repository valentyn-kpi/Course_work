//
// Created by Valentyn Valentiev on 2/17/2023.
//

#include "menu.h"
#include <stdio.h>
#include <stdlib.h>
#include "../settings.h"
#include <stdio.h>
#include <conio.h>

typedef struct menu_option {
    const char *name;

    void (*onEnter)();
} MenuOption;

static MenuOption *menu_options = NULL;
static short next_index = -1;

static void clear_screen() {
#ifdef SUP_DEBUG

#ifdef WIN32
    system("cls");
#else
    system("clear");
#endif

#endif
}

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

void PrintMenu() {
    if (next_index > -1) {
        clear_screen();
        printf("Select one option:\n");
        for (int i = 0; i < next_index; ++i) {
            printf("\t- Option %d: %s\n", i + 1, menu_options[i].name);
        }
        printf("\t- Option -1: Exit\n");
        printf("> ");
    } else {
        //not initialised
#ifndef SUP_DEBUG
        printf("Not initialized!\n");
#endif
    }
}

/**
 * Обробка вводу.
 * @param d - номер опції в меню
 */
void ProcessInput() {
    if (next_index > -1) {
        int d;
        while (1) {
            char buff[3];
            gets(buff);
            d = atoi(buff);
            if (d > 0 && d <= next_index) {
                clear_screen();

                menu_options[d - 1].onEnter();

                PrintMenu();
            } else if (d == -1) {
                break;
            } else {
                printf("Unlisted option. Use -1 to exit.\n\n> ");
            }

        }
    } else {
        //not initialised

#ifndef SUP_DEBUG
        printf("Not initialized!\n");
#endif
    }
}


