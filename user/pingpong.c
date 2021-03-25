#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char** argv){
    int fd[2];
    pipe(fd);
    int pid=fork();
    if(pid>0){
        char buf[128];
        write(fd[1],"pong",4);
        wait(0);
        read(fd[0],buf,sizeof(buf));
        printf("%d: received %s\n",getpid(),buf);
    }
    else if(pid==0){
        char buf[128];
        read(fd[0],buf,sizeof(buf));
        printf("%d: received %s\n",getpid(),buf);
        write(fd[1],"ping",4);
    }
    else{
        printf("error: fork error\n");
        exit(-1);
    }
    exit(0);
    return 0;
}