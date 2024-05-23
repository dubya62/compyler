
#ifndef SINT
#define SINT
typedef struct {
    int length; // the number of elements in the array
    int sign; 
    unsigned int* cont;
} sint;
#endif

#ifndef STR
#define STR
// static str object
typedef struct{
    // length does not include the null terminator
    int length; // should probably change this to a dynamic int later
    // cont should be a buffer of size at least length+1
    char* cont; // contents of the string
} str;
#endif

str* sint_c_toString(sint* instance);
