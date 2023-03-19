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
  
  for (i = 1; i <= n; i++) {        // 列印p[i][k]的內容 
    for (k = 0 ; k <= K; k++) {
      printf(" %d ", array[i][k]);
    }
    printf("\n");    
  }
  printf("\n"); 
}

main() {
  int i, j, k;
  int n = 4;                   // 可放入knapsack的物品個數 
  int K = 16, size, total;     // knapsack的容量 
  int S[] = {0, 2, 3, 5, 6};   // 欲放入kanpsack的物品的各別size 
  int profit[] = {0, 3, 5, 4, 2};
  
  int content[5];              // 用來儲存可exactly放入knapsack的subset成員 
  int biggest = 0;                 
  
  int p[5][17];                // p[i][k]=1, there exists a solution to the knapsack
  int p_exist[5][17];          // p_exist[i][k]=1, if the ith element belongs to that solution
  int p_profit[5][17];                // 欲放入kanpsack的物品的各別profit
  int tmp_i;
  int position_i, position_k;
      
  for (i = 0; i <= n; i++) {// 初始化p_profit[i][k]=0, _exist[i][k]=0 
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
  
  for (j = 0; j < k; j++)           // 列印標頭 
    printf(" %d ", j);
  printf("\n");
  
  
  print_array(p, n, K);             // 列印p[i][k]的內容 
  print_array(p_exist, n, K);       // 列印p_exist[i][k]的內容 
  print_array(p_profit, n, K);      // 列印p_profit[i][k]的內容 
   
  printf("The biggest profit: %d\n", biggest);
  
 
  printf("Knapsack content inculdes:\n");
  
  i = 1;
  total = 0;
  size = biggest;                                 
  while(total != biggest) {
    content[i] = S[position_i];              // 根據 p_exist[n][size]找出subset的elements
    total += profit[position_i];
    
    position_k = position_k - S[position_i];
    i++;
    position_i--;
    
    position_i = find_before(p_exist, position_i, position_k);
    
  }
  
  for ( j = 1; j < i; j++) {        // 列印出可放入knapsack的subset的elements 
    printf("content[%d]=%d\n", j, content[j]);
  }
  
  getch();
} // end main

