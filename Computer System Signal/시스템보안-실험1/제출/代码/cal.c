#include "stdio.h"
#include "time.h"

void main(){
    FILE *fp = fopen("/公共的/start.txt", "w");
    fprintf(fp, "This line will be written when the computer is turned on\n");
    fclose(fp);
}