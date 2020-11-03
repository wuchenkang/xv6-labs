#include "kernel/types.h"
#include "kernel/stat.h"
#include "kernel/param.h"
#include "kernel/fcntl.h"
#include "user/user.h"

#define MAXCHR 512

int main(int argc, char *argv[]){
    int pid, i, j, k;
    char temp, store[MAXCHR], *param[MAXARG];

    j = 0;
    for(i = 0; i < argc-1; i++){
        param[i] = store + j;
        strcpy(param[i], argv[i+1]);
        j += sizeof(argv[i+1]);
    }
    k = j;

    temp = ' ';
    do{
        if(temp != ' ' && temp != '\n'){
            store[j++] = temp;
        }else if(temp == ' '){
            store[j++] = '\0';
            param[i++] = store + j;
        }else{
            store[j++] = '\0';
            pid = fork();
            if(pid == 0){
                exec(param[0], param);
            }else{
                wait(0);
                i = argc - 1;
                j = k;
            }
        }
    }while(read(0, &temp, 1) != 0);

    exit(0);
}
