
#include "dynamic_type.h"

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
typedef struct{
    int length;
    int maxLength;
    DynamicNode* cont;
    int initialization; // whether or not the content was allocated with malloc
} DynamicArray;
#endif

/////////////////////////////////////////////////////////////////
/*
init (the first constructor requires recasting each element after initialization)
*/
// contents (the parameter) should be a NULL terminated array of pointers
DynamicArray* DynamicArray_c_init(void** contents);
DynamicArray* DynamicArray_r_init(void* ref, void** contents);
DynamicArray* DynamicArray_c_init_2(int length);
DynamicArray* DynamicArray_r_init_2(void* ref, int length);
/////////////////////////////////////////////////////////////////
/*
uninit
*/
int DynamicArray_n_uninit(DynamicArray* instance);
/////////////////////////////////////////////////////////////////
/*
becomes - sadly only copies the memory addresses. Does not make a deep copy of each element
*/
DynamicArray* DynamicArray_c_becomes(DynamicArray* instance);
DynamicArray* DynamicArray_r_becomes(DynamicArray* instance, void* ref);
/////////////////////////////////////////////////////////////////
/* WHETHER OR NOT THIS ACTS DIRECTLY ON AN ARRAY IS UNKNOWN. ALWAYS SET THE INSTANCE TO THE RESULT AFTER.
append - add an element to the end of a list. If the list is full, double its max size
*/
DynamicArray* DynamicArray_c_append(DynamicArray* instance, DynamicNode* element);
DynamicArray* DynamicArray_r_append(DynamicArray* instance, void* ref, DynamicNode* element);
/////////////////////////////////////////////////////////////////
/* WHETHER OR NOT THIS ACTS DIRECTLY ON AN ARRAY IS UNKNOWN. ALWAYS SET THE INSTANCE TO THE RESULT AFTER.
reverse - reverse an array
*/
DynamicArray* DynamicArray_c_reverse(DynamicArray* instance);
DynamicArray* DynamicArray_r_reverse(DynamicArray* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
pop - remove the last element from an array and return its value (if array is empty, return NULL)
*/
DynamicNode* DynamicArray_n_pop(DynamicArray* instance);
/////////////////////////////////////////////////////////////////
/*
remove
extend
sort
insert
clear
copy
count
index
*/
