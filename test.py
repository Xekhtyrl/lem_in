from collections import deque
import numpy as np

def bfs_level_graph(graph, source, sink, level):
    n = len(graph)
    level[:] = [-1] * n
    level[source] = 0
    queue = deque([source])
    
    while queue:
        u = queue.popleft()
        for v in range(n):
            if graph[u][v] > 0 and level[v] == -1:
                level[v] = level[u] + 1
                queue.append(v)
    
    return level[sink] != -1

def dfs_blocking_flow(graph, u, sink, flow, level, start):
    if u == sink:
        return flow
    
    for v in range(start[u], len(graph)):
        if graph[u][v] > 0 and level[v] == level[u] + 1:
            available_flow = min(flow, graph[u][v])
            pushed_flow = dfs_blocking_flow(graph, v, sink, available_flow, level, start)
            if pushed_flow > 0:
                graph[u][v] -= pushed_flow
                graph[v][u] += pushed_flow
                return pushed_flow
    
    return 0

def dinic_max_flow(graph, source, sink):
    n = len(graph)
    level = [-1] * n
    total_flow = 0
    
    while bfs_level_graph(graph, source, sink, level):
        start = [0] * n
        while True:
            flow = dfs_blocking_flow(graph, source, sink, float('inf'), level, start)
            if flow == 0:
                break
            total_flow += flow
    
    return total_flow

# Example graph as an adjacency matrix (capacity of the edges)
graph = [
	[0,1,1,1,0,0,0,0,0,0,1,0],
	[0,0,1,0,0,1,0,0,0,0,0,0],
	[0,0,0,0,1,0,0,0,0,0,0,0],
	[0,0,0,0,0,0,1,0,0,0,0,0],
	[0,0,0,0,0,0,0,0,1,0,0,0],
	[0,0,0,0,0,0,0,1,0,0,0,0],
	[0,0,0,0,0,0,0,0,0,1,0,0],
	[0,0,0,0,0,0,0,0,0,0,0,1],
	[0,0,0,0,0,0,0,0,0,0,0,1],
	[0,0,0,0,0,0,0,0,0,0,0,1],
	[0,0,0,0,0,0,0,0,0,0,0,1],
	[0,0,0,0,0,0,0,0,0,0,0,0]
]
source = 0
sink = 11
max_flow = dinic_max_flow(graph, source, sink)
print(f"The maximum flow is {max_flow}")
