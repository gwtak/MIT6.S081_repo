#include "kernel/types.h"
#include "user/user.h"

int main(){
    int nums[36];
    for(int i=0;i<36;i++) nums[i]=i;
    while(1){
        int fd[2];
        pipe(fd);
        int pid=fork();
        if(pid>0){
            for(int i=2;i<36;i++){
                if(nums[i]) write(fd[1],&i,sizeof(int));
            }
            close(fd[1]);
            wait(0);
            exit(0);
        }
        else if(pid==0){
            close(fd[1]);
            int val;
            if(read(fd[0],&val,sizeof(int))>0){
                printf("prime %d\n",val);
                nums[val]=0;
            }
            else exit(0);
            for(int cur;read(fd[0],&cur,sizeof(int))>0;){
                //printf("cur=%d\n",cur);
                if(cur%val==0) nums[cur]=0;
            }
        }
        else{
            printf("error: fork error\n");
            exit(-1);
        }
    }
    exit(0);
    return 0;
}