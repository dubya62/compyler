
#ifndef DYNAMIC_TYPE
#define DYNAMIC_TYPE
typedef enum{ // helps with the typing of DynamicNode
    CSTR, // a char array (C's implementation)
    CINT, // an integer (C's implementation)
    SSTR, // a str object (str.c implementation)
    SINT, // an integer (sint.c implementation
    DARR, // a dynamic array (dynamic_array.c implementation)
    DNODE, // a dynamic node (dynamic_type.c implementation)
} DynamicType;
#endif

#ifndef DYNAMIC_NODE
#define DYNAMIC_NODE
typedef struct{
    DynamicType type;
    void* data;
} DynamicNode;
#endif

/////////////////////////////////////////////////////////////////
/*
init
*/
DynamicNode* DynamicNode_c_init(int type, void* data);
DynamicNode* DynamicNode_r_init(void* ref, int type, void* data);
/////////////////////////////////////////////////////////////////
/*
uninit
*/
int DynamicNode_n_uninit(DynamicNode* instance);
/////////////////////////////////////////////////////////////////
/*
becomes
*/
DynamicNode* DynamicNode_c_becomes(DynamicNode* instance);
DynamicNode* DynamicNode_r_becomes(DynamicNode* instance, void* ref);
/////////////////////////////////////////////////////////////////
// return the string representation of a DynamicNode (uses the DynamicType definition)
char* DynamicNode_n_toString(DynamicNode* instance);



