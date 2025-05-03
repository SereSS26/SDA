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
depozit* new_depozit(char *nume)
{
    depozit *q=NULL;
    q=(depozit*)malloc(sizeof(depozit));
    if(q==NULL)
    {
        perror("Eroare la alocarea dinamica a meoriei\n");
        exit(-1);
    }
    strcpy(q->nume,nume);
    q->urm_lp=NULL;
    q->urm_ls=NULL;
    return q;
}
palet* new_palet(int cod)
{
    palet *q=NULL;
    q=(palet*)malloc(sizeof(palet));
    if(q==NULL)
    {
        perror("Eroare la alocarea dinamica a emoriei\n");
        exit(-1);
    }
    q->cod=cod;
    q->urm=NULL;
    return q;
}
depozit* adauga_depozit(char *nume,depozit *lp)
{
    depozit *q=new_depozit(nume);
    if(lp==NULL)
    {
        return q;
    }
    q->urm_lp=lp;
    lp=q;
    return lp;
}
palet* adauga_palet_ordonat(int cod,palet *ls)
{
    palet *q=new_palet(cod);
    if(ls==NULL||ls->cod>q->cod)
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
    q->urm=NULL;
    temp->urm=q;
    return ls;
}
depozit* adauga_palet(char *nume,int cod,depozit *lp)
{   
    depozit *temp=lp;
    while(temp!=NULL)
    {
        if(strcmp(temp->nume,nume)==0)
        {
            temp->urm_ls=adauga_palet_ordonat(cod,temp->urm_ls);
            return lp;
        }
        temp=temp->urm_lp;
    }
    return lp;
}
depozit *elimina_palet(int cod,depozit *lp)
{
    depozit* i = lp;
    while (i != NULL) {
        // Verificăm dacă primul palet din lista este cel care trebuie șters
        if (i->urm_ls != NULL && i->urm_ls->cod == cod) {
            palet* tmp = i->urm_ls;
            i->urm_ls = i->urm_ls->urm;
            free(tmp);
        }

        palet* j = i->urm_ls;
        while (j != NULL && j->urm != NULL) {
            if (j->urm->cod == cod) {
                palet* tmp = j->urm;
                j->urm = j->urm->urm;
                free(tmp);
                break;
            }
            j = j->urm;
        }

        i = i->urm_lp;
    }
    return lp;
}
void afisare_ls(palet *ls)
{
    while(ls!=NULL)
    {
        printf("%d ",ls->cod);
        ls=ls->urm;
    }
    printf("\n");
}
void afiseaza_lp(depozit *lp)
{
    while(lp!=NULL)
    {
        printf("%s :", lp->nume);
        afisare_ls(lp->urm_ls);
        lp=lp->urm_lp;
    }
    printf("\n");
}
int main(void)
{   
    depozit *lp=NULL;
    lp=adauga_depozit("depozit1",lp);
    lp=adauga_depozit("depozit3",lp);
    lp=adauga_depozit("depozit3",lp);
    lp=adauga_depozit("depozit4",lp);

    lp=adauga_palet("depozit1",4,lp);
    lp=adauga_palet("depozit1",1,lp);
    lp=adauga_palet("depozit1",2,lp);
    lp=adauga_palet("depozit1",3,lp);
    lp=adauga_palet("depozit1",0,lp);

    lp=elimina_palet(4,lp);

    afiseaza_lp(lp);

    return 0;
}