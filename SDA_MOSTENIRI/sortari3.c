#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define N 10
#define LINIE 1000

typedef struct angajat{
    char nume[25];
    int salariu;
    int bonus;
}angajat;

void citire(FILE *fis,angajat *angajati,int *numar_elemente)
{
    char buffer[LINIE];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        char *p=NULL;
        p=strtok(buffer," ");
        if(p!=NULL)
        {
            strcpy(angajati[*numar_elemente].nume,p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            angajati[*numar_elemente].salariu=atoi(p);
        }
        p=strtok(NULL," ");
        if(p!=NULL)
        {
            if(strcmp(p,"DA")==0)
                angajati[*numar_elemente].bonus=1;
            else
                angajati[*numar_elemente].bonus=0;
        }
        (*numar_elemente)++;
    }
}
void afisare(FILE *gis,angajat *angajati,int numar_elemente)
{
    int i=0;
    for(i=0;i<numar_elemente;i++)
    {
        fprintf(gis,"%s %d %d\n",angajati[i].nume,angajati[i].salariu,angajati[i].bonus);
    }
    fprintf(gis,"\n");
}
void swap(angajat* el1, angajat* el2)
{
	angajat tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
int sortare1(angajat *angajati,int numar_elemente)
{
    int i=0,j=0;
    for(i=0;i<numar_elemente;i++)
    {
        if(angajati[i].bonus==1)
        {
            swap(&angajati[i],&angajati[j]);
            j++;
        }
    }
    return j;
}
void sortare2(angajat a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	angajat pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].salariu > pivot.salariu)
			stanga++;
		while (pivot.salariu > a[dreapta].salariu)
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
    fis=fopen("sortari3.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari3.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier iesire\n");
        exit(-1);
    }
    angajat angajati[N];
    int numar_elemente=0;
    int inceput=0;
    citire(fis,angajati,&numar_elemente);
    inceput=sortare1(angajati,numar_elemente);
    afisare(gis,angajati,numar_elemente);
    sortare2(angajati,inceput,numar_elemente-1);
    afisare(gis,angajati,numar_elemente);
    fclose(fis);
    fclose(gis);

    return 0;
}