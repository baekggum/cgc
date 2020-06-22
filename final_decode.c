#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <ctype.h>
#define MAX_VALUE 700

int n = 0;
int g_n=0;
char bufr[20000], bufw[20000], buffer[20000];

typedef struct description1 {
  char data[MAX_VALUE];
}Description;

void return_Error(int g_n) {
  switch (g_n) {
    case 1:
      printf("*USER STATUS*\n");
      break;
    case 2:
      printf("*ITEMS*\n");
      break;
    case 3:
      printf("*FRIENDS LIST*\n");
      break;
    case 4:
      printf("*DESCRIPTION*\n");
      break;
  }
}

void decode(FILE* fq)
{
  FILE* fp = NULL;
  int l = 0;
  fp = fopen("result1.txt", "r");
  if (fp == NULL) {
    fprintf(stderr, "파일을  열수 없습니다.\n");
    exit(1);
  }

  while (l < n-1) {
    fgets(buffer, sizeof(buffer), fp);
    fputs(buffer, fq);
    l++;
  }
  fclose(fp);

}
void is_Right(Description* des, FILE* fp, int i) {
  int idx = 0;
  char* c;
  char data[MAX_VALUE] = { 0, }, data2[MAX_VALUE] = { 0, }, data3[MAX_VALUE] = { 0, };
  char* ptr = strtok(des[i].data, ":");
  if (des[i].data == "\0");
  strcpy(data, ptr);
  idx += (strlen(data));
  ptr = strtok(NULL, ":");
  strcpy(data2, ptr);
  idx += (strlen(data2));
  ptr = strtok(NULL, ":");
  ptr = strtok(ptr, "\n");
  strcpy(data3, ptr);
  ptr = strtok(NULL, " ");
  if ((strcmp(data, "/1") == 0) || (strcmp(data2, "/1") == 0) || (strcmp(data3, "/1") == 0))
    g_n = 1;
  else if ((strcmp(data, "/2") == 0) || (strcmp(data2, "/2") == 0) || (strcmp(data3, "/2") == 0))
    g_n = 2;
  else if ((strcmp(data, "/3") == 0) || (strcmp(data2, "/3") == 0) || (strcmp(data3, "/3") == 0))
    g_n = 3;
  else if ((strcmp(data, "/4") == 0) || (strcmp(data2, "/4") == 0) || (strcmp(data3, "/4") == 0))
    g_n = 4;
  int n = strlen(data);
  if (strcmp(data, data2) == 0) {
    if (strcmp(data, data3) == 0) {
      strcpy(des[i].data, data);
      return;
    }
    else {
      for (int p = 0; p < strlen(data); p++) {
        if (*(data + p) != *(data3 + p)) {
          printf("%c %c\n", *(data3 + p), *(data + p));
          strcpy(des[i].data, data);
          continue;
        }
      }
      return_Error(g_n);
    }
  }
  else {
    if (strcmp(data, data3) == 0) {
      for (int p = 0; p < strlen(data); p++) {
        if (*(data + p) != *(data2 + p)) {
          printf("%c %c\n", *(data2 + p), *(data + p));
          strcpy(des[i].data, data);
          continue;
        }
      }
      return_Error(g_n);
    }
    else if (strcmp(data2, data3) == 0) {
      for (int p = 0; p < strlen(data2); p++) {
        if (*(data + p) != *(data2 + p)) {
          printf("%c %c\n", *(data + p), *(data2 + p));
          strcpy(des[i].data, data2);
          continue;
        }
      }
      return_Error(g_n);
    }
    else {
      for (int i = 0; i < n; i++) {
        if (*(data + i) == *(data2 + i)) {
          if (*(data2 + i) == *(data3 + i))
            continue;
          printf("%c %c\n", *(data3 + i), *(data + i));
          *(data3 + i) = *(data + i);
        }
        else {
          if (*(data + i) == *(data3 + i)) {
            printf("%c %c\n", *(data2 + i), *(data + i));
            *(data2 + i) = *(data + i);
          }
          else {
            printf("%c %c\n", *(data + i), *(data2 + i));
            *(data + i) = *(data2 + i);
          }
        }
      }
      return_Error(g_n);
    }
  }
}
void decode_Data(Description* des, FILE* fp, FILE* fp1) {
  int r = 0, u = 0, h = 0;
  while (1) {
    char strTemp[MAX_VALUE];
    fgets(strTemp, sizeof(strTemp), fp);
    char* ptr = strtok(strTemp, "\0");
    strcpy(des[h].data, ptr);
    if (feof(fp)) break;
    h++;
    ptr = strtok(NULL, " ");
  }
  while (r <= h) {
    is_Right(des, fp, r);
    fprintf(fp1, "%s", des[r].data);

    r++;
    if (r <= h)
      fprintf(fp1, "\n");
  }
}

void add(FILE* fq) {
  FILE* fp = NULL;
  int k = 0;
  fp = fopen("copy.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "파일을  열수 없습니다.\n");
    exit(1);
  }
  while (k < n) {
    fgets(buffer, sizeof(buffer), fq);
    fputs(buffer, fp);
    k++;
  }
  fclose(fp);
}
void change(char x[], char y[])
{
  FILE *fp = NULL;
  FILE *fp2 = NULL;
  char* rp, * wp, * p;
  int i = 0, j = 0;
  fp = fopen("result1.txt", "r");
  if (fp == NULL) {
    fprintf(stderr, "파일을 열수 없습니다.\n");
    exit(1);
  }
  fp2 = fopen("cpfriend.txt", "w");
  if (fp2 == NULL) {
    fprintf(stderr, "파일을 열수 없습니다.\n");
    exit(1);
  }
  while (i < n-1) {
    fgets(bufr, sizeof(bufr), fp);
    rp = bufr;
    wp = bufw;
    while (*rp) {
      p = strstr(rp, x);
      if (!p) {
        strcpy(wp, rp);
        fprintf(fp2, "%s", bufw);
        break;
      }
      *p = 0;
      strcpy(wp, rp);
      wp += (p - rp);
      rp = p + strlen(x);
      strcpy(wp, y);
      wp += strlen(y);
    }
    i++;
  }
  fclose(fp);
  fclose(fp2);
  fp = fopen("result1.txt", "w");
  if (fp == NULL) {
    fprintf(stderr, "파일을  열수 없습니다.\n");
    exit(1);
  }
  fp2 = fopen("cpfriend.txt", "r");
  if (fp2 == NULL) {
    fprintf(stderr, "파일을 열수 없습니다.\n");
    exit(1);
  }
  while (j < n-1) {
    fgets(buffer, sizeof(buffer), fp2);
    fputs(buffer, fp);
    j++;
  }
  fclose(fp);
  fclose(fp2);
}

int main(int argc, char* argv[])
{
  FILE* fp = NULL;
  FILE* fp2 = NULL;
  FILE* fq = NULL;
  FILE* fq2 = NULL;
  FILE* fr = NULL;
  char friend_1[] = "FRIEND", friend_2[] = "`";
  char id_1[] = "ID: ", id_2[] = "~";
  char name_1[] = "NAME: ", name_2[] = "!";
  char gender_1[] = "GENDER: ", gender_2[] = "@";
  char age_1[] = "AGE: ", age_2[] = "#";
  char hp_1[] = "HP: ", hp_2[] = "$";
  char mp_1[] = "MP: ", mp_2[] = "%";
  char coin_1[] = "COIN: ", coin_2[] = "^";
  char bomb_1[] = "BOMB: ", bomb_2[] = "&";
  char potion_1[] = "POTION: ", potion_2[] = "<";
  char cure_1[] = "CURE: ", cure_2[] = ")";
  char shield_1[] = "SHIELD: ", shield_2[] = "[";
  char cannon_1[] = "CANNON: ", cannon_2[] = "]";
  char book_1[] = "BOOK: ", book_2[] = "(";
  char female_1[] = "FEMALE", female_2[] = "-";
  char male_1[] = "MALE", male_2[] = "+";
  char se1[] = "/1", se2[] = "/2", se3[] = "/3", se4[] = "/4";
  char stat[] = "*USER STATUS*";
  char item[] = "*ITEMS*";
  char list[] = "*FRIENDS LIST*";
  char desc[] = "*DESCRIPTION*";
  Description des[MAX_VALUE] = { 0, };
  fq = fopen(argv[1], "r");    //argv[1]
  if (fq == NULL) { exit(1); }
  while (1) {
    fgets(buffer, sizeof(buffer), fq);
    n++;
    if (feof(fq)){     
      fgets(buffer, sizeof(buffer), fq);
      break;
    }
  }
  fclose(fq);
  fq = fopen(argv[1], "r");    //argv[1]
  if (fq == NULL) { exit(1); }
  add(fq);
  fclose(fq);

  fq2 = fopen("result1.txt", "w");
  if (fq2 == NULL) { exit(1); }

  fr = fopen("copy.txt", "r");
  if (fr == NULL) { exit(1); }
  decode_Data(des, fr, fq2);
  fclose(fr);
  fclose(fq2);
  change(se2, item);
  change(se3, list);
  change(se4, desc);
  change(se1, stat);
  change(age_2, age_1);
  change(friend_2, friend_1);
  change(name_2, name_1);
  change(gender_2, gender_1);
  change(id_2, id_1);
  change(coin_2, coin_1);
  change(hp_2, hp_1);
  change(mp_2, mp_1);
  change(bomb_2, bomb_1);
  change(potion_2, potion_1);
  change(cure_2, cure_1);
  change(book_2, book_1);
  change(shield_2, shield_1);
  change(cannon_2, cannon_1);
  change(female_2, female_1);
  change(male_2, male_1);

  fp = fopen(argv[2], "w");      //argv[2]
  if (fp == NULL) { exit(1); }
  decode(fp);
  fclose(fp);
  return 0;
}
