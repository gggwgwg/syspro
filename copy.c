#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

int main(int argc, char *argv[]) {
    FILE *src, *dst;
    int ch;
    int option;

    if (argc != 4) {
        fprintf(stderr, "사용법: %s [옵션:0~2] source.txt destination.txt\n", argv[0]);
        return 1;
    }

    option = atoi(argv[1]);
    if (option < 0 || option > 2) {
        fprintf(stderr, "옵션은 0, 1, 2 중 하나여야 합니다.\n");
        return 1;
    }

    src = fopen(argv[2], "r");
    if (src == NULL) {
        perror("원본 파일 열기 실패");
        return 1;
    }

    dst = fopen(argv[3], "w");
    if (dst == NULL) {
        perror("복사본 파일 생성 실패");
        fclose(src);
        return 1;
    }

    while ((ch = fgetc(src)) != EOF) {
        if (option == 1)
            ch = tolower(ch);
        else if (option == 2)
            ch = toupper(ch);
        fputc(ch, dst);
    }

    fclose(src);
    fclose(dst);

    dst = fopen(argv[3], "r");
    if (dst == NULL) {
        perror("복사본 파일 읽기 실패");
        return 1;
    }

    printf("결과 (%s 파일 내용): ", argv[3]);
    while ((ch = fgetc(dst)) != EOF)
        putchar(ch);
    printf("\n");

    fclose(dst);
    return 0;
}


