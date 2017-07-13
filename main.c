#include <stdio.h>
#include "js.h"
#include "create.h"
#include "util.h"

int yyerror(char* str){
    fprintf(stderr,"compile failed,err:%s\n",str);
}


int main(int argc,char **argv){
    FILE *fp;
    if(argc != 2){
        fprintf(stderr,"Usage:%s filename",argv[0]);
        exit(1);
    }
    fp = open(argv[1],"r");
    if(fp == NULL){
        fprintf(stderr,"no such file",argv[1]);
        exit(1);
    }
    /*create interpreter*/
    JsInterpreter* interpreter =  JS_create_interpreter();
    if(NULL == interpreter){
        fprintf(stderr,"create interpreter failed...");
        exit(1);
    }  
    current_interpreter = interpreter;
    extern int yyparse(void);
    extern FILE *yyin;

    crb_set_current_interpreter(interpreter);

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }
    

    return 0;

}