#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <mode> <filename>\n", argv[0]);
        return 1;
    }
    int mode = strtol(argv[1], NULL, 8);
    if (chmod(argv[2], mode) < 0)
        perror("chmod");
    else
        printf("Permission changed: %s -> %o\n", argv[2], mode);
    return 0;
}

