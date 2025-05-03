#include <stdio.h>
#define MAX 1000

void SSM(int a[],int n)
{
    int maxSum=0;
    int curentSum=0;
    int start=0,end=0,temp=0;
    int i=0;
    for(i=0;i<n;i++)
    {
        curentSum=curentSum+a[i];
        if(curentSum>maxSum) 
        {
            maxSum=curentSum;
            start=temp;
            end=i;           
        }
        if(curentSum<0) 
        {
            curentSum=0;    
            temp=i+1;
        }
    }
    printf("Subsecvența cu suma maxima este de la indexul %d la %d.\n",start,end);
    printf("Suma maxima este: %d\n",maxSum);
}
int main(void)
{
    int n=0;
    int a[MAX];
    scanf("%d",&n);
    int i=0;
    for(i=0;i<n;i++)
    {
        scanf("%d",&a[i]);
    }
    SSM(a,n);

    return 0;
}
