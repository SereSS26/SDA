#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct produs{
    int cod;
    struct produs *urm;
}produs;

typedef struct magazin{
    char nume[25];
    struct produs *urm_ls;
    struct magazin *urm_lp;
}magazin;

magazin* new_magazin(char *nume)
{
    magazin *q=NULL;
    q=(magazin*)malloc(sizeof(magazin));
    if(q==NULL)
    {
        perror("Eroare la aloacrea dinamica a emoriei\n");
        exit(-1);
    }
    strcpy(q->nume,nume);
    q->urm_lp=NULL;
    q->urm_ls=NULL;
    return q;
}
produs* new_produs(int cod)
{
    produs *q=NULL;
    q=(produs*)malloc(sizeof(produs));
    if(q==NULL)
    {
        perror("Eroare la alocarea dinamica a meoriei\n");
        exit(-1);
    }
    q->cod=cod;
    q->urm=NULL;
    return q;
}

produs* adauga_produs_ordonat(int cod,produs *ls)
{   
    produs *q=new_produs(cod);
    produs *temp=ls;
    if(temp==NULL)
    {
        q->urm=temp;
        temp=q;
        ls=temp;
        return ls;
    }
    if(temp!=NULL&&q->cod<temp->cod)
    {
        q->urm=temp;
        temp=q;
        ls=temp;
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

magazin* adauga_produs(int cod,char *nume,magazin *lp)
{
    magazin *temp=lp;
    while(temp!=NULL)
    {
        if(strcmp(temp->nume,nume)==0)
        {   
            temp->urm_ls=adauga_produs_ordonat(cod,temp->urm_ls);
            return lp;
        }
        temp=temp->urm_lp;
    }
    return lp;
}
magazin* adauga_magazin(char *nume,magazin *lp)
{
    magazin *q=new_magazin(nume);
    if(lp==NULL)
    {
        lp=q;
        return lp;
    }
    q->urm_lp=lp;
    lp=q;
    return lp;
}

magazin* elimina_produs(int cod,magazin *lp)
{
    magazin *temp=lp;
    while(temp!=NULL)
    {   
        produs *prev=NULL;
        produs *curent=temp->urm_ls;
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
                produs *el=curent;
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

void afisare_ls(produs *ls)
{
    produs *temp=ls;
    while(temp!=NULL)
    {
        printf("%d ",temp->cod);
        temp=temp->urm;
    }
    printf("\n");
}
void afisare_lp(magazin *lp)
{
    magazin *temp=lp;
    while(temp!=NULL)
    {
        printf("%s: ",temp->nume);
        afisare_ls(temp->urm_ls);
        temp=temp->urm_lp;
    }
    printf("\n");
}

int main(void)
{   
    magazin *lp=NULL;
    lp=adauga_magazin("magazin1",lp);
    lp=adauga_magazin("magazin2",lp);
    lp=adauga_magazin("magazin3",lp);

    lp=adauga_produs(2,"magazin1",lp);
    lp=adauga_produs(0,"magazin1",lp);
    lp=adauga_produs(1,"magazin1",lp);
    lp=adauga_produs(3,"magazin1",lp);

    lp=adauga_produs(2,"magazin2",lp);
    lp=adauga_produs(0,"magazin2",lp);
    lp=adauga_produs(1,"magazin2",lp);
    lp=adauga_produs(3,"magazin2",lp);

    lp=adauga_produs(2,"magazin3",lp);
    lp=adauga_produs(0,"magazin3",lp);
    lp=adauga_produs(1,"magazin3",lp);
    lp=adauga_produs(3,"magazin3",lp);

    lp=elimina_produs(3,lp);

    afisare_lp(lp);
    return 0;
}