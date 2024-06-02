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

// initialize a static str object
str* str_c_init(char* data);
// initalize a static str object (from already allocated memory)
str* str_r_init(void* ref, char* data);
// initialize a static str object using the length
str* str_c_init_2(int len);
// initalize a static str object (from already allocated memory) using the length
str* str_r_init_2(void* ref, int len);
// uninitialize a static str object and free the memory
int str_n_uninit(str* instance);
// make a copy of a str object by copy
str* str_c_becomes(str* instance);
// make a copy of a str object by reference (if memory is already allocated)
str* str_r_becomes(str* instance, void* ref);
// make a copy of a str object and return a dynamic string
str* str_d_becomes(str* instance); // TODO
/////////////////////////////////////////////////////////////////
/*
capitalize()	Converts the first character to upper case
*/
str* str_c_capitalize(str* instance);
str* str_r_capitalize(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
title()	Converts the first character of each word to upper case
*/
str* str_c_title(str* instance);
str* str_r_title(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
upper()	Converts a string into upper case
*/
str* str_c_upper(str* instance);
str* str_r_upper(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
swapcase()	Swaps cases, lower case becomes upper case and vice versa
*/
str* str_c_swapcase(str* instance);
str* str_r_swapcase(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
lower()	Converts a string into lower case
*/
str* str_c_lower(str* instance);
str* str_r_lower(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
zfill()	Fills the string with a specified number of 0 values at the beginning
*/
str* str_c_zfill(str* instance, int padding);
str* str_r_zfill(str* instance, void* ref, int padding);
/////////////////////////////////////////////////////////////////
/*
casefold()	Converts string into lower case
*/
str* str_c_casefold(str* instance);
str* str_r_casefold(str* instance, void* ref);
/////////////////////////////////////////////////////////////////
/*
in  Returns True if the first string is in the second, False otherwise
*/
int str_n_in(str* first, str* second);
/////////////////////////////////////////////////////////////////
/*
rstrip()	Returns a right trim version of the string
*/
str* str_c_rstrip(str* instance, str* chars);
str* str_r_rstrip(str* instance, void* ref, str* chars);
/////////////////////////////////////////////////////////////////
/*
lstrip()	Returns a left trim version of the string
*/
str* str_c_lstrip(str* instance, str* chars);
str* str_r_lstrip(str* instance, void* ref, str* chars);
/////////////////////////////////////////////////////////////////
/*
strip()	Returns a trimmed version of the string
*/
str* str_c_strip(str* instance, str* chars);
str* str_r_strip(str* instance, void* ref, str* chars);
/////////////////////////////////////////////////////////////////
/* 
index()	Searches the string for a specified value and returns the position of where it was found
*/
int str_n_index(str* instance, str* search);
/////////////////////////////////////////////////////////////////
/*
center(width, fillChar)	Returns a centered string
*/
str* str_c_center(str* instance, int width, char fillChar);
str* str_r_center(str* instance, void* ref, int width, char fillChar);
/////////////////////////////////////////////////////////////////
/*
find()	Searches the string for a specified value and returns the position of where it was found
*/
int str_n_find(str* instance, str* search);
/////////////////////////////////////////////////////////////////
/*
endswith()	Returns true if the string ends with the specified value
*/
int str_n_endswith(str* instance, str* search);
/////////////////////////////////////////////////////////////////
/*
startswith()	Returns true if the string starts with the specified value
*/
int str_n_startswith(str* instance, str* search);
/////////////////////////////////////////////////////////////////
/*
count()	Returns the number of times a specified value occurs in a string
*/
int str_n_count(str* instance, str* search);
/////////////////////////////////////////////////////////////////
/*
isdigit()	Returns True if all characters in the string are digits
*/
int str_n_isdigit(str* instance);
/////////////////////////////////////////////////////////////////
/*
isalpha()	Returns True if all characters in the string are in the alphabet
*/
int str_n_isalpha(str* instance);
/////////////////////////////////////////////////////////////////
/*
islower()	Returns True if all characters in the string are lower case
*/
int str_n_islower(str* instance);
/////////////////////////////////////////////////////////////////
/*
isupper()	Returns True if all characters in the string are upper case
*/
int str_n_isupper(str* instance);
/////////////////////////////////////////////////////////////////
/*
isalnum()	Returns True if all characters in the string are alphanumeric
*/
int str_n_isalnum(str* instance);

/////////////////////////////////////////////////////////////////
/* TODO
replace()	Returns a string where a specified value is replaced with a specified value
*/
str* str_c_replace(str* instance, str* old, str* new);
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
str* sint_c_toString(sint* instance);
/////////////////////////////////////////////////////////////////

