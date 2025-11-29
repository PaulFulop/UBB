from edge import Edge
from copy import deepcopy

class DirectedGraph:
    def __init__(self, n=0, m=0):
        self.__n = n
        self.__m = m
        self.__vertices = list()
        self.__outbounds = dict()
        self.__inbounds = dict()
        self.__costs = dict()

        for i in range(n):
            self.__vertices.append(i)
            self.__outbounds[i] = []
            self.__inbounds[i] = []

    def add_vertex(self, v:int):
        if self.valid_vertex(v) == False:
            raise Exception("Invalid vertex!\n")

        if self.existing_vertex(v) == True:
            raise Exception("Vertex already exists!\n")

        self.__vertices.append(v)
        self.__outbounds[v] = []
        self.__inbounds[v] = []
        self.__n = max(self.__n, v)
    
    def remove_vertex(self, v:int):
        if self.valid_vertex(v) == False:
            raise Exception("Invalid vertex!\n")
        
        if self.existing_vertex(v) == False:
            raise Exception("Vertex not found!\n")

        cnt = 0
        for neighbors in self.__outbounds.values():
            if v in neighbors:
                self.remove_edge(cnt, v)
            cnt += 1

        cnt = 0
        for neighbors in self.__inbounds.values():
            if v in neighbors:
                self.remove_edge(v, cnt)
            cnt += 1
        
        
        self.__outbounds.pop(v)
        self.__inbounds.pop(v)
        self.__vertices.remove(v)
    
    def add_edge(self, v_from:int, v_to:int, e_cost:int):
        edge_id = Edge(v_from, v_to).edge_id

        if self.valid_edge(v_from, v_to) == False:
            raise Exception("Invalid edge!\n")
        
        if self.existing_edge(v_from, v_to) == True:
            raise Exception("Edge already exists!\n")

        self.__outbounds[v_from].append(v_to)
        self.__inbounds[v_to].append(v_from)
        self.__costs[edge_id] = e_cost
        self.__m += 1

    def remove_edge(self, v_from:int, v_to:int):
        if self.existing_edge(v_from, v_to) == False:
            raise Exception("Edge does not exist!\n")

        self.__outbounds[v_from].remove(v_to)
        self.__inbounds[v_to].remove(v_from)
        self.__costs.pop(Edge(v_from, v_to).edge_id)
        self.__m -= 1

    def get_nr_of_vertices(self):
        return len(self.__vertices)
    
    def get_nr_of_edges(self):
        return self.__m
    
    def vertices_iterator(self):
        for vertex in self.__vertices:
            yield vertex

    def edges_iterator(self):
        for edge_id, cost in self.__costs.items():
            v_from, v_to = self.get_endpoints(edge_id)
            yield [v_from, v_to, cost]

    def inbound_iterator(self, vertex_to:int):
        for neighbor in self.__inbounds[vertex_to]:
            yield neighbor

    def outbound_iterator(self, vertex_from:int):
        for neighbor in self.__outbounds[vertex_from]:
            yield neighbor

    def get_in_degree(self, vertex_to:int):
        return len(self.__inbounds[vertex_to])

    def get_out_degree(self, vertex_from:int):
        return len(self.__outbounds[vertex_from])

    def get_cost(self, vertex_from:int, vertex_to:int):
        if self.existing_edge(vertex_from, vertex_to) == False:
            raise Exception("The edge does not exist!\n")
        
        return self.__costs[Edge(vertex_from, vertex_to).edge_id]

    def set_cost(self, vertex_from:int, vertex_to:int, new_cost:int):
        if self.existing_edge(vertex_from, vertex_to) == False:
            raise Exception("The edge does not exist!\n")
        
        self.__costs[Edge(vertex_from, vertex_to).edge_id] = new_cost

    def copy(self):
        return deepcopy(self)

    def existing_vertex(self, v:int):
        return v in self.__vertices

    def valid_vertex(self, v:int):
        return  v >= 0 

    def valid_edge(self, v_from:int, v_to:int):
        return self.valid_vertex(v_from) and self.valid_vertex(v_to) and self.existing_vertex(v_from) and self.existing_vertex(v_to)

    def existing_edge(self, v_from:int, v_to:int):
        return v_from in self.__outbounds.keys() and v_to in self.__outbounds[v_from]

    def get_endpoints(self, edge_id:int):
        v1, v2 = 0, 0
        w = ((8 * edge_id + 1)**0.5 - 1) // 2 

        v2 = edge_id - w * (w + 1) // 2
        v1 = w - v2 

        return (int(v1), int(v2))

    def clear(self):
        self.__n = 0
        self.__m = 0
        self.__vertices.clear()
        self.__inbounds.clear()
        self.__outbounds.clear()