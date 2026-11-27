"""
Island Logistics A* Solver (Assignment 1 - Intro to AI, Bar-Ilan CS 89-570).

AI / Online Sources Disclosure:
- Used an AI coding assistant (Google Antigravity / Gemini) to design,
  mathematically verify admissibility of, implement, and optimize the state
  representation, safe pruning / POR rules, graph precomputations, and
  admissible A* heuristic in ex1.py.
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
    if m == 1:
        v0, best = req[0], _INF
        for row in start_rows:
            if row[v0] < best:
                best = row[v0]
        return best if best < _INF else 0
    if m == 2:
        v0, v1, d0, d1 = req[0], req[1], _INF, _INF
        for row in start_rows:
            if row[v0] < d0:
                d0 = row[v0]
            if row[v1] < d1:
                d1 = row[v1]
        e01 = dist_mat[v0][v1]
        c_sep = d0 + d1 if (d0 < _INF and d1 < _INF) else _INF
        c_ch = (d0 if d0 < d1 else d1) + e01 if (e01 < _INF and (d0 < _INF or d1 < _INF)) else _INF
        best = c_sep if c_sep <= c_ch else c_ch
        return best if best < _INF else 0
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
        self.pkg_init = init_p

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
        self._gcd_cap_cache, self._mask_cap_cache = {}, {}

        # 2. Safe static dead-end, dominated-port & directed one-way corridor analysis
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
        init_f_ports = set(init_f)
        for v in range(n):
            if not no_enter[v] and not rel[v] and not self.roads[v] and v not in init_f_ports:
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
        self.ferry_active_targets = tuple(
            tuple(p for p in active_served[fi] if not no_enter[p]) if active_f[fi] else ()
            for fi in range(self.num_ferries)
        )
        self.ferry_is_two_port = tuple(active_f[fi] and len(self.ferry_active_targets[fi]) <= 2 for fi in range(self.num_ferries))
        self.pure_corridor = tuple((not rel[v]) and (not self.is_port[v]) and len(self.roads[v]) == 2 for v in range(n))
        self.nonport_leaf = tuple((not self.is_port[v]) and len(self.roads[v]) == 1 for v in range(n))
        self.no_unload_loc = tuple(self.pure_corridor[v] or self.nonport_leaf[v] for v in range(n))

        # Directed pure-corridor state codes (>= n) eliminate backward U-turns
        phys_loc, cor_code, cor_meta = list(range(n)), {}, []
        for v in range(n):
            if self.pure_corridor[v]:
                a, b = self.roads[v]
                for frm, to in ((a, b), (b, a)):
                    cor_code[(v, frm)] = len(phys_loc)
                    phys_loc.append(v)
                    cor_meta.append((v, to))
        self.phys_loc = tuple(phys_loc)
        self.has_corridors = len(phys_loc) > n
        cor_next = [0] * len(phys_loc)
        cor_drive_strs = [[None] * len(phys_loc) for _ in range(self.num_trucks)]
        for idx, (v, nxt) in enumerate(cor_meta):
            code = n + idx
            cor_next[code] = cor_code[(nxt, v)] if self.pure_corridor[nxt] else nxt
            for ti, tid in enumerate(self.truck_ids):
                cor_drive_strs[ti][code] = f"DRIVE{{{tid},{v},{nxt}}}"
        self.cor_next = tuple(cor_next)
        self._cor_drive_strs = tuple(tuple(row) for row in cor_drive_strs)
        self.road_moves = tuple(
            tuple((cor_code[(v, u)] if self.pure_corridor[v] else v, v) for v in self.roads[u])
            for u in range(n)
        )

        # 3. Symmetry groups, exclusive-truck pkgs & pre-formatted action strings
        self.prev_sym_truck = tuple(tuple(t1 for t1 in range(ti) if self.truck_caps[t1] == self.truck_caps[ti]) for ti in range(self.num_trucks))
        self.prev_sym_ferry = tuple(
            tuple(f1 for f1 in range(fi) if active_f[f1] and active_f[fi] and self.ferry_caps[f1] == self.ferry_caps[fi] and self.ferry_served_ports[f1] == self.ferry_served_ports[fi])
            for fi in range(self.num_ferries)
        )
        self.same_sym_ferries = tuple(
            tuple(fj for fj in self.active_ferry_indices if fj != fi and active_f[fi] and self.ferry_caps[fj] == self.ferry_caps[fi] and self.ferry_served_ports[fj] == self.ferry_served_ports[fi])
            for fi in range(self.num_ferries)
        )
        self.prev_sym_pkg = tuple(
            tuple(p1 for p1 in range(pi) if self.pkg_weights[p1] == self.pkg_weights[pi] and self.pkg_goals[p1] == self.pkg_goals[pi])
            for pi in range(self.num_pkgs)
        )
        self.capable_trucks = tuple(tuple(ti for ti in range(self.num_trucks) if self.truck_caps[ti] >= self.pkg_weights[pi]) for pi in range(self.num_pkgs))
        excl_t = [[] for _ in range(self.num_trucks)]
        for pi in range(self.num_pkgs):
            if len(self.capable_trucks[pi]) == 1:
                excl_t[self.capable_trucks[pi][0]].append(pi)
        self.excl_pkgs_by_truck = tuple((ti, tuple(ps)) for ti, ps in enumerate(excl_t) if ps)

        self._load_strs = tuple(tuple(f"LOAD{{{p},{t}}}" for t in self.truck_ids) for p in self.pkg_ids)
        self._unload_strs = tuple(tuple(f"UNLOAD{{{p},{t}}}" for t in self.truck_ids) for p in self.pkg_ids)
        self._board_strs = tuple(tuple(f"BOARD{{{t},{f}}}" for f in self.ferry_ids) for t in self.truck_ids)
        self._disembark_strs = tuple(tuple(f"DISEMBARK{{{t},{f}}}" for f in self.ferry_ids) for t in self.truck_ids)
        self._drive_strs = tuple({(u, v): f"DRIVE{{{tid},{u},{v}}}" for u in range(n) for v in self.roads[u]} for tid in self.truck_ids)
        self._sail_strs = tuple(
            {(u, v): f"SAIL{{{self.ferry_ids[fi]},{u},{v}}}" for u in self.ferry_served_ports[fi] for v in self.ferry_active_targets[fi] if u != v}
            for fi in range(self.num_ferries)
        )

        # 4. Connected components of active G_rf (decompose when >= 2 comps have packages)
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

        # 5. All-pairs shortest paths (full=5, no-sail=2) + on-ferry tables + single-pkg UB
        self.dist_full, self.dist_no_sail = self._dijkstra(5), self._dijkstra(2)
        f_full, f_ns, max_to = [], [], [0] * n
        for u in range(n):
            du = self.dist_full[u]
            for v in range(n):
                if du[v] < _INF and du[v] > max_to[v]:
                    max_to[v] = du[v]
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
                for t in range(n):
                    if row[t] < _INF and row[t] > max_to[t]:
                        max_to[t] = row[t]
                ptab[cp] = tuple(row)
                dq = self.dist_no_sail[cp]
                for t in range(n):
                    if dq[t] < _INF and 1 + dq[t] < rns[t]:
                        rns[t] = 1 + dq[t]
            f_full.append(ptab)
            f_ns.append(tuple(rns))
        self.ferry_full_dist, self.ferry_disembark_no_sail = tuple(f_full), tuple(f_ns)
        self.max_to_loc = tuple(max_to)
        self.max_single_ub = max((max_to[u] + max((d for d in self.dist_full[u] if d < _INF), default=0) for u in range(n)), default=0)

        # 6. Road-only islands, inter-island ferry graph, bridges & contracted non-bridge metric
        self.island_of, self.num_islands = _components(self.roads)
        self.pkg_goal_islands = tuple(self.island_of[g] for g in self.pkg_goals)

        eff_desc = sorted(self.eff_truck_caps, reverse=True)
        self.max_ferry_weight = tuple(sum(eff_desc[: min(self.ferry_caps[fi], self.num_trucks)]) for fi in range(self.num_ferries))
        isl_adj, isl_fl, inter_f = [set() for _ in range(self.num_islands)], [[] for _ in range(self.num_islands)], []
        for fi in self.active_ferry_indices:
            s_isls = sorted({self.island_of[p] for p in active_served[fi]})
            if len(s_isls) >= 2:
                inter_f.append(fi)
                for isl in s_isls:
                    isl_fl[isl].append(fi)
                for i in range(len(s_isls)):
                    for j in range(i + 1, len(s_isls)):
                        isl_adj[s_isls[i]].add(s_isls[j])
                        isl_adj[s_isls[j]].add(s_isls[i])

        self.inter_island_ferries = tuple(inter_f)
        self.island_ferries = tuple(tuple(fl) for fl in isl_fl)
        self.active_inter_islands = tuple(i for i in range(self.num_islands) if self.island_ferries[i])
        self.max_island_sail_weight = tuple(max((self.max_ferry_weight[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
        self.max_island_ferry_truck_cap = tuple(max((self.ferry_caps[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
        self.has_inter_island_ferries = bool(inter_f)
        self.max_global_ferry_weight = max((self.max_ferry_weight[fi] for fi in inter_f), default=0)
        self.max_inter_ferry_truck_cap = max((self.ferry_caps[fi] for fi in inter_f), default=0)
        self.min_sails = _apsp_bfs(tuple(tuple(s) for s in isl_adj))
        self.island_diam_one = all(d <= 1 or d >= _INF for row in self.min_sails for d in row)

        self._precompute_bridges_and_nb(active_served)
        self._precompute_cut_ferries(active_served)
        self.all_inter_ferries_are_cuts = len(self.cut_ferries) == len(self.inter_island_ferries)
        self.need_pack_truck = (not self.is_pure_road_tree) and not (
            self.island_diam_one and (not self.has_non_bridge_roads) and (not self.all_inter_ferries_are_cuts)
        )
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
        """Precompute compressed G_rf road bridges (oriented along path) & contracted nb metric."""
        n, rf_adj, comp_of = self.num_locations, self._rf_adj, self.comp_of
        road_edges = [(u, v) for u in range(n) for v in self.roads[u] if u < v]
        bridges, bset, e2b = [], set(), {}
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
            p_start = path[0]
            int_mask, c_sides = 0, []
            for x in path[1:-1]:
                int_mask |= 1 << x
            for i in range(len(path) - 1):
                eb = e2b[(path[i], path[i + 1])]
                used[eb] = True
                raw_s = bridges[eb][2]
                # Orient consistently so path[0..i] is on side 0 and path[i+1..L] is on side 1
                if raw_s[p_start] == 1:
                    raw_s = tuple(1 - x if x < 2 else 2 for x in raw_s)
                c_sides.append(raw_s)
            m0 = m1 = 0
            s_first, s_last = c_sides[0], c_sides[-1]
            for loc in range(n):
                if s_first[loc] == 0:
                    m0 |= 1 << loc
                if s_last[loc] == 1:
                    m1 |= 1 << loc
            chains.append((cid, int_mask, tuple(path), tuple(c_sides), m0, m1))

        self.bridge_chains = tuple(chains)
        self.has_non_bridge_roads = len(bridges) < len(road_edges)
        self.is_pure_road_tree = (not self.active_ferry_indices) and (not self.has_non_bridge_roads)
        if not self.has_non_bridge_roads:
            self.nb_id = self.nb_dist = None
            self.num_nb = 0
            return

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
            self.num_nb = 0
            return
        nb_adj = [set() for _ in range(num_nb)]
        for u, v in nb_edges:
            a, b = nb_id[u], nb_id[v]
            if a != b:
                nb_adj[a].add(b)
                nb_adj[b].add(a)
        self.nb_id, self.nb_dist, self.num_nb = nb_id, _apsp_bfs(tuple(tuple(s) for s in nb_adj)), num_nb

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
                cuts.append((
                    fi,
                    tuple(tuple(bool((m >> i) & 1) for i in range(ni)) for m in masks),
                    tuple(bool((cm >> i) & 1) for i in range(ni)),
                ))
        self.cut_ferries = tuple(cuts)

    def path_cost(self, c, state1, action, state2):
        """ Do not change this. Returns the cost of reaching state2 from state1 via action,
        given cost c to reach state1: SAIL costs 3, every other action costs 1"""
        return c + (3 if action.startswith("SAIL") else 1)

    def successor(self, state):
        """Generate legal (action_str, next_state) pairs with optimality-preserving POR & pruning."""
        truck_locs, ferry_locs, pkg_locs = state
        n, num_trucks, is_port = self.num_locations, self.num_trucks, self.is_port
        truck_caps, ferry_caps, f_targets = self.truck_caps, self.ferry_caps, self.ferry_active_targets
        pkg_w, pkg_g, pkg_init = self.pkg_weights, self.pkg_goals, self.pkg_init
        leaf_np, no_ul = self.nonport_leaf, self.no_unload_loc
        prev_t, prev_f, prev_p = self.prev_sym_truck, self.prev_sym_ferry, self.prev_sym_pkg
        road_moves = self.road_moves

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

        # 1. Forced canonical UNLOAD at goal + truck loads/counts + min undelivered weight
        t_loads, t_cnts, min_undeliv_w = [0] * num_trucks, [0] * num_trucks, _INF
        for pi in p_iter:
            pl = pkg_locs[pi]
            if pl != pkg_g[pi]:
                w = pkg_w[pi]
                if w < min_undeliv_w:
                    min_undeliv_w = w
                if pl < 0:
                    ti = -pl - 1
                    tl = truck_locs[ti]
                    if 0 <= tl < n and tl == pkg_g[pi]:
                        return [(self._unload_strs[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (tl,) + pkg_locs[pi + 1 :]))]
                    t_loads[ti] += w
                    t_cnts[ti] += 1

        # 2. Ample-set A1: One-way directed pure-corridor traversal (bf = 1, zero U-turns)
        if self.has_corridors:
            for ti in t_iter:
                tl = truck_locs[ti]
                if tl >= n:
                    nxt = self.cor_next[tl]
                    return [(self._cor_drive_strs[ti][tl], (truck_locs[:ti] + (nxt,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs))]

        # 3. Ample-set A2 (loaded solo truck at non-port leaf) & A3 (full loaded truck at non-port)
        load_s, unload_s, drive_s = self._load_strs, self._unload_strs, self._drive_strs
        for ti in t_iter:
            tl = truck_locs[ti]
            if tl < 0 or t_cnts[ti] == 0:
                continue
            if leaf_np[tl]:
                solo = True
                for tj in t_iter:
                    if tj != ti and truck_locs[tj] == tl:
                        solo = False
                        break
                if solo:
                    in_t, rem_cap, res = -(ti + 1), truck_caps[ti] - t_loads[ti], []
                    if rem_cap >= min_undeliv_w:
                        max_il = -1
                        for pi in p_iter:
                            if pkg_locs[pi] == in_t and pkg_init[pi] == tl and pi > max_il:
                                max_il = pi
                        for pi in p_iter:
                            if pkg_locs[pi] == tl and tl != pkg_g[pi] and pkg_w[pi] <= rem_cap:
                                if pkg_init[pi] == tl and pi < max_il:
                                    continue
                                skip = False
                                for p1 in prev_p[pi]:
                                    if pkg_locs[p1] == tl:
                                        skip = True
                                        break
                                if not skip:
                                    res.append((load_s[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (in_t,) + pkg_locs[pi + 1 :])))
                    nxt_code, nxt_v = road_moves[tl][0]
                    res.append((drive_s[ti][(tl, nxt_v)], (truck_locs[:ti] + (nxt_code,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                    return res
            if (not is_port[tl]) and (truck_caps[ti] - t_loads[ti] < min_undeliv_w):
                dm, res = drive_s[ti], []
                for nxt_code, nxt_v in road_moves[tl]:
                    res.append((dm[(tl, nxt_v)], (truck_locs[:ti] + (nxt_code,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                if not no_ul[tl]:
                    in_t = -(ti + 1)
                    for pi in p_iter:
                        if pkg_locs[pi] == in_t:
                            skip = False
                            for p1 in prev_p[pi]:
                                if pkg_locs[p1] == in_t:
                                    skip = True
                                    break
                            if not skip:
                                res.append((unload_s[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (tl,) + pkg_locs[pi + 1 :])))
                return res

        # 4. Ferry occupancy & Ample-set B: full ferry OR any non-empty 2-port ferry
        f_cnts, any_ab = [0] * self.num_ferries, False
        for ti in t_iter:
            if truck_locs[ti] < 0:
                f_cnts[-truck_locs[ti] - 1] += 1
                any_ab = True

        board_s, disemb_s, sail_s = self._board_strs, self._disembark_strs, self._sail_strs
        if any_ab:
            two_port = self.ferry_is_two_port
            for fi in f_iter:
                fc = f_cnts[fi]
                if fc > 0 and (fc == ferry_caps[fi] or two_port[fi]):
                    cp, on_fi, res, max_ab_ti = ferry_locs[fi], -(fi + 1), [], -1
                    for ti in t_iter:
                        if truck_locs[ti] != on_fi:
                            continue
                        if ti > max_ab_ti:
                            max_ab_ti = ti
                        if t_cnts[ti] == 0:
                            skip = False
                            for t1 in prev_t[ti]:
                                if truck_locs[t1] == on_fi and t_cnts[t1] == 0:
                                    skip = True
                                    break
                            if skip:
                                continue
                        res.append((disemb_s[ti][fi], (truck_locs[:ti] + (cp,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                    if fc < ferry_caps[fi]:
                        for ti in t_iter:
                            if truck_locs[ti] != cp or ti < max_ab_ti:
                                continue
                            if t_cnts[ti] == 0:
                                skip = False
                                for t1 in prev_t[ti]:
                                    if truck_locs[t1] == cp and t_cnts[t1] == 0:
                                        skip = True
                                        break
                                if skip:
                                    continue
                            res.append((board_s[ti][fi], (truck_locs[:ti] + (on_fi,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))
                    sm = sail_s[fi]
                    for tp in f_targets[fi]:
                        if tp != cp:
                            res.append((sm[(cp, tp)], (truck_locs, ferry_locs[:fi] + (tp,) + ferry_locs[fi + 1 :], pkg_locs)))
                    return res

        # 5. Normal expansion: symmetry skips, canonical multi-LOAD & identical empty-ferry saturation
        succs = []
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
            for nxt_code, nxt_v in road_moves[tl]:
                succs.append((dm[(tl, nxt_v)], (truck_locs[:ti] + (nxt_code,) + truck_locs[ti + 1 :], ferry_locs, pkg_locs)))

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

            in_t, rem_cap, can_ul, max_il = -(ti + 1), truck_caps[ti] - t_loads[ti], not no_ul[tl], -1
            if rem_cap >= min_undeliv_w:
                for pi in p_iter:
                    if pkg_locs[pi] == in_t and pkg_init[pi] == tl and pi > max_il:
                        max_il = pi
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
                    if pkg_init[pi] == tl and pi < max_il:
                        continue
                    skip = False
                    for p1 in prev_p[pi]:
                        if pkg_locs[p1] == tl:
                            skip = True
                            break
                    if not skip:
                        succs.append((load_s[pi][ti], (truck_locs, ferry_locs, pkg_locs[:pi] + (in_t,) + pkg_locs[pi + 1 :])))

        same_f = self.same_sym_ferries
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
            sm, peers = sail_s[fi], same_f[fi] if empty else ()
            for tp in f_targets[fi]:
                if tp != cp and (not empty or tp in truck_locs):
                    if peers:
                        avail = 0
                        for fj in peers:
                            if ferry_locs[fj] == tp and f_cnts[fj] == 0:
                                avail += ferry_caps[fj]
                        if avail > 0:
                            nt_tp = 0
                            for ti in t_iter:
                                if truck_locs[ti] == tp:
                                    nt_tp += 1
                            if avail >= nt_tp:
                                continue
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

    def _eval_cut_ferries(self, pkg_info, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw):
        """Return (bd_cut_sum, sail_cut_sum) across inter-island cut ferries."""
        num_trucks, isl_of, f_caps = self.num_trucks, self.island_of, self.ferry_caps
        half_cap, cap_m1 = max_cap >> 1, max_cap - 1
        bd_cut = b7 = 0

        for fi, touched_in, in_comp in self.cut_ferries:
            cf, ft = max_fw[fi], f_caps[fi]
            if cf <= 0 or ft <= 0:
                continue
            cf_m1 = cf - 1
            f_isl = isl_of[ferry_locs[fi]]
            ab_trucks = [ti for ti in range(num_trucks) if t_on_f[ti] == fi]
            ab_c = len(ab_trucks)
            two_w = len(touched_in) == 2
            sides = (touched_in[0],) if two_w else touched_in
            sof = sif = msf = best_bd = 0

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
                woh = wih = hoh = hih = w_gnd_cur = h_gnd_cur = ab_loaded_mask = 0
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
                            if fi_in:
                                if on_f != fi:
                                    w_gnd_cur += w
                                    if w > half_cap:
                                        h_gnd_cur += 1
                                else:
                                    ab_loaded_mask |= 1 << (-pl - 1)
                        elif on_f == fi and fi_in:
                            ti_p = -pl - 1
                            ab_loaded_mask |= 1 << ti_p
                            if stay_w is None:
                                stay_w = [0] * num_trucks
                            stay_w[ti_p] += w
                        if is_gnd and w > mch:
                            ni_h = True
                    else:
                        if in_h[gi_s]:
                            wih += w
                            if w > half_cap:
                                hih += 1
                            if not fi_in:
                                if on_f != fi:
                                    w_gnd_cur += w
                                    if w > half_cap:
                                        h_gnd_cur += 1
                                else:
                                    ab_loaded_mask |= 1 << (-pl - 1)
                        elif on_f == fi and not fi_in:
                            ti_p = -pl - 1
                            ab_loaded_mask |= 1 << ti_p
                            if stay_w is None:
                                stay_w = [0] * num_trucks
                            stay_w[ti_p] += w
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
                    else:
                        se = sih + 1 if (mo == 0 and sih > 0) else sih
                        sf = (soh if soh >= se - 1 else se - 1) + (se if se >= soh else soh)
                    if sf > msf:
                        msf = sf

                if ab_c == 0:
                    cbd = 2 * (ro + ri)
                else:
                    # Exact admissible split of aboard trucks into:
                    #   x = direct crossers without disembarking on current side
                    #   z = empty aboard trucks never disembarking (unavailable on current side)
                    #   d = ab_c - x - z trucks disembarking on current side first (+d)
                    k_gnd_cur = (w_gnd_cur + cap_m1) // max_cap if w_gnd_cur > 0 else 0
                    if h_gnd_cur > k_gnd_cur:
                        k_gnd_cur = h_gnd_cur
                    empty_caps = sorted(eff_caps[ti] for ti in ab_trucks if not ((ab_loaded_mask >> ti) & 1))
                    stay_vals = sorted(sw for sw in stay_w if sw > 0) if stay_w is not None else []
                    ab_empty, ab_stay, cbd = len(empty_caps), len(stay_vals), _INF
                    for z in range(ab_empty + 1):
                        cz, max_x = sum(empty_caps[:z]), ab_c - z
                        for x in range(max_x + 1):
                            k_carry = x - (max_x - ab_stay)
                            extra_opp = sum(stay_vals[:k_carry]) if k_carry > 0 else 0
                            if z == 0 and extra_opp == 0:
                                r_cur, r_opp = (ro, ri) if fi_in else (ri, ro)
                            elif fi_in:
                                r_cur, r_opp = _flux_lb(woh, wih + extra_opp, hoh, hih, no_h, ni_h, mh - z, mo, ch - cz, co, max_cap)
                            else:
                                r_opp, r_cur = _flux_lb(woh + extra_opp, wih, hoh, hih, no_h, ni_h, mh, mo - z, ch, co - cz, max_cap)
                            c_cur = x + k_gnd_cur
                            if r_cur > c_cur:
                                c_cur = r_cur
                            cand = (max_x - x) + 2 * (c_cur + r_opp) - x
                            if cand < cbd:
                                cbd = cand
                if cbd > best_bd:
                    best_bd = cbd

            sails_f = sof if sof >= sif else sif
            if msf > sails_f:
                sails_f = msf

            bd_cut += best_bd
            b7 += sails_f
        return bd_cut, b7

    def _eval_island_ferries(self, pkg_info, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw, max_isl_sw, max_gfw):
        """Return (h_bd, h_sail) for maps with non-cut (cyclic) inter-island ferries."""
        ni, num_trucks = self.num_islands, self.num_trucks
        isl_of, isl_f, isl_ftcap = self.island_of, self.island_ferries, self.max_island_ferry_truck_cap
        cap_m1, half_cap, diam_one = max_cap - 1, max_cap >> 1, self.island_diam_one

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
        ms_tbl, capable = (None, None) if diam_one else (self.min_sails, self.capable_trucks)
        for pi, _, _, _, is_gnd, w, pi_s, gi_s, on_f in pkg_info:
            is_h = 1 if w > half_cap else 0
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
            else:
                wng_i[gi_s] += w
                hng_i[gi_s] += is_h
            if pi_s != gi_s:
                wo_i[pi_s] += w
                ho_i[pi_s] += is_h
                wi_i[gi_s] += w
                hi_i[gi_s] += is_h
            if not diam_one:
                ms = ms_tbl[pi_s][gi_s]
                if on_f < 0:
                    if pi_s != gi_s and ms < _INF:
                        bw += w * ms
                        dw += w * ms
                        if is_h:
                            bhd += ms
                            dhd += ms
                else:
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
            if wgo > cg_i[isl]:
                cw = (wgo - cg_i[isl] + cap_m1) // max_cap
                if cw > di:
                    di = cw
            d1 += di

            c_isl, ft = max_isl_sw[isl], isl_ftcap[isl]
            if c_isl <= 0 or ft <= 0:
                continue
            c_isl_m1, wo, wi = c_isl - 1, wo_i[isl], wi_i[isl]
            # Inlined _flux_lb for island cut (need_ab=False, need_ba=str_i[isl])
            kab = (wo + cap_m1) // max_cap if wo > 0 else 0
            if ho_i[isl] > kab:
                kab = ho_i[isl]
            kba = (wi + cap_m1) // max_cap if wi > 0 else 0
            if hi_i[isl] > kba:
                kba = hi_i[isl]
            if str_i[isl] and kba < 1:
                kba = 1
            m_a, c_a = mt_i[isl], ct_i[isl]
            m_b, c_b = num_trucks - m_a, tot_c - c_a
            tout = kab if kab >= kba - m_b else kba - m_b
            if wi > c_b:
                cw = (wi - c_b + cap_m1) // max_cap
                if cw > tout:
                    tout = cw
            tin = kba if kba >= kab - m_a else kab - m_a
            if wo > c_a:
                cw = (wo - c_a + cap_m1) // max_cap
                if cw > tin:
                    tin = cw

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
                fl, mi, ci, co = isl_f[isl], 0, 0, 0
                for fi in fl:
                    fw = max_fw[fi]
                    if isl_of[ferry_locs[fi]] == isl:
                        mi += 1
                        ci += fw
                    else:
                        co += fw
                ro = so if so >= si - (len(fl) - mi) else si - (len(fl) - mi)
                if wi > co and (wi - co + c_isl_m1) // c_isl > ro:
                    ro = (wi - co + c_isl_m1) // c_isl
                ri = si if si >= so - mi else so - mi
                if wo > ci and (wo - ci + c_isl_m1) // c_isl > ri:
                    ri = (wo - ci + c_isl_m1) // c_isl
                sum_req_i += ri
                if ro + ri > b3:
                    b3 = ro + ri

        if diam_one:
            lb_d, lb_b = d1, b1
        else:
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

        b7 = 0
        if self.cut_ferries:
            bd_c, b7 = self._eval_cut_ferries(
                pkg_info, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw,
            )
            if bd_c > h_bd:
                h_bd = bd_c

        vol = sum_so if sum_so >= sum_si else sum_si
        if not diam_one:
            b5 = (tot_sw + max_gfw - 1) // max_gfw if tot_sw > 0 and max_gfw > 0 else 0
            if h_sw > 0 and self.max_inter_ferry_truck_cap > 0:
                cap_h = sum(1 for ec in eff_caps if ec >= min_hsw)
                kh = self.max_inter_ferry_truck_cap if self.max_inter_ferry_truck_cap < cap_h else cap_h
                if kh > 0 and (h_sw + kh - 1) // kh > b5:
                    b5 = (h_sw + kh - 1) // kh
            if b4 > vol:
                vol = b4
            if b5 > vol:
                vol = b5
        if vol > 0 and n_ab == 0:
            if not any(mt_i[isl_of[ferry_locs[fi]]] > 0 for fi in self.active_ferry_indices):
                vol += 1
        ms_cnt = vol
        if sum_req_i > ms_cnt:
            ms_cnt = sum_req_i
        if b3 > ms_cnt:
            ms_cnt = b3
        if b7 > ms_cnt:
            ms_cnt = b7
        return h_bd, 3 * ms_cnt

    @staticmethod
    def _bridge_cycle_extra(unit_regions, pkg_info):
        """
        Admissible lower bound on extra bridge-chain crossings forced by directed
        precedence cycles among pairwise-disjoint 0-truck unit-flux bridge regions.
        """
        k = len(unit_regions)
        adj = [0] * k
        for _, _, gl, cl, _, _, _, _, _ in pkg_info:
            cbit, gbit = 1 << cl, 1 << gl
            src = dst = -1
            for i in range(k):
                rm = unit_regions[i][0]
                if rm & cbit:
                    src = i
                    if dst != -1:
                        break
                if rm & gbit:
                    dst = i
                    if src != -1:
                        break
            if src != -1 and dst != -1 and src != dst and (unit_regions[src][0] & unit_regions[dst][0]) == 0:
                adj[src] |= 1 << dst

        used = extra = 0
        # 1. Extract chain-disjoint 2-cycles greedily (largest min-length first)
        pairs = []
        for i in range(k):
            ai = adj[i]
            if not ai:
                continue
            for j in range(i + 1, k):
                if ((ai >> j) & 1) and ((adj[j] >> i) & 1):
                    li, lj = unit_regions[i][1], unit_regions[j][1]
                    pairs.append((li if li <= lj else lj, i, j))
        if len(pairs) > 1:
            pairs.sort(reverse=True)
        for ml, i, j in pairs:
            if not ((used >> i) & 1) and not ((used >> j) & 1):
                used |= (1 << i) | (1 << j)
                extra += ml

        # 2. Extract any remaining disjoint cycles of length >= 3
        for start in range(k):
            if (used >> start) & 1 or not adj[start]:
                continue
            stack = [(start, 1 << start, unit_regions[start][0], unit_regions[start][1])]
            found = None
            while stack:
                u, vmask, lmask, min_l = stack.pop()
                au = adj[u]
                if ((au >> start) & 1) and u != start:
                    found = (vmask, min_l)
                    break
                for v in range(start + 1, k):
                    if ((au >> v) & 1) and not (((used | vmask) >> v) & 1):
                        rm_v = unit_regions[v][0]
                        if (lmask & rm_v) == 0:
                            lv = unit_regions[v][1]
                            stack.append((v, vmask | (1 << v), lmask | rm_v, lv if lv < min_l else min_l))
            if found is not None:
                used |= found[0]
                extra += found[1]
        return extra

    def h_astar(self, node):
        """
        100% admissible integer heuristic over pairwise disjoint action sets:
          A_LU = {LOAD, UNLOAD}, A_drive = {DRIVE}, A_bd = {BOARD, DISEMBARK}, A_sail = {SAIL}.
          h_truck = max(h_drive + h_bd, h_pack_truck)
          h_move  = max(h_truck + h_sail, h_excl, h_single)
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
        island_of, goal_isls, phys_loc = self.island_of, self.pkg_goal_islands, self.phys_loc

        # 1. h_load_unload + bitmask-cached dynamic GCD effective capacities
        undeliv, h_lu = [], 0
        if self.has_mixed_weights:
            umask = 0
            for pi in range(self.num_pkgs):
                pl = pkg_locs[pi]
                if pl != pkg_goals[pi]:
                    undeliv.append(pi)
                    umask |= 1 << pi
                    h_lu += 1 if pl < 0 else 2
            entry = self._mask_cap_cache.get(umask)
            if entry is None:
                w_gcd, gcd = 0, math.gcd
                for pi in undeliv:
                    w_gcd = gcd(w_gcd, pkg_weights[pi])
                if w_gcd > self.init_w_gcd:
                    entry = self._gcd_cap_cache.get(w_gcd)
                    if entry is None:
                        ec = tuple((c // w_gcd) * w_gcd for c in self.eff_truck_caps)
                        ed = sorted(ec, reverse=True)
                        mfw = tuple(sum(ed[: min(self.ferry_caps[fi], num_trucks)]) for fi in range(self.num_ferries))
                        misw = tuple(max((mfw[fi] for fi in self.island_ferries[i]), default=0) for i in range(self.num_islands))
                        entry = (ec, max(ec, default=0), mfw, misw, max((mfw[fi] for fi in self.inter_island_ferries), default=0))
                        self._gcd_cap_cache[w_gcd] = entry
                else:
                    entry = (
                        self.eff_truck_caps, self.max_eff_truck_cap, self.max_ferry_weight,
                        self.max_island_sail_weight, self.max_global_ferry_weight,
                    )
                if len(self._mask_cap_cache) < 65536:
                    self._mask_cap_cache[umask] = entry
            eff_caps, max_cap, max_fw, max_isl_sw, max_gfw = entry
        else:
            for pi in range(self.num_pkgs):
                pl = pkg_locs[pi]
                if pl != pkg_goals[pi]:
                    undeliv.append(pi)
                    h_lu += 1 if pl < 0 else 2
            eff_caps, max_cap, max_fw, max_isl_sw, max_gfw = (
                self.eff_truck_caps, self.max_eff_truck_cap, self.max_ferry_weight,
                self.max_island_sail_weight, self.max_global_ferry_weight,
            )

        if num_trucks == 0 or max_cap <= 0:
            return h_lu

        # Extract physical truck & undelivered package metadata (decoding directed corridor codes)
        t_rep, t_on_f, t_isl, occ_mask = [0] * num_trucks, [-1] * num_trucks, [0] * num_trucks, 0
        for ti in range(num_trucks):
            tl = truck_locs[ti]
            if tl >= 0:
                ptl = phys_loc[tl]
                t_rep[ti], t_isl[ti] = ptl, island_of[ptl]
                occ_mask |= 1 << ptl
            else:
                fi = -tl - 1
                fp = ferry_locs[fi]
                t_on_f[ti], t_rep[ti], t_isl[ti] = fi, fp, island_of[fp]
                occ_mask |= 1 << fp

        if self.has_dead_locs or self.has_inactive_ferries:
            dl, af = self.dead_loc, self.active_ferry
            for ti in range(num_trucks):
                if (t_on_f[ti] < 0 and dl[t_rep[ti]]) or (t_on_f[ti] >= 0 and not af[t_on_f[ti]]):
                    return h_lu
            for pi in undeliv:
                if pkg_locs[pi] >= 0 and dl[pkg_locs[pi]]:
                    return h_lu

        half_cap = max_cap >> 1
        pkg_info = []
        for pi in undeliv:
            pl, gl, w, gi = pkg_locs[pi], pkg_goals[pi], pkg_weights[pi], goal_isls[pi]
            if pl >= 0:
                occ_mask |= 1 << pl
                pkg_info.append((pi, pl, gl, pl, True, w, island_of[pl], gi, -1))
            else:
                ti = -pl - 1
                pkg_info.append((pi, pl, gl, t_rep[ti], False, w, t_isl[ti], gi, t_on_f[ti]))

        # 2. Bound B: exclusive-truck heavy sum + exact DP (A_move)
        h_excl = 0
        if self.excl_pkgs_by_truck:
            for ti, excl_ps in self.excl_pkgs_by_truck:
                if t_on_f[ti] < 0:
                    s_key, s_row = t_rep[ti], dist_full[t_rep[ti]]
                else:
                    fi = t_on_f[ti]
                    s_key, s_row = (-fi - 1, ferry_locs[fi]), f_full[fi][ferry_locs[fi]]
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

        # 3. Bound A (heavy+light packing on A_truck)
        h_pack_truck = 0
        if self.need_pack_truck:
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

        # 4. Bound C: Disjoint A_drive (compressed road bridges + precedence cycles + contracted nb)
        h_bridge = 0
        if self.bridge_chains:
            comp_of = self.comp_of
            c_mcap = [0] * self.num_comps
            for ti in range(num_trucks):
                c = comp_of[t_rep[ti]]
                if eff_caps[ti] > c_mcap[c]:
                    c_mcap[c] = eff_caps[ti]
            unit_regions = []
            for cid, int_mask, path, c_sides, m0, m1 in self.bridge_chains:
                c_cap = c_mcap[cid]
                if c_cap <= 0:
                    continue
                c_cm1, c_half = c_cap - 1, c_cap >> 1
                any_int, n_ce, last_r = bool(occ_mask & int_mask), len(c_sides), 0
                pref_ok, pref_len, suff_len = True, 0, 0
                is_u0 = is_u1 = False
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
                            kab = (wuv + c_cm1) // c_cap if wuv > 0 else 0
                            if huv > kab:
                                kab = huv
                            if nuv and kab < 1:
                                kab = 1
                            kba = (wvu + c_cm1) // c_cap if wvu > 0 else 0
                            if hvu > kba:
                                kba = hvu
                            if nvu and kba < 1:
                                kba = 1
                            ruv = kab if kab >= kba - mv else kba - mv
                            if wvu > cv and (wvu - cv + c_cm1) // c_cap > ruv:
                                ruv = (wvu - cv + c_cm1) // c_cap
                            rvu = kba if kba >= kab - mu else kab - mu
                            if wuv > cu and (wuv - cu + c_cm1) // c_cap > rvu:
                                rvu = (wuv - cu + c_cm1) // c_cap
                            last_r = ruv + rvu
                            unit_both = ruv == 1 and rvu == 1 and wuv > 0 and wvu > 0
                            is_u0 = unit_both and mu == 0
                            is_u1 = unit_both and mv == 0
                            if not any_int:
                                h_bridge += last_r * n_ce
                                if is_u0:
                                    unit_regions.append((m0, n_ce))
                                elif is_u1:
                                    unit_regions.append((m1, n_ce))
                                pref_len = suff_len = 0
                                break
                        else:
                            last_r = 0
                            is_u0 = is_u1 = False
                            if not any_int:
                                break
                    h_bridge += last_r
                    if pref_ok and is_u0:
                        pref_len += 1
                    else:
                        pref_ok = False
                    suff_len = suff_len + 1 if is_u1 else 0
                if pref_len > 0:
                    unit_regions.append((m0, pref_len))
                if suff_len > 0:
                    unit_regions.append((m1, suff_len))
            if len(unit_regions) >= 2:
                h_bridge += self._bridge_cycle_extra(unit_regions, pkg_info)

        h_nb = 0
        if self.has_non_bridge_roads:
            nb_id, nb_dist, num_nb = self.nb_id, self.nb_dist, self.num_nb
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
            if num_nb == 2:
                nb_mst = 0
                if nb_p == 0 and nb_dist[0][1] < _INF:
                    s0 = nb_id[t_rep[0]]
                    if all(nb_id[t_rep[ti]] == s0 for ti in range(1, num_trucks)):
                        for _, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
                            if nb_id[gl] != s0 or (is_gnd and nb_id[pl] != s0):
                                nb_mst = 1
                                break
            elif nb_p >= num_nb - 1:
                nb_mst = 0
            else:
                nb_req = set()
                for _, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
                    nb_req.add(nb_id[gl])
                    if is_gnd:
                        nb_req.add(nb_id[pl])
                nb_mst = _mst_cost(list(nb_req), nb_dist, [nb_dist[nb_id[loc]] for loc in t_rep])
            h_nb = nb_mst if nb_mst >= nb_p else nb_p

        h_drive = h_bridge + h_nb

        # 5. Bound C (cont.): h_bd (A_bd) & h_sail (A_sail)
        h_bd = h_sail = 0
        if self.has_inter_island_ferries:
            if self.all_inter_ferries_are_cuts:
                h_bd, b7 = self._eval_cut_ferries(
                    pkg_info, ferry_locs, t_isl, t_on_f, eff_caps, max_cap, max_fw,
                )
                h_sail = 3 * b7
            else:
                h_bd, h_sail = self._eval_island_ferries(
                    pkg_info, ferry_locs, t_isl, t_on_f,
                    eff_caps, max_cap, max_fw, max_isl_sw, max_gfw,
                )

        # 6. Final Admissible Combination + gated h_single
        h_truck = h_drive + h_bd
        if h_pack_truck > h_truck:
            h_truck = h_pack_truck

        h_move = h_truck + h_sail
        if h_excl > h_move:
            h_move = h_excl

        if h_move < self.max_single_ub:
            capable, max_to_loc = self.capable_trucks, self.max_to_loc
            for pi, pl, gl, _, is_gnd, _, _, _, _ in pkg_info:
                if is_gnd:
                    dd = dist_full[pl][gl]
                    if dd < _INF and dd + max_to_loc[pl] > h_move:
                        mp = _INF
                        for ti in capable[pi]:
                            dp = dist_full[t_rep[ti]][pl] if t_on_f[ti] < 0 else f_full[t_on_f[ti]][ferry_locs[t_on_f[ti]]][pl]
                            if dp < mp:
                                mp = dp
                        if mp < _INF and mp + dd > h_move:
                            h_move = mp + dd
                else:
                    ti = -pl - 1
                    dd = dist_full[t_rep[ti]][gl] if t_on_f[ti] < 0 else f_full[t_on_f[ti]][ferry_locs[t_on_f[ti]]][gl]
                    if dd < _INF and dd > h_move:
                        h_move = dd

        res = h_lu + h_move
        if len(h_cache) < 500000:
            h_cache[state] = res
        return res


def create_logistics_problem(game):
    print("<<create_logistics_problem")
    """Create a logistics problem from the game dictionary."""
    return LogisticsProblem(game)


if __name__ == "__main__":
    ex1_check.main()
