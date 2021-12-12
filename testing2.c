#include <stdio.h>
int decToBinary(long long n, long long i)
{
    i--;
    for (i; i >= 0; i--)
    {
        long long k = n >> i;
        if (k & 1)
            printf("%s", "1");
        else
            printf("%s", "0");
    }
}


int main(){
    long long n = 7;
    decToBinary(n,5);
}