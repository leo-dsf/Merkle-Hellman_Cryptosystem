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

integer_t get_min(Heap *heap)
{
    // Only for MinHeaps
    // Return the root node element,
    // since that's the minimum
    return heap->arr[0];
}

integer_t get_max(Heap *heap)
{
    // Only for MaxHeaps
    // Return the root node element,
    // since that's the maximum
    return heap->arr[0];
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
        break;
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
        break;
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

Heap *delete_element(Heap *heap, integer_t index, char type)
{
    switch (type)
    {
    case 0:
        // Deletes an element, indexed by index
        // Ensure that it's lesser than the current root
        heap->arr[index] = get_min(heap) - 1;

        // Now keep swapping, until we update the tree
        integer_t curr = index;
        while (curr > 0 && heap->arr[parent(curr)] > heap->arr[curr])
        {
            integer_t temp = heap->arr[parent(curr)];
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
            integer_t temp = heap->arr[parent(curr)];
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

char SchroeppelShamir(int n, integer_t p[n], integer_t desired_sum, int result[])
{

    // Divide P into nearly equal 4 parts
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

    // Declaring Sum of all p L1 & L2 for minheap and R1 & R2 for max heap size = 2^lp
    integer_t L1[(1 << lp1)];
    integer_t L2[(1 << lp2)];
    integer_t R1[(1 << lp3)];
    integer_t R2[(1 << lp4)];

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

    integer_t min_size = 1ull << lengthP1;
    integer_t max_size = 1ull << lengthP2;
    Heap *minheap = init_heap(min_size);
    Heap *maxheap = init_heap(max_size);

    int found = 0;
    i = 0;
    integer_t j = 0;
    while (i < 1ull << lp1)
    {
        j = 0;
        while (j < 1ull << lp2)
        {
            if (L1[i] + L2[j] == desired_sum)
            {

                found = 1;
                integer_t count = 0;
                while (count < (1 << lp1))
                {
                    if (L1[count] == minheap->arr[0])
                    {
                        decToBinary(count, lp1, result, 0);
                        break;
                    }
                    count++;
                }
                count = 0;
                while (count < (1 << lp2))
                {
                    if (L2[count] == minheap->arr[0])
                    {
                        decToBinary(count, lp2, result, lp1);
                        break;
                    }
                    count++;
                }
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

                found = 1;
                integer_t count = 0;
                while (count < (1 << lp3))
                {
                    if (R1[count] == maxheap->arr[0])
                    {
                        decToBinary(count, lp3, result, 0);
                        break;
                    }
                    count++;
                }
                count = 0;
                while (count < (1 << lp4))
                {
                    if (R2[count] == maxheap->arr[0])
                    {
                        decToBinary(count, lp4, result, lp3);
                        break;
                    }
                    count++;
                }
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
    while (found != 1)
    {

        if (minheap->arr[0] + maxheap->arr[0] == desired_sum)
        {
            //printf("FOUND\n -> %lld + %lld = %lld = %lld\n", minheap->arr[0], maxheap->arr[0], minheap->arr[0] + maxheap->arr[0], desired_sum);
            integer_t count = 0;
            while (count < (1 << lp1))
            {
                if (L1[count] == minheap->arr[0])
                {
                    decToBinary(count, lp1, result, 0);
                    break;
                }
                count++;
            }
            count = 0;
            while (count < (1 << lp2))
            {
                if (L2[count] == minheap->arr[0])
                {
                    decToBinary(count, lp2, result, lp1);
                    break;
                }
                count++;
            }
            count = 0;
            while (count < (1 << lp3))
            {
                if (R1[count] == maxheap->arr[0])
                {
                    decToBinary(count, lp3, result, 0);
                    break;
                }
                count++;
            }
            count = 0;
            while (count < (1 << lp4))
            {
                if (R2[count] == maxheap->arr[0])
                {
                    decToBinary(count, lp4, result, lp3);
                    break;
                }
                count++;
            }
            return 1;
            found = 1;
        }
        else if (minheap->arr[0] + maxheap->arr[0] > desired_sum)
        {

            delete_maximum(maxheap);
        }
        else if (minheap->arr[0] + maxheap->arr[0] < desired_sum)
        {

            delete_minimum(minheap);
        }
        if (counter > (minheap->size * maxheap->size))
        {
            printf("NOT FOUND\n");
            return 0;
            break;
        }
        counter++;
    }

    free_heap(minheap);
    free_heap(maxheap);

    return 0;
}

int main()
{
    for (int i = 0; i < n_problems; i++)
    {
        int n = all_subset_sum_problems[i].n; // The value of n

        if (n > 57)
            continue; // Skip large values of n

        integer_t *p = all_subset_sum_problems[i].p; // The weights
        for (int k = 0; k < n_sums; k++)
        {
            integer_t desired_sum = all_subset_sum_problems[i].sums[k]; // The desire_sum
            int result[n];                                              // Array with the result
            for (int j = 0; j < n; j++)
                result[j] = 0;
            char found;

            double t1 = cpu_time();
            found = SchroeppelShamir(n, p, desired_sum, result);
            double t2 = cpu_time();
            // fprintf(fp, "%d %d %d %d %f\n", 2, n, k, found, t2 - t1);

            printf("For n = %d | Found: %d | Time: %f (s) | ", n, found, t2 - t1);
            printf("Result: ");
            for (int j = 0; j < n; j++)
                printf("%d", result[j]);
            printf("\n");
            break;
        }
    }
    return 0;
}