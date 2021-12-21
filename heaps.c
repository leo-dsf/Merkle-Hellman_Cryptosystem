#include <stdio.h>
#include <stdlib.h>

typedef struct Heap Heap;
struct Heap
{
    // type = 0 (Heap) || type = 1 (MaxHeap)
    char type;
    //
    int *arr;
    // Current Size of the Heap
    int size;
    // Maximum capacity of the heap
    int capacity;
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

Heap *init_heap(int capacity)
{
    Heap *heap = (Heap *)calloc(1, sizeof(Heap));
    heap->arr = (int *)calloc(capacity, sizeof(int));
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

        int left = left_child(index);
        int right = right_child(index);

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
        int curr = index;
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
            printf("%d -> ", heap->arr[i]);
        }
        printf("\n");
        break;
    case 1:
        // Simply print the array. This is an
        // inorder traversal of the tree
        printf("Max Heap:\n");
        for (int i = 0; i < heap->size; i++)
        {
            printf("%d -> ", heap->arr[i]);
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

int main()
{
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
    return 0;
}
