#include <iostream>
#include <vector>
#include <unordered_map>
#include <gettime.h>
#include <algorithm>

using namespace std;

float sequencer(vector<pair<int, int>> inputs, int capacity)
{
    sort(inputs.begin(), inputs.end(), [](pair<int, int> a, pair<int, int> b) -> bool
         { return a.first / b.second > a.first / b.second; });

    float res = 0;

    for (pair<int, int> input : inputs)
    {

        if (input.second <= capacity)
        {
            res += input.first;
            capacity -= input.second;
        }
        else
        {
            res += input.first * ((float)capacity / (float)input.second);
            break;
        }
    }

    return res;
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
    srand(time(0));
    for (int size : sizes)
    {

        vector<pair<int, int>> arr;

        for (int i = 0; i < size; i++)
        {
            arr.push_back({rand(), rand()});
        }

        long long time = getTime([&]
                                 { sequencer(arr, rand()); });

        cout << "Size: " << size << " Time: " << time << endl;
    }

    return 0;
}