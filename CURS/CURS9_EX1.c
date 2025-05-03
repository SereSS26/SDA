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
tip_lista insertie_fata(int cheie, tip_info info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
	if (q) //daca s-a alocat spatiu cu succes
	{
		q->cheie = cheie;
		q->info = info; //asignez valorile primite ca parametru
		q->urm = prim;  //facem legatura catre inceputul listei
		if (prim == NULL)
			ultim = q;
		prim = q;       //noul nod devine primul nod;
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
int numara_noduri(tip_lista prim)
{
    if(prim==NULL)
    {
        return 0;
    }
    return 1+numara_noduri(prim->urm);
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
    insertie_fata(1,1);
    insertie_fata(2,2);
    insertie_fata(3,3);
    insertie_fata(4,4);
    insertie_fata(5,5);
    afisare(prim);
    printf("Numarul de noduri este:%d\n",numara_noduri(prim));
    elibereaza_memorie(&prim);

    return 0;
}