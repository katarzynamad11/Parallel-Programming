#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc, char *argv[]) {
   
    printf("%s %s,PID: %d\n", argv[1],argv[2], getpid());
    return 0;
}
