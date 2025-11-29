#pragma once
#include <cmath>

class Edge {
    public:
        long long edge_id;
    
        Edge(int a, int b); // unique identifier for an edge, and also order sensitive                                                                      // Cantor's pairing function: f(x, y) = (x + y) * (x + y + 1) / 2 + y 
    };