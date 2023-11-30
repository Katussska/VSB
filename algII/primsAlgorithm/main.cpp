#include <iostream>
#include <vector>
#include <climits>

int najdiMinimum(std::vector<int>& key, std::vector<bool>& mstSet, int V) {
    int minimum = INT_MAX;
    int minIndex = -1;

    for (int v = 0; v < V; ++v) {
        if (!mstSet[v] && key[v] < minimum) {
            minimum = key[v];
            minIndex = v;
        }
    }

    return minIndex;
}

void tiskKostry(std::vector<int>& parent, std::vector<std::vector<int>>& graph, int V) {
    std::cout << "Hrany     Vaha" << std::endl;
    for (int i = 1; i < V; ++i) {
        std::cout << parent[i] << " - " << i << "    " << graph[i][parent[i]] << std::endl;
    }
}

void primAlgorithm(std::vector<std::vector<int>>& graph, int V) {
    std::vector<int> parent(V);
    std::vector<int> key(V, INT_MAX);
    std::vector<bool> mstSet(V, false);

    key[0] = 0;

    for (int count = 0; count < V - 1; ++count) {
        int u = najdiMinimum(key, mstSet, V);
        mstSet[u] = true;

        for (int v = 0; v < V; ++v) {
            if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                parent[v] = u;
                key[v] = graph[u][v];
            }
        }
    }

    tiskKostry(parent, graph, V);
}

int main() {
    std::vector<std::vector<int>> graph = {
            {0, 2, 0, 6, 0},
            {2, 0, 3, 8, 5},
            {0, 3, 0, 0, 7},
            {6, 8, 0, 0, 9},
            {0, 5, 7, 9, 0}
    };
    int V = graph.size();

     primAlgorithm(graph, V);

    graph = {
            {0, 9, 75, 0, 0},
            {9, 0, 95, 19, 42},
            {75, 95, 0, 51, 66},
            {0, 19, 51, 0, 31},
            {0, 42, 66, 31, 0}
    };
    V = graph.size();

    primAlgorithm(graph, V);

    graph = {
            {0, 19, 5, 0, 0},
            {19, 0, 5, 9, 2},
            {5, 5, 0, 1, 6},
            {0, 9, 1, 0, 1},
            {0, 2, 6, 1, 0}
    };
   V = graph.size();

    primAlgorithm(graph, V);

    return 0;
}