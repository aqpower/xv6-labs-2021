#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"



void 
primes(int primeNum, int p[]) 
{
    close(p[1]);
    int newPipe[2];
    pipe(newPipe);
    close(newPipe[0]);
    printf("prime %d\n", primeNum);
    int num;
    int fg = 1;
    while (1) {
        if(!read(p[0], &num, 4)){
            close(newPipe[1]);
            close(p[0]);
            exit(0);
            break;
        }
        if (!num) {
            close(newPipe[1]);
            break;
            exit(0);
        }
        if (num % primeNum) {
            write(newPipe[1], &num, 4);
            if(fg && !fork()){
                primes(num, newPipe);
            } else {
                fg = 0;
                wait(0);
            }
        }
    }
}

int 
main(int argc,char *argv[])
{
    int i;
    int p[2];
    pipe(p);
    if(fork()){
        close(p[0]);
        for (i = 2; i < 36; i++) {
            write(p[1], &i, sizeof(int));
        }
        close(p[1]);
        wait(0);
    } else {
        primes(2, p);
    }
    

    exit(0);
}