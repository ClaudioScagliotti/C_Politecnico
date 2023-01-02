#include <stdio.h>
#include <stdlib.h>
int disp_ripet(int pos, char *val, char *sol, int n, int k, int count, int z, int s, int r,int t,int j);
int main() {
    int i, n, n_dist, k, total, *dist_val, *mark;
    char *val,*sol;
    int j=0;
    int z=5,s=7,r=4,t=10;
    n=z+s+r+t;
    k=24; // con k=7 e la stampa ci mette un'ora e mezza
    //devo diminuire drasticamente i tempi di esecuzione, non trattare pietre come istanze
    //come variare automaticamente k senza aumentare esponenzialmente in numero di operazioni
    //approccio dicotomico per trovare la lunghezza di k oppure andare per costruzione di soluzioni man mano sempre + lunghe
    val = malloc(n * sizeof(char));
    sol = malloc(k * sizeof(char));
    for (i=0; i < k; i++)
        sol[i]= 'x';
    for (i=0; i<z; i++) {
        val[i]='z';
    }
    for (i=z; i<z+s; i++) {
        val[i]='s';
    }
    for (i=z+s; i<z+s+r; i++) {
        val[i]='r';
    }
    for (i=z+s+r; i<n; i++) {
        val[i]='t';
    }
    printf("Le disposizioni ripetute di %d lettere  ", n);
    for (i=0; i <n; i++)
        printf("%c, ", val[i]);
    printf("\n a %d a %d sono:\n", k, k);
    total = disp_ripet(0, val, sol, n, k, 0, z,s,r,t,j);
    printf("e in totale sono %d \n", total);
    free(sol);
    free(val);
    return 0;
}
int disp_ripet(int pos, char *val, char *sol, int n, int k, int count,int z, int s, int r,int t,int j) {
    int i,stampa=0;
    if (pos >= k) {

            for (i = 0; i < k; i++) {
                printf("%c ", sol[i]);
            }
            printf("\n");

            return count + 1;

        //else return count;
    }


      /*  if(z==0 && r>0){
            sol[pos]='r';
           // r--;
        }
        else {
            sol[pos]='z';
            //sol[pos] = val[pos + j];
        }
        if(r==0){
            if(s==0)
            sol[pos]='t';
            else
                sol[pos]='s';
        }*/
      if (pos==0){
        sol[pos]=val[0];
        if(z>0) z--;
        else if(s>0) s--;
        else if(r>0) r--;
        else t--;
      }
      else {
          if (sol[pos - 1] == 'z' && z == 0 && r > 0) {
              sol[pos] = 'r';
              r--;
          }
          else if (sol[pos - 1] == 'z' && z > 0 && r==0) {
              sol[pos] = 'z';
              z--;
          }
          else if(sol[pos - 1] == 'z' && z > 0 && r > 0) {
              if (z > r) {
                  sol[pos] = 'z';
                  z--;
              }
              else sol[pos] = 'r';
              r--;
          }
          else if (sol[pos - 1] == 'z' && z == 0 && r == 0) //da fare
              return count;



          else if (sol[pos - 1] == 'r' && s > 0 && t==0) {
              sol[pos] = 's';
              s--;
          }
          else if (sol[pos - 1] == 'r' && s == 0 && t > 0) {
              sol[pos] = 't';
              t--;
          }
          else if(sol[pos - 1] == 'r' && s > 0 && t > 0) {
              if (s > t) {
                  sol[pos] = 's';
                  s--;
              }
              else sol[pos] = 't';
              t--;
          }
          else if (sol[pos - 1] == 'r' && s == 0 && t == 0) // da fare
              return count;


          else if (sol[pos - 1] == 's' && s > 0 && t==0) {
              sol[pos] = 's';
              s--;
          }
          else if (sol[pos - 1] == 's' && s == 0 && t > 0) {
              sol[pos] = 't';
              t--;
          }
          else if(sol[pos - 1] == 's' && s > 0 && t > 0) {
              if (s > t) {
                  sol[pos] = 's';
                  s--;
              }
              else sol[pos] = 't';
              t--;
          }

          else if (sol[pos - 1] == 's' && s == 0 && t == 0) //da fare
              return count;


          else if (sol[pos - 1] == 't' && z > 0 && r==0) {
              sol[pos] = '<';
              z--;
          }
          else if (sol[pos - 1] == 't' && z == 0 && r > 0) {
              sol[pos] = 'r';
              r--;
          }
          else if(sol[pos - 1] == 't' && z > 0 && r > 0) {
              if (z > r) {
                  sol[pos] = 'z';
                  z--;
              } else sol[pos] = 'r';
              r--;
          }
          else if (sol[pos - 1] == 't' && z == 0 && r == 0)//da fare
              return count;
      }
   /* sol[pos] = val[pos + j];
            switch(sol[pos]){
                case 'z':z--; if ((val[pos+ 1] == 'z'  && z>0) || (val[pos+ 1] == 'r' && z>=0 && r>=0)){} else j++;
                    break;
                case 's':s--; if ((val[pos+ 1] == 's' && s>0) || (val[pos+ 1] == 't' && t>0 && s>=0)){} else j++;
                    break;
                case 'r':r--; if ((val[pos+ 1] == 's' && s>0) || (val[pos+ 1] == 't' && t>0 && s>=0)){} else j++;
                    break;
                case 't':t--; if ((val[j+ 1] == 'z'  && z>0) || (val[j+ 1] == 'r' && z>=0 && r>=0)){} else j++;
                    break;
                default: printf("Errore");
                break;
            }*/


        count = disp_ripet(pos+1, val, sol, n, k, count,z,s,r,t,j);

    return count;
}