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

int compara_tratta(elenco *p1, elenco *p2);
void scambio_punt(elenco *punt_tratta[MAXR], int i, int j);
int compara_char(elenco *p1, elenco *p2);
void scambio_char(elenco *puntatore[MAXR], int i, int j);

int main()
{
    int n, prim, sec,lun, t, m, stampa, i, j, key, posmin, codice_tratta;
    int flag_ordinato=0;
    char c[8],  citta[MAXC], ricerca[2], temp[MAXC];
    t=0;
    // 4 vett di puntatori ognuno alla struct all'inizio uguali poi si differenzziano
    elenco array[MAXR];
    elenco *punt_tratta[MAXR];
    elenco *punt_partenza[MAXR];
    elenco *punt_arrivo[MAXR];
    elenco *punt_data[MAXR];
    //assegno contenuto ai puntatori
    for ( i=0; i<MAXR; i++)
    {
        punt_tratta[i]=&array[i];
    }

    for ( i=0; i<MAXR; i++)
    {
        punt_partenza[i]=&array[i];
    }
    for ( i=0; i<MAXR; i++)
    {
        punt_arrivo[i]=&array[i];
    }
    for ( i=0; i<MAXR; i++)
    {
        punt_data[i]=&array[i];
    }

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
    for(int i=0;i<n;i++) //inizzializzo il vettore v_ricerca a -1 che indica che non e' stato trovato niente negli algoritmi di ricerca
    {
        v_ricerca[i]=-1;
    }
    int v_r[n]; //usato in ricerca dicotomica
    for(int i=0;i<n;i++)
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

    FILE *fp1; //file in cui stampare
    fp1=fopen("stampa.txt","w");
    if(fp1==NULL)
    {
        printf("errore apertura file in lettura\n");
        return -1;
    }

    do {
        printf( "\nInserisci un comando da tastiera tra: stampa; ordina; ricerca; termina. \n" );
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

                switch(key)
                {
                    case 1://tratte
                        for (i=0;i<n-1;i++)
                        {
                            posmin=i;
                            for(j=i+1; j<n; j++)
                            {
                                if(compara_tratta(punt_tratta[j],punt_tratta[posmin])<0)
                                {
                                    posmin=j;
                                }
                            }
                            scambio_punt(punt_tratta, i, posmin);
                        }
                        for (i=0; i<n; i++)
                        {
                            printf("%d %s %s %s %s %s %d \n",punt_tratta[i]->codice_tratta, punt_tratta[i]->luogo_partenza,punt_tratta[i]->luogo_arrivo,punt_tratta[i]->data,punt_tratta[i]->ora_p,punt_tratta[i]->ora_a,punt_tratta[i]->ritardo);

                        }
                        break;
                    case 2:   //partenza

                        for (i=0;i<n-1;i++)
                        {
                            posmin=i;
                            for(j=i+1; j<n; j++)
                            {

                                if(compara_char(punt_partenza[j]->luogo_partenza,punt_partenza[posmin]->luogo_partenza)<0)
                                {
                                    posmin=j;
                                }
                            }
                            scambio_char(punt_partenza, i, posmin);
                        }
                        flag_ordinato=1;
                        for (i=0; i<n; i++)
                        {
                            printf("%d %s %s %s %s %s %d \n",punt_partenza[i]->codice_tratta, punt_partenza[i]->luogo_partenza,punt_partenza[i]->luogo_arrivo,punt_partenza[i]->data,punt_partenza[i]->ora_p,punt_partenza[i]->ora_a,punt_partenza[i]->ritardo);
                        }

                        break;
                    case 3: //arrivo
                        for (i=0;i<n-1;i++)
                        {
                            posmin=i;
                            for(j=i+1; j<n; j++)
                            {

                                if(compara_char(punt_arrivo[j]->luogo_arrivo,punt_arrivo[posmin]->luogo_arrivo)<0)
                                {
                                    posmin=j;
                                }
                            }
                            scambio_char(punt_arrivo, i, posmin);
                        }
                        for (i=0; i<n; i++)
                        {
                            printf("%d %s %s %s %s %s %d \n",punt_arrivo[i]->codice_tratta, punt_arrivo[i]->luogo_partenza,punt_arrivo[i]->luogo_arrivo,punt_arrivo[i]->data,punt_arrivo[i]->ora_p,punt_arrivo[i]->ora_a,punt_arrivo[i]->ritardo);
                        }
                        break;
                    case 4: //ordinamento per data, a parita' di date ordina per ora di partenza
                        for (i=0;i<n-1;i++)
                        {
                            posmin=i;
                            for(j=i+1; j<n; j++)
                            {
                                if(compara_char(punt_data[j]->data,punt_data[posmin]->data)==0)
                                {
                                    if(compara_char(punt_data[j]->ora_p,punt_data[posmin]->ora_p)<0)
                                    {
                                        posmin=j;
                                        strcpy(temp,punt_data[i]->ora_p);
                                        strcpy(punt_data[i]->ora_p,punt_data[j]->ora_p);
                                        strcpy(punt_data[i]->ora_p,temp);
                                    }
                                }
                                else
                                {
                                    if(compara_char(punt_data[j]->data,punt_data[posmin]->data)<0)
                                    {
                                        posmin=j;
                                    }
                                }
                            }
                            scambio_char(punt_data, i, posmin);
                        }
                        for (i=0; i<n; i++)
                        {
                            printf("%d %s %s %s %s %s %d \n",punt_data[i]->codice_tratta, punt_data[i]->luogo_partenza,punt_data[i]->luogo_arrivo,punt_data[i]->data,punt_data[i]->ora_p,punt_data[i]->ora_a,punt_data[i]->ritardo);
                        }
                        break;
                    default: printf("errore");
                        break;
                }
                break;
            case 'r': //r sta per ricerca
                printf("Inserici da tastiera una citta' di partenza\n");
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
                    if(t==1)
                    {
                        printf("%d %s %s %s %s %s %d\n",array[risultato].codice_tratta, array[risultato].luogo_partenza, array[risultato].luogo_arrivo, array[risultato].data, array[risultato].ora_p, array[risultato].ora_a, array[risultato].ritardo );
                        //parto con una ricerca nell'intervallo superiore rispetto a m
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
                        //parto con una ricerca nell'intervallo inferiore rispetto a m
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
                        printf("Citta non trovata. \n");
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

void ricerca_lineare(elenco array[MAXR],int n,char k[MAXC],int *v_ricerca,int *l)
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
    if(flag==0)//caso in cui ricerco una citta non presente nel file
    {
        printf("Citta' non trovata\n");
    }
}
int ricerca_dicotomica(elenco *array, int p, int u,int m, char k[MAXC],int *l, int *flag)
{
    l=strlen(k);

    if(p>u)
    {
        return -1; //primo elemento e' maggiore dell'ultimo
    }
    m =(p+u)/2; //calcolo il punto medio tra gli estremi
    if(strncmp(k,array[m].luogo_partenza,l)==0) //se trovo citta'
    {
        *flag=1; //salvo che ho trovato almeno una volta la citta'
        return (m);//ritorno la posizione in cui e' stata trovata la citta'
    }
    if(strncmp(k,array[m].luogo_partenza,l)<0) //k e' prima in ordine alfabetico rispetto a array[m].luogo_partenza
    {
        return ricerca_dicotomica(array, p, m-1,m, k, &l, flag); //vado nella parte dx rispetto a m
    }
    return ricerca_dicotomica(array, m+1, u,m,k, &l, flag);//k viene dopo in ordine alfabetico rispetto a r[m].luogo_partenza
    //vado nella parte sx rispetto a m

}

void proseguimento_ricerca(elenco array[MAXR],int p, int s,char k[MAXC],int *v_ri,int *l) //dopo aver trovato m nella ricerca dicotomivěca
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

int compara_tratta(elenco *p1, elenco *p2)
{
    return (p1->codice_tratta - p2->codice_tratta);
    //si puo' anche scrivere: return ((*p1).codice_tratta - (*p2).codice_tratta);
}

void scambio_punt(elenco *punt_tratta[MAXR], int i, int j) //l'ordinamento avviene grazie a una struct temporanea
{
    elenco temp;

    temp=*punt_tratta[i];
    *punt_tratta[i]=*punt_tratta[j];
    *punt_tratta[j]=temp;
}

int compara_char(elenco *p1, elenco *p2)
{
    return strcmp(p1,p2);
}
void scambio_char(elenco *puntatore[MAXR], int i, int j)
{
    elenco temp;

    temp= *puntatore[i];
    *puntatore[i]=*puntatore[j];
    *puntatore[j]=temp;
}