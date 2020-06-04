#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#pragma pack(push, 1)
typedef struct {
	double x, y;
}Point;

typedef struct arraylist {
	char* id;
	fr_list* link;
}fr_list;

typedef struct Data {
	char id[10];        //  10바이트
	int age;     //  4바이트
	int HP;       //  4바이트
	Point point;    // 16
	fr_list list;
}User;
#pragma pack(pop)

void init_List(fr_list* list) {
	list->id = (char*)malloc(sizeof(char) * 20);
	list->link = NULL;
}

void add_friend(fr_list* head) {
	fr_list* ltmp;

	init_List(ltmp);
	printf("동맹 ID 를 입력하세요 :  ");
	scanf(" %s", ltmp->id);
	head->link = ltmp;
}

void write_User(User* user) {   // 플레이어 정보 기록하는 함수
	User tmp;

	char ch = ' ';  // 데이터 추가 제어 변수
	printf("ID 를 입력하세요 : ");
	scanf(" %s", tmp.id);
	strcpy(user->id, tmp.id);
	printf("나이를 입력하세요 : ");
	scanf(" %d", &tmp.age);
	user->age = tmp.age;
	printf("HP 를 입력하세요 : ");
	scanf(" %d", &tmp.HP);
	user->HP = tmp.HP;
	printf("X 좌표를 입력하세요 : ");
	scanf(" %lf", &tmp.point.x);
	user->point.x = tmp.point.x;
	printf("Y 좌표를 입력하세요 : ");
	scanf(" %lf", &tmp.point.y);
	user->point.y = tmp.point.y;
	while (1) {
		add_friend(&user->list);
		printf("데이터 추가를 계속 (Y/N) : ");
		scanf(" %c", &ch);  // 데이터 추가 제어 N이면 빠져나감
		if (ch == 'N') {
			printf("완료되었습니다.\n");
			break;
		}
	}
	printf("\n");
}

int main() {
	User user;
	FILE* fp = fopen("test1.bin", "wb");

	memset(&user, 0, sizeof(user));

	write_User(&user);

	fwrite(&user, sizeof(user), 1, fp);

	fclose(fp);
	return 0;
}
