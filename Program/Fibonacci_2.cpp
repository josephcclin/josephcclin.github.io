#include<stdio.h>
#include<time.h>
#include<stdlib.h>

int main()
  {    
    time_t start = time(NULL);
    int n=0;
    long result;
    long Fib(int);
    printf("\n¢i This program is recursive version:\n\n");
    printf("-----------------start-------------------------");
    printf("\nEnter the order of Fibonacci nember: ");
    scanf("%d",&n);
   
    if (n<1) {printf("\nInput is error!\n"); exit(0); }
       else result=Fib(n);
   
    printf("\nThe %dth Fibonacci number is %d\n",n,result);
    time_t end = time(NULL);
    printf("The executing time is %f seconds.",difftime(end, start));
    printf("\n-----------------end---------------------------\n\n"); 
    return 0;
  }

long Fib(int num)
     {
       if (num==1) return 0;
    	   else if (num==2) return 1;
	       else return (Fib(num-1)+Fib(num-2));
     }