#include "Directed_Graph.h"
#include "Edge.h"
#include <iostream>

DirectedGraph::DirectedGraph() : n {0}, m {0}
{}

DirectedGraph::DirectedGraph(int n) : n {n}, m {0}
{
    for (int i = 0; i < n; ++i)
        vertices.push_back(i);
}

DirectedGraph::~DirectedGraph()
{}

DirectedGraph& DirectedGraph::operator = (const DirectedGraph& other_graph) noexcept
{
    in_vertices.clear();
    out_vertices.clear();
    edges.clear();

    n = other_graph.n;
    m = other_graph.m;
    vertices = other_graph.vertices;
    in_vertices = other_graph.in_vertices;
    out_vertices = other_graph.out_vertices;
    edges = other_graph.edges;

    return *this;
}   

int DirectedGraph::GetNrOfVertices() const
{
    return vertices.size();
}

int DirectedGraph::GetNrOfEdges() const
{
    return m;
}

void DirectedGraph::AddEdge(int v1, int v2, int cost)
{
    if (!ValidEdge(v1, v2))
        throw exception("Invalid edge input!\n");

    if (FindEdge(v1, v2) != -1)
        throw exception("This edge already exists!\n");

    in_vertices[v2].push_back(v1);
    out_vertices[v1].push_back(v2);
    edges[Edge(v1, v2).edge_id] = cost;
    ++m;
}

void DirectedGraph::AddVertex(int v)
{
    if (!ValidVertex(v))
        throw exception("Invalid vertex input!\n");

    if (ExistingVertex(v))
        throw exception("Vertex already exists!\n");

    in_vertices[v] = vector<int>();
    out_vertices[v] = vector<int>();
    vertices.push_back(v);
    n = max(n, v + 1);
}

void DirectedGraph::RemoveVertex(int v)
{
    if (!ValidVertex(v) || !ExistingVertex(v))
        throw exception("No such vertex found!\n");

    vertices.erase(find(vertices.begin(), vertices.end(), v));

    // removing all the edges connecting to this vertex
    for (int neighbor : in_vertices[v])
    {
        edges.erase(Edge(neighbor, v).edge_id), --m;
        out_vertices[neighbor].erase(find(out_vertices[neighbor].begin(), out_vertices[neighbor].end(), v));
    }

    for (int neighbor : out_vertices[v])
    {
        edges.erase(Edge(v, neighbor).edge_id), --m;
        in_vertices[neighbor].erase(find(in_vertices[neighbor].begin(), in_vertices[neighbor].end(), v));
    }

    // removing vertex from the graph
    in_vertices.erase(v);
    out_vertices.erase(v);       
}

void DirectedGraph::RemoveEdge(int v1, int v2)
{
    if(!ValidEdge(v1, v2) || !ExistingEdge(v1, v2))
        throw exception("No such edge found!\n");

    edges.erase(Edge(v1, v2).edge_id); // removing the edge

    // removing the neighbor property
    in_vertices[v2].erase(find(in_vertices[v2].begin(), in_vertices[v2].end(), v1));
    out_vertices[v1].erase(find(out_vertices[v1].begin(), out_vertices[v1].end(), v2));
    --m;
}

int DirectedGraph::GetInDegree(int v)
{
    if (ValidVertex(v) && ExistingVertex(v))
        return in_vertices[v].size();

    return -1;
}

int DirectedGraph::GetOutDegree(int v)
{
    if (ValidVertex(v) && ExistingVertex(v))
        return out_vertices[v].size();

    return -1;
}

int DirectedGraph::FindEdge(int v1, int v2)
{
    return edges.count(Edge(v1, v2).edge_id) ? Edge(v1, v2).edge_id : -1;
}

void DirectedGraph::ChangeCost(int v1, int v2, int new_cost)
{
    if (FindEdge(v1, v2) == -1)
        throw exception("Edge not found!\n");

    edges[Edge(v1, v2).edge_id] = new_cost;
}

int DirectedGraph::GetCost(int v1, int v2)
{
    if (FindEdge(v1, v2) == -1)
        throw exception("The edge was not found!\n");

    return edges[Edge(v1, v2).edge_id];
}

// decoding cantor pairings function
pair<int, int> DirectedGraph::GetEndpoints(long long edge_id)
{
    int v1, v2;
    int w = floor((sqrt(8 * edge_id + 1) - 1) / 2);
    v2 = edge_id - (1LL * w * (1LL* w + 1) / 2);
    v1 = w - v2;

    return {v1, v2};
}

void DirectedGraph::ClearGraph()
{
    vertices.clear();
    in_vertices.clear();
    out_vertices.clear();
    edges.clear();
    m = 0;
    n = 0;
}

pair<unordered_map<long long, int>::iterator, unordered_map<long long, int>::iterator> DirectedGraph::IterEdges()
{
    return {edges.begin(), edges.end()};
}

pair<vector<long long>::iterator, vector<long long>::iterator> DirectedGraph::IterOutboundEdges(int v)
{
    outbound_edges.clear();
    
    if (ValidVertex(v) && ExistingVertex(v))
    {
        for (int outbound_vertex : out_vertices[v])
            outbound_edges.push_back(Edge(v, outbound_vertex).edge_id);

        return {outbound_edges.begin(), outbound_edges.end()};
    }

    return {outbound_edges.end(), outbound_edges.end()};
}

pair<vector<long long>::iterator, vector<long long>::iterator> DirectedGraph::IterInboundEdges(int v)
{
    inbound_edges.clear();

    if (ValidVertex(v) && ExistingVertex(v))
    {
        for (int inbound_vertex : in_vertices[v])
            inbound_edges.push_back(Edge(inbound_vertex, v).edge_id);

        return {inbound_edges.begin(), inbound_edges.end()};
    }

    return {inbound_edges.end(), inbound_edges.end()};
}

pair<vector<int>::iterator, vector<int>::iterator> DirectedGraph::IterVertices()
{   
    return {vertices.begin(), vertices.end()};
}

bool DirectedGraph::ValidVertex(int v)
{
    return v >= 0; // true if it's a valid vertex value
}

bool DirectedGraph::ValidEdge(int v1, int v2)
{
    return ValidVertex(v1) && ValidVertex(v2) && ExistingVertex(v1) && ExistingVertex(v2); // true if the vertices are valid and exist in the graph
}

bool DirectedGraph::ExistingVertex(int v)
{
    return find(vertices.begin(), vertices.end(), v) != vertices.end();// true if the vertex does exist in the graph
}

bool DirectedGraph::ExistingEdge(int v1, int v2)
{
    return FindEdge(v1, v2) != -1; // true if the edge exists in the graph already
}