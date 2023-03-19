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
	
	fp = fopen("LotteryNumbers.txt", "w"); // == NULL) printf("開啟記錄檔時發生錯誤!\n");
	
    printf("大樂透 49/6 號碼隨機產生器:\n");
    fprintf(fp, "大樂透 49/6 號碼隨機產生器:\n");
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
                    printf("由結婚紀念日推算:\t");
                    fprintf(fp, "由結婚紀念日推算:\t");
                    break;
               case 1:
                    printf("由亮予生日推算:\t\t");
                    fprintf(fp, "由亮予生日推算:\t");                    
                    break;
               case 2: 
                    printf("由莊傑生日推算:\t\t");
                    fprintf(fp, "由莊傑生日推算:\t");
                    break;
               case 3: 
                    printf("由淑君生日推算:\t\t");
                    fprintf(fp, "由淑君生日推算:\t");
                    break;
               case 4: 
                    printf("由莊傑身分證號推算:\t");
                    fprintf(fp, "由莊傑身分證號推算:\t");
                    break;
               case 5: 
                    printf("由淑君身分證號推算:\t");
                    fprintf(fp, "由淑君身分證號推算:\t");
                    break;
               case 6: 
                    printf("由亮予身分證號推算:\t");
                    fprintf(fp, "由亮予身分證號推算:\t");
                    break;
               defaut:
                    printf("程式錯誤!\t");
                    break;
        }
		printArray(ball, 6, fp);
	}
	printf("\n結果已寫入 LotteryNumbers.txt 文字檔中\n\n");
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
