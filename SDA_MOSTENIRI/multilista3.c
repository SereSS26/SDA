#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct gps{
    int cod;
    struct gps *urm;
}gps;
typedef struct firma{
    char nume[25];
    struct gps *urm_ls;
    struct firma *urm_lp;
}firma;

gps* new_gps(int cod)
{
    gps *q=NULL;
    q=(gps*)malloc(sizeof(gps));
    if(q==NULL)
    {
        perror("Eroare la alocarea dinamica a emoriei\n");
        exit(-1);
    }
    q->cod=cod;
    q->urm=NULL;
    return q;
}
firma* new_firma(char *nume)
{
    firma *q=NULL;
    q=(firma*)malloc(sizeof(firma));
    if(q==NULL)
    {
        perror("Eroare la alocarea dinamica a meoriei\n");
        exit(-1);
    }
    strcpy(q->nume,nume);
    q->urm_ls=NULL;
    q->urm_lp=NULL;
    return q;
}

firma* elimina_gps(int cod,firma *lp)
{
    firma *temp=lp;
    while(temp!=NULL)
    {   
        gps *curent=temp->urm_ls;
        gps *prev=NULL;
        while(curent!=NULL)
        {
            if(curent->cod==cod)
            {
                if(prev==NULL)
                {
                    temp->urm_ls=curent->urm;
                }
                else
                {
                    prev->urm=curent->urm;
                }
                gps *el=curent;
                curent=curent->urm;
                free(el);
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

gps* adauga_gps_ordonat(int cod,gps *ls)
{
    gps *temp=ls;
    gps *q=new_gps(cod);
    if(temp==NULL)
    {   
        ls=q;
        return ls;
    }
    if(temp!=NULL&&q->cod<temp->cod)
    {
        q->urm=temp;
        temp=q;
        ls=q;
        return ls;
    }
    while(temp->urm!=NULL)
    {
        if(temp->urm->cod>q->cod)
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
firma *adauga_gps(int cod,char *nume,firma *lp)
{
    firma *temp=lp;
    while(temp!=NULL)
    {
        if(strcmp(temp->nume,nume)==0)
        {
            temp->urm_ls=adauga_gps_ordonat(cod,temp->urm_ls);
            return lp;
        }
        temp=temp->urm_lp;
    }
    return lp;
}
firma* adauga_firma(char *nume,firma *lp)
{
    firma *q=new_firma(nume);
    if(lp==NULL)
    {
        lp=q;
        return lp;
    }
    else
    {
        q->urm_lp=lp;
        lp=q;
    }
    return lp;
}

void afiseaza_ls(gps *ls)
{
    gps* temp=ls;
    while(temp!=NULL)
    {
        printf("%d ",temp->cod);
        temp=temp->urm;
    }
    printf("\n");
}
void afiseaza_lp(firma *lp)
{
    firma *temp=lp;
    while(temp!=NULL)
    {
        printf("%s: ",temp->nume);
        afiseaza_ls(temp->urm_ls);
        temp=temp->urm_lp;
    }
    printf("\n");
}
int main(void)
{   
    firma *lp=NULL;

    lp=adauga_firma("firma1",lp);
    lp=adauga_firma("firma2",lp);
    lp=adauga_firma("firma3",lp);

    lp=adauga_gps(1,"firma1",lp);
    lp=adauga_gps(2,"firma1",lp);
    lp=adauga_gps(3,"firma1",lp);
    lp=adauga_gps(0,"firma1",lp);

    lp=elimina_gps(2,lp);

    afiseaza_lp(lp);

    return 0;
}