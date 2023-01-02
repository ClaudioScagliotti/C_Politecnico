#include <stdio.h>
#include <string.h>
#include <ctype.h>
#define N 50
int main() {
    int i,j,k,l,nr,nc, tmp=0,a=0,b=0, fleg=0;
    int ascissa[3], ordinata[3], base[3], altezza[3], area[3];
    for(i=0; i<3; i++){
        base[i]=0;
        altezza[i]=0;
        area[i]=0;
    }
    int mat[N][N];
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
            fscanf(fp1, "%d", &mat[i][j]);
        }
    }
    fclose(fp1);
    //stampo matrice
    for(i=0;i<nc;i++) {
        for(j=0;j<nr;j++) {
            printf( "%d ", mat[i][j]);
        }
        printf("\n");
    }
    // Scansiono le righe, cerco la base max
    for(j=0;j<nr;j++) {
        for(i=0;i<=nc;i++){
            if( mat[j][i]==1)
            {tmp++;}
            else if(tmp>base[0])
            {base[0]=tmp;
            ascissa[0]=j;
            ordinata[0]=i-tmp;
                tmp=0;}
            else{tmp=0;}
            }
        tmp=0;
        }
    // ora calcoli l'altezza di questa base e di conseguenza l'area
    //int t=ordinata[0];
    for(j=0;j<=nr-ascissa[0];j++){
        if(mat[ascissa[0]+j][ordinata[0]]==1){
            altezza[0]++;
        } else {break;}
    }

    area[0]=base[0]*altezza[0];
    tmp=0;

    //calcolo dati riguardanti il blocco più alto
    for(i=0;i<nr;i++) {
        for (j = 0; j <=nc; j++) {

            if (mat[j][i] == 1)
            { tmp++; }
            else if (tmp > altezza[1]) {
                altezza[1] = tmp;
                ascissa[1] = j-tmp;
                ordinata[1] = i;
                tmp = 0;
            } else { tmp = 0; }
        }
        tmp=0;
    }
    // ora calcolo base e area
       //  t=ascissa[1];
    for(j=0;j<=nc-ordinata[1];j++){
        if(mat[ascissa[1]][ordinata[1]+j]==1){
            base[1]++;
        } else {break;}
    }
    area[1]=base[1]*altezza[1];
    tmp=0;
    // ora calcolo area piu grande
    for(j=0; j<nr; j++){    //righe
        for(i=0; i<nc; i++){ //colonne
            if(mat[j][i]==1)
            { fleg=0;
                for(k=i; k<=(base[0]+i); k++) {

                        if (mat[j][k] == 1) {
                            b++;
                        } else {
                            for (l = j; l <= altezza[1] + j; l++) {
                                if (mat[l][i] == 1) {
                                    a++;
                                } else if ((a * b) > area[2]) {
                                    area[2] = (a * b);
                                    base[2] = b;
                                    altezza[2] = a;
                                    ascissa[2] = j;
                                    ordinata[2] = i;
                                    fleg = 1;
                                    i = i + b;
                                    a = 0;
                                    b = 0;
                                    break;
                                } else { break; }
                            }
                        }

                }
            }
        a=0; b=0;}
    }




    printf("Max Base: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", ascissa[0], ordinata[0], base[0], altezza[0], area[0]);
    printf("Max Area: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", ascissa[2], ordinata[2], base[2], altezza[2], area[2]);
    printf("Max Altezza: estr. sup. SX=<%d,%d> b=%d, h=%d, Area=%d\n", ascissa[1], ordinata[1], base[1], altezza[1], area[1]);
    return 0;
}