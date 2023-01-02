#include <stdio.h>
#include <stdlib.h>
typedef struct{
    int numero;
    char canzone[5][256];
} amico;
int generaplaylist( amico *a, int *sol, int max, int pos, int count, FILE *f); //principio di moltiplicazione
int main () {
    FILE *fp;
    FILE *fp1;
    int na; //numero amici
    int *sol;
    fp1 = fopen( "stampa.txt", "w");
    if ( fp1 == NULL )
    {
        printf("Errore apertura file");
        return -1;
    }
    fp = fopen( "brani.txt", "r");
    if ( fp == NULL )
    {
        printf("Errore apertura file");
        return -2;
    }
    // acquisizione file
        fscanf(fp,"%d",&na);
    sol = (int *) malloc( na * sizeof(int) );
    amico am[na];
    amico *a=&am;
        for(int i=0; i<na; i++){
            fscanf(fp,"%d",&am[i].numero);
            for(int j=0; j<am[i].numero; j++)
            {
                fscanf(fp,"%s", am[i].canzone[j]);
            }
        }
int tot=generaplaylist(a,sol,na, 0,0,fp1);
printf("ci sono in tutto %d playlist possibili", tot);
    free(sol);
    fclose(fp);
    fclose(fp1);
    return 0;

}
int generaplaylist( amico *a, int *sol, int max, int pos, int count, FILE *fp1){

int i;
if (pos >= max) {
for (i = 0; i < max; i++) {
    printf("%s\n ", a[i].canzone[sol[i]]);
    fprintf(fp1, "%s\n", a[i].canzone[sol[i]]);
}
printf("\n");
fprintf(fp1,"\n");
return count+1;
}
for (i = 0; i < a[pos].numero; i++) {
sol[pos] = i;
count = generaplaylist(a,sol,max,pos+1, count, fp1);
}
return count;
}