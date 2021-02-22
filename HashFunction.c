#include <stdio.h>

/*

1. main
C����̺꿡�� text.txt��� �ؽ�Ʈ ���Ͽ��� ������ �ִ� 50�� ���� �޾ƿ� �� �ֵ��� �̸��� num�� �迭�� �����Ѱ� ��� 0���� �ʱ�ȭ ��Ų��.
num�� ��� ������ 0���� �ʱ�ȭ ��Ű�� 0�� ��Ʈ�� ǥ���Ͽ��� �� ��Ʈ�� ��� 0�̱� ������ ���߿� 0���� padding���� �ʾƵ� �ȴ�.
�� �� temp��� ������ ������ �����ϰ� �װ��� �������� �ƴ��� �Ǻ��ϰ� �����̸� arr_size������ ���Ͽ� 
���������� �ؽ�Ʈ ���Ͽ� ������ ������ ����� Ȯ���Ѵ�. �� �� �ٽ� �� ���� ����Ű�� ���� rewind�� ����Ͽ� �� �պ��� �����ϵ��� �Ѵ�.

2. hashfunction
���� ������ 4bytes�̹Ƿ� �� 200bytes�� �����ϱ� ���� 8bytes ��� 25���� �ʿ��ϹǷ� ���� 8 ���� 8 ���̴� 25�� 3�����迭�� �����Ѵ�.
�׸��� �� ���� xor�����Ų�� ������ ��� �迭 result�� �����Ѵ�. ����� ���� ��� xor�� ������ 1���̱� ������ 1���̹Ƿ� ���� �Ű澲�� �ʰ� 2���� �迭�� �����Ѵ�.
������ ������ bit�� ǥ���ϱ� ���� bits��� �迭�� �����Ѵ�. 32bytes�� ������ 50�� �̹Ƿ� ��50 �� 32�� 2���� �迭�� �����Ѵ�.
���� ������ ��Ʈ�� ǥ���ϱ� ���� i�� �����ϰ� 1�� �ʱ�ȭ �� �� 1�� �� ������ ����Ʈ �����ش�. �� �� ������ &������ ����. �� �� &������ 1��1 �̿ܿ��� 0�̹Ƿ�
i�� �� �պ�Ʈ 1�� ������ �������� 0�̶�� ����� �����Ƿ� 1�� �Ű���ָ� �ȴ�. ���� �����ؼ� 0�� �ƴ϶�� i�� �ִ� 1��Ʈ�� ������ 1��Ʈ�� ���ٴ� �� �̹Ƿ� �� �ڸ��� �ִ� ������ ��Ʈ�� 1�̴�. 
�� ���� 1ĭ ����Ʈ����Ʈ�ؼ� �Ȱ��� ������� �����Ͽ� 1���� 0���� �˾Ƴ���.
�̷��� �ؼ� �� �ڸ��� ��Ʈ�� 1���� 0���� �˾� �� �� bits�� �迭�� �ڸ��� �°� �����Ѵ�.
�� �� 32bytes�� ������ 8bytes������ �߶� 8bytes x 8bytes�� �ڸ��� �µ��� �ε����� �Ű�Ἥ block�� �迭�� ����־��ش�.

3.XOR
3���� �迭�� xor���� ���Ѿ� �ϹǷ� �Ű������� ����,��,���� �������ְ� for������ ������ �ݺ��Ͽ� xor������ �ϹǷ� 
�ε��� ������ ������ ���� �ʵ��� 2���� �ε��� ���� �������ش�. �� �� ���η� ������ ��Ű�� ������ ���� 0~7�� �����ǰ� ���̿� ���� �Ű���ָ� �Ǳ� ������ 2���� �޴´�.
hashfunction�Լ����� result�� ���갪�� �����ؾ� �ϹǷ� int������ ��ȯ�����ش�.

4.hashfunction
���� xor ��� ���� int�� ��ȯ��Ű�� result�迭�� ��Ŀ� �°� ��������ش�.
�� �� ���Ͽ� �Է��� �����ش�.



*/

int XOR(int arr[25][8][8], int index1,int index2) { //index1 25 index2 8
	int result = 0;

	result = arr[index1][0][index2] ^ arr[index1][1][index2] ^ arr[index1][2][index2] ^ arr[index1][3][index2] ^ arr[index1][4][index2] ^ arr[index1][5][index2] ^ arr[index1][6][index2] ^ arr[index1][7][index2];

	return result;
}

void HashFunction(int *arr) {

	int block[25][8][8]; // 64bits block 25��
	int result[25][8] = {0, }; // ��� 25��
	int bits[50][32] = {0, }; // 32bits 50�� 0���� padding
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

	printf("================ �޽��� ��������Ʈ ������... ================\n");
	FILE *fp = fopen("c:\\text.txt", "wt");

	for (int i = 0; i < 25; i++) {
		for (int j = 0; j < 8; j++) {
			fprintf(fp, "%d", result[i][j]);
		}
		fprintf(fp, " ");
	}
	printf("================ �޽��� ��������Ʈ ����Ϸ�! ================\n");
	fclose(fp);
}



int main(void) {

	int num[50] = { 0, };
	int len=0;
	int temp = 0;
	int arr_size = 0;

	FILE *fp = fopen("c:\\text.txt", "r");
	if (fp == NULL) {
		printf("������ �������� �ʽ��ϴ�.");
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
		printf("���ڸ� 50�������� �Է��ϼ���.");
		fclose(fp);
	}

}
