/-
Module 1: Domain.lean

Formalizes the exact Island Logistics planning domain:
- Instances (locations, undirected roads, ports, trucks, ferries, packages)
- States, entity positions, truck loads, ferry occupancy, validity invariants
- The 6 legal actions (DRIVE, LOAD, UNLOAD, BOARD, DISEMBARK, SAIL) with exact
  preconditions and state transitions matching ex1.py / ex1_check.py
- Action costs (SAIL = 3, all others = 1), valid plans, and goal_test
- Exact disjoint action-cost partition lemma and master admissibility combination
  theorem matching ex1.py:L1625-L1652.
-/

namespace IslandLogistics

/-- Sum of `f i` over all `i : Fin n`. -/
def finSum {n : Nat} (f : Fin n → Nat) : Nat :=
  (List.finRange n).foldr (fun i acc => f i + acc) 0

/-- Helper: `finSum` equals `List.sum (List.map f (List.finRange n))`. -/
theorem finSum_eq_list_sum {n : Nat} (f : Fin n → Nat) :
    finSum f = ((List.finRange n).map f).sum := by
  unfold finSum
  induction (List.finRange n) with
  | nil => rfl
  | cons x xs ih => simp [ih]

/-- Monotonicity of `finSum`. -/
theorem finSum_le_finSum {n : Nat} {f g : Fin n → Nat} (h : ∀ i, f i ≤ g i) :
    finSum f ≤ finSum g := by
  simp only [finSum_eq_list_sum]
  suffices ∀ l : List (Fin n), (l.map f).sum ≤ (l.map g).sum from this (List.finRange n)
  intro l
  induction l with
  | nil => simp
  | cons x xs ih =>
    simp only [List.map_cons, List.sum_cons]
    have hx := h x
    omega

/-- Additivity of `finSum`. -/
theorem finSum_add {n : Nat} (f g : Fin n → Nat) :
    finSum (fun i => f i + g i) = finSum f + finSum g := by
  simp only [finSum_eq_list_sum]
  suffices ∀ l : List (Fin n), (l.map (fun i => f i + g i)).sum = (l.map f).sum + (l.map g).sum
    from this (List.finRange n)
  intro l
  induction l with
  | nil => simp
  | cons x xs ih =>
    simp only [List.map_cons, List.sum_cons, ih]
    omega

/-- Constant zero `finSum`. -/
theorem finSum_zero {n : Nat} : finSum (fun _ : Fin n => 0) = 0 := by
  simp only [finSum_eq_list_sum]
  suffices ∀ l : List (Fin n), (l.map (fun _ => 0)).sum = 0 from this (List.finRange n)
  intro l
  induction l with
  | nil => simp
  | cons _ xs ih => simp [ih]

/-- Single-element bound: `f i ≤ finSum f`. -/
theorem le_finSum {n : Nat} (f : Fin n → Nat) (i : Fin n) : f i ≤ finSum f := by
  simp only [finSum_eq_list_sum]
  have hmem : i ∈ List.finRange n := List.mem_finRange i
  suffices ∀ l : List (Fin n), i ∈ l → f i ≤ (l.map f).sum from this (List.finRange n) hmem
  intro l hl
  induction l with
  | nil => cases hl
  | cons x xs ih =>
    simp only [List.map_cons, List.sum_cons]
    rcases List.mem_cons.mp hl with rfl | hxs
    · omega
    · have := ih hxs; omega

/-- Pointwise update lemma for `finSum`: changing `f` at a single index `k`. -/
theorem finSum_update {n : Nat} (f : Fin n → Nat) (k : Fin n) (v : Nat) :
    finSum (fun i => if i = k then v else f i) + f k = finSum f + v := by
  simp only [finSum_eq_list_sum]
  have hnodup : (List.finRange n).Nodup := List.nodup_finRange n
  have hmem : k ∈ List.finRange n := List.mem_finRange k
  suffices ∀ l : List (Fin n), l.Nodup → k ∈ l →
      (l.map (fun i => if i = k then v else f i)).sum + f k = (l.map f).sum + v
    from this (List.finRange n) hnodup hmem
  intro l hnd hm
  induction l with
  | nil => cases hm
  | cons x xs ih =>
    have ⟨hx_not_mem, hnd_xs⟩ := List.nodup_cons.mp hnd
    simp only [List.map_cons, List.sum_cons]
    rcases List.mem_cons.mp hm with rfl | hxs
    · simp only [↓reduceIte]
      have heq : xs.map (fun i => if i = k then v else f i) = xs.map f := by
        apply List.map_congr_left
        intro y hy
        have hne : y ≠ k := fun h => hx_not_mem (h ▸ hy)
        simp [hne]
      rw [heq]
      omega
    · have hne : x ≠ k := fun h => hx_not_mem (h ▸ hxs)
      simp only [hne, ↓reduceIte]
      have hrec := ih hnd_xs hxs
      omega

/-- Scaling `finSum` by a constant on the left. -/
theorem finSum_mul_left {n : Nat} (c : Nat) (f : Fin n → Nat) :
    finSum (fun i => c * f i) = c * finSum f := by
  simp only [finSum_eq_list_sum]
  suffices ∀ l : List (Fin n), (l.map (fun i => c * f i)).sum = c * (l.map f).sum
    from this (List.finRange n)
  intro l
  induction l with
  | nil => simp
  | cons x xs ih =>
    simp only [List.map_cons, List.sum_cons, ih, Nat.mul_add]

/-- Swapping two nested `finSum`s. -/
theorem finSum_comm {m n : Nat} (f : Fin m → Fin n → Nat) :
    finSum (fun i => finSum (fun j => f i j)) =
    finSum (fun j => finSum (fun i => f i j)) := by
  simp only [finSum_eq_list_sum]
  suffices ∀ (la : List (Fin m)) (lb : List (Fin n)),
      (la.map (fun i => (lb.map (fun j => f i j)).sum)).sum =
      (lb.map (fun j => (la.map (fun i => f i j)).sum)).sum
    from this (List.finRange m) (List.finRange n)
  intro la lb
  induction la with
  | nil =>
    simp only [List.map_nil, List.sum_nil]
    induction lb with
    | nil => rfl
    | cons y ys ihy =>
      simp only [List.map_cons, List.sum_cons] at ihy ⊢
      omega
  | cons x xs ihx =>
    simp only [List.map_cons, List.sum_cons, ihx]
    clear ihx
    induction lb with
    | nil => simp
    | cons y ys ihy =>
      simp only [List.map_cons, List.sum_cons]
      omega

/-- Splitting `finSum` by a boolean predicate `p`. -/
theorem finSum_split_pred {n : Nat} (p : Fin n → Bool) (f : Fin n → Nat) :
    finSum f = finSum (fun i => if p i then f i else 0) +
               finSum (fun i => if !p i then f i else 0) := by
  rw [← finSum_add]
  congr 1
  funext i
  cases p i <;> simp

/-- `finSum` of a single indicator `if i = k then v else 0` equals `v`. -/
theorem finSum_ite_eq {n : Nat} (k : Fin n) (v : Nat) :
    finSum (fun i => if i = k then v else 0) = v := by
  have h := finSum_update (fun _ : Fin n => 0) k v
  rw [finSum_zero] at h
  omega

/-- `finSum` of `f` bounded by `finSum` of a constant `c` on a subset `p`. -/
theorem finSum_le_count_mul {n : Nat} (p : Fin n → Bool) (f : Fin n → Nat) (c : Nat)
    (h : ∀ i, p i = true → f i ≤ c) :
    finSum (fun i => if p i then f i else 0) ≤
    c * finSum (fun i => if p i then 1 else 0) := by
  rw [← finSum_mul_left]
  apply finSum_le_finSum
  intro i
  cases hp : p i with
  | false => simp
  | true => simp [h i hp]

/-- An Island Logistics problem instance. -/
structure Instance where
  numLocs    : Nat
  road       : Fin numLocs → Fin numLocs → Bool
  road_symm  : ∀ u v, road u v = road v u
  road_irref : ∀ u, road u u = false
  isPort     : Fin numLocs → Bool
  numTrucks  : Nat
  truckCap   : Fin numTrucks → Nat
  numFerries : Nat
  ferryCap   : Fin numFerries → Nat
  ferryServed : Fin numFerries → Fin numLocs → Bool
  numPkgs    : Nat
  pkgWeight  : Fin numPkgs → Nat
  pkgWeight_pos : ∀ p, 0 < pkgWeight p
  pkgGoal    : Fin numPkgs → Fin numLocs

/-- Position of a truck: either standing at a location or aboard a ferry. -/
inductive TruckPos (I : Instance) where
  | atLoc   (l : Fin I.numLocs)
  | onFerry (f : Fin I.numFerries)
  deriving DecidableEq

/-- Position of a package: either on the ground at a location or inside a truck. -/
inductive PkgPos (I : Instance) where
  | atLoc   (l : Fin I.numLocs)
  | inTruck (t : Fin I.numTrucks)
  deriving DecidableEq

/-- Complete physical world state of an Island Logistics instance. -/
structure State (I : Instance) where
  truckLoc : Fin I.numTrucks  → TruckPos I
  ferryLoc : Fin I.numFerries → Fin I.numLocs
  pkgLoc   : Fin I.numPkgs    → PkgPos I

/-- Physical location of a truck (port location of its ferry if aboard). -/
def State.truckPhysLoc {I : Instance} (s : State I) (t : Fin I.numTrucks) : Fin I.numLocs :=
  match s.truckLoc t with
  | .atLoc l   => l
  | .onFerry f => s.ferryLoc f

/-- Ferry that truck `t` is currently aboard, if any. -/
def State.truckOnFerry {I : Instance} (s : State I) (t : Fin I.numTrucks) : Option (Fin I.numFerries) :=
  match s.truckLoc t with
  | .atLoc _   => none
  | .onFerry f => some f

/-- Physical location of a package (physical location of its carrier truck if loaded). -/
def State.pkgPhysLoc {I : Instance} (s : State I) (p : Fin I.numPkgs) : Fin I.numLocs :=
  match s.pkgLoc p with
  | .atLoc l   => l
  | .inTruck t => s.truckPhysLoc t

/-- Ferry that package `p` is currently aboard (via its carrier truck), if any. -/
def State.pkgOnFerry {I : Instance} (s : State I) (p : Fin I.numPkgs) : Option (Fin I.numFerries) :=
  match s.pkgLoc p with
  | .atLoc _   => none
  | .inTruck t => s.truckOnFerry t

/-- Whether package `p` is on the ground (not inside any truck). -/
def State.pkgIsGround {I : Instance} (s : State I) (p : Fin I.numPkgs) : Bool :=
  match s.pkgLoc p with
  | .atLoc _   => true
  | .inTruck _ => false

/-- Whether package `p` is currently delivered (on the ground at its goal). -/
def State.pkgDelivered {I : Instance} (s : State I) (p : Fin I.numPkgs) : Bool :=
  decide (s.pkgLoc p = .atLoc (I.pkgGoal p))

/-- Current total package weight carried by truck `t`. -/
def State.truckLoad {I : Instance} (s : State I) (t : Fin I.numTrucks) : Nat :=
  finSum (fun p => if s.pkgLoc p = .inTruck t then I.pkgWeight p else 0)

/-- Number of trucks currently aboard ferry `f`. -/
def State.ferryCount {I : Instance} (s : State I) (f : Fin I.numFerries) : Nat :=
  finSum (fun t => if s.truckLoc t = .onFerry f then 1 else 0)

/-- Goal predicate matching `ex1.py:L824-L825` (`state[2] == self.pkg_goals`). -/
def goalTest (I : Instance) (s : State I) : Prop :=
  ∀ p : Fin I.numPkgs, s.pkgLoc p = .atLoc (I.pkgGoal p)

/-- Physical validity invariants of a reachable state. -/
structure ValidState (I : Instance) (s : State I) : Prop where
  load_le_cap   : ∀ t, s.truckLoad t ≤ I.truckCap t
  aboard_le_cap : ∀ f, s.ferryCount f ≤ I.ferryCap f
  ferry_served  : ∀ f, I.ferryServed f (s.ferryLoc f) = true

/-- Helper function update on `Fin n`. -/
def updateFn {α : Type} {n : Nat} (f : Fin n → α) (k : Fin n) (v : α) : Fin n → α :=
  fun i => if i = k then v else f i

/-- The 6 legal actions in the Island Logistics domain. -/
inductive Action (I : Instance) where
  | drive     (t : Fin I.numTrucks)  (u v : Fin I.numLocs)
  | load      (p : Fin I.numPkgs)    (t : Fin I.numTrucks)
  | unload    (p : Fin I.numPkgs)    (t : Fin I.numTrucks)
  | board     (t : Fin I.numTrucks)  (f : Fin I.numFerries)
  | disembark (t : Fin I.numTrucks)  (f : Fin I.numFerries)
  | sail      (f : Fin I.numFerries) (u v : Fin I.numLocs)
  deriving DecidableEq

/-- Exact single-step transition relation matching the Island Logistics domain rules. -/
inductive Step (I : Instance) : State I → Action I → State I → Prop where
  | drive {s : State I} {t : Fin I.numTrucks} {u v : Fin I.numLocs}
      (ht : s.truckLoc t = .atLoc u)
      (hne : u ≠ v)
      (hroad : I.road u v = true) :
      Step I s (.drive t u v)
        { s with truckLoc := updateFn s.truckLoc t (.atLoc v) }
  | load {s : State I} {p : Fin I.numPkgs} {t : Fin I.numTrucks} {l : Fin I.numLocs}
      (ht : s.truckLoc t = .atLoc l)
      (hp : s.pkgLoc p = .atLoc l)
      (hcap : s.truckLoad t + I.pkgWeight p ≤ I.truckCap t) :
      Step I s (.load p t)
        { s with pkgLoc := updateFn s.pkgLoc p (.inTruck t) }
  | unload {s : State I} {p : Fin I.numPkgs} {t : Fin I.numTrucks} {l : Fin I.numLocs}
      (ht : s.truckLoc t = .atLoc l)
      (hp : s.pkgLoc p = .inTruck t) :
      Step I s (.unload p t)
        { s with pkgLoc := updateFn s.pkgLoc p (.atLoc l) }
  | board {s : State I} {t : Fin I.numTrucks} {f : Fin I.numFerries}
      (ht : s.truckLoc t = .atLoc (s.ferryLoc f))
      (hcap : s.ferryCount f < I.ferryCap f) :
      Step I s (.board t f)
        { s with truckLoc := updateFn s.truckLoc t (.onFerry f) }
  | disembark {s : State I} {t : Fin I.numTrucks} {f : Fin I.numFerries}
      (ht : s.truckLoc t = .onFerry f) :
      Step I s (.disembark t f)
        { s with truckLoc := updateFn s.truckLoc t (.atLoc (s.ferryLoc f)) }
  | sail {s : State I} {f : Fin I.numFerries} {u v : Fin I.numLocs}
      (hf : s.ferryLoc f = u)
      (hne : u ≠ v)
      (hserved : I.ferryServed f v = true) :
      Step I s (.sail f u v)
        { s with ferryLoc := updateFn s.ferryLoc f v }

/-- A plan is a list of actions. -/
abbrev Plan (I : Instance) := List (Action I)

/-- Multi-step valid plan execution from `s` to `s'`. -/
inductive ValidPlan (I : Instance) : State I → Plan I → State I → Prop where
  | nil {s : State I} : ValidPlan I s [] s
  | cons {s s₁ s₂ : State I} {a : Action I} {π : Plan I}
      (hstep : Step I s a s₁)
      (hrest : ValidPlan I s₁ π s₂) :
      ValidPlan I s (a :: π) s₂

/-- Action cost matching `ex1.py:L583-L586`: SAIL costs 3, every other action costs 1. -/
def actionCost {I : Instance} : Action I → Nat
  | .sail _ _ _ => 3
  | _           => 1

/-- Disjoint action-set cost contributions: A_LU, A_drive, A_bd, A_sail. -/
def actionCostLU {I : Instance} : Action I → Nat
  | .load _ _   => 1
  | .unload _ _ => 1
  | _           => 0

def actionCostDrive {I : Instance} : Action I → Nat
  | .drive _ _ _ => 1
  | _            => 0

def actionCostBD {I : Instance} : Action I → Nat
  | .board _ _     => 1
  | .disembark _ _ => 1
  | _              => 0

def actionCostSail {I : Instance} : Action I → Nat
  | .sail _ _ _ => 3
  | _           => 0

/-- Total cost of a plan and its 4 pairwise-disjoint action-class components. -/
def planCost {I : Instance} (π : Plan I) : Nat :=
  (π.map actionCost).sum

def costLU {I : Instance} (π : Plan I) : Nat :=
  (π.map actionCostLU).sum

def costDrive {I : Instance} (π : Plan I) : Nat :=
  (π.map actionCostDrive).sum

def costBD {I : Instance} (π : Plan I) : Nat :=
  (π.map actionCostBD).sum

def costSail {I : Instance} (π : Plan I) : Nat :=
  (π.map actionCostSail).sum

/-- Number of SAIL actions in a plan (so `costSail π = 3 * sailCount π`). -/
def sailCount {I : Instance} (π : Plan I) : Nat :=
  (π.map (fun a => match a with | .sail _ _ _ => 1 | _ => 0)).sum

theorem costSail_eq_three_mul_sailCount {I : Instance} (π : Plan I) :
    costSail π = 3 * sailCount π := by
  induction π with
  | nil => rfl
  | cons a rest ih =>
    simp only [costSail, sailCount, List.map_cons, List.sum_cons] at ih ⊢
    cases a <;> simp [actionCostSail] <;> omega

/-- Per-action disjointness: every action contributes to exactly one of the 4 classes. -/
theorem actionCost_partition {I : Instance} (a : Action I) :
    actionCost a = actionCostLU a + actionCostDrive a + actionCostBD a + actionCostSail a := by
  cases a <;> rfl

/-- Exact disjoint action-cost partition lemma for any plan `π`. -/
theorem planCost_partition {I : Instance} (π : Plan I) :
    planCost π = costLU π + costDrive π + costBD π + costSail π := by
  induction π with
  | nil => rfl
  | cons a rest ih =>
    simp only [planCost, costLU, costDrive, costBD, costSail, List.map_cons, List.sum_cons] at ih ⊢
    have ha := actionCost_partition a
    omega

/-- Append additivity lemmas for plan costs. -/
theorem planCost_append {I : Instance} (π₁ π₂ : Plan I) :
    planCost (π₁ ++ π₂) = planCost π₁ + planCost π₂ := by
  simp [planCost]

theorem costLU_append {I : Instance} (π₁ π₂ : Plan I) :
    costLU (π₁ ++ π₂) = costLU π₁ + costLU π₂ := by
  simp [costLU]

theorem costDrive_append {I : Instance} (π₁ π₂ : Plan I) :
    costDrive (π₁ ++ π₂) = costDrive π₁ + costDrive π₂ := by
  simp [costDrive]

theorem costBD_append {I : Instance} (π₁ π₂ : Plan I) :
    costBD (π₁ ++ π₂) = costBD π₁ + costBD π₂ := by
  simp [costBD]

theorem costSail_append {I : Instance} (π₁ π₂ : Plan I) :
    costSail (π₁ ++ π₂) = costSail π₁ + costSail π₂ := by
  simp [costSail]

/-- `ValidState` is preserved by every legal single step `Step`. -/
theorem validState_step {I : Instance} {s s' : State I} {a : Action I}
    (hv : ValidState I s) (hstep : Step I s a s') : ValidState I s' := by
  cases hstep with
  | @drive t u v ht hne hroad =>
    refine ⟨hv.load_le_cap, ?_, hv.ferry_served⟩
    intro f
    have hle : ({ s with truckLoc := updateFn s.truckLoc t (.atLoc v) } : State I).ferryCount f ≤ s.ferryCount f := by
      apply finSum_le_finSum
      intro t'
      by_cases h : t' = t
      · subst h; simp [updateFn]
      · simp [updateFn, h]
    exact Nat.le_trans hle (hv.aboard_le_cap f)
  | @load p t l ht hp hcap =>
    refine ⟨?_, hv.aboard_le_cap, hv.ferry_served⟩
    intro t'
    by_cases heq : t' = t
    · subst heq
      have hupd := finSum_update
        (fun p' => if s.pkgLoc p' = .inTruck t' then I.pkgWeight p' else 0) p (I.pkgWeight p)
      have hnot : s.pkgLoc p ≠ .inTruck t' := by rw [hp]; intro h; cases h
      simp only [hnot, ↓reduceIte, Nat.add_zero] at hupd
      have hload : ({ s with pkgLoc := updateFn s.pkgLoc p (.inTruck t') } : State I).truckLoad t' =
                   s.truckLoad t' + I.pkgWeight p := by
        unfold State.truckLoad
        have hfn : (fun p' => if updateFn s.pkgLoc p (.inTruck t') p' = .inTruck t' then I.pkgWeight p' else 0) =
                   (fun p' => if p' = p then I.pkgWeight p else if s.pkgLoc p' = .inTruck t' then I.pkgWeight p' else 0) := by
          funext p'; by_cases hpp : p' = p <;> simp [updateFn, hpp]
        rw [hfn]
        exact hupd
      rw [hload]
      exact hcap
    · have hle : ({ s with pkgLoc := updateFn s.pkgLoc p (.inTruck t) } : State I).truckLoad t' ≤ s.truckLoad t' := by
        apply finSum_le_finSum
        intro p'
        by_cases hpp : p' = p
        · subst hpp; simp [updateFn, Ne.symm heq]
        · simp [updateFn, hpp]
      exact Nat.le_trans hle (hv.load_le_cap t')
  | @unload p t l ht hp =>
    refine ⟨?_, hv.aboard_le_cap, hv.ferry_served⟩
    intro t'
    have hle : ({ s with pkgLoc := updateFn s.pkgLoc p (.atLoc l) } : State I).truckLoad t' ≤ s.truckLoad t' := by
      apply finSum_le_finSum
      intro p'
      by_cases hpp : p' = p
      · subst hpp; simp [updateFn]
      · simp [updateFn, hpp]
    exact Nat.le_trans hle (hv.load_le_cap t')
  | @board t f ht hcap =>
    refine ⟨hv.load_le_cap, ?_, hv.ferry_served⟩
    intro f'
    by_cases heq : f' = f
    · subst heq
      have hupd := finSum_update
        (fun t' => if s.truckLoc t' = .onFerry f' then 1 else 0) t 1
      have hnot : s.truckLoc t ≠ .onFerry f' := by rw [ht]; intro h; cases h
      simp only [hnot, ↓reduceIte, Nat.add_zero] at hupd
      have hcnt : ({ s with truckLoc := updateFn s.truckLoc t (.onFerry f') } : State I).ferryCount f' =
                  s.ferryCount f' + 1 := by
        unfold State.ferryCount
        have hfn : (fun t' => if updateFn s.truckLoc t (.onFerry f') t' = .onFerry f' then 1 else 0) =
                   (fun t' => if t' = t then 1 else if s.truckLoc t' = .onFerry f' then 1 else 0) := by
          funext t'; by_cases htt : t' = t <;> simp [updateFn, htt]
        rw [hfn]
        exact hupd
      rw [hcnt]
      omega
    · have hle : ({ s with truckLoc := updateFn s.truckLoc t (.onFerry f) } : State I).ferryCount f' ≤ s.ferryCount f' := by
        apply finSum_le_finSum
        intro t'
        by_cases htt : t' = t
        · subst htt; simp [updateFn, Ne.symm heq]
        · simp [updateFn, htt]
      exact Nat.le_trans hle (hv.aboard_le_cap f')
  | @disembark t f ht =>
    refine ⟨hv.load_le_cap, ?_, hv.ferry_served⟩
    intro f'
    have hle : ({ s with truckLoc := updateFn s.truckLoc t (.atLoc (s.ferryLoc f)) } : State I).ferryCount f' ≤ s.ferryCount f' := by
      apply finSum_le_finSum
      intro t'
      by_cases htt : t' = t
      · subst htt; simp [updateFn]
      · simp [updateFn, htt]
    exact Nat.le_trans hle (hv.aboard_le_cap f')
  | @sail f u v hf hne hserved =>
    refine ⟨hv.load_le_cap, hv.aboard_le_cap, ?_⟩
    intro f'
    by_cases heq : f' = f
    · subst heq; simp [updateFn, hserved]
    · simp [updateFn, heq, hv.ferry_served f']

/-- `ValidState` is preserved along any multi-step valid plan. -/
theorem validState_plan {I : Instance} {s s' : State I} {π : Plan I}
    (hv : ValidState I s) (hplan : ValidPlan I s π s') : ValidState I s' := by
  induction hplan with
  | nil => exact hv
  | cons hstep _ ih => exact ih (validState_step hv hstep)

/-- Deterministic state transition function matching `Step`. -/
def applyAction {I : Instance} (s : State I) : Action I → State I
  | .drive t _ v    => { s with truckLoc := updateFn s.truckLoc t (.atLoc v) }
  | .load p t       => { s with pkgLoc := updateFn s.pkgLoc p (.inTruck t) }
  | .unload p t     => { s with pkgLoc := updateFn s.pkgLoc p (.atLoc (s.truckPhysLoc t)) }
  | .board t f      => { s with truckLoc := updateFn s.truckLoc t (.onFerry f) }
  | .disembark t f  => { s with truckLoc := updateFn s.truckLoc t (.atLoc (s.ferryLoc f)) }
  | .sail f _ v     => { s with ferryLoc := updateFn s.ferryLoc f v }

/-- Every legal `Step` produces `applyAction s a`. -/
theorem step_eq_applyAction {I : Instance} {s s' : State I} {a : Action I}
    (hstep : Step I s a s') : s' = applyAction s a := by
  cases hstep with
  | drive _ _ _ => rfl
  | load _ _ _ => rfl
  | @unload p t l ht _ =>
    simp [applyAction, State.truckPhysLoc, ht]
  | board _ _ => rfl
  | disembark _ => rfl
  | sail _ _ _ => rfl

/-- Master combination theorem matching `ex1.py:L1625-L1652`. -/
theorem master_combination {I : Instance} (π : Plan I)
    (h_lu h_drive h_bd h_sail h_pack_truck h_excl h_single : Nat)
    (h1 : h_lu ≤ costLU π)
    (h2 : h_drive ≤ costDrive π)
    (h3 : h_bd ≤ costBD π)
    (h4 : h_sail ≤ costSail π)
    (h5 : h_pack_truck ≤ costDrive π + costBD π)
    (h6 : h_excl ≤ costDrive π + costBD π + costSail π)
    (h7 : h_single ≤ costDrive π + costBD π + costSail π) :
    h_lu + max (max (h_drive + h_bd) h_pack_truck + h_sail) (max h_excl h_single) ≤ planCost π := by
  rw [planCost_partition π]
  omega

end IslandLogistics
