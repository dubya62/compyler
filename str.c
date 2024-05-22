// this file handles the static string object and its methods

// function naming convention
// className_modification_functionName
// valid modifications: 
//      c = pass by copy (has to request more memory)
//      r = pass by reference (parameters are modified, but is faster since memory is already allocated before call)
//      d = returns a dynamic string as a result (allows switching between static and dynamic)
//      n = none
//  if the modification is c or d, you must free the memory after you are done with the object
// each method requires passing the instance as the first argument

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define True 1
#define False 0

// static str object
typedef struct{
    // length does not include the null terminator
    int length; // should probably change this to a dynamic int later
    // cont should be a buffer of size at least length+1
    char* cont; // contents of the string
} str;

// initialize a static str object
str* str_c_init(char* data){
    int len = strlen(data);
    str* result = malloc(sizeof(str));
    result->length = len;
    int memsize = sizeof(char) * (len + 1); // bytes of memory allocated to buffer
    result->cont = malloc(memsize);
    memcpy(result->cont, data, memsize); // since we got the len from strlen, we know it will be null terminated
    return result;
}

// initalize a static str object (from already allocated memory)
str* str_r_init(void* ref, char* data){
    str* result = (str*) ref;
    int len = strlen(data);
    result->length = len;
    int memsize = sizeof(char) * (len + 1);
    // the character array is going to be allocated directly after the 
    // structure itself
    result->cont = ref + sizeof(str);
    memcpy(result->cont, data, memsize);
    return result;
}

// initialize a static str object using the length
str* str_c_init_2(int len){
    str* result = malloc(sizeof(str));
    result->length = len;
    result->cont = malloc(sizeof(char) * (len + 1));
    result->cont[len] = '\0';
    return result;
}

// initalize a static str object (from already allocated memory) using the length
str* str_r_init_2(void* ref, int len){
    str* result = (str*) ref;
    result->length = len;
    result->cont = ref + sizeof(str);
    result->cont[len] = '\0';
    return result;
}

// uninitialize a static str object and free the memory
int str_n_uninit(str* instance){
    free(instance->cont);
    free(instance);
    return 0;
}

// make a copy of a str object by copy
str* str_c_becomes(str* instance){
    // allocate result space
    str* result = str_c_init_2(instance->length);
    memcpy(result->cont, instance->cont, instance->length+1);
    return result;
}

// make a copy of a str object by reference (if memory is already allocated)
str* str_r_becomes(str* instance, void* ref){
    if (ref == instance){
        return instance;
    }
    str* result = str_r_init_2(ref, instance->length);
    memcpy(result->cont, instance->cont, instance->length+1);
    return result;
}

// make a copy of a str object and return a dynamic string
str* str_d_becomes(str* instance){
    // TODO
}

/////////////////////////////////////////////////////////////////
/*
capitalize()	Converts the first character to upper case
*/

str* str_c_capitalize(str* instance){
    // make a copy of the parameter
    str* result = str_c_becomes(instance);
    
    // check if the first character is able to be uppercased
    int val = (int) result->cont[0];
    if (96 < val < 123){
        // subtract 32 from the ascii value if needed
        result->cont[0] = (char) (val & 223);
    }

    return result;
}

str* str_r_capitalize(str* instance, void* ref){
    str* result = str_r_becomes(instance, ref);

    // check if the first character is able to be uppercased
    int val = (int) result->cont[0];
    if (96 < val < 123){
        // subtract 32 from the ascii value if needed
        result->cont[0] = (char) (val & 223);
    }

    return result;
}

/////////////////////////////////////////////////////////////////
/*
title()	Converts the first character of each word to upper case
*/
str* str_c_title(str* instance){
    str* result = str_c_becomes(instance);

    // after every non alphabetic character, uppercase
    // otherwise, lowercase
    int upper = 1;
    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        if (upper){
            // check if this is a lowercase character
            if (96 < val && val < 123){
                result->cont[i] = (char) (val & 223);
                upper = 0;
            }
        } else {
            // check if this is an uppercase letter
            if (64 < val && val < 91){
                result->cont[i] = (char) (val | 32);
            } else if (val < 96 || val > 123){ // check if this is a non alphabetic character
                upper = 1;
            }
        }
    }
    return result;
}

str* str_r_title(str* instance, void* ref){
    str* result = str_r_becomes(instance, ref);

    // after every non alphabetic character, uppercase
    // otherwise, lowercase
    int upper = 1;
    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        if (upper){
            // check if this is a lowercase character
            if (96 < val && val < 123){
                result->cont[i] = (char) (val & 223);
                upper = 0;
            }
        } else {
            // check if this is an uppercase letter
            if (64 < val && val < 91){
                result->cont[i] = (char) (val | 32);
            } else if (val < 96 || val > 123){ // check if this is a non alphabetic character
                upper = 1;
            }
        }
    }
    return result;
}

/////////////////////////////////////////////////////////////////
/*
upper()	Converts a string into upper case
*/
str* str_c_upper(str* instance){
    str* result = str_c_becomes(instance);

    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is a lowercase character
        if (96 < val && val < 123){
            result->cont[i] = (char) (val & 223);
        }
    }
    return result;
}

str* str_r_upper(str* instance, void* ref){
    str* result = str_r_becomes(instance, ref);
    
    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is a lowercase character
        if (96 < val && val < 123){
            result->cont[i] = (char) (val & 223);
        }
    }
    return result;
}

/////////////////////////////////////////////////////////////////
/*
swapcase()	Swaps cases, lower case becomes upper case and vice versa
*/
str* str_c_swapcase(str* instance){
    str* result = str_c_becomes(instance);

    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is a lowercase character
        if (96 < val && val < 123){
            result->cont[i] = (char) (val & 223);
        } else if (64 < val && val < 91){ // check if this is an uppercase letter
            result->cont[i] = (char) (val | 32);
        }
    }
    return result;
}

str* str_r_swapcase(str* instance, void* ref){
    str* result = str_r_becomes(instance, ref);

    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is a lowercase character
        if (96 < val && val < 123){
            result->cont[i] = (char) (val & 223);
        } else if (64 < val && val < 91){ // check if this is an uppercase letter
            result->cont[i] = (char) (val | 32);
        }
    }
    return result;
}

/////////////////////////////////////////////////////////////////
/*
lower()	Converts a string into lower case
*/
str* str_c_lower(str* instance){
    str* result = str_c_becomes(instance);

    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is an uppercase character
        if (64 < val && val < 91){ 
            result->cont[i] = (char) (val | 32);
        }
    }
    return result;
}

str* str_r_lower(str* instance, void* ref){
    str* result = str_r_becomes(instance, ref);

    for (int i=0; i<result->length; i++){
        int val = (int) (result->cont[i]);
        // check if this is an uppercase character
        if (64 < val && val < 91){ 
            result->cont[i] = (char) (val | 32);
        }
    }
    return result;
}

/////////////////////////////////////////////////////////////////
/*
zfill()	Fills the string with a specified number of 0 values at the beginning
*/
str* str_c_zfill(str* instance, int padding){
    str* result;
    int diff = instance->length - padding;
    if (diff >= 0){
        result = str_c_becomes(instance);
        return result;
    } else {
        result = str_c_init_2(padding+1);
        int ndiff = -diff;
        memcpy(result->cont + ndiff, instance->cont, sizeof(char) * (instance->length+1));
        for (int i=0; i<ndiff; i++){
            result->cont[i] = '0';
        }
        return result;
    }
}

str* str_r_zfill(str* instance, void* ref, int padding){
    str* result;
    int diff = instance->length - padding;
    if (diff >= 0){
        result = str_r_becomes(instance, ref);
        return result;
    } else {
        result = str_r_init_2(ref, padding+1);
        int ndiff = -diff;
        // if ref is the same as instance, we have to be carefull copying memory since overlapp will happen (use memmove instead)
        memmove(result->cont + ndiff, instance->cont, (instance->length+1) * sizeof(char));
        for (int i=0; i<ndiff; i++){
            result->cont[i] = '0';
        }
        return result;
    }
}

/////////////////////////////////////////////////////////////////
/*
casefold()	Converts string into lower case
*/
str* str_c_casefold(str* instance){
    return str_c_lower(instance);
}

str* str_r_casefold(str* instance, void* ref){
    return str_r_lower(instance, ref);
}

/////////////////////////////////////////////////////////////////
/*
in  Returns True if the first string is in the second, False otherwise
*/
int str_n_in(str* first, str* second){
    if (first->length > second->length){
        return 0;
    }
    // use strstr for searching (because I am too lazy to write my own implementation)
    char* result = strstr(second->cont, first->cont);
    if (result == NULL){
        return 0;
    }
    return 1;
}

/////////////////////////////////////////////////////////////////
/*
rstrip()	Returns a right trim version of the string
*/
str* str_c_rstrip(str* instance, str* chars){
    // find out how many chars need to be removed from the end
    int iterator = instance->length;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(instance+iterator, chars) && iterator){
        iterator--;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_c_init_2(iterator);
    
    memcpy(result->cont, instance->cont, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
}

str* str_r_rstrip(str* instance, void* ref, str* chars){
    // find out how many chars need to be removed from the end
    int iterator = instance->length;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(curr, chars) && iterator){
        iterator--;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_r_init_2(ref, iterator);
    
    // just in case they are overlapping areas
    memmove(result->cont, instance->cont, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
    
}


/////////////////////////////////////////////////////////////////
/*
lstrip()	Returns a left trim version of the string
*/
str* str_c_lstrip(str* instance, str* chars){
    // find out how many chars need to be removed from the beginning
    int iterator = 0;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(curr, chars) && iterator < instance->length){
        iterator++;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_c_init_2(instance->length-iterator);
    
    memcpy(result->cont, instance->cont+iterator, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
}

str* str_r_lstrip(str* instance, void* ref, str* chars){
    // find out how many chars need to be removed from the beginning
    int iterator = 0;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(curr, chars) && iterator < instance->length){
        iterator++;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_r_init_2(ref, instance->length-iterator);
    
    // just in case they are overlapping areas
    memmove(result->cont, instance->cont+iterator, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
    
}


/////////////////////////////////////////////////////////////////
/*
strip()	Returns a trimmed version of the string
*/
str* str_c_strip(str* instance, str* chars){
    // find out how many chars need to be removed from the end
    int iterator = 0;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(curr, chars) && iterator < instance->length){
        iterator++;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_c_init_2(instance->length-iterator);
    
    memcpy(result->cont, instance->cont+iterator, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
}

str* str_r_strip(str* instance, void* ref, str* chars){
    // find out how many chars need to be removed from the end
    int iterator = 0;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[iterator];
    while (str_n_in(curr, chars) && iterator < instance->length){
        iterator++;
        curr->cont[0] = instance->cont[iterator];
    }
    str_n_uninit(curr);

    str* result = str_r_init_2(ref, instance->length-iterator);
    
    // just in case they are overlapping areas
    memmove(result->cont, instance->cont+iterator, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
    
}


/////////////////////////////////////////////////////////////////
/*
center()	Returns a centered string
count()	Returns the number of times a specified value occurs in a string
encode()	Returns an encoded version of the string
endswith()	Returns true if the string ends with the specified value
expandtabs()	Sets the tab size of the string
find()	Searches the string for a specified value and returns the position of where it was found
format()	Formats specified values in a string
format_map()	Formats specified values in a string
index()	Searches the string for a specified value and returns the position of where it was found
isalnum()	Returns True if all characters in the string are alphanumeric
isalpha()	Returns True if all characters in the string are in the alphabet
isascii()	Returns True if all characters in the string are ascii characters
isdecimal()	Returns True if all characters in the string are decimals
isdigit()	Returns True if all characters in the string are digits
isidentifier()	Returns True if the string is an identifier
islower()	Returns True if all characters in the string are lower case
isnumeric()	Returns True if all characters in the string are numeric
isprintable()	Returns True if all characters in the string are printable
isspace()	Returns True if all characters in the string are whitespaces
istitle() 	Returns True if the string follows the rules of a title
isupper()	Returns True if all characters in the string are upper case
join()	Converts the elements of an iterable into a string
ljust()	Returns a left justified version of the string
maketrans()	Returns a translation table to be used in translations
partition()	Returns a tuple where the string is parted into three parts
replace()	Returns a string where a specified value is replaced with a specified value
rfind()	Searches the string for a specified value and returns the last position of where it was found
rindex()	Searches the string for a specified value and returns the last position of where it was found
rjust()	Returns a right justified version of the string
rpartition()	Returns a tuple where the string is parted into three parts
rsplit()	Splits the string at the specified separator, and returns a list
split()	Splits the string at the specified separator, and returns a list
splitlines()	Splits the string at line breaks and returns a list
startswith()	Returns true if the string starts with the specified value
translate()	Returns a translated string
*/


int main(){
    void* memspace = malloc(1000);
    char* chars = "\n\n\n\t   helloWorl?A!d wo2rld!";
    char* chars2 = " \n\t";

    str* test = str_r_init(memspace, chars);
    str* breakChars = str_c_init(chars2);

    printf("Length: %d\n", test->length);

    printf("Test1: %s", test->cont);

    str* test2 = str_r_lstrip(test, memspace+100, breakChars);

    printf("Length2: %d\n", test2->length);
    printf("Test2: %s", test2->cont);

    // free the memory
    str_n_uninit(breakChars);
    free(memspace);
    return 0;
}


