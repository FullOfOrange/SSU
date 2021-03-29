#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* origin = argv[1];
    long offset = atol(argv[2]);
    char* data = argv[3];
    int dataLen = 0;
    while (data[dataLen] != '\0') dataLen++;
    
    int originFd = open(origin, O_RDWR, 0755);
    if (originFd < 0) {
        printf("can not open file %s\n", origin);
        return 1;
    }
    // move pointer to offset position
    lseek(originFd, offset, 0);

    char buffer1[dataLen];
    char buffer2[dataLen];
    int state1 = 0;
    int state2 = 0;
    
    state2 = read(originFd, buffer2, dataLen);
    lseek(originFd, offset, 0);
    write(originFd, data, dataLen);
    int currentLen = offset + dataLen;
    
    while(1) {
        state1 = read(originFd, buffer1, dataLen);
        lseek(originFd, currentLen, 0);
        write(originFd, buffer2, state2);
        currentLen += state2;
        lseek(originFd, currentLen);
        if (state1 == 0) break;
        int j = 0;
        for(; j < state1; j++) {
            buffer2[j] = buffer1[j];
        }
        state2 = state1;
    }

    close(originFd);

    return 0;
}