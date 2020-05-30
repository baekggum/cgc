#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_VALUE 255

typedef struct {        // 유저정보가 들어가있는 구조체
    char name[MAX_VALUE];
    int age;
    char email[MAX_VALUE];
}User;

int g_count = 0;    // 전체 유저가 몇명인지 표시해주는 전역변수

bool is_Email(char* str) {  // 이메일의 형식인지 판별해주는 함수
    char form = '@';
    char tmp[MAX_VALUE];    // @뒤의 문자열을 넣어줄 변수
    int i = 0, j = 0;

    if (strchr(str, form) != NULL) {    // 받아온 문자열에 @가 있으면 실행
        for (i = 0; i < strlen(str); i++) { // @이후의 i와 받을 j를반환
            if (str[i - 1] == '@') {
                tmp[j] = str[i];
                i++;
                j++;
                break;
            }
        }
        for (i; i < strlen(str); i++) { // @이후의 값을 대입
            tmp[j] = str[i];
            j++;
        }
        tmp[j] = '\0';  // tmp 끝에 \0값 대입
        form = '.';     // .이 있는지 판별
        if (strchr(tmp, form) != NULL) {    // 받아온 문자열에 .이 있으면 실행
            if (tmp[0] != '.') {    // @뒤에 바로 .이 있다면 false반환
                for (int i = 0; i < strlen(tmp); i++) {
                    if (tmp[i] == '.' && tmp[i + 1] != '\0')    // .뒤에 다른 문자가 있으면 true 반환
                        return true;
                }
            }
            printf("이메일 형식이 맞지 않습니다.\n");
            return false;
        }
    }
    printf("이메일 형식이 맞지 않습니다.\n");
    return false;
}
void sync_User(User* user, FILE* fp) {  // 텍스트파일에 있는 유저정보 연동
    while (1)
    {
        char strTemp[MAX_VALUE];    // 문자열을 받아올 변수
        fgets(strTemp, sizeof(strTemp), fp);    // fp에 적혀있는 모든 값을 strTemp로 받아옴
        if (feof(fp)) break;    // 텍스트파일의 끝이라면 종료
        char* ptr = strtok(strTemp, "/");   // ptr에 /로 끊어서 값을 저장
        strcpy(user[g_count].name, ptr);    // user의 이름에 끊어진 ptr 이름 값 대입
        user[g_count].name[strlen(user[g_count].name) - 1] = '\0';  // 이름 끝에 \0 대입
        ptr = strtok(NULL, " ");    // 빈공백으로 문자열 자름
        user[g_count].age = atoi(ptr);  // 잘린 문자열을 int형으로 바꿔서 대입
        ptr = strtok(NULL, " ");    // 빈공백으로 문자열 자름
        ptr = strtok(NULL, " ");    // 빈공백으로 문자열 자름
        strcpy(user[g_count].email, ptr);   // 잘린 문자열을 email값에 대입
        ptr = strtok(NULL, " ");    // 빈공백으로 문자열 자름
        g_count++;  // 유저정보 수 증가
    }
}
void RewriteFile(FILE* fp, User* _user) // 텍스트파일을 다시 적는 함수
{
    fclose(fp); // 열린 fp파일 닫기
    remove("minidb.txt");   // 기존에 있는 minidb.txt 파일 삭제
    fp = fopen("minidb.txt", "a+t");    // 다시 minidb.txt파일 a+t모드로 열기
    for (int i = 0; i < g_count; ++i)   // User에 적용된 g_count만큼의 유저를 텍스트파일에 출력
    {
        fprintf(fp, "%s / %d / %s /\n", _user[i].name, _user[i].age, _user[i].email);
    }
}
void add_User(User* user, FILE* fp) {   // 유저 추가하는 함수
    char ch = ' ';  // 버퍼 지우기, 데이터 추가 제어 변수
    while (1) {
        printf("이름 : ");
        scanf("%c", &ch);   //버퍼 지우는 용도
        ch = ' ';
        fgets(user[g_count].name, sizeof(user[g_count].name), stdin);   // 유저의 이름을 입력받음
        user[g_count].name[strlen(user[g_count].name) - 1] = '\0';  // 끝에 \0문자 대입
        printf("나이 : ");
        scanf("%d", &user[g_count].age);
        while (1) {
            printf("이메일주소 : ");
            scanf("%s", user[g_count].email);
            if (is_Email(user[g_count].email))  // 이메일의 형식인지 판별
                break;
        }
        fprintf(fp, "%s / %d / %s /\n", user[g_count].name, user[g_count].age, user[g_count].email);    // 텍스트파일에 적용
        g_count++;  // 유저 추가했으니 전역변수 증가
        printf("데이터 추가를 계속 (Y/N) : ");
        scanf(" %c", &ch);  // 데이터 추가 제어 N이면 빠져나감
        if (ch == 'N')
            break;
        printf("\n");
    }
}
void edit_User(User* user, FILE* fp, int _count) {  // 유저정보 수정하는 함수
    char ch = ' ';
    printf("이름 : ");
    scanf(" %[^\n]s", user[_count].name);   // 공백포함 문자열을 받아서 이름에 대입
    printf("나이 : ");
    scanf(" %d", &user[_count].age);
    while (1) {
        printf("이메일주소 : ");
        scanf(" %s", user[_count].email);
        if (is_Email(user[_count].email))   // 이메일의 형식인지 판별
            break;
    }
    RewriteFile(fp, user);      // 유저정보 수정했으니 파일을 다시 쓰기
    printf("수정 완료 되었습니다.\n");
}
void delete_User(User* user, FILE* fp, int _count) {    // 유저 삭제 함수
    for (int i = _count; i < g_count - 1; i++) {    // 삭제할 유저 이름 번째에 있는 i의 값을 한개씩 땡겨서 없앰
        strcpy(user[i].name, user[i + 1].name);
        user[i].age = user[i + 1].age;
        strcpy(user[i].email, user[i + 1].email);
    }
    g_count--;  // 줄었으니 g_count 감소
    RewriteFile(fp, user);  // 유저정보 삭제했으니 파일 다시 쓰기
}
void print_User(User* user) {   // 유저정보 출력하는 함수
    for (int i = 0; i < g_count; i++) { // g_count까지 있는 유저 정보를 전부 출력
        printf("%s / %d / %s \n", user[i].name, user[i].age, user[i].email);
    }
}

int main(int argc, char* argv[]) {
    FILE* fp;       // 파일 포인터
    int value;     // 1~5번을 받을 value 
    char find_name[MAX_VALUE];    // 찾을 이름을 넣을 find_name
    User user[MAX_VALUE];   //User 구조체를 MAX_VALUE로 선언

    fp = fopen("minidb.txt", "a+t");    // fp에 minidb.txt를 텍스트 파일을 읽고 추가 쓰기로 파일 열기

    if (fp == NULL) {   // 파일을 열지 못한다면 오류 출력
        fprintf(stderr, "파일 minidb.txt 을 열 수 없습니다.\n");
        exit(1);
    }
    sync_User(user, fp);    // minidb에 있는 정보를 불러오는 함수

    do {
        printf("\n1. 신규회원 저장\n");
        printf("2. 회원정보 수정\n");
        printf("3. 회원 삭제\n");
        printf("4. 모든 회원 리스트\n");
        printf("5. 종료\n");
        printf("입력하세요> ");
        scanf("%d", &value);

        switch (value)      // value의 값에따라 실행되는 switch문 
        {
        case 1:
            add_User(user, fp);     // 유저정보 추가하는 함수
            printf("입력이 완료되었습니다.\n");
            break;
        case 2:
            printf("수정할 사람 이름을 입력해주세요: ");
            scanf(" %[^\n]s", find_name);   // 공백포함 문자열을 받음
            for (int i = 0; i < g_count; i++) {
                if (!strcmp(user[i].name, find_name)) { //입력받은 문자열과 db에 있는 이름이 같은지 판별 후 같다면 실행
                    printf("사용자 %s 을 수정합니다.\n", user[i].name);
                    edit_User(user, fp, i); // 유저정보 수정하는 함수
                    break;
                }
                else if (i == g_count - 1)
                    printf("사용자 %s 은 없습니다.\n", find_name);
            }
            break;
        case 3:
            printf("삭제할 사람 이름을 입력해주세요: ");
            scanf(" %[^\n]s", find_name);   // 공백포함 문자열을 받음
            for (int i = 0; i < g_count; i++) {
                if (!strcmp(user[i].name, find_name)) {
                    printf("사용자 %s 을 삭제합니다.\n", user[i].name);
                    delete_User(user, fp, i);   // 유저정보 삭제하는 함수
                    break;
                }
                else if (i == g_count - 1)
                    printf("사용자 %s 은 없습니다.\n", find_name);
            }
            break;
        case 4:
            print_User(user);   // 모든 유저정보 출력하는 함수
            break;
        case 5:
            printf("종료합니다.\n");
            break;
        default: printf("올바르지 않은 접근입니다.\n"); break;
        }

    } while (value != 5);

    fclose(fp); // 파일 닫는 함수
    return 0;
}
