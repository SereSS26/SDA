#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 3

int a[]={1,2,3,4,5,6};
/*
1->alb
2->galben
3->rosu
4->verde
5->albastru
6->negru
*/
int v[MAX];

int valid(int k)
{
    int contor_1=0;
    int contor_2=0;
    int contor_3=0;
    int contor_4=0;
    int contor_5=0;
    int contor_6=0;
    int i=0;
    for(i=0;i<=k;i++)
    {
        if(v[i]==1)
            contor_1++;
        if(v[i]==2)
            contor_2++;
        if(v[i]==3)
            contor_3++;
        if(v[i]==4)
            contor_4++;
        if(v[i]==5)
            contor_5++;
        if(v[i]==6)
            contor_6++;
    }
    if(contor_1>1||contor_2>1||contor_3>1||contor_4>1||contor_5>1||contor_6>1)
        return 0;
    if(k==1)
    {
        if(v[k]!=2&&v[k]!=4)
        {
            return 0;
        }
    }
    return 1;
}
int solutie(int k)
{
    if(k==MAX-1)
        return 1;
    return 0;
}
void afisare(int k)
{
    int i=0;
    for(i=0;i<=k;i++)
    {
        if(v[i]==1)
        {
            printf("alb ");
        }
        if(v[i]==2)
        {
            printf("galben ");
        }
        if(v[i]==3)
        {
            printf("rosu ");
        }
        if(v[i]==4)
        {
            printf("verde ");
        }
        if(v[i]==5)
        {
            printf("albastru ");
        }
        if(v[i]==6)
        {
            printf("negru ");
        }
    }
    printf("\n");
}
void back(int k)
{
    for(int i=0;i<6;i++)
    {   
        v[k]=a[i];
        if(valid(k)==1)
        {
            if(solutie(k)==1)
            {
                afisare(k);
            }
            else
            {
                back(k+1);
            }
        }
    }
}
int main(void)
{   
    back(0);

    return 0;
}