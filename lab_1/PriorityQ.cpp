#include <iostream>
#include <vector>
#include "gettime.h"
using namespace std;

class PriorityQ
{
public:
    vector<pair<int, int>> queue;

    int getParent(int idx)
    {
        if (idx % 2 == 0)
            return idx / 2 - 1;
        return idx / 2;
    }

    int leftIdx(int idx)
    {
        return 2 * idx + 1;
    }
    int rightIdx(int idx)
    {
        return 2 * idx + 2;
    }

    void shiftUp(int idx)
    {
        while (idx > 0 && queue[getParent(idx)].second < queue[idx].second)
        {
            swap(queue[getParent(idx)], queue[idx]);
            idx = getParent(idx);
        }
    }

    void shiftDown(int idx)
    {
        int maxIdx = idx;
        int left = leftIdx(idx);
        if (left < queue.size() && queue[left].second > queue[maxIdx].second)
        {
            maxIdx = left;
        }

        int right = rightIdx(idx);

        if (right < queue.size() && queue[right].second > queue[maxIdx].second)
        {
            maxIdx = right;
        }

        if (idx != maxIdx)
        {
            swap(queue[idx], queue[maxIdx]);
            shiftDown(maxIdx);
        }
    }

    int extractMax()
    {
        int res = queue[0].first;
        queue[0] = queue[queue.size() - 1];
        queue.pop_back();
        shiftDown(0);
        return res;
    }

    void remove(int idx)
    {
        queue[idx].second = queue[0].second + 1;
        shiftUp(idx);
        extractMax();
    }

    void push(int value, int priority)
    {
        queue.push_back({value, priority});
        shiftUp(queue.size() - 1);
    }
};

int main()
{
    vector<int> sizes;
    int start_size = 1000000;
    int increment = 500000;
    sizes.push_back(start_size);
    srand(time(NULL));
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + increment);
    }
    for (size_t i = 0; i < sizes.size(); i++)
    {
        int size = sizes[i];
        PriorityQ pq;
        long long time = getTime([&]()
                                 {
            for (size_t i = 0; i < size; i++)
            {
                //insert random values with random priority
                pq.push(rand(), rand());
            } });
        cout << "Insertion of " << size << " elements took " << time << " nanoseconds" << endl;
        time = getTime([&]()
                       {
            for (size_t i = 0; i < size; i++)
            {
                //remove random
                pq.remove(rand() % pq.queue.size());
            } });
        cout << "removal of " << size << " elements took " << time << " nanoseconds" << endl;
    }
    return 0;
}