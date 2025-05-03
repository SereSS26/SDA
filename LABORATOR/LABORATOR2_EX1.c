#include <stdio.h>
#include <stdlib.h>

void Ex1(FILE *fis,FILE *gis)
{
    int n=0,i=0,*v=NULL;
    fscanf(fis,"%d",&n);
    v=(int*)malloc(n*sizeof(int));
    if(v==NULL)
    {
        perror("Eroare la alocarea dinamica a memoriei\n");
        exit(-1);
    }
    for(i=1;i<=n;i++)
    {
        v[i-1]=i;
    }
    for(i=0;i<n;i++)
    {
        fprintf(gis,"%d ",v[i]);
    }
    fprintf(gis,"\n");
    free(v);
}
int Fibo1(int n)
{
    if(n==0)    
        return 0;
    else
    {
        if(n==1)
            return 1;
        else
            return Fibo1(n-1)+Fibo1(n-2);
    }
}
int Fibo2(int n)
{   
    int a=0,b=0,aux=0,i=0;
    if(n==0||n==1)
        return n;
    else
    {
        a=0;
        b=1;
        for(i=2;i<=n;i++)
        {
            aux=a+b;
            a=b;
            b=aux;
        }
        return b;
    }
}
void Ex2(FILE *fis,FILE *gis)
{
    int n=0;
    fscanf(fis,"%d",&n);
    fprintf(gis,"%d\n",Fibo1(n));
    fprintf(gis,"%d\n",Fibo2(n));
}
int Euclid1(int a,int b)
{
    int aux=0;
    while(b!=0)
    {
        aux=a%b;
        a=b;
        b=aux;
    }
    return a;
}
int Euclid2(int a,int b)
{   
    while(a!=b)
    {
        if(a>b)
            a=a-b;
        else
            b=b-a;
    }
    return a;
}
void Ex3(FILE *fis,FILE *gis)
{
    int a=0,b=0;
    fscanf(fis,"%d",&a);
    fscanf(fis,"%d",&b);
    fprintf(gis,"%d\n",Euclid1(a,b));
    fprintf(gis,"%d\n",Euclid2(a,b));
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("Lab2.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschiderea fisierului de intrare\n");
        exit(-1);
    }
    gis=fopen("Lab2.out","w");
    if(gis==NULL)
    {
        perror("eroare la deschiderea fisierului de iesire\n");
        exit(-1);
    }
    Ex1(fis,gis);
    Ex2(fis,gis);
    Ex3(fis,gis);
    fclose(fis);
    fclose(gis);

    return 0;
}