from service import GraphServices
from pb6 import solve

class UI:
    def __init__(self):
        self.__serv = GraphServices()
        self.__input_file = "graph1.txt"
        self.__output_file = "output_graph.txt"
        self.__rg_output_file = "random_graph.txt"
        self.__output_cc_file = "output_cc.txt"
    
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
            "8 -> add an edge\n"
            "9 -> remove an edge\n"
            "10 -> add a vertex\n"
            "11 -> remove a vertex\n"
            "12 -> find the connected components of an undirected graph using a breadth-first traversal of the graph and save them to a file\n"
            "13 -> solve for problem 6\n"
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
                    print()
                case 7:
                    v1, v2 = input("Insert the endpoints of the edge you want to find here: " ).split()
                    v1 = int(v1)
                    v2 = int(v2)

                    if self.__serv.graph.existing_edge(v1, v2) == True:
                        print(f"Found edge from vertex {v1} to vertex {v2}\n")
                    else:
                        print("Edge not found.\n")
                case 8:
                    v1, v2 = input("Insert the endpoints of the new edge here: " ).split()
                    v1 = int(v1)
                    v2 = int(v2)
                    try:
                        self.__serv.graph.add_edge(v1, v2)
                        print("The new edge has been added.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 9:
                    try:
                        v1, v2 = input("Insert the endpoints of edge to be removed here: " ).split()
                        v1 = int(v1)
                        v2 = int(v2)

                        self.__serv.graph.remove_edge(v1, v2)
                        print("The edge has been removed.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 10:
                    try:
                        v = int(input("Insert the new vertex here: " ))
                        self.__serv.graph.add_vertex(v)
                        print("The new vertex has been added.\n")
                    except Exception:
                        print(str(e) + "\n")
                case 11:
                    try:
                        v = int(input("Insert the vertex here: " ))
                        self.__serv.graph.remove_vertex(v)
                        print("The vertex has been removed.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 12:
                    try:
                        self.__serv.save_cc_to_file(self.__output_cc_file)
                        print(f"The connected components of the graph have been saved to {self.__output_cc_file}.\n")
                    except Exception as e:
                        print(str(e) + "\n")
                case 13:
                    solve()
                case 0:
                    print("Exiting...\n")
                    break
                case _:
                    print("Invalid command.\n")