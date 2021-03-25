#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/fs.h"
#include "user/user.h"

char* fmtname(char* path){
    char* p=path+strlen(path);
    while(p>=path&&*p!='/') p--;
    return ++p;
}

void find(char* path,char* target){
    int fd;
    struct dirent de;
    struct stat st;
    if((fd=open(path,0))<0){
        printf("error: cant open %s\n",path);
        exit(-1);
    }
    if(fstat(fd,&st)<0){
        printf("error: cant stat %s\n",path);
        exit(-1);
    }
    if(st.type==T_FILE){
        char* file=fmtname(path);
        if(strcmp(file,target)==0) printf("%s\n",path);
    }
    else if(st.type==T_DIR){
        while(read(fd,&de,sizeof(de))==sizeof(de)){
            if(de.inum==0||strcmp(de.name,".")==0||strcmp(de.name,"..")==0) continue;
            char buf[256];
            strcpy(buf,path);
            strcpy(buf+strlen(buf),"/");
            strcpy(buf+strlen(buf),de.name);
            //printf("%s\n",buf);
            if(stat(buf,&st)<0){
                printf("error: cant stat %s\n",buf);
                exit(-1);
            }
            if(st.type==T_FILE){
                char* file=fmtname(buf);
                if(strcmp(file,target)==0) printf("%s\n",buf);
            }
            else if(st.type==T_DIR) find(buf,target);
        }
    }
}

int main(int argc,char** argv){
    if(argc<3){
        printf("usage: find path target\n");
        exit(-1);
    }
    char* path=argv[1];
    char* target=argv[2];
    find(path,target);
    exit(0);
    return 0;
}