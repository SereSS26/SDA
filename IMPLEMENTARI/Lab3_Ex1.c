#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

void bubbleSort(int *v,int n)
{
    int ok=0,aux=0,i=0;
	do
	{	
		ok=1;
		for(i=0;i<n-1;i++)
		{
			if(v[i+1]<v[i])
			{
				aux=v[i+1];
				v[i+1]=v[i];
				v[i]=aux;
				ok=0;
			}
		}
	}while(ok==0);
}
void shakerSort(int *v,int n)
{
    int stanga=0,dreapta=n-1,poz=0,i=0,aux=0;
    while(stanga<dreapta)
	{
        poz=0;
        for(i=stanga;i<dreapta;i++)
		{
            if(v[i]>v[i+1])
			{
                aux=v[i];
                v[i]=v[i+1];
                v[i+1]=aux;
                poz=i;
            }
        }
        dreapta=poz;
        for(i=dreapta;i>stanga;i--)
		{
            if(v[i]<v[i-1])
			{
                aux=v[i];
                v[i]=v[i-1];
                v[i-1]=aux;
                poz=i;
            }
        }
        stanga=poz;
    }
}
void Generator(int *v,int n)
{
	int i=0;
    for(i=0;i<n;i++)
	{
        v[i]=rand()%10000;///Generam numere intre 0 și 9999
    }
}
void Tipareste(FILE *fis, const char *algoritm, int m, float timp)
{	
    fprintf(fis,"%s,%d,%.6f\n",algoritm,m,timp);
}
int main(void)
{ 
	FILE *fis=NULL;
	fis=fopen("results.txt","w");
	if(fis==NULL)
	{
		perror("Eroare la deschiderea fiserului\n");
		exit(-1);
	}
	int marimi[]={10000, 20000};
    int n=2,i=0;
	for(i=0;i<n;i++)
	{
		int *v=NULL;
		int m=marimi[i];
		v=(int*)malloc(m*sizeof(int));
		if(v==NULL)
		{
			perror("Eroare la alocarea dinamica a memoriei\n");
			exit(-1);
		}
		Generator(v,m);
        starton();
        bubbleSort(v,m);
        float timp1=startoff();
        Tipareste(fis,"BubbleSort",m,timp1);

        Generator(v,m);
        starton();
        shakerSort(v,n);
        float timp2=startoff();
        Tipareste(fis,"ShakerSort",m,timp2);

        free(v); 
	}
	fclose(fis);

	return 0;
} 