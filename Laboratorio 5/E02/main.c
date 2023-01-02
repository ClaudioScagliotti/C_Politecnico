#include <stdio.h>
#include <stdlib.h>

void separa(int **mat, int nr, int nc, int *vb,int *vn);
int **malloc2dR (FILE *f, int *nr, int *nc );

int main() {

    //scelgo che la prima casella della scacchiera sia bianca
    FILE *fp;
    int i, j, c, r;
    int **m, nc, nr;
    int *vb, *vn;
    printf("Matrice:\n");
    m = malloc2dR(fp, &nr, &nc);
    vn = (int *) malloc(((nr * nc) / 2) * sizeof(int));
    vb = (int *) malloc(((nr * nc) / 2) + 1 * sizeof(int)); //sovradimensiono di 1 il vett bianco perchè in base a nr, nc
    printf("dimensione matrice: %d x %d\n", nr, nc); // il + 1 potrebbe servirmi
    separa(m, nr, nc, vb, vn);
    printf("Vettore caselle 'nere':");
    for (i = 0; i < ((nr * nc) / 2); i++)
        printf("%d ", vn[i]);
    if ((nr % 2 != 0) && (nc % 2 != 0)) {   //se nr e nc sono entrambi dispari c'è un bianco in più
        printf("\nVettore caselle bianche:"); // in tutti gli altri casi i due vettori hanno lo stesso numero di elem.
        for (i = 0; i < (nr * nc) / 2 + 1; i++)
            printf("%d ", vb[i]);
    } else {
    printf("\nVettore caselle bianche:");
    for (i = 0; i < (nr * nc) / 2; i++)
        printf("%d ", vb[i]);
    }
    // due for per la free
   // for ( i = 0; i < nr; i++ )
      //  for ( j = 0; j < nc; j++ )
            free(m);
           // free(vb);
            //free(vn);
    return 0;
}
int **malloc2dR (FILE *f, int *nr, int *nc ) {

    int i,j,numr,numc,**mat;
    f=fopen("mat.txt","r");
    fscanf(f, "%d %d", nr, nc);
    mat = (int **) malloc( *nr * sizeof(int *) );
    for ( i = 0; i < *nr; i++ ) {
        mat[i] = (int *) malloc(*nc * sizeof(int));
    }

    for ( i = 0; i < *nr; i++ ) {
        for ( j = 0; j < *nc; j++ ) {
            fscanf( f, "%d ", &mat[i][j] );
            printf("%d  ", mat[i][j] );
        }
        printf("\n");
    }

    fclose(f);
    return mat;
}
void separa ( int **mat, int nr, int nc, int *vb, int *vn ) {
    int i, j;
    int b = 0, n = 0;
    for ( i = 0; i < nr; i++ ) {
        for (j = 0; j < nc; j++) {
            if (i % 2 == 0 && j % 2 == 0) //in caso di entrambe coord pari casella bianca
                vb[b++] = mat[i][j];

            if (i % 2 == 0 && j % 2 != 0)//in questo caso casella nera
                vn[n++] = mat[i][j];

            if (i % 2 != 0 && j % 2 == 0)//in questo caso casella nera
                vn[n++] = mat[i][j];

            if (i % 2 != 0 && j % 2 != 0)//in caso di entrambe coord dispari casella bianca
                vb[b++] = mat[i][j];
        }
    }
}
