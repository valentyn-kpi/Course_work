//
// Created by Valentyn Valentiev on 2/18/2023.
//

#ifndef COURSE_WORK_SPREADSHEET_H
#define COURSE_WORK_SPREADSHEET_H

void InitSpreadsheet();

void AddRow(const char *name, float sorted, float random, float back_sorted);

void PintRows(const char *description);

void DealocSpreadsheet();

void PrintRowsToFile(const char *description, const char *filename);

#endif //COURSE_WORK_SPREADSHEET_H
