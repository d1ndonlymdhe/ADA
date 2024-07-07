#include <iostream>
#include "gettime.h"
#include <vector>
#include <algorithm>
using namespace std;

int knapsack(int max_w, int values[], int weights[], int n)
{
    vector<vector<int>> matrix(n + 1, vector<int>(max_w + 1, 0));
    for (int i = 1; i <= n; i++)
    {
        for (int w = 0; w <= max_w; w++)
        {
            int current_value = values[i - 1];
            int current_weight = weights[i - 1];
            if (current_weight <= w)
            {
                matrix[i][w] = max(current_value + matrix[i - 1][w - current_weight], matrix[i - 1][w]);
            }
            else
            {
                matrix[i][w] = matrix[i - 1][w];
            }
        }
    }
    return matrix[n][max_w];
}

int main()
{
    vector<int> sizes;
    int start_size = 1000;
    int increment = 500;
    sizes.push_back(start_size);
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + increment);
    }
    srand(time(0));
    for (int i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        int *values = new int[size];
        int *weights = new int[size];
        for (int i = 0; i < size; i++)
        {
            values[i] = rand() % 1000;
            weights[i] = rand() % 1000;
        }
        int max_w = 100;
        long long time = getTime([&]()
                                 { knapsack(max_w, values, weights, size); });
        cout << "Size: " << size << " Time: " << time << endl;
    }
    return 0;
}
