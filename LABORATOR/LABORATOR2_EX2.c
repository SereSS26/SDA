#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define NMAX 100

typedef struct 
{
	int data[NMAX];
	int count;
}Multime;

void init(Multime *m)
{
	(*m).count = 0;
}
void add(Multime  *m, int el)
{
	int i = 0,ok=1;
	for (i = 0; i < (*m).count; i++)
	{
		if ((*m).data[i] == el)
		{
			ok = 0;
			break;
		}
	}
	if (ok == 1)
	{
		((*m).count)++;
		(*m).data[((*m).count)-1] = el;
	}
}
void sterge(Multime *m, int el)
{
	int i = 0,ok=0,poz=0;
	for (i = 0; i <= (*m).count; i++)
	{
		if ((*m).data[i] == el)
		{
			ok = 1;
			poz = i;
			break;
		}
	}
	if (ok == 1)
	{
		for (i = poz; i < (*m).count; i++)
		{
			(*m).data[i] = (*m).data[i + 1];
		}
		(*m).count--;
	}
}
void reuniune(Multime *m1, Multime *m2, Multime *m3)
{
	int i = 0,aux=0;
	for (i = 0; i < (*m1).count; i++)
	{	
		aux = (*m1).data[i];
		add(m3, aux);
	}
	for (i = 0; i < (*m2).count; i++)
	{	
		aux = (*m2).data[i];
		add(m3, aux);
	}
}
void intersectie(Multime *m1, Multime *m2, Multime *m4)
{
	int i = 0,j=0;
	for (i = 0; i < (*m1).count; i++)
	{
		for (j = 0; j<(*m2).count; j++)
		{
			if ((*m1).data[i] == (*m2).data[j])
			{
				add(m4, (*m1).data[i]);
			}
		}
	}
}
void diferenta(Multime* m1, Multime* m2, Multime* m5)
{
	int i = 0,j=0,ok=0;
	for (i = 0; i < (*m1).count; i++)
	{
		ok = 1;
		for (j = 0; j < (*m2).count; j++)
		{
			if ((*m1).data[i] == (*m2).data[j])
			{
				ok = 0;
				break;
			}
		}
		if (ok == 1)
		{
			add(m5, (*m1).data[i]);
		}
	}
}
void tipareste(Multime *m)
{
	int i = 0;
	for (i = 0; i < (*m).count; i++)
	{
		printf("%d ", (*m).data[i]);
	}
	printf("\n");
	
}
void Ex1()
{   
    printf("Rezultate Ex1: \n");
    Multime m1, m2, m3, m4, m5;
	init(&m1);
	add(&m1, 1);
	add(&m1, 2);
	add(&m1, 3);
	add(&m1, 4);
	add(&m1, 5);
	add(&m1, 5);
	tipareste(&m1);
	init(&m2);
	add(&m2, 1);
	add(&m2, 5);
	add(&m2, 6);
	add(&m2, 7);
	tipareste(&m2);
	init(&m3);
	init(&m4);
	init(&m5);
	sterge(&m1, 2);
	tipareste(&m1);
	reuniune(&m1, &m2, &m3);
	tipareste(&m3);
	intersectie(&m1, &m2, &m4);
	tipareste(&m4);
	diferenta(&m1, &m2, &m5);
	tipareste(&m5);
    printf("\n");
}
typedef struct{
    double real;
    double imaginar;
} NumarComplex;
void afisare(NumarComplex a) 
{
    if(a.imaginar>=0)
        printf("%.2f+%.2fi\n",a.real,a.imaginar);
    else
        printf("%.2f-%.2fi\n",a.real,-a.imaginar);
}
NumarComplex aduna(NumarComplex z1, NumarComplex z2) 
{
    NumarComplex rezultat;
    rezultat.real=z1.real+z2.real;
    rezultat.imaginar=z1.imaginar+z2.imaginar;
    return rezultat;
}
NumarComplex scade(NumarComplex z1, NumarComplex z2) 
{
    NumarComplex rezultat;
    rezultat.real=z1.real-z2.real;
    rezultat.imaginar=z1.imaginar-z2.imaginar;
    return rezultat;
}
double modul(NumarComplex z) 
{
    return sqrt(z.real*z.real+z.imaginar*z.imaginar);
}
NumarComplex conjugat(NumarComplex z) 
{
    NumarComplex rezultat;
    rezultat.real=z.real;
    rezultat.imaginar=-z.imaginar;
    return rezultat;
}
void Ex2()
{   
    printf("Rezultate Ex2: \n");
    NumarComplex z1,z2;
    z1.real=1.0;
    z1.imaginar=2.0;
    z2.real=3.0;
    z2.imaginar=3.0;
    afisare(z1);
    afisare(z2);
    NumarComplex suma=aduna(z1,z2);
    afisare(suma);
    NumarComplex diferenta=scade(z1,z2);
    afisare(diferenta);
    double mod=modul(z1);
    printf("%.2f\n",mod);
    NumarComplex conj=conjugat(z1);
    afisare(conj);
}
int main(void)
{	
	Ex1();
    Ex2();

	return 0;
}

