#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

void show_ids(void){
    printf("real uid: %d\n", getuid());
    printf("effective uid: %d\n", geteuid());
}

int main(int argc, char *argv[]){
    int uid;

    // 假设用户切换到http_server.exe的拥有者
    if(setuid(getuid()) < 0){
        perror("setuid error!");
    }
    show_ids();
    system("echo chmod u+s http_server.exe");
    system("chmod u+s http_server.exe");  //执行chmod u+s ,设置其setuid位
    system("ls -l http_server.exe");    //显示一下http_server.exe的权限位
    system("./http_server.exe");     //执行该文件
    return (0);
}



