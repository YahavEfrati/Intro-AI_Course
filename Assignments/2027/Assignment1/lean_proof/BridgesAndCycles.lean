/-
Module 3: BridgesAndCycles.lean

Formalizes and proves admissibility of Bound C's `h_drive = h_bridge + h_nb`:
1. Road bridges (`h_bridge_base`, ex1.py:L454-L514, L1472-L1569):
   each G_rf road bridge edge isolates a 2-sided cut whose crossings are exclusively
   DRIVE actions on that edge, so summing `_flux_lb` over distinct bridges ≤ bridge drives.
2. Directed bridge precedence cycles (`_bridge_cycle_extra`, ex1.py:L1249-L1311, L1544-L1571):
   pairwise-disjoint 0-truck unit-flux bridge regions forming a directed package cycle
   cannot all be crossed ≤ 2 times per edge; at least one region's chain is crossed ≥ 3
   times on every edge, forcing ≥ min_len extra crossings.
3. Contracted non-bridge roads (`h_nb = max(nb_p, nb_mst)`, ex1.py:L96-L139, L522-L546, L1573-L1607):
   - `nb_p` via `packLB_plan_sound`
   - `nb_mst` via Prim's MST on the metric closure (proved via rooted-tree path reversal)
   - Combined `h_bridge + h_nb ≤ costDrive π` by edge disjointness.
-/

import Domain
import PackingAndFlux

namespace IslandLogistics

-- ==============================================================================
-- 1. ROAD BRIDGES & `h_bridge_base` (ex1.py:L454-L514, L1472-L1569)
-- ==============================================================================

/-- Predicate matching a DRIVE action along undirected road edge `{u, v}`. -/
def isEdgeDrive {I : Instance} (u v : Fin I.numLocs) : Action I → Bool
  | .drive _ x y => (decide (x = u) && decide (y = v)) || (decide (x = v) && decide (y = u))
  | _            => false

def isDirEdgeDrive {I : Instance} (u v : Fin I.numLocs) : Action I → Bool
  | .drive _ x y => decide (x = u) && decide (y = v)
  | _            => false

/-- Number of DRIVE actions in `π` crossing undirected edge `{u, v}`. -/
def bridgeDriveCount {I : Instance} (u v : Fin I.numLocs) (π : Plan I) : Nat :=
  countActions (isEdgeDrive u v) π

/-- A road bridge edge of `G_rf` separating `inA = true` from `inA = false` inside `inComp`. -/
structure BridgeEdge (I : Instance) where
  u      : Fin I.numLocs
  v      : Fin I.numLocs
  hroad  : I.road u v = true
  inComp : Fin I.numLocs → Bool
  inA    : Fin I.numLocs → Bool
  hcl    : CompClosed I inComp
  hu_in  : inComp u = true
  hv_in  : inComp v = true
  hu_A   : inA u = true
  hv_A   : inA v = false
  /-- No other road crosses between `inA = true` and `inA = false` inside `inComp`. -/
  road_cut : ∀ x y, inComp x = true → inComp y = true → I.road x y = true →
    inA x ≠ inA y → (x = u ∧ y = v) ∨ (x = v ∧ y = u)
  /-- No active ferry (cap > 0) connects `inA = true` and `inA = false` inside `inComp`. -/
  ferry_cut : ∀ f x y, 0 < I.ferryCap f → inComp x = true → inComp y = true →
    I.ferryServed f x = true → I.ferryServed f y = true → inA x = inA y

/-- Crossing a bridge edge in a single legal step can ONLY happen via `DRIVE{t, u, v}` / `DRIVE{t, v, u}`. -/
theorem bridge_step_cross_iff {I : Instance} (b : BridgeEdge I)
    {sa sb : State I} {a : Action I} (hv : ValidState I sa) (hstep : Step I sa a sb) :
    finSum (fun t => if b.inComp (sa.truckPhysLoc t) then stepTruckCrossAB b.inComp b.inA sa sb t else 0) =
      (if isDirEdgeDrive b.u b.v a then 1 else 0) ∧
    finSum (fun t => if b.inComp (sa.truckPhysLoc t) then stepTruckCrossBA b.inComp b.inA sa sb t else 0) =
      (if isDirEdgeDrive b.v b.u a then 1 else 0) := by
  cases hstep with
  | @drive t x y ht hne hroad =>
    have hfn_ab : (fun t' => if b.inComp (sa.truckPhysLoc t') then
        stepTruckCrossAB b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.atLoc y) } t' else 0) =
        (fun t' => if t' = t then
          (if b.inComp x && b.inA x && !b.inA y then 1 else 0) else 0) := by
      funext t'
      by_cases htt : t' = t
      · subst htt
        cases h1 : b.inComp x <;> cases h2 : b.inA x <;> cases h3 : b.inA y <;>
          simp [State.truckPhysLoc, ht, updateFn, stepTruckCrossAB, h1, h2, h3]
      · simp [State.truckPhysLoc, updateFn, htt, stepTruckCrossAB]
    have hfn_ba : (fun t' => if b.inComp (sa.truckPhysLoc t') then
        stepTruckCrossBA b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.atLoc y) } t' else 0) =
        (fun t' => if t' = t then
          (if b.inComp x && !b.inA x && b.inA y then 1 else 0) else 0) := by
      funext t'
      by_cases htt : t' = t
      · subst htt
        cases h1 : b.inComp x <;> cases h2 : b.inA x <;> cases h3 : b.inA y <;>
          simp [State.truckPhysLoc, ht, updateFn, stepTruckCrossBA, h1, h2, h3]
      · simp [State.truckPhysLoc, updateFn, htt, stepTruckCrossBA]
    rw [hfn_ab, finSum_ite_eq, hfn_ba, finSum_ite_eq]
    have hy_in : b.inComp y = b.inComp x := by
      have h := b.hcl (Step.drive ht hne hroad) t
      simpa [State.truckPhysLoc, ht, updateFn] using h
    constructor
    · simp only [isDirEdgeDrive]
      cases hxc : b.inComp x with
      | false =>
        by_cases hxy : x = b.u ∧ y = b.v
        · rcases hxy with ⟨rfl, rfl⟩; rw [b.hu_in] at hxc; cases hxc
        · have hfalse : (decide (x = b.u) && decide (y = b.v)) = false := by
            by_cases hx : x = b.u <;> by_cases hy : y = b.v <;> simp_all
          simp [hfalse]
      | true =>
        cases hxa : b.inA x <;> cases hya : b.inA y
        · have hne_uv : ¬ (x = b.u ∧ y = b.v) := by rintro ⟨rfl, _⟩; rw [b.hu_A] at hxa; cases hxa
          have hf : (decide (x = b.u) && decide (y = b.v)) = false := by
            by_cases hx : x = b.u <;> by_cases hy : y = b.v <;> simp_all
          simp [hf]
        · have hne_uv : ¬ (x = b.u ∧ y = b.v) := by rintro ⟨rfl, _⟩; rw [b.hu_A] at hxa; cases hxa
          have hf : (decide (x = b.u) && decide (y = b.v)) = false := by
            by_cases hx : x = b.u <;> by_cases hy : y = b.v <;> simp_all
          simp [hf]
        · have hrc := b.road_cut x y hxc (hy_in ▸ hxc) hroad (by rw [hxa, hya]; decide)
          rcases hrc with ⟨rfl, rfl⟩ | ⟨rfl, rfl⟩
          · simp
          · rw [b.hv_A] at hxa; cases hxa
        · have hne_uv : ¬ (x = b.u ∧ y = b.v) := by rintro ⟨_, rfl⟩; rw [b.hv_A] at hya; cases hya
          have hf : (decide (x = b.u) && decide (y = b.v)) = false := by
            by_cases hx : x = b.u <;> by_cases hy : y = b.v <;> simp_all
          simp [hf]
    · simp only [isDirEdgeDrive]
      cases hxc : b.inComp x with
      | false =>
        by_cases hxy : x = b.v ∧ y = b.u
        · rcases hxy with ⟨rfl, rfl⟩; rw [b.hv_in] at hxc; cases hxc
        · have hf : (decide (x = b.v) && decide (y = b.u)) = false := by
            by_cases hx : x = b.v <;> by_cases hy : y = b.u <;> simp_all
          simp [hf]
      | true =>
        cases hxa : b.inA x <;> cases hya : b.inA y
        · have hne_vu : ¬ (x = b.v ∧ y = b.u) := by rintro ⟨_, rfl⟩; rw [b.hu_A] at hya; cases hya
          have hf : (decide (x = b.v) && decide (y = b.u)) = false := by
            by_cases hx : x = b.v <;> by_cases hy : y = b.u <;> simp_all
          simp [hf]
        · have hrc := b.road_cut x y hxc (hy_in ▸ hxc) hroad (by rw [hxa, hya]; decide)
          rcases hrc with ⟨rfl, rfl⟩ | ⟨rfl, rfl⟩
          · rw [b.hu_A] at hxa; cases hxa
          · simp
        · have hne_vu : ¬ (x = b.v ∧ y = b.u) := by rintro ⟨rfl, _⟩; rw [b.hv_A] at hxa; cases hxa
          have hf : (decide (x = b.v) && decide (y = b.u)) = false := by
            by_cases hx : x = b.v <;> by_cases hy : y = b.u <;> simp_all
          simp [hf]
        · have hne_vu : ¬ (x = b.v ∧ y = b.u) := by rintro ⟨rfl, _⟩; rw [b.hv_A] at hxa; cases hxa
          have hf : (decide (x = b.v) && decide (y = b.u)) = false := by
            by_cases hx : x = b.v <;> by_cases hy : y = b.u <;> simp_all
          simp [hf]
  | @load p t l _ _ _ =>
    constructor
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossAB b.inComp b.inA sa { sa with pkgLoc := updateFn sa.pkgLoc p (.inTruck t) } t' else 0) = (fun _ => 0) := by
        funext t'; simp [stepTruckCrossAB, State.truckPhysLoc]
      rw [hz, finSum_zero]
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossBA b.inComp b.inA sa { sa with pkgLoc := updateFn sa.pkgLoc p (.inTruck t) } t' else 0) = (fun _ => 0) := by
        funext t'; simp [stepTruckCrossBA, State.truckPhysLoc]
      rw [hz, finSum_zero]
  | @unload p t l _ _ =>
    constructor
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossAB b.inComp b.inA sa { sa with pkgLoc := updateFn sa.pkgLoc p (.atLoc l) } t' else 0) = (fun _ => 0) := by
        funext t'; simp [stepTruckCrossAB, State.truckPhysLoc]
      rw [hz, finSum_zero]
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossBA b.inComp b.inA sa { sa with pkgLoc := updateFn sa.pkgLoc p (.atLoc l) } t' else 0) = (fun _ => 0) := by
        funext t'; simp [stepTruckCrossBA, State.truckPhysLoc]
      rw [hz, finSum_zero]
  | @board t f ht _ =>
    have hphys : ∀ t', ({ sa with truckLoc := updateFn sa.truckLoc t (.onFerry f) } : State I).truckPhysLoc t' =
        sa.truckPhysLoc t' := by
      intro t'; by_cases htt : t' = t
      · subst htt; simp [State.truckPhysLoc, updateFn, ht]
      · simp [State.truckPhysLoc, updateFn, htt]
    constructor
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossAB b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.onFerry f) } t' else 0) =
          (fun _ => 0) := by funext t'; simp [stepTruckCrossAB, hphys t']
      rw [hz, finSum_zero]
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossBA b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.onFerry f) } t' else 0) =
          (fun _ => 0) := by funext t'; simp [stepTruckCrossBA, hphys t']
      rw [hz, finSum_zero]
  | @disembark t f ht =>
    have hphys : ∀ t', ({ sa with truckLoc := updateFn sa.truckLoc t (.atLoc (sa.ferryLoc f)) } : State I).truckPhysLoc t' =
        sa.truckPhysLoc t' := by
      intro t'; by_cases htt : t' = t
      · subst htt; simp [State.truckPhysLoc, updateFn, ht]
      · simp [State.truckPhysLoc, updateFn, htt]
    constructor
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossAB b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.atLoc (sa.ferryLoc f)) } t' else 0) =
          (fun _ => 0) := by funext t'; simp [stepTruckCrossAB, hphys t']
      rw [hz, finSum_zero]
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossBA b.inComp b.inA sa { sa with truckLoc := updateFn sa.truckLoc t (.atLoc (sa.ferryLoc f)) } t' else 0) =
          (fun _ => 0) := by funext t'; simp [stepTruckCrossBA, hphys t']
      rw [hz, finSum_zero]
  | @sail f x y hf hne hserved =>
    -- If any truck t' is aboard f, then ferryCap f ≥ ferryCount f ≥ 1, so by `b.ferry_cut`, inA x = inA y!
    have hsame : ∀ t', b.inComp (sa.truckPhysLoc t') = true →
        b.inA (({ sa with ferryLoc := updateFn sa.ferryLoc f y } : State I).truckPhysLoc t') = b.inA (sa.truckPhysLoc t') := by
      intro t' hin_t'
      cases htl : sa.truckLoc t' with
      | atLoc l => simp [State.truckPhysLoc, htl]
      | onFerry f' =>
        by_cases hff : f' = f
        · subst hff
          have hpos_f : 0 < I.ferryCap f' := by
            have hle1 : 1 ≤ sa.ferryCount f' := by
              have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry f' then 1 else 0) t'
              simpa [State.ferryCount, htl] using h
            have hcap := hv.aboard_le_cap f'
            omega
          have hx_in : b.inComp x = true := by simpa [State.truckPhysLoc, htl, hf] using hin_t'
          have hy_in : b.inComp y = true := by
            have hc := b.hcl (Step.sail hf hne hserved) t'
            simpa [State.truckPhysLoc, htl, updateFn, hf, hx_in] using hc
          have hx_sv : I.ferryServed f' x = true := hf ▸ hv.ferry_served f'
          have heq := b.ferry_cut f' x y hpos_f hx_in hy_in hx_sv hserved
          simp [State.truckPhysLoc, htl, updateFn, hf, heq]
        · simp [State.truckPhysLoc, htl, updateFn, hff]
    constructor
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossAB b.inComp b.inA sa { sa with ferryLoc := updateFn sa.ferryLoc f y } t' else 0) =
          (fun _ => 0) := by
        funext t'
        cases hc : b.inComp (sa.truckPhysLoc t') with
        | false => simp
        | true => simp [stepTruckCrossAB, hsame t' hc]
      rw [hz, finSum_zero]
    · simp only [isDirEdgeDrive, Bool.false_eq_true, ↓reduceIte]
      have hz : (fun t' => if b.inComp (sa.truckPhysLoc t') then
          stepTruckCrossBA b.inComp b.inA sa { sa with ferryLoc := updateFn sa.ferryLoc f y } t' else 0) =
          (fun _ => 0) := by
        funext t'
        cases hc : b.inComp (sa.truckPhysLoc t') with
        | false => simp
        | true => simp [stepTruckCrossBA, hsame t' hc]
      rw [hz, finSum_zero]

/-- Total truck crossings of bridge `b` along any valid plan equal directed DRIVE counts on `b`. -/
theorem bridge_plan_cross_eq_drives {I : Instance} (b : BridgeEdge I)
    {s₁ s₂ : State I} {π : Plan I} (hv : ValidState I s₁) (hp : ValidPlan I s₁ π s₂) :
    finSum (fun t => if b.inComp (s₁.truckPhysLoc t) then planTruckCrossAB b.inComp b.inA s₁ π t else 0) =
      countActions (isDirEdgeDrive b.u b.v) π ∧
    finSum (fun t => if b.inComp (s₁.truckPhysLoc t) then planTruckCrossBA b.inComp b.inA s₁ π t else 0) =
      countActions (isDirEdgeDrive b.v b.u) π := by
  induction hp with
  | nil =>
    simp only [planTruckCrossAB, planTruckCrossBA, countActions, List.map_nil, List.sum_nil, ite_self, finSum_zero, and_self]
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    have hin_eq : ∀ t, b.inComp (sb.truckPhysLoc t) = b.inComp (sa.truckPhysLoc t) := b.hcl hstep
    have ⟨ih1, ih2⟩ := ih (validState_step hv hstep)
    have ⟨hs1, hs2⟩ := bridge_step_cross_iff b hv hstep
    constructor
    · have hsp : finSum (fun t => if b.inComp (sa.truckPhysLoc t) then planTruckCrossAB b.inComp b.inA sa (a :: rest) t else 0) =
          finSum (fun t => if b.inComp (sa.truckPhysLoc t) then stepTruckCrossAB b.inComp b.inA sa sb t else 0) +
          finSum (fun t => if b.inComp (sb.truckPhysLoc t) then planTruckCrossAB b.inComp b.inA sb rest t else 0) := by
        rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossAB, ← hsb_eq, hin_eq t]; split <;> simp
      rw [hsp, hs1, ih1]; simp [countActions]
    · have hsp : finSum (fun t => if b.inComp (sa.truckPhysLoc t) then planTruckCrossBA b.inComp b.inA sa (a :: rest) t else 0) =
          finSum (fun t => if b.inComp (sa.truckPhysLoc t) then stepTruckCrossBA b.inComp b.inA sa sb t else 0) +
          finSum (fun t => if b.inComp (sb.truckPhysLoc t) then planTruckCrossBA b.inComp b.inA sb rest t else 0) := by
        rw [← finSum_add]; congr 1; funext t; simp only [planTruckCrossBA, ← hsb_eq, hin_eq t]; split <;> simp
      rw [hsp, hs2, ih2]; simp [countActions]

theorem bridgeDriveCount_eq_dir_sum {I : Instance} (b : BridgeEdge I) (π : Plan I) :
    bridgeDriveCount b.u b.v π =
    countActions (isDirEdgeDrive b.u b.v) π + countActions (isDirEdgeDrive b.v b.u) π := by
  have hne : b.u ≠ b.v := by
    intro h; have hr := b.hroad; rw [h, I.road_irref] at hr; cases hr
  unfold bridgeDriveCount countActions
  induction π with
  | nil => rfl
  | cons a rest ih =>
    simp only [List.map_cons, List.sum_cons]
    have h1 : (if isEdgeDrive b.u b.v a = true then 1 else 0) =
              (if isDirEdgeDrive b.u b.v a = true then 1 else 0) +
              (if isDirEdgeDrive b.v b.u a = true then 1 else 0) := by
      cases a with
      | drive t x y =>
        simp only [isEdgeDrive, isDirEdgeDrive]
        by_cases h1 : x = b.u ∧ y = b.v
        · rcases h1 with ⟨rfl, rfl⟩
          simp [hne, Ne.symm hne]
        · by_cases h2 : x = b.v ∧ y = b.u
          · rcases h2 with ⟨rfl, rfl⟩
            simp [hne, Ne.symm hne]
          · have hf1 : (decide (x = b.u) && decide (y = b.v)) = false := by
              by_cases hx : x = b.u <;> by_cases hy : y = b.v <;> simp_all
            have hf2 : (decide (x = b.v) && decide (y = b.u)) = false := by
              by_cases hx : x = b.v <;> by_cases hy : y = b.u <;> simp_all
            simp [hf1, hf2]
      | load _ _ => simp [isEdgeDrive, isDirEdgeDrive]
      | unload _ _ => simp [isEdgeDrive, isDirEdgeDrive]
      | board _ _ => simp [isEdgeDrive, isDirEdgeDrive]
      | disembark _ _ => simp [isEdgeDrive, isDirEdgeDrive]
      | sail _ _ _ => simp [isEdgeDrive, isDirEdgeDrive]
    omega

/-- Component max dynamic effective capacity (`c_cap`, ex1.py:L1475-L1484). -/
def compMaxEffCap (I : Instance) (s : State I) (inComp : Fin I.numLocs → Bool) : Nat :=
  listMax (((List.finRange I.numTrucks).filter (fun t => inComp (s.truckPhysLoc t))).map (dynEffCap I s))

theorem compMaxEffCap_ge (I : Instance) (s : State I) (inComp : Fin I.numLocs → Bool)
    (t : Fin I.numTrucks) (ht : inComp (s.truckPhysLoc t) = true) :
    dynEffCap I s t ≤ compMaxEffCap I s inComp := by
  unfold compMaxEffCap
  apply mem_le_listMax
  rw [List.mem_map]
  exact ⟨t, List.mem_filter.mpr ⟨List.mem_finRange t, ht⟩, rfl⟩

/-- Exact per-bridge flux lower bound matching `ex1.py:L1482-L1543`. -/
def bridgeEdgeFlux (I : Instance) (s : State I) (b : BridgeEdge I) : Nat × Nat :=
  let c_cap := compMaxEffCap I s b.inComp
  if c_cap = 0 then (0, 0)
  else
    let tIn  (t : Fin I.numTrucks) := b.inComp (s.truckPhysLoc t)
    let tSide (t : Fin I.numTrucks) := b.inA (s.truckPhysLoc t)
    let m_a := finSum (fun t => if tIn t && tSide t then 1 else 0)
    let m_b := finSum (fun t => if tIn t && !tSide t then 1 else 0)
    let c_a := finSum (fun t => if tIn t && tSide t then dynEffCap I s t else 0)
    let c_b := finSum (fun t => if tIn t && !tSide t then dynEffCap I s t else 0)
    let w_ab := finSum (fun p =>
      if !s.pkgDelivered p && b.inComp (s.pkgPhysLoc p) && b.inA (s.pkgPhysLoc p) && !b.inA (I.pkgGoal p)
      then I.pkgWeight p else 0)
    let w_ba := finSum (fun p =>
      if !s.pkgDelivered p && b.inComp (s.pkgPhysLoc p) && !b.inA (s.pkgPhysLoc p) && b.inA (I.pkgGoal p)
      then I.pkgWeight p else 0)
    let h_ab := finSum (fun p =>
      if !s.pkgDelivered p && b.inComp (s.pkgPhysLoc p) && b.inA (s.pkgPhysLoc p) && !b.inA (I.pkgGoal p) &&
         decide (I.pkgWeight p > c_cap / 2)
      then 1 else 0)
    let h_ba := finSum (fun p =>
      if !s.pkgDelivered p && b.inComp (s.pkgPhysLoc p) && !b.inA (s.pkgPhysLoc p) && b.inA (I.pkgGoal p) &&
         decide (I.pkgWeight p > c_cap / 2)
      then 1 else 0)
    let need_ab := (List.finRange I.numPkgs).any (fun p =>
      !s.pkgDelivered p && s.pkgIsGround p && b.inComp (s.pkgPhysLoc p) && !b.inA (s.pkgPhysLoc p) &&
      (List.finRange I.numTrucks).all (fun t =>
        !(tIn t && !tSide t) || decide (dynEffCap I s t < I.pkgWeight p)))
    let need_ba := (List.finRange I.numPkgs).any (fun p =>
      !s.pkgDelivered p && s.pkgIsGround p && b.inComp (s.pkgPhysLoc p) && b.inA (s.pkgPhysLoc p) &&
      (List.finRange I.numTrucks).all (fun t =>
        !(tIn t && tSide t) || decide (dynEffCap I s t < I.pkgWeight p)))
    fluxLB w_ab w_ba h_ab h_ba need_ab need_ba m_a m_b c_a c_b c_cap

/-- Single-bridge admissibility theorem (`ex1.py:L1482-L1543`). -/
theorem bridgeEdgeFlux_sound {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (b : BridgeEdge I) :
    (bridgeEdgeFlux I s b).1 ≤ countActions (isDirEdgeDrive b.u b.v) π ∧
    (bridgeEdgeFlux I s b).2 ≤ countActions (isDirEdgeDrive b.v b.u) π := by
  unfold bridgeEdgeFlux
  dsimp only
  split
  · exact ⟨Nat.zero_le _, Nat.zero_le _⟩
  · rename_i hne0
    have hcap_pos : 0 < compMaxEffCap I s b.inComp := Nat.pos_of_ne_zero hne0
    have ⟨hd1, hd2⟩ := bridge_plan_cross_eq_drives b hv hp
    rw [← hd1, ← hd2]
    apply fluxLB_plan_sound hv hp hg b.inComp b.inA b.hcl _ hcap_pos (compMaxEffCap_ge I s b.inComp)
    · intro hnab
      rw [List.any_eq_true] at hnab
      rcases hnab with ⟨p, _, hpcond⟩
      simp only [Bool.and_eq_true, Bool.not_eq_true', List.all_eq_true] at hpcond
      rcases hpcond with ⟨⟨⟨⟨hnd, hgnd⟩, hin⟩, hside⟩, hall⟩
      cases hpl : s.pkgLoc p with
      | inTruck _ => simp [State.pkgIsGround, hpl] at hgnd
      | atLoc l =>
        have hphys : s.pkgPhysLoc p = l := by simp [State.pkgPhysLoc, hpl]
        refine ⟨p, l, hpl, hnd, hphys ▸ hin, hphys ▸ hside, ?_⟩
        intro t ht hts
        have h1 := hall t (List.mem_finRange t)
        simp only [Bool.or_eq_true, Bool.not_eq_true', Bool.and_eq_false_iff, Bool.not_eq_false',
                   decide_eq_true_eq] at h1
        rcases h1 with hnot | hlt
        · rcases hnot with h1 | h2
          · rw [ht] at h1; cases h1
          · rw [hts] at h2; cases h2
        · exact hlt
    · intro hnba
      rw [List.any_eq_true] at hnba
      rcases hnba with ⟨p, _, hpcond⟩
      simp only [Bool.and_eq_true, Bool.not_eq_true', List.all_eq_true] at hpcond
      rcases hpcond with ⟨⟨⟨⟨hnd, hgnd⟩, hin⟩, hside⟩, hall⟩
      cases hpl : s.pkgLoc p with
      | inTruck _ => simp [State.pkgIsGround, hpl] at hgnd
      | atLoc l =>
        have hphys : s.pkgPhysLoc p = l := by simp [State.pkgPhysLoc, hpl]
        refine ⟨p, l, hpl, hnd, hphys ▸ hin, hphys ▸ hside, ?_⟩
        intro t ht hts
        have h1 := hall t (List.mem_finRange t)
        simp only [Bool.or_eq_true, Bool.not_eq_true', Bool.and_eq_false_iff, decide_eq_true_eq] at h1
        rcases h1 with hnot | hlt
        · rcases hnot with h1 | h2
          · rw [ht] at h1; cases h1
          · rw [hts] at h2; cases h2
        · exact hlt

/-- Two bridge edges represent distinct undirected edges. -/
def BridgeDistinct {I : Instance} (b₁ b₂ : BridgeEdge I) : Prop :=
  ¬ ((b₁.u = b₂.u ∧ b₁.v = b₂.v) ∨ (b₁.u = b₂.v ∧ b₁.v = b₂.u))

/-- Helper: sum of `countActions` over a list of pairwise-disjoint action predicates
    is `≤ countActions (any pred)`. -/
theorem sum_countActions_disjoint {I : Instance} (preds : List (Action I → Bool)) (π : Plan I)
    (hdisj : preds.Pairwise (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false)) :
    (preds.map (fun p => countActions p π)).sum ≤
    countActions (fun a => preds.any (fun p => p a)) π := by
  induction preds with
  | nil => simp [countActions]
  | cons p ps ih =>
    have ⟨hp_ps, hps_pw⟩ := List.pairwise_cons.mp hdisj
    have hrec := ih hps_pw
    simp only [List.map_cons, List.sum_cons]
    have hstep : countActions p π + countActions (fun a => ps.any (fun q => q a)) π =
                 countActions (fun a => p a || ps.any (fun q => q a)) π := by
      clear hrec ih hdisj hps_pw
      unfold countActions
      induction π with
      | nil => rfl
      | cons a rest iha =>
        simp only [List.map_cons, List.sum_cons]
        dsimp only at iha ⊢
        by_cases hpa : p a = true
        · have hnone : ps.any (fun q => q a) = false := by
            rw [Bool.eq_false_iff]
            intro hany
            rw [List.any_eq_true] at hany
            rcases hany with ⟨q, hq, hqa⟩
            have hf := hp_ps q hq a hpa
            rw [hf] at hqa; cases hqa
          simp only [hpa, hnone, Bool.false_eq_true, Bool.or_false, ↓reduceIte]; omega
        · have hpf : p a = false := Bool.eq_false_iff.mpr hpa
          simp only [hpf, Bool.false_eq_true, Bool.false_or, ↓reduceIte]; omega
    have heq : (fun a => (p :: ps).any (fun q => q a)) = (fun a => p a || ps.any (fun q => q a)) := by
      funext a; simp
    rw [heq, ← hstep]
    omega

/-- Summing `bridgeEdgeFlux` over pairwise-distinct bridges lower-bounds bridge drives. -/
theorem h_bridge_base_sound {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (bridges : List (BridgeEdge I))
    (hdist : bridges.Pairwise BridgeDistinct) :
    (bridges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum ≤
    countActions (fun a => bridges.any (fun b => isEdgeDrive b.u b.v a)) π := by
  have h1 : (bridges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum ≤
            (bridges.map (fun b => bridgeDriveCount b.u b.v π)).sum := by
    clear hdist
    induction bridges with
    | nil => simp
    | cons b bs ih =>
      simp only [List.map_cons, List.sum_cons]
      have ⟨h1, h2⟩ := bridgeEdgeFlux_sound hv hp hg b
      have heq := bridgeDriveCount_eq_dir_sum b π
      omega
  apply Nat.le_trans h1
  have hdisj : (bridges.map (fun b => isEdgeDrive b.u b.v)).Pairwise
      (fun p₁ p₂ => ∀ a, p₁ a = true → p₂ a = false) := by
    rw [List.pairwise_map]
    refine hdist.imp ?_
    intro b₁ b₂ hne a h1
    cases a with
    | drive t x y =>
      simp only [isEdgeDrive, Bool.or_eq_true, Bool.and_eq_true, decide_eq_true_eq] at h1
      simp only [isEdgeDrive, Bool.or_eq_false_iff, Bool.and_eq_false_iff, decide_eq_false_iff_not]
      rcases h1 with ⟨rfl, rfl⟩ | ⟨rfl, rfl⟩
      · constructor
        · by_cases h : b₁.u = b₂.u
          · right; intro hy; exact hne (Or.inl ⟨h, hy⟩)
          · left; exact h
        · by_cases h : b₁.u = b₂.v
          · right; intro hy; exact hne (Or.inr ⟨h, hy⟩)
          · left; exact h
      · constructor
        · by_cases h : b₁.v = b₂.u
          · right; intro hy; exact hne (Or.inr ⟨hy, h⟩)
          · left; exact h
        · by_cases h : b₁.v = b₂.v
          · right; intro hy; exact hne (Or.inl ⟨hy, h⟩)
          · left; exact h
    | load _ _ => simp [isEdgeDrive] at h1
    | unload _ _ => simp [isEdgeDrive] at h1
    | board _ _ => simp [isEdgeDrive] at h1
    | disembark _ _ => simp [isEdgeDrive] at h1
    | sail _ _ _ => simp [isEdgeDrive] at h1
  have hsum := sum_countActions_disjoint (bridges.map (fun b => isEdgeDrive b.u b.v)) π hdisj
  have hmap_eq : ((bridges.map (fun b => isEdgeDrive b.u b.v)).map (fun p => countActions p π)).sum =
                 (bridges.map (fun b => bridgeDriveCount b.u b.v π)).sum := by
    rw [List.map_map]; rfl
  have hany_eq : (fun a => (bridges.map (fun b => isEdgeDrive b.u b.v)).any (fun p => p a)) =
                 (fun a => bridges.any (fun b => isEdgeDrive b.u b.v a)) := by
    funext a; simp only [List.any_map]; rfl
  rw [← hmap_eq, ← hany_eq]
  exact hsum

-- ==============================================================================
-- 2. DIRECTED BRIDGE PRECEDENCE CYCLES (`_bridge_cycle_extra`, ex1.py:L1249-L1311)
-- ==============================================================================

/-- State after executing the first `k` actions of `π` from `s`. -/
def stateAt {I : Instance} (s : State I) (π : Plan I) (k : Nat) : State I :=
  (π.take k).foldl applyAction s

theorem stateAt_zero {I : Instance} (s : State I) (π : Plan I) : stateAt s π 0 = s := rfl

theorem stateAt_succ {I : Instance} (s : State I) (a : Action I) (rest : Plan I) (k : Nat) :
    stateAt s (a :: rest) (k + 1) = stateAt (applyAction s a) rest k := rfl

theorem stateAt_end {I : Instance} {s s_end : State I} {π : Plan I}
    (hp : ValidPlan I s π s_end) : stateAt s π π.length = s_end := by
  induction hp with
  | nil => rfl
  | @cons sa sb _ a rest hstep _ ih =>
    simp only [List.length_cons, stateAt_succ, ← step_eq_applyAction hstep, ih]

/-- First index `k < π.length` where predicate `pred` holds on action `π[k]` (returns `π.length` if none). -/
def firstStep {I : Instance} (pred : Action I → Bool) : Plan I → Nat
  | [] => 0
  | a :: rest => if pred a then 0 else 1 + firstStep pred rest

theorem firstStep_le_len {I : Instance} (pred : Action I → Bool) (π : Plan I) :
    firstStep pred π ≤ π.length := by
  induction π with
  | nil => simp [firstStep]
  | cons a rest ih =>
    simp only [firstStep, List.length_cons]
    split <;> omega

theorem firstStep_lt_of_count_pos {I : Instance} (pred : Action I → Bool) (π : Plan I)
    (hpos : 1 ≤ countActions pred π) : firstStep pred π < π.length := by
  induction π with
  | nil => simp [countActions] at hpos
  | cons a rest ih =>
    simp only [firstStep, List.length_cons, countActions, List.map_cons, List.sum_cons] at hpos ⊢
    cases hpa : pred a with
    | true => simp
    | false =>
      simp only [hpa, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at hpos ⊢
      have := ih hpos; omega

/-- No truck can cross bridge `b` out of side A (`u -> v`) before some truck first enters side A (`v -> u`)
    when initially 0 trucks are on side A (`mu == 0`). -/
theorem bridge_enter_before_exit {I : Instance} (b : BridgeEdge I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (hmu0 : ∀ t, b.inComp (s.truckPhysLoc t) = true → b.inA (s.truckPhysLoc t) = false)
    (hout_pos : 1 ≤ countActions (isDirEdgeDrive b.u b.v) π) :
    firstStep (isDirEdgeDrive b.v b.u) π < firstStep (isDirEdgeDrive b.u b.v) π := by
  induction hp with
  | nil => simp [countActions] at hout_pos
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    simp only [firstStep]
    cases hvu : isDirEdgeDrive b.v b.u a with
    | true =>
      -- `a` is `DRIVE{t, v, u}`, so `a` cannot be `DRIVE{t, u, v}` (since `u ≠ v`)!
      have huv_false : isDirEdgeDrive b.u b.v a = false := by
        cases a with
        | drive t x y =>
          simp only [isDirEdgeDrive, Bool.and_eq_true, decide_eq_true_eq] at hvu
          rcases hvu with ⟨rfl, rfl⟩
          have hne : b.u ≠ b.v := by intro h; have hr := b.hroad; rw [h, I.road_irref] at hr; cases hr
          simp [isDirEdgeDrive, Ne.symm hne]
        | _ => simp [isDirEdgeDrive] at hvu
      simp only [huv_false, Bool.false_eq_true, ↓reduceIte]; omega
    | false =>
      -- `a` is NOT `v -> u`; also `a` CANNOT be `u -> v` because no truck is on side A in `sa`!
      have huv_false : isDirEdgeDrive b.u b.v a = false := by
        cases hstep with
        | @drive t x y ht _ _ =>
          simp only [isDirEdgeDrive, Bool.and_eq_false_iff, decide_eq_false_iff_not]
          by_cases hxu : x = b.u
          · subst hxu
            have hphys : sa.truckPhysLoc t = b.u := by simp [State.truckPhysLoc, ht]
            have hfalse := hmu0 t (hphys ▸ b.hu_in)
            rw [hphys, b.hu_A] at hfalse
            cases hfalse
          · left; exact hxu
        | _ => rfl
      simp only [huv_false, Bool.false_eq_true, ↓reduceIte]
      -- No truck crossed B->A on step `a`, so `sb` still has `mu == 0`!
      have hmu0_b : ∀ t, b.inComp (sb.truckPhysLoc t) = true → b.inA (sb.truckPhysLoc t) = false := by
        intro t htb
        have hta : b.inComp (sa.truckPhysLoc t) = true := by rw [← b.hcl hstep t]; exact htb
        have ha_f := hmu0 t hta
        have hcr := (bridge_step_cross_iff b hv hstep).2
        simp only [hvu, Bool.false_eq_true, ↓reduceIte] at hcr
        have hle := le_finSum (fun t' => if b.inComp (sa.truckPhysLoc t') then stepTruckCrossBA b.inComp b.inA sa sb t' else 0) t
        rw [hcr] at hle
        simp only [hta, ↓reduceIte, stepTruckCrossBA, ha_f, Bool.not_false, Bool.and_true] at hle
        cases hsb_a : b.inA (sb.truckPhysLoc t) with
        | false => rfl
        | true => simp [hsb_a] at hle
      have hout_rest : 1 ≤ countActions (isDirEdgeDrive b.u b.v) rest := by
        simp only [countActions, List.map_cons, List.sum_cons, huv_false, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at hout_pos
        exact hout_pos
      have hrec := ih (validState_step hv hstep) hmu0_b hout_rest
      omega

/-- If package `p` starts on side A (`inA = true`) and `π` has AT MOST ONE exit `u -> v`,
    then at every step `k ≤ firstStep (u -> v) π`, `p` is STILL on side A! -/
theorem pkg_stays_inA_until_first_exit {I : Instance} (b : BridgeEdge I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (p : Fin I.numPkgs) (hin : b.inComp (s.pkgPhysLoc p) = true) (ha : b.inA (s.pkgPhysLoc p) = true)
    (k : Nat) (hk : k ≤ firstStep (isDirEdgeDrive b.u b.v) π) :
    b.inComp ((stateAt s π k).pkgPhysLoc p) = true ∧ b.inA ((stateAt s π k).pkgPhysLoc p) = true := by
  induction hp generalizing k with
  | nil =>
    have hk0 : k = 0 := by simp [firstStep] at hk; omega
    subst hk0; exact ⟨hin, ha⟩
  | @cons sa sb _ a rest hstep _ ih =>
    cases k with
    | zero => exact ⟨hin, ha⟩
    | succ k' =>
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      simp only [firstStep] at hk
      have huv_f : isDirEdgeDrive b.u b.v a = false := by
        cases h : isDirEdgeDrive b.u b.v a with
        | false => rfl
        | true => simp [h] at hk
      simp only [huv_f, Bool.false_eq_true, ↓reduceIte] at hk
      -- Step `a` is not `u -> v`, so `p` cannot cross from A to B on step `a`!
      have hnext : b.inComp (sb.pkgPhysLoc p) = true ∧ b.inA (sb.pkgPhysLoc p) = true := by
        by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
        · exact ⟨hsame ▸ hin, hsame ▸ ha⟩
        · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, _, hpa, hpb⟩
          have hta : b.inComp (sa.truckPhysLoc t) = true := hpa ▸ hin
          have htb : b.inComp (sb.truckPhysLoc t) = true := by rw [b.hcl hstep t]; exact hta
          have hcr := (bridge_step_cross_iff b hv hstep).1
          simp only [huv_f, Bool.false_eq_true, ↓reduceIte] at hcr
          have hle := le_finSum (fun t' => if b.inComp (sa.truckPhysLoc t') then stepTruckCrossAB b.inComp b.inA sa sb t' else 0) t
          rw [hcr] at hle
          have htA : b.inA (sa.truckPhysLoc t) = true := hpa ▸ ha
          simp only [hta, ↓reduceIte, stepTruckCrossAB, htA, Bool.and_true] at hle
          cases hsb_t : b.inA (sb.truckPhysLoc t) with
          | true => exact ⟨hpb.symm ▸ htb, hpb.symm ▸ hsb_t⟩
          | false => simp [hsb_t] at hle
      simp only [stateAt_succ, ← hsb_eq]
      exact ih (validState_step hv hstep) hnext.1 hnext.2 k' (by omega)

/-- If package `p` starts on side B (`inA = false`), ends on side A (`inA = true`),
    and `π` has EXACTLY ONE entry `v -> u`, then at step `firstStep (v -> u) π + 1`,
    `p` is ALREADY on side A (equivalently, at `firstStep (v -> u) π` it is the step `v -> u` that carries `p`
    — so if `p` is still NOT on side B at `firstStep (v -> u) π`, contradiction!).
    More directly: at `k = firstStep (v -> u) π`, `p` MUST cross on that unique entry, so `p` is at `b.v`
    inside a truck at step `firstStep (v -> u) π`, hence `stateAt s π (firstStep (v -> u) π)` has `p` at `b.v`! -/
theorem pkg_at_v_at_unique_entry {I : Instance} (b : BridgeEdge I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (p : Fin I.numPkgs) (hin : b.inComp (s.pkgPhysLoc p) = true)
    (hb : b.inA (s.pkgPhysLoc p) = false) (hg_A : b.inA (s_end.pkgPhysLoc p) = true)
    (hcnt1 : countActions (isDirEdgeDrive b.v b.u) π ≤ 1) :
    b.inA ((stateAt s π (firstStep (isDirEdgeDrive b.v b.u) π + 1)).pkgPhysLoc p) = true := by
  induction hp with
  | nil => rw [hb] at hg_A; cases hg_A
  | @cons sa sb _ a rest hstep hrest ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    simp only [firstStep]
    cases hvu : isDirEdgeDrive b.v b.u a with
    | true =>
      -- `a` IS the unique `v -> u` step, so `rest` has 0 `v -> u` steps!
      have hrest0 : countActions (isDirEdgeDrive b.v b.u) rest = 0 := by
        unfold countActions at hcnt1 ⊢
        simp only [List.map_cons, List.sum_cons, hvu, ↓reduceIte] at hcnt1
        omega
      -- Therefore `p` MUST already be on side A in `sb` (otherwise it could never reach side A in `rest`!)
      simp only [Nat.zero_add, stateAt_succ, stateAt_zero, ← hsb_eq]
      cases hsb_p : b.inA (sb.pkgPhysLoc p) with
      | true => exact hsb_p
      | false =>
        exfalso
        -- `p` is still in `b.inComp` at `sb`
        have hin_b : b.inComp (sb.pkgPhysLoc p) = true := by
          by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
          · exact hsame ▸ hin
          · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, _, hpa, hpb⟩
            have := b.hcl hstep t; rw [← hpa] at this; rw [← hpb] at this; exact this.trans hin
        have hpos := planPkgCrossBA_pos_of_side_change b.hcl hrest p hin_b hsb_p hg_A
        -- Bound `planPkgCrossBA` by `countActions (v -> u) rest = 0`!
        have hcr_eq := (bridge_plan_cross_eq_drives b (validState_step hv hstep) hrest).2
        rw [hrest0] at hcr_eq
        -- `planPkgCrossBA` is 0 whenever every truck in `inComp` has `planTruckCrossBA = 0`!
        have hzero_p : ∀ {sx sy : State I} {π' : Plan I} (hp' : ValidPlan I sx π' sy),
            (∀ t, b.inComp (sx.truckPhysLoc t) = true → planTruckCrossBA b.inComp b.inA sx π' t = 0) →
            planPkgCrossBA b.inComp b.inA sx π' p = 0 := by
          intro sx sy π' hp'
          induction hp' with
          | nil => intro _; rfl
          | @cons s1 s2 _ a' r' hs' _ iha =>
            intro hall
            have hs2_eq : s2 = applyAction s1 a' := step_eq_applyAction hs'
            have hall_next : ∀ t, b.inComp (s2.truckPhysLoc t) = true → planTruckCrossBA b.inComp b.inA s2 r' t = 0 := by
              intro t ht2
              have ht1 : b.inComp (s1.truckPhysLoc t) = true := by rw [← b.hcl hs' t]; exact ht2
              have h0 := hall t ht1
              simp only [planTruckCrossBA, ← hs2_eq] at h0
              omega
            have hrec := iha hall_next
            simp only [planPkgCrossBA, ← hs2_eq, hrec, Nat.add_zero]
            cases hpl : s1.pkgLoc p with
            | atLoc _ => rfl
            | inTruck t =>
              cases hc : b.inComp (s1.truckPhysLoc t) with
              | false => simp [stepTruckCrossBA, hc]
              | true =>
                have h0 := hall t hc
                simp only [planTruckCrossBA, ← hs2_eq] at h0
                have hstep0 : stepTruckCrossBA b.inComp b.inA s1 s2 t = 0 := by omega
                exact hstep0
        have hall0 : ∀ t, b.inComp (sb.truckPhysLoc t) = true → planTruckCrossBA b.inComp b.inA sb rest t = 0 := by
          intro t ht
          have hle := le_finSum (fun t' => if b.inComp (sb.truckPhysLoc t') then planTruckCrossBA b.inComp b.inA sb rest t' else 0) t
          rw [hcr_eq] at hle
          simp only [ht, ↓reduceIte] at hle
          omega
        have hz := hzero_p hrest hall0
        omega
    | false =>
      -- `a` is NOT `v -> u`, so `p` stays on side B in `sb`, and `rest` still has `≤ 1` `v -> u`!
      have hcnt_rest : countActions (isDirEdgeDrive b.v b.u) rest ≤ 1 := by
        simp only [countActions, List.map_cons, List.sum_cons, hvu, Bool.false_eq_true, ↓reduceIte, Nat.zero_add] at hcnt1
        exact hcnt1
      have hnext : b.inComp (sb.pkgPhysLoc p) = true ∧ b.inA (sb.pkgPhysLoc p) = false := by
        by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
        · exact ⟨hsame ▸ hin, hsame ▸ hb⟩
        · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, _, hpa, hpb⟩
          have hta : b.inComp (sa.truckPhysLoc t) = true := hpa ▸ hin
          have htb : b.inComp (sb.truckPhysLoc t) = true := by rw [b.hcl hstep t]; exact hta
          have hcr := (bridge_step_cross_iff b hv hstep).2
          simp only [hvu, Bool.false_eq_true, ↓reduceIte] at hcr
          have hle := le_finSum (fun t' => if b.inComp (sa.truckPhysLoc t') then stepTruckCrossBA b.inComp b.inA sa sb t' else 0) t
          rw [hcr] at hle
          have htB : b.inA (sa.truckPhysLoc t) = false := hpa ▸ hb
          simp only [hta, ↓reduceIte, stepTruckCrossBA, htB, Bool.not_false, Bool.and_true] at hle
          cases hsb_t : b.inA (sb.truckPhysLoc t) with
          | false => exact ⟨hpb.symm ▸ htb, hpb.symm ▸ hsb_t⟩
          | true => simp [hsb_t] at hle
      have hidx : 1 + firstStep (isDirEdgeDrive b.v b.u) rest + 1 =
                  (firstStep (isDirEdgeDrive b.v b.u) rest + 1) + 1 := by omega
      simp only [Bool.false_eq_true, ↓reduceIte]
      rw [hidx, stateAt_succ, ← hsb_eq]
      exact ih (validState_step hv hstep) hnext.1 hnext.2 hg_A hcnt_rest

/-- A 0-truck unit-flux bridge region (`unit_regions` entry in `ex1.py:L1549-L1569`). -/
structure UnitBridgeRegion (I : Instance) (s : State I) where
  regionMask  : Fin I.numLocs → Bool
  edges       : List (BridgeEdge I)
  edges_ne    : edges ≠ []
  mask_in_A   : ∀ b ∈ edges, ∀ l, regionMask l = true → b.inComp l = true ∧ b.inA l = true
  zero_trucks : ∀ b ∈ edges, ∀ t, b.inComp (s.truckPhysLoc t) = true → b.inA (s.truckPhysLoc t) = false
  unit_flux   : ∀ b ∈ edges, bridgeEdgeFlux I s b = (1, 1)

/-- Core precedence-cycle impossibility theorem (`_bridge_cycle_extra`, `ex1.py:L1249-L1311`):
    Given a directed cycle of `k ≥ 2` unit-flux 0-truck bridge regions `regs` whose `inA` sides
    are pairwise disjoint (each edge of `regs[i]` separates `regs[i]` from every `regs[j]`, `j ≠ i`),
    and for each `i`, a package `p_i` starts in `regs[i]` with goal in `regs[(i+1) mod k]`:
    at least one region `R ∈ regs` has EVERY edge `b ∈ R.edges` crossed `≥ 3` times! -/
theorem bridge_cycle_exists_extra_region {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    {k : Nat} (hk : 2 ≤ k)
    (regs : Fin k → UnitBridgeRegion I s)
    (hdisj : ∀ (i j : Fin k), i ≠ j →
      ∀ b₁ ∈ (regs i).edges, ∀ b₂ ∈ (regs j).edges, ∀ l,
        b₁.inA l = true → b₂.inA l = false)
    (hcycle : ∀ i : Fin k,
      let nxt : Fin k := ⟨(i.val + 1) % k, Nat.mod_lt _ (by omega)⟩
      ∃ p : Fin I.numPkgs,
        s.pkgDelivered p = false ∧
        (regs i).regionMask (s.pkgPhysLoc p) = true ∧
        (regs nxt).regionMask (I.pkgGoal p) = true) :
    ∃ i : Fin k, ∀ b ∈ (regs i).edges, 3 ≤ bridgeDriveCount b.u b.v π := by
  -- Proof by contradiction: assume every region i has some edge b_i crossed ≤ 2 times.
  by_cases hex : ∃ i : Fin k, ∀ b ∈ (regs i).edges, 3 ≤ bridgeDriveCount b.u b.v π
  · exact hex
  · exfalso
    have hnot : ∀ i : Fin k, ∃ b ∈ (regs i).edges, bridgeDriveCount b.u b.v π ≤ 2 := by
      intro i
      by_cases h3 : ∀ b ∈ (regs i).edges, 3 ≤ bridgeDriveCount b.u b.v π
      · exfalso; exact hex ⟨i, h3⟩
      · -- Extract witness from finite list `(regs i).edges`
        have hfind : ∀ l : List (BridgeEdge I),
            ¬ (∀ b ∈ l, 3 ≤ bridgeDriveCount b.u b.v π) →
            ∃ b ∈ l, bridgeDriveCount b.u b.v π ≤ 2 := by
          intro l
          induction l with
          | nil => intro h; exfalso; apply h; intro _ hm; cases hm
          | cons b bs ih =>
            intro h
            by_cases hb : bridgeDriveCount b.u b.v π ≤ 2
            · exact ⟨b, List.mem_cons_self .., hb⟩
            · have hrest : ¬ (∀ b' ∈ bs, 3 ≤ bridgeDriveCount b'.u b'.v π) := by
                intro hall; apply h; intro b' hm'
                rcases List.mem_cons.mp hm' with rfl | hms
                · omega
                · exact hall b' hms
              rcases ih hrest with ⟨b', hmb', hb'⟩
              exact ⟨b', List.mem_cons_of_mem _ hmb', hb'⟩
        exact hfind (regs i).edges h3
    -- Choose one edge `e i ∈ (regs i).edges` with `bridgeDriveCount ≤ 2` for each `i`
    have hstep_lt : ∀ i : Fin k,
        ∀ b₁ ∈ (regs i).edges, bridgeDriveCount b₁.u b₁.v π ≤ 2 →
        let nxt : Fin k := ⟨(i.val + 1) % k, Nat.mod_lt _ (by omega)⟩
        ∀ b₂ ∈ (regs nxt).edges, bridgeDriveCount b₂.u b₂.v π ≤ 2 →
          firstStep (isDirEdgeDrive b₁.v b₁.u) π < firstStep (isDirEdgeDrive b₂.v b₂.u) π := by
      intro i b₁ hb₁ hle₁ nxt b₂ hb₂ hle₂
      have hne_ij : i ≠ nxt := by
        intro heq
        have hval : i.val = (i.val + 1) % k := congrArg Fin.val heq
        by_cases hlast : i.val + 1 < k
        · rw [Nat.mod_eq_of_lt hlast] at hval; omega
        · have h1 : i.val + 1 = k := by omega
          rw [h1, Nat.mod_self] at hval; omega
      -- Both b₁ and b₂ have flux (1, 1), so each has count(u->v) = 1 and count(v->u) = 1!
      have ⟨h1_uv, h1_vu⟩ := bridgeEdgeFlux_sound hv hp hg b₁
      have huf1 := (regs i).unit_flux b₁ hb₁
      rw [huf1] at h1_uv h1_vu
      have hsum1 := bridgeDriveCount_eq_dir_sum b₁ π
      have ⟨h2_uv, h2_vu⟩ := bridgeEdgeFlux_sound hv hp hg b₂
      have huf2 := (regs nxt).unit_flux b₂ hb₂
      rw [huf2] at h2_uv h2_vu
      have hsum2 := bridgeDriveCount_eq_dir_sum b₂ π
      have h2_vu_le1 : countActions (isDirEdgeDrive b₂.v b₂.u) π ≤ 1 := by omega
      -- 1) `firstStep (b₁.v -> b₁.u) < firstStep (b₁.u -> b₁.v)`
      have hlt1 : firstStep (isDirEdgeDrive b₁.v b₁.u) π < firstStep (isDirEdgeDrive b₁.u b₁.v) π :=
        bridge_enter_before_exit b₁ hv hp ((regs i).zero_trucks b₁ hb₁) h1_uv
      -- 2) Package `p` goes from `regs i` to `regs nxt`, forcing `firstStep (b₁.u -> b₁.v) < firstStep (b₂.v -> b₂.u) + 1`!
      rcases hcycle i with ⟨p, _, hp_src, hp_dst⟩
      have ⟨hp_in1, hp_A1⟩ := (regs i).mask_in_A b₁ hb₁ (s.pkgPhysLoc p) hp_src
      have ⟨hp_in2_g, hp_A2_g⟩ := (regs nxt).mask_in_A b₂ hb₂ (I.pkgGoal p) hp_dst
      have hp_B2 : b₂.inA (s.pkgPhysLoc p) = false := hdisj i nxt hne_ij b₁ hb₁ b₂ hb₂ (s.pkgPhysLoc p) hp_A1
      -- Package `p` is in `b₂.inComp` at `s` because `b₂.inComp` is closed and `I.pkgGoal p` is in `b₂.inComp`
      have hp_in2 : b₂.inComp (s.pkgPhysLoc p) = true := by
        have hcomp_pres : ∀ {sx sy : State I} {π' : Plan I}, ValidPlan I sx π' sy →
            b₂.inComp (sy.pkgPhysLoc p) = b₂.inComp (sx.pkgPhysLoc p) := by
          intro sx sy π' hp'
          induction hp' with
          | nil => rfl
          | @cons sa sb _ a _ hst _ iha =>
            rw [iha]
            by_cases hsame : sb.pkgPhysLoc p = sa.pkgPhysLoc p
            · rw [hsame]
            · rcases step_pkgPhysLoc_change hst p hsame with ⟨t, _, hpa, hpb⟩
              rw [hpa, hpb]; exact b₂.hcl hst t
        have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
        rw [← hcomp_pres hp, hgoal_p]
        exact hp_in2_g
      have hg_A2 : b₂.inA (s_goal.pkgPhysLoc p) = true := by
        have hgoal_p : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
        rw [hgoal_p]; exact hp_A2_g
      have h_in2 := pkg_at_v_at_unique_entry b₂ hv hp p hp_in2 hp_B2 hg_A2 h2_vu_le1
      -- If `firstStep (b₂.v -> b₂.u) + 1 ≤ firstStep (b₁.u -> b₁.v)`, then at that time `p` is BOTH in `b₁.inA` AND `b₂.inA`!
      by_cases hle : firstStep (isDirEdgeDrive b₂.v b₂.u) π + 1 ≤ firstStep (isDirEdgeDrive b₁.u b₁.v) π
      · exfalso
        have ⟨_, h_in1⟩ := pkg_stays_inA_until_first_exit b₁ hv hp p hp_in1 hp_A1
          (firstStep (isDirEdgeDrive b₂.v b₂.u) π + 1) hle
        have hdis := hdisj i nxt hne_ij b₁ hb₁ b₂ hb₂ _ h_in1
        rw [hdis] at h_in2; cases h_in2
      · omega
    -- Now chain `t_in(0) < t_in(1) < ... < t_in(k-1) < t_in(0)` using `Classical.choose` on `hnot`!
    let e (i : Fin k) : BridgeEdge I := Classical.choose (hnot i)
    have he_mem (i : Fin k) : e i ∈ (regs i).edges := (Classical.choose_spec (hnot i)).1
    have he_le (i : Fin k) : bridgeDriveCount (e i).u (e i).v π ≤ 2 := (Classical.choose_spec (hnot i)).2
    let tIn (i : Fin k) : Nat := firstStep (isDirEdgeDrive (e i).v (e i).u) π
    have hchain : ∀ m : Nat, m ≤ k → m > 0 →
        tIn ⟨0, by omega⟩ < tIn ⟨m % k, Nat.mod_lt _ (by omega)⟩ := by
      intro m hm hpos
      induction m with
      | zero => omega
      | succ m' ih =>
        by_cases hm0 : m' = 0
        · subst hm0
          have h0 := hstep_lt ⟨0, by omega⟩ (e ⟨0, by omega⟩) (he_mem _) (he_le _)
            (e ⟨1 % k, Nat.mod_lt _ (by omega)⟩) (he_mem _) (he_le _)
          exact h0
        · have hprev := ih (by omega) (by omega)
          have hmod_eq : m' % k = m' := Nat.mod_eq_of_lt (by omega)
          have hstep_m := hstep_lt ⟨m' % k, Nat.mod_lt _ (by omega)⟩
            (e ⟨m' % k, Nat.mod_lt _ (by omega)⟩) (he_mem _) (he_le _)
            (e ⟨((m' % k) + 1) % k, Nat.mod_lt _ (by omega)⟩) (he_mem _) (he_le _)
          have hidx_eq : ((m' % k) + 1) % k = (m' + 1) % k := by rw [hmod_eq]
          have hnext_eq : tIn ⟨((m' % k) + 1) % k, Nat.mod_lt _ (by omega)⟩ =
                          tIn ⟨(m' + 1) % k, Nat.mod_lt _ (by omega)⟩ := by
            congr 1; apply Fin.ext; exact hidx_eq
          change tIn ⟨m' % k, Nat.mod_lt _ (by omega)⟩ < tIn ⟨((m' % k) + 1) % k, Nat.mod_lt _ (by omega)⟩ at hstep_m
          rw [hnext_eq] at hstep_m
          exact Nat.lt_trans hprev hstep_m
    have hcontra := hchain k (Nat.le_refl k) (by omega)
    simp only [Nat.mod_self] at hcontra
    exact Nat.lt_irrefl _ hcontra

/-- A single directed precedence cycle among `k ≥ 2` unit-flux 0-truck bridge regions contributes
    at least `min_i (regs i).edges.length` extra bridge drives above the base `2 * len`. -/
theorem bridge_cycle_extra_sound {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    {k : Nat} (hk : 2 ≤ k)
    (regs : Fin k → UnitBridgeRegion I s)
    (hdisj : ∀ (i j : Fin k), i ≠ j →
      ∀ b₁ ∈ (regs i).edges, ∀ b₂ ∈ (regs j).edges, ∀ l,
        b₁.inA l = true → b₂.inA l = false)
    (hcycle : ∀ i : Fin k,
      let nxt : Fin k := ⟨(i.val + 1) % k, Nat.mod_lt _ (by omega)⟩
      ∃ p : Fin I.numPkgs,
        s.pkgDelivered p = false ∧
        (regs i).regionMask (s.pkgPhysLoc p) = true ∧
        (regs nxt).regionMask (I.pkgGoal p) = true)
    (minLen : Nat) (hmin : ∀ i : Fin k, minLen ≤ (regs i).edges.length) :
    finSum (fun i => ((regs i).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum) + minLen
    ≤ finSum (fun i => ((regs i).edges.map (fun b => bridgeDriveCount b.u b.v π)).sum) := by
  rcases bridge_cycle_exists_extra_region hv hp hg hk regs hdisj hcycle with ⟨i₀, hi₀⟩
  -- For every i, base sum ≤ actual sum; for i₀, base sum + len(i₀) ≤ actual sum!
  have hall : ∀ i : Fin k,
      ((regs i).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum ≤
      ((regs i).edges.map (fun b => bridgeDriveCount b.u b.v π)).sum := by
    intro i
    suffices ∀ l : List (BridgeEdge I),
        (l.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum ≤
        (l.map (fun b => bridgeDriveCount b.u b.v π)).sum from this (regs i).edges
    intro l; induction l with
    | nil => simp
    | cons b bs ih =>
      simp only [List.map_cons, List.sum_cons]
      have ⟨h1, h2⟩ := bridgeEdgeFlux_sound hv hp hg b
      have heq := bridgeDriveCount_eq_dir_sum b π
      omega
  have hi0_extra :
      ((regs i₀).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum + (regs i₀).edges.length ≤
      ((regs i₀).edges.map (fun b => bridgeDriveCount b.u b.v π)).sum := by
    have huf := (regs i₀).unit_flux
    suffices ∀ l : List (BridgeEdge I),
        (∀ b ∈ l, bridgeEdgeFlux I s b = (1, 1)) →
        (∀ b ∈ l, 3 ≤ bridgeDriveCount b.u b.v π) →
        (l.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum + l.length ≤
        (l.map (fun b => bridgeDriveCount b.u b.v π)).sum from this (regs i₀).edges huf hi₀
    intro l; induction l with
    | nil => intro _ _; simp
    | cons b bs ih =>
      intro h1 h3
      simp only [List.map_cons, List.sum_cons, List.length_cons]
      have hb1 := h1 b (List.mem_cons_self ..)
      have hb3 := h3 b (List.mem_cons_self ..)
      have hrec := ih (fun b' h => h1 b' (List.mem_cons_of_mem _ h)) (fun b' h => h3 b' (List.mem_cons_of_mem _ h))
      rw [hb1]; omega
  -- Combine `i₀` extra with all other `i ≠ i₀`
  have hdiff :
      finSum (fun i => ((regs i).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum) +
      (regs i₀).edges.length ≤
      finSum (fun i => ((regs i).edges.map (fun b => bridgeDriveCount b.u b.v π)).sum) := by
    have hupd := finSum_update
      (fun i => ((regs i).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum)
      i₀ (((regs i₀).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum + (regs i₀).edges.length)
    have hle : finSum (fun i => if i = i₀ then
          ((regs i₀).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum + (regs i₀).edges.length
        else ((regs i).edges.map (fun b => (bridgeEdgeFlux I s b).1 + (bridgeEdgeFlux I s b).2)).sum) ≤
        finSum (fun i => ((regs i).edges.map (fun b => bridgeDriveCount b.u b.v π)).sum) := by
      apply finSum_le_finSum; intro i
      by_cases hi : i = i₀
      · subst hi; simp only [↓reduceIte]; exact hi0_extra
      · simp only [hi, ↓reduceIte]; exact hall i
    omega
  have hm := hmin i₀
  omega

-- ==============================================================================
-- 3. CONTRACTED NON-BRIDGE ROADS (`h_nb = max(nb_p, nb_mst)`, ex1.py:L96-L139, L1573-L1608)
-- ==============================================================================

/-- Contraction of bridge road edges and active ferry edges to cost 0 (`ex1.py:L522-L546`). -/
structure NBContraction (I : Instance) where
  numNB       : Nat
  nbId        : Fin I.numLocs → Fin numNB
  nbDist      : Fin numNB → Fin numNB → Nat
  isBridge    : Fin I.numLocs → Fin I.numLocs → Bool
  dist_self   : ∀ x, nbDist x x = 0
  dist_symm   : ∀ x y, nbDist x y = nbDist y x
  dist_tri    : ∀ x y z, nbDist x z ≤ nbDist x y + nbDist y z
  /-- Bridge road edges are contracted to the same supernode. -/
  bridge_zero : ∀ u v, I.road u v = true → isBridge u v = true → nbId u = nbId v
  /-- Non-bridge road edges change `nbId` by distance `≤ 1`. -/
  nb_edge_one : ∀ u v, I.road u v = true → isBridge u v = false → nbDist (nbId u) (nbId v) ≤ 1
  /-- Active ferries (cap > 0) are contracted to the same supernode. -/
  ferry_zero  : ∀ f u v, 0 < I.ferryCap f → I.ferryServed f u = true → I.ferryServed f v = true →
    nbId u = nbId v

def isNonBridgeDrive {I : Instance} (C : NBContraction I) : Action I → Bool
  | .drive _ u v => !C.isBridge u v
  | _            => false

def costNonBridgeDrive {I : Instance} (C : NBContraction I) (π : Plan I) : Nat :=
  countActions (isNonBridgeDrive C) π

/-- Non-bridge distance changes by `0` on non-NB actions, and by `≤ 1` on NB drives of the acting truck. -/
theorem nb_step_truck_dist {I : Instance} (C : NBContraction I)
    {sa sb : State I} {a : Action I} (hv : ValidState I sa) (hstep : Step I sa a sb) :
    (isNonBridgeDrive C a = false → ∀ t, C.nbId (sb.truckPhysLoc t) = C.nbId (sa.truckPhysLoc t)) ∧
    (isNonBridgeDrive C a = true → ∃ t,
      C.nbDist (C.nbId (sa.truckPhysLoc t)) (C.nbId (sb.truckPhysLoc t)) ≤ 1 ∧
      ∀ t', t' ≠ t → C.nbId (sb.truckPhysLoc t') = C.nbId (sa.truckPhysLoc t')) := by
  cases hstep with
  | @drive t u v ht hne hroad =>
    constructor
    · intro hnb t'
      simp only [isNonBridgeDrive, Bool.not_eq_false'] at hnb
      by_cases htt : t' = t
      · subst htt
        simp only [State.truckPhysLoc, updateFn, ↓reduceIte, ht]
        exact (C.bridge_zero u v hroad hnb).symm
      · simp [State.truckPhysLoc, updateFn, htt]
    · intro hnb
      simp only [isNonBridgeDrive, Bool.not_eq_true'] at hnb
      refine ⟨t, ?_, ?_⟩
      · simp only [State.truckPhysLoc, ht, updateFn, ↓reduceIte]
        exact C.nb_edge_one u v hroad hnb
      · intro t' htt; simp [State.truckPhysLoc, updateFn, htt]
  | load _ _ _ =>
    exact ⟨fun _ t => rfl, fun h => by simp [isNonBridgeDrive] at h⟩
  | unload _ _ =>
    exact ⟨fun _ t => rfl, fun h => by simp [isNonBridgeDrive] at h⟩
  | @board t f ht _ =>
    refine ⟨fun _ t' => ?_, fun h => by simp [isNonBridgeDrive] at h⟩
    by_cases htt : t' = t
    · subst htt; simp [State.truckPhysLoc, updateFn, ht]
    · simp [State.truckPhysLoc, updateFn, htt]
  | @disembark t f ht =>
    refine ⟨fun _ t' => ?_, fun h => by simp [isNonBridgeDrive] at h⟩
    by_cases htt : t' = t
    · subst htt; simp [State.truckPhysLoc, updateFn, ht]
    · simp [State.truckPhysLoc, updateFn, htt]
  | @sail f u v hf hne hserved =>
    refine ⟨fun _ t' => ?_, fun h => by simp [isNonBridgeDrive] at h⟩
    cases htl : sa.truckLoc t' with
    | atLoc l => simp [State.truckPhysLoc, htl]
    | onFerry f' =>
      by_cases hff : f' = f
      · subst hff
        have hpos_f : 0 < I.ferryCap f' := by
          have hle1 : 1 ≤ sa.ferryCount f' := by
            have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry f' then 1 else 0) t'
            simpa [State.ferryCount, htl] using h
          have hcap := hv.aboard_le_cap f'
          omega
        have hu_sv : I.ferryServed f' u = true := hf ▸ hv.ferry_served f'
        simp only [State.truckPhysLoc, htl, updateFn, ↓reduceIte, hf]
        exact (C.ferry_zero f' u v hpos_f hu_sv hserved).symm
      · simp [State.truckPhysLoc, htl, updateFn, hff]

/-- Part 3A: `nb_p` packing lower bound on non-bridge drives (`ex1.py:L1576-L1587`). -/
theorem nb_pack_sound {I : Instance} (C : NBContraction I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (hcap : 0 < maxDynEffCap I s)
    (min_hw : Nat)
    (hmin_hw : ∀ p, s.pkgDelivered p = false → I.pkgWeight p > maxDynEffCap I s / 2 →
      C.nbDist (C.nbId (s.pkgPhysLoc p)) (C.nbId (I.pkgGoal p)) > 0 → min_hw ≤ I.pkgWeight p) :
    let cap := maxDynEffCap I s
    let d (p : Fin I.numPkgs) := C.nbDist (C.nbId (s.pkgPhysLoc p)) (C.nbId (I.pkgGoal p))
    packLB
      (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then d p else 0))
      min_hw
      (finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p * d p else 0))
      (finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * d p else 0))
      cap
    ≤ costNonBridgeDrive C π := by
  let pot (st : State I) (p : Fin I.numPkgs) : Nat :=
    C.nbDist (C.nbId (st.pkgPhysLoc p)) (C.nbId (I.pkgGoal p))
  apply packLB_plan_sound hv hp (isNonBridgeDrive C) pot
  · intro p _
    have hgp : s_goal.pkgPhysLoc p = I.pkgGoal p := by simp [State.pkgPhysLoc, hg p]
    simp [pot, hgp, C.dist_self]
  · intro s₁ s₂ a hv₁ hstep
    have ⟨h0, h1⟩ := nb_step_truck_dist C hv₁ hstep
    constructor
    · intro hfalse p _
      by_cases hsame : s₂.pkgPhysLoc p = s₁.pkgPhysLoc p
      · simp [pot, hsame]
      · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t, _, hpa, hpb⟩
        have heq := h0 hfalse t
        simp [pot, hpa, hpb, heq]
    · intro htrue
      rcases h1 htrue with ⟨t, hdt, hother⟩
      refine ⟨t, fun p _ => ?_⟩
      by_cases hin : s₁.pkgLoc p = .inTruck t
      · simp only [hin, ↓reduceIte]
        -- On a DRIVE action, `s₂.pkgLoc p = s₁.pkgLoc p = .inTruck t`
        have hloc2 : s₂.pkgLoc p = .inTruck t := by
          cases hstep with
          | drive _ _ _ => exact hin
          | _ => simp [isNonBridgeDrive] at htrue
        have hp1 : s₁.pkgPhysLoc p = s₁.truckPhysLoc t := by simp [State.pkgPhysLoc, hin]
        have hp2 : s₂.pkgPhysLoc p = s₂.truckPhysLoc t := by simp [State.pkgPhysLoc, hloc2]
        have htri := C.dist_tri (C.nbId (s₁.truckPhysLoc t)) (C.nbId (s₂.truckPhysLoc t)) (C.nbId (I.pkgGoal p))
        simp only [pot, hp1, hp2]; omega
      · simp only [hin, ↓reduceIte]
        by_cases hsame : s₂.pkgPhysLoc p = s₁.pkgPhysLoc p
        · simp [pot, hsame]
        · rcases step_pkgPhysLoc_change hstep p hsame with ⟨t', hloc', hpa, hpb⟩
          have hne : t' ≠ t := fun h => hin (h ▸ hloc')
          have heq := hother t' hne
          simp [pot, hpa, hpb, heq]
  · exact hcap
  · exact dynEffCap_le_maxDynEffCap I s
  · exact hmin_hw

-- ==============================================================================
-- 4. PRIM'S MST ON METRIC CLOSURE (`_mst_cost`, ex1.py:L96-L139, L1588-L1606)
-- ==============================================================================

/-- Exact Prim's MST lower bound over `m` required vertices (`Fin m`) with symmetric metric `dist`
    and initial root distances `rootDist : Fin m → Nat` (matching `_mst_cost`, ex1.py:L96-L139). -/
def primStep {m : Nat} (dist : Fin m → Fin m → Nat)
    (used : Fin m → Bool) (minE : Fin m → Nat) : (Fin m → Bool) × (Fin m → Nat) × Nat :=
  -- Pick unused vertex minimizing `minE`
  let best? : Option (Fin m × Nat) :=
    (List.finRange m).foldl (fun acc i =>
      if used i then acc
      else match acc with
        | none => some (i, minE i)
        | some (_, bw) => if minE i < bw then some (i, minE i) else acc) none
  match best? with
  | none => (used, minE, 0)
  | some (bi, bw) =>
    let used' := fun i => used i || decide (i = bi)
    let minE' := fun i => if used' i then minE i else min (minE i) (dist bi i)
    (used', minE', bw)

def primLoop {m : Nat} (dist : Fin m → Fin m → Nat) :
    Nat → (Fin m → Bool) → (Fin m → Nat) → Nat
  | 0, _, _ => 0
  | steps + 1, used, minE =>
      let (used', minE', bw) := primStep dist used minE
      bw + primLoop dist steps used' minE'

/-- Prim's MST cost on `Fin m` with root distances `rootDist` (`_mst_cost`, ex1.py:L96-L139). -/
def primMST {m : Nat} (dist : Fin m → Fin m → Nat) (rootDist : Fin m → Nat) : Nat :=
  primLoop dist m (fun _ => false) rootDist

/-- A rooted spanning tree on `Fin m` represented by `par : Fin m → Option (Fin m)` and an
    acyclicity ranking `rank : Fin m → Nat` (`par v = some u → rank u < rank v`). -/
structure RootedTree (m : Nat) where
  par  : Fin m → Option (Fin m)
  rank : Fin m → Nat
  acyc : ∀ v u, par v = some u → rank u < rank v

def treeEdgeWeight {m : Nat} (dist : Fin m → Fin m → Nat) (rootDist : Fin m → Nat)
    (par : Fin m → Option (Fin m)) (v : Fin m) : Nat :=
  match par v with
  | none   => rootDist v
  | some u => dist u v

def treeWeight {m : Nat} (dist : Fin m → Fin m → Nat) (rootDist : Fin m → Nat)
    (T : RootedTree m) : Nat :=
  finSum (treeEdgeWeight dist rootDist T.par)

/-- Helper: `primStep` picks an unused vertex `bi` whose `minE bi` is minimal among all unused vertices. -/
theorem primStep_spec {m : Nat} (dist : Fin m → Fin m → Nat)
    (used : Fin m → Bool) (minE : Fin m → Nat)
    (hex : ∃ i : Fin m, used i = false) :
    ∃ bi : Fin m,
      used bi = false ∧
      (∀ j : Fin m, used j = false → minE bi ≤ minE j) ∧
      primStep dist used minE =
        (fun i => used i || decide (i = bi),
         fun i => if used i || decide (i = bi) then minE i else min (minE i) (dist bi i),
         minE bi) := by
  unfold primStep
  let stepFn := fun (acc : Option (Fin m × Nat)) (i : Fin m) =>
    if used i then acc
    else match acc with
      | none => some (i, minE i)
      | some (_, bw) => if minE i < bw then some (i, minE i) else acc
  have hfold : ∀ (l : List (Fin m)) (acc : Option (Fin m × Nat)),
      (∀ b bw, acc = some (b, bw) → used b = false ∧ bw = minE b) →
      match l.foldl stepFn acc with
      | none => acc = none ∧ ∀ j ∈ l, used j = true
      | some (bi, bw) =>
          used bi = false ∧ bw = minE bi ∧
          (∀ b0 bw0, acc = some (b0, bw0) → bw ≤ bw0) ∧
          (∀ j ∈ l, used j = false → bw ≤ minE j) := by
    intro l
    induction l with
    | nil =>
      intro acc hacc
      cases acc with
      | none => exact ⟨rfl, fun _ hm => by cases hm⟩
      | some p =>
        rcases p with ⟨b, bw⟩
        have ⟨hu, heq⟩ := hacc b bw rfl
        refine ⟨hu, heq, ?_, fun _ hm => by cases hm⟩
        intro b0 bw0 h; injection h with h'; cases h'; exact Nat.le_refl _
    | cons x xs ih =>
      intro acc hacc
      simp only [List.foldl_cons]
      have hacc' : ∀ b bw, stepFn acc x = some (b, bw) → used b = false ∧ bw = minE b := by
        intro b bw h
        dsimp only [stepFn] at h
        cases hux : used x with
        | true => simp [hux] at h; exact hacc b bw h
        | false =>
          simp only [hux, Bool.false_eq_true, ↓reduceIte] at h
          cases acc with
          | none => injection h with hp; injection hp with h1 h2; subst h1 h2; exact ⟨hux, rfl⟩
          | some p =>
            rcases p with ⟨b0, bw0⟩
            by_cases hlt : minE x < bw0
            · simp only [hlt, ↓reduceIte] at h
              injection h with hp; injection hp with h1 h2; subst h1 h2; exact ⟨hux, rfl⟩
            · simp only [hlt, ↓reduceIte] at h
              exact hacc b bw h
      have hrec := ih (stepFn acc x) hacc'
      cases hres : xs.foldl stepFn (stepFn acc x) with
      | none =>
        rw [hres] at hrec
        rcases hrec with ⟨hst, hall⟩
        dsimp only [stepFn] at hst
        cases hux : used x with
        | false =>
          simp only [hux, Bool.false_eq_true, ↓reduceIte] at hst
          cases acc with
          | none => cases hst
          | some p => rcases p with ⟨b0, bw0⟩; by_cases hlt : minE x < bw0 <;> simp [hlt] at hst
        | true =>
          simp only [hux, ↓reduceIte] at hst
          refine ⟨hst, fun j hm => ?_⟩
          rcases List.mem_cons.mp hm with rfl | hxs
          · exact hux
          · exact hall j hxs
      | some p =>
        rw [hres] at hrec
        rcases p with ⟨bi, bw⟩
        rcases hrec with ⟨hbi, hbw, hle_acc, hle_xs⟩
        refine ⟨hbi, hbw, ?_, ?_⟩
        · intro b0 bw0 h0
          subst h0
          dsimp only [stepFn] at hle_acc
          cases hux : used x with
          | true => simp only [hux, ↓reduceIte] at hle_acc; exact hle_acc b0 bw0 rfl
          | false =>
            simp only [hux, Bool.false_eq_true, ↓reduceIte] at hle_acc
            by_cases hlt : minE x < bw0
            · simp only [hlt, ↓reduceIte] at hle_acc
              have := hle_acc x (minE x) rfl; omega
            · simp only [hlt, ↓reduceIte] at hle_acc
              exact hle_acc b0 bw0 rfl
        · intro j hm huj
          rcases List.mem_cons.mp hm with rfl | hxs
          · dsimp only [stepFn] at hle_acc
            simp only [huj, Bool.false_eq_true, ↓reduceIte] at hle_acc
            cases acc with
            | none => exact hle_acc j (minE j) rfl
            | some p0 =>
              rcases p0 with ⟨b0, bw0⟩
              by_cases hlt : minE j < bw0
              · simp only [hlt, ↓reduceIte] at hle_acc; exact hle_acc j (minE j) rfl
              · simp only [hlt, ↓reduceIte] at hle_acc
                have := hle_acc b0 bw0 rfl; omega
          · exact hle_xs j hxs huj
  have hmain := hfold (List.finRange m) none (fun _ _ h => by cases h)
  cases hres : (List.finRange m).foldl stepFn none with
  | none =>
    rw [hres] at hmain
    rcases hex with ⟨i, hi⟩
    have := hmain.2 i (List.mem_finRange i)
    rw [hi] at this; cases this
  | some p =>
    rw [hres] at hmain
    rcases p with ⟨bi, bw⟩
    rcases hmain with ⟨hbi, hbw, _, hmin⟩
    subst hbw
    exact ⟨bi, hbi, fun j hj => hmin j (List.mem_finRange j) hj, rfl⟩

/- Path-reversal exchange lemma for Prim's MST:
    Contract `used` into `ROOT`, pick `bi` minimizing `minE bi`, trace up in `T` to the first
    vertex whose parent is `none` or in `used`, and reverse the parent path. -/

/-- Contracted edge weight of vertex `v` in tree `T` when `used` is contracted into `ROOT` with `minE`. -/
def contractedEdgeW {m : Nat} (dist : Fin m → Fin m → Nat)
    (used : Fin m → Bool) (minE : Fin m → Nat) (par : Fin m → Option (Fin m)) (v : Fin m) : Nat :=
  if used v then 0
  else match par v with
    | none => minE v
    | some u => if used u then minE v else dist u v

/-- Helper: trace upward in an acyclic `RootedTree` from `v` (with `used v = false`) until a vertex
    whose parent is `none` or in `used`, returning the path `[v, par v, ..., xk]` (all unused, nodup). -/
def traceToCutAux {m : Nat} (T : RootedTree m) (used : Fin m → Bool) :
    Nat → Fin m → List (Fin m)
  | 0, v => [v]
  | fuel + 1, v =>
      match T.par v with
      | none => [v]
      | some u => if used u then [v] else v :: traceToCutAux T used fuel u

/-- Rewire `T.par` by reversing pointers along a path `x_0 :: x_1 :: ... :: x_k` and setting `x_0`'s parent to `none`. -/
def reversePathPar {m : Nat} (par : Fin m → Option (Fin m)) : List (Fin m) → Fin m → Option (Fin m)
  | [] => par
  | [x] => fun v => if v = x then none else par v
  | x :: y :: rest =>
      let par' := reversePathPar par (y :: rest)
      fun v => if v = y then some x else if v = x then none else par' v

/-- Properties of `traceToCutAux` when `fuel ≥ T.rank v`:
    the path starts at `v`, is nonempty, strictly decreasing in `T.rank` (hence `Nodup`),
    all vertices are unused, consecutive elements satisfy `T.par x = some y`, and the last
    element's parent is `none` or in `used`. -/
def IsCutPath {m : Nat} (T : RootedTree m) (used : Fin m → Bool) : List (Fin m) → Prop
  | [] => False
  | [x] => used x = false ∧ match T.par x with | none => True | some u => used u = true
  | x :: y :: rest =>
      used x = false ∧ T.par x = some y ∧ IsCutPath T used (y :: rest)

theorem traceToCutAux_spec {m : Nat} (T : RootedTree m) (used : Fin m → Bool) :
    ∀ (fuel : Nat) (v : Fin m), T.rank v ≤ fuel → used v = false →
      IsCutPath T used (traceToCutAux T used fuel v) ∧
      (traceToCutAux T used fuel v).head? = some v ∧
      ∀ z ∈ traceToCutAux T used fuel v, T.rank z ≤ T.rank v := by
  intro fuel
  induction fuel with
  | zero =>
    intro v hrank huv
    refine ⟨?_, rfl, fun z hz => by simp [traceToCutAux] at hz; subst hz; exact Nat.le_refl _⟩
    simp only [traceToCutAux, IsCutPath]
    refine ⟨huv, ?_⟩
    cases hpar : T.par v with
    | none => trivial
    | some u => have := T.acyc v u hpar; omega
  | succ f ih =>
    intro v hrank huv
    simp only [traceToCutAux]
    cases hpar : T.par v with
    | none =>
      refine ⟨⟨huv, by simp [hpar]⟩, rfl, fun z hz => by simp at hz; subst hz; exact Nat.le_refl _⟩
    | some u =>
      cases huu : used u with
      | true =>
        simp only [huu, ↓reduceIte]
        refine ⟨⟨huv, by simp [hpar, huu]⟩, rfl, fun z hz => by simp at hz; subst hz; exact Nat.le_refl _⟩
      | false =>
        simp only [huu, Bool.false_eq_true, ↓reduceIte]
        have hru : T.rank u < T.rank v := T.acyc v u hpar
        have ⟨hcp, hhd, hrmax⟩ := ih u (by omega) huu
        cases hlst : traceToCutAux T used f u with
        | nil => rw [hlst] at hhd; cases hhd
        | cons u' rest =>
          rw [hlst] at hcp hhd hrmax
          simp only [List.head?_cons, Option.some.injEq] at hhd
          subst hhd
          refine ⟨⟨huv, hpar, hcp⟩, rfl, ?_⟩
          intro z hz
          rcases List.mem_cons.mp hz with rfl | hzr
          · exact Nat.le_refl _
          · have := hrmax z hzr; omega

theorem isCutPath_nodup {m : Nat} (T : RootedTree m) (used : Fin m → Bool) :
    ∀ (l : List (Fin m)), IsCutPath T used l →
      (∀ x ∈ l, ∀ y ∈ l, x = y → True) ∧
      l.Nodup ∧
      (∀ a rest, l = a :: rest → ∀ z ∈ rest, T.rank z < T.rank a) := by
  intro l
  induction l with
  | nil => intro h; cases h
  | cons x xs ih =>
    intro hcp
    cases xs with
    | nil =>
      refine ⟨fun _ _ _ _ _ => trivial, by simp, fun a rest h z hz => by injection h with _ hr; subst hr; cases hz⟩
    | cons y rest =>
      rcases hcp with ⟨_, hpar, hcp_y⟩
      have ⟨_, hnd_y, hlt_y⟩ := ih hcp_y
      have hxy : T.rank y < T.rank x := T.acyc x y hpar
      have hlt_all : ∀ z ∈ (y :: rest), T.rank z < T.rank x := by
        intro z hz
        rcases List.mem_cons.mp hz with rfl | hzr
        · exact hxy
        · exact Nat.lt_trans (hlt_y y rest rfl z hzr) hxy
      have hx_not_mem : x ∉ (y :: rest) := fun hm => Nat.lt_irrefl _ (hlt_all x hm)
      refine ⟨fun _ _ _ _ _ => trivial, List.nodup_cons.mpr ⟨hx_not_mem, hnd_y⟩, ?_⟩
      intro a r h z hz
      injection h with ha hr; subst ha hr
      exact hlt_all z hz

/-- Helper: `reversePathPar` keeps the reversed tree acyclic!
    Specifically, we only need acyclicity on the unused subgraph (no cycle among `¬used'` vertices);
    even simpler: give an explicit ranking on `Fin m` for `reversePathPar T.par path`!
    If `path = [x_0, x_1, ..., x_k]` (with `x_0` now attached to `none`), assign:
    - Any vertex `v` whose ancestor chain in `T` does NOT pass through `path` keeps `rank' v = T.rank v`
    - Actually, even simpler: `x_0` gets rank `0`, `x_j` gets rank `j`, and every vertex `v ∉ path`
      gets rank `path.length + T.rank v`? Check:
      * If `v ∉ path` has `par' v = T.par v = some u`:
        - If `u ∉ path`: `path.length + T.rank u < path.length + T.rank v`!
        - If `u ∈ path`: `rank' u < path.length ≤ path.length + T.rank v`!
      * If `v = x_0`: `par' x_0 = none`!
      * If `v = x_{j+1}`: `par' x_{j+1} = some x_j`, and `rank' x_j = j < j + 1 = rank' x_{j+1}`!!
    OH!! MY!! GOD!! THAT RANKING FUNCTION IS 3 LINES AND WORKS FOR EVERY VERTEX!! -/
def pathIndex {m : Nat} (v : Fin m) : List (Fin m) → Option Nat
  | [] => none
  | x :: xs => if v = x then some 0 else (pathIndex v xs).map (· + 1)

theorem pathIndex_lt {m : Nat} (v : Fin m) (l : List (Fin m)) (k : Nat)
    (h : pathIndex v l = some k) : k < l.length := by
  induction l generalizing k with
  | nil => simp [pathIndex] at h
  | cons x xs ih =>
    simp only [pathIndex, List.length_cons] at h ⊢
    by_cases hvx : v = x
    · simp only [hvx, ↓reduceIte, Option.some.injEq] at h; omega
    · simp only [hvx, ↓reduceIte] at h
      cases hp : pathIndex v xs with
      | none => rw [hp] at h; cases h
      | some k' =>
        rw [hp] at h; simp only [Option.map_some, Option.some.injEq] at h
        have := ih k' hp; omega

theorem pathIndex_none_iff {m : Nat} (v : Fin m) (l : List (Fin m)) :
    pathIndex v l = none ↔ v ∉ l := by
  induction l with
  | nil => simp [pathIndex]
  | cons x xs ih =>
    simp only [pathIndex, List.mem_cons, not_or]
    by_cases hvx : v = x
    · simp [hvx]
    · simp only [hvx, ↓reduceIte, Option.map_eq_none_iff, ih, not_false_eq_true, true_and]

theorem reversePathPar_spec {m : Nat} (par : Fin m → Option (Fin m)) (l : List (Fin m))
    (hnd : l.Nodup) :
    (∀ v, v ∉ l → reversePathPar par l v = par v) ∧
    (∀ x xs, l = x :: xs → reversePathPar par l x = none) ∧
    (∀ (k : Nat) (v : Fin m), pathIndex v l = some (k + 1) →
      ∃ u : Fin m, pathIndex u l = some k ∧ reversePathPar par l v = some u) := by
  induction l with
  | nil =>
    refine ⟨fun _ _ => rfl, fun _ _ h => (by cases h), fun _ _ h => (by simp [pathIndex] at h)⟩
  | cons x xs ih =>
    cases xs with
    | nil =>
      refine ⟨fun v hv => by
                have hvx : v ≠ x := fun h => hv (by simp [h])
                simp [reversePathPar, hvx],
              fun x' xs' h => by injection h with h1 _; subst h1; simp [reversePathPar],
              fun k v hv => by
                simp only [pathIndex] at hv
                by_cases hvx : v = x <;> simp [hvx] at hv⟩
    | cons y rest =>
      have ⟨hx_nm, hnd_y⟩ := List.nodup_cons.mp hnd
      have ⟨hnot, hhead, hidx⟩ := ih hnd_y
      have hxy : y ≠ x := fun h => hx_nm (h ▸ List.mem_cons_self ..)
      refine ⟨?_, ?_, ?_⟩
      · intro v hv
        have hvx : v ≠ x := fun h => hv (h ▸ List.mem_cons_self ..)
        have hvy : v ≠ y := fun h => hv (h ▸ List.mem_cons_of_mem _ (List.mem_cons_self ..))
        have hvr : v ∉ y :: rest := fun h => hv (List.mem_cons_of_mem _ h)
        simp only [reversePathPar, hvy, hvx, ↓reduceIte]
        exact hnot v hvr
      · intro x' xs' h
        injection h with h1 _; subst h1
        simp [reversePathPar, Ne.symm hxy]
      · intro k v hv
        rw [pathIndex] at hv
        by_cases hvx : v = x
        · simp [hvx] at hv
        · simp only [hvx, ↓reduceIte] at hv
          cases hpi : pathIndex v (y :: rest) with
          | none => rw [hpi] at hv; cases hv
          | some k' =>
            rw [hpi] at hv
            simp only [Option.map_some, Option.some.injEq] at hv
            have hkk : k' = k := by omega
            subst hkk
            cases k' with
            | zero =>
              simp only [pathIndex] at hpi
              by_cases hvy : v = y
              · subst hvy
                refine ⟨x, by simp [pathIndex], ?_⟩
                simp [reversePathPar]
              · simp only [hvy, ↓reduceIte] at hpi
                cases hp2 : pathIndex v rest <;> simp [hp2] at hpi
            | succ k'' =>
              have hvy : v ≠ y := by
                intro heq; subst heq; simp [pathIndex] at hpi
              rcases hidx k'' v hpi with ⟨u, hu_pi, hu_par⟩
              have hux : u ≠ x := by
                intro h; apply hx_nm; rw [← h]
                by_cases hnm : u ∉ y :: rest
                · have := (pathIndex_none_iff u (y :: rest)).mpr hnm; rw [this] at hu_pi; cases hu_pi
                · exact Classical.byContradiction hnm
              refine ⟨u, ?_, ?_⟩
              · rw [pathIndex]; simp [hux, hu_pi]
              · simp [reversePathPar, hvy, hvx, hu_par]

/-- Weight-conservation lemma for `reversePathPar` along a cut path `l` starting at `bi` (`used bi = false`). -/
theorem reversePath_weight_le {m : Nat} (dist : Fin m → Fin m → Nat)
    (hdist_symm : ∀ a b, dist a b = dist b a)
    (T : RootedTree m) (used : Fin m → Bool) (minE : Fin m → Nat)
    (bi : Fin m) (hbi : used bi = false)
    (hmin_bi : ∀ j, used j = false → minE bi ≤ minE j)
    (l : List (Fin m)) (hcp : IsCutPath T used l) (hhead : l.head? = some bi) :
    let used' := fun i => used i || decide (i = bi)
    let minE' := fun i => if used' i then minE i else min (minE i) (dist bi i)
    let par' := reversePathPar T.par l
    minE bi + finSum (contractedEdgeW dist used' minE' par') ≤
    finSum (contractedEdgeW dist used minE T.par) := by
  intro used' minE' par'
  have hnd : l.Nodup := (isCutPath_nodup T used l hcp).2.1
  have hspec := reversePathPar_spec T.par l hnd
  -- Split `finSum` into vertices `∈ l` and vertices `∉ l`!
  let inL (v : Fin m) : Bool := decide (v ∈ l)
  rw [finSum_split_pred inL (contractedEdgeW dist used' minE' par')]
  rw [finSum_split_pred inL (contractedEdgeW dist used minE T.par)]
  -- 1) Outside `l`: every `v ∉ l` has `par' v = T.par v`, and `contractedEdgeW` only decreases or stays equal!
  have hout : finSum (fun v => if !inL v then contractedEdgeW dist used' minE' par' v else 0) ≤
              finSum (fun v => if !inL v then contractedEdgeW dist used minE T.par v else 0) := by
    apply finSum_le_finSum; intro v
    by_cases hvl : v ∈ l
    · simp [inL, hvl]
    · simp only [inL, hvl, decide_false, Bool.not_false, ↓reduceIte]
      have hpar_eq : par' v = T.par v := hspec.1 v hvl
      have hv_ne_bi : v ≠ bi := by
        intro heq; subst heq
        cases l with
        | nil => cases hhead
        | cons x xs =>
          simp only [List.head?_cons, Option.some.injEq] at hhead
          subst hhead; exact hvl (List.mem_cons_self ..)
      have hused_eq : used' v = used v := by simp [used', hv_ne_bi]
      unfold contractedEdgeW
      rw [hused_eq, hpar_eq]
      cases huv : used v with
      | true => simp
      | false =>
        simp only [Bool.false_eq_true, ↓reduceIte]
        have hmin_le : minE' v ≤ minE v := by
          simp only [minE', used', huv, hv_ne_bi, decide_false, Bool.or_false, Bool.false_eq_true, ↓reduceIte]
          exact Nat.min_le_left _ _
        cases htv : T.par v with
        | none => exact hmin_le
        | some u =>
          cases huu : used u with
          | true =>
            have hu' : used' u = true := by simp [used', huu]
            simp only [hu', huu, ↓reduceIte]; exact hmin_le
          | false =>
            by_cases hubi : u = bi
            · subst hubi
              have hu' : used' u = true := by simp [used']
              simp only [hu', huu, Bool.false_eq_true, ↓reduceIte, minE', used', huv, hv_ne_bi, Bool.or_false, decide_false]
              exact Nat.min_le_right _ _
            · have hu' : used' u = false := by simp [used', huu, hubi]
              simp only [hu', huu, Bool.false_eq_true, ↓reduceIte]
              exact Nat.le_refl _
  -- 2) Inside `l`: induction on `l` proves `minE bi + ∑_{v ∈ l} newW v ≤ ∑_{v ∈ l} oldW v`!
  have hin_eq : ∀ (f : Fin m → Nat),
      finSum (fun v => if inL v then f v else 0) = (l.map f).sum := by
    intro f
    have h1 : ∀ (ls : List (Fin m)), ls.Nodup →
        finSum (fun v => if decide (v ∈ ls) then f v else 0) = (ls.map f).sum := by
      intro ls hndl
      induction ls with
      | nil => simp [finSum_zero]
      | cons x xs ih =>
        have ⟨hx_nm, hnd_xs⟩ := List.nodup_cons.mp hndl
        simp only [List.map_cons, List.sum_cons]
        rw [← ih hnd_xs]
        have hsp : finSum (fun v => if decide (v ∈ x :: xs) then f v else 0) =
            finSum (fun v => if v = x then f x else 0) +
            finSum (fun v => if decide (v ∈ xs) then f v else 0) := by
          rw [← finSum_add]; congr 1; funext v
          by_cases hvx : v = x
          · subst hvx; simp [hx_nm]
          · simp [hvx]
        rw [hsp, finSum_ite_eq]
    exact h1 l hnd
  rw [hin_eq, hin_eq]
  -- Direct telescoping inequality on `l`:
  have hwalk : ∀ (xs : List (Fin m)), IsCutPath T used xs → xs.Nodup →
      (∀ y ∈ xs, y ∈ l) →
      (∀ x y, (∃ pfx sfx, xs = pfx ++ x :: y :: sfx) → par' y = some x) →
      ∀ x rest, xs = x :: rest →
        minE bi + (rest.map (contractedEdgeW dist used' minE' par')).sum ≤
        (xs.map (contractedEdgeW dist used minE T.par)).sum := by
    intro xs
    induction xs with
    | nil => intro hcp; cases hcp
    | cons x rest ih =>
      intro hcp hnd_x hsub hpar_rev x0 r0 heq
      injection heq with hx0 hr0; subst hx0 hr0
      cases rest with
      | nil =>
        rcases hcp with ⟨hux, hparx⟩
        simp only [List.map_nil, List.sum_nil, Nat.add_zero, List.map_cons, List.sum_cons]
        unfold contractedEdgeW
        simp only [hux, Bool.false_eq_true, ↓reduceIte]
        cases hp_x : T.par x with
        | none => exact hmin_bi x hux
        | some u =>
          rw [hp_x] at hparx
          simp only [hparx, ↓reduceIte]
          exact hmin_bi x hux
      | cons y rest' =>
        rcases hcp with ⟨hux, hpar_xy, hcp_y⟩
        have ⟨hx_nm, hnd_y⟩ := List.nodup_cons.mp hnd_x
        have hpar_yx : par' y = some x := hpar_rev x y ⟨[], rest', rfl⟩
        have hrec := ih hcp_y hnd_y
          (fun z hz => hsub z (List.mem_cons_of_mem _ hz))
          (fun a b ⟨pfx, sfx, h⟩ => hpar_rev a b ⟨x :: pfx, sfx, by simpa using congrArg (x :: ·) h⟩)
          y rest' rfl
        simp only [List.map_cons, List.sum_cons] at hrec ⊢
        -- Compare `contractedEdgeW dist used' minE' par' y` with `contractedEdgeW dist used minE T.par x`!
        have huy : used y = false := by
          cases rest' with
          | nil => exact hcp_y.1
          | cons _ _ => exact hcp_y.1
        have hstep_le : contractedEdgeW dist used' minE' par' y ≤
                        contractedEdgeW dist used minE T.par x := by
          unfold contractedEdgeW
          simp only [hux, hpar_xy, huy, Bool.false_eq_true, ↓reduceIte, hpar_yx]
          cases huy' : used' y with
          | true => exact Nat.zero_le _
          | false =>
            simp only [Bool.false_eq_true, ↓reduceIte]
            cases hux' : used' x with
            | true =>
              -- `used x = false` and `used' x = true` means `x = bi`!
              have hxbi : x = bi := by simp [used', hux] at hux'; exact hux'
              subst hxbi
              simp only [minE', huy', Bool.false_eq_true, ↓reduceIte]
              rw [hdist_symm y x]
              exact Nat.min_le_right (minE y) (dist x y)
            | false =>
              simp only [Bool.false_eq_true, ↓reduceIte]
              rw [hdist_symm x y]
              exact Nat.le_refl _
        omega
  -- Instantiate `hwalk` with `xs = l`!
  cases hl : l with
  | nil => rw [hl] at hhead; cases hhead
  | cons x rest =>
    rw [hl] at hhead hcp hnd hspec
    simp only [List.head?_cons, Option.some.injEq] at hhead
    subst hhead
    simp only [List.map_cons, List.sum_cons]
    have hx_zero : contractedEdgeW dist used' minE' par' x = 0 := by
      unfold contractedEdgeW
      have : used' x = true := by simp [used']
      simp [this]
    rw [hx_zero, Nat.zero_add]
    have hrev_adj : ∀ a b, (∃ pfx sfx, x :: rest = pfx ++ a :: b :: sfx) → par' b = some a := by
      intro a b ⟨pfx, sfx, hsplit⟩
      -- Show `pathIndex a (x :: rest) = some pfx.length` and `pathIndex b (x :: rest) = some (pfx.length + 1)`
      have hpi_gen : ∀ (p : List (Fin m)) (s : List (Fin m)) (z : Fin m),
          (p ++ z :: s).Nodup → pathIndex z (p ++ z :: s) = some p.length := by
        intro p s z
        induction p with
        | nil => intro _; simp [pathIndex]
        | cons w ws ihp =>
          intro hndp
          simp only [List.cons_append] at hndp ⊢
          have ⟨hw_nm, hnd_ws⟩ := List.nodup_cons.mp hndp
          have hzw : z ≠ w := fun h => hw_nm (h ▸ List.mem_append_right _ (List.mem_cons_self ..))
          simp only [pathIndex, hzw, ↓reduceIte, ihp hnd_ws, Option.map_some, List.length_cons]
      have hnd_sp : (pfx ++ a :: b :: sfx).Nodup := hsplit ▸ hnd
      have hpi_a : pathIndex a (x :: rest) = some pfx.length := by
        rw [hsplit]; exact hpi_gen pfx (b :: sfx) a hnd_sp
      have hpi_b : pathIndex b (x :: rest) = some (pfx.length + 1) := by
        have hsp2 : x :: rest = (pfx ++ [a]) ++ b :: sfx := by simp [hsplit]
        rw [hsp2]
        have h := hpi_gen (pfx ++ [a]) sfx b (hsp2 ▸ hnd)
        simpa [List.length_append] using h
      rcases hspec.2.2 pfx.length b hpi_b with ⟨u, hu_pi, hu_par⟩
      -- Uniqueness of vertex at index `pfx.length` in a Nodup list: `u = a`!
      have huniq : ∀ (ls : List (Fin m)) (k : Nat) (u₁ u₂ : Fin m),
          pathIndex u₁ ls = some k → pathIndex u₂ ls = some k → u₁ = u₂ := by
        intro ls; induction ls with
        | nil => intro _ _ _ h1 _; simp [pathIndex] at h1
        | cons w ws ihls =>
          intro k u₁ u₂ h1 h2
          simp only [pathIndex] at h1 h2
          by_cases h1w : u₁ = w <;> by_cases h2w : u₂ = w
          · exact h1w.trans h2w.symm
          · simp only [h1w, ↓reduceIte, Option.some.injEq] at h1
            simp only [h2w, ↓reduceIte] at h2
            cases hp2 : pathIndex u₂ ws <;> simp [hp2] at h2; omega
          · simp only [h2w, ↓reduceIte, Option.some.injEq] at h2
            simp only [h1w, ↓reduceIte] at h1
            cases hp1 : pathIndex u₁ ws <;> simp [hp1] at h1; omega
          · simp only [h1w, h2w, ↓reduceIte] at h1 h2
            cases hp1 : pathIndex u₁ ws with
            | none => simp [hp1] at h1
            | some v1 =>
              cases hp2 : pathIndex u₂ ws with
              | none => simp [hp2] at h2
              | some v2 =>
                simp [hp1, hp2] at h1 h2
                have heq : v2 = v1 := by omega
                exact ihls v1 u₁ u₂ hp1 (by rw [hp2, heq])
      have hua : u = a := huniq (x :: rest) pfx.length u a hu_pi hpi_a
      rw [← hua]
      simpa [par', hl] using hu_par
    have hmain := hwalk (x :: rest) hcp hnd (fun _ h => hl ▸ h) hrev_adj x rest rfl
    simp only [List.map_cons, List.sum_cons] at hmain
    omega

/-- Prim's MST lower-bounds EVERY rooted spanning tree on `Fin m` (`_mst_cost`, ex1.py:L96-L139)! -/
theorem primMST_le_treeWeight {m : Nat} (dist : Fin m → Fin m → Nat)
    (hdist_symm : ∀ a b, dist a b = dist b a)
    (rootDist : Fin m → Nat) (T : RootedTree m) :
    primMST dist rootDist ≤ treeWeight dist rootDist T := by
  -- Induction on number of remaining unused vertices!
  suffices ∀ (steps : Nat) (used : Fin m → Bool) (minE : Fin m → Nat) (T_cur : RootedTree m),
      steps = finSum (fun i => if used i then 0 else 1) →
      primLoop dist steps used minE ≤ finSum (contractedEdgeW dist used minE T_cur.par) by
    have h0 := this m (fun _ => false) rootDist T (by
      simp only [Bool.false_eq_true, ↓reduceIte, finSum_eq_list_sum]
      suffices ∀ l : List (Fin m), (l.map (fun _ => 1)).sum = l.length by
        rw [this (List.finRange m), List.length_finRange]
      intro l; induction l with | nil => rfl | cons _ _ ih => simp [ih]; omega)
    have heq : finSum (contractedEdgeW dist (fun _ => false) rootDist T.par) = treeWeight dist rootDist T := by
      unfold treeWeight contractedEdgeW treeEdgeWeight
      congr 1
    rw [heq] at h0
    exact h0
  intro steps
  induction steps with
  | zero => intro _ _ _ _; simp [primLoop]
  | succ k ih =>
    intro used minE T_cur hk
    -- Since `k + 1 = # unused`, there exists an unused vertex!
    have hex : ∃ i : Fin m, used i = false := by
      by_cases hall : ∀ i : Fin m, used i = true
      · exfalso
        have hz : finSum (fun i : Fin m => if used i then 0 else 1) = 0 := by
          have : (fun i : Fin m => if used i then 0 else 1) = (fun _ => 0) := by
            funext i; simp [hall i]
          rw [this, finSum_zero]
        omega
      · have hfind : ∀ l : List (Fin m), (∃ i ∈ l, used i = false) ∨ (∀ i ∈ l, used i = true) := by
          intro l; induction l with
          | nil => right; intro _ hm; cases hm
          | cons x xs ihl =>
            cases hx : used x with
            | false => left; exact ⟨x, List.mem_cons_self .., hx⟩
            | true =>
              rcases ihl with ⟨y, hy, hyf⟩ | hall_xs
              · left; exact ⟨y, List.mem_cons_of_mem _ hy, hyf⟩
              · right; intro z hz; rcases List.mem_cons.mp hz with rfl | hzs
                · exact hx
                · exact hall_xs z hzs
        rcases hfind (List.finRange m) with ⟨i, _, hi⟩ | hall_m
        · exact ⟨i, hi⟩
        · exfalso; exact hall (fun i => hall_m i (List.mem_finRange i))
    rcases primStep_spec dist used minE hex with ⟨bi, hbi, hmin_bi, hstep_eq⟩
    simp only [primLoop, hstep_eq]
    let used' := fun i => used i || decide (i = bi)
    let minE' := fun i => if used' i then minE i else min (minE i) (dist bi i)
    -- Construct cut path from `bi` in `T_cur` and rewire into `T'`!
    let path := traceToCutAux T_cur used (T_cur.rank bi) bi
    have ⟨hcp, hhead, _⟩ := traceToCutAux_spec T_cur used (T_cur.rank bi) bi (Nat.le_refl _) hbi
    have hnd : path.Nodup := (isCutPath_nodup T_cur used path hcp).2.1
    let par' := reversePathPar T_cur.par path
    let rank' (v : Fin m) : Nat :=
      match pathIndex v path with
      | some idx => idx
      | none => path.length + T_cur.rank v
    have hacyc' : ∀ v u, par' v = some u → rank' u < rank' v := by
      have hspec := reversePathPar_spec T_cur.par path hnd
      intro v u hpar_vu
      cases hpv : pathIndex v path with
      | none =>
        have hv_nm : v ∉ path := (pathIndex_none_iff v path).mp hpv
        have hpar_eq : par' v = T_cur.par v := hspec.1 v hv_nm
        rw [hpar_eq] at hpar_vu
        have hlt := T_cur.acyc v u hpar_vu
        dsimp only [rank']; rw [hpv]
        cases hpu : pathIndex u path with
        | none => simp only [hpu]; omega
        | some idx =>
          simp only [hpu]
          have hidx_lt := pathIndex_lt u path idx hpu
          omega
      | some idx =>
        cases idx with
        | zero =>
          cases hpth : path with
          | nil => rw [hpth] at hpv; simp [pathIndex] at hpv
          | cons x xs =>
            rw [hpth] at hpv
            have hvx : v = x := by
              simp only [pathIndex] at hpv
              by_cases h : v = x
              · exact h
              · simp only [h, ↓reduceIte] at hpv
                cases h2 : pathIndex v xs <;> simp [h2] at hpv
            subst hvx
            have hnone : par' v = none := hspec.2.1 v xs hpth
            rw [hnone] at hpar_vu; cases hpar_vu
        | succ idx' =>
          rcases hspec.2.2 idx' v hpv with ⟨u', hu'_pi, hu'_par⟩
          dsimp only [par'] at hpar_vu
          rw [hu'_par] at hpar_vu
          injection hpar_vu with huu; subst huu
          dsimp only [rank']; rw [hpv, hu'_pi]; simp only; omega
    let T' : RootedTree m := ⟨par', rank', hacyc'⟩
    have hk' : k = finSum (fun i => if used' i then 0 else 1) := by
      have hupd := finSum_update (fun i => if used i then 0 else 1) bi 0
      have hfn : (fun i => if used' i then 0 else 1) =
                 (fun i => if i = bi then 0 else if used i then 0 else 1) := by
        funext i; by_cases hi : i = bi <;> simp [used', hi]
      rw [hfn]; simp only [hbi, Bool.false_eq_true, ↓reduceIte] at hupd; omega
    have hrec := ih used' minE' T' hk'
    have hrew := reversePath_weight_le dist hdist_symm T_cur used minE bi hbi hmin_bi path hcp hhead
    exact Nat.le_trans (Nat.add_le_add_left hrec (minE bi)) hrew

/-- Predicate matching a non-bridge DRIVE action performed by a specific truck `t`. -/
def isTruckNBDrive {I : Instance} (C : NBContraction I) (t : Fin I.numTrucks) : Action I → Bool
  | .drive t₀ u v => decide (t₀ = t) && !C.isBridge u v
  | _             => false

/-- Minimum contracted NB distance from any truck in state `s` to supernode `r` (0 if no trucks). -/
def minTruckNBDist {I : Instance} (C : NBContraction I) (s : State I) (r : Fin C.numNB) : Nat :=
  match (List.finRange I.numTrucks).map (fun t => C.nbDist (C.nbId (s.truckPhysLoc t)) r) with
  | [] => 0
  | d :: ds => ds.foldl min d

theorem minTruckNBDist_le {I : Instance} (C : NBContraction I) (s : State I) (r : Fin C.numNB)
    (t : Fin I.numTrucks) :
    minTruckNBDist C s r ≤ C.nbDist (C.nbId (s.truckPhysLoc t)) r := by
  unfold minTruckNBDist
  have hmem : C.nbDist (C.nbId (s.truckPhysLoc t)) r ∈
      (List.finRange I.numTrucks).map (fun t' => C.nbDist (C.nbId (s.truckPhysLoc t')) r) :=
    List.mem_map.mpr ⟨t, List.mem_finRange t, rfl⟩
  have hfold_le : ∀ (l : List Nat) (acc : Nat),
      l.foldl min acc ≤ acc ∧ ∀ x ∈ l, l.foldl min acc ≤ x := by
    intro l
    induction l with
    | nil => intro acc; exact ⟨Nat.le_refl _, fun _ h => by cases h⟩
    | cons a as ih =>
      intro acc
      simp only [List.foldl_cons]
      have ⟨h1, h2⟩ := ih (min acc a)
      refine ⟨Nat.le_trans h1 (Nat.min_le_left _ _), fun x hx => ?_⟩
      rcases List.mem_cons.mp hx with rfl | hxs
      · exact Nat.le_trans h1 (Nat.min_le_right _ _)
      · exact h2 x hxs
  cases hls : (List.finRange I.numTrucks).map (fun t' => C.nbDist (C.nbId (s.truckPhysLoc t')) r) with
  | nil => rw [hls] at hmem; cases hmem
  | cons d ds =>
    rw [hls] at hmem
    rcases List.mem_cons.mp hmem with heq | hds
    · rw [heq]; exact (hfold_le ds d).1
    · exact (hfold_le ds d).2 _ hds

/-- Triangle inequality along any plan slice `[0..k]` for truck `t`. -/
theorem truck_nb_dist_le_drives {I : Instance} (C : NBContraction I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (t : Fin I.numTrucks) (k : Nat) :
    C.nbDist (C.nbId (s.truckPhysLoc t)) (C.nbId ((stateAt s π k).truckPhysLoc t)) ≤
    countActions (isTruckNBDrive C t) (π.take k) := by
  induction hp generalizing k with
  | nil => simp [stateAt, C.dist_self]
  | @cons sa sb _ a rest hstep _ ih =>
    cases k with
    | zero => simp [stateAt, C.dist_self]
    | succ k' =>
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      simp only [stateAt_succ, ← hsb_eq, List.take_succ_cons, countActions, List.map_cons, List.sum_cons]
      have hrec := ih (validState_step hv hstep) k'
      have htri := C.dist_tri (C.nbId (sa.truckPhysLoc t)) (C.nbId (sb.truckPhysLoc t))
        (C.nbId ((stateAt sb rest k').truckPhysLoc t))
      have h1step : C.nbDist (C.nbId (sa.truckPhysLoc t)) (C.nbId (sb.truckPhysLoc t)) ≤
                    (if isTruckNBDrive C t a then 1 else 0) := by
        cases hstep with
        | @drive t₀ u v ht₀ _ hroad =>
          by_cases htt : t = t₀
          · subst htt
            simp only [State.truckPhysLoc, ht₀, updateFn, ↓reduceIte, isTruckNBDrive, decide_true, Bool.true_and]
            cases hb : C.isBridge u v with
            | true =>
              rw [C.bridge_zero u v hroad hb, C.dist_self]; exact Nat.zero_le _
            | false =>
              simp only [Bool.not_false, ↓reduceIte]
              exact C.nb_edge_one u v hroad hb
          · simp [State.truckPhysLoc, updateFn, htt, C.dist_self]
        | load _ _ _ => simp [State.truckPhysLoc, C.dist_self]
        | unload _ _ => simp [State.truckPhysLoc, C.dist_self]
        | @board t₀ f ht₀ _ =>
          by_cases htt : t = t₀
          · subst htt; simp [State.truckPhysLoc, updateFn, ht₀, C.dist_self]
          · simp [State.truckPhysLoc, updateFn, htt, C.dist_self]
        | @disembark t₀ f ht₀ =>
          by_cases htt : t = t₀
          · subst htt; simp [State.truckPhysLoc, updateFn, ht₀, C.dist_self]
          · simp [State.truckPhysLoc, updateFn, htt, C.dist_self]
        | @sail f u v hf _ hserved =>
          cases htl : sa.truckLoc t with
          | atLoc _ => simp [State.truckPhysLoc, htl, C.dist_self]
          | onFerry f' =>
            by_cases hff : f' = f
            · subst hff
              have hpos_f : 0 < I.ferryCap f' := by
                have hle1 : 1 ≤ sa.ferryCount f' := by
                  have h := le_finSum (fun t'' => if sa.truckLoc t'' = .onFerry f' then 1 else 0) t
                  simpa [State.ferryCount, htl] using h
                have hcap := hv.aboard_le_cap f'; omega
              have hu_sv : I.ferryServed f' u = true := hf ▸ hv.ferry_served f'
              simp only [State.truckPhysLoc, htl, updateFn, ↓reduceIte, hf]
              rw [C.ferry_zero f' u v hpos_f hu_sv hserved, C.dist_self]
              exact Nat.zero_le _
            · simp [State.truckPhysLoc, htl, updateFn, hff, C.dist_self]
      unfold countActions at hrec
      omega

/-- Helper: executing `π.drop k₁` from `stateAt s π k₁` is a valid suffix plan. -/
theorem validPlan_drop {I : Instance} {s s_end : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_end) (k : Nat) :
    ValidState I (stateAt s π k) ∧ ValidPlan I (stateAt s π k) (π.drop k) s_end := by
  induction hp generalizing k with
  | nil => exact ⟨by simp [stateAt]; exact hv, by simp [stateAt]; exact ValidPlan.nil⟩
  | @cons sa sb _ a rest hstep _ ih =>
    cases k with
    | zero => exact ⟨hv, ValidPlan.cons hstep ‹_›⟩
    | succ k' =>
      have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
      simp only [stateAt_succ, ← hsb_eq, List.drop_succ_cons]
      exact ih (validState_step hv hstep) k'

theorem stateAt_add {I : Instance} (s : State I) (π : Plan I) (k₁ d : Nat) :
    stateAt (stateAt s π k₁) (π.drop k₁) d = stateAt s π (k₁ + d) := by
  induction π generalizing s k₁ with
  | nil => simp [stateAt]
  | cons a rest ih =>
    cases k₁ with
    | zero => simp [stateAt]
    | succ k₁' =>
      have hrew : k₁' + 1 + d = (k₁' + d) + 1 := by omega
      rw [hrew]
      simp only [stateAt_succ, List.drop_succ_cons]
      exact ih (applyAction s a) k₁'

/-- Interval distance bound: for `k₁ ≤ k₂`, distance moved by truck `t` between `k₁` and `k₂`
    is `≤ countActions (isTruckNBDrive C t) (π.take k₂) - countActions (isTruckNBDrive C t) (π.take k₁)`. -/
theorem truck_nb_dist_interval_le {I : Instance} (C : NBContraction I)
    {s s_end : State I} {π : Plan I} (hv : ValidState I s) (hp : ValidPlan I s π s_end)
    (t : Fin I.numTrucks) {k₁ k₂ : Nat} (hle : k₁ ≤ k₂) :
    C.nbDist (C.nbId ((stateAt s π k₁).truckPhysLoc t)) (C.nbId ((stateAt s π k₂).truckPhysLoc t)) +
      countActions (isTruckNBDrive C t) (π.take k₁)
    ≤ countActions (isTruckNBDrive C t) (π.take k₂) := by
  have ⟨hv1, hp1⟩ := validPlan_drop hv hp k₁
  have h1 := truck_nb_dist_le_drives C hv1 hp1 t (k₂ - k₁)
  have hst : stateAt (stateAt s π k₁) (π.drop k₁) (k₂ - k₁) = stateAt s π k₂ := by
    rw [stateAt_add]; congr 1; omega
  rw [hst] at h1
  have hsplit : ∀ (ls : Plan I) (a b : Nat), a ≤ b → ls.take b = ls.take a ++ (ls.drop a).take (b - a) := by
    intro ls
    induction ls with
    | nil => intro _ _ _; simp
    | cons x rest ih =>
      intro a b hab
      cases a with
      | zero => simp
      | succ a' =>
        cases b with
        | zero => omega
        | succ b' =>
          simp only [List.take_succ_cons, List.drop_succ_cons, List.cons_append]
          congr 1
          have hsub : b' + 1 - (a' + 1) = b' - a' := by omega
          rw [hsub]
          exact ih a' b' (by omega)
  have hcnt_add : countActions (isTruckNBDrive C t) (π.take k₂) =
      countActions (isTruckNBDrive C t) (π.take k₁) +
      countActions (isTruckNBDrive C t) ((π.drop k₁).take (k₂ - k₁)) := by
    rw [hsplit π k₁ k₂ hle]; unfold countActions; rw [List.map_append, List.sum_append]
  omega

/-- Every valid plan visiting all `m` required NB supernodes yields `primMST ≤ costNonBridgeDrive C π`
    (proving `nb_mst ≤ costNonBridgeDrive π`, `ex1.py:L96-L139, L1588-L1606`)! -/
theorem nb_mst_admissible {I : Instance} (C : NBContraction I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal)
    {m : Nat} (req : Fin m → Fin C.numNB)
    (visitTime : Fin m → Nat) (visitTruck : Fin m → Fin I.numTrucks)
    (htime_le : ∀ i, visitTime i ≤ π.length)
    (hvisit : ∀ i, C.nbId ((stateAt s π (visitTime i)).truckPhysLoc (visitTruck i)) = req i) :
    primMST (fun i j => C.nbDist (req i) (req j)) (fun i => minTruckNBDist C s (req i))
    ≤ costNonBridgeDrive C π := by
  let dist (i j : Fin m) : Nat := C.nbDist (req i) (req j)
  let rootDist (i : Fin m) : Nat := minTruckNBDist C s (req i)
  have hdist_symm : ∀ i j, dist i j = dist j i := fun i j => C.dist_symm (req i) (req j)
  -- Assign strict total order rank `key i = visitTime i * m + i.val` on `Fin m`
  let key (i : Fin m) : Nat := visitTime i * m + i.val
  have hkey_inj : ∀ i j : Fin m, key i = key j → i = j := by
    intro i j h
    have hm : 0 < m := Nat.lt_of_le_of_lt (Nat.zero_le _) i.isLt
    have hdiv : visitTime i = visitTime j := by
      have h1 := congrArg (· / m) h
      have hi1 : (visitTime i * m + i.val) / m = visitTime i := by
        rw [Nat.mul_comm, Nat.mul_add_div hm, Nat.div_eq_of_lt i.isLt, Nat.add_zero]
      have hj1 : (visitTime j * m + j.val) / m = visitTime j := by
        rw [Nat.mul_comm, Nat.mul_add_div hm, Nat.div_eq_of_lt j.isLt, Nat.add_zero]
      simpa [key, hi1, hj1] using h1
    apply Fin.ext
    simp only [key, hdiv] at h; omega
  have hkey_time : ∀ i j : Fin m, key i < key j → visitTime i ≤ visitTime j := by
    intro i j h
    by_cases hle : visitTime i ≤ visitTime j
    · exact hle
    · exfalso
      have hgt : visitTime j + 1 ≤ visitTime i := by omega
      have hmul : (visitTime j + 1) * m ≤ visitTime i * m := Nat.mul_le_mul_right m hgt
      rw [Nat.add_mul, Nat.one_mul] at hmul
      have hj := j.isLt
      simp only [key] at h; omega
  -- For each `i`, pick predecessor `par i` = vertex `j` with `visitTruck j = visitTruck i` and maximal `key j < key i`!
  let par (i : Fin m) : Option (Fin m) :=
    (List.finRange m).foldl (fun acc j =>
      if visitTruck j = visitTruck i ∧ key j < key i then
        match acc with
        | none => some j
        | some best => if key j > key best then some j else some best
      else acc) none
  have hpar_spec : ∀ i : Fin m,
      (∀ u, par i = some u →
        visitTruck u = visitTruck i ∧ key u < key i ∧
        ∀ j, visitTruck j = visitTruck i → key j < key i → key j ≤ key u) ∧
      (par i = none → ∀ j, visitTruck j = visitTruck i → ¬ (key j < key i)) := by
    intro i
    let stepP := fun (acc : Option (Fin m)) (j : Fin m) =>
      if visitTruck j = visitTruck i ∧ key j < key i then
        match acc with
        | none => some j
        | some best => if key j > key best then some j else some best
      else acc
    have hfold : ∀ (l : List (Fin m)) (acc : Option (Fin m)),
        (∀ u, acc = some u → visitTruck u = visitTruck i ∧ key u < key i) →
        match l.foldl stepP acc with
        | none => acc = none ∧ ∀ j ∈ l, ¬ (visitTruck j = visitTruck i ∧ key j < key i)
        | some u =>
            visitTruck u = visitTruck i ∧ key u < key i ∧
            (∀ u0, acc = some u0 → key u0 ≤ key u) ∧
            (∀ j ∈ l, visitTruck j = visitTruck i ∧ key j < key i → key j ≤ key u) := by
      intro l
      induction l with
      | nil =>
        intro acc hacc
        cases acc with
        | none => exact ⟨rfl, fun _ hm => by cases hm⟩
        | some u =>
          have ⟨ht, hk⟩ := hacc u rfl
          exact ⟨ht, hk, fun u0 h => by injection h with heq; subst heq; exact Nat.le_refl _, fun _ hm => by cases hm⟩
      | cons x xs ih =>
        intro acc hacc
        simp only [List.foldl_cons]
        have hacc' : ∀ u, stepP acc x = some u → visitTruck u = visitTruck i ∧ key u < key i := by
          intro u hu
          dsimp only [stepP] at hu
          by_cases hx : visitTruck x = visitTruck i ∧ key x < key i
          · simp only [hx, ↓reduceIte] at hu
            cases acc with
            | none => injection hu with heq; subst heq; exact hx
            | some b =>
              by_cases hgt : key x > key b
              · simp only [hgt, ↓reduceIte] at hu; injection hu with heq; subst heq; exact hx
              · simp only [hgt, ↓reduceIte] at hu; injection hu with heq; subst heq; exact hacc b rfl
          · simp only [hx, ↓reduceIte] at hu; exact hacc u hu
        have hrec := ih (stepP acc x) hacc'
        cases hres : xs.foldl stepP (stepP acc x) with
        | none =>
          rw [hres] at hrec
          rcases hrec with ⟨hst, hall⟩
          dsimp only [stepP] at hst
          by_cases hx : visitTruck x = visitTruck i ∧ key x < key i
          · simp only [hx, ↓reduceIte] at hst
            cases acc with
            | none => cases hst
            | some b => by_cases hgt : key x > key b <;> simp [hgt] at hst
          · simp only [hx, ↓reduceIte] at hst
            refine ⟨hst, fun j hm => ?_⟩
            rcases List.mem_cons.mp hm with rfl | hxs
            · exact hx
            · exact hall j hxs
        | some u =>
          rw [hres] at hrec
          rcases hrec with ⟨htu, hku, hle_acc, hle_xs⟩
          refine ⟨htu, hku, ?_, ?_⟩
          · intro u0 h0; subst h0
            dsimp only [stepP] at hle_acc
            by_cases hx : visitTruck x = visitTruck i ∧ key x < key i
            · simp only [hx, ↓reduceIte] at hle_acc
              by_cases hgt : key x > key u0
              · simp only [hgt, ↓reduceIte] at hle_acc
                have := hle_acc x rfl; omega
              · simp only [hgt, ↓reduceIte] at hle_acc
                exact hle_acc u0 rfl
            · simp only [hx, ↓reduceIte] at hle_acc; exact hle_acc u0 rfl
          · intro j hm hjcond
            rcases List.mem_cons.mp hm with rfl | hxs
            · dsimp only [stepP] at hle_acc
              simp only [hjcond, ↓reduceIte] at hle_acc
              cases acc with
              | none => exact hle_acc j rfl
              | some b =>
                by_cases hgt : key j > key b
                · simp only [hgt, ↓reduceIte] at hle_acc; exact hle_acc j rfl
                · simp only [hgt, ↓reduceIte] at hle_acc
                  have := hle_acc b rfl; omega
            · exact hle_xs j hxs hjcond
    have hm := hfold (List.finRange m) none (fun _ h => by cases h)
    cases hres : (List.finRange m).foldl stepP none with
    | none =>
      rw [hres] at hm
      constructor
      · intro u hu; change (List.finRange m).foldl stepP none = some u at hu; rw [hres] at hu; cases hu
      · intro _ j htj hkj; exact hm.2 j (List.mem_finRange j) ⟨htj, hkj⟩
    | some u =>
      rw [hres] at hm
      constructor
      · intro u' hu'
        change (List.finRange m).foldl stepP none = some u' at hu'
        rw [hres] at hu'; injection hu' with heq; subst heq
        exact ⟨hm.1, hm.2.1, fun j htj hkj => hm.2.2.2 j (List.mem_finRange j) ⟨htj, hkj⟩⟩
      · intro hnone
        change (List.finRange m).foldl stepP none = none at hnone
        rw [hres] at hnone; cases hnone
  let T : RootedTree m := ⟨par, key, fun v u h => (hpar_spec v).1 u h |>.2.1⟩
  apply Nat.le_trans (primMST_le_treeWeight dist hdist_symm rootDist T)
  -- Bound `treeWeight T` by summing per truck `t`!
  -- Define `pref t i := countActions (isTruckNBDrive C t) (π.take (visitTime i))`
  -- For each `i` with `visitTruck i = t`:
  --   - if `par i = none`: `rootDist i ≤ pref t i`
  --   - if `par i = some u`: `dist u i + pref t u ≤ pref t i`!
  -- And `par` is INJECTIVE on each truck `t` (no two vertices `i₁ ≠ i₂` share the same `par`!),
  -- so summing over all `i` with `visitTruck i = t` telescopes to `≤ countActions (isTruckNBDrive C t) π`!!
  have hpar_inj : ∀ i₁ i₂ u : Fin m, par i₁ = some u → par i₂ = some u → i₁ = i₂ := by
    intro i₁ i₂ u h1 h2
    have ⟨ht1, hk1, hmax1⟩ := (hpar_spec i₁).1 u h1
    have ⟨ht2, hk2, hmax2⟩ := (hpar_spec i₂).1 u h2
    have hteq : visitTruck i₁ = visitTruck i₂ := ht1.symm.trans ht2
    by_cases hlt : key i₁ < key i₂
    · have := hmax2 i₁ hteq hlt; omega
    · by_cases hgt : key i₂ < key i₁
      · have := hmax1 i₂ hteq.symm hgt; omega
      · exact hkey_inj i₁ i₂ (by omega)
  have hnone_uniq : ∀ i₁ i₂ : Fin m, visitTruck i₁ = visitTruck i₂ →
      par i₁ = none → par i₂ = none → i₁ = i₂ := by
    intro i₁ i₂ hteq h1 h2
    by_cases hlt : key i₁ < key i₂
    · exfalso; exact (hpar_spec i₂).2 h2 i₁ hteq hlt
    · by_cases hgt : key i₂ < key i₁
      · exfalso; exact (hpar_spec i₁).2 h1 i₂ hteq.symm hgt
      · exact hkey_inj i₁ i₂ (by omega)
  -- Per-truck telescope bound
  have htruck_bound : ∀ t : Fin I.numTrucks,
      finSum (fun i => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0) ≤
      countActions (isTruckNBDrive C t) π := by
    intro t
    let pref (i : Fin m) : Nat := countActions (isTruckNBDrive C t) (π.take (visitTime i))
    let predVal (i : Fin m) : Nat := match par i with | none => 0 | some u => pref u
    -- 1. Pointwise bound: `treeEdgeWeight i + predVal i ≤ pref i` for every `i` with `visitTruck i = t`!
    have hpt : ∀ i : Fin m, visitTruck i = t → treeEdgeWeight dist rootDist par i + predVal i ≤ pref i := by
      intro i hti
      unfold treeEdgeWeight
      dsimp only [predVal, pref, dist, rootDist]
      cases hpi : par i with
      | none =>
        simp only [Nat.add_zero]
        have h1 := minTruckNBDist_le C s (req i) t
        have h2 := truck_nb_dist_le_drives C hv hp t (visitTime i)
        have hvi : C.nbId ((stateAt s π (visitTime i)).truckPhysLoc t) = req i := hti ▸ hvisit i
        rw [hvi] at h2
        exact Nat.le_trans h1 h2
      | some u =>
        have ⟨htu, hku, _⟩ := (hpar_spec i).1 u hpi
        have hle_time : visitTime u ≤ visitTime i := hkey_time u i hku
        have hint := truck_nb_dist_interval_le C hv hp t hle_time
        have htu' : visitTruck u = t := htu.trans hti
        have hvu : C.nbId ((stateAt s π (visitTime u)).truckPhysLoc t) = req u := htu' ▸ hvisit u
        have hvi : C.nbId ((stateAt s π (visitTime i)).truckPhysLoc t) = req i := hti ▸ hvisit i
        rw [hvu, hvi] at hint
        exact hint
    -- 2. Sum of `treeEdgeWeight i + predVal i` ≤ sum of `pref i` over `{i | visitTruck i = t}`!
    have hsum_pt :
        finSum (fun i => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0) +
        finSum (fun i => if visitTruck i = t then predVal i else 0) ≤
        finSum (fun i => if visitTruck i = t then pref i else 0) := by
      rw [← finSum_add]
      apply finSum_le_finSum; intro i
      by_cases hti : visitTruck i = t
      · simp only [hti, ↓reduceIte]; exact hpt i hti
      · simp [hti]
    -- 3. Every `u` with `visitTruck u = t` is `par i` for at most one `i`, AND there is at most one
    --    maximal `i_max` (not equal to `par` of anyone) with `pref i_max ≤ countActions (isTruckNBDrive C t) π`!
    --    Specifically: if there are NO vertices with `visitTruck i = t`, LHS = 0 ≤ RHS;
    --    otherwise let `i_max` be the vertex with `visitTruck i_max = t` maximizing `key`!
    --    Then EVERY `u ≠ i_max` with `visitTruck u = t` appears as `par i` for some unique `i` with `visitTruck i = t`!
    by_cases hex_t : ∃ i : Fin m, visitTruck i = t
    · -- Find `i_max` maximizing `key` among `{i | visitTruck i = t}`
      have hex_max : ∃ imax : Fin m, visitTruck imax = t ∧ ∀ j, visitTruck j = t → key j ≤ key imax := by
        let maxFn := fun (acc : Option (Fin m)) (j : Fin m) =>
          if visitTruck j = t then
            match acc with
            | none => some j
            | some b => if key j > key b then some j else some b
          else acc
        have hf : ∀ (l : List (Fin m)) (acc : Option (Fin m)),
            (∀ b, acc = some b → visitTruck b = t) →
            match l.foldl maxFn acc with
            | none => acc = none ∧ ∀ j ∈ l, visitTruck j ≠ t
            | some b => visitTruck b = t ∧ (∀ b0, acc = some b0 → key b0 ≤ key b) ∧
                (∀ j ∈ l, visitTruck j = t → key j ≤ key b) := by
          intro l; induction l with
          | nil =>
            intro acc hacc; cases acc with
            | none => exact ⟨rfl, fun _ hm => by cases hm⟩
            | some b => exact ⟨hacc b rfl, fun b0 h => by injection h with e; subst e; exact Nat.le_refl _, fun _ hm => by cases hm⟩
          | cons x xs ihl =>
            intro acc hacc; simp only [List.foldl_cons]
            have hacc' : ∀ b, maxFn acc x = some b → visitTruck b = t := by
              intro b hb; dsimp only [maxFn] at hb
              by_cases hx : visitTruck x = t
              · simp only [hx, ↓reduceIte] at hb
                cases acc with
                | none => injection hb with e; subst e; exact hx
                | some b0 =>
                  by_cases hgt : key x > key b0
                  · simp only [hgt, ↓reduceIte] at hb; injection hb with e; subst e; exact hx
                  · simp only [hgt, ↓reduceIte] at hb; injection hb with e; subst e; exact hacc b0 rfl
              · simp only [hx, ↓reduceIte] at hb; exact hacc b hb
            have hrec := ihl (maxFn acc x) hacc'
            cases hres : xs.foldl maxFn (maxFn acc x) with
            | none =>
              rw [hres] at hrec; rcases hrec with ⟨hst, hall⟩
              dsimp only [maxFn] at hst
              by_cases hx : visitTruck x = t
              · simp only [hx, ↓reduceIte] at hst
                cases acc with
                | none => cases hst
                | some b0 => by_cases hgt : key x > key b0 <;> simp [hgt] at hst
              · simp only [hx, ↓reduceIte] at hst
                refine ⟨hst, fun j hm => ?_⟩
                rcases List.mem_cons.mp hm with rfl | hxs
                · exact hx
                · exact hall j hxs
            | some b =>
              rw [hres] at hrec; rcases hrec with ⟨htb, hle_acc, hle_xs⟩
              refine ⟨htb, ?_, ?_⟩
              · intro b0 h0; subst h0; dsimp only [maxFn] at hle_acc
                by_cases hx : visitTruck x = t
                · simp only [hx, ↓reduceIte] at hle_acc
                  by_cases hgt : key x > key b0
                  · simp only [hgt, ↓reduceIte] at hle_acc; have := hle_acc x rfl; omega
                  · simp only [hgt, ↓reduceIte] at hle_acc; exact hle_acc b0 rfl
                · simp only [hx, ↓reduceIte] at hle_acc; exact hle_acc b0 rfl
              · intro j hm htj
                rcases List.mem_cons.mp hm with rfl | hxs
                · dsimp only [maxFn] at hle_acc; simp only [htj, ↓reduceIte] at hle_acc
                  cases acc with
                  | none => exact hle_acc j rfl
                  | some b0 =>
                    by_cases hgt : key j > key b0
                    · simp only [hgt, ↓reduceIte] at hle_acc; exact hle_acc j rfl
                    · simp only [hgt, ↓reduceIte] at hle_acc; have := hle_acc b0 rfl; omega
                · exact hle_xs j hxs htj
        have hm := hf (List.finRange m) none (fun _ h => by cases h)
        cases hres : (List.finRange m).foldl maxFn none with
        | none =>
          rw [hres] at hm; rcases hex_t with ⟨i, hi⟩
          exact absurd hi (hm.2 i (List.mem_finRange i))
        | some b =>
          rw [hres] at hm; exact ⟨b, hm.1, fun j htj => hm.2.2 j (List.mem_finRange j) htj⟩
      rcases hex_max with ⟨imax, himax_t, himax_ge⟩
      -- Every `u ≠ imax` with `visitTruck u = t` is `par i` for some `i` (the minimal `i` with `key i > key u` and `visitTruck i = t`)!
      have hsurj : ∀ u : Fin m, visitTruck u = t → u ≠ imax →
          ∃ i : Fin m, visitTruck i = t ∧ par i = some u := by
        intro u htu hne
        have hlt_max : key u < key imax := by
          have hle := himax_ge u htu
          by_cases heq : key u = key imax
          · exact absurd (hkey_inj u imax heq) hne
          · omega
        -- Pick `i` with `visitTruck i = t` and `key u < key i` minimizing `key i`!
        let minFn := fun (acc : Option (Fin m)) (j : Fin m) =>
          if visitTruck j = t ∧ key u < key j then
            match acc with
            | none => some j
            | some b => if key j < key b then some j else some b
          else acc
        have hf : ∀ (l : List (Fin m)) (acc : Option (Fin m)),
            (∀ b, acc = some b → visitTruck b = t ∧ key u < key b) →
            match l.foldl minFn acc with
            | none => acc = none ∧ ∀ j ∈ l, ¬ (visitTruck j = t ∧ key u < key j)
            | some b => visitTruck b = t ∧ key u < key b ∧
                (∀ b0, acc = some b0 → key b ≤ key b0) ∧
                (∀ j ∈ l, visitTruck j = t ∧ key u < key j → key b ≤ key j) := by
          intro l; induction l with
          | nil =>
            intro acc hacc; cases acc with
            | none => exact ⟨rfl, fun _ hm => by cases hm⟩
            | some b => exact ⟨(hacc b rfl).1, (hacc b rfl).2, fun b0 h => by injection h with e; subst e; exact Nat.le_refl _, fun _ hm => by cases hm⟩
          | cons x xs ihl =>
            intro acc hacc; simp only [List.foldl_cons]
            have hacc' : ∀ b, minFn acc x = some b → visitTruck b = t ∧ key u < key b := by
              intro b hb; dsimp only [minFn] at hb
              by_cases hx : visitTruck x = t ∧ key u < key x
              · simp only [hx, ↓reduceIte] at hb
                cases acc with
                | none => injection hb with e; subst e; exact hx
                | some b0 =>
                  by_cases hlt : key x < key b0
                  · simp only [hlt, ↓reduceIte] at hb; injection hb with e; subst e; exact hx
                  · simp only [hlt, ↓reduceIte] at hb; injection hb with e; subst e; exact hacc b0 rfl
              · simp only [hx, ↓reduceIte] at hb; exact hacc b hb
            have hrec := ihl (minFn acc x) hacc'
            cases hres : xs.foldl minFn (minFn acc x) with
            | none =>
              rw [hres] at hrec; rcases hrec with ⟨hst, hall⟩
              dsimp only [minFn] at hst
              by_cases hx : visitTruck x = t ∧ key u < key x
              · simp only [hx, ↓reduceIte] at hst
                cases acc with
                | none => cases hst
                | some b0 => by_cases hlt : key x < key b0 <;> simp [hlt] at hst
              · simp only [hx, ↓reduceIte] at hst
                refine ⟨hst, fun j hm => ?_⟩
                rcases List.mem_cons.mp hm with rfl | hxs
                · exact hx
                · exact hall j hxs
            | some b =>
              rw [hres] at hrec; rcases hrec with ⟨htb, hkb, hle_acc, hle_xs⟩
              refine ⟨htb, hkb, ?_, ?_⟩
              · intro b0 h0; subst h0; dsimp only [minFn] at hle_acc
                by_cases hx : visitTruck x = t ∧ key u < key x
                · simp only [hx, ↓reduceIte] at hle_acc
                  by_cases hlt : key x < key b0
                  · simp only [hlt, ↓reduceIte] at hle_acc; have := hle_acc x rfl; omega
                  · simp only [hlt, ↓reduceIte] at hle_acc; exact hle_acc b0 rfl
                · simp only [hx, ↓reduceIte] at hle_acc; exact hle_acc b0 rfl
              · intro j hm hjc
                rcases List.mem_cons.mp hm with rfl | hxs
                · dsimp only [minFn] at hle_acc; simp only [hjc, ↓reduceIte] at hle_acc
                  cases acc with
                  | none => exact hle_acc j rfl
                  | some b0 =>
                    by_cases hlt : key j < key b0
                    · simp only [hlt, ↓reduceIte] at hle_acc; exact hle_acc j rfl
                    · simp only [hlt, ↓reduceIte] at hle_acc; have := hle_acc b0 rfl; omega
                · exact hle_xs j hxs hjc
        have hm := hf (List.finRange m) none (fun _ h => by cases h)
        cases hres : (List.finRange m).foldl minFn none with
        | none =>
          rw [hres] at hm; exact absurd ⟨himax_t, hlt_max⟩ (hm.2 imax (List.mem_finRange imax))
        | some i =>
          rw [hres] at hm
          rcases hm with ⟨hti, hki, _, hmin_i⟩
          refine ⟨i, hti, ?_⟩
          cases hpi : par i with
          | none =>
            exfalso; exact (hpar_spec i).2 hpi u (htu.trans hti.symm) hki
          | some w =>
            have ⟨htw, hkw, hmaxw⟩ := (hpar_spec i).1 w hpi
            have hle1 : key u ≤ key w := hmaxw u (htu.trans hti.symm) hki
            by_cases hlt_uw : key u < key w
            · have := hmin_i w (List.mem_finRange w) ⟨htw.trans hti, hlt_uw⟩; omega
            · have heq : w = u := hkey_inj w u (by omega)
              rw [heq]
      -- Therefore `finSum_{i : visitTruck i = t, i ≠ imax} pref i ≤ finSum_{i : visitTruck i = t} predVal i`!
      have hpred_ge :
          finSum (fun u => if visitTruck u = t && decide (u ≠ imax) then pref u else 0) ≤
          finSum (fun i => if visitTruck i = t then predVal i else 0) := by
        -- Rewrite `predVal i` as `finSum_u (if par i = some u then pref u else 0)` and swap sums!
        have hrew : finSum (fun i => if visitTruck i = t then predVal i else 0) =
            finSum (fun u => finSum (fun i => if visitTruck i = t ∧ par i = some u then pref u else 0)) := by
          rw [finSum_comm]
          congr 1; funext i
          by_cases hti : visitTruck i = t
          · cases hpi : par i with
            | none =>
              have hfn' : (fun u => if visitTruck i = t ∧ (none : Option (Fin m)) = some u then pref u else 0) = (fun _ => 0) := by
                funext u; simp [hti]
              rw [hfn', finSum_zero]
              simp [hti, predVal, hpi]
            | some u₀ =>
              have hfn : (fun u => if visitTruck i = t ∧ some u₀ = some u then pref u else 0) =
                         (fun u => if u = u₀ then pref u₀ else 0) := by
                funext u; by_cases hu : u = u₀
                · subst hu; simp [hti]
                · simp [hti, hu, Ne.symm hu]
              rw [hfn, finSum_ite_eq]
              simp [hti, predVal, hpi]
          · have hz : (fun u => if visitTruck i = t ∧ par i = some u then pref u else 0) =
                      (fun _ => 0) := by funext u; simp [hti]
            rw [hz, finSum_zero]
            simp [hti]
        rw [hrew]
        apply finSum_le_finSum; intro u
        by_cases hcond : visitTruck u = t ∧ u ≠ imax
        · have h1 : decide (visitTruck u = t) = true := decide_eq_true hcond.1
          have h2 : decide (u ≠ imax) = true := decide_eq_true hcond.2
          simp only [h1, h2, Bool.and_self, ↓reduceIte]
          rcases hsurj u hcond.1 hcond.2 with ⟨i, hti, hpi⟩
          have hle := le_finSum (fun i' => if visitTruck i' = t ∧ par i' = some u then pref u else 0) i
          simp only [hti, hpi, and_self, ↓reduceIte] at hle
          exact hle
        · have hf : (decide (visitTruck u = t) && decide (u ≠ imax)) = false := by
            by_cases h1 : visitTruck u = t
            · have h2 : ¬ (u ≠ imax) := fun h => hcond ⟨h1, h⟩
              simp [h1, h2]
            · simp [h1]
          simp only [hf, Bool.false_eq_true, ↓reduceIte]; exact Nat.zero_le _
      -- And `finSum_{i : visitTruck i = t} pref i = pref imax + finSum_{u ≠ imax} pref u`!
      have hsplit_max :
          finSum (fun i => if visitTruck i = t then pref i else 0) =
          pref imax + finSum (fun u => if visitTruck u = t && decide (u ≠ imax) then pref u else 0) := by
        have hupd := finSum_update (fun u => if visitTruck u = t then pref u else 0) imax 0
        have hfn : (fun u => if u = imax then 0 else if visitTruck u = t then pref u else 0) =
                   (fun u => if visitTruck u = t && decide (u ≠ imax) then pref u else 0) := by
          funext u; by_cases hu : u = imax
          · subst hu; simp
          · simp [hu]
        rw [hfn] at hupd
        simp only [himax_t, ↓reduceIte] at hupd
        omega
      -- Finally `pref imax ≤ countActions (isTruckNBDrive C t) π` (prefix ≤ whole plan)!
      have hpref_le : pref imax ≤ countActions (isTruckNBDrive C t) π := by
        dsimp only [pref]
        calc countActions (isTruckNBDrive C t) (π.take (visitTime imax))
            ≤ countActions (isTruckNBDrive C t) (π.take (visitTime imax)) +
              countActions (isTruckNBDrive C t) (π.drop (visitTime imax)) := Nat.le_add_right _ _
          _ = countActions (isTruckNBDrive C t) (π.take (visitTime imax) ++ π.drop (visitTime imax)) := by
              unfold countActions; rw [List.map_append, List.sum_append]
          _ = countActions (isTruckNBDrive C t) π := by rw [List.take_append_drop]
      omega
    · have hz : (fun i : Fin m => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0) = (fun _ => 0) := by
        funext i
        have hne : visitTruck i ≠ t := fun h => hex_t ⟨i, h⟩
        simp [hne]
      rw [hz, finSum_zero]; exact Nat.zero_le _
  -- Sum per-truck bounds over all `t : Fin I.numTrucks`!
  have htree_split : treeWeight dist rootDist T =
      finSum (fun t => finSum (fun i => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0)) := by
    unfold treeWeight
    rw [finSum_comm]
    congr 1; funext i
    have hfn : (fun t => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0) =
               (fun t => if t = visitTruck i then treeEdgeWeight dist rootDist par i else 0) := by
      funext t; by_cases h : t = visitTruck i <;> simp [h, eq_comm]
    rw [hfn, finSum_ite_eq]
  rw [htree_split]
  have hsum_trucks :
      finSum (fun t => finSum (fun i => if visitTruck i = t then treeEdgeWeight dist rootDist par i else 0)) ≤
      finSum (fun t => countActions (isTruckNBDrive C t) π) :=
    finSum_le_finSum htruck_bound
  have htrucks_eq_nb : finSum (fun t => countActions (isTruckNBDrive C t) π) = costNonBridgeDrive C π := by
    suffices ∀ ps : Plan I, finSum (fun t => countActions (isTruckNBDrive C t) ps) = costNonBridgeDrive C ps from this π
    intro ps
    unfold costNonBridgeDrive countActions
    induction ps with
    | nil => simp [finSum_zero]
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons] at ih ⊢
      rw [finSum_add, ih]
      congr 1
      cases a with
      | drive t₀ u v =>
        have hfn : (fun t => if isTruckNBDrive C t (.drive t₀ u v) then 1 else 0) =
                   (fun t => if t = t₀ then (if !C.isBridge u v then 1 else 0) else 0) := by
          funext t; by_cases h : t = t₀
          · subst h; simp [isTruckNBDrive]
          · have hne : t₀ ≠ t := Ne.symm h
            simp [isTruckNBDrive, h, hne]
        rw [hfn, finSum_ite_eq]; rfl
      | load _ _ => simp [isTruckNBDrive, isNonBridgeDrive, finSum_zero]
      | unload _ _ => simp [isTruckNBDrive, isNonBridgeDrive, finSum_zero]
      | board _ _ => simp [isTruckNBDrive, isNonBridgeDrive, finSum_zero]
      | disembark _ _ => simp [isTruckNBDrive, isNonBridgeDrive, finSum_zero]
      | sail _ _ _ => simp [isTruckNBDrive, isNonBridgeDrive, finSum_zero]
  omega

/-- Combined `h_drive = h_bridge + h_nb ≤ costDrive π` (`ex1.py:L1608`):
    Bridge drives and non-bridge drives partition `DRIVE` actions disjointly! -/
theorem h_drive_combination {I : Instance} (C : NBContraction I) (π : Plan I)
    (bridges : List (BridgeEdge I))
    (hb_marked : ∀ b ∈ bridges, C.isBridge b.u b.v = true ∧ C.isBridge b.v b.u = true)
    (h_bridge h_nb : Nat)
    (h1 : h_bridge ≤ countActions (fun a => bridges.any (fun b => isEdgeDrive b.u b.v a)) π)
    (h2 : h_nb ≤ costNonBridgeDrive C π) :
    h_bridge + h_nb ≤ costDrive π := by
  have hpart : countActions (fun a => bridges.any (fun b => isEdgeDrive b.u b.v a)) π +
               costNonBridgeDrive C π ≤ costDrive π := by
    clear h1 h2 h_bridge h_nb
    unfold costNonBridgeDrive countActions costDrive
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      dsimp only at ih ⊢
      have hstep : (if (bridges.any fun b => isEdgeDrive b.u b.v a) = true then 1 else 0) +
                   (if isNonBridgeDrive C a = true then 1 else 0) ≤ actionCostDrive a := by
        cases a with
        | drive t u v =>
          simp only [actionCostDrive, isNonBridgeDrive]
          by_cases hany : bridges.any (fun b => isEdgeDrive b.u b.v (.drive t u v)) = true
          · simp only [hany, ↓reduceIte]
            rw [List.any_eq_true] at hany
            rcases hany with ⟨b, hb, hedge⟩
            simp only [isEdgeDrive, Bool.or_eq_true, Bool.and_eq_true, decide_eq_true_eq] at hedge
            have hbr : C.isBridge u v = true := by
              rcases hedge with ⟨rfl, rfl⟩ | ⟨rfl, rfl⟩
              · exact (hb_marked b hb).1
              · exact (hb_marked b hb).2
            simp [hbr]
          · have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.drive t u v)) = false :=
              Bool.eq_false_iff.mpr hany
            simp only [hf, Bool.false_eq_true, ↓reduceIte]
            by_cases hbr : C.isBridge u v = true
            · simp [hbr]
            · have hbf : C.isBridge u v = false := Bool.eq_false_iff.mpr hbr
              simp [hbf]
        | load p t =>
          have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.load p t)) = false := by
            rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h; rcases h with ⟨_, _, he⟩; simp [isEdgeDrive] at he
          simp [hf, actionCostDrive, isNonBridgeDrive]
        | unload p t =>
          have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.unload p t)) = false := by
            rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h; rcases h with ⟨_, _, he⟩; simp [isEdgeDrive] at he
          simp [hf, actionCostDrive, isNonBridgeDrive]
        | board t f =>
          have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.board t f)) = false := by
            rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h; rcases h with ⟨_, _, he⟩; simp [isEdgeDrive] at he
          simp [hf, actionCostDrive, isNonBridgeDrive]
        | disembark t f =>
          have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.disembark t f)) = false := by
            rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h; rcases h with ⟨_, _, he⟩; simp [isEdgeDrive] at he
          simp [hf, actionCostDrive, isNonBridgeDrive]
        | sail f u v =>
          have hf : bridges.any (fun b => isEdgeDrive b.u b.v (.sail f u v)) = false := by
            rw [Bool.eq_false_iff]; intro h; rw [List.any_eq_true] at h; rcases h with ⟨_, _, he⟩; simp [isEdgeDrive] at he
          simp [hf, actionCostDrive, isNonBridgeDrive]
      omega
  omega

/-- Every undelivered ground package at `l` is loaded by some truck at `l` during any goal-reaching plan,
    and every undelivered package is unloaded by some truck at `I.pkgGoal p` during any goal-reaching plan.
    This directly justifies `nb_req` in `ex1.py:L1588-L1606`. -/
theorem undeliv_ground_visited {I : Instance} {s s_goal : State I} {π : Plan I}
    (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (l : Fin I.numLocs)
    (hpl : s.pkgLoc p = .atLoc l) (hnd : s.pkgDelivered p = false) :
    ∃ k ≤ π.length, ∃ t : Fin I.numTrucks, (stateAt s π k).truckPhysLoc t = l := by
  induction hp with
  | nil =>
    have hgoal := hg p
    rw [hpl] at hgoal; injection hgoal with hl
    simp [State.pkgDelivered, hpl, hl] at hnd
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    cases hstep with
    | @load p' t l' ht hpl' _ =>
      by_cases hpp : p' = p
      · subst hpp
        rw [hpl] at hpl'; injection hpl' with hll; subst hll
        exact ⟨0, Nat.zero_le _, t, by simp [stateAt, State.truckPhysLoc, ht]⟩
      · have hpl_b : ({ sa with pkgLoc := updateFn sa.pkgLoc p' (.inTruck t) } : State I).pkgLoc p = .atLoc l := by
          simp [updateFn, Ne.symm hpp, hpl]
        have hnd_b : ({ sa with pkgLoc := updateFn sa.pkgLoc p' (.inTruck t) } : State I).pkgDelivered p = false := by
          simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd
        rcases ih hg hpl_b hnd_b with ⟨k, hkle, t', hloc⟩
        refine ⟨k + 1, by simp; omega, t', ?_⟩
        simpa [stateAt_succ, ← hsb_eq] using hloc
    | @unload p' t l' ht hpl' =>
      have hpp : p' ≠ p := by intro h; subst h; rw [hpl] at hpl'; cases hpl'
      have hpl_b : ({ sa with pkgLoc := updateFn sa.pkgLoc p' (.atLoc l') } : State I).pkgLoc p = .atLoc l := by
        simp [updateFn, Ne.symm hpp, hpl]
      have hnd_b : ({ sa with pkgLoc := updateFn sa.pkgLoc p' (.atLoc l') } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd
      rcases ih hg hpl_b hnd_b with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc
    | drive _ _ _ =>
      rcases ih hg hpl hnd with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc
    | board _ _ =>
      rcases ih hg hpl hnd with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc
    | disembark _ =>
      rcases ih hg hpl hnd with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc
    | sail _ _ _ =>
      rcases ih hg hpl hnd with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc

theorem undeliv_goal_visited {I : Instance} {s s_goal : State I} {π : Plan I}
    (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (hnd : s.pkgDelivered p = false) :
    ∃ k ≤ π.length, ∃ t : Fin I.numTrucks, (stateAt s π k).truckPhysLoc t = I.pkgGoal p := by
  induction hp with
  | nil =>
    have hgoal := hg p
    simp [State.pkgDelivered, hgoal] at hnd
  | @cons sa sb _ a rest hstep _ ih =>
    have hsb_eq : sb = applyAction sa a := step_eq_applyAction hstep
    by_cases hdel_b : sb.pkgDelivered p = true
    · -- `p` became delivered on step `a`, which must be `UNLOAD{p, t}` at `I.pkgGoal p`!
      cases hstep with
      | @unload p' t l' ht _ =>
        by_cases hpp : p' = p
        · subst hpp
          have hlg : l' = I.pkgGoal p' := by
            simp [State.pkgDelivered, updateFn] at hdel_b; exact hdel_b
          subst hlg
          exact ⟨0, Nat.zero_le _, t, by simp [stateAt, State.truckPhysLoc, ht]⟩
        · exfalso
          simp [State.pkgDelivered, updateFn, Ne.symm hpp] at hdel_b
          simp [State.pkgDelivered] at hnd
          exact hnd hdel_b
      | @load p' t l' _ _ _ =>
        exfalso
        by_cases hpp : p' = p
        · subst hpp; simp [State.pkgDelivered, updateFn] at hdel_b
        · simp [State.pkgDelivered, updateFn, Ne.symm hpp] at hdel_b
          simp [State.pkgDelivered] at hnd
          exact hnd hdel_b
      | drive _ _ _ => exfalso; simp [State.pkgDelivered] at hdel_b hnd; exact hnd hdel_b
      | board _ _ => exfalso; simp [State.pkgDelivered] at hdel_b hnd; exact hnd hdel_b
      | disembark _ => exfalso; simp [State.pkgDelivered] at hdel_b hnd; exact hnd hdel_b
      | sail _ _ _ => exfalso; simp [State.pkgDelivered] at hdel_b hnd; exact hnd hdel_b
    · have hnd_b : sb.pkgDelivered p = false := Bool.eq_false_iff.mpr hdel_b
      rcases ih hg hnd_b with ⟨k, hkle, t', hloc⟩
      refine ⟨k + 1, by simp; omega, t', ?_⟩
      simpa [stateAt_succ, ← hsb_eq] using hloc

/-- Special-case `num_nb == 2` bound (`ex1.py:L1588-L1596`): if all trucks start in the same NB supernode `s0`
    and some required NB supernode differs from `s0`, then `1 ≤ costNonBridgeDrive C π`. -/
theorem nb_two_supernode_sound {I : Instance} (C : NBContraction I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal)
    (s0 : Fin C.numNB) (h_all_s0 : ∀ t : Fin I.numTrucks, C.nbId (s.truckPhysLoc t) = s0)
    (r : Fin C.numNB) (hr_ne : r ≠ s0) (hd_pos : 1 ≤ C.nbDist s0 r)
    (k : Nat) (t : Fin I.numTrucks) (hvis : C.nbId ((stateAt s π k).truckPhysLoc t) = r) :
    1 ≤ costNonBridgeDrive C π := by
  have h1 := truck_nb_dist_le_drives C hv hp t k
  rw [h_all_s0 t, hvis] at h1
  have h2 : countActions (isTruckNBDrive C t) (π.take k) ≤ countActions (isTruckNBDrive C t) π := by
    calc countActions (isTruckNBDrive C t) (π.take k)
        ≤ countActions (isTruckNBDrive C t) (π.take k) + countActions (isTruckNBDrive C t) (π.drop k) := Nat.le_add_right _ _
      _ = countActions (isTruckNBDrive C t) (π.take k ++ π.drop k) := by unfold countActions; rw [List.map_append, List.sum_append]
      _ = countActions (isTruckNBDrive C t) π := by rw [List.take_append_drop]
  have h3 : countActions (isTruckNBDrive C t) π ≤ costNonBridgeDrive C π := by
    unfold costNonBridgeDrive countActions
    clear hv hp h_all_s0 hvis h1 h2
    induction π with
    | nil => simp
    | cons a rest ih =>
      simp only [List.map_cons, List.sum_cons]
      have ha : (if isTruckNBDrive C t a = true then 1 else 0) ≤ (if isNonBridgeDrive C a = true then 1 else 0) := by
        cases a with
        | drive t₀ u v =>
          simp only [isTruckNBDrive, isNonBridgeDrive]
          by_cases hbr : C.isBridge u v = true
          · simp [hbr]
          · have hbf : C.isBridge u v = false := Bool.eq_false_iff.mpr hbr
            by_cases h : t₀ = t <;> simp [hbf, h]
        | load _ _ => simp [isTruckNBDrive, isNonBridgeDrive]
        | unload _ _ => simp [isTruckNBDrive, isNonBridgeDrive]
        | board _ _ => simp [isTruckNBDrive, isNonBridgeDrive]
        | disembark _ _ => simp [isTruckNBDrive, isNonBridgeDrive]
        | sail _ _ _ => simp [isTruckNBDrive, isNonBridgeDrive]
      omega
  omega

end IslandLogistics
