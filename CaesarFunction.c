#include <stdio.h>

/*

 
1. main함수에서 2단계에서 사용할 키배열(keys)을 전부 27로 초기화 시킨다. 

그 이유는 함수에는 키와 원문만 들어가야하기 때문이고, 키 범위 밖인 27이 나오면 그 전의 인덱스가 키 값의 길이이기 때문이다.

 

 

2. ke1함수에서 check배열을 이용하여 소문자 대문자 화이트스페이스를 구별한다.

첫번째 for문에서는 각 문자를 구별하는데 배열이 0으로 초기화 되어있으므로 대문자와 화이트 스페이스일 경우만 생각하면 된다.

두번째 for문에서는 먼저 check배열을 바탕으로 start와 end 변수에 대문자 소문자를 구별하여 A와 Z의 아스키 코드값을 넣어준다.

그 후 change라는 변수를 이용하여 원문을 키 값만큼 이동시킨다. 이 때 다음 if문을 이용하여 만약 change가 end인 Z를 넘어가면 다시 A부터 시작해야 하므로

change = change-end+start-1 의 수식을 사용하여 A부터 시작되도록 한다.그 후 아스키 코드를 char형으로 강제형변환시켜 원문 변수에 집어넣는다.

 

만약 switch에서 대문자와 소문자 이외의 문자일경우는 continue를 이용하여 변환시키지 않고 다음 문자로 넘어간다.

 

 

3. ke2함수에서는 len이라는 키값의 길이를 저장하는 변수와 count라는 키 값의 인덱스와 원문의 인덱스를 구별할 변수를 추가로 선언한다.

첫번째 for문을 이용하여 main에서 27로 초기화 시킨 keys변수의 키 값 길이를 알아낸다. 

27은 키 범위 밖의 값 이므로 keys[i]가 27이 나올때까지 for문을 돌리면 27이 나오기 하나 전 인덱스값이 key의 길이이다.

두번째 for문은 ke1과 마찬가지로 대문자 소문자를 구별한 후 키 값 만큼 변환을 시켜준다. 

하지만 이 때 키 값의 길이와 원문의 길이가 다를 수 있기 때문에 키 값이 올바르게 순환할 수 있도록 count라는 변수를 사용한다. 

count변수는 i가 1이 증가할때마다 같이 1씩 증가한다.

처음 if문은 키값의 길이인 len과 count의 개수가 같아졌을 경우 다시 처음 인덱스인 0으로 초기화 시켜준다.

그 후 원문을 키 값으로 변환시킨 후 count++를 하여 1만큼 증가시킨다.

 

만약 인덱스 값이 2인 원문이 대문자 소문자가 아닐 경우는 count를 증가시키면 안되기 때문에 count++를 continue보다 뒤쪽에 작성하였다.

 

 

*/

 

void ke1(char* origin, int key) {

	int check[100] = { 0, }; //소문자 0 대문자 1 화이트스페이스 2
	int change, end, start;

	for (int i = 0; origin[i]; i++) {		
		if (origin[i] == ' ') {
			check[i] = 2;
			continue;
		}

		if (origin[i] >= 'A'&&origin[i] < 'Z') {
			check[i] = 1;
		}		
	}


	for (int i = 0; origin[i]; i++) {
		switch (check[i]) {
		case 0:
			end = 'z';
			start = 'a';
			break;
		case 1:
			end = 'Z';
			start = 'A';
			break;
		default:
			continue;
		} 

		change = (int)origin[i] + key;

		if (change > end) {			
			change = change - end + start - 1;
			origin[i] = (char)change;
		}

		else {
			change = (int)origin[i] + key;
			origin[i] = (char)change;
		}

	}

	printf("Ke1:");

	for (int i = 0; origin[i]; i++)
		printf("%c", origin[i]); 

	printf("\n");

}
 

void ke2(char* origin, int* keys) {

	int check[100] = { 0, }; //소문자 0 대문자 1 화이트스페이스 2
	int change, end, start;
	int len = 0; // key길이
	int count = 0; // 키인덱스 원문인덱스 구별용

	for (int i = 0; keys[i] != 27; i++)
		len++;

	for (int i = 0; origin[i]; i++) {
		if (origin[i] == ' ') {

			check[i] = 2;
			continue;
		}

		if (origin[i] >= 'A'&&origin[i] <= 'Z') {
			check[i] = 1;
		}
	}

	for (int i = 0; origin[i]; i++) {
		if (count == len)
			count = 0;
			
		switch (check[i]) {
		case 0:
			end = 'z';
			start = 'a';
			break;
		case 1:
			end = 'Z';
			start = 'A';
			break;
		default:
			continue;
		}
		change = (int)origin[i] + keys[count];
		if (change > end) {			
			change = change - end + start - 1;
			origin[i] = (char)change;
		}

		else {
			change = (int)origin[i] + keys[count];
			origin[i] = (char)change;
		}
		count++;
	}

	printf("Ke2:");

	for (int i = 0; origin[i]; i++)

		printf("%c", origin[i]);

	printf("\n");

}

 

 

int main() {

	char origin[100];
	int key, num, keys[100], select;

	for (int i = 0; i < 100; i++)
		keys[i] = 27;

	printf("원문입력:");

	do {

		printf("시저 암호(1. 1단계 2. 2단계 0. 종료)");
		printf("입력:");
		scanf("%d", &select);
		getchar();

		if (select == 1) {

			printf("1단계\n");
			printf("원문 입력:");
			gets(origin);
			printf("키값입력(0~25):");
			scanf("%d", &key);
			ke1(origin, key);

		}

		else if (select == 2) {
			
			printf("2단계\n");
			printf("원문 입력:");
			gets(origin);
			printf("몇개의키를입력받겠습니까");
			scanf("%d", &num);
			
			for (int i = 0; i < num; i++)
				scanf("%d", &keys[i]);

			ke2(origin, keys);

		}

		else {

			printf("종료\n");
			break;

		}

	} while (select == 1 || select == 2);

	return 0;

}
