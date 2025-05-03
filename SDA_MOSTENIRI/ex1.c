#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
//MAX e dimeniunea maxima a strcuturi
#define LINIE 500
//LINIE e dimesiunea unei linii citite din fiser

typedef struct agenda{
    char nume[25];
    char telefon[10];
    int an;
    int venit;
}agenda;
//strcutura agenda contine cele 4 campuri din enunt:nume,telefon,an si venit

void citire(FILE *fis,agenda *oameni,int *numar_oameni)//functie de citire a datelor din fisier
{
    char buffer[LINIE];//linie buffer pentru citire din fisier
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)//cat timp facem citire din fisier prelucram apoi datele
    {
        buffer[strcspn(buffer,"\n")]='\0';//scoatem din buffer '\n"
        char *p=NULL;//folosim token pentru spargere in campuri a lui buffer
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(oameni[*numar_oameni].nume,p);//luam valoare pentru nume
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(oameni[*numar_oameni].telefon,p);//luam valoare pentru telefon
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            oameni[*numar_oameni].an=atoi(p);//luam valoare pentru an
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            oameni[*numar_oameni].venit=atoi(p);//luam vloare pentru venit
        }
        (*numar_oameni)++;//actualizam numar de elemente
    }
}
void afisare(agenda *oameni,int numar_oameni)//functie de afisare
{
    int i=0;
    for(i=0;i<numar_oameni;i++)
    {
        printf("%s %s %d %d\n",oameni[i].nume,oameni[i].telefon,oameni[i].an,oameni[i].venit);//afiassm datele
    }
    printf("\n");
}

void swap(agenda* el1, agenda* el2)//functie de interschi,varte a doua elemnte folosnd metoda paharelor
{
	agenda tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void sortare1(agenda *oameni,int numar_oameni)//creinta 1
{
    int i=0,j=numar_oameni-1;
    for(i=0;i<numar_oameni;i++)//parcurgem strcutura
    {   
        if(i>j)//daca am ajuns in zona de lemete asezate la final ne oprim 
            break;
        if(oameni[i].venit<1000)//daca gasim elemte care convin le punem la final 
        {
            swap(&oameni[i],&oameni[j]);
            j--;
        }
    }
    //complexitate linira O(n)
}
void quicksort(agenda a[], int prim, int ultim)//functie quicksort preluata din implemntari laborator
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);//interschimbare
	//mutare pivot pe prima pozitie
	agenda pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (strcmp(a[stanga].nume,pivot.nume)<0)//comparar
			stanga++;
		while (strcmp(pivot.nume,a[dreapta].nume)<0)//comparare
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);//interschimbare
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		quicksort(a, prim, dreapta - 1);//apel recursiv
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);//apel rexursiv
}
void sortare2(agenda *oameni,int numar_oameni)//cerinta 2
{
    agenda *temp=NULL;//strcutra auxiliara
    temp=(agenda*)malloc(sizeof(agenda)*numar_oameni);//aloc memorie
    if(temp==NULL)//verificare alocare dinamica
    {
        perror("Eroare la alocarea memoriei dinamice\n");
        exit(-1);
    }
    int i=0;
    int nr=0;
    for(i=0;i<numar_oameni;i++)//aleg elemtele care convin
    {
        if(oameni[i].an>=30&&oameni[i].an<=40)
        {
            temp[nr]=oameni[i];
            nr++;
        }
    }
    quicksort(temp,0,nr-1);//le sortez,complexitate O(n*logn)
    nr=0;
    for(i=0;i<numar_oameni;i++)//le repun in strcuta initalia
    {
        if(oameni[i].an>=30&&oameni[i].an<=40)
        {
            oameni[i]=temp[nr];
            nr++;
        }
    }
    free(temp);//eliberez memoria alocata dinamic
}
int main(void)
{   
    FILE *fis=NULL;//fisier de intrare pentru citire data
    fis=fopen("ex1.txt","r");//deschidem fisier
    if(fis==NULL)//verificare deschidere fisier
    {
        perror("Eroare la deschiderea fisierului\n");
        exit(-1);
    }
    agenda oameni[MAX];//structura oameni in care salvam datele din fisier
    int numar_oameni=0;//numarul de elemente
    citire(fis,oameni,&numar_oameni);//functie de citire
    afisare(oameni,numar_oameni);//functie de afiasre
    printf("\n\n");

    sortare1(oameni,numar_oameni);//primul ex
    afisare(oameni,numar_oameni);//functie de afisare
    printf("\n\n");

    sortare2(oameni,numar_oameni);//al doilea ex
    afisare(oameni,numar_oameni);//functie de afisare

    fclose(fis);//inchidem fisier

    return 0;
}