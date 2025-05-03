#include "timer.h"
#include <stdio.h>
#include <stdlib.h>

#define MAX 100000

int cautareLinie(int *v,int n,int x)
{
    int i=0;
    for(i=0;i<n;i++)
    {
        if(v[i]==x)
        {
            return i;
        }
    }
    return -1;
}
int cautareBinara(int *v, int n, int x)
{
    int stanga=0;
    int dreapta=n-1;
    while(stanga<=dreapta) 
    {
        int mijloc=stanga+(dreapta-stanga)/2;
        if(v[mijloc]==x) 
        {
            return mijloc;  
        }
        if(v[mijloc]<x) 
        {
            stanga=mijloc+1; 
        } 
        else
        {
            dreapta=mijloc-1;  
        }
    }
    return -1; 
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
	fis=fopen("Ccurs7.out","w");
	if(fis==NULL)
	{
		perror("Eroare la deschiderea fiserului\n");
		exit(-1);
	}
	int marimi[]={10000, 20000};
    int n=2,i=0;
    int x=5000;//valoare ipotetica de cautat
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
        cautareLinie(v,m,x);
        float timp1=startoff();
        Tipareste(fis,"BubbleSort",m,timp1);

        Generator(v,m);
        starton();
        cautareBinara(v,m,x);
        float timp2=startoff();
        Tipareste(fis,"ShakerSort",m,timp2);

        free(v); 
	}
	fclose(fis);

	return 0;
} 
