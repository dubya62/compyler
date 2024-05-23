// This file is for static integers
// In some cases, normal integers in C work fine, 
// but integers in python are not limited by 32 or 64 bits
// This file is for large integers who cannot request more memory after being created

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "sint.h"

#ifndef SINT
#define SINT
typedef struct {
    int length; // the number of elements in the array
    int sign; 
    unsigned int* cont;
} sint;
#endif


/////////////////////////////////////////////////////////////////
/*
init
*/
// initialize based on a given normal integer value
sint* sint_c_init(int val){
    sint* result = malloc(sizeof(sint));
    result->length = 1;
    if (val < 0){
        result->sign = 1;
        val = -val;
    } else {
        result->sign = 0;
    }

    result->cont = malloc(sizeof(unsigned int) * result->length);
    result->cont[0] = val;
    
    return result;
}

sint* sint_r_init(void* ref, int val){
    sint* result = (sint*) ref;
    result->length = 1;
    if (val < 0){
        result->sign = 1;
        val = -val;
    } else {
        result->sign = 0;
    }

    result->cont = ref + sizeof(sint);
    result->cont[0] = val;
    
    return result;
}

sint* sint_c_init_2(int len){
    sint* result = malloc(sizeof(sint));
    result->length = len;
    result->sign = 0;

    result->cont = malloc(sizeof(unsigned int) * result->length);
    for (int i=0; i<result->length; i++){
        result->cont[i] = 0;
    }
    
    return result;
}

sint* sint_r_init_2(void* ref, int len){
    sint* result = (sint*) ref;
    result->length = len;
    result->sign = 0;

    result->cont = ref + sizeof(sint);
    for (int i=0; i<result->length; i++){
        result->cont[i] = 0;
    }

    return result;
}


/////////////////////////////////////////////////////////////////
/*
uninit
*/
int sint_n_uninit(sint* instance){
    free(instance->cont);
    free(instance);
    return 0;
}


/////////////////////////////////////////////////////////////////
/*
becomes
*/
sint* sint_c_becomes(sint* instance){
    sint* result = sint_c_init_2(instance->length);
    result->length = instance->length;
    result->sign = instance->sign;

    memcpy(result->cont, instance->cont, sizeof(unsigned int) * instance->length);
    
    return result;
}

sint* sint_r_becomes(sint* instance, void* ref){
    sint* result = (sint*) ref;
    result->length = instance->length;
    result->sign = instance->sign;
    result->cont = ref + sizeof(sint);

    memmove(result->cont, instance->cont, sizeof(unsigned int) * instance->length);
    
    return result;
}


/////////////////////////////////////////////////////////////////
/*
operators:
*/
/////////////////////////////////////////////////////////////////
/*
lt
*/
int sint_n_lt(sint* first, sint* second){
    // check the sign first
    if (first->sign != second->sign){
        if (first->sign){
            return 1;
        }
        return 0;
    }

    // figure out which one has more space allocated
    int diff = first->length - second->length;
    int ndiff = -diff;
    int bigger;
    int smallLen = 0;
    if (diff > 0){ // check the most significant digits first
        for (int i=0; i<diff; i++){
            if (first->cont[i]){
                if (first->sign){
                    return 1;
                } else {
                    return 0;
                }
            }
        }
        bigger = 0;
        smallLen = second->length;
    } else {
        for (int i=0; i<ndiff; i++){
            if (second->cont[i]){
                if (second->sign){
                    return 0;
                } else {
                    return 1;
                }
            }
        }
        bigger = 1;
        smallLen = first->length;
    }
    // now we are even. Check with the MSB of each
    if (bigger){
        for (int i=0; i<smallLen; i++){
            unsigned int fir = first->cont[i];
            unsigned int sec = second->cont[i+ndiff];
            if (fir == sec){
                continue;
            }
            int result = (fir < sec);
            if (first->sign){
                return !result;
            } else {
                return result;
            }
        }
    } else {
        for (int i=0; i<smallLen; i++){
            unsigned int fir = first->cont[i+diff];
            unsigned int sec = second->cont[i];
            if (fir == sec){
                continue;
            }
            int result = (fir < sec);
            if (first->sign){
                return !result;
            } else {
                return result;
            }
        }

    }

    return 0;
}


/////////////////////////////////////////////////////////////////
/*
gt
*/
int sint_n_gt(sint* first, sint* second){
    // check the sign first
    if (first->sign != second->sign){
        if (first->sign){
            return 0;
        }
        return 1;
    }

    // figure out which one has more space allocated
    int diff = first->length - second->length;
    int ndiff = -diff;
    int bigger;
    int smallLen = 0;
    if (diff > 0){ // check the most significant digits first
        for (int i=0; i<diff; i++){
            if (first->cont[i]){
                if (first->sign){
                    return 0;
                } else {
                    return 1;
                }
            }
        }
        bigger = 0;
        smallLen = second->length;
    } else {
        for (int i=0; i<ndiff; i++){
            if (second->cont[i]){
                if (second->sign){
                    return 1;
                } else {
                    return 0;
                }
            }
        }
        bigger = 1;
        smallLen = first->length;
    }
    // now we are even. Check with the MSB of each
    if (bigger){
        for (int i=0; i<smallLen; i++){
            unsigned int fir = first->cont[i];
            unsigned int sec = second->cont[i+ndiff];
            if (fir == sec){
                continue;
            }
            int result = (fir > sec);
            if (first->sign){
                return !result;
            } else {
                return result;
            }
        }
    } else {
        for (int i=0; i<smallLen; i++){
            unsigned int fir = first->cont[i+diff];
            unsigned int sec = second->cont[i];
            if (fir == sec){
                continue;
            }
            int result = (fir > sec);
            if (first->sign){
                return !result;
            } else {
                return result;
            }
        }

    }

    return 0;
}


/////////////////////////////////////////////////////////////////
/*
ge
*/
int sint_n_ge(sint* first, sint* second){
    return !(sint_n_lt(first, second));
}

/////////////////////////////////////////////////////////////////
/*
le
*/
int sint_n_le(sint* first, sint* second){
    return !(sint_n_gt(first, second));
}

/////////////////////////////////////////////////////////////////
/*
eq
*/
int sint_n_eq(sint* first, sint* second){
    if (first->sign != second->sign){
        return 0;
    }
    
    // start comparing
    int diff = first->length - second->length;
    int ndiff = -diff;
    if (diff){
        int start;
        if (diff > 0){
            start = memcmp(first->cont+diff, second->cont, second->length * sizeof(unsigned int));
        } else {
            start = memcmp(first->cont, second->cont+ndiff, first->length * sizeof(unsigned int));
        }
        if (start){
            return 0;
        }
        if (diff > 0){
            for (int i=0; i<diff; i++){
                if (first->cont[i]){
                    return 0;
                }
            }
            return 1;
        } else {
            for (int i=0; i<ndiff; i++){
                if (second->cont[i]){
                    return 0;
                }
            }
            return 1;

        }

    } else {
        return !(memcmp(first->cont, second->cont, first->length * sizeof(unsigned int)));
    }

}


/////////////////////////////////////////////////////////////////
/*
and - bitwise and (returns the minimum size integer allowed)
*/
sint* sint_c_and(sint* first, sint* second){
    int diff = first->length - second->length;
    int ndiff = -diff;

    sint* result;
    if (diff > 0){
        result = sint_c_becomes(second);
        for (int i=0; i<second->length; i++){
            result->cont[i] = first->cont[i+diff] & second->cont[i];
        }
    } else {
        result = sint_c_becomes(first);
        for (int i=0; i<first->length; i++){
            result->cont[i] = first->cont[i] & second->cont[i+ndiff];
        }
    }

    result->sign = first->sign && second->sign;

    return result;
}

sint* sint_r_and(sint* first, sint* second, void* ref){
    int diff = first->length - second->length;
    int ndiff = -diff;

    sint* result;
    if (diff > 0){
        result = sint_r_becomes(second, ref);
        for (int i=0; i<second->length; i++){
            result->cont[i] = first->cont[i+diff] & second->cont[i];
        }
    } else {
        result = sint_r_becomes(first, ref);
        for (int i=0; i<first->length; i++){
            result->cont[i] = first->cont[i] & second->cont[i+ndiff];
        }
    }

    result->sign = first->sign && second->sign;

    return result;
}


/////////////////////////////////////////////////////////////////
/*
or
not
xor
test (evaluates to either 0 or 1 for if statements and logical comparisons)
lshift
rshift
add
sub
mul
div
mod
truediv
power

functions:
as_integer_ratio - Return a pair of integers, whose ratio is exactly equal to the original int and with a positive denominator.
bit_count - Number of ones in the binary representation of the absolute value of self.
bit_length - Number of bits necessary to represent self in binary.
conjugate - Returns self, the complex conjugate of any int.
from_bytes - Return the integer represented by the given array of bytes.
to_bytes - Return an array of bytes representing an integer.
denominator - returns the denominator of a rational number in lowest terms
numerator - the numerator of a rational number in lowest terms
imag - returns the imaginary part of a complex number
real - returns the real part of a complex number
*/

/////////////////////////////////////////////////////////////////

#include "str.h"

int main(){
    void* memspace = malloc(1000);
    sint* test = sint_r_init(memspace, 7);
    sint* test2 = sint_r_init_2(memspace+100, 7);
    test2->cont[6] = 7;

    printf("%d\n", test->cont[0]);

    sint* test3 = sint_r_and(test, test2, memspace+200);

    free(memspace);
    return 0;
}




