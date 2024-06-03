
#include <stdio.h>
#include <stdlib.h>

#include "dynamic_type.h"
#include "dictionary.h"

int main(){
    printf("Hello, World!\n");

    Dictionary* test = Dictionary_c_init(12);

    printf("length: %d\nmaxLength: %d\ncontent: %p\n", test->length, test->maxLength, test->cont);

    Dictionary_n_uninit(test);

    return 0;
}

