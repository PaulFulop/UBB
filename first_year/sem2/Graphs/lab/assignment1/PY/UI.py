from directed_graph import DirectedGraph
from service import GraphServices

class UI:
    def __init__(self):
        self.__serv = GraphServices()
        self.__input_file = "main_graph.txt"
        self.__output_file = "graph_modif.txt"
        self.__rg_output_file = "random_graph1.txt"
    
    @staticmethod
    def print_menu():
        print("\nList of functionalities:\n\n"
            "1 -> read the graph from a text file\n"
            "2 -> write the graph to a text file\n"
            "3 -> generate a random graph with specified number of vertices and edges, and write it to a text file\n"
            "4 -> get the number of vertices and the number of edges\n"
            "5 -> display the set of vertices\n"
            "6 -> display the set of edges\n"
            "7 -> search for an edge\n"
            "8 -> get the in-degree and out-degree of a vertex\n"
            "9 -> display the set of outbound edges of a vertex\n"
            "10 -> display the set of inbound edges of a vertex\n"
            "11 -> get the endpoints of an edge specified by edge id\n"
            "12 -> add an edge\n"
            "13 -> remove an edge\n"
            "14 -> add a vertex\n"
            "15 -> remove a vertex\n"
            "16 -> change the cost of an edge\n"
            "0 -> exit\n")
    
    def start_menu(self):
        UI.print_menu()

        while True:
            try:
                cmd = int(input("> "))
            except Exception:
                cmd = 18


            match cmd:
                case 1:
                    self.__serv.read_graph_from_file(self.__input_file)
                    print("The graph has been read!\n")
                case 2:
                    self.__serv.save_graph_to_file(self.__output_file)
                    print("The graph has been saved to the file!\n")
                case 3:
                    r_graph = self.__serv.graph.copy()

                    n, m = input("Insert the number of vertices and the number of edges here: ").split()
                    n = int(n)
                    m = int(m)

                    self.__serv.graph = self.__serv.generate_random_graph(n, m)
                    self.__serv.save_graph_to_file(self.__rg_output_file)
                    self.__serv.graph = r_graph
                    print(f"The random graph has been generated and saved to the file {self.__rg_output_file}.\n")
                case 4:
                    print(f"The number of vertices is {self.__serv.graph.get_nr_of_vertices()}, and the number of edges is {self.__serv.graph.get_nr_of_edges()}.\n")
                case 5:
                    print("The set of vertices:\n")
                    for i in self.__serv.graph.vertices_iterator():
                        print(i)
                case 6:
                    print("The set of edges:\n")
                    for i in self.__serv.graph.edges_iterator():
                        print(i)
                case 7: #input will be the endpoints of the edge
                    v1, v2 = input("Insert the endpoints of the edge you want to find here: " ).split()
                    v1 = int(v1)
                    v2 = int(v2)

                    if self.__serv.graph.existing_edge(v1, v2) == True:
                        print(f"Found edge from vertex {v1} to vertex {v2}, having the cost of {self.__serv.graph.get_cost(v1, v2)}\n")
                    else:
                        print("Edge not found.\n")
                case 8:
                    v = int(input("Insert the vertex here: "))
                    print(f"The in-degree of vertex {v} is {self.__serv.graph.get_in_degree(v)}, and the out-degree is {self.__serv.graph.get_out_degree(v)}.\n")
                case 9:
                    v = int(input("Insert the vertex here: "))
                    print("The set of outbound edges:\n")
                    for i in self.__serv.graph.outbound_iterator(v):
                        print(f"{v} {i} {self.__serv.graph.get_cost(v, i)}")
                case 10:
                    v = int(input("Insert the vertex here: "))
                    print("The set of inbound edges:\n")
                    for i in self.__serv.graph.inbound_iterator(v):
                        print(f"{i} {v} {self.__serv.graph.get_cost(i, v)}")
                case 11:
                    edge_id = int(input("Insert the edge id here: "))
                    print(f"The endpoints of this edge are {self.__serv.graph.get_endpoints(edge_id)}.\n")
                case 12:
                    try:
                        v1, v2, cost = input("Insert the endpoints and the cost of the new edge here: " ).split()
                        v1 = int(v1)
                        v2 = int(v2)
                        cost = int(cost)

                        self.__serv.graph.add_edge(v1, v2, cost)
                        print("The new edge has been added.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 13:
                    try:
                        v1, v2 = input("Insert the endpoints of edge to be removed here: " ).split()
                        v1 = int(v1)
                        v2 = int(v2)

                        self.__serv.graph.remove_edge(v1, v2)
                        print("The edge has been removed.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 14:
                    try:
                        v = int(input("Insert the new vertex here: " ))
                        self.__serv.graph.add_vertex(v)
                        print("The new vertex has been added.\n")
                    except Exception:
                        print(str(e) + "\n")
                case 15:
                    try:
                        v = int(input("Insert the vertex here: " ))
                        self.__serv.graph.remove_vertex(v)
                        print("The vertex has been removed.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 16:
                    try:
                        v1, v2, cost = input("Insert the endpoints and the new cost of the edge here: " ).split()
                        v1 = int(v1)
                        v2 = int(v2)
                        cost = int(cost)

                        self.__serv.graph.set_cost(v1, v2, cost)
                        print("The cost of the edge has been updated.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 0:
                    print("Exiting...\n")
                    break
                case _:
                    print("Invalid command.\n")