#include <iostream>
#include <vector>
#include "gettime.h"
using namespace std;

class SubsetSumSolver
{
private:
    vector<int> set;
    int targetSum;
    vector<vector<int>> solutions;

    void backtrack(vector<int> &currentSubset, int currentSum, int index)
    {
        if (currentSum == targetSum)
        {
            solutions.push_back(currentSubset);
            return;
        }
        if (currentSum > targetSum || index >= set.size())
        {
            return;
        }
        currentSubset.push_back(set[index]);
        backtrack(currentSubset, currentSum + set[index], index + 1);
        currentSubset.pop_back();
        backtrack(currentSubset, currentSum, index + 1);
    }

public:
    SubsetSumSolver(const vector<int> &s, int target)
    {
        this->set = s;
        this->targetSum = target;
    }

    vector<vector<int>> solve()
    {
        vector<int> currentSubset;
        backtrack(currentSubset, 0, 0);
        return solutions;
    }
};

class SubsetSumExecutor
{
public:
    static void execute(int size)
    {
        vector<int> set;
        int targetSum = 50;
        for (int i = 0; i < size; i++)
        {
            set.push_back(rand() % 10);
        }
        SubsetSumSolver solver(set, targetSum);
        vector<vector<int>> solutions;
        long long time = getTime([&]()
                                 { solutions = solver.solve(); });
        cout << "Size = " << size << "Time = " << time << endl;
    }
};

bool flag = 0;
void PrintSubsetSum(int i, int n, int set[], int targetSum,
                    vector<int> &subset)
{
    if (targetSum == 0)
    {

        flag = 1;
        cout << "[ ";
        for (int i = 0; i < subset.size(); i++)
        {
            cout << subset[i] << " ";
        }
        cout << "]";
        return;
    }

    if (i == n)
    {
        return;
    }

    PrintSubsetSum(i + 1, n, set, targetSum, subset);

    if (set[i] <= targetSum)
    {

        subset.push_back(set[i]);

        PrintSubsetSum(i + 1, n, set, targetSum - set[i],
                       subset);

        subset.pop_back();
    }
}

int main()
{
    vector<int> sizes;
    int start_size = 15;
    int increment = 1;
    sizes.push_back(start_size);
    srand(time(NULL));
    SubsetSumExecutor::execute(start_size);
    for (size_t i = 0; i < 4; i++)
    {
        start_size += increment;
        sizes.push_back(start_size);
        SubsetSumExecutor::execute(start_size);
    }

    return 0;
}