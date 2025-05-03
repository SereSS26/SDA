#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 200
#define LINIE 1000

typedef struct echipa{
    char nume[25];
    int puncte;
    int buget;
    char oras[25];
}echipa;
void citire(FILE *fis,echipa *echipe,int *numar_elemente)
{
    char buffer[LINIE];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        char *p=NULL;
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(echipe[*numar_elemente].nume,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            echipe[*numar_elemente].puncte=atoi(p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            echipe[*numar_elemente].buget=atoi(p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            strcpy(echipe[*numar_elemente].oras,p);
        }
        (*numar_elemente)++;
    }
}
void afisare(FILE *gis,echipa *echipe,int numar_elemente)
{
    int i=0;
    for(i=0;i<numar_elemente;i++)
    {
        fprintf(gis,"%s %d %d %s\n",echipe[i].nume,echipe[i].puncte,echipe[i].buget,echipe[i].oras);
    }
    fprintf(gis,"\n");
}
void swap(echipa* el1, echipa* el2)
{
	echipa tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void sortare1(echipa *echipe,int numar_elemente)
{
    int i=0,j=0,k=numar_elemente-1;
    for(i=0;i<numar_elemente;i++)
    {
        if(echipe[i].puncte>45)
        {
            swap(&echipe[i],&echipe[j]);
            j++;
            i--;
        }
        if(echipe[i].puncte<20&&i<=k)
        {
            swap(&echipe[i],&echipe[k]);
            k--;
            i--;
        }
    } 
}
void quicksort(echipa a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	echipa pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].puncte > pivot.puncte)
			stanga++;
		while (pivot.puncte > a[dreapta].puncte)
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
void sortare2(echipa *echipe,int numar_elemente)
{
    echipa *temp=NULL;
    int j=0,i=0;
    temp=(echipa*)malloc(numar_elemente*sizeof(echipa));
    if(temp==NULL)
    {
        perror("Eroare la alocarea memorie dinamice\n");
        exit(-1);
    }
    for(i=0;i<numar_elemente;i++)
    {
        if(echipe[i].buget<100)
        {
            temp[j]=echipe[i];
            j++;
        }
    }
    quicksort(temp,0,j-1);
    j=0;
    for(i=0;i<numar_elemente;i++)
    {
        if(echipe[i].buget<100)
        {
            echipe[i]=temp[j];
            j++;
        }
    }
    free(temp);
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("sortari5.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari5.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fiser iesire\n");
        exit(-1);
    }
    echipa echipe[MAX];
    int numar_elemente=0;
    citire(fis,echipe,&numar_elemente);
    sortare1(echipe,numar_elemente);
    afisare(gis,echipe,numar_elemente);
    sortare2(echipe,numar_elemente);
    afisare(gis,echipe,numar_elemente);
    fclose(fis);
    fclose(gis);

    return 0;
}