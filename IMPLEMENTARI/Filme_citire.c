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
Film filme[MAXIM_FILME];


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

void swap(Film* el1, Film* el2,int *mutari)
{
    Film tmp;
    tmp = *el1;
    *el1 = *el2;
    *el2 = tmp;
    *mutari = *mutari + 1;
}
void swap1(Film* el1, Film* el2)
{
    Film tmp;
    tmp = *el1;
    *el1 = *el2;
    *el2 = tmp;
}
void deplasare(Film a[], int stanga, int dreapta,int *comparati,int *mutari)
{
    int fiu = 2 * stanga + 1;
    while (fiu <= dreapta)
    {   
        *comparati = *comparati + 1;
        if (fiu < dreapta && a[fiu].an>a[fiu+1].an)
            //daca al doilea fiu are cheia cea mai mare
            fiu++;
        *comparati = *comparati + 1;
        if (a[stanga].an>a[fiu].an)  //daca este necesar 
        {										 //schimba parinte cu fiu
            swap(&a[stanga], &a[fiu],mutari);			 //si deplaseaza in jos
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
    int comparati = 0;
    int mutari = 0;
    //algoritmul lui Floyd 
    for (i = n / 2 - 1; i >= 0; i--) //se creaza ansamblul
        deplasare(a, i, n - 1,&comparati,&mutari);
    //extragerea maximului si refacerea ansamblului
    for (i = n - 1; i >= 1; i--)
    {
        swap(&a[0], &a[i],&mutari);			//mutare element maxim pe pozitia a[i]
        deplasare(a, 0, i - 1,&comparati,&mutari);		//se reface proprietatea de ansamblu
    }
    printf("%d %d\n", comparati, mutari);
}
void selection_sort(Film a[], int n)
{   
    int comparati = 0;
    int mutari = 0;
    int i, j, min; // min retine INDEXUL elementului cu valoare minima
    for (i = 0; i < n - 1; i++)
    {
        min = i;
        for (j = i + 1; j < n; j++)
        {   
            comparati++;
            if (a[j].an < a[min].an)
            {
                min = j;
            }
                
        }
        swap(&a[min], &a[i],&mutari);
    }
    printf("%d %d\n", comparati, mutari);
}
int comparati = 0;
int mutari = 0;
void quicksort(Film a[], int prim, int ultim)
{   
    int stanga = prim + 1;
    int dreapta = ultim;
    //alegere pivot
    mutari++;
    swap1(&a[prim], &a[(prim + ultim) / 2]);
    //mutare pivot pe prima pozitie
    Film pivot = a[prim];
    while (stanga <= dreapta) //partitionare
    {
        while (strcmp(a[stanga].nume, pivot.nume) < 0)
        {   
            comparati++;
            stanga++;
        } 
        while (strcmp(pivot.nume, a[dreapta].nume) < 0)
        {
            dreapta--;
            comparati++;
        }
        if (stanga < dreapta)
        {   
            mutari++;
            swap1(&a[stanga++], &a[dreapta--]);
        }
            
        else
            stanga++;
    }
    //mutare pivot la locul sau final
    mutari++;
    swap1(&a[dreapta], &a[prim]);
    //apelurile recursive
    if (prim < dreapta - 1)
        quicksort(a, prim, dreapta - 1);
    if (dreapta + 1 < ultim)
        quicksort(a, dreapta + 1, ultim);
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
    gis=fopen("Lab5.txt","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier de iesire\n");
        exit(-1);
    }
    
    int numar_filme=0;
    citire(fis,filme,&numar_filme);

    //heap_sort(filme, numar_filme);
    //selection_sort(filme, numar_filme);
    //quicksort(filme, 0, numar_filme - 1,&comparati,&mutari);
    //printf("%d %d\n", comparati, mutari);

    afisare(gis,filme,numar_filme);
    fclose(fis);
    fclose(gis);
    
    return 0;
}
