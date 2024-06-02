#ifndef DYNAMIC_TYPE
#define DYNAMIC_TYPE
typedef enum{
   STR,
   INT,
   DARR,
} DynamicType;
#endif

// return the string representation of a DynamicNode
char* DynamicNode_n_toString(DynamicNode* instance);



