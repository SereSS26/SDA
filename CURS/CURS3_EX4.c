#include <stdio.h>

unsigned long long factorial(int n) 
{
    unsigned long long r=1;
    int i=0;
    for(i=1;i<=n;i++) 
    {
        r=r*i;
    }
    return r;
}

int main(void)
{
    int n;
    scanf("%d",&n);
    unsigned long long f=factorial(n);
    printf("Factorialul lui %d este:%llu\n",n,f);

    return 0;
}
