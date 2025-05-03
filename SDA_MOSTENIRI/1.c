#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct agenda {
    char nume[50];
    char telefon[10];
    int an;
    int venit;
} agenda;

void swap(agenda* a, agenda* b)
{
    agenda aux;
    aux = *a;
    *a = *b;
    *b = aux;
}

void sortarelafinal(agenda a[], int n)
{
    int index = n - 1;
    for (int i = 0; i < n; i++)
    {
        if (a[i].venit < 1000 && i<index)
        {
            swap(&a[i], &a[index]);
            index--;
        }
    }
}

void afisare(agenda a[], int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s---%s---%d---%d\n", a[i].nume, a[i].telefon, a[i].an, a[i].venit);
    }
    printf("\n");
}

void quicksort(agenda a[], int prim, int ultim)
{
    int stanga = prim + 1;
    int dreapta = ultim;

    swap(&a[prim], &a[(prim + ultim) / 2]);

    agenda pivot = a[prim];
    while (stanga <= dreapta) 
    {
        while (stanga <= ultim && strcmp(a[stanga].nume,pivot.nume)<0)
            stanga++;
        while (dreapta >= prim && strcmp(pivot.nume,a[dreapta].nume)<0)
            dreapta--;
        if (stanga < dreapta)
            swap(&a[stanga++], &a[dreapta--]);
        else
            stanga++;
    }

    swap(&a[dreapta], &a[prim]);

    if (prim < dreapta - 1)
        quicksort(a, prim, dreapta - 1);
    if (dreapta + 1 < ultim)
        quicksort(a, dreapta + 1, ultim);
}

void sortare(agenda a[], int n)
{
    int right = -1, left = -1;
        for (int i = 0; i < n; i++)
        {
            int varsta = 2025 - a[i].an;
            if (varsta >= 30 && varsta <= 40)
            {
                if (left == -1) left = i;
                right = i;
            }

        }
        if (left != -1 && right != -1)
        {
            quicksort(a, left, right);
        }
}
int main(void)
{
    FILE* f;
    if ((f = fopen("date.txt", "rt")) == NULL)
    {
        perror("Eroare la deschiderea fișierului");
        exit(-1);
    }

    agenda a[5];
    for (int i = 0; i < 5; i++)
    {
        fscanf(f, "%s", a[i].nume);
        fscanf(f, "%s", a[i].telefon);
        fscanf(f, "%d", &a[i].an);
        fscanf(f, "%d", &a[i].venit);
    }

    fclose(f);

    sortarelafinal(a, 5);
    afisare(a, 5);

    sortare(a, 5);
    afisare(a, 5);

    return 0;
}
