#include <stdio.h>
#include <stdlib.h>
typedef struct {
    int a;
    int b; //scruct che contiene i due vertici dell'arco
}arco;
void verifica(int *sol,int j,int n, arco a[n],int pos);
int powerset_comb_semp(int* val, int n, int* sol, arco a[n]);
int powerset_r(int* val, int n, int* sol, int i,int pos, int start, arco a[n]);
int main() {
    FILE *f;
    f=fopen("grafo.txt","r");
    if(f==NULL){
        printf("errore apertura file");
    }
    int i,j, n,e, cnt, *val, *sol;
fscanf(f,"%d %d", &n, &e);
    arco ar[e];
    val = malloc(n*sizeof(int));
    sol = calloc(n,sizeof(int));


    for (i=0; i<e; i++) {

        fscanf(f,"%d %d", &ar[i].a,&ar[i].b);
    }

    printf("Archi del grafo:\n");
    for(i =0; i<n; i++)
        printf(" %d  %d\n", ar[i].a, ar[i].b);

    for(i=0,j=0; i<n; i++)
    {
        val[i]=i; //faccio questa assegnazione dando ai vertici un numero identificativo da 0 a n-1
    }

    printf("Combinazioni semplici possibili:\n");
    cnt = powerset_comb_semp(val, n, sol,ar);
    printf ("Numero di combinazioni semplici: %d \n(Ho escluso l'insieme vuoto)", cnt);


    free(val);
    free(sol);

    return 0;
}


int powerset_comb_semp(int* val, int n, int* sol, arco a[n]){
    int count = 0, i;
   // printf("{ }\n"); non considero insieme vuoto
   // count++;
    for(i = 1; i <= n; i++){  //i=1 ti fa partire le 16 comb, i =2 parte dalle coppie quindi 11
        count += powerset_r(val, n, sol, i, 0, 0,a);
    }
    return count;
}

int powerset_r(int* val, int n, int* sol, int i,int pos, int start, arco a[]){
    int count = 0,k, j;

    if (pos == i){
        printf("{ ");
        for (j = 0; j < i; j++) {
            printf("%d ", sol[j]);

        }
        printf("}   ");
        verifica(sol,j,n, a,pos);
        return 1;
    }
    for (j = start; j < n; j++){
        sol[pos] = val[j];
        count += powerset_r(val, n, sol, i, pos+1, j+1,a);
    }
    return count;
}
void verifica(int *sol,int j, int n,arco a[n], int pos){

    int k,ok[n],i=0,c,fleg=1; //vett[n];
    for(k=0; k<n; k++)
     ok[k]=0;

    //    printf("SOL DA VERIFICARE:\n");
   for(c=0; c<n; c++, i++) {
       for (k = 0; k < pos && ok[i]==0; k++) {
           if (sol[k] == a[c].a || sol[k] == a[c].b) {
               ok[i] = 1;

           }
       }
   }
    for(k=0; k<n; k++)
    {
        if(ok[k]!=1)
            fleg=0;
    }
    if(fleg==0) {
        printf("Soluzione non valida\n");

    }
    else {
        printf("Vertex cover\n");

    }

}