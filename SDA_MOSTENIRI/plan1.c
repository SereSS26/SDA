#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 4

typedef struct{
    int linie;
    int coloana;
}coordonate;

coordonate pos[4];
coordonate a[MAX*MAX]; // Maximizează dimensiunea pentru cale
int lungime = 0;
int matrice[MAX][MAX] = { {2, 5, 8, 5},
                          {4, 4, 3, 7},
                          {1, 2, 8, 1},
                          {9, 3, 1, 8} };

void initializare() {
    pos[0].coloana = 0;
    pos[0].linie = -1;  // Sus
    pos[1].coloana = 1;
    pos[1].linie = 0;   // Dreapta
    pos[2].coloana = 0;
    pos[2].linie = 1;   // Jos
    pos[3].coloana = -1;
    pos[3].linie = 0;   // Stânga
}

int solutie(coordonate c) {
    if(c.coloana == 0 || c.linie == 0 || c.coloana == MAX - 1 || c.linie == MAX - 1) {
        return 1;  // Dacă am ajuns pe marginea matricei
    }
    return 0;
}

void afisare(int lungime) {
    int i;
    for(i = 0; i < lungime; i++) {
        printf("%d %d\n", a[i].linie, a[i].coloana);
    }
    printf("\n");
}

int acceptabil(coordonate c, coordonate urm) {
    if (urm.linie >= 0 && urm.coloana >= 0 && urm.linie < MAX && urm.coloana < MAX) {
        if (matrice[c.linie][c.coloana] > matrice[urm.linie][urm.coloana]) {  // Căutăm o cale unde valorile scad
            return 1;
        }
    }
    return 0;
}

void back(int x, int y) {
    coordonate aux;
    int i;

    // Salvăm poziția curentă în drumul parcurs
    a[lungime].linie = x;
    a[lungime].coloana = y;
    lungime++;

    // Verificăm dacă am ajuns la o soluție
    if(solutie(a[lungime - 1]) == 1) {
        afisare(lungime);
    } else {
        for(i = 0; i < 4; i++) {
            aux.coloana = a[lungime - 1].coloana + pos[i].coloana;
            aux.linie = a[lungime - 1].linie + pos[i].linie;
            if(acceptabil(a[lungime - 1], aux)) {
                back(aux.linie, aux.coloana);  // Continuă căutarea recursivă
            }
        }
    }
    lungime--;  // Întoarcere la pasul anterior (backtracking)
}

int main(void) {   
    initializare();  // Inițializăm direcțiile
    back(2, 2);  // Pornim căutarea de la poziția (2, 2)

    return 0;
}
