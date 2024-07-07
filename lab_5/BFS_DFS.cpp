#include <iostream>
#include <queue>
#include <stack>
#include <vector>
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
            cout << names[v] << " " << endl;
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
                    cout << names[top] << endl;
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

int main()
{
    Graph g(6, {"A", "B", "C", "D", "E", "F"});
    g.matrix = {{0, 1, 1, 0, 0, 0}, {1, 0, 1, 1, 1, 0}, {1, 0, 1, 1, 1, 0}, {0, 1, 1, 0, 1, 1}, {0, 1, 1, 1, 0, 1}, {0, 0, 0, 1, 1, 0}};
    cout << "DFS" << endl;
    g.dfs();
    cout << "BFS" << endl;
    g.bfs();
}