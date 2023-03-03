#include <stdio.h>
#include "./user_interface/menu.h"
#include "./time_measurement/measure_options.h"

void foo() {
    printf("Pizdec called!");
}

void death() {
    printf("You died!");
}

int main() {
    InitialiseMenu();//Ініціалізація меню.

    AddOption("Run full debug", Debug_f);

    PrintMenu();    //Вивід меню.

    ProcessInput(); //Зациклення меню до виходу з нього. обробка вводу.

    DeallocateMenu();

    getchar();
    return 0;
}
