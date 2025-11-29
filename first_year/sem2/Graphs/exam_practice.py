from collections import defaultdict, deque

def count_longest_paths(graph, s, t):
    Q = deque([s])
    distance = defaultdict(lambda:float('-inf'))
    distance[s] = 0
    count = defaultdict(int)
    count[s] = 1

    while Q:
        u = Q.popleft()
        for v in graph[u]:
            if distance[v] < distance[u] + 1:
                distance[v] = distance[u] + 1
                count[v] = count[u]
                Q.append(v)
            elif distance[v] == distance[u] + 1:
                count[v] += count[u]
    
    return count[t]

def find_min_cost_paths(graph, s, t):
    Q = deque([s])
    distance = defaultdict(lambda:float('inf'))
    count = defaultdict(int)

    distance[s] = 0
    count[s] = 1

    while Q:
        u = Q.popleft()
        for (v, w) in graph[u]:
            if distance[v] > distance[u] + w:
                distance[v] = distance[u] + w
                count[v] = count[u]
                Q.append(v)
            elif distance[v] == distance[u] + w:
                count[v] += count[u]
    
    return count[t]

def find_min_cycle(graph):
    n = len(graph)
    dist = [[float('inf')] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if graph[i][j] != 0:
                dist[i][j] = 1

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]
    
    min_cycle_length = min(dist[i][i] for i in range(n))

    if min_cycle_length != float('inf'):
        return min_cycle_length
    
    return "No cycle exists!\n"

def find_min_cycle_through_vertex(graph, v):
    n = len(graph)
    dist = [[float('inf')] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            if graph[i][j] != 0:
                dist[i][j] = 1

    for k in range(n):
        for i in range(n):
            for j in range(n):
                if dist[i][j] > dist[i][k] + dist[k][j]:
                    dist[i][j] = dist[i][k] + dist[k][j]

    if dist[v][v] == float('inf'):
        return "No cycles found!\n"
    
    return dist[v][v]

# graph = [
#     [0, 1, 0, 0],
#     [0, 0, 1, 0],
#     [1, 0, 0, 1],
#     [0, 0, 0, 0]
# ]

# for v in range(4):
#     print(f"Cycle through vertex {v}: {find_min_cycle_through_vertex(graph, v)}\n")