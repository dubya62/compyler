
#include <stdlib.h>

#include "dynamic_type.h"

/////////////////////////////////////////////////////////////////
/*
init
*/
DynamicNode* DynamicNode_c_init(int type, void* data){
    DynamicNode* result = (DynamicNode*) malloc(sizeof(DynamicNode));
    result->type = type;
    result->data = data;
    return result;
}
DynamicNode* DynamicNode_r_init(void* ref, int type, void* data){
    DynamicNode* result = (DynamicNode*) ref;
    result->type = type;
    result->data = data;
    return result;
}


/////////////////////////////////////////////////////////////////
/*
uninit
*/
int DynamicNode_n_uninit(DynamicNode* instance){
    free(instance);
    return 0;
}


/////////////////////////////////////////////////////////////////
/*
becomes
*/
DynamicNode* DynamicNode_c_becomes(DynamicNode* instance){
    return DynamicNode_c_init(instance->type, instance->data);
}

DynamicNode* DynamicNode_r_becomes(DynamicNode* instance, void* ref){
    return DynamicNode_r_init(ref, instance->type, instance->data);
}

/////////////////////////////////////////////////////////////////
char* DynamicNode_n_toString(DynamicNode* instance){
    switch(instance->type){
        case CSTR:
            return (char*) (instance->data);
        case CINT:
            return "CINT";
        case SSTR:
            return "SSTR";
        case SINT:
            return "SINT";
        case DARR:
            return "[]";
        case DNODE:
            if (instance->data == instance){
                return "<DNODE>";
            }
            return DynamicNode_n_toString((DynamicNode*) (instance->data));
        default:
            return "NULL";
    }
}

