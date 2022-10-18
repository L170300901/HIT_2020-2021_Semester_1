#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
    printf("以root身份运行root_o.exe\n");
    system("./root_o.exe");

    seteuid(1000);  //临时放弃权限
    printf("临时放弃root权限\n");

    printf("以普通身份运行root_o.exe\n");
    system("./root_o.exe");

    seteuid(0);  //临时放弃权限
    printf("重新获取root权限\n");

    printf("以root身份运行root_o.exe\n");
    system("./root_o.exe");

    setuid(1000);  //永久放弃权限
    printf("永久放弃root权限\n");  

    printf("以普通身份运行root_o.exe\n");
    system("./root_o.exe");

    printf("尝试获取root权限\n");  
    if(setuid(0)<0){
        printf("尝试获取root权限 失败！\n");  
    }
    return 0;





}