#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/wait.h>

int main(){
    if (fork()==0)
    {
        printf("当前时间：\n");
        execlp("date", "date", NULL);
    }
    else
    {
        wait(NULL);
        printf("设置新的时间: \n");
        execlp("date", "date", "-s", "2019-11-25",NULL);
    }
    wait(NULL);
    return 0;
}