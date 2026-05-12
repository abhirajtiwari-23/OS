#include <stdio.h>

void fit(int b[], int nb, int p[], int np, int type)
{
    int a[np];

    for(int i=0;i<np;i++) a[i] = -1;

    for(int i=0;i<np;i++)
    {
        int idx = -1;

        for(int j=0;j<nb;j++)
        {
            if(b[j] >= p[i])
            {
                if(type==0) { idx=j; break; }          // First Fit
                if(idx==-1 ||
                  (type==1 && b[j]<b[idx]) ||          // Best Fit
                  (type==2 && b[j]>b[idx]))            // Worst Fit
                    idx=j;
            }
        }

        if(idx!=-1)
        {
            a[i]=idx;
            b[idx]-=p[i];
        }
    }

    printf("\nPNo\tPSize\tBlock\n");

    for(int i=0;i<np;i++)
    {
        printf("%d\t%d\t", i+1, p[i]);

        if(a[i]!=-1)
            printf("%d\n", a[i]+1);
        else
            printf("NA\n");
    }
}

int main()
{
    int nb,np;

    printf("Enter no. of blocks: ");
    scanf("%d",&nb);

    int b[nb], b1[nb], b2[nb], b3[nb];

    printf("Enter block sizes:\n");
    for(int i=0;i<nb;i++)
    {
        scanf("%d",&b[i]);
        b1[i]=b2[i]=b3[i]=b[i];
    }

    printf("Enter no. of processes: ");
    scanf("%d",&np);

    int p[np];

    printf("Enter process sizes:\n");
    for(int i=0;i<np;i++)
        scanf("%d",&p[i]);

    printf("\nFIRST FIT");
    fit(b1,nb,p,np,0);

    printf("\nBEST FIT");
    fit(b2,nb,p,np,1);

    printf("\nWORST FIT");
    fit(b3,nb,p,np,2);

    return 0;
}
