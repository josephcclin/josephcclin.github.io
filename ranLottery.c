#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

const int Anniversary = 20070512;
const int SherryBirthday = 20110222;
const int JosephBirthday = 19791205;
const int MaggieBirthday = 19800515;
const int JosephID = 121715804;
const int MaggieID = 227120692;
const int SherryID = 224703933;

int repeatTest(int num[], int size);
int printArray(int array[], int size, FILE *fp); 
int compare(const void *a, const void *b); 

int main()
{
    FILE *fp;
	int ball[6] = { 0, 0, 0, 0, 0, 0}; 
	int SEED[7] = { Anniversary, SherryBirthday, JosephBirthday, MaggieBirthday, 
			JosephID, MaggieID, SherryID };
	int i, j;
	int flag = 0;
	
	fp = fopen("LotteryNumbers.txt", "w"); // == NULL) printf("�}�ҰO���ɮɵo�Ϳ��~!\n");
	
    printf("�j�ֳz 49/6 ���X�H�����;�:\n");
    fprintf(fp, "�j�ֳz 49/6 ���X�H�����;�:\n");
    printf("************************************************\n");
    fprintf(fp, "************************************************\n");

	for (j=0; j<7; j++) {
		srand(SEED[j]+(int)time(NULL));
		flag = 0;
		while (flag == 0) {
			for (i=0; i<6; i++) {
				ball[i] = 1 + rand()%49;
			}
			qsort(ball, 6, sizeof(int), compare);
			if (repeatTest(ball, 6) == 1) {
				flag = 0;
			} else 
				flag = 1;
		}
		switch (j) {
               case 0:
                    printf("�ѵ��B���������:\t");
                    fprintf(fp, "�ѵ��B���������:\t");
                    break;
               case 1:
                    printf("�ѫG���ͤ����:\t\t");
                    fprintf(fp, "�ѫG���ͤ����:\t");                    
                    break;
               case 2: 
                    printf("�Ѳ��ǥͤ����:\t\t");
                    fprintf(fp, "�Ѳ��ǥͤ����:\t");
                    break;
               case 3: 
                    printf("�ѲQ�g�ͤ����:\t\t");
                    fprintf(fp, "�ѲQ�g�ͤ����:\t");
                    break;
               case 4: 
                    printf("�Ѳ��Ǩ����Ҹ�����:\t");
                    fprintf(fp, "�Ѳ��Ǩ����Ҹ�����:\t");
                    break;
               case 5: 
                    printf("�ѲQ�g�����Ҹ�����:\t");
                    fprintf(fp, "�ѲQ�g�����Ҹ�����:\t");
                    break;
               case 6: 
                    printf("�ѫG�������Ҹ�����:\t");
                    fprintf(fp, "�ѫG�������Ҹ�����:\t");
                    break;
               defaut:
                    printf("�{�����~!\t");
                    break;
        }
		printArray(ball, 6, fp);
	}
	printf("\n���G�w�g�J LotteryNumbers.txt ��r�ɤ�\n\n");
	system("PAUSE");
	fclose(fp);
	return 0;
}

int repeatTest(int A[], int s)
{
	int i = 0;
	for (i=0; i<s-1; i++) {
		if (A[i] == A[i+1]) return 1;
	}
	return 0;
}

int compare(const void *a, const void *b)
{
	int *aa = (int * )a, *bb = (int * )b;
	if (*aa > *bb) return 1;
	if (*aa == *bb) return 0;
	if (*aa < *bb) return -1;
}

int printArray(int A[], int s, FILE *fp)
{
	int i = 0;
	for (i=0; i<s-1; i++) {
		printf("%4d", A[i]);
		fprintf(fp, "%4d", A[i]);
	}
	printf("%4d\n", A[s-1]);
	fprintf(fp, "%4d\n", A[s-1]);
	return 0;
}
