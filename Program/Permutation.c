#include<stdio.h>

 int n; 
 int a[100];       
 int no = 0;
 
 int main()
    {
     int i;
     void permu(int array[], int index);//initialize the fuction of permutation

     printf("\nEnter the number of characters: ");
     scanf("%d", &n);  
     printf("Enter the characters you want to permutate: \n");
     for(i=0; i<n; i++)
        {
         printf("No.%d element: ",i+1);
         scanf("%d", &a[i]);
          //printf("a[%d]=%d\n", i,a[i]);
         getchar();
        }

     printf("\nPress any key to get the result...");
     getchar();
     permu(a,0);  //seed of the recursive permutation function
     printf("\n"); 
     return 0;
    }
                                                         
 void permu(int ar[], int k)
   {
    int temp;
    int j;
    if(k == n-1)  //output permutation
      {
       no++;
       printf("\nNo.%dresult: ", no);    
       //getchar();
       for(j=0; j<n; j++) {printf("%d ", a[j]);}		  
       getchar();
      }  
                                                                      	    		            	    
    else
      {
       for(j=k; j<n; j++) 
         {
         temp = a[j]; a[j] = a[k]; a[k] = temp;  
            //interchange ch[j] and ch[k]
         permu(ar,k+1);      
         temp = a[k]; a[k] = a[j]; a[j] = temp;  
         //interchange ch[j] and ch[k] again to return to the orginal situation
            }  //end of for
        }  //end of else

   }  //end of permu
            