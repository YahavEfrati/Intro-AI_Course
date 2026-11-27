/-
Module 2: PackingAndFlux.lean

Formalizes and proves the exact integer arithmetic lower bounds from ex1.py:
- Ceiling division matching `(w + cap - 1) // cap if w > 0 else 0`
- Subset-sum effective truck capacities (`eff_truck_caps`, ex1.py:L176-L188) and
  dynamic GCD tightening (`w_gcd`, ex1.py:L1347-L1368), plus top-k ferry weight
  capacity (`max_ferry_weight`, ex1.py:L354-L355, L1356-L1357)
- Heavy+light bin-packing lower bound `_pack_lb` (ex1.py:L54-L63) and its plan-level
  admissibility theorem (covering both `h_pack_truck` and `h_nb`)
- Two-sided cut truck-flux lower bound `_flux_lb` (ex1.py:L66-L93) and its plan-level
  admissibility theorem (covering road bridges, cut ferries, and island cuts).
-/

import Domain

namespace IslandLogistics

-- ==============================================================================
-- 1. CEILING DIVISION & ARITHMETIC HELPERS
-- ==============================================================================

/-- Exact ceiling division matching `(a + cap - 1) // cap if a > 0 else 0` in ex1.py. -/
def ceilDiv (a cap : Nat) : Nat :=
  if a > 0 then (a + (cap - 1)) / cap else 0

theorem ceilDiv_le_of_le_mul {a k cap : Nat} (hcap : 0 < cap) (hle : a ≤ k * cap) :
    ceilDiv a cap ≤ k := by
  unfold ceilDiv
  split
  · rw [Nat.div_le_iff_le_mul_add_pred hcap]
    have h1 : a + (cap - 1) ≤ k * cap + (cap - 1) := Nat.add_le_add_right hle (cap - 1)
    rw [Nat.mul_comm cap k]
    omega
  · exact Nat.zero_le k

theorem ceilDiv_mono {a b cap : Nat} (hle : a ≤ b) : ceilDiv a cap ≤ ceilDiv b cap := by
  unfold ceilDiv
  split
  · rename_i ha
    have hb : b > 0 := Nat.lt_of_lt_of_le ha hle
    simp only [hb, ↓reduceIte]
    exact Nat.div_le_div_right (Nat.add_le_add_right hle (cap - 1))
  · exact Nat.zero_le _

theorem ceilDiv_zero_left (cap : Nat) : ceilDiv 0 cap = 0 := by
  simp [ceilDiv]

-- ==============================================================================
-- 2. SUBSET-SUM EFFECTIVE CAPACITIES & DYNAMIC GCD TIGHTENING
--    (Matches ex1.py:L176-L188, L354-L355, L1347-L1368)
-- ==============================================================================

/-- Total weight of a boolean subset `mask` of `Fin n`. -/
def subsetWeight {n : Nat} (w : Fin n → Nat) (mask : Fin n → Bool) : Nat :=
  finSum (fun i => if mask i then w i else 0)

/-- Exact subset-sum DP reachability over a list of weights `ws`, matching `ex1.py:L177-L180`. -/
def reachableSumsList (ws : List Nat) (cap : Nat) : List Nat :=
  ws.foldl (fun acc w =>
    if 0 < w ∧ w ≤ cap then
      acc ++ (acc.map (· + w)).filter (· ≤ cap)
    else acc) [0]

theorem subset_sum_mem_reachableSumsList (ws : List Nat) (cap : Nat) :
    ∀ (chosen : List Bool), chosen.length = ws.length →
      let s := (ws.zip chosen).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0
      s ≤ cap → s ∈ reachableSumsList ws cap := by
  unfold reachableSumsList
  suffices ∀ (ws : List Nat) (acc : List Nat) (chosen : List Bool),
      chosen.length = ws.length →
      ∀ base ∈ acc,
      let s := base + (ws.zip chosen).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0
      s ≤ cap →
      s ∈ ws.foldl (fun acc w =>
        if 0 < w ∧ w ≤ cap then acc ++ (acc.map (· + w)).filter (· ≤ cap) else acc) acc by
    intro chosen hlen s hs
    have h := this ws [0] chosen hlen 0 (by simp) (by simpa [s] using hs)
    simpa [s] using h
  intro ws
  induction ws with
  | nil =>
    intro acc chosen hlen base hbase s hs
    cases chosen with
    | nil => simpa [s] using hbase
    | cons _ _ => simp at hlen
  | cons w rest ih =>
    intro acc chosen hlen base hbase
    cases chosen with
    | nil => simp at hlen
    | cons b brest =>
      simp only [List.length_cons, Nat.add_right_cancel_iff] at hlen
      simp only [List.zip_cons_cons, List.foldr_cons, List.foldl_cons]
      intro hs
      cases b with
      | false =>
        simp only [Bool.false_eq_true, ↓reduceIte] at hs ⊢
        apply ih _ brest hlen base
        · split
          · exact List.mem_append_left _ hbase
          · exact hbase
        · exact hs
      | true =>
        simp only [↓reduceIte] at hs ⊢
        by_cases hw0 : w = 0
        · subst hw0
          have hrew : base + (0 + (rest.zip brest).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0) =
                      base + (rest.zip brest).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0 := by omega
          rw [hrew]
          apply ih _ brest hlen base
          · split
            · exact List.mem_append_left _ hbase
            · exact hbase
          · omega
        · have hwpos : 0 < w := Nat.pos_of_ne_zero hw0
          have hwle : w ≤ cap := by omega
          have hcond : 0 < w ∧ w ≤ cap := ⟨hwpos, hwle⟩
          simp only [hcond]
          have hbw : base + w ≤ cap := by omega
          have hmem_bw : base + w ∈ acc ++ (acc.map (· + w)).filter (· ≤ cap) := by
            apply List.mem_append_right
            rw [List.mem_filter]
            refine ⟨List.mem_map.mpr ⟨base, hbase, rfl⟩, decide_eq_true hbw⟩
          have hrew : base + (w + (rest.zip brest).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0) =
                      (base + w) + (rest.zip brest).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0 := by omega
          rw [hrew]
          exact ih _ brest hlen (base + w) hmem_bw (by omega)

/-- Maximum element of a `List Nat` (0 if empty). -/
def listMax : List Nat → Nat
  | []      => 0
  | x :: xs => max x (listMax xs)

theorem mem_le_listMax {l : List Nat} {x : Nat} (h : x ∈ l) : x ≤ listMax l := by
  induction l with
  | nil => cases h
  | cons y ys ih =>
    simp only [listMax]
    rcases List.mem_cons.mp h with rfl | hys
    · exact Nat.le_max_left _ _
    · exact Nat.le_trans (ih hys) (Nat.le_max_right _ _)

/-- Subset-sum effective capacity of capacity `c`, matching `ex1.py:L176-L188`. -/
def effCap (I : Instance) (c : Nat) : Nat :=
  listMax (reachableSumsList ((List.finRange I.numPkgs).map I.pkgWeight) c)

theorem subsetWeight_le_effCap (I : Instance) (c : Nat) (mask : Fin I.numPkgs → Bool)
    (hle : subsetWeight I.pkgWeight mask ≤ c) :
    subsetWeight I.pkgWeight mask ≤ effCap I c := by
  unfold effCap
  apply mem_le_listMax
  have hlen : ((List.finRange I.numPkgs).map mask).length =
              ((List.finRange I.numPkgs).map I.pkgWeight).length := by simp
  have hmem := subset_sum_mem_reachableSumsList
    ((List.finRange I.numPkgs).map I.pkgWeight) c ((List.finRange I.numPkgs).map mask) hlen
  have hsum_eq :
      (((List.finRange I.numPkgs).map I.pkgWeight).zip ((List.finRange I.numPkgs).map mask)).foldr
        (fun p acc => if p.2 then p.1 + acc else acc) 0 =
      subsetWeight I.pkgWeight mask := by
    unfold subsetWeight finSum
    suffices ∀ l : List (Fin I.numPkgs),
        ((l.map I.pkgWeight).zip (l.map mask)).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0 =
        l.foldr (fun i acc => (if mask i then I.pkgWeight i else 0) + acc) 0
      from this (List.finRange I.numPkgs)
    intro l
    induction l with
    | nil => rfl
    | cons x xs ih =>
      simp only [List.map_cons, List.zip_cons_cons, List.foldr_cons, ih]
      cases mask x <;> simp
  rw [hsum_eq] at hmem
  exact hmem hle

/-- GCD of a list of natural numbers (0 if empty). -/
def listGcd : List Nat → Nat
  | []      => 0
  | x :: xs => Nat.gcd x (listGcd xs)

theorem listGcd_dvd {l : List Nat} {x : Nat} (h : x ∈ l) : listGcd l ∣ x := by
  induction l with
  | nil => cases h
  | cons y ys ih =>
    simp only [listGcd]
    rcases List.mem_cons.mp h with rfl | hys
    · exact Nat.gcd_dvd_left _ _
    · exact Nat.dvd_trans (Nat.gcd_dvd_right _ _) (ih hys)

/-- Dynamic GCD of all undelivered package weights in state `s` (`ex1.py:L1349-L1351`). -/
def undelivGcd (I : Instance) (s : State I) : Nat :=
  listGcd (((List.finRange I.numPkgs).filter (fun p => !s.pkgDelivered p)).map I.pkgWeight)

theorem undelivGcd_dvd (I : Instance) (s : State I) (p : Fin I.numPkgs)
    (hu : s.pkgDelivered p = false) : undelivGcd I s ∣ I.pkgWeight p := by
  unfold undelivGcd
  apply listGcd_dvd
  rw [List.mem_map]
  refine ⟨p, ?_, rfl⟩
  rw [List.mem_filter]
  exact ⟨List.mem_finRange p, by simp [hu]⟩

/-- Initial GCD over all packages (`init_w_gcd`, `ex1.py:L189`). -/
def initWGcd (I : Instance) : Nat :=
  listGcd ((List.finRange I.numPkgs).map I.pkgWeight)

/-- Dynamic GCD-tightened effective truck capacity matching `ex1.py:L1352-L1365`. -/
def dynEffCap (I : Instance) (s : State I) (t : Fin I.numTrucks) : Nat :=
  let base := effCap I (I.truckCap t)
  let g := undelivGcd I s
  if g > initWGcd I then (base / g) * g else base

theorem le_div_mul_of_dvd {w c g : Nat} (hdvd : g ∣ w) (hle : w ≤ c) :
    w ≤ (c / g) * g := by
  by_cases hg : g = 0
  · subst hg
    rcases hdvd with ⟨k, hk⟩
    simp at hk
    omega
  · rcases hdvd with ⟨k, rfl⟩
    have hgpos : 0 < g := Nat.pos_of_ne_zero hg
    have hk : k ≤ c / g := by
      rw [Nat.le_div_iff_mul_le hgpos]
      simpa [Nat.mul_comm] using hle
    have hmul := Nat.mul_le_mul_right g hk
    simpa [Nat.mul_comm] using hmul

theorem dvd_finSum {n g : Nat} {f : Fin n → Nat} (h : ∀ i, g ∣ f i) : g ∣ finSum f := by
  simp only [finSum_eq_list_sum]
  suffices ∀ l : List (Fin n), g ∣ (l.map f).sum from this (List.finRange n)
  intro l
  induction l with
  | nil => simp
  | cons x xs ih =>
    simp only [List.map_cons, List.sum_cons]
    exact Nat.dvd_add (h x) ih

/-- Core effective-capacity theorem (`ex1.py:L176-L188, L1347-L1368`):
    Any subset `mask` of `s`-undelivered packages fitting in `I.truckCap t`
    has total weight `≤ dynEffCap I s t`. -/
theorem subsetWeight_undeliv_le_dynEffCap (I : Instance) (s : State I) (t : Fin I.numTrucks)
    (mask : Fin I.numPkgs → Bool)
    (hundeliv : ∀ p, mask p = true → s.pkgDelivered p = false)
    (hle : subsetWeight I.pkgWeight mask ≤ I.truckCap t) :
    subsetWeight I.pkgWeight mask ≤ dynEffCap I s t := by
  have hbase : subsetWeight I.pkgWeight mask ≤ effCap I (I.truckCap t) :=
    subsetWeight_le_effCap I (I.truckCap t) mask hle
  unfold dynEffCap
  dsimp only
  split
  · apply le_div_mul_of_dvd _ hbase
    unfold subsetWeight
    apply dvd_finSum
    intro p
    cases hm : mask p with
    | false => simp
    | true =>
      simp only [↓reduceIte]
      exact undelivGcd_dvd I s p (hundeliv p hm)
  · exact hbase

/-- Any truck's load of `s`-undelivered packages in ANY valid state `s'` is `≤ dynEffCap I s t`. -/
theorem truckLoad_undeliv_le_dynEffCap {I : Instance} {s s' : State I}
    (hv' : ValidState I s') (t : Fin I.numTrucks) :
    finSum (fun p => if !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
      ≤ dynEffCap I s t := by
  let mask : Fin I.numPkgs → Bool := fun p => !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t)
  change subsetWeight I.pkgWeight mask ≤ dynEffCap I s t
  apply subsetWeight_undeliv_le_dynEffCap I s t mask
  · intro p hm
    simp only [mask, Bool.and_eq_true, Bool.not_eq_true'] at hm
    exact hm.1
  · have hsub : subsetWeight I.pkgWeight mask ≤ s'.truckLoad t := by
      unfold subsetWeight State.truckLoad
      apply finSum_le_finSum
      intro p
      cases hu : s.pkgDelivered p <;> by_cases hp : s'.pkgLoc p = .inTruck t <;> simp [mask, hu, hp]
    exact Nat.le_trans hsub (hv'.load_le_cap t)

/-- Maximum dynamic effective truck capacity across all trucks (`max_cap`, `ex1.py:L1359`). -/
def maxDynEffCap (I : Instance) (s : State I) : Nat :=
  listMax ((List.finRange I.numTrucks).map (dynEffCap I s))

theorem dynEffCap_le_maxDynEffCap (I : Instance) (s : State I) (t : Fin I.numTrucks) :
    dynEffCap I s t ≤ maxDynEffCap I s := by
  unfold maxDynEffCap
  apply mem_le_listMax
  exact List.mem_map.mpr ⟨t, List.mem_finRange t, rfl⟩

-- ==============================================================================
-- 3. TOP-K FERRY WEIGHT CAPACITY (`max_ferry_weight`, ex1.py:L354-L355, L1356-L1357)
-- ==============================================================================

def insertDesc (x : Nat) : List Nat → List Nat
  | []      => [x]
  | y :: ys => if x ≥ y then x :: y :: ys else y :: insertDesc x ys

def sortDesc : List Nat → List Nat
  | []      => []
  | x :: xs => insertDesc x (sortDesc xs)

/-- Sum of the `k` largest elements of `xs` (`sum(sorted(ec, reverse=True)[:k])`). -/
def topKSum (xs : List Nat) (k : Nat) : Nat :=
  ((sortDesc xs).take k).sum

def IsDesc : List Nat → Prop
  | [] => True
  | [_] => True
  | x :: y :: rest => x ≥ y ∧ IsDesc (y :: rest)

theorem isDesc_insertDesc {x : Nat} {l : List Nat} (hl : IsDesc l) : IsDesc (insertDesc x l) := by
  induction l with
  | nil => trivial
  | cons y ys ih =>
    simp only [insertDesc]
    split
    · rename_i hxy
      exact ⟨hxy, hl⟩
    · rename_i hxy
      cases ys with
      | nil =>
        exact ⟨by omega, trivial⟩
      | cons z zs =>
        have ⟨hyz, hzs⟩ := hl
        have hrec := ih hzs
        simp only [insertDesc] at hrec ⊢
        by_cases hxz : x ≥ z
        · simp only [hxz, ↓reduceIte] at hrec ⊢
          exact ⟨by omega, hrec⟩
        · simp only [hxz, ↓reduceIte] at hrec ⊢
          exact ⟨hyz, hrec⟩

theorem isDesc_sortDesc (l : List Nat) : IsDesc (sortDesc l) := by
  induction l with
  | nil => trivial
  | cons x xs ih => exact isDesc_insertDesc ih

theorem take_sum_le_cons_of_isDesc {y : Nat} {ys : List Nat} (hd : IsDesc (y :: ys)) (k : Nat) :
    (ys.take k).sum ≤ ((y :: ys).take k).sum := by
  induction ys generalizing y k with
  | nil =>
    cases k <;> simp
  | cons z zs ih =>
    cases k with
    | zero => simp
    | succ k' =>
      have ⟨hyz, hzs⟩ := hd
      simp only [List.take_succ_cons, List.sum_cons]
      have hrec := ih hzs k'
      omega

theorem take_sum_le_insertDesc_take_sum {x : Nat} {l : List Nat} (hd : IsDesc l) (k : Nat) :
    (l.take k).sum ≤ ((insertDesc x l).take k).sum := by
  induction l generalizing k with
  | nil =>
    cases k <;> simp [insertDesc]
  | cons y ys ih =>
    cases k with
    | zero => simp
    | succ k' =>
      simp only [insertDesc]
      split
      · rename_i hxy
        simp only [List.take_succ_cons, List.sum_cons]
        have hstep := take_sum_le_cons_of_isDesc hd k'
        omega
      · simp only [List.take_succ_cons, List.sum_cons]
        have hys : IsDesc ys := by cases ys <;> simp [IsDesc] at hd ⊢; exact hd.2
        have := ih hys k'
        omega

theorem add_take_sum_le_insertDesc_take_succ {x : Nat} {l : List Nat} (hd : IsDesc l) (k : Nat) :
    x + (l.take k).sum ≤ ((insertDesc x l).take (k + 1)).sum := by
  induction l generalizing k with
  | nil => simp [insertDesc]
  | cons y ys ih =>
    simp only [insertDesc]
    split
    · simp only [List.take_succ_cons, List.sum_cons]
      omega
    · rename_i hxy
      cases k with
      | zero =>
        simp only [List.take_zero, List.sum_nil, Nat.add_zero, List.take_succ_cons, List.sum_cons]
        omega
      | succ k' =>
        simp only [List.take_succ_cons, List.sum_cons]
        have hys : IsDesc ys := by cases ys <;> simp [IsDesc] at hd ⊢; exact hd.2
        have hrec := ih hys k'
        omega

theorem take_sum_mono_k (l : List Nat) {k₁ k₂ : Nat} (hle : k₁ ≤ k₂) :
    (l.take k₁).sum ≤ (l.take k₂).sum := by
  induction l generalizing k₁ k₂ with
  | nil => simp
  | cons y ys ih =>
    cases k₁ with
    | zero => simp
    | succ k₁' =>
      cases k₂ with
      | zero => omega
      | succ k₂' =>
        simp only [List.take_succ_cons, List.sum_cons]
        have := ih (by omega : k₁' ≤ k₂')
        omega

/-- Any subset of at most `k` elements from `xs` has sum `≤ topKSum xs k`. -/
theorem sublist_subset_sum_le_topKSum (xs : List Nat) (chosen : List Bool)
    (hlen : chosen.length = xs.length) :
    let cnt := (chosen.map (fun b => if b then 1 else 0)).sum
    let total := (xs.zip chosen).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0
    total ≤ topKSum xs cnt := by
  unfold topKSum
  induction xs generalizing chosen with
  | nil =>
    cases chosen with
    | nil => simp [sortDesc]
    | cons _ _ => simp at hlen
  | cons x rest ih =>
    cases chosen with
    | nil => simp at hlen
    | cons b brest =>
      simp only [List.length_cons, Nat.add_right_cancel_iff] at hlen
      have hrec := ih brest hlen
      dsimp only at hrec ⊢
      simp only [List.map_cons, List.sum_cons, List.zip_cons_cons, List.foldr_cons, sortDesc]
      have hd : IsDesc (sortDesc rest) := isDesc_sortDesc rest
      cases b with
      | false =>
        simp only [Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
        exact Nat.le_trans hrec (take_sum_le_insertDesc_take_sum hd _)
      | true =>
        simp only [↓reduceIte]
        have hadd := add_take_sum_le_insertDesc_take_succ (x := x) hd
          ((brest.map (fun b => if b then 1 else 0)).sum)
        have h1 : 1 + (brest.map (fun b => if b then 1 else 0)).sum =
                  (brest.map (fun b => if b then 1 else 0)).sum + 1 := by omega
        rw [h1]
        omega

/-- Maximum undelivered package weight ferry `f` can carry (`max_ferry_weight`, `ex1.py:L355, L1357`). -/
def maxFerryWeight (I : Instance) (s : State I) (f : Fin I.numFerries) : Nat :=
  topKSum ((List.finRange I.numTrucks).map (dynEffCap I s)) (min (I.ferryCap f) I.numTrucks)

/-- For any subset of trucks `mask` of size `≤ k`, their summed `dynEffCap` is `≤ topKSum ... k`. -/
theorem truck_subset_dynEffCap_le_topKSum (I : Instance) (s : State I)
    (mask : Fin I.numTrucks → Bool) (k : Nat)
    (hcnt : finSum (fun t => if mask t then 1 else 0) ≤ k) :
    finSum (fun t => if mask t then dynEffCap I s t else 0) ≤
    topKSum ((List.finRange I.numTrucks).map (dynEffCap I s)) k := by
  let xs := (List.finRange I.numTrucks).map (dynEffCap I s)
  let chosen := (List.finRange I.numTrucks).map mask
  have hlen : chosen.length = xs.length := by simp [xs, chosen]
  have hsub := sublist_subset_sum_le_topKSum xs chosen hlen
  dsimp only at hsub
  have hcnt_eq : (chosen.map (fun b => if b then 1 else 0)).sum =
                 finSum (fun t => if mask t then 1 else 0) := by
    simp only [chosen, List.map_map, finSum_eq_list_sum]
    rfl
  have htot_eq : (xs.zip chosen).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0 =
                 finSum (fun t => if mask t then dynEffCap I s t else 0) := by
    simp only [xs, chosen, finSum]
    suffices ∀ l : List (Fin I.numTrucks),
        ((l.map (dynEffCap I s)).zip (l.map mask)).foldr (fun p acc => if p.2 then p.1 + acc else acc) 0 =
        l.foldr (fun i acc => (if mask i then dynEffCap I s i else 0) + acc) 0
      from this (List.finRange I.numTrucks)
    intro l
    induction l with
    | nil => rfl
    | cons t ts ih =>
      simp only [List.map_cons, List.zip_cons_cons, List.foldr_cons, ih]
      cases mask t <;> simp
  rw [hcnt_eq, htot_eq] at hsub
  exact Nat.le_trans hsub (take_sum_mono_k _ hcnt)

/-- In any valid state `s'`, total weight of `s`-undelivered packages aboard ferry `f`
    is `≤ maxFerryWeight I s f`. -/
theorem ferryLoad_undeliv_le_maxFerryWeight {I : Instance} {s s' : State I}
    (hv' : ValidState I s') (f : Fin I.numFerries) :
    finSum (fun p => if !s.pkgDelivered p && (s'.pkgOnFerry p == some f) then I.pkgWeight p else 0)
      ≤ maxFerryWeight I s f := by
  -- Regroup package weights by carrier truck aboard ferry f
  have hregroup :
      finSum (fun p => if !s.pkgDelivered p && (s'.pkgOnFerry p == some f) then I.pkgWeight p else 0) =
      finSum (fun t =>
        if s'.truckLoc t = .onFerry f then
          finSum (fun p => if !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
        else 0) := by
    rw [show finSum (fun t =>
        if s'.truckLoc t = .onFerry f then
          finSum (fun p => if !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
        else 0) =
        finSum (fun t => finSum (fun p =>
          if s'.truckLoc t = .onFerry f then
            if !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t) then I.pkgWeight p else 0
          else 0)) from by
      congr 1; funext t; split
      · rfl
      · exact (finSum_zero).symm]
    rw [finSum_comm]
    congr 1
    funext p
    cases hpl : s'.pkgLoc p with
    | atLoc l =>
      simp [State.pkgOnFerry, hpl]
      exact (finSum_zero).symm
    | inTruck t =>
      simp only [State.pkgOnFerry, State.truckOnFerry, hpl]
      have hfn : (fun t' => if s'.truckLoc t' = .onFerry f then
          if !s.pkgDelivered p && (PkgPos.inTruck t == PkgPos.inTruck t') then I.pkgWeight p else 0 else 0) =
          (fun t' => if t' = t then
            (if s'.truckLoc t = .onFerry f then if !s.pkgDelivered p then I.pkgWeight p else 0 else 0) else 0) := by
        funext t'
        by_cases ht : t' = t
        · subst ht; simp
        · have hne : (PkgPos.inTruck t == PkgPos.inTruck t') = false := by
            simp [Ne.symm ht]
          simp [ht, hne]
      rw [hfn, finSum_ite_eq]
      cases htl : s'.truckLoc t with
      | atLoc l => simp
      | onFerry f' =>
        by_cases hf : f' = f <;> cases s.pkgDelivered p <;> simp [hf]
  rw [hregroup]
  have hle_caps :
      finSum (fun t =>
        if s'.truckLoc t = .onFerry f then
          finSum (fun p => if !s.pkgDelivered p && (s'.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
        else 0) ≤
      finSum (fun t => if decide (s'.truckLoc t = .onFerry f) then dynEffCap I s t else 0) := by
    apply finSum_le_finSum
    intro t
    by_cases h : s'.truckLoc t = .onFerry f
    · simp only [h, ↓reduceIte, decide_true]
      exact truckLoad_undeliv_le_dynEffCap hv' t
    · simp [h]
  apply Nat.le_trans hle_caps
  unfold maxFerryWeight
  apply truck_subset_dynEffCap_le_topKSum
  have hcnt1 : finSum (fun t => if decide (s'.truckLoc t = .onFerry f) then 1 else 0) ≤ I.ferryCap f := by
    have heq : finSum (fun t => if decide (s'.truckLoc t = .onFerry f) then 1 else 0) = s'.ferryCount f := by
      unfold State.ferryCount
      congr 1; funext t; by_cases h : s'.truckLoc t = .onFerry f <;> simp [h]
    rw [heq]
    exact hv'.aboard_le_cap f
  have hcnt2 : finSum (fun t => if decide (s'.truckLoc t = .onFerry f) then 1 else 0) ≤ I.numTrucks := by
    have h1 : finSum (fun t : Fin I.numTrucks => if decide (s'.truckLoc t = .onFerry f) then 1 else 0) ≤
              finSum (fun _ : Fin I.numTrucks => 1) := by
      apply finSum_le_finSum; intro t; split <;> omega
    have h2 : finSum (fun _ : Fin I.numTrucks => 1) = I.numTrucks := by
      simp only [finSum_eq_list_sum]
      suffices ∀ l : List (Fin I.numTrucks), (l.map (fun _ => 1)).sum = l.length by
        rw [this (List.finRange I.numTrucks), List.length_finRange]
      intro l; induction l with | nil => rfl | cons _ _ ih => simp [ih]; omega
    omega
  exact Nat.le_min.mpr ⟨hcnt1, hcnt2⟩

-- ==============================================================================
-- 4. HEAVY + LIGHT BIN-PACKING LOWER BOUND (`_pack_lb`, ex1.py:L54-L63)
-- ==============================================================================

/-- Exact `_pack_lb` matching `ex1.py:L54-L63` verbatim. -/
def packLB (heavy_d min_hw light_wd total_wd cap : Nat) : Nat :=
  let cm1 := cap - 1
  let lb := if total_wd > 0 then (total_wd + cm1) / cap else 0
  if heavy_d > 0 then
    let rem := light_wd - (cap - min_hw) * heavy_d
    let cand := heavy_d + (if rem > 0 then (rem + cm1) / cap else 0)
    if cand > lb then cand else lb
  else lb

/-- At most one heavy package (`w > cap / 2`) can fit inside total weight `≤ cap`. -/
theorem at_most_one_heavy {n : Nat} (w : Fin n → Nat) (mask : Fin n → Bool) (cap : Nat)
    (hle : subsetWeight w mask ≤ cap) :
    finSum (fun i => if mask i && decide (w i > cap / 2) then 1 else 0) ≤ 1 := by
  by_cases hle1 : finSum (fun i => if mask i && decide (w i > cap / 2) then 1 else 0) ≤ 1
  · exact hle1
  · exfalso
    have hge2 : finSum (fun i => if mask i && decide (w i > cap / 2) then 1 else 0) ≥ 2 := by omega
    have hsum_heavy :
        finSum (fun i => if mask i && decide (w i > cap / 2) then w i else 0) ≥
        (cap / 2 + 1) * finSum (fun i => if mask i && decide (w i > cap / 2) then 1 else 0) := by
      rw [← finSum_mul_left]
      apply finSum_le_finSum
      intro i
      cases hm : mask i <;> by_cases hw : w i > cap / 2 <;> simp [hm, hw] <;> omega
    have hsub :
        finSum (fun i => if mask i && decide (w i > cap / 2) then w i else 0) ≤ subsetWeight w mask := by
      unfold subsetWeight
      apply finSum_le_finSum
      intro i
      cases hm : mask i <;> by_cases hw : w i > cap / 2 <;> simp [hm, hw]
    have hmul : (cap / 2 + 1) * 2 ≤ (cap / 2 + 1) *
        finSum (fun i => if mask i && decide (w i > cap / 2) then 1 else 0) :=
      Nat.mul_le_mul_left _ hge2
    omega

/-- Abstract soundness of `packLB` (`ex1.py:L54-L63`):
    For any list of `K` steps, each carrying a subset of packages of total weight `≤ cap`,
    where every carried heavy package (`w > cap / 2`) has `min_hw ≤ w`,
    `packLB heavy_d min_hw light_wd total_wd cap ≤ steps.length`. -/
theorem packLB_abstract_sound {n : Nat} (w : Fin n → Nat) (cap : Nat) (hcap : 0 < cap)
    (steps : List (Fin n → Bool))
    (hstep_cap : ∀ m ∈ steps, subsetWeight w m ≤ cap)
    (heavy_d min_hw light_wd total_wd : Nat)
    (hmin_hw : ∀ m ∈ steps, ∀ i, m i = true → w i > cap / 2 → min_hw ≤ w i)
    (hheavy : heavy_d ≤ (steps.map (fun m =>
        finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0))).sum)
    (hlight : light_wd ≤ (steps.map (fun m =>
        finSum (fun i => if m i && decide (w i ≤ cap / 2) then w i else 0))).sum)
    (htotal : total_wd ≤ (steps.map (fun m => subsetWeight w m)).sum) :
    packLB heavy_d min_hw light_wd total_wd cap ≤ steps.length := by
  -- 1. Volume bound: total_wd ≤ steps.length * cap
  have hvol : total_wd ≤ steps.length * cap := by
    apply Nat.le_trans htotal
    clear htotal hheavy hlight hmin_hw
    induction steps with
    | nil => simp
    | cons m ms ih =>
      simp only [List.map_cons, List.sum_cons, List.length_cons]
      have hm := hstep_cap m (List.mem_cons_self ..)
      have hms := ih (fun m' hm' => hstep_cap m' (List.mem_cons_of_mem _ hm'))
      have : (ms.length + 1) * cap = ms.length * cap + cap := by rw [Nat.add_mul, Nat.one_mul]
      omega
  have hlb1 : (if total_wd > 0 then (total_wd + (cap - 1)) / cap else 0) ≤ steps.length :=
    ceilDiv_le_of_le_mul hcap hvol

  -- 2. Heavy+light packing bound
  unfold packLB
  dsimp only
  split
  · rename_i hhd_pos
    -- Split steps into H (carrying a heavy pkg) and L (carrying no heavy pkg)
    let isH (m : Fin n → Bool) : Bool :=
      decide (finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0) ≥ 1)
    let H := (steps.map (fun m => if isH m then 1 else 0)).sum
    let L := (steps.map (fun m => if !isH m then 1 else 0)).sum
    have hHL : H + L = steps.length := by
      dsimp only [H, L]
      clear hvol hlb1 hheavy hlight htotal hmin_hw hstep_cap
      induction steps with
      | nil => simp
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons, List.length_cons]
        cases h : isH m with
        | false => simp only [Bool.false_eq_true, Bool.not_false, ↓reduceIte]; omega
        | true => simp only [Bool.not_true, Bool.false_eq_true, ↓reduceIte]; omega
    have hheavy_le_H : heavy_d ≤ H := by
      apply Nat.le_trans hheavy
      dsimp only [H, isH]
      clear hvol hlb1 hheavy hlight htotal hmin_hw hHL H L
      induction steps with
      | nil => simp
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons]
        have hm1 := at_most_one_heavy w m cap (hstep_cap m (List.mem_cons_self ..))
        have hms := ih (fun m' hm' => hstep_cap m' (List.mem_cons_of_mem _ hm'))
        by_cases h1 : finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0) ≥ 1
        · simp only [h1, decide_true, ↓reduceIte]; omega
        · simp only [h1, decide_false, Bool.false_eq_true, ↓reduceIte]; omega
    -- Bound light weight per step: if isH m then ≤ cap - min_hw, else ≤ cap
    have hlight_bound : light_wd ≤ (cap - min_hw) * H + cap * L := by
      apply Nat.le_trans hlight
      dsimp only [H, L]
      clear hvol hlb1 hheavy hlight htotal hHL hheavy_le_H H L
      induction steps with
      | nil => simp
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons]
        have hm_cap := hstep_cap m (List.mem_cons_self ..)
        have hms := ih
          (fun m' hm' => hstep_cap m' (List.mem_cons_of_mem _ hm'))
          (fun m' hm' => hmin_hw m' (List.mem_cons_of_mem _ hm'))
        -- Split subsetWeight w m into heavy + light
        have hsplit :
            subsetWeight w m =
            finSum (fun i => if m i && decide (w i > cap / 2) then w i else 0) +
            finSum (fun i => if m i && decide (w i ≤ cap / 2) then w i else 0) := by
          unfold subsetWeight
          rw [← finSum_add]
          congr 1; funext i
          cases hm : m i <;> by_cases hw : w i > cap / 2
          · simp [hm]
          · simp [hm]
          · have hnot : ¬ (w i ≤ cap / 2) := by omega
            simp [hm, hw, hnot]
          · have hle' : w i ≤ cap / 2 := by omega
            simp [hm, hw, hle']
        cases hH : isH m with
        | false =>
          simp only [Bool.false_eq_true, ↓reduceIte, Bool.not_false, Nat.zero_add]
          have hmul : cap * (1 + (ms.map (fun m => if !isH m then 1 else 0)).sum) =
                      cap + cap * (ms.map (fun m => if !isH m then 1 else 0)).sum := by
            rw [Nat.mul_add, Nat.mul_one]
          rw [hmul]
          omega
        | true =>
          simp only [↓reduceIte, Bool.not_true, Bool.false_eq_true, Nat.zero_add]
          -- Since isH m = true, some heavy package is in m, so heavy sum ≥ min_hw
          have hge1 : finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0) ≥ 1 := by
            simp only [isH, decide_eq_true_eq] at hH; exact hH
          have hheavy_ge_min : min_hw ≤ finSum (fun i => if m i && decide (w i > cap / 2) then w i else 0) := by
            have h1 : min_hw * finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0) ≤
                      finSum (fun i => if m i && decide (w i > cap / 2) then w i else 0) := by
              rw [← finSum_mul_left]
              apply finSum_le_finSum
              intro i
              cases hm : m i with
              | false => simp
              | true =>
                by_cases hw : w i > cap / 2
                · simp only [hw, decide_true, Bool.and_self, ↓reduceIte, Nat.mul_one]
                  exact hmin_hw m (List.mem_cons_self ..) i hm hw
                · simp [hw]
            have h2 : min_hw ≤ min_hw * finSum (fun i => if m i && decide (w i > cap / 2) then 1 else 0) := by
              calc min_hw = min_hw * 1 := (Nat.mul_one _).symm
                _ ≤ min_hw * _ := Nat.mul_le_mul_left _ hge1
            omega
          have hmul : (cap - min_hw) * (1 + (ms.map (fun m => if isH m then 1 else 0)).sum) =
                      (cap - min_hw) + (cap - min_hw) * (ms.map (fun m => if isH m then 1 else 0)).sum := by
            rw [Nat.mul_add, Nat.mul_one]
          rw [hmul]
          omega
    -- Now let delta = H - heavy_d ≥ 0; since cap - min_hw ≤ cap:
    -- light_wd - (cap - min_hw) * heavy_d ≤ (delta + L) * cap
    have hrem : light_wd - (cap - min_hw) * heavy_d ≤ (H - heavy_d + L) * cap := by
      have hdecomp : H = heavy_d + (H - heavy_d) := by omega
      have h1 : (cap - min_hw) * H = (cap - min_hw) * heavy_d + (cap - min_hw) * (H - heavy_d) := by
        calc (cap - min_hw) * H = (cap - min_hw) * (heavy_d + (H - heavy_d)) := by rw [← hdecomp]
          _ = (cap - min_hw) * heavy_d + (cap - min_hw) * (H - heavy_d) := Nat.mul_add _ _ _
      have h2 : (cap - min_hw) * (H - heavy_d) ≤ cap * (H - heavy_d) :=
        Nat.mul_le_mul_right _ (Nat.sub_le cap min_hw)
      have h3 : (H - heavy_d + L) * cap = cap * (H - heavy_d) + cap * L := by
        rw [Nat.add_mul, Nat.mul_comm (H - heavy_d) cap, Nat.mul_comm L cap]
      omega
    have hrem_ceil : (if light_wd - (cap - min_hw) * heavy_d > 0
                      then (light_wd - (cap - min_hw) * heavy_d + (cap - 1)) / cap else 0)
                     ≤ H - heavy_d + L :=
      ceilDiv_le_of_le_mul hcap hrem
    have hcand : heavy_d + (if light_wd - (cap - min_hw) * heavy_d > 0
                      then (light_wd - (cap - min_hw) * heavy_d + (cap - 1)) / cap else 0)
                 ≤ steps.length := by omega
    by_cases hcmp : heavy_d + (if light_wd - (cap - min_hw) * heavy_d > 0
                      then (light_wd - (cap - min_hw) * heavy_d + (cap - 1)) / cap else 0) >
                    (if total_wd > 0 then (total_wd + (cap - 1)) / cap else 0)
    · simp only [hcmp, ↓reduceIte]; exact hcand
    · simp only [hcmp, ↓reduceIte]; exact hlb1
  · exact hlb1

/-- Count of actions in a plan satisfying a boolean predicate `pred`. -/
def countActions {I : Instance} (pred : Action I → Bool) (π : Plan I) : Nat :=
  (π.map (fun a => if pred a then 1 else 0)).sum

/-- Plan-level soundness of `packLB`:
    Given ANY action filter `isCounted` and package distance potential `pot : State I → Fin I.numPkgs → Nat`
    that vanishes at goal, never decreases on uncounted actions, and decreases by at most 1 per
    counted action ONLY for packages inside the acting truck, `packLB` lower-bounds `countActions isCounted π`.
    Directly proves BOTH `h_pack_truck` (with `dist_no_sail`) and `nb_p` (with `nb_dist`). -/
theorem packLB_plan_sound {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hplan : ValidPlan I s π s_goal)
    (isCounted : Action I → Bool)
    (pot : State I → Fin I.numPkgs → Nat)
    (hgoal_zero : ∀ p, s.pkgDelivered p = false → pot s_goal p = 0)
    (hstep_pot : ∀ {s₁ s₂ : State I} {a : Action I},
      ValidState I s₁ → Step I s₁ a s₂ →
      (isCounted a = false → ∀ p, s.pkgDelivered p = false → pot s₁ p ≤ pot s₂ p) ∧
      (isCounted a = true → ∃ t : Fin I.numTrucks,
        ∀ p, s.pkgDelivered p = false →
          if s₁.pkgLoc p = .inTruck t then pot s₁ p ≤ pot s₂ p + 1
          else pot s₁ p ≤ pot s₂ p))
    (cap : Nat) (hcap : 0 < cap)
    (hcap_ge : ∀ t, dynEffCap I s t ≤ cap)
    (min_hw : Nat)
    (hmin_hw : ∀ p, s.pkgDelivered p = false → I.pkgWeight p > cap / 2 → pot s p > 0 → min_hw ≤ I.pkgWeight p) :
    packLB
      (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then pot s p else 0))
      min_hw
      (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p * pot s p else 0))
      (finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * pot s p else 0))
      cap
    ≤ countActions isCounted π := by
  -- Extract the list of carried-package masks on counted steps along `π`
  suffices ∃ steps : List (Fin I.numPkgs → Bool),
      steps.length = countActions isCounted π ∧
      (∀ m ∈ steps, subsetWeight I.pkgWeight m ≤ cap) ∧
      (∀ m ∈ steps, ∀ p, m p = true → I.pkgWeight p > cap / 2 → min_hw ≤ I.pkgWeight p) ∧
      (∀ p, s.pkgDelivered p = false →
        pot s p ≤ (steps.map (fun m => if m p then 1 else 0)).sum) by
    rcases this with ⟨steps, hlen, hsc, hsm, hcov⟩
    rw [← hlen]
    apply packLB_abstract_sound I.pkgWeight cap hcap steps hsc _ min_hw _ _ hsm
    · -- heavy_d ≤ sum over steps of heavy count
      have h1 : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then pot s p else 0) ≤
                finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
                  (steps.map (fun m => if m p then 1 else 0)).sum else 0) := by
        apply finSum_le_finSum; intro p
        cases hu : s.pkgDelivered p <;> by_cases hw : I.pkgWeight p > cap / 2 <;> simp [hu, hw]
        exact hcov p hu
      apply Nat.le_trans h1
      clear h1 hcov hsm hsc hlen
      induction steps with
      | nil => simp [finSum_zero]
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons]
        have hsplit :
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (if m p then 1 else 0) + (ms.map (fun m' => if m' p then 1 else 0)).sum else 0) =
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (if m p then 1 else 0) else 0) +
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (ms.map (fun m' => if m' p then 1 else 0)).sum else 0) := by
          rw [← finSum_add]; congr 1; funext p; split <;> simp
        rw [hsplit]
        have hhd : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (if m p then 1 else 0) else 0) ≤
            finSum (fun p => if m p && decide (I.pkgWeight p > cap / 2) then 1 else 0) := by
          apply finSum_le_finSum; intro p
          cases s.pkgDelivered p <;> cases m p <;> by_cases hw : I.pkgWeight p > cap / 2 <;> simp [hw]
        omega
    · -- light_wd ≤ sum over steps of light weight
      have h1 : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
                  I.pkgWeight p * pot s p else 0) ≤
                finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
                  I.pkgWeight p * (steps.map (fun m => if m p then 1 else 0)).sum else 0) := by
        apply finSum_le_finSum; intro p
        cases hu : s.pkgDelivered p <;> by_cases hw : I.pkgWeight p ≤ cap / 2 <;> simp [hu, hw]
        exact Nat.mul_le_mul_left _ (hcov p hu)
      apply Nat.le_trans h1
      clear h1 hcov hsm hsc hlen
      induction steps with
      | nil => simp [finSum_zero]
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons]
        have hsplit :
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
              I.pkgWeight p * ((if m p then 1 else 0) + (ms.map (fun m' => if m' p then 1 else 0)).sum) else 0) =
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
              I.pkgWeight p * (if m p then 1 else 0) else 0) +
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
              I.pkgWeight p * (ms.map (fun m' => if m' p then 1 else 0)).sum else 0) := by
          rw [← finSum_add]; congr 1; funext p; split <;> simp [Nat.mul_add]
        rw [hsplit]
        have hhd : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then
              I.pkgWeight p * (if m p then 1 else 0) else 0) ≤
            finSum (fun p => if m p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p else 0) := by
          apply finSum_le_finSum; intro p
          cases s.pkgDelivered p <;> cases m p <;> by_cases hw : I.pkgWeight p ≤ cap / 2 <;> simp [hw]
        omega
    · -- total_wd ≤ sum over steps of subsetWeight
      have h1 : finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * pot s p else 0) ≤
                finSum (fun p => if !s.pkgDelivered p then
                  I.pkgWeight p * (steps.map (fun m => if m p then 1 else 0)).sum else 0) := by
        apply finSum_le_finSum; intro p
        cases hu : s.pkgDelivered p <;> simp [hu]
        exact Nat.mul_le_mul_left _ (hcov p hu)
      apply Nat.le_trans h1
      clear h1 hcov hsm hsc hlen
      induction steps with
      | nil => simp [finSum_zero]
      | cons m ms ih =>
        simp only [List.map_cons, List.sum_cons]
        have hsplit :
            finSum (fun p => if !s.pkgDelivered p then
              I.pkgWeight p * ((if m p then 1 else 0) + (ms.map (fun m' => if m' p then 1 else 0)).sum) else 0) =
            finSum (fun p => if !s.pkgDelivered p then
              I.pkgWeight p * (if m p then 1 else 0) else 0) +
            finSum (fun p => if !s.pkgDelivered p then
              I.pkgWeight p * (ms.map (fun m' => if m' p then 1 else 0)).sum else 0) := by
          rw [← finSum_add]; congr 1; funext p; split <;> simp [Nat.mul_add]
        rw [hsplit]
        have hhd : finSum (fun p => if !s.pkgDelivered p then
              I.pkgWeight p * (if m p then 1 else 0) else 0) ≤ subsetWeight I.pkgWeight m := by
          unfold subsetWeight; apply finSum_le_finSum; intro p
          cases s.pkgDelivered p <;> cases m p <;> simp
        omega
  -- Prove the existential by induction on `hplan`, keeping `s` (for `s.pkgDelivered`) fixed!
  suffices ∀ {s_cur s_end : State I} {π' : Plan I},
      ValidPlan I s_cur π' s_end → ValidState I s_cur →
      (∀ p, s.pkgDelivered p = false → pot s_end p = 0) →
      (∃ steps : List (Fin I.numPkgs → Bool),
        steps.length = countActions isCounted π' ∧
        (∀ m ∈ steps, subsetWeight I.pkgWeight m ≤ cap) ∧
        (∀ m ∈ steps, ∀ p, m p = true → s.pkgDelivered p = false) ∧
        (∀ p, s.pkgDelivered p = false →
          pot s_cur p ≤ (steps.map (fun m => if m p then 1 else 0)).sum)) by
    rcases this hplan hv hgoal_zero with ⟨steps, hlen, hsc, hsund, hcov⟩
    refine ⟨steps.map (fun m p => m p && decide (pot s p > 0)), by simp [hlen], ?_, ?_, ?_⟩
    · intro m' hm'
      rcases List.mem_map.mp hm' with ⟨m, hm, rfl⟩
      have hsub : subsetWeight I.pkgWeight (fun p => m p && decide (pot s p > 0)) ≤ subsetWeight I.pkgWeight m := by
        unfold subsetWeight; apply finSum_le_finSum; intro p
        cases hmp : m p <;> by_cases hp : pot s p > 0 <;> simp [hmp, hp]
      exact Nat.le_trans hsub (hsc m hm)
    · intro m' hm' p hmp hw
      rcases List.mem_map.mp hm' with ⟨m, hm, rfl⟩
      simp only [Bool.and_eq_true, decide_eq_true_eq] at hmp
      exact hmin_hw p (hsund m hm p hmp.1) hw hmp.2
    · intro p hu
      by_cases hp0 : pot s p = 0
      · omega
      · have hpos : pot s p > 0 := Nat.pos_of_ne_zero hp0
        have hmap : ((steps.map (fun m p => m p && decide (pot s p > 0))).map
                     (fun m => if m p then 1 else 0)).sum =
                    (steps.map (fun m => if m p then 1 else 0)).sum := by
          rw [List.map_map]
          congr 1; apply List.map_congr_left; intro m _; simp [hpos]
        rw [hmap]
        exact hcov p hu
  intro s_cur s_end π' hplan'
  induction hplan' with
  | nil =>
    intro _ hgz
    refine ⟨[], rfl, ?_, ?_, ?_⟩
    · intro _ hm; cases hm
    · intro _ hm; cases hm
    · intro p hu; simp [hgz p hu]
  | @cons s₁ s₂ s₃ a rest hstep _ ih =>
    intro hv_cur hgz
    have hv₂ := validState_step hv_cur hstep
    rcases ih hv₂ hgz with ⟨steps, hlen, hsc, hsund, hcov⟩
    have ⟨hunc, hcnt⟩ := hstep_pot hv_cur hstep
    cases hca : isCounted a with
    | false =>
      refine ⟨steps, ?_, hsc, hsund, ?_⟩
      · simp [countActions, hca, hlen]
      · intro p hu
        exact Nat.le_trans (hunc hca p hu) (hcov p hu)
    | true =>
      rcases hcnt hca with ⟨t, ht_pot⟩
      let m0 : Fin I.numPkgs → Bool := fun p => !s.pkgDelivered p && (s₁.pkgLoc p == .inTruck t)
      refine ⟨m0 :: steps, ?_, ?_, ?_, ?_⟩
      · simp [countActions, hca, hlen]; omega
      · intro m hm
        rcases List.mem_cons.mp hm with rfl | hms
        · exact Nat.le_trans (truckLoad_undeliv_le_dynEffCap hv_cur t) (hcap_ge t)
        · exact hsc m hms
      · intro m hm p hmp
        rcases List.mem_cons.mp hm with rfl | hms
        · simp only [m0, Bool.and_eq_true, Bool.not_eq_true'] at hmp
          exact hmp.1
        · exact hsund m hms p hmp
      · intro p hu
        simp only [List.map_cons, List.sum_cons]
        have hstep_p := ht_pot p hu
        have hrest_p := hcov p hu
        by_cases hin : s₁.pkgLoc p = .inTruck t
        · simp only [hin, ↓reduceIte] at hstep_p
          have hm0p : m0 p = true := by simp [m0, hu, hin]
          simp only [hm0p, ↓reduceIte]
          omega
        · simp only [hin, ↓reduceIte] at hstep_p
          omega

-- ==============================================================================
-- 5. TWO-SIDED CUT TRUCK-FLUX LOWER BOUND (`_flux_lb`, ex1.py:L66-L93)
-- ==============================================================================

/-- Exact `_flux_lb` matching `ex1.py:L66-L93` verbatim. -/
def fluxLB (w_ab w_ba h_ab h_ba : Nat) (need_ab need_ba : Bool)
    (m_a m_b c_a c_b cap : Nat) : Nat × Nat :=
  let cm1 := cap - 1
  let kab0 := if w_ab > 0 then (w_ab + cm1) / cap else 0
  let kab1 := if h_ab > kab0 then h_ab else kab0
  let kab := if need_ab && kab1 < 1 then 1 else kab1
  let kba0 := if w_ba > 0 then (w_ba + cm1) / cap else 0
  let kba1 := if h_ba > kba0 then h_ba else kba0
  let kba := if need_ba && kba1 < 1 then 1 else kba1
  let rab0 := if kba - m_b > kab then kba - m_b else kab
  let rab := if w_ba > c_b then
      let cw := (w_ba - c_b + cm1) / cap
      if cw > rab0 then cw else rab0
    else rab0
  let rba0 := if kab - m_a > kba then kab - m_a else kba
  let rba := if w_ab > c_a then
      let cw := (w_ab - c_a + cm1) / cap
      if cw > rba0 then cw else rba0
    else rba0
  (rab, rba)

/-- Abstract soundness of `fluxLB` (`ex1.py:L66-L93`):
    Given trucks partitioned into side A (`tSide = true`, count `m_a`, cap sum `c_a`)
    and side B (`tSide = false`, count `m_b`, cap sum `c_b`) with each `ec t ≤ cap`,
    and crossing counts `xAB t`, `xBA t` satisfying alternation and cargo bounds,
    both components of `fluxLB` lower-bound `finSum xAB` and `finSum xBA`. -/
theorem fluxLB_abstract_sound {nt : Nat} (tIn : Fin nt → Bool) (tSide : Fin nt → Bool)
    (ec xAB xBA carryAB carryBA : Fin nt → Nat) (cap : Nat) (hcap : 0 < cap)
    (hec_le : ∀ t, tIn t = true → ec t ≤ cap)
    (halt_ab : ∀ t, tIn t = true → xAB t ≤ (if tSide t then 1 else 0) + xBA t)
    (halt_ba : ∀ t, tIn t = true → xBA t ≤ (if !tSide t then 1 else 0) + xAB t)
    (hcarry_ab : ∀ t, tIn t = true → carryAB t ≤ xAB t * ec t)
    (hcarry_ba : ∀ t, tIn t = true → carryBA t ≤ xBA t * ec t)
    (w_ab w_ba h_ab h_ba : Nat) (need_ab need_ba : Bool)
    (hw_ab : w_ab ≤ finSum (fun t => if tIn t then carryAB t else 0))
    (hw_ba : w_ba ≤ finSum (fun t => if tIn t then carryBA t else 0))
    (hh_ab : h_ab ≤ finSum (fun t => if tIn t then xAB t else 0))
    (hh_ba : h_ba ≤ finSum (fun t => if tIn t then xBA t else 0))
    (hneed_ab : need_ab = true → 1 ≤ finSum (fun t => if tIn t then xAB t else 0))
    (hneed_ba : need_ba = true → 1 ≤ finSum (fun t => if tIn t then xBA t else 0)) :
    let m_a := finSum (fun t => if tIn t && tSide t then 1 else 0)
    let m_b := finSum (fun t => if tIn t && !tSide t then 1 else 0)
    let c_a := finSum (fun t => if tIn t && tSide t then ec t else 0)
    let c_b := finSum (fun t => if tIn t && !tSide t then ec t else 0)
    let r := fluxLB w_ab w_ba h_ab h_ba need_ab need_ba m_a m_b c_a c_b cap
    r.1 ≤ finSum (fun t => if tIn t then xAB t else 0) ∧
    r.2 ≤ finSum (fun t => if tIn t then xBA t else 0) := by
  intro m_a m_b c_a c_b r
  let Xab := finSum (fun t => if tIn t then xAB t else 0)
  let Xba := finSum (fun t => if tIn t then xBA t else 0)
  -- 1. Direct weight bounds: w_ab ≤ Xab * cap, w_ba ≤ Xba * cap
  have hwab_mul : w_ab ≤ Xab * cap := by
    apply Nat.le_trans hw_ab
    rw [Nat.mul_comm, ← finSum_mul_left]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      simp only [↓reduceIte]
      have h1 := hcarry_ab t hin
      have h2 := Nat.mul_le_mul_left (xAB t) (hec_le t hin)
      rw [Nat.mul_comm cap (xAB t)]
      exact Nat.le_trans h1 h2
  have hwba_mul : w_ba ≤ Xba * cap := by
    apply Nat.le_trans hw_ba
    rw [Nat.mul_comm, ← finSum_mul_left]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      simp only [↓reduceIte]
      have h1 := hcarry_ba t hin
      have h2 := Nat.mul_le_mul_left (xBA t) (hec_le t hin)
      rw [Nat.mul_comm cap (xBA t)]
      exact Nat.le_trans h1 h2
  have hkab0 : (if w_ab > 0 then (w_ab + (cap - 1)) / cap else 0) ≤ Xab :=
    ceilDiv_le_of_le_mul hcap hwab_mul
  have hkba0 : (if w_ba > 0 then (w_ba + (cap - 1)) / cap else 0) ≤ Xba :=
    ceilDiv_le_of_le_mul hcap hwba_mul
  -- 2. Truck count conservation: Xab ≤ m_a + Xba and Xba ≤ m_b + Xab
  have hcons_ab : Xab ≤ m_a + Xba := by
    dsimp only [Xab, Xba, m_a]
    rw [← finSum_add]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      have h := halt_ab t hin
      cases hs : tSide t <;> simp [hs] at h ⊢ <;> omega
  have hcons_ba : Xba ≤ m_b + Xab := by
    dsimp only [Xab, Xba, m_b]
    rw [← finSum_add]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      have h := halt_ba t hin
      cases hs : tSide t <;> simp [hs] at h ⊢ <;> omega
  -- 3. Capacity conservation: w_ab ≤ c_a + Xba * cap and w_ba ≤ c_b + Xab * cap
  have hcap_ab : w_ab ≤ c_a + Xba * cap := by
    apply Nat.le_trans hw_ab
    dsimp only [c_a, Xba]
    rw [Nat.mul_comm _ cap, ← finSum_mul_left, ← finSum_add]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      simp only [↓reduceIte, Bool.true_and]
      have h1 := hcarry_ab t hin
      have h2 := halt_ab t hin
      have h3 := hec_le t hin
      cases hs : tSide t with
      | false =>
        simp only [hs, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at h2 ⊢
        have h4 : xAB t * ec t ≤ xBA t * cap := Nat.mul_le_mul h2 h3
        rw [Nat.mul_comm cap (xBA t)]
        exact Nat.le_trans h1 h4
      | true =>
        simp only [hs, ↓reduceIte] at h2 ⊢
        have h4 : xAB t * ec t ≤ (1 + xBA t) * ec t := Nat.mul_le_mul_right (ec t) h2
        rw [Nat.add_mul, Nat.one_mul] at h4
        have h5 : xBA t * ec t ≤ xBA t * cap := Nat.mul_le_mul_left (xBA t) h3
        rw [Nat.mul_comm cap (xBA t)]
        omega
  have hcap_ba : w_ba ≤ c_b + Xab * cap := by
    apply Nat.le_trans hw_ba
    dsimp only [c_b, Xab]
    rw [Nat.mul_comm _ cap, ← finSum_mul_left, ← finSum_add]
    apply finSum_le_finSum; intro t
    cases hin : tIn t with
    | false => simp
    | true =>
      simp only [↓reduceIte, Bool.true_and]
      have h1 := hcarry_ba t hin
      have h2 := halt_ba t hin
      have h3 := hec_le t hin
      cases hs : tSide t with
      | true =>
        simp only [hs, Bool.not_true, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at h2 ⊢
        have h4 : xBA t * ec t ≤ xAB t * cap := Nat.mul_le_mul h2 h3
        rw [Nat.mul_comm cap (xAB t)]
        exact Nat.le_trans h1 h4
      | false =>
        simp only [hs, Bool.not_false, ↓reduceIte] at h2 ⊢
        have h4 : xBA t * ec t ≤ (1 + xAB t) * ec t := Nat.mul_le_mul_right (ec t) h2
        rw [Nat.add_mul, Nat.one_mul] at h4
        have h5 : xAB t * ec t ≤ xAB t * cap := Nat.mul_le_mul_left (xAB t) h3
        rw [Nat.mul_comm cap (xAB t)]
        omega
  have hcw_ba : w_ba > c_b → (w_ba - c_b + (cap - 1)) / cap ≤ Xab := by
    intro hgt
    have hsub : w_ba - c_b ≤ Xab * cap := by omega
    have hc := ceilDiv_le_of_le_mul hcap hsub
    unfold ceilDiv at hc
    have hpos : w_ba - c_b > 0 := by omega
    simpa [hpos] using hc
  have hcw_ab : w_ab > c_a → (w_ab - c_a + (cap - 1)) / cap ≤ Xba := by
    intro hgt
    have hsub : w_ab - c_a ≤ Xba * cap := by omega
    have hc := ceilDiv_le_of_le_mul hcap hsub
    unfold ceilDiv at hc
    have hpos : w_ab - c_a > 0 := by omega
    simpa [hpos] using hc
  -- 4. Assemble both components of `fluxLB`
  let kab0 := if w_ab > 0 then (w_ab + (cap - 1)) / cap else 0
  let kab1 := if h_ab > kab0 then h_ab else kab0
  let kab := if need_ab && kab1 < 1 then 1 else kab1
  let kba0 := if w_ba > 0 then (w_ba + (cap - 1)) / cap else 0
  let kba1 := if h_ba > kba0 then h_ba else kba0
  let kba := if need_ba && kba1 < 1 then 1 else kba1
  have hkab1 : kab1 ≤ Xab := by
    change (if h_ab > kab0 then h_ab else kab0) ≤ Xab
    have h0 : kab0 ≤ Xab := hkab0
    split <;> omega
  have hkba1 : kba1 ≤ Xba := by
    change (if h_ba > kba0 then h_ba else kba0) ≤ Xba
    have h0 : kba0 ≤ Xba := hkba0
    split <;> omega
  have hkab : kab ≤ Xab := by
    dsimp only [kab]
    cases hnab : need_ab with
    | false => simp only [Bool.false_and, Bool.false_eq_true, ↓reduceIte]; exact hkab1
    | true =>
      have h1 := hneed_ab hnab
      by_cases hlt : kab1 < 1
      · simp only [Bool.true_and, hlt, decide_true, ↓reduceIte]; exact h1
      · simp only [Bool.true_and, hlt, decide_false, Bool.false_eq_true, ↓reduceIte]; exact hkab1
  have hkba : kba ≤ Xba := by
    dsimp only [kba]
    cases hnba : need_ba with
    | false => simp only [Bool.false_and, Bool.false_eq_true, ↓reduceIte]; exact hkba1
    | true =>
      have h1 := hneed_ba hnba
      by_cases hlt : kba1 < 1
      · simp only [Bool.true_and, hlt, decide_true, ↓reduceIte]; exact h1
      · simp only [Bool.true_and, hlt, decide_false, Bool.false_eq_true, ↓reduceIte]; exact hkba1
  have hrab0 : (if kba - m_b > kab then kba - m_b else kab) ≤ Xab := by
    split <;> omega
  have hrba0 : (if kab - m_a > kba then kab - m_a else kba) ≤ Xba := by
    split <;> omega
  have hrab : (if w_ba > c_b then
      let cw := (w_ba - c_b + (cap - 1)) / cap
      if cw > (if kba - m_b > kab then kba - m_b else kab) then cw else (if kba - m_b > kab then kba - m_b else kab)
    else (if kba - m_b > kab then kba - m_b else kab)) ≤ Xab := by
    by_cases hgt : w_ba > c_b
    · simp only [hgt, ↓reduceIte]
      have hcw := hcw_ba hgt
      by_cases hcmp : (w_ba - c_b + (cap - 1)) / cap > (if kba - m_b > kab then kba - m_b else kab)
      · simp only [hcmp, ↓reduceIte]; exact hcw
      · simp only [hcmp, ↓reduceIte]; exact hrab0
    · simp only [hgt, ↓reduceIte]; exact hrab0
  have hrba : (if w_ab > c_a then
      let cw := (w_ab - c_a + (cap - 1)) / cap
      if cw > (if kab - m_a > kba then kab - m_a else kba) then cw else (if kab - m_a > kba then kab - m_a else kba)
    else (if kab - m_a > kba then kab - m_a else kba)) ≤ Xba := by
    by_cases hgt : w_ab > c_a
    · simp only [hgt, ↓reduceIte]
      have hcw := hcw_ab hgt
      by_cases hcmp : (w_ab - c_a + (cap - 1)) / cap > (if kab - m_a > kba then kab - m_a else kba)
      · simp only [hcmp, ↓reduceIte]; exact hcw
      · simp only [hcmp, ↓reduceIte]; exact hrba0
    · simp only [hgt, ↓reduceIte]; exact hrba0
  exact ⟨hrab, hrba⟩

/-- Per-truck crossing counts across a 2-sided cut `(inComp, inA)` along a plan `π`,
    starting from state `s₁`. -/
def stepTruckCrossAB {I : Instance} (inComp inA : Fin I.numLocs → Bool)
    (s₁ s₂ : State I) (t : Fin I.numTrucks) : Nat :=
  if inComp (s₁.truckPhysLoc t) && inA (s₁.truckPhysLoc t) && !inA (s₂.truckPhysLoc t) then 1 else 0

def stepTruckCrossBA {I : Instance} (inComp inA : Fin I.numLocs → Bool)
    (s₁ s₂ : State I) (t : Fin I.numTrucks) : Nat :=
  if inComp (s₁.truckPhysLoc t) && !inA (s₁.truckPhysLoc t) && inA (s₂.truckPhysLoc t) then 1 else 0

/-- Deterministic plan-indexed crossing counters using `applyAction`. -/
def planTruckCrossAB {I : Instance} (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numTrucks → Nat
  | _, []      , _ => 0
  | s₁, a :: π , t =>
      let sm := applyAction s₁ a
      stepTruckCrossAB inComp inA s₁ sm t + planTruckCrossAB inComp inA sm π t

def planTruckCrossBA {I : Instance} (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numTrucks → Nat
  | _, []      , _ => 0
  | s₁, a :: π , t =>
      let sm := applyAction s₁ a
      stepTruckCrossBA inComp inA s₁ sm t + planTruckCrossBA inComp inA sm π t

/-- Total weight of `s_root`-undelivered packages carried by truck `t` on A->B crossings. -/
def planTruckCarryAB {I : Instance} (s_root : State I) (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numTrucks → Nat
  | _, []      , _ => 0
  | s₁, a :: π , t =>
      let sm := applyAction s₁ a
      (if stepTruckCrossAB inComp inA s₁ sm t = 1 then
        finSum (fun p => if !s_root.pkgDelivered p && (s₁.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
       else 0) + planTruckCarryAB s_root inComp inA sm π t

def planTruckCarryBA {I : Instance} (s_root : State I) (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numTrucks → Nat
  | _, []      , _ => 0
  | s₁, a :: π , t =>
      let sm := applyAction s₁ a
      (if stepTruckCrossBA inComp inA s₁ sm t = 1 then
        finSum (fun p => if !s_root.pkgDelivered p && (s₁.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
       else 0) + planTruckCarryBA s_root inComp inA sm π t

/-- Number of steps in `π` where package `p` is carried across A->B (resp. B->A). -/
def planPkgCrossAB {I : Instance} (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numPkgs → Nat
  | _, []      , _ => 0
  | s₁, a :: π , p =>
      let sm := applyAction s₁ a
      (match s₁.pkgLoc p with
       | .atLoc _ => 0
       | .inTruck t => stepTruckCrossAB inComp inA s₁ sm t) +
      planPkgCrossAB inComp inA sm π p

def planPkgCrossBA {I : Instance} (inComp inA : Fin I.numLocs → Bool) :
    State I → Plan I → Fin I.numPkgs → Nat
  | _, []      , _ => 0
  | s₁, a :: π , p =>
      let sm := applyAction s₁ a
      (match s₁.pkgLoc p with
       | .atLoc _ => 0
       | .inTruck t => stepTruckCrossBA inComp inA s₁ sm t) +
      planPkgCrossBA inComp inA sm π p

/-- Component invariance: `inComp` is closed under every truck movement in `I`. -/
def CompClosed (I : Instance) (inComp : Fin I.numLocs → Bool) : Prop :=
  ∀ {s₁ s₂ : State I} {a : Action I}, Step I s₁ a s₂ →
    ∀ t : Fin I.numTrucks, inComp (s₂.truckPhysLoc t) = inComp (s₁.truckPhysLoc t)

/-- A package's physical location only changes when it is inside a truck whose physical location changes. -/
theorem step_pkgPhysLoc_change {I : Instance} {s₁ s₂ : State I} {a : Action I}
    (hstep : Step I s₁ a s₂) (p : Fin I.numPkgs) :
    s₂.pkgPhysLoc p ≠ s₁.pkgPhysLoc p →
    ∃ t : Fin I.numTrucks, s₁.pkgLoc p = .inTruck t ∧
      s₁.pkgPhysLoc p = s₁.truckPhysLoc t ∧ s₂.pkgPhysLoc p = s₂.truckPhysLoc t := by
  cases hstep with
  | @drive t u v ht hne hroad =>
    intro hne_p
    cases hp : s₁.pkgLoc p with
    | atLoc l =>
      simp [State.pkgPhysLoc, hp] at hne_p
    | inTruck t' =>
      refine ⟨t', rfl, ?_, ?_⟩ <;> simp [State.pkgPhysLoc, hp]
  | @load p' t l ht hp hcap =>
    intro hne_p
    by_cases hpp : p = p'
    · subst hpp
      simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp] at hne_p
    · simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp] at hne_p
  | @unload p' t l ht hp =>
    intro hne_p
    by_cases hpp : p = p'
    · subst hpp
      simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp] at hne_p
    · simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp] at hne_p
  | @board t f ht hcap =>
    intro hne_p
    cases hp : s₁.pkgLoc p with
    | atLoc l => simp [State.pkgPhysLoc, hp] at hne_p
    | inTruck t' =>
      by_cases htt : t' = t
      · subst htt
        simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hp, ht] at hne_p
      · simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hp, htt] at hne_p
  | @disembark t f ht =>
    intro hne_p
    cases hp : s₁.pkgLoc p with
    | atLoc l => simp [State.pkgPhysLoc, hp] at hne_p
    | inTruck t' =>
      by_cases htt : t' = t
      · subst htt
        simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hp, ht] at hne_p
      · simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hp, htt] at hne_p
  | @sail f u v hf hne hserved =>
    intro hne_p
    cases hp : s₁.pkgLoc p with
    | atLoc l => simp [State.pkgPhysLoc, hp] at hne_p
    | inTruck t' =>
      refine ⟨t', rfl, ?_, ?_⟩ <;> simp [State.pkgPhysLoc, hp]

/-- Truck alternation along any `ValidPlan` inside a closed component `inComp`. -/
theorem planTruckCross_alternation {I : Instance} {inComp inA : Fin I.numLocs → Bool}
    (hcl : CompClosed I inComp)
    {s₁ s₂ : State I} {π : Plan I} (hp : ValidPlan I s₁ π s₂) (t : Fin I.numTrucks)
    (hin : inComp (s₁.truckPhysLoc t) = true) :
    planTruckCrossAB inComp inA s₁ π t ≤ (if inA (s₁.truckPhysLoc t) then 1 else 0) + planTruckCrossBA inComp inA s₁ π t ∧
    planTruckCrossBA inComp inA s₁ π t ≤ (if !inA (s₁.truckPhysLoc t) then 1 else 0) + planTruckCrossAB inComp inA s₁ π t := by
  induction hp with
  | nil => simp [planTruckCrossAB, planTruckCrossBA]
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hin_b : inComp (sb.truckPhysLoc t) = true := by rw [hcl hstep t]; exact hin
    have ⟨h1, h2⟩ := ih hin_b
    simp only [planTruckCrossAB, planTruckCrossBA, ← hsb_eq, stepTruckCrossAB, stepTruckCrossBA, hin]
    cases ha : inA (sa.truckPhysLoc t) <;> cases hb : inA (sb.truckPhysLoc t) <;>
      simp only [ha, hb, Bool.true_and, Bool.false_and, Bool.not_true, Bool.not_false,
                 Bool.false_eq_true, ↓reduceIte] at h1 h2 ⊢ <;> omega

/-- If a truck starts on A and ends on B inside `inComp`, it crosses A->B at least once. -/
theorem planTruckCrossAB_pos_of_side_change {I : Instance} {inComp inA : Fin I.numLocs → Bool}
    (hcl : CompClosed I inComp)
    {s₁ s₂ : State I} {π : Plan I} (hp : ValidPlan I s₁ π s₂) (t : Fin I.numTrucks)
    (hin : inComp (s₁.truckPhysLoc t) = true)
    (ha : inA (s₁.truckPhysLoc t) = true) (hb : inA (s₂.truckPhysLoc t) = false) :
    1 ≤ planTruckCrossAB inComp inA s₁ π t := by
  induction hp with
  | nil => rw [ha] at hb; cases hb
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hin_b : inComp (sb.truckPhysLoc t) = true := by rw [hcl hstep t]; exact hin
    simp only [planTruckCrossAB, ← hsb_eq, stepTruckCrossAB, hin, ha]
    cases hsb : inA (sb.truckPhysLoc t) with
    | false => simp
    | true =>
      have := ih hin_b hsb hb
      omega

theorem planTruckCrossBA_pos_of_side_change {I : Instance} {inComp inA : Fin I.numLocs → Bool}
    (hcl : CompClosed I inComp)
    {s₁ s₂ : State I} {π : Plan I} (hp : ValidPlan I s₁ π s₂) (t : Fin I.numTrucks)
    (hin : inComp (s₁.truckPhysLoc t) = true)
    (ha : inA (s₁.truckPhysLoc t) = false) (hb : inA (s₂.truckPhysLoc t) = true) :
    1 ≤ planTruckCrossBA inComp inA s₁ π t := by
  induction hp with
  | nil => rw [ha] at hb; cases hb
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hin_b : inComp (sb.truckPhysLoc t) = true := by rw [hcl hstep t]; exact hin
    simp only [planTruckCrossBA, ← hsb_eq, stepTruckCrossBA, hin, ha]
    cases hsb : inA (sb.truckPhysLoc t) with
    | true => simp
    | false =>
      have := ih hin_b hsb hb
      omega

/-- Any package starting on A and ending on B inside `inComp` is carried across A->B at least once. -/
theorem planPkgCrossAB_pos_of_side_change {I : Instance} {inComp inA : Fin I.numLocs → Bool}
    (hcl : CompClosed I inComp)
    {s₁ s₂ : State I} {π : Plan I} (hp : ValidPlan I s₁ π s₂) (p : Fin I.numPkgs)
    (hin : inComp (s₁.pkgPhysLoc p) = true)
    (ha : inA (s₁.pkgPhysLoc p) = true) (hb : inA (s₂.pkgPhysLoc p) = false) :
    1 ≤ planPkgCrossAB inComp inA s₁ π p := by
  induction hp with
  | nil => rw [ha] at hb; cases hb
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
    · have hin_b : inComp (sb.pkgPhysLoc p) = true := hsame ▸ hin
      have ha_b : inA (sb.pkgPhysLoc p) = true := hsame ▸ ha
      have := ih hin_b ha_b hb
      simp only [planPkgCrossAB, ← hsb_eq]
      omega
    · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, hloc, hpa, hpb⟩
      have hin_t : inComp (sa.truckPhysLoc t) = true := hpa ▸ hin
      have hin_tb : inComp (sb.truckPhysLoc t) = true := by rw [hcl hstep t]; exact hin_t
      have hin_pb : inComp (sb.pkgPhysLoc p) = true := hpb.symm ▸ hin_tb
      simp only [planPkgCrossAB, ← hsb_eq, hloc]
      cases hsb : inA (sb.pkgPhysLoc p) with
      | false =>
        have htb : inA (sb.truckPhysLoc t) = false := hpb ▸ hsb
        have hta : inA (sa.truckPhysLoc t) = true := hpa ▸ ha
        simp [stepTruckCrossAB, hin_t, hta, htb]
      | true =>
        have := ih hin_pb hsb hb
        omega

theorem planPkgCrossBA_pos_of_side_change {I : Instance} {inComp inA : Fin I.numLocs → Bool}
    (hcl : CompClosed I inComp)
    {s₁ s₂ : State I} {π : Plan I} (hp : ValidPlan I s₁ π s₂) (p : Fin I.numPkgs)
    (hin : inComp (s₁.pkgPhysLoc p) = true)
    (ha : inA (s₁.pkgPhysLoc p) = false) (hb : inA (s₂.pkgPhysLoc p) = true) :
    1 ≤ planPkgCrossBA inComp inA s₁ π p := by
  induction hp with
  | nil => rw [ha] at hb; cases hb
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
    · have hin_b : inComp (sb.pkgPhysLoc p) = true := hsame ▸ hin
      have ha_b : inA (sb.pkgPhysLoc p) = false := hsame ▸ ha
      have := ih hin_b ha_b hb
      simp only [planPkgCrossBA, ← hsb_eq]
      omega
    · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, hloc, hpa, hpb⟩
      have hin_t : inComp (sa.truckPhysLoc t) = true := hpa ▸ hin
      have hin_tb : inComp (sb.truckPhysLoc t) = true := by rw [hcl hstep t]; exact hin_t
      have hin_pb : inComp (sb.pkgPhysLoc p) = true := hpb.symm ▸ hin_tb
      simp only [planPkgCrossBA, ← hsb_eq, hloc]
      cases hsb : inA (sb.pkgPhysLoc p) with
      | true =>
        have htb : inA (sb.truckPhysLoc t) = true := hpb ▸ hsb
        have hta : inA (sa.truckPhysLoc t) = false := hpa ▸ ha
        simp [stepTruckCrossBA, hin_t, hta, htb]
      | false =>
        have := ih hin_pb hsb hb
        omega

/-- Any ground undelivered package at `l` must be loaded at `l` by some capable truck along any plan to goal. -/
theorem ground_undeliv_loaded_by_capable {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (l : Fin I.numLocs)
    (hloc : s.pkgLoc p = .atLoc l) (hnd : s.pkgDelivered p = false)
    (inComp inA : Fin I.numLocs → Bool) (hcl : CompClosed I inComp)
    (hin : inComp l = true) (hside : inA l = false)
    (hno_capable : ∀ t, inComp (s.truckPhysLoc t) = true → inA (s.truckPhysLoc t) = false →
      dynEffCap I s t < I.pkgWeight p) :
    ∃ t : Fin I.numTrucks, inComp (s.truckPhysLoc t) = true ∧ 1 ≤ planTruckCrossAB inComp inA s π t := by
  suffices ∀ {s₁ s_end : State I} {π' : Plan I},
      ValidPlan I s₁ π' s_end → goalTest I s_end → ValidState I s₁ →
      s₁.pkgLoc p = .atLoc l →
      ∃ t : Fin I.numTrucks,
        I.pkgWeight p ≤ dynEffCap I s t ∧
        inComp (s₁.truckPhysLoc t) = true ∧
        (inA (s₁.truckPhysLoc t) = false ∨ 1 ≤ planTruckCrossAB inComp inA s₁ π' t) by
    rcases this hp hg hv hloc with ⟨t, hcap_t, hin_t, hcase⟩
    refine ⟨t, hin_t, ?_⟩
    rcases hcase with hB | hcross
    · have := hno_capable t hin_t hB
      omega
    · exact hcross
  intro s₁ s_end π' hp'
  induction hp' with
  | nil =>
    intro hg_end _ hloc1
    have hg_p := hg_end p
    rw [hloc1] at hg_p
    have hdel : s.pkgDelivered p = true := by
      unfold State.pkgDelivered
      rw [hloc, hg_p]
      simp
    rw [hnd] at hdel
    cases hdel
  | @cons sa sb _ a rest hstep _ ih =>
    intro hg_end hv₁ hloc_a
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hvb := validState_step hv₁ hstep
    by_cases hstill : sb.pkgLoc p = .atLoc l
    · rcases ih hg_end hvb hstill with ⟨t, hcap_t, hin_tb, hcase⟩
      have hin_ta : inComp (sa.truckPhysLoc t) = true := by rw [← hcl hstep t]; exact hin_tb
      refine ⟨t, hcap_t, hin_ta, ?_⟩
      cases hsa : inA (sa.truckPhysLoc t) with
      | false => left; rfl
      | true =>
        right
        simp only [planTruckCrossAB, ← hsb_eq, stepTruckCrossAB, hin_ta, hsa]
        rcases hcase with hsbB | hrest_c
        · simp [hsbB]
        · omega
    · cases hstep with
      | @load p' t l' ht_a hp_a hload_cap =>
        by_cases hpp : p' = p
        · have hl_eq : l' = l := by
            rw [hpp, hloc_a] at hp_a; injection hp_a with hl; exact hl.symm
          have hphys : sa.truckPhysLoc t = l := by simp [State.truckPhysLoc, ht_a, hl_eq]
          have hcap_t : I.pkgWeight p ≤ dynEffCap I s t := by
            let mask : Fin I.numPkgs → Bool := fun q => decide (q = p)
            have hsw : subsetWeight I.pkgWeight mask = I.pkgWeight p := by
              unfold subsetWeight
              have hfn : (fun q => if mask q then I.pkgWeight q else 0) =
                         (fun q => if q = p then I.pkgWeight p else 0) := by
                funext q; by_cases hqp : q = p <;> simp [mask, hqp]
              rw [hfn, finSum_ite_eq]
            rw [← hsw]
            apply subsetWeight_undeliv_le_dynEffCap I s t mask
            · intro q hmq
              simp only [mask, decide_eq_true_eq] at hmq
              subst hmq; exact hnd
            · rw [hsw]
              have hle_p : I.pkgWeight p' ≤ I.truckCap t := Nat.le_trans (Nat.le_add_left _ _) hload_cap
              rw [hpp] at hle_p
              exact hle_p
          exact ⟨t, hcap_t, hphys.symm ▸ hin, Or.inl (hphys.symm ▸ hside)⟩
        · exfalso; apply hstill; simp [updateFn, Ne.symm hpp, hloc_a]
      | drive _ _ _ => exfalso; exact hstill hloc_a
      | @unload p' _ _ _ hp_a =>
        by_cases hpp : p' = p
        · rw [hpp, hloc_a] at hp_a; cases hp_a
        · exfalso; apply hstill; simp [updateFn, Ne.symm hpp, hloc_a]
      | board _ _ => exfalso; exact hstill hloc_a
      | disembark _ => exfalso; exact hstill hloc_a
      | sail _ _ _ => exfalso; exact hstill hloc_a

/-- Symmetric lemma for ground undelivered package on side A needing a truck from side B. -/
theorem ground_undeliv_loaded_by_capable_BA {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (l : Fin I.numLocs)
    (hloc : s.pkgLoc p = .atLoc l) (hnd : s.pkgDelivered p = false)
    (inComp inA : Fin I.numLocs → Bool) (hcl : CompClosed I inComp)
    (hin : inComp l = true) (hside : inA l = true)
    (hno_capable : ∀ t, inComp (s.truckPhysLoc t) = true → inA (s.truckPhysLoc t) = true →
      dynEffCap I s t < I.pkgWeight p) :
    ∃ t : Fin I.numTrucks, inComp (s.truckPhysLoc t) = true ∧ 1 ≤ planTruckCrossBA inComp inA s π t := by
  have hflip := ground_undeliv_loaded_by_capable hv hp hg p l hloc hnd inComp (fun x => !inA x)
    hcl hin (by simp [hside]) (by intro t ht hna; apply hno_capable t ht; simp at hna; exact hna)
  rcases hflip with ⟨t, ht, hpos⟩
  refine ⟨t, ht, ?_⟩
  have heq : ∀ (sa : State I) (π' : Plan I),
      planTruckCrossAB inComp (fun x => !inA x) sa π' t = planTruckCrossBA inComp inA sa π' t := by
    intro sa π'
    induction π' generalizing sa with
    | nil => rfl
    | cons a rest ih =>
      simp only [planTruckCrossAB, planTruckCrossBA, stepTruckCrossAB, stepTruckCrossBA, Bool.not_not, ih]
  rw [heq] at hpos
  exact hpos

/-- Plan-level soundness of `fluxLB` for ANY 2-sided cut `(inComp, inA)` (`ex1.py:L66-L93`).
    Proves both directed crossing lower bounds directly on `planTruckCrossAB` / `planTruckCrossBA`. -/
theorem fluxLB_plan_sound {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (inComp inA : Fin I.numLocs → Bool) (hcl : CompClosed I inComp)
    (cap : Nat) (hcap : 0 < cap)
    (hcap_ge : ∀ t, inComp (s.truckPhysLoc t) = true → dynEffCap I s t ≤ cap)
    (need_ab need_ba : Bool)
    (hneed_ab_sound : need_ab = true →
      ∃ p l, s.pkgLoc p = .atLoc l ∧ s.pkgDelivered p = false ∧
        inComp l = true ∧ inA l = false ∧
        ∀ t, inComp (s.truckPhysLoc t) = true → inA (s.truckPhysLoc t) = false →
          dynEffCap I s t < I.pkgWeight p)
    (hneed_ba_sound : need_ba = true →
      ∃ p l, s.pkgLoc p = .atLoc l ∧ s.pkgDelivered p = false ∧
        inComp l = true ∧ inA l = true ∧
        ∀ t, inComp (s.truckPhysLoc t) = true → inA (s.truckPhysLoc t) = true →
          dynEffCap I s t < I.pkgWeight p) :
    let tIn  (t : Fin I.numTrucks) := inComp (s.truckPhysLoc t)
    let tSide (t : Fin I.numTrucks) := inA (s.truckPhysLoc t)
    let m_a := finSum (fun t => if tIn t && tSide t then 1 else 0)
    let m_b := finSum (fun t => if tIn t && !tSide t then 1 else 0)
    let c_a := finSum (fun t => if tIn t && tSide t then dynEffCap I s t else 0)
    let c_b := finSum (fun t => if tIn t && !tSide t then dynEffCap I s t else 0)
    let w_ab := finSum (fun p =>
      if !s.pkgDelivered p && inComp (s.pkgPhysLoc p) && inA (s.pkgPhysLoc p) && !inA (I.pkgGoal p)
      then I.pkgWeight p else 0)
    let w_ba := finSum (fun p =>
      if !s.pkgDelivered p && inComp (s.pkgPhysLoc p) && !inA (s.pkgPhysLoc p) && inA (I.pkgGoal p)
      then I.pkgWeight p else 0)
    let h_ab := finSum (fun p =>
      if !s.pkgDelivered p && inComp (s.pkgPhysLoc p) && inA (s.pkgPhysLoc p) && !inA (I.pkgGoal p) &&
         decide (I.pkgWeight p > cap / 2)
      then 1 else 0)
    let h_ba := finSum (fun p =>
      if !s.pkgDelivered p && inComp (s.pkgPhysLoc p) && !inA (s.pkgPhysLoc p) && inA (I.pkgGoal p) &&
         decide (I.pkgWeight p > cap / 2)
      then 1 else 0)
    let r := fluxLB w_ab w_ba h_ab h_ba need_ab need_ba m_a m_b c_a c_b cap
    r.1 ≤ finSum (fun t => if tIn t then planTruckCrossAB inComp inA s π t else 0) ∧
    r.2 ≤ finSum (fun t => if tIn t then planTruckCrossBA inComp inA s π t else 0) := by
  intro tIn tSide m_a m_b c_a c_b w_ab w_ba h_ab h_ba r
  -- Helper: carryAB ≤ xAB * dynEffCap and carryBA ≤ xBA * dynEffCap
  have hcarry_bound : ∀ {s₁ s_end : State I} {π' : Plan I} (hp' : ValidPlan I s₁ π' s_end)
      (hv₁ : ValidState I s₁) (t : Fin I.numTrucks),
      planTruckCarryAB s inComp inA s₁ π' t ≤ planTruckCrossAB inComp inA s₁ π' t * dynEffCap I s t ∧
      planTruckCarryBA s inComp inA s₁ π' t ≤ planTruckCrossBA inComp inA s₁ π' t * dynEffCap I s t := by
    intro s₁ s_end π' hp'
    induction hp' with
    | nil => intro _ _; simp [planTruckCarryAB, planTruckCarryBA, planTruckCrossAB, planTruckCrossBA]
    | @cons sa sb _ a rest hstep _ ih =>
      intro hv₁ t
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      have ⟨ih1, ih2⟩ := ih (validState_step hv₁ hstep) t
      have hld := truckLoad_undeliv_le_dynEffCap (s := s) hv₁ t
      simp only [planTruckCarryAB, planTruckCarryBA, planTruckCrossAB, planTruckCrossBA, ← hsb_eq]
      constructor
      · unfold stepTruckCrossAB
        split
        · simp only [↓reduceIte, Nat.add_mul, Nat.one_mul]; omega
        · simp only [Nat.zero_ne_one, ↓reduceIte, Nat.zero_add]; omega
      · unfold stepTruckCrossBA
        split
        · simp only [↓reduceIte, Nat.add_mul, Nat.one_mul]; omega
        · simp only [Nat.zero_ne_one, ↓reduceIte, Nat.zero_add]; omega
  -- Helper: sum of `I.pkgWeight p * planPkgCrossAB p` over undeliv pkgs = sum of `planTruckCarryAB t`
  have hpkg_to_truck_ab : ∀ {s₁ s_end : State I} {π' : Plan I} (hp' : ValidPlan I s₁ π' s_end),
      finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inComp inA s₁ π' p else 0) =
      finSum (fun t => if inComp (s₁.truckPhysLoc t) then planTruckCarryAB s inComp inA s₁ π' t else 0) := by
    intro s₁ s_end π' hp'
    induction hp' with
    | nil =>
      simp only [planPkgCrossAB, planTruckCarryAB, Nat.mul_zero, ite_self, finSum_zero]
    | @cons sa sb _ a rest hstep _ ih =>
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      have hin_eq : ∀ t, inComp (sb.truckPhysLoc t) = inComp (sa.truckPhysLoc t) := hcl hstep
      have hsplit_l :
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inComp inA sa (a :: rest) p else 0) =
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p *
            (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossAB inComp inA sa sb t) else 0) +
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inComp inA sb rest p else 0) := by
        rw [← finSum_add]; congr 1; funext p; simp only [planPkgCrossAB, ← hsb_eq]
        split <;> simp [Nat.mul_add]
      have hsplit_r :
          finSum (fun t => if inComp (sa.truckPhysLoc t) then planTruckCarryAB s inComp inA sa (a :: rest) t else 0) =
          finSum (fun t => if inComp (sa.truckPhysLoc t) then
            (if stepTruckCrossAB inComp inA sa sb t = 1 then
              finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
             else 0) else 0) +
          finSum (fun t => if inComp (sb.truckPhysLoc t) then planTruckCarryAB s inComp inA sb rest t else 0) := by
        rw [← finSum_add]; congr 1; funext t; simp only [planTruckCarryAB, ← hsb_eq, hin_eq t]
        split <;> simp
      rw [hsplit_l, hsplit_r, ih]
      congr 1
      have hhead :
          finSum (fun t => if inComp (sa.truckPhysLoc t) then
            (if stepTruckCrossAB inComp inA sa sb t = 1 then
              finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
             else 0) else 0) =
          finSum (fun t => finSum (fun p =>
            if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) &&
               !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t)
            then I.pkgWeight p else 0)) := by
        congr 1; funext t
        cases hc : inComp (sa.truckPhysLoc t) with
        | false => simp only [Bool.false_eq_true, ↓reduceIte, Bool.false_and, finSum_zero]
        | true =>
          by_cases hcr : stepTruckCrossAB inComp inA sa sb t = 1
          · simp [hcr]
          · simp only [hc, hcr, decide_false, Bool.and_false, Bool.false_and, Bool.false_eq_true, ↓reduceIte, finSum_zero]
      rw [hhead, finSum_comm]
      congr 1; funext p
      cases hpl : sa.pkgLoc p with
      | atLoc l =>
        simp only [Nat.mul_zero, ite_self]
        have hz : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossAB inComp inA sa sb t' = 1) &&
            !s.pkgDelivered p && (PkgPos.atLoc l == PkgPos.inTruck t') then I.pkgWeight p else 0) =
            (fun _ => 0) := by funext t'; simp
        rw [hz, finSum_zero]
      | inTruck t =>
        have hfn : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossAB inComp inA sa sb t' = 1) &&
            !s.pkgDelivered p && (PkgPos.inTruck t == PkgPos.inTruck t') then I.pkgWeight p else 0) =
            (fun t' => if t' = t then
              (if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) && !s.pkgDelivered p
               then I.pkgWeight p else 0) else 0) := by
          funext t'
          by_cases ht : t' = t
          · subst ht; simp
          · have hne : (PkgPos.inTruck t == PkgPos.inTruck t') = false := by simp [Ne.symm ht]
            simp [ht, hne]
        rw [hfn, finSum_ite_eq]
        unfold stepTruckCrossAB
        cases hd : s.pkgDelivered p <;> cases hc : inComp (sa.truckPhysLoc t) <;>
          cases ha : inA (sa.truckPhysLoc t) <;> cases hb : inA (sb.truckPhysLoc t) <;> simp [hd, hc, ha, hb]
  have hpkg_to_truck_ba : ∀ {s₁ s_end : State I} {π' : Plan I} (hp' : ValidPlan I s₁ π' s_end),
      finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inComp inA s₁ π' p else 0) =
      finSum (fun t => if inComp (s₁.truckPhysLoc t) then planTruckCarryBA s inComp inA s₁ π' t else 0) := by
    intro s₁ s_end π' hp'
    induction hp' with
    | nil =>
      simp only [planPkgCrossBA, planTruckCarryBA, Nat.mul_zero, ite_self, finSum_zero]
    | @cons sa sb _ a rest hstep _ ih =>
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      have hin_eq : ∀ t, inComp (sb.truckPhysLoc t) = inComp (sa.truckPhysLoc t) := hcl hstep
      have hsplit_l :
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inComp inA sa (a :: rest) p else 0) =
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p *
            (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossBA inComp inA sa sb t) else 0) +
          finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inComp inA sb rest p else 0) := by
        rw [← finSum_add]; congr 1; funext p; simp only [planPkgCrossBA, ← hsb_eq]
        split <;> simp [Nat.mul_add]
      have hsplit_r :
          finSum (fun t => if inComp (sa.truckPhysLoc t) then planTruckCarryBA s inComp inA sa (a :: rest) t else 0) =
          finSum (fun t => if inComp (sa.truckPhysLoc t) then
            (if stepTruckCrossBA inComp inA sa sb t = 1 then
              finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
             else 0) else 0) +
          finSum (fun t => if inComp (sb.truckPhysLoc t) then planTruckCarryBA s inComp inA sb rest t else 0) := by
        rw [← finSum_add]; congr 1; funext t; simp only [planTruckCarryBA, ← hsb_eq, hin_eq t]
        split <;> simp
      rw [hsplit_l, hsplit_r, ih]
      congr 1
      have hhead :
          finSum (fun t => if inComp (sa.truckPhysLoc t) then
            (if stepTruckCrossBA inComp inA sa sb t = 1 then
              finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) then I.pkgWeight p else 0)
             else 0) else 0) =
          finSum (fun t => finSum (fun p =>
            if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) &&
               !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t)
            then I.pkgWeight p else 0)) := by
        congr 1; funext t
        cases hc : inComp (sa.truckPhysLoc t) with
        | false => simp only [Bool.false_eq_true, ↓reduceIte, Bool.false_and, finSum_zero]
        | true =>
          by_cases hcr : stepTruckCrossBA inComp inA sa sb t = 1
          · simp [hcr]
          · simp only [hc, hcr, decide_false, Bool.and_false, Bool.false_and, Bool.false_eq_true, ↓reduceIte, finSum_zero]
      rw [hhead, finSum_comm]
      congr 1; funext p
      cases hpl : sa.pkgLoc p with
      | atLoc l =>
        simp only [Nat.mul_zero, ite_self]
        have hz : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossBA inComp inA sa sb t' = 1) &&
            !s.pkgDelivered p && (PkgPos.atLoc l == PkgPos.inTruck t') then I.pkgWeight p else 0) =
            (fun _ => 0) := by funext t'; simp
        rw [hz, finSum_zero]
      | inTruck t =>
        have hfn : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossBA inComp inA sa sb t' = 1) &&
            !s.pkgDelivered p && (PkgPos.inTruck t == PkgPos.inTruck t') then I.pkgWeight p else 0) =
            (fun t' => if t' = t then
              (if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) && !s.pkgDelivered p
               then I.pkgWeight p else 0) else 0) := by
          funext t'
          by_cases ht : t' = t
          · subst ht; simp
          · have hne : (PkgPos.inTruck t == PkgPos.inTruck t') = false := by simp [Ne.symm ht]
            simp [ht, hne]
        rw [hfn, finSum_ite_eq]
        unfold stepTruckCrossBA
        cases hd : s.pkgDelivered p <;> cases hc : inComp (sa.truckPhysLoc t) <;>
          cases ha : inA (sa.truckPhysLoc t) <;> cases hb : inA (sb.truckPhysLoc t) <;> simp [hd, hc, ha, hb]
  -- Helper: heavy crossings bound `finSum_{heavy} planPkgCrossAB ≤ finSum_{t in comp} planTruckCrossAB`
  have hheavy_to_truck : ∀ {s₁ s_end : State I} {π' : Plan I} (hp' : ValidPlan I s₁ π' s_end)
      (hv₁ : ValidState I s₁) (hcap_ge₁ : ∀ t, inComp (s₁.truckPhysLoc t) = true → dynEffCap I s t ≤ cap),
      finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
        planPkgCrossAB inComp inA s₁ π' p else 0) ≤
      finSum (fun t => if inComp (s₁.truckPhysLoc t) then planTruckCrossAB inComp inA s₁ π' t else 0) ∧
      finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
        planPkgCrossBA inComp inA s₁ π' p else 0) ≤
      finSum (fun t => if inComp (s₁.truckPhysLoc t) then planTruckCrossBA inComp inA s₁ π' t else 0) := by
    intro s₁ s_end π' hp'
    induction hp' with
    | nil =>
      intro _ _
      simp only [planPkgCrossAB, planPkgCrossBA, planTruckCrossAB, planTruckCrossBA, ite_self, finSum_zero, Nat.le_refl, and_self]
    | @cons sa sb _ a rest hstep _ ih =>
      intro hv₁ hcap_ge₁
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      have hin_eq : ∀ t, inComp (sb.truckPhysLoc t) = inComp (sa.truckPhysLoc t) := hcl hstep
      have hcap_ge₂ : ∀ t, inComp (sb.truckPhysLoc t) = true → dynEffCap I s t ≤ cap := by
        intro t ht; exact hcap_ge₁ t (hin_eq t ▸ ht)
      have ⟨ih1, ih2⟩ := ih (validState_step hv₁ hstep) hcap_ge₂
      have hone_heavy : ∀ t, inComp (sa.truckPhysLoc t) = true →
          finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) &&
              decide (I.pkgWeight p > cap / 2) then 1 else 0) ≤ 1 := by
        intro t ht
        let mask : Fin I.numPkgs → Bool := fun p => !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t)
        have hle : subsetWeight I.pkgWeight mask ≤ cap :=
          Nat.le_trans (truckLoad_undeliv_le_dynEffCap hv₁ t) (hcap_ge₁ t ht)
        exact at_most_one_heavy I.pkgWeight mask cap hle
      constructor
      · have hsl : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
            planPkgCrossAB inComp inA sa (a :: rest) p else 0) =
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossAB inComp inA sa sb t) else 0) +
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              planPkgCrossAB inComp inA sb rest p else 0) := by
          rw [← finSum_add]; congr 1; funext p; simp only [planPkgCrossAB, ← hsb_eq]; split <;> simp
        have hsr : finSum (fun t => if inComp (sa.truckPhysLoc t) then
            planTruckCrossAB inComp inA sa (a :: rest) t else 0) =
            finSum (fun t => if inComp (sa.truckPhysLoc t) then stepTruckCrossAB inComp inA sa sb t else 0) +
            finSum (fun t => if inComp (sb.truckPhysLoc t) then planTruckCrossAB inComp inA sb rest t else 0) := by
          rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossAB, ← hsb_eq, hin_eq t]; split <;> simp
        rw [hsl, hsr]
        have hhead_le : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
            (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossAB inComp inA sa sb t) else 0) ≤
            finSum (fun t => if inComp (sa.truckPhysLoc t) then stepTruckCrossAB inComp inA sa sb t else 0) := by
          have heq :
              finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
                (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossAB inComp inA sa sb t) else 0) =
              finSum (fun t => if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) then
                finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) &&
                  decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) := by
            rw [show finSum (fun t => if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) then
                  finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) &&
                    decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) =
                finSum (fun t => finSum (fun p =>
                  if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) &&
                     !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0)) from by
              congr 1; funext t
              by_cases hcond : (inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1)) = true
              · simp only [hcond, ↓reduceIte, Bool.true_and]
              · simp only [hcond, ↓reduceIte, Bool.false_and]
                exact finSum_zero.symm]
            rw [finSum_comm]
            congr 1; funext p
            cases hpl : sa.pkgLoc p with
            | atLoc l =>
              simp only [ite_self]
              have hz : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossAB inComp inA sa sb t' = 1) &&
                  !s.pkgDelivered p && (PkgPos.atLoc l == PkgPos.inTruck t') && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0) = (fun _ => 0) := by funext t'; simp
              rw [hz, finSum_zero]
            | inTruck t =>
              have hfn : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossAB inComp inA sa sb t' = 1) &&
                  !s.pkgDelivered p && (PkgPos.inTruck t == PkgPos.inTruck t') && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0) =
                  (fun t' => if t' = t then
                    (if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossAB inComp inA sa sb t = 1) &&
                        !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) := by
                funext t'; by_cases ht : t' = t
                · subst ht; simp
                · have hne : (PkgPos.inTruck t == PkgPos.inTruck t') = false := by simp [Ne.symm ht]
                  simp [ht, hne]
              rw [hfn, finSum_ite_eq]
              unfold stepTruckCrossAB
              cases hd : s.pkgDelivered p <;> by_cases hw : I.pkgWeight p > cap / 2 <;>
                cases hc : inComp (sa.truckPhysLoc t) <;> cases ha : inA (sa.truckPhysLoc t) <;>
                cases hb : inA (sb.truckPhysLoc t) <;> simp [hd, hw, hc, ha, hb]
          rw [heq]
          apply finSum_le_finSum; intro t
          cases hc : inComp (sa.truckPhysLoc t) with
          | false => simp
          | true =>
            by_cases hcr : stepTruckCrossAB inComp inA sa sb t = 1
            · simp only [hc, hcr, decide_true, Bool.and_self, ↓reduceIte]
              exact hone_heavy t hc
            · simp [hcr]
        omega
      · have hsl : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
            planPkgCrossBA inComp inA sa (a :: rest) p else 0) =
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossBA inComp inA sa sb t) else 0) +
            finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
              planPkgCrossBA inComp inA sb rest p else 0) := by
          rw [← finSum_add]; congr 1; funext p; simp only [planPkgCrossBA, ← hsb_eq]; split <;> simp
        have hsr : finSum (fun t => if inComp (sa.truckPhysLoc t) then
            planTruckCrossBA inComp inA sa (a :: rest) t else 0) =
            finSum (fun t => if inComp (sa.truckPhysLoc t) then stepTruckCrossBA inComp inA sa sb t else 0) +
            finSum (fun t => if inComp (sb.truckPhysLoc t) then planTruckCrossBA inComp inA sb rest t else 0) := by
          rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossBA, ← hsb_eq, hin_eq t]; split <;> simp
        rw [hsl, hsr]
        have hhead_le : finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
            (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossBA inComp inA sa sb t) else 0) ≤
            finSum (fun t => if inComp (sa.truckPhysLoc t) then stepTruckCrossBA inComp inA sa sb t else 0) := by
          have heq :
              finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then
                (match sa.pkgLoc p with | .atLoc _ => 0 | .inTruck t => stepTruckCrossBA inComp inA sa sb t) else 0) =
              finSum (fun t => if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) then
                finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) &&
                  decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) := by
            rw [show finSum (fun t => if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) then
                  finSum (fun p => if !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) &&
                    decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) =
                finSum (fun t => finSum (fun p =>
                  if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) &&
                     !s.pkgDelivered p && (sa.pkgLoc p == .inTruck t) && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0)) from by
              congr 1; funext t
              by_cases hcond : (inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1)) = true
              · simp only [hcond, ↓reduceIte, Bool.true_and]
              · simp only [hcond, ↓reduceIte, Bool.false_and]
                exact finSum_zero.symm]
            rw [finSum_comm]
            congr 1; funext p
            cases hpl : sa.pkgLoc p with
            | atLoc l =>
              simp only [ite_self]
              have hz : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossBA inComp inA sa sb t' = 1) &&
                  !s.pkgDelivered p && (PkgPos.atLoc l == PkgPos.inTruck t') && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0) = (fun _ => 0) := by funext t'; simp
              rw [hz, finSum_zero]
            | inTruck t =>
              have hfn : (fun t' => if inComp (sa.truckPhysLoc t') && decide (stepTruckCrossBA inComp inA sa sb t' = 1) &&
                  !s.pkgDelivered p && (PkgPos.inTruck t == PkgPos.inTruck t') && decide (I.pkgWeight p > cap / 2)
                  then 1 else 0) =
                  (fun t' => if t' = t then
                    (if inComp (sa.truckPhysLoc t) && decide (stepTruckCrossBA inComp inA sa sb t = 1) &&
                        !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then 1 else 0) else 0) := by
                funext t'; by_cases ht : t' = t
                · subst ht; simp
                · have hne : (PkgPos.inTruck t == PkgPos.inTruck t') = false := by simp [Ne.symm ht]
                  simp [ht, hne]
              rw [hfn, finSum_ite_eq]
              unfold stepTruckCrossBA
              cases hd : s.pkgDelivered p <;> by_cases hw : I.pkgWeight p > cap / 2 <;>
                cases hc : inComp (sa.truckPhysLoc t) <;> cases ha : inA (sa.truckPhysLoc t) <;>
                cases hb : inA (sb.truckPhysLoc t) <;> simp [hd, hw, hc, ha, hb]
          rw [heq]
          apply finSum_le_finSum; intro t
          cases hc : inComp (sa.truckPhysLoc t) with
          | false => simp
          | true =>
            by_cases hcr : stepTruckCrossBA inComp inA sa sb t = 1
            · simp only [hc, hcr, decide_true, Bool.and_self, ↓reduceIte]
              exact hone_heavy t hc
            · simp [hcr]
        omega
  -- Apply `fluxLB_abstract_sound`!
  apply fluxLB_abstract_sound tIn tSide (dynEffCap I s)
    (planTruckCrossAB inComp inA s π) (planTruckCrossBA inComp inA s π)
    (planTruckCarryAB s inComp inA s π) (planTruckCarryBA s inComp inA s π) cap hcap
  · intro t ht; exact hcap_ge t ht
  · intro t ht; exact (planTruckCross_alternation hcl hp t ht).1
  · intro t ht; exact (planTruckCross_alternation hcl hp t ht).2
  · intro t _; exact (hcarry_bound hp hv t).1
  · intro t _; exact (hcarry_bound hp hv t).2
  · -- w_ab ≤ sum carryAB
    rw [← hpkg_to_truck_ab hp]
    apply finSum_le_finSum; intro p
    cases hu : s.pkgDelivered p <;> cases hc : inComp (s.pkgPhysLoc p) <;>
      cases ha : inA (s.pkgPhysLoc p) <;> cases hgb : inA (I.pkgGoal p) <;> simp
    have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    have hpos := planPkgCrossAB_pos_of_side_change hcl hp p hc ha (hgoal_p ▸ hgb)
    calc I.pkgWeight p = I.pkgWeight p * 1 := (Nat.mul_one _).symm
      _ ≤ I.pkgWeight p * planPkgCrossAB inComp inA s π p := Nat.mul_le_mul_left _ hpos
  · -- w_ba ≤ sum carryBA
    rw [← hpkg_to_truck_ba hp]
    apply finSum_le_finSum; intro p
    cases hu : s.pkgDelivered p <;> cases hc : inComp (s.pkgPhysLoc p) <;>
      cases ha : inA (s.pkgPhysLoc p) <;> cases hgb : inA (I.pkgGoal p) <;> simp
    have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    have hpos := planPkgCrossBA_pos_of_side_change hcl hp p hc ha (hgoal_p ▸ hgb)
    calc I.pkgWeight p = I.pkgWeight p * 1 := (Nat.mul_one _).symm
      _ ≤ I.pkgWeight p * planPkgCrossBA inComp inA s π p := Nat.mul_le_mul_left _ hpos
  · -- h_ab ≤ sum xAB
    apply Nat.le_trans _ (hheavy_to_truck hp hv hcap_ge).1
    apply finSum_le_finSum; intro p
    cases hu : s.pkgDelivered p <;> cases hc : inComp (s.pkgPhysLoc p) <;>
      cases ha : inA (s.pkgPhysLoc p) <;> cases hgb : inA (I.pkgGoal p) <;>
      by_cases hw : I.pkgWeight p > cap / 2 <;> simp [hw]
    have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    exact planPkgCrossAB_pos_of_side_change hcl hp p hc ha (hgoal_p ▸ hgb)
  · -- h_ba ≤ sum xBA
    apply Nat.le_trans _ (hheavy_to_truck hp hv hcap_ge).2
    apply finSum_le_finSum; intro p
    cases hu : s.pkgDelivered p <;> cases hc : inComp (s.pkgPhysLoc p) <;>
      cases ha : inA (s.pkgPhysLoc p) <;> cases hgb : inA (I.pkgGoal p) <;>
      by_cases hw : I.pkgWeight p > cap / 2 <;> simp [hw]
    have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    exact planPkgCrossBA_pos_of_side_change hcl hp p hc ha (hgoal_p ▸ hgb)
  · -- need_ab → 1 ≤ sum xAB
    intro hnab
    rcases hneed_ab_sound hnab with ⟨p, l, hloc, hnd, hin, hside, hnocap⟩
    rcases ground_undeliv_loaded_by_capable hv hp hg p l hloc hnd inComp inA hcl hin hside hnocap with ⟨t, hin_t, hpos⟩
    have hle := le_finSum (fun t' => if tIn t' then planTruckCrossAB inComp inA s π t' else 0) t
    simp only [tIn, hin_t, ↓reduceIte] at hle
    exact Nat.le_trans hpos hle
  · -- need_ba → 1 ≤ sum xBA
    intro hnba
    rcases hneed_ba_sound hnba with ⟨p, l, hloc, hnd, hin, hside, hnocap⟩
    rcases ground_undeliv_loaded_by_capable_BA hv hp hg p l hloc hnd inComp inA hcl hin hside hnocap with ⟨t, hin_t, hpos⟩
    have hle := le_finSum (fun t' => if tIn t' then planTruckCrossBA inComp inA s π t' else 0) t
    simp only [tIn, hin_t, ↓reduceIte] at hle
    exact Nat.le_trans hpos hle

end IslandLogistics

