import heapq
from collections import deque
import ex1, search

game = {
    "Locations": 3,
    "Roads": [(1, 2)],
    "Ports": [0, 1, 2],
    "Trucks": {10: (1, 1), 11: (2, 4)},
    "Ferries": {20: (2, (0, 1, 2), 2)},
    "Packages": {30: (1, 4, 2), 31: (0, 4, 1)},
}

# Build full unpruned state space + reverse edges
adj_r = {0: [], 1: [2], 2: [1]}
ports = {0, 1, 2}
t_caps = (1, 4)
f_ports = ((0, 1, 2),)
f_caps = (2,)
p_w = (4, 4)
p_g = (2, 1)
s0 = ((1, 2), (2,), (1, 0))

def unpruned_succ(st):
    tl, fl, pl = st
    out = []
    t_load = [0, 0]
    for pi in range(2):
        if pl[pi] < 0:
            t_load[-pl[pi] - 1] += p_w[pi]
    f_cnt = [sum(1 for x in tl if x == -1)]
    for ti in range(2):
        loc = tl[ti]
        if loc < 0:
            out.append((1, (tl[:ti] + (fl[0],) + tl[ti+1:], fl, pl)))
        else:
            for nxt in adj_r[loc]:
                out.append((1, (tl[:ti] + (nxt,) + tl[ti+1:], fl, pl)))
            if loc in ports and fl[0] == loc and f_cnt[0] < f_caps[0]:
                out.append((1, (tl[:ti] + (-1,) + tl[ti+1:], fl, pl)))
            for pi in range(2):
                if pl[pi] == -(ti + 1):
                    out.append((1, (tl, fl, pl[:pi] + (loc,) + pl[pi+1:])))
                elif pl[pi] == loc and t_load[ti] + p_w[pi] <= t_caps[ti]:
                    out.append((1, (tl, fl, pl[:pi] + (-(ti + 1),) + pl[pi+1:])))
    for tp in f_ports[0]:
        if tp != fl[0]:
            out.append((3, (tl, (tp,), pl)))
    return out

# BFS reachable states
rev = {s0: []}
q = deque([s0])
goals = []
while q:
    u = q.popleft()
    if u[2] == p_g:
        goals.append(u)
    for c, v in unpruned_succ(u):
        if v not in rev:
            rev[v] = []
            q.append(v)
        rev[v].append((c, u))

# Reverse Dijkstra from all goal states
dist = {g: 0 for g in goals}
pq = [(0, g) for g in goals]
while pq:
    d, u = heapq.heappop(pq)
    if d > dist[u]:
        continue
    for c, p in rev[u]:
        if d + c < dist.get(p, 10**9):
            dist[p] = d + c
            heapq.heappush(pq, (d + c, p))

prob = ex1.create_logistics_problem(game)
sol = search.astar_search(prob, prob.h_astar)
goal_node = sol[0] if isinstance(sol, tuple) else sol
print(f"Total reachable states: {len(rev)}, true h*(s0)={dist[s0]}, ex1 A* cost={goal_node.path_cost if goal_node else None}")
# Check every reachable state
bad = []
for st, h_star in dist.items():
    h_val = prob.h_astar(search.Node(st))
    if h_val > h_star:
        bad.append((h_val - h_star, h_val, h_star, st))

bad.sort(reverse=True)
print(f"Admissibility violations: {len(bad)}")
for diff, hv, hs, st in bad[:5]:
    print(f"  VIOLATION: state={st} | h={hv} > h*={hs} (diff=+{diff})")
