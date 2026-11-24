import ex1_check
import search
import utils
import heapq

id = ["212535660"]


class LogisticsProblem(search.Problem):
    """This class implements a logistics problem"""

    def __init__(self, initial):
        # Initialize an adjacency list of the roads using dic of sets
        self.roads = {}
        for i in range(initial["Locations"]):
            self.roads[i] = set()

        # Unpack each road tuple and add to the adjacency list
        for u, v in initial["Roads"]:
            self.roads[u].add(v)
            self.roads[v].add(u)

        self.ports = initial["Ports"]
        
        # Dictionary to hold truck caps, ferry caps, ferry served ports, packages weights and packages goals
        self.truck_caps = {t_id: cap for t_id, (loc, cap) in initial["Trucks"].items()}
        self.ferry_caps = {f_id: cap for f_id, (port, ports, cap) in initial["Ferries"].items()}
        self.ferry_served_ports = {f_id: ports for f_id, (port, ports, cap) in initial["Ferries"].items()}
        self.package_weights = {p_id: weight for p_id, (start, weight, goal) in initial["Packages"].items()}
        self.package_goals = {p_id: goal for p_id, (start, weight, goal) in initial["Packages"].items()}

        # --- Precompute shortest path distances between all pairs of locations ---
        self.num_locations = initial["Locations"]
        self.distances = self._precompute_distances()

        # Create immutable, sorted tuples for the dynamic state components
        truck_state = tuple(sorted((t_id, loc) for t_id, (loc, cap) in initial["Trucks"].items()))
        ferries_state = tuple(sorted((f_id, port) for f_id, (port, ports, cap) in initial["Ferries"].items()))
        packages_state = tuple(sorted((p_id, start) for p_id, (start, weight, goal) in initial["Packages"].items()))
        
        # Start state
        start_state = (truck_state, ferries_state, packages_state)

        search.Problem.__init__(self, start_state)

    def _precompute_distances(self):
        """
        Precomputes the minimum movement cost between every pair of locations
        using Dijkstra's algorithm from each location.
        """
        adj = {i: [] for i in range(self.num_locations)}
        
        for u in self.roads:
            for v in self.roads[u]:
                adj[u].append((v, 1))
                
        for f_id, served_ports in self.ferry_served_ports.items():
            for u in served_ports:
                for v in served_ports:
                    if u != v:
                        adj[u].append((v, 5))

        all_distances = {}
        for start_node in range(self.num_locations):
            dist = {i: float('inf') for i in range(self.num_locations)}
            dist[start_node] = 0
            pq = [(0, start_node)]
            
            while pq:
                current_dist, u = heapq.heappop(pq)
                
                if current_dist > dist[u]:
                    continue
                    
                for v, weight in adj[u]:
                    if dist[u] + weight < dist[v]:
                        dist[v] = dist[u] + weight
                        heapq.heappush(pq, (dist[v], v))
                        
            all_distances[start_node] = dist
            
        return all_distances

    def path_cost(self, c, state1, action, state2):
        """ Do not change this. Returns the cost of reaching state2 from state1 via action,
        given cost c to reach state1: SAIL costs 3, every other action costs 1"""
        return c + (3 if action.startswith("SAIL") else 1)

    def successor(self, state):
        trucks_state, ferries_state, packages_state = state
        successors = []

        # --- 1. Pre-computations for O(1) lookups ---
        ferry_locs = dict(ferries_state)
        
        # Calculate current load of each truck
        truck_loads = {t_id: 0 for t_id, _ in trucks_state}
        for p_id, p_loc in packages_state:
            if p_loc < 0:  # Package is inside a truck
                in_truck_id = -p_loc - 1
                truck_loads[in_truck_id] += self.package_weights[p_id]
                
        # Calculate how many trucks are currently on each ferry
        ferry_truck_counts = {f_id: 0 for f_id in ferry_locs}
        for t_id, t_loc in trucks_state:
            if t_loc < 0:  # Truck is aboard a ferry
                on_ferry_id = -t_loc - 1
                ferry_truck_counts[on_ferry_id] += 1

        # --- 2. Truck Actions: DRIVE, BOARD, DISEMBARK, LOAD, UNLOAD ---
        for t_id, t_loc in trucks_state:
            
            # Case A: Truck is currently aboard a ferry (t_loc < 0)
            if t_loc < 0:
                f_id = -t_loc - 1
                current_port = ferry_locs[f_id]
                
                # Action: DISEMBARK (truck moves to current_port)
                new_trucks = tuple((t, current_port) if t == t_id else (t, l) for t, l in trucks_state)
                action_str = f"DISEMBARK{{{t_id},{f_id}}}"
                successors.append((action_str, (new_trucks, ferries_state, packages_state)))
                continue 

            # Case B: Truck is currently on land (t_loc >= 0)
            # Action: DRIVE
            if t_loc in self.roads:
                for target_loc in self.roads[t_loc]:
                    new_trucks = tuple((t, target_loc) if t == t_id else (t, l) for t, l in trucks_state)
                    action_str = f"DRIVE{{{t_id},{t_loc},{target_loc}}}"
                    successors.append((action_str, (new_trucks, ferries_state, packages_state)))
            
            # Action: BOARD
            if t_loc in self.ports:
                for f_id, f_port in ferries_state:
                    if f_port == t_loc and ferry_truck_counts[f_id] < self.ferry_caps[f_id]:
                        new_trucks = tuple((t, -(f_id + 1)) if t == t_id else (t, l) for t, l in trucks_state)
                        action_str = f"BOARD{{{t_id},{f_id}}}"
                        successors.append((action_str, (new_trucks, ferries_state, packages_state)))
            
            # Action: LOAD and UNLOAD
            for p_id, p_loc in packages_state:
                # UNLOAD: Package is inside THIS truck
                if p_loc == -(t_id + 1):
                    new_packages = tuple((p, t_loc) if p == p_id else (p, l) for p, l in packages_state)
                    action_str = f"UNLOAD{{{p_id},{t_id}}}"
                    successors.append((action_str, (trucks_state, ferries_state, new_packages)))
                
                # LOAD: Package is on the ground at the same location as the truck
                elif p_loc == t_loc:
                    if t_loc == self.package_goals[p_id]:
                        continue
                    
                    if truck_loads[t_id] + self.package_weights[p_id] <= self.truck_caps[t_id]:
                        new_packages = tuple((p, -(t_id + 1)) if p == p_id else (p, l) for p, l in packages_state)
                        action_str = f"LOAD{{{p_id},{t_id}}}"
                        successors.append((action_str, (trucks_state, ferries_state, new_packages)))

        # --- 3. Ferry Actions: SAIL ---
        for f_id, current_port in ferries_state:
            for target_port in self.ferry_served_ports[f_id]:
                if target_port != current_port:
                    
                    if ferry_truck_counts[f_id] == 0:
                        truck_at_target = any(t_loc == target_port for _, t_loc in trucks_state)
                        if not truck_at_target:
                            continue
                            
                    new_ferries = tuple((f, target_port) if f == f_id else (f, p) for f, p in ferries_state)
                    action_str = f"SAIL{{{f_id},{current_port},{target_port}}}"
                    successors.append((action_str, (trucks_state, new_ferries, packages_state)))
                    
        return successors

    def goal_test(self, state):
        packages_state = state[2]
        return all(p_loc == self.package_goals[p_id] for p_id, p_loc in packages_state)

    def h_astar(self, node):
        """
        Admissible heuristic function for A* search.
        Structured into independent, modular sections:
          h(s) = h_load_unload + h_movement
        """
        trucks_state, ferries_state, packages_state = node.state
        
        truck_locs = dict(trucks_state)
        ferry_locs = dict(ferries_state)

        def get_truck_ground_dist(t_id, target_loc):
            t_loc = truck_locs[t_id]
            if t_loc >= 0:
                return self.distances[t_loc][target_loc]
            else:
                f_id = -t_loc - 1
                current_port = ferry_locs[f_id]
                cost_disembark_now = 1 + self.distances[current_port][target_loc]
                cost_sail = min(
                    (4 + self.distances[other_port][target_loc]
                     for other_port in self.ferry_served_ports[f_id]
                     if other_port != current_port),
                    default=float('inf')
                )
                return min(cost_disembark_now, cost_sail)

        # =========================================================================
        # SECTION 1: Additive Component (h_load_unload)
        # =========================================================================
        h_load_unload = 0
        
        for p_id, p_loc in packages_state:
            goal_loc = self.package_goals[p_id]
            
            if p_loc == goal_loc:
                continue
                
            if p_loc < 0:
                h_load_unload += 1
            else:
                h_load_unload += 2

        # =========================================================================
        # SECTION 2: Max Component (h_movement)
        # =========================================================================
        h_movement = 0
        
        for p_id, p_loc in packages_state:
            goal_loc = self.package_goals[p_id]
            
            if p_loc == goal_loc:
                continue
                
            if p_loc >= 0:
                p_weight = self.package_weights[p_id]
                min_pickup_dist = min(
                    (get_truck_ground_dist(t_id, p_loc)
                     for t_id, _ in trucks_state
                     if self.truck_caps[t_id] >= p_weight),
                    default=0
                )
                pkg_move_cost = min_pickup_dist + self.distances[p_loc][goal_loc]
                
            else:
                t_id = -p_loc - 1
                pkg_move_cost = get_truck_ground_dist(t_id, goal_loc)
                    
            if pkg_move_cost > h_movement:
                h_movement = pkg_move_cost

        # --- Capacity Bound to address heavy payload scenarios ---
        max_truck_cap = max(self.truck_caps.values()) if self.truck_caps else 1
        loc_weights = {}
        for p_id, p_loc in packages_state:
            if p_loc >= 0 and p_loc != self.package_goals[p_id]:
                loc_weights[p_loc] = loc_weights.get(p_loc, 0) + self.package_weights[p_id]
                
        h_capacity = sum((w + max_truck_cap - 1) // max_truck_cap for w in loc_weights.values())
        h_movement = max(h_movement, h_capacity)

        # =========================================================================
        # SECTION 3: Final Combination
        # =========================================================================
        total_h = h_load_unload + h_movement
        return total_h


def create_logistics_problem(game):
    print("<<create_logistics_problem")
    """ Create a logistics problem, based on the description.
    game - dictionary as described in pdf file"""
    return LogisticsProblem(game)


if __name__ == '__main__':
    ex1_check.main()