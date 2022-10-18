
#include <stdio.h>
#include <string.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/types.h>


//改变文件中 某用户的内容
void change(char *user, char *context);

int main(int argc, char **argv){
    uid_t ruid, euid, suid;
    struct passwd *user;
    getresuid(&ruid, &euid, &suid);
    user = getpwuid(ruid);
    printf("当前的用户为：%s\n", user->pw_name);

    switch(argc){
        case 2:    //两个参数，修改用户自己
            change(user->pw_name, argv[1]);
            break;
        case 3:   //三个参数，修改其他用户
            if(strcmp(user->pw_name, "root") == 0){
                change(argv[1], argv[2]);
            }
            break;
    }
    return 0;
}


//改变文件中 某用户的内容
void change(char *user, char *context){
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read_line;  //ssize_t 是signed_size_t
    long offset;
    char *p = NULL;
    int same;
    char buf_after[1000] = {0};
    char buf_before[100][100];

    
    fp = fopen("aaa", "r+");  //打开可读写的文件，该文件必须存在
    offset = ftell(fp);  //得到文件位置指针，当前位置相对于文件收不的偏移量（字节）
    int i = 0;

    //read file
    while((read_line = getline(&line, &len, fp)) != -1){
        strcpy(buf_before[i], line);

        p = strstr(line, ":" );  //判断字符串str2是否是str1的子串，如果是，则返回str2在str1中首次出现的地址，否则，返回NULL
        if(p == NULL){
            continue;
        }
        //p-str line 指定比较字符的个数
        same = strncmp(user, line, p-line);
        //匹配成功，找到该用户的内容
        if(!same){
            int index = 0;
            
            //检测流上的文件结束符，如果文件结束，则返回非0值，否则返回0
            //读取当前指针之后的所有文件内容
            while(!feof(fp)){
                buf_after[index++] = fgetc(fp);
            }
            if(index > 0){
                buf_after[index - 1] == '\0';
            }
            fclose(fp);
            break;

        }
        offset = ftell(fp);
        i++;
    }
    //重新写入文件
    fp = fopen("aaa", "w+");
    for(int j = 0; j < i; j++){
        fprintf(fp, "%s", buf_before[j]);
    }
    fprintf(fp, "%s:%s\n", user, context);
    fprintf(fp, "%s", buf_after);
    printf("将用户%s 的内容改为 %s \n", user, context);
}