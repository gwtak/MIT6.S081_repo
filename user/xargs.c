#include "kernel/types.h"
#include "user/user.h"

int main(int argc,char** argv){
    if(argc<2){
        printf("usage: xargs command\n");
        exit(-1);
    }
    int argvIndex=0;
    for(int i=1;i<argc;i++) strcpy(argv[argvIndex++],argv[i]);
    char* buf=(char*)malloc(256);
    int bufIndex=0;
    while(read(0,&buf[bufIndex],1)>0){
        if(buf[bufIndex]=='\n'||buf[bufIndex]==' '){
            buf[bufIndex]=0;
            argv[argvIndex++]=buf;
            buf=(char*)malloc(256);
            bufIndex=0;
        }
        else bufIndex++;
    }
    argv[argvIndex++]=0;
    //for(int i=0;i<argvIndex;i++) printf("%s ",argv[i]);
    exec(argv[0],argv);
    exit(0);
    return 0;
}