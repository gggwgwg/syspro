#define RECORD_SIZE  sizeof(struct student)
#define MAX_NAME_LEN 20

struct student {
    int id;
    char name[MAX_NAME_LEN];
    int score;
};


