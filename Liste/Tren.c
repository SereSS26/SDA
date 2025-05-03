#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define LUNGIME_NUME 20
#define MAXIM_VAGOANE 5

typedef struct pasager{
    char nume[LUNGIME_NUME];
    int id_pasager;
    struct pasager *urm;
}pasager;

typedef struct vagon{
    int id_vagon;
    int numar_vagon;
    struct pasager *prim;
}vagon;
typedef vagon *vagon1;

typedef struct tren{
    vagon vagoane[MAXIM_VAGOANE];
    int ultim;
}tren;
typedef tren *locomotiva;

void initializeaza(locomotiva *Locomotiva)
{
    *Locomotiva=(tren*)malloc(sizeof(tren));
    (*Locomotiva)->ultim=0;
    int i=0;
    for(i=0;i<MAXIM_VAGOANE;i++)
    {
        (*Locomotiva)->vagoane[i].prim=NULL;
    }
}
void adauga_vagon1(locomotiva *Locomotiva,int numar_vagon,int id_vagon)
{
    (*Locomotiva)->vagoane[(*Locomotiva)->ultim].numar_vagon=numar_vagon;
    (*Locomotiva)->vagoane[(*Locomotiva)->ultim].id_vagon=id_vagon;
    (*Locomotiva)->ultim++;
}
void adauga_vagon2(locomotiva *Locomotiva,vagon *Vagon)
{
    (*Locomotiva)->vagoane[(*Locomotiva)->ultim]=*Vagon;
    (*Locomotiva)->ultim++;
}
void initializeaza_vagon(vagon1 *Vagon,int numar_vagon,int id_vagon)
{
    *Vagon=(vagon*)malloc(sizeof(vagon));
    (*Vagon)->numar_vagon=numar_vagon;
    (*Vagon)->id_vagon=id_vagon;
}
void adauga_pasager2(vagon1 *Vagon,char *nume,int id_pasager)
{
    pasager *temp=NULL;
    temp=(pasager*)malloc(sizeof(pasager));
    temp->id_pasager=id_pasager;
    strcpy(temp->nume,nume);
    temp->urm=(*Vagon)->prim;
    (*Vagon)->prim=temp;
}
void afiseaza_tren(locomotiva Locomotiva)
{
    int i=0;
    for(i=0;i<Locomotiva->ultim;i++)
    {
        printf("%d %d:\n",Locomotiva->vagoane[i].numar_vagon,Locomotiva->vagoane[i].id_vagon);
        pasager *temp=Locomotiva->vagoane[i].prim;
        while(temp!=NULL)
        {
            printf("%d %s\n",temp->id_pasager,temp->nume);
            temp=temp->urm;
        }
    }
    printf("\n");
}
int main(void)
{   
    locomotiva Locomotiva=NULL;
    initializeaza(&Locomotiva);
    vagon1 Vagon1=NULL;
    vagon1 Vagon2=NULL;
    initializeaza_vagon(&Vagon1,3,3003);
    initializeaza_vagon(&Vagon2,4,4004);
    adauga_vagon1(&Locomotiva,1,1001);
    adauga_vagon1(&Locomotiva,2,2002);
    adauga_pasager2(&Vagon1,"Artur",1);
    adauga_vagon2(&Locomotiva,Vagon1);
    adauga_vagon2(&Locomotiva,Vagon2);
    afiseaza_tren(Locomotiva);

    return 0;
}