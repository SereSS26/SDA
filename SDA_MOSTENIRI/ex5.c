#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define INFINIT 1000

#define N 3

typedef struct coordonate
{
int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { {1,0,1},
				   {0,2,1},
				   {1,0,0}};

void initializare() //int pos[] variabila globala
{	//initializarea posibilitatilor de deplasare Posibilitățile de deplasare sunt Nord, Est, Sud, Vest
	pos[0].coloana = 0; // Nord
	pos[0].linie = -1;// y scade spre Nord
	pos[1].coloana = 1; // Est – x creste spre Est
	pos[1].linie = 0;
	pos[2].coloana = 0; // Sud
	pos[2].linie = 1; // y creste spre Sud
	pos[3].coloana = -1;// Vest – x scade spre Vest
	pos[3].linie = 0;
}

int temp=0;
int solutie(int k, coordonate c)
{
	if (c.coloana == 0 || c.linie == 0 || c.coloana == N - 1 || c.linie == N - 1) //daca am ajuns la margine
		return 1;
	else
		return 0;
}
int acceptabil(coordonate c)
{
	if (matrice[c.linie][c.coloana] < temp && c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N) //daca este liber si coordonata se afla in dimensiunile matricei
		return 1;
	else return 0;
}
void afiseaza_solutia(int k)
{
    int i=0;
    for(i=0;i<k;i++)
    {
        printf("%d %d\n",a[i].linie,a[i].coloana);
    }
    printf("\n");
}
void labirint(int k)  //k pasul, c coordonata curenta
{
	int i; coordonate aux;
	if (solutie(k, a[k - 1]))        //solutie completa
		afiseaza_solutia(k);
	else
	{   
        temp=matrice[a[k].linie][a[k].coloana];
        matrice[a[k].linie][a[k].coloana] = 1000; //marchez ca vizitat
		for (i = 0; i < 4; i++)  // parcurgem pe rand posibilitatile
		{
			aux.coloana = a[k - 1].coloana + pos[i].coloana;
			aux.linie = a[k - 1].linie + pos[i].linie;
			if (acceptabil(aux)) {//daca posibilitatea  e acceptabila
				a[k] = aux;
				matrice[a[k].linie][a[k].coloana] = 1000; //marcheaza ca vizitat
				labirint(k + 1);     // back1(posibilitate_k+1)
			}
		}
	}
}   /*labirint*/
int main(void)
{   
    initializare();
	a[0].linie=1;
    a[0].coloana=2;
    temp=matrice[a[0].linie][a[0].coloana];
	labirint(1);
    return 0;
}