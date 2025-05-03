 #include <stdio.h>
 #include <stdlib.h>
 #include <string.h>
 #define MAX 20

 typedef struct tip_nod{
    int cheie;
    char nume[MAX];
    struct tip_nod *urm;
 }tip_nod;
 typedef tip_nod *tip_lista;
 void insereaza(tip_lista *prim,int cheie,char *nume)
 {
    tip_nod *q=NULL;
    q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q!=NULL)
    {
        q->cheie=cheie;
        strcpy(q->nume,nume);
        q->urm=*prim;
    }
    *prim=q;
 }
void afiseaza(tip_lista prim)
{
    while(prim!=NULL)
    {
        printf("%d %s\n",prim->cheie,prim->nume);
        prim=prim->urm;
    }
    printf("\n");
}
void elibereaza(tip_lista *prim)
{
    tip_nod *temp=*prim;
    while(*prim!=NULL)
    {
        temp=*prim;
        *prim=(*prim)->urm;
        free(temp);
    }
}
int cauta(tip_lista prim,int cheie)
{
    int pozitie=-1;
    while(prim!=NULL)
    {
        pozitie++;
        if(prim->cheie==cheie)
            return pozitie;
        prim=prim->urm;
    }
    return -1;
}
void stergere(tip_lista *prim,int pozitie)
{
    if(pozitie==-1)
    {
        printf("Nu e in lista\n");
        return;
    }
    int contor=0;
    tip_nod *curent=*prim;
    tip_nod *anterior=NULL;
    if(pozitie==0)
    {
        *prim=(*prim)->urm;
        free(curent);
        return;
    }
    while(curent!=NULL)
    {
        if(contor==pozitie)
        {
            anterior->urm=curent->urm;
            free(curent);
            return;
        }   
        anterior=curent;
        curent=curent->urm;
        contor++;
    }
}
 int main(void)
 {  
    tip_lista prim=NULL;  
    int pozitie=-1;
    insereaza(&prim,1,"a");
    insereaza(&prim,2,"b");
    insereaza(&prim,3,"c");
    insereaza(&prim,4,"d");
    insereaza(&prim,5,"f");
    afiseaza(prim); 
    pozitie=cauta(prim,3);
    stergere(&prim,pozitie);
    afiseaza(prim);
    elibereaza(&prim);   

    return 0;
 }