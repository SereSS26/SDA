#include <stdio.h>
#include <string.h>
#include <stdlib.h>
///BILETE_AVION
typedef struct rezervare{
	int id_rezervare;
	char nume[100];
	struct rezervare* urm;
}rezervare;
typedef rezervare* tip_lista_rezervari;
typedef struct zbor{
    int id_zbor;
    char nume_zbor[100];
    struct rezervare *lista_rezervari;
    struct zbor *urm;
}zbor;
typedef zbor *multi_lista;
multi_lista prim_zbor=NULL;
tip_lista_rezervari adauga_rezervare(tip_lista_rezervari *prim,int id_rezervare,char *nume)
{       
    rezervare *curent=*prim;
    rezervare *q=NULL;
    q=(rezervare*)malloc(sizeof(rezervare));
    if(q!=NULL)
    {
        q->id_rezervare=id_rezervare;
        strcpy(q->nume,nume);
        q->urm=NULL;
    }
    if(curent==NULL)
    {
        *prim=q;
        return *prim;
    }
    if(*prim!=NULL&&strcmp((*prim)->nume,nume)>0)
    {   
        q->urm=*prim;
        *prim=q;
        return *prim;
    }
    while(curent->urm!=NULL&&strcmp(curent->urm->nume,q->nume)<0)
    {
        curent=curent->urm;
    }
    q->urm=curent->urm;
    curent->urm=q;
    return *prim;
}
void elimina_rezervare(tip_lista_rezervari *prim,int cheie)
{
    rezervare *curent=*prim;
    rezervare *anterior=NULL;
    while(curent!=NULL&&curent->id_rezervare!=cheie)
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
void afiseaza_lista_rezervari(tip_lista_rezervari prim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->id_rezervare,prim->nume);
        prim=prim->urm;
    }
}
void elibereaza_memorie_lista_rezervari(tip_lista_rezervari *prim)
{
    rezervare *temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        *prim=(*prim)->urm;
        free(temp);
    }
}
multi_lista adauga_zbor(int id_zbor,char *nume_zbor)
{
    zbor *curent=prim_zbor;
    zbor *q=NULL;
    q=(zbor*)malloc(sizeof(zbor));
    if(q!=NULL)
    {
        q->id_zbor=id_zbor;
        strcpy(q->nume_zbor,nume_zbor);
        q->urm=NULL;
    }
    if(curent==NULL)
    {
        prim_zbor=q;
        return prim_zbor;
    }
    if(prim_zbor!=NULL&&strcmp(prim_zbor->nume_zbor,nume_zbor)>0)
    {   
        q->urm=prim_zbor;
        prim_zbor=q;
        return prim_zbor;
    }
    while(curent->urm!=NULL&&strcmp(curent->urm->nume_zbor,q->nume_zbor)<0)
    {
        curent=curent->urm;
    }
    q->urm=curent->urm;
    curent->urm=q;
    return prim_zbor;
}
int cauta_rezervare(int id_avion,int id_rezervare)
{
    zbor *curent=prim_zbor;
    while(curent!=NULL&&curent->id_zbor!=id_avion)
    {
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        rezervare *curent1=curent->lista_rezervari;
        while(curent1!=NULL&&curent1->id_rezervare!=id_rezervare)
        {
            curent1=curent1->urm;
        }
        if(curent1!=NULL)
        {
            return 1;
        }
    }
    return 0;
}
multi_lista adauga_pasager_la_zbor(int id_zbor,int id,char *nume)
{   
    zbor *curent=prim_zbor;
    while(curent!=NULL&&curent->id_zbor!=id_zbor)
    {
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        curent->lista_rezervari=adauga_rezervare(&curent->lista_rezervari,id,nume);
    }
    return prim_zbor;
}
void elimina_pasager_la_zbor(zbor *prim_zbor,int id_zbor,int id,char *nume)
{
    zbor *curent=prim_zbor;
    while(curent!=NULL&&curent->id_zbor!=id_zbor)
    {
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        elimina_rezervare(&(curent->lista_rezervari),id);
    }
}
void afiseaza_lista_zboruri(multi_lista prim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->id_zbor,prim->nume_zbor);
        afiseaza_lista_rezervari(prim->lista_rezervari);
        prim=prim->urm;
    }
}
void elibereaza_memorie_lista_zbor(multi_lista *prim)
{
    zbor *temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        *prim=(*prim)->urm;
        elibereaza_memorie_lista_rezervari(&temp->lista_rezervari);
        free(temp);
    }
}
int main(void)
{       
    int opt=0;
    int id_rezervare=0;
    char nume[100];
    prim_zbor=adauga_zbor(1,"Roma-Paris");
    prim_zbor=adauga_zbor(2,"Paris-Roma");
    afiseaza_lista_zboruri(prim_zbor);
    do
    {   
        scanf("%d",&opt);
        switch(opt)
        {
            case 1:
                ///!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                adauga_pasager_la_zbor(1,6,"Alina");
                ////!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                adauga_pasager_la_zbor(1,1,"Cosmin");
                adauga_pasager_la_zbor(2,2,"Tobi");
                adauga_pasager_la_zbor(2,3,"Solo");
                adauga_pasager_la_zbor(1,4,"Artur");
                adauga_pasager_la_zbor(1,5,"Mirela");
                break;
            case 2:
                elimina_pasager_la_zbor(prim_zbor,2,2,"Tobi");
                break;
            case 3:
                if(cauta_rezervare(1,1)!=0)
                {
                    printf("DA\n");
                }
                else
                {
                    printf("NU\n");
                }
                break;
            case 4:
                afiseaza_lista_zboruri(prim_zbor);
                break;
            case 0:
                elibereaza_memorie_lista_zbor(&prim_zbor);
                break;
            default:
                break;
        }
    }while(opt!=0);

    return 0;
}