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
#define STUDENT_H_FILE "103360.h"
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

//
// Function to make Subset Sums
//

void HorowitzSahniSums(int n, integer_t total1, integer_t total2, const integer_t p[n], integer_t s1[], integer_t s2[], integer_t duplicated_s1[], integer_t duplicated_s2[])
{
    // Calculating subset sums and duplicating arrays -> Need to find another way to save sums indexes
    // When converting the index to binary and inverting order I will have the result

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
                    sum2 += p2[j];
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
}

char HorowitzSahni(integer_t total1, integer_t total2, int lengthP1, int lengthP2, const integer_t s1[], const integer_t s2[], const integer_t duplicated_s1[], const integer_t duplicated_s2[], integer_t desired_sum, int result[])
{
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
                    decToBinary(count, lengthP2, result, lengthP1);
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
    return 0;
}

//
// Fourth approach to the problem
//

//
// SchroeppelShamirs starts here
//

typedef struct Heap Heap;
struct Heap
{
    // type = 0 (Heap) || type = 1 (MaxHeap)
    char type;
    //
    integer_t *arr;
    // Current Size of the Heap
    integer_t size;
    // Maximum capacity of the heap
    integer_t capacity;
};

integer_t parent(integer_t i)
{
    // Get the index of the parent
    return (i - 1) / 2;
}

integer_t left_child(integer_t i)
{
    return (2 * i + 1);
}

integer_t right_child(integer_t i)
{
    return (2 * i + 2);
}

Heap *init_heap(integer_t capacity)
{
    Heap *heap = (Heap *)calloc(1ull, sizeof(Heap));
    heap->arr = (integer_t *)calloc(capacity, sizeof(integer_t));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

Heap *insert_heap(Heap *heap, integer_t element, char type)
{
    if (type == 0)
    {
        // Inserts an element to the min heap
        // We first add it to the bottom (last level)
        // of the tree, and keep swapping with it's parent
        // if it is lesser than it. We keep doing that until
        // we reach the root node. So, we will have inserted the
        // element in it's proper position to preserve the min heap property
        if (heap->size == heap->capacity)
        {
            fprintf(stderr, "Cannot insert %llu. Heap is already full!\n", element);
            return heap;
        }
        // We can add it. Increase the size and add it to the end
        heap->size++;
        heap->arr[heap->size - 1ull] = element;

        // Keep swapping until we reach the root
        integer_t curr = heap->size - 1ull;
        // As long as you aren't in the root node, and while the
        // parent of the last element is greater than it
        while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr])
        {
            // Swap
            integer_t temp = heap->arr[parent(curr)];
            heap->arr[parent(curr)] = heap->arr[curr];
            heap->arr[curr] = temp;
            // Update the current index of element
            curr = parent(curr);
        }
        return heap;
    }
    else if (type == 1)
    {
        // Inserts an element to the max heap
        // We first add it to the bottom (last level)
        // of the tree, and keep swapping with it's parent
        // if it is grater than it. We keep doing that until
        // we reach the root node. So, we will have inserted the
        // element in it's proper position to preserve the max heap property
        if (heap->size == heap->capacity)
        {
            fprintf(stderr, "Cannot insert %llu. Heap is already full!\n", element);
            return heap;
        }
        // We can add it. Increase the size and add it to the end
        heap->size++;
        heap->arr[heap->size - 1ull] = element;

        // Keep swapping until we reach the root
        integer_t curr = heap->size - 1ull;
        // As long as you aren't in the root node, and while the
        // parent of the last element is lesser than it
        while (curr > 0 && heap->arr[parent(curr)] < heap->arr[curr])
        {
            // Swap
            integer_t temp = heap->arr[parent(curr)];
            heap->arr[parent(curr)] = heap->arr[curr];
            heap->arr[curr] = temp;
            // Update the current index of element
            curr = parent(curr);
        }
        return heap;
    }
    return heap;
}

Heap *heapify(Heap *heap, integer_t index, char type)
{
    switch (type)
    {
        case 0:
            // Rearranges the heap as to maintain
            // the min-heap property
            if (heap->size <= 1ull)
                return heap;

            integer_t left = left_child(index);
            integer_t right = right_child(index);

            // Variable to get the smallest element of the subtree
            // of an element an index
            integer_t smallest = index;

            // If the left child is smaller than this element, it is
            // the smallest
            if (left < heap->size && heap->arr[left] < heap->arr[index])
                smallest = left;

            // Similarly for the right, but we are updating the smallest element
            // so that it will definitely give the least element of the subtree
            if (right < heap->size && heap->arr[right] < heap->arr[smallest])
                smallest = right;

            // Now if the current element is not the smallest,
            // swap with the current element. The min heap property
            // is now satisfied for this subtree. We now need to
            // recursively keep doing this until we reach the root node,
            // the point at which there will be no change!
            if (smallest != index)
            {
                integer_t temp = heap->arr[index];
                heap->arr[index] = heap->arr[smallest];
                heap->arr[smallest] = temp;
                heap = heapify(heap, smallest, 0);
            }

            return heap;
        case 1:
            // Rearranges the heap as to maintain
            // the max-heap property
            if (heap->size <= 1ull)
                return heap;

            left = left_child(index);
            right = right_child(index);

            // Variable to get the greatest element of the subtree
            // of an element an index
            integer_t greatest = index;

            // If the left child is greatest than this element, it is
            // the greatest
            if (left < heap->size && heap->arr[left] > heap->arr[index])
                greatest = left;

            // Similarly for the right, but we are updating the greatest element
            // so that it will definitely give the least element of the subtree
            if (right < heap->size && heap->arr[right] > heap->arr[greatest])
                greatest = right;

            // Now if the current element is not the greatest,
            // swap with the current element. The max heap property
            // is now satisfied for this subtree. We now need to
            // recursively keep doing this until we reach the root node,
            // the point at which there will be no change!
            if (greatest != index)
            {
                integer_t temp = heap->arr[index];
                heap->arr[index] = heap->arr[greatest];
                heap->arr[greatest] = temp;
                heap = heapify(heap, greatest, 1);
            }

            return heap;
    }
    return heap;
}

Heap *delete_minimum(Heap *heap)
{
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    integer_t size = heap->size;
    integer_t last_element = heap->arr[size - 1];

    // Update root value with the last element
    heap->arr[0] = last_element;

    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;

    // We need to call heapify(), to maintain the min-heap
    // property
    heap = heapify(heap, 0, 0);
    return heap;
}

Heap *delete_maximum(Heap *heap)
{
    // Deletes the maximum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    integer_t size = heap->size;
    integer_t last_element = heap->arr[size - 1];

    // Update root value with the last element
    heap->arr[0] = last_element;

    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;

    // We need to call heapify(), to maintain the max-heap
    // property
    heap = heapify(heap, 0, 1);
    return heap;
}

void free_heap(Heap *heap)
{
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

void SchroeppelShamirSums(int n, const integer_t p[n], integer_t lp1, integer_t lp2, integer_t lp3, integer_t lp4, integer_t L1[], integer_t L2[], integer_t R1[], integer_t R2[])
{
    // Divide P into 4 nearly equal parts
    integer_t p1[lp1];
    integer_t p2[lp2];
    integer_t p3[lp3];
    integer_t p4[lp4];

    integer_t c = 0;
    for (integer_t i = 0; i < lp1; i++)
    {
        p1[c] = p[i];
        c++;
    }
    c = 0;
    for (integer_t i = lp1; i < lp1 + lp2; i++)
    {
        p2[c] = p[i];
        c++;
    }
    c = 0;
    for (integer_t i = lp1 + lp2; i < lp1 + lp2 + lp3; i++)
    {
        p3[c] = p[i];
        c++;
    }
    c = 0;
    for (integer_t i = lp1 + lp2 + lp3; i < lp1 + lp2 + lp3 + lp4; i++)
    {
        p4[c] = p[i];
        c++;
    }

    integer_t i = 0;
    while (i < (1ull << lp1))
    {
        integer_t sum1 = 0;
        integer_t sum2 = 0;
        integer_t sum3 = 0;
        integer_t sum4 = 0;
        for (integer_t j = 0; j < n; j++)
        {
            if (i & (1ull << j))
            {
                sum1 += p1[j];
                if (i < (1 << lp2))
                {
                    sum2 += p2[j];
                }
                if (i < (1 << lp3))
                {
                    sum3 += p3[j];
                }
                if (i < (1 << lp4))
                {
                    sum4 += p4[j];
                }
            }
        }
        if (i < (1 << lp1))
        {
            L1[i] = sum1;
        }
        if (i < (1 << lp2))
        {
            L2[i] = sum2;
        }
        if (i < (1 << lp3))
        {
            R1[i] = sum3;
        }
        if (i < (1 << lp4))
        {
            R2[i] = sum4;
        }
        i++;
    }
}

char SchroeppelShamir(integer_t lp1, integer_t lp2, integer_t lp3, integer_t lp4, const integer_t L1[], const integer_t L2[], const integer_t R1[], const integer_t R2[], Heap *minheap, Heap *maxheap, integer_t desired_sum)
{
    integer_t i = 0, j;
    while (i < 1ull << lp1)
    {
        j = 0;
        while (j < 1ull << lp2)
        {
            if (L1[i] + L2[j] == desired_sum)
            {
                return 1;
            }
            if (L1[i] + L2[j] < desired_sum)
            {
                insert_heap(minheap, L1[i] + L2[j], 0);
            }
            j++;
        }
        i++;
    }
    i = 0;
    while (i < 1ull << lp3)
    {
        j = 0;
        while (j < 1ull << lp4)
        {
            if (R1[i] + R2[j] == desired_sum)
            {
                return 1;
            }
            if (R1[i] + R2[j] < desired_sum)
            {
                insert_heap(maxheap, R1[i] + R2[j], 1);
            }
            j++;
        }
        i++;
    }
    integer_t counter = 0;
    while (1)
    {
        if (minheap->arr[0] + maxheap->arr[0] == desired_sum)
        {
            return 1;
        }
        else if (minheap->arr[0] + maxheap->arr[0] > desired_sum)
        {
            delete_maximum(maxheap);
        }
        else if (minheap->arr[0] + maxheap->arr[0] < desired_sum)
        {
            delete_minimum(minheap);
        }
        if (counter > (minheap->capacity * maxheap->capacity))
        {
            break;
        }
        counter++;
    }
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
    FILE *fp1 = fopen("data.txt","w");
    FILE *fp2 = fopen("results.txt","w");

    for (int i = 0; i < 41; i++)
    {
        int n = all_subset_sum_problems[i].n; // The value of n
        integer_t *p = all_subset_sum_problems[i].p; // The weights

        char found;
        int result[n]; // Array with the result
        for (int index = 0; index < n; index++)
            result[index] = 0;

        // Making Subset Sums for HorowitzSahni()
        double timeSumsH1 = cpu_time();
        int lengthP1 = n % 2 + n / 2;
        int lengthP2 = n / 2;
        integer_t total1 = (1 << lengthP1); // s1 length = (2^lengthP1)
        integer_t total2 = (1 << lengthP2); // s2 length = (2^lengthP2)
        integer_t *s1, *s2, *duplicated_s1, *duplicated_s2;
        s1 = (integer_t *)malloc(total1 * sizeof(integer_t));
        s2 = (integer_t *)malloc(total2 * sizeof(integer_t));
        duplicated_s1 = (integer_t *)malloc(total1 * sizeof(integer_t));
        duplicated_s2 = (integer_t *)malloc(total2 * sizeof(integer_t));

        HorowitzSahniSums(n,total1,total2,p,s1,s2,duplicated_s1, duplicated_s2);
        double timeSumsH2 = cpu_time();
        double timeSumsH = (timeSumsH2 - timeSumsH1)/(double)20;

        // Making Subset Sums for SchroeppelShamir()
        double timeSumsS1 = cpu_time();
        int len1 = n % 2 + n / 2;
        int len2 = n / 2;
        integer_t lp1 = len1 % 2 + len1 / 2;
        integer_t lp2 = len1 / 2;
        integer_t lp3 = len2 % 2 + len2 / 2;
        integer_t lp4 = len2 / 2;
        // Declaring Sum of all p L1 & L2 for minheap and R1 & R2 for max heap size = 2^lp
        integer_t L1[(1 << lp1)];
        integer_t L2[(1 << lp2)];
        integer_t R1[(1 << lp3)];
        integer_t R2[(1 << lp4)];

        SchroeppelShamirSums(n, p, lp1, lp2, lp3, lp4, L1, L2, R1, R2);
        integer_t min_size = 1ull << len1;
        integer_t max_size = 1ull << len2;
        double timeSumsS2 = cpu_time();
        double timeSumsS = (timeSumsS2 - timeSumsS1)/(double)20;

        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum

            //
            // bruteForce() ---> id = 0
            //

            if (n <= 30)
            {
                double t1 = cpu_time();
                found = bruteForceV2(n, p, desired_sum, result);
                double t2 = cpu_time();
                fprintf(fp1, "%d %d %d %d %f\n", 0, n, k, found, t2 - t1);
            }

            //
            // bruteForceRecursive() ---> id = 1
            //

            if (n <= 40)
            {
                double t1 = cpu_time();
                found = bruteForceRecursiveV3(n, p, desired_sum, 0, 0, result);
                double t2 = cpu_time();
                fprintf(fp1, "%d %d %d %d %f\n", 1, n, k, found, t2 - t1);
            }

            //
            // HorowitzSahni() ---> id = 2
            //

            double timeAlgorithm1 = cpu_time();
            found = HorowitzSahni(total1, total2, lengthP1, lengthP2, s1, s2, duplicated_s1, duplicated_s2, desired_sum, result);
            double timeAlgorithm2 = cpu_time();
            fprintf(fp1, "%d %d %d %d %f\n", 2, n, k, found, (timeAlgorithm2 - timeAlgorithm1) + timeSumsH);

            //
            // SchroeppelShamir() ---> id = 3
            //

            timeAlgorithm1 = cpu_time();
            Heap *minheap = init_heap(min_size);
            Heap *maxheap = init_heap(max_size);
            found = SchroeppelShamir(lp1, lp2, lp3, lp4, L1, L2, R1, R2, minheap, maxheap, desired_sum);
            timeAlgorithm2 = cpu_time();
            fprintf(fp1,"%d %d %d %d %f\n", 3, n, k, found, (timeAlgorithm2 - timeAlgorithm1) + timeSumsS);
            free_heap(minheap);
            free_heap(maxheap);

            // Write results to the file
            fprintf(fp2, "For n: %d | IdSum = %d | Found: %d | Result: ", n, k, found);
            for (int j = 0; j < n; j++)
                fprintf(fp2, "%d", result[j]);
            fprintf(fp2, "\n");
        }
        free(s1);
        free(s2);
        free(duplicated_s1);
        free(duplicated_s2);
    }
    fclose(fp1);
    fclose(fp2);
    return 0;
}