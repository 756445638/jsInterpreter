#ifndef STRING_H
#define STRING_H

#define STRING_INIT_ALLOC_SIZE (256)

typedef struct STRING_tag{
    char* s;
    int length;
    /* alloc >= length + 1*/
    int alloc;
}STRING;








#endif