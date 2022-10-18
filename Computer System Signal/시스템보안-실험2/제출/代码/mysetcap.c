#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/stat.h>

#undef _POSIX_SOURCE
#include <sys/capability.h>

void list_cap(){
    cap_user_header_t cap_header = malloc(8);
    cap_user_data_t cap_data = malloc(12);
    cap_header->pid = getpid();
    cap_header->version = _LINUX_CAPABILITY_VERSION;

    if (capget(cap_header, cap_data)<0)
    {
        perror("failed capget");
        exit(1);
    }
    printf("cap data permitted: 0x%x, effective: 0x%x, inheritable: 0x%x\n", 
                cap_data->permitted, cap_data->effective, cap_data->inheritable);
}

void listcaps(){
    cap_t caps = cap_get_proc();
    ssize_t y = 0;
    printf("the peocess %d was give capabilities %s\n", (int)getpid(), cap_to_text(caps, &y));
    fflush(0);
    cap_free(caps);
}

int main(){
    cap_t caps = cap_init();
    cap_value_t caplist[5] = {CAP_SETGID, CAP_FSETID, CAP_FOWNER, CAP_SETUID, CAP_CHOWN};
    pid_t parentpid = getpid();
    if(!parentpid){
        printf("pid error!\n");
        return 0;
    }
    unsigned num_caps = 5;
    cap_set_flag(caps, CAP_EFFECTIVE, num_caps, caplist, CAP_SET);
    cap_set_flag(caps, CAP_INHERITABLE, num_caps, caplist, CAP_SET);
    cap_set_flag(caps, CAP_PERMITTED, num_caps, caplist, CAP_SET);
    if(cap_set_proc(caps)){
        perror("cap_set_proc");
        return 0;
    }
    list_cap();
    listcaps();
    if(chown("/home/zhh/lab2/test_setcap",0 ,0)==0){
        printf("chown succeed\n");
    }
    else
    {
        perror("chown()");
        return 0;
    }
    if(chmod("/home/zhh/lab2/test_setcap", 04777)==0){
        printf("chmod succeed\n");
    }
    else
    {
        perror("chmod()");
        return 0;
    }
    cap_clear(caps);
    if(cap_set_proc(caps)){
        perror("cap_set_proc");
        return 0;
    }
    list_cap();
    listcaps();
    cap_free(caps);
    return 0;
    



}





