#include <iostream>
#include <vector>
#include <unordered_map>
#include <gettime.h>
#include <algorithm>

using namespace std;

class Job
{
public:
    string id;
    int deadline;
    int profit;
};

vector<Job> sequencer(vector<Job> inputs)
{
    sort(inputs.begin(), inputs.end(), [](Job a, Job b) -> bool
         { return a.profit > b.profit; });

    int n = inputs.size();
    vector<bool> slot(n - 1, false);
    vector<Job> res(n - 1, Job());
    for (Job input : inputs)
    {
        for (int j = min(n, input.deadline) - 1; j >= 0; j--)
        {
            if (slot[j] == false)
            {
                res[j] = input;
                slot[j] = true;
                break;
            }
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

        vector<Job> arr;
        string id = "a";

        for (int i = 0; i < size; i++)
        {
            Job job;
            job.id = id;
            job.deadline = rand() % 10 + 1;
            job.profit = rand() % 100 + 1;
            arr.push_back(job);
        }

        long long time = getTime([&]
                                 { sequencer(arr); });

        cout << "Size: " << size << " Time: " << time << endl;
    }

    return 0;
}