#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void main(){
    printf("使用execlp函数，不指定路径\n");
    execlp("ls", "ls", "-l",NULL);
}