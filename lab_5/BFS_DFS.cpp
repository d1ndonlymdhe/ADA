#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include "gettime.h"
#define INFINITY -1

using namespace std;

template <class T>
bool vectorHas(vector<T> vec, T val)
{
    for (size_t i = 0; i < vec.size(); i++)
    {
        if (vec[i] == val)
        {
            return true;
        }
    }
    return false;
}

class Graph
{
public:
    vector<vector<int>> matrix;
    vector<string> names;
    int degree;
    Graph(int degree, vector<string> names)
    {
        this->degree = degree;
        this->names = names;
        matrix = vector<vector<int>>(degree, vector<int>(degree, 0));
    }

    vector<int> getAdjacent(int idx)
    {
        vector<int> arr;
        for (int i = 0; i < degree; i++)
        {
            if (matrix[idx][i] > 0)
            {
                arr.push_back(i);
            }
        }
        return arr;
    }

    void bfs()
    {
        queue<int> q;
        vector<int> visited;
        q.push(0);
        visited.push_back(0);
        do
        {
            int v = q.front();
            q.pop();
            // cout << names[v] << " " << endl;
            for (int i : getAdjacent(v))
            {
                if (!vectorHas(visited, i))
                {
                    q.push(i);
                    visited.push_back(i);
                }
            }
        } while (!q.empty());
    }

    void dfs()
    {
        stack<int> nodes;
        vector<int> visited;
        nodes.push(0);
        if (degree > 0)
        {
            while (visited.size() != degree)
            {
                int top = nodes.top();
                nodes.pop();
                if (!vectorHas(visited, top))
                {
                    // cout << names[top] << endl;
                    visited.push_back(top);
                }

                for (int j : getAdjacent(top))
                {
                    if (!vectorHas(visited, j))
                    {
                        nodes.push(j);
                    }
                }
            }
        }
    }
};

vector<string> names(int n)
{
    vector<string> res;
    for (int i = 0; i < n; i++)
    {
        res.push_back(to_string(i));
    }
    return res;
}

int main()
{
    vector<int> sizes;
    int start_size = 100;
    int increment = 100;
    sizes.push_back(start_size);
    srand(time(NULL));
    for (size_t i = 0; i < 4; i++)
    {
        sizes.push_back(sizes.back() + increment);
    }
    for (int size : sizes)
    {
        Graph g(size, names(size));
        vector<vector<int>> matrix;
        for (int i = 0; i < size; i++)
        {
            vector<int> row;
            for (int j = 0; j < size; j++)
            {
                if (rand() % 2 == 0)
                {
                    row.push_back(1);
                }
                else
                {
                    row.push_back(0);
                }
            }
            matrix.push_back(row);
        }
        g.matrix = matrix;

        cout << "size = " << size << endl;
        long long time = getTime([&]()
                                 { g.dfs(); });
        cout << "DFS time = " << time << endl;
        time = getTime([&]()
                       { g.bfs(); });
        cout << "BFS time = " << time << endl;
    }
}