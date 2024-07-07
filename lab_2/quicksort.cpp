#include <iostream>
#include <vector>
#include <gettime.h>
using namespace std;

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

int partition(vector<int> &arr, int start, int end)
{
    int pivot = arr[end];
    int i = start - 1;    

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

void quicksort(vector<int> &arr, int start, int end)
{
    if (start < end)
    {
        int pi = partition(arr, start, end);
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
                                     quicksort(arr, 0, arr.size()); });
        cout << "Time taken to quicksort " << size << " items: " << time << " nanoseconds\n";
    }
}