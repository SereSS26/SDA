#include <stdio.h>
#include <stdlib.h>
#define HASH_SIZE 1000

int hash(int key) 
{
    return abs(key)%HASH_SIZE;
}
int existaDuplicate(int a[],int n) 
{   
    int i=0;
    int index;
    int hashTablou[HASH_SIZE]={0};
    int ok=0;
    for(i=0;i<n;i++) 
    {
        index=hash(a[i]);
        if(hashTablou[index]!=0)
        {   
            ok=1;
            return ok;
        }
        hashTablou[index]=1;
    }
    return ok;
}
int main(void) 
{
    int a[]={1,2,3,4,5,6,2};
    int n=7;
    if (existaDuplicate(a,n)) 
    {
        printf("Exista duplicate in tablou\n");
    } 
    else 
    {
        printf("Nu exista duplicate in tablou\n");
    }

    return 0;
}
