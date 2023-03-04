
#include "./user_interface/menu.h"
#include "./time_measurement/measure_options.h"

int main() {
    InitialiseMenu();//Ініціалізація меню.

    AddOption("Run full debug", Debug_f);

    PrintMenu();    //Вивід меню.

    ProcessInput(); //Зациклення меню до виходу з нього. обробка вводу.

    DeallocateMenu();
    return 0;
}
