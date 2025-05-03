#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct tip_nod{
    int cheie;
    char nume[MAX];
    struct tip_nod *urm;
}tip_nod;
typedef tip_nod *tip_coada;
void insereaza(tip_coada *prim,int cheie,char *nume)
{
    tip_nod *q=NULL;
    tip_nod *curent=*prim;
    tip_nod *anterior=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q!=NULL)
    {
        q->cheie=cheie;
        strcpy(q->nume,nume);
        q->urm=NULL;
    }
    if(*prim==NULL)
    {
        *prim=q;
        return;
    }
    if(q->cheie<curent->cheie)
    {
        q->urm=curent;
        *prim=q;
        return;
    }
    if(curent->urm==NULL)
    {
        curent->urm=q;
        return;
    }
    while(curent!=NULL)
    {   
        if(q->cheie<curent->cheie)
            break;
        anterior=curent;
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        anterior->urm=q;
        q->urm=curent;
    }
    else
    {
        anterior->urm=q;
    }
}
tip_nod *cauta(tip_coada prim,int cheie)
{
    tip_nod *curent=prim;
    while(curent!=NULL)
    {
        if(curent->cheie==cheie)
            return curent;
        curent=curent->urm;
    }
    return NULL;
}
void stergere(tip_coada *prim,tip_nod *q)
{   
    tip_nod *curent=*prim;
    tip_nod *anterior=NULL;
    int contor=0;
    while(curent!=NULL)
    {
        if(curent==q)
        {
            if(contor==0)
            {
                *prim=(*prim)->urm;
                free(curent);
                return;
            }
            anterior->urm=curent->urm;
            free(curent);
            return;
        }
        anterior=curent;
        curent=curent->urm;
        contor++;
    }
}
void afiseaza(tip_coada prim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->cheie,prim->nume);
        prim=prim->urm;
    }
    printf("\n");
}
void elibereaza(tip_coada *prim)
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
    tip_coada prim=NULL;
    tip_nod *q=NULL;
    insereaza(&prim,1,"a");
    insereaza(&prim,2,"b");
    insereaza(&prim,4,"d");
    insereaza(&prim,3,"c");
    insereaza(&prim,5,"f");
    afiseaza(prim);
    q=cauta(prim,7);
    if(q!=NULL)
    {
        printf("%d %s\n\n",q->cheie,q->nume);
        stergere(&prim,q);
    }
    afiseaza(prim);
    elibereaza(&prim);
    return 0;
}