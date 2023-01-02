#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_LUNG_RIGA 201//del file sorgente
#define S_MAX 30    //NUMERO MAX DI RICODIFICHE

typedef struct {
    char sostituire[MAX_LUNG_RIGA];  //parola da sostituire
    char confrontare[MAX_LUNG_RIGA];    //parola da confrontare
} dizionario;

int lettura_parole_file_dizionario (dizionario diz[]);

int main()
{
     int flag=0;
     char riga[MAX_LUNG_RIGA];
     dizionario d[S_MAX];

     FILE *fp2, *fp3;
     fp2 = fopen ( "sorgente.txt", "r" );
     fp3 = fopen ( "ricodificato.txt", "w" );
     if ( fp2 == NULL || fp3 == NULL )
     {
         printf ( "Errore nell'apertura dei file" );
         return -1;
     }

     int n;
     n= lettura_parole_file_dizionario(d);
    // printf("%d\n",n);

      while(fgets(riga,MAX_LUNG_RIGA,fp2)!=NULL)
        {
           int lunghezza_c;
           int l_r=strlen(riga);  //lunghezza riga
           for(int i=0;i<l_r;i++) //scorre riga sorgente
           {
               flag=0;
               int flag_stampa=0;
               for(int j=0;j<n;j++)//scorre in verticale la struttura d
               {
                   lunghezza_c=strlen(d[j].confrontare);  //lunghezza della stringa confrontare presente nella struttura
                   for(int k=0; k<lunghezza_c; k++) // scorre in orizzontale ogni singolo elemento della struttura d
                   {
                           if(riga[i+k]!=d[j].confrontare[k])
                           {
                              flag=0;
                              break;
                           }
                           else
                            {
                              flag=1;
                            }
                    }
                    if(flag==1)
                    {
                         fprintf(fp3,"%s", d[j].sostituire);
                         i=i+(lunghezza_c-1);
                         flag_stampa=1;
                     }
                }
                if(flag_stampa==0)
                {
                   fprintf(fp3,"%c", riga[i]);
                }
            }
        }
    fclose(fp2);
    fclose(fp3);
    return 0;
}


int lettura_parole_file_dizionario (dizionario diz[S_MAX]){
    int n=0;

    FILE* fp1;
    if((fp1=fopen("dizionario.txt","r"))==NULL)
    {
        printf("errore apertura file\n");
        return 1;
    }
    else
    {
        fscanf(fp1, "%d",&n); //legge numero di parole da sostituire, ovvero legge il numero di parole presenti del file dizionario
        for(int i=0;i<n;i++)
        {
        fscanf(fp1, "%s %s", diz[i].sostituire, diz[i].confrontare);
        }
    }
    fclose(fp1);
    return n;
}


