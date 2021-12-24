//
// Schroeppel and Shamir's Algorithm for Subset Sum Problem
//
#if __STDC_VERSION__ < 199901L
#error "This code must must be compiled in c99 mode or later (-std=c99)" // to handle the unsigned long long data type
#endif
#ifndef STUDENT_H_FILE
#define STUDENT_H_FILE "000000.h"
#endif

//
// include files
//

#include <stdio.h>
#include <stdlib.h>
#include "elapsed_time.h"
#include STUDENT_H_FILE

//
// Fourth approach to the problem
//




char SchroeppelShamirs(int n, const integer_t p[n], integer_t desired_sum, int result[])
{
    // Divide P into nearly equal 4 parts
    int lengthP1 = n % 2 + n / 2;
    int lengthP2 = n / 2;
    int lp1 = lengthP1 % 2 + lengthP1 / 2;
    int lp2 = lengthP1 / 2;
    int lp3 = lengthP2 % 2 + lengthP2 / 2;
    int lp4 = lengthP2 / 2;

    integer_t p1[lp1];
    integer_t p2[lp2];
    integer_t p3[lp3];
    integer_t p4[lp4];
    int c = 0;
    for (int i = 0; i < lp1; i++)
    {
        p1[c] = p[i];
        c++;
    }
    c = 0;
    for (int i = lp1; i < lp1 + lp2; i++)
    {
        p2[c] = p[i];
        c++;
    }
    c = 0;
    for (int i = lp1 + lp2; i < lp1 + lp2 + lp3; i++)
    {
        p3[c] = p[i];
        c++;
    }
    c = 0;
    for (int i = lp1 + lp2 + lp3; i < lp1 + lp2 + lp3 + lp4; i++)
    {
        p4[c] = p[i];
        c++;
    }

    // Declaring Sum of all p L1 & L2 for minheap and R1 & R2 for max heap size = 2^lp
    integer_t L1[(1 << lp1)];
    integer_t L2[(1 << lp2)];
    integer_t R1[(1 << lp3)];
    integer_t R2[(1 << lp4)];





    return 0;
}

int main(void)
{
    for (int i = 22; i < n_problems; i++)
    {
        int n = all_subset_sum_problems[i].n; // The value of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            int result[n]; // Array with the result
            for (int j = 0; j < n; j++)
                result[j] = 0;
            char found;

            double t1 = cpu_time();
            found = SchroeppelShamirs(n, p, desired_sum, result);
            double t2 = cpu_time();

            printf("For n = %d | Found: %d | Time: %f (s) | ", n, found, t2-t1);
            printf("Result: ");
            for (int j = 0; j < n; j++)
                printf("%d", result[j]);
            printf("\n");
            break;
        }
    }
    return 0;
}