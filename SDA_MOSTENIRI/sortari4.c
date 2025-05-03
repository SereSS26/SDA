#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 100
#define LINIE 1000

typedef struct student{
    char nume[25];
    int varsta;
    int premiu;
}student;

void citire(FILE *fis,student *studenti,int *numar_elemente)
{
    char buffer[LINIE];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        char *p=NULL;
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(studenti[*numar_elemente].nume,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            studenti[*numar_elemente].varsta=atoi(p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            if(strcmp(p,"DA")==0)
            {
                studenti[*numar_elemente].premiu=1;
            }
            else
            {
                studenti[*numar_elemente].premiu=0;
            }
        }
        (*numar_elemente)++;
    }
}
void afisare(FILE *gis,student *studenti,int numar_elemente)
{
    int i=0;
    for(i=0;i<numar_elemente;i++)
    {
        fprintf(gis,"%s %d %d\n",studenti[i].nume,studenti[i].varsta,studenti[i].premiu);
    }
    fprintf(gis,"\n");
}
void swap(student* el1, student* el2)
{
	student tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
int sortare1(student *studenti,int numar_elemente)
{
    int i=0,j=0;
    for(i=0;i<numar_elemente;i++)
    {
        if(studenti[i].premiu==1)
        {
            swap(&studenti[i],&studenti[j]);
            j++;
        }
    }
    return j;
}
void sortare2(student a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	student pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (strcmp(a[stanga].nume,pivot.nume)<0)
			stanga++;
		while (strcmp(pivot.nume,a[dreapta].nume)<0)
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
    fis=fopen("sortari4.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari4.out","w");
    if(gis==NULL)
    {
        perror("Eroare la desschidere fisier iesire\n");
        exit(-1);
    }
    student studenti[MAX];
    int numar_elemente=0;
    int inceput=0;
    citire(fis,studenti,&numar_elemente);
    inceput=sortare1(studenti,numar_elemente);
    afisare(gis,studenti,numar_elemente);
    sortare2(studenti,0,inceput-1);
    afisare(gis,studenti,numar_elemente);
    fclose(fis);
    fclose(gis);

    return 0;
}