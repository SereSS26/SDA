#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 4

typedef struct coordonate
{
   int linie, coloana;
}coordonate;
coordonate pos[4];
coordonate a[N * N];
int matrice[N][N] = { {-1,-1,0,-1},
				      {-1,0,0,-1},
				      {-1,2,0,0},
				      {-1,0,-1,-1} };

int energie=1;
int temp=0;
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

int solutie(int k, coordonate c)
{
	if (c.coloana == 0 || c.linie == 0 || c.coloana == N - 1 || c.linie == N - 1) //daca am ajuns la margine
		return 1;
	else
		return 0;
}
int acceptabil(coordonate c,int k)
{
    if(energie>0&& matrice[c.linie][c.coloana]!=-1&& c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N)
    {
        int i=0;
        for(i=0;i<k;i++)
        {
            if(a[i].linie==c.linie&&a[i].coloana==c.coloana)
                return 0;
            return 1;
        }
    }
    return 0;
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
		for (i = 0; i < 4; i++)  // parcurgem pe rand posibilitatile
		{
			aux.coloana = a[k - 1].coloana + pos[i].coloana;
			aux.linie = a[k - 1].linie + pos[i].linie;
			if (acceptabil(aux,k))
            {       
                a[k] = aux;
                int consum=1;
                if(matrice[a[k].linie][a[k].coloana]>0)
                {
                    consum=consum-matrice[a[k].linie][a[k].coloana];
                }
                energie=energie-consum;
                temp=matrice[a[k].linie][a[k].coloana];
				matrice[a[k].linie][a[k].coloana] = -1; //marcheaza ca vizitat
				labirint(k + 1);     // back1(posibilitate_k+1)
				matrice[a[k].linie][a[k].coloana] = temp; //sterge marcajul ca vizitat
                energie=energie+consum;
			}
		}
	}
}   /*labirint*/
int main(void)
{
    initializare();
    a[0].linie=1;
    a[0].coloana=1;
    matrice[a[0].linie][a[0].coloana] = -1; //marchez ca vizitat
    labirint(1);

    return 0;
}