#include <stdio.h>
#include <string.h>
#include <stdlib.h>
///BILETE DE AVION

///1.ListaTablou
#define lung_max 100
typedef int tip_indice;
typedef struct tipnod
{
	int info;
} tipnod;
typedef struct tiplista
{
	tipnod noduri[lung_max];
	tip_indice ultim;
} tiplista;
typedef tip_indice tip_pozitie;
typedef unsigned boolean;
#define true (1)
#define false (0)
boolean reccmp(tipnod x, tipnod y);/*comparare conţinut  noduri*/
void insereaza(tiplista* l, tipnod x,tip_pozitie p, boolean* er)/*plasează pe x în poziţia p a listei; performanţa O(n)*/
{
	tip_pozitie q;
	*er = false;
	if (l->ultim >= (lung_max - 1)) {
		*er = true;
		printf("lista este plina");
	}
	else
		if ((p > l->ultim + 1) || (p < 0)) {
			*er = true;
			printf("pozitie invalida");
		}
		else {
			for (q = l->ultim + 1; q > p; q--)
				l->noduri[q] = l->noduri[q - 1];//se face loc pentru noul element
			l->noduri[p] = x;					//se insereaza elementul
			l->ultim++;							//se incrementeaza numarul de elemente
		}
} /*insereaza*/
boolean reccmp(tipnod x, tipnod y)
/*comparare conţinut noduri*/
{
	if (x.info == y.info)
		return true;
	else
		return false;
}
tip_pozitie cauta1(tipnod x, tiplista l)
{
	/*returnează poziţia lui x în listă*/
	tip_pozitie q;
	boolean gasit;
	tip_pozitie cauta_result;
	q = 0; gasit = false; /*performanţa O(n)*/
	do {
		if (reccmp(l.noduri[q], x) != 0) {
			cauta_result = q;
			gasit = true;
		}
		q = q + 1;
	} while (!(gasit || (q == l.ultim + 1)));
	if (!gasit) cauta_result = -1;
	return cauta_result;
}
/*cauta*/
void suprima(tiplista* l, tip_pozitie p, boolean* er)
/*extrage elementul din poziţia p a listei*/
{
	tip_pozitie q; /*performanţa O(n)*/
	*er = false;
	if ((p > l->ultim + 1) || (p < 0)) {
		*er = true;
		printf("pozitie invalida");
	}
	else {
		for (q = p; q <= l->ultim; q++)
			l->noduri[q] = l->noduri[q + 1];
		l->ultim = l->ultim - 1;
	}
} /*suprima*/
void afiseaza_lista_tablou(tiplista *lista)
{
    for(int i=0;i<=lista->ultim;i++)
    {
        printf("%d ",lista->noduri[i].info);
    }
    printf("\n");
}

///2.ListaPointeri_SIMPLA
/*
typedef struct tip_nod{
	int cheie;
	char info[100];
	struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_lista;
tip_lista prim = NULL;
tip_lista ultim = NULL;
tip_lista insertie_final_sortata(int cheie, char *info)
{
	tip_nod* q; //noul nod
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
    q->cheie=cheie;
    strcpy(q->info,info);
    q->urm=NULL;
    tip_nod *curent=prim;
    if(prim==NULL)
    {
        prim=q;
        return prim;
    }
    if(prim!=NULL&&strcmp(prim->info,q->info)>0)
    {
        q->urm=prim;
        prim=q;
    }
    else
    {
        while(curent->urm!=NULL&&strcmp(curent->urm->info,q->info)<0)
        {
            curent=curent->urm;
        }
        q->urm=curent->urm;
        curent->urm=q;
    }
    return prim;
}
tip_nod* cauta(int cheie)
{
	tip_nod* p;
	//cat timp nu am gasit cheia si nu am ajuns la capatul listei avansez in lista
	for (p = prim; (p != NULL) && (p->cheie != cheie); p = p->urm);
	//atentie: conteaza ordinea celor doua contitii, deoarece in C expresiile logice se evalueaza in scurtcircuit
	return p; //functia returneaza NULL in caz ca nu a gasit cheia
}
tip_lista stergere_element_lista(int cheie)
{
    tip_nod *curent=prim;
    tip_nod *anterior=NULL;
    while(curent!=NULL&&curent->cheie!=cheie)
    {   
        anterior=curent;
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        anterior->urm=curent->urm;
    }
    free(curent);
    return prim;
}
void afiseaza_lista(tip_lista prim)
{
    while(prim!=NULL)
    {
        printf("%s ",prim->info);
        prim=prim->urm;
    }
    printf("\n");
}
void elibereaza_memorie_lista(tip_lista *prim)
{
    tip_nod *temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        (*prim)=(*prim)->urm;
        free(temp);
    }
}
*/

///ListaPointeri_DUBLU
/*
typedef int tip_info;
typedef struct tip_nod{
	int cheie;
	char info[100];
	struct tip_nod* urm;
    struct tip_nod *prev;
} tip_nod;
typedef tip_nod* tip_lista;
tip_lista prim = NULL;
tip_lista ultim = NULL;
tip_lista insertie_final_sortata(int cheie, char *info)
{
	tip_nod* q; //noul nod
    tip_nod *curent=prim;
	q = (tip_nod*)malloc(sizeof(tip_nod)); // aloc spatiu pentru noul nod
    q->cheie = cheie;
	strcpy(q->info,info);//asignez valorile primite ca parametru
	q->urm = NULL;
    q->prev=NULL;
    if(prim==NULL)
    {
        prim=q;
        return prim;
    }
    if(prim!=NULL&&strcmp(prim->info,info)>0)
    {
        prim->prev=q;
        q->urm=prim;
        prim=q;
    }
    else
    {
        while(curent->urm!=NULL&&strcmp(curent->urm->info,q->info)<0)
        {
            curent=curent->urm;
        }
        q->urm=curent->urm;
        q->prev=curent;
        curent->urm=q;
    }
	return prim;
}
void afiseaza_lista(tip_lista prim)
{
    while(prim!=NULL)
    {
        printf("%s ",prim->info);
        prim=prim->urm;
    }
    printf("\n");
}
tip_nod* cauta(int cheie)
{
	tip_nod* p;
	//cat timp nu am gasit cheia si nu am ajuns la capatul listei avansez in lista
	for (p = prim; (p != NULL) && (p->cheie != cheie); p = p->urm);
	//atentie: conteaza ordinea celor doua contitii, deoarece in C expresiile logice se evalueaza in scurtcircuit
	return p; //functia returneaza NULL in caz ca nu a gasit cheia
}
tip_lista stergere_element_lista(int cheie)
{   
    tip_nod *curent=prim;
    while(curent!=NULL&&curent->cheie!=cheie)
    {
        curent=curent->urm;
    }
    if(curent!=NULL)
    {
        curent->prev->urm=curent->urm;
        curent->urm->prev=curent->prev;
        free(curent);
    }
    return prim;
}
void elibereaza_memorie_lista(tip_lista *prim)
{
    tip_nod *temp=NULL;
    while(*prim!=NULL)
    {
        temp=*prim;
        *prim=(*prim)->urm;
        free(temp);
    }
}
*/
///MULTILISTA
typedef struct rezervare{
	int id_rezervare;
	char nume_pasager[100];
	struct rezervare* urm;
}rezervare;
typedef struct zbor{
    int id_zbor;
    char nume_zbor[100];
    struct rezervare *lista_rezervari;
    struct zbor *urm;
}zbor;
typedef zbor *mult_lista;

zbor* creare_zbor(int id_zbor, char* nume_zbor) 
{
    zbor* nou = (zbor*)malloc(sizeof(zbor));
    nou->id_zbor = id_zbor;
    strcpy(nou->nume_zbor, nume_zbor);
    nou->lista_rezervari = NULL;
    nou->urm = NULL;
    return nou;
}
void adauga_zbor(mult_lista* lista, int id_zbor, char* nume_zbor) {
    zbor* nou = creare_zbor(id_zbor, nume_zbor);
    nou->urm = *lista;
    *lista = nou;
}
rezervare* creare_rezervare(int id_rezervare, char* nume_pasager) {
    rezervare* nou = (rezervare*)malloc(sizeof(rezervare));
    nou->id_rezervare = id_rezervare;
    strcpy(nou->nume_pasager, nume_pasager);
    nou->urm = NULL;
    return nou;
}
void adauga_rezervare(zbor* z, int id_rezervare, char* nume_pasager) {
    rezervare* nou = creare_rezervare(id_rezervare, nume_pasager);
    rezervare* curent = z->lista_rezervari;
    rezervare* anterior = NULL;

    // Inserare ordonată după numele pasagerilor
    while (curent != NULL && strcmp(curent->nume_pasager, nume_pasager) < 0) {
        anterior = curent;
        curent = curent->urm;
    }

    if (anterior == NULL) { // Inserare la început
        nou->urm = z->lista_rezervari;
        z->lista_rezervari = nou;
    } else { // Inserare la mijloc sau final
        nou->urm = curent;
        anterior->urm = nou;
    }
}
void anuleaza_rezervare(zbor* z, int id_rezervare) {
    rezervare* curent = z->lista_rezervari;
    rezervare* anterior = NULL;

    while (curent != NULL && curent->id_rezervare != id_rezervare) {
        anterior = curent;
        curent = curent->urm;
    }

    if (curent != NULL) { // Rezervarea găsită
        if (anterior == NULL) { // Prima rezervare
            z->lista_rezervari = curent->urm;
        } else { // Orice altă poziție
            anterior->urm = curent->urm;
        }
        free(curent);
        printf("Rezervarea cu ID %d a fost anulată.\n", id_rezervare);
    } else {
        printf("Rezervarea cu ID %d nu a fost găsită.\n", id_rezervare);
    }
}
void afiseaza_rezervari(zbor* z) {
    printf("Rezervări pentru zborul %s:\n", z->nume_zbor);
    rezervare* curent = z->lista_rezervari;
    while (curent != NULL) {
        printf("ID rezervare: %d, Nume pasager: %s\n", curent->id_rezervare, curent->nume_pasager);
        curent = curent->urm;
    }
}
zbor* cauta_zbor(mult_lista lista, int id_zbor) {
    zbor* curent = lista;
    while (curent != NULL && curent->id_zbor != id_zbor) {
        curent = curent->urm;
    }
    return curent;
}

int main(void)
{       
    ///ListaTablou
    tiplista l;
	boolean er;
	l.ultim = -1;
	tipnod a = { 1 };
	insereaza(&l, a, 0, &er);
	a.info = 2;
	insereaza(&l, a, 1, &er);
	a.info = 3;
	insereaza(&l, a, 2, &er);
	a.info = 4;
	insereaza(&l, a, 3, &er);
	a.info = 4;
    afiseaza_lista_tablou(&l);
    a.info=2;
    printf("%d\n", cauta1(a, l));
    suprima(&l, 0, &er);
    afiseaza_lista_tablou(&l);
    printf("\n");

    ///ListaPointeri_SIMPLA
    ///Ex1)
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    /*
    prim = insertie_final_sortata(5, "5");
    prim = insertie_final_sortata(2, "2");
    prim = insertie_final_sortata(4, "4");
    prim = insertie_final_sortata(3, "3");
    prim = insertie_final_sortata(1, "1");
    afiseaza_lista(prim);
    if(cauta(3)!=NULL)
    {
        printf("DA\n");
    }
    stergere_element_lista(3);
    afiseaza_lista(prim);
    elibereaza_memorie_lista(&prim);
    printf("\n");
    */
    //!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!

    ///ListaPointeri_DUBLU
    ///Ex1)
    /*
    prim = insertie_final_sortata(5, "5");
    prim = insertie_final_sortata(2, "2");
    prim = insertie_final_sortata(4, "4");
    prim = insertie_final_sortata(3, "3");
    prim = insertie_final_sortata(1, "1");
    afiseaza_lista(prim);
    if(cauta(3)!=NULL)
    {
        printf("DA\n");
    }
    stergere_element_lista(3);
    afiseaza_lista(prim);
    elibereaza_memorie_lista(&prim);
    */

    ///MULTI_LISTE
    ///Ex2)
    mult_lista lista_zboruri = NULL;
    creare_zbor(1,"Timisoara-Buzau");
    adauga_zbor(&lista_zboruri,1,"Timisoara-Buzau");
    adauga_zbor(&lista_zboruri, 2, "Roma-Timisoara");
    zbor* z = cauta_zbor(lista_zboruri, 1);
    adauga_rezervare(z, 1, "Artur");
    adauga_rezervare(z,2,"Solo");
    adauga_rezervare(z,3,"Cosmin");
    afiseaza_rezervari(z);

    return 0;
}