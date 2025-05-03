#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef int tip_info;
typedef struct tip_nod{
	int cheie;
	tip_info info;
	struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_lista;
tip_lista prim = NULL;
tip_lista ultim = NULL;
void initializare_lista() 
{
    prim=NULL;
}
tip_lista insertie_prioritate(int cheie, int info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
    q->cheie=cheie;
    q->info=info;
    q->urm=NULL;
    tip_nod *curent=prim;
    if(prim==NULL)
    {
        prim=q;
        return prim;
    }
    if(prim!=NULL&&prim->info<q->info)
    {
        q->urm=prim;
        prim=q;
    }
    else
    {
        while(curent->urm!=NULL&&curent->urm->info>q->info)
        {
            curent=curent->urm;
        }
        q->urm=curent->urm;
        curent->urm=q;
    }
    return prim;
}
void afisare(tip_lista prim)
{
    while(prim!=NULL)
    {
        printf("%d ",prim->info);
        prim=prim->urm;
    }
    printf("\n");
}
tip_lista extrage_prioritar() 
{
    if(prim==NULL) 
    {
        printf("Lista este goala, nu se poate extrage elementul prioritar.\n");
        return NULL;
    }
    tip_nod* nod_extras=prim;
    prim=prim->urm;  
    nod_extras->urm=NULL;  
    free(nod_extras); 
    return prim;
}
void elibereaza_memorie(tip_lista *prim)
{
    tip_lista temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        (*prim)=(*prim)->urm;
        free(temp);
    }
}
int main(void)
{       
    initializare_lista();
    insertie_prioritate(1,1);
    insertie_prioritate(2,2);
    insertie_prioritate(3,3);
    insertie_prioritate(4,4);
    insertie_prioritate(5,5);
    afisare(prim);
    prim=extrage_prioritar();
    afisare(prim);
    elibereaza_memorie(&prim);

    return 0;
}