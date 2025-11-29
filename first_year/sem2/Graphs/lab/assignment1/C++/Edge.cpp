#include "Edge.h"

Edge::Edge(int a, int b): edge_id {1LL * ((a + b) * (a + b + 1) / 2 + b)} // unique identifier for an edge, and also order sensitive
{}                                                                       // Cantor's pairing function: f(x, y) = (x + y) * (x + y + 1) / 2 + y 