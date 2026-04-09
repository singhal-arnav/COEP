import copy

class Router:
    def __init__(self, name):
        self.name = name
        self.routing_table = {}
        self.neighbors = {}
        self.INFINITY = 16

    def init_routes(self):
        self.routing_table[self.name] = [self.name, 0]
        for neighbor, cost in self.neighbors.items():
            self.routing_table[neighbor] = [neighbor, cost]

    def update_table(self, received_table, source_router):
        updated = False
        link_cost = self.neighbors[source_router]
        
        for dest, (next_hop_at_source, dist) in received_table.items():
            new_dist = min(dist + link_cost, self.INFINITY)
            
            if dest not in self.routing_table:
                self.routing_table[dest] = [source_router, new_dist]
                updated = True
            else:
                current_next_hop = self.routing_table[dest][0]
                current_dist = self.routing_table[dest][1]
                
                if new_dist < current_dist:
                    self.routing_table[dest] = [source_router, new_dist]
                    updated = True
                elif source_router == current_next_hop and new_dist != current_dist:
                    self.routing_table[dest] = [source_router, new_dist]
                    updated = True
                    
        return updated

    def print_routing_table(self):
        print(f"  Router {self.name}:")
        print(f"    {'Dest':<8} {'Next Hop':<10} {'Distance'}")
        print(f"    {'-'*8} {'-'*10} {'-'*8}")
        for dest in sorted(self.routing_table):
            next_hop, dist = self.routing_table[dest]
            dist_str = "INF" if dist >= self.INFINITY else dist
            print(f"    {dest:<8} {next_hop:<10} {dist_str}")
        print()

def simulate_rip():
    router_a = Router("A")
    router_c = Router("C")
    router_d = Router("D")

    router_a.neighbors = {"C": 8, "D": 3}
    router_c.neighbors = {"A": 8, "D": 4}
    router_d.neighbors = {"A": 3, "C": 4}

    routers = [router_a, router_c, router_d]
    for r in routers:
        r.init_routes()

    print(f"Graph Links: A-C(8), A-D(3), C-D(4)\n")

    iteration = 0
    while True:
        print(f"-> Round {iteration}\n")
        for r in routers:
            r.print_routing_table()

        snapshots = {r.name: copy.deepcopy(r.routing_table) for r in routers}
        any_updated = False
        
        for r in routers:
            for neighbor_name in r.neighbors:
                if r.update_table(snapshots[neighbor_name], neighbor_name):
                    any_updated = True

        if not any_updated:
            print("Final Converged Tables\n")
            for r in routers:
                r.print_routing_table()
            print("Convergence achieved.")
            break
        
        iteration += 1
        if iteration > 15: break

simulate_rip()
