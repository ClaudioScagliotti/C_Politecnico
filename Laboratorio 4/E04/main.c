#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 30 //num max caratteri di ogni parolaa della riga
#define MAXR 1000 //num max di righe nel file (max di nr)

typedef struct { //struttura per conservare i record del file
    int codice_tratta;
    char luogo_partenza[MAXC];
    char luogo_arrivo[MAXC];
    char data[11];
    char ora_p[6]; //orario di partenza
    char ora_a[6]; //orario di arrivo
    int ritardo;

} elenco;

int compara(elenco st1, elenco st2, int key);
void scambio(elenco array[MAXR], int i, int j);
void ricerca_lineare(elenco array[MAXR],int n,char k[MAXC],int *v_ricerca, int *l);
int ricerca_dicotomica(elenco *array, int p, int u,int m, char k[MAXC], int *l, int *flag);
void proseguimento_ricerca(elenco array[MAXR],int p, int s,char k[MAXC],int *v_ri,int *l);

int main()
{
    int n, prim, sec, m,lun, t, stampa, i, j, key, posmin, codice_tratta;
    int flag_ordinato=0;
    char c[8],  citta[MAXC], ricerca[2];
    t=0;
    elenco array[MAXR];

    FILE *fp;
    fp=fopen("corse.txt","r");
    if(fp==NULL)
    {
        printf("errore apertura file in lettura\n");
        return -1;
    }
    fscanf( fp, "%d", &n );

    int l=0,f=n-1, risultato; //usati per ricerca dicotomica
    int v_ricerca[n]; //usato in ricerca lineare
    for(int i=0;i<n;i++) //inizializzo il vettore v_ricerca a -1 che indica che non e' stato trovato niente negli algoritmi di ricerca
    {
        v_ricerca[i]=-1;
    }
    int v_r[n]; //usato in ricerca dicotomica
    for(int i=0;i<n;i++) //inizializzo il vettore v_ricerca a -1 che indica che non e' stato trovato niente negli algoritmi di ricerca
    {
        v_r[i]=-1;
    }
    for ( i = 0; i < n; i++ )
    {
        fscanf( fp,"%d %s %s %s %s %s %d",&array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, &array[i].ritardo );
        //ulteriore stampa di controllo non indispensabile
        printf("%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo );
    }
    fclose (fp);

    FILE *fp1;
    fp1=fopen("stampa.txt","w");
    if(fp1==NULL)
    {
        printf("errore apertura file in lettura\n");
        return -1;
    }

    do {
        printf( "\nInserisci da tastiera un comando tra: stampa; ordina; ricerca; termina. \n" );
        scanf("%s",c); //assume la stringa di comando da tastiera
        switch(c[0]) //fa il controllo solo sul primo carattere della stringa
        {
            case 's': // s sta per stampa
                printf("Inserisci dove vuoi stampare: 1) stampa a video 2) stampa su file \n");
                scanf("%d",&stampa);
                switch(stampa)
                {
                    case 1: //stampa a video
                        for (i=0; i<n; i++)
                        {
                            printf("%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo );
                        }
                        break;
                    case 2: //stampa su file
                        for(i=0; i<n; i++)
                        {
                            fprintf(fp1,"%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo);
                        }
                        break;

                    default:
                        printf("Parametri errati.");
                }
                break;
            case 'o': //o sta per ordina
                printf("Inserisci cosa vuoi ordinare: \n1) per codice tratta \n2) per il luogo di partenza  \n3) per il luogo di arrivo \n4) per la data\n");
                scanf("%d",&key);

                for (i=0;i<n-1;i++)
                {
                    posmin=i;
                    for(j=i+1; j<n; j++)
                    {
                        if(compara(array[j],array[posmin],key)<0)
                        {
                            posmin=j;
                        }
                    }
                    scambio(array, i, posmin);
                }
                for ( i = 0; i < n; i++ )
                {
                    printf("%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo );
                }
                if(key==2) //ho ordinato le citta di partena, ora posso fare la ricerca dicotomica
                {//la ricerca dicotomica non si puo' fare se prima il vettore non e' stato ordinato
                    flag_ordinato=1;
                }
                break;
            case 'r': //r sta per ricerca
                printf("Inserici una citta' di partenza:\n");
                scanf("%s",citta);
                if(flag_ordinato==0)//ricerca lineare
                {
                    printf("Ricerca lineare:\n");
                    ricerca_lineare(array,n,citta,v_ricerca,&lun);
                    for(int j=0; j<n; j++)
                    {
                        if(v_ricerca[j]!=(-1)) //stampo le tratte che corrispondono alla citta' di partenza che ho richiesto. Prima il vett lo avevo inizzializzato a -1
                        {
                            printf("%d %s %s %s %s %s %d\n",array[v_ricerca[j]].codice_tratta, array[v_ricerca[j]].luogo_partenza, array[v_ricerca[j]].luogo_arrivo, array[v_ricerca[j]].data, array[v_ricerca[j]].ora_p, array[v_ricerca[j]].ora_a, array[v_ricerca[j]].ritardo );
                        }
                    }
                    for(int i=0;i<n;i++) //risetto il vettore v_ricerca, dopo la stampa, per poterlo riutilizzare
                    {
                        v_ricerca[i]=-1;
                    }
                }
                else//ricerca dicotomica si puo' fare perche' ho flag_ordinato=1
                {
                    printf("Ricerca dicotomica:\n");
                    risultato=ricerca_dicotomica(array,l,f,m,citta,&lun, &t); //ottengo la posizione in cui e' stata trovata, per la prima volta, la citta' tramite l'algoritmo di ricerca dicotomica
                    //printf("%d %s %s %s %s %s %d\n",array[risultato].codice_tratta, array[risultato].luogo_partenza, array[risultato].luogo_arrivo, array[risultato].data, array[risultato].ora_p, array[risultato].ora_a, array[risultato].ritardo );
                    if(t==1) //PROBLEMA
                    {
                        printf("%d %s %s %s %s %s %d\n",array[risultato].codice_tratta, array[risultato].luogo_partenza, array[risultato].luogo_arrivo, array[risultato].data, array[risultato].ora_p, array[risultato].ora_a, array[risultato].ritardo );
                        prim=0, sec=risultato;
                        proseguimento_ricerca(array,prim,sec,citta,v_r,&lun);

                        for(int j=0; j<n; j++)
                        {
                            if(v_r[j]!=(-1)) //stampo le tratte che corrispondono alla citta' di partenza che ho richiesto. Prima il vett lo avevo inizzializzato a -1
                            {
                                printf("%d %s %s %s %s %s %d\n",array[v_r[j]].codice_tratta, array[v_r[j]].luogo_partenza, array[v_r[j]].luogo_arrivo, array[v_r[j]].data, array[v_r[j]].ora_p, array[v_r[j]].ora_a, array[v_r[j]].ritardo );
                            }
                        }
                        for(int i=0;i<n;i++) //risetto il vettore v_ricerca, dopo la stampa, per poterlo riutilizzare
                        {
                            v_r[i]=-1;
                        }

                        prim=risultato+1, sec=n;
                        proseguimento_ricerca(array,prim,sec,citta,v_r,&lun);

                        for(int j=0; j<n; j++)
                        {
                            if(v_r[j]!=(-1)) //stampo le tratte che corrispondono alla citta' di partenza che ho richiesto. Prima il vett lo avevo inizzializzato a -1
                            {
                                printf("%d %s %s %s %s %s %d\n",array[v_r[j]].codice_tratta, array[v_r[j]].luogo_partenza, array[v_r[j]].luogo_arrivo, array[v_r[j]].data, array[v_r[j]].ora_p, array[v_r[j]].ora_a, array[v_r[j]].ritardo );
                            }
                        }
                        for(int i=0;i<n;i++) //risetto il vettore v_ricerca, dopo la stampa, per poterlo riutilizzare
                        {
                            v_r[i]=-1;
                        }
                    }
                    else
                    {
                        printf("Citta' non trovata\n");
                    }
                }

                break;
            case 't': //t sta per termina
                printf("\nProgramma terminato");
                break;
            default:
                printf("Comando non valido.\n");
                break;
        }
    } while (c[0]!='t');

    fclose (fp1);
    return 0;
}
int compara(elenco st1, elenco st2, int key)
{
    switch(key)
    {
        case 1:   return st1.codice_tratta - st2.codice_tratta; //l'ordinamento di codice.tratta e' un ord. di int (faccio sottrazione)
        case 2:   return strcmp(st1.luogo_partenza,st2.luogo_partenza);//e' un ordinamento alfabetico
        case 3:   return strcmp(st1.luogo_arrivo,st2.luogo_arrivo);
        case 4:
            if (strcmp(st1.data,st2.data)==0) //a parita' di date, vado in ordine crescente di orario partenza
            {
                return strcmp(st1.ora_p,st2.ora_p);
            }
            else
            {
                return strcmp(st1.data,st2.data);
            }

        default:
            printf("Comando key errato.\n");
            break;
    }
}
void scambio(elenco array[MAXR], int i, int j) //l'ordinamento avviene grazie a una struct temporanea
{
    elenco temp;

    temp=array[i];
    array[i]=array[j];
    array[j]=temp;
}

void ricerca_lineare(elenco array[MAXR],int n,char k[MAXC],int *v_ricerca, int *l)
{
    int j=0, flag=0;
    l=strlen(k);
    for(int i=0; i<n; i++)
    {
        if(strncmp(k,array[i].luogo_partenza,l)==0) //riporta zero se e' vero
        {
            v_ricerca[j]=i; //salvo la posizione in cui ho trovato il vettore
            j++;
            flag=1;
        }
    }
    if(flag==0)
    {
        printf("Citta' non trovata\n");
    }
}

//ricerca dicotomica o binaria. NON mi riporta tutti gli elementi che si ripetono ma solo il primo che trova (RICERCA PARZIALE)
int ricerca_dicotomica(elenco *array, int p, int u,int m, char k[MAXC],int *l, int *flag)
{
    l=strlen(k);
    int trovato=0;
    if(p>u)
    {
        return -1; //primo elemento e' maggiore dell'ultimo
    }
    m =(p+u)/2; //calcolo il punto medio tra gli estremi
    if(strncmp(k,array[m].luogo_partenza,l)==0) //se trovo citta'
    {
        //trovato=1;
        //flag=&trovato;
        *flag=1;
        return (m);
    }
    if(strncmp(k,array[m].luogo_partenza,l)<0) //k e' prima in ordine alfabetico di array[m].luogo_partenza
    {
        return ricerca_dicotomica(array, p, m-1,m, k, &l, flag); //vado nella parte dx rispetto a m
    }
    return ricerca_dicotomica(array, m+1, u,m,k, &l, flag);//k viene dopo in ordine alfabetico rispetto a r[m].luogo_partenza
    //vado nella parte sx rispetto a m
}
void proseguimento_ricerca(elenco array[MAXR],int p, int s,char k[MAXC],int *v_ri,int *l)
{
    int j=0, i;
    l=strlen(k);

    for(i=p; i<s; i++)
    {
        if(strncmp(k,array[i].luogo_partenza,l)==0) //riporta zero se e' vero
        {
            v_ri[j]=i; //salvo la posizione in cui ho trovato il vettore
            j++;
        }
    }

}
