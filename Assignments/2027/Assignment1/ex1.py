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
        
        # Dictionary to hold truck caps, ferry caps, ferry served ports, packages weights and pakeges goals
        self.truck_caps = {t_id: cap for t_id, (loc, cap) in initial["Trucks"].items()}
        self.ferry_caps = {f_id: cap for f_id, (port, ports, cap) in initial["Ferries"].items()}
        self.ferry_served_ports = {f_id: ports for f_id, (port, ports, cap) in initial["Ferries"].items()}
        self.package_weights = {p_id: weight for p_id, (start, weight, goal) in initial["Packages"].items()}
        self.package_goals = {p_id: goal for p_id, (start, weight, goal) in initial["Packages"].items()}

        # Create imutable, sorted tuples for the dynamic state components
        truck_state = tuple(sorted((t_id, loc) for t_id, (loc, cap) in initial["Trucks"].items()))
        ferries_state = tuple(sorted((f_id, port) for f_id, (port, ports, cap) in initial["Ferries"].items()))
        packages_state = tuple(sorted((p_id, start) for p_id, (start, weight, goal) in initial["Packages"].items()))
        
        # --- Precompute shortest path distances between all pairs of locations ---
        self.num_locations = initial["Locations"]
        self.distances = self._precompute_distances()
        
        # Start state
        start_state = (truck_state, ferries_state, packages_state)

        search.Problem.__init__(self, start_state)

    def _precompute_distances(self):
        """
        Precomputes the minimum movement cost between every pair of locations
        using Dijkstra's algorithm from each location.
        - Road transition (DRIVE) costs 1.
        - Ferry transition between two ports served by the same ferry costs 5:
          BOARD (1) + SAIL (3) + DISEMBARK (1) = 5.
          (Note: If a truck is ALREADY aboard a ferry during runtime, we handle that
          specifically in h_astar so we never overestimate).
        """
        # Build combined adjacency graph for movement: {u: [(v, weight), ...]}
        adj = {i: [] for i in range(self.num_locations)}
        
        # 1. Add road edges (cost 1)
        for u in self.roads:
            for v in self.roads[u]:
                adj[u].append((v, 1))
                
        # 2. Add ferry edges between served ports (cost 5: BOARD + SAIL + DISEMBARK)
        for f_id, served_ports in self.ferry_served_ports.items():
            for u in served_ports:
                for v in served_ports:
                    if u != v:
                        adj[u].append((v, 5))

        # Run Dijkstra from every location
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
        # Convert tuples to dictionaries for fast lookups
        ferry_locs = dict(ferries_state)
        
        # Calculate current load of each truck
        truck_loads = {t_id: 0 for t_id, _ in trucks_state}
        for p_id, p_loc in packages_state:
            if p_loc in truck_loads: # If package location is a truck ID, it's inside the truck
                truck_loads[p_loc] += self.package_weights[p_id]
                
        # Calculate how many trucks are currently on each ferry
        ferry_truck_counts = {f_id: 0 for f_id in ferry_locs}
        for t_id, t_loc in trucks_state:
            if t_loc in ferry_truck_counts: # If truck location is a ferry ID
                ferry_truck_counts[t_loc] += 1

        # --- 2. Truck Actions: DRIVE, BOARD, DISEMBARK, LOAD, UNLOAD ---
        for t_id, t_loc in trucks_state:
            
            # Case A: Truck is currently aboard a ferry
            if t_loc in ferry_locs:
                f_id = t_loc
                current_port = ferry_locs[f_id]
                
                # Action: DISEMBARK
                new_trucks = tuple((t, current_port) if t == t_id else (t, l) for t, l in trucks_state)
                action_str = f"DISEMBARK{{{t_id},{f_id}}}"
                successors.append((action_str, (new_trucks, ferries_state, packages_state)))
                
                # A truck on a ferry cannot do anything else (cannot drive, load, or unload)
                continue 

            # Case B: Truck is currently on land (at a location)
            # Action: DRIVE
            if t_loc in self.roads:
                for target_loc in self.roads[t_loc]:
                    new_trucks = tuple((t, target_loc) if t == t_id else (t, l) for t, l in trucks_state)
                    action_str = f"DRIVE{{{t_id},{t_loc},{target_loc}}}"
                    successors.append((action_str, (new_trucks, ferries_state, packages_state)))
            
            # Action: BOARD
            if t_loc in self.ports:
                for f_id, f_port in ferries_state:
                    # Check if ferry is at the same port and has room
                    if f_port == t_loc and ferry_truck_counts[f_id] < self.ferry_caps[f_id]:
                        new_trucks = tuple((t, f_id) if t == t_id else (t, l) for t, l in trucks_state)
                        action_str = f"BOARD{{{t_id},{f_id}}}"
                        successors.append((action_str, (new_trucks, ferries_state, packages_state)))
            
            # Action: LOAD and UNLOAD
            for p_id, p_loc in packages_state:
                # UNLOAD: Package is inside THIS truck
                if p_loc == t_id:
                    new_packages = tuple((p, t_loc) if p == p_id else (p, l) for p, l in packages_state)
                    action_str = f"UNLOAD{{{p_id},{t_id}}}"
                    successors.append((action_str, (trucks_state, ferries_state, new_packages)))
                
                # LOAD: Package is at the same location as the truck
                elif p_loc == t_loc:
                    # Pruning 1: Do not load a package if it is already at its final goal location
                    if t_loc == self.package_goals[p_id]:
                        continue
                    
                    # Check if the truck has enough capacity
                    if truck_loads[t_id] + self.package_weights[p_id] <= self.truck_caps[t_id]:
                        new_packages = tuple((p, t_id) if p == p_id else (p, l) for p, l in packages_state)
                        action_str = f"LOAD{{{p_id},{t_id}}}"
                        successors.append((action_str, (trucks_state, ferries_state, new_packages)))

        # --- 3. Ferry Actions: SAIL ---
        for f_id, current_port in ferries_state:
            for target_port in self.ferry_served_ports[f_id]:
                if target_port != current_port:
                    
                    # Pruning 2: If the ferry is totally empty, and NO truck is waiting at the target port,
                    # sailing there right now is pointless. We wait for a truck to arrive at that port first.
                    if ferry_truck_counts[f_id] == 0:
                        truck_at_target = any(t_loc == target_port for _, t_loc in trucks_state)
                        if not truck_at_target:
                            continue # Prune this SAIL action
                            
                    new_ferries = tuple((f, target_port) if f == f_id else (f, p) for f, p in ferries_state)
                    action_str = f"SAIL{{{f_id},{current_port},{target_port}}}"
                    successors.append((action_str, (trucks_state, new_ferries, packages_state)))
                    
        return successors


    def goal_test(self, state):

        # Extract the packages state tuple, which is the third element (index 2)
        packages_state = state[2]
        
        # Check if every package's current location matches its required goal
        return all(loc == self.package_goals[p_id] for p_id, loc in packages_state)

    def h_astar(self, node):
        """
        Admissible heuristic function for A* search.
        Structured into independent, modular sections:
          h(s) = h_load_unload + h_movement
        """
        trucks_state, ferries_state, packages_state = node.state
        
        # Fast lookup dictionaries for current state positions
        truck_locs = dict(trucks_state)
        ferry_locs = dict(ferries_state)

        # =========================================================================
        # SECTION 1: Additive Component (h_load_unload)
        # Counts mandatory LOAD and UNLOAD actions for each undelivered package.
        # Since LOAD/UNLOAD actions apply to a single package at a time, they can 
        # be safely summed across all packages.
        # =========================================================================
        h_load_unload = 0
        
        for p_id, p_loc in packages_state:
            goal_loc = self.package_goals[p_id]
            
            # Case 1: Package is already at its final destination on the ground
            if p_loc == goal_loc:
                continue
                
            # Case 2: Package is currently inside a truck
            if p_loc in truck_locs:
                # Needs at least 1 UNLOAD action to be placed at its destination
                h_load_unload += 1
            # Case 3: Package is lying on the ground at a non-goal location
            else:
                # Needs at least 1 LOAD and 1 UNLOAD action
                h_load_unload += 2

        # =========================================================================
        # SECTION 2: Max Component (h_movement)
        # Estimates the minimum movement cost (DRIVE, BOARD, SAIL, DISEMBARK) 
        # required for the farthest undelivered package to reach its goal.
        # We take the MAX across packages because multiple packages can share 
        # truck drives and ferry sails.
        # =========================================================================
        h_movement = 0
        
        for p_id, p_loc in packages_state:
            goal_loc = self.package_goals[p_id]
            
            if p_loc == goal_loc:
                continue
                
            # Subcase 2A: Package is on the ground at location p_loc
            if p_loc not in truck_locs:
                pkg_move_cost = self.distances[p_loc][goal_loc]
                
            # Subcase 2B: Package is inside a truck (p_loc is the truck_id)
            else:
                t_loc = truck_locs[p_loc]
                
                # Truck is standing on the ground at location t_loc
                if t_loc not in ferry_locs:
                    pkg_move_cost = self.distances[t_loc][goal_loc]
                    
                # Truck is currently aboard a ferry (t_loc is the ferry_id)
                else:
                    f_id = t_loc
                    current_port = ferry_locs[f_id]
                    
                    # Because the truck is ALREADY on the ferry, it already paid the BOARD cost (1).
                    # From here, it can either:
                    # Option 1: DISEMBARK at current_port (cost 1) + travel from current_port to goal
                    cost_disembark_now = 1 + self.distances[current_port][goal_loc]
                    
                    # Option 2: SAIL to another served port (cost 3) + DISEMBARK (cost 1) + travel to goal
                    cost_sail_then_disembark = min(
                        (3 + 1 + self.distances[other_port][goal_loc]
                         for other_port in self.ferry_served_ports[f_id]
                         if other_port != current_port),
                        default=float('inf')
                    )
                    
                    pkg_move_cost = min(cost_disembark_now, cost_sail_then_disembark)
                    
            # Update the maximum movement cost among all packages
            if pkg_move_cost > h_movement:
                h_movement = pkg_move_cost

        # =========================================================================
        # SECTION 3: Final Combination
        # Combine independent lower bounds into the final admissible heuristic.
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
