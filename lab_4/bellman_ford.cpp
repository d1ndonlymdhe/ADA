#include <iostream>
#include <vector>
#include <algorithm>
#include "gettime.h"
using namespace std;

class Edge
{
public:
    int src, dest, weight;
    Edge()
    {
    }
    Edge(int src, int dest, int weight)
    {
        this->src = src;
        this->dest = dest;
        this->weight = weight;
    }
};

class Graph
{
public:
    int V, E;
    Edge *edges;
    Graph(int V, int E)
    {
        this->V = V;
        this->E = E;
        this->edges = new Edge[E];
    }
};

void bellman_ford(Graph g, int src)
{
    int v = g.V;
    int e = g.E;
    int *dist = new int[v];
    for (int i = 0; i < v; i++)
    {
        dist[i] = INT_MAX;
    }
    dist[src] = 0;
    for (int i = 0; i < v - 1; i++)
    {
        for (int j = 0; j < e; j++)
        {
            int u = g.edges[j].src;
            int v = g.edges[j].dest;
            int wieght = g.edges[j].weight;
            if (dist[u] != INT_MAX && dist[u] + wieght < dist[v])
            {
                dist[v] = dist[u] + wieght;
            }
        }
    }
    for (int i = 0; i < e; i++)
    {
        int u = g.edges[i].src;
        int v = g.edges[i].dest;
        int weight = g.edges[i].weight;
        if (dist[u] != INT_MAX && dist[u] + weight < dist[v])
        {
            cout << "Negative weight cycle " << endl;
            return;
        }
    }

    for (int i = 0; i < v; i++)
    {
        cout << i << "\t\t " << dist[i] << endl;
    }
}

int main()
{
    int V = 5;
    int E = 8;
    Graph graph(V, E);

    graph.edges[0].src = 0;
    graph.edges[0].dest = 1;
    graph.edges[0].weight = -1;

    graph.edges[1].src = 0;
    graph.edges[1].dest = 2;
    graph.edges[1].weight = 4;

    graph.edges[2].src = 1;
    graph.edges[2].dest = 2;
    graph.edges[2].weight = 3;

    graph.edges[3].src = 1;
    graph.edges[3].dest = 3;
    graph.edges[3].weight = 2;

    graph.edges[4].src = 1;
    graph.edges[4].dest = 4;
    graph.edges[4].weight = 2;

    graph.edges[5].src = 3;
    graph.edges[5].dest = 2;
    graph.edges[5].weight = 5;

    graph.edges[6].src = 3;
    graph.edges[6].dest = 1;
    graph.edges[6].weight = 1;

    graph.edges[7].src = 4;
    graph.edges[7].dest = 3;
    graph.edges[7].weight = -3;

    long long time = getTime([&]()
                             { bellman_ford(graph, 0); });
    cout << "time = " << time << " ns";
}