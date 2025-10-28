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

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        perror("open");
        exit(1);
    }

    struct flock lock;
    struct student record;

    printf("수정할 학번 입력: ");
    int id; scanf("%d", &id);

    while (read(fd, &record, RECORD_SIZE) > 0) {
        if (record.id == id) {
            lock.l_type = F_WRLCK;
            lock.l_whence = SEEK_CUR;
            lock.l_start = -RECORD_SIZE;
            lock.l_len = RECORD_SIZE;
            fcntl(fd, F_SETLKW, &lock);

            printf("학번 %d의 이름과 점수를 수정하세요.\n", id);
            scanf("%s %d", record.name, &record.score);
            lseek(fd, -RECORD_SIZE, SEEK_CUR);
            write(fd, &record, RECORD_SIZE);

            sleep(10); // 잠금 유지 상태 확인용
            lock.l_type = F_UNLCK;
            fcntl(fd, F_SETLK, &lock);
            break;
        }
    }

    close(fd);
    return 0;
}

