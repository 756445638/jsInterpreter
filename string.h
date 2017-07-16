#ifndef STRING_H
#define STRING_H
#include "memory.h"

#define STRING_INIT_ALLOC_SIZE (256)

typedef struct STRING_tag{
    char* s;
    int length;
    /* alloc >= length + 1*/
    int alloc;
}STRING;


STRING* STRING_concat(Memory*m ,STRING* s ,char* ss);
STRING* STRING_new(Memory*m);
STRING* STRING_appendchar(Memory*m,STRING* s,char c);





#endif