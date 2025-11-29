from graph import DirectedGraph
from egde import Edge
from random import randint

class GraphServices:
    def __init__(self):
        self.graph = DirectedGraph()

    @staticmethod
    def generate_random_graph(nr_of_vertices:int, nr_of_edges:int):
        graph = DirectedGraph(nr_of_vertices)

        while nr_of_edges > 0:
            try:
                graph.add_edge(randint(0, nr_of_vertices), randint(0, nr_of_vertices), randint(0, 1000))
                nr_of_edges -= 1
            except Exception:
                pass

        return graph

    def read_graph_from_file(self, file_descriptor:str):
        with open(file_descriptor, "r") as file:
            tokens = file.readline().split(" ")
            n, m = int(tokens[0].strip()), int(tokens[1].strip().removesuffix("\n"))

            self.graph = DirectedGraph(n)

            while m > 0:
                tokens = file.readline().split(" ")
                v_from, v_to, cost = int(tokens[0].strip()), int(tokens[1].strip()), int(tokens[2].strip().removesuffix("\n"))
                self.graph.add_edge(v_from, v_to, cost)

                m -= 1

    def save_graph_to_file(self, file_descriptor:str):
        with open(file_descriptor, "w") as file:
            n = self.graph.get_nr_of_vertices()
            file.write(f"{n} {self.graph.get_nr_of_edges()}\n\n")
            for v in self.graph.vertices_iterator():
                if self.graph.get_out_degree(v) != 0:
                    for out_neighbor in self.graph.outbound_iterator(v):
                        file.write(f"{v} {out_neighbor} {self.graph.get_cost(v, out_neighbor)}\n")