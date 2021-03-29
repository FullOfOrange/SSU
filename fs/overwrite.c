#include <stdio.h>
#include <fcntl.h>

int main(int argc, char* argv[]) {
    char* origin = argv[1];
    long offset = atol(argv[2]);
    char* data = argv[3];

    char buffer[100];
    int originFd;

    if ((originFd = open(origin, O_RDWR, 0755)) < 0) {
        printf("can not open file %s\n", origin);
        return 1;
    }

    lseek(originFd, offset, 0);

    char temp;
    int i = 0;
    while ((temp = data[i++]) != '\0') {
        write(originFd, &temp, 1);
    }

    close(originFd);

    return 0;
}