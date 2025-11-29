class Edge:
    def __init__(self, v1:int, v2:int):
        self.edge_id = (v1 + v2) * (v1 + v2 + 1) // 2 + v2 

    def get_edge_id(self):
        return self.edge_id