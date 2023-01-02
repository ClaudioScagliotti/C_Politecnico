#include <stdio.h>
int bigendian() {
    int i=1;
    unsigned char *c= (unsigned char *) &i; //cast per il puntatore ad i, facendolo diventare uns. char
    if(c[0]==1) {return 1;} // little       //1 byte anziche i 4 dell'int
            else{ return 0; }// big             //se c[0] è 1 allora sono in little endian
}
void stampaCodifica (void *p, int size, int bigEndian);
void conversione(int binario[], int decimale);
int main() {
    float af;
    double ad;
    long double ald;
    int bigEndian=bigendian();
 if(bigendian()){
     printf("Il pc lavora in Little Endian\n");
 }
 else{
     printf("Il pc lavora in Big Endian\n");
 }
   int  dimf= sizeof(float);
   int  dimd= sizeof(double);
    int dimld=sizeof(long double);

    printf("Float: %d byte, %d bit\n",dimf, 8*dimf);
    printf("Double: %d byte, %d bit\n",dimd, 8*dimd);
    printf("Long Double: %d byte, %d bit\n",dimld, 8*dimld);
    printf("Inserisci 3 numeri da tastiera:\n");
    scanf("%f", &af);
    stampaCodifica((void *)&af,sizeof(af),bigEndian);
    scanf("%lf", &ad);
    stampaCodifica((void *)&ad,sizeof(ad),bigEndian);
    /*scanf("%Lf", &ald);
    stampaCodifica((void *)&ald,sizeof(long double),bigEndian);*/




    return 0;
}
void stampaCodifica (void *p, int size, int bigEndian) {

    unsigned char *v = (unsigned char *) p;//cast a unsigned char * per p
    int i;
    int binario[8];
    if (bigEndian) // valore 1= little endian
    {
        switch (size) {
            case 4: {


                printf("Codifica del Float:\nBit per il segno:\n");


                conversione(binario, v[3]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                    if(i==7){printf("\nBit per l'esponente:\n");}

                }

                conversione(binario, v[2]);     // 00111111100000000000000000000000
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                    if(i==7){printf("\nBit per la mantissa:\n");}
                }


                conversione(binario, v[1]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }


                conversione(binario, v[0]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                printf("\n");
                break;
            }


            case 8: {
                printf("Codifica del Long:\nBit per il segno:\n");
                conversione(binario, v[7]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                    if(i==7){printf("\nBit per l'esponente:\n");}

                }
                conversione(binario, v[6]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                    if(i==3){printf("\nBit per la mantissa:\n");}

                }//0 10000000101 0101010010000000000000000000000000000000000000000000   85.125
                conversione(binario, v[5]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                conversione(binario, v[4]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                conversione(binario, v[3]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                conversione(binario, v[2]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                conversione(binario, v[1]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                conversione(binario, v[0]);
                for (i = 7; i >= 0; i--) {
                    printf("%d", binario[i]);
                }
                break;
            }
            case 16: {

                break;
            }


        }
    }

    else // valore 0 = big endian
    {
        switch (size) {
            case 4: {
               // v = (unsigned char *) p;
                conversione(binario,v[0]);
                // printf("prova%x\n",v[3]);
                for( i=0; i<8; i++){
                    printf("%d",binario[i]);
                }
                printf("\n");
                conversione(binario,v[1]);
                // printf("prova%x\n",v[3]);
                for( i=0; i<8; i++){
                    printf("%d",binario[i]);
                }printf("\n");
                conversione(binario,v[2]);
                // printf("prova%x\n",v[3]);
                for( i=0; i<8; i++){
                    printf("%d",binario[i]);
                }
                printf("\n");
                conversione(binario,v[3]);
                // printf("prova%x\n",v[3]);
                for( i=8; i>0; i--){
                    printf("%d",binario[i]);
                }
                break;
            }
            case 8: {
                break;
            }
            case 16: {
                break;
            }

        }
    }
}
void conversione(int binario[], int decimale) {
    int i;

    for(i=0; i<8; i++)
    {
        binario[i]=0;
    }

    for(i=0; i<8; i++) {
        if(decimale%2==0) {
            binario[i]=0;
        }
        else {
            binario[i]=1;
        }

        decimale = decimale/2;
    }

}