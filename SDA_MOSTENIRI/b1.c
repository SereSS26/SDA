#include <stdio.h>

int a[6] = {'a','b','c'};
int v[11];
int n = 10;

int ct=0;

void afisare(int pos)
{
    for (int i = 0; i < n; i++)
    {
        printf("%c ", v[i]);
    }
    printf("\n");
}

int valid(int pos)
{   int cta=0;
    int ctb=0;
    int ctc=0;
    for(int i=0;i<=pos;i++)
        {
            if(v[i]=='a')
            cta++;
            if(v[i]=='b')
            ctb++;
            if(v[i]=='c')
            ctc++;

        }
    if(cta>3)
        return 0;
    if(ctb>4)
        return 0;
    if(ctc>3)
        return 0;

    return 1;
}

int solutie(int pos)
{

    if (pos == n-1)
        return 1;

    return 0;
}

void back(int k)
{   if(ct<6)
    for (int i = 0; i < 3; i++)
    {
        v[k] = a[i];
        if (valid(k))
            if (solutie(k))
                {
                    afisare(k);
                    ct++;
                }
            else
                back(k + 1);
    }
}



int main()
{
    back(0);
    return 0;
}