# `ex1.py` — Complete Code Walkthrough & Formal Admissibility Audit

This document provides a read-only, line-referenced architectural walkthrough of `ex1.py` followed by a formal admissibility and optimality audit of every heuristic component, combination rule, and search-space pruning / partial-order reduction (POR) rule.

---

## PART 1: FULL CODE WALKTHROUGH

### 1.1 Module-Level Helper Functions (`L22–L140`)

- **`_components(adj)` (`L22–L34`)**: Standard BFS connected-components decomposition of an undirected graph. Returns `(comp_of, num_comps)`.
- **`_apsp_bfs(adj)` (`L37–L51`)**: Unweighted All-Pairs Shortest Paths (APSP) via BFS from every vertex. Unreachable pairs receive `_INF = 10**9`.
- **`_pack_lb(heavy_d, min_hw, light_wd, total_wd, cap)` (`L54–L63`)**: Heavy+light bin-packing lower bound on unit truck steps. Computes:
  $$\max\!\left(\left\lceil \frac{\text{total\_wd}}{C} \right\rceil,\; \text{heavy\_d} + \left\lceil \frac{\max(0,\, \text{light\_wd} - (C - \text{min\_hw}) \cdot \text{heavy\_d})}{C} \right\rceil\right)$$
  where a package is *heavy* if $w > \lfloor C/2 \rfloor$ (so no two heavy packages can share a truck simultaneously).
- **`_flux_lb(w_ab, w_ba, h_ab, h_ba, need_ab, need_ba, m_a, m_b, c_a, c_b, cap)` (`L66–L93`)**: Minimum directed truck crossings $(r_{ab}, r_{ba})$ across a 2-sided cut $(A, B)$:
  - Direct demand $k_{ab} = \max(\lceil w_{ab}/C \rceil, h_{ab}, \mathbb{1}[\text{need}_{ab}])$ (and symmetrically $k_{ba}$).
  - Truck-count and truck-capacity conservation:
    $$r_{ab} = \max\!\left(k_{ab},\; k_{ba} - m_b,\; \left\lceil \frac{\max(0, w_{ba} - c_b)}{C} \right\rceil\right)$$
    and symmetrically for $r_{ba}$.
- **`_mst_cost(req, dist_mat, start_rows)` (`L96–L139`)**: Prim's Minimum Spanning Tree (MST) on the metric closure `dist_mat` over required vertices `req`, rooted at a virtual super-source whose distance to each $v \in \text{req}$ is $\min_{r \in \text{start\_rows}} r[v]$. Fast-paths `m = 0, 1, 2`.

---

### 1.2 State Representation & Encoding (`L145–L174`, `L245–L268`, `L392`)

All entity IDs (trucks, ferries, packages) are sorted and mapped to compact 0-based indices (`truck_ids`, `ferry_ids`, `pkg_ids`). This cleanly decouples internal indexing from arbitrary or overlapping external IDs.

A search state is a hashable 3-tuple of integer tuples:
```python
state = (truck_locs, ferry_locs, pkg_locs)
```
- **`truck_locs[ti]`**:
  - `0 <= val < n`: Truck `ti` is standing at physical location `val`.
  - `val < 0`: Truck `ti` is aboard ferry `fi = -val - 1` (encoded as `-(fi + 1)`).
  - `val >= n`: **Directed pure-corridor state code**. Represents truck `ti` located at physical degree-2 corridor vertex `phys_loc[val]` moving in a fixed direction `(frm -> v -> to)`, eliminating backward U-turns and mid-corridor interleavings.
- **`ferry_locs[fi]`**: Current port index (`0 <= val < n`) of ferry `fi`.
- **`pkg_locs[pi]`**:
  - `val >= 0`: Package `pi` is on the ground at location `val`.
  - `val < 0`: Package `pi` is loaded inside truck `ti = -val - 1` (encoded as `-(ti + 1)`).

---

### 1.3 Static Precomputations in `LogisticsProblem.__init__` (`L145–L590`)

1. **Metadata & Subset-Sum Effective Capacities (`L146–L191`)**:
   - Extracts adjacency lists `raw_roads`, `is_port`, entity capacities, ferry served ports, and initial/goal locations.
   - Uses a bitmask Subset-Sum DP over `self.pkg_weights` to compute `eff_truck_caps[ti]`: the largest subset sum of package weights $\le \text{truck\_caps}[ti]$ (used **only** inside `h_astar`, never to alter legal transitions).
   - Stores `init_w_gcd` and `has_mixed_weights` to enable dynamic GCD capacity tightening during search.

2. **Dead Locations, Dominated Ports, Corridors & Unload Restrictions (`L193–L268`, `_find_dead_locs` `L395–L432`)**:
   - Marks `rel[loc] = True` for all `init_t`, `init_p`, and `pkg_goals`.
   - `_find_dead_locs` builds the combined road+ferry graph `rf_raw` and marks as `dead`: (a) any node unreachable from `rel`, and (b) any component separated by an articulation point `u` that contains no `rel` node. Dead nodes are stripped from `self.roads`.
   - Identifies `active_ferry` (capacity $> 0$ and $\ge 2$ non-dead ports).
   - Marks `no_enter[v] = True` for isolated non-`rel` ports (no roads) whose serving ferries all share another non-`no_enter` port. These ports are excluded from `ferry_active_targets`. *(Note: see Audit Section 2.1 for a subtle optimality bug found here when a ferry starts at `v`.)*
   - Identifies `pure_corridor` (non-`rel`, non-port, road-degree 2) and builds directed codes `>= n` (`phys_loc`, `cor_next`, `_cor_drive_strs`, `road_moves`).
   - Identifies `nonport_leaf` (non-port, road-degree 1) and sets `no_unload_loc[v] = pure_corridor[v] or nonport_leaf[v]`.

3. **Symmetry Groups, Exclusive-Truck Packages & Action Strings (`L270–L299`)**:
   - `prev_sym_truck[ti]`: earlier trucks with identical capacity.
   - `prev_sym_ferry[fi]` / `same_sym_ferries[fi]`: active ferries with identical capacity and served ports.
   - `prev_sym_pkg[pi]`: earlier packages with identical weight and goal.
   - `capable_trucks[pi]` and `excl_pkgs_by_truck`: packages that only a single truck in the entire problem is capable of carrying.
   - Pre-formats all legal action strings (`_load_strs`, `_unload_strs`, `_board_strs`, `_disembark_strs`, `_drive_strs`, `_sail_strs`).

4. **Connected-Component Decomposition (`L301–L314`)**:
   - Computes connected components of the active road+ferry graph `_rf_adj` (`comp_of`, `comp_trucks`, `comp_ferries`, `comp_pkgs`).
   - Enables `use_comp_decomp = True` when $\ge 2$ components contain packages and every package's start and goal lie in the same component.

5. **All-Pairs Shortest Paths & On-Ferry Distance Tables (`L316–L348`, `_dijkstra` `L434–L458`)**:
   - `dist_full = _dijkstra(5)`: road edge = 1 (`DRIVE`), ferry hop = 5 (`BOARD(1) + SAIL(3) + DISEMBARK(1)`).
   - `dist_no_sail = _dijkstra(2)`: road edge = 1 (`DRIVE`), ferry hop = 2 (`BOARD(1) + DISEMBARK(1)`, zero `SAIL` cost).
   - `ferry_full_dist[fi][cp][t]`: minimum `A_move` cost for a truck currently aboard ferry `fi` at port `cp` to reach `t` (`1 + dist_full[cp][t]` by disembarking immediately, or `4 + dist_full[op][t]` by sailing once to another port `op` and disembarking).
   - `ferry_disembark_no_sail[fi][t]`: $\min_{cp \in \text{served}[fi]} (1 + \text{dist\_no\_sail}[cp][t])$.
   - `max_to_loc` and `max_single_ub`: static upper bounds used to gate `h_single` at runtime.

6. **Islands, Road Bridges, Contracted Non-Bridge Metric & Cut Ferries (`L349–L390`)**:
   - `island_of`, `num_islands`, `road_dist`: road-only connected components and unweighted road APSP.
   - `inter_island_ferries`, `island_ferries`, `isl_sole_ferry`, `min_sails`, `island_diam_one`: inter-island ferry graph and APSP in sail count.
   - `_precompute_bridges_and_nb` (`L460–L554`): finds all road edges that are bridges of `_rf_adj` (and not parallel to an active ferry), compresses maximal chains of bridges through `pure_corridor` vertices into `bridge_chains`, and contracts all bridges + active ferry cliques to cost 0 to form the non-bridge metric `(nb_id, nb_dist, num_nb)`.
   - `_precompute_cut_ferries` (`L555–L589`): identifies inter-island ferries whose removal disconnects the island graph (`cut_ferries`).

---

### 1.4 `path_cost` (`L591–L594`) and `goal_test` (`L832–L833`)

- **`path_cost(c, state1, action, state2)`**: returns `c + (3 if action.startswith("SAIL") else 1)`.
- **`goal_test(state)`**: returns `state[2] == self.pkg_goals` (every package is on the ground at its goal location).

---

### 1.5 `successor()` — Transitions, POR / Ample-Sets & Symmetry Breaking (`L596–L830`)

`successor()` applies an ordered hierarchy of optimality-preserving reductions before falling back to normal expansion:

1. **Component Decomposition (`L606–L619`)**:
   If `use_comp_decomp` is active, selects the first component `ac` that still has an undelivered package and restricts expansion exclusively to `comp_trucks[ac]`, `comp_ferries[ac]`, `comp_pkgs[ac]`.
2. **Forced Canonical `UNLOAD` at Goal (`L621–L635`)**:
   If any truck `ti` at physical location `tl` carries a package `pi` with `pkg_goals[pi] == tl`, immediately returns **only** `[UNLOAD(pi, ti)]`. Simultaneously computes `t_loads`, `t_cnts`, and `min_undeliv_w`.
3. **Ample-Set A1 — One-Way Pure Corridor (`L637–L643`)**:
   If any truck `ti` has `truck_locs[ti] >= n` (inside a `pure_corridor`), immediately returns **only** `[DRIVE(ti, v, cor_next[tl])]`.
4. **Ample-Set A2 & A3 — Loaded Trucks at Restricted Nodes (`L645–L693`)**:
   - **A2 (`L651–L677`)**: If a loaded truck `ti` is the **sole** truck at a `nonport_leaf`, returns only legal `LOAD`s at `tl` (with `max_il` canonicalization and `prev_sym_pkg` symmetry skip) and the unique exit `DRIVE`.
   - **A3 (`L678–L693`)**: If a loaded truck `ti` is at a non-port and cannot load any remaining undelivered package (`rem_cap < min_undeliv_w`), returns only `ti`'s `DRIVE`s and `UNLOAD`s (if not `no_unload_loc[tl]`).
5. **Ample-Set B — Full Ferry or Non-Empty 2-Port Ferry (`L695–L740`)**:
   If any active ferry `fi` has `fc > 0` trucks aboard and either `fc == ferry_caps[fi]` or `ferry_is_two_port[fi]`, returns only actions involving `fi`: `DISEMBARK` (with `prev_sym_truck` skip for identical empty trucks), `BOARD` of trucks at `cp` if `fc < ferry_caps[fi]` in ascending index order (`ti >= max_ab_ti`), and `SAIL` to `tp != cp`.
6. **Normal Expansion with Symmetry Breaking & Saturation (`L742–L830`)**:
   - **Empty truck symmetry (`prev_sym_truck`)**: among identical empty trucks at the same location, only the lowest-indexed truck is expanded.
   - **Package symmetry (`prev_sym_pkg`) & canonical multi-`LOAD` (`max_il`)**: among identical packages at the same location (or in the same truck), only the lowest-indexed is loaded/unloaded; packages originating at `tl` (`pkg_init[pi] == tl`) are loaded in ascending index order.
   - **No useless unloads (`no_unload_loc`)**: forbids unloading non-goal packages at `pure_corridor` or `nonport_leaf` nodes.
   - **Empty ferry rules (`L803–L829`)**:
     - Identical empty ferries at the same port break symmetry via `prev_sym_ferry`.
     - An empty ferry only sails to a port `tp` where a truck is currently standing (`tp in truck_locs`).
     - **Saturation**: if identical empty peer ferries (`same_sym_ferries`) already docked at `tp` have total capacity `avail >= nt_tp` (number of trucks at `tp`), sailing another empty ferry to `tp` is pruned.

---

### 1.6 `h_astar()` — Action Cost Partitioning & Sub-Heuristics (`L1386–L1732`)

#### Action Cost Partitioning
Every action in a plan is partitioned into four pairwise-disjoint sets:
- $A_{\text{LU}} = \{\text{LOAD}, \text{UNLOAD}\}$
- $A_{\text{drive}} = \{\text{DRIVE}\} = A_{\text{bridge}} \sqcup A_{\text{nb}}$
- $A_{\text{bd}} = \{\text{BOARD}, \text{DISEMBARK}\}$
- $A_{\text{sail}} = \{\text{SAIL}\}$

With unions $A_{\text{truck}} = A_{\text{drive}} \sqcup A_{\text{bd}}$ and $A_{\text{move}} = A_{\text{truck}} \sqcup A_{\text{sail}}$, the heuristic combines sub-bounds via (`L1700–L1729`):
```python
h_drive = h_bridge + h_nb
h_truck = max(h_drive + h_bd, h_pack_truck)
h_move  = max(h_truck + h_sail, h_excl, h_trade, h_single)
return h_lu + h_move
```

#### Dynamic GCD Capacity Tightening (`L1410–L1451`)
If `has_mixed_weights` is `True`, computes $g = \gcd\{w_p : p \in \text{undeliv}\}$ (cached by undelivered bitmask `umask`) and tightens each truck's effective capacity to $\lfloor \text{eff\_truck\_caps}[ti] / g \rfloor \cdot g$, propagating to `max_fw`, `max_isl_sw`, and `max_gfw`.

#### Sub-Heuristic Components
1. **`h_lu` ($A_{\text{LU}}$, `L1411–L1447`)**: $+1$ per undelivered package inside a truck (`UNLOAD`), $+2$ per undelivered grounded package (`LOAD` + `UNLOAD`).
2. **`h_bridge` ($A_{\text{bridge}}$, `L1545–L1644`) + `_bridge_cycle_extra` (`L1322–L1384`)**:
   - Sums `_flux_lb` (inlined) over every edge in `bridge_chains` (compressed when no truck/package occupies interior corridor nodes).
   - Tracks 0-truck unit-flux (`ruv == rvu == 1`) prefix/suffix regions and calls `_bridge_cycle_extra` to extract pairwise-disjoint directed package-precedence cycles, adding $\min_i \ell_i$ extra crossings per disjoint cycle.
3. **`h_nb` ($A_{\text{nb}}$, `L1646–L1680`)**:
   - On the contracted graph `nb_dist` (where bridges and ferries cost 0), takes `max(nb_p, nb_mst)`: `_pack_lb` on weighted non-bridge distances vs. `_mst_cost` rooted at truck positions covering all required non-bridge super-nodes.
4. **`h_bd` ($A_{\text{bd}}$) & `h_sail` ($A_{\text{sail}}$)**:
   - **All inter-island ferries are cuts (`_eval_cut_ferries`, `L895–L1104`)**: For each cut ferry `fi`, computes `_flux_lb` across its cuts, converts to minimum sails (`sails_f`, accounting for initial ferry side, alternation, and empty-ferry fetch when `mh == 0`), and computes `best_bd` (including an exact minimization over `(z, x)` for trucks already aboard `fi`: `x` direct crossers, `z` unused empty trucks, `d = ab_c - x - z` disembarking first).
   - **Cyclic ferry maps (`_eval_island_ferries`, `L1106–L1319`)**:
     - `h_bd`: combines per-island boarding/disembarking flux (`b1, d1`), multi-hop `min_sails` bounds (`b2, d2`), aboard balance (`lb_b >= lb_d - n_ab`), and cut-ferry `bd_c`.
     - `h_sail`: takes `3 * max(vol, sum_req_i, b3, b7)` where `vol` combines `sum_so`, `sum_si`, single-package `b4`, weighted/heavy sail volume `b5`, plus `+1` if `n_ab == 0` and no active ferry is on any truck's island.
5. **`h_pack_truck` ($A_{\text{truck}}$, `L1529–L1542`)**: `_pack_lb` over `dist_no_sail` (and `ferry_disembark_no_sail` for packages aboard ferries).
6. **`h_excl` ($A_{\text{move}}$, `L1491–L1526`) + `_excl_tsp_lb` (`L835–L893`)**: For each truck with exclusive packages, takes `max` of: (a) sum of `dist_full` of heavy exclusive packages ($w > \lfloor \text{eff\_cap}/2 \rfloor$) plus approach distance if not holding one, and (b) exact infinite-capacity pickup-and-delivery DP over up to 4 exclusive packages.
7. **`h_trade` ($A_{\text{move}}$, `L1042–L1100`, `L1294–L1295`, `L1691–L1692`)**: For an empty docked cut ferry `fi` that is the sole ferry on a bridge-free island `f_isl` achieving `cur_sf == sails_f`: either `fi` performs $\ge \text{sails\_f} + 1$ sails (`+3`), or it performs 0 intra-island sails, forcing road drives on `f_isl` (reaching `p0` + grounded intra-island packages at `p0`, or an island MST when `cur_si == 0, cur_so <= 1`). Adds $\min(3, \text{req\_rd} - h_{\text{nb}})$ to `h_drive + h_bd + 3 * b7`.
8. **`h_single` ($A_{\text{move}}$, `L1710–L1727`)**: Gated single-package `dist_full` lower bound (approach of closest capable truck + delivery distance, or remaining delivery distance if already loaded).

---

## PART 2: FORMAL ADMISSIBILITY & OPTIMALITY AUDIT

> **Note on `search.astar_search`**: In `search.py` (`L147–L150`), `graph_search` stores `closed[state] = path_cost` and **re-opens** states if reached with a strictly lower `g`-cost. Therefore, **admissibility** ($h(s) \le h^*(s)$) without consistency is sufficient for A* optimality, provided `successor()` preserves at least one optimal plan.

### 2.1 CRITICAL FINDING — Optimality-Breaking Bug in Static `no_enter` Port Pruning (`L194–L196`, `L219–L231`)

#### Flaw
In `__init__` (`L194–L196`), `rel` marks initial truck locations, package starts, and package goals — **but omits `init_f` (initial ferry locations)**:
```python
rel = [False] * n
for loc in init_t + init_p + self.pkg_goals:
    rel[loc] = True
```
Then, in `L219–L231`, any non-`rel`, roadless port `v` whose serving ferries all share another non-`no_enter` port `q` is marked `no_enter[v] = True`, forbidding all ferries from sailing to `v`.

If a ferry `f1` is **initially docked at `v`**, another ferry `f2` can no longer sail to `v` to hand off a truck directly to `f1` (which would require 0 positioning sails for `f1`). Instead, `f1` is forced to sail empty `v -> q` (+3 cost) so the transfer happens at `q`.

#### Concrete Counterexample (Suboptimal Plan Produced)
- **Locations**: `4` (`0 = a`, `1 = b`, `2 = v`, `3 = q`), **Roads**: `set()`, **Ports**: `{0, 1, 2, 3}`.
- **Trucks**: `{10: (1, 5)}` (at `b = 1`).
- **Packages**: `{30: (1, 1, 0)}` (from `b = 1` to `a = 0`).
- **Ferries**:
  - `20` (`f1`): `(2, (0, 2, 3), 1)` — starts at `v = 2`, serves `{0, 2, 3}`.
  - `21` (`f2`): `(1, (1, 2, 3), 1)` — starts at `b = 1`, serves `{1, 2, 3}`.
- **Trace**:
  - `rel = [True, True, False, False]`, `dead = [False, False, False, False]`.
  - For `v = 2`: `not rel[2]`, `not roads[2]`, `f_at_p[2] = [0, 1]`, `common = {3}`, `not no_enter[3]` is `True` $\implies$ **`no_enter[2] = True`**.
  - `ferry_active_targets[f2]` excludes `2`, so `SAIL{21,1,2}` is pruned.
- **True Optimal Plan (cost 12)**:
  `LOAD{30,10}` (1) $\to$ `BOARD{10,21}` (1) $\to$ `SAIL{21,1,2}` (3) $\to$ `DISEMBARK{10,21}` (1) $\to$ `BOARD{10,20}` (1) $\to$ `SAIL{20,2,0}` (3) $\to$ `DISEMBARK{10,20}` (1) $\to$ `UNLOAD{30,10}` (1).
- **Best Plan Allowed by `ex1.py` (cost 15)**:
  Must additionally execute `SAIL{20,2,3}` (+3) and transfer at `q = 3`, returning cost **15 > 12**.

#### Exact Fix (Do Not Edit Yet)
Guard `no_enter` against initial ferry ports, e.g., include `init_f` in `rel` (`L195`) or add `and v not in init_f` at `L221`:
```python
init_f_set = set(init_f)
for v in range(n):
    if not no_enter[v] and not rel[v] and not self.roads[v] and v not in init_f_set:
```
*(Note: `_find_dead_locs` itself does not suffer from this bug when `len(nd) >= 2`, because in `rf_raw` all served ports of a ferry form a clique, so no port of a ferry with $\ge 2$ surviving ports can ever be separated into a `rel`-free component by removing a single articulation point.)*

---

### 2.2 Formal Admissibility Proofs for `h_astar()`

**Verdict on `h_astar()`**: **100% ADMISSIBLE.** No overestimation bug ($h(s) > h^*(s)$) was found in any heuristic component, helper function, or combination rule.

#### 1. Cost Partitioning & Combination (`L1700–L1729`)
For any valid plan $\pi$ from $s$, its actions partition into pairwise-disjoint sets $A_{\text{LU}}$, $A_{\text{bridge}}$, $A_{\text{nb}}$, $A_{\text{bd}}$, $A_{\text{sail}}$:
$$c(\pi) = c^*(A_{\text{LU}}) + c^*(A_{\text{move}}),\quad c^*(A_{\text{move}}) = c^*(A_{\text{truck}}) + c^*(A_{\text{sail}}),\quad c^*(A_{\text{truck}}) = c^*(A_{\text{bridge}}) + c^*(A_{\text{nb}}) + c^*(A_{\text{bd}})$$
Every `+` in `h_astar` sums strictly disjoint action-cost lower bounds (`h_bridge + h_nb`, `h_drive + h_bd`, `h_truck + h_sail`, `h_lu + h_move`), and every `max` is over valid lower bounds for the same action subset.

#### 2. Dynamic GCD & Subset-Sum Effective Capacities (`L176–L188`, `L1412–L1441`)
- No optimal plan ever loads an already-delivered package (it only adds `LOAD`/`UNLOAD` cost and consumes capacity). Any package inside a truck has `pkg_locs[pi] < 0 != pkg_goals[pi]`, so it is included in `undeliv`.
- Therefore, at any point in an optimal plan from $s$, the total weight of undelivered packages in truck `ti` is a subset sum of `undeliv` weights $\le c_{ti}$, hence both $\le \text{eff\_truck\_caps}[ti]$ and a multiple of $g = \gcd(\{w_p : p \in \text{undeliv}\})$, so $\le \lfloor \text{eff\_truck\_caps}[ti] / g \rfloor \cdot g$.
- Summing the top $\min(\text{ferry\_caps}[fi], \text{num\_trucks})$ effective capacities upper-bounds the undelivered weight on ferry `fi`.

#### 3. `h_lu` (`L1411–L1447`)
Each undelivered package requires at least 1 `UNLOAD` (if currently in a truck) or 1 `LOAD` + 1 `UNLOAD` (if on the ground). Actions in $A_{\text{LU}}$ affect one package each at cost 1. Thus `h_lu` $\le c^*(A_{\text{LU}})$. $\square$

#### 4. `_pack_lb` (`L54–L63`) & `h_pack_truck` (`L1529–L1542`)
- For integer $C$, $w > \lfloor C/2 \rfloor \iff 2w > C$, so at most one heavy package fits in a truck at any step.
- Let $S_H$ be the number of unit-cost truck steps carrying a heavy package and $S_L$ the rest. Then $S_H \ge \text{heavy\_d}$ and $(C - \text{min\_hw})S_H + C S_L \ge \text{light\_wd}$. Since $C - \text{min\_hw} \le C$, replacing $(S_H - \text{heavy\_d})$ heavy-steps by light-steps yields $(C - \text{min\_hw})\text{heavy\_d} + C(S_H + S_L - \text{heavy\_d}) \ge \text{light\_wd}$, proving `_pack_lb` $\le S_H + S_L$.
- In `dist_no_sail`, each road step costs 1 (`DRIVE`) and each ferry hop costs 2 (`BOARD + DISEMBARK`, with `SAIL = 0`). For a package aboard ferry `on_f`, `ferry_disembark_no_sail[on_f][gl]` charges 1 for `DISEMBARK` at the optimal served port plus `dist_no_sail`. Even under relays, every unit of `dist_no_sail` progress requires a truck carrying the package to pay 1 unit in $A_{\text{truck}}$. Thus `h_pack_truck` $\le c^*(A_{\text{truck}})$. $\square$

#### 5. `h_bridge` (`L1545–L1644`) & `_bridge_cycle_extra` (`L1322–L1384`)
- Each bridge edge $e = (u, v)$ separates its component into side 0 and side 1. Every truck initially on side 1 provides at most 1 crossing $1 \to 0$ (of capacity $c_t$) before any $0 \to 1$ crossing occurs; each $0 \to 1$ crossing enables at most 1 additional $1 \to 0$ crossing of capacity $\le c_{\text{cap}}$. Thus $c_v + r_{uv} c_{\text{cap}} \ge w_{vu}$ and $m_v + r_{uv} \ge k_{ba}$, proving `_flux_lb` $\le$ actual crossings of $e$.
- Interior vertices of a `bridge_chain` are `pure_corridor` nodes (`not rel`, `not is_port`), so they can never hold package goals or ferries; `occ_mask` captures all trucks and grounded packages, so chain compression is exact.
- In `_bridge_cycle_extra`, if a cycle $R_0 \to \dots \to R_{m-1} \to R_0$ of pairwise location-disjoint 0-truck unit-flux regions had every edge of every region's prefix/suffix crossed at most once in and once out, then for each $i$ the sole incoming crossing (delivering $p_{i-1}$) must precede the sole outgoing crossing (exporting $p_i$), yielding a strict temporal cycle contradiction. Hence at least one region $R_i$ must cross its entire prefix/suffix at least 3 times (+1 per edge, $+\ell_i$ total). Even when both `pref_len > 0` and `suff_len > 0` occur on the same chain (due to an interior truck), their edge segments are strictly disjoint. Summing $\min_i \ell_i$ over disjoint cycles is $\le c^*(A_{\text{bridge}})$. $\square$

#### 6. `h_nb` (`L1646–L1680`)
- Contracting bridges and ferry cliques to cost 0 yields `nb_dist`, where every action outside $A_{\text{nb}}$ moves distance 0 and every action in $A_{\text{nb}}$ moves distance $\le 1$.
- `nb_p` is valid by the `_pack_lb` proof.
- **Why `nb_mst` is valid despite Steiner-tree subtleties**: Unlike a branching Steiner tree, trucks execute sequential *walks* $W_1, \dots, W_k$ starting at $s_1, \dots, s_k$. If walk $W_j$ visits required nodes $v_{j,1}, \dots, v_{j,m_j}$ in order, triangle inequality gives $\text{len}(W_j) \ge d(s_j, v_{j,1}) + \sum_t d(v_{j,t}, v_{j,t+1})$. The union of these metric-closure paths spans $\{r\} \cup \text{nb\_req}$ (where $w(r, v) = \min_i d(s_i, v)$), so $\sum_j \text{len}(W_j) \ge \text{MST}(\{r\} \cup \text{nb\_req}) = \text{nb\_mst}$.
- Skipping `nb_mst` when `nb_p >= num_nb - 1` can only lower the bound, never overestimate. Thus `h_nb` $\le c^*(A_{\text{nb}})$. $\square$

#### 7. `_eval_cut_ferries` (`L895–L1104`) & `h_trade` (`L1042–L1100`)
- Each cut ferry `fi` is the unique link between its separated island sets, so `_flux_lb` lower-bounds truck crossings via `fi`, and `sails_f = max(sof, sif, msf)` lower-bounds `fi`'s sails (including `+1` empty fetch when `mh == 0` and `soh > 0`, and alternation of outgoing/incoming sails).
- For `ab_c > 0`, every valid plan partitions the `ab_c` aboard trucks into `x` direct crossers (saving `x` `BOARD`s, forced to carry `extra_opp` stay-weight back if `x > max_x - ab_stay`, and unable to pick up `w_gnd_cur` before crossing), `z` unused empty trucks (removing `(z, cz)` from the current side), and `d = ab_c - x - z` trucks disembarking first (`+d`). Minimizing over all `(z, x)` guarantees `best_bd` $\le c^*(A_{\text{bd}}(f_i))$.
- For `h_trade`: `isl_sole_ferry[f_isl] == fi` guarantees that `fi`'s cut component `in_h` is `{f_isl}` alone, and `not isl_has_bridge[f_isl]` guarantees all roads on `f_isl` belong to $A_{\text{nb}}$. Either `fi` executes $\ge \text{sails\_f} + 1$ sails (`+3`), or it executes 0 intra-island sails and (when `cur_so >= cur_si` and `cur_so >= 1`) cannot start with an empty sail without exceeding `cur_sf`, forcing `g_trucks` to drive $\ge d_{\min} + p_{0,\text{intra}}$ (or the island MST when `cur_si == 0, cur_so <= 1`) on $A_{\text{nb}}$. Taking $\max$ across cut ferries avoids double-counting `h_nb`. Thus `h_trade` $\le c^*(A_{\text{move}})$. $\square$

#### 8. `_eval_island_ferries` (`L1106–L1319`)
- `b1, d1` sum disjoint per-island `BOARD` and `DISEMBARK` minimums (with truck conservation).
- `b2, d2` use `min_sails[pi_s][gi_s]`; for a package aboard a ferry, triangle inequality guarantees that disembarking at any port served by that ferry still leaves $\ge \text{ms} - 1$ future `BOARD`s and $\ge \text{ms} - 1$ future `DISEMBARK`s (+1 for the initial disembark).
- `lb_b >= lb_d - n_ab` holds because every `DISEMBARK` comes from either an initially aboard truck or a `BOARD`.
- For `h_sail`, every term contributing to `vol` (`sum_so`, `sum_si`, `b4`, `b5`) counts strictly **occupied** sails (carrying $\ge 1$ truck). When `vol > 0`, `n_ab == 0`, and no active ferry is on any truck's island, at least 1 **empty** positioning sail must precede all occupied sails, so `vol += 1` (applied *before* taking `max` with `sum_req_i`, `b3`, `b7`, which may include empty sails) is strictly admissible. $\square$

#### 9. `h_excl` (`L1491–L1526`) & `h_single` (`L1710–L1727`)
- Heavy exclusive packages ($w > \lfloor \text{eff\_cap}/2 \rfloor$) must be transported sequentially by their sole capable truck `ti` in disjoint time intervals, after `ti` reaches the first one (if not already holding one). `_excl_tsp_lb` relaxes capacity to $\infty$ over a subset of $\le 4$ exclusive packages. Both are $\le c^*(A_{\text{move}})$.
- `h_single` sums time-disjoint approach (`min` over capable trucks) + delivery in `dist_full` (or `f_full` when aboard a ferry, which accounts for mandatory `DISEMBARK` before `UNLOAD`). Gating by `max_single_ub` and `max_to_loc` is exact. Thus `h_single` $\le c^*(A_{\text{move}})$. $\square$

---

### 2.3 Formal Optimality Audit of `successor()` Pruning & POR Rules

| Rule | Lines | Verdict | Proof Sketch |
| :--- | :---: | :---: | :--- |
| **Component decomposition** (`use_comp_decomp`) | `L606–L619` | **100% Sound** | Disconnected components of `_rf_adj` cannot interact; sequential execution preserves exact optimal cost. |
| **Forced `UNLOAD` at goal** | `L621–L635` | **100% Sound** | Package must eventually be unloaded at its goal; advancing `UNLOAD` frees capacity earlier and commutes with all other actions. |
| **Ample-set A1** (directed `pure_corridor`) | `L637–L643` | **100% Sound** | Non-`rel`, non-port, degree-2 nodes allow no `LOAD`/`UNLOAD`/`BOARD`; continuing forward commutes with all other agents and eliminates U-turns. |
| **Ample-set A2** (solo loaded truck at `nonport_leaf`) | `L651–L677` | **100% Sound** | Truck must eventually leave the leaf; waiting for another truck to relay at a leaf is strictly dominated by meeting at the leaf's unique neighbor. |
| **Ample-set A3** (full loaded truck at non-port) | `L678–L693` | **100% Sound** | Truck cannot `LOAD` (`rem_cap < min_undeliv_w`) or `BOARD` (non-port); no other agent can enable new useful actions for it, and it must eventually `DRIVE` or `UNLOAD`. |
| **Ample-set B** (full / 2-port non-empty ferry) | `L695–L740` | **100% Sound** | All trucks start on the ground. Any truck/package preparation at `cp` can be scheduled *before* the first truck boards `fi`; once all boarding trucks are ready at `cp`, they can board in ascending index order (`ti >= max_ab_ti`), sail, and disembark. |
| **Symmetry skips** (`prev_sym_truck/ferry/pkg`) & **canonical `max_il`** | `L746–L814` | **100% Sound** | Identical entities in identical states are interchangeable; carrying a `tl`-origin package away from `tl` and back to `tl` without unloading it is dominated by leaving it at `tl` until final departure. |
| **Empty-ferry target & saturation** (`tp in truck_locs`, `avail >= nt_tp`) | `L815–L828` | **100% Sound** | An empty ferry sailing to `tp` commutes with trucks moving to `tp`, so delaying `SAIL` until a truck is at `tp` (and `nt_tp > avail`) preserves optimality. |
| **Static `no_enter` dominated ports** | `L219–L231` | **BUG (Suboptimal)** | Omits `init_f` from `rel`; prunes optimal transfers at a roadless port where a ferry is initially docked (see Section 2.1). |
