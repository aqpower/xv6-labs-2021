#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int
main(int argc, char *argv[])
{
    int p1[2];
    int p2[2];
    pipe(p1);
    pipe(p2);
    int pid = fork();
    if(pid == 0){
        close(p1[1]);
        char buf[2];
        read(p1[0], buf, 1);
        int nowPid = getpid();
        printf("%d: received ping\n", nowPid);
        close(p2[0]);
        write(p2[1], "a", 1);
    } else {
       close(p1[0]);
       write(p1[1], "a", 1);
       close(p1[1]);
       char buf[2];
       read(p2[0], buf, 1);
       int nowPid = getpid();
       printf("%d: received pong\n", nowPid);
    }

    exit(0);
}