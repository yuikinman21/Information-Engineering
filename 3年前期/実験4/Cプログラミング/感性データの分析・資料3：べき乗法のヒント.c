#include<stdio.h>
#include<math.h>
#define N 5
int main(void)
{
    int i,j;
    double Norm, y[N];
    double a[N][N]={{1.0,2.0,3.0,4.0,5.0},
                    {6.0,7.0,8.0,9.0,0.0},
                    {1.0,2.0,3.0,4.0,5.0},
                    {6.0,7.0,8.0,9.0,0.0},
                    {1.0,2.0,3.0,4.0,5.0}};

    double x[N]={1.0,2.0,3.0,4.0,5.0};

    printf("\n\n---行列Aの表示---");
    for(i=0; i<=N-1; i++)
    {
        printf("\n");
        for(j=0; j<=N-1; j++)
        {
            printf("%3.1lf,",a[i][j]);
        }
    }

    Norm=0.0;
    for(i=0; i<=N-1; i++)
    {
        Norm+=x[i]*x[i];
    }
    Norm=sqrt(Norm);
    for(i=0; i<=N-1; i++)
    {
        x[i]/=Norm;
    }

    printf("\n\n---基準化したベクトルxの表示---\n");
    for(i=0; i<=N-1; i++)
    {
        printf("%3.1lf,",x[i]);
    }


    for(i=0; i<=N-1; i++)
    {
        y[i]=0.0;
        for(j=0; j<=N-1; j++)
        {
            y[i]+=a[i][j]*x[j];
        }
    }

    printf("\n\n---行列Aと基準化したベクトルxの積の表示---\n");
    for(i=0; i<=N-1; i++)
    {
        printf("%3.1lf,",y[i]);
    }
    printf("\n\n");

    return 0;
}
