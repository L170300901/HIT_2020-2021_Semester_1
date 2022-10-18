#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


void show_ids(int *ruid, int *euid, int *suid){
    getresuid(ruid, euid, suid);  //获取r，e，suid
    printf("real uid: %d,  effective uid: %d,  suid: %d  ", *ruid, *euid, *suid);  //打印
    
}


int main(int argc, char *argv[]){
    int ruid, euid, suid;

    print("**************\n");
    printf("after:\n");
    show_ids(&ruid, &euid, &suid);   //打印父进程的res uid
    
    return 0;
}

