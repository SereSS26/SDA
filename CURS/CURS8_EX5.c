#include <stdio.h>
#include <stdlib.h>

typedef int tip_info;
typedef struct tip_nod {
    tip_info info;
    struct tip_nod* urm;
} tip_nod;
typedef tip_nod* tip_stiva;

void push(tip_stiva* top, tip_info val)
{
    tip_nod* q=(tip_nod*)malloc(sizeof(tip_nod));
    if(q==NULL)
    {
        printf("Eroare la alocarea memoriei\n");
        return;
    }
    q->info = val;
    q->urm = *top;
    *top=q;
}
tip_info pop(tip_stiva* top) 
{
    if(*top == NULL) 
    {
        printf("Stiva este goală!\n");
        return -1;
    }
    tip_nod* temp=*top;
    tip_info val=temp->info;
    *top=(*top)->urm;
    free(temp);
    return val;
}
void inverseaza_stiva(tip_stiva* top)
{
    if (*top == NULL) // Caz de oprire: dacă stiva este goală
        return;

    // Scoatem un element din stivă
    tip_info val = pop(top);

    // Inversăm restul stivei recursiv
    inverseaza_stiva(top);

    // Punem elementul înapoi în stivă, aceasta va fi pus în ordine inversă
    push(top, val);
}
void afisare_stiva(tip_stiva top)
{
    if(top==NULL)
    {
        printf("Stiva este goala\n");
        return;
    }
    while(top!=NULL)
    {
        printf("%d ",top->info);
        top=top->urm;
    }
    printf("\n");
}
void elibereaza_memorie(tip_stiva* top) 
{
    while(*top!=NULL)
    {
        pop(top);
    }
}
int main() 
{
    tip_stiva stiva=NULL;
    push(&stiva, 1);
    push(&stiva, 2);
    push(&stiva, 3);
    push(&stiva, 4);
    push(&stiva, 5);
    printf("Stiva inainte de inversare:\n");
    afisare_stiva(stiva);
    inverseaza_stiva(&stiva);
    printf("Stiva dupa inversare:\n");
    afisare_stiva(stiva);
    elibereaza_memorie(&stiva);

    return 0;
}
