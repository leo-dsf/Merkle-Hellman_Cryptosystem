//
// AED, November 2021
//
// Solution of the first practical assignment (subset sum problem)
//
// Leonardo dos Santos Flórido, 103360
//
// Gabriel Hall Abreu, 102851
//
// João Ricardo Paço Matos, 103182
//

#if __STDC_VERSION__ < 199901L
# error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
# define STUDENT_H_FILE "000000.h"
#endif

//
// include files
//

#include <stdio.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

//
// functions
//
//
// First approach to the problem
//
char bruteForceV1(int n, integer_t p[n], integer_t desired_sum)
{
    for (int comb = 0; comb < (1 << n); ++comb) // (1 << n) == pow(2,n)
    {
        integer_t test_sum = 0;

        for (int bit = 0; bit < n; bit++)
        {
            if (comb & (1 << bit))
            {
                test_sum += p[bit];
            }
        }

        if (test_sum == desired_sum)
        {
            return 1;
        }
    }
    return 0;
}

char bruteForceV2(int n, integer_t p[n], integer_t desired_sum, int result[])
{
    for (int comb = 0; comb < (1 << n); ++comb)
    {
        integer_t test_sum = 0;

        for (int bit = 0; bit < n; bit++)
        {
            if (comb & (1 << bit))
            {
                result[bit] = 1;
                test_sum += p[bit];
            }
            else
            {
                result[bit] = 0;
            }
        }

        if (test_sum == desired_sum)
        {
            return 1;
        }
    }
    return 0;
}
//
// Second approach to the problem
//
char bruteForceRecursiveV1(int n, integer_t p[n], integer_t desired_sum, int current_index, integer_t partial_sum)
{
    if(partial_sum == desired_sum)
        return 1;

    if(current_index == n)
        return 0;

    for(int index = current_index; index < n; index++)
    {
        if (bruteForceRecursiveV1(n, p, desired_sum, ++current_index, partial_sum + p[index]))
            return 1;
    }
    return 0;
}

char bruteForceRecursiveV2(int n, integer_t p[n], integer_t desired_sum, int current_index, integer_t partial_sum, int result[])
{
    if(partial_sum == desired_sum)
        return 1;

    if(current_index == n)
        return 0;

    for(int index = current_index; index < n; index++)
    {
        result[index] = 1;
        if (bruteForceRecursiveV2(n, p, desired_sum, ++current_index, partial_sum + p[index], result))
            return 1;
        result[index] = 0;
    }
    return 0;
}

char bruteForceRecursiveV3(int n, integer_t p[n], integer_t desired_sum, int current_index, integer_t partial_sum, int result[])
{
    if(partial_sum == desired_sum)
        return 1;

    if(current_index == n)
        return 0;

    if(partial_sum > desired_sum)
        return 0;

    for(int index = current_index; index < n; index++)
    {
        result[index] = 1;
        if (bruteForceRecursiveV3(n, p, desired_sum, ++current_index, partial_sum + p[index], result))
            return 1;
        result[index] = 0;
    }
    return 0;
}
//
// main program
//
int main(void) {
    /*
    fprintf(stderr,"Program configuration:\n");
    fprintf(stderr,"  min_n ....... %d\n",min_n);
    fprintf(stderr,"  max_n ....... %d\n",max_n);
    fprintf(stderr,"  n_sums ...... %d\n",n_sums);
    fprintf(stderr,"  n_problems .. %d\n",n_problems);
    fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
     */

    for (int i = 0; i < n_problems; i++) {
        int n = all_subset_sum_problems[i].n; // The value of n

        if (n > 30)
            continue; // Skip large values of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            // Array with the result
            int result[n];
            for (int j = 0; j < n; j++)
                result[j] = 0;

            //printf("N = %d, Found: %d, ", n, bruteForceV2(n, p, desired_sum, result));
            //printf("%d\n", bruteForceV1(n, p, desired_sum));
            //printf("N = %d, Found: %d, ", n, bruteForceRecursiveV1(n, p, desired_sum, 0,0));
            //printf("N = %d, Found: %d, ", n, bruteForceRecursiveV2(n, p, desired_sum, 0,0,result));
            printf("Para n = %d | Found: %d | ", n, bruteForceRecursiveV3(n, p, desired_sum, 0,0,result));

            printf("Result: ");

            for (int j = 0; j < n; j++)
                printf("%d", result[j]);

            printf("\n");
        }
    }
    return 0;
}
