#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* origin = argv[1];
    long offset = atol(argv[2]);
    long bytes = atol(argv[3]);

    char buffer;
    int originFd;

    if ((originFd = open(origin, O_RDONLY, 0755)) < 0) {
        printf("can not open file %s\n", origin);
        return 1;
    }

    lseek(originFd, offset, 0);
    int state = 0;
    for (int i = 0; i < bytes; i++) {
        state = read(originFd, &buffer, 1);
        if(state == 0) break;
        write(0, &buffer, 1);
    }

    close(originFd);

    return 0;
}