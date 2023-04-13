//
// Created by Valentyn Valentiev on 2/18/2023.
//

#ifndef COURSE_WORK_COMMON_ARRAY_H
#define COURSE_WORK_COMMON_ARRAY_H

void AllocateVector(int n);

void Allocate3DArray(int p, int m, int n);

int ***GetPointer_3DArray();

int *GetPointer_Vector();

int GetDimension(char C);

void FillVector(int sort, unsigned int seed);

void Fill3DArray(int sort, unsigned int seed);

void Deallocate3DArray();

void DeallocateVector();

#endif //COURSE_WORK_COMMON_ARRAY_H
