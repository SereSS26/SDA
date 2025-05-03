#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100

void citire(FILE *fis,int a[],int *numar_elemente)
{   
    int aux=0;
    while(fscanf(fis,"%d",&aux)!=EOF)
    {
        a[*numar_elemente]=aux;
        (*numar_elemente)++;
    }
}
void afisare(FILE *gis,int a[],int numar_elemente)
{
    int i=0;
    for(i=0;i<numar_elemente;i++)
    {
        fprintf(gis,"%d ",a[i]);
    }
    fprintf(gis,"\n");
}
void swap(int* el1, int* el2)
{
	int tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
int sortare1(int a[],int numar_elemente)
{
    int i=0,j=0;
    for(i=0;i<numar_elemente;i++)
    {
        if(a[i]<0)
        {
            swap(&a[i],&a[j]);
            j++;
        }
    }
    return j;
}
void sortare2(int a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	int pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga] < pivot)
			stanga++;
		while (pivot < a[dreapta])
			dreapta--;
		if (stanga < dreapta)
			swap(&a[stanga++], &a[dreapta--]);
		else
			stanga++;
	}
	//mutare pivot la locul sau final
	swap(&a[dreapta], &a[prim]);
	//apelurile recursive
	if (prim < dreapta - 1)
		sortare2(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		sortare2(a, dreapta + 1, ultim);
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("sortari1.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari1.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
        exit(-1);
    }
    int a[MAX];
    int numar_elemente=0;
    int inceput=0;
    citire(fis,a,&numar_elemente);
    inceput=sortare1(a,numar_elemente);
    afisare(gis,a,numar_elemente);
    sortare2(a,inceput,numar_elemente-1);
    afisare(gis,a,numar_elemente);
    fclose(fis);
    fclose(gis);

    return 0;
}