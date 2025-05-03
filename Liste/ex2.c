#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct tip_nod{
    int cheie;
    char nume[MAX];
    struct tip_nod *urm;
    struct tip_nod *prev;
}tip_nod;
typedef tip_nod *tip_lista;

void insereaza(tip_lista *prim,int cheie,char *nume)
{
    tip_nod *q=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q!=NULL)
    {
        q->cheie=cheie;
        strcpy(q->nume,nume);
        q->urm=NULL;
        q->prev=NULL;
    }
    if(*prim==NULL)
    {
        *prim=q;
        return;
    }
    q->urm=*prim;
    (*prim)->prev=q;
    *prim=q;
}
void afiseaza(tip_lista prim,tip_lista *ultim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->cheie,prim->nume);
        prim=prim->urm;
        if(prim!=NULL)
            *ultim=prim;
    }
    printf("\n");
}
void afiseaza_spate(tip_lista ultim)
{
    while(ultim!=NULL)
    {
        printf("%d %s\n",ultim->cheie,ultim->nume);
        ultim=ultim->prev;
    }
    printf("\n");
}
int cauta(tip_lista prim,int cheie)
{
    int pozitie=-1;
    while(prim!=NULL)
    {
        pozitie++;
        if(prim->cheie==cheie)
        {
            return pozitie;
        }
        prim=prim->urm;
    }
    return -1;
}
void stergere(tip_lista *prim,int pozitie)
{
    if(pozitie==-1)
    {
        printf("Nu e in lista\n");
        return;
    }
    tip_nod *curent=*prim;
    tip_nod *anterior=NULL;
    int contor=0;
    if(pozitie==0)
    {
        *prim=(*prim)->urm;
        (*prim)->prev=NULL;
        free(curent);
        return;
    }
    while(curent->urm!=NULL)
    {   
        if(contor==pozitie)
        {
            anterior->urm=curent->urm;
            curent->urm->prev=curent->prev;
            free(curent);
            return;
        }
        anterior=curent;
        curent=curent->urm;
        contor++;
    }
    free(curent);
    anterior->urm=NULL;
    
}
void elibereaza(tip_lista *prim)
{
    tip_nod *temp=*prim;
    while(*prim!=NULL)
    {
        temp=*prim;
        *prim=(*prim)->urm;
        free(temp);
    }
}
int main(void)
{       
    tip_lista prim=NULL;
    tip_lista ultim=NULL;
    int pozitie=-1;
    insereaza(&prim,1,"a");
    insereaza(&prim,2,"b");
    insereaza(&prim,3,"c");
    insereaza(&prim,4,"d");
    insereaza(&prim,5,"e");
    afiseaza(prim,&ultim);
    afiseaza_spate(ultim);
    pozitie=cauta(prim,1);
    stergere(&prim,pozitie);
    afiseaza(prim,&ultim);
    afiseaza_spate(ultim);
    elibereaza(&prim);

    return 0;
}