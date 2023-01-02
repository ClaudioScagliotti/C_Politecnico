#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define MAXR 50

 void leggiMatrice(int M[][MAXR],int dim ,int *nr, int *nc);
int riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *b, int *h);

int main() {
    int i,j,k,l,nr,nc, tmp=0,a=0,o=0, fleg=0;
   // int ascissa[3], ordinata[3], base[3], altezza[3], area[3];
   /* for(i=0; i<3; i++){
        base[i]=0;
        altezza[i]=0;
        area[i]=0;
    } */
    int M[MAXR][MAXR];
    FILE *fp1;
    //controllo file
    fp1 = fopen("regioni.txt", "r");
    if(fp1==NULL)
    {
        printf("errore apertura file in lettura\n");
        return -1;
    }
    // leggo matrice
    fscanf(fp1, "%d %d", &nc, &nr);
    for(i=0;i<nc;i++) {
        for(j=0;j<nr;j++) {
            fscanf(fp1, "%d", &M[i][j]);
        }
    }
    fclose(fp1);
    for(i=0; i<nr+1; i++) // con questi due for incornicio a destra e sotto la matrice in modo che
    {                     // nella matrice sovradimensionata non si confonda il mio rettangolo con
        M[i][nc]=2;         // il contenuto delle altre celle
    }
    for(i=0; i<nc+1; i++)
    {
        M[nr][i]=2;
    }
    leggiMatrice(M,MAXR,&nr,&nc); // la funzione riporta nr e nc usando i puntatori
    printf("dimensioni matrice: %dx%d",nr,nc);
    //stampo matrice
    for(i=0;i<nc;i++) {
        for(j=0;j<nr;j++) {
            printf( "%d ", M[i][j]);
        }
        printf("\n");
    }
    int r,c, b=0, h=0; // leggo da tastiera la coppia di numeri in cui verificare se sono estr. sup. sx
    printf("Inserisci il valore r:\n");
    scanf("%d",&r);
    printf("Inserisci il valore c:\n");
    scanf("%d",&c);
    if(riconosciRegione(M, nr, nc, r, c, &b, &h))
    {
        printf("Il rettangolo che ha estr. sup sx in (%d,%d) ha base %d, altezza %d e area %d\n", r,c,b,h, b*h);
    }
    else{
        printf("La casella %d,%d non e' l'estr. sup sx. di un rettangolo\n ", r, c);
    }

    return 0;
}
void leggiMatrice(int M[][MAXR],int dim ,int *nr, int *nc)
{
    int i,c=0,r=0;
    for(i=0; i<dim; i++){
        if(M[i][0]==1 || M[i][0]==0)
        {  r++;}
        else {break;}
    }
    for(i=0; i<dim; i++){
        if(M[0][i]==1 || M[0][i]==0)
        {  c++;}
        else{break;}
    }
    *nc=c;
    *nr=r;

}
int riconosciRegione(int M[][MAXR],int nr,int nc,int r,int c,int *b,int *h)
{
    int fleg=1,i; //fleg inizializzato a vero
    if(M[r][c]==1)
    {
        if(r-1>=0) //se esiste la casella sopra
        {
            if(M[r-1][c]!=1){} // se la casella e' diversa da 1
                else{
                     fleg=0;
                     }

        }
        if(c-1>=0) //se esiste la casella <----
        {
            if(M[r][c-1]!=1){} // se la casella e' diversa da 1
            else{
                fleg=0;
            }

        }
        if(fleg==1){
            *h=0;
            *b=0;
            for(i=r; i<nr; i++)
            {
                if(M[i][c]==1){*h=*h+1;}
                else{break;}
            }
            for(i=c; i<nc; i++)
            {
                if(M[r][i]==1){*b=*b+1;}
                else{break;}
            }
        }

    }
    else{
        fleg=0;
    }
    return fleg;

}