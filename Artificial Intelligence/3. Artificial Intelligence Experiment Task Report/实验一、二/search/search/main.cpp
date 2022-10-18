#include<stdio.h>
#include<pthread.h>
#include<sys/prctl.h>
void* tmain(void*arg)
{
char name[32];
prctl(PR_SET_NAME,(unsignedlong)"xx");
prctl(PR_GET_NAME,(unsignedlong)name);
printf("%s/n", name);
while(1)
sleep(1);
}


int main(void)
{
pthread_t tid;
pthread_create(&tid,NULL, tmain,NULL);
pthread_join(tid,NULL);


return 0;
}
