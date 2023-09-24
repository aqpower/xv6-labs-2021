#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"
#include "kernel/param.h"

int main(int argc, char *argv[]) {
    char buf[512];
    sleep(10);
    read(0, buf, sizeof(buf));
    char *q = buf;
    char *p = buf;
    char *argList[32];
    int ind = 0;
    int i;
    for(i = 1;i < argc; i++){
        argList[ind++] = argv[i];
    }
    while (1) {
        if (*q == ' ') {
            *q = 0;
            argList[ind++] = p;
            p = q + 1;
        } else if (*q == '\n') {
            *q = '\0';
            argList[ind++] = p;
            p = q + 1;
            if(!fork()){
                exec("echo", argList);
                exit(0);
            } else {
                ind = argc;
                wait(0);
            }
        } else if (*q == '\0') {
            break;
        }
        q++;
    }


    exit(0);
}
