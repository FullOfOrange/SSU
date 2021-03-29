#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* main = argv[1];
    char* copy1 = argv[2];
    char* copy2 = argv[3];
    char buffer[10];
    int mainFd, copy1Fd, copy2Fd;

    mainFd = open(main, O_RDWR|O_CREAT|O_TRUNC, 0755);
    
    if ((copy1Fd = open(copy1, O_RDONLY, 0755)) < 0) {
        printf("can not open file %s\n", copy1);
        return 1;
    }
    if ((copy2Fd = open(copy2, O_RDONLY, 0755)) < 0) {
        printf("can not open file %s\n", copy2);
        return 1;
    }

    int readSize;
    while((readSize = read(copy1Fd, buffer, 10)) != 0) {
        write(mainFd, buffer, readSize);
    }

    while((readSize = read(copy2Fd, buffer, 10)) != 0) {
        write(mainFd, buffer, readSize);
    }

    close(mainFd);
    close(copy1Fd);
    close(copy2Fd);

    return 0;
}