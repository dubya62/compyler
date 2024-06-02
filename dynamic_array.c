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
#include "dynamic_type.h"


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
    int initialization; // whether or not the content was allocated with malloc
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
    result->initialization = 1; // it was malloc'ed

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
    result->initialization = 0; // it was not malloc'ed

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
    result->initialization = 1; // was malloc'ed

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
    result->initialization = 0; // was not malloc'ed

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
/* WHETHER OR NOT THIS ACTS DIRECTLY ON AN ARRAY IS UNKNOWN. ALWAYS SET THE INSTANCE TO THE RESULT AFTER.
append - add an element to the end of a list. If the list is full, double its max size
*/
DynamicArray* DynamicArray_c_append(DynamicArray* instance, DynamicNode* element){
    // if we need to double the array first
    if (instance->length == instance->maxLength){
        // create space with double the size
        int newMaxLen = instance->maxLength << 1;
        DynamicNode* newSpace = (DynamicNode*) malloc(newMaxLen * sizeof(DynamicNode));
        
        // copy the data over
        memcpy(newSpace, instance->cont, instance->length * sizeof(DynamicNode));
        if (instance->initialization){ // if the result's content was created with malloc
            free(instance->cont);
        }
        instance->cont = newSpace;
        instance->maxLength = newMaxLen;
        instance->initialization = 1;
    }

    instance->cont[instance->length] = *element;
    instance->length++;

    return instance;
}

DynamicArray* DynamicArray_r_append(DynamicArray* instance, void* ref, DynamicNode* element){
    DynamicArray* result = (DynamicArray*) ref;

    if (instance != ref){ // if the instance is not at ref already
        int newSize = result->maxLength << 1;
        result->initialization = 0;
        result->length = instance->length;
        result->maxLength = instance->maxLength;
        if (instance->length == instance->maxLength){
            result->maxLength <<= 1;
        } 
        result->cont = (DynamicNode*) (result + sizeof(DynamicArray));

        memmove(result->cont, instance->cont, instance->length * sizeof(DynamicNode));
        // if the content was malloc'ed
        if (instance->initialization){
            DynamicArray_n_uninit(instance);
        } else {
            // do nothing
        }
    } else { // otherwise, just get more space
        // do nothing
    }

    result->cont[result->length] = *element;
    result->length++;

    return result;
}


/////////////////////////////////////////////////////////////////
/* WHETHER OR NOT THIS ACTS DIRECTLY ON AN ARRAY IS UNKNOWN. ALWAYS SET THE INSTANCE TO THE RESULT AFTER.
reverse - reverse an array
*/
DynamicArray* DynamicArray_c_reverse(DynamicArray* instance){
    int halfway = instance->length >> 1;
    DynamicNode* temp = malloc(sizeof(DynamicNode));
    int back = instance->length-1;
    for (int i=0; i<halfway; i++, back--){
        memcpy(temp, &(instance->cont[i]), sizeof(DynamicNode));
        memcpy(&(instance->cont[i]), &(instance->cont[back]), sizeof(DynamicNode));
        memcpy(&(instance->cont[back]), temp, sizeof(DynamicNode));
    }
    free(temp);
    return instance;
}

DynamicArray* DynamicArray_r_reverse(DynamicArray* instance, void* ref){
    DynamicArray* result = (DynamicArray*) ref;
    if (result != instance){
        DynamicArray_r_becomes(instance, result);
        if (instance->initialization){
            DynamicArray_n_uninit(instance);
        }
    }
    int halfway = result->length >> 1;
    DynamicNode* temp = malloc(sizeof(DynamicNode));
    int back = result->length-1;
    for (int i=0; i<halfway; i++, back--){
        memcpy(temp, &(result->cont[i]), sizeof(DynamicNode));
        memcpy(&(result->cont[i]), &(result->cont[back]), sizeof(DynamicNode));
        memcpy(&(result->cont[back]), temp, sizeof(DynamicNode));
    }
    free(temp);
    return result;
}

/////////////////////////////////////////////////////////////////
/*
pop - remove the last element from an array and return its value (if array is empty, return NULL)
*/
DynamicNode* DynamicArray_n_pop(DynamicArray* instance){
    if (instance->length == 0){
        return NULL;
    }
    instance->length--;
    return &(instance->cont[instance->length]);
}


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


