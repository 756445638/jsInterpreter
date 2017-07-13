#include "js.h"

JsFunction*
JS_search_func_from_list(JsFucntionList* list,char* name){
    while(list != NULL){
        if(0 == strcmp(list->func->name,name)){
            return list;
        }
        list = list->next;
    }
    return NULL;
}



