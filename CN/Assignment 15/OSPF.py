import heapq

def add_edge(graph, u, v, weight):
    if u not in graph: graph[u] = []
    if v not in graph: graph[v] = []
    graph[u].append((v, weight))
    graph[v].append((u, weight))

def ospf_dijkstra(graph, start):
    dist = {node: float('inf') for node in graph}
    dist[start] = 0
    prev = {node: None for node in graph}
    pq = [(0, start)]

    while pq:
        curr_dist, curr_node = heapq.heappop(pq)
        
        if curr_dist > dist[curr_node]:
            continue
            
        for neighbor, weight in graph[curr_node]:
            new_dist = curr_dist + weight
            if new_dist < dist[neighbor]:
                dist[neighbor] = new_dist
                prev[neighbor] = curr_node
                heapq.heappush(pq, (new_dist, neighbor))
    return dist, prev

def get_path_info(prev, start, end):
    path = []
    curr = end
    while curr is not None:
        path.append(curr)
        curr = prev[curr]
    path.reverse()
    
    if len(path) > 1 and path[0] == start:
        return path, path[1]
    return path, start

network = {}
edges = [
    ('u', 'v', 2), ('u', 'x', 1), ('u', 'w', 5),
    ('v', 'x', 2), ('v', 'w', 3),
    ('x', 'y', 1),
    ('w', 'y', 1), ('w', 'z', 5),
    ('y', 'z', 2)
]

for u, v, w in edges:
    add_edge(network, u, v, w)

start_node = 'u'
dist, prev = ospf_dijkstra(network, start_node)

print(f"OSPF shortest path calculations from Router {start_node.upper()}:")
print(f"{'Dest':<6} {'Cost':<6} {'Next Hop':<10} {'Path'}")
print("-" * 40)

for node in sorted(network.keys()):
    if node == start_node: continue
    path, next_hop = get_path_info(prev, start_node, node)
    print(f"{node:<6} {dist[node]:<6} {next_hop:<10} {' -> '.join(path)}")
