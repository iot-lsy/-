#include <stdio.h>

/*

1. main
C드라이브에서 text.txt라는 텍스트 파일에서 정수를 최대 50개 까지 받아올 수 있도록 이름이 num인 배열을 선언한고 모두 0으로 초기화 시킨다.
num의 모든 값들을 0으로 초기화 시키면 0을 비트로 표현하였을 때 비트가 모두 0이기 때문에 나중에 0으로 padding하지 않아도 된다.
그 후 temp라는 변수에 정수를 저장하고 그것이 정수인지 아닌지 판별하고 정수이면 arr_size변수를 더하여 
최종적으로 텍스트 파일에 정수의 개수가 몇개인지 확인한다. 그 후 다시 맨 앞을 가리키기 위해 rewind를 사용하여 맨 앞부터 저장하도록 한다.

2. hashfunction
먼저 정수는 4bytes이므로 총 200bytes를 저장하기 위해 8bytes 블록 25개가 필요하므로 행은 8 열은 8 높이는 25인 3차원배열을 선언한다.
그리고 각 열을 xor연산시킨뒤 저장할 결과 배열 result를 선언한다. 결과의 행은 모든 xor이 끝나면 1개이기 때문에 1행이므로 행은 신경쓰지 않고 2차원 배열로 선언한다.
각각의 정수를 bit로 표현하기 위해 bits라는 배열을 선언한다. 32bytes의 정수가 50개 이므로 행50 열 32의 2차원 배열을 선언한다.
먼저 정수를 비트로 표현하기 위해 i를 선언하고 1로 초기화 한 뒤 1을 맨 앞으로 쉬프트 시켜준다. 그 후 정수와 &연산을 쓴다. 이 때 &연산은 1과1 이외에는 0이므로
i의 맨 앞비트 1를 제외한 나머지는 0이라는 결과가 나오므로 1만 신경써주면 된다. 만약 연산해서 0이 아니라면 i에 있는 1비트와 정수의 1비트가 같다는 것 이므로 그 자리에 있는 정수의 비트는 1이다. 
그 다음 1칸 라이트쉬프트해서 똑같은 방식으로 연산하여 1인지 0인지 알아낸다.
이렇게 해서 각 자리의 비트가 1인지 0인지 알아 낸 후 bits의 배열에 자리에 맞게 저장한다.
그 후 32bytes의 정수를 8bytes단위로 잘라 8bytes x 8bytes의 자리에 맞도록 인덱스를 신경써서 block의 배열에 집어넣어준다.

3.XOR
3차원 배열을 xor연산 시켜야 하므로 매개변수를 높이,행,렬을 설정해주고 for문에서 여러번 반복하여 xor연산을 하므로 
인덱스 때문에 오류가 나지 않도록 2개의 인덱스 값도 전달해준다. 이 때 세로로 연산을 시키기 때문에 행은 0~7로 고정되고 높이와 열만 신경써주면 되기 때문에 2개를 받는다.
hashfunction함수에서 result에 연산값을 저장해야 하므로 int형으로 반환시켜준다.

4.hashfunction
이후 xor 결과 값을 int로 반환시키고 result배열에 행렬에 맞게 저장시켜준다.
이 후 파일에 입력을 시켜준다.



*/

int XOR(int arr[25][8][8], int index1,int index2) { //index1 25 index2 8
	int result = 0;

	result = arr[index1][0][index2] ^ arr[index1][1][index2] ^ arr[index1][2][index2] ^ arr[index1][3][index2] ^ arr[index1][4][index2] ^ arr[index1][5][index2] ^ arr[index1][6][index2] ^ arr[index1][7][index2];

	return result;
}

void HashFunction(int *arr) {

	int block[25][8][8]; // 64bits block 25개
	int result[25][8] = {0, }; // 결과 25개
	int bits[50][32] = {0, }; // 32bits 50개 0으로 padding
	unsigned int i = 1;
	int len = 0;
	i <<= 31;
	int count1 = 0, count2 = 0;

	for (int j = 0; j < 50; j++) {
		for (int k = 0; k < 32; k++) {
			if ((i & arr[j])!=0) {
				bits[j][k] = 1;
			}
			else {
				bits[j][k] = 0;
			}
			i >>= 1;
		}
		i = 1;
		i <<= 31;
	}

	for (int j = 0; j < 25; j++) {
		for (int k = 0; k < 8; k++) {
			for (int l = 0; l < 8; l++) {
				if (bits[count1][count2] == 1) {
					block[j][k][l] = 1;
				}
				else {
					block[j][k][l] = 0;
				}
				count2++;
			}
			if ((k+1)%4==0) {
				count1++;
				count2 = 0;
			}
		}
	}

	count1 = 0;

	for (int i = 0; i<25; i++) {
		for (int j = 0; j<8; j++) {
			result[i][j] = XOR(block, i, j);
		}
	}

	printf("================ 메시지 다이제스트 저장중... ================\n");
	FILE *fp = fopen("c:\\text.txt", "wt");

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 8; j++) {
			fprintf(fp, "%d", result[i][j]);
		}
		fprintf(fp, " ");
	}
	printf("================ 메시지 다이제스트 저장완료! ================\n");
	fclose(fp);
}



int main(void) {

	int num[50] = { 0, };
	int len=0;
	int temp = 0;
	int arr_size = 0;

	FILE *fp = fopen("c:\\text.txt", "r");
	if (fp == NULL) {
		printf("파일이 존재하지 않습니다.");
		return -1;
	}

	while (1) {
		temp = fscanf(fp, "%d", &temp);
		if (temp == EOF)
			break;
		arr_size++;
	}

	rewind(fp);

	for (int i = 0; i < arr_size; i++) {
		fscanf(fp, "%d", &num[i]);
	}

	if (arr_size <= 50) {
		HashFunction(num);
	}
	else {
		printf("숫자를 50개까지만 입력하세요.");
		fclose(fp);
	}

}
