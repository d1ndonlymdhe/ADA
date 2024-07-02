#include <iostream>
#include <vector>
#include <gettime.h>
using namespace std;

vector<int> merge(vector<int> left, int pivot, vector<int> right)
{
    vector<int> arr;
    for (size_t i = 0; i < left.size(); i++)
    {
        arr.push_back(left[i]);
    }
    arr.push_back(pivot);
    for (size_t i = 0; i < right.size(); i++)
    {
        arr.push_back(right[i]);
    }
    return arr;
}

vector<int> mergesort(vector<int> arr)
{
    size_t size = arr.size();
    if (size == 0)
    {
        return {};
    }
    if (size == 1)
    {
        return arr;
    }
    if (size == 2)
    {
        if (arr[1] < arr[0])
        {
            int t = arr[0];
            arr[0] = arr[1];
            arr[1] = t;
        }
        return arr;
    }
    vector<int> left, right;
    size_t pivotIdx = size / 2;
    for (size_t i = 0; i < size; i++)
    {
        if (i != pivotIdx)
        {
            if (arr[i] <= arr[pivotIdx])
            {
                left.push_back(arr[i]);
            }
            else
            {
                right.push_back(arr[i]);
            }
        }
    }
    vector<int> leftSort = mergesort(left);
    int pivot = arr[pivotIdx];
    vector<int> rightSort = mergesort(right);
    return merge(leftSort, pivot, rightSort);
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
                                     mergesort(arr); });
        cout << "Time taken to mergesort " << size << " items: " << time << " nanoseconds\n";
    }
}