#include <stdio.h>
#include "js.h"

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
    



}