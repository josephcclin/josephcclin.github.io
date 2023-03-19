#include<stdio.h>

int max(int x, int y, int z) //find out the maximum value without negative value
{
	int t;
	if(x >= y)
	{
		t = x;
	}
	else
	{
		t = y;
	}
	if(z >= t)
	{
		t = z;
	}
	if (0 >= t)
	{
		t = 0;
	}
	return t;
}

int local_alignment(int a[], int n1, int b[], int n2) //begin to implement local alignment
{
	int i, j, temp1, temp2, temp3, s=0; //"s" represents the score of local alignment		
	int align[1300][1300];

	for(i=0; i<=n1; i++)
	{
		for(j=0; j<=n2; j++)
		{
		     align[i][j] = 0;
		}
	}	
	for(i=1; i<=n1; i++)
	{
		for(j=1; j<=n2; j++)
		{		
			if(a[i]==b[j])
			{
				temp1 = align[i-1][j-1] + 5;
			}	
			else
			{
				temp1 = align[i-1][j-1] - 2;
			}
			temp2 = align[i-1][j] - 1;
			temp3 = align[i][j-1] - 1;
			align[i][j] = max(temp1, temp2, temp3);
			if(align[i][j] > s) {s = align[i][j];} 
		}
	}		  
	return s;
}

int vicemain(char fptr1[], char fptr2[])
{
	FILE *fp1, *fp2;
	int seq1[1300], seq2[1300];
	int i, j, num1 = 0, num2 = 0, num, score;
	float percent;
	
	for(i=0; i<1300; i++)
	{
		seq1[i] = 9999;//initialize seq1
		seq2[i] = 9999;//initialize seq2
	}

// **************** Now we put 1st file to array seq1 ***************

	if ((fp1 = fopen(fptr1,"r")) == NULL) 
	{
		printf("\nError occurs while reading 1st file...\n");
		printf("\nTerminating this program...\n\n");
		getchar();
		exit(0);
	}
    else
	{
		i=1;
		while(!feof(fp1))
		{
			fscanf(fp1,"%d\t",&seq1[i]);
			i++;
			num1++;
		}
	}

// **************** Now we put 2nd file to array seq2 ****************

	if ((fp2 = fopen(fptr2,"r")) == NULL) 
	{
		printf("\nError occurs while reading 2nd file...\n");
		printf("\nTerminating this program...\n\n"); 
		getchar();
		exit(0);
	}
    else
	{
		j=1;
		while(!feof(fp2))
		{
			fscanf(fp2,"%d\t",&seq2[j]);
			j++;
			num2++;
		}
	}	

	printf("\nThe number of tokens in file1 is %d", num1);
	printf("\nThe number of tokens in file2 is %d", num2);
	if (num1 > num2) {num = num2;}
	else {num = num1;}
	
	score = local_alignment(seq1, num1, seq2, num2); //start local alignment!
	percent = (float)score/(float)(5*num);
	printf("\nThe original score: %d", score);
	printf("\nThe score of local alignment on these two files is: %2.2f percent\n", percent*100);

	if (percent >= 0.75) 
		printf("\nThese two files are quite similar!!.\n\n");
	else if (percent >= 0.5)
		printf("\nTwo files might be similar.\n\n");
	else	
		printf("\nThese two files should be independent.\n\n");
		
        fclose(fp1);
        fclose(fp2);                
	return 0;	
}

int main()
{
	char c1, c2, ch1, ch2;
	char file1[30], file2[30];
	printf("\n***************************************************");
	printf("\n*                                                 *");
	printf("\n* This the final project of Computational Biology *");
	printf("\n*                                                 *"); 
	printf("\n* Author     : Chuang-Chieh Lin                   *");
	printf("\n* Student ID : 91321501                           *");
	printf("\n*                                                 *");
	printf("\n***************************************************\n");
	
	do
	{
		printf("\nPlease input 1st file: ");
		scanf("%s%c", &file1, &c1);
		printf("Please input 2nd file: ");
		scanf("%s%c", &file2, &c2);
		printf("\nPress any key to continue...");
		getchar();
		vicemain(file1, file2); 
		printf("\nWill you do it again? (Y/n): ");
		scanf("%c%c", &ch1, &ch2);
	} 
	while(ch1 != 'n');	
	printf("\nThanks for your using and testing, goodbye.\n\n");
	return 0;
} 
