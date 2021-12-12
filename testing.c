#include <stdio.h>
#include "elapsed_time.h"
int main()
{

long long p[15] = {1, 5, 13,4,23,66,3,45,34,67,14,56,77,88,99};

long long s1[(1 << 15)] ;
long long m = 0;
s1[0] = 0;
long long k = 15;


//printf("%d\n",1 << 1);
while (m < k)
{
    long long c = 0;
    while (c < (1 << (m)))
    {
        //printf("c = %lld\n",c);
        s1[c + (1 << (m))] = s1[c] + p[m];
        //printf("%d\n",s1[c]);
        c++;
    }

    m++;
}




/*

double t1 = cpu_time();
long long p1[3] = {1,5,13};
int n = 3;
long long total1 = 8;
long long i = 0;
long long s1[8];

    while (i<total1){
        long long sum1 = 0;
        long long sum2 = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1 << j))
            {
                sum1 += p1[j];
                if (i<total2){
                    sum2 += p2[j];
                }
            }
        }
        s1[i] = sum1;
        printf("%lld;",s1[i]);
        //if (i<total2){
        //    s2[i] = sum2;
        //}
        i++;
    }

double t2 = cpu_time();
printf("elapsed time: %.6f seconds\n",t2 - t1);
*/

for (int i = 0; i<256; i++){
    printf("%lld,",s1[i]);
}

}
