/-
Module 4: Ferries.lean

Formalizes and proves admissibility of Bound C's ferry lower bounds (`h_bd`, `h_sail`):
1. Road-only island graph, ferry action counters, and loaded inter-island sail counters.
2. Cut ferries (`_eval_cut_ferries`, ex1.py:L887-L1033):
   - Per-side sail lower bounds `soh`, `sih`, 2-way/multi-way sums `sof`, `sif`,
     and empty-fetch parity bound `msf`.
   - Exact aboard-truck `(z, x)` split minimization `cbd` via frozen-aboard side tracking.
   - Additivity across distinct cut ferries (`bd_cut ≤ costBD π`, `b7 ≤ sailCount π`).
3. General / cyclic island ferries (`_eval_island_ferries`, ex1.py:L1035-L1246):
   - Per-island board/disembark bounds `b1`, `d1` (including `str_g`, `bi - mg_i`,
     and capacity conservation `(wgo - cg_i) / max_cap`).
   - Multi-hop island metric bounds `b2`, `d2` via ferry-invariant potentials `potB`, `potD`.
   - Global board/disembark conservation `lb_d - n_ab ≤ boardCount π`.
   - Loaded inter-island sail bounds `sum_so`, `sum_si`, `b4`, `b5` (weight + heavy `h_sw / kh`),
     and empty-positioning `+1` when `vol > 0`, `n_ab = 0`, and no active ferry starts on a truck island.
   - Island ferry-conservation bounds `sum_req_i` and `b3 = max_isl (ro + ri)`.
-/

import Domain
import PackingAndFlux
import BridgesAndCycles

namespace IslandLogistics

-- ==============================================================================
-- 1. ISLAND GRAPH & FERRY ACTION COUNTERS
-- ==============================================================================

/-- Road-only island decomposition and island-level ferry metadata (`ex1.py:L350-L384`). -/
structure IslandGraph (I : Instance) where
  numIslands        : Nat
  islandOf          : Fin I.numLocs → Fin numIslands
  road_same         : ∀ u v, I.road u v = true → islandOf u = islandOf v
  minSails          : Fin numIslands → Fin numIslands → Nat
  minSails_self     : ∀ i, minSails i i = 0
  minSails_tri      : ∀ i j k, minSails i k ≤ minSails i j + minSails j k
  minSails_ferry    : ∀ f u v, 0 < I.ferryCap f →
    I.ferryServed f u = true → I.ferryServed f v = true →
    minSails (islandOf u) (islandOf v) ≤ 1
  /-- Active inter-island ferries serving island `isl` (`island_ferries[isl]`). -/
  islandFerries     : Fin numIslands → List (Fin I.numFerries)
  islandFerries_nd  : ∀ isl, (islandFerries isl).Nodup
  islandFerries_cov : ∀ f u v, 0 < I.ferryCap f →
    I.ferryServed f u = true → I.ferryServed f v = true →
    islandOf u ≠ islandOf v →
    f ∈ islandFerries (islandOf u) ∧ f ∈ islandFerries (islandOf v)
  /-- Upper bound on `I.ferryCap f` over `f ∈ islandFerries isl` (`max_island_ferry_truck_cap`). -/
  maxIslandFerryCap : Fin numIslands → Nat
  maxIslandFerryCap_ge : ∀ isl f, f ∈ islandFerries isl → I.ferryCap f ≤ maxIslandFerryCap isl
  /-- Upper bound on `I.ferryCap f` over all active inter-island ferries (`max_inter_ferry_truck_cap`). -/
  maxInterFerryCap  : Nat
  maxInterFerryCap_ge : ∀ f u v, 0 < I.ferryCap f →
    I.ferryServed f u = true → I.ferryServed f v = true →
    islandOf u ≠ islandOf v → I.ferryCap f ≤ maxInterFerryCap

def isBoard {I : Instance} : Action I → Bool
  | .board _ _ => true
  | _          => false

def isDisembark {I : Instance} : Action I → Bool
  | .disembark _ _ => true
  | _              => false

def isFerryBoard {I : Instance} (f : Fin I.numFerries) : Action I → Bool
  | .board _ f' => decide (f' = f)
  | _           => false

def isFerryDisembark {I : Instance} (f : Fin I.numFerries) : Action I → Bool
  | .disembark _ f' => decide (f' = f)
  | _               => false

def isFerryBD {I : Instance} (f : Fin I.numFerries) : Action I → Bool
  | .board _ f'     => decide (f' = f)
  | .disembark _ f' => decide (f' = f)
  | _               => false

def isFerrySail {I : Instance} (f : Fin I.numFerries) : Action I → Bool
  | .sail f' _ _ => decide (f' = f)
  | _            => false

def isTruckFerryBoard {I : Instance} (t : Fin I.numTrucks) (f : Fin I.numFerries) : Action I → Bool
  | .board t' f' => decide (t' = t) && decide (f' = f)
  | _            => false

def isTruckFerryDisembark {I : Instance} (t : Fin I.numTrucks) (f : Fin I.numFerries) : Action I → Bool
  | .disembark t' f' => decide (t' = t) && decide (f' = f)
  | _                => false

def isTruckBoard {I : Instance} (t : Fin I.numTrucks) : Action I → Bool
  | .board t' _ => decide (t' = t)
  | _           => false

def isTruckDisembark {I : Instance} (t : Fin I.numTrucks) : Action I → Bool
  | .disembark t' _ => decide (t' = t)
  | _               => false

def boardCount {I : Instance} (π : Plan I) : Nat := countActions isBoard π
def disembarkCount {I : Instance} (π : Plan I) : Nat := countActions isDisembark π
def ferryBDCount {I : Instance} (f : Fin I.numFerries) (π : Plan I) : Nat := countActions (isFerryBD f) π
def ferrySailCount {I : Instance} (f : Fin I.numFerries) (π : Plan I) : Nat := countActions (isFerrySail f) π

theorem costBD_eq_board_add_disembark {I : Instance} (π : Plan I) :
    costBD π = boardCount π + disembarkCount π := by
  unfold costBD boardCount disembarkCount countActions
  induction π with
  | nil => rfl
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons]
    have ha : actionCostBD a = (if isBoard a = true then 1 else 0) + (if isDisembark a = true then 1 else 0) := by
      cases a <;> rfl
    omega

theorem ferryBDCount_eq_sum_trucks {I : Instance} (f : Fin I.numFerries) (π : Plan I) :
    ferryBDCount f π =
    finSum (fun t => countActions (isTruckFerryBoard t f) π + countActions (isTruckFerryDisembark t f) π) := by
  unfold ferryBDCount countActions
  induction π with
  | nil => simp [finSum_zero]
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons]
    have hsplit : finSum (fun t =>
        ((if isTruckFerryBoard t f a = true then 1 else 0) +
          (List.map (fun a => if isTruckFerryBoard t f a = true then 1 else 0) rest).sum) +
        ((if isTruckFerryDisembark t f a = true then 1 else 0) +
          (List.map (fun a => if isTruckFerryDisembark t f a = true then 1 else 0) rest).sum)) =
      finSum (fun t => (if isTruckFerryBoard t f a = true then 1 else 0) +
                       (if isTruckFerryDisembark t f a = true then 1 else 0)) +
      finSum (fun t => (List.map (fun a => if isTruckFerryBoard t f a = true then 1 else 0) rest).sum +
                       (List.map (fun a => if isTruckFerryDisembark t f a = true then 1 else 0) rest).sum) := by
      rw [← finSum_add]; congr 1; funext t; omega
    rw [hsplit, ← ih]
    congr 1
    cases a with
    | board t₀ f₀ =>
      have hfn : (fun t => (if isTruckFerryBoard t f (.board t₀ f₀) = true then 1 else 0) +
                           (if isTruckFerryDisembark t f (.board t₀ f₀) = true then 1 else 0)) =
                 (fun t => if t = t₀ then (if decide (f₀ = f) = true then 1 else 0) else 0) := by
        funext t; by_cases ht : t = t₀
        · subst ht; simp [isTruckFerryBoard, isTruckFerryDisembark]
        · have hne : t₀ ≠ t := Ne.symm ht
          simp [isTruckFerryBoard, isTruckFerryDisembark, ht, hne]
      rw [hfn, finSum_ite_eq]; rfl
    | disembark t₀ f₀ =>
      have hfn : (fun t => (if isTruckFerryBoard t f (.disembark t₀ f₀) = true then 1 else 0) +
                           (if isTruckFerryDisembark t f (.disembark t₀ f₀) = true then 1 else 0)) =
                 (fun t => if t = t₀ then (if decide (f₀ = f) = true then 1 else 0) else 0) := by
        funext t; by_cases ht : t = t₀
        · subst ht; simp [isTruckFerryBoard, isTruckFerryDisembark]
        · have hne : t₀ ≠ t := Ne.symm ht
          simp [isTruckFerryBoard, isTruckFerryDisembark, ht, hne]
      rw [hfn, finSum_ite_eq]; rfl
    | drive _ _ _ => simp [isFerryBD, isTruckFerryBoard, isTruckFerryDisembark, finSum_zero]
    | load _ _ => simp [isFerryBD, isTruckFerryBoard, isTruckFerryDisembark, finSum_zero]
    | unload _ _ => simp [isFerryBD, isTruckFerryBoard, isTruckFerryDisembark, finSum_zero]
    | sail _ _ _ => simp [isFerryBD, isTruckFerryBoard, isTruckFerryDisembark, finSum_zero]

/-- Summing `ferryBDCount f π` over a `Nodup` list of ferries is `≤ costBD π`. -/
theorem sum_ferryBDCount_le_costBD {I : Instance} (fs : List (Fin I.numFerries)) (hnd : fs.Nodup) (π : Plan I) :
    (fs.map (fun f => ferryBDCount f π)).sum ≤ costBD π := by
  have hdisj : (fs.map isFerryBD).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
    rw [List.pairwise_map]
    refine hnd.imp ?_
    intro f₁ f₂ hne a h1
    cases a with
    | board _ f' => simp [isFerryBD] at h1 ⊢; subst h1; exact hne
    | disembark _ f' => simp [isFerryBD] at h1 ⊢; subst h1; exact hne
    | _ => simp [isFerryBD] at h1
  have hsum := sum_countActions_disjoint (fs.map isFerryBD) π hdisj
  have hmap : ((fs.map isFerryBD).map (fun p => countActions p π)).sum =
              (fs.map (fun f => ferryBDCount f π)).sum := by
    rw [List.map_map]; rfl
  rw [hmap] at hsum
  apply Nat.le_trans hsum
  unfold countActions costBD
  clear hdisj hsum hmap hnd
  induction π with
  | nil => simp
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons]
    dsimp only at ih ⊢
    have ha : (if ((fs.map isFerryBD).any fun p => p a) = true then 1 else 0) ≤ actionCostBD a := by
      cases a with
      | board _ _ => simp [actionCostBD]; split <;> omega
      | disembark _ _ => simp [actionCostBD]; split <;> omega
      | drive t u v =>
        have hf : ((fs.map isFerryBD).any fun p => p (.drive t u v)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p, hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerryBD] at hpa
        simp [hf, actionCostBD]
      | load p t =>
        have hf : ((fs.map isFerryBD).any fun p' => p' (.load p t)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p', hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerryBD] at hpa
        simp [hf, actionCostBD]
      | unload p t =>
        have hf : ((fs.map isFerryBD).any fun p' => p' (.unload p t)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p', hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerryBD] at hpa
        simp [hf, actionCostBD]
      | sail f u v =>
        have hf : ((fs.map isFerryBD).any fun p => p (.sail f u v)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p, hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f', _, rfl⟩; simp [isFerryBD] at hpa
        simp [hf, actionCostBD]
    omega

/-- Summing `ferrySailCount f π` over a `Nodup` list of ferries is `≤ sailCount π`. -/
theorem sum_ferrySailCount_le_sailCount {I : Instance} (fs : List (Fin I.numFerries)) (hnd : fs.Nodup) (π : Plan I) :
    (fs.map (fun f => ferrySailCount f π)).sum ≤ sailCount π := by
  have hdisj : (fs.map isFerrySail).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
    rw [List.pairwise_map]
    refine hnd.imp ?_
    intro f₁ f₂ hne a h1
    cases a with
    | sail f' _ _ => simp [isFerrySail] at h1 ⊢; subst h1; exact hne
    | _ => simp [isFerrySail] at h1
  have hsum := sum_countActions_disjoint (fs.map isFerrySail) π hdisj
  have hmap : ((fs.map isFerrySail).map (fun p => countActions p π)).sum =
              (fs.map (fun f => ferrySailCount f π)).sum := by
    rw [List.map_map]; rfl
  rw [hmap] at hsum
  apply Nat.le_trans hsum
  unfold countActions sailCount
  clear hdisj hsum hmap hnd
  induction π with
  | nil => simp
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons]
    dsimp only at ih ⊢
    have ha : (if ((fs.map isFerrySail).any fun p => p a) = true then 1 else 0) ≤
              (match a with | .sail _ _ _ => 1 | _ => 0) := by
      cases a with
      | sail f u v => by_cases h : ((fs.map isFerrySail).any fun p => p (.sail f u v)) = true <;> simp [h]
      | drive t u v =>
        have hf : ((fs.map isFerrySail).any fun p => p (.drive t u v)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p, hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerrySail] at hpa
        simp [hf]
      | load p t =>
        have hf : ((fs.map isFerrySail).any fun p' => p' (.load p t)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p', hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerrySail] at hpa
        simp [hf]
      | unload p t =>
        have hf : ((fs.map isFerrySail).any fun p' => p' (.unload p t)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p', hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f, _, rfl⟩; simp [isFerrySail] at hpa
        simp [hf]
      | board t f =>
        have hf : ((fs.map isFerrySail).any fun p => p (.board t f)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p, hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f', _, rfl⟩; simp [isFerrySail] at hpa
        simp [hf]
      | disembark t f =>
        have hf : ((fs.map isFerrySail).any fun p => p (.disembark t f)) = false := by
          rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h
          rcases h with ⟨p, hp, hpa⟩; rw [List.mem_map] at hp; rcases hp with ⟨f', _, rfl⟩; simp [isFerrySail] at hpa
        simp [hf]
    exact Nat.add_le_add ha ih

-- ==============================================================================
-- 2. CUT FERRIES (`_eval_cut_ferries`, ex1.py:L887-L1033)
-- ==============================================================================

/-- A cut ferry disconnecting the island graph into `sides` (`len ≥ 2`) inside `inComp`
    (`_precompute_cut_ferries`, ex1.py:L547-L581). -/
structure CutFerry (I : Instance) (G : IslandGraph I) where
  fi            : Fin I.numFerries
  sides         : List (Fin G.numIslands → Bool)
  inComp        : Fin G.numIslands → Bool
  sides_len     : 2 ≤ sides.length
  hcl           : CompClosed I (fun l => inComp (G.islandOf l))
  fi_inComp     : ∀ l, I.ferryServed fi l = true → inComp (G.islandOf l) = true
  sides_sub     : ∀ inH ∈ sides, ∀ isl, inH isl = true → inComp isl = true
  sides_disj    : sides.Pairwise (fun h₁ h₂ => ∀ isl, h₁ isl = true → h₂ isl = false)
  /-- Removing `fi` disconnects every `inH ∈ sides` from `¬inH` inside `inComp`. -/
  ferry_cut     : ∀ inH ∈ sides, ∀ fj u v, fj ≠ fi → 0 < I.ferryCap fj →
    inComp (G.islandOf u) = true → inComp (G.islandOf v) = true →
    I.ferryServed fj u = true → I.ferryServed fj v = true →
    inH (G.islandOf u) = inH (G.islandOf v)

/-- Predicate matching a `SAIL` of ferry `fi` crossing from `inH = true` to `inH = false`. -/
def isCutSailAB {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (inH : Fin G.numIslands → Bool) : Action I → Bool
  | .sail f u v => decide (f = fi) && inH (G.islandOf u) && !inH (G.islandOf v)
  | _           => false

/-- Predicate matching a `SAIL` of ferry `fi` crossing from `inH = false` to `inH = true`. -/
def isCutSailBA {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (inH : Fin G.numIslands → Bool) : Action I → Bool
  | .sail f u v => decide (f = fi) && !inH (G.islandOf u) && inH (G.islandOf v)
  | _           => false

/-- State-dependent counter of LOADED (≥ 1 truck aboard `fi`) crossing sails `AB` of `fi`. -/
def loadedCutSailAB {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (inH : Fin G.numIslands → Bool) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest =>
      (if isCutSailAB G fi inH a && decide (0 < s.ferryCount fi) then 1 else 0) +
      loadedCutSailAB G fi inH (applyAction s a) rest

def loadedCutSailBA {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (inH : Fin G.numIslands → Bool) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest =>
      (if isCutSailBA G fi inH a && decide (0 < s.ferryCount fi) then 1 else 0) +
      loadedCutSailBA G fi inH (applyAction s a) rest

/-- Helper: sum of `dynEffCap` of trucks aboard ferry `f` in any valid state `sa` is `≤ maxFerryWeight I s0 f`. -/
theorem ferryAboard_dynEffCap_le_maxFerryWeight (I : Instance) (s0 sa : State I) (f : Fin I.numFerries)
    (hv : ValidState I sa) :
    finSum (fun t => if decide (sa.truckLoc t = .onFerry f) = true then dynEffCap I s0 t else 0) ≤
    maxFerryWeight I s0 f := by
  unfold maxFerryWeight
  apply truck_subset_dynEffCap_le_topKSum I s0 (fun t => decide (sa.truckLoc t = .onFerry f))
    (min (I.ferryCap f) I.numTrucks)
  apply Nat.le_min.mpr
  constructor
  · have h := hv.aboard_le_cap f
    simpa [State.ferryCount] using h
  · have hle : finSum (fun t : Fin I.numTrucks => if decide (sa.truckLoc t = .onFerry f) = true then 1 else 0) ≤
               finSum (fun _ : Fin I.numTrucks => 1) := by
      apply finSum_le_finSum; intro t; by_cases h : sa.truckLoc t = .onFerry f <;> simp [h]
    have hones : finSum (fun _ : Fin I.numTrucks => 1) = I.numTrucks := by
      rw [finSum_eq_list_sum]
      suffices ∀ l : List (Fin I.numTrucks), (l.map (fun _ => 1)).sum = l.length by
        rw [this (List.finRange I.numTrucks), List.length_finRange]
      intro l; induction l with | nil => rfl | cons _ _ ih => simp [ih]; omega
    omega

/-- Helper: across a cut ferry `cf` and side `inH`, on a single step:
    - total truck crossings `AB` ≤ `I.ferryCap cf.fi * (if loadedCutSailAB then 1 else 0)`
    - total undelivered weight carried `AB` ≤ `maxFerryWeight I s0 cf.fi * (if loadedCutSailAB then 1 else 0)`
    (and symmetrically for `BA`). -/
theorem cutFerry_step_bounds {I : Instance} (G : IslandGraph I) (cf : CutFerry I G)
    (inH : Fin G.numIslands → Bool) (hside : inH ∈ cf.sides)
    {s0 sa sb : State I} {a : Action I}
    (hv : ValidState I sa) (hstep : Step I sa a sb)
    (hdyn : ∀ t, finSum (fun p => if !s0.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t) then I.pkgWeight p else 0) ≤ dynEffCap I s0 t) :
    let inC := fun l => cf.inComp (G.islandOf l)
    let inA := fun l => inH (G.islandOf l)
    let hitAB := if isCutSailAB G cf.fi inH a && decide (0 < sa.ferryCount cf.fi) then 1 else 0
    let hitBA := if isCutSailBA G cf.fi inH a && decide (0 < sa.ferryCount cf.fi) then 1 else 0
    finSum (fun t => if inC (sa.truckPhysLoc t) then stepTruckCrossAB inC inA sa sb t else 0) ≤
      I.ferryCap cf.fi * hitAB ∧
    finSum (fun t => if inC (sa.truckPhysLoc t) then stepTruckCrossBA inC inA sa sb t else 0) ≤
      I.ferryCap cf.fi * hitBA ∧
    finSum (fun p => if !s0.pkgDelivered p then
        match sa.pkgLoc p with
        | .atLoc _ => 0
        | .inTruck t => if stepTruckCrossAB inC inA sa sb t = 1 then I.pkgWeight p else 0
      else 0) ≤ maxFerryWeight I s0 cf.fi * hitAB ∧
    finSum (fun p => if !s0.pkgDelivered p then
        match sa.pkgLoc p with
        | .atLoc _ => 0
        | .inTruck t => if stepTruckCrossBA inC inA sa sb t = 1 then I.pkgWeight p else 0
      else 0) ≤ maxFerryWeight I s0 cf.fi * hitBA := by
  intro inC inA hitAB hitBA
  -- First prove: if `a` is NOT `sail cf.fi u v`, then `inA (sb.truckPhysLoc t) = inA (sa.truckPhysLoc t)` for all `t` in `inC`!
  have hno_cross : ∀ t, inC (sa.truckPhysLoc t) = true →
      (stepTruckCrossAB inC inA sa sb t = 1 →
        sa.truckLoc t = .onFerry cf.fi ∧ isCutSailAB G cf.fi inH a = true) ∧
      (stepTruckCrossBA inC inA sa sb t = 1 →
        sa.truckLoc t = .onFerry cf.fi ∧ isCutSailBA G cf.fi inH a = true) := by
    intro t htc
    cases hstep with
    | @drive t₀ u v ht₀ _ hroad =>
      have hsame : inA (({ sa with truckLoc := updateFn sa.truckLoc t₀ (.atLoc v) } : State I).truckPhysLoc t) =
                   inA (sa.truckPhysLoc t) := by
        by_cases htt : t = t₀
        · subst htt; simp [State.truckPhysLoc, ht₀, updateFn, inA, G.road_same u v hroad]
        · simp [State.truckPhysLoc, updateFn, htt]
      constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
    | load _ _ _ =>
      constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, State.truckPhysLoc] at h)
    | unload _ _ =>
      constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, State.truckPhysLoc] at h)
    | @board t₀ f ht₀ _ =>
      have hsame : ({ sa with truckLoc := updateFn sa.truckLoc t₀ (.onFerry f) } : State I).truckPhysLoc t =
                   sa.truckPhysLoc t := by
        by_cases htt : t = t₀
        · subst htt; simp [State.truckPhysLoc, ht₀, updateFn]
        · simp [State.truckPhysLoc, updateFn, htt]
      constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
    | @disembark t₀ f ht₀ =>
      have hsame : ({ sa with truckLoc := updateFn sa.truckLoc t₀ (.atLoc (sa.ferryLoc f)) } : State I).truckPhysLoc t =
                   sa.truckPhysLoc t := by
        by_cases htt : t = t₀
        · subst htt; simp [State.truckPhysLoc, ht₀, updateFn]
        · simp [State.truckPhysLoc, updateFn, htt]
      constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
    | @sail f u v hf hne hserved =>
      cases htl : sa.truckLoc t with
      | atLoc l =>
        have hsame : ({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckPhysLoc t = sa.truckPhysLoc t := by
          simp [State.truckPhysLoc, htl]
        constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
      | onFerry f' =>
        by_cases hff : f' = f
        · subst hff
          by_cases hfi : f' = cf.fi
          · subst hfi
            constructor
            · intro h
              simp only [stepTruckCrossAB, State.truckPhysLoc, htl, updateFn, ↓reduceIte, hf] at h
              split at h
              · rename_i hcond
                simp only [Bool.and_eq_true, Bool.not_eq_true'] at hcond
                exact ⟨rfl, by simp only [isCutSailAB, decide_true, Bool.true_and, Bool.and_eq_true, Bool.not_eq_true']; exact ⟨hcond.1.2, hcond.2⟩⟩
              · cases h
            · intro h
              simp only [stepTruckCrossBA, State.truckPhysLoc, htl, updateFn, ↓reduceIte, hf] at h
              split at h
              · rename_i hcond
                simp only [Bool.and_eq_true, Bool.not_eq_true'] at hcond
                exact ⟨rfl, by simp only [isCutSailBA, decide_true, Bool.true_and, Bool.and_eq_true, Bool.not_eq_true']; exact ⟨hcond.1.2, hcond.2⟩⟩
              · cases h
          · -- `f' ≠ cf.fi`, and `t` is aboard `f'`, so `0 < I.ferryCap f'`, hence by `cf.ferry_cut`, `inA u = inA v`!
            have hpos_f : 0 < I.ferryCap f' := by
              have hle1 : 1 ≤ sa.ferryCount f' := by
                have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry f' then 1 else 0) t
                simpa [State.ferryCount, htl] using h
              have := hv.aboard_le_cap f'; omega
            have hu_in : cf.inComp (G.islandOf u) = true := by simpa [inC, State.truckPhysLoc, htl, hf] using htc
            have hv_in : cf.inComp (G.islandOf v) = true := by
              have hc := cf.hcl (Step.sail hf hne hserved) t
              simpa [State.truckPhysLoc, htl, updateFn, hf, hu_in] using hc
            have hu_sv : I.ferryServed f' u = true := hf ▸ hv.ferry_served f'
            have heq := cf.ferry_cut inH hside f' u v hfi hpos_f hu_in hv_in hu_sv hserved
            have hsame : inA (({ sa with ferryLoc := updateFn sa.ferryLoc f' v } : State I).truckPhysLoc t) =
                         inA (sa.truckPhysLoc t) := by
              simp [State.truckPhysLoc, htl, updateFn, hf, inA, heq]
            constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
        · have hsame : ({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckPhysLoc t = sa.truckPhysLoc t := by
            simp [State.truckPhysLoc, htl, updateFn, hff]
          constructor <;> (intro h; simp [stepTruckCrossAB, stepTruckCrossBA, hsame] at h)
  -- Helper: when `hitAB = 0`, no truck crosses AB; when `hitAB = 1`, every crossing truck is aboard `cf.fi`!
  have hab_cross_zero : hitAB = 0 → ∀ t, stepTruckCrossAB inC inA sa sb t = 0 := by
    intro h0 t
    by_cases hcr : stepTruckCrossAB inC inA sa sb t = 1
    · exfalso
      have htc : inC (sa.truckPhysLoc t) = true := by
        unfold stepTruckCrossAB at hcr
        split at hcr
        · rename_i hc; simp only [Bool.and_eq_true] at hc; exact hc.1.1
        · cases hcr
      have ⟨hab_t, hsail⟩ := (hno_cross t htc).1 hcr
      have hpos : 0 < sa.ferryCount cf.fi := by
        have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry cf.fi then 1 else 0) t
        simp only [hab_t, ↓reduceIte] at h
        unfold State.ferryCount; omega
      simp [hitAB, hsail, hpos] at h0
    · unfold stepTruckCrossAB at hcr ⊢; split at hcr <;> simp_all
  have hba_cross_zero : hitBA = 0 → ∀ t, stepTruckCrossBA inC inA sa sb t = 0 := by
    intro h0 t
    by_cases hcr : stepTruckCrossBA inC inA sa sb t = 1
    · exfalso
      have htc : inC (sa.truckPhysLoc t) = true := by
        unfold stepTruckCrossBA at hcr
        split at hcr
        · rename_i hc; simp only [Bool.and_eq_true] at hc; exact hc.1.1
        · cases hcr
      have ⟨hab_t, hsail⟩ := (hno_cross t htc).2 hcr
      have hpos : 0 < sa.ferryCount cf.fi := by
        have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry cf.fi then 1 else 0) t
        simp only [hab_t, ↓reduceIte] at h
        unfold State.ferryCount; omega
      simp [hitBA, hsail, hpos] at h0
    · unfold stepTruckCrossBA at hcr ⊢; split at hcr <;> simp_all
  refine ⟨?_, ?_, ?_, ?_⟩
  · by_cases hh : hitAB = 0
    · have hz : (fun t => if inC (sa.truckPhysLoc t) then stepTruckCrossAB inC inA sa sb t else 0) = (fun _ => 0) := by
        funext t; simp [hab_cross_zero hh t]
      rw [hz, finSum_zero]; exact Nat.zero_le _
    · have hh1 : hitAB = 1 := by unfold hitAB at hh ⊢; split at hh <;> simp_all
      rw [hh1, Nat.mul_one]
      apply Nat.le_trans _ (hv.aboard_le_cap cf.fi)
      unfold State.ferryCount
      apply finSum_le_finSum; intro t
      by_cases htc : inC (sa.truckPhysLoc t) = true
      · simp only [htc, ↓reduceIte]
        by_cases hcr : stepTruckCrossAB inC inA sa sb t = 1
        · have ⟨hab_t, _⟩ := (hno_cross t htc).1 hcr
          simp [hcr, hab_t]
        · have h0 : stepTruckCrossAB inC inA sa sb t = 0 := by
            unfold stepTruckCrossAB at hcr ⊢; split at hcr <;> simp_all
          simp [h0]
      · simp [htc]
  · by_cases hh : hitBA = 0
    · have hz : (fun t => if inC (sa.truckPhysLoc t) then stepTruckCrossBA inC inA sa sb t else 0) = (fun _ => 0) := by
        funext t; simp [hba_cross_zero hh t]
      rw [hz, finSum_zero]; exact Nat.zero_le _
    · have hh1 : hitBA = 1 := by unfold hitBA at hh ⊢; split at hh <;> simp_all
      rw [hh1, Nat.mul_one]
      apply Nat.le_trans _ (hv.aboard_le_cap cf.fi)
      unfold State.ferryCount
      apply finSum_le_finSum; intro t
      by_cases htc : inC (sa.truckPhysLoc t) = true
      · simp only [htc, ↓reduceIte]
        by_cases hcr : stepTruckCrossBA inC inA sa sb t = 1
        · have ⟨hab_t, _⟩ := (hno_cross t htc).2 hcr
          simp [hcr, hab_t]
        · have h0 : stepTruckCrossBA inC inA sa sb t = 0 := by
            unfold stepTruckCrossBA at hcr ⊢; split at hcr <;> simp_all
          simp [h0]
      · simp [htc]
  · by_cases hh : hitAB = 0
    · have hz : (fun p => if !s0.pkgDelivered p then
          match sa.pkgLoc p with
          | .atLoc _ => 0
          | .inTruck t => if stepTruckCrossAB inC inA sa sb t = 1 then I.pkgWeight p else 0
        else 0) = (fun _ => 0) := by
        funext p; cases s0.pkgDelivered p <;> cases sa.pkgLoc p <;> simp [hab_cross_zero hh]
      rw [hz, finSum_zero]; exact Nat.zero_le _
    · have hh1 : hitAB = 1 := by unfold hitAB at hh ⊢; split at hh <;> simp_all
      rw [hh1, Nat.mul_one]
      -- Every package counted is in some truck `t` with `sa.truckLoc t = .onFerry cf.fi`!
      have hle_ferry : finSum (fun p => if !s0.pkgDelivered p then
            match sa.pkgLoc p with
            | .atLoc _ => 0
            | .inTruck t => if stepTruckCrossAB inC inA sa sb t = 1 then I.pkgWeight p else 0
          else 0) ≤
          finSum (fun t => if decide (sa.truckLoc t = .onFerry cf.fi) = true then dynEffCap I s0 t else 0) := by
        have hrew : finSum (fun p => if !s0.pkgDelivered p then
              match sa.pkgLoc p with
              | .atLoc _ => 0
              | .inTruck t => if stepTruckCrossAB inC inA sa sb t = 1 then I.pkgWeight p else 0
            else 0) ≤
            finSum (fun t => finSum (fun p => if sa.truckLoc t = .onFerry cf.fi then
              if !s0.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0)) := by
          rw [finSum_comm]
          apply finSum_le_finSum; intro p
          cases hdel : s0.pkgDelivered p with
          | true => simp
          | false =>
            simp only [Bool.not_false, ↓reduceIte]
            cases hpl : sa.pkgLoc p with
            | atLoc _ => simp
            | inTruck t =>
              by_cases hcr : stepTruckCrossAB inC inA sa sb t = 1
              · have htc : inC (sa.truckPhysLoc t) = true := by
                  unfold stepTruckCrossAB at hcr; split at hcr
                  · rename_i hc; simp only [Bool.and_eq_true] at hc; exact hc.1.1
                  · cases hcr
                have ⟨hab_t, _⟩ := (hno_cross t htc).1 hcr
                simp only [hcr, ↓reduceIte]
                have hle := le_finSum (fun t' => if sa.truckLoc t' = .onFerry cf.fi then
                  if (!false && decide (PkgPos.inTruck t = PkgPos.inTruck t')) = true then I.pkgWeight p else 0 else 0) t
                simpa [hab_t] using hle
              · simp [hcr]
        apply Nat.le_trans hrew
        apply finSum_le_finSum; intro t
        by_cases h : sa.truckLoc t = .onFerry cf.fi
        · simp only [h, decide_true, ↓reduceIte]; exact hdyn t
        · have hz : (fun p => if sa.truckLoc t = .onFerry cf.fi then
              if !s0.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0) = (fun _ => 0) := by
            funext p; simp [h]
          rw [hz, finSum_zero]; exact Nat.zero_le _
      exact Nat.le_trans hle_ferry (ferryAboard_dynEffCap_le_maxFerryWeight I s0 sa cf.fi hv)
  · by_cases hh : hitBA = 0
    · have hz : (fun p => if !s0.pkgDelivered p then
          match sa.pkgLoc p with
          | .atLoc _ => 0
          | .inTruck t => if stepTruckCrossBA inC inA sa sb t = 1 then I.pkgWeight p else 0
        else 0) = (fun _ => 0) := by
        funext p; cases s0.pkgDelivered p <;> cases sa.pkgLoc p <;> simp [hba_cross_zero hh]
      rw [hz, finSum_zero]; exact Nat.zero_le _
    · have hh1 : hitBA = 1 := by unfold hitBA at hh ⊢; split at hh <;> simp_all
      rw [hh1, Nat.mul_one]
      have hle_ferry : finSum (fun p => if !s0.pkgDelivered p then
            match sa.pkgLoc p with
            | .atLoc _ => 0
            | .inTruck t => if stepTruckCrossBA inC inA sa sb t = 1 then I.pkgWeight p else 0
          else 0) ≤
          finSum (fun t => if decide (sa.truckLoc t = .onFerry cf.fi) = true then dynEffCap I s0 t else 0) := by
        have hrew : finSum (fun p => if !s0.pkgDelivered p then
              match sa.pkgLoc p with
              | .atLoc _ => 0
              | .inTruck t => if stepTruckCrossBA inC inA sa sb t = 1 then I.pkgWeight p else 0
            else 0) ≤
            finSum (fun t => finSum (fun p => if sa.truckLoc t = .onFerry cf.fi then
              if !s0.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0)) := by
          rw [finSum_comm]
          apply finSum_le_finSum; intro p
          cases hdel : s0.pkgDelivered p with
          | true => simp
          | false =>
            simp only [Bool.not_false, ↓reduceIte]
            cases hpl : sa.pkgLoc p with
            | atLoc _ => simp
            | inTruck t =>
              by_cases hcr : stepTruckCrossBA inC inA sa sb t = 1
              · have htc : inC (sa.truckPhysLoc t) = true := by
                  unfold stepTruckCrossBA at hcr; split at hcr
                  · rename_i hc; simp only [Bool.and_eq_true] at hc; exact hc.1.1
                  · cases hcr
                have ⟨hab_t, _⟩ := (hno_cross t htc).2 hcr
                simp only [hcr, ↓reduceIte]
                have hle := le_finSum (fun t' => if sa.truckLoc t' = .onFerry cf.fi then
                  if (!false && decide (PkgPos.inTruck t = PkgPos.inTruck t')) = true then I.pkgWeight p else 0 else 0) t
                simpa [hab_t] using hle
              · simp [hcr]
        apply Nat.le_trans hrew
        apply finSum_le_finSum; intro t
        by_cases h : sa.truckLoc t = .onFerry cf.fi
        · simp only [h, decide_true, ↓reduceIte]; exact hdyn t
        · have hz : (fun p => if sa.truckLoc t = .onFerry cf.fi then
              if !s0.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0) = (fun _ => 0) := by
            funext p; simp [h]
          rw [hz, finSum_zero]; exact Nat.zero_le _
      exact Nat.le_trans hle_ferry (ferryAboard_dynEffCap_le_maxFerryWeight I s0 sa cf.fi hv)

/-- Plan-level cut-ferry crossing bounds: total crossings and carried undelivered weight
    are bounded by `ferryCap * loadedCutSail` and `maxFerryWeight * loadedCutSail`. -/
theorem cutFerry_plan_bounds {I : Instance} (G : IslandGraph I) (cf : CutFerry I G)
    (inH : Fin G.numIslands → Bool) (hside : inH ∈ cf.sides)
    {s0 sa s_end : State I} {π : Plan I}
    (hv : ValidState I sa) (hp : ValidPlan I sa π s_end)
    (hgcd : ∀ p, s0.pkgDelivered p = false → undelivGcd I s0 ∣ I.pkgWeight p) :
    let inC := fun l => cf.inComp (G.islandOf l)
    let inA := fun l => inH (G.islandOf l)
    finSum (fun t => if inC (sa.truckPhysLoc t) then planTruckCrossAB inC inA sa π t else 0) ≤
      I.ferryCap cf.fi * loadedCutSailAB G cf.fi inH sa π ∧
    finSum (fun t => if inC (sa.truckPhysLoc t) then planTruckCrossBA inC inA sa π t else 0) ≤
      I.ferryCap cf.fi * loadedCutSailBA G cf.fi inH sa π ∧
    finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inC inA sa π p else 0) ≤
      maxFerryWeight I s0 cf.fi * loadedCutSailAB G cf.fi inH sa π ∧
    finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inC inA sa π p else 0) ≤
      maxFerryWeight I s0 cf.fi * loadedCutSailBA G cf.fi inH sa π := by
  intro inC inA
  induction hp with
  | nil =>
    simp [planTruckCrossAB, planTruckCrossBA, planPkgCrossAB, planPkgCrossBA,
          loadedCutSailAB, loadedCutSailBA, finSum_zero]
  | @cons s1 s2 _ a rest hstep _ ih =>
    have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
    have hin_eq : ∀ t, inC (s2.truckPhysLoc t) = inC (s1.truckPhysLoc t) := cf.hcl hstep
    have ⟨ih1, ih2, ih3, ih4⟩ := ih (validState_step hv hstep)
    have hdyn : ∀ t, finSum (fun p => if !s0.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t) then I.pkgWeight p else 0) ≤ dynEffCap I s0 t := by
      intro t
      have hle_cap : subsetWeight I.pkgWeight (fun p => !s0.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t)) ≤ I.truckCap t := by
        apply Nat.le_trans _ (hv.load_le_cap t)
        unfold subsetWeight State.truckLoad
        apply finSum_le_finSum; intro p
        cases hdel : s0.pkgDelivered p <;> by_cases h : s1.pkgLoc p = .inTruck t <;> simp [hdel, h]
      exact subsetWeight_undeliv_le_dynEffCap I s0 t (fun p => !s0.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t))
        (fun p hp => by simp only [Bool.and_eq_true, Bool.not_eq_true'] at hp; exact hp.1)
        hle_cap
    have ⟨hs1, hs2, hs3, hs4⟩ := cutFerry_step_bounds G cf inH hside hv hstep hdyn
    have hsp1 : finSum (fun t => if inC (s1.truckPhysLoc t) then planTruckCrossAB inC inA s1 (a :: rest) t else 0) =
        finSum (fun t => if inC (s1.truckPhysLoc t) then stepTruckCrossAB inC inA s1 s2 t else 0) +
        finSum (fun t => if inC (s2.truckPhysLoc t) then planTruckCrossAB inC inA s2 rest t else 0) := by
      rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossAB, ← hs2_eq, hin_eq t]; split <;> simp
    have hsp2 : finSum (fun t => if inC (s1.truckPhysLoc t) then planTruckCrossBA inC inA s1 (a :: rest) t else 0) =
        finSum (fun t => if inC (s1.truckPhysLoc t) then stepTruckCrossBA inC inA s1 s2 t else 0) +
        finSum (fun t => if inC (s2.truckPhysLoc t) then planTruckCrossBA inC inA s2 rest t else 0) := by
      rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossBA, ← hs2_eq, hin_eq t]; split <;> simp
    have hsp3 : finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inC inA s1 (a :: rest) p else 0) =
        finSum (fun p => if !s0.pkgDelivered p then
          match s1.pkgLoc p with
          | .atLoc _ => 0
          | .inTruck t => if stepTruckCrossAB inC inA s1 s2 t = 1 then I.pkgWeight p else 0 else 0) +
        finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossAB inC inA s2 rest p else 0) := by
      rw [← finSum_add]; congr 1; funext p
      cases s0.pkgDelivered p with
      | true => simp
      | false =>
        simp only [Bool.not_false, ↓reduceIte, planPkgCrossAB, ← hs2_eq]
        cases s1.pkgLoc p with
        | atLoc _ => simp
        | inTruck t =>
          unfold stepTruckCrossAB
          by_cases hcr : (inC (s1.truckPhysLoc t) && inA (s1.truckPhysLoc t) && !inA (s2.truckPhysLoc t)) = true
          · simp [hcr, Nat.mul_add]
          · have hf : (inC (s1.truckPhysLoc t) && inA (s1.truckPhysLoc t) && !inA (s2.truckPhysLoc t)) = false :=
              Bool.eq_false_iff.mpr hcr
            simp [hf]
    have hsp4 : finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inC inA s1 (a :: rest) p else 0) =
        finSum (fun p => if !s0.pkgDelivered p then
          match s1.pkgLoc p with
          | .atLoc _ => 0
          | .inTruck t => if stepTruckCrossBA inC inA s1 s2 t = 1 then I.pkgWeight p else 0 else 0) +
        finSum (fun p => if !s0.pkgDelivered p then I.pkgWeight p * planPkgCrossBA inC inA s2 rest p else 0) := by
      rw [← finSum_add]; congr 1; funext p
      cases s0.pkgDelivered p with
      | true => simp
      | false =>
        simp only [Bool.not_false, ↓reduceIte, planPkgCrossBA, ← hs2_eq]
        cases s1.pkgLoc p with
        | atLoc _ => simp
        | inTruck t =>
          unfold stepTruckCrossBA
          by_cases hcr : (inC (s1.truckPhysLoc t) && !inA (s1.truckPhysLoc t) && inA (s2.truckPhysLoc t)) = true
          · simp [hcr, Nat.mul_add]
          · have hf : (inC (s1.truckPhysLoc t) && !inA (s1.truckPhysLoc t) && inA (s2.truckPhysLoc t)) = false :=
              Bool.eq_false_iff.mpr hcr
            simp [hf]
    simp only [loadedCutSailAB, loadedCutSailBA, ← hs2_eq, Nat.mul_add]
    rw [hsp1, hsp2, hsp3, hsp4]
    exact ⟨Nat.add_le_add hs1 ih1, Nat.add_le_add hs2 ih2, Nat.add_le_add hs3 ih3, Nat.add_le_add hs4 ih4⟩

/-- Ferry parity alternation: for any ferry `f` and Boolean side `inH` on islands,
    the directed sail counts `sailAB = countActions (isCutSailAB G f inH) π` and
    `sailBA = countActions (isCutSailBA G f inH) π` alternate according to `inH (G.islandOf (s.ferryLoc f))`. -/
theorem ferry_sail_alternation {I : Instance} (G : IslandGraph I) (f : Fin I.numFerries)
    (inH : Fin G.numIslands → Bool)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end) :
    let sailAB := countActions (isCutSailAB G f inH) π
    let sailBA := countActions (isCutSailBA G f inH) π
    (inH (G.islandOf (s.ferryLoc f)) = true → sailBA ≤ sailAB ∧ sailAB ≤ sailBA + 1) ∧
    (inH (G.islandOf (s.ferryLoc f)) = false → sailAB ≤ sailBA ∧ sailBA ≤ sailAB + 1) := by
  induction hp with
  | nil => simp [countActions]
  | @cons sa sb _ a rest hstep _ ih =>
    have ⟨ihT, ihF⟩ := ih
    simp only [countActions, List.map_cons, List.sum_cons] at ihT ihF ⊢
    cases hstep with
    | @sail f' u v hf _ _ =>
      by_cases hff : f' = f
      · subst hff
        have hloc_b : ({ sa with ferryLoc := updateFn sa.ferryLoc f' v } : State I).ferryLoc f' = v := by
          simp [updateFn]
        rw [hloc_b] at ihT ihF
        rw [hf]
        cases hu : inH (G.islandOf u) <;> cases hv' : inH (G.islandOf v) <;>
          simp [isCutSailAB, isCutSailBA, hu, hv'] at ihT ihF ⊢ <;> omega
      · have hloc_b : ({ sa with ferryLoc := updateFn sa.ferryLoc f' v } : State I).ferryLoc f = sa.ferryLoc f := by
          simp [updateFn, Ne.symm hff]
        rw [hloc_b] at ihT ihF
        simp [isCutSailAB, isCutSailBA, hff]; exact ⟨ihT, ihF⟩
    | drive _ _ _ => simp [isCutSailAB, isCutSailBA]; exact ⟨ihT, ihF⟩
    | load _ _ _ => simp [isCutSailAB, isCutSailBA]; exact ⟨ihT, ihF⟩
    | unload _ _ => simp [isCutSailAB, isCutSailBA]; exact ⟨ihT, ihF⟩
    | board _ _ => simp [isCutSailAB, isCutSailBA]; exact ⟨ihT, ihF⟩
    | disembark _ => simp [isCutSailAB, isCutSailBA]; exact ⟨ihT, ihF⟩

/-- Empty-fetch sail lemma (`ex1.py:L986, L989`):
    If ferry `fi` starts in side `inH = true` (`fi_in = true`) AND 0 trucks start on side `inH = true`
    inside `inComp` (`mh = 0`), AND `1 ≤ loadedCutSailAB`, then the VERY FIRST `isCutSailAB` sail of `fi`
    is EMPTY (carries 0 trucks), so `loadedCutSailAB + 1 ≤ countActions (isCutSailAB G cf.fi inH) π`! -/
theorem cutFerry_empty_fetch_AB {I : Instance} (G : IslandGraph I) (cf : CutFerry I G)
    (inH : Fin G.numIslands → Bool) (hside : inH ∈ cf.sides)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (hfi_in : inH (G.islandOf (s.ferryLoc cf.fi)) = true)
    (hmh0 : ∀ t, cf.inComp (G.islandOf (s.truckPhysLoc t)) = true → inH (G.islandOf (s.truckPhysLoc t)) = false)
    (hpos : 1 ≤ loadedCutSailAB G cf.fi inH s π) :
    loadedCutSailAB G cf.fi inH s π + 1 ≤ countActions (isCutSailAB G cf.fi inH) π := by
  have hle_gen : ∀ {sx sy : State I} {ps : Plan I}, ValidPlan I sx ps sy →
      loadedCutSailAB G cf.fi inH sx ps ≤ countActions (isCutSailAB G cf.fi inH) ps := by
    intro sx sy ps hp'
    induction hp' with
    | nil => simp [loadedCutSailAB, countActions]
    | @cons s1 s2 _ a r hst _ iha =>
      simp only [loadedCutSailAB, countActions, List.map_cons, List.sum_cons, ← step_eq_applyAction hst] at iha ⊢
      by_cases h1 : isCutSailAB G cf.fi inH a = true <;> by_cases h2 : 0 < s1.ferryCount cf.fi <;> simp [h1, h2] <;> omega
  induction hp with
  | nil => simp [loadedCutSailAB] at hpos
  | @cons sa sb _ a rest hstep hrest ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    -- No truck is aboard `cf.fi` in `sa` (since `cf.fi` is in `inH = true`, which is in `inComp`, and `hmh0` says 0 trucks are in `inH = true`)!
    have hfc0 : sa.ferryCount cf.fi = 0 := by
      unfold State.ferryCount
      have hz : (fun t => if sa.truckLoc t = .onFerry cf.fi then 1 else 0) = (fun _ => 0) := by
        funext t; by_cases h : sa.truckLoc t = .onFerry cf.fi
        · exfalso
          have hphys : sa.truckPhysLoc t = sa.ferryLoc cf.fi := by simp [State.truckPhysLoc, h]
          have hinc : cf.inComp (G.islandOf (sa.truckPhysLoc t)) = true :=
            cf.sides_sub inH hside _ (hphys ▸ hfi_in)
          have hf := hmh0 t hinc
          rw [hphys, hfi_in] at hf; cases hf
        · simp [h]
      rw [hz, finSum_zero]
    simp only [loadedCutSailAB, countActions, List.map_cons, List.sum_cons, ← hsb_eq, hfc0,
               Nat.lt_irrefl, decide_false, Bool.and_false, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at hpos ⊢
    by_cases hsail : isCutSailAB G cf.fi inH a = true
    · -- THIS step `a` IS an empty `AB` sail! Combine with `loadedCutSailAB rest ≤ countActions rest`!
      simp only [hsail, ↓reduceIte]
      have := hle_gen hrest
      unfold countActions at this; omega
    · have hsf : isCutSailAB G cf.fi inH a = false := Bool.eq_false_iff.mpr hsail
      simp only [hsf, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      -- Step `a` is NOT an `AB` sail of `cf.fi`, so `cf.fi` stays in `inH = true` AND `hmh0` still holds in `sb`!
      have hfi_b : inH (G.islandOf (sb.ferryLoc cf.fi)) = true := by
        cases hstep with
        | @sail f u v hf _ _ =>
          by_cases hff : f = cf.fi
          · subst hff
            simp only [updateFn, ↓reduceIte]
            cases hv' : inH (G.islandOf v) with
            | true => rfl
            | false =>
              exfalso
              have hu : inH (G.islandOf u) = true := hf ▸ hfi_in
              simp [isCutSailAB, hu, hv'] at hsf
          · simp [updateFn, Ne.symm hff, hfi_in]
        | drive _ _ _ => exact hfi_in
        | load _ _ _ => exact hfi_in
        | unload _ _ => exact hfi_in
        | board _ _ => exact hfi_in
        | disembark _ => exact hfi_in
      have hmh0_b : ∀ t, cf.inComp (G.islandOf (sb.truckPhysLoc t)) = true → inH (G.islandOf (sb.truckPhysLoc t)) = false := by
        intro t htc_b
        have hcl_t := cf.hcl hstep t
        have htc_a : cf.inComp (G.islandOf (sa.truckPhysLoc t)) = true := hcl_t.symm.trans htc_b
        have ha_f := hmh0 t htc_a
        have hdyn : ∀ t', finSum (fun p => if !sa.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t') then I.pkgWeight p else 0) ≤ dynEffCap I sa t' := by
          intro t'
          have hle_cap : subsetWeight I.pkgWeight (fun p => !sa.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t')) ≤ I.truckCap t' := by
            apply Nat.le_trans _ (hv.load_le_cap t'); unfold subsetWeight State.truckLoad; apply finSum_le_finSum
            intro p; cases hdel : sa.pkgDelivered p <;> by_cases h : sa.pkgLoc p = .inTruck t' <;> simp [hdel, h]
          exact subsetWeight_undeliv_le_dynEffCap I sa t' _ (fun p hp => by simp only [Bool.and_eq_true, Bool.not_eq_true'] at hp; exact hp.1) hle_cap
        have hba := (cutFerry_step_bounds G cf inH hside hv hstep hdyn).2.1
        simp only [hfc0, Nat.lt_irrefl, decide_false, Bool.and_false, Bool.false_eq_true, ↓reduceIte, Nat.mul_zero] at hba
        have hle := le_finSum (fun t' => if cf.inComp (G.islandOf (sa.truckPhysLoc t')) then
          stepTruckCrossBA (fun l => cf.inComp (G.islandOf l)) (fun l => inH (G.islandOf l)) sa sb t' else 0) t
        have hba_le : stepTruckCrossBA (fun l => cf.inComp (G.islandOf l)) (fun l => inH (G.islandOf l)) sa sb t ≤ 0 := by
          simp only [htc_a, ↓reduceIte] at hle; exact Nat.le_trans hle hba
        cases hsb_in : inH (G.islandOf (sb.truckPhysLoc t)) with
        | false => rfl
        | true => simp [stepTruckCrossBA, htc_a, ha_f, hsb_in] at hba_le
      have hrec := ih (validState_step hv hstep) hfi_b hmh0_b hpos
      unfold countActions at hrec; exact hrec

/-- Symmetric empty-fetch sail lemma when `cf.fi` starts in `inH = false` and `mo = 0`. -/
theorem cutFerry_empty_fetch_BA {I : Instance} (G : IslandGraph I) (cf : CutFerry I G)
    (inH : Fin G.numIslands → Bool) (hside : inH ∈ cf.sides)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (hfi_out : inH (G.islandOf (s.ferryLoc cf.fi)) = false)
    (hfi_inComp : cf.inComp (G.islandOf (s.ferryLoc cf.fi)) = true)
    (hmo0 : ∀ t, cf.inComp (G.islandOf (s.truckPhysLoc t)) = true → inH (G.islandOf (s.truckPhysLoc t)) = true)
    (hpos : 1 ≤ loadedCutSailBA G cf.fi inH s π) :
    loadedCutSailBA G cf.fi inH s π + 1 ≤ countActions (isCutSailBA G cf.fi inH) π := by
  have hle_gen : ∀ {sx sy : State I} {ps : Plan I}, ValidPlan I sx ps sy →
      loadedCutSailBA G cf.fi inH sx ps ≤ countActions (isCutSailBA G cf.fi inH) ps := by
    intro sx sy ps hp'
    induction hp' with
    | nil => simp [loadedCutSailBA, countActions]
    | @cons s1 s2 _ a r hst _ iha =>
      simp only [loadedCutSailBA, countActions, List.map_cons, List.sum_cons, ← step_eq_applyAction hst] at iha ⊢
      by_cases h1 : isCutSailBA G cf.fi inH a = true <;> by_cases h2 : 0 < s1.ferryCount cf.fi <;> simp [h1, h2] <;> omega
  induction hp with
  | nil => simp [loadedCutSailBA] at hpos
  | @cons sa sb _ a rest hstep hrest ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hfc0 : sa.ferryCount cf.fi = 0 := by
      unfold State.ferryCount
      have hz : (fun t => if sa.truckLoc t = .onFerry cf.fi then 1 else 0) = (fun _ => 0) := by
        funext t; by_cases h : sa.truckLoc t = .onFerry cf.fi
        · exfalso
          have hphys : sa.truckPhysLoc t = sa.ferryLoc cf.fi := by simp [State.truckPhysLoc, h]
          have hinc : cf.inComp (G.islandOf (sa.truckPhysLoc t)) = true := hphys ▸ hfi_inComp
          have ht := hmo0 t hinc
          rw [hphys, hfi_out] at ht; cases ht
        · simp [h]
      rw [hz, finSum_zero]
    simp only [loadedCutSailBA, countActions, List.map_cons, List.sum_cons, ← hsb_eq, hfc0,
               Nat.lt_irrefl, decide_false, Bool.and_false, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at hpos ⊢
    by_cases hsail : isCutSailBA G cf.fi inH a = true
    · simp only [hsail, ↓reduceIte]
      have := hle_gen hrest
      unfold countActions at this; omega
    · have hsf : isCutSailBA G cf.fi inH a = false := Bool.eq_false_iff.mpr hsail
      simp only [hsf, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      have hfi_b : inH (G.islandOf (sb.ferryLoc cf.fi)) = false := by
        cases hstep with
        | @sail f u v hf _ _ =>
          by_cases hff : f = cf.fi
          · subst hff
            simp only [updateFn, ↓reduceIte]
            cases hv' : inH (G.islandOf v) with
            | false => rfl
            | true =>
              exfalso
              have hu : inH (G.islandOf u) = false := hf ▸ hfi_out
              simp [isCutSailBA, hu, hv'] at hsf
          · simp [updateFn, Ne.symm hff, hfi_out]
        | drive _ _ _ => exact hfi_out
        | load _ _ _ => exact hfi_out
        | unload _ _ => exact hfi_out
        | board _ _ => exact hfi_out
        | disembark _ => exact hfi_out
      have hfi_inc_b : cf.inComp (G.islandOf (sb.ferryLoc cf.fi)) = true := by
        cases hstep with
        | @sail f u v hf _ hsv =>
          by_cases hff : f = cf.fi
          · subst hff; simp only [updateFn, ↓reduceIte]; exact cf.fi_inComp v hsv
          · simp [updateFn, Ne.symm hff, hfi_inComp]
        | drive _ _ _ => exact hfi_inComp
        | load _ _ _ => exact hfi_inComp
        | unload _ _ => exact hfi_inComp
        | board _ _ => exact hfi_inComp
        | disembark _ => exact hfi_inComp
      have hmo0_b : ∀ t, cf.inComp (G.islandOf (sb.truckPhysLoc t)) = true → inH (G.islandOf (sb.truckPhysLoc t)) = true := by
        intro t htc_b
        have hcl_t := cf.hcl hstep t
        have htc_a : cf.inComp (G.islandOf (sa.truckPhysLoc t)) = true := hcl_t.symm.trans htc_b
        have ha_t := hmo0 t htc_a
        have hdyn : ∀ t', finSum (fun p => if !sa.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t') then I.pkgWeight p else 0) ≤ dynEffCap I sa t' := by
          intro t'
          have hle_cap : subsetWeight I.pkgWeight (fun p => !sa.pkgDelivered p && decide (sa.pkgLoc p = .inTruck t')) ≤ I.truckCap t' := by
            apply Nat.le_trans _ (hv.load_le_cap t'); unfold subsetWeight State.truckLoad; apply finSum_le_finSum
            intro p; cases hdel : sa.pkgDelivered p <;> by_cases h : sa.pkgLoc p = .inTruck t' <;> simp [hdel, h]
          exact subsetWeight_undeliv_le_dynEffCap I sa t' _ (fun p hp => by simp only [Bool.and_eq_true, Bool.not_eq_true'] at hp; exact hp.1) hle_cap
        have hab := (cutFerry_step_bounds G cf inH hside hv hstep hdyn).1
        simp only [hfc0, Nat.lt_irrefl, decide_false, Bool.and_false, Bool.false_eq_true, ↓reduceIte, Nat.mul_zero] at hab
        have hle := le_finSum (fun t' => if cf.inComp (G.islandOf (sa.truckPhysLoc t')) then
          stepTruckCrossAB (fun l => cf.inComp (G.islandOf l)) (fun l => inH (G.islandOf l)) sa sb t' else 0) t
        have hab_le : stepTruckCrossAB (fun l => cf.inComp (G.islandOf l)) (fun l => inH (G.islandOf l)) sa sb t ≤ 0 := by
          simp only [htc_a, ↓reduceIte] at hle; exact Nat.le_trans hle hab
        cases hsb_in : inH (G.islandOf (sb.truckPhysLoc t)) with
        | true => rfl
        | false => simp [stepTruckCrossAB, htc_a, ha_t, hsb_in] at hab_le
      have hrec := ih (validState_step hv hstep) hfi_b hfi_inc_b hmo0_b hpos
      unfold countActions at hrec; exact hrec

/-- Exact parity + empty-fetch formula `sf` (`ex1.py:L984-L992`) lower-bounds `ferrySailCount cf.fi π`! -/
theorem cutFerry_parity_msf_sound {I : Instance} (G : IslandGraph I) (cf : CutFerry I G)
    (inH : Fin G.numIslands → Bool)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end)
    (soh sih se : Nat)
    (h_ab : (inH (G.islandOf (s.ferryLoc cf.fi)) = true → se ≤ countActions (isCutSailAB G cf.fi inH) π) ∧
            (inH (G.islandOf (s.ferryLoc cf.fi)) = false → soh ≤ countActions (isCutSailAB G cf.fi inH) π))
    (h_ba : (inH (G.islandOf (s.ferryLoc cf.fi)) = true → sih ≤ countActions (isCutSailBA G cf.fi inH) π) ∧
            (inH (G.islandOf (s.ferryLoc cf.fi)) = false → se ≤ countActions (isCutSailBA G cf.fi inH) π)) :
    (if inH (G.islandOf (s.ferryLoc cf.fi)) then
      max se sih + max sih (se - 1)
     else
      max soh (se - 1) + max se soh) ≤ ferrySailCount cf.fi π := by
  have ⟨haltT, haltF⟩ := ferry_sail_alternation G cf.fi inH hp
  have hdisj : countActions (isCutSailAB G cf.fi inH) π + countActions (isCutSailBA G cf.fi inH) π ≤
               ferrySailCount cf.fi π := by
    unfold ferrySailCount countActions
    clear haltT haltF h_ab h_ba hp
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      have ha : (if isCutSailAB G cf.fi inH a = true then 1 else 0) +
                (if isCutSailBA G cf.fi inH a = true then 1 else 0) ≤
                (if isFerrySail cf.fi a = true then 1 else 0) := by
        cases a with
        | sail f u v =>
          by_cases hff : f = cf.fi
          · subst hff
            by_cases hu : inH (G.islandOf u) = true <;> by_cases hv' : inH (G.islandOf v) = true
            · simp [isCutSailAB, isCutSailBA, isFerrySail, hu, hv']
            · have hvf : inH (G.islandOf v) = false := Bool.eq_false_iff.mpr hv'
              simp [isCutSailAB, isCutSailBA, isFerrySail, hu, hvf]
            · have huf : inH (G.islandOf u) = false := Bool.eq_false_iff.mpr hu
              simp [isCutSailAB, isCutSailBA, isFerrySail, huf, hv']
            · have huf : inH (G.islandOf u) = false := Bool.eq_false_iff.mpr hu
              have hvf : inH (G.islandOf v) = false := Bool.eq_false_iff.mpr hv'
              simp [isCutSailAB, isCutSailBA, isFerrySail, huf, hvf]
          · simp [isCutSailAB, isCutSailBA, isFerrySail, hff]
        | _ => simp [isCutSailAB, isCutSailBA, isFerrySail]
      omega
  cases hfi : inH (G.islandOf (s.ferryLoc cf.fi)) with
  | true =>
    simp only [↓reduceIte]
    have ⟨h1, h2⟩ := haltT hfi
    have hab := h_ab.1 hfi
    have hba := h_ba.1 hfi
    omega
  | false =>
    simp only [Bool.false_eq_true, ↓reduceIte]
    have ⟨h1, h2⟩ := haltF hfi
    have hab := h_ab.2 hfi
    have hba := h_ba.2 hfi
    omega

/-- Multi-way cut sail sums `sof = ∑ soh` and `sif = ∑ sih` (`ex1.py:L979-L983, L1027`):
    Because `cf.sides` are pairwise disjoint, outgoing sails `isCutSailAB G cf.fi inH` are pairwise
    disjoint across `inH ∈ cf.sides`, and incoming sails `isCutSailBA G cf.fi inH` are pairwise disjoint! -/
theorem cutFerry_multiway_sail_sum {I : Instance} (G : IslandGraph I) (cf : CutFerry I G) (π : Plan I) :
    (cf.sides.map (fun inH => countActions (isCutSailAB G cf.fi inH) π)).sum ≤ ferrySailCount cf.fi π ∧
    (cf.sides.map (fun inH => countActions (isCutSailBA G cf.fi inH) π)).sum ≤ ferrySailCount cf.fi π := by
  constructor
  · have hdisj : (cf.sides.map (isCutSailAB G cf.fi)).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
      rw [List.pairwise_map]
      refine cf.sides_disj.imp ?_
      intro h₁ h₂ hd a h1
      cases a with
      | sail f u v =>
        simp only [isCutSailAB, Bool.and_eq_true, decide_eq_true_eq] at h1
        simp only [isCutSailAB, hd (G.islandOf u) h1.1.2, Bool.and_false, Bool.false_and]
      | _ => simp [isCutSailAB] at h1
    have hsum := sum_countActions_disjoint (cf.sides.map (isCutSailAB G cf.fi)) π hdisj
    have hmap : ((cf.sides.map (isCutSailAB G cf.fi)).map (fun p => countActions p π)).sum =
                (cf.sides.map (fun inH => countActions (isCutSailAB G cf.fi inH) π)).sum := by
      rw [List.map_map]; rfl
    rw [hmap] at hsum
    apply Nat.le_trans hsum
    unfold ferrySailCount countActions
    clear hdisj hsum hmap
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      dsimp only at ih ⊢
      have ha : (if ((cf.sides.map (isCutSailAB G cf.fi)).any fun p => p a) = true then 1 else 0) ≤
                (if isFerrySail cf.fi a = true then 1 else 0) := by
        by_cases hany : ((cf.sides.map (isCutSailAB G cf.fi)).any fun p => p a) = true
        · rw [List.any_eq_true] at hany
          rcases hany with ⟨p, hp, hpa⟩
          rw [List.mem_map] at hp; rcases hp with ⟨inH, _, rfl⟩
          cases a with
          | sail f u v =>
            simp only [isCutSailAB, Bool.and_eq_true, decide_eq_true_eq] at hpa
            simp only [isFerrySail, hpa.1.1, decide_true, ↓reduceIte]; split <;> omega
          | _ => simp [isCutSailAB] at hpa
        · have hf : ((cf.sides.map (isCutSailAB G cf.fi)).any fun p => p a) = false := Bool.eq_false_iff.mpr hany
          simp [hf]
      omega
  · have hdisj : (cf.sides.map (isCutSailBA G cf.fi)).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
      rw [List.pairwise_map]
      refine cf.sides_disj.imp ?_
      intro h₁ h₂ hd a h1
      cases a with
      | sail f u v =>
        simp only [isCutSailBA, Bool.and_eq_true, decide_eq_true_eq] at h1
        simp only [isCutSailBA, hd (G.islandOf v) h1.2, Bool.and_false]
      | _ => simp [isCutSailBA] at h1
    have hsum := sum_countActions_disjoint (cf.sides.map (isCutSailBA G cf.fi)) π hdisj
    have hmap : ((cf.sides.map (isCutSailBA G cf.fi)).map (fun p => countActions p π)).sum =
                (cf.sides.map (fun inH => countActions (isCutSailBA G cf.fi inH) π)).sum := by
      rw [List.map_map]; rfl
    rw [hmap] at hsum
    apply Nat.le_trans hsum
    unfold ferrySailCount countActions
    clear hdisj hsum hmap
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      dsimp only at ih ⊢
      have ha : (if ((cf.sides.map (isCutSailBA G cf.fi)).any fun p => p a) = true then 1 else 0) ≤
                (if isFerrySail cf.fi a = true then 1 else 0) := by
        by_cases hany : ((cf.sides.map (isCutSailBA G cf.fi)).any fun p => p a) = true
        · rw [List.any_eq_true] at hany
          rcases hany with ⟨p, hp, hpa⟩
          rw [List.mem_map] at hp; rcases hp with ⟨inH, _, rfl⟩
          cases a with
          | sail f u v =>
            simp only [isCutSailBA, Bool.and_eq_true, decide_eq_true_eq] at hpa
            simp only [isFerrySail, hpa.1.1, decide_true, ↓reduceIte]; split <;> omega
          | _ => simp [isCutSailBA] at hpa
        · have hf : ((cf.sides.map (isCutSailBA G cf.fi)).any fun p => p a) = false := Bool.eq_false_iff.mpr hany
          simp [hf]
      omega

-- ==============================================================================
-- 3. EXACT ABOARD-TRUCK `(z, x)` SPLIT FOR `bd_cut` (`ex1.py:L994-L1025`)
-- ==============================================================================

/-- Insert `x` into a list sorted in ASCENDING order. -/
def insertAsc (x : Nat) : List Nat → List Nat
  | [] => [x]
  | y :: ys => if x ≤ y then x :: y :: ys else y :: insertAsc x ys

def sortAsc : List Nat → List Nat
  | [] => []
  | x :: xs => insertAsc x (sortAsc xs)

def sumTake (k : Nat) (l : List Nat) : Nat := (l.take k).sum

/-- Sortedness predicate for ascending lists. -/
def IsSortedAsc : List Nat → Prop
  | [] => True
  | [_] => True
  | x :: y :: rest => x ≤ y ∧ IsSortedAsc (y :: rest)

theorem head_le_all_of_sortedAsc (x : Nat) (xs : List Nat) (h : IsSortedAsc (x :: xs)) :
    ∀ y ∈ xs, x ≤ y := by
  induction xs generalizing x with
  | nil => intro _ hm; cases hm
  | cons y ys ih =>
    rcases h with ⟨hxy, hys⟩
    intro z hz
    rcases List.mem_cons.mp hz with rfl | hzs
    · exact hxy
    · exact Nat.le_trans hxy (ih y hys z hzs)

theorem insertAsc_sorted (x : Nat) (l : List Nat) (hl : IsSortedAsc l) :
    IsSortedAsc (insertAsc x l) := by
  induction l with
  | nil => trivial
  | cons y ys ih =>
    simp only [insertAsc]
    by_cases hxy : x ≤ y
    · simp only [hxy, ↓reduceIte]; exact ⟨hxy, hl⟩
    · simp only [hxy, ↓reduceIte]
      cases ys with
      | nil => simp [insertAsc, IsSortedAsc]; omega
      | cons z zs =>
        rcases hl with ⟨hyz, hzs⟩
        have hrec := ih hzs
        simp only [insertAsc] at hrec ⊢
        by_cases hxz : x ≤ z
        · simp only [hxz, ↓reduceIte] at hrec ⊢; exact ⟨by omega, hrec⟩
        · simp only [hxz, ↓reduceIte] at hrec ⊢; exact ⟨hyz, hrec⟩

theorem sortAsc_sorted (l : List Nat) : IsSortedAsc (sortAsc l) := by
  induction l with
  | nil => trivial
  | cons x xs ih => exact insertAsc_sorted x (sortAsc xs) ih

theorem sumTake_mono_len (l : List Nat) {a b : Nat} (h : a ≤ b) :
    sumTake a l ≤ sumTake b l := by
  induction l generalizing a b with
  | nil => simp [sumTake]
  | cons x xs ih =>
    cases a with
    | zero => simp [sumTake]
    | succ a' =>
      cases b with
      | zero => omega
      | succ b' =>
        simp only [sumTake, List.take_succ_cons, List.sum_cons]
        have hrec := ih (a := a') (b := b') (by omega)
        unfold sumTake at hrec; omega

theorem sumTake_insertAsc_sorted (x : Nat) (l : List Nat) (hl : IsSortedAsc l) (k : Nat) :
    (k ≤ l.length → sumTake k (insertAsc x l) ≤ sumTake k l) ∧
    (∀ k', k' + 1 = k → sumTake k (insertAsc x l) ≤ x + sumTake k' l) := by
  induction l generalizing k with
  | nil =>
    cases k with
    | zero => exact ⟨fun _ => Nat.le_refl _, fun _ h => by omega⟩
    | succ k' => exact ⟨fun h => by simp at h, fun k'' h => by simp [insertAsc, sumTake]⟩
  | cons y ys ih =>
    simp only [insertAsc]
    by_cases hxy : x ≤ y
    · simp only [hxy, ↓reduceIte]
      cases k with
      | zero => exact ⟨fun _ => Nat.le_refl _, fun _ h => by omega⟩
      | succ k' =>
        simp only [sumTake, List.take_succ_cons, List.sum_cons]
        constructor
        · intro hk
          have hshift : ∀ (a : Nat) (ls : List Nat) (m : Nat),
              IsSortedAsc (a :: ls) → m ≤ ls.length →
              ((a :: ls).take m).sum ≤ (ls.take m).sum := by
            intro a ls m
            induction ls generalizing a m with
            | nil => intro _ hm; have hm0 : m = 0 := Nat.le_zero.mp hm; subst hm0; exact Nat.le_refl 0
            | cons b bs ihl =>
              intro hs hm
              rcases hs with ⟨hab, hbs⟩
              cases m with
              | zero => simp
              | succ m' =>
                simp only [List.take_succ_cons, List.sum_cons]
                have := ihl b m' hbs (by simp at hm; omega)
                omega
          have hs := hshift y ys k' hl (by simp at hk; omega)
          omega
        · intro k'' hk; have heq : k'' = k' := by omega
          subst heq; omega
    · simp only [hxy, ↓reduceIte]
      cases k with
      | zero => exact ⟨fun _ => Nat.le_refl _, fun _ h => by omega⟩
      | succ k' =>
        simp only [sumTake, List.take_succ_cons, List.sum_cons]
        have hys : IsSortedAsc ys := by cases ys with | nil => trivial | cons _ _ => exact hl.2
        have ⟨h1, _⟩ := ih hys k'
        constructor
        · intro hk
          have hle := h1 (by simp at hk; omega)
          unfold sumTake at hle; omega
        · intro k'' hk; have heq : k'' = k' := by omega
          subst heq
          cases k'' with
          | zero => simp [sumTake]; omega
          | succ k''' =>
            have h2' := (ih hys (k''' + 1)).2 k''' rfl
            simp only [sumTake, List.take_succ_cons, List.sum_cons] at h2' ⊢
            omega

/-- For any subset `sub` (`Fin n → Bool`) of a base subset `base` (`Fin n → Bool`) with size `k`,
    the sum of `val` over `sub` is `≥ sumTake k (sortAsc (vals of base))`! -/
theorem sumTake_sortAsc_le_subset {n : Nat} (base sub : Fin n → Bool) (val : Fin n → Nat)
    (hsub : ∀ i, sub i = true → base i = true) :
    let vals := ((List.finRange n).filter (fun i => base i)).map val
    let k := finSum (fun i => if sub i then 1 else 0)
    sumTake k (sortAsc vals) ≤ finSum (fun i => if sub i then val i else 0) := by
  suffices ∀ (ls : List (Fin n)),
      sumTake ((ls.map (fun i => if sub i then 1 else 0)).sum)
        (sortAsc ((ls.filter (fun i => base i)).map val)) ≤
      (ls.map (fun i => if sub i then val i else 0)).sum by
    simpa [finSum_eq_list_sum] using this (List.finRange n)
  intro ls
  induction ls with
  | nil => simp [sortAsc, sumTake]
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons, List.filter_cons]
    cases hb : base a with
    | false =>
      have hs : sub a = false := by
        cases h : sub a with | false => rfl | true => have := hsub a h; rw [hb] at this; cases this
      simp only [hs, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih
    | true =>
      simp only [↓reduceIte, List.map_cons, sortAsc]
      have hsorted := sortAsc_sorted ((rest.filter (fun i => base i)).map val)
      cases hs : sub a with
      | false =>
        simp only [Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
        have hlen : (rest.map (fun i => if sub i then 1 else 0)).sum ≤
                    (sortAsc ((rest.filter (fun i => base i)).map val)).length := by
          have hlen_sort : ∀ l : List Nat, (sortAsc l).length = l.length := by
            intro l; induction l with
            | nil => rfl
            | cons x xs ihl =>
              simp only [sortAsc, List.length_cons]
              have hins : ∀ y l', (insertAsc y l').length = l'.length + 1 := by
                intro y l'; induction l' with
                | nil => rfl
                | cons z zs ihz => simp only [insertAsc]; split <;> simp [ihz]
              rw [hins, ihl]
          rw [hlen_sort, List.length_map]
          clear ih hsorted hlen_sort
          induction rest with
          | nil => simp
          | cons b bs ihb =>
            simp only [List.map_cons, List.sum_cons, List.filter_cons]
            cases hbb : base b with
            | false =>
              have hsb : sub b = false := by cases h : sub b with | false => rfl | true => have := hsub b h; rw [hbb] at this; cases this
              simp [hsb]; exact ihb
            | true =>
              simp only [↓reduceIte, List.length_cons]
              cases sub b <;> simp <;> omega
        exact Nat.le_trans ((sumTake_insertAsc_sorted (val a) _ hsorted _).1 hlen) ih
      | true =>
        simp only [↓reduceIte]
        have hle := (sumTake_insertAsc_sorted (val a) _ hsorted
          (1 + (rest.map (fun i => if sub i then 1 else 0)).sum)).2
          ((rest.map (fun i => if sub i then 1 else 0)).sum) (by omega)
        omega

/-- Abstract exact aboard-truck `(z, x)` split theorem (`ex1.py:L994-L1025`):
    Given the plan's actual partition of the `ab_c` trucks initially aboard `cf.fi` into:
    - `Z` (empty aboard trucks that NEVER disembark from `cf.fi`, size `z ≤ ab_empty`),
    - `X` (aboard trucks whose FIRST disembarkation is on `opp`, size `x ≤ ab_c - z`),
    - `D` (aboard trucks whose FIRST disembarkation is on `cur`, size `d = ab_c - z - x`),
    and given:
    - `F_cur, F_opp` = number of effective side crossings (`cur -> opp` and `opp -> cur`) of `frozenSide`
    - `BD(fi) ≥ d + 2 * (F_cur + F_opp) - x`
    - `F_cur ≥ x + k_gnd_cur`
    - `F_cur ≥ r_cur` and `F_opp ≥ r_opp` (from `fluxLB` with `m_cur - z`, `c_cur - sumTake z empty_caps`, `w_opp + sumTake k_carry stay_vals`)
    then the minimum over all `0 ≤ z ≤ ab_empty`, `0 ≤ x ≤ ab_c - z` in `ex1.py:L1007-L1023`
    is `≤ BD(fi)`! -/
def cutFerryBDCand (w_cur w_opp h_cur h_opp need_cur need_opp m_cur m_opp c_cur c_opp cap : Nat)
    (need_cur_b need_opp_b : Bool)
    (ab_c k_gnd_cur ab_stay : Nat) (empty_caps stay_vals : List Nat)
    (z x : Nat) : Nat :=
  let cz := sumTake z empty_caps
  let max_x := ab_c - z
  let k_carry := x - (max_x - ab_stay)
  let extra_opp := sumTake k_carry stay_vals
  let (r_cur, r_opp) :=
    fluxLB w_cur (w_opp + extra_opp) h_cur h_opp need_cur_b need_opp_b (m_cur - z) m_opp (c_cur - cz) c_opp cap
  let c_cur_eff := max r_cur (x + k_gnd_cur)
  (max_x - x) + 2 * (c_cur_eff + r_opp) - x

/-- Exact min over `z ∈ [0..ab_empty]`, `x ∈ [0..ab_c - z]` matching `ex1.py:L1007-L1023`. -/
def cutFerryBDMin (cand : Nat → Nat → Nat) (ab_empty ab_c : Nat) : Nat :=
  let pairs : List (Nat × Nat) :=
    (List.range (ab_empty + 1)).flatMap (fun z =>
      (List.range (ab_c - z + 1)).map (fun x => (z, x)))
  match pairs.map (fun (z, x) => cand z x) with
  | [] => 0
  | v :: vs => vs.foldl min v

theorem cutFerryBDMin_le (cand : Nat → Nat → Nat) (ab_empty ab_c z x : Nat)
    (hz : z ≤ ab_empty) (hx : x ≤ ab_c - z) :
    cutFerryBDMin cand ab_empty ab_c ≤ cand z x := by
  unfold cutFerryBDMin
  dsimp only
  have hmem : cand z x ∈
      ((List.range (ab_empty + 1)).flatMap (fun z' =>
        (List.range (ab_c - z' + 1)).map (fun x' => (z', x')))).map (fun (z, x) => cand z x) := by
    rw [List.mem_map]
    refine ⟨(z, x), ?_, rfl⟩
    rw [List.mem_flatMap]
    refine ⟨z, List.mem_range.mpr (by omega), ?_⟩
    rw [List.mem_map]
    exact ⟨x, List.mem_range.mpr (by omega), rfl⟩
  have hfold_le : ∀ (l : List Nat) (acc : Nat),
      l.foldl min acc ≤ acc ∧ ∀ v ∈ l, l.foldl min acc ≤ v := by
    intro l; induction l with
    | nil => intro acc; exact ⟨Nat.le_refl _, fun _ h => by cases h⟩
    | cons a as ih =>
      intro acc; simp only [List.foldl_cons]
      have ⟨h1, h2⟩ := ih (min acc a)
      refine ⟨Nat.le_trans h1 (Nat.min_le_left _ _), fun v hv => ?_⟩
      rcases List.mem_cons.mp hv with rfl | hvs
      · exact Nat.le_trans h1 (Nat.min_le_right _ _)
      · exact h2 v hvs
  cases hls : (((List.range (ab_empty + 1)).flatMap (fun z' =>
        (List.range (ab_c - z' + 1)).map (fun x' => (z', x')))).map (fun (z, x) => cand z x)) with
  | nil => rw [hls] at hmem; cases hmem
  | cons v vs =>
    rw [hls] at hmem
    rcases List.mem_cons.mp hmem with heq | hvs
    · rw [heq]; exact (hfold_le vs v).1
    · exact (hfold_le vs v).2 _ hvs

/-- Per-truck BD / frozen-side state machine for cut ferry `cf.fi`!
    Given a truck `t` and a cut `curSide : Fin G.numIslands → Bool` (where `curSide = inH` if `fi_in` else `!inH`):
    Track `(aboard : Bool, side : Bool)` along the plan:
    - When `t` is NOT aboard `cf.fi`, `side = curSide (G.islandOf (st.truckPhysLoc t))`.
    - When `t` IS aboard `cf.fi`, `side` is FROZEN at the side where `t` boarded `cf.fi` (or `true = cur` initially)!
    - On `DISEMBARK(t, cf.fi)` at location `l`: `side` updates to `curSide (G.islandOf l)`.
      * If `side` flips `true -> false`, record a `cur -> opp` flip!
      * If `side` flips `false -> true`, record an `opp -> cur` flip!
    Prove that for EVERY truck `t`:
    1. If `t` is NOT initially aboard `cf.fi`:
       `2 * (flipsAB + flipsBA) ≤ board(t, fi) + disembark(t, fi)`!
    2. If `t` IS initially aboard `cf.fi` and NEVER disembarks (`disembark(t, fi) = 0`):
       `flipsAB = 0 ∧ flipsBA = 0`!
    3. If `t` IS initially aboard `cf.fi` and its FIRST disembarkation is on `opp` (`curSide = false`):
       `2 * (flipsAB + flipsBA) - 1 ≤ board(t, fi) + disembark(t, fi)` AND `flipsAB ≥ 1`!
    4. If `t` IS initially aboard `cf.fi` and its FIRST disembarkation is on `cur` (`curSide = true`):
       `1 + 2 * (flipsAB + flipsBA) ≤ board(t, fi) + disembark(t, fi)`! -/
def frozenFlipsAB {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (curSide : Fin G.numIslands → Bool) (t : Fin I.numTrucks) : Bool → State I → Plan I → Nat
  | _, _, [] => 0
  | fSide, s, a :: rest =>
      match a with
      | .disembark t' f' =>
          if t' = t ∧ f' = fi then
            let newSide := curSide (G.islandOf (s.ferryLoc fi))
            (if fSide && !newSide then 1 else 0) +
            frozenFlipsAB G fi curSide t newSide (applyAction s a) rest
          else
            frozenFlipsAB G fi curSide t fSide (applyAction s a) rest
      | _ => frozenFlipsAB G fi curSide t fSide (applyAction s a) rest

def frozenFlipsBA {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (curSide : Fin G.numIslands → Bool) (t : Fin I.numTrucks) : Bool → State I → Plan I → Nat
  | _, _, [] => 0
  | fSide, s, a :: rest =>
      match a with
      | .disembark t' f' =>
          if t' = t ∧ f' = fi then
            let newSide := curSide (G.islandOf (s.ferryLoc fi))
            (if !fSide && newSide then 1 else 0) +
            frozenFlipsBA G fi curSide t newSide (applyAction s a) rest
          else
            frozenFlipsBA G fi curSide t fSide (applyAction s a) rest
      | _ => frozenFlipsBA G fi curSide t fSide (applyAction s a) rest

/-- Fundamental per-truck BD conservation theorem for `frozenFlipsAB` / `frozenFlipsBA`!
    - When `t` is NOT aboard `fi`: `2 * (flipsAB + flipsBA) ≤ boards + disembarks`.
    - When `t` IS aboard `fi` with frozen side `fSide`:
      * if `disembarks = 0`: `flipsAB = 0 ∧ flipsBA = 0`.
      * if `disembarks ≥ 1`:
        - `2 * (flipsAB + flipsBA) ≤ boards + disembarks + 1` always (cost ≥ `2*F - 1`), AND
        - if the first disembarkation is on `fSide` (no flip on first disembark!), `1 + 2 * (flipsAB + flipsBA) ≤ boards + disembarks`! -/
theorem frozenFlips_le_truckBD {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (curSide : Fin G.numIslands → Bool) (t : Fin I.numTrucks)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end) :
    ∀ fSide : Bool,
      let fAB := frozenFlipsAB G fi curSide t fSide s π
      let fBA := frozenFlipsBA G fi curSide t fSide s π
      let bCnt := countActions (isTruckFerryBoard t fi) π
      let dCnt := countActions (isTruckFerryDisembark t fi) π
      (s.truckLoc t ≠ .onFerry fi → 2 * (fAB + fBA) ≤ bCnt + dCnt) ∧
      (s.truckLoc t = .onFerry fi →
        (dCnt = 0 → fAB = 0 ∧ fBA = 0) ∧
        2 * (fAB + fBA) ≤ bCnt + dCnt + 1) := by
  induction hp with
  | nil =>
    intro fSide
    simp [frozenFlipsAB, frozenFlipsBA, countActions]
  | @cons sa sb _ a rest hstep _ ih =>
    intro fSide
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    cases hstep with
    | @board t' f' ht' _ =>
      by_cases htf : t' = t ∧ f' = fi
      · rcases htf with ⟨rfl, rfl⟩
        have hnot_ab : sa.truckLoc t' ≠ .onFerry f' := by rw [ht']; intro h; cases h
        have hab_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f') } : State I).truckLoc t' = .onFerry f' := by
          simp [updateFn]
        have ⟨_, hrec⟩ := ih fSide
        have h2 := (hrec hab_b).2
        simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                   isTruckFerryBoard, isTruckFerryDisembark, decide_true, Bool.and_self, ↓reduceIte,
                   Bool.false_eq_true, Nat.zero_add] at h2 ⊢
        refine ⟨fun _ => by omega, fun h => absurd h hnot_ab⟩
      · have hbf : isTruckFerryBoard t fi (.board t' f') = false := by
          simp only [isTruckFerryBoard, Bool.and_eq_false_iff, decide_eq_false_iff_not]
          by_cases ht : t' = t
          · right; intro hf; exact htf ⟨ht, hf⟩
          · left; exact ht
        simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                   hbf, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
        have ⟨ihN, ihA⟩ := ih fSide
        by_cases ht : t = t'
        · subst ht
          have hf : f' ≠ fi := fun h => htf ⟨rfl, h⟩
          have hna_a : sa.truckLoc t ≠ .onFerry fi := by rw [ht']; intro h; cases h
          have hna_b : ({ sa with truckLoc := updateFn sa.truckLoc t (.onFerry f') } : State I).truckLoc t ≠ .onFerry fi := by
            simp [updateFn, hf]
          exact ⟨fun _ => ihN hna_b, fun h => absurd h hna_a⟩
        · have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f') } : State I).truckLoc t = sa.truckLoc t := by
            simp [updateFn, ht]
          rw [heq] at ihN ihA
          exact ⟨ihN, ihA⟩
    | @disembark t' f' ht' =>
      by_cases htf : t' = t ∧ f' = fi
      · rcases htf with ⟨rfl, rfl⟩
        have hab_a : sa.truckLoc t' = .onFerry f' := ht'
        have hna_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } : State I).truckLoc t' ≠ .onFerry f' := by
          simp [updateFn]
        let newSide := curSide (G.islandOf (sa.ferryLoc f'))
        have ⟨ihN, _⟩ := ih newSide
        have hrec := ihN hna_b
        have hfb_cons : countActions (isTruckFerryBoard t' f') (.disembark t' f' :: rest) =
            countActions (isTruckFerryBoard t' f') rest := by
          unfold countActions; simp [isTruckFerryBoard]
        have hfd_cons : countActions (isTruckFerryDisembark t' f') (.disembark t' f' :: rest) =
            1 + countActions (isTruckFerryDisembark t' f') rest := by
          unfold countActions; simp [isTruckFerryDisembark]
        rw [hfb_cons, hfd_cons]
        simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, and_self, ↓reduceIte]
        refine ⟨fun h => absurd hab_a h, fun _ => ⟨fun hd0 => by omega, ?_⟩⟩
        cases fSide <;> cases hns : curSide (G.islandOf (sa.ferryLoc f')) <;> simp [newSide, hns] at hrec ⊢ <;> omega
      · have hdf : isTruckFerryDisembark t fi (.disembark t' f') = false := by
          simp only [isTruckFerryDisembark, Bool.and_eq_false_iff, decide_eq_false_iff_not]
          by_cases ht : t' = t
          · right; intro hf; exact htf ⟨ht, hf⟩
          · left; exact ht
        simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, htf, ↓reduceIte, countActions,
                   List.map_cons, List.sum_cons, isTruckFerryBoard, hdf, Bool.false_eq_true, Nat.zero_add]
        have ⟨ihN, ihA⟩ := ih fSide
        by_cases ht : t = t'
        · subst ht
          have hf : f' ≠ fi := fun h => htf ⟨rfl, h⟩
          have hna_a : sa.truckLoc t ≠ .onFerry fi := by rw [ht']; intro h; injection h with h'; exact hf h'
          have hna_b : ({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc (sa.ferryLoc f')) } : State I).truckLoc t ≠ .onFerry fi := by
            simp [updateFn]
          exact ⟨fun _ => ihN hna_b, fun h => absurd h hna_a⟩
        · have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } : State I).truckLoc t = sa.truckLoc t := by
            simp [updateFn, ht]
          rw [heq] at ihN ihA
          exact ⟨ihN, ihA⟩
    | @drive t' u v ht' _ _ =>
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      have ⟨ihN, ihA⟩ := ih fSide
      by_cases ht : t = t'
      · subst ht
        have hna_a : sa.truckLoc t ≠ .onFerry fi := by rw [ht']; intro h; cases h
        have hna_b : ({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc v) } : State I).truckLoc t ≠ .onFerry fi := by
          simp [updateFn]
        exact ⟨fun _ => ihN hna_b, fun h => absurd h hna_a⟩
      · have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckLoc t = sa.truckLoc t := by
          simp [updateFn, ht]
        rw [heq] at ihN ihA; exact ⟨ihN, ihA⟩
    | load _ _ _ =>
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih fSide
    | unload _ _ =>
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih fSide
    | sail _ _ _ =>
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih fSide

/-- First disembarkation side of a truck initially aboard `fi` (`none` if it never disembarks,
    `some true` if first disembark is on `curSide = true`, `some false` if on `opp`). -/
def firstDisembarkSide {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (curSide : Fin G.numIslands → Bool) (t : Fin I.numTrucks) : State I → Plan I → Option Bool
  | _, [] => none
  | s, a :: rest =>
      match a with
      | .disembark t' f' =>
          if t' = t ∧ f' = fi then some (curSide (G.islandOf (s.ferryLoc fi)))
          else firstDisembarkSide G fi curSide t (applyAction s a) rest
      | _ => firstDisembarkSide G fi curSide t (applyAction s a) rest

/-- Refined per-truck BD bound for initially aboard trucks (`D` case: first disembarkation is on `cur`,
    costing `+1` extra BD above `2 * (fAB + fBA)`!). -/
theorem frozenFlips_firstDisembark_cur {I : Instance} (G : IslandGraph I) (fi : Fin I.numFerries)
    (curSide : Fin G.numIslands → Bool) (t : Fin I.numTrucks)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end)
    (hab : s.truckLoc t = .onFerry fi)
    (hfirst : firstDisembarkSide G fi curSide t s π = some true) :
    1 + 2 * (frozenFlipsAB G fi curSide t true s π + frozenFlipsBA G fi curSide t true s π) ≤
    countActions (isTruckFerryBoard t fi) π + countActions (isTruckFerryDisembark t fi) π := by
  induction hp with
  | nil => simp [firstDisembarkSide] at hfirst
  | @cons sa sb _ a rest hstep hrest ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    cases hstep with
    | @disembark t' f' ht' =>
      by_cases htf : t' = t ∧ f' = fi
      · rcases htf with ⟨rfl, rfl⟩
        simp only [firstDisembarkSide, and_self, ↓reduceIte, Option.some.injEq] at hfirst
        have hna_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } : State I).truckLoc t' ≠ .onFerry f' := by
          simp [updateFn]
        have hrec := (frozenFlips_le_truckBD G f' curSide t' hrest true).1 hna_b
        have hfb_cons : countActions (isTruckFerryBoard t' f') (.disembark t' f' :: rest) =
            countActions (isTruckFerryBoard t' f') rest := by
          unfold countActions; simp [isTruckFerryBoard]
        have hfd_cons : countActions (isTruckFerryDisembark t' f') (.disembark t' f' :: rest) =
            1 + countActions (isTruckFerryDisembark t' f') rest := by
          unfold countActions; simp [isTruckFerryDisembark]
        rw [hfb_cons, hfd_cons]
        have hstep_ab : frozenFlipsAB G f' curSide t' true sa (.disembark t' f' :: rest) =
            frozenFlipsAB G f' curSide t' true { sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } rest := by
          simp [frozenFlipsAB, hfirst, ← hsb_eq]
        have hstep_ba : frozenFlipsBA G f' curSide t' true sa (.disembark t' f' :: rest) =
            frozenFlipsBA G f' curSide t' true { sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } rest := by
          simp [frozenFlipsBA, hfirst, ← hsb_eq]
        rw [hstep_ab, hstep_ba]
        omega
      · have hdf : isTruckFerryDisembark t fi (.disembark t' f') = false := by
          simp only [isTruckFerryDisembark, Bool.and_eq_false_iff, decide_eq_false_iff_not]
          by_cases ht : t' = t
          · right; intro hf; exact htf ⟨ht, hf⟩
          · left; exact ht
        have ht_ne : t ≠ t' := by
          intro h; subst h; rw [hab] at ht'; injection ht' with hf; exact htf ⟨rfl, hf.symm⟩
        have hab_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f')) } : State I).truckLoc t = .onFerry fi := by
          simp [updateFn, ht_ne, hab]
        simp only [firstDisembarkSide, htf, ↓reduceIte, ← hsb_eq] at hfirst
        simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, htf, ↓reduceIte, countActions,
                   List.map_cons, List.sum_cons, isTruckFerryBoard, hdf, Bool.false_eq_true, Nat.zero_add]
        exact ih hab_b hfirst
    | @board t' f' ht' _ =>
      have ht_ne : t ≠ t' := by intro h; subst h; rw [hab] at ht'; cases ht'
      have hbf : isTruckFerryBoard t fi (.board t' f') = false := by
        simp [isTruckFerryBoard, Ne.symm ht_ne]
      have hab_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f') } : State I).truckLoc t = .onFerry fi := by
        simp [updateFn, ht_ne, hab]
      simp only [firstDisembarkSide, ← hsb_eq] at hfirst
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 hbf, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih hab_b hfirst
    | @drive t' u v ht' _ _ =>
      have ht_ne : t ≠ t' := by intro h; subst h; rw [hab] at ht'; cases ht'
      have hab_b : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckLoc t = .onFerry fi := by
        simp [updateFn, ht_ne, hab]
      simp only [firstDisembarkSide, ← hsb_eq] at hfirst
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih hab_b hfirst
    | load _ _ _ =>
      simp only [firstDisembarkSide, ← hsb_eq] at hfirst
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih hab hfirst
    | unload _ _ =>
      simp only [firstDisembarkSide, ← hsb_eq] at hfirst
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih hab hfirst
    | sail _ _ _ =>
      simp only [firstDisembarkSide, ← hsb_eq] at hfirst
      simp only [frozenFlipsAB, frozenFlipsBA, ← hsb_eq, countActions, List.map_cons, List.sum_cons,
                 isTruckFerryBoard, isTruckFerryDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
      exact ih hab hfirst

/-- Master algebraic combination for the `(z, x)` aboard-truck split (`ex1.py:L994-L1025`):
    Given the plan's actual partition `(Z, X, D)` of aboard trucks and total frozen flips `F_cur, F_opp`,
    `cutFerryBDMin` is `≤ ferryBDCount fi π`! -/
theorem cutFerry_zx_split_algebra
    {w_cur w_opp h_cur h_opp m_cur m_opp c_cur c_opp cap : Nat}
    {need_cur_b need_opp_b : Bool}
    {ab_c ab_empty ab_stay k_gnd_cur z x F_cur F_opp bd_fi : Nat}
    {empty_caps stay_vals : List Nat}
    (hz : z ≤ ab_empty)
    (hx : x ≤ ab_c - z)
    (hbd : (ab_c - z - x) + 2 * (F_cur + F_opp) ≤ bd_fi + x)
    (hF_gnd : x + k_gnd_cur ≤ F_cur)
    (hflux :
      let cz := sumTake z empty_caps
      let k_carry := x - (ab_c - z - ab_stay)
      let extra_opp := sumTake k_carry stay_vals
      let r := fluxLB w_cur (w_opp + extra_opp) h_cur h_opp need_cur_b need_opp_b (m_cur - z) m_opp (c_cur - cz) c_opp cap
      r.1 ≤ F_cur ∧ r.2 ≤ F_opp) :
    cutFerryBDMin
      (cutFerryBDCand w_cur w_opp h_cur h_opp 0 0 m_cur m_opp c_cur c_opp cap
        need_cur_b need_opp_b ab_c k_gnd_cur ab_stay empty_caps stay_vals)
      ab_empty ab_c ≤ bd_fi := by
  apply Nat.le_trans (cutFerryBDMin_le _ ab_empty ab_c z x hz hx)
  unfold cutFerryBDCand
  dsimp only at hflux ⊢
  omega

-- ==============================================================================
-- 4. GENERAL / CYCLIC ISLAND FERRIES (`_eval_island_ferries`, ex1.py:L1035-L1246)
-- ==============================================================================

/-- Predicate matching a `BOARD` action occurring on island `isl` (in state `s`). -/
def isBoardOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (s : State I) : Action I → Bool
  | .board _ f => decide (G.islandOf (s.ferryLoc f) = isl)
  | _          => false

/-- Predicate matching a `DISEMBARK` action occurring on island `isl` (in state `s`). -/
def isDisembarkOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (s : State I) : Action I → Bool
  | .disembark _ f => decide (G.islandOf (s.ferryLoc f) = isl)
  | _              => false

/-- State-dependent counters for boards/disembarks on a specific island `isl` (total & per truck). -/
def boardOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest => (if isBoardOnIsl G isl s a then 1 else 0) + boardOnIsl G isl (applyAction s a) rest

def disembarkOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest => (if isDisembarkOnIsl G isl s a then 1 else 0) + disembarkOnIsl G isl (applyAction s a) rest

def truckBoardOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (t : Fin I.numTrucks) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest =>
      (match a with
       | .board t' f => if t' = t ∧ G.islandOf (s.ferryLoc f) = isl then 1 else 0
       | _ => 0) + truckBoardOnIsl G isl t (applyAction s a) rest

def truckDisembarkOnIsl {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (t : Fin I.numTrucks) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest =>
      (match a with
       | .disembark t' f => if t' = t ∧ G.islandOf (s.ferryLoc f) = isl then 1 else 0
       | _ => 0) + truckDisembarkOnIsl G isl t (applyAction s a) rest

theorem sum_boardOnIsl_eq_boardCount {I : Instance} (G : IslandGraph I) (s : State I) (π : Plan I) :
    finSum (fun isl => boardOnIsl G isl s π) = boardCount π := by
  unfold boardCount countActions
  induction π generalizing s with
  | nil => simp [boardOnIsl, finSum_zero]
  | cons a rest ih =>
    simp only [boardOnIsl, List.map_cons, List.sum_cons]
    rw [finSum_add, ih (applyAction s a)]
    congr 1
    cases a with
    | board t f =>
      have hfn : (fun isl => if isBoardOnIsl G isl s (.board t f) = true then 1 else 0) =
                 (fun isl => if isl = G.islandOf (s.ferryLoc f) then 1 else 0) := by
        funext isl; by_cases h : isl = G.islandOf (s.ferryLoc f)
        · subst h; simp [isBoardOnIsl]
        · simp [isBoardOnIsl, h, Ne.symm h]
      rw [hfn, finSum_ite_eq]; rfl
    | drive _ _ _ => simp [isBoardOnIsl, isBoard, finSum_zero]
    | load _ _ => simp [isBoardOnIsl, isBoard, finSum_zero]
    | unload _ _ => simp [isBoardOnIsl, isBoard, finSum_zero]
    | disembark _ _ => simp [isBoardOnIsl, isBoard, finSum_zero]
    | sail _ _ _ => simp [isBoardOnIsl, isBoard, finSum_zero]

theorem sum_disembarkOnIsl_eq_disembarkCount {I : Instance} (G : IslandGraph I) (s : State I) (π : Plan I) :
    finSum (fun isl => disembarkOnIsl G isl s π) = disembarkCount π := by
  unfold disembarkCount countActions
  induction π generalizing s with
  | nil => simp [disembarkOnIsl, finSum_zero]
  | cons a rest ih =>
    simp only [disembarkOnIsl, List.map_cons, List.sum_cons]
    rw [finSum_add, ih (applyAction s a)]
    congr 1
    cases a with
    | disembark t f =>
      have hfn : (fun isl => if isDisembarkOnIsl G isl s (.disembark t f) = true then 1 else 0) =
                 (fun isl => if isl = G.islandOf (s.ferryLoc f) then 1 else 0) := by
        funext isl; by_cases h : isl = G.islandOf (s.ferryLoc f)
        · subst h; simp [isDisembarkOnIsl]
        · simp [isDisembarkOnIsl, h, Ne.symm h]
      rw [hfn, finSum_ite_eq]; rfl
    | drive _ _ _ => simp [isDisembarkOnIsl, isDisembark, finSum_zero]
    | load _ _ => simp [isDisembarkOnIsl, isDisembark, finSum_zero]
    | unload _ _ => simp [isDisembarkOnIsl, isDisembark, finSum_zero]
    | board _ _ => simp [isDisembarkOnIsl, isDisembark, finSum_zero]
    | sail _ _ _ => simp [isDisembarkOnIsl, isDisembark, finSum_zero]

/-- Per-truck conservation on island `isl` (`ex1.py:L1138-L1143`):
    A truck can board a ferry at `isl` at most `disembarks_at_isl + (1 if initially non-aboard on isl else 0)` times! -/
theorem truck_boardOnIsl_le_disembarkOnIsl {I : Instance} (G : IslandGraph I)
    (isl : Fin G.numIslands) (t : Fin I.numTrucks)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end) :
    truckBoardOnIsl G isl t s π ≤
    truckDisembarkOnIsl G isl t s π +
      (if s.truckOnFerry t = none ∧ G.islandOf (s.truckPhysLoc t) = isl then 1 else 0) := by
  induction hp with
  | nil => simp [truckBoardOnIsl, truckDisembarkOnIsl]
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    simp only [truckBoardOnIsl, truckDisembarkOnIsl, ← hsb_eq]
    cases hstep with
    | @drive t' u v ht' _ hroad =>
      let sb' : State I := { sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) }
      have hsame : (sb'.truckOnFerry t = none ∧ G.islandOf (sb'.truckPhysLoc t) = isl) ↔
                   (sa.truckOnFerry t = none ∧ G.islandOf (sa.truckPhysLoc t) = isl) := by
        by_cases ht : t = t'
        · subst ht; simp [sb', State.truckOnFerry, State.truckPhysLoc, updateFn, ht', G.road_same u v hroad]
        · simp [sb', State.truckOnFerry, State.truckPhysLoc, updateFn, ht]
      by_cases hc : sa.truckOnFerry t = none ∧ G.islandOf (sa.truckPhysLoc t) = isl
      · have hcb : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckOnFerry t = none ∧
                   G.islandOf (({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckPhysLoc t) = isl := hsame.mpr hc
        simp only [hc, ↓reduceIte, Nat.zero_add]
        simp only [hcb, ↓reduceIte] at ih; exact ih
      · have hcb : ¬ (({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckOnFerry t = none ∧
                      G.islandOf (({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckPhysLoc t) = isl) :=
          fun h => hc (hsame.mp h)
        simp only [hc, ↓reduceIte, Nat.zero_add]
        simp only [hcb, ↓reduceIte] at ih; exact ih
    | load _ _ _ => simp only [Nat.zero_add, State.truckOnFerry, State.truckPhysLoc] at ih ⊢; exact ih
    | unload _ _ => simp only [Nat.zero_add, State.truckOnFerry, State.truckPhysLoc] at ih ⊢; exact ih
    | @board t' f ht' _ =>
      by_cases ht : t' = t
      · subst ht
        have ha_on : sa.truckOnFerry t' = none := by simp [State.truckOnFerry, ht']
        have ha_phys : sa.truckPhysLoc t' = sa.ferryLoc f := by simp [State.truckPhysLoc, ht']
        have hb_off : ¬ (({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckOnFerry t' = none ∧
                         G.islandOf (({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckPhysLoc t') = isl) := by
          simp [State.truckOnFerry, updateFn]
        simp only [hb_off, ↓reduceIte, Nat.add_zero] at ih
        by_cases hisl : G.islandOf (sa.ferryLoc f) = isl
        · simp [hisl, ha_on, ha_phys]; omega
        · simp [hisl, ha_on, ha_phys]; omega
      · have hne : t ≠ t' := Ne.symm ht
        have heq_on : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckOnFerry t = sa.truckOnFerry t := by
          simp [State.truckOnFerry, updateFn, hne]
        have heq_ph : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckPhysLoc t = sa.truckPhysLoc t := by
          simp [State.truckPhysLoc, updateFn, hne]
        simp only [ht, false_and, ↓reduceIte, Nat.zero_add]
        rw [heq_on, heq_ph] at ih; exact ih
    | @disembark t' f ht' =>
      by_cases ht : t' = t
      · subst ht
        have ha_off : ¬ (sa.truckOnFerry t' = none ∧ G.islandOf (sa.truckPhysLoc t') = isl) := by
          simp [State.truckOnFerry, ht']
        have hb_on : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckOnFerry t' = none := by
          simp [State.truckOnFerry, updateFn]
        have hb_phys : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckPhysLoc t' = sa.ferryLoc f := by
          simp [State.truckPhysLoc, updateFn]
        simp only [ha_off, ↓reduceIte, Nat.add_zero]
        by_cases hisl : G.islandOf (sa.ferryLoc f) = isl
        · simp [hisl, hb_on, hb_phys] at ih ⊢; omega
        · simp [hisl, hb_on, hb_phys] at ih ⊢; omega
      · have hne : t ≠ t' := Ne.symm ht
        have heq_on : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckOnFerry t = sa.truckOnFerry t := by
          simp [State.truckOnFerry, updateFn, hne]
        have heq_ph : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckPhysLoc t = sa.truckPhysLoc t := by
          simp [State.truckPhysLoc, updateFn, hne]
        simp only [ht, false_and, ↓reduceIte, Nat.zero_add]
        rw [heq_on, heq_ph] at ih; exact ih
    | @sail f u v hf _ _ =>
      have hsame : (({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckOnFerry t = none ∧
                    G.islandOf (({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckPhysLoc t) = isl) ↔
                   (sa.truckOnFerry t = none ∧ G.islandOf (sa.truckPhysLoc t) = isl) := by
        cases htl : sa.truckLoc t with
        | atLoc l => simp [State.truckOnFerry, State.truckPhysLoc, htl]
        | onFerry f' => simp [State.truckOnFerry, htl]
      by_cases hc : sa.truckOnFerry t = none ∧ G.islandOf (sa.truckPhysLoc t) = isl
      · have hcb : ({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckOnFerry t = none ∧
                   G.islandOf (({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckPhysLoc t) = isl := hsame.mpr hc
        simp only [hc, ↓reduceIte, Nat.zero_add]; simp only [hcb, ↓reduceIte] at ih; exact ih
      · have hcb : ¬ (({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckOnFerry t = none ∧
                      G.islandOf (({ sa with ferryLoc := updateFn sa.ferryLoc f v } : State I).truckPhysLoc t) = isl) :=
          fun h => hc (hsame.mp h)
        simp only [hc, ↓reduceIte, Nat.zero_add]; simp only [hcb, ↓reduceIte] at ih; exact ih

/-- Global board/disembark conservation (`ex1.py:L1212-L1213`):
    `disembarkCount π ≤ boardCount π + n_ab` (so `lb_d - n_ab ≤ boardCount π`)! -/
theorem disembarkCount_le_boardCount_add_nab {I : Instance}
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end) :
    disembarkCount π ≤ boardCount π + finSum (fun t => if s.truckOnFerry t ≠ none then 1 else 0) := by
  have hper_truck : ∀ t : Fin I.numTrucks,
      countActions (isTruckDisembark t) π ≤
      countActions (isTruckBoard t) π + (if s.truckOnFerry t ≠ none then 1 else 0) := by
    intro t
    induction hp with
    | nil => simp [countActions]
    | @cons sa sb _ a rest hstep _ ih =>
      have hbd_step : ∀ (p : Action I → Bool), countActions p (a :: rest) = (if p a = true then 1 else 0) + countActions p rest :=
        fun _ => rfl
      rw [hbd_step, hbd_step]
      cases hstep with
      | @board t' f ht' _ =>
        by_cases ht : t' = t
        · subst ht
          have hna : sa.truckOnFerry t' = none := by simp [State.truckOnFerry, ht']
          have hab : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckOnFerry t' ≠ none := by
            simp [State.truckOnFerry, updateFn]
          simp [isTruckBoard, isTruckDisembark, hna, hab] at ih ⊢; omega
        · have hne : t ≠ t' := Ne.symm ht
          have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.onFerry f) } : State I).truckOnFerry t = sa.truckOnFerry t := by
            simp [State.truckOnFerry, updateFn, hne]
          simp [isTruckBoard, isTruckDisembark, ht, heq] at ih ⊢; omega
      | @disembark t' f ht' =>
        by_cases ht : t' = t
        · subst ht
          have hab : sa.truckOnFerry t' ≠ none := by simp [State.truckOnFerry, ht']
          have hna : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckOnFerry t' = none := by
            simp [State.truckOnFerry, updateFn]
          simp [isTruckBoard, isTruckDisembark, hna, hab] at ih ⊢; omega
        · have hne : t ≠ t' := Ne.symm ht
          have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc (sa.ferryLoc f)) } : State I).truckOnFerry t = sa.truckOnFerry t := by
            simp [State.truckOnFerry, updateFn, hne]
          simp [isTruckBoard, isTruckDisembark, ht, heq] at ih ⊢; omega
      | @drive t' u v ht' _ _ =>
        have heq : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckOnFerry t = sa.truckOnFerry t := by
          by_cases ht : t = t'
          · subst ht; simp [State.truckOnFerry, updateFn, ht']
          · simp [State.truckOnFerry, updateFn, ht]
        simp only [isTruckBoard, isTruckDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
        rw [heq] at ih; exact ih
      | load _ _ _ => simp only [isTruckBoard, isTruckDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]; exact ih
      | unload _ _ => simp only [isTruckBoard, isTruckDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]; exact ih
      | sail _ _ _ => simp only [isTruckBoard, isTruckDisembark, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]; exact ih
  have hsum := finSum_le_finSum hper_truck
  rw [finSum_add] at hsum
  have hdis : finSum (fun t => countActions (isTruckDisembark t) π) = disembarkCount π := by
    unfold disembarkCount countActions
    clear hper_truck hsum hp
    induction π with
    | nil => simp [finSum_zero]
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      rw [finSum_add, ih]; congr 1
      cases a with
      | disembark t₀ f₀ =>
        have hfn : (fun t => if isTruckDisembark t (.disembark t₀ f₀) = true then 1 else 0) =
                   (fun t => if t = t₀ then 1 else 0) := by
          funext t; by_cases h : t = t₀
          · subst h; simp [isTruckDisembark]
          · simp [isTruckDisembark, h, Ne.symm h]
        rw [hfn, finSum_ite_eq]; rfl
      | drive _ _ _ => simp [isTruckDisembark, isDisembark, finSum_zero]
      | load _ _ => simp [isTruckDisembark, isDisembark, finSum_zero]
      | unload _ _ => simp [isTruckDisembark, isDisembark, finSum_zero]
      | board _ _ => simp [isTruckDisembark, isDisembark, finSum_zero]
      | sail _ _ _ => simp [isTruckDisembark, isDisembark, finSum_zero]
  have hbrd : finSum (fun t => countActions (isTruckBoard t) π) = boardCount π := by
    unfold boardCount countActions
    clear hper_truck hsum hdis hp
    induction π with
    | nil => simp [finSum_zero]
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      rw [finSum_add, ih]; congr 1
      cases a with
      | board t₀ f₀ =>
        have hfn : (fun t => if isTruckBoard t (.board t₀ f₀) = true then 1 else 0) =
                   (fun t => if t = t₀ then 1 else 0) := by
          funext t; by_cases h : t = t₀
          · subst h; simp [isTruckBoard]
          · simp [isTruckBoard, h, Ne.symm h]
        rw [hfn, finSum_ite_eq]; rfl
      | drive _ _ _ => simp [isTruckBoard, isBoard, finSum_zero]
      | load _ _ => simp [isTruckBoard, isBoard, finSum_zero]
      | unload _ _ => simp [isTruckBoard, isBoard, finSum_zero]
      | disembark _ _ => simp [isTruckBoard, isBoard, finSum_zero]
      | sail _ _ _ => simp [isTruckBoard, isBoard, finSum_zero]
  omega

-- ==============================================================================
-- 5. MULTI-HOP ISLAND METRIC POTENTIALS FOR `b2` AND `d2` (`ex1.py:L1086-L1109, L1204-L1211`)
-- ==============================================================================

/-- Minimum `minSails` distance from any port served by ferry `f` to target island `g`. -/
def ferryMinSails {I : Instance} (G : IslandGraph I) (f : Fin I.numFerries) (g : Fin G.numIslands) : Nat :=
  match ((List.finRange I.numLocs).filter (fun l => I.ferryServed f l)).map (fun l => G.minSails (G.islandOf l) g) with
  | [] => 0
  | d :: ds => ds.foldl min d

theorem ferryMinSails_le {I : Instance} (G : IslandGraph I) (f : Fin I.numFerries) (g : Fin G.numIslands)
    (l : Fin I.numLocs) (hsv : I.ferryServed f l = true) :
    ferryMinSails G f g ≤ G.minSails (G.islandOf l) g := by
  unfold ferryMinSails
  have hmem : G.minSails (G.islandOf l) g ∈
      ((List.finRange I.numLocs).filter (fun l' => I.ferryServed f l')).map (fun l' => G.minSails (G.islandOf l') g) :=
    List.mem_map.mpr ⟨l, List.mem_filter.mpr ⟨List.mem_finRange l, hsv⟩, rfl⟩
  have hfold_le : ∀ (ls : List Nat) (acc : Nat), ls.foldl min acc ≤ acc ∧ ∀ v ∈ ls, ls.foldl min acc ≤ v := by
    intro ls; induction ls with
    | nil => intro acc; exact ⟨Nat.le_refl _, fun _ h => by cases h⟩
    | cons a as ih =>
      intro acc; simp only [List.foldl_cons]
      have ⟨h1, h2⟩ := ih (min acc a)
      refine ⟨Nat.le_trans h1 (Nat.min_le_left _ _), fun v hv => ?_⟩
      rcases List.mem_cons.mp hv with rfl | hvs
      · exact Nat.le_trans h1 (Nat.min_le_right _ _)
      · exact h2 v hvs
  cases hls : (((List.finRange I.numLocs).filter (fun l' => I.ferryServed f l')).map (fun l' => G.minSails (G.islandOf l') g)) with
  | nil => rw [hls] at hmem; cases hmem
  | cons d ds =>
    rw [hls] at hmem
    rcases List.mem_cons.mp hmem with heq | hds
    · rw [heq]; exact (hfold_le ds d).1
    · exact (hfold_le ds d).2 _ hds

theorem minSails_le_ferryMinSails_add_one {I : Instance} (G : IslandGraph I)
    (f : Fin I.numFerries) (g : Fin G.numIslands) (u : Fin I.numLocs)
    (hcap : 0 < I.ferryCap f) (hsv : I.ferryServed f u = true) :
    G.minSails (G.islandOf u) g ≤ ferryMinSails G f g + 1 := by
  unfold ferryMinSails
  have hmem : G.minSails (G.islandOf u) g ∈
      ((List.finRange I.numLocs).filter (fun l' => I.ferryServed f l')).map (fun l' => G.minSails (G.islandOf l') g) :=
    List.mem_map.mpr ⟨u, List.mem_filter.mpr ⟨List.mem_finRange u, hsv⟩, rfl⟩
  have hall : ∀ v ∈ (((List.finRange I.numLocs).filter (fun l' => I.ferryServed f l')).map
      (fun l' => G.minSails (G.islandOf l') g)), G.minSails (G.islandOf u) g ≤ v + 1 := by
    intro v hv
    rw [List.mem_map] at hv
    rcases hv with ⟨l, hl, rfl⟩
    have hl_sv : I.ferryServed f l = true := (List.mem_filter.mp hl).2
    have htri := G.minSails_tri (G.islandOf u) (G.islandOf l) g
    have h1 := G.minSails_ferry f u l hcap hsv hl_sv
    omega
  have hfold_ge : ∀ (ls : List Nat) (acc : Nat) (B : Nat),
      B ≤ acc + 1 → (∀ v ∈ ls, B ≤ v + 1) → B ≤ ls.foldl min acc + 1 := by
    intro ls; induction ls with
    | nil => intro acc B ha _; exact ha
    | cons a as ih =>
      intro acc B ha hls
      simp only [List.foldl_cons]
      apply ih (min acc a) B
      · have h1 := hls a (List.mem_cons_self ..)
        by_cases h : acc ≤ a
        · rw [Nat.min_eq_left h]; exact ha
        · rw [Nat.min_eq_right (by omega)]; exact h1
      · intro v hv; exact hls v (List.mem_cons_of_mem _ hv)
  cases hls : (((List.finRange I.numLocs).filter (fun l' => I.ferryServed f l')).map (fun l' => G.minSails (G.islandOf l') g)) with
  | nil => rw [hls] at hmem; cases hmem
  | cons d ds =>
    rw [hls] at hall
    exact hfold_ge ds d _ (hall d (List.mem_cons_self ..)) (fun v hv => hall v (List.mem_cons_of_mem _ hv))

/-- Ferry-invariant BOARD potential `potB` (`ex1.py:L1090-L1100`):
    drops by `≤ 1` ONLY on `BOARD` actions (and by `0` on `DRIVE`, `LOAD`, `UNLOAD`, `DISEMBARK`, `SAIL`)! -/
def potB {I : Instance} (G : IslandGraph I) (s : State I) (p : Fin I.numPkgs) : Nat :=
  match s.pkgOnFerry p with
  | none   => G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p))
  | some f => ferryMinSails G f (G.islandOf (I.pkgGoal p))

/-- Ferry-invariant DISEMBARK potential `potD` (`ex1.py:L1091-L1108`):
    drops by `≤ 1` ONLY on `DISEMBARK` actions (and by `0` on `DRIVE`, `LOAD`, `UNLOAD`, `BOARD`, `SAIL`)! -/
def potD {I : Instance} (G : IslandGraph I) (s : State I) (p : Fin I.numPkgs) : Nat :=
  match s.pkgOnFerry p with
  | none   => G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p))
  | some f => 1 + ferryMinSails G f (G.islandOf (I.pkgGoal p))

private theorem max_ceilDiv_hd_le_packLB (bw bhd hd l tot cap : Nat)
    (hbw : bw ≤ tot) (hbhd : bhd ≤ hd) :
    max (ceilDiv bw cap) bhd ≤ packLB hd 0 l tot cap := by
  have hc1 : ceilDiv bw cap ≤ ceilDiv tot cap := ceilDiv_mono hbw
  unfold packLB
  dsimp only
  have hc_eq : (if tot > 0 then (tot + (cap - 1)) / cap else 0) = ceilDiv tot cap := rfl
  rw [hc_eq]
  by_cases h1 : hd > 0
  · simp only [h1, ↓reduceIte]
    generalize (if l - (cap - 0) * hd > 0 then (l - (cap - 0) * hd + (cap - 1)) / cap else 0) = extra
    by_cases h2 : hd + extra > ceilDiv tot cap
    · simp only [h2, ↓reduceIte]; omega
    · simp only [h2, ↓reduceIte]; omega
  · simp only [h1, ↓reduceIte]; omega

/-- `b2 ≤ boardCount π` (`ex1.py:L1086-L1100, L1204-L1206`) via `packLB_plan_sound` on `potB`! -/
theorem b2_le_boardCount {I : Instance} (G : IslandGraph I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (hcap : 0 < maxDynEffCap I s) :
    let cap := maxDynEffCap I s
    let ms (p : Fin I.numPkgs) := G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p))
    let bm (p : Fin I.numPkgs) := match s.pkgOnFerry p with | none => ms p | some _ => ms p - 1
    let bw := finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * bm p else 0)
    let bhd := finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then bm p else 0)
    max (ceilDiv bw cap) bhd ≤ boardCount π := by
  intro cap ms bm bw bhd
  -- Prove `bm p ≤ potB G s p` for all `p`!
  have hbm_le : ∀ p, bm p ≤ potB G s p := by
    intro p
    dsimp only [bm, potB, ms]
    cases hpf : s.pkgOnFerry p with
    | none => exact Nat.le_refl _
    | some f =>
      -- `p` is in some truck `t` aboard `f`, so `0 < I.ferryCap f`, `s.pkgPhysLoc p = s.ferryLoc f`, and `I.ferryServed f (s.ferryLoc f) = true`!
      cases hpl : s.pkgLoc p with
      | atLoc _ => simp [State.pkgOnFerry, hpl] at hpf
      | inTruck t =>
        cases htl : s.truckLoc t with
        | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hpf
        | onFerry f' =>
          simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hpf
          subst hpf
          have hpos_f : 0 < I.ferryCap f' := by
            have h := le_finSum (fun t'' => if s.truckLoc t'' = .onFerry f' then 1 else 0) t
            have h1 : 1 ≤ s.ferryCount f' := by simpa [State.ferryCount, htl] using h
            have := hv.aboard_le_cap f'; omega
          have hphys : s.pkgPhysLoc p = s.ferryLoc f' := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
          rw [hphys]
          have hle := minSails_le_ferryMinSails_add_one G f' (G.islandOf (I.pkgGoal p)) (s.ferryLoc f') hpos_f (hv.ferry_served f')
          simp only; omega
  -- Apply `packLB_plan_sound` to `isBoard` and `potB G` (with `min_hw = cap`, since we only need `ceilDiv bw cap` and `bhd`)!
  have hpack := packLB_plan_sound hv hp isBoard (potB G)
    (fun p _ => by
      have hg_p := hg p
      simp [potB, State.pkgOnFerry, State.pkgPhysLoc, hg_p, G.minSails_self])
    (fun {s1 s2 a} hv1 hstep => by
      cases hstep with
      | @board t f ht hcap_f =>
        refine ⟨fun h => by simp [isBoard] at h, fun _ => ⟨t, fun p _ => ?_⟩⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · simp only [hpl, ↓reduceIte]
          have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = some f := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hphys1 : s1.pkgPhysLoc p = s1.ferryLoc f := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          simp only [potB, hpf1, hpf2, hphys1]
          exact minSails_le_ferryMinSails_add_one G f (G.islandOf (I.pkgGoal p)) (s1.ferryLoc f) (by omega) (hv1.ferry_served f)
        · simp only [hpl, ↓reduceIte]
          have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' =>
              have hne : t' ≠ t := fun h => hpl (h ▸ hpl')
              simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne : t' ≠ t := fun h => hpl (h ▸ hpl')
              simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potB, hpf_eq, hph_eq]
      | @disembark t f ht =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isBoard] at h⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · have hpf1 : s1.pkgOnFerry p = some f := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hphys2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.ferryLoc f := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          simp only [potB, hpf1, hpf2, hphys2]
          exact ferryMinSails_le G f (G.islandOf (I.pkgGoal p)) (s1.ferryLoc f) (hv1.ferry_served f)
        · have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' =>
              have hne : t' ≠ t := fun h => hpl (h ▸ hpl')
              simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne : t' ≠ t := fun h => hpl (h ▸ hpl')
              simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potB, hpf_eq, hph_eq]
      | @drive t u v ht _ hroad =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isBoard] at h⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hph1 : s1.pkgPhysLoc p = u := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          have hph2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = v := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          simp [potB, hpf1, hpf2, hph1, hph2, G.road_same u v hroad]
        · have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potB, hpf_eq, hph_eq]
      | @load p0 t l ht hp0 _ =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isBoard] at h⟩
        by_cases hpp : p = p0
        · subst hpp; simp [potB, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
        · simp [potB, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp]
      | @unload p0 t l ht hp0 =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isBoard] at h⟩
        by_cases hpp : p = p0
        · subst hpp; simp [potB, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
        · simp [potB, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp]
      | @sail f u v hf _ _ =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isBoard] at h⟩
        cases hpl : s1.pkgLoc p with
        | atLoc l => simp [potB, State.pkgOnFerry, State.pkgPhysLoc, hpl]
        | inTruck t =>
          cases htl : s1.truckLoc t with
          | atLoc l => simp [potB, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
          | onFerry f' => simp [potB, State.pkgOnFerry, State.truckOnFerry, hpl, htl]
    ) cap hcap (dynEffCap_le_maxDynEffCap I s) 0 (fun _ _ _ _ => Nat.zero_le _)
  -- Extract `ceilDiv (sum w*potB) cap ≤ packLB ≤ boardCount` and `sum_{heavy} potB ≤ packLB ≤ boardCount`!
  have hbw_le : bw ≤ finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * potB G s p else 0) := by
    apply finSum_le_finSum; intro p
    cases s.pkgDelivered p <;> simp [Nat.mul_le_mul_left _ (hbm_le p)]
  have hbhd_le : bhd ≤ finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then potB G s p else 0) := by
    apply finSum_le_finSum; intro p
    cases s.pkgDelivered p <;> cases decide (I.pkgWeight p > cap / 2) <;> simp [hbm_le p]
  have hpack_ge : max (ceilDiv bw cap) bhd ≤
      packLB
        (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then potB G s p else 0))
        0
        (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p * potB G s p else 0))
        (finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * potB G s p else 0))
        cap :=
    max_ceilDiv_hd_le_packLB _ _ _ _ _ _ hbw_le hbhd_le
  exact Nat.le_trans hpack_ge hpack

/-- `d2 ≤ disembarkCount π` (`ex1.py:L1086-L1109, L1207-L1209`) via `packLB_plan_sound` on `potD`! -/
theorem d2_le_disembarkCount {I : Instance} (G : IslandGraph I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (hcap : 0 < maxDynEffCap I s) :
    let cap := maxDynEffCap I s
    let ms (p : Fin I.numPkgs) := G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p))
    let dm (p : Fin I.numPkgs) := match s.pkgOnFerry p with | none => ms p | some _ => max 1 (ms p)
    let dw := finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * dm p else 0)
    let dhd := finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then dm p else 0)
    max (ceilDiv dw cap) dhd ≤ disembarkCount π := by
  intro cap ms dm dw dhd
  have hdm_le : ∀ p, dm p ≤ potD G s p := by
    intro p
    dsimp only [dm, potD, ms]
    cases hpf : s.pkgOnFerry p with
    | none => exact Nat.le_refl _
    | some f =>
      cases hpl : s.pkgLoc p with
      | atLoc _ => simp [State.pkgOnFerry, hpl] at hpf
      | inTruck t =>
        cases htl : s.truckLoc t with
        | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hpf
        | onFerry f' =>
          simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hpf
          subst hpf
          have hpos_f : 0 < I.ferryCap f' := by
            have h := le_finSum (fun t'' => if s.truckLoc t'' = .onFerry f' then 1 else 0) t
            have h1 : 1 ≤ s.ferryCount f' := by simpa [State.ferryCount, htl] using h
            have := hv.aboard_le_cap f'; omega
          have hphys : s.pkgPhysLoc p = s.ferryLoc f' := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
          rw [hphys]
          have hle := minSails_le_ferryMinSails_add_one G f' (G.islandOf (I.pkgGoal p)) (s.ferryLoc f') hpos_f (hv.ferry_served f')
          simp only; omega
  have hpack := packLB_plan_sound hv hp isDisembark (potD G)
    (fun p _ => by
      have hg_p := hg p
      simp [potD, State.pkgOnFerry, State.pkgPhysLoc, hg_p, G.minSails_self])
    (fun {s1 s2 a} hv1 hstep => by
      cases hstep with
      | @disembark t f ht =>
        refine ⟨fun h => by simp [isDisembark] at h, fun _ => ⟨t, fun p _ => ?_⟩⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · simp only [hpl, ↓reduceIte]
          have hpf1 : s1.pkgOnFerry p = some f := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hphys2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.ferryLoc f := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          simp only [potD, hpf1, hpf2, hphys2]
          have hle := ferryMinSails_le G f (G.islandOf (I.pkgGoal p)) (s1.ferryLoc f) (hv1.ferry_served f)
          omega
        · simp only [hpl, ↓reduceIte]
          have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potD, hpf_eq, hph_eq]
      | @board t f ht hcap_f =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isDisembark] at h⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = some f := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hphys1 : s1.pkgPhysLoc p = s1.ferryLoc f := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          simp only [potD, hpf1, hpf2, hphys1]
          have hle := minSails_le_ferryMinSails_add_one G f (G.islandOf (I.pkgGoal p)) (s1.ferryLoc f) (by omega) (hv1.ferry_served f)
          omega
        · have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potD, hpf_eq, hph_eq]
      | @drive t u v ht _ hroad =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isDisembark] at h⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hph1 : s1.pkgPhysLoc p = u := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          have hph2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = v := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          simp [potD, hpf1, hpf2, hph1, hph2, G.road_same u v hroad]
        · have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' => have hne : t' ≠ t := fun h => hpl (h ▸ hpl'); simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
          simp [potD, hpf_eq, hph_eq]
      | @load p0 t l ht hp0 _ =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isDisembark] at h⟩
        by_cases hpp : p = p0
        · subst hpp; simp [potD, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
        · simp [potD, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp]
      | @unload p0 t l ht hp0 =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isDisembark] at h⟩
        by_cases hpp : p = p0
        · subst hpp; simp [potD, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
        · simp [potD, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp]
      | @sail f u v hf _ _ =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isDisembark] at h⟩
        cases hpl : s1.pkgLoc p with
        | atLoc l => simp [potD, State.pkgOnFerry, State.pkgPhysLoc, hpl]
        | inTruck t =>
          cases htl : s1.truckLoc t with
          | atLoc l => simp [potD, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
          | onFerry f' => simp [potD, State.pkgOnFerry, State.truckOnFerry, hpl, htl]
    ) cap hcap (dynEffCap_le_maxDynEffCap I s) 0 (fun _ _ _ _ => Nat.zero_le _)
  have hdw_le : dw ≤ finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * potD G s p else 0) := by
    apply finSum_le_finSum; intro p
    cases s.pkgDelivered p <;> simp [Nat.mul_le_mul_left _ (hdm_le p)]
  have hdhd_le : dhd ≤ finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then potD G s p else 0) := by
    apply finSum_le_finSum; intro p
    cases s.pkgDelivered p <;> cases decide (I.pkgWeight p > cap / 2) <;> simp [hdm_le p]
  have hpack_ge : max (ceilDiv dw cap) dhd ≤
      packLB
        (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then potD G s p else 0))
        0
        (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p * potD G s p else 0))
        (finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * potD G s p else 0))
        cap :=
    max_ceilDiv_hd_le_packLB _ _ _ _ _ _ hdw_le hdhd_le
  exact Nat.le_trans hpack_ge hpack

-- ==============================================================================
-- 6. LOADED INTER-ISLAND SAILS, `b4`, `b5`, EMPTY POSITIONING `+1`, `b3`, `sum_req_i`
-- ==============================================================================

/-- Predicate matching an inter-island `SAIL` action (`islandOf u ≠ islandOf v`). -/
def isInterSail {I : Instance} (G : IslandGraph I) : Action I → Bool
  | .sail _ u v => decide (G.islandOf u ≠ G.islandOf v)
  | _           => false

/-- Count of LOADED inter-island sails (≥ 1 truck aboard the sailing ferry). -/
def loadedInterSailCount {I : Instance} (G : IslandGraph I) : State I → Plan I → Nat
  | _, [] => 0
  | s, a :: rest =>
      (match a with
       | .sail f u v => if G.islandOf u ≠ G.islandOf v ∧ 0 < s.ferryCount f then 1 else 0
       | _ => 0) + loadedInterSailCount G (applyAction s a) rest

theorem loadedInterSailCount_le_sailCount {I : Instance} (G : IslandGraph I) (s : State I) (π : Plan I) :
    loadedInterSailCount G s π ≤ sailCount π := by
  unfold sailCount
  induction π generalizing s with
  | nil => simp [loadedInterSailCount]
  | cons a rest ih =>
    simp only [loadedInterSailCount, List.map_cons, List.sum_cons]
    have hrec := ih (applyAction s a)
    cases a with
    | sail f u v =>
      by_cases h : G.islandOf u ≠ G.islandOf v ∧ 0 < s.ferryCount f <;> simp [h] <;> omega
    | _ => simp; exact hrec

/-- Empty-positioning `+1` theorem (`ex1.py:L1236-L1238`):
    If `1 ≤ loadedInterSailCount G s π`, NO truck starts aboard a ferry (`n_ab = 0`),
    and NO active ferry starts on any island containing a truck,
    then some empty `SAIL` must occur BEFORE the first loaded inter-island sail,
    so `loadedInterSailCount G s π + 1 ≤ sailCount π`! -/
theorem empty_positioning_extra_sail {I : Instance} (G : IslandGraph I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (hnab0 : ∀ t, s.truckOnFerry t = none)
    (hno_co : ∀ f t, 0 < I.ferryCap f → G.islandOf (s.ferryLoc f) ≠ G.islandOf (s.truckPhysLoc t))
    (hpos : 1 ≤ loadedInterSailCount G s π) :
    loadedInterSailCount G s π + 1 ≤ sailCount π := by
  induction hp with
  | nil => simp [loadedInterSailCount] at hpos
  | @cons sa sb _ a rest hstep hrest ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    -- In `sa`, `ferryCount f = 0` for every ferry `f`!
    have hfc0 : ∀ f, sa.ferryCount f = 0 := by
      intro f; unfold State.ferryCount
      have hz : (fun t => if sa.truckLoc t = .onFerry f then 1 else 0) = (fun _ => 0) := by
        funext t; have h := hnab0 t
        cases htl : sa.truckLoc t with
        | atLoc _ => simp
        | onFerry _ => simp [State.truckOnFerry, htl] at h
      rw [hz, finSum_zero]
    simp only [loadedInterSailCount, sailCount, List.map_cons, List.sum_cons, ← hsb_eq] at hpos ⊢
    cases hstep with
    | @sail f u v hf _ _ =>
      simp only [hfc0 f, Nat.lt_irrefl, and_false, ↓reduceIte, Nat.zero_add] at hpos ⊢
      have := loadedInterSailCount_le_sailCount G { sa with ferryLoc := updateFn sa.ferryLoc f v } rest
      unfold sailCount at this; omega
    | @board t f ht hcap_f =>
      exfalso
      have hphys : sa.truckPhysLoc t = sa.ferryLoc f := by simp [State.truckPhysLoc, ht]
      exact hno_co f t (by omega) (by rw [hphys])
    | @disembark t f ht =>
      exfalso; have h := hnab0 t; simp [State.truckOnFerry, ht] at h
    | @drive t u v ht hne hroad =>
      simp only [Nat.zero_add] at hpos ⊢
      have hnab_b : ∀ t', ({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc v) } : State I).truckOnFerry t' = none := by
        intro t'; by_cases h : t' = t
        · subst h; simp [State.truckOnFerry, updateFn]
        · simp only [State.truckOnFerry, updateFn, h, ↓reduceIte]
          exact hnab0 t'
      have hno_b : ∀ f t', 0 < I.ferryCap f →
          G.islandOf (({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc v) } : State I).ferryLoc f) ≠
          G.islandOf (({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc v) } : State I).truckPhysLoc t') := by
        intro f t' hcf
        by_cases h : t' = t
        · subst h
          have h1 := hno_co f t' hcf
          have hp1 : sa.truckPhysLoc t' = u := by simp [State.truckPhysLoc, ht]
          have hp2 : ({ sa with truckLoc := updateFn sa.truckLoc t' (.atLoc v) } : State I).truckPhysLoc t' = v := by
            simp [State.truckPhysLoc, updateFn]
          intro heq; apply h1
          rw [hp1, G.road_same u v hroad, ← hp2]; exact heq
        · have hp_eq : ({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc v) } : State I).truckPhysLoc t' = sa.truckPhysLoc t' := by
            simp [State.truckPhysLoc, updateFn, h]
          intro heq
          dsimp only at heq
          rw [hp_eq] at heq
          exact hno_co f t' hcf heq
      have hrec := ih (validState_step hv (Step.drive ht hne hroad)) hnab_b hno_b hpos
      unfold sailCount at hrec; exact hrec
    | @load p t l ht hp0 hcap0 =>
      simp only [Nat.zero_add] at hpos ⊢
      have hrec := ih (validState_step hv (Step.load ht hp0 hcap0)) hnab0 hno_co hpos
      unfold sailCount at hrec; exact hrec
    | @unload p t l ht hp0 =>
      simp only [Nat.zero_add] at hpos ⊢
      have hrec := ih (validState_step hv (Step.unload ht hp0)) hnab0 hno_co hpos
      unfold sailCount at hrec; exact hrec

/-- `b5` (total sail weight + heavy sail hops `h_sw / kh`) lower-bounds `loadedInterSailCount G s π` (`ex1.py:L1226-L1231`)! -/
theorem b5_le_loadedInterSailCount {I : Instance} (G : IslandGraph I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (max_gfw : Nat) (h_gfw : ∀ f u v, 0 < I.ferryCap f →
      I.ferryServed f u = true → I.ferryServed f v = true →
      G.islandOf u ≠ G.islandOf v → maxFerryWeight I s f ≤ max_gfw)
    (min_hsw : Nat)
    (h_min_hsw : ∀ p, s.pkgDelivered p = false → I.pkgWeight p > maxDynEffCap I s / 2 →
      0 < G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) → min_hsw ≤ I.pkgWeight p) :
    let cap := maxDynEffCap I s
    let ms (p : Fin I.numPkgs) := G.minSails (G.islandOf (s.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p))
    let tot_sw := finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * ms p else 0)
    let h_sw := finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then ms p else 0)
    let cap_h := finSum (fun t => if dynEffCap I s t ≥ min_hsw then 1 else 0)
    let kh := min G.maxInterFerryCap cap_h
    (if 0 < max_gfw then ceilDiv tot_sw max_gfw else 0) ≤ loadedInterSailCount G s π ∧
    (if 0 < kh then ceilDiv h_sw kh else 0) ≤ loadedInterSailCount G s π := by
  intro cap ms tot_sw h_sw cap_h kh
  -- Prove simultaneously by induction on `hp` that for EVERY intermediate valid state `sa` along `π`:
  --   `tot_sw(sa) ≤ max_gfw * loadedInterSailCount G sa rest` AND
  --   `h_sw(sa)   ≤ kh * loadedInterSailCount G sa rest`!
  -- Wait: for `h_sw(sa)`, we ONLY count heavy packages with `I.pkgWeight p ≥ min_hsw`!
  let heavyOk (p : Fin I.numPkgs) : Bool :=
    !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) && decide (min_hsw ≤ I.pkgWeight p)
  have hmain : ∀ {sa s_end : State I} {ps : Plan I},
      ValidState I sa → ValidPlan I sa ps s_end → goalTest I s_end →
      finSum (fun p => if !s.pkgDelivered p then
        I.pkgWeight p * G.minSails (G.islandOf (sa.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) ≤
        max_gfw * loadedInterSailCount G sa ps ∧
      finSum (fun p => if heavyOk p then
        G.minSails (G.islandOf (sa.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) ≤
        kh * loadedInterSailCount G sa ps := by
    intro sa s_end ps hva hpa hga
    induction hpa with
    | @nil s_nil =>
      have hz1 : (fun p => if !s.pkgDelivered p then
          I.pkgWeight p * G.minSails (G.islandOf (s_nil.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) = (fun _ => 0) := by
        funext p; have hgp : s_nil.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hga p]
        cases hdel : s.pkgDelivered p <;> simp [hdel, hgp, G.minSails_self]
      have hz2 : (fun p => if heavyOk p then
          G.minSails (G.islandOf (s_nil.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) = (fun _ => 0) := by
        funext p; have hgp : s_nil.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hga p]
        cases hh : heavyOk p <;> simp [hh, hgp, G.minSails_self]
      rw [hz1, hz2, finSum_zero]; exact ⟨Nat.zero_le _, Nat.zero_le _⟩
    | @cons s1 s2 _ a rest hstep _ ih =>
      have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
      have ⟨ih1, ih2⟩ := ih (validState_step hva hstep) hga
      -- On any step OTHER than a loaded inter-island sail, `G.islandOf (pkgPhysLoc p)` is unchanged!
      cases hstep with
      | @sail f u v hf hne hserved =>
        let s2' : State I := { s1 with ferryLoc := updateFn s1.ferryLoc f v }
        simp only [loadedInterSailCount, ← hs2_eq]
        by_cases hinter : G.islandOf u ≠ G.islandOf v ∧ 0 < s1.ferryCount f
        · simp only [hinter, ↓reduceIte, Nat.mul_add, Nat.mul_one]
          have hpos_f : 0 < I.ferryCap f := by have := hva.aboard_le_cap f; omega
          have hu_sv : I.ferryServed f u = true := hf ▸ hva.ferry_served f
          have hmf_le : maxFerryWeight I s f ≤ max_gfw := h_gfw f u v hpos_f hu_sv hserved hinter.1
          -- 1. Weight drop ≤ `maxFerryWeight I s f ≤ max_gfw`!
          have hdrop_w :
              finSum (fun p => if !s.pkgDelivered p then
                I.pkgWeight p * G.minSails (G.islandOf (s1.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) ≤
              finSum (fun p => if !s.pkgDelivered p && decide (s1.pkgOnFerry p = some f) then I.pkgWeight p else 0) +
              finSum (fun p => if !s.pkgDelivered p then
                I.pkgWeight p * G.minSails (G.islandOf (s2'.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) := by
            rw [← finSum_add]; apply finSum_le_finSum; intro p
            cases hdel : s.pkgDelivered p with
            | true => simp
            | false =>
              simp only [Bool.not_false, Bool.true_and, ↓reduceIte]
              by_cases hon : s1.pkgOnFerry p = some f
              · simp only [hon, decide_true, ↓reduceIte]
                have hp1 : s1.pkgPhysLoc p = u := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl] at hon
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hon
                    | onFerry f' =>
                      simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hon
                      subst hon; simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, hf]
                have hp2 : s2'.pkgPhysLoc p = v := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl] at hon
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hon
                    | onFerry f' =>
                      simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hon
                      subst hon; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn]
                have htri := G.minSails_tri (G.islandOf u) (G.islandOf v) (G.islandOf (I.pkgGoal p))
                have h1 := G.minSails_ferry f u v hpos_f hu_sv hserved
                rw [hp1, hp2]
                have hle_d : G.minSails (G.islandOf u) (G.islandOf (I.pkgGoal p)) ≤
                             1 + G.minSails (G.islandOf v) (G.islandOf (I.pkgGoal p)) := by omega
                have hmul := Nat.mul_le_mul_left (I.pkgWeight p) hle_d
                rw [Nat.mul_add, Nat.mul_one] at hmul; exact hmul
              · have hsame : s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [s2', State.pkgPhysLoc, hpl]
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
                    | onFerry f' =>
                      have hne_f : f' ≠ f := by intro h; subst h; exact hon (by simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl])
                      simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn, hne_f]
                simp [hon, hsame]
          have hload_f : finSum (fun p => if !s.pkgDelivered p && decide (s1.pkgOnFerry p = some f) then I.pkgWeight p else 0) ≤
                         maxFerryWeight I s f := by
            have hle_t : finSum (fun p => if !s.pkgDelivered p && decide (s1.pkgOnFerry p = some f) then I.pkgWeight p else 0) ≤
                finSum (fun t => if decide (s1.truckLoc t = .onFerry f) = true then dynEffCap I s t else 0) := by
              have hrew : finSum (fun p => if !s.pkgDelivered p && decide (s1.pkgOnFerry p = some f) then I.pkgWeight p else 0) ≤
                  finSum (fun t => finSum (fun p => if s1.truckLoc t = .onFerry f then
                    if !s.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0)) := by
                rw [finSum_comm]; apply finSum_le_finSum; intro p
                cases s.pkgDelivered p with
                | true => simp
                | false =>
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl]
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl]
                    | onFerry f' =>
                      by_cases hff : f' = f
                      · subst hff
                        have hle := le_finSum (fun t' => if s1.truckLoc t' = .onFerry f' then
                          if (!false && decide (PkgPos.inTruck t = PkgPos.inTruck t')) = true then I.pkgWeight p else 0 else 0) t
                        simpa [State.pkgOnFerry, State.truckOnFerry, hpl, htl] using hle
                      · simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl, hff]
              apply Nat.le_trans hrew
              apply finSum_le_finSum; intro t
              by_cases ht : s1.truckLoc t = .onFerry f
              · simp only [ht, decide_true, ↓reduceIte]
                have hcap_t : subsetWeight I.pkgWeight (fun p => !s.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t)) ≤ I.truckCap t := by
                  apply Nat.le_trans _ (hva.load_le_cap t); unfold subsetWeight State.truckLoad; apply finSum_le_finSum
                  intro p; cases hdel : s.pkgDelivered p <;> by_cases h : s1.pkgLoc p = .inTruck t <;> simp [hdel, h]
                exact subsetWeight_undeliv_le_dynEffCap I s t _ (fun p hp => by simp only [Bool.and_eq_true, Bool.not_eq_true'] at hp; exact hp.1) hcap_t
              · have hz : (fun p => if s1.truckLoc t = .onFerry f then
                    if !s.pkgDelivered p && decide (s1.pkgLoc p = .inTruck t) then I.pkgWeight p else 0 else 0) = (fun _ => 0) := by
                  funext p; simp [ht]
                rw [hz, finSum_zero]; exact Nat.zero_le _
            exact Nat.le_trans hle_t (ferryAboard_dynEffCap_le_maxFerryWeight I s s1 f hva)
          -- 2. Heavy package count drop ≤ `kh = min maxInterFerryCap cap_h`!
          have hdrop_h :
              finSum (fun p => if heavyOk p then G.minSails (G.islandOf (s1.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) ≤
              finSum (fun p => if heavyOk p && decide (s1.pkgOnFerry p = some f) then 1 else 0) +
              finSum (fun p => if heavyOk p then G.minSails (G.islandOf (s2'.pkgPhysLoc p)) (G.islandOf (I.pkgGoal p)) else 0) := by
            rw [← finSum_add]; apply finSum_le_finSum; intro p
            cases hhok : heavyOk p with
            | false => simp
            | true =>
              simp only [Bool.true_and, ↓reduceIte]
              by_cases hon : s1.pkgOnFerry p = some f
              · simp only [hon, decide_true, ↓reduceIte]
                have hp1 : s1.pkgPhysLoc p = u := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl] at hon
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hon
                    | onFerry f' =>
                      simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hon
                      subst hon; simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, hf]
                have hp2 : s2'.pkgPhysLoc p = v := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl] at hon
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl] at hon
                    | onFerry f' =>
                      simp only [State.pkgOnFerry, State.truckOnFerry, hpl, htl, Option.some.injEq] at hon
                      subst hon; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn]
                have htri := G.minSails_tri (G.islandOf u) (G.islandOf v) (G.islandOf (I.pkgGoal p))
                have h1 := G.minSails_ferry f u v hpos_f hu_sv hserved
                rw [hp1, hp2]; omega
              · have hsame : s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [s2', State.pkgPhysLoc, hpl]
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
                    | onFerry f' =>
                      have hne_f : f' ≠ f := by intro h; subst h; exact hon (by simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl])
                      simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn, hne_f]
                simp [hon, hsame]
          -- Each truck aboard `f` holds ≤ 1 heavy package, AND if it holds a `heavyOk` package, `dynEffCap I s t ≥ min_hsw`!
          have hheavy_le_kh : finSum (fun p => if heavyOk p && decide (s1.pkgOnFerry p = some f) then 1 else 0) ≤ kh := by
            have hle_t : finSum (fun p => if heavyOk p && decide (s1.pkgOnFerry p = some f) then 1 else 0) ≤
                finSum (fun t => if s1.truckLoc t = .onFerry f ∧ dynEffCap I s t ≥ min_hsw then 1 else 0) := by
              have hrew : finSum (fun p => if heavyOk p && decide (s1.pkgOnFerry p = some f) then 1 else 0) ≤
                  finSum (fun t => finSum (fun p => if s1.truckLoc t = .onFerry f then
                    if heavyOk p && decide (s1.pkgLoc p = .inTruck t) then 1 else 0 else 0)) := by
                rw [finSum_comm]; apply finSum_le_finSum; intro p
                cases hhok : heavyOk p with
                | false => simp
                | true =>
                  cases hpl : s1.pkgLoc p with
                  | atLoc _ => simp [State.pkgOnFerry, hpl]
                  | inTruck t =>
                    cases htl : s1.truckLoc t with
                    | atLoc _ => simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl]
                    | onFerry f' =>
                      by_cases hff : f' = f
                      · subst hff
                        have hle := le_finSum (fun t' => if s1.truckLoc t' = .onFerry f' then
                          if (true && decide (PkgPos.inTruck t = PkgPos.inTruck t')) = true then 1 else 0 else 0) t
                        simpa [State.pkgOnFerry, State.truckOnFerry, hpl, htl] using hle
                      · simp [State.pkgOnFerry, State.truckOnFerry, hpl, htl, hff]
              apply Nat.le_trans hrew
              apply finSum_le_finSum; intro t
              by_cases ht : s1.truckLoc t = .onFerry f
              · simp only [ht, ↓reduceIte]
                by_cases hex_h : ∃ p, heavyOk p = true ∧ s1.pkgLoc p = .inTruck t
                · rcases hex_h with ⟨p0, hp0_ok, hp0_in⟩
                  have hp0_c : s.pkgDelivered p0 = false ∧ I.pkgWeight p0 > cap / 2 ∧ min_hsw ≤ I.pkgWeight p0 := by
                    simp only [heavyOk, Bool.and_eq_true, Bool.not_eq_true', decide_eq_true_eq] at hp0_ok
                    exact ⟨hp0_ok.1.1, hp0_ok.1.2, hp0_ok.2⟩
                  have hdyn_ge : dynEffCap I s t ≥ min_hsw := by
                    have h1 : subsetWeight I.pkgWeight (fun p => decide (p = p0)) = I.pkgWeight p0 := by
                      unfold subsetWeight
                      have hfn : (fun p => if decide (p = p0) = true then I.pkgWeight p else 0) =
                                 (fun p => if p = p0 then I.pkgWeight p0 else 0) := by
                        funext p; by_cases h : p = p0 <;> simp [h]
                      rw [hfn, finSum_ite_eq]
                    have hle_cap : subsetWeight I.pkgWeight (fun p => decide (p = p0)) ≤ I.truckCap t := by
                      rw [h1]
                      have h2 := le_finSum (fun p => if s1.pkgLoc p = .inTruck t then I.pkgWeight p else 0) p0
                      simp only [hp0_in, ↓reduceIte] at h2
                      have := hva.load_le_cap t; unfold State.truckLoad at this; omega
                    have hle_dyn := subsetWeight_undeliv_le_dynEffCap I s t (fun p => decide (p = p0))
                      (fun p hp => by simp only [decide_eq_true_eq] at hp; subst hp; exact hp0_c.1) hle_cap
                    omega
                  simp only [true_and, hdyn_ge, ↓reduceIte]
                  have hdyn_le_cap : finSum (fun p => if heavyOk p && decide (s1.pkgLoc p = .inTruck t) then I.pkgWeight p else 0) ≤ cap := by
                    apply Nat.le_trans _ (dynEffCap_le_maxDynEffCap I s t)
                    have hcap_t : subsetWeight I.pkgWeight (fun p => heavyOk p && decide (s1.pkgLoc p = .inTruck t)) ≤ I.truckCap t := by
                      apply Nat.le_trans _ (hva.load_le_cap t); unfold subsetWeight State.truckLoad; apply finSum_le_finSum
                      intro p; cases hh : heavyOk p <;> by_cases h : s1.pkgLoc p = .inTruck t <;> simp [hh, h]
                    exact subsetWeight_undeliv_le_dynEffCap I s t _
                      (fun p hp => by simp only [heavyOk, Bool.and_eq_true, Bool.not_eq_true'] at hp; exact hp.1.1.1)
                      hcap_t
                  have h1h := at_most_one_heavy I.pkgWeight (fun p => heavyOk p && decide (s1.pkgLoc p = .inTruck t)) cap hdyn_le_cap
                  have hfn_eq : (fun p => if heavyOk p && decide (s1.pkgLoc p = .inTruck t) then 1 else 0) =
                                (fun p => if (heavyOk p && decide (s1.pkgLoc p = .inTruck t)) && decide (I.pkgWeight p > cap / 2) then 1 else 0) := by
                    funext p; cases hh : heavyOk p with
                    | false => simp
                    | true =>
                      have hw : I.pkgWeight p > cap / 2 := by
                        simp only [heavyOk, Bool.and_eq_true, decide_eq_true_eq] at hh; exact hh.1.2
                      simp [hw]
                  rw [hfn_eq]; exact h1h
                · have hz : (fun p => if heavyOk p && decide (s1.pkgLoc p = .inTruck t) then 1 else 0) = (fun _ => 0) := by
                    funext p; by_cases hc : heavyOk p = true ∧ s1.pkgLoc p = .inTruck t
                    · exact absurd ⟨p, hc.1, hc.2⟩ hex_h
                    · have hf' : (heavyOk p && decide (s1.pkgLoc p = .inTruck t)) = false := by
                        cases h1 : heavyOk p <;> by_cases h2 : s1.pkgLoc p = .inTruck t <;> simp_all
                      simp [hf']
                  rw [hz, finSum_zero]; exact Nat.zero_le _
              · have hz : (fun p => if s1.truckLoc t = .onFerry f then
                    if heavyOk p && decide (s1.pkgLoc p = .inTruck t) then 1 else 0 else 0) = (fun _ => 0) := by
                  funext p; simp [ht]
                rw [hz, finSum_zero]; exact Nat.zero_le _
            apply Nat.le_trans hle_t
            apply Nat.le_min.mpr
            constructor
            · apply Nat.le_trans _ (G.maxInterFerryCap_ge f u v hpos_f hu_sv hserved hinter.1)
              apply Nat.le_trans _ (hva.aboard_le_cap f)
              unfold State.ferryCount; apply finSum_le_finSum
              intro t; by_cases h1 : s1.truckLoc t = .onFerry f <;> by_cases h2 : dynEffCap I s t ≥ min_hsw <;> simp [h1, h2]
            · apply finSum_le_finSum
              intro t; by_cases h1 : s1.truckLoc t = .onFerry f <;> by_cases h2 : dynEffCap I s t ≥ min_hsw <;> simp [h1, h2]
          dsimp only [s2'] at hdrop_w hdrop_h
          have hne_i : G.islandOf u ≠ G.islandOf v := hinter.1
          exact ⟨by
            have h1 := Nat.le_trans hdrop_w (Nat.add_le_add (Nat.le_trans hload_f hmf_le) ih1)
            simpa [hne_i, Nat.mul_one] using h1,
            by
            have h2 := Nat.le_trans hdrop_h (Nat.add_le_add hheavy_le_kh ih2)
            simpa [hne_i, Nat.mul_one] using h2⟩
        · simp only [hinter, ↓reduceIte, Nat.zero_add]
          have hisl_same : ∀ p, G.islandOf (s2'.pkgPhysLoc p) = G.islandOf (s1.pkgPhysLoc p) := by
            intro p
            cases hpl : s1.pkgLoc p with
            | atLoc _ => simp [s2', State.pkgPhysLoc, hpl]
            | inTruck t =>
              cases htl : s1.truckLoc t with
              | atLoc _ => simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
              | onFerry f' =>
                by_cases hff : f' = f
                · subst hff
                  have hpos_fc : 0 < s1.ferryCount f' := by
                    have h := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f' then 1 else 0) t
                    unfold State.ferryCount; simp only [htl, ↓reduceIte] at h; omega
                  have heq_isl : G.islandOf u = G.islandOf v := by
                    by_cases hne_i : G.islandOf u = G.islandOf v
                    · exact hne_i
                    · exact absurd ⟨hne_i, hpos_fc⟩ hinter
                  simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn, hf, heq_isl]
                · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, htl, updateFn, hff]
          dsimp only [s2'] at hisl_same
          simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
      | @drive t u v ht _ hroad =>
        let s2' : State I := { s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) }
        have hisl_same : ∀ p, G.islandOf (s2'.pkgPhysLoc p) = G.islandOf (s1.pkgPhysLoc p) := by
          intro p
          by_cases hpl : s1.pkgLoc p = .inTruck t
          · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn, ht, G.road_same u v hroad]
          · cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [s2', State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne : t' ≠ t := fun h => hpl (h ▸ hpl')
              simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne]
        simp only [loadedInterSailCount, ← hs2_eq, Nat.zero_add]
        dsimp only [s2'] at hisl_same
        simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
      | @load p0 t l ht hp0 _ =>
        let s2' : State I := { s1 with pkgLoc := updateFn s1.pkgLoc p0 (.inTruck t) }
        have hisl_same : ∀ p, s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
          intro p; by_cases h : p = p0
          · subst h; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
          · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, updateFn, h]
        simp only [loadedInterSailCount, ← hs2_eq, Nat.zero_add]
        dsimp only [s2'] at hisl_same
        simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
      | @unload p0 t l ht hp0 =>
        let s2' : State I := { s1 with pkgLoc := updateFn s1.pkgLoc p0 (.atLoc l) }
        have hisl_same : ∀ p, s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
          intro p; by_cases h : p = p0
          · subst h; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht, hp0]
          · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, updateFn, h]
        simp only [loadedInterSailCount, ← hs2_eq, Nat.zero_add]
        dsimp only [s2'] at hisl_same
        simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
      | @board t f ht _ =>
        let s2' : State I := { s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) }
        have hisl_same : ∀ p, s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
          intro p; cases hpl : s1.pkgLoc p with
          | atLoc _ => simp [s2', State.pkgPhysLoc, hpl]
          | inTruck t' =>
            by_cases h : t' = t
            · subst h; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn, ht]
            · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn, h]
        simp only [loadedInterSailCount, ← hs2_eq, Nat.zero_add]
        dsimp only [s2'] at hisl_same
        simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
      | @disembark t f ht =>
        let s2' : State I := { s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) }
        have hisl_same : ∀ p, s2'.pkgPhysLoc p = s1.pkgPhysLoc p := by
          intro p; cases hpl : s1.pkgLoc p with
          | atLoc _ => simp [s2', State.pkgPhysLoc, hpl]
          | inTruck t' =>
            by_cases h : t' = t
            · subst h; simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn, ht]
            · simp [s2', State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn, h]
        simp only [loadedInterSailCount, ← hs2_eq, Nat.zero_add]
        dsimp only [s2'] at hisl_same
        simp only [hisl_same] at ih1 ih2; exact ⟨ih1, ih2⟩
  have ⟨hm1, hm2⟩ := hmain hv hp hg
  -- Connect `h_sw` to `heavyOk`: every term with `ms p > 0` satisfies `min_hsw ≤ I.pkgWeight p`!
  have hh_eq : h_sw = finSum (fun p => if heavyOk p then ms p else 0) := by
    dsimp only [h_sw]
    congr 1; funext p
    cases hdel : s.pkgDelivered p with
    | true => simp [heavyOk, hdel]
    | false =>
      cases hw : decide (I.pkgWeight p > cap / 2) with
      | false => simp [heavyOk, hdel, hw]
      | true =>
        by_cases hms : 0 < ms p
        · have hmin := h_min_hsw p hdel (of_decide_eq_true hw) hms
          simp [heavyOk, hdel, hw, hmin]
        · have hm0 : ms p = 0 := by omega
          simp [hm0]
  constructor
  · by_cases hpos : 0 < max_gfw
    · simp only [hpos, ↓reduceIte]
      exact ceilDiv_le_of_le_mul hpos (by rw [Nat.mul_comm]; exact hm1)
    · simp [hpos]
  · by_cases hpos : 0 < kh
    · simp only [hpos, ↓reduceIte]
      rw [hh_eq]
      exact ceilDiv_le_of_le_mul hpos (by rw [Nat.mul_comm]; exact hm2)
    · simp [hpos]

/-- Single-step indicator for a loaded inter-island sail. -/
def stepLoadedInterSail {I : Instance} (G : IslandGraph I) (s : State I) : Action I → Nat
  | .sail f u v => if G.islandOf u ≠ G.islandOf v ∧ 0 < s.ferryCount f then 1 else 0
  | _           => 0

/-- `b4` (single-package inter-island approach + delivery) lower-bounds `loadedInterSailCount G s π` (`ex1.py:L1115-L1124`)! -/
theorem b4_le_loadedInterSailCount {I : Instance} (G : IslandGraph I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (hnd : s.pkgDelivered p = false) :
    (∀ t, s.pkgLoc p = .inTruck t →
      G.minSails (G.islandOf (s.truckPhysLoc t)) (G.islandOf (I.pkgGoal p)) ≤ loadedInterSailCount G s π) ∧
    (∀ l, s.pkgLoc p = .atLoc l →
      ∀ mps : Nat, (∀ t, I.pkgWeight p ≤ I.truckCap t → mps ≤ G.minSails (G.islandOf (s.truckPhysLoc t)) (G.islandOf l)) →
      mps + G.minSails (G.islandOf l) (G.islandOf (I.pkgGoal p)) ≤ loadedInterSailCount G s π) := by
  -- Helper 1: distance moved by a single truck `t` in `minSails` ≤ `loadedInterSailCount`!
  have htruck_move : ∀ {sa sb : State I} {ps : Plan I} (hva : ValidState I sa) (hpa : ValidPlan I sa ps sb) (t : Fin I.numTrucks),
      G.minSails (G.islandOf (sa.truckPhysLoc t)) (G.islandOf (sb.truckPhysLoc t)) ≤ loadedInterSailCount G sa ps := by
    intro sa sb ps hva hpa t
    induction hpa with
    | nil => simp [G.minSails_self]
    | @cons s1 s2 s_last a rest hstep _ ih =>
      have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
      have hrec := ih (validState_step hva hstep)
      have htri := G.minSails_tri (G.islandOf (s1.truckPhysLoc t)) (G.islandOf (s2.truckPhysLoc t)) (G.islandOf (s_last.truckPhysLoc t))
      have h1step : G.minSails (G.islandOf (s1.truckPhysLoc t)) (G.islandOf (s2.truckPhysLoc t)) ≤
          stepLoadedInterSail G s1 a := by
        cases hstep with
        | @sail f u v hf _ hserved =>
          cases htl : s1.truckLoc t with
          | atLoc _ =>
            have hsame : ({ s1 with ferryLoc := updateFn s1.ferryLoc f v } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
              simp [State.truckPhysLoc, htl]
            rw [hsame, G.minSails_self]; exact Nat.zero_le _
          | onFerry f' =>
            by_cases hff : f' = f
            · subst hff
              have hpos_fc : 0 < s1.ferryCount f' := by
                have h := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f' then 1 else 0) t
                unfold State.ferryCount; simp only [htl, ↓reduceIte] at h; omega
              have hpos_f : 0 < I.ferryCap f' := by have := hva.aboard_le_cap f'; omega
              have hp1 : s1.truckPhysLoc t = u := by simp [State.truckPhysLoc, htl, hf]
              have hp2 : ({ s1 with ferryLoc := updateFn s1.ferryLoc f' v } : State I).truckPhysLoc t = v := by
                simp [State.truckPhysLoc, htl, updateFn]
              rw [hp1, hp2]
              by_cases hne_i : G.islandOf u ≠ G.islandOf v
              · rw [show stepLoadedInterSail G s1 (.sail f' u v) = 1 from by
                  unfold stepLoadedInterSail; exact ite_eq_left_iff.mpr (fun h => absurd ⟨hne_i, hpos_fc⟩ h)]
                exact G.minSails_ferry f' u v hpos_f (hf ▸ hva.ferry_served f') hserved
              · have heq_i : G.islandOf u = G.islandOf v := Classical.byContradiction hne_i
                rw [heq_i, G.minSails_self]; exact Nat.zero_le _
            · have hsame : ({ s1 with ferryLoc := updateFn s1.ferryLoc f v } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
                simp [State.truckPhysLoc, htl, updateFn, hff]
              rw [hsame, G.minSails_self]; exact Nat.zero_le _
        | @drive t' u v ht' _ hroad =>
          have hsame : G.islandOf (({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc v) } : State I).truckPhysLoc t) =
                       G.islandOf (s1.truckPhysLoc t) := by
            by_cases h : t = t'
            · subst h; simp [State.truckPhysLoc, ht', updateFn, G.road_same u v hroad]
            · simp [State.truckPhysLoc, updateFn, h]
          rw [hsame, G.minSails_self]; exact Nat.zero_le _
        | load _ _ _ => simp [State.truckPhysLoc, G.minSails_self]
        | unload _ _ => simp [State.truckPhysLoc, G.minSails_self]
        | @board t' f ht' _ =>
          have hsame : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.onFerry f) } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
            by_cases h : t = t'
            · subst h; simp [State.truckPhysLoc, ht', updateFn]
            · simp [State.truckPhysLoc, updateFn, h]
          rw [hsame, G.minSails_self]; exact Nat.zero_le _
        | @disembark t' f ht' =>
          have hsame : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc (s1.ferryLoc f)) } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
            by_cases h : t = t'
            · subst h; simp [State.truckPhysLoc, ht', updateFn]
            · simp [State.truckPhysLoc, updateFn, h]
          rw [hsame, G.minSails_self]; exact Nat.zero_le _
      have hcnt : loadedInterSailCount G s1 (a :: rest) = stepLoadedInterSail G s1 a + loadedInterSailCount G s2 rest := by
        cases a <;> simp [loadedInterSailCount, stepLoadedInterSail, hs2_eq]
      rw [hcnt]
      exact Nat.le_trans htri (Nat.add_le_add h1step hrec)
  -- Helper 2: distance moved by a package `p` in `minSails` ≤ `loadedInterSailCount`!
  have hpkg_move : ∀ {sa sb : State I} {ps : Plan I} (hva : ValidState I sa) (hpa : ValidPlan I sa ps sb),
      G.minSails (G.islandOf (sa.pkgPhysLoc p)) (G.islandOf (sb.pkgPhysLoc p)) ≤ loadedInterSailCount G sa ps := by
    intro sa sb ps hva hpa
    induction hpa with
    | nil => simp [G.minSails_self]
    | @cons s1 s2 s_last a rest hstep _ ih =>
      have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
      have hrec := ih (validState_step hva hstep)
      have htri := G.minSails_tri (G.islandOf (s1.pkgPhysLoc p)) (G.islandOf (s2.pkgPhysLoc p)) (G.islandOf (s_last.pkgPhysLoc p))
      have h1step : G.minSails (G.islandOf (s1.pkgPhysLoc p)) (G.islandOf (s2.pkgPhysLoc p)) ≤
          stepLoadedInterSail G s1 a := by
        by_cases hsame : s2.pkgPhysLoc p = s1.pkgPhysLoc p
        · rw [hsame, G.minSails_self]; exact Nat.zero_le _
        · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, hpl, hp1, hp2⟩
          rw [hp1, hp2]
          cases hstep with
          | @sail f u v hf _ hserved =>
            cases htl : s1.truckLoc t with
            | atLoc _ =>
              have hsame_t : ({ s1 with ferryLoc := updateFn s1.ferryLoc f v } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
                simp [State.truckPhysLoc, htl]
              rw [hsame_t, G.minSails_self]; exact Nat.zero_le _
            | onFerry f' =>
              by_cases hff : f' = f
              · subst hff
                have hpos_fc : 0 < s1.ferryCount f' := by
                  have h := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f' then 1 else 0) t
                  unfold State.ferryCount; simp only [htl, ↓reduceIte] at h; omega
                have hpos_f : 0 < I.ferryCap f' := by have := hva.aboard_le_cap f'; omega
                have hu : s1.truckPhysLoc t = u := by simp [State.truckPhysLoc, htl, hf]
                have hv' : ({ s1 with ferryLoc := updateFn s1.ferryLoc f' v } : State I).truckPhysLoc t = v := by
                  simp [State.truckPhysLoc, htl, updateFn]
                rw [hu, hv']
                by_cases hne_i : G.islandOf u ≠ G.islandOf v
                · rw [show stepLoadedInterSail G s1 (.sail f' u v) = 1 from by
                    unfold stepLoadedInterSail; exact ite_eq_left_iff.mpr (fun h => absurd ⟨hne_i, hpos_fc⟩ h)]
                  exact G.minSails_ferry f' u v hpos_f (hf ▸ hva.ferry_served f') hserved
                · have heq_i : G.islandOf u = G.islandOf v := Classical.byContradiction hne_i
                  rw [heq_i, G.minSails_self]; exact Nat.zero_le _
              · have hsame_t : ({ s1 with ferryLoc := updateFn s1.ferryLoc f v } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
                  simp [State.truckPhysLoc, htl, updateFn, hff]
                rw [hsame_t, G.minSails_self]; exact Nat.zero_le _
          | @drive t' u v ht' _ hroad =>
            have hsame_i : G.islandOf (({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc v) } : State I).truckPhysLoc t) =
                           G.islandOf (s1.truckPhysLoc t) := by
              by_cases h : t = t'
              · subst h; simp [State.truckPhysLoc, ht', updateFn, G.road_same u v hroad]
              · simp [State.truckPhysLoc, updateFn, h]
            rw [hsame_i, G.minSails_self]; exact Nat.zero_le _
          | load _ _ _ => simp [State.truckPhysLoc, G.minSails_self]
          | unload _ _ => simp [State.truckPhysLoc, G.minSails_self]
          | @board t' f ht' _ =>
            have hsame_t : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.onFerry f) } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
              by_cases h : t = t'
              · subst h; simp [State.truckPhysLoc, ht', updateFn]
              · simp [State.truckPhysLoc, updateFn, h]
            rw [hsame_t, G.minSails_self]; exact Nat.zero_le _
          | @disembark t' f ht' =>
            have hsame_t : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc (s1.ferryLoc f)) } : State I).truckPhysLoc t = s1.truckPhysLoc t := by
              by_cases h : t = t'
              · subst h; simp [State.truckPhysLoc, ht', updateFn]
              · simp [State.truckPhysLoc, updateFn, h]
            rw [hsame_t, G.minSails_self]; exact Nat.zero_le _
      have hcnt : loadedInterSailCount G s1 (a :: rest) = stepLoadedInterSail G s1 a + loadedInterSailCount G s2 rest := by
        cases a <;> simp [loadedInterSailCount, stepLoadedInterSail, hs2_eq]
      rw [hcnt]
      exact Nat.le_trans htri (Nat.add_le_add h1step hrec)
  constructor
  · intro t hpl
    have h := hpkg_move hv hp
    have h1 : s.pkgPhysLoc p = s.truckPhysLoc t := by simp [State.pkgPhysLoc, hpl]
    have h2 : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    rwa [h1, h2] at h
  · -- Ground package `p` at `l`: split `π` at the FIRST `LOAD(p, t)`!
    intro l hpl mps hmps
    -- Find prefix `π₁` + suffix `π₂` with `π = π₁ ++ π₂` where `t` loads `p` at `l`!
    have hsplit : ∀ {sa s_end : State I} {ps : Plan I}
        (hva : ValidState I sa) (hpa : ValidPlan I sa ps s_end) (hga : goalTest I s_end),
        sa.pkgLoc p = .atLoc l → sa.pkgDelivered p = false →
        ∃ (t : Fin I.numTrucks) (s_mid : State I) (p1 p2 : Plan I),
          ps = p1 ++ p2 ∧ I.pkgWeight p ≤ I.truckCap t ∧
          ValidPlan I sa p1 s_mid ∧ ValidState I s_mid ∧ ValidPlan I s_mid p2 s_end ∧
          s_mid.truckPhysLoc t = l ∧ s_mid.pkgPhysLoc p = l := by
      intro sa s_end ps hva hpa hga hpl_a hnd_a
      induction hpa with
      | nil =>
        have hgp := hga p; rw [hpl_a] at hgp; injection hgp with hl
        simp [State.pkgDelivered, hpl_a, hl] at hnd_a
      | @cons s1 s2 _ a rest hstep hrest ih =>
        cases hstep with
        | @load p' t' l' ht' hp' hcap' =>
          by_cases hpp : p' = p
          · subst hpp
            rw [hpl_a] at hp'; injection hp' with hll; subst hll
            exact ⟨t', s1, [], .load p' t' :: rest, rfl, by omega, ValidPlan.nil, hva,
              ValidPlan.cons (Step.load ht' hpl_a hcap') hrest,
              by simp [State.truckPhysLoc, ht'], by simp [State.pkgPhysLoc, hpl_a]⟩
          · have hpl_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgLoc p = .atLoc l := by
              simp [updateFn, Ne.symm hpp, hpl_a]
            have hnd_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgDelivered p = false := by
              simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd_a
            rcases ih (validState_step hva (Step.load ht' hp' hcap')) hga hpl_b hnd_b with
              ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
            exact ⟨t, sm, .load p' t' :: p1, p2, by simp [heq], hcap_t,
              ValidPlan.cons (Step.load ht' hp' hcap') hp1, hvm, hp2, htl_m, hpl_m⟩
        | @unload p' t' l' ht' hp' =>
          have hpp : p' ≠ p := by intro h; subst h; rw [hpl_a] at hp'; cases hp'
          have hpl_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgLoc p = .atLoc l := by
            simp [updateFn, Ne.symm hpp, hpl_a]
          have hnd_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgDelivered p = false := by
            simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd_a
          rcases ih (validState_step hva (Step.unload ht' hp')) hga hpl_b hnd_b with
            ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
          exact ⟨t, sm, .unload p' t' :: p1, p2, by simp [heq], hcap_t,
            ValidPlan.cons (Step.unload ht' hp') hp1, hvm, hp2, htl_m, hpl_m⟩
        | @drive t' u v ht' hne hroad =>
          rcases ih (validState_step hva (Step.drive ht' hne hroad)) hga hpl_a hnd_a with
            ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
          exact ⟨t, sm, .drive t' u v :: p1, p2, by simp [heq], hcap_t,
            ValidPlan.cons (Step.drive ht' hne hroad) hp1, hvm, hp2, htl_m, hpl_m⟩
        | @board t' f ht' hcf =>
          rcases ih (validState_step hva (Step.board ht' hcf)) hga hpl_a hnd_a with
            ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
          exact ⟨t, sm, .board t' f :: p1, p2, by simp [heq], hcap_t,
            ValidPlan.cons (Step.board ht' hcf) hp1, hvm, hp2, htl_m, hpl_m⟩
        | @disembark t' f ht' =>
          rcases ih (validState_step hva (Step.disembark ht')) hga hpl_a hnd_a with
            ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
          exact ⟨t, sm, .disembark t' f :: p1, p2, by simp [heq], hcap_t,
            ValidPlan.cons (Step.disembark ht') hp1, hvm, hp2, htl_m, hpl_m⟩
        | @sail f u v hf hne hsv =>
          rcases ih (validState_step hva (Step.sail hf hne hsv)) hga hpl_a hnd_a with
            ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
          exact ⟨t, sm, .sail f u v :: p1, p2, by simp [heq], hcap_t,
            ValidPlan.cons (Step.sail hf hne hsv) hp1, hvm, hp2, htl_m, hpl_m⟩
    -- Additivity of `loadedInterSailCount` on `p1 ++ p2`
    have hadd : ∀ {s1 s2 : State I} {p1 p2 : Plan I}, ValidPlan I s1 p1 s2 →
        loadedInterSailCount G s1 (p1 ++ p2) = loadedInterSailCount G s1 p1 + loadedInterSailCount G s2 p2 := by
      intro s1 s2 p1 p2 hp1
      induction hp1 with
      | nil => simp [loadedInterSailCount]
      | @cons sa sb _ a r hst _ iha =>
        simp only [List.cons_append, loadedInterSailCount, ← step_eq_applyAction hst, iha]; omega
    rcases hsplit hv hp hg hpl hnd with ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
    have h1 := hmps t hcap_t
    have h2 := htruck_move hv hp1 t
    rw [htl_m] at h2
    have h3 := hpkg_move hvm hp2
    have hg_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    rw [hpl_m, hg_p] at h3
    rw [heq, hadd hp1]
    omega

/-- Per-island ferry sail conservation (`ex1.py:L1182-L1199`):
    For each island `isl` and each ferry `f ∈ G.islandFerries isl`:
    - `sailOut(isl, f) ≤ sailIn(isl, f) + (1 if f starts on isl else 0)`
    - `sailIn(isl, f) ≤ sailOut(isl, f) + (1 if f starts NOT on isl else 0)`
    This directly proves `ro ≤ totalSailOut(isl)`, `ri ≤ totalSailIn(isl)`,
    `b3 = max_isl (ro + ri) ≤ sailCount π`, and `sum_req_i = ∑ ri ≤ sailCount π`! -/
def isIslFerrySailOut {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (f : Fin I.numFerries) : Action I → Bool
  | .sail f' u v => decide (f' = f) && decide (G.islandOf u = isl) && decide (G.islandOf v ≠ isl)
  | _            => false

def isIslFerrySailIn {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (f : Fin I.numFerries) : Action I → Bool
  | .sail f' u v => decide (f' = f) && decide (G.islandOf u ≠ isl) && decide (G.islandOf v = isl)
  | _            => false

def isIslSailOut {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) : Action I → Bool
  | .sail _ u v => decide (G.islandOf u = isl) && decide (G.islandOf v ≠ isl)
  | _           => false

def isIslSailIn {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) : Action I → Bool
  | .sail _ u v => decide (G.islandOf u ≠ isl) && decide (G.islandOf v = isl)
  | _           => false

theorem island_ferry_conservation {I : Instance} (G : IslandGraph I)
    (isl : Fin G.numIslands) (f : Fin I.numFerries)
    {s s_end : State I} {π : Plan I} (hp : ValidPlan I s π s_end) :
    let sOut := countActions (isIslFerrySailOut G isl f) π
    let sIn  := countActions (isIslFerrySailIn G isl f) π
    sOut ≤ sIn + (if G.islandOf (s.ferryLoc f) = isl then 1 else 0) ∧
    sIn ≤ sOut + (if G.islandOf (s.ferryLoc f) ≠ isl then 1 else 0) := by
  have ⟨hT, hF⟩ := ferry_sail_alternation G f (fun i => decide (i = isl)) hp
  have heq_out : countActions (isIslFerrySailOut G isl f) π =
                 countActions (isCutSailAB G f (fun i => decide (i = isl))) π := by
    unfold countActions; apply congrArg List.sum; apply List.map_congr_left; intro a _
    cases a with
    | sail f' u v =>
      by_cases h1 : f' = f <;> by_cases h2 : G.islandOf u = isl <;> by_cases h3 : G.islandOf v = isl <;>
        simp [isIslFerrySailOut, isCutSailAB, h1, h2, h3]
    | _ => rfl
  have heq_in : countActions (isIslFerrySailIn G isl f) π =
                countActions (isCutSailBA G f (fun i => decide (i = isl))) π := by
    unfold countActions; apply congrArg List.sum; apply List.map_congr_left; intro a _
    cases a with
    | sail f' u v =>
      by_cases h1 : f' = f <;> by_cases h2 : G.islandOf u = isl <;> by_cases h3 : G.islandOf v = isl <;>
        simp [isIslFerrySailIn, isCutSailBA, h1, h2, h3]
    | _ => rfl
  rw [heq_out, heq_in]
  by_cases h : G.islandOf (s.ferryLoc f) = isl
  · have ht : decide (G.islandOf (s.ferryLoc f) = isl) = true := decide_eq_true h
    have ⟨h1, h2⟩ := hT ht
    simp only [h, ↓reduceIte]; omega
  · have hf : decide (G.islandOf (s.ferryLoc f) = isl) = false := decide_eq_false h
    have ⟨h1, h2⟩ := hF hf
    have hite : (if G.islandOf (s.ferryLoc f) ≠ isl then 1 else 0) = 1 := if_pos h
    rw [hite]; simp only [h, ↓reduceIte]; omega

/-- Combining per-island sail conservation (`b3` and `sum_req_i`, `ex1.py:L1182-L1199`):
    1) `countActions (isIslSailOut G isl) π + countActions (isIslSailIn G isl) π ≤ sailCount π` (proving `b3 ≤ sailCount π`)
    2) `finSum (fun isl => countActions (isIslSailIn G isl) π) ≤ sailCount π` (proving `sum_req_i ≤ sailCount π`). -/
theorem island_sail_disjoint_bounds {I : Instance} (G : IslandGraph I) (π : Plan I) :
    (∀ isl : Fin G.numIslands,
      countActions (isIslSailOut G isl) π + countActions (isIslSailIn G isl) π ≤ sailCount π) ∧
    finSum (fun isl => countActions (isIslSailIn G isl) π) ≤ sailCount π := by
  constructor
  · intro isl
    induction π with
    | nil => simp [countActions, sailCount]
    | cons a rest ih =>
      have hhead : countActions (isIslSailOut G isl) [a] + countActions (isIslSailIn G isl) [a] ≤ sailCount [a] := by
        cases a with
        | sail f u v =>
          by_cases h1 : G.islandOf u = isl <;> by_cases h2 : G.islandOf v = isl <;>
            simp [countActions, sailCount, isIslSailOut, isIslSailIn, h1, h2]
        | drive _ _ _ => simp [countActions, sailCount, isIslSailOut, isIslSailIn]
        | load _ _ => simp [countActions, sailCount, isIslSailOut, isIslSailIn]
        | unload _ _ => simp [countActions, sailCount, isIslSailOut, isIslSailIn]
        | board _ _ => simp [countActions, sailCount, isIslSailOut, isIslSailIn]
        | disembark _ _ => simp [countActions, sailCount, isIslSailOut, isIslSailIn]
      have ho : countActions (isIslSailOut G isl) (a :: rest) =
          countActions (isIslSailOut G isl) [a] + countActions (isIslSailOut G isl) rest := by
        simp [countActions]
      have hi : countActions (isIslSailIn G isl) (a :: rest) =
          countActions (isIslSailIn G isl) [a] + countActions (isIslSailIn G isl) rest := by
        simp [countActions]
      have hs : sailCount (a :: rest) = sailCount [a] + sailCount rest := by
        simp [sailCount]
      omega
  · unfold countActions sailCount
    induction π with
    | nil => simp [finSum_zero]
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      rw [finSum_add]
      have ha : finSum (fun isl => if isIslSailIn G isl a = true then 1 else 0) ≤
                (match a with | .sail _ _ _ => 1 | _ => 0) := by
        cases a with
        | sail f u v =>
          by_cases hne : G.islandOf u = G.islandOf v
          · have hz : (fun isl => if isIslSailIn G isl (.sail f u v) = true then 1 else 0) = (fun _ => 0) := by
              funext isl; by_cases h : G.islandOf v = isl <;> simp [isIslSailIn, hne, h]
            rw [hz, finSum_zero]; omega
          · have hfn : (fun isl => if isIslSailIn G isl (.sail f u v) = true then 1 else 0) =
                       (fun isl => if isl = G.islandOf v then 1 else 0) := by
              funext isl; by_cases h : isl = G.islandOf v
              · subst h; simp [isIslSailIn, hne]
              · simp [isIslSailIn, h, Ne.symm h]
            rw [hfn, finSum_ite_eq]; simp
        | drive _ _ _ => simp [isIslSailIn, finSum_zero]
        | load _ _ => simp [isIslSailIn, finSum_zero]
        | unload _ _ => simp [isIslSailIn, finSum_zero]
        | board _ _ => simp [isIslSailIn, finSum_zero]
        | disembark _ _ => simp [isIslSailIn, finSum_zero]
      exact Nat.add_le_add ha ih

/-- Exact island ferry-conservation algebra (`ex1.py:L1191-L1196`):
    Given `fl = G.islandFerries isl` (Nodup) with `mi` ferries starting on `isl` (total weight capacity `ci`),
    `len - mi` ferries starting off `isl` (total weight capacity `co`), max sail weight `c_isl`,
    and total weight carried out `wo` / in `wi` across `isl`, prove `ro ≤ totalOut` and `ri ≤ totalIn`! -/
theorem island_ro_ri_sound {I : Instance} (G : IslandGraph I)
    (isl : Fin G.numIslands) {s s_end : State I} {π : Plan I}
    (hp : ValidPlan I s π s_end)
    (so si wo wi c_isl : Nat) (hc_pos : 0 < c_isl)
    (hc_ge : ∀ f ∈ G.islandFerries isl, maxFerryWeight I s f ≤ c_isl)
    (hso : so ≤ (G.islandFerries isl |>.map (fun f => countActions (isIslFerrySailOut G isl f) π)).sum)
    (hsi : si ≤ (G.islandFerries isl |>.map (fun f => countActions (isIslFerrySailIn G isl f) π)).sum)
    (hwo : wo ≤ (G.islandFerries isl |>.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailOut G isl f) π)).sum)
    (hwi : wi ≤ (G.islandFerries isl |>.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailIn G isl f) π)).sum) :
    let fl := G.islandFerries isl
    let mi := (fl.map (fun f => if G.islandOf (s.ferryLoc f) = isl then 1 else 0)).sum
    let ci := (fl.map (fun f => if G.islandOf (s.ferryLoc f) = isl then maxFerryWeight I s f else 0)).sum
    let co := (fl.map (fun f => if G.islandOf (s.ferryLoc f) ≠ isl then maxFerryWeight I s f else 0)).sum
    let ro := max (max so (si - (fl.length - mi))) (if wi > co then ceilDiv (wi - co) c_isl else 0)
    let ri := max (max si (so - mi)) (if wo > ci then ceilDiv (wo - ci) c_isl else 0)
    ro ≤ countActions (isIslSailOut G isl) π ∧
    ri ≤ countActions (isIslSailIn G isl) π := by
  intro fl mi ci co ro ri
  let totOut := (fl.map (fun f => countActions (isIslFerrySailOut G isl f) π)).sum
  let totIn  := (fl.map (fun f => countActions (isIslFerrySailIn G isl f) π)).sum
  -- 1. `totOut ≤ countActions (isIslSailOut G isl) π` and `totIn ≤ countActions (isIslSailIn G isl) π` (since `fl.Nodup`)!
  have htot_out_le : totOut ≤ countActions (isIslSailOut G isl) π := by
    have hdisj : (fl.map (isIslFerrySailOut G isl)).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
      rw [List.pairwise_map]
      refine (G.islandFerries_nd isl).imp ?_
      intro f₁ f₂ hne a h1
      cases a with
      | sail f' u v =>
        simp only [isIslFerrySailOut, Bool.and_eq_true, decide_eq_true_eq] at h1
        rcases h1 with ⟨⟨rfl, _⟩, _⟩
        simp [isIslFerrySailOut, hne]
      | _ => simp [isIslFerrySailOut] at h1
    have hsum := sum_countActions_disjoint (fl.map (isIslFerrySailOut G isl)) π hdisj
    have hmap : ((fl.map (isIslFerrySailOut G isl)).map (fun p => countActions p π)).sum = totOut := by
      rw [List.map_map]; rfl
    rw [hmap] at hsum
    apply Nat.le_trans hsum
    unfold countActions; clear hdisj hsum hmap hso hsi hwo hwi hp
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      dsimp only at ih ⊢
      have ha : (if ((fl.map (isIslFerrySailOut G isl)).any fun p => p a) = true then 1 else 0) ≤
                (if isIslSailOut G isl a = true then 1 else 0) := by
        by_cases hany : ((fl.map (isIslFerrySailOut G isl)).any fun p => p a) = true
        · rw [List.any_eq_true] at hany; rcases hany with ⟨p, hp', hpa⟩
          rw [List.mem_map] at hp'; rcases hp' with ⟨f, _, rfl⟩
          cases a with
          | sail f' u v =>
            simp only [isIslFerrySailOut, Bool.and_eq_true, decide_eq_true_eq] at hpa
            have h1 : decide (G.islandOf u = isl) = true := decide_eq_true hpa.1.2
            have h2 : decide (G.islandOf v ≠ isl) = true := decide_eq_true hpa.2
            simp only [isIslSailOut, h1, h2, Bool.and_self, ↓reduceIte]; split <;> omega
          | _ => simp [isIslFerrySailOut] at hpa
        · have hf : ((fl.map (isIslFerrySailOut G isl)).any fun p => p a) = false := Bool.eq_false_iff.mpr hany
          simp [hf]
      omega
  have htot_in_le : totIn ≤ countActions (isIslSailIn G isl) π := by
    have hdisj : (fl.map (isIslFerrySailIn G isl)).Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
      rw [List.pairwise_map]
      refine (G.islandFerries_nd isl).imp ?_
      intro f₁ f₂ hne a h1
      cases a with
      | sail f' u v =>
        simp only [isIslFerrySailIn, Bool.and_eq_true, decide_eq_true_eq] at h1
        rcases h1 with ⟨⟨rfl, _⟩, _⟩
        simp [isIslFerrySailIn, hne]
      | _ => simp [isIslFerrySailIn] at h1
    have hsum := sum_countActions_disjoint (fl.map (isIslFerrySailIn G isl)) π hdisj
    have hmap : ((fl.map (isIslFerrySailIn G isl)).map (fun p => countActions p π)).sum = totIn := by
      rw [List.map_map]; rfl
    rw [hmap] at hsum
    apply Nat.le_trans hsum
    unfold countActions; clear htot_out_le hdisj hsum hmap hso hsi hwo hwi hp
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      dsimp only at ih ⊢
      have ha : (if ((fl.map (isIslFerrySailIn G isl)).any fun p => p a) = true then 1 else 0) ≤
                (if isIslSailIn G isl a = true then 1 else 0) := by
        by_cases hany : ((fl.map (isIslFerrySailIn G isl)).any fun p => p a) = true
        · rw [List.any_eq_true] at hany; rcases hany with ⟨p, hp', hpa⟩
          rw [List.mem_map] at hp'; rcases hp' with ⟨f, _, rfl⟩
          cases a with
          | sail f' u v =>
            simp only [isIslFerrySailIn, Bool.and_eq_true, decide_eq_true_eq] at hpa
            have h1 : decide (G.islandOf u ≠ isl) = true := decide_eq_true hpa.1.2
            have h2 : decide (G.islandOf v = isl) = true := decide_eq_true hpa.2
            simp only [isIslSailIn, h1, h2, Bool.and_self, ↓reduceIte]; split <;> omega
          | _ => simp [isIslFerrySailIn] at hpa
        · have hf : ((fl.map (isIslFerrySailIn G isl)).any fun p => p a) = false := Bool.eq_false_iff.mpr hany
          simp [hf]
      omega
  -- 2. Conservation inequalities summed over `fl`:
  have hcons :
      totOut ≤ totIn + mi ∧
      totIn ≤ totOut + (fl.length - mi) ∧
      (fl.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailOut G isl f) π)).sum ≤ ci + c_isl * totIn ∧
      (fl.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailIn G isl f) π)).sum ≤ co + c_isl * totOut := by
    suffices ∀ (ls : List (Fin I.numFerries)),
        (∀ f ∈ ls, maxFerryWeight I s f ≤ c_isl) →
        (ls.map (fun f => countActions (isIslFerrySailOut G isl f) π)).sum ≤
          (ls.map (fun f => countActions (isIslFerrySailIn G isl f) π)).sum +
          (ls.map (fun f => if G.islandOf (s.ferryLoc f) = isl then 1 else 0)).sum ∧
        (ls.map (fun f => countActions (isIslFerrySailIn G isl f) π)).sum ≤
          (ls.map (fun f => countActions (isIslFerrySailOut G isl f) π)).sum +
          (ls.length - (ls.map (fun f => if G.islandOf (s.ferryLoc f) = isl then 1 else 0)).sum) ∧
        (ls.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailOut G isl f) π)).sum ≤
          (ls.map (fun f => if G.islandOf (s.ferryLoc f) = isl then maxFerryWeight I s f else 0)).sum +
          c_isl * (ls.map (fun f => countActions (isIslFerrySailIn G isl f) π)).sum ∧
        (ls.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailIn G isl f) π)).sum ≤
          (ls.map (fun f => if G.islandOf (s.ferryLoc f) ≠ isl then maxFerryWeight I s f else 0)).sum +
          c_isl * (ls.map (fun f => countActions (isIslFerrySailOut G isl f) π)).sum from
      this fl hc_ge
    intro ls
    induction ls with
    | nil => intro _; simp
    | cons f fs ih =>
      intro hfs
      have hf_c := hfs f (List.mem_cons_self ..)
      have ⟨ih1, ih2, ih3, ih4⟩ := ih (fun f' hm => hfs f' (List.mem_cons_of_mem _ hm))
      have ⟨hc1, hc2⟩ := island_ferry_conservation G isl f hp
      have hmi_le_len : (fs.map (fun f' => if G.islandOf (s.ferryLoc f') = isl then 1 else 0)).sum ≤ fs.length := by
        clear ih hfs hf_c ih1 ih2 ih3 ih4 hc1 hc2
        induction fs with
        | nil => simp
        | cons x xs ihx => simp only [List.map_cons, List.sum_cons, List.length_cons]; split <;> omega
      simp only [List.map_cons, List.sum_cons, List.length_cons, Nat.mul_add]
      have hm1 : maxFerryWeight I s f * countActions (isIslFerrySailOut G isl f) π ≤
                 (if G.islandOf (s.ferryLoc f) = isl then maxFerryWeight I s f else 0) +
                 c_isl * countActions (isIslFerrySailIn G isl f) π := by
        have h1 := Nat.mul_le_mul_left (maxFerryWeight I s f) hc1
        rw [Nat.mul_add] at h1
        have h2 := Nat.mul_le_mul_right (countActions (isIslFerrySailIn G isl f) π) hf_c
        by_cases h : G.islandOf (s.ferryLoc f) = isl <;> simp [h] at h1 ⊢ <;> omega
      have hm2 : maxFerryWeight I s f * countActions (isIslFerrySailIn G isl f) π ≤
                 (if G.islandOf (s.ferryLoc f) ≠ isl then maxFerryWeight I s f else 0) +
                 c_isl * countActions (isIslFerrySailOut G isl f) π := by
        have h1 := Nat.mul_le_mul_left (maxFerryWeight I s f) hc2
        rw [Nat.mul_add] at h1
        have h2 := Nat.mul_le_mul_right (countActions (isIslFerrySailOut G isl f) π) hf_c
        by_cases h : G.islandOf (s.ferryLoc f) = isl <;> simp [h] at h1 ⊢ <;> omega
      refine ⟨by omega, ?_, by omega, by omega⟩
      by_cases h : G.islandOf (s.ferryLoc f) = isl <;> simp [h] at hc2 ⊢ <;> omega
  rcases hcons with ⟨hc_out, hc_in, hc_wo, hc_wi⟩
  have hso' : so ≤ totOut := hso
  have hsi' : si ≤ totIn := hsi
  have hwo' : wo ≤ (fl.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailOut G isl f) π)).sum := hwo
  have hwi' : wi ≤ (fl.map (fun f => maxFerryWeight I s f * countActions (isIslFerrySailIn G isl f) π)).sum := hwi
  have hro_ceil : (if wi > co then ceilDiv (wi - co) c_isl else 0) ≤ totOut := by
    by_cases h : wi > co
    · simp only [h, ↓reduceIte]
      exact ceilDiv_le_of_le_mul hc_pos (by rw [Nat.mul_comm]; omega)
    · simp [h]
  have hri_ceil : (if wo > ci then ceilDiv (wo - ci) c_isl else 0) ≤ totIn := by
    by_cases h : wo > ci
    · simp only [h, ↓reduceIte]
      exact ceilDiv_le_of_le_mul hc_pos (by rw [Nat.mul_comm]; omega)
    · simp [h]
  dsimp only [ro, ri]
  exact ⟨by omega, by omega⟩

/-- Loaded inter-island sails departing from (resp. arriving at) island `isl`. -/
def loadedIslSailOut {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (s : State I) : Plan I → Nat
  | [] => 0
  | a :: rest =>
    (match a with
     | .sail f u v => if G.islandOf u = isl ∧ G.islandOf v ≠ isl ∧ 0 < s.ferryCount f then 1 else 0
     | _ => 0) +
    loadedIslSailOut G isl (applyAction s a) rest

def loadedIslSailIn {I : Instance} (G : IslandGraph I) (isl : Fin G.numIslands) (s : State I) : Plan I → Nat
  | [] => 0
  | a :: rest =>
    (match a with
     | .sail f u v => if G.islandOf u ≠ isl ∧ G.islandOf v = isl ∧ 0 < s.ferryCount f then 1 else 0
     | _ => 0) +
    loadedIslSailIn G isl (applyAction s a) rest

/-- Summing `loadedIslSailOut` (resp. `loadedIslSailIn`) over all islands equals `loadedInterSailCount G s π`!
    This justifies `sum_so ≤ loadedInterSailCount` and `sum_si ≤ loadedInterSailCount` (`ex1.py:L1180-L1181, L1224`)! -/
theorem sum_loadedIslSail_eq {I : Instance} (G : IslandGraph I) (s : State I) (π : Plan I) :
    finSum (fun isl => loadedIslSailOut G isl s π) = loadedInterSailCount G s π ∧
    finSum (fun isl => loadedIslSailIn G isl s π) = loadedInterSailCount G s π := by
  induction π generalizing s with
  | nil => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, finSum_zero]
  | cons a rest ih =>
    have ⟨ihO, ihI⟩ := ih (applyAction s a)
    cases a with
    | sail f u v =>
      simp only [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount]
      rw [finSum_add, finSum_add, ihO, ihI]
      by_cases hne : G.islandOf u ≠ G.islandOf v
      · by_cases hfc : 0 < s.ferryCount f
        · have hc : G.islandOf u ≠ G.islandOf v ∧ 0 < s.ferryCount f := ⟨hne, hfc⟩
          have hO : (fun isl => if G.islandOf u = isl ∧ G.islandOf v ≠ isl ∧ 0 < s.ferryCount f then 1 else 0) =
                    (fun isl => if isl = G.islandOf u then 1 else 0) := by
            funext isl; by_cases h : isl = G.islandOf u
            · subst h; simp [Ne.symm hne, hfc]
            · simp [h, Ne.symm h]
          have hI : (fun isl => if G.islandOf u ≠ isl ∧ G.islandOf v = isl ∧ 0 < s.ferryCount f then 1 else 0) =
                    (fun isl => if isl = G.islandOf v then 1 else 0) := by
            funext isl; by_cases h : isl = G.islandOf v
            · subst h; simp [hne, hfc]
            · simp [h, Ne.symm h]
          rw [hO, hI, finSum_ite_eq, finSum_ite_eq]
          simp [hc]
        · have hO : (fun isl => if G.islandOf u = isl ∧ G.islandOf v ≠ isl ∧ 0 < s.ferryCount f then 1 else 0) = fun _ => 0 := by
            funext isl; simp [hfc]
          have hI : (fun isl => if G.islandOf u ≠ isl ∧ G.islandOf v = isl ∧ 0 < s.ferryCount f then 1 else 0) = fun _ => 0 := by
            funext isl; simp [hfc]
          rw [hO, hI, finSum_zero]; simp [hfc]
      · have heq : G.islandOf u = G.islandOf v := Classical.byContradiction hne
        have hO : (fun isl => if G.islandOf u = isl ∧ G.islandOf v ≠ isl ∧ 0 < s.ferryCount f then 1 else 0) = fun _ => 0 := by
          funext isl; by_cases h : G.islandOf v = isl <;> simp [heq, h]
        have hI : (fun isl => if G.islandOf u ≠ isl ∧ G.islandOf v = isl ∧ 0 < s.ferryCount f then 1 else 0) = fun _ => 0 := by
          funext isl; by_cases h : G.islandOf v = isl <;> simp [heq, h]
        rw [hO, hI, finSum_zero]; simp [hne]
    | drive _ _ _ => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, ihO, ihI]
    | load _ _ => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, ihO, ihI]
    | unload _ _ => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, ihO, ihI]
    | board _ _ => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, ihO, ihI]
    | disembark _ _ => simp [loadedIslSailOut, loadedIslSailIn, loadedInterSailCount, ihO, ihI]

end IslandLogistics
