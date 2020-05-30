#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#define MAX_VALUE 255

typedef struct {
  char name[255];
  int age;
  char email[255];
}User;

int g_count = 0;

bool is_Email(char* str) {
  char form = '@';
  char tmp[30];
  int i = 0, j = 0;

  if (strchr(str, form) != NULL) {
    for (i = 0; i < strlen(str); i++) {
      if (str[i - 1] == '@') {
        tmp[j] = str[i];
        i++;
        j++;
        break;
      }
    }
    for (i; i < strlen(str); i++) {
      tmp[j] = str[i];
      j++;
    }
    tmp[j] = '\0';
    form = '.';
    if (strchr(tmp, form)!=NULL) {
      if (tmp[0] != '.') {
        for (int i = 0; i < strlen(tmp); i++) {
          if (tmp[i] == '.' && tmp[i + 1] != '\0')
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
void sync_User(User* user, FILE* fp) {
  while (1)
  {
    char strTemp[255];
    fgets(strTemp, sizeof(strTemp), fp);
    if (feof(fp)) break;
    char* ptr = strtok(strTemp, "/");
    strcpy(user[g_count].name, ptr);
    user[g_count].name[strlen(user[g_count].name) - 1] = '\0';
    ptr = strtok(NULL, " ");
    user[g_count].age = atoi(ptr);
    ptr = strtok(NULL, " ");
    ptr = strtok(NULL, " ");
    strcpy(user[g_count].email, ptr);
    ptr = strtok(NULL, " ");
    g_count++;
  }
}
void RewriteFile(FILE* fp, User* _user)
{
  fclose(fp);
  remove("minidb.txt");
  fp = fopen("minidb.txt", "a+t");
  for (int i = 0; i < g_count; ++i)
  {
    fprintf(fp, "%s / %d / %s /\n", _user[i].name, _user[i].age, _user[i].email);
  }
}
void add_User(User* user, FILE* fp) {
  char ch = ' ';
  while(1){
    printf("이름 : ");
    scanf("%c",&ch);
    ch=' ';
    fgets(user[g_count].name, sizeof(user[g_count].name), stdin);
    user[g_count].name[strlen(user[g_count].name) - 1] = '\0';
    printf("나이 : ");
    scanf("%d", &user[g_count].age);
    while (1) {
      printf("이메일주소 : ");
      scanf("%s", user[g_count].email);
      if (is_Email(user[g_count].email))
        break;
    }
    fprintf(fp, "%s / %d / %s /\n", user[g_count].name, user[g_count].age, user[g_count].email);
    g_count++;
    printf("데이터 추가를 계속 (Y/N) : ");
    scanf(" %c",&ch);
    if(ch=='N')
      break;
    printf("\n");
  }
}
void edit_User(User* user, FILE* fp, int _count) {
  char ch = ' ';
  printf("이름 : ");
  scanf(" %[^\n]s", user[_count].name);
  printf("나이 : ");
  scanf(" %d", &user[_count].age);
  while (1) {
    printf("이메일주소 : ");
    scanf(" %s", user[_count].email);
    if (is_Email(user[_count].email))
      break;
  }
  RewriteFile(fp, user);
  printf("수정 완료 되었습니다.\n");
}
void delete_User(User* user, FILE* fp, int _count) {
  for (int i = _count; i < g_count - 1; i++) {
    strcpy(user[i].name, user[i + 1].name);
    user[i].age = user[i + 1].age;
    strcpy(user[i].email, user[i + 1].email);
  }
  g_count--;
  RewriteFile(fp, user);
}
void print_User(User* user) {
  for (int i = 0; i < g_count; i++) {
    printf("%s / %d / %s \n", user[i].name, user[i].age, user[i].email);
  }
}

int main(int argc, char* argv[]) {
  FILE* fp;
  int value, age;
  char ch = ' ';
  char name[255];
  char find_name[255];
  char email[255];
  User user[MAX_VALUE];

  fp = fopen("minidb.txt", "a+t");

  if (fp == NULL) {
    fprintf(stderr, "파일 minidb.txt 을 열 수 없습니다.\n");
    exit(1);
  }
  sync_User(user, fp);

  do {
    printf("\n1. 신규회원 저장\n");
    printf("2. 회원정보 수정\n");
    printf("3. 회원 삭제\n");
    printf("4. 모든 회원 리스트\n");
    printf("5. 종료\n");
    printf("입력하세요> ");
    scanf("%d", &value);

    switch (value)
    {
      case 1:
        add_User(user, fp);
        printf("입력이 완료되었습니다.\n");
        break;
      case 2: 
        printf("수정할 사람 이름을 입력해주세요: ");
        scanf(" %[^\n]s", find_name);
        for (int i = 0; i < g_count; i++) {
          if (!strcmp(user[i].name, find_name)) {
            printf("사용자 %s 을 수정합니다.\n", user[i].name);
            edit_User(user, fp, i);
            break;
          }
          else if (i == g_count - 1)
            printf("사용자 %s 은 없습니다.\n", find_name);
        }
        break;
      case 3: 
        printf("삭제할 사람 이름을 입력해주세요: ");
        scanf(" %[^\n]s", find_name);
        for (int i = 0; i < g_count; i++) {
          if (!strcmp(user[i].name, find_name)) {
            printf("사용자 %s 을 삭제합니다.\n", user[i].name);
            delete_User(user, fp, i);
            break;
          }
          else if (i == g_count - 1)
            printf("사용자 %s 은 없습니다.\n", find_name);
        }
        break;
      case 4: 
        print_User(user);
        break;
      case 5: 
        printf("종료합니다.\n"); 
        break;
      default: printf("올바르지 않은 접근입니다.\n"); break;
    }

  } while (value != 5);	

  fclose(fp);
  return 0;
}
