#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
#define LINIE 1000
#define AN_CURENT 2025

typedef struct agenda{
    char nume[25];
    char telefon[10];
    int an;
    int venit;
}agenda;
void citire(FILE *fis,agenda *agende,int *numar_elemente)
{
    char buffer[LINIE];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        char *p=NULL;
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(agende[*numar_elemente].nume,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(agende[*numar_elemente].telefon,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            agende[*numar_elemente].an=atoi(p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            agende[*numar_elemente].venit=atoi(p);
        }
        (*numar_elemente)++;
    }
}
void afisare(FILE *gis,agenda *agende,int numar_elemente)
{
    int i=0;
    for(i=0;i<numar_elemente;i++)
    {
        fprintf(gis,"%s %s %d %d\n",agende[i].nume,agende[i].telefon,agende[i].an,agende[i].venit);
    }
    fprintf(gis,"\n");
}
void swap(agenda* el1, agenda* el2)
{
	agenda tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void sortare1(agenda *agende,int numar_elemente)
{
    int i=0,j=numar_elemente-1;
    int ok=0;
    for(i=0;i<numar_elemente;i++)
    {
        if(ok==2)
            return;
        if(i>j)
            return;
        if(agende[i].venit<1000)
        {
            swap(&agende[i],&agende[j]);
            j--;
            ok++;
        }
    }
}
void quicksort(agenda a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	agenda pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (strcmp(a[stanga].nume,pivot.nume))
			stanga++;
		while (strcmp(pivot.nume,a[dreapta].nume))
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
		quicksort(a, prim, dreapta - 1);
	if (dreapta + 1 < ultim)
		quicksort(a, dreapta + 1, ultim);
}
void sortare2(agenda *agende,int numar_elemente)
{
    agenda *temp=NULL;
    int i=0;
    int j=0;
    temp=(agenda*)malloc(numar_elemente*sizeof(agenda));
    if(temp==NULL)
    {
        perror("Eroare la alocarea dinaica a meoriei\n");
        exit(-1);
    }
    for(i=0;i<numar_elemente;i++)
    {
        if(AN_CURENT-agende[i].an>=30&&AN_CURENT-agende[i].an<=40)
        {
            temp[j]=agende[i];
        }
    }
    quicksort(temp,0,j-1);
    j=0;
    for(i=0;i<=numar_elemente;i++)
    {
        if(AN_CURENT-agende[i].an>=30&&AN_CURENT-agende[i].an<=40)
        {
            agende[i]=temp[j];
            j++;
        }
    }
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("sortari2.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari2.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fiser iesire\n");
        exit(-1);
    }
    agenda agende[MAX];
    int numar_elemente=0;
    citire(fis,agende,&numar_elemente);
    sortare1(agende,numar_elemente);
    afisare(gis,agende,numar_elemente);
    sortare2(agende,numar_elemente);
    afisare(gis,agende,numar_elemente);
    fclose(fis);
    fclose(gis);

    return 0;
}