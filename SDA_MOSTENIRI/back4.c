#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 6

int a[]={0,1};
int v[MAX];
int contor=0;

int valid(int k)
{
    int contor_0=0;
    int contor_1=0;
    int i=0;
    for(i=0;i<=k;i++)
    {
        if(v[i]==0)
            contor_0++;
        if(v[i]==1)
            contor_1++;
    }
    if(contor_0>2||contor_1>4)
        return 0;
    if(k==1&&v[k]==1&&v[k-1]==1)
        return 0;
    if(k==5&&v[k]==0)
        return 0;
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
        printf("%d",v[i]);
    }
    printf("\n");
}
void back(int k)
{
    int i=0;
    if(contor<3)
    {
        for(i=0;i<2;i++)
        {
            v[k]=a[i];
            if(valid(k)==1)
            {
                if(solutie(k)==1)
                {
                    afisare(k);
                    contor++;
                }
                else
                {
                    back(k+1);
                }
            }
        }
    }
}
int main(void)
{
    back(0);

    return 0;
}