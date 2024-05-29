// This file is for static integers
// In some cases, normal integers in C work fine, // but integers in python are not limited by 32 or 64 bits // This file is for large integers who cannot request more memory after being created

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

    result->cont = (unsigned int*) malloc(sizeof(unsigned int) * result->length);
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

    result->cont = (unsigned int*) (((char*) ref) + sizeof(sint));
    result->cont[0] = val;
    
    return result;
}

sint* sint_c_init_2(int len){
    sint* result = malloc(sizeof(sint));
    result->length = len;
    result->sign = 0;

    result->cont = (unsigned int*) malloc(sizeof(unsigned int) * result->length);
    for (int i=0; i<result->length; i++){
        result->cont[i] = 0;
    }
    
    return result;
}

sint* sint_r_init_2(void* ref, int len){
    sint* result = (sint*) ref;
    result->length = len;
    result->sign = 0;

    result->cont = (unsigned int*) (((char*) ref) + sizeof(sint));
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
*/
sint* sint_c_or(sint* first, sint* second){
    int diff = first->length - second->length;
    int ndiff = -diff;

    sint* result;
    if (diff > 0){
        result = sint_c_becomes(first);
        for (int i=0; i<second->length; i++){
            int off = i + diff;
            result->cont[off] = first->cont[off] | second->cont[i];
        }
        for (int i=0; i<diff; i++){
            result->cont[i] = first->cont[i];
        }
    } else {
        result = sint_c_becomes(second);
        for (int i=0; i<first->length; i++){
            int off = i + ndiff;
            result->cont[off] = first->cont[i] | second->cont[off];
        }
        for (int i=0; i<diff; i++){
            result->cont[i] = second->cont[i];
        }
    }

    result->sign = first->sign || second->sign;

    return result;
}

sint* sint_r_or(sint* first, sint* second, void* ref){
    int diff = first->length - second->length;
    int ndiff = -diff;

    sint* result;
    if (diff > 0){
        result = sint_r_becomes(first, ref);
        for (int i=0; i<second->length; i++){
            int off = i + diff;
            result->cont[off] = first->cont[off] | second->cont[i];
        }
        for (int i=0; i<diff; i++){
            result->cont[i] = first->cont[i];
        }
    } else {
        result = sint_r_becomes(second, ref);
        for (int i=0; i<first->length; i++){
            int off = i + ndiff;
            result->cont[off] = first->cont[i] | second->cont[off];
        }
        for (int i=0; i<diff; i++){
            result->cont[i] = second->cont[i];
        }
    }

    result->sign = first->sign || second->sign;

    return result;
}

/////////////////////////////////////////////////////////////////
/*
not
*/
sint* sint_c_not(sint* instance){
    sint* result = sint_c_becomes(instance);

    result->sign = !(result->sign);

    for (int i=0; i<result->length; i++){
        result->cont[i] = ~(result->cont[i]);
    }
    return result;
}

sint* sint_r_not(sint* instance, void* ref){
    sint* result = sint_r_becomes(instance, ref);

    result->sign = !(result->sign);

    for (int i=0; i<result->length; i++){
        result->cont[i] = ~(result->cont[i]);
    }
    return result;
}


/////////////////////////////////////////////////////////////////
/*
xor
*/
sint* sint_c_xor(sint* first, sint* second){
    int len = 0;
    sint* result;
    int diff = first->length - second->length;
    int ndiff = -diff;
    if (diff > 0){
        result = sint_c_becomes(first);

        for (int i=0; i<diff; i++){
            int curr = i+diff;
            result->cont[curr] = first->cont[curr] ^ second->cont[i];
        }

        for (int i=0; i<diff; i++){
            result->cont[i] = first->cont[i];
        }

    } else {
        result = sint_c_becomes(second);

        for (int i=0; i<ndiff; i++){
            int curr = i+ndiff;
            result->cont[curr] = second->cont[curr] ^ first->cont[i];
        }

        for (int i=0; i<ndiff; i++){
            result->cont[i] = second->cont[i];
        }

    }

    result->sign = first->sign ^ second->sign;

    return result;
}

sint* sint_r_xor(sint* first, sint* second, void* ref){
    int len = 0;
    sint* result;
    int diff = first->length - second->length;
    int ndiff = -diff;
    if (diff > 0){
        result = sint_r_becomes(first, ref);

        for (int i=0; i<diff; i++){
            int curr = i+diff;
            result->cont[curr] = first->cont[curr] ^ second->cont[i];
        }

        for (int i=0; i<diff; i++){
            result->cont[i] = first->cont[i];
        }

    } else {
        result = sint_r_becomes(second, ref);

        for (int i=0; i<ndiff; i++){
            int curr = i+ndiff;
            result->cont[curr] = second->cont[curr] ^ first->cont[i];
        }

        for (int i=0; i<ndiff; i++){
            result->cont[i] = second->cont[i];
        }

    }

    result->sign = first->sign ^ second->sign;

    return result;
}

/////////////////////////////////////////////////////////////////
/*
test (evaluates to either 0 or 1 for if statements and logical comparisons)
*/
int sint_n_test(sint* instance){
    if (instance->sign){
        for (int i=0; i<instance->length; i++){
            if (~(instance->cont[i])){
                return 1;
            }
        }
        return 0;
    } else {
        for (int i=0; i<instance->length; i++){
            if (instance->cont[i]){
                return 1;
            }
        }
        return 0;
    }
}


/////////////////////////////////////////////////////////////////
/*
lshift
*/
sint* sint_c_lshift(sint* instance, int shifts){
    int intBits = sizeof(unsigned int) * 8;

    int extra = shifts / intBits;
    int smallShifts = shifts % intBits;
    int remaining = intBits - smallShifts;

    int total = instance->length + extra;
    if (smallShifts){
        total++;
    }

    sint* result = sint_c_init_2(total);
    result->sign = instance->sign;

    memcpy(result->cont, instance->cont, sizeof(unsigned int) * instance->length);
    for (int i=instance->length; i<result->length; i++){
        result->cont[i] = 0;
    }

    // now entire array needs to be shifted to the right by remaining (the variable) bits
    unsigned int previous = 0;
    unsigned int next = 0;
    unsigned int mask = (1 << remaining) - 1;
    for (int i=0; i<result->length; i++){
        // save end of current integer for the next one
        next = (result->cont[i] & mask) << smallShifts;
        // shift to the right enough times
        result->cont[i] >>= remaining;
        // replace the beginning of the current with the end of the previous
        result->cont[i] |= previous;
        previous = next;
    }

    return result;
}

sint* sint_r_lshift(sint* instance, void* ref, int shifts){
    int intBits = sizeof(unsigned int) * 8;

    int extra = shifts / intBits;
    int smallShifts = shifts % intBits;
    int remaining = intBits - smallShifts;

    int total = instance->length + extra;
    if (smallShifts){
        total++;
    }

    sint* result = sint_r_init_2(ref, total);
    result->sign = instance->sign;

    memmove(result->cont, instance->cont, sizeof(unsigned int) * instance->length);
    for (int i=instance->length; i<result->length; i++){
        result->cont[i] = 0;
    }

    // now entire array needs to be shifted to the right by remaining (the variable) bits
    unsigned int previous = 0;
    unsigned int next = 0;
    unsigned int mask = (1 << remaining) - 1;
    for (int i=0; i<result->length; i++){
        // save end of current integer for the next one
        next = (result->cont[i] & mask) << smallShifts;
        // shift to the right enough times
        result->cont[i] >>= remaining;
        // replace the beginning of the current with the end of the previous
        result->cont[i] |= previous;
        previous = next;
    }

    return result;
}

/////////////////////////////////////////////////////////////////
/*
rshift
*/
sint* sint_c_rshift(sint* instance, int shifts){
    int intBits = sizeof(unsigned int) * 8;

    int extra = shifts / intBits;
    int smallShifts = shifts % intBits;
    int remaining = intBits - smallShifts;

    int total = instance->length - extra;

    sint* result = sint_c_init_2(total);
    result->sign = instance->sign;

    memcpy(result->cont, instance->cont, sizeof(unsigned int) * result->length);

    // now entire array needs to be shifted to the right by smallShifts (the variable) bits
    unsigned int previous = 0;
    if (instance->sign){
        previous = ~(previous) << remaining;
    }
    unsigned int next = 0;
    unsigned int mask = (1 << smallShifts) - 1;
    for (int i=0; i<result->length; i++){
        // save end of current integer for the next one
        next = (result->cont[i] & mask) << remaining;
        // shift to the right enough times
        result->cont[i] >>= smallShifts;
        // replace the beginning of the current with the end of the previous
        result->cont[i] |= previous;
        previous = next;
    }

    return result;
}

sint* sint_r_rshift(sint* instance, void* ref, int shifts){
    int intBits = sizeof(unsigned int) * 8;

    int extra = shifts / intBits;
    int smallShifts = shifts % intBits;
    int remaining = intBits - smallShifts;

    int total = instance->length - extra;

    sint* result = sint_r_init_2(ref, total);
    result->sign = instance->sign;

    memmove(result->cont, instance->cont, sizeof(unsigned int) * result->length);

    // now entire array needs to be shifted to the right by smallShifts (the variable) bits
    unsigned int previous = 0;
    if (instance->sign){
        previous = ~(previous) << remaining;
    }
    unsigned int next = 0;
    unsigned int mask = (1 << smallShifts) - 1;
    for (int i=0; i<result->length; i++){
        // save end of current integer for the next one
        next = (result->cont[i] & mask) << remaining;
        // shift to the right enough times
        result->cont[i] >>= smallShifts;
        // replace the beginning of the current with the end of the previous
        result->cont[i] |= previous;
        previous = next;
    }

    return result;
}


/////////////////////////////////////////////////////////////////
/*
negate - not and add 1
*/
sint* sint_c_negate(sint* instance){
    sint* result = sint_c_not(instance);
    unsigned int max = ~0;

    for (int i=result->length-1; i>=0; i--){
        if (result->cont[i] == max){
            result->cont[i] = 0;
            if (!i){
                if (result->sign){
                    result->sign = 0;
                } else {
                    result->sign = 1;
                }
            }
        } else {
            result->cont[i] += 1;
            break;
        }
    }

    return result;
}

sint* sint_r_negate(sint* instance, void* ref){
    sint* result = sint_r_not(instance, ref);
    unsigned int max = ~0;

    for (int i=result->length-1; i>=0; i--){
        if (result->cont[i] == max){
            result->cont[i] = 0;
            if (!i){
                if (result->sign){
                    result->sign = 0;
                } else {
                    result->sign = 1;
                }
            }
        } else {
            result->cont[i] += 1;
            break;
        }
    }

    return result;
}


/////////////////////////////////////////////////////////////////
/*
add
*/
sint* sint_c_add(sint* first, sint* second){
    // figure out which one is bigger
    int diff = first->length - second->length;

    sint* result;
    if (diff < 0){
        result = sint_c_becomes(second);

        int j = second->length-1;
        unsigned int max = ~0;
        unsigned int carry = 0;
        for (int i=first->length-1; i>=0; i--){
            // check for overflow possibility
            unsigned int overflow = max - first->cont[i] - carry;
            // overflow is now the max allowed value for second->cont[j]
            if (second->cont[j] > overflow){
                carry = 1; // we need to carry a 1 to the next value
                result->cont[j] = second->cont[j] - overflow - 1;
            } else {
                carry = 0;
                result->cont[j] = second->cont[j] + first->cont[i] + carry;
            }
            j--;
        }

        if (first->sign){
            for (int i=-diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = -carry;
                // overflow is now the max allowed value for second->cont[j]
                if (second->cont[i] > -carry){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[i] = second->cont[i] + carry;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[i] = second->cont[i] + max + carry;
                }
            }
        } else { // if first was positive
            for (int i=-diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = max - carry;
                // overflow is now the max allowed value for second->cont[j]
                if (second->cont[j] > overflow){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[j] = second->cont[j] - overflow;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[j] = second->cont[j] + carry;
                }
            }
        }
    } else {
        result = sint_c_becomes(first);

        int j = first->length-1;
        unsigned int max = ~0;
        unsigned int carry = 0;
        for (int i=second->length-1; i>=0; i--){
            // check for overflow possibility
            unsigned int overflow = max - second->cont[i] - carry;
            // overflow is now the max allowed value for first->cont[j]
            if (first->cont[j] > overflow){
                carry = 1; // we need to carry a 1 to the next value
                result->cont[j] = first->cont[j] - overflow - 1;
            } else {
                carry = 0;
                result->cont[j] = first->cont[j] + second->cont[i] + carry;
            }
            j--;
        }

        if (second->sign){
            for (int i=diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = -carry;
                // overflow is now the max allowed value for first->cont[j]
                if (first->cont[j] > -carry){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[j] = first->cont[j] + carry;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[j] = first->cont[j] + max + carry;
                }
            }
        } else { // if first was positive
            for (int i=diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = max - carry;
                // overflow is now the max allowed value for first->cont[j]
                if (first->cont[i] > overflow){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[i] = first->cont[i] - overflow;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[i] = first->cont[i] + carry;
                }
            }
        }


    }

    return result;
}

sint* sint_r_add(sint* first, sint* second, void* ref){
    // figure out which one is bigger
    int diff = first->length - second->length;

    sint* result;
    if (diff < 0){
        result = sint_r_becomes(second, ref);

        int j = second->length-1;
        unsigned int max = ~0;
        unsigned int carry = 0;
        for (int i=first->length-1; i>=0; i--){
            // check for overflow possibility
            unsigned int overflow = max - first->cont[i] - carry;
            // overflow is now the max allowed value for second->cont[j]
            if (second->cont[j] > overflow){
                carry = 1; // we need to carry a 1 to the next value
                result->cont[j] = second->cont[j] - overflow - 1;
            } else {
                carry = 0;
                result->cont[j] = second->cont[j] + first->cont[i] + carry;
            }
            j--;
        }

        if (first->sign){
            for (int i=-diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = -carry;
                // overflow is now the max allowed value for second->cont[j]
                if (second->cont[i] > -carry){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[i] = second->cont[i] + carry;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[i] = second->cont[i] + max + carry;
                }
            }
        } else { // if first was positive
            for (int i=-diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = max - carry;
                // overflow is now the max allowed value for second->cont[j]
                if (second->cont[j] > overflow){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[j] = second->cont[j] - overflow;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[j] = second->cont[j] + carry;
                }
            }
        }
    } else {
        result = sint_r_becomes(first, ref);

        int j = first->length-1;
        unsigned int max = ~0;
        unsigned int carry = 0;
        for (int i=second->length-1; i>=0; i--){
            // check for overflow possibility
            unsigned int overflow = max - second->cont[i] - carry;
            // overflow is now the max allowed value for first->cont[j]
            if (first->cont[j] > overflow){
                carry = 1; // we need to carry a 1 to the next value
                result->cont[j] = first->cont[j] - overflow - 1;
            } else {
                carry = 0;
                result->cont[j] = first->cont[j] + second->cont[i] + carry;
            }
            j--;
        }

        if (second->sign){
            for (int i=diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = -carry;
                // overflow is now the max allowed value for first->cont[j]
                if (first->cont[j] > -carry){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[j] = first->cont[j] + carry;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[j] = first->cont[j] + max + carry;
                }
            }
        } else { // if first was positive
            for (int i=diff; i>=0; i--){
                // check for overflow possibility
                unsigned int overflow = max - carry;
                // overflow is now the max allowed value for first->cont[j]
                if (first->cont[i] > overflow){
                    carry = 1; // we need to carry a 1 to the next value
                    result->cont[i] = first->cont[i] - overflow;
                    if (!i){
                        result->sign = (first->sign + second->sign) & 1;
                    }
                } else {
                    carry = 0;
                    result->cont[i] = first->cont[i] + carry;
                }
            }
        }


    }

    return result;
}


/////////////////////////////////////////////////////////////////
/*
sub - for now, just negate the second then add them together (this can be optimized later to remove the negation)
*/
sint* sint_c_sub(sint* first, sint* second){
    sint* temp = sint_c_negate(second);
    sint* result = sint_c_add(first, temp);
    sint_n_uninit(temp);
    return result;
}

sint* sint_r_sub(sint* first, sint* second, void* ref){
    sint* temp = sint_r_negate(second, ref);
    return sint_r_add(first, temp, ref);
}

/////////////////////////////////////////////////////////////////
/*
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
    void* memspace = malloc(65536);

    sint* test = sint_r_init(memspace, 11);
    sint* test2 = sint_r_init_2(((char*) memspace)+100, 2);
    test2->cont[1] = 7;

    printf("%d\n", test->cont[0]);

    sint* test3 = sint_r_sub(test, test2, test2);

    printf("%d\n", test3->cont[test3->length-1]);

    //sint_n_uninit(test3);
    free(memspace);
    return 0;
}




