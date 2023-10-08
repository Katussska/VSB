#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <algorithm>

using namespace std;

struct Node
{
    vector<Node *> neighbors;
    int id;
    bool added = false;
    bool pushed = false;
    int dist = -1;
};

struct Graph
{
    Node *nodes;
    int count;
};

/**
 * Nacte graf ze souboru
 *
 * @param fileName Jmeno souboru, ze ktereho bude graf nacten
 * @return Nacteny graf ve forme struktury Graph
 */

Graph readGraph(string fileName)
{
    int count;
    int from, to;
    ifstream infile;
    infile.open(fileName);

    if (!infile.is_open())
    {
        cerr << "File could not be opened" << endl;
        exit(-1);
    }

    infile >> count;
    Node *nodes = new Node[count];
    Graph graph = {nodes, count};

    for (int i = 0; i < count; i++)
    {
        nodes[i].id = i;
    }
    while (!infile.eof())
    {
        infile >> from >> to;
        if (!infile.fail())
        {
            nodes[from].neighbors.push_back(nodes + to);
            nodes[to].neighbors.push_back(nodes + from);
        }
    }
    infile.close();
    return graph;
}

/**
 * Vypise na standardni vystup vsechny hodnoty z vektoru oddelene mezerami a odradkuje.
 *
 * @param v Vektor, jehoz hodnoty se vypisuji
 */
void printVector(vector<int> v)
{
    for (int i : v)
    {
        cout << i << " ";
    }
    cout << endl;
}

int sumComponent(Graph graph, int start)
{
    stack<Node *> nodeStack;
    nodeStack.push(&graph.nodes[start]);
    graph.nodes[start].pushed = true;
    int current = start;
    int sum = 0;

    while (nodeStack.empty() == false)
    {
        current = nodeStack.top()->id;
        if (graph.nodes[current].added == false)
        {
            graph.nodes[current].added = true;
            sum += nodeStack.top()->id;
            nodeStack.pop();

            for (unsigned int i = 0; i < (graph.nodes[current].neighbors.size()); i++)
            {
                if (graph.nodes[current].neighbors[i]->pushed == false)
                {
                    nodeStack.push(graph.nodes[current].neighbors[i]);
                    graph.nodes[current].neighbors[i]->pushed = true;
                }
            }
        }
    }  
    return sum;
}

vector<int> findComponents(Graph graph)
{
    vector<int> compSum;
    int start;

    for (int i = 0; i < graph.count; i++)
    {

        if (graph.nodes[i].added == false)
        {
            start = i;
            compSum.push_back(sumComponent(graph, start));
        }
    }
    return compSum;
}

vector<int> findNeighbours(Graph graph, int start, int dist)
{
    queue<Node *> nodeStack;
    nodeStack.push(&graph.nodes[start]);
    graph.nodes[start].pushed = true;
    graph.nodes[start].dist = 0;
    int current = start;

    while (nodeStack.empty() == false)
    {
        current = nodeStack.front()->id;
        graph.nodes[current].added = true;
        nodeStack.pop();
        for (unsigned int i = 0; i < (graph.nodes[current].neighbors.size()); i++)
        {

            if (graph.nodes[current].neighbors[i]->pushed == false)
            {
                graph.nodes[current].neighbors[i]->dist = graph.nodes[current].dist + 1;
                nodeStack.push(graph.nodes[current].neighbors[i]);
                graph.nodes[current].neighbors[i]->pushed = true;
            }
        }
    } 

    vector<int> foundIds;
    for (int i = 0; i < graph.count; i++)
    {
        if (graph.nodes[i].dist == dist)
        {
            foundIds.push_back(graph.nodes[i].id);
        }
    }
    return foundIds;
}

int main(int argc, char **argv)
{
    if (argc < 4)
    {
        return -1;
    }

    Graph graph;
    vector<int> vect;
    graph = readGraph(argv[1]);
    vect = findComponents(graph);
    sort(vect.begin(), vect.end());
    cout << "Komponenty: ";
    printVector(vect);
    delete[] graph.nodes;

    graph = readGraph(argv[1]);
    vect = findNeighbours(graph, stoi(argv[2]), stoi(argv[3]));
    sort(vect.begin(), vect.end());
    cout << "Sousede vrcholu " << argv[2] << " ve vzdalenosti " << argv[3] << ": ";
    printVector(vect);
    delete[] graph.nodes;
    return 1;
}