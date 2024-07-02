#include <iostream>
#include <vector>
#include <gettime.h>
using namespace std;

// Helper function to swap two elements
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

// Partition function
int partition(vector<int> &arr, int start, int end)
{
    int pivot = arr[end]; // Choose the last element as pivot
    int i = start - 1;    // Index of the smaller element

    for (int j = start; j <= end - 1; j++)
    {
        if (arr[j] <= pivot)
        {
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[end]);
    return (i + 1);
}

// Quicksort function
void quicksort(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int pi = partition(arr, start, end); // Partitioning index

        // Recursively sort elements before and after partition
        quicksort(arr, start, pi - 1);
        quicksort(arr, pi + 1, end);
    }
}

int main()
{
    vector<int> sizes;
    int start_size = 1000000;
    int increment = 500000;
    sizes.push_back(start_size);
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + increment);
    }

    for (int size : sizes)
    {
        vector<int> arr;

        for (int i = 0; i < size; i++)
        {
            arr.push_back(rand());
        }

        long long time = getTime([&]()
                                 {
                                    //  cout << "size of arr: " << (sizeof arr) / (sizeof(int)) << "\n";
                                     quicksort(arr, 0, arr.size()); });
        cout << "Time taken to quicksort " << size << " items: " << time << " nanoseconds\n";
    }
}