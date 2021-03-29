#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* origin = argv[1];
    long offset = atol(argv[2]);
    long deleteOffset = atol(argv[3]);
    
    char buffer1[100];
    int state1 = 0;

    char* tempFile = "01234567890abcdefg";
    int originFd = open(origin, O_RDONLY, 0755);
    int tempFd = open(tempFile, O_WRONLY | O_CREAT | O_TRUNC, 0755);
    if (originFd < 0) {
        printf("can not open file %s\n", origin);
        return 1;
    }

    int tempOffset = offset;

    while(1) {
        int bufSize = tempOffset - 100;
        if (bufSize < 0) bufSize = 100 + bufSize;
        state1 = read(originFd, buffer1, bufSize);
        if(state1 == 0) break;
        write(tempFd, buffer1, state1);
    }

    while(1) {
        lseek(originFd, deleteOffset, 1);
        state1 = read(originFd, buffer1, 100);
        if(state1 == 0) break;
        write(tempFd, buffer1, state1);
    }

    close(originFd);
    close(tempFd);

    remove(origin);
    rename(tempFile, origin);

    return 0;
}