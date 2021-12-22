//
// AED, November 2021
//
// Solution of the first practical assignment (subset sum problem)
//
// Leonardo dos Santos Flórido, 103360
//
// Gabriel Hall Abreu, 102851
//
// Diogo Alves da Silva, 103925
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
// functions
//
//
// First approach to the problem
//

char bruteForceV1(int n, const integer_t p[n], integer_t desired_sum)
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

char bruteForceV2(int n, const integer_t p[n], integer_t desired_sum, int result[])
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
    if (partial_sum == desired_sum)
        return 1;

    if (current_index == n)
        return 0;

    for (int index = current_index; index < n; index++)
    {
        if (bruteForceRecursiveV1(n, p, desired_sum, ++current_index, partial_sum + p[index]))
            return 1;
    }
    return 0;
}

char bruteForceRecursiveV2(int n, integer_t p[n], integer_t desired_sum, int current_index, integer_t partial_sum, int result[])
{
    if (partial_sum == desired_sum)
        return 1;

    if (current_index == n)
        return 0;

    for (int index = current_index; index < n; index++)
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
    if (partial_sum == desired_sum)
        return 1;

    if (current_index == n)
        return 0;

    if (partial_sum > desired_sum)
        return 0;

    for (int index = current_index; index < n; index++)
    {
        result[index] = 1;
        if (bruteForceRecursiveV3(n, p, desired_sum, ++current_index, partial_sum + p[index], result))
            return 1;
        result[index] = 0;
    }
    return 0;
}

//
// Third approach to the problem
//
//
// HorowitzSahni starts here
//
// Implementing quick sort function
//

void swap(integer_t *a, integer_t *b)
{
    integer_t t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
the pivot element at its correct position in sorted
array, and places all smaller (smaller than pivot)
to left of pivot and all greater elements to right
of pivot */

integer_t partition(integer_t arr[], integer_t low, integer_t high)
{
    integer_t pivot = arr[high]; // pivot
    integer_t i = (low - 1);     // Index of smaller element and indicates the right position of pivot found so far

    for (integer_t j = low; j <= high - 1; j++)
    {
        // If current element is smaller than the pivot
        if (arr[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
arr[] --> Array to be sorted,
low --> Starting index,
high --> Ending index */

void quickSort(integer_t arr[], integer_t low, integer_t high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
        at right place */
        integer_t pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

//
// Function to transform decimal into binary
// n = number | i = binary length -> it will return in reverse order
//

char decToBinary(integer_t n, integer_t c, int result[], int index)
{
    for (integer_t i = index; i < c + index; i++)
    {
        integer_t k = n >> (i - index);
        if (k & 1)
        {
            result[i] = 1;
        }
        else
        {
            result[i] = 0;
        }
    }
    return 0;
}

char HorowitzSahni(int n, const integer_t p[n], integer_t desired_sum, int result[])
{
    int lengthP1 = n % 2 + n / 2;
    int lengthP2 = n / 2;
    integer_t p1[n % 2 + n / 2];
    integer_t p2[n / 2];

    int c = 0;
    for (int j = 0; j < n; j++)
    {
        if (j < (n % 2 + n / 2))
        {
            p1[j] = p[j];
        }
        else
        {
            p2[c] = p[j];
            c++;
        }
    }

    // Making Subset sums
    integer_t total1 = (1 << lengthP1); // s1 length 2^n
    integer_t total2 = (1 << lengthP2); // s2 length
    integer_t *s1, *s2, *duplicated_s1, *duplicated_s2;
    s1 = (integer_t *)malloc(total1 * sizeof(integer_t));
    s2 = (integer_t *)malloc(total2 * sizeof(integer_t));
    duplicated_s1 = (integer_t *)malloc(total1 * sizeof(integer_t));
    duplicated_s2 = (integer_t *)malloc(total2 * sizeof(integer_t));

    // Calculating subset sums and duplicating arrays -> Need to find another way to save sums indexes
    // When converting the index to binary and inverting order I will have the result

    integer_t i = 0;
    while (i < total1)
    {
        integer_t sum1 = 0;
        integer_t sum2 = 0;
        for (int j = 0; j < n; j++)
        {
            if (i & (1ull << j))
            {
                sum1 += p1[j];
                if (i < total2)
                {
                    sum2 += p2[j];
                }
            }
        }
        s1[i] = sum1;
        duplicated_s1[i] = sum1;

        if (i < total2)
        {
            s2[i] = sum2;
            duplicated_s2[i] = sum2;
        }
        i++;
    }

    // Sorting with quick sort method
    quickSort(s1, 0, total1 - 1);
    quickSort(s2, 0, total2 - 1);

    integer_t k = 0;
    integer_t j = total2 - 1;
    while (k < total1 && j >= 0)
    {
        if (s1[k] + s2[j] == desired_sum)
        {
            // finding indexes
            integer_t count = 0;
            while (count < total1)
            {
                if (duplicated_s1[count] == s1[k])
                {
                    decToBinary(count, lengthP1, result, 0);
                    break;
                }
                count++;
            }
            count = 0;
            while (count < total2)
            {
                if (duplicated_s2[count] == s2[j])
                {
                    decToBinary(count, lengthP2, result,lengthP1);
                    break;
                }
                count++;
            }
            return 1;
        }
        else if (s1[k] + s2[j] < desired_sum)
        {
            k++;
        }
        else if (s1[k] + s2[j] > desired_sum)
        {
            j--;
        }
    }
    free(s1);
    free(s2);
    free(duplicated_s1);
    free(duplicated_s2);
    return 0;
}

//
// main program
//

int main(void)
{
    /*
    fprintf(stderr,"Program configuration:\n");
    fprintf(stderr,"  min_n ....... %d\n",min_n);
    fprintf(stderr,"  max_n ....... %d\n",max_n);
    fprintf(stderr,"  n_sums ...... %d\n",n_sums);
    fprintf(stderr,"  n_problems .. %d\n",n_problems);
    fprintf(stderr,"  integer_t ... %d bits\n",8 * (int)sizeof(integer_t));
     */

    // FILE *fp = fopen("data.txt","w");

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

            //
            // bruteForce() ---> (id = 0)
            //

            /*
            if (n >= 30)
            {
                double t1 = cpu_time();
                found = bruteForceV2(n, p, desired_sum, result);
                double t2 = cpu_time();
                fprintf(fp, "%d %d %d %d %f\n", 0, n, k, found, t2 - t1);
            }

            //
            // bruteForceRecursive() ---> (id = 1)
            //

            if (n >= 40)
            {
                double t1 = cpu_time();
                found = bruteForceRecursiveV3(n, p, desired_sum, 0, 0, result);
                double t2 = cpu_time();
                fprintf(fp, "%d %d %d %d %f\n", 1, n, k, found, t2 - t1);
            }
            */

            //
            // HorowitzSahni() ---> (id = 2)
            //

            double t1 = cpu_time();
            found = HorowitzSahni(n, p, desired_sum, result);
            double t2 = cpu_time();
            // fprintf(fp, "%d %d %d %d %f\n", 2, n, k, found, t2 - t1);

            printf("For n = %d | Found: %d | Time: %f (s) | ", n, found, t2-t1);
            printf("Result: ");
            for (int j = 0; j < n; j++)
                 printf("%d", result[j]);
             printf("\n");
            break;
        }
    }
    // fclose(fp);
    return 0;
}
