#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_BOOKS 100

typedef struct {
    int id;
    char bookname[50];
    char author[50];
    int year;
    int numofborrow;
    bool borrow;
} Book;

Book library[MAX_BOOKS];
int count = 0;

void add_book(int id, char *bookname, char *author, int year) {
    library[count].id = id;
    strcpy(library[count].bookname, bookname);
    strcpy(library[count].author, author);
    library[count].year = year;
    library[count].numofborrow = 0;
    library[count].borrow = false;
    count++;
}

void borrow_book(int id) {
    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            if (library[i].borrow) {
                printf("%s은(는) 이미 대출 중입니다.\n", library[i].bookname);
            } else {
                library[i].borrow = true;
                library[i].numofborrow++;
                printf("%s을(를) 대출했습니다.\n", library[i].bookname);
            }
            return;
        }
    }
    printf("해당 ID의 책이 없습니다.\n");
}

void return_book(int id) {
    for (int i = 0; i < count; i++) {
        if (library[i].id == id) {
            if (!library[i].borrow) {
                printf("%s은(는) 이미 반납된 상태입니다.\n", library[i].bookname);
            } else {
                library[i].borrow = false;
                printf("%s을(를) 반납했습니다.\n", library[i].bookname);
            }
            return;
        }
    }
    printf("해당 ID의 책이 없습니다.\n");
}

void list_all_books() {
    printf("\nlist of all books\n");
    printf("id  bookname      author       year  numofborrow  borrow\n");
    for (int i = 0; i < count; i++) {
        printf("%-3d %-12s %-12s %-6d %-12d %s\n",
               library[i].id, library[i].bookname, library[i].author,
               library[i].year, library[i].numofborrow,
               library[i].borrow ? "True" : "False");
    }
}

void list_available_books() {
    printf("\nlist of available books\n");
    printf("id  bookname      author       year  numofborrow  borrow\n");
    for (int i = 0; i < count; i++) {
        if (!library[i].borrow) {
            printf("%-3d %-12s %-12s %-6d %-12d %s\n",
                   library[i].id, library[i].bookname, library[i].author,
                   library[i].year, library[i].numofborrow, "False");
        }
    }
}

int main() {
    add_book(1, "Luster", "Bookname", 2020);
    add_book(2, "Thalman", "Nicholas", 2021);
    add_book(3, "Hamnet", "Maggie", 2020);

    list_all_books();
    borrow_book(2);
    list_all_books();
    return_book(2);
    list_available_books();

    return 0;
}

