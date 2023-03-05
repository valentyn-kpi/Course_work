
#include "./user_interface/menu.h"
#include "./time_measurement/measure_options.h"

int main() {
    InitialiseMenu();//Ініціалізація меню.

    AddOption("Run any debug", Debug_f);
    AddOption("Run only select sorting (debug)", SelectSort_debug);
    AddOption("Run only hybrid sorting (select #1 - exchange)(debug)", HybridSort_exchange_debug);
    AddOption("Run only shell sorting (debug)", ShellSort_debug);
    AddOption("Run all sorting, build full table (debug)", All_debug);
    AddOption("First research case", FirstResearchCase);
    AddOption("Second research case", SecondResearchCase);
    AddOption("Third research case", ThirdResearchCase);
    AddOption("Full research", AllResearchCases);
    PrintMenu();    //Вивід меню.

    ProcessInput(); //Зациклення меню до виходу з нього. обробка вводу.

    DeallocateMenu();
    return 0;
}
