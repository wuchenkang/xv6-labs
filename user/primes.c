#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int pid, ret;
    int read_fd, write_fd, fds[2];
    int begin, end, num, root;
    
    begin = 2;
    end = 35;
    root = 1;

    do{
        pipe(fds);
        pid = fork();
        if(pid == 0){
            root = 0;

            close(fds[1]);
            read_fd = fds[0];
            
            ret = read(read_fd, &num, sizeof(int));
            if(ret == 0){
                break;
            }else{
                begin = num;
                continue;
            }
        }else{
            close(fds[0]);
            write_fd = fds[1];

            if(root != 0){
                for(int i = begin; i <= end; i++){
                    num = i;
                    write(write_fd, &num, sizeof(int));
                }
                close(write_fd);
            }else{
                printf("prime %d\n", begin);
                do{
                    if(num % begin != 0){
                        write(write_fd, &num, sizeof(int));
                    }
                }while(read(read_fd, &num, sizeof(int)));
                close(read_fd);
                close(write_fd);
            }
            wait(0);
        }
    }while(pid == 0);
    exit(0);
}
