"""
Island Logistics A* Solver (Assignment 1 - Intro to AI, Bar-Ilan CS 89-570).

AI / Online Sources Disclosure:
- Used an AI coding assistant (Google Antigravity / Gemini) to design,
  mathematically verify admissibility of, implement, and optimize the state
  representation, safe pruning rules, graph precomputations, and modular A*
  heuristic in ex1.py.
"""

from collections import deque
import heapq
import math

import ex1_check
import search
import utils

id = ["212535660"]

_INF = 10**9
_DERANGEMENTS_3 = ((1, 2, 0), (2, 0, 1))
_DERANGEMENTS_4 = (
    (1, 0, 3, 2),
    (1, 2, 3, 0),
    (1, 3, 0, 2),
    (2, 0, 3, 1),
    (2, 3, 0, 1),
    (2, 3, 1, 0),
    (3, 0, 1, 2),
    (3, 2, 0, 1),
    (3, 2, 1, 0),
)


class LogisticsProblem(search.Problem):
    """Optimal A* formulation for the Island Logistics planning domain."""

    def __init__(self, initial):
        # ------------------------------------------------------------------
        # 1. Static map topology & entity metadata (flat index-based tuples)
        # ------------------------------------------------------------------
        n = initial["Locations"]
        self.num_locations = n

        adj_sets = [set() for _ in range(n)]
        for u, v in initial["Roads"]:
            if u != v:
                adj_sets[u].add(v)
                adj_sets[v].add(u)
        raw_roads = [tuple(sorted(adj_sets[i])) for i in range(n)]

        ports_set = set(initial["Ports"])
        self.is_port = tuple(i in ports_set for i in range(n))

        # Sort entity IDs once so dynamic states are flat index-based tuples
        self.truck_ids = tuple(sorted(initial["Trucks"]))
        self.ferry_ids = tuple(sorted(initial["Ferries"]))
        self.pkg_ids = tuple(sorted(initial["Packages"]))

        self.num_trucks = len(self.truck_ids)
        self.num_ferries = len(self.ferry_ids)
        self.num_pkgs = len(self.pkg_ids)

        self.truck_caps = tuple(
            initial["Trucks"][tid][1] for tid in self.truck_ids
        )
        self.max_truck_cap = max(self.truck_caps) if self.truck_caps else 0

        self.ferry_caps = tuple(
            initial["Ferries"][fid][2] for fid in self.ferry_ids
        )
        self.ferry_served_ports = tuple(
            tuple(sorted(set(initial["Ferries"][fid][1])))
            for fid in self.ferry_ids
        )

        self.pkg_weights = tuple(
            initial["Packages"][pid][1] for pid in self.pkg_ids
        )
        self.pkg_goals = tuple(
            initial["Packages"][pid][2] for pid in self.pkg_ids
        )

        init_truck_locs = tuple(
            initial["Trucks"][tid][0] for tid in self.truck_ids
        )
        init_ferry_locs = tuple(
            initial["Ferries"][fid][0] for fid in self.ferry_ids
        )
        init_pkg_locs = tuple(
            initial["Packages"][pid][0] for pid in self.pkg_ids
        )

        # Exact subset-sum effective truck capacity (for h_astar ONLY):
        # Maximum total package weight a truck can ever simultaneously carry
        # from any subset of problem packages without exceeding its nominal cap.
        if self.max_truck_cap > 0 and self.num_pkgs > 0:
            limit_mask = (1 << (self.max_truck_cap + 1)) - 1
            reachable = 1
            for w in self.pkg_weights:
                if 0 < w <= self.max_truck_cap:
                    reachable |= (reachable << w) & limit_mask
            eff_caps = []
            for cap in self.truck_caps:
                masked = reachable & ((1 << (cap + 1)) - 1)
                eff_caps.append(masked.bit_length() - 1 if masked > 1 else 0)
            self.eff_truck_caps = tuple(eff_caps)
        else:
            self.eff_truck_caps = self.truck_caps
        self.max_eff_truck_cap = (
            max(self.eff_truck_caps) if self.eff_truck_caps else 0
        )
        init_w_gcd = 0
        for w in self.pkg_weights:
            init_w_gcd = math.gcd(init_w_gcd, w)
        self.init_w_gcd = init_w_gcd
        self._gcd_cap_cache = {}

        # ------------------------------------------------------------------
        # 2. Safe static relevance & dead-end graph analysis
        # ------------------------------------------------------------------
        relevant = [False] * n
        for loc in init_truck_locs:
            relevant[loc] = True
        for loc in init_pkg_locs:
            relevant[loc] = True
        for loc in self.pkg_goals:
            relevant[loc] = True

        rf_adj_raw = [set(raw_roads[u]) for u in range(n)]
        for fi in range(self.num_ferries):
            if self.ferry_caps[fi] <= 0:
                continue
            served = self.ferry_served_ports[fi]
            for u in served:
                for v in served:
                    if u != v:
                        rf_adj_raw[u].add(v)

        # Any component D of (G_rf \ {u}) with no relevant nodes can never be
        # profitably entered in an optimal plan (actions inside D shift to u).
        dead_loc = [False] * n
        relevant_nodes = [v for v in range(n) if relevant[v]]
        if relevant_nodes:
            seen_all = [False] * n
            q = deque(relevant_nodes)
            for v in relevant_nodes:
                seen_all[v] = True
            while q:
                x = q.popleft()
                for y in rf_adj_raw[x]:
                    if not seen_all[y]:
                        seen_all[y] = True
                        q.append(y)
            for v in range(n):
                if not seen_all[v]:
                    dead_loc[v] = True

            for u in range(n):
                if dead_loc[u]:
                    continue
                visited = [False] * n
                visited[u] = True
                for start in rf_adj_raw[u]:
                    if visited[start] or dead_loc[start]:
                        continue
                    comp = []
                    has_rel = False
                    q = deque([start])
                    visited[start] = True
                    while q:
                        x = q.popleft()
                        comp.append(x)
                        if relevant[x]:
                            has_rel = True
                        for y in rf_adj_raw[x]:
                            if not visited[y] and not dead_loc[y]:
                                visited[y] = True
                                q.append(y)
                    if not has_rel:
                        for x in comp:
                            dead_loc[x] = True

        self.dead_loc = tuple(dead_loc)
        self.has_dead_locs = any(dead_loc)

        # Active roads exclude dead-end locations
        self.roads = tuple(
            tuple(v for v in raw_roads[u] if not dead_loc[v])
            if not dead_loc[u]
            else ()
            for u in range(n)
        )

        # Active ferries: cap > 0 and serving at least 2 non-dead ports
        active_ferry = [False] * self.num_ferries
        active_served = []
        for fi in range(self.num_ferries):
            non_dead = tuple(
                p for p in self.ferry_served_ports[fi] if not dead_loc[p]
            )
            if self.ferry_caps[fi] > 0 and len(non_dead) >= 2:
                active_ferry[fi] = True
                active_served.append(non_dead)
            else:
                active_served.append(())

        # Count how many active ferries serve each port
        ferries_at_port = [[] for _ in range(n)]
        for fi in range(self.num_ferries):
            if active_ferry[fi]:
                for p in active_served[fi]:
                    ferries_at_port[p].append(fi)
        self.port_ferry_count = tuple(len(ferries_at_port[v]) for v in range(n))

        # Dominated isolated ports: non-relevant, no roads, and every active
        # ferry serving v also serves some other non-dominated port q != v.
        no_enter_port = list(dead_loc)
        for v in range(n):
            if no_enter_port[v] or relevant[v] or self.roads[v]:
                continue
            fl = ferries_at_port[v]
            if not fl:
                no_enter_port[v] = True
                continue
            common = set(active_served[fl[0]])
            for fi in fl[1:]:
                common.intersection_update(active_served[fi])
            common.discard(v)
            if any(not no_enter_port[q] for q in common):
                no_enter_port[v] = True

        self.no_enter_port = tuple(no_enter_port)
        self.active_ferry = tuple(active_ferry)
        self.has_inactive_ferries = not all(active_ferry)
        self.active_ferry_indices = tuple(
            fi for fi in range(self.num_ferries) if active_ferry[fi]
        )
        self.ferry_active_targets = tuple(
            tuple(p for p in active_served[fi] if not no_enter_port[p])
            if active_ferry[fi]
            else ()
            for fi in range(self.num_ferries)
        )

        # Pure corridor interiors: degree <= 2, not a port, not relevant.
        # By linearity of travel cost along an empty corridor, there always
        # exists an optimal plan that never unloads at a pure corridor interior.
        self.no_unload_loc = tuple(
            (not relevant[v])
            and (not self.is_port[v])
            and (len(self.roads[v]) <= 2)
            for v in range(n)
        )

        # ------------------------------------------------------------------
        # 3. Symmetry groups & static lookup tables
        # ------------------------------------------------------------------
        self.prev_sym_truck = tuple(
            tuple(
                ti1
                for ti1 in range(ti)
                if self.truck_caps[ti1] == self.truck_caps[ti]
            )
            for ti in range(self.num_trucks)
        )
        self.prev_sym_ferry = tuple(
            tuple(
                fi1
                for fi1 in range(fi)
                if self.active_ferry[fi1]
                and self.active_ferry[fi]
                and self.ferry_caps[fi1] == self.ferry_caps[fi]
                and self.ferry_served_ports[fi1] == self.ferry_served_ports[fi]
            )
            for fi in range(self.num_ferries)
        )
        self.prev_sym_pkg = tuple(
            tuple(
                pi1
                for pi1 in range(pi)
                if self.pkg_weights[pi1] == self.pkg_weights[pi]
                and self.pkg_goals[pi1] == self.pkg_goals[pi]
            )
            for pi in range(self.num_pkgs)
        )

        self.capable_trucks = tuple(
            tuple(
                ti
                for ti in range(self.num_trucks)
                if self.truck_caps[ti] >= self.pkg_weights[pi]
            )
            for pi in range(self.num_pkgs)
        )

        self._load_strs = tuple(
            tuple(f"LOAD{{{pid},{tid}}}" for tid in self.truck_ids)
            for pid in self.pkg_ids
        )
        self._unload_strs = tuple(
            tuple(f"UNLOAD{{{pid},{tid}}}" for tid in self.truck_ids)
            for pid in self.pkg_ids
        )
        self._board_strs = tuple(
            tuple(f"BOARD{{{tid},{fid}}}" for fid in self.ferry_ids)
            for tid in self.truck_ids
        )
        self._disembark_strs = tuple(
            tuple(f"DISEMBARK{{{tid},{fid}}}" for fid in self.ferry_ids)
            for tid in self.truck_ids
        )
        self._drive_strs = tuple(
            {
                (u, v): f"DRIVE{{{tid},{u},{v}}}"
                for u in range(n)
                for v in self.roads[u]
            }
            for tid in self.truck_ids
        )
        self._sail_strs = tuple(
            {
                (u, v): f"SAIL{{{self.ferry_ids[fi]},{u},{v}}}"
                for u in self.ferry_served_ports[fi]
                for v in self.ferry_active_targets[fi]
                if u != v
            }
            for fi in range(self.num_ferries)
        )

        # ------------------------------------------------------------------
        # 4. Connected components of road+ferry graph (safe decomposition)
        # ------------------------------------------------------------------
        rf_adj = [set(self.roads[u]) for u in range(n)]
        for fi in self.active_ferry_indices:
            served = active_served[fi]
            for u in served:
                for v in served:
                    if u != v:
                        rf_adj[u].add(v)
        self._rf_adj = tuple(tuple(sorted(rf_adj[u])) for u in range(n))

        comp_of = [-1] * n
        num_comps = 0
        for loc in range(n):
            if comp_of[loc] == -1:
                q = deque([loc])
                comp_of[loc] = num_comps
                while q:
                    u = q.popleft()
                    for v in self._rf_adj[u]:
                        if comp_of[v] == -1:
                            comp_of[v] = num_comps
                            q.append(v)
                num_comps += 1
        self.comp_of = tuple(comp_of)
        self.num_comps = num_comps

        self.use_comp_decomp = (
            num_comps > 1
            and all(
                comp_of[init_pkg_locs[pi]] == comp_of[self.pkg_goals[pi]]
                for pi in range(self.num_pkgs)
            )
        )
        self.comp_trucks = tuple(
            tuple(
                ti
                for ti in range(self.num_trucks)
                if comp_of[init_truck_locs[ti]] == c
            )
            for c in range(num_comps)
        )
        self.comp_ferries = tuple(
            tuple(
                fi
                for fi in self.active_ferry_indices
                if comp_of[init_ferry_locs[fi]] == c
            )
            for c in range(num_comps)
        )
        self.comp_pkgs = tuple(
            tuple(
                pi
                for pi in range(self.num_pkgs)
                if comp_of[init_pkg_locs[pi]] == c
            )
            for c in range(num_comps)
        )

        # ------------------------------------------------------------------
        # 5. All-pairs shortest path precomputations
        # ------------------------------------------------------------------
        self.dist_full = self._precompute_dijkstra(ferry_weight=5)
        self.dist_no_sail = self._precompute_dijkstra(ferry_weight=2)
        self.dist_cut = self._precompute_bfs_cut()

        ferry_full_dist = []
        ferry_disembark_no_sail = []
        for fi in range(self.num_ferries):
            served = self.ferry_served_ports[fi]
            port_table = {}
            for cur_port in served:
                d_cur = self.dist_full[cur_port]
                row = [
                    1 + d_cur[t] if d_cur[t] < _INF else _INF for t in range(n)
                ]
                for other_port in served:
                    if other_port == cur_port:
                        continue
                    d_other = self.dist_full[other_port]
                    for t in range(n):
                        dt = d_other[t]
                        if dt < _INF:
                            cand = 4 + dt
                            if cand < row[t]:
                                row[t] = cand
                port_table[cur_port] = tuple(row)
            ferry_full_dist.append(port_table)

            row_ns = [_INF] * n
            for q_port in served:
                dq = self.dist_no_sail[q_port]
                for t in range(n):
                    dt = dq[t]
                    if dt < _INF:
                        cand = 1 + dt
                        if cand < row_ns[t]:
                            row_ns[t] = cand
            ferry_disembark_no_sail.append(tuple(row_ns))
        self.ferry_full_dist = tuple(ferry_full_dist)
        self.ferry_disembark_no_sail = tuple(ferry_disembark_no_sail)

        self.ferry_min_cut = tuple(
            tuple(
                min(
                    (self.dist_cut[u][p] for p in self.ferry_served_ports[fi]),
                    default=_INF,
                )
                for fi in range(self.num_ferries)
            )
            for u in range(n)
        )
        self.ferry_max_cut = tuple(
            tuple(
                max(
                    (self.dist_cut[u][p] for p in self.ferry_served_ports[fi]),
                    default=_INF,
                )
                for fi in range(self.num_ferries)
            )
            for u in range(n)
        )

        # ------------------------------------------------------------------
        # 6. Islands (road-only components) & inter-island ferry structures
        # ------------------------------------------------------------------
        island_of = [-1] * n
        num_islands = 0
        for loc in range(n):
            if island_of[loc] == -1:
                q = deque([loc])
                island_of[loc] = num_islands
                while q:
                    u = q.popleft()
                    for v in self.roads[u]:
                        if island_of[v] == -1:
                            island_of[v] = num_islands
                            q.append(v)
                num_islands += 1
        self.island_of = tuple(island_of)
        self.num_islands = num_islands
        self.pkg_goal_islands = tuple(
            self.island_of[g] for g in self.pkg_goals
        )

        road_dist = []
        for src in range(n):
            dist = [_INF] * n
            dist[src] = 0
            q = deque([src])
            while q:
                u = q.popleft()
                du = dist[u] + 1
                for v in self.roads[u]:
                    if dist[v] == _INF:
                        dist[v] = du
                        q.append(v)
            road_dist.append(tuple(dist))
        self.road_dist = tuple(road_dist)

        island_active_ports = [set() for _ in range(num_islands)]
        island_active_ferries = [set() for _ in range(num_islands)]
        for fi in self.active_ferry_indices:
            for p in active_served[fi]:
                isl = island_of[p]
                island_active_ports[isl].add(p)
                island_active_ferries[isl].add(fi)
        # If an island is served by exactly ONE active ferry (inter- or intra-),
        # store its index; otherwise -1.
        self.island_sole_ferry = tuple(
            next(iter(fl)) if len(fl) == 1 else -1
            for fl in island_active_ferries
        )

        dist_to_any_active_port = [_INF] * n
        for loc in range(n):
            isl = island_of[loc]
            if island_active_ports[isl]:
                d_row = self.road_dist[loc]
                dist_to_any_active_port[loc] = min(
                    d_row[p] for p in island_active_ports[isl]
                )
        self.dist_to_any_active_port = tuple(dist_to_any_active_port)

        # Shortest road-only distance between locations on the same island even if
        # ferries teleported between ports for 0 road drives.
        road_dist_free_ferry = []
        for u in range(n):
            isl_u = island_of[u]
            du = self.road_dist[u]
            du_p = dist_to_any_active_port[u]
            row_ff = []
            for v in range(n):
                if island_of[v] != isl_u:
                    row_ff.append(_INF)
                else:
                    d = du[v]
                    if du_p < _INF and dist_to_any_active_port[v] < _INF:
                        via_p = du_p + dist_to_any_active_port[v]
                        if via_p < d:
                            d = via_p
                    row_ff.append(d)
            road_dist_free_ferry.append(tuple(row_ff))
        self.road_dist_free_ferry = tuple(road_dist_free_ferry)

        eff_caps_desc = sorted(self.eff_truck_caps, reverse=True)
        self.max_ferry_weight = tuple(
            sum(eff_caps_desc[: min(self.ferry_caps[fi], self.num_trucks)])
            for fi in range(self.num_ferries)
        )

        island_adj = [set() for _ in range(num_islands)]
        island_ferry_lists = [[] for _ in range(num_islands)]
        island_has_intra_ferry = [False] * num_islands
        island_inter_ports = [set() for _ in range(num_islands)]
        inter_island_ferries = []

        for fi in self.active_ferry_indices:
            ports_by_isl = {}
            for p in active_served[fi]:
                ports_by_isl.setdefault(island_of[p], []).append(p)
            for isl, plist in ports_by_isl.items():
                if len(plist) >= 2:
                    island_has_intra_ferry[isl] = True
            served_islands = sorted(ports_by_isl)
            if len(served_islands) >= 2:
                inter_island_ferries.append(fi)
                for isl in served_islands:
                    island_ferry_lists[isl].append(fi)
                    for p in ports_by_isl[isl]:
                        island_inter_ports[isl].add(p)
                for i_idx in range(len(served_islands)):
                    isl_a = served_islands[i_idx]
                    for j_idx in range(i_idx + 1, len(served_islands)):
                        isl_b = served_islands[j_idx]
                        island_adj[isl_a].add(isl_b)
                        island_adj[isl_b].add(isl_a)

        self.inter_island_ferries = tuple(inter_island_ferries)
        self.island_ferries = tuple(tuple(fl) for fl in island_ferry_lists)
        self.active_inter_islands = tuple(
            isl for isl in range(num_islands) if self.island_ferries[isl]
        )
        self.island_has_intra_ferry = tuple(island_has_intra_ferry)
        self.max_island_sail_weight = tuple(
            max(
                (self.max_ferry_weight[fi] for fi in self.island_ferries[isl]),
                default=0,
            )
            for isl in range(num_islands)
        )
        self.max_island_ferry_truck_cap = tuple(
            max(
                (self.ferry_caps[fi] for fi in self.island_ferries[isl]),
                default=0,
            )
            for isl in range(num_islands)
        )
        self.has_inter_island_ferries = len(self.inter_island_ferries) > 0
        self.max_global_ferry_weight = max(
            (self.max_ferry_weight[fi] for fi in self.inter_island_ferries),
            default=0,
        )

        dist_to_inter_port = [_INF] * n
        for loc in range(n):
            isl = island_of[loc]
            if island_inter_ports[isl]:
                d_row = self.road_dist[loc]
                dist_to_inter_port[loc] = min(
                    d_row[p] for p in island_inter_ports[isl]
                )
        self.dist_to_inter_port = tuple(dist_to_inter_port)

        # Road bridges, compressed chains, bridge-block branches & private goal bridges
        self._precompute_road_bridges()

        num_active_roads = sum(len(self.roads[u]) for u in range(n)) // 2
        self.all_active_roads_are_bridges = (
            num_active_roads > 0 and len(self.road_bridges) == num_active_roads
        )
        self.is_pure_road_tree = (
            not self.active_ferry_indices and self.all_active_roads_are_bridges
        )

        isl_has_bridge = [False] * num_islands
        for u, _, _, _, _ in self.road_bridges:
            isl_has_bridge[island_of[u]] = True
        self.island_has_bridge = tuple(isl_has_bridge)
        self.non_bridge_islands_with_roads = tuple(
            isl
            for isl in range(num_islands)
            if not isl_has_bridge[isl]
            and any(
                len(self.roads[loc]) > 0
                for loc in range(n)
                if island_of[loc] == isl
            )
        )

        # Precompute road-only bridges for non-bridge islands served by a sole ferry
        # (used for the zero-extra-sail road-bridge trade-off bound).
        isl_road_bridges = [() for _ in range(num_islands)]
        for isl in self.non_bridge_islands_with_roads:
            sole_fi = self.island_sole_ferry[isl]
            if sole_fi == -1:
                continue
            fi_ports_on_isl = frozenset(
                p for p in active_served[sole_fi] if island_of[p] == isl
            )
            isl_nodes = [loc for loc in range(n) if island_of[loc] == isl]
            rb_list = []
            for u in isl_nodes:
                for v in self.roads[u]:
                    if u >= v:
                        continue
                    # BFS on road-only graph of isl without edge (u, v)
                    vis = [False] * n
                    vis[u] = True
                    q = deque([u])
                    while q:
                        x = q.popleft()
                        for y in self.roads[x]:
                            if (x == u and y == v) or (x == v and y == u):
                                continue
                            if not vis[y]:
                                vis[y] = True
                                q.append(y)
                    if not vis[v]:
                        side = [2] * n
                        has_p0 = False
                        has_p1 = False
                        for loc in isl_nodes:
                            if vis[loc]:
                                side[loc] = 0
                                if loc in fi_ports_on_isl:
                                    has_p0 = True
                            else:
                                side[loc] = 1
                                if loc in fi_ports_on_isl:
                                    has_p1 = True
                        rb_list.append((tuple(side), has_p0, has_p1))
            if rb_list:
                isl_road_bridges[isl] = tuple(rb_list)
        self.isl_road_bridges = tuple(isl_road_bridges)

        # min_sails[I][J]: BFS shortest path on the island-ferry graph
        min_sails = []
        for src in range(num_islands):
            dist = [_INF] * num_islands
            dist[src] = 0
            q = deque([src])
            while q:
                u = q.popleft()
                du = dist[u] + 1
                for v in island_adj[u]:
                    if dist[v] == _INF:
                        dist[v] = du
                        q.append(v)
            min_sails.append(tuple(dist))
        self.min_sails = tuple(min_sails)

        # Per-ferry served island masks, island-pair ferries & cut-ferry decompositions
        ferry_island_masks = [0] * self.num_ferries
        isl_pair_f = [[[] for _ in range(num_islands)] for _ in range(num_islands)]
        for fi in self.inter_island_ferries:
            mask = 0
            fi_isls_set = set()
            for p in active_served[fi]:
                isl_p = island_of[p]
                mask |= 1 << isl_p
                fi_isls_set.add(isl_p)
            ferry_island_masks[fi] = mask
            fi_isls_s = sorted(fi_isls_set)
            for a_i in range(len(fi_isls_s)):
                ia = fi_isls_s[a_i]
                for b_i in range(a_i + 1, len(fi_isls_s)):
                    ib = fi_isls_s[b_i]
                    isl_pair_f[ia][ib].append(fi)
                    isl_pair_f[ib][ia].append(fi)
        self.ferry_island_masks = tuple(ferry_island_masks)
        self.island_pair_ferries = tuple(
            tuple(tuple(fl) for fl in row) for row in isl_pair_f
        )

        cut_ferries = []
        for fi in self.inter_island_ferries:
            adj_wo = [set() for _ in range(num_islands)]
            for fj in self.inter_island_ferries:
                if fj == fi:
                    continue
                isls = sorted({island_of[p] for p in active_served[fj]})
                for i_idx in range(len(isls)):
                    ia = isls[i_idx]
                    for j_idx in range(i_idx + 1, len(isls)):
                        ib = isls[j_idx]
                        adj_wo[ia].add(ib)
                        adj_wo[ib].add(ia)
            seen = [False] * num_islands
            touched_masks = []
            fi_isls = sorted({island_of[p] for p in active_served[fi]})
            for start_isl in fi_isls:
                if seen[start_isl]:
                    continue
                mask = 0
                q = deque([start_isl])
                seen[start_isl] = True
                while q:
                    x = q.popleft()
                    mask |= 1 << x
                    for y in adj_wo[x]:
                        if not seen[y]:
                            seen[y] = True
                            q.append(y)
                touched_masks.append(mask)
            if len(touched_masks) >= 2:
                comp_mask_isl = 0
                for m in touched_masks:
                    comp_mask_isl |= m
                touched_in = tuple(
                    tuple(bool((m >> isl) & 1) for isl in range(num_islands))
                    for m in touched_masks
                )
                in_comp = tuple(
                    bool((comp_mask_isl >> isl) & 1) for isl in range(num_islands)
                )
                sole_rb_sides = []
                for h_idx, m in enumerate(touched_masks):
                    if m.bit_count() == 1:
                        isl_h = m.bit_length() - 1
                        if (
                            self.island_sole_ferry[isl_h] == fi
                            and not self.island_has_bridge[isl_h]
                            and self.isl_road_bridges[isl_h]
                        ):
                            sole_rb_sides.append((h_idx, isl_h))
                cut_ferries.append((fi, touched_in, in_comp, tuple(sole_rb_sides)))
        self.cut_ferries = tuple(cut_ferries)
        self.all_inter_ferries_are_cuts = (
            len(self.cut_ferries) == len(self.inter_island_ferries)
        )
        # Skip h_ring_cut when road bridges + cut-ferries already cover the graph
        # (always runs on cyclic/grid/non-bridge maps such as x1, x5, p2).
        self.skip_ring_cut = (
            len(self.road_bridges) + len(self.cut_ferries) >= num_active_roads
            and (len(self.road_bridges) > 0 or len(self.cut_ferries) > 0)
        )

        # Precompute concentric island-cut boundary ferries for each (center_isl, r)
        sail_cut_ferries = []
        for c_isl in range(num_islands):
            dc = self.min_sails[c_isl]
            max_r = max((d for d in dc if d < _INF), default=0)
            by_r = [None] * (max_r + 1)
            for r in range(1, max_r + 1):
                crossing = []
                for fi in self.inter_island_ferries:
                    fi_isls = [
                        isl
                        for isl in range(num_islands)
                        if (ferry_island_masks[fi] >> isl) & 1
                    ]
                    d_vals = [dc[isl] for isl in fi_isls]
                    if min(d_vals) < r <= max(d_vals) and max(d_vals) < _INF:
                        crossing.append(fi)
                max_w = max(
                    (self.max_ferry_weight[fi] for fi in crossing), default=0
                )
                by_r[r] = (tuple(crossing), max_w)
            sail_cut_ferries.append(tuple(by_r))
        self.sail_cut_ferries = tuple(sail_cut_ferries)

        # ------------------------------------------------------------------
        # 7. Initial dynamic state: (truck_locs, ferry_locs, pkg_locs)
        # ------------------------------------------------------------------
        self._h_cache = {}
        start_state = (init_truck_locs, init_ferry_locs, init_pkg_locs)
        search.Problem.__init__(self, start_state)

    def _precompute_road_bridges(self):
        """
        Find all road edges that are bridges in G_rf, build O(1) side-lookup
        tables, compress pure-corridor chains, build 2-edge-connected
        bridge-block branch groups (for global end-truck conservation and
        first-entry deadlock breaking), and identify pairwise-disjoint private
        goal bridges for the consolidation trade-off bound.
        """
        n = self.num_locations
        rf_adj = self._rf_adj
        comp_of = self.comp_of
        no_unload_loc = self.no_unload_loc

        road_edges = []
        for u in range(n):
            for v in self.roads[u]:
                if u < v:
                    road_edges.append((u, v))

        bridge_list = []
        bridge_masks = []
        bridge_set = set()
        edge_to_bidx = {}

        for u, v in road_edges:
            ferry_direct = False
            for fi in self.active_ferry_indices:
                sp = self.ferry_served_ports[fi]
                if u in sp and v in sp:
                    ferry_direct = True
                    break
            if ferry_direct:
                continue

            visited = [False] * n
            visited[u] = True
            q = deque([u])
            mask_u = 1 << u
            while q:
                x = q.popleft()
                for y in rf_adj[x]:
                    if (x == u and y == v) or (x == v and y == u):
                        continue
                    if not visited[y]:
                        visited[y] = True
                        mask_u |= 1 << y
                        q.append(y)
            if not visited[v]:
                c_id = comp_of[u]
                side = [2] * n
                mask_v = 0
                for loc in range(n):
                    if comp_of[loc] == c_id:
                        if visited[loc]:
                            side[loc] = 0
                        else:
                            side[loc] = 1
                            mask_v |= 1 << loc
                b_idx = len(bridge_list)
                bridge_list.append((u, v, tuple(side), c_id, visited.count(True)))
                bridge_masks.append((mask_u, mask_v))
                bridge_set.add((u, v))
                bridge_set.add((v, u))
                edge_to_bidx[(u, v)] = b_idx
                edge_to_bidx[(v, u)] = b_idx

        self.road_bridges = tuple(bridge_list)
        num_b = len(bridge_list)

        # Compress consecutive bridge edges along pure corridors into chains
        used_b = [False] * num_b
        bridge_chains = []
        edge_to_chain_info = {}
        for b_idx in range(num_b):
            if used_b[b_idx]:
                continue
            u, v, _, _, _ = bridge_list[b_idx]
            left_nodes = [u]
            cur, prev = u, v
            while no_unload_loc[cur] and len(self.roads[cur]) == 2:
                nxt = (
                    self.roads[cur][0]
                    if self.roads[cur][1] == prev
                    else self.roads[cur][1]
                )
                if (cur, nxt) not in edge_to_bidx or used_b[edge_to_bidx[(cur, nxt)]]:
                    break
                left_nodes.append(nxt)
                prev, cur = cur, nxt
            left_nodes.reverse()

            right_nodes = [v]
            cur, prev = v, u
            while no_unload_loc[cur] and len(self.roads[cur]) == 2:
                nxt = (
                    self.roads[cur][0]
                    if self.roads[cur][1] == prev
                    else self.roads[cur][1]
                )
                if (cur, nxt) not in edge_to_bidx or used_b[edge_to_bidx[(cur, nxt)]]:
                    break
                right_nodes.append(nxt)
                prev, cur = cur, nxt

            path = tuple(left_nodes + right_nodes)
            interior_mask = 0
            for v_int in path[1:-1]:
                interior_mask |= 1 << v_int

            chain_bidxs = []
            first_bidx = edge_to_bidx[(path[0], path[1])]
            first_u = bridge_list[first_bidx][0]
            ref_u_is_left = first_u == path[0]
            for i in range(len(path) - 1):
                a, b = path[i], path[i + 1]
                bi = edge_to_bidx[(a, b)]
                used_b[bi] = True
                bu = bridge_list[bi][0]
                same_as_ref = (bu == a) == ref_u_is_left
                chain_bidxs.append((bi, same_as_ref))

            chain_len = len(chain_bidxs)
            bridge_chains.append((path, interior_mask, tuple(chain_bidxs)))
            fwd_edges = tuple(
                (
                    edge_to_bidx[(path[i], path[i + 1])],
                    bool((bridge_masks[edge_to_bidx[(path[i], path[i + 1])]][0] >> path[i + 1]) & 1),
                )
                for i in range(chain_len)
            )
            rev_path = path[::-1]
            rev_edges = tuple(
                (
                    edge_to_bidx[(rev_path[i], rev_path[i + 1])],
                    bool((bridge_masks[edge_to_bidx[(rev_path[i], rev_path[i + 1])]][0] >> rev_path[i + 1]) & 1),
                )
                for i in range(chain_len)
            )
            edge_to_chain_info[(path[0], path[1])] = (chain_len, interior_mask, path, fwd_edges)
            edge_to_chain_info[(path[-1], path[-2])] = (chain_len, interior_mask, rev_path, rev_edges)

        self.bridge_chains = tuple(bridge_chains)

        # Build 2-edge-connected bridge-blocks (components of G_rf \ road_bridges)
        hub_groups_by_comp = [[] for _ in range(self.num_comps)]
        if num_b > 0:
            block_of = [-1] * n
            blocks = []
            for loc in range(n):
                if block_of[loc] == -1 and not self.dead_loc[loc]:
                    blk = []
                    q = deque([loc])
                    block_of[loc] = len(blocks)
                    while q:
                        x = q.popleft()
                        blk.append(x)
                        for y in rf_adj[x]:
                            if (x, y) in bridge_set:
                                continue
                            if block_of[y] == -1 and not self.dead_loc[y]:
                                block_of[y] = len(blocks)
                                q.append(y)
                    blocks.append(tuple(blk))

            for blk in blocks:
                if len(blk) == 1 and no_unload_loc[blk[0]]:
                    continue
                c_id = comp_of[blk[0]]
                blk_set = set(blk)
                incident = []
                for x in blk:
                    for y in self.roads[x]:
                        if (x, y) in bridge_set and y not in blk_set:
                            incident.append((x, y))
                if len(incident) < 2:
                    continue

                branches = []
                for hub_node, start in incident:
                    trunk_bidx = edge_to_bidx[(hub_node, start)]
                    mu, mv = bridge_masks[trunk_bidx]
                    trunk_far_is_u = bool((mu >> start) & 1)
                    branch_mask = mu if trunk_far_is_u else mv
                    (
                        trunk_len,
                        trunk_int_mask,
                        trunk_nodes,
                        trunk_edges,
                    ) = edge_to_chain_info[(hub_node, start)]
                    far_bidx, far_is_u = trunk_edges[-1]
                    far_side = bridge_list[far_bidx][2]
                    far_val = 0 if far_is_u else 1

                    branch_edges = []
                    for bi in range(num_b):
                        if bridge_list[bi][3] != c_id:
                            continue
                        b_mu, b_mv = bridge_masks[bi]
                        if (b_mu & branch_mask) == b_mu:
                            branch_edges.append((bi, True))
                        elif (b_mv & branch_mask) == b_mv:
                            branch_edges.append((bi, False))
                    if branch_edges:
                        branches.append(
                            (
                                trunk_bidx,
                                trunk_far_is_u,
                                trunk_len,
                                trunk_int_mask,
                                trunk_nodes,
                                far_bidx,
                                far_is_u,
                                far_side,
                                far_val,
                                tuple(branch_edges),
                            )
                        )
                if len(branches) >= 2:
                    hub_groups_by_comp[c_id].append(tuple(branches))

        self.hub_groups_by_comp = tuple(
            tuple(groups) for groups in hub_groups_by_comp
        )

        # Identify pairwise-disjoint private road bridges per goal location g
        goal_counts = {}
        for g in self.pkg_goals:
            goal_counts[g] = goal_counts.get(g, 0) + 1
        multi_goals = {g for g, cnt in goal_counts.items() if cnt >= 2}
        all_goals_set = set(self.pkg_goals)

        priv_by_goal = {}
        for b_idx in range(num_b):
            mu, mv = bridge_masks[b_idx]
            goals_u = [g for g in all_goals_set if (mu >> g) & 1]
            goals_v = [g for g in all_goals_set if (mv >> g) & 1]
            chosen = None
            if len(goals_u) == 1 and goals_u[0] in multi_goals:
                if (
                    len(goals_v) != 1
                    or goals_v[0] not in multi_goals
                    or bridge_list[b_idx][4] <= (n // 2)
                ):
                    chosen = (goals_u[0], 0)
            if chosen is None and len(goals_v) == 1 and goals_v[0] in multi_goals:
                chosen = (goals_v[0], 1)
            if chosen is not None:
                g_loc, g_side = chosen
                priv_by_goal.setdefault(g_loc, []).append((b_idx, g_side))

        private_goal_bridges = []
        for g_loc, edges in sorted(priv_by_goal.items()):
            g_pkgs = tuple(
                pi for pi in range(self.num_pkgs) if self.pkg_goals[pi] == g_loc
            )
            private_goal_bridges.append((g_loc, g_pkgs, tuple(edges)))
        self.private_goal_bridges = tuple(private_goal_bridges)

    def _precompute_dijkstra(self, ferry_weight):
        """All-pairs shortest paths via Dijkstra with given ferry edge weight."""
        n = self.num_locations
        adj_map = [{} for _ in range(n)]

        for u in range(n):
            for v in self.roads[u]:
                adj_map[u][v] = 1

        for fi in self.active_ferry_indices:
            served = self.ferry_served_ports[fi]
            for u in served:
                if self.dead_loc[u]:
                    continue
                row = adj_map[u]
                for v in served:
                    if u != v and not self.dead_loc[v]:
                        if v not in row or ferry_weight < row[v]:
                            row[v] = ferry_weight

        adj = [tuple(adj_map[u].items()) for u in range(n)]
        all_dist = []
        for src in range(n):
            dist = [_INF] * n
            dist[src] = 0
            pq = [(0, src)]
            while pq:
                d, u = heapq.heappop(pq)
                if d > dist[u]:
                    continue
                for v, w in adj[u]:
                    nd = d + w
                    if nd < dist[v]:
                        dist[v] = nd
                        heapq.heappush(pq, (nd, v))
            all_dist.append(tuple(dist))
        return tuple(all_dist)

    def _precompute_bfs_cut(self):
        """All-pairs unit-weight BFS where both roads and ferry hops cost 1."""
        n = self.num_locations
        adj_sets = [set(self.roads[u]) for u in range(n)]

        for fi in self.active_ferry_indices:
            served = self.ferry_served_ports[fi]
            for u in served:
                if self.dead_loc[u]:
                    continue
                row = adj_sets[u]
                for v in served:
                    if u != v and not self.dead_loc[v]:
                        row.add(v)

        adj = [tuple(adj_sets[u]) for u in range(n)]
        all_dist = []
        for src in range(n):
            dist = [_INF] * n
            dist[src] = 0
            q = deque([src])
            while q:
                u = q.popleft()
                du = dist[u] + 1
                for v in adj[u]:
                    if dist[v] == _INF:
                        dist[v] = du
                        q.append(v)
            all_dist.append(tuple(dist))
        return tuple(all_dist)

    def path_cost(self, c, state1, action, state2):
        """ Do not change this. Returns the cost of reaching state2 from state1 via action,
        given cost c to reach state1: SAIL costs 3, every other action costs 1"""
        return c + (3 if action.startswith("SAIL") else 1)

    def successor(self, state):
        """Generate legal (action_str, next_state) pairs with optimality-preserving pruning."""
        truck_locs, ferry_locs, pkg_locs = state

        num_trucks = self.num_trucks
        num_ferries = self.num_ferries
        num_pkgs = self.num_pkgs
        roads = self.roads
        is_port = self.is_port
        truck_caps = self.truck_caps
        ferry_caps = self.ferry_caps
        ferry_active_targets = self.ferry_active_targets
        pkg_weights = self.pkg_weights
        pkg_goals = self.pkg_goals
        no_unload_loc = self.no_unload_loc
        prev_sym_truck = self.prev_sym_truck
        prev_sym_ferry = self.prev_sym_ferry
        prev_sym_pkg = self.prev_sym_pkg
        load_strs = self._load_strs
        unload_strs = self._unload_strs
        board_strs = self._board_strs
        disembark_strs = self._disembark_strs
        drive_strs = self._drive_strs
        sail_strs = self._sail_strs

        # Component decomposition: solve independent disconnected components in order
        if self.use_comp_decomp:
            active_comp = -1
            for c in range(self.num_comps):
                for pi in self.comp_pkgs[c]:
                    if pkg_locs[pi] != pkg_goals[pi]:
                        active_comp = c
                        break
                if active_comp != -1:
                    break
            if active_comp == -1:
                return []
            truck_iter = self.comp_trucks[active_comp]
            ferry_iter = self.comp_ferries[active_comp]
            pkg_iter = self.comp_pkgs[active_comp]
        else:
            truck_iter = range(num_trucks)
            ferry_iter = self.active_ferry_indices
            pkg_iter = range(num_pkgs)

        # Single O(P) pass: forced canonical UNLOAD at goal + truck loads/counts
        truck_loads = [0] * num_trucks
        truck_pkg_counts = [0] * num_trucks
        for pi in pkg_iter:
            pl = pkg_locs[pi]
            if pl < 0:
                ti = -pl - 1
                tl = truck_locs[ti]
                if tl >= 0 and tl == pkg_goals[pi]:
                    new_p = list(pkg_locs)
                    new_p[pi] = tl
                    return [
                        (
                            unload_strs[pi][ti],
                            (truck_locs, ferry_locs, tuple(new_p)),
                        )
                    ]
                truck_loads[ti] += pkg_weights[pi]
                truck_pkg_counts[ti] += 1

        # Ample-set Reduction A (Mid-Corridor Commutativity):
        # A truck at a pure corridor interior (degree 2, non-port, non-relevant,
        # no ground packages) can only DRIVE, and its DRIVE commutes with all
        # actions of other trucks and ferries.
        for ti in truck_iter:
            tl = truck_locs[ti]
            if tl >= 0 and no_unload_loc[tl] and tl not in pkg_locs:
                d_map = drive_strs[ti]
                res = []
                for target_loc in roads[tl]:
                    new_t = list(truck_locs)
                    new_t[ti] = target_loc
                    res.append(
                        (
                            d_map[(tl, target_loc)],
                            (tuple(new_t), ferry_locs, pkg_locs),
                        )
                    )
                return res

        # Ferry occupancy & Ample-set Reduction B (Full Ferry Commutativity)
        ferry_counts = [0] * num_ferries
        any_aboard = False
        for ti in truck_iter:
            tl = truck_locs[ti]
            if tl < 0:
                ferry_counts[-tl - 1] += 1
                any_aboard = True

        if any_aboard:
            for fi in ferry_iter:
                if ferry_counts[fi] == ferry_caps[fi] and ferry_counts[fi] > 0:
                    cur_port = ferry_locs[fi]
                    on_fi = -(fi + 1)
                    res = []
                    for ti in truck_iter:
                        if truck_locs[ti] != on_fi:
                            continue
                        if truck_pkg_counts[ti] == 0:
                            sym_skip = False
                            for ti1 in prev_sym_truck[ti]:
                                if (
                                    truck_locs[ti1] == on_fi
                                    and truck_pkg_counts[ti1] == 0
                                ):
                                    sym_skip = True
                                    break
                            if sym_skip:
                                continue
                        new_t = list(truck_locs)
                        new_t[ti] = cur_port
                        res.append(
                            (
                                disembark_strs[ti][fi],
                                (tuple(new_t), ferry_locs, pkg_locs),
                            )
                        )
                    s_map = sail_strs[fi]
                    for target_port in ferry_active_targets[fi]:
                        if target_port != cur_port:
                            new_f = list(ferry_locs)
                            new_f[fi] = target_port
                            res.append(
                                (
                                    s_map[(cur_port, target_port)],
                                    (truck_locs, tuple(new_f), pkg_locs),
                                )
                            )
                    return res

        successors = []

        # 1. Truck actions: DISEMBARK, DRIVE, BOARD, UNLOAD, LOAD
        for ti in truck_iter:
            tl = truck_locs[ti]

            # Symmetry breaking for empty statically identical trucks at same location
            if truck_pkg_counts[ti] == 0:
                sym_skip = False
                for ti1 in prev_sym_truck[ti]:
                    if truck_locs[ti1] == tl and truck_pkg_counts[ti1] == 0:
                        sym_skip = True
                        break
                if sym_skip:
                    continue

            # Case A: truck is aboard a ferry -> can only DISEMBARK
            if tl < 0:
                fi = -tl - 1
                new_t = list(truck_locs)
                new_t[ti] = ferry_locs[fi]
                successors.append(
                    (disembark_strs[ti][fi], (tuple(new_t), ferry_locs, pkg_locs))
                )
                continue

            # Case B: truck is standing on the ground at location tl
            d_map = drive_strs[ti]

            # DRIVE along active adjacent roads
            for target_loc in roads[tl]:
                new_t = list(truck_locs)
                new_t[ti] = target_loc
                successors.append(
                    (
                        d_map[(tl, target_loc)],
                        (tuple(new_t), ferry_locs, pkg_locs),
                    )
                )

            # BOARD a docked active ferry with available capacity
            if is_port[tl]:
                for fi in ferry_iter:
                    if ferry_locs[fi] == tl and ferry_counts[fi] < ferry_caps[fi]:
                        if ferry_counts[fi] == 0:
                            sym_f = False
                            for fi1 in prev_sym_ferry[fi]:
                                if ferry_locs[fi1] == tl and ferry_counts[fi1] == 0:
                                    sym_f = True
                                    break
                            if sym_f:
                                continue
                        new_t = list(truck_locs)
                        new_t[ti] = -(fi + 1)
                        successors.append(
                            (
                                board_strs[ti][fi],
                                (tuple(new_t), ferry_locs, pkg_locs),
                            )
                        )

            # UNLOAD packages inside this truck / LOAD packages at this location
            in_this_truck = -(ti + 1)
            remaining_cap = truck_caps[ti] - truck_loads[ti]
            allow_unload_here = not no_unload_loc[tl]

            for pi in pkg_iter:
                pl = pkg_locs[pi]
                if pl == in_this_truck:
                    if not allow_unload_here:
                        continue
                    sym_p = False
                    for pi1 in prev_sym_pkg[pi]:
                        if pkg_locs[pi1] == in_this_truck:
                            sym_p = True
                            break
                    if sym_p:
                        continue
                    new_p = list(pkg_locs)
                    new_p[pi] = tl
                    successors.append(
                        (
                            unload_strs[pi][ti],
                            (truck_locs, ferry_locs, tuple(new_p)),
                        )
                    )
                elif pl == tl:
                    if tl != pkg_goals[pi] and pkg_weights[pi] <= remaining_cap:
                        sym_p = False
                        for pi1 in prev_sym_pkg[pi]:
                            if pkg_locs[pi1] == tl:
                                sym_p = True
                                break
                        if sym_p:
                            continue
                        new_p = list(pkg_locs)
                        new_p[pi] = in_this_truck
                        successors.append(
                            (
                                load_strs[pi][ti],
                                (truck_locs, ferry_locs, tuple(new_p)),
                            )
                        )

        # 2. Ferry actions: SAIL (active ferries only)
        for fi in ferry_iter:
            cur_port = ferry_locs[fi]
            is_empty = ferry_counts[fi] == 0

            if is_empty:
                sym_f = False
                for fi1 in prev_sym_ferry[fi]:
                    if ferry_locs[fi1] == cur_port and ferry_counts[fi1] == 0:
                        sym_f = True
                        break
                if sym_f:
                    continue

            s_map = sail_strs[fi]
            for target_port in ferry_active_targets[fi]:
                if target_port == cur_port:
                    continue
                if is_empty and target_port not in truck_locs:
                    continue
                new_f = list(ferry_locs)
                new_f[fi] = target_port
                successors.append(
                    (
                        s_map[(cur_port, target_port)],
                        (truck_locs, tuple(new_f), pkg_locs),
                    )
                )

        return successors

    def goal_test(self, state):
        """Return True iff every package is on the ground at its goal location."""
        return state[2] == self.pkg_goals

    def h_astar(self, node):
        """
        100% admissible heuristic decomposing all actions into pairwise disjoint sets:
          - A_LU    = {LOAD, UNLOAD}                       (cost 1 each)
          - A_truck = A_drive U A_bd                       (cost 1 each)
                      where A_drive = {DRIVE},
                            A_bd    = {BOARD} U {DISEMBARK}
          - A_sail  = {SAIL}                               (cost 3 each)

        Final combination:
          h_truck_total = max(h_mst, h_ring_cut, h_ton_km, h_drive + h_bd)
          h_std         = h_load_unload + max(h_single, h_truck_total + h_sail)
          h_consol      = h_load_unload + h_road_bridge_base + non_bridge_drive
                          + h_bd + h_sail + h_consol_extra
          h_port_trade  = h_load_unload + h_road_bridge + non_bridge_drive
                          + h_bd + h_sail + h_empty_port_extra
          return max(h_std, h_consol, h_port_trade)
        """
        state = node.state
        h_cache = self._h_cache
        cached = h_cache.get(state)
        if cached is not None:
            return cached

        truck_locs, ferry_locs, pkg_locs = state
        pkg_goals = self.pkg_goals

        if pkg_locs == pkg_goals:
            return 0

        num_trucks = self.num_trucks
        num_pkgs = self.num_pkgs
        pkg_weights = self.pkg_weights
        dist_full = self.dist_full
        dist_no_sail = self.dist_no_sail
        ferry_full_dist = self.ferry_full_dist
        ferry_disembark_no_sail = self.ferry_disembark_no_sail
        capable_trucks = self.capable_trucks

        undelivered = [
            pi for pi in range(num_pkgs) if pkg_locs[pi] != pkg_goals[pi]
        ]

        # =====================================================================
        # SECTION 1: h_load_unload (Lower bound on A_LU ONLY)
        # =====================================================================
        h_load_unload = 0
        w_gcd = 0
        gcd = math.gcd
        for pi in undelivered:
            w_gcd = gcd(w_gcd, pkg_weights[pi])
            if pkg_locs[pi] < 0:
                h_load_unload += 1
            else:
                h_load_unload += 2

        eff_truck_caps = self.eff_truck_caps
        if w_gcd > self.init_w_gcd:
            # Remaining package weights share a larger GCD than initially:
            # cache tightened truck and ferry effective capacities per w_gcd.
            gcd_entry = self._gcd_cap_cache.get(w_gcd)
            if gcd_entry is None:
                eff_c = tuple((ec // w_gcd) * w_gcd for ec in eff_truck_caps)
                max_ec = max(eff_c) if eff_c else 0
                eff_desc = sorted(eff_c, reverse=True)
                ferry_caps = self.ferry_caps
                mfw = tuple(
                    sum(eff_desc[: min(ferry_caps[fi], num_trucks)])
                    for fi in range(self.num_ferries)
                )
                misw = tuple(
                    max(
                        (mfw[fi] for fi in self.island_ferries[isl]),
                        default=0,
                    )
                    for isl in range(self.num_islands)
                )
                mgfw = max(
                    (mfw[fi] for fi in self.inter_island_ferries), default=0
                )
                gcd_entry = (eff_c, max_ec, mfw, misw, mgfw)
                self._gcd_cap_cache[w_gcd] = gcd_entry
            eff_truck_caps, max_eff_cap, max_ferry_weight_dyn, max_island_sail_weight_dyn, max_gfw_dyn = gcd_entry
        else:
            max_eff_cap = self.max_eff_truck_cap
            max_ferry_weight_dyn = self.max_ferry_weight
            max_island_sail_weight_dyn = self.max_island_sail_weight
            max_gfw_dyn = self.max_global_ferry_weight

        if num_trucks == 0 or max_eff_cap <= 0:
            return h_load_unload

        # Safety guard for external unpruned admissibility checkers:
        # Our own successor() never enters dead_loc or inactive ferries, so this
        # fallback never triggers during A* search, yet guarantees 100% admissibility
        # even if an external test evaluates h_astar on a state inside a dead-end.
        if self.has_dead_locs or self.has_inactive_ferries:
            dead_loc = self.dead_loc
            active_ferry = self.active_ferry
            in_dead = False
            for tl in truck_locs:
                if tl >= 0:
                    if dead_loc[tl]:
                        in_dead = True
                        break
                elif not active_ferry[-tl - 1]:
                    in_dead = True
                    break
            if not in_dead:
                for pi in undelivered:
                    pl = pkg_locs[pi]
                    if pl >= 0 and dead_loc[pl]:
                        in_dead = True
                        break
            if in_dead:
                return h_load_unload

        cap_m1 = max_eff_cap - 1
        half_eff_cap = max_eff_cap >> 1
        island_of = self.island_of
        pkg_goal_islands = self.pkg_goal_islands

        # Single O(T + P) pass to pre-extract truck and undelivered package metadata
        # (eliminates repeated per-section indexing and list.append overhead).
        truck_rep_loc = [0] * num_trucks
        truck_on_ferry = [-1] * num_trucks
        truck_eff_island = [0] * num_trucks
        occ_mask = 0
        for ti in range(num_trucks):
            tl = truck_locs[ti]
            if tl >= 0:
                truck_rep_loc[ti] = tl
                truck_eff_island[ti] = island_of[tl]
                occ_mask |= 1 << tl
            else:
                fi = -tl - 1
                fp = ferry_locs[fi]
                truck_on_ferry[ti] = fi
                truck_rep_loc[ti] = fp
                truck_eff_island[ti] = island_of[fp]
                occ_mask |= 1 << fp

        # Each entry in pkg_info: (pi, pl, gl, cur_loc, is_gnd, w, p_isl, g_isl, on_f)
        pkg_info = []
        num_in_trucks = 0
        for pi in undelivered:
            pl = pkg_locs[pi]
            gl = pkg_goals[pi]
            w = pkg_weights[pi]
            g_isl = pkg_goal_islands[pi]
            if pl >= 0:
                occ_mask |= 1 << pl
                pkg_info.append((pi, pl, gl, pl, True, w, island_of[pl], g_isl, -1))
            else:
                ti = -pl - 1
                num_in_trucks += 1
                pkg_info.append(
                    (
                        pi,
                        pl,
                        gl,
                        truck_rep_loc[ti],
                        False,
                        w,
                        truck_eff_island[ti],
                        g_isl,
                        truck_on_ferry[ti],
                    )
                )

        # =====================================================================
        # SECTION 2: h_single (Lower bound on A_truck U A_sail)
        # =====================================================================
        h_single = 0
        for pi, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
            if is_gnd:
                d_deliver = dist_full[pl][gl]
                if d_deliver >= _INF:
                    continue
                min_pickup = _INF
                for ti in capable_trucks[pi]:
                    tl = truck_locs[ti]
                    if tl >= 0:
                        d_pick = dist_full[tl][pl]
                    else:
                        d_pick = ferry_full_dist[-tl - 1][ferry_locs[-tl - 1]][pl]
                    if d_pick < min_pickup:
                        min_pickup = d_pick
                if min_pickup < _INF:
                    pkg_cost = min_pickup + d_deliver
                    if pkg_cost > h_single:
                        h_single = pkg_cost
            else:
                tl = truck_locs[-pl - 1]
                if tl >= 0:
                    pkg_cost = dist_full[tl][gl]
                else:
                    pkg_cost = ferry_full_dist[-tl - 1][ferry_locs[-tl - 1]][gl]
                if pkg_cost < _INF and pkg_cost > h_single:
                    h_single = pkg_cost

        # =====================================================================
        # SECTION 3: h_mst (Lower bound on A_truck ONLY via Prim's MST)
        # =====================================================================
        # On a pure road tree with zero active ferries, h_road_bridge provably
        # dominates both h_mst and h_ton_km, so we skip redundant MST/ton-km work.
        is_pure_road_tree = self.is_pure_road_tree
        req_nodes = None
        h_mst = 0
        if not is_pure_road_tree:
            req_set = set()
            for _, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
                if is_gnd:
                    req_set.add(pl)
                req_set.add(gl)

            req_nodes = list(req_set)
            num_req = len(req_nodes)
            if num_req > 0:
                min_edge = [_INF] * num_req
                for ti in range(num_trucks):
                    tl = truck_locs[ti]
                    d_row = (
                        dist_no_sail[tl]
                        if tl >= 0
                        else ferry_disembark_no_sail[-tl - 1]
                    )
                    for idx in range(num_req):
                        d = d_row[req_nodes[idx]]
                        if d < min_edge[idx]:
                            min_edge[idx] = d

                in_tree = [False] * num_req
                for _ in range(num_req):
                    best_idx = -1
                    best_w = _INF
                    for idx in range(num_req):
                        if not in_tree[idx] and min_edge[idx] < best_w:
                            best_w = min_edge[idx]
                            best_idx = idx
                    if best_idx == -1:
                        break
                    in_tree[best_idx] = True
                    h_mst += best_w
                    u_row = dist_no_sail[req_nodes[best_idx]]
                    for idx in range(num_req):
                        if not in_tree[idx]:
                            d = u_row[req_nodes[idx]]
                            if d < min_edge[idx]:
                                min_edge[idx] = d

        # =====================================================================
        # SECTION 4: h_ring_cut (Lower bound on DRIVE + DISEMBARK subset of A_truck)
        # =====================================================================
        # Evaluated on all maps with cyclic/non-bridge topology; skipped when
        # exact bridge & cut-ferry bounds already cover the graph.
        h_ring_cut = 0
        if not self.skip_ring_cut:
            dist_cut = self.dist_cut
            ferry_min_cut = self.ferry_min_cut
            ferry_max_cut = self.ferry_max_cut

            for u in req_nodes:
                du = dist_cut[u]
                d_max = 0
                for v in req_nodes:
                    dv = du[v]
                    if dv < _INF and dv > d_max:
                        d_max = dv
                if d_max == 0:
                    continue

                f_min_u = ferry_min_cut[u]
                f_max_u = ferry_max_cut[u]

                size = d_max + 2
                diff_w_out = [0] * size
                diff_w_in = [0] * size
                diff_m_in = [0] * size
                diff_m_out = [0] * size

                for _, pl, gl, _, is_gnd, w, _, _, on_f in pkg_info:
                    dg = du[gl]
                    if dg >= _INF:
                        continue
                    if is_gnd:
                        dp = du[pl]
                        if dp >= _INF:
                            continue
                        if dp < dg:
                            lo = dp + 1
                            if lo <= d_max:
                                hi = dg if dg < d_max else d_max
                                diff_w_out[lo] += w
                                diff_w_out[hi + 1] -= w
                        elif dg < dp:
                            lo = dg + 1
                            if lo <= d_max:
                                hi = dp if dp < d_max else d_max
                                diff_w_in[lo] += w
                                diff_w_in[hi + 1] -= w
                    elif on_f < 0:
                        dp = du[truck_locs[-pl - 1]]
                        if dp >= _INF:
                            continue
                        if dp < dg:
                            lo = dp + 1
                            if lo <= d_max:
                                hi = dg if dg < d_max else d_max
                                diff_w_out[lo] += w
                                diff_w_out[hi + 1] -= w
                        elif dg < dp:
                            lo = dg + 1
                            if lo <= d_max:
                                hi = dp if dp < d_max else d_max
                                diff_w_in[lo] += w
                                diff_w_in[hi + 1] -= w
                    else:
                        f_min = f_min_u[on_f]
                        f_max = f_max_u[on_f]
                        if f_min >= _INF:
                            continue
                        if f_max < dg:
                            lo = f_max + 1
                            if lo <= d_max:
                                hi = dg if dg < d_max else d_max
                                diff_w_out[lo] += w
                                diff_w_out[hi + 1] -= w
                        elif dg < f_min:
                            lo = dg + 1
                            if lo <= d_max:
                                hi = f_min if f_min < d_max else d_max
                                diff_w_in[lo] += w
                                diff_w_in[hi + 1] -= w

                for ti in range(num_trucks):
                    tl = truck_locs[ti]
                    if tl >= 0:
                        dt = du[tl]
                        if dt >= _INF:
                            continue
                        if dt < d_max:
                            diff_m_in[dt + 1] += 1
                        if dt >= 1:
                            hi = dt if dt < d_max else d_max
                            diff_m_out[1] += 1
                            diff_m_out[hi + 1] -= 1
                    else:
                        fi = -tl - 1
                        f_min = f_min_u[fi]
                        f_max = f_max_u[fi]
                        if f_min >= _INF:
                            continue
                        if f_min < d_max:
                            diff_m_in[f_min + 1] += 1
                        if f_max >= 1:
                            hi = f_max if f_max < d_max else d_max
                            diff_m_out[1] += 1
                            diff_m_out[hi + 1] -= 1

                w_out = w_in = m_in = m_out = 0
                cut_sum = 0
                for r in range(1, d_max + 1):
                    w_out += diff_w_out[r]
                    w_in += diff_w_in[r]
                    m_in += diff_m_in[r]
                    m_out += diff_m_out[r]
                    if w_out == 0 and w_in == 0:
                        continue
                    k_out = (w_out + cap_m1) // max_eff_cap if w_out > 0 else 0
                    k_in = (w_in + cap_m1) // max_eff_cap if w_in > 0 else 0
                    req_out = k_out if k_out >= k_in - m_out else k_in - m_out
                    req_in = k_in if k_in >= k_out - m_in else k_out - m_in
                    cut_sum += req_out + req_in

                if cut_sum > h_ring_cut:
                    h_ring_cut = cut_sum

        # =====================================================================
        # SECTION 5: h_ton_km (Lower bound on A_truck ONLY)
        #            + h_drive + h_bd (Disjoint A_drive + A_bd lower bound)
        # =====================================================================
        h_ton_km = 0
        if not is_pure_road_tree:
            total_work = 0
            for _, pl, gl, cur_loc, is_gnd, w, _, _, on_f in pkg_info:
                if is_gnd or on_f < 0:
                    d = dist_no_sail[cur_loc][gl]
                else:
                    d = ferry_disembark_no_sail[on_f][gl]
                if d < _INF:
                    total_work += w * d
            if total_work > 0:
                h_ton_km = (total_work + cap_m1) // max_eff_cap

        # 5a. h_road_bridge: sum over bridge road edges of G_rf (A_drive ONLY)
        road_bridges = self.road_bridges
        h_road_bridge_base = 0
        h_hub_extra = 0
        h_consol_extra = 0

        if road_bridges:
            num_b = len(road_bridges)
            b_req_uv = [0] * num_b
            b_req_vu = [0] * num_b
            b_m_u = [0] * num_b
            b_m_v = [0] * num_b

            comp_of = self.comp_of
            num_comps = self.num_comps
            comp_max_cap = [0] * num_comps
            comp_truck_cnt = [0] * num_comps
            for ti in range(num_trucks):
                loc = truck_rep_loc[ti]
                c = comp_of[loc]
                comp_truck_cnt[c] += 1
                ec = eff_truck_caps[ti]
                if ec > comp_max_cap[c]:
                    comp_max_cap[c] = ec

            # Evaluate compressed pure-corridor bridge chains using O(1) bitmask + side tuples
            for path_nodes, interior_mask, chain_bidxs in self.bridge_chains:
                any_in_int = bool(occ_mask & interior_mask)
                num_ce = len(chain_bidxs)
                r_ref_uv = r_ref_vu = m_ref_u = m_ref_v = 0
                for idx_c in range(num_ce):
                    bi, same_dir = chain_bidxs[idx_c]
                    if idx_c == 0 or (any_in_int and ((occ_mask >> path_nodes[idx_c]) & 1)):
                        _, _, side, c_id, _ = road_bridges[bi]
                        c_cap = comp_max_cap[c_id]
                        m_u = m_v = cap_sum_u = cap_sum_v = 0
                        max_cap_u = max_cap_v = -1
                        for ti in range(num_trucks):
                            s_t = side[truck_rep_loc[ti]]
                            if s_t == 0:
                                tcap = eff_truck_caps[ti]
                                m_u += 1
                                cap_sum_u += tcap
                                if tcap > max_cap_u:
                                    max_cap_u = tcap
                            elif s_t == 1:
                                tcap = eff_truck_caps[ti]
                                m_v += 1
                                cap_sum_v += tcap
                                if tcap > max_cap_v:
                                    max_cap_v = tcap

                        if c_cap <= 0:
                            r_cur_uv = 0
                            r_cur_vu = 0
                        else:
                            c_cap_m1 = c_cap - 1
                            c_half = c_cap >> 1
                            w_uv = w_vu = h_uv = h_vu = 0
                            need_v_to_u = False
                            need_u_to_v = False
                            for _, _, gl, cur_loc, is_gnd, w, _, _, _ in pkg_info:
                                s_p = side[cur_loc]
                                if s_p == 0:
                                    if side[gl] == 1:
                                        w_uv += w
                                        if w > c_half:
                                            h_uv += 1
                                    if is_gnd and w > max_cap_u:
                                        need_v_to_u = True
                                elif s_p == 1:
                                    if side[gl] == 0:
                                        w_vu += w
                                        if w > c_half:
                                            h_vu += 1
                                    if is_gnd and w > max_cap_v:
                                        need_u_to_v = True

                            if w_uv == 0 and w_vu == 0 and not need_v_to_u and not need_u_to_v:
                                r_cur_uv = 0
                                r_cur_vu = 0
                            else:
                                k_uv = (w_uv + c_cap_m1) // c_cap if w_uv > 0 else 0
                                if h_uv > k_uv:
                                    k_uv = h_uv
                                if need_u_to_v and k_uv < 1:
                                    k_uv = 1

                                k_vu = (w_vu + c_cap_m1) // c_cap if w_vu > 0 else 0
                                if h_vu > k_vu:
                                    k_vu = h_vu
                                if need_v_to_u and k_vu < 1:
                                    k_vu = 1

                                r_cur_uv = k_uv
                                if k_vu - m_v > r_cur_uv:
                                    r_cur_uv = k_vu - m_v
                                if w_vu > cap_sum_v:
                                    cw = (w_vu - cap_sum_v + c_cap_m1) // c_cap
                                    if cw > r_cur_uv:
                                        r_cur_uv = cw

                                r_cur_vu = k_vu
                                if k_uv - m_u > r_cur_vu:
                                    r_cur_vu = k_uv - m_u
                                if w_uv > cap_sum_u:
                                    cw = (w_uv - cap_sum_u + c_cap_m1) // c_cap
                                    if cw > r_cur_vu:
                                        r_cur_vu = cw

                        if not any_in_int:
                            if r_cur_uv or r_cur_vu:
                                h_road_bridge_base += (r_cur_uv + r_cur_vu) * num_ce
                            for bi2, sd2 in chain_bidxs:
                                if sd2:
                                    b_req_uv[bi2] = r_cur_uv
                                    b_req_vu[bi2] = r_cur_vu
                                    b_m_u[bi2] = m_u
                                    b_m_v[bi2] = m_v
                                else:
                                    b_req_uv[bi2] = r_cur_vu
                                    b_req_vu[bi2] = r_cur_uv
                                    b_m_u[bi2] = m_v
                                    b_m_v[bi2] = m_u
                            break

                        if same_dir:
                            r_ref_uv, r_ref_vu = r_cur_uv, r_cur_vu
                            m_ref_u, m_ref_v = m_u, m_v
                        else:
                            r_ref_uv, r_ref_vu = r_cur_vu, r_cur_uv
                            m_ref_u, m_ref_v = m_v, m_u

                    if same_dir:
                        b_req_uv[bi] = r_ref_uv
                        b_req_vu[bi] = r_ref_vu
                        b_m_u[bi] = m_ref_u
                        b_m_v[bi] = m_ref_v
                    else:
                        b_req_uv[bi] = r_ref_vu
                        b_req_vu[bi] = r_ref_uv
                        b_m_u[bi] = m_ref_v
                        b_m_v[bi] = m_ref_u
                    h_road_bridge_base += r_ref_uv + r_ref_vu

            # 2-edge-connected bridge-block end-truck conservation (OUT direction)
            # + empty-tail first-entry deadlock min-weight FVS (IN direction).
            for c_id in range(num_comps):
                hub_groups = self.hub_groups_by_comp[c_id]
                if not hub_groups:
                    continue
                mc = comp_truck_cnt[c_id]
                best_extra = 0
                for branches in hub_groups:
                    total_s = 0
                    unit_costs = []
                    dl_cands = []
                    for (
                        trunk_bidx,
                        trunk_far_is_u,
                        trunk_len,
                        trunk_int_mask,
                        trunk_nodes,
                        far_bidx,
                        far_is_u,
                        far_side,
                        far_val,
                        branch_edges,
                    ) in branches:
                        if trunk_far_is_u:
                            m_br = b_m_u[trunk_bidx]
                            t_in = b_req_vu[trunk_bidx]
                            t_out = b_req_uv[trunk_bidx]
                        else:
                            m_br = b_m_v[trunk_bidx]
                            t_in = b_req_uv[trunk_bidx]
                            t_out = b_req_vu[trunk_bidx]

                        int_occ = bool(occ_mask & trunk_int_mask)
                        s_i = m_br + t_in - t_out
                        if s_i > 0:
                            total_s += s_i
                            if m_br == 0 and s_i == 1:
                                deficit = 0
                                for bi, far_is_u_e in branch_edges:
                                    diff = (
                                        b_req_vu[bi] - b_req_uv[bi]
                                        if far_is_u_e
                                        else b_req_uv[bi] - b_req_vu[bi]
                                    )
                                    if diff > 0:
                                        deficit += diff
                                cost_u = deficit if deficit > 0 else 1
                            else:
                                cost_u = 1 if int_occ else trunk_len
                            unit_costs.append((cost_u, s_i))

                        # Empty-tail deadlock check: even if a truck is partway down
                        # the trunk corridor, the unoccupied tail behind it still
                        # enforces strict entry-order dependency on its tail edges.
                        if far_is_u:
                            m_far = b_m_u[far_bidx]
                            t_in_far = b_req_vu[far_bidx]
                            t_out_far = b_req_uv[far_bidx]
                        else:
                            m_far = b_m_v[far_bidx]
                            t_in_far = b_req_uv[far_bidx]
                            t_out_far = b_req_vu[far_bidx]

                        if m_far == 0 and t_in_far == 1 and t_out_far == 1:
                            if not int_occ:
                                tail_len = trunk_len
                            else:
                                j_occ = trunk_len - 1
                                while j_occ > 0 and not ((occ_mask >> trunk_nodes[j_occ]) & 1):
                                    j_occ -= 1
                                tail_len = trunk_len - j_occ
                            dl_cands.append((far_side, far_val, tail_len))

                    group_extra = 0
                    excess = total_s - mc
                    if excess > 0:
                        unit_costs.sort()
                        rem = excess
                        for cost_u, cnt in unit_costs:
                            take = cnt if cnt < rem else rem
                            group_extra += cost_u * take
                            rem -= take
                            if rem == 0:
                                break

                    # Min-weight Feedback Vertex Set on empty-tail dependency graph
                    num_dl = len(dl_cands)
                    if num_dl >= 2:
                        alive_mask = 0
                        in_mask = [0] * num_dl
                        out_mask = [0] * num_dl
                        for _, _, gl, cur_loc, is_gnd, _, _, _, _ in pkg_info:
                            if not is_gnd:
                                continue
                            src_i = -1
                            dst_i = -1
                            for di in range(num_dl):
                                f_side, f_val, _ = dl_cands[di]
                                if f_side[cur_loc] == f_val:
                                    src_i = di
                                if f_side[gl] == f_val:
                                    dst_i = di
                            if src_i != -1 and dst_i != -1 and src_i != dst_i:
                                sb = 1 << src_i
                                db = 1 << dst_i
                                out_mask[src_i] |= db
                                in_mask[dst_i] |= sb
                                alive_mask |= sb | db

                        # Iteratively prune vertices with in-deg 0 or out-deg 0
                        while alive_mask:
                            new_mask = alive_mask
                            rem_m = alive_mask
                            while rem_m:
                                lsb = rem_m & -rem_m
                                di = lsb.bit_length() - 1
                                rem_m ^= lsb
                                if not (in_mask[di] & alive_mask) or not (out_mask[di] & alive_mask):
                                    new_mask ^= lsb
                            if new_mask == alive_mask:
                                break
                            alive_mask = new_mask

                        if alive_mask:
                            w_dl = [c[2] for c in dl_cands]

                            def _find_short_cycle(msk):
                                # Fast path: find any 2-cycle u <-> v
                                rm = msk
                                while rm:
                                    lsb = rm & -rm
                                    u = lsb.bit_length() - 1
                                    rm ^= lsb
                                    two = out_mask[u] & in_mask[u] & msk
                                    if two:
                                        return lsb | (two & -two)
                                # General BFS for a short directed cycle inside msk
                                best_cyc = 0
                                best_len = _INF
                                rm = msk
                                while rm:
                                    lsb = rm & -rm
                                    start = lsb.bit_length() - 1
                                    rm ^= lsb
                                    q_bfs = [(start, lsb, 1)]
                                    seen_bfs = lsb
                                    qi = 0
                                    while qi < len(q_bfs):
                                        cur_v, path_m, plen = q_bfs[qi]
                                        qi += 1
                                        if plen >= best_len:
                                            break
                                        nbrs = out_mask[cur_v] & msk
                                        if nbrs & lsb:
                                            best_len = plen
                                            best_cyc = path_m
                                            break
                                        unseen = nbrs & ~seen_bfs
                                        while unseen:
                                            nb = unseen & -unseen
                                            unseen ^= nb
                                            seen_bfs |= nb
                                            q_bfs.append((nb.bit_length() - 1, path_m | nb, plen + 1))
                                return best_cyc

                            if alive_mask.bit_count() <= 10:
                                fvs_memo = {}

                                def _exact_fvs(msk):
                                    while msk:
                                        nxt_m = msk
                                        rm = msk
                                        while rm:
                                            lsb = rm & -rm
                                            u = lsb.bit_length() - 1
                                            rm ^= lsb
                                            if not (in_mask[u] & msk) or not (out_mask[u] & msk):
                                                nxt_m ^= lsb
                                        if nxt_m == msk:
                                            break
                                        msk = nxt_m
                                    if not msk:
                                        return 0
                                    hit = fvs_memo.get(msk)
                                    if hit is not None:
                                        return hit
                                    cyc = _find_short_cycle(msk)
                                    if not cyc:
                                        fvs_memo[msk] = 0
                                        return 0
                                    best_v = _INF
                                    rm = cyc
                                    while rm:
                                        lsb = rm & -rm
                                        u = lsb.bit_length() - 1
                                        rm ^= lsb
                                        cand = w_dl[u] + _exact_fvs(msk ^ lsb)
                                        if cand < best_v:
                                            best_v = cand
                                    fvs_memo[msk] = best_v
                                    return best_v

                                group_extra += _exact_fvs(alive_mask)
                            else:
                                # Vertex-disjoint cycle packing lower bound for large graphs
                                rem_g = alive_mask
                                while rem_g:
                                    while rem_g:
                                        nxt_m = rem_g
                                        rm = rem_g
                                        while rm:
                                            lsb = rm & -rm
                                            u = lsb.bit_length() - 1
                                            rm ^= lsb
                                            if not (in_mask[u] & rem_g) or not (out_mask[u] & rem_g):
                                                nxt_m ^= lsb
                                        if nxt_m == rem_g:
                                            break
                                        rem_g = nxt_m
                                    if not rem_g:
                                        break
                                    cyc = _find_short_cycle(rem_g)
                                    if not cyc:
                                        break
                                    min_w = _INF
                                    rm = cyc
                                    while rm:
                                        lsb = rm & -rm
                                        u = lsb.bit_length() - 1
                                        rm ^= lsb
                                        if w_dl[u] < min_w:
                                            min_w = w_dl[u]
                                    group_extra += min_w
                                    rem_g ^= cyc

                    if group_extra > best_extra:
                        best_extra = group_extra
                h_hub_extra += best_extra

            # Disjoint destination-leaf consolidation trade-off bound
            if num_in_trucks >= 2 and self.private_goal_bridges:
                for g_loc, g_pkgs, priv_edges in self.private_goal_bridges:
                    trk_cnts = None
                    for pi in g_pkgs:
                        pl = pkg_locs[pi]
                        if pl < 0:
                            ti = -pl - 1
                            if trk_cnts is None:
                                trk_cnts = [0] * num_trucks
                            trk_cnts[ti] += 1
                    if trk_cnts is None:
                        continue
                    active_trks = [ti for ti in range(num_trucks) if trk_cnts[ti] > 0]
                    m_trks = len(active_trks)
                    if m_trks < 2:
                        continue
                    base_ins = []
                    for bi, g_side in priv_edges:
                        side = road_bridges[bi][2]
                        other_side = 1 - g_side
                        all_out = True
                        for ti in active_trks:
                            if side[truck_rep_loc[ti]] != other_side:
                                all_out = False
                                break
                        if all_out:
                            base_ins.append(
                                b_req_vu[bi] if g_side == 0 else b_req_uv[bi]
                            )
                    if not base_ins:
                        continue
                    cnts = sorted(trk_cnts[ti] for ti in active_trks)
                    best_g = 0
                    for bi_req in base_ins:
                        if m_trks > bi_req:
                            best_g += m_trks - bi_req
                    pref_lu = 0
                    for unload_k in range(1, m_trks + 1):
                        pref_lu += 2 * cnts[unload_k - 1]
                        if pref_lu >= best_g:
                            break
                        r_cross = m_trks - unload_k
                        d_extra = 0
                        for bi_req in base_ins:
                            if r_cross > bi_req:
                                d_extra += r_cross - bi_req
                        tot_g = pref_lu + d_extra
                        if tot_g < best_g:
                            best_g = tot_g
                    h_consol_extra += best_g

        h_road_bridge = h_road_bridge_base + h_hub_extra

        # 5b. Additive road-only MST & free-ferry road ton-km on islands without G_rf bridges
        road_dist = self.road_dist
        road_dist_free_ferry = self.road_dist_free_ferry
        dist_to_any_active_port = self.dist_to_any_active_port
        non_bridge_drive = 0
        non_bridge_drive_by_isl = None
        if self.non_bridge_islands_with_roads:
            non_bridge_drive_by_isl = [0] * self.num_islands
            for isl in self.non_bridge_islands_with_roads:
                isl_req = [v for v in req_nodes if island_of[v] == isl]
                if not isl_req:
                    continue
                k_r = len(isl_req)
                min_e = [dist_to_any_active_port[v] for v in isl_req]
                for ti in range(num_trucks):
                    tl = truck_locs[ti]
                    if tl >= 0 and island_of[tl] == isl:
                        d_row = road_dist[tl]
                        for idx in range(k_r):
                            d = d_row[isl_req[idx]]
                            if d < min_e[idx]:
                                min_e[idx] = d
                used_r = [False] * k_r
                isl_mst = 0
                for _ in range(k_r):
                    bi = -1
                    bw = _INF
                    for idx in range(k_r):
                        if not used_r[idx] and min_e[idx] < bw:
                            bw = min_e[idx]
                            bi = idx
                    if bi == -1:
                        break
                    used_r[bi] = True
                    isl_mst += bw
                    u_row = road_dist[isl_req[bi]]
                    for idx in range(k_r):
                        if not used_r[idx]:
                            d = u_row[isl_req[idx]]
                            if d < min_e[idx]:
                                min_e[idx] = d

                # Even with free intra-island ferry teleportation, non-port locations
                # require road ton-km on this island alone.
                isl_rw = 0
                for _, _, gl, cur_loc, _, w, p_isl, g_isl, on_f in pkg_info:
                    if p_isl == isl:
                        if g_isl == isl:
                            dr = road_dist_free_ferry[cur_loc][gl]
                            if dr < _INF:
                                isl_rw += w * dr
                        elif on_f < 0:
                            dp_p = dist_to_any_active_port[cur_loc]
                            if dp_p < _INF:
                                isl_rw += w * dp_p
                    elif g_isl == isl:
                        dg_p = dist_to_any_active_port[gl]
                        if dg_p < _INF:
                            isl_rw += w * dg_p
                isl_ton = (isl_rw + cap_m1) // max_eff_cap if isl_rw > 0 else 0
                isl_drv = isl_mst if isl_mst >= isl_ton else isl_ton
                non_bridge_drive_by_isl[isl] = isl_drv
                non_bridge_drive += isl_drv

        # 5c. h_road_ton_km (A_drive ONLY, valid on all islands including intra-ferry islands)
        h_road_ton_km = 0
        if not is_pure_road_tree:
            island_has_intra_ferry = self.island_has_intra_ferry
            dist_to_inter_port = self.dist_to_inter_port
            total_road_work = 0
            for _, _, gl, cur_loc, _, w, p_isl, g_isl, on_f in pkg_info:
                d_road = 0
                if p_isl == g_isl:
                    if on_f < 0:
                        dr = (
                            road_dist_free_ferry[cur_loc][gl]
                            if island_has_intra_ferry[p_isl]
                            else road_dist[cur_loc][gl]
                        )
                        if dr < _INF:
                            d_road = dr
                    else:
                        dg_p = dist_to_any_active_port[gl]
                        if dg_p < _INF:
                            d_road = dg_p
                else:
                    if on_f < 0:
                        dp_port = (
                            dist_to_any_active_port[cur_loc]
                            if island_has_intra_ferry[p_isl]
                            else dist_to_inter_port[cur_loc]
                        )
                        if dp_port < _INF:
                            d_road += dp_port
                    dg_port = (
                        dist_to_any_active_port[gl]
                        if island_has_intra_ferry[g_isl]
                        else dist_to_inter_port[gl]
                    )
                    if dg_port < _INF:
                        d_road += dg_port
                total_road_work += w * d_road
            if total_road_work > 0:
                h_road_ton_km = (total_road_work + cap_m1) // max_eff_cap

        h_drive = h_road_bridge + non_bridge_drive
        if h_road_ton_km > h_drive:
            h_drive = h_road_ton_km

        # =====================================================================
        # SECTION 5d & SECTION 6: h_bd (BOARD + DISEMBARK) & h_sail (SAIL)
        # =====================================================================
        h_bd = 0
        h_sail = 0
        h_empty_port_extra = 0
        if self.has_inter_island_ferries:
            num_islands = self.num_islands
            island_ferries = self.island_ferries
            max_island_ferry_truck_cap = self.max_island_ferry_truck_cap
            min_sails = self.min_sails

            max_ferry_weight = max_ferry_weight_dyn
            max_island_sail_weight = max_island_sail_weight_dyn
            max_gfw = max_gfw_dyn

            # Single truck pass for both h_bd and h_sail
            w_ground_out = [0] * num_islands
            h_ground_out = [0] * num_islands
            w_not_ground_in = [0] * num_islands
            h_not_ground_in = [0] * num_islands
            m_ground_isl = [0] * num_islands
            c_ground_isl = [0] * num_islands
            max_ground_cap_isl = [-1] * num_islands
            m_isl_trk = [0] * num_islands
            c_isl_trk = [0] * num_islands
            max_cap_on_island = [-1] * num_islands
            total_c_all = 0
            num_trucks_aboard = 0

            for ti in range(num_trucks):
                ec = eff_truck_caps[ti]
                total_c_all += ec
                isl = truck_eff_island[ti]
                if truck_on_ferry[ti] < 0:
                    m_ground_isl[isl] += 1
                    c_ground_isl[isl] += ec
                    if ec > max_ground_cap_isl[isl]:
                        max_ground_cap_isl[isl] = ec
                else:
                    num_trucks_aboard += 1
                m_isl_trk[isl] += 1
                c_isl_trk[isl] += ec
                if ec > max_cap_on_island[isl]:
                    max_cap_on_island[isl] = ec

            # Single package pass for both h_bd and h_sail
            stranded_ground_isl = [False] * num_islands
            stranded_in = [False] * num_islands
            w_out_isl = [0] * num_islands
            w_in_isl = [0] * num_islands
            h_out_isl = [0] * num_islands
            h_in_isl = [0] * num_islands
            board_work = 0
            disembark_work = 0
            total_sail_work = 0
            bound4_sails = 0

            for pi, pl, _, _, is_gnd, w, p_isl, g_isl, fi_t in pkg_info:
                is_h = 1 if w > half_eff_cap else 0
                ms = min_sails[p_isl][g_isl]

                if is_gnd:
                    if w > max_ground_cap_isl[p_isl]:
                        stranded_ground_isl[p_isl] = True
                    if w > max_cap_on_island[p_isl]:
                        stranded_in[p_isl] = True
                    if p_isl != g_isl:
                        w_ground_out[p_isl] += w
                        h_ground_out[p_isl] += is_h
                        w_not_ground_in[g_isl] += w
                        h_not_ground_in[g_isl] += is_h
                        if ms < _INF:
                            board_work += w * ms
                            disembark_work += w * ms
                    if ms < _INF:
                        total_sail_work += w * ms
                        min_pick_s = _INF
                        for ti in capable_trucks[pi]:
                            ds = min_sails[truck_eff_island[ti]][p_isl]
                            if ds < min_pick_s:
                                min_pick_s = ds
                        if min_pick_s < _INF:
                            s_chain = min_pick_s + ms
                            if s_chain > bound4_sails:
                                bound4_sails = s_chain
                else:
                    if fi_t < 0:
                        if p_isl != g_isl:
                            w_ground_out[p_isl] += w
                            h_ground_out[p_isl] += is_h
                            w_not_ground_in[g_isl] += w
                            h_not_ground_in[g_isl] += is_h
                            if ms < _INF:
                                board_work += w * ms
                                disembark_work += w * ms
                    else:
                        w_not_ground_in[g_isl] += w
                        h_not_ground_in[g_isl] += is_h
                        if ms < _INF:
                            if ms > 1:
                                board_work += w * (ms - 1)
                            disembark_work += w * (ms if ms >= 1 else 1)
                        else:
                            disembark_work += w
                    if ms < _INF:
                        total_sail_work += w * ms
                        if ms > bound4_sails:
                            bound4_sails = ms

                if p_isl != g_isl:
                    w_out_isl[p_isl] += w
                    h_out_isl[p_isl] += is_h
                    w_in_isl[g_isl] += w
                    h_in_isl[g_isl] += is_h

            # Island-level h_bd + Bounds 6.1, 6.2, 6.3 for h_sail
            b1 = 0
            d1 = 0
            sum_s_out = 0
            sum_s_in = 0
            bound3_sails = 0
            so_by_isl = [0] * num_islands
            si_by_isl = [0] * num_islands
            max_so_si = 0
            for isl in self.active_inter_islands:
                wgo = w_ground_out[isl]
                b_isl = (wgo + cap_m1) // max_eff_cap if wgo > 0 else 0
                if h_ground_out[isl] > b_isl:
                    b_isl = h_ground_out[isl]
                b1 += b_isl

                wngi = w_not_ground_in[isl]
                d_isl = (wngi + cap_m1) // max_eff_cap if wngi > 0 else 0
                if h_not_ground_in[isl] > d_isl:
                    d_isl = h_not_ground_in[isl]
                if stranded_ground_isl[isl] and d_isl < 1:
                    d_isl = 1
                if b_isl - m_ground_isl[isl] > d_isl:
                    d_isl = b_isl - m_ground_isl[isl]
                if wgo > c_ground_isl[isl]:
                    cw = (wgo - c_ground_isl[isl] + cap_m1) // max_eff_cap
                    if cw > d_isl:
                        d_isl = cw
                d1 += d_isl

                fl = island_ferries[isl]
                cap_isl = max_island_sail_weight[isl]
                f_trk_cap = max_island_ferry_truck_cap[isl]
                if cap_isl <= 0 or f_trk_cap <= 0:
                    continue
                cap_isl_m1 = cap_isl - 1

                wo = w_out_isl[isl]
                wi = w_in_isl[isl]
                so = (wo + cap_isl_m1) // cap_isl if wo > 0 else 0
                si = (wi + cap_isl_m1) // cap_isl if wi > 0 else 0
                if stranded_in[isl] and si < 1:
                    si = 1

                k_out_t = (wo + cap_m1) // max_eff_cap if wo > 0 else 0
                if h_out_isl[isl] > k_out_t:
                    k_out_t = h_out_isl[isl]
                k_in_t = (wi + cap_m1) // max_eff_cap if wi > 0 else 0
                if h_in_isl[isl] > k_in_t:
                    k_in_t = h_in_isl[isl]
                if stranded_in[isl] and k_in_t < 1:
                    k_in_t = 1

                t_in = k_in_t
                if k_out_t - m_isl_trk[isl] > t_in:
                    t_in = k_out_t - m_isl_trk[isl]
                if wo > c_isl_trk[isl]:
                    cw = (wo - c_isl_trk[isl] + cap_m1) // max_eff_cap
                    if cw > t_in:
                        t_in = cw

                m_other_t = num_trucks - m_isl_trk[isl]
                c_other_t = total_c_all - c_isl_trk[isl]
                t_out = k_out_t
                if k_in_t - m_other_t > t_out:
                    t_out = k_in_t - m_other_t
                if wi > c_other_t:
                    cw = (wi - c_other_t + cap_m1) // max_eff_cap
                    if cw > t_out:
                        t_out = cw

                si_from_t = (t_in + f_trk_cap - 1) // f_trk_cap if t_in > 0 else 0
                so_from_t = (t_out + f_trk_cap - 1) // f_trk_cap if t_out > 0 else 0
                if si_from_t > si:
                    si = si_from_t
                if so_from_t > so:
                    so = so_from_t

                so_by_isl[isl] = so
                si_by_isl[isl] = si
                if so > max_so_si:
                    max_so_si = so
                if si > max_so_si:
                    max_so_si = si
                sum_s_out += so
                sum_s_in += si

                if so > 0 or si > 0:
                    m_i = 0
                    c_i = 0
                    c_other = 0
                    for fi in fl:
                        fw = max_ferry_weight[fi]
                        if island_of[ferry_locs[fi]] == isl:
                            m_i += 1
                            c_i += fw
                        else:
                            c_other += fw
                    m_other = len(fl) - m_i
                    req_out = so
                    if si - m_other > req_out:
                        req_out = si - m_other
                    if wi > c_other:
                        cw = (wi - c_other + cap_isl_m1) // cap_isl
                        if cw > req_out:
                            req_out = cw
                    req_in = si
                    if so - m_i > req_in:
                        req_in = so - m_i
                    if wo > c_i:
                        cw = (wo - c_i + cap_isl_m1) // cap_isl
                        if cw > req_in:
                            req_in = cw
                    b3 = req_out + req_in
                    if b3 > bound3_sails:
                        bound3_sails = b3

            b2 = (board_work + cap_m1) // max_eff_cap if board_work > 0 else 0
            d2 = (
                (disembark_work + cap_m1) // max_eff_cap
                if disembark_work > 0
                else 0
            )
            lb_disembark = d1 if d1 >= d2 else d2
            lb_board = b1 if b1 >= b2 else b2
            if lb_disembark - num_trucks_aboard > lb_board:
                lb_board = lb_disembark - num_trucks_aboard
            h_bd = lb_board + lb_disembark

            # Merged single-pass cut-ferry evaluation for BOTH h_bd and Bound 6.7 (h_sail).
            # For 2-way cut ferries (the common case), evaluate only touched_in[0] once (2x faster).
            bound7_sails = 0
            if self.cut_ferries:
                bd_cut_sum = 0
                island_sole_ferry = self.island_sole_ferry
                island_has_bridge = self.island_has_bridge
                isl_road_bridges = self.isl_road_bridges
                ferry_caps = self.ferry_caps
                for fi, touched_in, in_comp, sole_rb_sides in self.cut_ferries:
                    cap_f = max_ferry_weight[fi]
                    if cap_f <= 0:
                        continue
                    cap_f_m1 = cap_f - 1
                    cur_f_port = ferry_locs[fi]
                    cur_f_isl = island_of[cur_f_port]

                    ab_cnt = 0
                    ab_cap_sum = 0
                    for ti in range(num_trucks):
                        if truck_on_ferry[ti] == fi:
                            ab_cnt += 1
                            ab_cap_sum += eff_truck_caps[ti]

                    is_two_way = len(touched_in) == 2
                    eval_sides = (touched_in[0],) if is_two_way else touched_in
                    side_stats = [None] * len(touched_in) if sole_rb_sides else None

                    sum_out_f = 0
                    sum_in_f = 0
                    max_single_f = 0
                    best_fi_bd = 0
                    cur_h_so = 0
                    cur_h_si = 0
                    cur_h_single = -1

                    for h_idx, in_h in enumerate(eval_sides):
                        fi_in_h = in_h[cur_f_isl]
                        m_h = m_out = c_h = c_out = 0
                        max_cap_h = max_cap_out = -1
                        for ti in range(num_trucks):
                            isl = truck_eff_island[ti]
                            if not in_comp[isl]:
                                continue
                            ec = eff_truck_caps[ti]
                            if in_h[isl]:
                                m_h += 1
                                c_h += ec
                                if ec > max_cap_h:
                                    max_cap_h = ec
                            else:
                                m_out += 1
                                c_out += ec
                                if ec > max_cap_out:
                                    max_cap_out = ec

                        wo_h = wi_h = ho_h = hi_h = 0
                        wo_not_ab = wi_not_ab = ho_not_ab = hi_not_ab = 0
                        need_in_h = False
                        need_out_h = False
                        ab_stay_w_by_t = None
                        for _, pl, _, _, is_gnd, w, p_isl, g_isl, on_f in pkg_info:
                            if not in_comp[p_isl]:
                                continue
                            on_this_f = on_f == fi
                            if in_h[p_isl]:
                                if not in_h[g_isl]:
                                    wo_h += w
                                    if w > half_eff_cap:
                                        ho_h += 1
                                    if not on_this_f:
                                        wo_not_ab += w
                                        if w > half_eff_cap:
                                            ho_not_ab += 1
                                elif on_this_f and fi_in_h:
                                    ti_p = -pl - 1
                                    if ab_stay_w_by_t is None:
                                        ab_stay_w_by_t = [0] * num_trucks
                                    ab_stay_w_by_t[ti_p] += w
                                if is_gnd and w > max_cap_h:
                                    need_in_h = True
                            else:
                                if in_h[g_isl]:
                                    wi_h += w
                                    if w > half_eff_cap:
                                        hi_h += 1
                                    if not on_this_f:
                                        wi_not_ab += w
                                        if w > half_eff_cap:
                                            hi_not_ab += 1
                                elif on_this_f and not fi_in_h:
                                    ti_p = -pl - 1
                                    if ab_stay_w_by_t is None:
                                        ab_stay_w_by_t = [0] * num_trucks
                                    ab_stay_w_by_t[ti_p] += w
                                if is_gnd and w > max_cap_out:
                                    need_out_h = True

                        # --- Cut-ferry BOARD + DISEMBARK bound ---
                        ko = (wo_h + cap_m1) // max_eff_cap if wo_h > 0 else 0
                        if ho_h > ko:
                            ko = ho_h
                        if need_out_h and ko < 1:
                            ko = 1
                        ki = (wi_h + cap_m1) // max_eff_cap if wi_h > 0 else 0
                        if hi_h > ki:
                            ki = hi_h
                        if need_in_h and ki < 1:
                            ki = 1

                        # --- Cut-ferry SAIL bound (Bound 6.7) ---
                        so_h = (wo_h + cap_f_m1) // cap_f if wo_h > 0 else 0
                        si_h = (wi_h + cap_f_m1) // cap_f if wi_h > 0 else 0
                        if need_in_h and si_h < 1:
                            si_h = 1
                        if need_out_h and so_h < 1:
                            so_h = 1

                        if side_stats is not None:
                            side_stats[h_idx] = (so_h, si_h, wo_h, wi_h, ko)
                            if is_two_way:
                                side_stats[1] = (si_h, so_h, wi_h, wo_h, ki)

                        if is_two_way:
                            sum_out_f = so_h + si_h
                            sum_in_f = sum_out_f
                        else:
                            sum_out_f += so_h
                            sum_in_f += si_h

                        if so_h > 0 or si_h > 0:
                            if fi_in_h:
                                cur_h_so = so_h
                                cur_h_si = si_h
                                s_o = so_h if so_h >= si_h else si_h
                                s_i = si_h if si_h >= so_h - 1 else so_h - 1
                                cur_h_single = s_o + s_i
                            else:
                                s_o = so_h if so_h >= si_h - 1 else si_h - 1
                                s_i = si_h if si_h >= so_h else so_h
                                if is_two_way:
                                    cur_h_so = si_h
                                    cur_h_si = so_h
                                    cur_h_single = s_o + s_i
                            if s_o + s_i > max_single_f:
                                max_single_f = s_o + s_i

                        req_o = ko
                        if ki - m_out > req_o:
                            req_o = ki - m_out
                        if wi_h > c_out:
                            cw = (wi_h - c_out + cap_m1) // max_eff_cap
                            if cw > req_o:
                                req_o = cw

                        req_i = ki
                        if ko - m_h > req_i:
                            req_i = ko - m_h
                        if wo_h > c_h:
                            cw = (wo_h - c_h + cap_m1) // max_eff_cap
                            if cw > req_i:
                                req_i = cw

                        if ab_cnt == 0:
                            cand_bd = 2 * (req_o + req_i)
                        else:
                            ko_not_ab = (
                                (wo_not_ab + cap_m1) // max_eff_cap
                                if wo_not_ab > 0
                                else 0
                            )
                            if ho_not_ab > ko_not_ab:
                                ko_not_ab = ho_not_ab
                            ki_not_ab = (
                                (wi_not_ab + cap_m1) // max_eff_cap
                                if wi_not_ab > 0
                                else 0
                            )
                            if hi_not_ab > ki_not_ab:
                                ki_not_ab = hi_not_ab

                            # Non-fi trucks on cur_f_isl's side: any truck aboard fi
                            # must DISEMBARK onto cur_f_isl's side before loading
                            # packages not yet aboard fi.
                            if fi_in_h:
                                m_avail = m_h - ab_cnt
                                c_avail = c_h - ab_cap_sum
                            else:
                                m_avail = m_out - ab_cnt
                                c_avail = c_out - ab_cap_sum

                            if ab_stay_w_by_t is not None:
                                stay_ws = sorted(w for w in ab_stay_w_by_t if w > 0)
                                m_stay = len(stay_ws)
                                cand_bd = _INF
                                carry_w = 0
                                for carry_k in range(m_stay + 1):
                                    if carry_k > 0:
                                        carry_w += stay_ws[carry_k - 1]
                                    drop_k = m_stay - carry_k
                                    free_ab = ab_cnt - drop_k
                                    if fi_in_h:
                                        wi2 = wi_h + carry_w
                                        ki2 = (wi2 + cap_m1) // max_eff_cap if wi2 > 0 else 0
                                        if hi_h > ki2:
                                            ki2 = hi_h
                                        if need_in_h and ki2 < 1:
                                            ki2 = 1
                                        ro2 = ko
                                        if ki2 - m_out > ro2:
                                            ro2 = ki2 - m_out
                                        if wi2 > c_out:
                                            cw = (wi2 - c_out + cap_m1) // max_eff_cap
                                            if cw > ro2:
                                                ro2 = cw
                                        ri2 = ki2
                                        if ko - m_h > ri2:
                                            ri2 = ko - m_h
                                        if wo_h > c_h:
                                            cw = (wo_h - c_h + cap_m1) // max_eff_cap
                                            if cw > ri2:
                                                ri2 = cw
                                        bo_rem = ro2 - free_ab if ro2 > free_ab else 0
                                        if ko_not_ab > bo_rem:
                                            bo_rem = ko_not_ab
                                        d_in = ri2 + drop_k
                                        if bo_rem - m_avail > d_in:
                                            d_in = bo_rem - m_avail
                                        if wo_not_ab > c_avail:
                                            cw = (wo_not_ab - c_avail + cap_m1) // max_eff_cap
                                            if cw > d_in:
                                                d_in = cw
                                        val = ro2 + d_in + bo_rem + ri2
                                    else:
                                        wo2 = wo_h + carry_w
                                        ko2 = (wo2 + cap_m1) // max_eff_cap if wo2 > 0 else 0
                                        if ho_h > ko2:
                                            ko2 = ho_h
                                        if need_out_h and ko2 < 1:
                                            ko2 = 1
                                        ro2 = ko2
                                        if ki - m_out > ro2:
                                            ro2 = ki - m_out
                                        if wi_h > c_out:
                                            cw = (wi_h - c_out + cap_m1) // max_eff_cap
                                            if cw > ro2:
                                                ro2 = cw
                                        ri2 = ki
                                        if ko2 - m_h > ri2:
                                            ri2 = ko2 - m_h
                                        if wo2 > c_h:
                                            cw = (wo2 - c_h + cap_m1) // max_eff_cap
                                            if cw > ri2:
                                                ri2 = cw
                                        bi_rem = ri2 - free_ab if ri2 > free_ab else 0
                                        if ki_not_ab > bi_rem:
                                            bi_rem = ki_not_ab
                                        d_out = ro2 + drop_k
                                        if bi_rem - m_avail > d_out:
                                            d_out = bi_rem - m_avail
                                        if wi_not_ab > c_avail:
                                            cw = (wi_not_ab - c_avail + cap_m1) // max_eff_cap
                                            if cw > d_out:
                                                d_out = cw
                                        val = d_out + ri2 + ro2 + bi_rem
                                    if val < cand_bd:
                                        cand_bd = val
                            else:
                                if fi_in_h:
                                    bo_rem = req_o - ab_cnt if req_o > ab_cnt else 0
                                    if ko_not_ab > bo_rem:
                                        bo_rem = ko_not_ab
                                    d_in = req_i
                                    if bo_rem - m_avail > d_in:
                                        d_in = bo_rem - m_avail
                                    if wo_not_ab > c_avail:
                                        cw = (wo_not_ab - c_avail + cap_m1) // max_eff_cap
                                        if cw > d_in:
                                            d_in = cw
                                    cand_bd = req_o + d_in + bo_rem + req_i
                                else:
                                    bi_rem = req_i - ab_cnt if req_i > ab_cnt else 0
                                    if ki_not_ab > bi_rem:
                                        bi_rem = ki_not_ab
                                    d_out = req_o
                                    if bi_rem - m_avail > d_out:
                                        d_out = bi_rem - m_avail
                                    if wi_not_ab > c_avail:
                                        cw = (wi_not_ab - c_avail + cap_m1) // max_eff_cap
                                        if cw > d_out:
                                            d_out = cw
                                    cand_bd = d_out + req_i + req_o + bi_rem

                        if cand_bd > best_fi_bd:
                            best_fi_bd = cand_bd

                    bd_cut_sum += best_fi_bd

                    sails_f = sum_out_f
                    if sum_in_f > sails_f:
                        sails_f = sum_in_f
                    if max_single_f > sails_f:
                        sails_f = max_single_f

                    # Zero-extra-sail trade-off for cut-ferry fi:
                    # Either fi executes >= sails_f + 1 sails (+3 over bound7_sails),
                    # OR fi executes strictly sails_f alternating inter-island sails
                    # with zero intra-island sails.
                    bumped_sail = False
                    fi_trade = 0
                    f_cap_t = ferry_caps[fi]

                    if (
                        ab_cnt == 0
                        and cur_h_single == sails_f
                        and island_sole_ferry[cur_f_isl] == fi
                    ):
                        already_cur = (
                            non_bridge_drive_by_isl[cur_f_isl]
                            if non_bridge_drive_by_isl is not None
                            else 0
                        )
                        if cur_h_so >= 1 and cur_h_so >= cur_h_si and cur_f_port not in truck_locs:
                            min_d_p0 = _INF
                            d_p0_row = road_dist[cur_f_port]
                            for ti in range(num_trucks):
                                tl = truck_locs[ti]
                                if tl >= 0 and island_of[tl] == cur_f_isl:
                                    dp = d_p0_row[tl]
                                    if dp < min_d_p0:
                                        min_d_p0 = dp
                            if min_d_p0 >= _INF:
                                sails_f += 1
                                bumped_sail = True
                            elif not island_has_bridge[cur_f_isl]:
                                drive_extra = min_d_p0 - already_cur
                                if drive_extra > 0:
                                    tr = 3 if drive_extra >= 3 else drive_extra
                                    if tr > fi_trade:
                                        fi_trade = tr

                        if (
                            not bumped_sail
                            and cur_h_si == 0
                            and cur_h_so <= 1
                            and not island_has_bridge[cur_f_isl]
                            and m_ground_isl[cur_f_isl] > 0
                            and fi_trade < 3
                        ):
                            isl_req_ext = [
                                v for v in req_nodes if island_of[v] == cur_f_isl
                            ]
                            if cur_h_so >= 1 and cur_f_port not in isl_req_ext:
                                isl_req_ext.append(cur_f_port)
                            if isl_req_ext:
                                k_re = len(isl_req_ext)
                                min_re = [_INF] * k_re
                                for ti in range(num_trucks):
                                    tl = truck_locs[ti]
                                    if tl >= 0 and island_of[tl] == cur_f_isl:
                                        d_row = road_dist[tl]
                                        for idx in range(k_re):
                                            d = d_row[isl_req_ext[idx]]
                                            if d < min_re[idx]:
                                                min_re[idx] = d
                                used_re = [False] * k_re
                                mst_no_entry = 0
                                for _ in range(k_re):
                                    bi_r = -1
                                    bw_r = _INF
                                    for idx in range(k_re):
                                        if not used_re[idx] and min_re[idx] < bw_r:
                                            bw_r = min_re[idx]
                                            bi_r = idx
                                    if bi_r == -1:
                                        break
                                    used_re[bi_r] = True
                                    mst_no_entry += bw_r
                                    u_row = road_dist[isl_req_ext[bi_r]]
                                    for idx in range(k_re):
                                        if not used_re[idx]:
                                            d = u_row[isl_req_ext[idx]]
                                            if d < min_re[idx]:
                                                min_re[idx] = d
                                single_to_port = 0
                                if cur_h_so >= 1:
                                    d_p0_row = road_dist[cur_f_port]
                                    for pi, pl, _, cur_loc, is_gnd, _, p_isl, g_isl, _ in pkg_info:
                                        if g_isl == cur_f_isl or p_isl != cur_f_isl:
                                            continue
                                        if is_gnd:
                                            d_to_f = d_p0_row[pl]
                                            if d_to_f >= _INF:
                                                continue
                                            mp = _INF
                                            for ti in capable_trucks[pi]:
                                                tl = truck_locs[ti]
                                                if tl >= 0 and island_of[tl] == cur_f_isl:
                                                    dp = road_dist[tl][pl]
                                                    if dp < mp:
                                                        mp = dp
                                            if mp < _INF and mp + d_to_f > single_to_port:
                                                single_to_port = mp + d_to_f
                                        else:
                                            d_to_f = d_p0_row[cur_loc]
                                            if d_to_f < _INF and d_to_f > single_to_port:
                                                single_to_port = d_to_f
                                best_no_entry = (
                                    mst_no_entry
                                    if mst_no_entry >= single_to_port
                                    else single_to_port
                                )
                                drive_extra = best_no_entry - already_cur
                                if drive_extra > 0:
                                    tr = 3 if drive_extra >= 3 else drive_extra
                                    if tr > fi_trade:
                                        fi_trade = tr

                    # Generalized exact zero-extra-sail road-only bridge conservation
                    # on ANY sole-ferry non-bridge island touched by cut-ferry fi
                    # (valid regardless of where fi is docked or whether trucks are aboard).
                    if not bumped_sail and sole_rb_sides:
                        for h_idx_s, isl_s in sole_rb_sides:
                            so_i, si_i, wo_i, wi_i, ko_i = side_stats[h_idx_s]
                            if so_i == 0 and si_i == 0:
                                continue
                            fi_on_i = cur_f_isl == isl_s
                            if fi_on_i:
                                s_o_i = so_i if so_i >= si_i else si_i
                                s_i_i = si_i if si_i >= so_i - 1 else so_i - 1
                            else:
                                s_i_i = si_i if si_i >= so_i else so_i
                                s_o_i = so_i if so_i >= si_i - 1 else si_i - 1
                            if s_o_i + s_i_i != sails_f:
                                continue

                            m_i_eff = m_ground_isl[isl_s] + (ab_cnt if fi_on_i else 0)
                            if ko_i > m_i_eff + s_i_i * f_cap_t:
                                sails_f += 1
                                bumped_sail = True
                                break

                            out_slk = s_o_i * cap_f - wo_i
                            if out_slk < 0:
                                out_slk = 0
                            in_slk = s_i_i * cap_f - wi_i
                            if in_slk < 0:
                                in_slk = 0
                            io_slk = out_slk if out_slk < in_slk else in_slk

                            rb_drive_lb = 0
                            for rb_side, has_p0, has_p1 in isl_road_bridges[isl_s]:
                                if fi_on_i:
                                    side_a = rb_side[cur_f_port]
                                    a_has_p = True
                                    b_has_p = has_p1 if side_a == 0 else has_p0
                                else:
                                    side_a = 0
                                    a_has_p = has_p0
                                    b_has_p = has_p1

                                m_a = m_b = 0
                                max_cap_a = max_cap_b = -1
                                for ti in range(num_trucks):
                                    if truck_eff_island[ti] == isl_s:
                                        ec = eff_truck_caps[ti]
                                        if rb_side[truck_rep_loc[ti]] == side_a:
                                            m_a += 1
                                            if ec > max_cap_a:
                                                max_cap_a = ec
                                        else:
                                            m_b += 1
                                            if ec > max_cap_b:
                                                max_cap_b = ec

                                w_ab_int = w_ba_int = 0
                                w_a_lv = w_b_lv = w_a_ar = w_b_ar = 0
                                need_in_a_gnd = False
                                need_in_b_gnd = False
                                for _, _, gl, cur_loc, is_gnd, w, p_isl, g_isl, _ in pkg_info:
                                    if p_isl == isl_s:
                                        in_a_p = rb_side[cur_loc] == side_a
                                        if is_gnd:
                                            if in_a_p:
                                                if w > max_cap_a:
                                                    need_in_a_gnd = True
                                            elif w > max_cap_b:
                                                need_in_b_gnd = True
                                        if g_isl == isl_s:
                                            in_a_g = rb_side[gl] == side_a
                                            if in_a_p and not in_a_g:
                                                w_ab_int += w
                                            elif not in_a_p and in_a_g:
                                                w_ba_int += w
                                        else:
                                            if in_a_p:
                                                w_a_lv += w
                                            else:
                                                w_b_lv += w
                                    elif g_isl == isl_s:
                                        if rb_side[gl] == side_a:
                                            w_a_ar += w
                                        else:
                                            w_b_ar += w

                                if fi_on_i:
                                    if not b_has_p:
                                        da_pairs = ((0, 0),)
                                    elif s_o_i == s_i_i + 1:
                                        da_pairs = tuple((t, t) for t in range(s_i_i + 1))
                                    else:
                                        da_pairs = tuple(
                                            (t, t + b_end)
                                            for t in range(s_i_i)
                                            for b_end in (0, 1)
                                        )
                                else:
                                    if not a_has_p:
                                        da_pairs = ((s_o_i, s_i_i),)
                                    elif not b_has_p:
                                        da_pairs = ((0, 0),)
                                    elif s_i_i == s_o_i:
                                        da_pairs = tuple((t, t) for t in range(s_o_i + 1))
                                    else:
                                        da_pairs = tuple(
                                            (t, t + b_end)
                                            for t in range(s_o_i + 1)
                                            for b_end in (0, 1)
                                        )

                                best_e = _INF
                                for dep_b, arr_b in da_pairs:
                                    dep_a = s_o_i - dep_b
                                    arr_a = s_i_i - arr_b

                                    byp_ab = io_slk
                                    cap_da = dep_a * cap_f
                                    cap_ab_arr = arr_b * cap_f
                                    if cap_da < byp_ab:
                                        byp_ab = cap_da
                                    if cap_ab_arr < byp_ab:
                                        byp_ab = cap_ab_arr
                                    w_ab = w_ab_int - byp_ab if w_ab_int > byp_ab else 0
                                    if w_a_lv > cap_da:
                                        w_ab += w_a_lv - cap_da
                                    if w_b_ar > cap_ab_arr:
                                        w_ab += w_b_ar - cap_ab_arr

                                    byp_ba = io_slk
                                    cap_db = dep_b * cap_f
                                    cap_aa = arr_a * cap_f
                                    if cap_db < byp_ba:
                                        byp_ba = cap_db
                                    if cap_aa < byp_ba:
                                        byp_ba = cap_aa
                                    w_ba = w_ba_int - byp_ba if w_ba_int > byp_ba else 0
                                    if w_b_lv > cap_db:
                                        w_ba += w_b_lv - cap_db
                                    if w_a_ar > cap_aa:
                                        w_ba += w_a_ar - cap_aa

                                    k_ab = (w_ab + cap_m1) // max_eff_cap if w_ab > 0 else 0
                                    k_ba = (w_ba + cap_m1) // max_eff_cap if w_ba > 0 else 0
                                    if arr_a == 0 and need_in_a_gnd and k_ba < 1:
                                        k_ba = 1
                                    if arr_b == 0 and need_in_b_gnd and k_ab < 1:
                                        k_ab = 1

                                    rem_a = ko_i - dep_b * f_cap_t
                                    net_lv_a = (rem_a if rem_a > 0 else 0) - arr_a * f_cap_t
                                    rem_b = ko_i - dep_a * f_cap_t
                                    net_lv_b = (rem_b if rem_b > 0 else 0) - arr_b * f_cap_t

                                    r_ba = k_ba
                                    c_ba = k_ab + net_lv_a - m_a
                                    if c_ba > r_ba:
                                        r_ba = c_ba
                                    r_ab = k_ab
                                    c_ab = r_ba + net_lv_b - m_b
                                    if c_ab > r_ab:
                                        r_ab = c_ab
                                    c_ba2 = r_ab + net_lv_a - m_a
                                    if c_ba2 > r_ba:
                                        r_ba = c_ba2

                                    tot_e = r_ab + r_ba
                                    if tot_e < best_e:
                                        best_e = tot_e
                                rb_drive_lb += best_e

                            already_s = (
                                non_bridge_drive_by_isl[isl_s]
                                if non_bridge_drive_by_isl is not None
                                else 0
                            )
                            drive_extra = rb_drive_lb - already_s
                            if drive_extra > 0:
                                tr = 3 if drive_extra >= 3 else drive_extra
                                if tr > fi_trade:
                                    fi_trade = tr

                    if not bumped_sail and fi_trade > h_empty_port_extra:
                        h_empty_port_extra = fi_trade

                    bound7_sails += sails_f

                if bd_cut_sum > h_bd:
                    h_bd = bd_cut_sum

            # Bound 6.5: Global ton-sails lower bound
            bound5_sails = (
                (total_sail_work + max_gfw - 1) // max_gfw
                if total_sail_work > 0 and max_gfw > 0
                else 0
            )

            # Empty-first-sail bonus: if all active ferries are empty & on 0-truck islands
            vol_sails = sum_s_out if sum_s_out >= sum_s_in else sum_s_in
            if bound4_sails > vol_sails:
                vol_sails = bound4_sails
            if bound5_sails > vol_sails:
                vol_sails = bound5_sails
            if vol_sails > 0 and num_trucks_aboard == 0:
                any_ferry_with_truck = False
                for fi in self.active_ferry_indices:
                    if m_isl_trk[island_of[ferry_locs[fi]]] > 0:
                        any_ferry_with_truck = True
                        break
                if not any_ferry_with_truck:
                    vol_sails += 1

            # Bound 6.6: Concentric island-cut bound (only needed if island graph has cycles)
            bound6_sails = 0
            if not self.all_inter_ferries_are_cuts:
                active_isls = set()
                for _, _, _, _, _, _, p_isl, g_isl, _ in pkg_info:
                    active_isls.add(p_isl)
                    active_isls.add(g_isl)
                sail_cut_ferries = self.sail_cut_ferries

                for c_isl in active_isls:
                    dc = min_sails[c_isl]
                    d_max = 0
                    for isl in active_isls:
                        dv = dc[isl]
                        if dv < _INF and dv > d_max:
                            d_max = dv
                    if d_max <= 1:
                        continue

                    by_r = sail_cut_ferries[c_isl]
                    cut_sails = 0
                    for r in range(1, d_max + 1):
                        crossing_ferries, max_w = by_r[r]
                        if max_w <= 0:
                            continue
                        w_out_c = 0
                        w_in_c = 0
                        max_cap_in_c = -1
                        max_cap_out_c = -1
                        for ti in range(num_trucks):
                            dt = dc[truck_eff_island[ti]]
                            if dt >= _INF:
                                continue
                            tcap = eff_truck_caps[ti]
                            if dt < r:
                                if tcap > max_cap_in_c:
                                    max_cap_in_c = tcap
                            else:
                                if tcap > max_cap_out_c:
                                    max_cap_out_c = tcap

                        need_in_c = False
                        need_out_c = False
                        for _, _, _, _, is_gnd, w, p_isl, g_isl, _ in pkg_info:
                            dp = dc[p_isl]
                            dg = dc[g_isl]
                            if dp >= _INF or dg >= _INF:
                                continue
                            if dp < r:
                                if dg >= r:
                                    w_out_c += w
                                if is_gnd and w > max_cap_in_c:
                                    need_in_c = True
                            else:
                                if dg < r:
                                    w_in_c += w
                                if is_gnd and w > max_cap_out_c:
                                    need_out_c = True

                        if w_out_c == 0 and w_in_c == 0 and not need_in_c and not need_out_c:
                            continue

                        mw_m1 = max_w - 1
                        k_out = (w_out_c + mw_m1) // max_w if w_out_c > 0 else 0
                        if need_out_c and k_out < 1:
                            k_out = 1
                        k_in = (w_in_c + mw_m1) // max_w if w_in_c > 0 else 0
                        if need_in_c and k_in < 1:
                            k_in = 1

                        m_in_f = 0
                        c_in_f = 0
                        c_out_f = 0
                        for fi in crossing_ferries:
                            fw = max_ferry_weight[fi]
                            if dc[island_of[ferry_locs[fi]]] < r:
                                m_in_f += 1
                                c_in_f += fw
                            else:
                                c_out_f += fw
                        m_out_f = len(crossing_ferries) - m_in_f

                        req_out = k_out
                        if k_in - m_out_f > req_out:
                            req_out = k_in - m_out_f
                        if w_in_c > c_out_f:
                            cw = (w_in_c - c_out_f + mw_m1) // max_w
                            if cw > req_out:
                                req_out = cw

                        req_in = k_in
                        if k_out - m_in_f > req_in:
                            req_in = k_out - m_in_f
                        if w_out_c > c_in_f:
                            cw = (w_out_c - c_in_f + mw_m1) // max_w
                            if cw > req_in:
                                req_in = cw

                        cut_sails += req_out + req_in

                    if cut_sails > bound6_sails:
                        bound6_sails = cut_sails

            min_sail_count = vol_sails
            if bound3_sails > min_sail_count:
                min_sail_count = bound3_sails
            if bound6_sails > min_sail_count:
                min_sail_count = bound6_sails
            if bound7_sails > min_sail_count:
                min_sail_count = bound7_sails

            # Exact derangement sail feasibility check (3 <= k <= 4):
            # If every active island requires 1 outgoing & 1 incoming sail and
            # min_sail_count == k, then any k-sail plan must form a derangement
            # of those k islands. If no derangement satisfies reachability and
            # per-arc ferry weight capacity, at least k + 1 sails are mandatory.
            if (
                not self.all_inter_ferries_are_cuts
                and max_so_si == 1
                and min_sail_count == sum_s_out
                and min_sail_count == sum_s_in
                and (min_sail_count == 3 or min_sail_count == 4)
            ):
                u_isls = [
                    isl
                    for isl in self.active_inter_islands
                    if so_by_isl[isl] == 1 and si_by_isl[isl] == 1
                ]
                if len(u_isls) == min_sail_count:
                    k_d = min_sail_count
                    isl_to_u = [-1] * num_islands
                    for idx_u in range(k_d):
                        isl_to_u[u_isls[idx_u]] = idx_u
                    inter_pairs = []
                    all_in_u = True
                    for _, _, _, _, _, w, p_isl, g_isl, _ in pkg_info:
                        if p_isl != g_isl:
                            su = isl_to_u[p_isl]
                            du = isl_to_u[g_isl]
                            if su < 0 or du < 0:
                                all_in_u = False
                                break
                            inter_pairs.append((su, du, w))
                    if all_in_u and inter_pairs:
                        pair_f = self.island_pair_ferries
                        cap_mat = [[0] * k_d for _ in range(k_d)]
                        for i_u in range(k_d):
                            ia = u_isls[i_u]
                            for j_u in range(k_d):
                                if i_u == j_u:
                                    continue
                                fl_ab = pair_f[ia][u_isls[j_u]]
                                if fl_ab:
                                    mc_ab = 0
                                    for fi_ab in fl_ab:
                                        fw = max_ferry_weight[fi_ab]
                                        if fw > mc_ab:
                                            mc_ab = fw
                                    cap_mat[i_u][j_u] = mc_ab
                        derangs = (
                            _DERANGEMENTS_3 if k_d == 3 else _DERANGEMENTS_4
                        )
                        any_feasible = False
                        for perm in derangs:
                            arc_ok = True
                            for i_u in range(k_d):
                                if cap_mat[i_u][perm[i_u]] <= 0:
                                    arc_ok = False
                                    break
                            if not arc_ok:
                                continue
                            loads = [0] * k_d
                            for su, du, w in inter_pairs:
                                cur_u = su
                                steps = 0
                                while cur_u != du and steps < k_d:
                                    nxt_u = perm[cur_u]
                                    nl = loads[cur_u] + w
                                    if nl > cap_mat[cur_u][nxt_u]:
                                        arc_ok = False
                                        break
                                    loads[cur_u] = nl
                                    cur_u = nxt_u
                                    steps += 1
                                if not arc_ok or cur_u != du:
                                    arc_ok = False
                                    break
                            if arc_ok:
                                any_feasible = True
                                break
                        if not any_feasible:
                            min_sail_count += 1

            h_sail = 3 * min_sail_count

        # =====================================================================
        # SECTION 7: Final Admissible Combination
        # =====================================================================
        h_truck_total = h_drive + h_bd
        if h_mst > h_truck_total:
            h_truck_total = h_mst
        if h_ring_cut > h_truck_total:
            h_truck_total = h_ring_cut
        if h_ton_km > h_truck_total:
            h_truck_total = h_ton_km
        h_move = h_truck_total + h_sail
        if h_single > h_move:
            h_move = h_single
        res = h_load_unload + h_move

        if h_consol_extra > 0:
            h_consol = (
                h_load_unload
                + h_road_bridge_base
                + non_bridge_drive
                + h_bd
                + h_sail
                + h_consol_extra
            )
            if h_consol > res:
                res = h_consol

        if h_empty_port_extra > 0:
            # Valid specifically on top of (h_road_bridge + non_bridge_drive) + h_bd + (3 * bound7_sails)
            h_port_trade = (
                h_load_unload
                + h_road_bridge
                + non_bridge_drive
                + h_bd
                + 3 * bound7_sails
                + h_empty_port_extra
            )
            if h_port_trade > res:
                res = h_port_trade

        if len(h_cache) < 500000:
            h_cache[state] = res
        return res


def create_logistics_problem(game):
    print("<<create_logistics_problem")
    """ Create a logistics problem, based on the description.
    game - dictionary as described in pdf file"""
    return LogisticsProblem(game)


if __name__ == "__main__":
    ex1_check.main()
