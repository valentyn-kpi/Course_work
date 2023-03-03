//
// Created by Valentyn Valentiev on 2/17/2023.
//

#ifndef COURSE_WORK_MENU_H
#define COURSE_WORK_MENU_H


void InitialiseMenu();

void AddOption(const char *name, void (*onEnter)());

void DeallocateMenu();

void PrintMenu();

void ProcessInput();

#endif //COURSE_WORK_MENU_H
