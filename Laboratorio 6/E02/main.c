#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>
#define MAXC 50

// s sta per struct T per tpo
struct Sinfo //struct delle tue info su anagrafe
{
    char codice[6];
    char nome[MAXC];
    char cognome[MAXC];
    char data_di_nascita[11];
    char via[MAXC];
    char citta[MAXC];
    int cap;
};
typedef struct Sinfo Tinfo;  //assegni un nome alla struct che contiene le tue informazioni di anagrafe


struct Snode //crei struct del nodo
{
    Tinfo info;
    struct Snode *link;
};
typedef struct Snode Tnode; //assegni nome alla struct nodo
typedef Tnode *Tlist; //nodo successivo


Tlist crea_lista();
Tinfo leggi_ifo_tastiera();
Tlist inserisci_elemento(Tlist lista,Tinfo info);
Tinfo leggi_ifo_file(FILE *fp,Tlist lista);

void stampa_lista_video(Tlist lista);
void stampa_lista_file(FILE *fp,Tlist lista);

Tlist cancella_prec(Tlist lista, char data_p[10]);
Tlist cancella_succ(Tlist lista, char data_s[10]);


int main()
{
    Tlist lista;
    Tinfo info;
    Tnode* nodo;
    Tlist head;
    Tlist p,s; //precedente e successivo
    Tlist pr,su,cu;//precedente , successivo e corrente
    head=NULL;
    int i, dim,comando,flag_trovato=0,flag_uscita=0;
    char data_p[10];//data prima
    char data_s[10];//data seconda
    char elem[6];
    char canc[6];
    FILE*fp1;
    FILE* fp2;

    //crea una lista vuota
    lista=crea_lista();

    do
        {
            printf("Inserisci il numero corrispondente al comando che vuoi eseguire: \n-digita 1 per inserimento dati da tastiera;\n-digita 2 per inserimento dati da file;\n-digita 3 per ricerca per codice di un elemento;\n-digita 4 per cancellazione di un elemento in base al codice;\n-digita 5 per cancellazione di tutti gli elementi compresi tra due date;\n-digita 6 per stampa la lista a video;\n-digita 7 per stampa la lista su file;\n-digita 8 per termina.\n");
            scanf("%d",&comando);

            switch(comando)
            {
            case 1://inserimento tastiera

                printf("Quanti elementi vuoi inserire da tastiera?");
                scanf("%d",&dim);

                for(i=0; i<dim;i++)
                {
                   //leggi e inserisci elemento
                   info=leggi_ifo_tastiera();
                   lista=inserisci_elemento(lista,info);
                }
                head=lista;
                break;
            case 2://inserimento da file

                fp1=fopen("anagrafica.txt","r");
                if(fp1==NULL)
                {
                    printf("errore apertura file in lettura\n");
                    return -1;
                }

                info=leggi_ifo_file(fp1,lista);
                lista=inserisci_elemento(lista,info);

                    while(!feof(fp1))
                    {
                       info=leggi_ifo_file(fp1,lista);
                       if (!feof(fp1))
                        {
                            lista=inserisci_elemento(lista,info);
                        }
                    }
                head=lista;

                fclose(fp1);
                break;
            case 3://ricerca per codice

                printf("Inserisci elemento da cercare:\n");
                scanf("%s",elem);

                for(lista=head; lista!=NULL; lista=lista->link)
                {
                   if(strcmp(elem,lista->info.codice)==0)
                   {
                       flag_trovato=1;
                       printf("Codice trovato nella lista:\n");
                       printf("%s %s %s %s %s %s %d\n\n",  lista->info.codice, lista->info.nome,lista->info.cognome,lista->info.data_di_nascita,lista->info.via,lista->info.citta,lista->info.cap);
                   }
                }
                if(flag_trovato==0)
                {
                     printf("Codice NON trovato nella lista\n");
                }
                flag_trovato=0;//rinizzializzo flag per prossima ricerca
                 lista=head;
                break;
            case 4://cancellazione elemento in base al codice
                printf("Inserisci elemento che vuoi cancellare in base al codice:\n");
                scanf("%s",canc);
                pr=NULL;
                cu=lista;
                for(lista=head; lista!=NULL, flag_uscita==0; lista=lista->link)
                {

                   pr=cu;
                   cu=lista;
                   su=cu->link;
                   if(strcmp(canc,lista->info.codice)==0)
                   {
                       flag_trovato=1;
                       printf("L'elemento che vuoi cancellare dalla lista e':\n");
                       printf("%s %s %s %s %s %s %d\n\n",  lista->info.codice, lista->info.nome,lista->info.cognome,lista->info.data_di_nascita,lista->info.via,lista->info.citta,lista->info.cap);

                       printf("%s = codice precedente\n",pr->info.codice);
                       printf("%s = codice corrente\n",cu->info.codice);
                       printf("%s = codice successivo\n",su->info.codice);

                       if(pr==cu)//l'elemento che voglio cancellare e' il primo della lista
                       {
                           head=su; //la mia lista partira dal successivo
                       }
                       else//l'elemento che voglio cancellare si trova a meta lista
                        {
                            pr->link=cu->link;//supero elemento corrente per poi andarlo a cancellare con free
                        }
                       free(cu);

                       printf("La nuova lista senza l'elemento cancellato e':\n");
                       for(lista=head; lista!=NULL; lista=lista->link)
                       {
                         printf("%s %s %s %s %s %s %d\n",  lista->info.codice, lista->info.nome,lista->info.cognome,lista->info.data_di_nascita,lista->info.via,lista->info.citta,lista->info.cap);
                       }
                       lista=head;
                       flag_uscita=1;
                       printf("\n");
                       break;

                   }
                }
                if(flag_trovato==0)
                {
                     printf("Codice NON trovato nella lista\n");
                }
                flag_trovato=0;

                break;
            case 5://cancellazione di tutti gli elementi compresi tra due date
                printf("Inserisci la prima data da cui partire a cancellare:\n");
                scanf("%s",data_p);
                p=cancella_prec(lista,  data_p);

                printf("Inserisci la seconda data di termine della cancellazione:\n");
                scanf("%s",data_s);
                if((strcmp(data_p,data_s)==0)||(strcmp(data_p,data_s)>0))
                {
                    printf("ERRORE la seconda data deve essere  inferiore della prima.\n");
                    break;
                }

                s=cancella_succ(lista,  data_s);


                if(p==NULL)
                {
                    head=s;
                }
                else
                    {
                        p->link=s;
                    }


                printf("\n");
                //stampa_lista_video(lista);
                for(lista=head; lista!=NULL; lista=lista->link)
                       {
                         printf("%s %s %s %s %s %s %d\n",  lista->info.codice, lista->info.nome,lista->info.cognome,lista->info.data_di_nascita,lista->info.via,lista->info.citta,lista->info.cap);
                       }
                printf("\n");
                 lista=head;
                break;
            case 6://stampa la lista a video
                 printf("\n");
                 stampa_lista_video(lista);
                 printf("\n");
                break;
            case 7://stampa lista su file
                fp2=fopen("stampa.txt","w");
                if(fp2==NULL)
                {
                    printf("errore apertura file in scrittura\n");
                    return -1;
                }
                 printf("\n");
                 printf("E' stata stampata la lista su file, digitare 8 per poi controllare.");
                 stampa_lista_file(fp2,lista);
                 printf("\n");

                 fclose(fp2);
                break;
            case 8://termina
                break;
            default:
                printf("comando errato\n");
                    break;

            }
        }while(comando!=8);

    return 0;
}

// funz che crea la lista vuota
Tlist crea_lista(){
return NULL;
}
//funz che legge da tastiera le info
Tinfo leggi_ifo_tastiera()
{
    Tinfo info;
    printf("Inserisci codice nel formato AXXXX dove X e' un cifra da 0 a 9:");
    scanf("%s",info.codice);

    printf("Inserisci nome:");
    scanf("%s",info.nome);

    printf("Inserisci cognome:");
    scanf("%s",info.cognome);

    printf("Inserisci data di nascita nel formato aaaa/mm/gg:"); //IL FORMATO DELLA DATA NON ORDINA PER GG/MM/AAAA COME RICHIESTO DAL TESTO MA ORDINA PER AAAA/MM/GG
    scanf("%s",info.data_di_nascita);

    printf("Inserisci via senza spazi:");
    scanf("%s",info.via);

    printf("Inserisci citta':");
    scanf("%s",info.citta);

    printf("Inserisci cap:");
    scanf("%d",&info.cap);
    return info;
}

Tinfo leggi_ifo_file(FILE *fp,Tlist lista)
{
    Tinfo info;

    fscanf(fp,"%s %s %s %s %s %s %d",info.codice,info.nome,info.cognome,info.data_di_nascita,info.via,info.citta,&info.cap);

    return info;
}

//INSERIMENTO DI ELEMENTI IN MODO ORDINATO ALL'interno della lista
Tlist inserisci_elemento(Tlist lista,Tinfo info)
{
     int a;
     Tlist prec,curr, newnode; //curr sta per corrente
     prec=NULL;
     curr=lista;//primo nodo lista
     //FASE 1 ricerca della posizione
     //scorro lista

     while(curr!=NULL &&  (strcmp(info.data_di_nascita , (curr->info).data_di_nascita))<0 )
     {
         prec=curr;
         curr=curr->link; //curr si sposta al nodo successivo
     }
     //FASE 2 allocazione dinamica
     newnode=(Tnode *)malloc(sizeof(Tnode));
     assert (newnode!=NULL); //comando di verifica assegnazione malloc
     newnode->info=info;
     //FASE 3 aggiornamento collegamenti
     if(prec==NULL) //nodo precedente e' uguale a null vuol dire che la posizione e' quella di testa(lista era vuota)
     {
        newnode->link=lista;
        lista=newnode;
        return  lista;
     }
     else //inserisco in posizione centrale o in coda
        {
            prec->link=newnode; //qui newnode e' quello centrale
            newnode->link=curr;
            return lista;
        }
}

void stampa_lista_video(Tlist lista)
{
    Tlist curr;//Tnode *curr ???? //curr e' il primo nodo della lista
    //curr sta per elemento corrente
    //devo stampare il campo info di ogni nodo che sto visitando e poi spostatrci al nodo successivo
    //tutto questo finchè curr!=NULL
    //questo perche una volta che arriviamo a un nodo NULL vuol dire che e' terminata la lista
    curr=lista;
    //lista e' il puntatore al primo nodo della struttura dati, quindi lo imposto a curr
    while(curr!=NULL)
    {
         // si puo' anche scrivere come: stampa_info(curr->info);
         printf("%s %s %s %s %s %s %d\n",  curr->info.codice, curr->info.nome,curr->info.cognome,curr->info.data_di_nascita,curr->info.via,curr->info.citta,curr->info.cap);
        curr=curr->link;
    }
}

void stampa_lista_file(FILE *fp,Tlist lista)
{

    Tlist curr; //curr e' il primo nodo della lista
    //curr sta per elemento corrente
    //devo stampare il campo info di ogni nodo che sto visitando e poi spostatrci al nodo successivo
    //tutto questo finchè curr!=NULL
    //questo perche una volta che arriviamo a un nodo NULL vuol dire che e' terminata la lista
    curr=lista;
    //lista e' il puntatore al primo nodo della struttura dati, quindi lo imposto a curr
    while(curr!=NULL)
    {
        fprintf(fp,"%s %s %s %s %s %s %d\n", curr->info.codice, curr->info.nome,curr->info.cognome, curr->info.data_di_nascita,curr->info.via,curr->info.citta,curr->info.cap);
        curr=curr->link;
    }
}


Tlist cancella_prec(Tlist lista, char data_p[10])
{
     Tlist prec,curr, succ; //curr sta per corrente
     prec=NULL;
     curr=lista;
     succ=curr->link;
     //scorro lista

     while(curr!=NULL &&  (strcmp(data_p, (curr->info).data_di_nascita))<0 )
     {
         prec=curr;
         curr=curr->link; //curr si sposta al nodo successivo
     }
     //elemento trovato
     if((strcmp(data_p,curr->info.data_di_nascita)==0)||(strcmp(data_p,curr->info.data_di_nascita)>0))
     {


         if(prec==NULL)//elem trovato in testa
         {

         }
         else//elem al centro. punt a nodo precedente deve puntare al puntatore del nodo successivo
            {
                prec->link=curr->link;
            }
         free(curr);
     }
    return prec;
}


Tlist cancella_succ(Tlist lista, char data_s[10])
{
     Tlist prec,curr,succ; //curr sta per corrente
     prec=NULL;
     curr=lista;

    while(curr!=NULL &&  (strcmp(data_s, (curr->info).data_di_nascita))<0 )//vai fino a quando trovi dat_s
    {
         prec=curr;
         curr=curr->link; //curr si sposta al nodo successivo
    }

    if(curr==NULL)
         {
             succ=NULL;
             return succ;
         }

        //e' uguale?
         if(strcmp(data_s,curr->info.data_di_nascita)==0)
     {

         if(curr->link==NULL)
         {
             succ=NULL;
             return succ;
         }
         else
            {
                succ=curr->link;
                return succ;
            }
     }
    if(strcmp(data_s,curr->info.data_di_nascita)>0)
    {
        succ=curr;
        return succ;
    }
    return succ;
}
