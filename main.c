
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_type.h"
#include "stack.h"


int main(){
    printf("Hello, World!\n");

    // create an empty stack
    Stack* test = Stack_c_init_2(0); 

    // Create a DynamicNode object that holds an integer
    int testInt = 5;
    DynamicNode* data = DynamicNode_c_init(CINT, &testInt);
    test = Stack_c_push(test, data);

    printf("%s\n", DynamicNode_n_toString(data));

    DynamicNode_n_uninit(data);

    return 0;
}
