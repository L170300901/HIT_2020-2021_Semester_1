#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void main(){
    printf("使用execl函数，指定路径\n");
    execl("/bin/ls", "ls", "-l", NULL);
}