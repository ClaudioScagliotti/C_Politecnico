#include <stdio.h>

int maj ( int *a, int iniz, int fine ) {

    if ( iniz == fine-1 ) // se ho solo due elementi
        if ( a[iniz] == a[fine] ) return a[iniz]; // se sono uguali l'elemento è maggiorante
        else return -1; // se sono diversi non ho un maggiorante, caso terminale solo se ho un vettore di dim pari
    else if ( iniz == fine ) // se ho solo un elemento è maggiorante
        return a[iniz]; // quindi ritorno quel valore, caso che capita se ho un vettore di dim dispari

    // faccio la ricorsione
    int meta=(iniz+fine)/2;
    int u = maj( a, iniz, meta ); // prima metà del vettore
    int v = maj( a, (meta+1), fine ); // seconda metà del vettore

    if ( u == v )  return u;  // se sono uguali ne ritorno uno dei due
    else {                       // non ho ancora trovato il maggiorante, devo fare un controllo, so che se
                                // c'è è uno tra u e v

        // inizializzo le variabili per il ciclo for
        int i, len = (fine-iniz)+1;
        int c1 = 0, c2 = 0;

        for ( i = iniz; i <= fine; i++ ) { // ciclo il sottovettore attuale da inf fino a sup
            if ( u == a[i] ) c1++; // se e1 è uguale aumento c1
            if ( v == a[i] ) c2++; // se e2 è uguale aumento c2
        }

        // finiti i cicli ho i due contatori per e1 ed e2
        if ( c1 > len/2 && c2 <= len/2 ) return u;
        else if ( c2 > len/2 && c1 <= len/2 ) return v;
        else return -1;

    }
}

int majority ( int *a, int N ) {
    int start = 0;
    int end = N-1;
    return maj( a, start, end );
}

int main (void) {

    int i, N = 7;
    int v[N];
printf("inserisci vettore:\n");
    for ( i = 0; i < N; i++ )
        scanf( "%d", &v[i] );

    printf( "\nMagg: %d", majority( v, N ) );

    return 0;
}
