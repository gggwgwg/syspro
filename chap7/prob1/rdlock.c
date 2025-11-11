#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "student.h"

int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(1);
    }

    int fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    struct flock lock;
    struct student record;

    printf("조회할 학번 입력: ");
    int id; scanf("%d", &id);

    while (read(fd, &record, RECORD_SIZE) > 0) {
        if (record.id == id) {
            lock.l_type = F_RDLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -RECORD_SIZE;
            lock.l_len = RECORD_SIZE;
            fcntl(fd, F_SETLKW, &lock);

            printf("학번:%d 이름:%s 점수:%d\n", record.id, record.name, record.score);
            sleep(5);

            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            break;
        }
    }

    close(fd);
    return 0;
}
<<<<<<< HEAD

=======
>>>>>>> f9398552a7a04525647112aecc2bd27f94c675e8
