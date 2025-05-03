#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct tip_nod{
    char nume[MAX];
    int cheie;
    struct tip_nod *urm;
}tip_nod;

typedef struct tip_Nod{
    char nume[MAX];
    int cheie;
    tip_nod *Nod;
}tip_Nod;

typedef struct{
    tip_Nod tablou[MAX];
    int ultim;
}Lista;
typedef Lista *tip_multi_lista;

void initializeaza(tip_multi_lista *Prim)
{
    *Prim=(Lista*)malloc(sizeof(Lista));
    if(*Prim==NULL)
    {
        perror("Eroare la alocare dinamica\n");
        exit(-1);
    }
    (*Prim)->ultim=0;
}
void adauga_Nod(tip_multi_lista *Prim,char *nume,int cheie)
{
    (*Prim)->tablou[(*Prim)->ultim].cheie=cheie;
    strcpy((*Prim)->tablou[(*Prim)->ultim].nume,nume);
    (*Prim)->ultim++;
}
void adauga_nod(tip_multi_lista *Prim,int Cheie,char *nume,int cheie)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        if((*Prim)->tablou[i].cheie==Cheie)
        {
            tip_nod *q=NULL;
            q=(tip_nod*)malloc(sizeof(tip_nod));
            if(q!=NULL)
            {
                q->cheie=cheie;
                strcpy(q->nume,nume);
                q->urm=NULL;
            }
            q->urm=(*Prim)->tablou[i].Nod;
            (*Prim)->tablou[i].Nod=q;
            return;
        }
    }
}
void cauta(tip_multi_lista Prim,int cheie)
{
    int i=0;
    for(i=0;i<Prim->ultim;i++)
    {   
        tip_nod *temp=Prim->tablou[i].Nod;
        while(temp!=NULL)
        {   
            if(temp->cheie==cheie)
            {
                printf("%s\n\n",temp->nume);
                return;
            }
            temp=temp->urm;
        }
    }
}
void elimina(tip_multi_lista *Prim,int cheie)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        tip_nod *curent=(*Prim)->tablou[i].Nod;
        tip_nod *anterior=NULL;
        if(curent->cheie==cheie&&curent->urm==NULL)
        {   
            free(curent);
            return;
        }
        if(curent->cheie==cheie&&curent->urm!=NULL)
        {   
            anterior=curent;
            curent=curent->urm;
            free(anterior);
            (*Prim)->tablou[i].Nod=curent;
            return;
        }
        while(curent->urm!=NULL)
        {
            if(curent->cheie==cheie)
            {
                anterior->urm=curent->urm;
                free(curent);
                return;
            }
            anterior=curent;
            curent=curent->urm;
        }
        if(curent->cheie==cheie)
        {
            anterior->urm=NULL;
            free(curent);
        }
    }
}
void afisare_multi_lista(tip_multi_lista Prim)
{
    int i=0;
    for(i=0;i<Prim->ultim;i++)
    {
        printf("%d %s :\n",Prim->tablou[i].cheie,Prim->tablou[i].nume);
        tip_nod *temp=Prim->tablou[i].Nod;
        while(temp!=NULL)
        {
            printf("%d %s\n",temp->cheie,temp->nume);
            temp=temp->urm;
        }
    }
    printf("\n");
}
void elibereaza(tip_multi_lista *Prim)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        tip_nod *temp=(*Prim)->tablou[i].Nod;
        while((*Prim)->tablou[i].Nod!=NULL)
        {
            temp=(*Prim)->tablou[i].Nod;
            (*Prim)->tablou[i].Nod=temp->urm;
            free(temp);
        }
    }
}
int main(void)
{       
    tip_multi_lista Prim=NULL;
    initializeaza(&Prim);
    adauga_Nod(&Prim,"Zbor1",1);
    adauga_nod(&Prim,1,"Calator1",1);
    adauga_nod(&Prim,1,"Calator2",2);
    adauga_nod(&Prim,1,"Calator3",3);
    adauga_Nod(&Prim,"Zbor2",2);
    adauga_nod(&Prim,2,"Calator1",4);
    adauga_nod(&Prim,2,"Calator2",5);
    adauga_nod(&Prim,1,"Calator4",6);
    afisare_multi_lista(Prim);
    cauta(Prim,6);
    elimina(&Prim,5);
    afisare_multi_lista(Prim);
    elibereaza(&Prim);

    return 0;
}