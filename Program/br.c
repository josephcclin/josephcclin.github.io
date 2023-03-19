/* 
 * NAME: 
 *	br - calculating branching numbers 
 *
 * SYNOPSIS: 
 * 	br NUM_1 NUM_2 ...
 *
 * Compiling instruction: 
 *	gcc br.c -lm -o br
 *
 * Author: 
 *	Joseph, Chuang-Chieh Lin
 *
 * Email: 
 * 	lincc@cs.ccu.edu.tw or josephcclin@gmail.com
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//calculating the value of a characteristic polynomial
double CH_POLY(int *array, double variable, int array_size); 
//calculating the  branching numbers 
double BranchNumber(int *array, int arry_size);

#define PRECISION 8

int main(int argc, char **argv)
{
	
	int *bv;
	int i = 0;
	if (argc == 1) {
		printf("Error!\n");
		return 1;
	}	
	bv = (int *)malloc(sizeof(int)*argc);
	for (i=0; i<argc-1; i++) {
		*(bv+i) = atoi(*(argv+i+1));
	}
	printf("%1.8f\n",BranchNumber(bv,argc-1));
	free(bv);
	return 0;
}

double CH_POLY(int *A, double var, int n)
{
       	int i = 0; 
	double s = 0;
      	for (i=0; i<n; i++) {
		s += pow(var,*(A+i));
       	}
       	return 1-s; 
}

double BranchNumber(int *BV, int n)
{
      int d = 0; 
      double temp = 0;
      double poly_result = 1;
      for (d=1; d<=PRECISION; d++) { 
          poly_result = 1;
          while (poly_result > 0) {
                temp += pow(0.1, d);
                poly_result = CH_POLY(BV, temp, n);
          } 
          temp -= pow(0.1, d);
      }
      return (1/temp);
}

