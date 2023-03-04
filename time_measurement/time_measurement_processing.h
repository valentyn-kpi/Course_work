//
// Created by Valentyn Valentiev on 2/14/2023.
//

#ifndef COURSE_WORK_TIME_MEASUREMENT_PROCESSING_H
#define COURSE_WORK_TIME_MEASUREMENT_PROCESSING_H

#include <time.h>

void InitializeTimeMeasurement();

void AddValue(float value);

void DeallocTimeMeasurement();

void ClearTimeMeasurement();

float ProcessValues();

float lowDiffAvgTimeMeasure(clock_t (*fnc)(), int scase, int array_type);

#endif //COURSE_WORK_TIME_MEASUREMENT_PROCESSING_H
