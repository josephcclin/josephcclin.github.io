/* ACM problem 305: Joseph
 * Author: Joseph, Chuang-Chieh Lin
 * Email address: lincc@cs.ccu.edu.tw; josephcclin@gmail.com
 * Date: April 20, 2010
 * 
 * ACM Problem 100: The 3n+1 problem
 * 
 */

#include <stdio.h>

int simulate(int num); 

int main()
{
	int i = 0,j = 0, t = 0, k = 0, temp = 0, MaxLength = 0; 
	int mark = 0;

	while (scanf("%d%d", &i, &j) == 2) {
		if (i>j) { 
			t = i; 
			i = j; 
			j = t;
			mark = 1;
		}
		for (k=i; k<=j; k++) {
			temp = simulate(k);
			if (temp > MaxLength) MaxLength = temp;
		}
		if (mark == 0) {
			printf("%d %d %d\n", i, j, MaxLength); 
		} else {
                        printf("%d %d %d\n", j, i, MaxLength);
		}
		MaxLength = 0;
		mark = 0;
	}
	return 0;
}

int simulate (int num)
{
	int count = 1;
	while (num != 1) {
		if (num%2) num = 3*num + 1;
		else num = num/2;
		count++;
	}
	return count;
}
