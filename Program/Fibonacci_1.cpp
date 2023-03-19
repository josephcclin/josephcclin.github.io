#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
 {
   time_t start = time(NULL);
   long first = 0, result = 1, n, temp;
   printf("\n¢i This program is nonrecursive version:\n\n");
   printf("---------------------start-------------------------");
   printf("\nEnter the position of Fibonacci number: ");
   scanf("%d", &n);
   if (n<0) { printf("\nError!!\n"); exit(0);}
    else if (n==1) { result=0; }
     else if (n==2) { result=1; }
      else{ 
           int f=n;
	   while( f>2 )
		{
	    	  temp = first;
                  first = result;
	          result = temp + result;
	          f--;
	        } 
	  }
   printf("\nThe %dth Fibonacci number is %d\n",n,result);
   time_t end = time(NULL);
   printf("The executing time is %f seconds.\n",difftime(end, start));
   printf("---------------------end---------------------------\n\n");
   return 0;
 }
