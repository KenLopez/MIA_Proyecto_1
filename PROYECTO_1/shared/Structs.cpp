#include "../headers/Structs.h"
#include <stdlib.h>
#include <vector>

PARAMETER *createParam(PARAM_NAME name, char *text, int value, PARAM_TYPE param)
{
    PARAMETER *p = (PARAMETER*)malloc(sizeof(PARAMETER));

    if(p==NULL)
        return NULL;

    p->name = name;
    p->value = value;
    p->text = text;
    p->param = param;

    return p;
}

void deleteParam(PARAMETER *p)
{
    if(p==NULL)
        return;
    
    free(p);
}

COMMAND *allocateCOMMAND(){
    COMMAND *c = (COMMAND *)malloc(sizeof(COMMAND));

    if (c == NULL) return NULL;

    c->name = cNONE;
    c->parameters = NULL;

    return c;
}

void deleteCOMMAND(COMMAND *c){
    if (c == NULL)
        return;
    free(c->parameters);
    free(c);
}
