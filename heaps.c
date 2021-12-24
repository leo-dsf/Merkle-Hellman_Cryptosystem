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

// QUARTA E ULTIMA FUNÇÃO
// HEAPS
// NODE IS AT INDEX I
// LEFT CHILD IS AT 2*I
// RIGHT CHILD IS AT 2*I+1
// ITS PARENT IS AT 2/I
// BINARY TREE HAS 2^(H-1)-1 NODES, H = HEIGHT OF BINARY TREE
// minuto 31:54 https://www.youtube.com/watch?v=HqPJF2L5h9U
// https://gist.github.com/sudhanshuptl/d86da25da46aa3d060e7be876bbdb343 -> min heap implementation
// https://www.journaldev.com/36805/min-heap-binary-tree -> another min heap implementation

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

int parent(int i)
{
    // Get the index of the parent
    return (i - 1) / 2;
}

int left_child(int i)
{
    return (2 * i + 1);
}

int right_child(int i)
{
    return (2 * i + 2);
}

int get_min(Heap *heap)
{
    // Only for MinHeaps
    // Return the root node element,
    // since that's the minimum
    return heap->arr[0];
}

int get_max(Heap *heap)
{
    // Only for MaxHeaps
    // Return the root node element,
    // since that's the maximum
    return heap->arr[0];
}

Heap *init_heap(integer_t capacity)
{
    Heap *heap = (Heap *)calloc(1, sizeof(Heap));
    heap->arr = (integer_t *)calloc(capacity, sizeof(integer_t));
    heap->capacity = capacity;
    heap->size = 0;
    return heap;
}

Heap *insert_heap(Heap *heap, int element, char type)
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
        while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr])
        {
            // Swap
            int temp = heap->arr[parent(curr)];
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
            fprintf(stderr, "Cannot insert %d. Heap is already full!\n", element);
            return heap;
        }
        // We can add it. Increase the size and add it to the end
        heap->size++;
        heap->arr[heap->size - 1] = element;

        // Keep swapping until we reach the root
        int curr = heap->size - 1;
        // As long as you aren't in the root node, and while the
        // parent of the last element is lesser than it
        while (curr > 0 && heap->arr[parent(curr)] < heap->arr[curr])
        {
            // Swap
            int temp = heap->arr[parent(curr)];
            heap->arr[parent(curr)] = heap->arr[curr];
            heap->arr[curr] = temp;
            // Update the current index of element
            curr = parent(curr);
        }
        return heap;
    }
    return heap;
}

Heap *heapify(Heap *heap, int index, char type)
{
    switch (type)
    {
    case 0:
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
            heap = heapify(heap, smallest, 0);
        }

        return heap;
        break;
    case 1:
        // Rearranges the heap as to maintain
        // the min-heap property
        if (heap->size <= 1)
            return heap;

        left = left_child(index);
        right = right_child(index);

        // Variable to get the greatest element of the subtree
        // of an element an index
        int greatest = index;

        // If the left child is greatest than this element, it is
        // the greatest
        if (left > heap->size && heap->arr[left] > heap->arr[index])
            greatest = left;

        // Similarly for the right, but we are updating the greatest element
        // so that it will definitely give the least element of the subtree
        if (right > heap->size && heap->arr[right] > heap->arr[greatest])
            greatest = right;

        // Now if the current element is not the greatest,
        // swap with the current element. The max heap property
        // is now satisfied for this subtree. We now need to
        // recursively keep doing this until we reach the root node,
        // the point at which there will be no change!
        if (greatest != index)
        {
            int temp = heap->arr[index];
            heap->arr[index] = heap->arr[greatest];
            heap->arr[greatest] = temp;
            heap = heapify(heap, greatest, 0);
        }

        return heap;
        break;
    }
    return heap;
}

Heap *delete_minimum(Heap *heap)
{
    // Deletes the minimum element, at the root
    if (!heap || heap->size == 0)
        return heap;

    int size = heap->size;
    int last_element = heap->arr[size - 1];

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

    int size = heap->size;
    int last_element = heap->arr[size - 1];

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

Heap *delete_element(Heap *heap, int index, char type)
{
    switch (type)
    {
    case 0:
        // Deletes an element, indexed by index
        // Ensure that it's lesser than the current root
        heap->arr[index] = get_min(heap) - 1;

        // Now keep swapping, until we update the tree
        int curr = index;
        while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr])
        {
            int temp = heap->arr[parent(curr)];
            heap->arr[parent(curr)] = heap->arr[curr];
            heap->arr[curr] = temp;
            curr = parent(curr);
        }

        // Now simply delete the minimum element
        heap = delete_minimum(heap);
        return heap;
        break;
    case 1:
        // Deletes an element, indexed by index
        // Ensure that it's lesser than the current root
        heap->arr[index] = get_min(heap) - 1;

        // Now keep swapping, until we update the tree
        curr = index;
        while (curr > 0 && heap->arr[parent(curr)] < heap->arr[curr])
        {
            int temp = heap->arr[parent(curr)];
            heap->arr[parent(curr)] = heap->arr[curr];
            heap->arr[curr] = temp;
            curr = parent(curr);
        }

        // Now simply delete the maximum element
        heap = delete_maximum(heap);
        return heap;
        break;
        break;
    }
    return heap;
}

void print_heap(Heap *heap, char type)
{
    switch (type)
    {
    case 0:
        // Simply print the array. This is an
        // inorder traversal of the tree
        printf("Min Heap:\n");
        for (int i = 0; i < heap->size; i++)
        {
            printf("%llu -> ", heap->arr[i]);
        }
        printf("\n");
        break;
    case 1:
        // Simply print the array. This is an
        // inorder traversal of the tree
        printf("Max Heap:\n");
        for (int i = 0; i < heap->size; i++)
        {
            printf("%llu -> ", heap->arr[i]);
        }
        printf("\n");
        break;
    }
}

void free_heap(Heap *heap)
{
    if (!heap)
        return;
    free(heap->arr);
    free(heap);
}

void SchroeppelShamir(int n, integer_t p[n], integer_t desired_sum)
{
    printf("p = : ");
    for (int i = 0; i < n; i++)
    {
        printf("%lld;", p[i]);
    }
    printf("\n");
    // Divide P into nearly equal 4 parts
    int lengthP1 = n % 2 + n / 2;
    int lengthP2 = n / 2;
    int lp1 = lengthP1 % 2 + lengthP1 / 2;
    int lp2 = lengthP1 / 2;
    int lp3 = lengthP2 % 2 + lengthP2 / 2;
    int lp4 = lengthP2 / 2;
    printf("lp1 = %d;\nlp2 = %d;\nlp3 = %d;\nlp4 = %d;\n", lp1, lp2, lp3, lp4);

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

    printf("p1 = ");
    for (int i = 0; i < lp1; i++)
    {
        printf("%lld;", p1[i]);
    }
    printf("\n");
    printf("p2 = ");
    for (int i = 0; i < lp2; i++)
    {
        printf("%lld;", p2[i]);
    }
    printf("\n");
    printf("p3 = ");
    for (int i = 0; i < lp3; i++)
    {
        printf("%lld;", p3[i]);
    }
    printf("\n");
    printf("p4 = ");
    for (int i = 0; i < lp4; i++)
    {
        printf("%lld;", p4[i]);
    }
    printf("\n");

    // Declaring Sum of all p L1 & L2 for minheap and R1 & R2 for max heap size = 2^lp
    integer_t L1[(1 << lp1)];
    integer_t L2[(1 << lp2)];
    integer_t R1[(1 << lp3)];
    integer_t R2[(1 << lp4)];

    integer_t i = 0;
    while (i < (1 << lp1))
    {
        integer_t sum1 = 0;
        integer_t sum2 = 0;
        integer_t sum3 = 0;
        integer_t sum4 = 0;
        for (int j = 0; j < n; j++)
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

    printf("L1 = ");
    for (int i = 0; i < (1 << lp1); i++)
    {
        printf("%lld;", L1[i]);
    }
    printf("\n");

    printf("L2 = ");
    for (int i = 0; i < (1 << lp2); i++)
    {
        printf("%lld;", L2[i]);
    }
    printf("\n");

    printf("R1 = ");
    for (int i = 0; i < (1 << lp3); i++)
    {
        printf("%lld;", R1[i]);
    }
    printf("\n");

    printf("R2 = ");
    for (int i = 0; i < (1 << lp4); i++)
    {
        printf("%lld;", R2[i]);
    }
    printf("\n");

    Heap *minheap = init_heap(1ull << lengthP1);
    Heap *maxheap = init_heap(1ull << lengthP2);

    int found = 0;
    i = 0; 
    integer_t j = 0, k = (1ull << lp3) - 1, l = (1ull << lp4) - 1;
    while (i < 1ull << lp1)
    {
        j=0;
        while (j < 1ull << lp2)
        {
            if (L1[i] + L2[j] == desired_sum)
            {
                printf("FOUND\n");
                found = 1;
                break;
            }
            insert_heap(minheap, L1[i] + L2[j], 0);
            j++;
        }

        i++;
    }
    while (k >= 0)
    {
        l = (1ull << lp4) - 1;
        while (l >= 0)
        {
            if (R1[k] + R2[l] == desired_sum)
            {
                printf("FOUND\n");
                found = 1;
                break;
            }
            insert_heap(maxheap, R1[k] + R2[l], 0);
            l--;
        }
        k--;
    }
    i = 0, j = 0;
    while (found != 1)
    {
        if (minheap->arr[i] + maxheap->arr[j] == desired_sum)
        {
            printf("FOUND\n");
            found = 1;
        }else if (minheap->arr[i] + maxheap->arr[j] > desired_sum)
        {
            delete_maximum(maxheap);
            
        }else if (minheap->arr[i] + maxheap->arr[j] < desired_sum)
        {
            delete_minimum(minheap);
        }
        
    }

    print_heap(minheap, 0);
    print_heap(maxheap, 1);

    free_heap(minheap);
    free_heap(maxheap);
}

int main()
{
    /*
    // Capacity of 10 elements
    Heap *minheap = init_heap(10);
    Heap *maxheap = init_heap(20);

    insert_heap(minheap, 40, 0);
    insert_heap(minheap, 50, 0);
    insert_heap(minheap, 60, 0);
    insert_heap(minheap, 10, 0);
    insert_heap(minheap, 30, 0);
    insert_heap(minheap, 15, 0);
    insert_heap(minheap, 55, 0);
    insert_heap(minheap, 23, 0);
    insert_heap(minheap, 100, 0);

    print_heap(minheap, 0);

    insert_heap(maxheap, 40, 1);
    insert_heap(maxheap, 50, 1);
    insert_heap(maxheap, 60, 1);
    insert_heap(maxheap, 10, 1);

    print_heap(maxheap, 1);

    // Delete the heap->arr[1] (23)
    delete_element(minheap, 1, 0);

    print_heap(minheap, 0);
    free_heap(minheap);
    */
    printf("n = 10\n");
    int n = all_subset_sum_problems[0].n;
    integer_t *p = all_subset_sum_problems[0].p;
    integer_t desired_sum = all_subset_sum_problems[0].sums[0];
    SchroeppelShamir(n, p, desired_sum);
    /*
    for (int i = 1; i < n_problems; i++)
    {
        int n = all_subset_sum_problems[i].n; // The value of n

        if (n > 20)
            continue; // Skip large values of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum

            break;
        }
    }
    */

    return 0;
}