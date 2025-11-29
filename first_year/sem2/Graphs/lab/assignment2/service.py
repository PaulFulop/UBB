from graph import Graph
from random import randint

class GraphServices:
    def __init__(self):
        self.graph = Graph()

    @staticmethod
    def generate_random_graph(nr_of_vertices:int, nr_of_edges:int):
        graph = Graph(nr_of_vertices)

        while nr_of_edges > 0:
            try:
                graph.add_edge(randint(0, nr_of_vertices), randint(0, nr_of_vertices))
                nr_of_edges -= 1
            except Exception:
                pass

        return graph

    def read_graph_from_file(self, file_descriptor:str):
        with open(file_descriptor, "r") as file:
            tokens = file.readline().split(" ")
            n, m = int(tokens[0].strip()), int(tokens[1].strip().removesuffix("\n"))

            self.graph = Graph(n)

            while m > 0:
                tokens = file.readline().split(" ")
                v_from, v_to = int(tokens[0].strip()), int(tokens[1].strip().removesuffix("\n"))
                self.graph.add_edge(v_from, v_to)

                m -= 1

    def save_graph_to_file(self, file_descriptor:str):
        with open(file_descriptor, "w") as file:
            n = self.graph.get_nr_of_vertices()
            file.write(f"{n} {self.graph.get_nr_of_edges()}\n\n")
            for v1, v2 in self.graph.edges_iterator():
                file.write(f"{v1} {v2}\n")

    # FOR LAB 2
    # finds all the connected components of the graph and returns a list of Graph objects
    def find_cc(self) -> list:
        visited = [False] * self.graph.get_nr_of_vertices
        connected_components = []
        for vertex in self.graph.vertices_iterator():
            if not visited[vertex]:
                connected_components.append(GraphServices.bfs(self.graph, vertex, visited))

        return connected_components

    # FOR LAB 2
    # saves the connected components of the graph in a file with a given name/path
    def save_cc_to_file(self, file_descriptor:str):
        with open(file_descriptor, "w") as file:
            cc = self.find_cc()
            current_cc = 1
            for component in cc:
                file.write(f"Connected component {current_cc}:\n")
                file.write(f"Nodes: {component.vertices}\n")
                file.write(f"Edges:\n")

                if component.get_nr_of_edges == 0:
                    file.write("No edges.\n")
                else:
                    for v1, v2 in component.edges_iterator():
                        file.write(f"{v1} {v2}\n")
                    file.write("\n")
                    current_cc += 1
    
    # FOR LAB 2
    # Breadth-First Search algorithm -> starts from a node and finds all the nodes that can be accessible from it 
    # It basically finds the connected component containing starting_node and returns it as a Graph object   
    @staticmethod
    def bfs(graph:Graph, starting_node:int, visited:list) -> Graph:
        head = 0
        cc = Graph()
        cc.add_vertex(starting_node)
        visited[starting_node] = True

        while head < cc.get_nr_of_vertices:
            current_node = cc.vertices[head]
            head += 1
            neighbors = graph.get_neighbors(current_node)

            for neighbor in neighbors:
                if not visited[neighbor]:
                    visited[neighbor] = True
                    cc.add_vertex(neighbor)
                    cc.add_edge(current_node, neighbor)
                else:
                    if not cc.existing_edge(current_node, neighbor) and graph.existing_edge(current_node, neighbor):
                        cc.add_edge(current_node, neighbor)

        return cc