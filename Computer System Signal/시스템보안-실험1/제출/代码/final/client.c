#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

/*客户函数所有者为用户*/
/*调用http程序， http的所有者为root，同时拥有setuid位*/


void show_id(uid_t *ruid, uid_t *euid, uid_t *suid){
    getresuid(ruid, euid, suid);  //获取r，e，suid
    printf("ruid: %d,  euid: %d,  suid: %d\n", *ruid, *euid, *suid);  //打印当前uid号
}


int main(int argc, char *argv[]){

    uid_t ruid, euid, suid;
    pid_t pid;
    printf("*********** 客户端进程 ************\n");

    //第一次开启多进程，测试fork和uid的关系
    printf("**** 测试fork ****\n");

    if( (pid=fork()) < 0 ){  
        printf(" fork error ! \n");
    }
    else if (pid == 0){
        printf("子进程1: ");
        show_id(&ruid, &euid, &suid);
        exit 0;
    }
    else{
        printf("父进程:");
        show_id(&ruid, &euid, &suid);
    }


    //第2次开启多进程，测试execl和setuid的关系，同时测试root权限的收放
    printf("**** 测试execl ****\n");

    if( (pid=fork()) < 0 ){  
        printf(" fork error ! \n");
    }
    else if (pid == 0){
        printf("子进程2: \n");
        execl("http", "./http", NULL);
    }
    else{
        printf("父进程:");
        show_id(&ruid, &euid, &suid);
    }

    printf("*********** 客户端进程结束 ************\n");

    return 0;

}


