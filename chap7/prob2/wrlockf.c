#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include "../student.h"   // 상위 폴더에 student.h 존재한다고 가정

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

    struct student record;
    int id;

    printf("수정할 학번 입력: ");
    scanf("%d", &id);

    while (read(fd, &record, sizeof(record)) > 0) {
        if (record.id == id) {
            printf("\n현재 학번 %d 잠금 시도 중...\n", id);

            // 현재 위치부터 레코드 크기만큼 잠금
            if (lockf(fd, F_LOCK, sizeof(record)) == -1) {
                perror("lockf");
                close(fd);
                exit(1);
            }

            printf("잠금 완료! (%d)\n", id);
            printf("수정할 이름과 점수 입력: ");
            scanf("%s %d", record.name, &record.score);

            // 수정 내용 덮어쓰기
            lseek(fd, -sizeof(record), SEEK_CUR);
            write(fd, &record, sizeof(record));

            printf("수정 완료. 10초 동안 잠금 유지 중...\n");
            sleep(10);

            // 잠금 해제
            lockf(fd, F_ULOCK, sizeof(record));
            printf("잠금 해제 완료.\n");
            close(fd);
            return 0;
        }
    }

    printf("해당 학번을 찾을 수 없습니다.\n");
    close(fd);
    return 0;
}

