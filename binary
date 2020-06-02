#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_VALUE 255

typedef struct {
    double x, y;
}Point;

typedef struct {        // 플레이어 정보가 들어가있는 구조체
    char id[MAX_VALUE];
    int age;
    int HP;
    Point point;
    char* list[255];
}User;

int g_count = 0;    // 동맹 유저가 몇명인지 표시해주는 전역변수

void write_User(User* user, FILE* fp) {   // 플레이어 정보 기록하는 함수
    remove("binary.bin");
    fp = fopen("binary.bin", "a+b");
    char ch = ' ';  // 데이터 추가 제어 변수
    printf("ID 를 입력하세요 : ");
    scanf("%s", user->id);
    fwrite(&user->id, sizeof(user->id), sizeof(user->id) / sizeof(user->id[0]), fp);
    printf("나이를 입력하세요 : ");
    scanf("%d", &user->age);
    fwrite(&user->age, sizeof(int), 1, fp);
    printf("HP 를 입력하세요 : ");
    scanf("%d", &user->HP);
    fwrite(&user->HP, sizeof(int), 1, fp);
    printf("X 좌표를 입력하세요 : ");
    scanf("%lf", &user->point.x);
    fwrite(&user->point.x, sizeof(double), 1, fp);
    printf("Y 좌표를 입력하세요 : ");
    scanf("%lf", &user->point.y);
    fwrite(&user->point.y, sizeof(double), 1, fp);

    while (1) {
        user->list[g_count] = malloc(sizeof(char) * MAX_VALUE);
        printf("동맹 ID 를 입력하세요 :  ");
        scanf("%s", user->list[g_count]);
        user->list[g_count][strlen(user->list[g_count])] = '\0';
        int size = sizeof(user->list[g_count]);
        fwrite(&user->list[g_count], size, 1, fp);
        g_count++;  // 동맹 유저 추가했으니 전역변수 증가
        printf("데이터 추가를 계속 (Y/N) : ");
        scanf(" %c", &ch);  // 데이터 추가 제어 N이면 빠져나감
        if (ch == 'N') {
            printf("완료되었습니다.\n");
            break;
        }
    }
    printf("\n");
}
void print_User(User* user) {   // 플레이어 정보 출력하는 함수
    printf("ID: %s / 나이: %d / HP: %d / 좌표: %.3lf,%.3lf\n", user->id, user->age, user->HP, user->point.x, user->point.y);
    printf("등록된 동맹 수: %d명\n", g_count);
    for (int i = 0; i < g_count; i++) { // g_count까지 있는 동맹 유저 정보를 전부 출력
        if (i == g_count - 1)
            printf("%s\n", user->list[i]);
        else
            printf("%s / ",user->list[i]);
    }
}

int main(int argc, char* argv[]) {
    FILE* fp;       // 파일 포인터
    int value;     // 1~3번을 받을 value 
    User user[MAX_VALUE];   //User 구조체를 MAX_VALUE로 선언

    fp = fopen("binary.bin", "a+b");    // fp에 binary.bin를 바이너리 파일을 읽고 추가 쓰기로 파일 열기

    if (fp == NULL) {   // 파일을 열지 못한다면 오류 출력
        fprintf(stderr, "파일 binary.bin 을 열 수 없습니다.\n");
        exit(1);
    }

    do {
        printf("\n1. 플레이어 정보 기록\n");
        printf("2. 플레이어 정보 확인\n");
        printf("3. 종료\n");
        printf("입력하세요> ");
        scanf("%d", &value);

        switch (value)      // value의 값에따라 실행되는 switch문 
        {
        case 1:
            write_User(user, fp);     // 플레이어 정보 추가하는 함수
            printf("입력이 완료되었습니다.\n");
            break;
        case 2:
            print_User(user);
            break;
        case 3:
            printf("종료되었습니다.\n");
            break;
        default: printf("올바르지 않은 접근입니다.\n"); break;
        }

    } while (value != 3);

    fclose(fp); // 파일 닫는 함수
    return 0;
}
