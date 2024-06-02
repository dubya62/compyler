#ifndef SINT_H
#define SINT_H

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
sint* sint_c_init(int val);
sint* sint_r_init(void* ref, int val);
sint* sint_c_init_2(int len);
sint* sint_r_init_2(void* ref, int len);
/////////////////////////////////////////////////////////////////
/*
uninit
*/
int sint_n_uninit(sint* instance);
/////////////////////////////////////////////////////////////////
/*
becomes
*/
sint* sint_c_becomes(sint* instance);
sint* sint_r_becomes(sint* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
operators:
*/
/////////////////////////////////////////////////////////////////
/*
lt
*/
int sint_n_lt(sint* first, sint* second);
/////////////////////////////////////////////////////////////////
/*
gt
*/
int sint_n_gt(sint* first, sint* second);
/////////////////////////////////////////////////////////////////
/*
ge
*/
int sint_n_ge(sint* first, sint* second);
/////////////////////////////////////////////////////////////////
/*
le
*/
int sint_n_le(sint* first, sint* second);
/////////////////////////////////////////////////////////////////
/*
eq
*/
int sint_n_eq(sint* first, sint* second);
/////////////////////////////////////////////////////////////////
/*
and - bitwise and (returns the minimum size integer allowed)
*/
sint* sint_c_and(sint* first, sint* second);
sint* sint_r_and(sint* first, sint* second, void* ref);
/////////////////////////////////////////////////////////////////
/*
or
*/
sint* sint_c_or(sint* first, sint* second);
sint* sint_r_or(sint* first, sint* second, void* ref);
/////////////////////////////////////////////////////////////////
/*
not
*/
sint* sint_c_not(sint* instance);
sint* sint_r_not(sint* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
xor
*/
sint* sint_c_xor(sint* first, sint* second);
sint* sint_r_xor(sint* first, sint* second, void* ref);
/////////////////////////////////////////////////////////////////
/*
test (evaluates to either 0 or 1 for if statements and logical comparisons)
*/
int sint_n_test(sint* instance);
/////////////////////////////////////////////////////////////////
/*
lshift
*/
sint* sint_c_lshift(sint* instance, int shifts);
sint* sint_r_lshift(sint* instance, void* ref, int shifts);
/////////////////////////////////////////////////////////////////
/*
rshift
*/
sint* sint_c_rshift(sint* instance, int shifts);
sint* sint_r_rshift(sint* instance, void* ref, int shifts);
/////////////////////////////////////////////////////////////////
/*
negate - not and add 1
*/
sint* sint_c_negate(sint* instance);
sint* sint_r_negate(sint* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
add
*/
sint* sint_c_add(sint* first, sint* second);
sint* sint_r_add(sint* first, sint* second, void* ref);
/////////////////////////////////////////////////////////////////
/*
sub - for now, just negate the second then add them together (this can be optimized later to remove the negation)
*/
sint* sint_c_sub(sint* first, sint* second);
sint* sint_r_sub(sint* first, sint* second, void* ref);
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







#endif
