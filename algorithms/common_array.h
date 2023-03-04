//
// Created by Valentyn Valentiev on 2/18/2023.
//

#ifndef COURSE_WORK_COMMON_ARRAY_H
#define COURSE_WORK_COMMON_ARRAY_H

int GetDimension(char C);

void Allocate3DArray(int p, int m, int n);

int ***GetPointer_3DArray();

void Deallocate3DArray();

void Fill3DArray(int sort, unsigned int seed);

void VerifySorting();

void VerifySortingVector();

int *GetPointer_Vector();

void DeallocateVector();

void FillVector(int sort, unsigned int seed);

void AllocateVector(int n);

#endif //COURSE_WORK_COMMON_ARRAY_H
