
#ifndef DICTIONARY_H
#define DICTIONARY_H

#include "dynamic_type.h"

#ifndef DICTIONARY_NODE
#define DICTIONARY_NODE
typedef struct{
    DynamicNode key;
    DynamicNode value;
} DictionaryNode;
#endif

#ifndef DICTIONARY
#define DICTIONARY
typedef struct{
    int length; // number of elements
    int maxLength; // buffer size
    DictionaryNode* cont; // buffer for DictionaryNodes
} Dictionary;
#endif


/////////////////////////////////////////////////////////////////
/*
init - initializer
*/
Dictionary* Dictionary_c_init(int maxLength);
Dictionary* Dictionary_r_init(void* ref, int maxLength);
/////////////////////////////////////////////////////////////////
/*
uninit - uninitializer
*/
int Dictionary_n_uninit(Dictionary* instance);
/////////////////////////////////////////////////////////////////
/*
becomes - 
*/
Dictionary* Dictionary_c_becomes(Dictionary* instance);
Dictionary* Dictionary_r_becomes(Dictionary* instance, void* ref);
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
































#endif
