#include "string.h"
#include "memory.h"
#include <string.h>
#include "util.h"

STRING* STRING_concat(Memory*m ,STRING* s ,char* ss){
    int length = strlen(ss);
    int i ;
    if((length + s->length + 1) > s->alloc) {
        //alloc more memory
        STRING* newstring = MEM_alloc(m,sizeof(STRING) + s->alloc*2,get_line_number());
        if(NULL == newstring){
            MEM_free(m,s);
            return NULL;
        }
        newstring->alloc = s->alloc*2;
        newstring->s = (char*)newstring + sizeof(STRING);
        for(i=0;i<s->length;i++){  /*copy old*/
            newstring->s[i] = s->s[i];
        }
        for(i = 0;i<length ;i++){/*copy new*/
            newstring->s[i + s->length] = ss[i];
        }
        newstring->s[length + s->length] = 0;  /*end*/ 
        newstring->length = length + s->length;/*reset lenth*/
        MEM_free(m,s);  /*free old string*/
        return newstring;
    }else{
        for(i = 0;i<length;i++){
            s->s[s->length + i] = ss[i];
        }
        s->s[s->length + length] = 0;
        s->length += length;
        return s;
    }
}

STRING* STRING_new(Memory*m){
    STRING* newstring = MEM_alloc(m,sizeof(STRING) + STRING_INIT_ALLOC_SIZE,get_line_number());
    if(NULL == newstring){
        return NULL;
    }
    newstring->length = 0;
    newstring->alloc = STRING_INIT_ALLOC_SIZE;
    newstring->s = (char*) (newstring + 1);
    return newstring;
}


STRING* STRING_new_form_chars(Memory*m,char* s){
	int length = strlen(s);
	STRING* newstring = MEM_alloc(m,sizoeof(STRING) + length * 2,get_line_number());
    if(NULL == newstring){
        return NULL;
    }
	newstring->length = length;
	newstring->alloc = length * 2;
	newstring->s = (char*)(newstring + 1);
	int i = 0;
	for(i ==0 ;i<length;i++){
		newstring->s[i] = s[i];
	}
	newstring->s[length] = 0;
	return newstring;
}



STRING* STRING_appendchar(Memory*m,STRING* s,char c){
    char a[2] = {c,0};
    return STRING_concat(m,s,a);
}




