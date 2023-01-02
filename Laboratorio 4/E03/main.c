#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#define N 1000
#define M 100
char *cercaRegexp(char *src, char *regexp);
int main() {
    // stringa regexp con all'interno la cosa da cercare
    char regexp[M] = "\\ar\\A[^aei]b.e[lm]i d. r\\a[^ade]ce";
    char src[N] = "I pra I prDoblemi di riicerca di stringhe all’interno di testi e collezioni di stringhe solitamente di dimensione maggiore rispetto alla stringa cercata si basano raramente su un confronto esatto ma molto spesso necessitano di rappresentare in modo compatto non una ma un insieme di stringhe cercate evitandone per quanto possibile l’enumerazione esplicita";
    char *punt;
    punt=cercaRegexp(src, regexp);
    if(punt==NULL)
        printf("codifica non trovata");
    else printf("codifica trovata!");
    /*COMMENTI SULLE SCELTE CHE HO FATTO:
     * ciò che c'è in regexp va rispettato, quindi se c'è uno spazio deve esserci anche nel testo e viceversa
     * ho misurato le stringhe per ridurre le dim dei cicli  (m e n)
     */


    return 0;
}
char *cercaRegexp(char *src, char *regexp){
    int n=strlen(src);
    int m=strlen(regexp);
    int j=0, start = 1,d;
    int iniz=0;
    int fleg = 0,i,t;
        for(d=0; d<n && fleg==0; d++){ // per ogni carattere di src io scandisco la stringa più piccola fino a che meccia

        iniz=d;
        j = d; t = 0;i=0; fleg = 1; // vero
        while (regexp[i] != '\0' && fleg == 1) { //leggo regexp per tutta la sua lunghezza

            if (isalpha(regexp[i])) { //caso carettere
                if (src[j] == regexp[i]) {
                    j++;
                    i++;
                } // carattere corrispondere a carattere, vai avanti
                else {
                    fleg = 0; //falso
                    break;
                } // falso
            } else { //esamino i casi con i metacaratteri
                if (regexp[i] == '[' && regexp[i + 1] == '^') {
                    i = i + 2;
                    for (i = i; regexp[i] != ']'; i++) {
                        if (src[j] == regexp[i]) {
                            fleg = 0;
                            break;
                        }
                    }
                    i++;  //salto la parentesi chiusa
                    j++; //aggiorno anche la j
                }

                if (regexp[i] == '[' && regexp[i + 1] != '^') {
                    i++;
                    for (i = i; regexp[i] != ']'; i++) {
                        if (src[j] == regexp[i]) { t = 1; } // t=1 trovato, mi basta che diventi vero una volta
                    }
                    if (t == 0) {//non è mai stato vero
                        fleg = 0;
                    }
                    t = 0; //rimetto a falso t
                    i++;
                    j++;
                }
                if (regexp[i] == '\\' && regexp[i + 1] == 'A') {
                    if(isalpha(src[j]) && (src[j]==toupper(src[j]))){
                        j++;
                        i=i+2;
                    }
                    else{fleg=0;}
                }
                if (regexp[i] == '\\' && regexp[i + 1] == 'a') {
                    if(isalpha(src[j]) && (src[j]==tolower(src[j]))){
                        j++;
                        i=i+2;
                    }
                    else{fleg=0;}
                }
                if (regexp[i] == '.') {// va bene qualunque carattere
                    if (isalpha(src[j])) {
                        i++;
                        j++;
                    }
                }
                if (isspace(regexp[i]) && isspace(src[j])) {
                    i++;
                    j++;
                } else if ((isspace(regexp[i]) && !isspace(src[j])) || (!isspace(regexp[i]) && isspace(src[j]))) {
                    fleg = 0;
                }
            }
        }
    }

    if (fleg==1) {
        char * p= &src[iniz-1]; //codifica trovata
        return p;
    }
    else
        return NULL; //codifica non trovata
}