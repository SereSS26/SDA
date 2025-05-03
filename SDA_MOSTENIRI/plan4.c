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
int matrice[N][N] = { {1,1,1,1},
				   {1,0,0,1},
				   {1,0,1,0},
				   {1,0,0,1} };

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

int obiecte=0;

int acceptabil(coordonate c)
{
	if (matrice[c.linie][c.coloana] == 1 && c.linie >= 0 && c.coloana >= 0 && c.linie < N && c.coloana < N) //daca este liber si coordonata se afla in dimensiunile matricei
		return 1;
	else return 0;
}
void labirint(int x,int y)  //k pasul, c coordonata curenta
{
	int i; coordonate aux;
    matrice[x][y]=2;
	
		for (i = 0; i < 4; i++)  // parcurgem pe rand posibilitatile
		{
			aux.coloana = y + pos[i].coloana;
			aux.linie = x + pos[i].linie;
			if (acceptabil(aux)) {//daca posibilitatea  e acceptabila
				labirint(aux.linie,aux.coloana);     // back1(posibilitate_k+1)
			}
		}
	
}   /*labirint*/
int main(void)
{       
    initializare();
    int i=0;
    int j=0;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            if(matrice[i][j]==1)
            {
                obiecte++;
                labirint(i,j);
            }
        }
    }
    printf("%d\n",obiecte);

    return 0;
}