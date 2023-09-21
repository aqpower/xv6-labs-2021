#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

int 
main(int argc, char *argv[])
{

    if(argc < 2) {
        fprintf(2, "error: lake of arguments!\n");
        exit(1);
    }

    int i;

    for(i = 1; i < argc; i++){
        int sleep_time = atoi(argv[i]);
        sleep(sleep_time);
        fprintf(2, "sleep ");
        fprintf(2, argv[i]);
        fprintf(2, " ticks.\n");
    }

    exit(0);
}