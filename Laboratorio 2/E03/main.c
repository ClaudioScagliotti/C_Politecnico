#include <stdio.h>
#include <stdlib.h>
#include<ctype.h>
#include<string.h>

#define N_MAX 20 //numero massimo di sequenze da controllare presenti nel file sequenze.txt
#define LUN_MAX_RIGA 201 //numero di caratteri massimi presenti in una riga
#define LUNG_MAX_PAROLA 26 //numero max di caratteri per ogni parola
#define N_MAX_OCCORRENZE 10 //num max occorrenze per ogni sequenza

typedef struct {
    char confrontare[5+1];
} sequenza;

typedef struct {
    char elementi[LUNG_MAX_PAROLA];
} parola;

int lettura_file_sequenze(sequenza seq[]);

int main()
{

    sequenza s[N_MAX];
    char appoggio[LUNG_MAX_PAROLA];
    char *punt=NULL;
    char matrice[LUNG_MAX_PAROLA][900];
    parola pa[900];
    int n=0, c;
    n=lettura_file_sequenze (s);
    printf("Numero di sequenze:%d\n",n);

    int vett_i[n][N_MAX_OCCORRENZE+1];
    for(int d=0; d<n;d++)
    {
        for(c=0; c<N_MAX_OCCORRENZE+1;c++)
        {
            vett_i[d][c]=0;
        }
    }
    FILE *fp2;
    fp2 = fopen ("testo.txt", "r" );
    if ( fp2 == NULL)
    {
        printf ( "Errore nell'apertura del file fp2" );
        return -1;
    }
    int i=0; //scorre struttura in verticale passando da una parola all'altra
    int j=0; //scorre struttura in orizzontale passando da una carattere al altro
    int flag=1; //prima  c'è carattere usato per virgola spazio
    int z=0;
    char riga[LUN_MAX_RIGA];
    while(fgets(riga, LUN_MAX_RIGA, fp2)!=NULL) //lo uso quando non so il formato del file
    {
        for(z=0, j=0; z<LUN_MAX_RIGA && riga[z]!='\n' &&riga[z]!='\0'; z++)
        {
            if((isspace(riga[z])==0)&&(ispunct(riga[z])==0) && (isalnum(riga[z]))&&riga[z]!='\n'&&riga[z]!='\0') // 0 falso
            {
                pa[i].elementi[j]=riga[z];
                j++;
                flag=1; //trova carattere

            }
                // }
            else
            {
                if(flag==1)
                {
                    j=0;
                    i++;
                    flag=0;
                }
                else
                {
                    flag=0;
                }
            }
        }
        i++;
    }

    c=1;

    for(int x=0; x<n; x++)
    {
        for(int y=0; y<i;y++)
        {
            strcpy(appoggio,pa[y].elementi);
            for(int r=0;r<LUNG_MAX_PAROLA; r++){
                appoggio[r]=tolower(appoggio[r]);
            }
            punt=strstr(appoggio,s[x].confrontare); //riporta puntatore alla prima occorrenza della s.confrontare
            if(punt!=NULL)
            {
                vett_i[x][c]=y;
                c++;

                vett_i[x][0]=vett_i[x][0] +1;
                if(c>10)
                {
                    break;
                }
            }
        }
        punt=NULL;
        c=1;
    }
    int u=0;


    for(int x=0; x<n; x++)
    {
        if(vett_i[x][0]>0){
        int l=vett_i[x][0];
        printf("la sequenza:");
        printf("%s ",s[x].confrontare);
        printf(" e' contenuta in: ");
        for(int c=1; c<l+1; c++)
        {
            u=vett_i[x][c];
            printf("%s ",pa[u].elementi);
            printf("(parola in posizione %d nel testo) \n",u);

        }
        printf("\n");
       } else
        {printf("La sequenza %s non e' presente nel testo\n", s[x].confrontare);}
    }
    fclose(fp2);
    return 0;
}

int lettura_file_sequenze(sequenza seq[N_MAX]){
    int n=0;

    FILE* fp1;
    if((fp1=fopen("sequenze.txt","r"))==NULL)
    {
        printf("errore apertura file\n");
        return 1;
    }
    else
    {
        fscanf(fp1, "%d",&n); //legge numero di sequenze presenti
        if(n<=20)
        {
            for(int x=0;x<n;x++)
            {
                fscanf(fp1,"%s",seq[x].confrontare);
            }
        }
        else
        {
            printf("errore:nel file sequenze.txt sono presenti più di 20 sequenze. Modificare il file.");
        }
    }
    fclose(fp1);
    return n;
}
