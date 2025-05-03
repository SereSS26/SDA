#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef char tip_info[100];
typedef struct tip_nod{
	int cheie;
	tip_info info;
	struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_lista;
tip_lista adauga_nod(tip_lista *prim,int cheie,char *info)
{
    tip_nod *q=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q!=NULL)
    {
        q->cheie=cheie;
        strcpy(q->info,info);
        q->urm=NULL;
    }
    tip_nod *curent=*prim;
    if(curent==NULL)
    {
        *prim=q;
        return *prim;
    }
    if(curent!=NULL&&strcmp(curent->info,q->info)>0)
    {
        q->urm=curent;
        (*prim)=q;
        return *prim;
    }
    while(curent->urm!=NULL&&strcmp(curent->urm->info,q->info)<0)
    {
        curent=curent->urm;
    }
    q->urm=curent->urm;
    curent->urm=q;
    return *prim;
}
tip_nod* cauta_nod(tip_lista prim,int cheie)
{   
    tip_nod *curent=prim;
    while(curent!=NULL&&curent->cheie!=cheie)
    {
        curent=curent->urm;
    }
    return curent;
}
void elimina_nod(tip_lista *prim,int cheie)
{
    tip_nod *curent=*prim;
    tip_nod *anterior=NULL;
    while(curent!=NULL&&curent->cheie!=cheie)
    {
        anterior=curent;
        curent=curent->urm;
    }
    if(anterior==NULL)
    {
        (*prim)=(*prim)->urm;
        free(curent);
    }
    else
    {
        anterior->urm=curent->urm;
        free(curent);
    }
}
void afiseaza_lista(tip_lista prim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->cheie,prim->info);
        prim=prim->urm;
    }
}
void elibereaza_memorie_lista(tip_lista *prim)
{
    tip_nod *temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        (*prim)=(*prim)->urm;
        free(temp);
    }
}
int main(void)
{   
    tip_lista prim = NULL;
    prim=adauga_nod(&prim,2,"2");
    prim=adauga_nod(&prim,1,"1");
    prim=adauga_nod(&prim,4,"4");
    prim=adauga_nod(&prim,5,"5");
    prim=adauga_nod(&prim,3,"3");
    afiseaza_lista(prim);
    tip_nod *nod=NULL;
    nod=cauta_nod(prim,3);
    if(nod!=NULL)
    {
        printf("\n%d %s\n\n",nod->cheie,nod->info);
    }
    elimina_nod(&prim,5);
    afiseaza_lista(prim);
    elibereaza_memorie_lista(&prim);
    
    return 0;
}