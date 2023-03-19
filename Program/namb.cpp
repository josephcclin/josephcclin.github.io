#include <stdio.h>
#include <stdlib.h>
#include <iostream.h>
#include <time.h>

int pt, pu, pm, A, B;

int input[4]; // input sequence
int target[4]; // target sequence

int main()
{
   	int i, opt;
	void generate(void); 
   	void getin(void); 
	void show_matrix(int martix[], int n);
	int match(int mat1[], int mat2[], int, int);
    
	system("cls");
	generate(); // generate computers's number
	do {
		getin(); // get input
		opt = match(input, target, 4, 4); 
	} while (opt == 0);
   	cout << endl;
   	return 0;    
}

void generate()
{
    int i, j, num, again;
    int check(int mat[]);
    
    srand((unsigned)time(NULL));
    
    do {
        target[0] = rand()%10;
        target[1] = rand()%10;
        target[2] = rand()%10;
        target[3] = rand()%10;
    } while (check(target));
}

int check(int matrix[])
{
	int i, j;
	for (i=0; i<4; i++) {
		for (j=i+1; j<4; j++) {
			if (matrix[i] == matrix[j]) {
				return 1; 
			}
                }
    	}
	return 0;
}

void getin()
{
	int n;
	int check(int m[]);
	
	cout << "Please input your sequece: ";
	cin >> n;
	
	input[0] = (int)(n/1000);
	input[1] = (int)((n-1000*input[0])/100);
	input[2] = (int)((n-1000*input[0]-100*input[1])/10);
	input[3] = (int)((n-1000*input[0]-100*input[1]-10*input[2])); 
	if (check(input)) {
		cout << "\nPlease don't input repeated numbers." 
			<< " \nEnter the sequence again! <Click any key to continue.>"; 
		getchar();
		getchar();
		system("cls");
		getin();
	}
}

int match(int m1[], int m2[], int n1, int n2)
{
	int a = 0, b = 0;
	int i, j;
	int com[n1][n2];

	int compare(int c1, int c2);

	for (i=0; i<n1; i++) 
	{
		for (j=0; j<n2; j++) 
		{
			com[i][j] = compare(m1[i], m2[j]);
			if (com[i][j]==1) {
				if (i==j) 
					a++; 
				else
					b++; 
			} 
		} 
	}
	cout << "=>" << a << "A" << b << "B" << endl;
	if (a == 4) {
		return 1;
		cout << "\nYou win!";
	}
	else 
		return 0;
	getchar();
}

int compare(int c1, int c2)
{ 
	if (c1 == c2) 
		return 1;
	else
		return 0;
}
