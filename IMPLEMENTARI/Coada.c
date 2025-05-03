#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct tip_nod{
	int id;
	int data;
    char text[200];
    int prioriate;
	struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_coada;
void adauga_nod_final(tip_coada *coada,int id,int data,char *text,int prioriate)
{
    tip_nod *q=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q==NULL)
    {
        perror("Eroare la alocarea memoriei dinamice\n");
        exit(-1);
    }
    q->id=id;
    q->data=data;
    strcpy(q->text,text);
    q->prioriate=prioriate;
    q->urm=NULL;
    tip_nod *curent=*coada;
    if(*coada==NULL)
    {
        *coada=q;
        return;
    }
    while(curent->urm!=NULL)
    {
        curent=curent->urm;
    }
    curent->urm=q;
}
void afisare(tip_coada coada)
{
    while(coada!=NULL)
    {
        printf("%d %d %s %d\n",coada->id,coada->data,coada->text,coada->prioriate);
        coada=coada->urm;
    }
    printf("\n");
}
void elibereaza_coada(tip_coada *coada)
{
    tip_nod *temp=NULL;
    while(*coada!=NULL)
    {
        temp=*coada;
        *coada=(*coada)->urm;
        free(temp);
    }
}
void adauga_nod_prioritate(tip_coada *coada,int id,int data,char *text,int prioriate)
{
    tip_nod *curent=*coada;
    tip_nod *q=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q==NULL)
    {
        perror("Eroare la alocarea memoriei dinamice\n");
        exit(-1);
    }
    q->id=id;
    q->data=data;
    strcpy(q->text,text);
    q->prioriate=prioriate;
    if(*coada==NULL)
    {
        *coada=q;
        return;
    }
    if(q->data<curent->data)
    {
        q->urm=curent;
        *coada=q;
        return;
    }
    while(curent->urm!=NULL&&(curent->urm->data<q->data))
    {
        curent=curent->urm;
    }
    q->urm=curent->urm;
    curent->urm=q;
}
void parcurge_coada(tip_coada coada,tip_coada *coada1,tip_coada *coada2)
{
    tip_nod *curent=coada;
    while(curent!=NULL)
    {
        if(curent->prioriate==0)
        {
            adauga_nod_prioritate(coada1,curent->id,curent->data,curent->text,curent->prioriate);
        }
        else
        {
            adauga_nod_prioritate(coada2,curent->id,curent->data,curent->text,curent->prioriate);
        }
        curent=curent->urm;
    }
}
void interclaseaza(tip_coada *coada,tip_coada coada1,tip_coada coada2)
{
    while(coada1!=NULL&&coada2!=NULL)
    {
        if(coada1->data<coada2->data)
        {
            adauga_nod_final(coada,coada1->id,coada1->data,coada1->text,coada1->prioriate);
            coada1=coada1->urm;
        }
        else
        {
            adauga_nod_final(coada,coada2->id,coada2->data,coada2->text,coada2->prioriate);
            coada2=coada2->urm;
        }
    }
    while(coada1!=NULL)
    {
        adauga_nod_final(coada,coada1->id,coada1->data,coada1->text,coada1->prioriate);
        coada1=coada1->urm;
    }
    while(coada2!=NULL)
    {
        adauga_nod_final(coada,coada2->id,coada2->data,coada2->text,coada2->prioriate);
        coada2=coada2->urm;
    }
}
int main(void)
{   
    tip_coada coada=NULL;
    tip_coada coada1=NULL;
    tip_coada coada2=NULL;
    adauga_nod_final(&coada,2,2,"2",0);
    adauga_nod_final(&coada,3,3,"3",1);
    adauga_nod_final(&coada,1,1,"1",0);
    adauga_nod_final(&coada,5,5,"5",1);
    adauga_nod_final(&coada,4,4,"4",0);
    parcurge_coada(coada,&coada1,&coada2);
    afisare(coada);
    afisare(coada1);
    afisare(coada2);
    elibereaza_coada(&coada);
    interclaseaza(&coada,coada1,coada2);
    afisare(coada);
    elibereaza_coada(&coada);
    elibereaza_coada(&coada1);
    elibereaza_coada(&coada2);

    return 0;
}