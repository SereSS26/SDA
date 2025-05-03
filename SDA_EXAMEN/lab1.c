#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 100
#define NUMAR_CANDIDATI 5

typedef struct{
    int data[MAX];
    int nr;
}Multime;

typedef struct{
    char nume[NUMAR_CANDIDATI][MAX];
    int numar;
}Candidat;

void ex1(FILE *fis,FILE *gis)
{
    int n=0,i=0;
    fscanf(fis,"%d",&n);
    for(i=1;i<=n;i++)
    {
        fprintf(gis,"%d ",i);
    }
    fprintf(gis,"\n");
}
void ex2(FILE *fis,FILE *gis)
{
    int n=0,i=0;
    //0 1 1 2 3
    fscanf(fis,"%d",&n);
    int a=0,b=1,c=0;
    if(n==1)
    {
        fprintf(gis,"%d\n",a);
        return;
    }
    if(n==2)
    {
        fprintf(gis,"%d\n",b);
        return;
    }
    if(n>=3)
    {
        for(i=3;i<=n;i++)
        {
            c=a+b;
            a=b;
            b=c;
        }
        fprintf(gis,"%d\n",c);
        return;
    }
}
void ex3(FILE *fis,FILE *gis)
{
    int n=0,m=0,r=0;
    fscanf(fis,"%d",&n);
    fscanf(fis,"%d",&m);
    while(n!=0)
    {
        r=m%n;
        m=n;
        n=r;
    }   
    fprintf(gis,"%d\n",m);
}
void adauga(Multime *m,int valoare)
{   
    int i=0,ok=1;
    for(i=0;i<m->nr;i++)
    {
        if(m->data[i]==valoare)
            ok=0;
    }
    if(ok==1)
    {
        m->data[m->nr]=valoare;
        m->nr++;
    }
}
void afiseaza(FILE *gis,Multime *m)
{
    int i=0;
    for(i=0;i<m->nr;i++)
    {
        fprintf(gis,"%d ",m->data[i]);
    }
    fprintf(gis,"\n");
}
void reuniune(Multime *m3,Multime *m1,Multime *m2)
{
    int i=0;
    for(i=0;i<m1->nr;i++)
    {
        adauga(m3,m1->data[i]);
    }
    for(i=0;i<m2->nr;i++)
    {
        adauga(m3,m2->data[i]);
    }
}
void intersectie(Multime *m4,Multime *m1,Multime *m2)
{
    int i=0,j=0;
    for(i=0;i<m1->nr;i++)
    {
        for(j=0;j<m2->nr;j++)
        {
            if(m1->data[i]==m2->data[j])
                adauga(m4,m1->data[i]);
        }
    }
}
void diferenta(Multime *m5,Multime *m1,Multime *m2)
{
    int i=0,j=0,ok=1;
    for(i=0;i<m1->nr;i++)
    {   
        ok=1;
        for(j=0;j<m2->nr;j++)
        {   
            if(m1->data[i]==m2->data[j])
                ok=0;
        }
        if(ok==1)
            adauga(m5,m1->data[i]);
    }
}
void ex4(FILE *fis,FILE *gis)
{
    Multime *m1=NULL,*m2=NULL,*m3=NULL,*m4=NULL,*m5=NULL;
    m1=(Multime*)malloc(sizeof(Multime));
    if(m1==NULL)
    {
        perror("Eroare la alocarea memorie dinamice\n");
        exit(-1);
    }
    (*m1).nr=0;
    m2=(Multime*)malloc(sizeof(Multime));
    if(m2==NULL)
    {
        perror("Eroare la alocarea memoriei dinamice\n");
        exit(-1);
    }
    (*m2).nr=0;
    adauga(m1,1);
    adauga(m1,2);
    adauga(m1,3);
    adauga(m1,1);
    adauga(m1,5);

    adauga(m2,1);
    adauga(m2,2);
    adauga(m2,4);
    adauga(m2,4);
    adauga(m2,5);

    afiseaza(gis,m1);
    afiseaza(gis,m2);

    m3=(Multime*)malloc(sizeof(Multime));
    if(m3==NULL)
    {
        perror("Eroare la alocarea dinamica a memroie\n");
        exit(-1);
    }
    (*m3).nr=0;
    reuniune(m3,m1,m2);
    afiseaza(gis,m3);
    
    m4=(Multime*)malloc(sizeof(Multime));
    if(m4==NULL)
    {
        perror("Eroare la alocarea dinamica a memoeire\n");
        exit(-1);
    }
    intersectie(m4,m1,m2);
    afiseaza(gis,m4);

    m5=(Multime*)malloc(sizeof(Multime));
    if(m5==NULL)
    {
        perror("Eroare la alocarea memorie dinamice\n");
        exit(-1);
    }
    (*m5).nr=0;
    diferenta(m5,m1,m2);
    afiseaza(gis,m5);
}
void adauga_candidat(Candidat *candidati,char *nume)
{   
    int ok=0,i=0;
    if(candidati->numar<NUMAR_CANDIDATI)
    {   
        for(i=0;i<candidati->numar;i++)
        {
            if(strcmp(candidati->nume[i],nume)==0)
                ok=1;
        }
        if(ok==1)
            return;
        else
        {
            strcpy(candidati->nume[candidati->numar],nume);
            candidati->numar++;
        }
    }
}
void afiseaza_candidati(FILE *gis,Candidat candidati)
{
    int i=0;
    for(i=0;i<candidati.numar;i++)
    {
        fprintf(gis,"%s\n",candidati.nume[i]);
    }
    fprintf(gis,"\n");
}
void elimina_candidat(Candidat *candidati,char *nume)
{
    int i=0,j=0;
    for(i=0;i<candidati->numar;i++)
    {
        if(strcmp(candidati->nume[i],nume)==0)
        {
            for(j=i;j<candidati->numar-1;j++)
            {
                strcpy(candidati->nume[j],candidati->nume[j+1]);
            }
            candidati->numar--;
            return;
        }
    }
}
void cauta_candidat(FILE *gis,Candidat candidati,char *nume)
{
    int i=0,ok=0;
    for(i=0;i<candidati.numar;i++)
    {
        if(strcmp(candidati.nume[i],nume)==0)
            ok=1;
    }
    if(ok==0)
    {
        fprintf(gis,"NU\n");
    }
    else
    {
        fprintf(gis,"DA\n");
    }
}
void ex6(FILE *fis,FILE *gis)
{
    Candidat candidati;
    candidati.numar=0;
    adauga_candidat(&candidati,"Alex");
    adauga_candidat(&candidati,"Alex");
    adauga_candidat(&candidati,"Cosmin");
    adauga_candidat(&candidati,"Artur");
    elimina_candidat(&candidati,"Cosmin");
    cauta_candidat(gis,candidati,"Mirela");
    afiseaza_candidati(gis,candidati);
}
int main(void)
{   
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("lab1.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschiderea fisierului de intrare\n");
        exit(-1);
    }
    gis=fopen("lab1.out","w");
    if(gis==NULL)
    {
        perror("Eroare la dechiderea fisierului de iesire\n");
        exit(-1);
    }
    ///Scheme Logice
    ex1(fis,gis);
    ex2(fis,gis);
    ex3(fis,gis);
    ///Tipuri de date abstracte
    ex4(fis,gis);
    ///Alte aplicatii
    fprintf(gis,"\n");
    ex6(fis,gis);
    fclose(fis);
    fclose(gis);
    
    return 0;
}