#ifndef _DARRAY_H
#define _DARRAY_H
#include <stddef.h>

typedef struct{
    void** data;
    size_t size;
    size_t max_size;
} DArray;

DArray* createDArray();
void appendDA(DArray* arr, void* element);
void removeDA(DArray* arr, size_t index);
void insertDA(DArray* arr, void* element, size_t index);
void doubleSizeDA(DArray* arr);
void freeDA(DArray** arr);
void printDA(DArray arr, void (*print_fun)(void*));

#endif
