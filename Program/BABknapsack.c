#include<stdio.h>
#include<stdlib.h>

#include<time.h>

int n = 25, wl = 0, minubd = 0, final_profit = 0, kind;
int mark[1000];
int final_mark[1000];
int prof[1000];
int w[1000];
float pw[1000];
long nodecount; //total nodes
long solcount; //solution nodes


int ceil(double number) {
   int temp;
   temp = number + 1;
   return temp;
}

void randomdata()
   {
    int i;
    srand( (unsigned)time( NULL ) );
    for(i=1; i<=n; i++)
       {
	      prof[i] = rand() % 100;
        do
          {
	         w[i] = rand() % 100;
          }while (w[i] == 0);
          pw[i] = (float)prof[i]/(float)w[i];
       }
    for(i=1; i<=n; i++)
       {
        wl += w[i];
       }  
    wl = wl / 2;   
   }     
void change(int *a, int *b)
   {
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
   }

void fchange(float *a, float *b)
   {
    float temp;
    temp = *a;
    *a = *b;
    *b = temp;
   }

void shitsort()
   {
    int i, j, t;
    float tf;
    for(i = 1; i <= n; i++)
       {
        for(j = n; j > i; j--)
          {
           if(pw[j] > pw[j-1])
             {
              fchange(pw+j,pw+j-1);
              change(prof+j,prof+j-1);
              change(w+j,w+j-1);
             }
          }   
       }
   }

int lbd_1(int x, int wl, int p) //Method in Textbook
    {
     int i;
     for(i=x+1; i<=n; i++)
       {
        if (wl < w[i])
          {
           p = p + (float)prof[i] / (float)w[i] * wl;
           wl = 0;
           break;// Jump out of for-loop
          }
        else
         {
          p = p + prof[i];
          wl = wl - w[i];
         }
       }
     return ceil(-p);
    }

int lbd_2(int x, int wl, int p) //Method given by Prof. MT
    {
     int i,j;
     int tw[1000];
     int tprof[1000];

     for(i = x+1; i <= n; i++)
      {
        tprof[i] = prof[i];
        tw[i] = w[i];
      }
     for (i = n; i >= x + 1; i--)
      {
        for(j = x + 1; j < i ; j++)
          {
            if(tprof[j] < tprof[j+1])
              {
                fchange(tprof + j,tprof + j + 1);
              }
            if(tw[j] > tw[j+1])
              {
                change(tw + j ,tw + j + 1);
              }
          }
      }
     for(i=x+1; i<=n; i++)
      {
        if(wl < tw[i]) break;
          else
            {
              wl = wl - tw[i];
              p = p + tprof[i];
            }
      }
     return ceil(-p);
    }


int ubd(int x, int wl, int p)
   {
    int i;
    for(i=x+1; i<=n; i++)
       {
        if ((wl = wl-w[i]) > 0)
          p = p + prof[i];
        else
          break;
       }
    return ceil(-p);
   }

void knaptree(int level, int wl, int p, int kind)
     {
      int i, lbdtemp, lbdtemp0, lbdtemp1, ubdtemp, ubdtemp0, ubdtemp1, protemp = 0;
      ubdtemp = ubd(level, wl, p);
      ubdtemp0 = ubd(level+1, wl, p);
      ubdtemp1 = ubd(level+1, wl-w[level], p+prof[level]);

      if (kind == 0)
        {
          lbdtemp = lbd_1(level, wl, p);
          lbdtemp1 = lbd_1(level+1, wl-w[level], p+prof[level]);
          lbdtemp0 = lbd_1(level+1, wl, p);
        }
      else
        {
          lbdtemp = lbd_2(level, wl, p);
          lbdtemp1 = lbd_2(level+1, wl-w[level], p+prof[level]);
          lbdtemp0 = lbd_2(level+1, wl, p);
        }
      if(ubdtemp < minubd)
           {
            minubd = ubdtemp;
           }

      if (lbdtemp == ubdtemp) //stop generating ===> Case No.1
          {
            nodecount++;
            for(i=level+1; i<=n; i++)
              {
                if (wl < w[i]) mark[i] = 0;
                  else
                      {
                       mark[i] = 1;
                       wl = wl - w[i];
                      }
              }
            if(final_profit > lbdtemp)
              {
                final_profit = lbdtemp;
                for(i=1; i<=n; i++) //record the solution
                  {
                    final_mark[i] = mark[i];
                  }
              }
          }
      else if(level == n) //stop generating ===> Case No.2
          {
            nodecount++;
            for(i=1; i<=n; i++) {protemp = protemp + mark[i]* prof[i];}
            if(protemp < final_profit)
              {
                final_profit = protemp;
                for(i=1; i<=n; i++) //Record the solution
                  {
                    final_mark[i] = mark[i];
                  }
              }
          }
      else if (lbdtemp >= minubd) //stop generating ===> Case No.3
          {
            nodecount++;
            return;
          }
      else if (wl < w[level+1]) //level-th stuff can't be put in the knapsack ===> Case No.4
          {
            nodecount++;
            mark[level+1] = 0;
            nodecount++; //infeasible nodes
            knaptree(level+1, wl, p, kind);
          }
      else  // ===> Case No.5
          {
            if( lbdtemp0 > lbdtemp1) //expand the node with the best LB
              {
                nodecount++;
                mark[level+1] = 1;
                knaptree(level+1, wl-w[level+1], p+prof[level+1],kind);
                mark[level+1] = 0;
                knaptree(level+1, wl, p, kind);
              }
            else if(lbdtemp0 < lbdtemp1)
              {
                nodecount++;
                mark[level+1] = 0;
                knaptree(level+1, wl, p, kind);
                mark[level+1] = 1;
                knaptree(level+1, wl-w[level+1], p+prof[level+1], kind);
              }
            if(ubdtemp0 >= ubdtemp1) //If LB is the same, expand the node with the lower upperbound
              {
                nodecount++;
                mark[level+1] = 1;
                knaptree(level+1, wl-w[level+1], p+prof[level+1],kind);
                mark[level+1] = 0;
                knaptree(level+1, wl, p, kind);
              }
            else
              {
                nodecount++;
                mark[level+1] = 0;
                knaptree(level+1, wl, p, kind);
                mark[level+1] = 1;
                knaptree(level+1, wl-w[level+1], p+prof[level+1], kind);
              }
           }
     }

void initialize()     
            {
             int i;
             for(i=1; i<=n; i++)
                {
                  final_mark[i] = 0;
                  mark[i] = 0;
                }
             final_profit = 0;
             nodecount = 0;
             solcount = 0;
             minubd = 0;
            }

int main()
    {
     int x = 0, i, j;
     time_t start1, end1, start2, end2;
     randomdata();
     shitsort();
     for(i=1; i<=n; i++)
        mark[i] = 0;
     printf("\n***************************** Final Assignment *****************************\n");
     printf("First Result : (Using the lower bound given in Textbook)\n");
     printf("\nThe profit of each data:\n");
     for(i=1; i<=n; i++)
        {
          printf("%3d", prof[i]);
        }
     printf("\nThe weight of each data:\n");
     for(i=1; i<=n; i++)
        {
          printf("%3d", w[i]);
        }
     printf("\n");
     start1 = time(NULL);
     knaptree(x, wl, 0, 0);
     printf("\nThe best profit is %d", -final_profit);
     printf("\nThe number of total nodes is: %ld", nodecount);
     printf("\nThe solution is: ");
     for(i=1; i<=n; i++)
        {
          printf("%2d", final_mark[i]);
        }
     end1 = time(NULL);
     //getchar();

     printf("\n========================================================================\n");
     initialize();

     start2 = time(NULL);
     knaptree(x, wl, 0, 1);
     printf("Second Result : (Using the lower bound given by Prof. Lin)\n");
     printf("\nThe best profit is %d", -final_profit);
     printf("\nThe number of total nodes is: %ld", nodecount);
     printf("\nThe solution is: ");
     for(i=1; i<=n; i++)
        {
          printf("%2d", final_mark[i]);
        }

     end2 = time(NULL);

     printf("\n\n========================================================================\n");
     printf("\nThe execution time of method 1: %f seconds", difftime(end1, start1));
     printf("\nThe execution time of method 2: %f seconds\n\n", difftime(end2, start2));

     return 0;   
    }
