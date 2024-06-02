#ifndef STACK_H
#define STACK_H

#include "dynamic_type.h"
#include "dynamic_array.h"

#ifndef STACK
#define STACK
typedef struct{ // stack is simply a dynamic array with fewer functions
    DynamicArray* cont;
} Stack;
#endif

/////////////////////////////////////////////////////////////////
/*
init
*/
Stack* Stack_c_init(void** contents);
Stack* Stack_r_init(void* ref, void** contents);
Stack* Stack_c_init_2(int length);
Stack* Stack_r_init_2(void* ref, int length);
/////////////////////////////////////////////////////////////////
/*
uninit
*/
int Stack_n_uninit(Stack* instance);
/////////////////////////////////////////////////////////////////
/*
becomes
*/
Stack* Stack_c_becomes(Stack* instance);
Stack* Stack_r_becomes(Stack* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
push - add an element to the end of the stack
*/
Stack* Stack_c_push(Stack* instance, void* element);
Stack* Stack_r_push(Stack* instance, void* ref, void* element);
/////////////////////////////////////////////////////////////////
/*
pop - remove an element from the end of the stack (returns NULL for an empty stack)
*/
DynamicNode* Stack_n_pop(Stack* instance);
/////////////////////////////////////////////////////////////////
/*
peek
*/
DynamicNode* Stack_n_peek(Stack* instance);
/////////////////////////////////////////////////////////////////

#endif
