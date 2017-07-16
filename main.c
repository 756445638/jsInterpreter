#include <stdio.h>
#include "js.h"
#include "create.h"
#include "util.h"
#include <unistd.h>

int yyerror(char* str){
    fprintf(stderr,"compile failed,line:%d,err:%s\n",get_line_number(),str);
    return 0;
}


int main(int argc,char **argv){
    FILE *fp;
    if(argc != 2){
        fprintf(stderr,"Usage:%s filename",argv[0]);
        _exit(1);
    }
    fp = fopen(argv[1],"r");
    if(fp == NULL){
        fprintf(stderr,"no such file:%s",argv[1]);
        _exit(1);
    }



    /*create interpreter*/
    JsInterpreter* interpreter =  JS_create_interpreter();
    if(NULL == interpreter){
        fprintf(stderr,"create interpreter failed...");
        _exit(1);
    }
    current_interpreter = interpreter;
    extern int yyparse(void);
    extern FILE *yyin;
    

    yyin = fp;
    if (yyparse()) {
        fprintf(stderr, "Error ! Error ! Error !\n");
        _exit(1);
    }


    

    return 0;

}