#include <stdio.h>

/*

201721188 ����Ʈ������Ű��а� �̼ҿ�

������ : 2018. 3. 24

 

1. main�Լ����� 2�ܰ迡�� ����� Ű�迭(keys)�� ���� 27�� �ʱ�ȭ ��Ų��. 

�� ������ �Լ����� Ű�� ������ �����ϱ� �����̰�, Ű ���� ���� 27�� ������ �� ���� �ε����� Ű ���� �����̱� �����̴�.

 

 

2. ke1�Լ����� check�迭�� �̿��Ͽ� �ҹ��� �빮�� ȭ��Ʈ�����̽��� �����Ѵ�.

ù��° for�������� �� ���ڸ� �����ϴµ� �迭�� 0���� �ʱ�ȭ �Ǿ������Ƿ� �빮�ڿ� ȭ��Ʈ �����̽��� ��츸 �����ϸ� �ȴ�.

�ι�° for�������� ���� check�迭�� �������� start�� end ������ �빮�� �ҹ��ڸ� �����Ͽ� A�� Z�� �ƽ�Ű �ڵ尪�� �־��ش�.

�� �� change��� ������ �̿��Ͽ� ������ Ű ����ŭ �̵���Ų��. �� �� ���� if���� �̿��Ͽ� ���� change�� end�� Z�� �Ѿ�� �ٽ� A���� �����ؾ� �ϹǷ�

change = change-end+start-1 �� ������ ����Ͽ� A���� ���۵ǵ��� �Ѵ�.�� �� �ƽ�Ű �ڵ带 char������ ��������ȯ���� ���� ������ ����ִ´�.

 

���� switch���� �빮�ڿ� �ҹ��� �̿��� �����ϰ��� continue�� �̿��Ͽ� ��ȯ��Ű�� �ʰ� ���� ���ڷ� �Ѿ��.

 

 

3. ke2�Լ������� len�̶�� Ű���� ���̸� �����ϴ� ������ count��� Ű ���� �ε����� ������ �ε����� ������ ������ �߰��� �����Ѵ�.

ù��° for���� �̿��Ͽ� main���� 27�� �ʱ�ȭ ��Ų keys������ Ű �� ���̸� �˾Ƴ���. 

27�� Ű ���� ���� �� �̹Ƿ� keys[i]�� 27�� ���ö����� for���� ������ 27�� ������ �ϳ� �� �ε������� key�� �����̴�.

�ι�° for���� ke1�� ���������� �빮�� �ҹ��ڸ� ������ �� Ű �� ��ŭ ��ȯ�� �����ش�. 

������ �� �� Ű ���� ���̿� ������ ���̰� �ٸ� �� �ֱ� ������ Ű ���� �ùٸ��� ��ȯ�� �� �ֵ��� count��� ������ ����Ѵ�. 

count������ i�� 1�� �����Ҷ����� ���� 1�� �����Ѵ�.

ó�� if���� Ű���� ������ len�� count�� ������ �������� ��� �ٽ� ó�� �ε����� 0���� �ʱ�ȭ �����ش�.

�� �� ������ Ű ������ ��ȯ��Ų �� count++�� �Ͽ� 1��ŭ ������Ų��.

 

���� �ε��� ���� 2�� ������ �빮�� �ҹ��ڰ� �ƴ� ���� count�� ������Ű�� �ȵǱ� ������ count++�� continue���� ���ʿ� �ۼ��Ͽ���.

 

 

*/

 

void ke1(char* origin, int key) {

	int check[100] = { 0, }; //�ҹ��� 0 �빮�� 1 ȭ��Ʈ�����̽� 2
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

	int check[100] = { 0, }; //�ҹ��� 0 �빮�� 1 ȭ��Ʈ�����̽� 2
	int change, end, start;
	int len = 0; // key����
	int count = 0; // Ű�ε��� �����ε��� ������

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

	printf("�����Է�:");

	do {

		printf("���� ��ȣ(1. 1�ܰ� 2. 2�ܰ� 0. ����)");
		printf("�Է�:");
		scanf("%d", &select);
		getchar();

		if (select == 1) {

			printf("1�ܰ�\n");
			printf("���� �Է�:");
			gets(origin);
			printf("Ű���Է�(0~25):");
			scanf("%d", &key);
			ke1(origin, key);

		}

		else if (select == 2) {
			
			printf("2�ܰ�\n");
			printf("���� �Է�:");
			gets(origin);
			printf("���Ű���Է¹ްڽ��ϱ�");
			scanf("%d", &num);
			
			for (int i = 0; i < num; i++)
				scanf("%d", &keys[i]);

			ke2(origin, keys);

		}

		else {

			printf("����\n");
			break;

		}

	} while (select == 1 || select == 2);

	return 0;

}
