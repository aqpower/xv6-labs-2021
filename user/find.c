#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#include "kernel/fs.h"

char rule1[5] = ".";
char rule2[5] = "..";

int fmtPath(char *p, char *tar) {
    char buf[50], *q;
    memmove(buf, p, strlen(p));
    q = buf + strlen(p);
    *q = 0;
    while (*q != '/') {
        q--;
    }
    q++;
    if (!strcmp(q, tar)) {
        return 1;
    }
    return 0;
}

void openPath(char path[], char *tar) {
    char buf[512], *p;
    struct dirent de;
    struct stat st;
    int fd;
    if ((fd = open(path, 0)) < 0) {
        fprintf(2, "ls: cannot open %s\n", path);
        return;
    }
    // 将打开文件fd的信息放入*st
    if (fstat(fd, &st) < 0) {
        fprintf(2, "ls: cannot stat %s\n", path);
        close(fd);
        return;
    }
    switch (st.type) {
    case T_FILE:
        if(fmtPath(path, tar)){
            write(1, path, strlen(path));
            write(1, "\n", 1);
        }
        break;
    case T_DIR:
        if (strlen(path) + 1 + DIRSIZ + 1 > sizeof buf) {
            printf("ls: path too long\n");
            break;
        }
        strcpy(buf, path);
        p = buf + strlen(buf);
        *p++ = '/';
        while (read(fd, &de, sizeof(de)) == sizeof(de)) {
            if (de.inum == 0)
                continue;
            if (strcmp(de.name, rule1) && strcmp(de.name, rule2)) {
                memmove(p, de.name, DIRSIZ);
                p[DIRSIZ] = 0;
                openPath(buf, tar);
            }
        }
        break;
    }
    close(fd);
}

int main(int argc, char *argv[]) {
    openPath(argv[1], argv[2]);

    exit(0);
}