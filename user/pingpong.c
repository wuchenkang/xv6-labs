#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int main(int argc, char *argv[]){
    int pid, ret, fds[4];
    char message = 'O';

    ret = pipe(fds);
    if(ret != 0){
        fprintf(2, "pingpong: cannot create pipe\n");
        exit(1);
    }
    ret = pipe(fds+2);
    if(ret != 0){
        fprintf(2, "pingpong: cannot create pipe\n");
        exit(1);
    }

    pid = fork();
    if(pid < 0){
        fprintf(2, "pingpong: failed to fork\n");
        exit(1);
    }

    if(pid == 0){
        close(fds[1]);
        close(fds[2]);

        read(fds[0], &message, 1);
        printf("%d: received ping\n", getpid());
        close(fds[0]);

        write(fds[3], &message, 1);
        close(fds[3]);
    }else{
        close(fds[0]);
        close(fds[3]);

        write(fds[1], &message, 1);
        close(fds[1]);

        read(fds[2], &message, 1);
        printf("%d: received pong\n", getpid());
        close(fds[2]);
        
        wait(0);
    }
    exit(0);
}
