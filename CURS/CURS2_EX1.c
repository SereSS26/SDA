#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
//Numerele sunt de la 0 la 1000,adica 1001 numere.
#define SIZE 1001/8+1001%8
//Dimeniunea vectorului va fi de 126 de elemente in acest caz,deoarece fiecare element va avea cate 8 biti(8*125==1000),deci avem nevoie de mai un element pentru a stoca si aparitia valorii 1000 in multime.
void showBits8(uint8_t n,FILE *gis)
{
    int i=0;
    for(i=sizeof(n)*8-1;i>=0;i--)
    {
        fprintf(gis,"%d",(n>>i)&1);//am pus numerele pe biti in fiser.
    }
    fprintf(gis,"\n");
}
void setbit(int n,uint8_t *v,int m1,int m2)
{
    v[m1]=v[m1]|(1<<m2);//setam bitul,asta inseamna ca numarul n se regasete in multime si bitul din al m1-lea element(n/8),de pe pozitia m2(n%8) va devenii 1.
}
void citire(FILE *fis,uint8_t *v)
{   
    int n=0;
    while(fscanf(fis,"%d",&n)==1)
    {
        setbit(n,v,n/8,n%8);//functie de setare a bitului potirivit/corespunzator pentru un numar n din intervalul [0,1000].
    }
}
/*
Explicatie:
Am considerat LSB al primului element corespondentul lui 0 din multimea numerelor date din intervalul [0,1000].
Daca de exemplu primeam ca elemente ale multimii numerele 0,1,7,8,999,1000,atunci vectorul nostru avea urmatoarele elemente pe biti:
10000011(MSB 7->apare,6->nu apare,...,0(LSB)->apare),
00000001(LSB 8->apare,...),
...
...
...
10000000(MSB 999->apare,...),
00000001(LSB 1000->apare)
*/
int main(void)
{   
    uint8_t *v=NULL;
    int i=0;
    FILE *fis=NULL,*gis=NULL;
    fis=fopen("bits.in","r");
    if(fis==NULL)
    {
        perror("Eroare la deschidere fisier bits.in\n");
        exit(-1);
    }   
    v=(uint8_t*)calloc(SIZE,sizeof(uint8_t));//am folosit calloc pentru a initializa toate elementele din vector cu 0(pentru a avea toti bitii 0 la inceput)
    if(v==NULL)
    {
        perror("Eroare la alocarea memoriei dinamice\n");
        exit(-1);
    }
    citire(fis,v);//functie de citire a datelor.
    fclose(fis);
    gis=fopen("bits.out","w");
    if(gis==NULL)
    {
        perror("Eroare la deschidere fisier bits.out\n");
        exit(-1);
    }
    for(i=0;i<SIZE;i++)
    {
        showBits8(v[i],gis);//functie pentru a vedea bitii.
    }
    fclose(gis);
    free(v);//eliberam memoria alocata dinamic.

    return 0;   
}

///SAU SE MAI POATE FOLOSII O STRUCTURA DE GENUL:
///
///typedef struct {
///int *digits;     // Pointer către cifrele numărului
///int size;        // Numărul de cifre
///int sign;        // Semnul numărului: 1 pentru pozitiv, -1 pentru negativ
///} BigInt;
