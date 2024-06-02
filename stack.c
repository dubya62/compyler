
#include <stdlib.h>
#include <string.h>


#include "stack.h"


/////////////////////////////////////////////////////////////////
/*
init
*/
Stack* Stack_c_init(void** contents){
    Stack* result = (Stack*) malloc(sizeof(Stack));
    result->cont = DynamicArray_c_init(contents);
    return result;
}

Stack* Stack_r_init(void* ref, void** contents){
    Stack* result = (Stack*) ref;
    result->cont = DynamicArray_r_init(ref, contents);
    return result;
}

Stack* Stack_c_init_2(int length){
    Stack* result = (Stack*) malloc(sizeof(Stack));
    result->cont = DynamicArray_c_init_2(length);
    return result;
}

Stack* Stack_r_init_2(void* ref, int length){
    Stack* result = (Stack*) ref;
    result->cont = DynamicArray_r_init_2(ref, length);
    return result;
}

/////////////////////////////////////////////////////////////////
/*
uninit
*/
int Stack_n_uninit(Stack* instance){
    DynamicArray_n_uninit(instance->cont);
    free(instance);
    return 0;
}

/////////////////////////////////////////////////////////////////
/*
becomes
*/
Stack* Stack_c_becomes(Stack* instance){
    Stack* result = (Stack*) malloc(sizeof(Stack));
    result->cont = DynamicArray_c_becomes(instance->cont);
    return result;
}
Stack* Stack_r_becomes(Stack* instance, void* ref){
    Stack* result = (Stack*) ref;
    result->cont = DynamicArray_r_becomes(instance->cont, result+1);
    return result;
}

/////////////////////////////////////////////////////////////////
/*
push - add an element to the end of the stack
*/
Stack* Stack_c_push(Stack* instance, void* element){
    instance->cont = DynamicArray_c_append(instance->cont, element);
    return instance;
}
Stack* Stack_r_push(Stack* instance, void* ref, void* element){
    instance->cont = DynamicArray_r_append(instance->cont, ref, element);
    return instance;
}

/////////////////////////////////////////////////////////////////
/*
pop - remove an element from the end of the stack (returns NULL for an empty stack)
*/
DynamicNode* Stack_n_pop(Stack* instance){
    return DynamicArray_n_pop(instance->cont);
}

/////////////////////////////////////////////////////////////////
/*
peek
*/
DynamicNode* Stack_n_peek(Stack* instance){
    int n = instance->cont->length;
    if (!n){
        return NULL;
    }
    return &(instance->cont->cont[n-1]);
}

/////////////////////////////////////////////////////////////////



