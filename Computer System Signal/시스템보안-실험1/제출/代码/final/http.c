#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void show_id(uid_t *ruid, uid_t *euid, uid_t *suid){    
    getresuid(ruid, euid, suid);  //获取r，e，suid
    printf("ruid: %d,  euid: %d,  suid: %d\n", *ruid, *euid, *suid);  //打印
    
}

int main(int argc, char *argv[]){

    uid_t ruid, euid ,suid;

    printf("***** http server START! *****\n");

    show_id(&ruid, &euid, &suid);  //打印初始uid
    
    printf("以root身份运行root_only.exe\n");
    system("./root_only.exe");



    seteuid(1000);  //临时放弃root权限
    printf("\n临时放弃root权限\n");
    show_id(&ruid, &euid, &suid);

    printf("以普通身份运行root_only.exe\n");
    system("./root_only.exe");



    seteuid(0);  //重新获取root权限
    printf("\n重新获取root权限\n");
    show_id(&ruid, &euid, &suid);

    printf("以root身份运行root_only.exe\n");
    system("./root_only.exe");



    setuid(1000);  //永久放弃root权限
    printf("\n永久放弃root权限\n");  
    show_id(&ruid, &euid, &suid);

    printf("以普通身份运行root_o.exe\n");
    system("./root_o.exe");


    printf("\n尝试重新获取root权限\n");  
    show_id(&ruid, &euid, &suid);

    if(setuid(0)<0){
        printf("尝试重新获取root权限 失败！\n");  
    }

    printf("***** http server END! *****\n");
    return 0;
}