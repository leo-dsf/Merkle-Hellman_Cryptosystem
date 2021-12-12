#include <stdio.h>
#include "elapsed_time.h"
void swap(int* a, int* b) 
{ 
    int t = *a; 
    *a = *b; 
    *b = t; 
} 
  
/* This function takes last element as pivot, places 
the pivot element at its correct position in sorted 
array, and places all smaller (smaller than pivot) 
to left of pivot and all greater elements to right 
of pivot */
int partition (int arr[], int low, int high) 
{ 
    int pivot = arr[high]; // pivot 
    int i = (low - 1); // Index of smaller element and indicates the right position of pivot found so far
  
    for (int j = low; j <= high - 1; j++) 
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
void quickSort(int arr[], int low, int high) 
{ 
    if (low < high) 
    { 
        /* pi is partitioning index, arr[p] is now 
        at right place */
        int pi = partition(arr, low, high); 
  
        // Separately sort elements before 
        // partition and after partition 
        quickSort(arr, low, pi - 1); 
        quickSort(arr, pi + 1, high); 
    } 
} 

int main(){
    double t1 = cpu_time();
    int arr[] = {0,1,5,6,13,14,18,19,4,5,9,10,17,18,22,23,23,24,28,29,36,37,41,42,27,28,32,33,40,41,45,46,66,67,71,72,79,80,84,85,70,71,75,76,83,84,88,89,89,90,94,95,102,103,107,108,93,94,98,99,106,107,111,112,3,4,8,9,16,17,21,22,7,8,12,13,20,21,25,26,26,27,31,32,39,40,44,45,30,31,35,36,43,44,48,49,69,70,74,75,82,83,87,88,73,74,78,79,86,87,91,92,92,93,97,98,105,106,110,111,96,97,101,102,109,110,114,115,45,46,50,51,58,59,63,64,49,50,54,55,62,63,67,68,68,69,73,74,81,82,86,87,72,73,77,78,85,86,90,91,111,112,116,117,124,125,129,130,115,116,120,121,128,129,133,134,134,135,139,140,147,148,152,153,138,139,143,144,151,152,156,157,48,49,53,54,61,62,66,67,52,53,57,58,65,66,70,71,71,72,76,77,84,85,89,90,75,76,80,81,88,89,93,94,114,115,119,120,127,128,132,133,118,119,123,124,131,132,136,137,137,138,142,143,150,151,155,156,141,142,146,147,154,155,159,160}; 
    int n = sizeof(arr) / sizeof(arr[0]); 
    quickSort(arr, 0, n - 1); 
    double t2 = cpu_time();
    printf("elapsed time: %.6f seconds\n", t2 - t1);
    for (int i = 0; i<n ; i++){
        printf("%d;",arr[i]);
    }
}