#include <stdio.h>


                                     
int find_before(int array[][17], int n, int size) {
  int i;
  for(i = n; i > 0; i--) {
    if(array[i][size]) {
      return i;
    }
  }
  return 0;
}

void print_array(int array[][17], int n, int K) {
  int i, k;
  
  for (i = 1; i <= n; i++) {        // �C�Lp[i][k]�����e 
    for (k = 0 ; k <= K; k++) {
      printf(" %d ", array[i][k]);
    }
    printf("\n");    
  }
  printf("\n"); 
}

main() {
  int i, j, k;
  int n = 4;                   // �i��Jknapsack�����~�Ӽ� 
  int K = 16, size, total;     // knapsack���e�q 
  int S[] = {0, 2, 3, 5, 6};   // ����Jkanpsack�����~���U�Osize 
  int profit[] = {0, 3, 5, 4, 2};
  
  int content[5];              // �Ψ��x�s�iexactly��Jknapsack��subset���� 
  int biggest = 0;                 
  
  int p[5][17];                // p[i][k]=1, there exists a solution to the knapsack
  int p_exist[5][17];          // p_exist[i][k]=1, if the ith element belongs to that solution
  int p_profit[5][17];                // ����Jkanpsack�����~���U�Oprofit
  int tmp_i;
  int position_i, position_k;
      
  for (i = 0; i <= n; i++) {// ��l��p_profit[i][k]=0, _exist[i][k]=0 
    for (k = 0 ; k <= K; k++) {
      p[i][k] = 0;
      p_exist[i][k] = 0;
      p_profit[i][k] = 0; 
    }
  }  // end for i  
  p[0][0] = 1;             // p[0][0]=0, trivial
  
  for (i = 1; i <= n; i++) {
    for (k = 0; k <= K; k++) {
      if (p[i-1][k]) {
        p[i][k] = 1;
      } else if (k -S[i] >= 0) {
        if (p[i-1][k-S[i]]) {
          p[i][k] = 1;
          p_exist[i][k] = 1;
          
          tmp_i = find_before(p_profit, i - 1, k - S[i]);
          p_profit[i][k] = profit[i] + p_profit[tmp_i][k - S[i]];
          
          if (p_profit[i][k] > biggest) {
            biggest = p_profit[i][k];
            position_i = i;
            position_k = k;         
          }
        }
      } // end if p[i-1][k]
    }   // end for k
  }     // end for i
  
  for (j = 0; j < k; j++)           // �C�L���Y 
    printf(" %d ", j);
  printf("\n");
  
  
  print_array(p, n, K);             // �C�Lp[i][k]�����e 
  print_array(p_exist, n, K);       // �C�Lp_exist[i][k]�����e 
  print_array(p_profit, n, K);      // �C�Lp_profit[i][k]�����e 
   
  printf("The biggest profit: %d\n", biggest);
  
 
  printf("Knapsack content inculdes:\n");
  
  i = 1;
  total = 0;
  size = biggest;                                 
  while(total != biggest) {
    content[i] = S[position_i];              // �ھ� p_exist[n][size]��Xsubset��elements
    total += profit[position_i];
    
    position_k = position_k - S[position_i];
    i++;
    position_i--;
    
    position_i = find_before(p_exist, position_i, position_k);
    
  }
  
  for ( j = 1; j < i; j++) {        // �C�L�X�i��Jknapsack��subset��elements 
    printf("content[%d]=%d\n", j, content[j]);
  }
  
  getch();
} // end main

