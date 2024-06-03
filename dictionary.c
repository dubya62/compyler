
#include <stdlib.h>
#include <string.h>

#include "dynamic_type.h"
#include "dictionary.h"


int getNextBiggestPrime(int starting){
    int PRIMES[] = {11, 23, 47, 101, 211, 431, 673, 1409, 2851, 5711, 12007, 24103, 48311, 97001, 200003, 400009, 800029, 1600121, 3200311, 6500003};
    int NUM_PRIMES = 20;

    if (starting > PRIMES[NUM_PRIMES-1]){
        return starting;
    }
    int iterator = 0;
    int current = PRIMES[iterator];
    while (current < starting){
        iterator++;
        current = PRIMES[iterator];
    }

    return current;
}


/////////////////////////////////////////////////////////////////
/*
init - initializer
*/
Dictionary* Dictionary_c_init(int maxLength){
    Dictionary* result = (Dictionary*) malloc(sizeof(Dictionary));
    result->length = 0;
    
    result->maxLength = getNextBiggestPrime(maxLength);

    result->cont = (DictionaryNode*) malloc(sizeof(DictionaryNode) * result->maxLength);

    return result;
}

Dictionary* Dictionary_r_init(void* ref, int maxLength){
    Dictionary* result = (Dictionary*) ref;
    result->length = 0;

    result->maxLength = getNextBiggestPrime(maxLength);

    result->cont = (DictionaryNode*) (result+1);

    return result;
}


/////////////////////////////////////////////////////////////////
/*
uninit - uninitializer
*/
int Dictionary_n_uninit(Dictionary* instance){
    free(instance->cont);
    free(instance);
    return 0;
}


/////////////////////////////////////////////////////////////////
/*
becomes - 
*/
Dictionary* Dictionary_c_becomes(Dictionary* instance){
    Dictionary* result = Dictionary_c_init(instance->maxLength);
    // copy the content
    result->length = instance->length;
    memcpy(result->cont, instance->cont, instance->maxLength * sizeof(DictionaryNode));
    return result;
}

Dictionary* Dictionary_r_becomes(Dictionary* instance, void* ref){
    if (instance == ref){
        return instance;
    }
    Dictionary* result = Dictionary_r_init(ref, instance->maxLength);
    // copy the content
    result->length = instance->length;
    memmove(result->cont, instance->cont, instance->maxLength * sizeof(DictionaryNode));
    return result;
}


/////////////////////////////////////////////////////////////////
/*
add - adds an element to the dictionary
*/

/*
resize - resize the Dictionary to the next biggest prime (to make collisions less likely)
clear - Removes all the elements from the dictionary
copy - Returns a copy of the dictionary
fromkeys - Returns a dictionary with the specified keys and value
get	- Returns the value of the specified key
items - Returns a list containing a tuple for each key value pair
keys - Returns a list containing the dictionary's keys
pop	- Removes the element with the specified key
popitem	- Removes the last inserted key-value pair
setdefault - Returns the value of the specified key. If the key does not exist: insert the key, with the specified value
update - Updates the dictionary with the specified key-value pairs
values - Returns a list of all the values in the dictionary
*/
/////////////////////////////////////////////////////////////////




























