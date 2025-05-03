#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 20

typedef struct lista_secundara{
    char nume[MAX];
    int numar;
    struct lista_secundara *urm;
}lista_secundara;

typedef struct lista_principala{
    char nume[MAX];
    int numar;
    struct lista_secundara *urm;
}lista_principala;
typedef lista_principala *Lista_principala;

typedef struct multi_lista{
    lista_principala lista[MAX];
    int ultim;
}multi_lista;
typedef multi_lista *Multi_lista;

void initializeaza_Multi_lista(Multi_lista *Prim)
{
    *Prim=(multi_lista*)malloc(sizeof(multi_lista*));
    if(Prim==NULL)
    {
        perror("Eroare la alocarea memorie dinamice\n");
        exit(-1);
    }
    (*Prim)->ultim=0;
}
void initializeaza_Lista_principala(Lista_principala *prim,char *nume,int numar)
{
    *prim=(lista_principala*)malloc(sizeof(lista_principala));
    if(prim==NULL)
    {
        perror("Eroare la alocarea dinamica\n");
        exit(-1);
    }
    (*prim)->numar=numar;
    strcpy((*prim)->nume,nume);
}
void adauga_lista_principala1(Multi_lista *Prim,char *nume,int numar)
{
    (*Prim)->lista[(*Prim)->ultim].numar=numar;
    strcpy((*Prim)->lista[(*Prim)->ultim].nume,nume);
    (*Prim)->ultim++;
}
void adauga_lista_principala2(Multi_lista *Prim,Lista_principala prim)
{
    (*Prim)->lista[(*Prim)->ultim]=*prim;
    (*Prim)->ultim++;
}
void adauaga_lista_secundara1(Multi_lista *Prim,int Cheie,char *nume,int numar)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        if((*Prim)->lista[i].numar==Cheie)
        {
            lista_secundara *q=NULL;
            q=(lista_secundara*)malloc(sizeof(lista_secundara));
            if(q==NULL)
            {
                perror("Eroare la alocarea memoriei\n");
                exit(-1);
            }
            q->numar=numar;
            strcpy(q->nume,nume);
            q->urm=NULL;
            q->urm=(*Prim)->lista[i].urm;
            (*Prim)->lista[i].urm=q;
            return;
        }
    }
}
void adauaga_lista_secundara2(Multi_lista *Prim,Lista_principala prim,char *nume,int numar)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        if((*Prim)->lista[i].numar==prim->numar)
        {   
            lista_secundara *q=NULL;
            q=(lista_secundara*)malloc(sizeof(lista_secundara));
            if(q==NULL)
            {
                perror("Eroare la alocarea memoriei\n");
                exit(-1);
            }
            q->numar=numar;
            strcpy(q->nume,nume);
            q->urm=NULL;
            q->urm=(*Prim)->lista[i].urm;
            (*Prim)->lista[i].urm=q;
            return;
        }
    }
}
void elimina(Multi_lista *Prim,int numar)
{
    int i=0;
    for(i=0;i<(*Prim)->ultim;i++)
    {
        lista_secundara *temp=(*Prim)->lista[i].urm;
        lista_secundara *anterior=NULL;
        while(temp!=NULL)
        {
            if(temp->numar==numar)
            {
                if(anterior==NULL)
                {
                    (*Prim)->lista[i].urm=temp->urm;
                    free(temp);
                    return;
                }
                else
                {
                    anterior->urm=temp->urm;
                    free(temp);
                    return;
                }
            }
            anterior=temp;
            temp=temp->urm;
        }
    }
}
void afiseaza_Multi_lista(Multi_lista Prim)
{
    int i=0;
    for(i=0;i<Prim->ultim;i++)
    {
        printf("%d %s:\n",Prim->lista[i].numar,Prim->lista[i].nume);
        lista_secundara *temp=Prim->lista[i].urm;
        while(temp!=NULL)
        {
            printf("%d %s\n",temp->numar,temp->nume);
            temp=temp->urm;
        }
    }
    printf("\n");
}
int main(void)
{   
    Multi_lista Prim=NULL;
    Lista_principala prim=NULL;
    initializeaza_Multi_lista(&Prim);
    adauga_lista_principala1(&Prim,"numar1",1);
    initializeaza_Lista_principala(&prim,"numar2",2);
    adauga_lista_principala2(&Prim,prim);
    adauaga_lista_secundara1(&Prim,1,"n1",1);
    adauaga_lista_secundara2(&Prim,prim,"n2",2);
    afiseaza_Multi_lista(Prim);
    elimina(&Prim,2);
    afiseaza_Multi_lista(Prim);

    return 0;
}