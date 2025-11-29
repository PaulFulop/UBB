#include <iostream>
#include <fstream>
#include <random>
#include "Directed_Graph.h"
using namespace std;

mt19937 gen(random_device{}());

// External functions
void WriteGraph(DirectedGraph& dgraph, string filename);
void ReadGraph(DirectedGraph& dgraph, string filename);
DirectedGraph GenerateRandomGraph(int n, int m);
int random(int limit);
void PrintMenu();
void StartMenu();

int main()
{
    StartMenu();
    return 0;
}

void PrintMenu()
{
    cout << "List of functionalities:\n\n"
        << "1 -> read the graph from a text file\n"
        << "2 -> write the graph to a text file\n"
        << "3 -> generate a random graph with specified number of vertices and edges, and write it to a text file\n"
        << "4 -> get the number of vertices and the number of edges\n"
        << "5 -> display the set of vertices\n"
        << "6 -> display the set of edges\n"
        << "7 -> search for an edge\n"
        << "8 -> get the in-degree and out-degree of a vertex\n"
        << "9 -> display the set of outbound edges of a vertex\n"
        << "10 -> display the set of inbound edges of a vertex\n"
        << "11 -> get the endpoints of an edge specified by edge id\n"
        << "12 -> add an edge\n"
        << "13 -> remove an edge\n"
        << "14 -> add a vertex\n"
        << "15 -> remove a vertex\n"
        << "16 -> change the cost of an edge\n"
        << "17 -> find the connected of a unidirected graph using BFS traversal of the graph\n"
        << "0 -> exit\n";
}

void StartMenu()
{
    long long edge_id;
    int cmd = 0;
    int v, v1, v2, cost;
    int n, m;
    string input_file = "main_graph.txt", output_file = "graph_modif.txt", rg_output_file = "random_graph1.txt";
    pair<vector<long long>::iterator, vector<long long>::iterator> it_edges;

    DirectedGraph dgraph, random_graph;
    PrintMenu();
    while (true)
    {
        cout << "\n> ";
        cin >> cmd;

        switch (cmd)
        {
            case 1:
                ReadGraph(dgraph, input_file);
                cout << "A graph has been read!\n";
                break;
            case 2:
                WriteGraph(dgraph, output_file);
                cout << "The graph has been written to the file.\n";
                break;
            case 3:
                n, m;
                cout << "Insert the number of vertices here: ";
                cin >> n;

                cout << "Insert the number of edges here: ";
                cin >> m;

                dgraph = GenerateRandomGraph(n, m);
                WriteGraph(dgraph, rg_output_file);
                cout << "A random graph has been generated and written to the file.\n";
                break;
            case 4:
                cout << "The number of vertices is " << dgraph.GetNrOfVertices() << " and the number of edges is " << dgraph.GetNrOfEdges() << ".\n";
                break;
            case 5:
                if (!dgraph.GetNrOfVertices())
                    cout << "No vertces in the graph!\n";
                else
                {
                    cout << "The set of vertices is:\n\n";
                    pair<vector<int>::iterator, vector<int>::iterator> it_vertices = dgraph.IterVertices();
                    for (vector<int>::iterator it = it_vertices.first; it != it_vertices.second; ++it)
                        cout << *it << '\n';
                }
                break;
            case 6:
                if (!dgraph.GetNrOfEdges())
                    cout << "No edges in the graph!\n";
                else
                {
                    cout << "The set of edges is:\n\n";
                    pair<unordered_map<long long, int>::iterator, unordered_map<long long, int>::iterator> it_edges = dgraph.IterEdges();
                    for (unordered_map<long long, int>::iterator it = it_edges.first; it != it_edges.second; ++it)
                        cout << it->first << ' ' << it->second << '\n';
                }
                break;
            case 7:
                v1, v2;
                cout << "Insert the endpoints of an edge here: ";
                cin >> v1 >> v2;
                edge_id = dgraph.FindEdge(v1, v2);

                if (edge_id == -1)
                    cout << "No edge with endpoints " << v1 << " and " << v2 << " has been found.\n";
                else
                    cout << "Found edge with id " << edge_id << ".\n";
                break;
            case 8:
                v;
                cout << "Insert the vertex here: ";
                cin >> v;

                if (dgraph.GetInDegree(v) == -1)
                    cout << "Invalid vertex!\n";
                else
                    cout << "Vertex " << v << " has a in-degree of " << dgraph.GetInDegree(v) << " and a out-degree of " << dgraph.GetOutDegree(v) << ".\n";
                break;
            case 9:
                v;
                cout << "Insert the vertex here: ";
                cin >> v;

                it_edges = dgraph.IterOutboundEdges(v);
                if (it_edges.first == it_edges.second)
                    cout << "Vertex " << v << " has no outbound edges.\n";
                else
                {
                    for (vector<long long>::iterator it2 = it_edges.first; it2 != it_edges.second; ++it2)
                    {
                        pair<int, int> endpoints = dgraph.GetEndpoints(*it2);
                        cout << endpoints.first << ' ' << endpoints.second << ' ' << dgraph.edges[*it2] << '\n';
                    }
                }
                break;
            case 10:
                int v;
                cout << "Insert the vertex here: ";
                cin >> v;

                it_edges = dgraph.IterInboundEdges(v);
                if (it_edges.first == it_edges.second)
                    cout << "Vertex " << v << " has no outbound edges.\n";
                else
                {
                    for (vector<long long>::iterator it2 = it_edges.first; it2 != it_edges.second; ++it2)
                    {
                        pair<int, int> endpoints = dgraph.GetEndpoints(*it2);
                        cout << endpoints.first << ' ' << endpoints.second << ' ' << dgraph.edges[*it2] << '\n';
                    }
                }
                break;
            case 11:
                cout << "Insert the edge id here: ";
                cin >> edge_id;
                tie(v1, v2) = dgraph.GetEndpoints(edge_id);

                if (dgraph.FindEdge(v1, v2) == -1)
                    cout << "No such edge found in the graph!\n";
                else
                    cout << "Found edge with endpoints " << v1 << " and " << v2 << ".\n";
                break;
            case 12:
                cout << "Insert a new edge here (<vertex1> <vertex2> <cost>): ";
                cin >> v1 >> v2 >> cost;
                try {
                    dgraph.AddEdge(v1, v2, cost);
                    cout << "The new edge has been added.\n";
                }
                catch (const exception& e){
                    cout << e.what();
                }
                break;
            case 13:
                cout << "Insert the endpoints of an edge here: ";
                cin >> v1 >> v2;

                try {
                    dgraph.RemoveEdge(v1, v2);
                    cout << "The egde has been removed.\n";
                }
                catch (const exception& e) {
                    cout << e.what();
                }
                break;
            case 14:
                cout << "Insert the new vertex here: ";
                cin >> v;

                try {
                    dgraph.AddVertex(v);
                    cout << "The new vertex has been added.\n";
                }
                catch (const exception& e) {
                    cout << e.what();
                }
                break;
            case 15:
                cout << "Insert the vertex here: ";
                cin >> v;

                try {
                    dgraph.RemoveVertex(v);
                    cout << "The vertex has been removed.\n";
                }
                catch (const exception& e) {
                    cout << e.what();
                }
                break;
            case 16:
                cout << "Insert the endpoints of an edge here and new cost (<vertex1> <vertex2> <new_cost>): ";
                cin >> v1 >> v2 >> cost;

                try {
                    dgraph.ChangeCost(v1, v2, cost);
                    cout << "The cost of the edge has been changed.\n";
                }
                catch (const exception& e) {
                    cout << e.what();
                }
                break;
            case 17:
                // TODO continue here
                break;
            case 0:
                cout << "Exiting...\n";
                exit(0);
                break;
            default:
                cout << "Invalid command.\n";
                break;
        }
    }
}

void WriteGraph(DirectedGraph& dgraph, string filename)
{
    ofstream fout(filename);

    fout << dgraph.GetNrOfVertices() << ' ' << dgraph.m << "\n\n";
    pair<vector<int>::iterator, vector<int>::iterator> it_vertices = dgraph.IterVertices();
    for (vector<int>::iterator it1 = it_vertices.first; it1 != it_vertices.second; ++it1)
    {
        if (dgraph.GetOutDegree(*it1))
        {
            pair<vector<long long>::iterator, vector<long long>::iterator> it_edges = dgraph.IterOutboundEdges(*it1);
            for (vector<long long>::iterator it2 = it_edges.first; it2 != it_edges.second; ++it2)
            {
                pair<int, int> endpoints = dgraph.GetEndpoints(*it2);
                fout << endpoints.first << ' ' << endpoints.second << ' ' << dgraph.edges[*it2] << '\n';
            }
        }
    }

    fout.close();
}

void ReadGraph(DirectedGraph& dgraph, string filename)
{
    ifstream fin(filename);
    dgraph.ClearGraph();

    int n, m;
    int v1, v2, cost;
    fin >> n >> m;

    dgraph.n = n;

    for (int i = 0; i < n; ++i)
        dgraph.AddVertex(i);

    while(m--)
    {
        fin >> v1 >> v2 >> cost;
        dgraph.AddEdge(v1, v2, cost);
    }

    fin.close();
}

DirectedGraph GenerateRandomGraph(int n, int m)
{
    DirectedGraph dgraph(n);
    if (1LL * m <= 1LL * (n * n) && m >= 0) // if the number of edges does not exceed the max. amount of edges on a directed graph of n vertices
    {
        while(m)
        {
            int v1 = random(n), v2 = random(n);
            
            if (dgraph.FindEdge(v1, v2) == -1)
            {
                int cost = random(1000);
                dgraph.AddEdge(v1, v2, cost);
                --m;
            }
        }
    }

    return dgraph;
}

int random(int limit)
{
    uniform_int_distribution<> distr(0, limit - 1);
    return distr(gen);
}