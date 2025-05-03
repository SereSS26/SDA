#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define LUNGIME_NUME 300
#define MAXIM_NUMAR_FILME 5001

typedef struct{

    int an;
    int durata;
    char nume[LUNGIME_NUME];
    char categorie[LUNGIME_NUME];
    char premiu[LUNGIME_NUME];
}Film;
void citire1(FILE *fis,Film *filme,int *numar_filme)
{
    char buffer[LUNGIME_NUME];
    int index=0;
    fgets(buffer,sizeof(buffer),fis);
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        sscanf(buffer,"%d\t%d\t%[^\t]\t%[^\t]\t%[^\n]",
               &filme[index].an,
               &filme[index].durata,
               filme[index].nume,
               filme[index].categorie,
               filme[index].premiu);
        index++;
    }
    *numar_filme=index;
}
void citire2(FILE *fis,Film *filme,int *numar_filme)
{
    char buffer[LUNGIME_NUME];
    int index=0;
    fgets(buffer,sizeof(buffer),fis);
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {
        char *p=strtok(buffer,"\t");
        if(p!=NULL)
            filme[index].an=atoi(p);
        p=strtok(NULL,"\t");
        if(p!=NULL)
            filme[index].durata=atoi(p);
        p=strtok(NULL,"\t");
        if(p!=NULL)
            strcpy(filme[index].nume,p);
        p=strtok(NULL,"\t");
        if(p!=NULL)
            strcpy(filme[index].categorie,p);
        p=strtok(NULL,"\n");
        if(p!=NULL) 
            strcpy(filme[index].premiu,p); 
        index++;
    }
    *numar_filme=index;
}
void afisare(FILE *gis,Film *filme,int numar_filme)
{
    int i=0;
    for(i=0;i<numar_filme;i++)
    {
        fprintf(gis,"%d %d %s %s %s\n",filme[i].an,filme[i].durata,filme[i].nume,filme[i].categorie,filme[i].premiu);
    }
}
void sortare1(Film *a,int n)
{
    int i, j;
	Film tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (strcmp(tmp.nume,a[j-1].nume)<1); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
void sortare2(Film *a,int n)
{
    int i, j;
	Film tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (strcmp(tmp.premiu,a[j-1].premiu)<1); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
void swap(Film *el1, Film *el2)
{
	Film tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void quicksort(Film a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Film pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (a[stanga].an < pivot.an)
			stanga++;
		while (pivot.an < a[dreapta].an)
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
// T este dimensiunea tabloului de incrementi
#define T 5
int h[T];
/*
void genereare_incrementi(int h[], int t)
{
	int i;
	//generare tablou de incrementi
	h[T - 1] = 1;
	for (i = T - 2; i >=
		0; i--)
	{
		h[i] = 3 * h[i + 1] + 1;
	}
}
*/
void genereare_incrementi(int h[], int t)
{
    int i;
    
    // Primii doi termeni ai șirului Fibonacci
    h[t - 1] = 1;
    if (t > 1)
        h[t - 2] = 1;

    // Generarea restului termenilor din șirul Fibonacci
    for (i = t - 3; i >= 0; i--)
    {
        h[i] = h[i + 1] + h[i + 2]; // F_n = F_(n-1) + F_(n-2)
    }
}
void shell_sort(Film a[], int n)
{
	int i, j, k, hCnt, H;
	Film tmp;
	genereare_incrementi(h, T);
	//pentru fiecare increment
	for (i = 0; i < T; i++)
	{
		H = h[i]; //incrementul curent
		//pentru fiecare subtablou
		for (hCnt = 0; hCnt < H; hCnt++)
		{ //insetion_sort pentru subtablou
			for (j = H + hCnt; j < n; j += H)
			{
				tmp = a[j];
				for (k = j; (k - H >= 0) && tmp.an < a[k - H].an; k -= H)
					a[k] = a[k - H];
				a[k] = tmp;
			}
		}
	}
}
int main(void)
{       
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("curs6.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("curs6.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
        exit(-1);
    }
    Film filme[MAXIM_NUMAR_FILME];
    int numar_filme=0;
    //citire1(fis,filme,&numar_filme);
    citire2(fis,filme,&numar_filme);
    //sortare1(filme,numar_filme);
    //sortare2(filme,numar_filme);
    //quicksort(filme,0,numar_filme-1);
    shell_sort(filme,numar_filme);
    afisare(gis,filme,numar_filme);
    fclose(fis);
    fclose(gis);

    return 0;
}
