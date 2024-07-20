#include "darray.h"
#include <stdlib.h>
#include <stddef.h>
#include <sys/types.h>
#include <stdio.h>

DArray createDArray(){
    DArray arr;
    arr.max_size = 4;
    arr.data = malloc(sizeof(void*) * arr.max_size);
    arr.size = 0;

    return arr;
}

void doubleSizeDA(DArray* arr){
    arr->max_size *= 2; 
    arr->data = realloc(arr->data, sizeof(void*) * arr->max_size);
}

void appendDA(DArray* arr, void* element){
    if(arr->max_size == arr->size) doubleSizeDA(arr);
    arr->data[arr->size++] = element;
}

void freeDA(DArray* arr){
    for(size_t i=0; i<arr->size; i++) free(arr->data[i]);
    free(arr->data);
    arr->data = NULL;
    arr->size = 0;
    arr->max_size = 0;
}

void removeDA(DArray* arr, size_t index){
    if(index >= arr->size) return;
    free(arr->data[index]);
    for(size_t i=index; i<arr->size-1; i++){
        arr->data[i] = arr->data[i+1];
    }
    arr->size--;
}

void insertDA(DArray* arr, void* element, size_t index){
    if(arr->max_size == arr->size) doubleSizeDA(arr);
    for(size_t i = arr->size; i > index; i--){
        arr->data[i] = arr->data[i-1];
    }
    arr->data[index] = element;
    arr->size++;
}

void printDA(DArray arr, void (*print_fun)(void*)){
    for(size_t i=0; i<arr.size; i++) (*print_fun)(arr.data[i]);
}
