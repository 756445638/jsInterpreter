#include <stdio.h>
#include "js.h"
#include "create.h"
#include "util.h"

int yyerror(char* str){
    fprintf(stderr,"compile failed,line:%d,err:%s\n",get_line_number(),str);
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
    temproryMem = interpreter->interpreter_memory;
    current_interpreter = interpreter;
    extern int yyparse(void);
    extern FILE *yyin;



    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        exit(1);
    }







    

    return 0;

}