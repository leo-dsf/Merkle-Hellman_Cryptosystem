//
// AED, November 2021
//
// Solution of the first practical assignment (subset sum problem)
//
// Leonardo dos Santos Flórido, 103360
//
// Gabriel Hall Abreu, 102851
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

// HorowitzSahni starts here

// Implementig quick sort function

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
int partition(integer_t arr[], integer_t low, integer_t high)
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

// Funciton to transform decimal into binary
// n = number | i = binary length -> it will return in reverse order
char decToBinary(integer_t n, integer_t c)
{

    for (integer_t i = 0; i < c; i++)
    {
        integer_t k = n >> i;
        if (k & 1)
        {
            printf("%s", "1");
        }
        else
        {
            printf("%s", "0");
        }
    }
    return 0;
}

char HorowitzSahni(int n, integer_t p[n], integer_t desired_sum)
{
    integer_t lengthP1 = n % 2 + n / 2;
    integer_t lengthP2 = n / 2;
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

    // Calculating subset sums and duplicating arrays -> Need to find an other way to save sums indexes
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
            integer_t c = 0;
            while (c < total1)
            {
                if (duplicated_s1[c] == s1[k])
                {
                    decToBinary(c, lengthP1);
                    break;
                }
                c++;
            }
            c = 0;
            while (c < total2)
            {
                if (duplicated_s2[c] == s2[j])
                {
                    decToBinary(c, lengthP2);
                    break;
                }
                c++;
            }
            break;
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



//QUARTA E ULTIMA FUNÇÃO
//HEAPS
//NODE IS AT INDEX I
//LEFT CHILD IS AT 2*I
//RIGHT CHILD IS AT 2*I+1
//ITS PARENT IS AT 2/I
//BINARY TREE HAS 2^(H-1)-1 NODES, H = HEIGHT OF BINARY TREE
//minuto 31:54 https://www.youtube.com/watch?v=HqPJF2L5h9U
//https://gist.github.com/sudhanshuptl/d86da25da46aa3d060e7be876bbdb343 -> min heap implementation
//https://www.journaldev.com/36805/min-heap-binary-tree -> another min heap implementation

typedef struct MinHeap MinHeap;
struct MinHeap {
    int* arr;
    // Current Size of the Heap
    int size;
    // Maximum capacity of the heap
    int capacity;
};
 
int parent(int i) {
    // Get the index of the parent
    return (i - 1) / 2;
}
 
int left_child(int i) {
    return (2*i + 1);
}
 
int right_child(int i) {
    return (2*i + 2);
}
 
int get_min(MinHeap* heap) {
    // Return the root node element,
    // since that's the minimum
    return heap->arr[0];
}
 
MinHeap* init_minheap(int capacity) {
    MinHeap* minheap = (MinHeap*) calloc (1, sizeof(MinHeap));
    minheap->arr = (int*) calloc (capacity, sizeof(int));
    minheap->capacity = capacity;
    minheap->size = 0;
    return minheap;
}
 
MinHeap* insert_minheap(MinHeap* heap, int element) {
    // Inserts an element to the min heap
    // We first add it to the bottom (last level)
    // of the tree, and keep swapping with it's parent
    // if it is lesser than it. We keep doing that until
    // we reach the root node. So, we will have inserted the
    // element in it's proper position to preserve the min heap property
    if (heap->size == heap->capacity) {
        fprintf(stderr, "Cannot insert %d. Heap is already full!\n", element);
        return heap;
    }
    // We can add it. Increase the size and add it to the end
    heap->size++;
    heap->arr[heap->size - 1] = element;
 
    // Keep swapping until we reach the root
    int curr = heap->size - 1;
    // As long as you aren't in the root node, and while the 
    // parent of the last element is greater than it
    while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr]) {
        // Swap
        int temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        // Update the current index of element
        curr = parent(curr);
    }
    return heap; 
}
 
MinHeap* heapify(MinHeap* heap, int index) {
    // Rearranges the heap as to maintain
    // the min-heap property
    if (heap->size <= 1)
        return heap;
     
    int left = left_child(index); 
    int right = right_child(index); 
 
    // Variable to get the smallest element of the subtree
    // of an element an index
    int smallest = index; 
     
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
        int temp = heap->arr[index];
        heap->arr[index] = heap->arr[smallest];
        heap->arr[smallest] = temp;
        heap = heapify(heap, smallest); 
    }
 
    return heap;
}
 
MinHeap* delete_minimum(MinHeap* heap) {
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;
 
    int size = heap->size;
    int last_element = heap->arr[size-1];
     
    // Update root value with the last element
    heap->arr[0] = last_element;
 
    // Now remove the last element, by decreasing the size
    heap->size--;
    size--;
 
    // We need to call heapify(), to maintain the min-heap
    // property
    heap = heapify(heap, 0);
    return heap;
}
 
MinHeap* delete_element(MinHeap* heap, int index) {
    // Deletes an element, indexed by index
    // Ensure that it's lesser than the current root
    heap->arr[index] = get_min(heap) - 1;
     
    // Now keep swapping, until we update the tree
    int curr = index;
    while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr]) {
        int temp = heap->arr[parent(curr)];
        heap->arr[parent(curr)] = heap->arr[curr];
        heap->arr[curr] = temp;
        curr = parent(curr);
    }
 
    // Now simply delete the minimum element
    heap = delete_minimum(heap);
    return heap;
}
 
void print_heap(MinHeap* heap) {
    // Simply print the array. This is an
    // inorder traversal of the tree
    printf("Min Heap:\n");
    for (int i=0; i<heap->size; i++) {
        printf("%d -> ", heap->arr[i]);
    }
    printf("\n");
}
 
void free_minheap(MinHeap* heap) {
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}
/*
    //Capacity of 10 elements
    MinHeap* heap = init_minheap(10);
 
    insert_minheap(heap, 40);
    insert_minheap(heap, 50);
    insert_minheap(heap, 5);
    print_heap(heap);
     
    // Delete the heap->arr[1] (50)
    delete_element(heap, 1);
 
    print_heap(heap);
    free_minheap(heap);
    return 0;
*/



char SchroeppelShamir(int n, integer_t p[n], integer_t desired_sum)
{
    //Dividir p em 4 partes nearly iguais
    integer_t lengthP1 = n % 2 + n / 2;
    integer_t lengthP2 = n / 2;
    integer_t lp1 = lengthP1 % 2 + lengthP1 / 2;
    integer_t lp2 = lengthP1 / 2;
    integer_t lp3 = lengthP2 % 2 + lengthP2 / 2;
    integer_t lp4 = lengthP2 / 2;
    
    integer_t p1[lp1];
    integer_t p2[lp2];
    integer_t p3[lp3];
    integer_t p4[lp4];

    //Fazer arrays a1 a2 b1 b2 em que são geradas como min e max heaps sem usar memoria???????????????????????



    //
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

    for (int i = 22; i < n_problems; i++)
    {
        int n = all_subset_sum_problems[i].n; // The value of n

        if (n > 57)
            continue; // Skip large values of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            // Array with the result
            int result[n];

            for (int j = 0; j < n; j++)
                result[j] = 0;
            printf("n = %d \n", n);
            double t1 = cpu_time();
            HorowitzSahni(n, p, desired_sum);
            printf("\n");
            double t2 = cpu_time();
            printf("elapsed time: %.6f seconds\n", t2 - t1);

            // printf("N = %d, Found: %d, ", n, bruteForceV2(n, p, desired_sum, result));
            // printf("%d\n", bruteForceV1(n, p, desired_sum));
            // printf("N = %d, Found: %d, ", n, bruteForceRecursiveV1(n, p, desired_sum, 0,0));
            // printf("N = %d, Found: %d, ", n, bruteForceRecursiveV2(n, p, desired_sum, 0,0,result));
            // double t1 = cpu_time();
            // printf("Para n = %d | Found: %d | ", n, bruteForceRecursiveV3(n, p, desired_sum, 0, 0, result));

            // printf("Result: ");

            // for (int j = 0; j < n; j++)
            //     printf("%d", result[j]);
            //
            // printf("\n");
            //  double t2 = cpu_time();
            //  printf("elapsed time: %.6f seconds\n", t2 - t1);
            break;
        }
    }
    return 0;
}
