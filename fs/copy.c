#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* origin = argv[1];
    char* copy = argv[2];
    char buffer[11];


    int originFd, copyFd;

    if ((originFd = open(origin, O_RDONLY, 0755)) < 0) {
        printf("can not open file %s\n", origin);
        return 1;
    }
    copyFd = open(copy, O_RDWR|O_CREAT|O_TRUNC, 0755);

    int readSize;
    while((readSize = read(originFd, buffer, 10)) != 0) {
        write(copyFd, buffer, readSize);
    }

    close(originFd);
    close(copyFd);

    return 0;
}