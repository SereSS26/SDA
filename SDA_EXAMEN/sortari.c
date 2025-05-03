#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 200
#define NUMAR_JOCURI 200

typedef struct
{
    int an;
    char platforma[MAX];
    char titlu[MAX];
    char gen[MAX];
    char multiplayer[MAX];
}Joc;

void citire(FILE *fis,Joc *jocuri,int *numar_jocuri)
{
    char buffer[MAX];
    while(fgets(buffer,sizeof(buffer),fis)!=NULL)
    {       
        buffer[strcspn(buffer,"\n")]='\0';
        char *p=NULL;
        p=strtok(buffer,"\t");
        if(p!=NULL)
        {
            jocuri[*numar_jocuri].an=atoi(p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(jocuri[*numar_jocuri].platforma,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(jocuri[*numar_jocuri].titlu,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(jocuri[*numar_jocuri].gen,p);
        }
        p=strtok(NULL,"\t");
        if(p!=NULL)
        {
            strcpy(jocuri[*numar_jocuri].multiplayer,p);
        }
        (*numar_jocuri)++;
    }
}
void afisare(FILE *gis,Joc *jocuri,int numar_jocuri)
{
    int i=0;
    for(i=0;i<numar_jocuri;i++)
    {
        fprintf(gis,"%d %s %s %s %s\n",jocuri[i].an,jocuri[i].platforma,jocuri[i].titlu,jocuri[i].gen,jocuri[i].multiplayer);
    }
}
///SORTARI
void insertie(Joc a[], int n)
{
	int i, j;
	Joc tmp;
	for (i = 1; i < n; i++)
	{
		tmp = a[i];
		for (j = i; (j > 0) && (tmp.an < a[j - 1].an); j--)
			a[j] = a[j - 1];
		a[j] = tmp;
	}
}
void swap(Joc* el1, Joc* el2)
{
	Joc tmp;
	tmp = *el1;
	*el1 = *el2;
	*el2 = tmp;
}
void selectie(Joc a[], int n)
{
	int i, j, min; // min retine INDEXUL elementului cu valoare minima
	for (i = 0; i < n - 1; i++)
	{
		min = i;
		for (j = i + 1; j < n; j++)
		{
			if (a[j].an < a[min].an)
				min = j;
		}
		swap(&a[min], &a[i]);
	}
}
void bubble_sort(Joc a[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)
	{
		for (j = n - 1; j > i; j--)
			if (a[j].an < a[j - 1].an) //daca nu sunt in ordinea potrivita
				swap(&a[j], &a[j - 1]);
	}
}
// T este dimensiunea tabloului de incrementi
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
void shell_sort(Joc a[], int n)
{

	int i, j, k, hCnt, H;
	Joc tmp;
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
void quicksort(Joc a[], int prim, int ultim)
{
	int stanga = prim + 1;
	int dreapta = ultim;
	//alegere pivot
	swap(&a[prim], &a[(prim + ultim) / 2]);
	//mutare pivot pe prima pozitie
	Joc pivot = a[prim];
	while (stanga <= dreapta) //partitionare
	{
		while (stanga<=ultim && a[stanga].an < pivot.an)
			stanga++;
		while (dreapta>=prim && pivot.an < a[dreapta].an)
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
#define NMAX 1500
void qsortnerec(Joc a[], int n)
{
	int i, j, s, d;
	Joc x, temp;
	unsigned char is;
	struct {
		int s, d;
	}
	stiva[NMAX];
	is = 1; stiva[0].s = 0; stiva[0].d = n - 1; /*amorsare*/
	do {
		s = stiva[is - (1)].s; d = stiva[is - (1)].d; is = is - 1;
		do {
			i = s; j = d; x = a[(s + d) / 2];
			do {
				while (a[i].an < x.an) i = i + 1;
				while (x.an < a[j].an) j = j - 1;
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
void mmergesort(Joc A[], Joc temp[], int left, int right) {
	if (left == right) return; // secventa de un element
	int mid = (left + right) / 2;
	mmergesort(A, temp, left, mid);
	mmergesort(A, temp, mid + 1, right);
	for (int i = left; i <= right; i++) temp[i] = A[i]; // se copiaza secventa in temp
	int i1 = left; int i2 = mid + 1; // interclasare inapoi in A
	for (int index = left; index <= right; index++) {
		if (i1 == mid + 1) A[index] = temp[i2++];  // s-a epuizat secventa din stanga
		else if (i2 > right) A[index] = temp[i1++]; // s-a epuizat secventa din dreapta
		else if (temp[i1].an < temp[i2].an) A[index] = temp[i1++];
		else A[index] = temp[i2++];
	}
}
void deplasare(Joc a[], int stanga, int dreapta)
{
	int fiu = 2 * stanga + 1;
	while (fiu <= dreapta)
	{
		if (fiu < dreapta && a[fiu].an < a[fiu + 1].an)
			//daca al doilea fiu are cheia cea mai mare
			fiu++;								//retinem al doilea fiu
		if (a[stanga].an < a[fiu].an)  //daca este necesar 
		{										 //schimba parinte cu fiu
			swap(&a[stanga], &a[fiu]);			 //si deplaseaza in jos
			stanga = fiu;
			fiu = 2 * stanga + 1;
		}
		else
			fiu = dreapta + 1;
	}
}
void hheapsort(Joc a[], int n)
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
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("sortari.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier intrare\n");
        exit(-1);
    }
    gis=fopen("sortari.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier iesire\n");
        exit(-1);
    }
    Joc jocuri[NUMAR_JOCURI];
    int numar_jocuri=0;
    citire(fis,jocuri,&numar_jocuri);
    //insertie(jocuri,numar_jocuri);
    //selectie(jocuri,numar_jocuri);
    //bubble_sort(jocuri,numar_jocuri);
    //shell_sort(jocuri,numar_jocuri);
    //quicksort(jocuri,0,numar_jocuri-1);
    //qsortnerec(jocuri,numar_jocuri);
    //Joc temp[NUMAR_JOCURI];
    //mmergesort(jocuri,temp,0,numar_jocuri-1);
    hheapsort(jocuri,numar_jocuri);
    afisare(gis,jocuri,numar_jocuri);
    ///sa repeti cautare_binara....
    fclose(fis);
    fclose(gis);

    return 0;
}