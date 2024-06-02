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

#include "sint.h"
#include "str.h"

#define True 1
#define False 0


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
    result->cont = ((char*) ref) + sizeof(str);
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
    result->cont = ((char*) ref) + sizeof(str);
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
    int before = 0;
    int after = instance->length;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[after];
    while (str_n_in(curr, chars) && after > 0){
        after--;
        curr->cont[0] = instance->cont[after];
    }
    curr->cont[0] = instance->cont[before];
    while (str_n_in(curr, chars) && before < after){
        before++;
        curr->cont[0] = instance->cont[before];
    }
    str_n_uninit(curr);

    str* result = str_c_init_2(after-before+1);
    
    memcpy(result->cont, instance->cont+before, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
}

str* str_r_strip(str* instance, void* ref, str* chars){
    int before = 0;
    int after = instance->length;
    str* curr = str_c_init_2(1);
    curr->cont[0] = instance->cont[after];
    while (str_n_in(curr, chars) && after > 0){
        after--;
        curr->cont[0] = instance->cont[after];
    }
    curr->cont[0] = instance->cont[before];
    while (str_n_in(curr, chars) && before < after){
        before++;
        curr->cont[0] = instance->cont[before];
    }
    str_n_uninit(curr);

    str* result = str_r_init_2(ref, after-before+1);
    
    memcpy(result->cont, instance->cont+before, sizeof(char) * (result->length+1));
    result->cont[result->length] = '\0';

    return result;
}


/////////////////////////////////////////////////////////////////
/* 
index()	Searches the string for a specified value and returns the position of where it was found
*/
int str_n_index(str* instance, str* search){
    if (search->length > instance->length){
        return -1;
    }
    // use strstr for searching (because I am too lazy to write my own implementation)
    char* result = strstr(instance->cont, search->cont);
    if (result == NULL){
        return -1;
    }
    return result - instance->cont;
}

/////////////////////////////////////////////////////////////////
/*
center(width, fillChar)	Returns a centered string
*/
str* str_c_center(str* instance, int width, char fillChar){
    str* result;
    int diff = instance->length - width;
    if (diff >= 0){
        result = str_c_becomes(instance);
        return result;
    }
    result = str_c_init_2(width);
    int halfed = -diff/2;

    memcpy(result->cont+halfed, instance->cont, instance->length);
    for (int i=0; i<halfed; i++){
        result->cont[i] = fillChar;
    }
    for (int i=halfed+instance->length; i<width; i++){
        result->cont[i] = fillChar;
    }
    result->cont[width] = '\0';
    return result;
}

str* str_r_center(str* instance, void* ref, int width, char fillChar){
    str* result;
    int len = instance->length;
    int diff = instance->length - width;
    if (diff >= 0){
        result = str_r_becomes(instance, ref);
        return result;
    }
    result = str_r_init_2(ref, width);
    int halfed = -diff/2;

    memmove(result->cont+halfed, instance->cont, len);
    for (int i=0; i<halfed; i++){
        result->cont[i] = fillChar;
    }
    for (int i=halfed+len; i<result->length; i++){
        result->cont[i] = fillChar;
    }
    result->cont[width] = '\0';
    return result;
}

/////////////////////////////////////////////////////////////////
/*
find()	Searches the string for a specified value and returns the position of where it was found
*/
int str_n_find(str* instance, str* search){
    return str_n_index(instance, search);
}


/////////////////////////////////////////////////////////////////
/*
endswith()	Returns true if the string ends with the specified value
*/
int str_n_endswith(str* instance, str* search){
    int diff = instance->length - search->length;
    if (diff < 0){
        return 0;
    }
    int k = 0;
    for (int i=diff; i<instance->length; i++){
        if (instance->cont[i] != search->cont[k]){
            return 0;
        }
        k++;
    }
    return 1;
}


/////////////////////////////////////////////////////////////////
/*
startswith()	Returns true if the string starts with the specified value
*/
int str_n_startswith(str* instance, str* search){
    int diff = instance->length - search->length;
    if (diff < 0){
        return 0;
    }
    int k = 0;
    for (int i=0; i<search->length; i++){
        if (instance->cont[i] != search->cont[k]){
            return 0;
        }
        k++;
    }
    return 1;
}


/////////////////////////////////////////////////////////////////
/*
count()	Returns the number of times a specified value occurs in a string
*/
int str_n_count(str* instance, str* search){
    int result = 0;
    int diff = instance->length - search->length;
    if (diff < 0){
        return result;
    }
    int k = 0;
    str* temp = str_c_becomes(instance);
    char* org = temp->cont;
    while (k  < instance->length){
        int curr = str_n_index(temp, search);
        if (curr == -1){
            temp->cont = org;
            str_n_uninit(temp);
            return result;
        }
        temp->cont += curr + search->length;
        result++;
    }
    temp->cont = org;
    str_n_uninit(temp);
    return result;
}


/////////////////////////////////////////////////////////////////
/*
isdigit()	Returns True if all characters in the string are digits
*/
int str_n_isdigit(str* instance){
    for (int i=0; i<instance->length; i++){
        int val = (int) instance->cont[i];
        if (val < 48 || val > 57){
            return 0;
        }
    }
    return 1;
}


/////////////////////////////////////////////////////////////////
/*
isalpha()	Returns True if all characters in the string are in the alphabet
*/
int str_n_isalpha(str* instance){
    for (int i=0; i<instance->length; i++){
        int val = (int) instance->cont[i];

        if ((val < 97 && val > 90) || val < 65 || val > 122){
            return 0;
        }
    }
    return 1;
}

/////////////////////////////////////////////////////////////////
/*
islower()	Returns True if all characters in the string are lower case
*/
int str_n_islower(str* instance){
    for (int i=0; i<instance->length; i++){
        int val = (int) instance->cont[i];

        if (val < 97 || val > 122){
            return 0;
        }
    }
    return 1;
}


/////////////////////////////////////////////////////////////////
/*
isupper()	Returns True if all characters in the string are upper case
*/
int str_n_isupper(str* instance){
    for (int i=0; i<instance->length; i++){
        int val = (int) instance->cont[i];

        if (val < 65 || val > 90){
            return 0;
        }
    }
    return 1;
}

/////////////////////////////////////////////////////////////////
/*
isalnum()	Returns True if all characters in the string are alphanumeric
*/
int str_n_isalnum(str* instance){
    for (int i=0; i<instance->length; i++){
        int val = (int) instance->cont[i];

        if (val < 48 || (val > 57 && val < 65) || (val > 90 && val < 97) || val > 122){
            return 0;
        }
    }
    return 1;
}


/////////////////////////////////////////////////////////////////
/* TODO
replace()	Returns a string where a specified value is replaced with a specified value
*/
str* str_c_replace(str* instance, str* old, str* new){
    

}

/////////////////////////////////////////////////////////////////
/*
encode()	Returns an encoded version of the string
expandtabs()	Sets the tab size of the string
format()	Formats specified values in a string
format_map()	Formats specified values in a string
isascii()	Returns True if all characters in the string are ascii characters
isdecimal()	Returns True if all characters in the string are decimals
isidentifier()	Returns True if the string is an identifier
isnumeric()	Returns True if all characters in the string are numeric
isprintable()	Returns True if all characters in the string are printable
isspace()	Returns True if all characters in the string are whitespaces
istitle() 	Returns True if the string follows the rules of a title
join()	Converts the elements of an iterable into a string
ljust()	Returns a left justified version of the string
maketrans()	Returns a translation table to be used in translations
partition()	Returns a tuple where the string is parted into three parts
rfind()	Searches the string for a specified value and returns the last position of where it was found
rindex()	Searches the string for a specified value and returns the last position of where it was found
rjust()	Returns a right justified version of the string
rpartition()	Returns a tuple where the string is parted into three parts
rsplit()	Splits the string at the specified separator, and returns a list
split()	Splits the string at the specified separator, and returns a list
splitlines()	Splits the string at line breaks and returns a list
translate()	Returns a translated string
*/

/////////////////////////////////////////////////////////////////
/*
sint.toString - returns the string representation of the integer
*/
str* sint_c_toString(sint* instance){
    // ceiling(instance->length/4) + 1 should be the perfect number of chars to represent the number
    int chars = instance->length * (sizeof(unsigned int) >> 2) + 3; // plus one for null char and for extra space after ceiling

    char buffer[chars];

    buffer[0] = '\0';

    
    



    buffer[chars-1] = '\0';

}

/////////////////////////////////////////////////////////////////

