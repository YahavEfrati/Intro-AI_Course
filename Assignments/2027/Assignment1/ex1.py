"""
Island Logistics A* Solver (Assignment 1 - Intro to AI, Bar-Ilan CS 89-570).

AI / Online Sources Disclosure:
- Used an AI coding assistant (Google Antigravity / Gemini) to design,
  mathematically verify admissibility of, implement, and optimize the state
  representation, safe pruning rules, graph precomputations, and admissible A*
  heuristic in ex1.py.
"""

from collections import deque
import heapq
import math

import ex1_check
import search

id = ["212535660"]
_INF = 10**9


def _components(adj):
    """Return (comp_of, num_comps) for an undirected adjacency sequence."""
    n, comp, nc = len(adj), [-1] * len(adj), 0
    for s in range(n):
        if comp[s] == -1:
            comp[s], q = nc, deque([s])
            while q:
                for v in adj[q.popleft()]:
                    if comp[v] == -1:
                        comp[v] = nc
                        q.append(v)
            nc += 1
    return tuple(comp), nc


def _apsp_bfs(adj):
    """All-pairs unweighted shortest paths via BFS."""
    n, out = len(adj), []
    for s in range(n):
        d, q = [_INF] * n, deque([s])
        d[s] = 0
        while q:
            u = q.popleft()
            du = d[u] + 1
            for v in adj[u]:
                if d[v] == _INF:
                    d[v] = du
                    q.append(v)
        out.append(tuple(d))
    return tuple(out)


def _pack_lb(heavy_d, min_hw, light_wd, total_wd, cap):
    """Exact heavy+light bin-packing lower bound on truck steps."""
    cm1 = cap - 1
    lb = (total_wd + cm1) // cap if total_wd > 0 else 0
    if heavy_d > 0:
        rem = light_wd - (cap - min_hw) * heavy_d
        cand = heavy_d + ((rem + cm1) // cap if rem > 0 else 0)
        if cand > lb:
            lb = cand
    return lb


def _flux_lb(w_ab, w_ba, h_ab, h_ba, need_ab, need_ba, m_a, m_b, c_a, c_b, cap):
    """Minimum directed truck crossings (r_ab, r_ba) across a 2-sided cut."""
    cm1 = cap - 1
    kab = (w_ab + cm1) // cap if w_ab > 0 else 0
    if h_ab > kab:
        kab = h_ab
    if need_ab and kab < 1:
        kab = 1
    kba = (w_ba + cm1) // cap if w_ba > 0 else 0
    if h_ba > kba:
        kba = h_ba
    if need_ba and kba < 1:
        kba = 1
    rab = kab
    if kba - m_b > rab:
        rab = kba - m_b
    if w_ba > c_b:
        cw = (w_ba - c_b + cm1) // cap
        if cw > rab:
            rab = cw
    rba = kba
    if kab - m_a > rba:
        rba = kab - m_a
    if w_ab > c_a:
        cw = (w_ab - c_a + cm1) // cap
        if cw > rba:
            rba = cw
    return rab, rba


def _mst_cost(req, dist_mat, start_rows):
    """Prim's MST on metric closure dist_mat over req rooted at start_rows."""
    m = len(req)
    if m == 0:
        return 0
    min_e = [_INF] * m
    for row in start_rows:
        for i in range(m):
            d = row[req[i]]
            if d < min_e[i]:
                min_e[i] = d
    used, total = [False] * m, 0
    for _ in range(m):
        bi, bw = -1, _INF
        for i in range(m):
            if not used[i] and min_e[i] < bw:
                bw, bi = min_e[i], i
        if bi == -1:
            break
        used[bi] = True
        total += bw
        urow = dist_mat[req[bi]]
        for i in range(m):
            if not used[i] and urow[req[i]] < min_e[i]:
                min_e[i] = urow[req[i]]
    return total


class LogisticsProblem(search.Problem):
    """Optimal A* formulation for the Island Logistics planning domain."""

    def __init__(self, initial):
        # 1. Static map topology & entity metadata
        n = initial["Locations"]
        self.num_locations = n
        adj_s = [set() for _ in range(n)]
        for u, v in initial["Roads"]:
            if u != v:
                adj_s[u].add(v)
                adj_s[v].add(u)
        raw_roads = [tuple(sorted(adj_s[i])) for i in range(n)]

        ports = set(initial["Ports"])
        self.is_port = tuple(i in ports for i in range(n))
        self.truck_ids = tuple(sorted(initial["Trucks"]))
        self.ferry_ids = tuple(sorted(initial["Ferries"]))
        self.pkg_ids = tuple(sorted(initial["Packages"]))
        self.num_trucks, self.num_ferries, self.num_pkgs = (
            len(self.truck_ids), len(self.ferry_ids), len(self.pkg_ids)
        )
        self.truck_caps = tuple(initial["Trucks"][t][1] for t in self.truck_ids)
        self.max_truck_cap = max(self.truck_caps, default=0)
        self.ferry_caps = tuple(initial["Ferries"][f][2] for f in self.ferry_ids)
        self.ferry_served_ports = tuple(tuple(sorted(set(initial["Ferries"][f][1]))) for f in self.ferry_ids)
        self.pkg_weights = tuple(initial["Packages"][p][1] for p in self.pkg_ids)
        self.pkg_goals = tuple(initial["Packages"][p][2] for p in self.pkg_ids)
        init_t = tuple(initial["Trucks"][t][0] for t in self.truck_ids)
        init_f = tuple(initial["Ferries"][f][0] for f in self.ferry_ids)
        init_p = tuple(initial["Packages"][p][0] for p in self.pkg_ids)

        # Subset-sum effective capacities (for h_astar ONLY)
        if self.max_truck_cap > 0 and self.num_pkgs > 0:
            lmask, reach = (1 << (self.max_truck_cap + 1)) - 1, 1
            for w in self.pkg_weights:
                if 0 < w <= self.max_truck_cap:
                    reach |= (reach << w) & lmask
            self.eff_truck_caps = tuple(
                (reach & ((1 << (c + 1)) - 1)).bit_length() - 1
                if (reach & ((1 << (c + 1)) - 1)) > 1 else 0
                for c in self.truck_caps
            )
        else:
            self.eff_truck_caps = self.truck_caps
        self.max_eff_truck_cap = max(self.eff_truck_caps, default=0)
        self.init_w_gcd = math.gcd(*self.pkg_weights) if self.pkg_weights else 0
        self.has_mixed_weights = len(set(self.pkg_weights)) > 1
        self._gcd_cap_cache = {}

        # 2. Safe static dead-end, dominated-port & corridor analysis
        rel = [False] * n
        for loc in init_t + init_p + self.pkg_goals:
            rel[loc] = True
        rf_raw = [set(raw_roads[u]) for u in range(n)]
        for fi in range(self.num_ferries):
            if self.ferry_caps[fi] > 0:
                sp = self.ferry_served_ports[fi]
                for u in sp:
                    rf_raw[u].update(v for v in sp if v != u)

        dead = self._find_dead_locs(n, rf_raw, rel)
        self.dead_loc, self.has_dead_locs = tuple(dead), any(dead)
        self.roads = tuple(tuple(v for v in raw_roads[u] if not dead[v]) if not dead[u] else () for u in range(n))

        active_f, active_served, f_at_p = [False] * self.num_ferries, [], [[] for _ in range(n)]
        for fi in range(self.num_ferries):
            nd = tuple(p for p in self.ferry_served_ports[fi] if not dead[p])
            if self.ferry_caps[fi] > 0 and len(nd) >= 2:
                active_f[fi] = True
                active_served.append(nd)
                for p in nd:
                    f_at_p[p].append(fi)
            else:
                active_served.append(())

        no_enter = list(dead)
        for v in range(n):
            if not no_enter[v] and not rel[v] and not self.roads[v]:
                fl = f_at_p[v]
                if not fl:
                    no_enter[v] = True
                else:
                    common = set(active_served[fl[0]])
                    for fi in fl[1:]:
                        common.intersection_update(active_served[fi])
                    common.discard(v)
                    if any(not no_enter[q] for q in common):
                        no_enter[v] = True

        self.active_ferry = tuple(active_f)
        self.has_inactive_ferries = not all(active_f)
        self.active_ferry_indices = tuple(fi for fi in range(self.num_ferries) if active_f[fi])
        self.ferry_active_targets = tuple(tuple(p for p in active_served[fi] if not no_enter[p]) if active_f[fi] else () for fi in range(self.num_ferries))
        self.pure_corridor = tuple((not rel[v]) and (not self.is_port[v]) and len(self.roads[v]) == 2 for v in range(n))
        self.nonport_leaf = tuple((not self.is_port[v]) and len(self.roads[v]) == 1 for v in range(n))
        self.no_unload_loc = tuple(self.pure_corridor[v] or self.nonport_leaf[v] for v in range(n))

        # 3. Symmetry groups, capability tiers & pre-formatted action strings
        self.prev_sym_truck = tuple(tuple(t1 for t1 in range(ti) if self.truck_caps[t1] == self.truck_caps[ti]) for ti in range(self.num_trucks))
        self.prev_sym_ferry = tuple(
            tuple(f1 for f1 in range(fi) if active_f[f1] and active_f[fi] and self.ferry_caps[f1] == self.ferry_caps[fi] and self.ferry_served_ports[f1] == self.ferry_served_ports[fi])
            for fi in range(self.num_ferries)
        )
        self.prev_sym_pkg = tuple(tuple(p1 for p1 in range(pi) if self.pkg_weights[p1] == self.pkg_weights[pi] and self.pkg_goals[p1] == self.pkg_goals[pi]) for pi in range(self.num_pkgs))
        self.capable_trucks = tuple(tuple(ti for ti in range(self.num_trucks) if self.truck_caps[ti] >= self.pkg_weights[pi]) for pi in range(self.num_pkgs))

        excl_t, tiers = [[] for _ in range(self.num_trucks)], {}
        for pi in range(self.num_pkgs):
            ct = self.capable_trucks[pi]
            if len(ct) == 1:
                excl_t[ct[0]].append(pi)
            elif 2 <= len(ct) < self.num_trucks:
                tiers.setdefault(ct, []).append(pi)
        self.excl_pkgs_by_truck = tuple((ti, tuple(ps)) for ti, ps in enumerate(excl_t) if ps)
        self.multi_truck_tiers = tuple((ct, tuple(ps)) for ct, ps in tiers.items())

        self._load_strs = tuple(tuple(f"LOAD{{{p},{t}}}" for t in self.truck_ids) for p in self.pkg_ids)
        self._unload_strs = tuple(tuple(f"UNLOAD{{{p},{t}}}" for t in self.truck_ids) for p in self.pkg_ids)
        self._board_strs = tuple(tuple(f"BOARD{{{t},{f}}}" for f in self.ferry_ids) for t in self.truck_ids)
        self._disembark_strs = tuple(tuple(f"DISEMBARK{{{t},{f}}}" for f in self.ferry_ids) for t in self.truck_ids)
        self._drive_strs = tuple({(u, v): f"DRIVE{{{tid},{u},{v}}}" for u in range(n) for v in self.roads[u]} for tid in self.truck_ids)
        self._sail_strs = tuple(
            {(u, v): f"SAIL{{{self.ferry_ids[fi]},{u},{v}}}" for u in self.ferry_served_ports[fi] for v in self.ferry_active_targets[fi] if u != v}
            for fi in range(self.num_ferries)
        )

        # 4. Connected components of active G_rf (decompose only when >= 2 comps have packages)
        rf_adj = [set(self.roads[u]) for u in range(n)]
        for fi in self.active_ferry_indices:
            for u in active_served[fi]:
                rf_adj[u].update(v for v in active_served[fi] if v != u)
        self._rf_adj = tuple(tuple(sorted(rf_adj[u])) for u in range(n))
        self.comp_of, self.num_comps = _components(self._rf_adj)
        self.comp_trucks = tuple(tuple(ti for ti in range(self.num_trucks) if self.comp_of[init_t[ti]] == c) for c in range(self.num_comps))
        self.comp_ferries = tuple(tuple(fi for fi in self.active_ferry_indices if self.comp_of[init_f[fi]] == c) for c in range(self.num_comps))
        self.comp_pkgs = tuple(tuple(pi for pi in range(self.num_pkgs) if self.comp_of[init_p[pi]] == c) for c in range(self.num_comps))
        self.use_comp_decomp = (
            sum(1 for cp in self.comp_pkgs if cp) >= 2
            and all(self.comp_of[init_p[pi]] == self.comp_of[self.pkg_goals[pi]] for pi in range(self.num_pkgs))
        )

        # 5. All-pairs shortest paths (full=5, no-sail=2) + on-ferry tables
        self.dist_full, self.dist_no_sail = self._dijkstra(5), self._dijkstra(2)
        f_full, f_ns = [], []
        for fi in range(self.num_ferries):
            served, ptab, rns = self.ferry_served_ports[fi], {}, [_INF] * n
            for cp in served:
                dc = self.dist_full[cp]
                row = [1 + dc[t] if dc[t] < _INF else _INF for t in range(n)]
                for op in served:
                    if op != cp:
                        do = self.dist_full[op]
                        for t in range(n):
                            if do[t] < _INF and 4 + do[t] < row[t]:
                                row[t] = 4 + do[t]
                ptab[cp] = tuple(row)
                dq = self.dist_no_sail[cp]
                for t in range(n):
                    if dq[t] < _INF and 1 + dq[t] < rns[t]:
                        rns[t] = 1 + dq[t]
            f_full.append(ptab)
            f_ns.append(tuple(rns))
        self.ferry_full_dist, self.ferry_disembark_no_sail = tuple(f_full), tuple(f_ns)

        # 6. Road-only islands, inter-island ferry graph, bridges & contracted non-bridge metric
        self.island_of, self.num_islands = _components(self.roads)
        self.pkg_goal_islands = tuple(self.island_of[g] for g in self.pkg_goals)
        self.road_dist = _apsp_bfs(self.roads)

        isl_ports, isl_all_f = [set() for _ in range(self.num_islands)], [set() for _ in range(self.num_islands)]
        for fi in self.active_ferry_indices:
            for p in active_served[fi]:
                isl = self.island_of[p]
                isl_ports[isl].add(p)
                isl_all_f[isl].add(fi)
        self.isl_sole_ferry = tuple(next(iter(fs)) if len(fs) == 1 else -1 for fs in isl_all_f)
        self.dist_to_any_active_port = tuple(min((self.road_dist[loc][p] for p in isl_ports[self.island_of[loc]]), default=_INF) for loc in range(n))
        self.road_dist_free_ferry = tuple(
            tuple(_INF if self.island_of[u] != self.island_of[v] else min(self.road_dist[u][v], self.dist_to_any_active_port[u] + self.dist_to_any_active_port[v]) for v in range(n))
            for u in range(n)
        )

        eff_desc = sorted(self.eff_truck_caps, reverse=True)
        self.max_ferry_weight = tuple(sum(eff_desc[: min(self.ferry_caps[fi], self.num_trucks)]) for fi in range(self.num_ferries))
        isl_adj = [set() for _ in range(self.num_islands)]
        isl_fl, isl_intra, isl_ip, inter_f = [[] for _ in range(self.num_islands)], [False] * self.num_islands, [set() for _ in range(self.num_islands)], []
        for fi in self.active_ferry_indices:
            by_isl = {}
            for p in active_served[fi]:
                by_isl.setdefault(self.island_of[p], []).append(p)
            for isl, plist in by_isl.items():
                if len(plist) >= 2:
                    isl_intra[isl] = True
            s_isls = sorted(by_isl)
            if len(s_isls) >= 2:
                inter_f.append(fi)
                for isl in s_isls:
                    isl_fl[isl].append(fi)
                    isl_ip[isl].update(by_isl[isl])
                for i in range(len(s_isls)):
                    for j in range(i + 1, len(s_isls)):
                        isl_adj[s_isls[i]].add(s_isls[j])
                        isl_adj[s_isls[j]].add(s_isls[i])

        self.inter_island_ferries = tuple(inter_f)
        self.island_ferries = tuple(tuple(fl) for fl in isl_fl)
        self.active_inter_islands = tuple(i for i in range(self.num_islands) if self.island_ferries[i])
        self.island_has_intra_ferry = tuple(isl_intra)
        self.max_island_sail_weight = tuple(max((self.max_ferry_weight[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
        self.max_island_ferry_truck_cap = tuple(max((self.ferry_caps[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
        self.has_inter_island_ferries = bool(inter_f)
        self.max_global_ferry_weight = max((self.max_ferry_weight[fi] for fi in inter_f), default=0)
        self.max_inter_ferry_truck_cap = max((self.ferry_caps[fi] for fi in inter_f), default=0)
        self.dist_to_inter_port = tuple(min((self.road_dist[loc][p] for p in isl_ip[self.island_of[loc]]), default=_INF) for loc in range(n))
        self.min_sails = _apsp_bfs(tuple(tuple(s) for s in isl_adj))

        self._precompute_bridges_and_nb(active_served)
        self._precompute_cut_ferries(active_served)
        self.all_inter_ferries_are_cuts = len(self.cut_ferries) == len(self.inter_island_ferries)
        self._h_cache, self._excl_tsp_cache = {}, {}
        search.Problem.__init__(self, (init_t, init_f, init_p))

    @staticmethod
    def _find_dead_locs(n, rf_raw, rel):
        dead, rel_nodes = [False] * n, [v for v in range(n) if rel[v]]
        if not rel_nodes:
            return dead
        seen, q = [False] * n, deque(rel_nodes)
        for v in rel_nodes:
            seen[v] = True
        while q:
            for y in rf_raw[q.popleft()]:
                if not seen[y]:
                    seen[y] = True
                    q.append(y)
        for v in range(n):
            if not seen[v]:
                dead[v] = True
        for u in range(n):
            if dead[u]:
                continue
            vis = [False] * n
            vis[u] = True
            for s in rf_raw[u]:
                if vis[s] or dead[s]:
                    continue
                comp, has_r, q = [], False, deque([s])
                vis[s] = True
                while q:
                    x = q.popleft()
                    comp.append(x)
                    if rel[x]:
                        has_r = True
                    for y in rf_raw[x]:
                        if not vis[y] and not dead[y]:
                            vis[y] = True
                            q.append(y)
                if not has_r:
                    for x in comp:
                        dead[x] = True
        return dead

    def _dijkstra(self, ferry_weight):
        n = self.num_locations
        adj_m = [{v: 1 for v in self.roads[u]} for u in range(n)]
        for fi in self.active_ferry_indices:
            sp = self.ferry_served_ports[fi]
            for u in sp:
                if not self.dead_loc[u]:
                    row = adj_m[u]
                    for v in sp:
                        if u != v and not self.dead_loc[v] and ferry_weight < row.get(v, _INF):
                            row[v] = ferry_weight
        adj, out = [tuple(m.items()) for m in adj_m], []
        for s in range(n):
            d, pq = [_INF] * n, [(0, s)]
            d[s] = 0
            while pq:
                du, u = heapq.heappop(pq)
                if du > d[u]:
                    continue
                for v, w in adj[u]:
                    if du + w < d[v]:
                        d[v] = du + w
                        heapq.heappush(pq, (du + w, v))
            out.append(tuple(d))
        return tuple(out)

    def _precompute_bridges_and_nb(self, active_served):
        """Precompute compressed G_rf road bridges and contracted 0-1 non-bridge metric."""
        n, rf_adj, comp_of = self.num_locations, self._rf_adj, self.comp_of
        road_edges = [(u, v) for u in range(n) for v in self.roads[u] if u < v]
        bridges, bset, e2b, isl_hb = [], set(), {}, [False] * self.num_islands
        for u, v in road_edges:
            if any(u in active_served[fi] and v in active_served[fi] for fi in self.active_ferry_indices):
                continue
            vis, q = [False] * n, deque([u])
            vis[u] = True
            while q:
                x = q.popleft()
                for y in rf_adj[x]:
                    if not vis[y] and not ((x == u and y == v) or (x == v and y == u)):
                        vis[y] = True
                        q.append(y)
            if not vis[v]:
                cid = comp_of[u]
                side = tuple(2 if comp_of[loc] != cid else (0 if vis[loc] else 1) for loc in range(n))
                e2b[(u, v)] = e2b[(v, u)] = len(bridges)
                bridges.append((u, v, side, cid))
                bset.update(((u, v), (v, u)))
                isl_hb[self.island_of[u]] = True
        self.isl_has_bridge = tuple(isl_hb)

        used, chains, pc = [False] * len(bridges), [], self.pure_corridor
        for bi, (u, v, _, cid) in enumerate(bridges):
            if used[bi]:
                continue
            ends = []
            for start, prev in ((u, v), (v, u)):
                seg, cur, pr = [start], start, prev
                while pc[cur]:
                    nxt = self.roads[cur][0] if self.roads[cur][1] == pr else self.roads[cur][1]
                    nbi = e2b.get((cur, nxt))
                    if nbi is None or used[nbi]:
                        break
                    seg.append(nxt)
                    pr, cur = cur, nxt
                ends.append(seg)
            path = ends[0][::-1] + ends[1]
            int_mask, c_sides = 0, []
            for x in path[1:-1]:
                int_mask |= 1 << x
            for i in range(len(path) - 1):
                eb = e2b[(path[i], path[i + 1])]
                used[eb] = True
                c_sides.append(bridges[eb][2])
            chains.append((cid, int_mask, tuple(path), tuple(c_sides)))

        self.bridge_chains = tuple(chains)
        self.has_non_bridge_roads = len(bridges) < len(road_edges)
        self.is_pure_road_tree = (not self.active_ferry_indices) and (not self.has_non_bridge_roads)
        if not self.has_non_bridge_roads:
            self.nb_id = self.nb_dist = None
            return

        # Contract 0-weight edges (bridge roads + active ferries) into super-nodes
        z_adj, nb_edges = [set() for _ in range(n)], []
        for u, v in road_edges:
            if (u, v) in bset:
                z_adj[u].add(v)
                z_adj[v].add(u)
            else:
                nb_edges.append((u, v))
        for fi in self.active_ferry_indices:
            sp = self.ferry_served_ports[fi]
            for u in sp:
                z_adj[u].update(v for v in sp if v != u)
        nb_id, num_nb = _components(tuple(tuple(s) for s in z_adj))
        if num_nb <= 1:
            self.has_non_bridge_roads = False
            self.nb_id = self.nb_dist = None
            return
        nb_adj = [set() for _ in range(num_nb)]
        for u, v in nb_edges:
            a, b = nb_id[u], nb_id[v]
            if a != b:
                nb_adj[a].add(b)
                nb_adj[b].add(a)
        self.nb_id, self.nb_dist = nb_id, _apsp_bfs(tuple(tuple(s) for s in nb_adj))

    def _precompute_cut_ferries(self, active_served):
        """Find inter-island ferries whose removal disconnects the island graph."""
        ni, isl_of, cuts = self.num_islands, self.island_of, []
        for fi in self.inter_island_ferries:
            adj_wo = [set() for _ in range(ni)]
            for fj in self.inter_island_ferries:
                if fj != fi:
                    isls = sorted({isl_of[p] for p in active_served[fj]})
                    for i in range(len(isls)):
                        for j in range(i + 1, len(isls)):
                            adj_wo[isls[i]].add(isls[j])
                            adj_wo[isls[j]].add(isls[i])
            seen, masks = [False] * ni, []
            for s in sorted({isl_of[p] for p in active_served[fi]}):
                if not seen[s]:
                    m, q = 0, deque([s])
                    seen[s] = True
                    while q:
                        x = q.popleft()
                        m |= 1 << x
                        for y in adj_wo[x]:
                            if not seen[y]:
                                seen[y] = True
                                q.append(y)
                    masks.append(m)
            if len(masks) >= 2:
                cm = 0
                for m in masks:
                    cm |= m
                cuts.append((fi, tuple(tuple(bool((m >> i) & 1) for i in range(ni)) for m in masks), tuple(bool((cm >> i) & 1) for i in range(ni))))
        self.cut_ferries = tuple(cuts)

    def path_cost(self, c, state1, action, state2):
        """ Do not change this. Returns the cost of reaching state2 from state1 via action,
        given cost c to reach state1: SAIL costs 3, every other action costs 1"""
        return c + (3 if action.startswith("SAIL") else 1)

    def successor(self, state):
        """Generate legal (action_str, next_state) pairs with optimality-preserving pruning."""
        truck_locs, ferry_locs, pkg_locs = state
        num_trucks, roads, is_port = self.num_trucks, self.roads, self.is_port
        truck_caps, ferry_caps, f_targets = self.truck_caps, self.ferry_caps, self.ferry_active_targets
        pkg_w, pkg_g = self.pkg_weights, self.pkg_goals
        pure_cor, leaf_np, no_ul = self.pure_corridor, self.nonport_leaf, self.no_unload_loc
        prev_t, prev_f, prev_p = self.prev_sym_truck, self.prev_sym_ferry, self.prev_sym_pkg

        if self.use_comp_decomp:
            ac = -1
            for c in range(self.num_comps):
                for pi in self.comp_pkgs[c]:
                    if pkg_locs[pi] != pkg_g[pi]:
                        ac = c
                        break
                if ac != -1:
                    break
            if ac == -1:
                return []
            t_iter, f_iter, p_iter = self.comp_trucks[ac], self.comp_ferries[ac], self.comp_pkgs[ac]
        else:
            t_iter, f_iter, p_iter = range(num_trucks), self.active_ferry_indices, range(self.num_pkgs)

        # Forced canonical UNLOAD at goal + truck loads/counts
        t_loads, t_cnts = [0] * num_trucks, [0] * num_trucks
        for pi in p_iter:
            pl = pkg_locs[pi]
            if pl < 0:
                ti = -pl - 1
                tl = truck_locs[ti]
                if tl >= 0 and tl == pkg_g[pi]:
                    return [(self._unload_strs[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (tl,) + pkg_locs[pi + 1 :]))]
                t_loads[ti] += pkg_w[pi]
                t_cnts[ti] += 1

        # Ample-set A: pure empty corridor OR loaded truck at non-port leaf with no loadable pkg
        for ti in t_iter:
            tl = truck_locs[ti]
            if tl < 0:
                continue
            if pure_cor[tl] and tl not in pkg_locs:
                dm = self._drive_strs[ti]
                return [(dm[(tl, nxt)], (truck_locs[:ti] + (nxt,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)) for nxt in roads[tl]]
            if leaf_np[tl] and t_cnts[ti] > 0:
                rem, can_load = truck_caps[ti] - t_loads[ti], False
                for pi in p_iter:
                    if pkg_locs[pi] == tl and tl != pkg_g[pi] and pkg_w[pi] <= rem:
                        can_load = True
                        break
                if not can_load:
                    nxt = roads[tl][0]
                    return [(self._drive_strs[ti][(tl, nxt)], (truck_locs[:ti] + (nxt,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs))]

        # Ferry occupancy & Ample-set B: full ferry actions commute with other entities
        f_cnts, any_ab = [0] * self.num_ferries, False
        for ti in t_iter:
            if truck_locs[ti] < 0:
                f_cnts[-truck_locs[ti] - 1] += 1
                any_ab = True

        if any_ab:
            for fi in f_iter:
                if f_cnts[fi] == ferry_caps[fi] and f_cnts[fi] > 0:
                    cp, on_fi, res = ferry_locs[fi], -(fi + 1), []
                    for ti in t_iter:
                        if truck_locs[ti] != on_fi:
                            continue
                        if t_cnts[ti] == 0:
                            skip = False
                            for t1 in prev_t[ti]:
                                if truck_locs[t1] == on_fi and t_cnts[t1] == 0:
                                    skip = True
                                    break
                            if skip:
                                continue
                        res.append((self._disembark_strs[ti][fi], (truck_locs[:ti] + (cp,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                    sm = self._sail_strs[fi]
                    for tp in f_targets[fi]:
                        if tp != cp:
                            res.append((sm[(cp, tp)], (truck_locs, ferry_locs[:fi] + (tp,) + ferry_locs[fi + 1 :], pkg_locs)))
                    return res

        succs = []
        load_s, unload_s, board_s, disemb_s = self._load_strs, self._unload_strs, self._board_strs, self._disembark_strs
        drive_s, sail_s = self._drive_strs, self._sail_strs

        for ti in t_iter:
            tl = truck_locs[ti]
            if t_cnts[ti] == 0:
                skip = False
                for t1 in prev_t[ti]:
                    if truck_locs[t1] == tl and t_cnts[t1] == 0:
                        skip = True
                        break
                if skip:
                    continue
            if tl < 0:
                fi = -tl - 1
                cp = ferry_locs[fi]
                succs.append((disemb_s[ti][fi], (truck_locs[:ti] + (cp,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                continue

            dm = drive_s[ti]
            for nxt in roads[tl]:
                succs.append((dm[(tl, nxt)], (truck_locs[:ti] + (nxt,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))

            if is_port[tl]:
                for fi in f_iter:
                    if ferry_locs[fi] == tl and f_cnts[fi] < ferry_caps[fi]:
                        if f_cnts[fi] == 0:
                            skip = False
                            for f1 in prev_f[fi]:
                                if ferry_locs[f1] == tl and f_cnts[f1] == 0:
                                    skip = True
                                    break
                            if skip:
                                continue
                        succs.append((board_s[ti][fi], (truck_locs[:ti] + (-(fi + 1),) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))

            in_t, rem_cap, can_ul = -(ti + 1), truck_caps[ti] - t_loads[ti], not no_ul[tl]
            for pi in p_iter:
                pl = pkg_locs[pi]
                if pl == in_t and can_ul:
                    skip = False
                    for p1 in prev_p[pi]:
                        if pkg_locs[p1] == in_t:
                            skip = True
                            break
                    if not skip:
                        succs.append((unload_s[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (tl,) + pkg_locs[pi + 1 :])))
                elif pl == tl and tl != pkg_g[pi] and pkg_w[pi] <= rem_cap:
                    skip = False
                    for p1 in prev_p[pi]:
                        if pkg_locs[p1] == tl:
                            skip = True
                            break
                    if not skip:
                        succs.append((load_s[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (in_t,) + pkg_locs[pi + 1 :])))

        for fi in f_iter:
            cp, empty = ferry_locs[fi], f_cnts[fi] == 0
            if empty:
                skip = False
                for f1 in prev_f[fi]:
                    if ferry_locs[f1] == cp and f_cnts[f1] == 0:
                        skip = True
                        break
                if skip:
                    continue
            sm = sail_s[fi]
            for tp in f_targets[fi]:
                if tp != cp and (not empty or tp in truck_locs):
                    succs.append((sm[(cp, tp)], (truck_locs, ferry_locs[:fi] + (tp,) + ferry_locs[fi + 1 :], pkg_locs)))
        return succs

    def goal_test(self, state):
        return state[2] == self.pkg_goals

    def _excl_tsp_lb(self, start_key, start_row, pairs):
        """Exact infinite-capacity pickup-and-delivery DP for a sole capable truck (A_move)."""
        cache = self._excl_tsp_cache
        ckey = (start_key, pairs)
        hit = cache.get(ckey)
        if hit is not None:
            return hit

        df, k = self.dist_full, len(pairs)
        if k > 4:
            scored = [(start_row[gl] if pl < 0 else start_row[pl] + df[pl][gl], pl, gl) for pl, gl in pairs]
            scored.sort(key=lambda x: x[0] if x[0] < _INF else 0, reverse=True)
            pairs, k = tuple(sorted((pl, gl) for _, pl, gl in scored[:4])), 4

        init_pm = rem_ev = 0
        for i in range(k):
            if pairs[i][0] < 0:
                init_pm |= 1 << i
                rem_ev += 1
            else:
                rem_ev += 2

        layer = {}
        for i in range(k):
            bit = 1 << i
            picked = bool(init_pm & bit)
            loc = pairs[i][1] if picked else pairs[i][0]
            d = start_row[loc]
            if d < _INF:
                st = (init_pm, bit, loc) if picked else (init_pm | bit, 0, loc)
                if d < layer.get(st, _INF):
                    layer[st] = d

        for _ in range(rem_ev - 1):
            nxt = {}
            for (pm, dm, cur), cost in layer.items():
                d_row = df[cur]
                for i in range(k):
                    bit = 1 << i
                    if dm & bit:
                        continue
                    picked = bool(pm & bit)
                    loc = pairs[i][1] if picked else pairs[i][0]
                    d = d_row[loc]
                    if d < _INF:
                        nc = cost + d
                        st = (pm, dm | bit, loc) if picked else (pm | bit, dm, loc)
                        if nc < nxt.get(st, _INF):
                            nxt[st] = nc
            layer = nxt
            if not layer:
                break

        res = min(layer.values(), default=0)
        if res >= _INF:
            res = 0
        if len(cache) < 200000:
            cache[ckey] = res
        return res

    def _eval_cut_ferries(self, pkg_info, req_nodes, truck_locs, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw, h_nb):
        """Return (bd_cut_sum, sail_cut_sum, approach_trade_extra) across inter-island cut ferries."""
        num_trucks, isl_of, f_caps = self.num_trucks, self.island_of, self.ferry_caps
        half_cap = max_cap >> 1
        bd_cut = b7 = trade_extra = 0

        for fi, touched_in, in_comp in self.cut_ferries:
            cf, ft = max_fw[fi], f_caps[fi]
            if cf <= 0 or ft <= 0:
                continue
            cf_m1, p0 = cf - 1, ferry_locs[fi]
            f_isl = isl_of[p0]
            ab_c = 0
            for ti in range(num_trucks):
                if t_on_f[ti] == fi:
                    ab_c += 1
            two_w = len(touched_in) == 2
            sides = (touched_in[0],) if two_w else touched_in
            sof = sif = msf = best_bd = cur_so = cur_si = cur_sf = 0

            for in_h in sides:
                fi_in = in_h[f_isl]
                mh = mo = ch = co = 0
                mch = mco = -1
                for ti in range(num_trucks):
                    isl = t_isl[ti]
                    if not in_comp[isl]:
                        continue
                    ec = eff_caps[ti]
                    if in_h[isl]:
                        mh += 1
                        ch += ec
                        if ec > mch:
                            mch = ec
                    else:
                        mo += 1
                        co += ec
                        if ec > mco:
                            mco = ec
                woh = wih = hoh = hih = 0
                ni_h = no_h = False
                stay_w = None
                for _, pl, _, _, is_gnd, w, pi_s, gi_s, on_f in pkg_info:
                    if not in_comp[pi_s]:
                        continue
                    if in_h[pi_s]:
                        if not in_h[gi_s]:
                            woh += w
                            if w > half_cap:
                                hoh += 1
                        elif on_f == fi and fi_in:
                            if stay_w is None:
                                stay_w = [0] * num_trucks
                            stay_w[-pl - 1] += w
                        if is_gnd and w > mch:
                            ni_h = True
                    else:
                        if in_h[gi_s]:
                            wih += w
                            if w > half_cap:
                                hih += 1
                        elif on_f == fi and not fi_in:
                            if stay_w is None:
                                stay_w = [0] * num_trucks
                            stay_w[-pl - 1] += w
                        if is_gnd and w > mco:
                            no_h = True

                ro, ri = _flux_lb(woh, wih, hoh, hih, no_h, ni_h, mh, mo, ch, co, max_cap)
                soh = (woh + cf_m1) // cf if woh > 0 else 0
                if ro > 0 and (ro + ft - 1) // ft > soh:
                    soh = (ro + ft - 1) // ft
                sih = (wih + cf_m1) // cf if wih > 0 else 0
                if ri > 0 and (ri + ft - 1) // ft > sih:
                    sih = (ri + ft - 1) // ft

                if two_w:
                    sof = sif = soh + sih
                else:
                    sof += soh
                    sif += sih
                if soh > 0 or sih > 0:
                    if fi_in:
                        se = soh + 1 if (mh == 0 and soh > 0) else soh
                        sf = (se if se >= sih else sih) + (sih if sih >= se - 1 else se - 1)
                        cur_so, cur_si, cur_sf = soh, sih, sf
                    else:
                        se = sih + 1 if (mo == 0 and sih > 0) else sih
                        sf = (soh if soh >= se - 1 else se - 1) + (se if se >= soh else soh)
                        if two_w:
                            cur_so, cur_si, cur_sf = sih, soh, sf
                    if sf > msf:
                        msf = sf

                fc = ro if fi_in else ri
                if stay_w is None:
                    cbd = 2 * (ro + ri) - (ab_c if ab_c < fc else fc)
                else:
                    ab_stay, min_sw = 0, _INF
                    for sw in stay_w:
                        if sw > 0:
                            ab_stay += 1
                            if sw < min_sw:
                                min_sw = sw
                    ab_free = ab_c - ab_stay
                    bd_drop = 2 * (ro + ri) + ab_stay - (ab_free if ab_free < fc else fc)
                    if fi_in:
                        ro2, ri2 = _flux_lb(woh, wih + min_sw, hoh, hih, no_h, ni_h, mh, mo, ch, co, max_cap)
                        bd_carry = 2 * (ro2 + ri2) - (ab_c if ab_c < ro2 else ro2)
                    else:
                        ro2, ri2 = _flux_lb(woh + min_sw, wih, hoh, hih, no_h, ni_h, mh, mo, ch, co, max_cap)
                        bd_carry = 2 * (ro2 + ri2) - (ab_c if ab_c < ri2 else ri2)
                    cbd = bd_drop if bd_drop <= bd_carry else bd_carry
                if cbd > best_bd:
                    best_bd = cbd

            sails_f = sof if sof >= sif else sif
            if msf > sails_f:
                sails_f = msf

            # General docked cut-ferry zero-extra-sail trade-off on a sole-ferry non-bridge island:
            # Either fi executes >= sails_f + 1 sails (+3), or fi executes strictly sails_f
            # inter-island sails with 0 intra-island sails (forcing road drives on f_isl).
            # (When no grounded truck is on f_isl, se = soh + 1 above already added the empty sail.)
            if ab_c == 0 and cur_sf == sails_f and self.isl_sole_ferry[f_isl] == fi and not self.isl_has_bridge[f_isl]:
                rd = self.road_dist
                g_trucks = [tl for tl in truck_locs if tl >= 0 and isl_of[tl] == f_isl]
                if g_trucks:
                    if cur_so >= 1 and cur_so >= cur_si and p0 not in truck_locs:
                        d_row, d_min = rd[p0], _INF
                        for tl in g_trucks:
                            if d_row[tl] < d_min:
                                d_min = d_row[tl]
                        if d_min < _INF and d_min > h_nb:
                            tr = 3 if d_min - h_nb >= 3 else d_min - h_nb
                            if tr > trade_extra:
                                trade_extra = tr
                    # Zero incoming sails into f_isl (cur_si == 0 and cur_so <= 1):
                    # all required nodes & outgoing packages on f_isl must use road_dist only.
                    if cur_si == 0 and cur_so <= 1 and trade_extra < 3:
                        g_rows = [rd[tl] for tl in g_trucks]
                        isl_req = [v for v in req_nodes if isl_of[v] == f_isl]
                        if cur_so == 1 and p0 not in isl_req:
                            isl_req.append(p0)
                        best_rd = _mst_cost(isl_req, rd, g_rows) if isl_req else 0
                        if cur_so == 1:
                            d_p0 = rd[p0]
                            capable = self.capable_trucks
                            for pi, pl, _, cl, is_gnd, _, pi_s, gi_s, _ in pkg_info:
                                if pi_s != f_isl or gi_s == f_isl:
                                    continue
                                if is_gnd:
                                    dtf = d_p0[pl]
                                    if dtf < _INF:
                                        mp = _INF
                                        for ti in capable[pi]:
                                            tl = truck_locs[ti]
                                            if tl >= 0 and isl_of[tl] == f_isl and rd[tl][pl] < mp:
                                                mp = rd[tl][pl]
                                        if mp < _INF and mp + dtf > best_rd:
                                            best_rd = mp + dtf
                                else:
                                    dtf = d_p0[cl]
                                    if dtf < _INF and dtf > best_rd:
                                        best_rd = dtf
                        if best_rd > h_nb:
                            tr = 3 if best_rd - h_nb >= 3 else best_rd - h_nb
                            if tr > trade_extra:
                                trade_extra = tr

            bd_cut += best_bd
            b7 += sails_f
        return bd_cut, b7, trade_extra

    def _eval_island_ferries(self, pkg_info, req_nodes, truck_locs, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw, max_isl_sw, max_gfw, h_bridge, h_nb):
        """Return (h_bd, h_sail, h_trade) for maps with non-cut (cyclic) inter-island ferries."""
        ni, num_trucks = self.num_islands, self.num_trucks
        isl_of, isl_f, isl_ftcap, ms_tbl = self.island_of, self.island_ferries, self.max_island_ferry_truck_cap, self.min_sails
        capable, cap_m1, half_cap = self.capable_trucks, max_cap - 1, max_cap >> 1

        wg_o, hg_o, wng_i, hng_i = [0] * ni, [0] * ni, [0] * ni, [0] * ni
        mg_i, cg_i, max_gc = [0] * ni, [0] * ni, [-1] * ni
        mt_i, ct_i, max_tc = [0] * ni, [0] * ni, [-1] * ni
        tot_c = n_ab = 0
        for ti in range(num_trucks):
            ec, isl = eff_caps[ti], t_isl[ti]
            tot_c += ec
            if t_on_f[ti] < 0:
                mg_i[isl] += 1
                cg_i[isl] += ec
                if ec > max_gc[isl]:
                    max_gc[isl] = ec
            else:
                n_ab += 1
            mt_i[isl] += 1
            ct_i[isl] += ec
            if ec > max_tc[isl]:
                max_tc[isl] = ec

        str_g, str_i = [False] * ni, [False] * ni
        wo_i, wi_i, ho_i, hi_i = [0] * ni, [0] * ni, [0] * ni, [0] * ni
        bw = dw = bhd = dhd = tot_sw = h_sw = b4 = 0
        min_hsw = _INF
        for pi, _, _, _, is_gnd, w, pi_s, gi_s, on_f in pkg_info:
            is_h, ms = (1 if w > half_cap else 0), ms_tbl[pi_s][gi_s]
            if is_gnd:
                if w > max_gc[pi_s]:
                    str_g[pi_s] = True
                if w > max_tc[pi_s]:
                    str_i[pi_s] = True
            if on_f < 0:
                if pi_s != gi_s:
                    wg_o[pi_s] += w
                    hg_o[pi_s] += is_h
                    wng_i[gi_s] += w
                    hng_i[gi_s] += is_h
                    if ms < _INF:
                        bw += w * ms
                        dw += w * ms
                        if is_h:
                            bhd += ms
                            dhd += ms
            else:
                wng_i[gi_s] += w
                hng_i[gi_s] += is_h
                if ms < _INF:
                    if ms > 1:
                        bw += w * (ms - 1)
                        if is_h:
                            bhd += ms - 1
                    dm = ms if ms >= 1 else 1
                    dw += w * dm
                    if is_h:
                        dhd += dm
                else:
                    dw += w
                    if is_h:
                        dhd += 1
            if ms < _INF:
                tot_sw += w * ms
                if is_h and ms > 0:
                    h_sw += ms
                    if w < min_hsw:
                        min_hsw = w
                if is_gnd:
                    mps = _INF
                    for ti in capable[pi]:
                        ds = ms_tbl[t_isl[ti]][pi_s]
                        if ds < mps:
                            mps = ds
                    if mps < _INF and mps + ms > b4:
                        b4 = mps + ms
                elif ms > b4:
                    b4 = ms
            if pi_s != gi_s:
                wo_i[pi_s] += w
                ho_i[pi_s] += is_h
                wi_i[gi_s] += w
                hi_i[gi_s] += is_h

        b1 = d1 = sum_so = sum_si = sum_req_i = b3 = 0
        for isl in self.active_inter_islands:
            wgo, wng = wg_o[isl], wng_i[isl]
            bi = (wgo + cap_m1) // max_cap if wgo > 0 else 0
            if hg_o[isl] > bi:
                bi = hg_o[isl]
            b1 += bi
            di = (wng + cap_m1) // max_cap if wng > 0 else 0
            if hng_i[isl] > di:
                di = hng_i[isl]
            if str_g[isl] and di < 1:
                di = 1
            if bi - mg_i[isl] > di:
                di = bi - mg_i[isl]
            if wgo > cg_i[isl] and (wgo - cg_i[isl] + cap_m1) // max_cap > di:
                di = (wgo - cg_i[isl] + cap_m1) // max_cap
            d1 += di

            c_isl, ft = max_isl_sw[isl], isl_ftcap[isl]
            if c_isl <= 0 or ft <= 0:
                continue
            c_isl_m1, wo, wi = c_isl - 1, wo_i[isl], wi_i[isl]
            tout, tin = _flux_lb(wo, wi, ho_i[isl], hi_i[isl], False, str_i[isl], mt_i[isl], num_trucks - mt_i[isl], ct_i[isl], tot_c - ct_i[isl], max_cap)
            so = (wo + c_isl_m1) // c_isl if wo > 0 else 0
            if tout > 0 and (tout + ft - 1) // ft > so:
                so = (tout + ft - 1) // ft
            si = (wi + c_isl_m1) // c_isl if wi > 0 else 0
            if str_i[isl] and si < 1:
                si = 1
            if tin > 0 and (tin + ft - 1) // ft > si:
                si = (tin + ft - 1) // ft
            sum_so += so
            sum_si += si
            if so > 0 or si > 0:
                fl = isl_f[isl]
                mi = ci = co = 0
                for fi in fl:
                    fw = max_fw[fi]
                    if isl_of[ferry_locs[fi]] == isl:
                        mi += 1
                        ci += fw
                    else:
                        co += fw
                ro = so
                if si - (len(fl) - mi) > ro:
                    ro = si - (len(fl) - mi)
                if wi > co and (wi - co + c_isl_m1) // c_isl > ro:
                    ro = (wi - co + c_isl_m1) // c_isl
                ri = si
                if so - mi > ri:
                    ri = so - mi
                if wo > ci and (wo - ci + c_isl_m1) // c_isl > ri:
                    ri = (wo - ci + c_isl_m1) // c_isl
                sum_req_i += ri
                if ro + ri > b3:
                    b3 = ro + ri

        b2 = (bw + cap_m1) // max_cap if bw > 0 else 0
        if bhd > b2:
            b2 = bhd
        d2 = (dw + cap_m1) // max_cap if dw > 0 else 0
        if dhd > d2:
            d2 = dhd
        lb_d = d1 if d1 >= d2 else d2
        lb_b = b1 if b1 >= b2 else b2
        if lb_d - n_ab > lb_b:
            lb_b = lb_d - n_ab
        h_bd = lb_b + lb_d

        b7 = h_trade = 0
        if self.cut_ferries:
            bd_c, b7, tr_ex = self._eval_cut_ferries(pkg_info, req_nodes, truck_locs, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw, h_nb)
            if bd_c > h_bd:
                h_bd = bd_c
            if tr_ex > 0:
                h_trade = h_bridge + h_nb + h_bd + 3 * b7 + tr_ex

        # Global ton-sails + heavy-package sail bound (divided by max heavy trucks per sail)
        b5 = (tot_sw + max_gfw - 1) // max_gfw if tot_sw > 0 and max_gfw > 0 else 0
        if h_sw > 0 and self.max_inter_ferry_truck_cap > 0:
            cap_h = 0
            for ec in eff_caps:
                if ec >= min_hsw:
                    cap_h += 1
            kh = self.max_inter_ferry_truck_cap if self.max_inter_ferry_truck_cap < cap_h else cap_h
            if kh > 0 and (h_sw + kh - 1) // kh > b5:
                b5 = (h_sw + kh - 1) // kh

        vol = sum_so if sum_so >= sum_si else sum_si
        if b4 > vol:
            vol = b4
        if b5 > vol:
            vol = b5
        if vol > 0 and n_ab == 0:
            any_ft = False
            for fi in self.active_ferry_indices:
                if mt_i[isl_of[ferry_locs[fi]]] > 0:
                    any_ft = True
                    break
            if not any_ft:
                vol += 1
        ms_cnt = vol
        if sum_req_i > ms_cnt:
            ms_cnt = sum_req_i
        if b3 > ms_cnt:
            ms_cnt = b3
        if b7 > ms_cnt:
            ms_cnt = b7
        return h_bd, 3 * ms_cnt, h_trade

    def h_astar(self, node):
        """
        100% admissible heuristic over pairwise disjoint action sets:
          A_LU = {LOAD, UNLOAD}, A_drive = {DRIVE}, A_bd = {BOARD, DISEMBARK}, A_sail = {SAIL}.
          h_truck = max(h_mst, h_tier_mst, h_pack_truck, h_drive + h_bd)
          h_move  = max(h_single, h_excl, h_truck + h_sail, h_trade)
          return h_lu + h_move
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

        num_trucks, pkg_weights = self.num_trucks, self.pkg_weights
        dist_full, dist_ns = self.dist_full, self.dist_no_sail
        f_full, f_ns = self.ferry_full_dist, self.ferry_disembark_no_sail
        capable, island_of, goal_isls = self.capable_trucks, self.island_of, self.pkg_goal_islands

        # 1. h_load_unload + dynamic GCD effective capacities
        undeliv, h_lu = [], 0
        if self.has_mixed_weights:
            w_gcd, gcd = 0, math.gcd
            for pi in range(self.num_pkgs):
                pl = pkg_locs[pi]
                if pl != pkg_goals[pi]:
                    undeliv.append(pi)
                    w_gcd = gcd(w_gcd, pkg_weights[pi])
                    h_lu += 1 if pl < 0 else 2
        else:
            w_gcd = self.init_w_gcd
            for pi in range(self.num_pkgs):
                pl = pkg_locs[pi]
                if pl != pkg_goals[pi]:
                    undeliv.append(pi)
                    h_lu += 1 if pl < 0 else 2

        eff_caps = self.eff_truck_caps
        if w_gcd > self.init_w_gcd:
            entry = self._gcd_cap_cache.get(w_gcd)
            if entry is None:
                ec = tuple((c // w_gcd) * w_gcd for c in eff_caps)
                ed = sorted(ec, reverse=True)
                mfw = tuple(sum(ed[: min(self.ferry_caps[fi], num_trucks)]) for fi in range(self.num_ferries))
                misw = tuple(max((mfw[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
                entry = (ec, max(ec, default=0), mfw, misw, max((mfw[fi] for fi in self.inter_island_ferries), default=0))
                self._gcd_cap_cache[w_gcd] = entry
            eff_caps, max_cap, max_fw, max_isl_sw, max_gfw = entry
        else:
            max_cap, max_fw, max_isl_sw, max_gfw = (
                self.max_eff_truck_cap, self.max_ferry_weight,
                self.max_island_sail_weight, self.max_global_ferry_weight,
            )

        if num_trucks == 0 or max_cap <= 0:
            return h_lu
        if self.has_dead_locs or self.has_inactive_ferries:
            dl, af = self.dead_loc, self.active_ferry
            for tl in truck_locs:
                if (tl >= 0 and dl[tl]) or (tl < 0 and not af[-tl - 1]):
                    return h_lu
            for pi in undeliv:
                if pkg_locs[pi] >= 0 and dl[pkg_locs[pi]]:
                    return h_lu

        half_cap = max_cap >> 1

        # Extract truck & undelivered package metadata
        t_rep, t_on_f, t_isl, occ_mask = [0] * num_trucks, [-1] * num_trucks, [0] * num_trucks, 0
        for ti in range(num_trucks):
            tl = truck_locs[ti]
            if tl >= 0:
                t_rep[ti], t_isl[ti] = tl, island_of[tl]
                occ_mask |= 1 << tl
            else:
                fi = -tl - 1
                fp = ferry_locs[fi]
                t_on_f[ti], t_rep[ti], t_isl[ti] = fi, fp, island_of[fp]
                occ_mask |= 1 << fp

        pkg_info, req_set = [], set()
        for pi in undeliv:
            pl, gl, w, gi = pkg_locs[pi], pkg_goals[pi], pkg_weights[pi], goal_isls[pi]
            req_set.add(gl)
            if pl >= 0:
                occ_mask |= 1 << pl
                req_set.add(pl)
                pkg_info.append((pi, pl, gl, pl, True, w, island_of[pl], gi, -1))
            else:
                ti = -pl - 1
                pkg_info.append((pi, pl, gl, t_rep[ti], False, w, t_isl[ti], gi, t_on_f[ti]))
        req_nodes = list(req_set)

        # 2. h_single & Bound B: exclusive-truck heavy sum + exact DP (A_move)
        h_single = 0
        for pi, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
            if is_gnd:
                dd = dist_full[pl][gl]
                if dd < _INF:
                    mp = _INF
                    for ti in capable[pi]:
                        tl = truck_locs[ti]
                        dp = dist_full[tl][pl] if tl >= 0 else f_full[-tl - 1][ferry_locs[-tl - 1]][pl]
                        if dp < mp:
                            mp = dp
                    if mp < _INF and mp + dd > h_single:
                        h_single = mp + dd
            else:
                tl = truck_locs[-pl - 1]
                dd = dist_full[tl][gl] if tl >= 0 else f_full[-tl - 1][ferry_locs[-tl - 1]][gl]
                if dd < _INF and dd > h_single:
                    h_single = dd

        h_excl = 0
        for ti, excl_ps in self.excl_pkgs_by_truck:
            tl = truck_locs[ti]
            s_key, s_row = (tl, dist_full[tl]) if tl >= 0 else ((-(-tl - 1) - 1, ferry_locs[-tl - 1]), f_full[-tl - 1][ferry_locs[-tl - 1]])
            t_half = eff_caps[ti] >> 1
            h_sum, h_app, hold_h, h_ok, pset = 0, _INF, False, True, set()
            for pi in excl_ps:
                pl, gl = pkg_locs[pi], pkg_goals[pi]
                if pl == gl:
                    continue
                pset.add((-1 if pl < 0 else pl, gl))
                if pkg_weights[pi] > t_half:
                    if pl < 0:
                        hold_h, dh = True, s_row[gl]
                    else:
                        dh, da = dist_full[pl][gl], s_row[pl]
                        if da < h_app:
                            h_app = da
                    if dh >= _INF:
                        h_ok = False
                    else:
                        h_sum += dh
            if not pset:
                continue
            if h_ok and h_sum > 0:
                ch = h_sum + (0 if hold_h else (h_app if h_app < _INF else 0))
                if ch > h_excl:
                    h_excl = ch
            if len(pset) >= 2:
                ct = self._excl_tsp_lb(s_key, s_row, tuple(sorted(pset)))
                if ct > h_excl:
                    h_excl = ct

        # 3. Bound A (heavy+light packing) & MST on A_truck
        h_mst = h_tier_mst = h_pack_truck = 0
        if not self.is_pure_road_tree:
            if not self.all_inter_ferries_are_cuts:
                t_ns_rows = [dist_ns[tl] if tl >= 0 else f_ns[-tl - 1] for tl in truck_locs]
                h_mst = _mst_cost(req_nodes, dist_ns, t_ns_rows)
                for t_trks, t_ps in self.multi_truck_tiers:
                    t_req = set()
                    for pi in t_ps:
                        pl, gl = pkg_locs[pi], pkg_goals[pi]
                        if pl != gl:
                            t_req.add(gl)
                            if pl >= 0:
                                t_req.add(pl)
                    if t_req:
                        tm = _mst_cost(list(t_req), dist_ns, [t_ns_rows[ti] for ti in t_trks])
                        if tm > h_tier_mst:
                            h_tier_mst = tm
            hd, min_hw, lwd, twd = 0, _INF, 0, 0
            for _, _, gl, cl, is_gnd, w, _, _, on_f in pkg_info:
                d = dist_ns[cl][gl] if (is_gnd or on_f < 0) else f_ns[on_f][gl]
                if d < _INF:
                    twd += w * d
                    if w > half_cap:
                        hd += d
                        if w < min_hw:
                            min_hw = w
                    else:
                        lwd += w * d
            h_pack_truck = _pack_lb(hd, min_hw, lwd, twd, max_cap)

        # 4. Bound C: Disjoint A_drive (compressed road bridges + contracted non-bridge metric)
        h_bridge = 0
        if self.bridge_chains:
            comp_of = self.comp_of
            c_mcap = [0] * self.num_comps
            for ti in range(num_trucks):
                c = comp_of[t_rep[ti]]
                if eff_caps[ti] > c_mcap[c]:
                    c_mcap[c] = eff_caps[ti]
            for cid, int_mask, path, c_sides in self.bridge_chains:
                c_cap = c_mcap[cid]
                if c_cap <= 0:
                    continue
                c_half, any_int, n_ce, last_r = c_cap >> 1, bool(occ_mask & int_mask), len(c_sides), 0
                for idx in range(n_ce):
                    if idx == 0 or (any_int and ((occ_mask >> path[idx]) & 1)):
                        side = c_sides[idx]
                        mu = mv = cu = cv = 0
                        mcu = mcv = -1
                        for ti in range(num_trucks):
                            st = side[t_rep[ti]]
                            if st == 0:
                                ec = eff_caps[ti]
                                mu += 1
                                cu += ec
                                if ec > mcu:
                                    mcu = ec
                            elif st == 1:
                                ec = eff_caps[ti]
                                mv += 1
                                cv += ec
                                if ec > mcv:
                                    mcv = ec
                        wuv = wvu = huv = hvu = 0
                        nvu = nuv = False
                        for _, _, gl, cl, is_gnd, w, _, _, _ in pkg_info:
                            sp = side[cl]
                            if sp == 0:
                                if side[gl] == 1:
                                    wuv += w
                                    if w > c_half:
                                        huv += 1
                                if is_gnd and w > mcu:
                                    nvu = True
                            elif sp == 1:
                                if side[gl] == 0:
                                    wvu += w
                                    if w > c_half:
                                        hvu += 1
                                if is_gnd and w > mcv:
                                    nuv = True
                        if wuv or wvu or nvu or nuv:
                            ruv, rvu = _flux_lb(wuv, wvu, huv, hvu, nuv, nvu, mu, mv, cu, cv, c_cap)
                            last_r = ruv + rvu
                        else:
                            last_r = 0
                        if not any_int:
                            h_bridge += last_r * n_ce
                            break
                    h_bridge += last_r

        h_nb = h_rpack = 0
        if self.has_non_bridge_roads:
            nb_id, nb_dist = self.nb_id, self.nb_dist
            nb_req = list({nb_id[v] for v in req_nodes})
            nb_mst = _mst_cost(nb_req, nb_dist, [nb_dist[nb_id[loc]] for loc in t_rep])
            nhd, nmhw, nlwd, ntwd = 0, _INF, 0, 0
            for _, _, gl, cl, _, w, _, _, _ in pkg_info:
                d = nb_dist[nb_id[cl]][nb_id[gl]]
                if 0 < d < _INF:
                    ntwd += w * d
                    if w > half_cap:
                        nhd += d
                        if w < nmhw:
                            nmhw = w
                    else:
                        nlwd += w * d
            nb_p = _pack_lb(nhd, nmhw, nlwd, ntwd, max_cap)
            h_nb = nb_mst if nb_mst >= nb_p else nb_p

            if not self.all_inter_ferries_are_cuts:
                r_dist, r_ff = self.road_dist, self.road_dist_free_ferry
                d_any, d_int, intra = self.dist_to_any_active_port, self.dist_to_inter_port, self.island_has_intra_ferry
                rhd, rmhw, rlwd, rtwd = 0, _INF, 0, 0
                for _, _, gl, cl, _, w, pi_s, gi_s, on_f in pkg_info:
                    dr = 0
                    if pi_s == gi_s:
                        v = (r_ff[cl][gl] if intra[pi_s] else r_dist[cl][gl]) if on_f < 0 else d_any[gl]
                        if v < _INF:
                            dr = v
                    else:
                        if on_f < 0:
                            v = d_any[cl] if intra[pi_s] else d_int[cl]
                            if v < _INF:
                                dr += v
                        v = d_any[gl] if intra[gi_s] else d_int[gl]
                        if v < _INF:
                            dr += v
                    if dr > 0:
                        rtwd += w * dr
                        if w > half_cap:
                            rhd += dr
                            if w < rmhw:
                                rmhw = w
                        else:
                            rlwd += w * dr
                h_rpack = _pack_lb(rhd, rmhw, rlwd, rtwd, max_cap)

        h_drive = h_bridge + h_nb
        if h_rpack > h_drive:
            h_drive = h_rpack

        # 5. Bound C (cont.): h_bd (A_bd) & h_sail (A_sail)
        h_bd = h_sail = h_trade = 0
        if self.has_inter_island_ferries:
            if self.all_inter_ferries_are_cuts:
                h_bd, b7, tr_ex = self._eval_cut_ferries(pkg_info, req_nodes, truck_locs, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw, h_nb)
                h_sail = 3 * b7
                if tr_ex > 0:
                    h_trade = h_bridge + h_nb + h_bd + h_sail + tr_ex
            else:
                h_bd, h_sail, h_trade = self._eval_island_ferries(
                    pkg_info, req_nodes, truck_locs, ferry_locs, t_isl, t_on_f,
                    eff_caps, max_cap, max_fw, max_isl_sw, max_gfw, h_bridge, h_nb,
                )

        # 6. Final Admissible Combination
        h_truck = h_drive + h_bd
        if h_mst > h_truck:
            h_truck = h_mst
        if h_tier_mst > h_truck:
            h_truck = h_tier_mst
        if h_pack_truck > h_truck:
            h_truck = h_pack_truck

        h_move = h_truck + h_sail
        if h_single > h_move:
            h_move = h_single
        if h_excl > h_move:
            h_move = h_excl
        if h_trade > h_move:
            h_move = h_trade

        res = h_lu + h_move
        if len(h_cache) < 500000:
            h_cache[state] = res
        return res


def create_logistics_problem(game):
    """Create a logistics problem from the game dictionary."""
    return LogisticsProblem(game)


if __name__ == "__main__":
    ex1_check.main()
