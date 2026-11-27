# Read-Only Code Audit & Performance Profile of `ex1.py`

> **Target file:** `ex1.py` (3,485 lines, unmodified)  
> **Benchmark files:** `ex1_check.py`, `hard_problems.txt` (88 problems)  
> **Profiled instances:** Problems 7, 12 (15s cap), and 15 from `hard_problems.txt`

---

## 1. Code Audit of `ex1.py`

### A. Classes, Methods, and Heuristic Components

| Symbol / Section | Lines | Line Count | Purpose |
|---|---:|---:|---|
| Module constants (`id`, `_INF`, `_DERANGEMENTS_3`, `_DERANGEMENTS_4`) | L1–L34 | 34 | Imports & hardcoded 3/4-element derangement tables |
| `class LogisticsProblem(search.Problem)` | L36–L3474 | 3,439 | Sole class in the file |
| ├── `__init__` | L39–L810 | 772 | Static parsing, subset-sum effective caps, dead-end/corridor/port pruning, symmetry tables, pre-formatted action strings, component decomposition, APSP tables (`dist_full`, `dist_no_sail`, `dist_cut`, `road_dist`, `road_dist_free_ferry`), island graph, `isl_road_bridges`, `cut_ferries`, `sail_cut_ferries` |
| ├── `_precompute_road_bridges` | L812–L1068 | 257 | Bridges in $G_{rf}$, compressed pure-corridor chains, 2-edge-connected bridge-block hub groups, private goal bridges |
| ├── `_precompute_dijkstra` | L1070–L1106 | 37 | All-pairs Dijkstra (`ferry_weight=5` and `2`) |
| ├── `_precompute_bfs_cut` | L1108–L1137 | 30 | All-pairs unit-weight BFS on $G_{rf}$ |
| ├── `path_cost` | L1139–L1142 | 4 | Action cost (`SAIL` = 3, others = 1) |
| ├── `successor` | L1144–L1412 | 269 | Component ordering, forced goal-unload, Ample-set A (mid-corridor drive), Ample-set B (full ferry), empty truck/ferry/pkg symmetry breaking, legal action generation |
| ├── `goal_test` | L1414–L1416 | 3 | `state[2] == self.pkg_goals` |
| └── `h_astar` (monolithic method) | L1418–L3474 | **2,057** | All heuristic components inlined into one function: |
| &emsp;• Sec 1: `h_load_unload` + dynamic GCD caps + dead-loc guard + metadata | L1436–L1587 | 152 | Cache lookup (`_h_cache`, cap 500k), `LOAD`/`UNLOAD` LB, dynamic weight-GCD cap tightening, entity extraction |
| &emsp;• Sec 2: `h_single` | L1588–L1618 | 31 | Max single-package pickup + delivery cost (using `dist_full`) |
| &emsp;• Sec 3: `h_mst` | L1619–L1668 | 50 | Prim's MST over required pickup/goal nodes on `dist_no_sail` |
| &emsp;• Sec 4: `h_ring_cut` | L1669–L1795 | 127 | Concentric BFS-ball cut sweeps from every `u in req_nodes` on `dist_cut` |
| &emsp;• Sec 5: `h_ton_km` | L1796–L1812 | 17 | Global weight × `dist_no_sail` divided by `max_eff_cap` |
| &emsp;• Sec 5a: `h_road_bridge` (chains + hub-groups/FVS + private goal consolidation) | L1813–L2250 | 438 | Compressed bridge-chain flux, 2-edge-connected bridge-block end-truck conservation + exact/packing min-weight Feedback Vertex Set (L2044–L2193), destination-leaf consolidation trade-off (L2198–L2249) |
| &emsp;• Sec 5b: `non_bridge_drive` | L2252–L2315 | 64 | Per-island road-only MST & free-ferry road ton-km (only on islands with **zero** $G_{rf}$ bridges) |
| &emsp;• Sec 5c: `h_road_ton_km` | L2316–L2360 | 45 | Global road-only ton-km |
| &emsp;• Sec 5d & 6a: Island-level `h_bd` + `h_sail` (Bounds 6.1–6.5) | L2361–L2605 | 245 | Island flux for `BOARD`/`DISEMBARK` (`b1, b2, d1, d2`) and `SAIL` (`sum_s_out`, `sum_s_in`, `bound3`, `bound4`) |
| &emsp;• Sec 6b: Cut-ferry `h_bd` + `bound7_sails` + zero-extra-sail trade-off | L2606–L3214 | **609** | Cut-ferry BD/sail flux (with `ab_stay_w_by_t` casework), sole-ferry port-reach MST, and road-bridge trade-off on sole-ferry non-bridge islands |
| &emsp;• Sec 6c: `bound5_sails` + empty-first-sail + `bound6_sails` + derangement check | L3215–L3431 | 217 | Global ton-sails, empty-first-sail bonus, concentric island-cut (`bound6_sails`), 3/4-island derangement feasibility check |
| &emsp;• Sec 7: Final combination & cache write | L3432–L3474 | 43 | Combines `h_std`, `h_consol`, `h_port_trade` |
| `create_logistics_problem` + `__main__` | L3477–L3485 | 9 | Factory function + debug `print("<<create_logistics_problem")` |

---

### B. Dead Code, Redundancies, Over-Engineering, and Overfitting to `ex1_check.py`

1. **Dead code & leftover artifacts**
   - `import utils` (L17): completely unused.
   - `self.port_ferry_count` (L215): computed and assigned, never read anywhere.
   - `self.no_enter_port` (L234) and `self.ferry_island_masks` (L713): stored on `self` and never read outside `__init__`.
   - `print("<<create_logistics_problem")` (L3478): leftover debug print.
   - **False `use_comp_decomp` bug** (L360–L366): `dead_loc` vertices have empty adjacency lists, so BFS turns each dead-end vertex into its own singleton component, making `num_comps > 1` even when all active locations and packages belong to 1 component. Across all 88 problems in `hard_problems.txt`, `use_comp_decomp` is `True` on **42** problems, of which **40 are fake** (only 2 actually have $\ge 2$ components with packages—Problem 15 pays this scan on every expansion).

2. **Severe overfitting / special-casing to `p/x/y` in `ex1_check.py`**
   - **Zero-extra-sail road-bridge trade-off on sole-ferry non-bridge islands** (L633–L677, L2910–L3210; ~350 lines): Built specifically for `y7` (the only problem in `ex1_check.py` that triggers it). Only **3 of 88** problems in `hard_problems.txt` even build `isl_road_bridges`.
   - **3/4-island derangement feasibility check** (L22–L33, L3348–L3429; ~95 lines): Hardcoded to exact `max_so_si == 1` and `min_sail_count in {3, 4}`—tailored to `y2`/`y4`/`y6`, yet burns 3.6% CPU on Problem 15 with minimal benefit.
   - **Tree/bridge-heavy machinery** (`_precompute_road_bridges`, compressed pure-corridor chains, 2-edge-connected hub groups + inline exact Feedback Vertex Set solver, private-goal-bridge consolidation trade-off; ~720 lines across L812–L1068 & L1813–L2250): In `ex1_check.py`, 6/18 problems are pure road trees (`y3` is a 65-node tree with 15-edge corridors; `y1`, `x2`, `x4`, `x6`, `p3` are trees/stars) and 12/18 have `skip_ring_cut = True`. By contrast, across the 88 `hard_problems.txt` instances, only **4/88** are pure road trees, **23/88** skip `h_ring_cut`, and **53/88** have zero `cut_ferries` (making the entire 609-line cut-ferry section dead on them).

3. **Redundant / self-defeating logic**
   - **`h_ring_cut` vs `h_drive + h_bd`**: On Problem 15, `h_ring_cut` uniquely wins the `max()` on **0.0%** (0/500) of sampled states, yet consumes **19.0%** of total CPU. On Problem 12, it uniquely wins on only **1.6%** (8/500) of states while consuming **25.4%** of total CPU.
   - **`non_bridge_islands_with_roads` (L622–L631)**: Disables per-island road MST & road ton-km on any island that happens to contain *even one* leaf bridge (e.g., all 3 islands of Problem 12 have a single leaf road bridge, so `non_bridge_drive = 0`, throwing away all road-MST lower bounds on the non-bridge spines of all 3 islands).
   - **`bound6_sails` (L3253)**: `if d_max <= 1: continue` means on any 3-island ferry triangle (like Problems 12 and 15), `bound6_sails` loops over `active_isls`, computes `d_max = 1`, and returns `0`.
   - **Overlapping weak relaxations**: `h_ton_km`, `h_road_ton_km`, `h_mst`, `non_bridge_drive`, and `h_ring_cut` all run sequentially on cyclic multi-island maps despite heavy overlap, and none of `h_ring_cut`, `h_ton_km`, or `h_road_ton_km` account for heavy-package incompatibility ($w > C_{\max}/2$) or heterogeneous truck capabilities.

---

## 2. Profiling Results on Problems 7, 12 (15s cap), and 15

Profiled in WSL Ubuntu (Python 3.12.3) via two passes on unmodified `ex1.py`:
- **Pass 1**: Exact replica of `search.astar_search` with manual `time.perf_counter()` instrumentation and 1 kHz `SIGPROF` line-level sampling (wrapper overhead adds ~10–15% to wall-clock time; `h_astar`/`successor` timings exclude wrapper overhead).
- **Pass 2**: Unmodified `search.astar_search` under `cProfile` (15s cap on Problem 12).

### A. Summary Metrics

| Metric | Problem 7 | Problem 12 (15s cap) | Problem 15 |
|---|---:|---:|---:|
| **Topology** | 12 locs, 12 roads (10-cycle + 2 leaves), 0 ferries, 3T, 7P | 13 locs, 10 roads, 3 ferries (3-island ring), 3T, 6P | 12 locs, 8 active roads, 3 ferries (3-island ring), 3T, 5P |
| **`h(start)` vs Optimal Cost** | **32** vs **38** (gap = **6**) | **36** vs **50** (gap = **14**) | **39** vs **55** (gap = **16**) |
| **Reference Time** | 0.2s | 0.4s | 0.7s |
| **Status / Reached `f`** | Solved (`cost = 38`) | Timed out at `f = 44` (6 below opt) | Solved (`cost = 55`) |
| **Pass 1 Wall Time (instrumented)** | 58.48s | 15.00s | 91.87s |
| **Nodes Expanded** | **124,265** | **29,077** *(in 15s)* | **193,309** |
| **Nodes Generated** | **999,358** (avg BF = **8.04**) | **200,224** (avg BF = **6.89**) | **1,017,933** (avg BF = **5.27**) |
| **Popped / Skipped (already closed)** | 335,817 / 211,551 (63.0%) | 88,063 / 58,986 (67.0%) | 558,166 / 364,856 (65.4%) |
| **`h_astar` Calls (Cache Hit Rate)** | 999,358 (55.3% hits; 446,250 misses) | 200,224 (60.3% hits; 79,421 misses) | 1,017,933 (62.4% hits; 382,693 misses) |
| **`h_astar` Total Time (% of total)** | **45.66s (78.1%)** | **11.85s (79.0%)** | **69.61s (75.8%)** |
| **`h_astar` Avg Time / Call (Avg / Miss)** | **45.69 µs** (**96.26 µs / miss**, 4.89 µs / hit) | **59.18 µs** (**145.22 µs / miss**, 2.61 µs / hit) | **68.39 µs** (**170.67 µs / miss**, 6.77 µs / hit) |
| **`successor` Total Time (% of total)** | **2.61s (4.5%)** | **0.77s (5.1%)** | **4.19s (4.6%)** |
| **`successor` Avg Time / Expanded Node** | **21.03 µs** | **26.32 µs** | **21.65 µs** |
| **PQ Push (excl. `h`) + Pop Time** | 5.26s + 1.48s = **6.74s (11.5%)** | 1.17s + 0.42s = **1.59s (10.6%)** | 7.11s + 3.13s = **10.24s (11.1%)** |

### B. Heuristic Component Values at `start`

- **Problem 7** (`opt=38`, `h0=32`): `h_load_unload=14`, `h_single=7`, `h_mst=8`, `h_ring_cut=18`, `h_ton_km=15`, `h_road_bridge=3`, `h_road_ton_km=15`, `h_hub_extra=0`.
- **Problem 12** (`opt=50`, `h0=36`): `h_load_unload=12`, `h_single=11`, `h_mst=9`, `h_ring_cut=11`, `h_ton_km=9`, `h_road_bridge=6`, `non_bridge_drive=0`, `h_bd=6`, `h_sail=12` (`bound3=4`, `bound6=0`, `bound7=0`).
- **Problem 15** (`opt=55`, `h0=39`): `h_load_unload=10`, `h_single=15`, `h_mst=7`, `h_ring_cut=15`, `h_ton_km=15`, `h_road_bridge=8`, `non_bridge_drive=1`, `h_bd=8`, `h_sail=12` (`sum_s_in=4`, `bound6=0`, `bound7=0`).

### C. Top 10 CPU Hotspots

#### Function-level (`cProfile` ordered by `tottime`)

| Rank | Problem 7 (79.4s cProfile) | Problem 12 (15.0s cProfile) | Problem 15 (127.1s cProfile) |
|---:|---|---|---|
| 1 | `ex1.py:h_astar` — **49.88s (62.8%)** | `ex1.py:h_astar` — **9.58s (63.7%)** | `ex1.py:h_astar` — **80.82s (63.6%)** |
| 2 | `ex1.py:successor` — **4.83s (6.1%)** | `ex1.py:successor` — **0.62s (4.2%)** | `ex1.py:successor` — **5.29s (4.2%)** |
| 3 | `search.py:f` — **3.27s (4.1%)** | `{method 'add' of 'set'}` — **0.28s (1.9%)** | `search.py:f` — **5.20s (4.1%)** |
| 4 | `utils.py:update` (`Node.__init__`) — **1.96s (2.5%)** | `_heapq.heappop` — **0.26s (1.7%)** | `search.py:graph_search` — **3.53s (2.8%)** |
| 5 | `_heapq.heappop` — **1.50s (1.9%)** | `utils.py:memoized_fn` — **0.25s (1.7%)** | `_heapq.heappop` — **3.28s (2.6%)** |
| 6 | `utils.py:memoized_fn` — **1.50s (1.9%)** | `{method 'append' of 'list'}` — **0.19s (1.2%)** | `search.py:Node.__eq__` (5.4M calls) — **2.30s (1.8%)** |
| 7 | `{method 'get' of 'dict'}` — **1.45s (1.8%)** | `utils.py:PriorityQueue.append` — **0.18s (1.2%)** | `{method 'get' of 'dict'}` — **2.28s (1.8%)** |
| 8 | `search.py:graph_search` — **1.45s (1.8%)** | `search.py:Node.__eq__` (535k calls) — **0.18s (1.2%)** | `search.py:Node.expand` — **2.20s (1.7%)** |
| 9 | `search.py:Node.expand` — **1.34s (1.7%)** | `utils.py:update` — **0.17s (1.1%)** | `utils.py:memoized_fn` — **2.17s (1.7%)** |
| 10 | `search.py:Node.__eq__` (3.7M calls) — **1.16s (1.5%)** | `search.py:graph_search` / harness — **~0.73s** | `utils.py:update` (`Node.__init__`) — **2.04s (1.6%)** |

#### Section & Line-level inside `ex1.py` (`SIGPROF` 1 kHz sampling)

| Rank | Problem 7 (13,466 samples) | Problem 12 (3,619 samples) | Problem 15 (20,599 samples) |
|---:|---|---|---|
| 1 | **Sec 4 `h_ring_cut`** (L1669–L1795): **37.5%** — L1791 (9.8%), L1712 (5.2%), L1718 (5.1%), L1764 (4.5%) | **Sec 4 `h_ring_cut`**: **25.4%** — L1791 (7.2%), L1718 (3.9%), L1764 (2.8%) | **Sec 4 `h_ring_cut`**: **19.0%** — L1791 (4.9%), L1712 (3.1%), L1718 (2.4%) |
| 2 | **Sec 3 `h_mst`** (L1619–L1668): **11.6%** | **Sec 5d/6 Island passes (`h_bd`/`h_sail`)** (L2361–L2605): **13.6%** — L2574 (2.8%), L2572 (2.6%), L2442 (2.5%) | **Sec 5d/6 Island passes (`h_bd`/`h_sail`)**: **14.2%** — L2572 (3.1%), L2574 (3.0%), L2442 (2.7%) |
| 3 | **Sec 1 `h_load_unload` + metadata** (L1436–L1587): **8.0%** | **Sec 5a `h_road_bridge` chains** (L1813–L1957): **10.3%** | **Sec 5a `h_road_bridge` chains**: **8.0%** |
| 4 | **Sec 5a `h_road_bridge` chains**: **7.9%** | **Sec 3 `h_mst`**: **7.7%** | **Sec 1 `h_load_unload` + metadata**: **7.3%** |
| 5 | `ex1.py:successor`: **3.7%** | **Sec 1 `h_load_unload` + metadata**: **6.7%** | **Sec 3 `h_mst`**: **6.5%** |
| 6 | **Sec 5a `hub_groups` + FVS** (L1958–L2197): **2.7%** | **Sec 5a `hub_groups` + FVS**: **4.4%** | `ex1.py:successor`: **4.1%** |
| 7 | **Sec 2 `h_single`**: **2.6%** | `ex1.py:successor`: **3.3%** | **Sec 6 Derangement check** (L3348–L3431): **3.6%** |
| 8 | **Sec 5c `h_road_ton_km`**: **1.5%** | **Sec 6 `bound6` concentric isl-cut**: **2.7%** | **Sec 5a `hub_groups` + FVS**: **3.5%** |
| 9 | *(search/PQ overhead)* | **Sec 5c `h_road_ton_km`**: **2.1%** | **Sec 5b `non_bridge_drive`**: **3.3%** |
| 10 | *(search/PQ overhead)* | **Sec 2 `h_single`**: **1.6%** | **Sec 6 `bound6` concentric isl-cut**: **2.6%** |

---

## 3. Diagnosis & Simplification Plan

### Diagnosis: **BOTH** — Massive Node Explosion *Multiplied By* a Bloated Per-Node Heuristic

Neither factor alone explains a 70×–250× slowdown relative to the reference times (`0.2s`, `0.4s`, `0.7s`):

1. **Primary Root Cause — Too Many Expanded Nodes (Weak Heuristic on General Maps + High Branching):**
   - Even if `h_astar` cost **0 µs**, the non-heuristic overhead alone (`successor` + `search.py` `Node` creation + `PriorityQueue`) already takes **12.8s** on Problem 7 (64× slower than 0.2s ref) and **22.3s** on Problem 15 (32× slower than 0.7s ref) simply because A* expands **124k–193k** nodes and generates **~1M** nodes.
   - **Three blind spots driving the large `h(start)` gaps (6, 14, 16):**
     1. **No heavy-package incompatibility in general movement bounds**: In Problem 7, five packages have weight `3` with `max_cap = 5` (no two can ever share a truck, so each requires its own full shortest path—sum = `23`, giving `14 + 23 = 37` vs `opt = 38`). Because `h_ton_km` and `h_ring_cut` divide total weight by `5`, they only reach `15` and `18`, leaving a gap of 6 that causes 124k expansions.
     2. **No capability-partitioned / single-truck tour bound for heterogeneous trucks**: In Problem 12, only Truck 10 (`cap=6`) can carry packages 34 and 35 (`w=5`); in Problem 15, only Truck 11 (`cap=4`) can carry packages 31 and 32 (`w=4`). Because `h_single` looks at 1 package at a time and `h_mst`/`h_ton_km`/`h_sail` assume all trucks have `max_eff_cap`, the heuristic misses the mandatory multi-package/multi-island tour of the sole capable truck (missing 10+ units on Problems 12 & 15).
     3. **Ferry rings & non-bridge roads collapse specialized bounds**: Problems 12 and 15 have 3-island ferry rings (`cut_ferries = ()`, `d_max = 1`), so all 609 lines of cut-ferry logic AND `bound6_sails` return **0**, while a single leaf bridge per island disables `non_bridge_drive` across the rest of the island.
   - **Branching factor (`5.3–8.0`) & duplicate generation**: `no_unload_loc` is `False` on almost all nodes of general maps (12/12 in Problem 7), and 63–67% of popped nodes are duplicates already in `closed`.

2. **Secondary Multiplier — Bloated `h_astar` (46–68 µs/call, 96–171 µs/cache-miss, ~77% of CPU):**
   - `h_astar` runs 12+ overlapping sub-heuristics sequentially on every cache miss.
   - `h_ring_cut` alone burns **19–38% of total CPU** while contributing **0.0%** unique wins on Problem 15 and **1.6%** on Problem 12.
   - `successor` is reasonably fast (`21–26 µs/node`, ~4.6% of CPU), though 40/88 hard problems unnecessarily run the `use_comp_decomp` branch due to dead-end singleton components.

---

### Clean, General, 100% Admissible Simplification Plan

Target: cut `ex1.py` from **~3,485 lines to ~500–700 lines**, achieving **~10–25 µs per `h_astar` miss** while cutting expanded nodes by **10×–100×** on general benchmarks and preserving 100% optimality across `ex1_check.py` and `hard_problems.txt`.

1. **Strip Overfit / Low-ROI Complexity (~2,200+ lines removed):**
   - Remove `isl_road_bridges` & zero-extra-sail sole-ferry trade-offs (~350 lines; fires on 3/88 hard problems).
   - Remove `_DERANGEMENTS_3`/`_DERANGEMENTS_4` check (~95 lines).
   - Remove `hub_groups_by_comp` + inline FVS solver + `private_goal_bridges` consolidation (~500+ lines; `<2%` trigger rate on hard benchmarks).
   - Remove `h_ring_cut` (~130 lines + `dist_cut`/`ferry_min_cut`/`ferry_max_cut`) and `bound6_sails` (~110 lines).
   - Simplify `cut_ferries` to a concise ~50-line bridge-cut flux check (removing the 300-line `ab_stay_w_by_t` and `fi_trade` branches) and simplify `road_bridges` (removing 250-line chain/hub precomputation).
   - Remove dead attributes (`port_ferry_count`, `no_enter_port`, `ferry_island_masks`), unused `import utils`, and leftover debug `print`.

2. **Fix `use_comp_decomp` and Streamline `successor`:**
   - Enable `use_comp_decomp` only when `sum(1 for cp in comp_pkgs if cp) >= 2` (eliminating the 40/88 fake triggers).
   - Keep the fast, provably safe reductions: forced canonical `UNLOAD` at goal, dead-end pruning, mid-corridor ample-set, full-ferry ample-set, and empty truck/ferry/package symmetry breaking.
   - Evaluate adding strictly optimality-preserving `UNLOAD` dominance (verified against all `p/x/y` + `hard_problems.txt`).

3. **Replace Weak/Bloated Bounds with 4 Lean, General, High-Impact Admissible Bounds:**
   Keeping the disjoint action partition $A_{LU} \sqcup (A_{\text{drive}} \sqcup A_{bd}) \sqcup A_{\text{sail}}$:
   - **Bound A — Heavy-Package / Weight-Class Disjoint Packing (fixes Problem 7):**
     - Any undelivered packages with $w_i > C_{\max}/2$ are pairwise incompatible (cannot share a truck). Summing their shortest-path distances $\sum_{w_p > C_{\max}/2} d(p, g_p)$ (combined with $\lceil \sum_{\text{all}} w_p d_p / C_{\max} \rceil$ for `dist_no_sail`, `road_dist_free_ferry`, and `min_sails`) is $O(P)$, runs in `<2 µs`, and raises Problem 7's `h(start)` from `32` to `37` (gap `1` vs `6`).
   - **Bound B — Capability-Tier / Exclusive-Truck Tour Lower Bound (fixes Problems 12 & 15):**
     - Partition by distinct truck capacity tiers: when a single truck $t^*$ is the **only** truck capable of carrying a subset of packages $P_{\text{excl}}$ (as in Problem 12 for $w=5$ and Problem 15 for $w=4$), compute an exact small-DP / Held-Karp lower bound on `dist_full` (for $A_{\text{truck}} \cup A_{\text{sail}}$) over $t^*$ and $P_{\text{excl}}$ respecting capacity/heavy-incompatibility (for $|P_{\text{excl}}| \le 5$, takes `<5 µs`).
     - For tiers with $\ge 2$ capable trucks, compute tier-restricted ton-km / MST / ferry-sail bounds using only trucks and ferries usable by that tier.
   - **Bound C — Clean Additive Road + Ferry Cut/Flux Bound (trees, bridges, AND cyclic islands):**
     - Keep lightweight $G_{rf}$ road-bridge flux + **non-bridge-subgraph road MST** (over non-bridge edges on *every* island, rather than skipping an island whenever it has 1 leaf bridge—fixing the Problem 12 bug).
     - Keep concise island-level `h_bd` and `h_sail` (`sum_s_out`, `sum_s_in`, ferry availability `bound3`, heavy-aware ton-sails, and clean 2-way cut-ferry flux).
   - **Bound D — Lightweight `h_mst` + `h_single` + Fast Cache:**
     - Retain fast $O(P + R^2)$ `h_mst` and `h_single` as cheap complements with `_h_cache`.
