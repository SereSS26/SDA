#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGIME_NUME 200
#define MAXIM_NUMAR_STUDENTI 5001

typedef struct{
    char nume[LUNGIME_NUME];
    float nota;
}Student;

void citire(FILE *fis,Student *studenti,int *numar_studenti)
{
    char buffer[LUNGIME_NUME];
    int index=0;
    while(fgets(buffer,LUNGIME_NUME,fis)!=NULL)
    {
        buffer[strcspn(buffer,"\n")]='\0';
        strcpy(studenti[index].nume,buffer);
        if(fgets(buffer,LUNGIME_NUME,fis)!=NULL)
        {
            studenti[index].nota=atof(buffer);
            index++;
        }
    }
    *numar_studenti=index;
}
void afisare(FILE *gis,Student *studenti,int numar_studenti)
{
    int i=0;
    for(i=0;i<numar_studenti;i++)
    {
        fprintf(gis,"%s %.6f\n",studenti[i].nume,studenti[i].nota);
    }
}
void sortare1(Student a[], int n)
{
	int i, j;
	Student tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (strcmp(tmp.nume,a[j - 1].nume)<0); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
void sortare2(Student *studenti,int numar_studenti)
{
    int i=0,ok=0;
    Student aux;
    do
    {
        ok=0;
        for(i=0;i<numar_studenti-1;i++)
        {
            if(studenti[i].nota<5&&studenti[i+1].nota>=5)
            {
                aux=studenti[i];
                studenti[i]=studenti[i+1];
                studenti[i+1]=aux;
                ok=1;
            }
        }
    }while(ok==1);
}
void swap(Student *el1,Student *el2)
{
    Student aux;
    aux=*el1;
    *el1=*el2;
    *el2=aux;

}
void quicksort(Student *a,int prim,int ultim)
{
    int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Student pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].nota < pivot.nota)
			stanga++;
		while (pivot.nota < a[dreapta].nota)
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
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Studenti2.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("Lab4.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier iesire\n");
        exit(-1);
    }
    Student studenti[MAXIM_NUMAR_STUDENTI];
    int numar_studenti=0;
    citire(fis,studenti,&numar_studenti);
    sortare1(studenti,numar_studenti);
    //sortare2(studenti,numar_studenti);
    //quicksort(studenti,0,numar_studenti-1);
    afisare(gis,studenti,numar_studenti);
    fclose(fis);
    fclose(gis);

    return 0;
}