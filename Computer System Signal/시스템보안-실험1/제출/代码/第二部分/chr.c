#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(){
    uid_t ruid, euid, suid;
    getresuid(&ruid, &euid, &suid);
    printf("before:\n ruid:%d\t euid:%d\t suid:%d\n", ruid, euid, suid);
    printf("now chdir\n");
    chdir("/var/chroot\n");
    if(chroot("/var/chroot")==0){
        printf("chroot succeed!\n");
    }
    getresuid(&ruid, &euid, &suid);
    printf("before:\n ruid:%d\t euid:%d\t suid:%d\n", ruid, euid, suid);
    printf("now give up root permission.....\n");
    setresuid(1000, 1000, 1000);   //test的uid
    getresuid(&ruid, &euid, &suid);
    printf("now: \nruid:%d\teuid:%d\tsuid:%d\n", ruid, euid, suid);
    execlp("ls", "ls", NULL);
    return 0;
}

