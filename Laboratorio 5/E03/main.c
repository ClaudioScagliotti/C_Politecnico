#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXC 30 //num max caratteri di ogni parolaa della riga
#define MAXR 1000
typedef struct { //struttura per conservare i record del file
    int codice_tratta;
    char luogo_partenza[MAXC];
    char luogo_arrivo[MAXC];
    char data[11];
    char ora_p[6]; //orario di partenza
    char ora_a[6]; //orario di arrivo
    int ritardo;

} elenco;
elenco *alloc_array(FILE *f, int *num_p);
elenco *alloc(int *num_p, elenco *array); // rifare con una sola funzione
//elenco *alloc_partenza(int *num_p, elenco *array);
//elenco *alloc_arrivo(int *num_p, elenco *array);
//elenco *alloc_data(int *num_p, elenco *array);


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
    int n, m, stampa, i, j, key, posmin, codice_tratta;
    int  prim, sec,lun, t;
    int flag_ordinato=0;
    char c[8],  citta[MAXC], ricerca[2], temp[MAXC], nome_file1[MAXC],nome_file2[MAXC];
    t=0; //e' il flag trovato della citta nella ricerca dicotomica
    FILE *fp2; //leggi corse.2
    FILE *fp3; //stampa corse.1
    FILE *fp1;  // leggi corse.1
    printf("Digita il nome del file su cui vuoi lavorare.\nPuoi scegliere tra i file: corse1.txt o corse2.txt\n");
    scanf("%s",nome_file1);
    fp1=fopen(nome_file1,"r");
    if(fp1==NULL)
    {
        printf("Errore apertura file in lettura. Controllare di aver digitato in modo corretto il nome del file o di averlo depositato nella directory del programma.\n");
        return -1;
    }

    elenco *array;//creazione della struct
    elenco **punt_tratta;
    elenco **punt_partenza;// copie parallele disordinate che conterranno ogni ordinamento
    elenco **punt_arrivo;
    elenco **punt_data;

   array=alloc_array(fp1, &n); //riempi array con quello che c'è nel file
   punt_tratta=alloc(&n,array);
   punt_partenza=alloc(&n,array);
   punt_arrivo=alloc(&n,array);
   punt_data=alloc(&n,array);


    int l=0,f=n-1, risultato; //usati per ricerca dicotomica
    int v_ricerca[n]; //usato in ricerca lineare
    for(int i=0;i<n;i++) //inizializzo il vettore v_ricerca a -1 che indica che non e' stato trovato niente negli algoritmi di ricerca
    {
        v_ricerca[i]=-1;
    }
    int v_r[n]; //usato in ricerca dicotomica
    for(int i=0;i<n;i++)
    {
        v_r[i]=-1;
    }
    fclose (fp1);

    fp3=fopen("stampa1.txt","w");
    if(fp3==NULL)
    {
        printf("errore apertura file \n");
        return -1;
    }


 do {
        printf( "\nInserisci un comando da tastiera tra: stampa; ordina; ricerca; file nuovo; termina. \n" );
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
                            fprintf(fp3,"%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo);
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
                            {   //quello che viene dopo - quello che viene prima, se è negativo scambio
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
                        flag_ordinato=1; //ora potro fare la ricerca dicotomica
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
                                    ricerca_lineare(array,n,citta,v_ricerca,&lun); //qui salvo in v_ricerca le posizioni,di tutte le volte in cui trovo la città
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
                                    if(t==1)//trovato
                                     {
                                          printf("%d %s %s %s %s %s %d\n",array[risultato].codice_tratta, array[risultato].luogo_partenza, array[risultato].luogo_arrivo, array[risultato].data, array[risultato].ora_p, array[risultato].ora_a, array[risultato].ritardo );
                                          //parto con una ricerca nell'intervallo superiore rispetto a m
                                          prim=0, sec=risultato;
                                          proseguimento_ricerca(array,prim,sec,citta,v_r,&lun);// cerco se ce ne sono altri sopra

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
            case 'f': //t sta per termina
                flag_ordinato=0;
                printf("Digita il nome del file su cui vuoi lavorare.\nPuoi scegliere tra i file: corse1.txt o corse2.txt\n");
                scanf("%s",nome_file2);
                fp2=fopen(nome_file2,"r");
                if(fp2==NULL)
                {
                    printf("errore apertura file\n");
                    return -1;
                }
                //per liberare le malloc dei puntatori devo prima liberare la malloc a cui loro puntano, ovvero la malloc array
                free(array);
                free(punt_tratta);
                free(punt_partenza);
                free(punt_arrivo);
                free(punt_data);
                array=alloc_array(fp2, &n);
                punt_tratta=alloc(&n,array);// una sola funzione
                punt_partenza=alloc(&n,array);
                punt_arrivo=alloc(&n,array);
                punt_data=alloc(&n,array);
                for (i=0; i<n; i++)
                {
                            printf("%d %s %s %s %s %s %d\n",array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, array[i].ritardo );
                }
               fclose (fp2);
                break;
            default:
                printf("Comando non valido.\n");
                break;
        }
    } while (c[0]!='t');

    fclose (fp3);
    return 0;
}

elenco *alloc_array(FILE *f, int *num_p)
{
    int n;
    elenco *array;
    fscanf( f, "%d", &n ); // numero di corse
    array=(elenco *)malloc(n * sizeof(elenco));
    if(array==NULL) //controllo su array
    {
            printf("errore2");
            exit(-1);
    }
    //allocameto del file dentro array
    for ( int i = 0; i < n; i++ )
    {
        fscanf( f,"%d %s %s %s %s %s %d",&array[i].codice_tratta, array[i].luogo_partenza, array[i].luogo_arrivo, array[i].data, array[i].ora_p, array[i].ora_a, &array[i].ritardo );
    }
   *num_p=n;//riporto il numero di corse

return array;
}


elenco *alloc(int *num_p, elenco *array)
{
    elenco **punt_generico;

    punt_generico=(elenco **)malloc(*num_p * sizeof(elenco*));
    if(punt_generico==NULL)//controllo su puntatore a punt_tratta
    {
            printf("errore1");
            exit(-1);
    }
    //associo a cosa deve puntare punt_tratta
    for (int i=0; i<=*num_p; i++)
    {
       punt_generico[i]= &array[i];
    }
   return punt_generico;
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

void proseguimento_ricerca(elenco array[MAXR],int p, int s,char k[MAXC],int *v_ri,int *l) //dopo aver trovato m nella ricerca dicotomiv�ca
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
