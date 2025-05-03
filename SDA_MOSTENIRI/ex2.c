#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct palet{
    int cod;
    struct palet *urm;
}palet;
typedef struct depozit{
    char nume[25];
    struct palet *urm_ls;
    struct depozit *urm_lp;
}depozit;

palet* new_palet(int cod)
{
    palet *q=NULL;
    q=(palet*)malloc(sizeof(palet));
    if(q==NULL)
    {
        perror("Eroare la alocarea memorie dinalimce\n");
        exit(-1);
    }
    q->cod=cod;
    q->urm=NULL;
    return q;
}
depozit* new_depozit(char *nume)
{
    depozit *q=NULL;
    q=(depozit*)malloc(sizeof(depozit));
    if(q==NULL)
    {
        perror("Eroare la alocarea memorie dinalimce\n");
        exit(-1);
    }
    strcpy(q->nume,nume);
    q->urm_ls=NULL;
    q->urm_lp=NULL;
    return q;
}
void afisare_ls(palet *ls)
{
    palet *temp=ls;
    while(temp!=NULL)
    {
        printf("%d ",temp->cod);
        temp=temp->urm;
    }
    printf("\n");
}
void afisare_lp(depozit *lp)
{
    depozit *temp=lp;
    while(temp!=NULL)
    {
        printf("%s: ",temp->nume);
        afisare_ls(temp->urm_ls);
        temp=temp->urm_lp;
    }
    printf("\n");
}

depozit *adauga_depozit(char *nume,depozit *lp)
{
    depozit *q=new_depozit(nume);
    if(lp==NULL)
    {
        lp=q;
        return lp;
    }
    q->urm_lp=lp;
    lp=q;
    return lp;
}
palet* adauga_palet_ordine(palet *ls,int cod)
{
    palet *q=new_palet(cod);
    if(ls==NULL)
    {   
        ls=q;
        return ls;
    }
    if(ls!=NULL&&ls->cod>q->cod)
    {
        q->urm=ls;
        ls=q;
        return ls;
    }
    palet *temp=ls;
    while(temp->urm!=NULL)
    {
        if(q->cod<temp->urm->cod)
        {
            q->urm=temp->urm;
            temp->urm=q;
            return ls;
        }
        temp=temp->urm;
    }
    temp->urm=q;
    return ls;
}
depozit *adauga_palet(int cod,char *nume,depozit *lp)
{
    depozit *temp=lp;
    while(temp!=NULL)
    {
        if(strcmp(temp->nume,nume)==0)
        {   
            temp->urm_ls=adauga_palet_ordine(temp->urm_ls,cod);
            return lp;
        }
        temp=temp->urm_lp;
    }
    return lp;
}
depozit *elimina_palet(int cod,depozit *lp)
{
    depozit *temp=lp;
    while(temp!=NULL)
    {   
        palet *curent=temp->urm_ls;
        palet *prev=NULL;
        while(curent!=NULL)
        {
            if(curent->cod==cod)
            {
                if(prev==NULL)
                {   
                    palet *el=curent;
                    curent=el->urm;
                    temp->urm_ls=curent;
                    free(el);
                }
                else
                {   
                    palet *el=curent;
                    prev->urm=curent->urm;
                    free(el);
                }
                curent=curent->urm;
            }
            else
            {
                prev=curent;
                curent=curent->urm;
            }
        }
        temp=temp->urm_lp;
    }
    return lp;
}
int main(void)
{   
    depozit *lp=NULL;

    lp=adauga_depozit("depozit1",lp);
    lp=adauga_depozit("depozit2",lp);
    lp=adauga_depozit("depozit3",lp);

    lp=adauga_palet(2,"depozit1",lp);
    lp=adauga_palet(0,"depozit1",lp);
    lp=adauga_palet(1,"depozit1",lp);
    lp=adauga_palet(3,"depozit1",lp);

    lp=elimina_palet(3,lp);

    afisare_lp(lp);

    return 0;
}