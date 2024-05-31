/*
This file will handle the dynamic array implementation
This implementation will simply be an array of structures that point to data
The data field of the structure should be casted to a pointer to whatever the data is
They are initialized as NULL pointers and append operations double the size of a full Array
This implementation has slow deletes and inserts, but has fast retrieval using indexes
(basically a normal array in C but allows data of different types
*/




#include <stdlib.h>
#include <string.h>

#include "dynamic_array.h"

#ifndef DYNAMIC_TYPE
#define DYNAMIC_TYPE
typedef enum{
   STR,
   INT,
   DARR,
} DynamicType;
#endif

#ifndef DYNAMIC_NODE
#define DYNAMIC_NODE
typedef struct{
    DynamicType type;
    void* data;
} DynamicNode;
#endif

#ifndef DYNAMIC_ARRAY
#define DYNAMIC_ARRAY
typedef struct{
    int length;
    int maxLength;
    DynamicNode* cont;
} DynamicArray;
#endif

/////////////////////////////////////////////////////////////////
/*
init (the first constructor requires recasting each element after initialization)
*/
// contents (the parameter) should be a NULL terminated array of pointers
DynamicArray* DynamicArray_c_init(void** contents){
    DynamicArray* result = malloc(sizeof(DynamicArray));
    
    // cheating the system by casting to char array
    char** cheating = (char**) contents;

    int i=0;
    while (cheating[i] != NULL){
        i++;
    }
    result->length = i+1;
    // set the max size to the next biggest power of 2, starting at 16
    if (result->length < 16){
        result->maxLength = 16;
    } else {
        int next = 1;
        while (result->length > next){
            next <<= 1;
        }
        result->maxLength = next;
    }

    result->cont = (DynamicNode*) malloc(sizeof(DynamicNode) * result->maxLength);

    memcpy(result->cont, contents, result->length * sizeof(DynamicNode));
    for (int i=result->length; i<result->maxLength; i++){
        (result->cont[i]).data = NULL;
        (result->cont[i]).type = -1;
    }

    return result;
}

DynamicArray* DynamicArray_r_init(void* ref, void** contents){
    DynamicArray* result = (DynamicArray*) ref;
    
    // cheating the system by casting to char array
    char** cheating = (char**) contents;

    int i=0;
    while (cheating[i] != NULL){
        i++;
    }
    result->length = i+1;
    // set the max size to the next biggest power of 2, starting at 16
    if (result->length < 16){
        result->maxLength = 16;
    } else {
        int next = 1;
        while (result->length > next){
            next <<= 1;
        }
        result->maxLength = next;
    }

    result->cont = (DynamicNode*) (((char*) ref) + sizeof(DynamicArray));

    memmove(result->cont, contents, result->length * sizeof(DynamicNode));
    for (int i=result->length; i<result->maxLength; i++){
        (result->cont[i]).data = NULL;
        result->cont[i].type = -1;
    }

    return result;
}

DynamicArray* DynamicArray_c_init_2(int length){
    DynamicArray* result = malloc(sizeof(DynamicArray));

    result->length = length;
    
    // set the max size to the next biggest power of 2, starting at 16
    if (result->length < 16){
        result->maxLength = 16;
    } else {
        int next = 1;
        while (result->length > next){
            next <<= 1;
        }
        result->maxLength = next;
    }

    result->cont = (DynamicNode*) malloc(sizeof(DynamicNode) * result->maxLength);

    for (int i=0; i<result->maxLength; i++){
        (result->cont[i]).data = NULL;
        result->cont[i].type = -1;
    }

    return result;
}

DynamicArray* DynamicArray_r_init_2(void* ref, int length){
    DynamicArray* result = (DynamicArray*) ref;

    result->length = length;
    
    // set the max size to the next biggest power of 2, starting at 16
    if (result->length < 16){
        result->maxLength = 16;
    } else {
        int next = 1;
        while (result->length > next){
            next <<= 1;
        }
        result->maxLength = next;
    }

    result->cont = (DynamicNode*) (((char*) ref) + sizeof(DynamicArray));

    for (int i=0; i<result->maxLength; i++){
        (result->cont[i]).data = NULL;
        result->cont[i].type = -1;
    }

    return result;
}

/////////////////////////////////////////////////////////////////
/*
uninit
*/
int DynamicArray_n_uninit(DynamicArray* instance){
    free(instance->cont);
    free(instance);
    return 0;
}


/////////////////////////////////////////////////////////////////
/*
becomes - sadly only copies the memory addresses. Does not make a deep copy of each element
*/
DynamicArray* DynamicArray_c_becomes(DynamicArray* instance){
    DynamicArray* result = (DynamicArray*) malloc(sizeof(DynamicArray));

    result->length = instance->length;
    result->maxLength = instance->maxLength;
    result->cont = malloc(sizeof(char*) * result->maxLength);
    memcpy(result->cont, instance->cont, instance->maxLength * sizeof(char*));
    
    return result;
}

DynamicArray* DynamicArray_r_becomes(DynamicArray* instance, void* ref){
    DynamicArray* result = (DynamicArray*) ref;

    if (ref != instance){
        result->length = instance->length;
        result->maxLength = instance->maxLength;
        result->cont = (DynamicNode*) (((char*) ref) + sizeof(DynamicArray));
        memmove(result->cont, instance->cont, instance->maxLength * sizeof(char*));
        return result;
    } else {
        return instance;
    }
}


/////////////////////////////////////////////////////////////////
/* OPERATES DIRECTLY ON AN ARRAY
append - add an element to the end of a list. If the list is full, double its max size
*/
DynamicArray* DynamicArray_c_append(DynamicArray* instance, void* element){
    // if we need to double the array first
    DynamicArray* result;
    if (instance->length == instance->maxLength){ 
        // create a new array
        result = DynamicArray_c_init_2(instance->maxLen+1);
        memcpy(result->cont, instance->cont, instance->maxLen * sizeof(DynamicNode));
        result->length = instance->length;
        DynamicArray_n_uninit(instance);
    }
}


/////////////////////////////////////////////////////////////////
/*
extend
sort
reverse
insert
pop
remove
clear
copy
count
index
*/

#include <stdio.h>


int main(){
    void* memspace = malloc(65536);

    DynamicArray* test = DynamicArray_r_init_2(memspace, 2);

    char* data = "Hello, World!";
    int data2 = 5;

    (test->cont[0]).data = data;
    test->cont[0].type = STR;
    (test->cont[1]).data = &data2;
    test->cont[1].type = INT;

    printf("Length of array: %d\n", test->length);
    for (int i=0; i<test->length; i++){
        switch(test->cont[i].type){
            case 0:
                printf("%s\n", ((char*) test->cont[i].data));
                break;
            case 1:
                printf("%d\n", *((int*)test->cont[i].data));
                break;
            default:
                printf("This element is not printable");
                break;
        }
    }

    free(memspace);
    return 0;
}


