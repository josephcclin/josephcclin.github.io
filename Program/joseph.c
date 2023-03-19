/* ACM problem 305: Joseph 
 * Author: Joseph, Chuang-Chieh Lin
 * Email address: lincc@cs.ccu.edu.tw; josephcclin@gmail.com
 * Date: April 19, 2010
 * 
 * Problem description: 
 * 
 * The Joseph's problem is notoriously known. 
 * For those who are not familiar with the original problem: from
 * among n people, numbered 1, 2, ..., n, standing in circle every mth
 * is going to be executed and only the life of the last remaining
 * person will be saved. Joseph was smart enough to choose the
 * position of the last remaining person, thus saving his life to give
 * us the message about the incident. For example when n = 6 and m = 5
 * then the people will be executed in the order 5, 4, 6, 2, 3 and 1
 * will be saved. Suppose that there are k good guys and k bad guys.
 * In the circle the first k are good guys and the last k bad guys.
 * You have to determine such minimal m that all the bad guys will be
 * executed before the first good guy. 
 *
 * Input: 
 *
 * The input file consists of separate lines containing k. The last
 * line in the input file contains 0. You can suppose that 0 < k < 14. 
 *
 * Output: 
 *
 * The output file will consist of separate lines containing m
 * corresponding to k in the input file. 
 *
 * */

#include <stdio.h>

int check(int array[], int size, long rotate); 	
// Checking if good people survive for the input k and the number m,
// where `size' stands for the number 2*k and `rotate' stands for the
// number m.

int initialize(int array[], int size);
// This subroutine initialize the input sequence of people to be 
// 1, 2, ..., k, k+1, ..., 2k.

long table[14]; 
// This table is used for storing the obtained answers. 

int main()
{
	int k, i;
	long m, j;
        int flag = 0;	
	int joseph[28];
	for (i=0; i<14; i++) { // initializing the table 
		table[i] = 0;
	}
        
	// The program ends when the last line of the input contains 0.
	// We only check m in the range k+1 <= m%2k <= 2k since
	// m % 2k < k+1 implies that a good person is killed during
	// the first round
	while (scanf("%d", &k)==1 && (k!=0)) { 
		if (table[k] != 0) printf("%d\n", table[k]); 
		else { 
			for (i=0; ; i+=2) {
				for (j=(i+1)*k+1; j<=(i+2)*k; j++) { 
					initialize(joseph, 2*k);
					if (check(joseph, 2*k, j) == 0) { 
						continue; // a good person is killed
					} else { // the minimum m is found
						m = j;
						flag = 1;
						break;
					}
				}
				if (flag == 1) break;
			}
			printf("%d\n", m);
			table[k] = m;
			flag = 0;
		}
	}
	return 0;
}

int initialize(int array[], int size) 
{
	int i = 0; 
	for (i=0; i<size; i++) 
		array[i] = i+1;
	
	return 0;
}

int check(int josef[], int size, long rotate)
{
	int i = 0, j = 0, index = 0; 
	int result[28]; 
	int temp_size = size;

	while (1) { 
		index = (index + rotate-1)%temp_size;
		result[i] = josef[index];// The killed person in the (i+1)th round

		if (index != temp_size-1) {
                	for (j=index; j<temp_size-1; j++) {
                        	josef[j] = josef[j+1];
                	}
			josef[temp_size-1] = 0;
			// Move the people after the killed person one
			// position forward.
		}
		
		if (i<size/2 && result[i]<=size/2) { // A good person is killed too early
			return 0;
		} else if (i>=size/2-1) { // No good people are killed too early. 
			return 1;
		} else {
			i++;
			temp_size--; 
		}
	}
}
