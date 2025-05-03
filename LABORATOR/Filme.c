#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXIM_FILME 5050
#define LUNGIME_NUME 200

typedef struct{
    int an;
    int durata;
    char nume[LUNGIME_NUME];
    char categorie[LUNGIME_NUME];
    char premiu[LUNGIME_NUME];
}Film;

void citire(FILE *fis,Film *filme,int *numar_filme)
{
    int index=0;
    char buffer[LUNGIME_NUME];
    fgets(buffer,sizeof(buffer),fis);
    char *p=NULL;
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {   
        buffer[strcspn(buffer,"\n")]='\0';
        p=strtok(buffer,"\t");
        if(p!=NULL)
        {
            filme[index].an=atoi(p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            filme[index].durata=atoi(p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].nume,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].categorie,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(filme[index].premiu,p);
        }
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

void insertion_sort(Film a[], int n)
{
	int i, j;
	Film tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (strcmp(tmp.nume,a[j-1].nume)>0); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
void swap(Film * el1, Film * el2)
{
	Film tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void selection_sort(Film a[], int n)
{
	int i, j, min; // min retine INDEXUL elementului cu valoare minima
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (strcmp(a[j].nume,a[min].nume)>0)
				min = j;
		}
		swap(&a[min], &a[i]);
	}
}
void bubble_sort(Film a[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 1; j > i; j--)
			if (strcmp(a[j].nume,a[j-1].nume)>0) //daca nu sunt in ordinea potrivita
				swap(&a[j], &a[j - 1]);
	}
}
#define T 3
int h[T];
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
				for (k = j; (k - H >= 0) && (strcmp(tmp.nume,a[k-H].nume)>0); k -= H)
					a[k] = a[k - H];
				a[k] = tmp;
			}
		}
	}
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
		while (strcmp(a[stanga].nume,pivot.nume)>0)
			stanga++;
		while (strcmp(pivot.nume,a[dreapta].nume)>0)
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
#define MAX 1500
void qsortnerec(Film a[], int n)
{
	int i, j, s, d;
	Film x, temp;
	unsigned char is;
	struct {
		int s, d;
	}
	stiva[MAX];
	is = 1; stiva[0].s = 0; stiva[0].d = n - 1; /*amorsare*/
	do {
		s = stiva[is - (1)].s; d = stiva[is - (1)].d; is = is - 1;
		do {
			i = s; j = d; x = a[(s + d) / 2];
			do {
				while (strcmp(a[i].nume,x.nume)>0) i = i + 1;
				while (strcmp(x.nume,a[j].nume)>0) j = j - 1;
				if (i <= j)
				{
					temp = a[i]; a[i] = a[j]; a[j] = temp;
					i = i + 1; j = j - 1;
				}
			} while (!(i > j));
			if (i < d)
			{
				is = is + 1; stiva[is - 1].s = i; stiva[is - 1].d = d;
			}
			d = j;
		} while (!(s >= d));
	} while (!(is == 0));
} /*quicksort_nerecursiv*/
void deplasare(Film a[], int stanga, int dreapta)
{
	int fiu = 2 * stanga + 1;
	while (fiu <= dreapta)
	{
		if (fiu < dreapta && (strcmp(a[fiu].nume,a[fiu+1].nume)>0))
			//daca al doilea fiu are cheia cea mai mare
			fiu++;								//retinem al doilea fiu
		if ((strcmp(a[stanga].nume,a[fiu].nume)>0))  //daca este necesar 
		{										 //schimba parinte cu fiu
			swap(&a[stanga], &a[fiu]);			 //si deplaseaza in jos
			stanga = fiu;
			fiu = 2 * stanga + 1;
		}
		else
			fiu = dreapta + 1;
	}
}
void heap_sort(Film a[], int n)
{
	int i;
	//algoritmul lui Floyd 
	for (i = n / 2 - 1; i >= 0; i--) //se creaza ansamblul
		deplasare(a, i, n - 1);
	//extragerea maximului si refacerea ansamblului
	for (i = n - 1; i >= 1; i--)
	{
		swap(&a[0], &a[i]);			//mutare element maxim pe pozitia a[i]
		deplasare(a, 0, i - 1);		//se reface proprietatea de ansamblu
	}
}
#define MAX 1500

void qsortnerec_3way(Film a[], int n) {
    int s, d, lt, gt, i;
    Film x, temp;
    unsigned char is;
    struct {
        int s, d;
    } stiva[MAX];
    is = 1;
    stiva[0].s = 0;
    stiva[0].d = n - 1; // Inițializare stivă

    do {
        s = stiva[is - 1].s;
        d = stiva[is - 1].d;
        is = is - 1;

        while (s < d) {
            // Selectăm pivotul și inițializăm limitele
            x = a[(s + d) / 2];
            lt = s;
            gt = d;
            i = s;

            // Partiționarea în trei secțiuni
            while (i <= gt) {
                if (strcmp(a[i].nume,x.nume)>0) {
                    // Element mai mic decât pivot -> îl mutăm în secțiunea < pivot
                    temp = a[lt];
                    a[lt] = a[i];
                    a[i] = temp;
                    lt++;
                    i++;
                } else if (strcmp(a[i].nume,x.nume)<0) {
                    // Element mai mare decât pivot -> îl mutăm în secțiunea > pivot
                    temp = a[i];
                    a[i] = a[gt];
                    a[gt] = temp;
                    gt--;
                } else {
                    // Element egal cu pivot -> îl lăsăm la locul lui și avansăm
                    i++;
                }
            }

            // Salvăm secțiunile care mai necesită sortare pe stivă
            if (lt - s < d - gt) {
                if (s < lt - 1) {
                    is = is + 1;
                    stiva[is - 1].s = s;
                    stiva[is - 1].d = lt - 1;
                }
                s = gt + 1;
            } else {
                if (gt + 1 < d) {
                    is = is + 1;
                    stiva[is - 1].s = gt + 1;
                    stiva[is - 1].d = d;
                }
                d = lt - 1;
            }
        }
    } while (is != 0);
}


int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Filme.txt","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier de intrare\n");
        exit(-1);
    }
    gis=fopen("Lab5.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
        exit(-1);
    }
    Film filme[MAXIM_FILME];
    int numar_filme=0;
    citire(fis,filme,&numar_filme);
    
    //insertion_sort(filme,numar_filme);
    //selection_sort(filme,numar_filme);
    //bubble_sort(filme,numar_filme);
    //shell_sort(filme,numar_filme);
    //quicksort(filme,0,numar_filme-1);
    //qsortnerec(filme,numar_filme);
    //heap_sort(filme,numar_filme);
    //qsortnerec_3way(filme,numar_filme);

    afisare(gis,filme,numar_filme);
    fclose(fis);
    fclose(gis);
    
    return 0;
}