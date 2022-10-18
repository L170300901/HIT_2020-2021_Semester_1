#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void main(){
    printf("使用execl函数，不指定路径\n");
    execl("ls", "ls", "-l",NULL);
}