#pragma once
#include <unordered_map>
#include <vector>
#include <exception>
#include <cmath>
#include <algorithm>
using namespace std;

class DirectedGraph {
    public:
        int n, m;
        
        // Automatically initialized to an empty map
        vector<int> vertices;
        unordered_map<int, vector<int>> in_vertices;
        unordered_map<int, vector<int>> out_vertices;
        unordered_map<long long, int> edges;

        DirectedGraph();
        DirectedGraph(int n);
        ~DirectedGraph();
    
        DirectedGraph& operator = (const DirectedGraph& other_graph) noexcept;

        int GetNrOfVertices() const;

        int GetNrOfEdges() const;

        void AddEdge(int v1, int v2, int cost);
    
        void AddVertex(int v);
    
        void RemoveVertex(int v);
    
        void RemoveEdge(int v1, int v2);
    
        int GetInDegree(int v);
    
        int GetOutDegree(int v);
    
        int FindEdge(int v1, int v2);
    
        void ChangeCost(int v1, int v2, int new_cost);

        int GetCost(int v1, int v2);

        void ClearGraph();
    
        pair<int, int> GetEndpoints(long long edge_id);
    
        pair<unordered_map<long long, int>::iterator, unordered_map<long long, int>::iterator> IterEdges();

        pair<vector<long long>::iterator, vector<long long>::iterator> IterOutboundEdges(int v);
    
        pair<vector<long long>::iterator, vector<long long>::iterator> IterInboundEdges(int v);
    
        pair<vector<int>::iterator, vector<int>::iterator> IterVertices();
    
    private:
        // for parsing
        vector<long long> outbound_edges;
        vector<long long> inbound_edges;
    
        // for validation
        bool ValidVertex(int v);

        bool ValidEdge(int v1, int v2);

        bool ExistingVertex(int v);
    
        bool ExistingEdge(int v1, int v2);
    };