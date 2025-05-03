#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 10

int a[]={0,1,2,3,4,5,6,7,8,9};
int v[MAX];


int valid(int k)
{
    if(k==0&&v[k]!=0)
        return 0;
    if(k==1&&v[k]!=7)
        return 0;
    if(k==2&&v[k]!=9)
        return 0;
    if(k==3&&v[k]!=9)
        return 0;
    if(k==9&&v[k]!=0)
        return 0;
    int i=0;
    for(i=1;i<=k;i++)
    {
        if(v[i]%2==0&&v[i-1]%2==0)
            return 0;
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
        printf("%d",v[i]);
    }
    printf("\n");
}
void back(int k)
{
    int i=0;
    for(i=0;i<10;i++)
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