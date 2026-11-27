/-
  SingleAndExclusive.lean — Module 5a of the Island Logistics Admissibility Proof.
  Formalizes and proves admissibility of:
    1. `h_lu` (load/unload lower bound on `costLU`, `ex1.py:L1338-L1375`)
    2. `NoSailMetric` and `h_pack_truck` (heavy+light packing on `costDrive + costBD`, `ex1.py:L318, L340-L346, L1455-L1470`)
    3. `FullMetric`, `costMove`, and `h_single` (single-package lower bound on `costMove`, `ex1.py:L318-L348, L1633-L1650`)
    4. Sole-capable-truck heavy exclusive sum + approach (`ex1.py:L1418-L1449`)
    5. Exact infinite-capacity pickup-and-delivery forward layered DP `_excl_tsp_lb` (`ex1.py:L827-L885, L1450-L1453`)

  ZERO `sorry`, ZERO `admit`, ZERO custom `axiom`. Pure Lean 4 core only.
-/

import Domain
import PackingAndFlux
import BridgesAndCycles

namespace IslandLogistics

-- ==============================================================================
-- 1. Load/Unload Lower Bound `h_lu ≤ costLU π` (`ex1.py:L1338-L1375`)
-- ==============================================================================

/-- Per-package load/unload potential: 0 if delivered, 1 if in a truck, 2 if on ground. -/
def pkgLUPot {I : Instance} (s : State I) (p : Fin I.numPkgs) : Nat :=
  if s.pkgDelivered p then 0
  else match s.pkgLoc p with
    | .inTruck _ => 1
    | .atLoc _   => 2

/-- `h_lu(s)` matching `ex1.py:L1338-L1375`: sum of `1` for loaded undelivered packages
    and `2` for ground undelivered packages. -/
def hLU (I : Instance) (s : State I) : Nat :=
  finSum (fun p => pkgLUPot s p)

/-- Indicator for load/unload actions acting on package `p`. -/
def isPkgLU {I : Instance} (p : Fin I.numPkgs) : Action I → Bool
  | .load p' _   => decide (p' = p)
  | .unload p' _ => decide (p' = p)
  | _            => false

/-- Per-package load/unload bound: `pkgLUPot s p ≤ countActions (isPkgLU p) π`. -/
theorem pkgLUPot_le_count {I : Instance} {s s_goal : State I} {π : Plan I}
    (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal) (p : Fin I.numPkgs) :
    pkgLUPot s p ≤ countActions (isPkgLU p) π := by
  induction hp with
  | @nil s_end =>
    have hgp := hg p
    simp [pkgLUPot, State.pkgDelivered, hgp]
  | @cons s1 s2 _ a rest hstep _ ih =>
    have hstep_drop : pkgLUPot s1 p ≤ (if isPkgLU p a = true then 1 else 0) + pkgLUPot s2 p := by
      cases hstep with
      | @load p' t l ht hp' hcap =>
        by_cases hpp : p' = p
        · subst hpp
          by_cases hgl : l = I.pkgGoal p'
          · simp [pkgLUPot, isPkgLU, State.pkgDelivered, hp', updateFn, hgl]
          · simp [pkgLUPot, isPkgLU, State.pkgDelivered, hp', updateFn, hgl]
        · have hdel : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t) } : State I).pkgDelivered p = s1.pkgDelivered p := by
            simp [State.pkgDelivered, updateFn, Ne.symm hpp]
          have hpot : pkgLUPot { s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t) } p = pkgLUPot s1 p := by
            simp [pkgLUPot, hdel, updateFn, Ne.symm hpp]
          rw [hpot]; exact Nat.le_add_left _ _
      | @unload p' t l ht hp' =>
        by_cases hpp : p' = p
        · subst hpp
          by_cases hgl : l = I.pkgGoal p'
          · simp [pkgLUPot, isPkgLU, State.pkgDelivered, hp', updateFn, hgl]
          · simp [pkgLUPot, isPkgLU, State.pkgDelivered, hp', updateFn, hgl]
        · have hdel : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l) } : State I).pkgDelivered p = s1.pkgDelivered p := by
            simp [State.pkgDelivered, updateFn, Ne.symm hpp]
          have hpot : pkgLUPot { s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l) } p = pkgLUPot s1 p := by
            simp [pkgLUPot, hdel, updateFn, Ne.symm hpp]
          rw [hpot]; exact Nat.le_add_left _ _
      | drive _ _ _ => simp [pkgLUPot, State.pkgDelivered]
      | board _ _ => simp [pkgLUPot, State.pkgDelivered]
      | disembark _ => simp [pkgLUPot, State.pkgDelivered]
      | sail _ _ _ => simp [pkgLUPot, State.pkgDelivered]
    have hcnt : countActions (isPkgLU p) (a :: rest) =
        (if isPkgLU p a = true then 1 else 0) + countActions (isPkgLU p) rest := by
      simp [countActions]
    have hrec := ih hg
    omega

/-- Sum of per-package load/unload counts equals `costLU π`. -/
theorem sum_pkgLU_eq_costLU {I : Instance} (π : Plan I) :
    finSum (fun p => countActions (isPkgLU p) π) = costLU π := by
  induction π with
  | nil => simp [countActions, costLU, finSum_zero]
  | cons a rest ih =>
    have hsplit : (fun p => countActions (isPkgLU p) (a :: rest)) =
        fun p => (if isPkgLU p a = true then 1 else 0) + countActions (isPkgLU p) rest := by
      funext p; simp [countActions]
    rw [hsplit, finSum_add, ih]
    cases a with
    | load p' t =>
      have hf : (fun p => if isPkgLU p (.load p' t) = true then 1 else 0) =
                (fun p => if p = p' then 1 else 0) := by
        funext p; by_cases h : p = p'
        · subst h; simp [isPkgLU]
        · simp [isPkgLU, h, Ne.symm h]
      rw [hf, finSum_ite_eq]; simp [costLU, actionCostLU]
    | unload p' t =>
      have hf : (fun p => if isPkgLU p (.unload p' t) = true then 1 else 0) =
                (fun p => if p = p' then 1 else 0) := by
        funext p; by_cases h : p = p'
        · subst h; simp [isPkgLU]
        · simp [isPkgLU, h, Ne.symm h]
      rw [hf, finSum_ite_eq]; simp [costLU, actionCostLU]
    | drive _ _ _ => simp [isPkgLU, finSum_zero, costLU, actionCostLU]
    | board _ _ => simp [isPkgLU, finSum_zero, costLU, actionCostLU]
    | disembark _ _ => simp [isPkgLU, finSum_zero, costLU, actionCostLU]
    | sail _ _ _ => simp [isPkgLU, finSum_zero, costLU, actionCostLU]

/-- Admissibility of `h_lu`: `hLU I s ≤ costLU π` (`ex1.py:L1338-L1375`). -/
theorem hLU_le_costLU {I : Instance} {s s_goal : State I} {π : Plan I}
    (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal) :
    hLU I s ≤ costLU π := by
  unfold hLU
  calc finSum (fun p => pkgLUPot s p)
      ≤ finSum (fun p => countActions (isPkgLU p) π) := finSum_le_finSum (fun p => pkgLUPot_le_count hp hg p)
    _ = costLU π := sum_pkgLU_eq_costLU π

-- ==============================================================================
-- 2. No-Sail Metric & `h_pack_truck ≤ costDrive π + costBD π` (`ex1.py:L1455-L1470`)
-- ==============================================================================

/-- Exact specification of `dist_no_sail` (road = 1, active ferry = 2) and
    `ferry_disembark_no_sail` (`min_{p served} (1 + dist_no_sail p g)`),
    with unreachable entries encoded as 0 (`ex1.py:L318, L340-L346, L1461`). -/
structure NoSailMetric (I : Instance) where
  distNS         : Fin I.numLocs → Fin I.numLocs → Nat
  ferryNS        : Fin I.numFerries → Fin I.numLocs → Nat
  distNS_self    : ∀ u, distNS u u = 0
  distNS_road    : ∀ u v g, I.road u v = true → distNS u g ≤ 1 + distNS v g
  board_step     : ∀ f p g, 0 < I.ferryCap f → I.ferryServed f p = true → distNS p g ≤ 1 + ferryNS f g
  disembark_step : ∀ f p g, 0 < I.ferryCap f → I.ferryServed f p = true → ferryNS f g ≤ 1 + distNS p g

/-- Truck action indicator (`DRIVE`, `BOARD`, `DISEMBARK`). -/
def isTruckAct {I : Instance} : Action I → Bool
  | .drive _ _ _   => true
  | .board _ _     => true
  | .disembark _ _ => true
  | _              => false

theorem countActions_isTruckAct {I : Instance} (π : Plan I) :
    countActions isTruckAct π = costDrive π + costBD π := by
  induction π with
  | nil => simp [countActions, costDrive, costBD]
  | cons a rest ih =>
    cases a <;> simp [countActions, isTruckAct, costDrive, costBD, actionCostDrive, actionCostBD] at ih ⊢ <;> omega

/-- Package no-sail potential matching `ex1.py:L1460`:
    `dist_ns[cl][gl]` if on ground or in a grounded truck, `f_ns[on_f][gl]` if aboard a ferry. -/
def potNS {I : Instance} (M : NoSailMetric I) (s : State I) (p : Fin I.numPkgs) : Nat :=
  match s.pkgOnFerry p with
  | none   => M.distNS (s.pkgPhysLoc p) (I.pkgGoal p)
  | some f => M.ferryNS f (I.pkgGoal p)

/-- Exact definition of `h_pack_truck` matching `ex1.py:L1456-L1469`. -/
def hPackTruck {I : Instance} (M : NoSailMetric I) (s : State I) (min_hw : Nat) : Nat :=
  let cap := maxDynEffCap I s
  let hd  := finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p > cap / 2) then potNS M s p else 0)
  let lwd := finSum (fun p => if !s.pkgDelivered p && decide (I.pkgWeight p ≤ cap / 2) then I.pkgWeight p * potNS M s p else 0)
  let twd := finSum (fun p => if !s.pkgDelivered p then I.pkgWeight p * potNS M s p else 0)
  packLB hd min_hw lwd twd cap

/-- Admissibility of `h_pack_truck`: `hPackTruck M s min_hw ≤ costDrive π + costBD π`
    (`ex1.py:L1455-L1470`) via `packLB_plan_sound`! -/
theorem hPackTruck_le_drive_add_bd {I : Instance} (M : NoSailMetric I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (hcap : 0 < maxDynEffCap I s)
    (min_hw : Nat)
    (hmin_hw : ∀ p, s.pkgDelivered p = false → I.pkgWeight p > maxDynEffCap I s / 2 → min_hw ≤ I.pkgWeight p) :
    hPackTruck M s min_hw ≤ costDrive π + costBD π := by
  rw [← countActions_isTruckAct π]
  unfold hPackTruck
  refine packLB_plan_sound hv hp isTruckAct (potNS M)
    (fun p _ => by
      have hgp := hg p
      simp [potNS, State.pkgOnFerry, State.pkgPhysLoc, hgp, M.distNS_self])
    (fun {s1 s2 a} hv1 hstep => by
      cases hstep with
      | @drive t u v ht hne hroad =>
        refine ⟨fun h => by simp [isTruckAct] at h, fun _ => ⟨t, fun p _ => ?_⟩⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · simp only [hpl, ↓reduceIte]
          have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hph1 : s1.pkgPhysLoc p = u := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          have hph2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = v := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          simp only [potNS, hpf1, hpf2, hph1, hph2]
          have := M.distNS_road u v (I.pkgGoal p) hroad; omega
        · simp only [hpl, ↓reduceIte]
          have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne_t]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc v) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne_t]
          simp [potNS, hpf_eq, hph_eq]
      | @board t f ht hcap_f =>
        refine ⟨fun h => by simp [isTruckAct] at h, fun _ => ⟨t, fun p _ => ?_⟩⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · simp only [hpl, ↓reduceIte]
          have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = some f := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hph1 : s1.pkgPhysLoc p = s1.ferryLoc f := by simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, ht]
          simp only [potNS, hpf1, hpf2, hph1]
          have := M.board_step f (s1.ferryLoc f) (I.pkgGoal p) (by omega) (hv1.ferry_served f); omega
        · simp only [hpl, ↓reduceIte]
          have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne_t]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.onFerry f) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne_t]
          simp [potNS, hpf_eq, hph_eq]
      | @disembark t f ht =>
        refine ⟨fun h => by simp [isTruckAct] at h, fun _ => ⟨t, fun p _ => ?_⟩⟩
        by_cases hpl : s1.pkgLoc p = .inTruck t
        · simp only [hpl, ↓reduceIte]
          have hpf1 : s1.pkgOnFerry p = some f := by simp [State.pkgOnFerry, State.truckOnFerry, hpl, ht]
          have hpf2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, hpl, updateFn]
          have hph2 : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.ferryLoc f := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, hpl, updateFn]
          have hpos_f : 0 < I.ferryCap f := by
            have h := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f then 1 else 0) t
            have h1 : 1 ≤ s1.ferryCount f := by simpa [State.ferryCount, ht] using h
            have := hv1.aboard_le_cap f; omega
          simp only [potNS, hpf1, hpf2, hph2]
          have := M.disembark_step f (s1.ferryLoc f) (I.pkgGoal p) hpos_f (hv1.ferry_served f); omega
        · simp only [hpl, ↓reduceIte]
          have hpf_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgOnFerry, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgOnFerry, State.truckOnFerry, hpl', updateFn, hne_t]
          have hph_eq : ({ s1 with truckLoc := updateFn s1.truckLoc t (.atLoc (s1.ferryLoc f)) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl' : s1.pkgLoc p with
            | atLoc _ => simp [State.pkgPhysLoc, hpl']
            | inTruck t' =>
              have hne_t : t' ≠ t := by intro h; subst h; exact hpl hpl'
              simp [State.pkgPhysLoc, State.truckPhysLoc, hpl', updateFn, hne_t]
          simp [potNS, hpf_eq, hph_eq]
      | @load p' t l ht hp' hcap_l =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isTruckAct] at h⟩
        by_cases hpp : p = p'
        · subst hpp
          have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, hp']
          have hpf2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p (.inTruck t) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, State.truckOnFerry, updateFn, ht]
          have hph1 : s1.pkgPhysLoc p = l := by simp [State.pkgPhysLoc, hp']
          have hph2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p (.inTruck t) } : State I).pkgPhysLoc p = l := by
            simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, ht]
          simp [potNS, hpf1, hpf2, hph1, hph2]
        · have hpf : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl : s1.pkgLoc p <;> simp [State.pkgOnFerry, State.truckOnFerry, updateFn, hpp, hpl]
          have hph : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl : s1.pkgLoc p <;> simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp, hpl]
          simp [potNS, hpf, hph]
      | @unload p' t l ht hp' =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isTruckAct] at h⟩
        by_cases hpp : p = p'
        · subst hpp
          have hpf1 : s1.pkgOnFerry p = none := by simp [State.pkgOnFerry, State.truckOnFerry, hp', ht]
          have hpf2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p (.atLoc l) } : State I).pkgOnFerry p = none := by
            simp [State.pkgOnFerry, updateFn]
          have hph1 : s1.pkgPhysLoc p = l := by simp [State.pkgPhysLoc, State.truckPhysLoc, hp', ht]
          have hph2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p (.atLoc l) } : State I).pkgPhysLoc p = l := by
            simp [State.pkgPhysLoc, updateFn]
          simp [potNS, hpf1, hpf2, hph1, hph2]
        · have hpf : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l) } : State I).pkgOnFerry p = s1.pkgOnFerry p := by
            cases hpl : s1.pkgLoc p <;> simp [State.pkgOnFerry, State.truckOnFerry, updateFn, hpp, hpl]
          have hph : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l) } : State I).pkgPhysLoc p = s1.pkgPhysLoc p := by
            cases hpl : s1.pkgLoc p <;> simp [State.pkgPhysLoc, State.truckPhysLoc, updateFn, hpp, hpl]
          simp [potNS, hpf, hph]
      | @sail f u v hf hne hserved =>
        refine ⟨fun _ p _ => ?_, fun h => by simp [isTruckAct] at h⟩
        cases hpl : s1.pkgLoc p with
        | atLoc l =>
          simp [potNS, State.pkgOnFerry, State.pkgPhysLoc, hpl]
        | inTruck t =>
          cases htl : s1.truckLoc t with
          | atLoc l =>
            simp [potNS, State.pkgOnFerry, State.truckOnFerry, State.pkgPhysLoc, State.truckPhysLoc, hpl, htl]
          | onFerry f' =>
            simp [potNS, State.pkgOnFerry, State.truckOnFerry, hpl, htl])
    (maxDynEffCap I s) hcap (fun t => dynEffCap_le_maxDynEffCap I s t) min_hw (fun p h1 h2 _ => hmin_hw p h1 h2)

-- ==============================================================================
-- 3. Full Movement Metric, `costMove`, and `h_single ≤ costMove π` (`ex1.py:L318-L348, L1633-L1650`)
-- ==============================================================================

/-- Exact specification of `dist_full` (road = 1, active ferry = 5) and
    `ferry_full_dist` (`f_full[f][cp][g] = min(1 + dist_full[cp][g], min_{op≠cp} (4 + dist_full[op][g]))`),
    with unreachable entries encoded as 0 (`ex1.py:L318-L346`). -/
structure FullMetric (I : Instance) where
  distFull       : Fin I.numLocs → Fin I.numLocs → Nat
  ferryFull      : Fin I.numFerries → Fin I.numLocs → Fin I.numLocs → Nat
  distFull_self  : ∀ u, distFull u u = 0
  distFull_tri   : ∀ u v w, distFull u w ≤ distFull u v + distFull v w
  distFull_road  : ∀ u v g, I.road u v = true → distFull u g ≤ 1 + distFull v g
  board_step     : ∀ f p g, 0 < I.ferryCap f → I.ferryServed f p = true → distFull p g ≤ 1 + ferryFull f p g
  disembark_step : ∀ f p g, 0 < I.ferryCap f → I.ferryServed f p = true → ferryFull f p g ≤ 1 + distFull p g
  sail_step      : ∀ f u v g, 0 < I.ferryCap f → I.ferryServed f u = true → I.ferryServed f v = true →
                   ferryFull f u g ≤ 3 + ferryFull f v g

/-- Total movement cost (`A_move = A_drive ∪ A_bd ∪ A_sail`). -/
def costMove {I : Instance} (π : Plan I) : Nat :=
  costDrive π + costBD π + costSail π

/-- Single-step movement cost (`DRIVE = 1`, `BOARD = 1`, `DISEMBARK = 1`, `SAIL = 3`, `LOAD/UNLOAD = 0`). -/
def stepMoveCost {I : Instance} : Action I → Nat
  | .drive _ _ _   => 1
  | .board _ _     => 1
  | .disembark _ _ => 1
  | .sail _ _ _    => 3
  | .load _ _      => 0
  | .unload _ _    => 0

theorem costMove_cons {I : Instance} (a : Action I) (rest : Plan I) :
    costMove (a :: rest) = stepMoveCost a + costMove rest := by
  cases a <;> simp only [costMove, stepMoveCost, costDrive, costBD, costSail,
    actionCostDrive, actionCostBD, actionCostSail, List.map_cons, List.sum_cons] <;> omega

theorem costMove_append {I : Instance} (p1 p2 : Plan I) :
    costMove (p1 ++ p2) = costMove p1 + costMove p2 := by
  induction p1 with
  | nil => simp [costMove, costDrive, costBD, costSail]
  | cons a r ih => rw [List.cons_append, costMove_cons, costMove_cons, ih]; omega

/-- Truck full-cost potential to target location `g` (`ex1.py:L1422, L1425, L1641, L1648`). -/
def truckFullPot {I : Instance} (M : FullMetric I) (s : State I) (t : Fin I.numTrucks) (g : Fin I.numLocs) : Nat :=
  match s.truckLoc t with
  | .atLoc u   => M.distFull u g
  | .onFerry f => M.ferryFull f (s.ferryLoc f) g

/-- Package full-cost potential to target location `g`. -/
def pkgFullPot {I : Instance} (M : FullMetric I) (s : State I) (p : Fin I.numPkgs) (g : Fin I.numLocs) : Nat :=
  match s.pkgLoc p with
  | .atLoc u   => M.distFull u g
  | .inTruck t => truckFullPot M s t g

/-- Single-step drop of `truckFullPot` is bounded by `stepMoveCost`. -/
theorem truckFullPot_step {I : Instance} (M : FullMetric I)
    {s1 s2 : State I} {a : Action I} (hv1 : ValidState I s1) (hstep : Step I s1 a s2)
    (t : Fin I.numTrucks) (g : Fin I.numLocs) :
    truckFullPot M s1 t g ≤ stepMoveCost a + truckFullPot M s2 t g := by
  cases hstep with
  | @drive t' u v ht' _ hroad =>
    by_cases h : t = t'
    · subst h
      simp only [truckFullPot, ht', updateFn, ↓reduceIte, stepMoveCost]
      exact M.distFull_road u v g hroad
    · simp [truckFullPot, updateFn, h, stepMoveCost]
  | @board t' f ht' hcap_f =>
    by_cases h : t = t'
    · subst h
      simp only [truckFullPot, ht', updateFn, ↓reduceIte, stepMoveCost]
      exact M.board_step f (s1.ferryLoc f) g (by omega) (hv1.ferry_served f)
    · simp [truckFullPot, updateFn, h, stepMoveCost]
  | @disembark t' f ht' =>
    by_cases h : t = t'
    · subst h
      have hpos_f : 0 < I.ferryCap f := by
        have h1 := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f then 1 else 0) t
        have h2 : 1 ≤ s1.ferryCount f := by simpa [State.ferryCount, ht'] using h1
        have := hv1.aboard_le_cap f; omega
      simp only [truckFullPot, ht', updateFn, ↓reduceIte, stepMoveCost]
      exact M.disembark_step f (s1.ferryLoc f) g hpos_f (hv1.ferry_served f)
    · simp [truckFullPot, updateFn, h, stepMoveCost]
  | @sail f u v hf _ hserved =>
    cases htl : s1.truckLoc t with
    | atLoc l => simp [truckFullPot, htl, stepMoveCost]
    | onFerry f' =>
      by_cases hff : f' = f
      · subst hff
        have hpos_f : 0 < I.ferryCap f' := by
          have h1 := le_finSum (fun t'' => if s1.truckLoc t'' = .onFerry f' then 1 else 0) t
          have h2 : 1 ≤ s1.ferryCount f' := by simpa [State.ferryCount, htl] using h1
          have := hv1.aboard_le_cap f'; omega
        simp only [truckFullPot, htl, hf, updateFn, ↓reduceIte, stepMoveCost]
        exact M.sail_step f' u v g hpos_f (hf ▸ hv1.ferry_served f') hserved
      · simp [truckFullPot, htl, updateFn, hff, stepMoveCost]
  | load _ _ _ => simp [truckFullPot, stepMoveCost]
  | unload _ _ => simp [truckFullPot, stepMoveCost]

/-- Multi-step drop of `truckFullPot` is bounded by `costMove`. -/
theorem truckFullPot_drop_le_costMove {I : Instance} (M : FullMetric I)
    {sa sb : State I} {ps : Plan I}
    (hva : ValidState I sa) (hpa : ValidPlan I sa ps sb)
    (t : Fin I.numTrucks) (g : Fin I.numLocs) :
    truckFullPot M sa t g ≤ costMove ps + truckFullPot M sb t g := by
  induction hpa with
  | nil => simp [costMove, costDrive, costBD, costSail]
  | @cons s1 s2 _ a rest hstep _ ih =>
    have h1 := truckFullPot_step M hva hstep t g
    have h2 := ih (validState_step hva hstep)
    rw [costMove_cons]
    omega

/-- Single-step drop of `pkgFullPot` is bounded by `stepMoveCost` (and is 0 unless `p` is in a moving truck). -/
theorem pkgFullPot_step {I : Instance} (M : FullMetric I)
    {s1 s2 : State I} {a : Action I} (hv1 : ValidState I s1) (hstep : Step I s1 a s2)
    (p : Fin I.numPkgs) (g : Fin I.numLocs) :
    pkgFullPot M s1 p g ≤ stepMoveCost a + pkgFullPot M s2 p g := by
  cases hstep with
  | @load p' t l ht hp' hcap =>
    by_cases hpp : p = p'
    · subst hpp; simp [pkgFullPot, truckFullPot, hp', ht, updateFn, stepMoveCost]
    · cases hpl : s1.pkgLoc p <;> simp [pkgFullPot, truckFullPot, updateFn, hpp, hpl, stepMoveCost]
  | @unload p' t l ht hp' =>
    by_cases hpp : p = p'
    · subst hpp; simp [pkgFullPot, truckFullPot, hp', ht, updateFn, stepMoveCost]
    · cases hpl : s1.pkgLoc p <;> simp [pkgFullPot, truckFullPot, updateFn, hpp, hpl, stepMoveCost]
  | @drive t u v ht hne hroad =>
    cases hpl : s1.pkgLoc p with
    | atLoc l => simp [pkgFullPot, hpl, stepMoveCost]
    | inTruck t' =>
      simpa [pkgFullPot, hpl] using truckFullPot_step M hv1 (Step.drive ht hne hroad) t' g
  | @board t f ht hcap_f =>
    cases hpl : s1.pkgLoc p with
    | atLoc l => simp [pkgFullPot, hpl, stepMoveCost]
    | inTruck t' =>
      simpa [pkgFullPot, hpl] using truckFullPot_step M hv1 (Step.board ht hcap_f) t' g
  | @disembark t f ht =>
    cases hpl : s1.pkgLoc p with
    | atLoc l => simp [pkgFullPot, hpl, stepMoveCost]
    | inTruck t' =>
      simpa [pkgFullPot, hpl] using truckFullPot_step M hv1 (Step.disembark ht) t' g
  | @sail f u v hf hne hserved =>
    cases hpl : s1.pkgLoc p with
    | atLoc l => simp [pkgFullPot, hpl, stepMoveCost]
    | inTruck t' =>
      simpa [pkgFullPot, hpl] using truckFullPot_step M hv1 (Step.sail hf hne hserved) t' g

/-- Multi-step drop of `pkgFullPot` is bounded by `costMove`. -/
theorem pkgFullPot_drop_le_costMove {I : Instance} (M : FullMetric I)
    {sa sb : State I} {ps : Plan I}
    (hva : ValidState I sa) (hpa : ValidPlan I sa ps sb)
    (p : Fin I.numPkgs) (g : Fin I.numLocs) :
    pkgFullPot M sa p g ≤ costMove ps + pkgFullPot M sb p g := by
  induction hpa with
  | nil => simp [costMove, costDrive, costBD, costSail]
  | @cons s1 s2 _ a rest hstep _ ih =>
    have h1 := pkgFullPot_step M hva hstep p g
    have h2 := ih (validState_step hva hstep)
    rw [costMove_cons]
    omega

/-- Split a valid plan at the first `LOAD(p, t)` for a ground undelivered package `p`. -/
theorem split_first_load {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (l : Fin I.numLocs)
    (hpl : s.pkgLoc p = .atLoc l) (hnd : s.pkgDelivered p = false) :
    ∃ (t : Fin I.numTrucks) (s_mid : State I) (p1 p2 : Plan I),
      π = p1 ++ p2 ∧ I.pkgWeight p ≤ I.truckCap t ∧
      ValidPlan I s p1 s_mid ∧ ValidState I s_mid ∧ ValidPlan I s_mid p2 s_goal ∧
      s_mid.truckLoc t = .atLoc l ∧ s_mid.pkgLoc p = .atLoc l := by
  induction hp with
  | nil =>
    have hgp := hg p; rw [hpl] at hgp; injection hgp with hl
    simp [State.pkgDelivered, hpl, hl] at hnd
  | @cons s1 s2 _ a rest hstep hrest ih =>
    cases hstep with
    | @load p' t' l' ht' hp' hcap' =>
      by_cases hpp : p' = p
      · subst hpp
        rw [hpl] at hp'; injection hp' with hll; subst hll
        exact ⟨t', s1, [], .load p' t' :: rest, rfl, by omega, ValidPlan.nil, hv,
          ValidPlan.cons (Step.load ht' hpl hcap') hrest, ht', hpl⟩
      · have hpl_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgLoc p = .atLoc l := by
          simp [updateFn, Ne.symm hpp, hpl]
        have hnd_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgDelivered p = false := by
          simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd
        rcases ih (validState_step hv (Step.load ht' hp' hcap')) hg hpl_b hnd_b with
          ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
        exact ⟨t, sm, .load p' t' :: p1, p2, by simp [heq], hcap_t,
          ValidPlan.cons (Step.load ht' hp' hcap') hp1, hvm, hp2, htl_m, hpl_m⟩
    | @unload p' t' l' ht' hp' =>
      have hpp : p' ≠ p := by intro h; subst h; rw [hpl] at hp'; cases hp'
      have hpl_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgLoc p = .atLoc l := by
        simp [updateFn, Ne.symm hpp, hpl]
      have hnd_b : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered, updateFn, Ne.symm hpp] using hnd
      rcases ih (validState_step hv (Step.unload ht' hp')) hg hpl_b hnd_b with
        ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
      exact ⟨t, sm, .unload p' t' :: p1, p2, by simp [heq], hcap_t,
        ValidPlan.cons (Step.unload ht' hp') hp1, hvm, hp2, htl_m, hpl_m⟩
    | @drive t' u v ht' hne hroad =>
      rcases ih (validState_step hv (Step.drive ht' hne hroad)) hg hpl hnd with
        ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
      exact ⟨t, sm, .drive t' u v :: p1, p2, by simp [heq], hcap_t,
        ValidPlan.cons (Step.drive ht' hne hroad) hp1, hvm, hp2, htl_m, hpl_m⟩
    | @board t' f ht' hcf =>
      rcases ih (validState_step hv (Step.board ht' hcf)) hg hpl hnd with
        ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
      exact ⟨t, sm, .board t' f :: p1, p2, by simp [heq], hcap_t,
        ValidPlan.cons (Step.board ht' hcf) hp1, hvm, hp2, htl_m, hpl_m⟩
    | @disembark t' f ht' =>
      rcases ih (validState_step hv (Step.disembark ht')) hg hpl hnd with
        ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
      exact ⟨t, sm, .disembark t' f :: p1, p2, by simp [heq], hcap_t,
        ValidPlan.cons (Step.disembark ht') hp1, hvm, hp2, htl_m, hpl_m⟩
    | @sail f u v hf hne hsv =>
      rcases ih (validState_step hv (Step.sail hf hne hsv)) hg hpl hnd with
        ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
      exact ⟨t, sm, .sail f u v :: p1, p2, by simp [heq], hcap_t,
        ValidPlan.cons (Step.sail hf hne hsv) hp1, hvm, hp2, htl_m, hpl_m⟩

/-- Admissibility of `h_single` (`ex1.py:L1633-L1650`):
    - Loaded package `p` on truck `t`: `truckFullPot M s t (I.pkgGoal p) ≤ costMove π`.
    - Ground undelivered package `p` at `l`: `min_{t capable} truckFullPot M s t l + distFull l (I.pkgGoal p) ≤ costMove π`. -/
theorem hSingle_le_costMove {I : Instance} (M : FullMetric I)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (p : Fin I.numPkgs) (hnd : s.pkgDelivered p = false) :
    (∀ t, s.pkgLoc p = .inTruck t → truckFullPot M s t (I.pkgGoal p) ≤ costMove π) ∧
    (∀ l, s.pkgLoc p = .atLoc l →
      ∀ mp : Nat, (∀ t, I.pkgWeight p ≤ I.truckCap t → mp ≤ truckFullPot M s t l) →
      mp + M.distFull l (I.pkgGoal p) ≤ costMove π) := by
  constructor
  · intro t hpl
    have h := pkgFullPot_drop_le_costMove M hv hp p (I.pkgGoal p)
    have h1 : pkgFullPot M s p (I.pkgGoal p) = truckFullPot M s t (I.pkgGoal p) := by
      simp [pkgFullPot, hpl]
    have h2 : pkgFullPot M s_goal p (I.pkgGoal p) = 0 := by
      simp [pkgFullPot, hg p, M.distFull_self]
    omega
  · intro l hpl mp hmp
    rcases split_first_load hv hp hg p l hpl hnd with
      ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
    have h1 := hmp t hcap_t
    have h2 := truckFullPot_drop_le_costMove M hv hp1 t l
    have hm1 : truckFullPot M sm t l = 0 := by simp [truckFullPot, htl_m, M.distFull_self]
    have h3 := pkgFullPot_drop_le_costMove M hvm hp2 p (I.pkgGoal p)
    have hm2 : pkgFullPot M sm p (I.pkgGoal p) = M.distFull l (I.pkgGoal p) := by
      simp [pkgFullPot, hpl_m]
    have hg2 : pkgFullPot M s_goal p (I.pkgGoal p) = 0 := by
      simp [pkgFullPot, hg p, M.distFull_self]
    rw [heq, costMove_append]
    omega

-- ==============================================================================
-- 4. Exclusive-Truck Heavy Sum + Approach (`ex1.py:L1418-L1449`)
-- ==============================================================================

/-- Predicate asserting that `ti` is the SOLE truck capable of carrying package `p`
    (`ex1.py:L368-L374`). -/
def isExclusive (I : Instance) (ti : Fin I.numTrucks) (p : Fin I.numPkgs) : Prop :=
  ∀ t', t' ≠ ti → I.truckCap t' < I.pkgWeight p

/-- In any valid state, an exclusive package of `ti` can never be in any other truck `t' ≠ ti`. -/
theorem exclusive_only_in_ti {I : Instance} {s : State I} (hv : ValidState I s)
    {ti : Fin I.numTrucks} {p : Fin I.numPkgs} (hexcl : isExclusive I ti p)
    {t' : Fin I.numTrucks} (hpl : s.pkgLoc p = .inTruck t') :
    t' = ti := by
  by_cases h : t' = ti
  · exact h
  · exfalso
    have hlt := hexcl t' h
    have hle : I.pkgWeight p ≤ s.truckLoad t' := by
      have h1 := le_finSum (fun p' => if s.pkgLoc p' = .inTruck t' then I.pkgWeight p' else 0) p
      unfold State.truckLoad; simp only [hpl, ↓reduceIte] at h1; exact h1
    have hcap := hv.load_le_cap t'
    omega

/-- Heavy exclusive sum bound (without approach):
    if `heavyExcl p = true` implies `p` is exclusive to `ti`, undelivered at `s0`,
    and `I.pkgWeight p > dynEffCap I s0 ti / 2`, then
    `∑_{p heavyExcl} pkgFullPot M s p (I.pkgGoal p) ≤ costMove π`!
    Notice this holds EVEN IF `ti` temporarily unloads and reloads packages! -/
theorem excl_heavy_sum_le_costMove {I : Instance} (M : FullMetric I)
    (ti : Fin I.numTrucks) (s0 : State I)
    (heavyExcl : Fin I.numPkgs → Bool)
    (hspec : ∀ p, heavyExcl p = true →
      isExclusive I ti p ∧ s0.pkgDelivered p = false ∧ I.pkgWeight p > dynEffCap I s0 ti / 2)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal) :
    finSum (fun p => if heavyExcl p then pkgFullPot M s p (I.pkgGoal p) else 0) ≤ costMove π := by
  induction hp with
  | @nil s_end =>
    have hz : (fun p => if heavyExcl p then pkgFullPot M s_end p (I.pkgGoal p) else 0) = fun _ => 0 := by
      funext p; cases heavyExcl p <;> simp [pkgFullPot, hg p, M.distFull_self]
    rw [hz, finSum_zero]; exact Nat.zero_le _
  | @cons s1 s2 _ a rest hstep _ ih =>
    have hv2 := validState_step hv hstep
    have hrec := ih hv2 hg
    -- At most ONE `heavyExcl` package is in `ti` at `s1`!
    let mask : Fin I.numPkgs → Bool := fun p => heavyExcl p && decide (s1.pkgLoc p = .inTruck ti)
    have hmask_w : subsetWeight I.pkgWeight mask ≤ dynEffCap I s0 ti := by
      apply subsetWeight_undeliv_le_dynEffCap I s0 ti mask
      · intro p hm
        simp only [mask, Bool.and_eq_true] at hm
        exact (hspec p hm.1).2.1
      · have hle : subsetWeight I.pkgWeight mask ≤ s1.truckLoad ti := by
          unfold subsetWeight State.truckLoad
          apply finSum_le_finSum; intro p
          by_cases h1 : heavyExcl p = true <;> by_cases h2 : s1.pkgLoc p = .inTruck ti <;>
            simp [mask, h1, h2]
        exact Nat.le_trans hle (hv.load_le_cap ti)
    have hat_most_one : finSum (fun p => if mask p then 1 else 0) ≤ 1 := by
      have h1 := at_most_one_heavy I.pkgWeight mask (dynEffCap I s0 ti) hmask_w
      have heq : (fun p => if mask p then 1 else 0) =
                 (fun p => if mask p && decide (I.pkgWeight p > dynEffCap I s0 ti / 2) then 1 else 0) := by
        funext p
        by_cases hm : mask p = true
        · simp only [mask, Bool.and_eq_true] at hm
          have hgt := (hspec p hm.1).2.2
          simp [mask, hm.1, hm.2, hgt]
        · have hf : mask p = false := Bool.eq_false_iff.mpr hm
          simp [hf]
      rw [heq]; exact h1
    -- Any `heavyExcl` package NOT in `ti` at `s1` has unchanged `pkgFullPot` on step `a`!
    have hnot_in_ti : ∀ p, heavyExcl p = true → s1.pkgLoc p ≠ .inTruck ti →
        pkgFullPot M s1 p (I.pkgGoal p) ≤ pkgFullPot M s2 p (I.pkgGoal p) := by
      intro p hhe hne_ti
      have hnot_any : ∀ t', s1.pkgLoc p ≠ .inTruck t' := by
        intro t' hpl
        exact hne_ti ((exclusive_only_in_ti hv (hspec p hhe).1 hpl) ▸ hpl)
      cases hpl : s1.pkgLoc p with
      | inTruck t' => exact absurd hpl (hnot_any t')
      | atLoc l =>
        cases hstep with
        | @load p' t l' ht' hp' _ =>
          by_cases hpp : p = p'
          · subst hpp; rw [hpl] at hp'; injection hp' with hll; subst hll
            simp [pkgFullPot, truckFullPot, hpl, updateFn, ht']
          · simp [pkgFullPot, hpl, updateFn, hpp]
        | @unload p' t l' ht' hp' =>
          have hpp : p ≠ p' := by intro h; subst h; rw [hpl] at hp'; cases hp'
          simp [pkgFullPot, hpl, updateFn, hpp]
        | drive _ _ _ => simp [pkgFullPot, hpl]
        | board _ _ => simp [pkgFullPot, hpl]
        | disembark _ => simp [pkgFullPot, hpl]
        | sail _ _ _ => simp [pkgFullPot, hpl]
    -- Therefore total potential drop across ALL `heavyExcl` packages ≤ `stepMoveCost a`!
    have hstep_sum :
        finSum (fun p => if heavyExcl p then pkgFullPot M s1 p (I.pkgGoal p) else 0) ≤
        stepMoveCost a + finSum (fun p => if heavyExcl p then pkgFullPot M s2 p (I.pkgGoal p) else 0) := by
      have hpt : ∀ p, (if heavyExcl p then pkgFullPot M s1 p (I.pkgGoal p) else 0) ≤
          (if mask p then stepMoveCost a else 0) + (if heavyExcl p then pkgFullPot M s2 p (I.pkgGoal p) else 0) := by
        intro p
        by_cases hhe : heavyExcl p = true
        · simp only [hhe, ↓reduceIte]
          by_cases hin : s1.pkgLoc p = .inTruck ti
          · have hm : mask p = true := by simp [mask, hhe, hin]
            simp only [hm, ↓reduceIte]
            exact pkgFullPot_step M hv hstep p (I.pkgGoal p)
          · have hm : mask p = false := by simp [mask, hhe, hin]
            simp only [hm, Bool.false_eq_true, ↓reduceIte, Nat.zero_add]
            exact hnot_in_ti p hhe hin
        · simp [hhe]
      have hsum_le := finSum_le_finSum hpt
      rw [finSum_add] at hsum_le
      have hmask_cost : finSum (fun p => if mask p then stepMoveCost a else 0) ≤ stepMoveCost a := by
        have hmul : finSum (fun p => if mask p then stepMoveCost a else 0) =
            stepMoveCost a * finSum (fun p => if mask p then 1 else 0) := by
          have h1 : (fun p => if mask p then stepMoveCost a else 0) =
                    (fun p => stepMoveCost a * (if mask p then 1 else 0)) := by
            funext p; cases mask p <;> simp
          rw [h1, finSum_mul_left]
        rw [hmul]
        have := Nat.mul_le_mul_left (stepMoveCost a) hat_most_one
        omega
      omega
    rw [costMove_cons]
    omega

/-- Full heavy exclusive bound INCLUDING `h_app` when `¬hold_h` (`ex1.py:L1433-L1449`):
    - If `ti` already holds a heavy exclusive package (`hold_h = true`), `h_sum ≤ costMove π`.
    - If `ti` holds NO heavy exclusive package (`hold_h = false`) and at least one exists,
      `h_app + h_sum ≤ costMove π` where `h_app ≤ min_{p heavy excl} truckFullPot M s ti pl_p`. -/
theorem excl_heavy_with_app_le_costMove {I : Instance} (M : FullMetric I)
    (ti : Fin I.numTrucks) {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (heavyExcl : Fin I.numPkgs → Bool)
    (hspec : ∀ p, heavyExcl p = true →
      isExclusive I ti p ∧ s.pkgDelivered p = false ∧ I.pkgWeight p > dynEffCap I s ti / 2)
    (h_app : Nat)
    (hno_hold : ∀ p, heavyExcl p = true → ∀ t, s.pkgLoc p ≠ .inTruck t)
    (hexists : ∃ p, heavyExcl p = true)
    (happ_le : ∀ p l, heavyExcl p = true → s.pkgLoc p = .atLoc l → h_app ≤ truckFullPot M s ti l) :
    h_app + finSum (fun p => if heavyExcl p then pkgFullPot M s p (I.pkgGoal p) else 0) ≤ costMove π := by
  -- Split `π = p1 ++ p2` at the FIRST `LOAD(p*, ti)` for ANY `p*` with `heavyExcl p* = true`!
  have hsplit : ∀ {sa s_end : State I} {ps : Plan I}
      (hva : ValidState I sa) (hpa : ValidPlan I sa ps s_end) (hga : goalTest I s_end),
      (∀ p, heavyExcl p = true → sa.pkgLoc p = s.pkgLoc p) →
      ∃ (p_star : Fin I.numPkgs) (l_star : Fin I.numLocs) (s_mid : State I) (p1 p2 : Plan I),
        ps = p1 ++ p2 ∧ heavyExcl p_star = true ∧ s.pkgLoc p_star = .atLoc l_star ∧
        ValidPlan I sa p1 s_mid ∧ ValidState I s_mid ∧ ValidPlan I s_mid p2 s_end ∧
        s_mid.truckLoc ti = .atLoc l_star ∧
        (∀ p, heavyExcl p = true → s_mid.pkgLoc p = s.pkgLoc p) := by
    intro sa s_end ps hva hpa hga hsame
    induction hpa with
    | nil =>
      rcases hexists with ⟨p0, hp0⟩
      have hloc := hsame p0 hp0
      have hgp := hga p0
      have hnd := (hspec p0 hp0).2.1
      rw [hloc] at hgp
      simp [State.pkgDelivered, hgp] at hnd
    | @cons s1 s2 _ a rest hstep hrest ih =>
      cases hstep with
      | @load p' t' l' ht' hp' hcap' =>
        by_cases hhe : heavyExcl p' = true
        · have ht_eq : t' = ti := by
            by_cases h : t' = ti
            · exact h
            · exfalso; have hlt := (hspec p' hhe).1 t' h; omega
          subst ht_eq
          have hloc_s : s.pkgLoc p' = .atLoc l' := by rw [← hsame p' hhe, hp']
          exact ⟨p', l', s1, [], .load p' t' :: rest, rfl, hhe, hloc_s,
            ValidPlan.nil, hva, ValidPlan.cons (Step.load ht' hp' hcap') hrest, ht', hsame⟩
        · have hsame2 : ∀ p, heavyExcl p = true →
              ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgLoc p = s.pkgLoc p := by
            intro p hp_he
            have hne : p ≠ p' := by intro h; subst h; exact hhe hp_he
            simp [updateFn, hne, hsame p hp_he]
          rcases ih (validState_step hva (Step.load ht' hp' hcap')) hga hsame2 with
            ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
          exact ⟨ps', ls', sm, .load p' t' :: p1, p2, by simp [heq], hhe', hls',
            ValidPlan.cons (Step.load ht' hp' hcap') hp1, hvm, hp2, htm, hsm⟩
      | @unload p' t' l' ht' hp' =>
        have hhe_f : heavyExcl p' = false := by
          cases h : heavyExcl p'
          · rfl
          · exfalso
            have hloc := hsame p' h
            rw [hp'] at hloc
            exact hno_hold p' h t' hloc.symm
        have hsame2 : ∀ p, heavyExcl p = true →
            ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgLoc p = s.pkgLoc p := by
          intro p hp_he
          have hne : p ≠ p' := by intro h; subst h; simp [hp_he] at hhe_f
          simp [updateFn, hne, hsame p hp_he]
        rcases ih (validState_step hva (Step.unload ht' hp')) hga hsame2 with
          ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
        exact ⟨ps', ls', sm, .unload p' t' :: p1, p2, by simp [heq], hhe', hls',
          ValidPlan.cons (Step.unload ht' hp') hp1, hvm, hp2, htm, hsm⟩
      | @drive t' u v ht' hne hroad =>
        rcases ih (validState_step hva (Step.drive ht' hne hroad)) hga hsame with
          ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
        exact ⟨ps', ls', sm, .drive t' u v :: p1, p2, by simp [heq], hhe', hls',
          ValidPlan.cons (Step.drive ht' hne hroad) hp1, hvm, hp2, htm, hsm⟩
      | @board t' f ht' hcf =>
        rcases ih (validState_step hva (Step.board ht' hcf)) hga hsame with
          ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
        exact ⟨ps', ls', sm, .board t' f :: p1, p2, by simp [heq], hhe', hls',
          ValidPlan.cons (Step.board ht' hcf) hp1, hvm, hp2, htm, hsm⟩
      | @disembark t' f ht' =>
        rcases ih (validState_step hva (Step.disembark ht')) hga hsame with
          ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
        exact ⟨ps', ls', sm, .disembark t' f :: p1, p2, by simp [heq], hhe', hls',
          ValidPlan.cons (Step.disembark ht') hp1, hvm, hp2, htm, hsm⟩
      | @sail f u v hf hne hsv =>
        rcases ih (validState_step hva (Step.sail hf hne hsv)) hga hsame with
          ⟨ps', ls', sm, p1, p2, heq, hhe', hls', hp1, hvm, hp2, htm, hsm⟩
        exact ⟨ps', ls', sm, .sail f u v :: p1, p2, by simp [heq], hhe', hls',
          ValidPlan.cons (Step.sail hf hne hsv) hp1, hvm, hp2, htm, hsm⟩
  rcases hsplit hv hp hg (fun _ _ => rfl) with
    ⟨p_star, l_star, sm, p1, p2, heq, hhe_star, hloc_star, hp1, hvm, hp2, htm, hsm⟩
  -- Bound prefix `p1` by `h_app`:
  have h1 := happ_le p_star l_star hhe_star hloc_star
  have h2 := truckFullPot_drop_le_costMove M hv hp1 ti l_star
  have hm_zero : truckFullPot M sm ti l_star = 0 := by simp [truckFullPot, htm, M.distFull_self]
  -- Bound suffix `p2` by `excl_heavy_sum_le_costMove`:
  have h3 := excl_heavy_sum_le_costMove M ti s heavyExcl hspec hvm hp2 hg
  have hsum_eq :
      finSum (fun p => if heavyExcl p then pkgFullPot M sm p (I.pkgGoal p) else 0) =
      finSum (fun p => if heavyExcl p then pkgFullPot M s p (I.pkgGoal p) else 0) := by
    congr 1; funext p
    by_cases hhe : heavyExcl p = true
    · simp only [hhe, ↓reduceIte]
      have hloc := hsm p hhe
      cases hpl : s.pkgLoc p with
      | atLoc l => simp [pkgFullPot, hloc, hpl]
      | inTruck t => exact absurd hpl (hno_hold p hhe t)
    · simp [hhe]
  rw [heq, costMove_append]
  omega

-- ==============================================================================
-- 5. Exact Layered Forward DP `_excl_tsp_lb` (`ex1.py:L827-L885, L1450-L1453`)
-- ==============================================================================

/-- Plan slicing lemma: `ValidPlan` splits at any `k ≤ π.length` into `π.take k` and `π.drop k`. -/
theorem validPlan_take_drop {I : Instance} {s s_end : State I} {π : Plan I}
    (hp : ValidPlan I s π s_end) (k : Nat) :
    ValidPlan I s (π.take k) (stateAt s π k) ∧ ValidPlan I (stateAt s π k) (π.drop k) s_end := by
  induction hp generalizing k with
  | nil =>
    simp only [List.take_nil, List.drop_nil, stateAt]
    exact ⟨ValidPlan.nil, ValidPlan.nil⟩
  | @cons s1 s2 s_last a rest hstep hrest ih =>
    cases k with
    | zero =>
      simp only [List.take_zero, List.drop_zero, stateAt]
      exact ⟨ValidPlan.nil, ValidPlan.cons hstep hrest⟩
    | succ k' =>
      have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
      have ⟨h1, h2⟩ := ih k'
      have hst : stateAt s1 (a :: rest) (k' + 1) = stateAt s2 rest k' := by
        simp only [stateAt, List.take_succ_cons, List.foldl_cons, ← hs2_eq]
      rw [hst]
      simp only [List.take_succ_cons, List.drop_succ_cons]
      exact ⟨ValidPlan.cons hstep h1, h2⟩

theorem stateAt_drop {I : Instance} (s : State I) (π : Plan I) (k j : Nat) :
    stateAt (stateAt s π k) (π.drop k) j = stateAt s π (k + j) := by
  induction π generalizing s k with
  | nil => simp [stateAt]
  | cons a rest ih =>
    cases k with
    | zero => simp [stateAt]
    | succ k' =>
      simp only [List.drop_succ_cons, stateAt, Nat.succ_add]
      exact ih (applyAction s a) k'

theorem validState_stateAt {I : Instance} {s s_end : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_end) (k : Nat) :
    ValidState I (stateAt s π k) := by
  have ⟨h1, _⟩ := validPlan_take_drop hp k
  exact validState_plan hv h1

/-- Every undelivered exclusive package of `ti` has a step `d < π.length` where `ti` is at its goal. -/
theorem excl_exists_deliver_step {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (ti : Fin I.numTrucks) (p : Fin I.numPkgs)
    (hexcl : isExclusive I ti p) (hnd : s.pkgDelivered p = false) :
    ∃ d < π.length, (stateAt s π d).truckLoc ti = .atLoc (I.pkgGoal p) := by
  induction hp with
  | nil =>
    have hgp := hg p; simp [State.pkgDelivered, hgp] at hnd
  | @cons s1 s2 _ a rest hstep _ ih =>
    have hv2 := validState_step hv hstep
    have hs2_eq : s2 = applyAction s1 a := step_eq_applyAction hstep
    have hstep_at : ∀ d, stateAt s1 (a :: rest) (d + 1) = stateAt s2 rest d := by
      intro d; simp only [stateAt, List.take_succ_cons, List.foldl_cons, ← hs2_eq]
    cases hstep with
    | @unload p' t' l' ht' hp' =>
      by_cases hcond : p' = p ∧ l' = I.pkgGoal p
      · rcases hcond with ⟨rfl, rfl⟩
        have ht_eq : t' = ti := exclusive_only_in_ti hv hexcl hp'
        subst ht_eq
        exact ⟨0, Nat.zero_lt_succ _, by simpa [stateAt] using ht'⟩
      · have hnd2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.atLoc l') } : State I).pkgDelivered p = false := by
          simp only [State.pkgDelivered, updateFn]
          by_cases hpp : p = p'
          · subst hpp
            have hne_l : l' ≠ I.pkgGoal p := fun h => hcond ⟨rfl, h⟩
            simp [hne_l]
          · simpa [State.pkgDelivered, hpp] using hnd
        rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
        exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩
    | @load p' t' l' ht' hp' hcap' =>
      have hnd2 : ({ s1 with pkgLoc := updateFn s1.pkgLoc p' (.inTruck t') } : State I).pkgDelivered p = false := by
        simp only [State.pkgDelivered, updateFn]
        by_cases hpp : p = p'
        · subst hpp; simp
        · simpa [State.pkgDelivered, hpp] using hnd
      rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
      exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩
    | @drive t' u v ht' hne hroad =>
      have hnd2 : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc v) } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered] using hnd
      rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
      exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩
    | @board t' f ht' hcf =>
      have hnd2 : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.onFerry f) } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered] using hnd
      rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
      exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩
    | @disembark t' f ht' =>
      have hnd2 : ({ s1 with truckLoc := updateFn s1.truckLoc t' (.atLoc (s1.ferryLoc f)) } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered] using hnd
      rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
      exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩
    | @sail f u v hf hne hsv =>
      have hnd2 : ({ s1 with ferryLoc := updateFn s1.ferryLoc f v } : State I).pkgDelivered p = false := by
        simpa [State.pkgDelivered] using hnd
      rcases ih hv2 hg hnd2 with ⟨d, hd, hloc⟩
      exact ⟨d + 1, Nat.succ_lt_succ hd, by rw [hstep_at]; exact hloc⟩

/-- Every ground undelivered exclusive package of `ti` has `t_pick < t_drop < π.length`
    where `ti` is at `l` at `t_pick` and at `I.pkgGoal p` at `t_drop`. -/
theorem excl_exists_pickup_before_deliver {I : Instance} {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (ti : Fin I.numTrucks) (p : Fin I.numPkgs) (l : Fin I.numLocs)
    (hexcl : isExclusive I ti p) (hpl : s.pkgLoc p = .atLoc l) (hnd : s.pkgDelivered p = false) :
    ∃ t_pick t_drop, t_pick < t_drop ∧ t_drop < π.length ∧
      (stateAt s π t_pick).truckLoc ti = .atLoc l ∧
      (stateAt s π t_drop).truckLoc ti = .atLoc (I.pkgGoal p) := by
  rcases split_first_load hv hp hg p l hpl hnd with
    ⟨t, sm, p1, p2, heq, hcap_t, hp1, hvm, hp2, htl_m, hpl_m⟩
  have ht_eq : t = ti := by
    by_cases h : t = ti
    · exact h
    · exfalso; have hlt := hexcl t h; omega
  subst t
  have hnd_m : sm.pkgDelivered p = false := by
    have hne : l ≠ I.pkgGoal p := by
      intro h; subst h; simp [State.pkgDelivered, hpl] at hnd
    simp [State.pkgDelivered, hpl_m, hne]
  rcases excl_exists_deliver_step hvm hp2 hg ti p hexcl hnd_m with ⟨d, hd, hloc_d⟩
  have hd_pos : 0 < d := by
    by_cases h0 : d = 0
    · subst h0
      simp only [stateAt, List.take_zero, List.foldl_nil] at hloc_d
      rw [htl_m] at hloc_d; injection hloc_d with hlg
      simp [State.pkgDelivered, hpl, hlg] at hnd
    · omega
  have hstate_app : ∀ {sa sb : State I} (qa qb : Plan I), ValidPlan I sa qa sb →
      ∀ j, stateAt sa (qa ++ qb) (qa.length + j) = stateAt sb qb j := by
    intro sa sb qa qb hqa j
    induction hqa with
    | nil => simp [stateAt]
    | @cons s1 s2 _ a r hst _ ih =>
      have hs2_eq := step_eq_applyAction hst
      simp only [List.cons_append, List.length_cons]
      rw [Nat.add_right_comm]
      simp only [stateAt, List.take_succ_cons, List.foldl_cons, ← hs2_eq]
      exact ih
  refine ⟨p1.length, p1.length + d, by omega, ?_, ?_, ?_⟩
  · rw [heq, List.length_append]; omega
  · rw [heq]
    have h0 := hstate_app p1 p2 hp1 0
    simp only [Nat.add_zero] at h0
    rw [h0]; simp only [stateAt, List.take_zero, List.foldl_nil]; exact htl_m
  · rw [heq, hstate_app p1 p2 hp1 d]; exact hloc_d

/-- Event type for exclusive pickup-and-delivery DP. -/
inductive ExclEv (k : Nat) where
  | pickup  (i : Fin k)
  | deliver (i : Fin k)
  deriving DecidableEq

/-- Initial pickup bitmask (`ex1.py:L842-L845`): `true` if pair `i` starts loaded (`none`). -/
def exclInitPM {I : Instance} {k : Nat} (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) : Fin k → Bool :=
  fun i => (pairs i).1.isNone

/-- Total remaining events (`ex1.py:L841-L847`): 1 per loaded pair, 2 per ground pair. -/
def exclRemEv {I : Instance} {k : Nat} (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) : Nat :=
  finSum (fun i => if (pairs i).1.isNone then 1 else 2)

/-- Target location of event `(i, picked)` (`ex1.py:L853, L869`). -/
def exclLoc {I : Instance} {k : Nat} (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    (i : Fin k) (picked : Bool) : Fin I.numLocs :=
  if picked then (pairs i).2 else (pairs i).1.getD (pairs i).2

/-- Target location of an `ExclEv`. -/
def exclEvLoc {I : Instance} {k : Nat} (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) :
    ExclEv k → Fin I.numLocs
  | .pickup i  => exclLoc pairs i false
  | .deliver i => exclLoc pairs i true

/-- Set bit `i` in a `Fin k → Bool` mask. -/
def setBit {k : Nat} (m : Fin k → Bool) (i : Fin k) : Fin k → Bool :=
  fun j => if j = i then true else m j

/-- Forward layered DP entry matching `(pm, dm, cur) -> cost` in `ex1.py:L849-L876`. -/
structure ExclDPState (I : Instance) (k : Nat) where
  pm   : Fin k → Bool
  dm   : Fin k → Bool
  cur  : Fin I.numLocs
  cost : Nat

/-- Key equality for DP state deduplication. -/
def sameDPKey {I : Instance} {k : Nat} (a b : ExclDPState I k) : Prop :=
  (∀ j, a.pm j = b.pm j) ∧ (∀ j, a.dm j = b.dm j) ∧ a.cur = b.cur

instance {I : Instance} {k : Nat} (a b : ExclDPState I k) : Decidable (sameDPKey a b) := by
  unfold sameDPKey; infer_instance

/-- Insert a DP entry into a layer keeping the minimum cost per `(pm, dm, cur)` (`ex1.py:L857-L858, L874-L875`). -/
def exclDedupInsert {I : Instance} {k : Nat} (st : ExclDPState I k) :
    List (ExclDPState I k) → List (ExclDPState I k)
  | [] => [st]
  | h :: t =>
    if sameDPKey h st then (if st.cost < h.cost then st else h) :: t
    else h :: exclDedupInsert st t

theorem exclDedupInsert_self {I : Instance} {k : Nat} (st : ExclDPState I k) (l : List (ExclDPState I k)) :
    ∃ x ∈ exclDedupInsert st l, sameDPKey x st ∧ x.cost ≤ st.cost := by
  induction l with
  | nil => exact ⟨st, List.mem_cons_self .., ⟨fun _ => rfl, fun _ => rfl, rfl⟩, Nat.le_refl _⟩
  | cons h t ih =>
    unfold exclDedupInsert
    by_cases hk : sameDPKey h st
    · simp only [hk, ↓reduceIte]
      by_cases hc : st.cost < h.cost
      · simp only [hc, ↓reduceIte]
        exact ⟨st, List.mem_cons_self .., ⟨fun _ => rfl, fun _ => rfl, rfl⟩, Nat.le_refl _⟩
      · simp only [hc, ↓reduceIte]
        exact ⟨h, List.mem_cons_self .., hk, by omega⟩
    · simp only [hk, ↓reduceIte]
      rcases ih with ⟨x, hx, hkx, hcx⟩
      exact ⟨x, List.mem_cons_of_mem _ hx, hkx, hcx⟩

theorem exclDedupInsert_mem {I : Instance} {k : Nat} (st : ExclDPState I k) (l : List (ExclDPState I k))
    {y : ExclDPState I k} (hy : y ∈ l) :
    ∃ x ∈ exclDedupInsert st l, sameDPKey x y ∧ x.cost ≤ y.cost := by
  induction l with
  | nil => simp at hy
  | cons h t ih =>
    unfold exclDedupInsert
    rcases List.mem_cons.mp hy with rfl | hyt
    · by_cases hk : sameDPKey y st
      · simp only [hk, ↓reduceIte]
        by_cases hc : st.cost < y.cost
        · simp only [hc, ↓reduceIte]
          exact ⟨st, List.mem_cons_self .., ⟨fun j => (hk.1 j).symm, fun j => (hk.2.1 j).symm, hk.2.2.symm⟩, by omega⟩
        · simp only [hc, ↓reduceIte]
          exact ⟨y, List.mem_cons_self .., ⟨fun _ => rfl, fun _ => rfl, rfl⟩, Nat.le_refl _⟩
      · simp only [hk, ↓reduceIte]
        exact ⟨y, List.mem_cons_self .., ⟨fun _ => rfl, fun _ => rfl, rfl⟩, Nat.le_refl _⟩
    · by_cases hk : sameDPKey h st
      · simp only [hk, ↓reduceIte]
        exact ⟨y, List.mem_cons_of_mem _ hyt, ⟨fun _ => rfl, fun _ => rfl, rfl⟩, Nat.le_refl _⟩
      · simp only [hk, ↓reduceIte]
        rcases ih hyt with ⟨x, hx, hkx, hcx⟩
        exact ⟨x, List.mem_cons_of_mem _ hx, hkx, hcx⟩

/-- Deduplicate an entire list of DP entries. -/
def exclDedupList {I : Instance} {k : Nat} : List (ExclDPState I k) → List (ExclDPState I k)
  | [] => []
  | h :: t => exclDedupInsert h (exclDedupList t)

theorem exclDedupList_mem {I : Instance} {k : Nat} (l : List (ExclDPState I k))
    {y : ExclDPState I k} (hy : y ∈ l) :
    ∃ x ∈ exclDedupList l, sameDPKey x y ∧ x.cost ≤ y.cost := by
  induction l with
  | nil => simp at hy
  | cons h t ih =>
    unfold exclDedupList
    rcases List.mem_cons.mp hy with rfl | hyt
    · exact exclDedupInsert_self y (exclDedupList t)
    · rcases ih hyt with ⟨z, hz, hkz, hcz⟩
      rcases exclDedupInsert_mem h (exclDedupList t) hz with ⟨x, hx, hkx, hcx⟩
      exact ⟨x, hx, ⟨fun j => (hkx.1 j).trans (hkz.1 j), fun j => (hkx.2.1 j).trans (hkz.2.1 j),
        hkx.2.2.trans hkz.2.2⟩, Nat.le_trans hcx hcz⟩

/-- Initial DP layer (`ex1.py:L849-L858`). -/
def exclInitLayer {I : Instance} {k : Nat} (startRow : Fin I.numLocs → Nat)
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) : List (ExclDPState I k) :=
  let ipm := exclInitPM pairs
  let raw := (List.finRange k).map fun i =>
    let picked := ipm i
    let loc := exclLoc pairs i picked
    let d := startRow loc
    if picked then
      { pm := ipm, dm := setBit (fun _ => false) i, cur := loc, cost := d }
    else
      { pm := setBit ipm i, dm := fun _ => false, cur := loc, cost := d }
  exclDedupList raw

/-- Single forward layer transition (`ex1.py:L860-L876`). -/
def exclStepLayer {I : Instance} (M : FullMetric I) {k : Nat}
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    (layer : List (ExclDPState I k)) : List (ExclDPState I k) :=
  let raw := layer.flatMap fun st =>
    (List.finRange k).filterMap fun i =>
      if st.dm i then none
      else
        let picked := st.pm i
        let loc := exclLoc pairs i picked
        let nc := st.cost + M.distFull st.cur loc
        some (if picked then
          { pm := st.pm, dm := setBit st.dm i, cur := loc, cost := nc }
        else
          { pm := setBit st.pm i, dm := st.dm, cur := loc, cost := nc })
  exclDedupList raw

/-- Run `n` forward layer transitions. -/
def exclIterLayers {I : Instance} (M : FullMetric I) {k : Nat}
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) :
    Nat → List (ExclDPState I k) → List (ExclDPState I k)
  | 0, layer => layer
  | n + 1, layer => exclIterLayers M pairs n (exclStepLayer M pairs layer)

/-- Minimum cost of a DP layer (`min(layer.values(), default=0)`, `ex1.py:L880`). -/
def exclLayerMin {I : Instance} {k : Nat} : List (ExclDPState I k) → Nat
  | [] => 0
  | [x] => x.cost
  | x :: xs => min x.cost (exclLayerMin xs)

theorem exclLayerMin_le_mem {I : Instance} {k : Nat} (l : List (ExclDPState I k))
    {x : ExclDPState I k} (hx : x ∈ l) : exclLayerMin l ≤ x.cost := by
  induction l with
  | nil => simp at hx
  | cons a t ih =>
    cases t with
    | nil =>
      simp only [List.mem_singleton] at hx; subst hx; simp [exclLayerMin]
    | cons b t' =>
      simp only [exclLayerMin]
      rcases List.mem_cons.mp hx with rfl | ht
      · exact Nat.min_le_left _ _
      · exact Nat.le_trans (Nat.min_le_right _ _) (ih ht)

/-- Exact `_excl_tsp_lb` matching `ex1.py:L827-L885`! -/
def exclTspLB {I : Instance} (M : FullMetric I) {k : Nat}
    (startRow : Fin I.numLocs → Nat)
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) : Nat :=
  let rev := exclRemEv pairs
  if rev = 0 then 0
  else exclLayerMin (exclIterLayers M pairs (rev - 1) (exclInitLayer startRow pairs))

/-- Valid event transition predicate for a sequence of `ExclEv k` from `(pm, dm)`. -/
def validEvStep {k : Nat} (pm dm : Fin k → Bool) : ExclEv k → Bool
  | .pickup i  => !dm i && !pm i
  | .deliver i => !dm i && pm i

def applyEvPM {k : Nat} (pm : Fin k → Bool) : ExclEv k → Fin k → Bool
  | .pickup i  => setBit pm i
  | .deliver _ => pm

def applyEvDM {k : Nat} (dm : Fin k → Bool) : ExclEv k → Fin k → Bool
  | .pickup _  => dm
  | .deliver i => setBit dm i

/-- Cost of visiting a non-empty sequence of events starting with `startRow`. -/
def evTailCost {I : Instance} (M : FullMetric I) {k : Nat}
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    (cur : Fin I.numLocs) : List (ExclEv k) → Nat
  | [] => 0
  | e :: es => M.distFull cur (exclEvLoc pairs e) + evTailCost M pairs (exclEvLoc pairs e) es

def evSeqCost {I : Instance} (M : FullMetric I) {k : Nat}
    (startRow : Fin I.numLocs → Nat)
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs) : List (ExclEv k) → Nat
  | [] => 0
  | e :: es => startRow (exclEvLoc pairs e) + evTailCost M pairs (exclEvLoc pairs e) es

/-- Validity of an entire event suffix from `(pm, dm)`. -/
def validEvSeq {k : Nat} (pm dm : Fin k → Bool) : List (ExclEv k) → Prop
  | [] => True
  | e :: es => validEvStep pm dm e = true ∧ validEvSeq (applyEvPM pm e) (applyEvDM dm e) es

/-- Key forward-layer tracking invariant:
    If `(pm, dm, cur, cost)` is dominated by some entry in `layer`, and `es` is a valid suffix of length `n`,
    then `exclIterLayers M pairs n layer` contains an entry with cost `≤ cost + evTailCost M pairs cur es`! -/
theorem exclIterLayers_tracks {I : Instance} (M : FullMetric I) {k : Nat}
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    (es : List (ExclEv k)) :
    ∀ (layer : List (ExclDPState I k)) (pm dm : Fin k → Bool) (cur : Fin I.numLocs) (cost : Nat),
      (∃ st ∈ layer, sameDPKey st ⟨pm, dm, cur, cost⟩ ∧ st.cost ≤ cost) →
      validEvSeq pm dm es →
      ∃ st_end ∈ exclIterLayers M pairs es.length layer,
        st_end.cost ≤ cost + evTailCost M pairs cur es := by
  induction es with
  | nil =>
    intro layer pm dm cur cost ⟨st, hmem, _, hle⟩ _
    exact ⟨st, hmem, by simpa [evTailCost] using hle⟩
  | cons e rest ih =>
    intro layer pm dm cur cost ⟨st, hmem, hkey, hle⟩ ⟨hstep, hrest⟩
    have hdm_eq : ∀ j, st.dm j = dm j := hkey.2.1
    have hpm_eq : ∀ j, st.pm j = pm j := hkey.1
    have hcur_eq : st.cur = cur := hkey.2.2
    -- Produce the successor entry in `exclStepLayer M pairs layer`!
    have hnext : ∃ st' ∈ exclStepLayer M pairs layer,
        sameDPKey st' ⟨applyEvPM pm e, applyEvDM dm e, exclEvLoc pairs e, cost + M.distFull cur (exclEvLoc pairs e)⟩ ∧
        st'.cost ≤ cost + M.distFull cur (exclEvLoc pairs e) := by
      cases e with
      | pickup i =>
        simp only [validEvStep, Bool.and_eq_true, Bool.not_eq_true'] at hstep
        have hdm_i : st.dm i = false := (hdm_eq i).trans hstep.1
        have hpm_i : st.pm i = false := (hpm_eq i).trans hstep.2
        let cand : ExclDPState I k :=
          { pm := setBit st.pm i, dm := st.dm, cur := exclLoc pairs i false,
            cost := st.cost + M.distFull st.cur (exclLoc pairs i false) }
        have hcand_in : cand ∈ layer.flatMap (fun st0 =>
            (List.finRange k).filterMap fun j =>
              if st0.dm j then none
              else
                let picked := st0.pm j
                let loc := exclLoc pairs j picked
                let nc := st0.cost + M.distFull st0.cur loc
                some (if picked then
                  { pm := st0.pm, dm := setBit st0.dm j, cur := loc, cost := nc }
                else
                  { pm := setBit st0.pm j, dm := st0.dm, cur := loc, cost := nc })) := by
          rw [List.mem_flatMap]
          refine ⟨st, hmem, ?_⟩
          rw [List.mem_filterMap]
          refine ⟨i, List.mem_finRange i, ?_⟩
          simp [hdm_i, hpm_i, cand]
        rcases exclDedupList_mem _ hcand_in with ⟨st', hst', hks', hcs'⟩
        refine ⟨st', hst', ?_, ?_⟩
        · refine ⟨fun j => ?_, fun j => (hks'.2.1 j).trans (hdm_eq j), hks'.2.2⟩
          rw [hks'.1 j]; dsimp [cand, applyEvPM, setBit]; split <;> simp [hpm_eq]
        · dsimp only [cand] at hcs'; rw [hcur_eq] at hcs'; dsimp [exclEvLoc]; omega
      | deliver i =>
        simp only [validEvStep, Bool.and_eq_true, Bool.not_eq_true'] at hstep
        have hdm_i : st.dm i = false := (hdm_eq i).trans hstep.1
        have hpm_i : st.pm i = true := (hpm_eq i).trans hstep.2
        let cand : ExclDPState I k :=
          { pm := st.pm, dm := setBit st.dm i, cur := exclLoc pairs i true,
            cost := st.cost + M.distFull st.cur (exclLoc pairs i true) }
        have hcand_in : cand ∈ layer.flatMap (fun st0 =>
            (List.finRange k).filterMap fun j =>
              if st0.dm j then none
              else
                let picked := st0.pm j
                let loc := exclLoc pairs j picked
                let nc := st0.cost + M.distFull st0.cur loc
                some (if picked then
                  { pm := st0.pm, dm := setBit st0.dm j, cur := loc, cost := nc }
                else
                  { pm := setBit st0.pm j, dm := st0.dm, cur := loc, cost := nc })) := by
          rw [List.mem_flatMap]
          refine ⟨st, hmem, ?_⟩
          rw [List.mem_filterMap]
          refine ⟨i, List.mem_finRange i, ?_⟩
          simp [hdm_i, hpm_i, cand]
        rcases exclDedupList_mem _ hcand_in with ⟨st', hst', hks', hcs'⟩
        refine ⟨st', hst', ?_, ?_⟩
        · refine ⟨fun j => (hks'.1 j).trans (hpm_eq j), fun j => ?_, hks'.2.2⟩
          rw [hks'.2.1 j]; dsimp [cand, applyEvDM, setBit]; split <;> simp [hdm_eq]
        · dsimp only [cand] at hcs'; rw [hcur_eq] at hcs'; dsimp [exclEvLoc]; omega
    rcases ih (exclStepLayer M pairs layer) (applyEvPM pm e) (applyEvDM dm e) (exclEvLoc pairs e)
        (cost + M.distFull cur (exclEvLoc pairs e)) hnext hrest with ⟨st_end, hmem_end, hle_end⟩
    refine ⟨st_end, ?_, ?_⟩
    · simpa [List.length_cons, exclIterLayers] using hmem_end
    · simp only [evTailCost]; omega

/-- `exclTspLB` is `≤ evSeqCost` for ANY valid event sequence of length `exclRemEv pairs`! -/
theorem exclTspLB_le_validEvSeq {I : Instance} (M : FullMetric I) {k : Nat}
    (startRow : Fin I.numLocs → Nat)
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    (evs : List (ExclEv k))
    (hlen : evs.length = exclRemEv pairs)
    (hvalid : validEvSeq (exclInitPM pairs) (fun _ => false) evs) :
    exclTspLB M startRow pairs ≤ evSeqCost M startRow pairs evs := by
  cases evs with
  | nil =>
    have h0 : exclRemEv pairs = 0 := by simpa using hlen.symm
    simp [exclTspLB, h0]
  | cons e0 rest =>
    have hrev : exclRemEv pairs = rest.length + 1 := by simpa using hlen.symm
    unfold exclTspLB
    simp only [hrev, Nat.add_eq_zero_iff, Nat.one_ne_zero, and_false, ↓reduceIte, Nat.add_sub_cancel]
    rcases hvalid with ⟨hstep0, hrest⟩
    -- Show the first event `e0` is tracked in `exclInitLayer startRow pairs`!
    have hinit : ∃ st ∈ exclInitLayer startRow pairs,
        sameDPKey st ⟨applyEvPM (exclInitPM pairs) e0, applyEvDM (fun _ => false) e0,
                      exclEvLoc pairs e0, startRow (exclEvLoc pairs e0)⟩ ∧
        st.cost ≤ startRow (exclEvLoc pairs e0) := by
      cases e0 with
      | pickup i =>
        simp only [validEvStep, Bool.not_false, Bool.true_and, Bool.not_eq_true'] at hstep0
        let cand : ExclDPState I k :=
          { pm := setBit (exclInitPM pairs) i, dm := fun _ => false,
            cur := exclLoc pairs i false, cost := startRow (exclLoc pairs i false) }
        have hcand_in : cand ∈ (List.finRange k).map (fun j =>
            let picked := exclInitPM pairs j
            let loc := exclLoc pairs j picked
            let d := startRow loc
            if picked then
              { pm := exclInitPM pairs, dm := setBit (fun _ => false) j, cur := loc, cost := d }
            else
              { pm := setBit (exclInitPM pairs) j, dm := fun _ => false, cur := loc, cost := d }) := by
          rw [List.mem_map]; exact ⟨i, List.mem_finRange i, by simp [hstep0, cand]⟩
        rcases exclDedupList_mem _ hcand_in with ⟨st, hst, hks, hcs⟩
        exact ⟨st, hst, hks, hcs⟩
      | deliver i =>
        simp only [validEvStep, Bool.not_false, Bool.true_and] at hstep0
        let cand : ExclDPState I k :=
          { pm := exclInitPM pairs, dm := setBit (fun _ => false) i,
            cur := exclLoc pairs i true, cost := startRow (exclLoc pairs i true) }
        have hcand_in : cand ∈ (List.finRange k).map (fun j =>
            let picked := exclInitPM pairs j
            let loc := exclLoc pairs j picked
            let d := startRow loc
            if picked then
              { pm := exclInitPM pairs, dm := setBit (fun _ => false) j, cur := loc, cost := d }
            else
              { pm := setBit (exclInitPM pairs) j, dm := fun _ => false, cur := loc, cost := d }) := by
          rw [List.mem_map]; exact ⟨i, List.mem_finRange i, by simp [hstep0, cand]⟩
        rcases exclDedupList_mem _ hcand_in with ⟨st, hst, hks, hcs⟩
        exact ⟨st, hst, hks, hcs⟩
    rcases exclIterLayers_tracks M pairs rest (exclInitLayer startRow pairs)
        (applyEvPM (exclInitPM pairs) e0) (applyEvDM (fun _ => false) e0)
        (exclEvLoc pairs e0) (startRow (exclEvLoc pairs e0)) hinit hrest with ⟨st_end, hmem_end, hle_end⟩
    exact Nat.le_trans (exclLayerMin_le_mem _ hmem_end) hle_end

/-- Tail path cost for a sequence of timed visits `(stepIdx, loc)`. -/
def visitsTailCost {I : Instance} (M : FullMetric I) (cur : Fin I.numLocs) : List (Nat × Fin I.numLocs) → Nat
  | [] => 0
  | (_, l) :: r => M.distFull cur l + visitsTailCost M l r

/-- Total path cost for a sequence of timed visits `(stepIdx, loc)` starting from `truckFullPot M s ti`. -/
def visitsPathCost {I : Instance} (M : FullMetric I) (s : State I) (ti : Fin I.numTrucks) :
    List (Nat × Fin I.numLocs) → Nat
  | [] => 0
  | (_, l0) :: rest => truckFullPot M s ti l0 + visitsTailCost M l0 rest

theorem visitsTailCost_map_shift {I : Instance} (M : FullMetric I) (t0 : Nat)
    (cur : Fin I.numLocs) (ls : List (Nat × Fin I.numLocs)) :
    visitsTailCost M cur (ls.map (fun v => (v.1 - t0, v.2))) = visitsTailCost M cur ls := by
  induction ls generalizing cur with
  | nil => rfl
  | cons x xs ih => simp only [List.map_cons, visitsTailCost, ih]

/-- Any sorted sequence of visited `(stepIdx, loc)` pairs along `π` for truck `ti` has path cost `≤ costMove π`! -/
theorem sorted_visits_cost_le_costMove {I : Instance} (M : FullMetric I)
    (ti : Fin I.numTrucks) :
    ∀ (n : Nat) (visits : List (Nat × Fin I.numLocs)), visits.length = n →
      ∀ {s s_end : State I} {π : Plan I},
        ValidState I s → ValidPlan I s π s_end →
        visits.Pairwise (fun a b => a.1 ≤ b.1) →
        (∀ v ∈ visits, (stateAt s π v.1).truckLoc ti = .atLoc v.2) →
        visitsPathCost M s ti visits ≤ costMove π := by
  intro n
  induction n with
  | zero =>
    intro visits hlen _ _ _ _ _ _ _
    cases visits with
    | nil => exact Nat.zero_le _
    | cons _ _ => simp at hlen
  | succ n' ih =>
    intro visits hlen s s_end π hv hp hpw hloc
    cases visits with
    | nil => simp at hlen
    | cons v0 rest =>
      rcases v0 with ⟨t0, l0⟩
      have ⟨hp_take, hp_drop⟩ := validPlan_take_drop hp t0
      have hvm : ValidState I (stateAt s π t0) := validState_stateAt hv hp t0
      have hloc0 : (stateAt s π t0).truckLoc ti = .atLoc l0 := hloc (t0, l0) (List.mem_cons_self ..)
      have hfirst : truckFullPot M s ti l0 ≤ costMove (π.take t0) := by
        have h := truckFullPot_drop_le_costMove M hv hp_take ti l0
        have hz : truckFullPot M (stateAt s π t0) ti l0 = 0 := by simp [truckFullPot, hloc0, M.distFull_self]
        omega
      have hcost_eq : costMove π = costMove (π.take t0) + costMove (π.drop t0) := by
        rw [← costMove_append, List.take_append_drop]
      cases rest with
      | nil =>
        simp only [visitsPathCost, visitsTailCost, Nat.add_zero]
        omega
      | cons v1 rest' =>
        rcases v1 with ⟨t1, l1⟩
        have hle_all : ∀ v ∈ (t1, l1) :: rest', t0 ≤ v.1 := (List.pairwise_cons.mp hpw).1
        have hpw_rest : ((t1, l1) :: rest').Pairwise (fun a b => a.1 ≤ b.1) := (List.pairwise_cons.mp hpw).2
        let shifted := ((t1, l1) :: rest').map (fun v => (v.1 - t0, v.2))
        have hsh_len : shifted.length = n' := by
          dsimp only [shifted]; rw [List.length_map]; simp at hlen; omega
        have hpw_sh : shifted.Pairwise (fun a b => a.1 ≤ b.1) := by
          rw [List.pairwise_map]
          exact hpw_rest.imp (fun {a b} hab => Nat.sub_le_sub_right hab t0)
        have hloc_sh : ∀ v ∈ shifted, (stateAt (stateAt s π t0) (π.drop t0) v.1).truckLoc ti = .atLoc v.2 := by
          intro v hv_mem
          rw [List.mem_map] at hv_mem
          rcases hv_mem with ⟨u, hu_mem, rfl⟩
          rw [stateAt_drop]
          have ht0_le : t0 ≤ u.1 := hle_all u hu_mem
          have hadd : t0 + (u.1 - t0) = u.1 := by omega
          rw [hadd]
          exact hloc u (List.mem_cons_of_mem _ hu_mem)
        have hih := ih shifted hsh_len hvm hp_drop hpw_sh hloc_sh
        have hpot1 : truckFullPot M (stateAt s π t0) ti l1 = M.distFull l0 l1 := by
          simp [truckFullPot, hloc0]
        simp only [shifted, List.map_cons, visitsPathCost] at hih
        rw [hpot1, visitsTailCost_map_shift] at hih
        simp only [visitsPathCost, visitsTailCost]
        omega

/-- Insertion sort on timed events `(stepIdx, ExclEv k)` by `stepIdx`. -/
def insertTimedEv {k : Nat} (x : Nat × ExclEv k) : List (Nat × ExclEv k) → List (Nat × ExclEv k)
  | [] => [x]
  | y :: ys => if x.1 ≤ y.1 then x :: y :: ys else y :: insertTimedEv x ys

def sortTimedEvs {k : Nat} : List (Nat × ExclEv k) → List (Nat × ExclEv k)
  | [] => []
  | x :: xs => insertTimedEv x (sortTimedEvs xs)

theorem insertTimedEv_length {k : Nat} (x : Nat × ExclEv k) (l : List (Nat × ExclEv k)) :
    (insertTimedEv x l).length = l.length + 1 := by
  induction l with
  | nil => rfl
  | cons y ys ih => unfold insertTimedEv; split <;> simp [ih]

theorem sortTimedEvs_length {k : Nat} (l : List (Nat × ExclEv k)) :
    (sortTimedEvs l).length = l.length := by
  induction l with
  | nil => rfl
  | cons x xs ih => simp [sortTimedEvs, insertTimedEv_length, ih]

theorem mem_insertTimedEv {k : Nat} (x y : Nat × ExclEv k) (l : List (Nat × ExclEv k)) :
    y ∈ insertTimedEv x l ↔ y = x ∨ y ∈ l := by
  induction l with
  | nil => simp [insertTimedEv]
  | cons z zs ih =>
    unfold insertTimedEv; split
    · simp
    · simp only [List.mem_cons, ih]
      constructor
      · rintro (rfl | rfl | h)
        · exact Or.inr (Or.inl rfl)
        · exact Or.inl rfl
        · exact Or.inr (Or.inr h)
      · rintro (rfl | rfl | h)
        · exact Or.inr (Or.inl rfl)
        · exact Or.inl rfl
        · exact Or.inr (Or.inr h)

theorem mem_sortTimedEvs {k : Nat} (y : Nat × ExclEv k) (l : List (Nat × ExclEv k)) :
    y ∈ sortTimedEvs l ↔ y ∈ l := by
  induction l with
  | nil => simp [sortTimedEvs]
  | cons x xs ih => simp [sortTimedEvs, mem_insertTimedEv, ih]

theorem insertTimedEv_pairwise {k : Nat} (x : Nat × ExclEv k) {l : List (Nat × ExclEv k)}
    (hl : l.Pairwise (fun a b => a.1 ≤ b.1)) :
    (insertTimedEv x l).Pairwise (fun a b => a.1 ≤ b.1) := by
  induction l with
  | nil => simp [insertTimedEv]
  | cons y ys ih =>
    unfold insertTimedEv
    by_cases hxy : x.1 ≤ y.1
    · simp only [hxy, ↓reduceIte]
      rw [List.pairwise_cons]
      refine ⟨?_, hl⟩
      intro z hz
      rcases List.mem_cons.mp hz with rfl | hzys
      · exact hxy
      · exact Nat.le_trans hxy ((List.pairwise_cons.mp hl).1 z hzys)
    · simp only [hxy, ↓reduceIte]
      rw [List.pairwise_cons]
      refine ⟨?_, ih (List.pairwise_cons.mp hl).2⟩
      intro z hz
      rw [mem_insertTimedEv] at hz
      rcases hz with rfl | hzys
      · omega
      · exact (List.pairwise_cons.mp hl).1 z hzys

theorem sortTimedEvs_pairwise {k : Nat} (l : List (Nat × ExclEv k)) :
    (sortTimedEvs l).Pairwise (fun a b => a.1 ≤ b.1) := by
  induction l with
  | nil => simp [sortTimedEvs]
  | cons x xs ih => exact insertTimedEv_pairwise x ih

theorem insertTimedEv_nodup {k : Nat} {x : Nat × ExclEv k} {l : List (Nat × ExclEv k)}
    (hx : x ∉ l) (hnd : l.Nodup) : (insertTimedEv x l).Nodup := by
  induction l with
  | nil => simp [insertTimedEv]
  | cons y ys ih =>
    unfold insertTimedEv
    have ⟨hny, hndys⟩ := List.nodup_cons.mp hnd
    have hxy : x ≠ y := fun h => hx (h ▸ List.mem_cons_self ..)
    have hxys : x ∉ ys := fun h => hx (List.mem_cons_of_mem _ h)
    split
    · exact List.nodup_cons.mpr ⟨hx, hnd⟩
    · refine List.nodup_cons.mpr ⟨?_, ih hxys hndys⟩
      rw [mem_insertTimedEv]; intro h; rcases h with h1 | h2
      · exact hxy h1.symm
      · exact hny h2

theorem sortTimedEvs_nodup {k : Nat} {l : List (Nat × ExclEv k)} (hnd : l.Nodup) :
    (sortTimedEvs l).Nodup := by
  induction l with
  | nil => simp [sortTimedEvs]
  | cons x xs ih =>
    have ⟨hx, hxs⟩ := List.nodup_cons.mp hnd
    exact insertTimedEv_nodup (by rwa [mem_sortTimedEvs]) (ih hxs)

/-- Any sorted, duplicate-free list of timed events where each `i` has `(dropStep i, .deliver i)`
    and (if `initPM pairs i = false`) `(pickStep i, .pickup i)` with `pickStep i < dropStep i`
    induces a `validEvSeq` from `(exclInitPM pairs, fun _ => false)`! -/
theorem sorted_timed_evs_valid {k : Nat}
    (pickStep dropStep : Fin k → Nat)
    (l : List (Nat × ExclEv k))
    (hlt : ∀ i, (pickStep i, ExclEv.pickup i) ∈ l → pickStep i < dropStep i)
    (hpw : l.Pairwise (fun a b => a.1 ≤ b.1))
    (hnd : l.Nodup)
    (pm dm : Fin k → Bool)
    (hinv : ∀ j, dm j = true → pm j = true)
    (hspec_p : ∀ i, (pickStep i, ExclEv.pickup i) ∈ l ↔ pm i = false)
    (hspec_d : ∀ i, (dropStep i, ExclEv.deliver i) ∈ l ↔ dm i = false)
    (honly : ∀ x ∈ l, (∃ i, x = (pickStep i, .pickup i)) ∨ (∃ i, x = (dropStep i, .deliver i))) :
    validEvSeq pm dm (l.map Prod.snd) := by
  induction l generalizing pm dm with
  | nil => trivial
  | cons x xs ih =>
    have hpw_xs := (List.pairwise_cons.mp hpw).2
    have hle_xs := (List.pairwise_cons.mp hpw).1
    have ⟨hx_not_xs, hnd_xs⟩ := List.nodup_cons.mp hnd
    have hlt_xs : ∀ i, (pickStep i, ExclEv.pickup i) ∈ xs → pickStep i < dropStep i :=
      fun i hi => hlt i (List.mem_cons_of_mem _ hi)
    have honly_xs : ∀ y ∈ xs, (∃ i, y = (pickStep i, .pickup i)) ∨ (∃ i, y = (dropStep i, .deliver i)) :=
      fun y hy => honly y (List.mem_cons_of_mem _ hy)
    rcases honly x (List.mem_cons_self ..) with ⟨i, rfl⟩ | ⟨i, rfl⟩
    · -- Head event is `(pickStep i, .pickup i)`
      have hpm_i : pm i = false := (hspec_p i).mp (List.mem_cons_self ..)
      have hdm_i : dm i = false := by
        cases hd : dm i
        · rfl
        · have := hinv i hd; rw [hpm_i] at this; cases this
      refine ⟨by simp [validEvStep, hpm_i, hdm_i], ?_⟩
      apply ih hlt_xs hpw_xs hnd_xs (setBit pm i) dm
      · intro j hj; dsimp [setBit]; split
        · rfl
        · exact hinv j hj
      · intro j
        by_cases hji : j = i
        · subst hji
          simp only [setBit, ↓reduceIte, Bool.true_eq_false, iff_false]
          exact hx_not_xs
        · simp only [setBit, hji, ↓reduceIte]
          constructor
          · intro hmem; exact (hspec_p j).mp (List.mem_cons_of_mem _ hmem)
          · intro hpmj
            have hmem := (hspec_p j).mpr hpmj
            rcases List.mem_cons.mp hmem with heq | hmem_xs
            · injection heq with _ hev; injection hev with hji'; exact absurd hji' hji
            · exact hmem_xs
      · intro j
        constructor
        · intro hmem; exact (hspec_d j).mp (List.mem_cons_of_mem _ hmem)
        · intro hdmj
          have hmem := (hspec_d j).mpr hdmj
          rcases List.mem_cons.mp hmem with heq | hmem_xs
          · injection heq with _ hev; cases hev
          · exact hmem_xs
      · exact honly_xs
    · -- Head event is `(dropStep i, .deliver i)`
      have hdm_i : dm i = false := (hspec_d i).mp (List.mem_cons_self ..)
      have hpm_i : pm i = true := by
        cases hp : pm i
        · have hmem := (hspec_p i).mpr hp
          rcases List.mem_cons.mp hmem with heq | hmem_xs
          · injection heq with _ hev; cases hev
          · have hle := hle_xs (pickStep i, .pickup i) hmem_xs
            have hlt_i := hlt i (List.mem_cons_of_mem _ hmem_xs)
            omega
        · rfl
      refine ⟨by simp [validEvStep, hpm_i, hdm_i], ?_⟩
      apply ih hlt_xs hpw_xs hnd_xs pm (setBit dm i)
      · intro j hj; dsimp [setBit] at hj; split at hj
        · rename_i hji; subst hji; exact hpm_i
        · exact hinv j hj
      · intro j
        constructor
        · intro hmem; exact (hspec_p j).mp (List.mem_cons_of_mem _ hmem)
        · intro hpmj
          have hmem := (hspec_p j).mpr hpmj
          rcases List.mem_cons.mp hmem with heq | hmem_xs
          · injection heq with _ hev; cases hev
          · exact hmem_xs
      · intro j
        by_cases hji : j = i
        · subst hji
          simp only [setBit, ↓reduceIte, Bool.true_eq_false, iff_false]
          exact hx_not_xs
        · simp only [setBit, hji, ↓reduceIte]
          constructor
          · intro hmem; exact (hspec_d j).mp (List.mem_cons_of_mem _ hmem)
          · intro hdmj
            have hmem := (hspec_d j).mpr hdmj
            rcases List.mem_cons.mp hmem with heq | hmem_xs
            · injection heq with _ hev; injection hev with hji'; exact absurd hji' hji
            · exact hmem_xs
      · exact honly_xs

/-- Admissibility of `_excl_tsp_lb` (`ex1.py:L827-L885, L1450-L1453`):
    For ANY truck `ti` and ANY finite family of pairs `pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs`
    (covering deduplication, sorting, AND the `k > 4` 4-element subset selection!),
    if every pair `i` is witnessed by an undelivered exclusive package `p` of `ti`, then
    `exclTspLB M (truckFullPot M s ti) pairs ≤ costMove π`! -/
theorem exclTspLB_le_costMove {I : Instance} (M : FullMetric I)
    (ti : Fin I.numTrucks) {k : Nat}
    (pairs : Fin k → Option (Fin I.numLocs) × Fin I.numLocs)
    {s s_goal : State I} {π : Plan I}
    (hv : ValidState I s) (hp : ValidPlan I s π s_goal) (hg : goalTest I s_goal)
    (hwitness : ∀ i : Fin k, ∃ p : Fin I.numPkgs,
      isExclusive I ti p ∧
      s.pkgDelivered p = false ∧
      I.pkgGoal p = (pairs i).2 ∧
      (match (pairs i).1 with
       | none   => s.pkgLoc p = .inTruck ti
       | some l => s.pkgLoc p = .atLoc l)) :
    exclTspLB M (truckFullPot M s ti) pairs ≤ costMove π := by
  -- 1. Extract `(pickStep i, dropStep i)` for every `i : Fin k` via Classical.choice
  have hex : ∀ i : Fin k, ∃ (tp td : Nat),
      (exclInitPM pairs i = false → tp < td) ∧
      (stateAt s π td).truckLoc ti = .atLoc (pairs i).2 ∧
      (∀ l, (pairs i).1 = some l → (stateAt s π tp).truckLoc ti = .atLoc l) := by
    intro i
    rcases hwitness i with ⟨p, hexcl, hnd, hgl, hloc⟩
    cases hopt : (pairs i).1 with
    | none =>
      rw [hopt] at hloc
      rcases excl_exists_deliver_step hv hp hg ti p hexcl hnd with ⟨td, _, hloc_d⟩
      exact ⟨0, td, fun h => by simp [exclInitPM, hopt] at h, hgl ▸ hloc_d, fun l h => by cases h⟩
    | some l =>
      rw [hopt] at hloc
      rcases excl_exists_pickup_before_deliver hv hp hg ti p l hexcl hloc hnd with
        ⟨tp, td, hlt, _, hloc_p, hloc_d⟩
      exact ⟨tp, td, fun _ => hlt, hgl ▸ hloc_d, fun l' h => by injection h with hll; subst hll; exact hloc_p⟩
  let pickStep : Fin k → Nat := fun i => (Classical.choose (hex i))
  let dropStep : Fin k → Nat := fun i => (Classical.choose (Classical.choose_spec (hex i)))
  have hspec : ∀ i : Fin k,
      (exclInitPM pairs i = false → pickStep i < dropStep i) ∧
      (stateAt s π (dropStep i)).truckLoc ti = .atLoc (pairs i).2 ∧
      (∀ l, (pairs i).1 = some l → (stateAt s π (pickStep i)).truckLoc ti = .atLoc l) :=
    fun i => Classical.choose_spec (Classical.choose_spec (hex i))
  -- 2. Build raw timed event list of exact length `exclRemEv pairs`
  let rawEvs : List (Nat × ExclEv k) :=
    (List.finRange k).flatMap fun i =>
      if (pairs i).1.isNone then [(dropStep i, .deliver i)]
      else [(pickStep i, .pickup i), (dropStep i, .deliver i)]
  have hraw_len : rawEvs.length = exclRemEv pairs := by
    dsimp only [rawEvs, exclRemEv]
    unfold finSum
    rw [List.length_flatMap]
    suffices ∀ (ls : List (Fin k)),
        (ls.map (fun a => (if (pairs a).1.isNone then [(dropStep a, ExclEv.deliver a)]
                           else [(pickStep a, .pickup a), (dropStep a, .deliver a)]).length)).sum =
        ls.foldr (fun i acc => (if (pairs i).1.isNone then 1 else 2) + acc) 0 from
      this (List.finRange k)
    intro ls
    induction ls with
    | nil => rfl
    | cons a as iha =>
      simp only [List.map_cons, List.sum_cons, List.foldr_cons, iha]
      cases (pairs a).1 <;> simp
  have hraw_mem_p : ∀ i, (pickStep i, ExclEv.pickup i) ∈ rawEvs ↔ exclInitPM pairs i = false := by
    intro i; dsimp only [rawEvs, exclInitPM]
    rw [List.mem_flatMap]
    constructor
    · rintro ⟨j, _, hj⟩
      cases hopt : (pairs j).1 with
      | none => simp [hopt] at hj
      | some l =>
        simp only [hopt, Option.isNone_some, Bool.false_eq_true, ↓reduceIte, List.mem_cons, List.not_mem_nil, or_false] at hj
        rcases hj with h1 | h2
        · injection h1 with _ hev; injection hev with hij; subst hij; simp [hopt]
        · injection h2 with _ hev; cases hev
    · intro hf
      refine ⟨i, List.mem_finRange i, ?_⟩
      simp [hf]
  have hraw_mem_d : ∀ i, (dropStep i, ExclEv.deliver i) ∈ rawEvs := by
    intro i; dsimp only [rawEvs]
    rw [List.mem_flatMap]; refine ⟨i, List.mem_finRange i, ?_⟩
    cases (pairs i).1 <;> simp
  have hraw_only : ∀ x ∈ rawEvs, (∃ i, x = (pickStep i, .pickup i)) ∨ (∃ i, x = (dropStep i, .deliver i)) := by
    intro x hx; dsimp only [rawEvs] at hx
    rw [List.mem_flatMap] at hx; rcases hx with ⟨i, _, hi⟩
    cases hopt : (pairs i).1 with
    | none => simp [hopt] at hi; exact Or.inr ⟨i, hi⟩
    | some l =>
      simp only [hopt, Option.isNone_some, Bool.false_eq_true, ↓reduceIte, List.mem_cons, List.not_mem_nil, or_false] at hi
      rcases hi with rfl | rfl
      · exact Or.inl ⟨i, rfl⟩
      · exact Or.inr ⟨i, rfl⟩
  have hraw_nd : rawEvs.Nodup := by
    have hfm : ∀ (ls : List (Fin k)), ls.Nodup →
        (ls.flatMap fun i =>
          if (pairs i).1.isNone then [(dropStep i, ExclEv.deliver i)]
          else [(pickStep i, .pickup i), (dropStep i, .deliver i)]).Nodup := by
      intro ls hnd_ls
      induction ls with
      | nil => simp
      | cons a as iha =>
        have ⟨ha_not, hnd_as⟩ := List.nodup_cons.mp hnd_ls
        have hih := iha hnd_as
        simp only [List.flatMap_cons]
        have hnot_in : ∀ (x : Nat × ExclEv k),
            (x = (pickStep a, .pickup a) ∨ x = (dropStep a, .deliver a)) →
            x ∉ as.flatMap (fun i =>
              if (pairs i).1.isNone then [(dropStep i, ExclEv.deliver i)]
              else [(pickStep i, .pickup i), (dropStep i, .deliver i)]) := by
          intro x hx hmem
          rw [List.mem_flatMap] at hmem
          rcases hmem with ⟨j, hj, hxj⟩
          have hne : a ≠ j := fun h => ha_not (h ▸ hj)
          cases hopt : (pairs j).1 with
          | none =>
            simp [hopt] at hxj
            rcases hx with rfl | rfl
            · injection hxj with _ hev; cases hev
            · injection hxj with _ hev; injection hev with h1; exact hne h1
          | some l =>
            simp only [hopt, Option.isNone_some, Bool.false_eq_true, ↓reduceIte, List.mem_cons, List.not_mem_nil, or_false] at hxj
            rcases hx with rfl | rfl <;> rcases hxj with h1 | h2
            · injection h1 with _ hev; injection hev with he; exact hne he
            · injection h2 with _ hev; cases hev
            · injection h1 with _ hev; cases hev
            · injection h2 with _ hev; injection hev with he; exact hne he
        cases (pairs a).1 with
        | none =>
          simp only [Option.isNone_none, ↓reduceIte, List.singleton_append]
          exact List.nodup_cons.mpr ⟨hnot_in _ (Or.inr rfl), hih⟩
        | some l =>
          simp only [Option.isNone_some, Bool.false_eq_true, ↓reduceIte, List.cons_append, List.nil_append]
          refine List.nodup_cons.mpr ⟨?_, List.nodup_cons.mpr ⟨hnot_in _ (Or.inr rfl), hih⟩⟩
          intro hmem
          rcases List.mem_cons.mp hmem with h1 | h2
          · injection h1 with _ hev; cases hev
          · exact hnot_in _ (Or.inl rfl) h2
    exact hfm (List.finRange k) (List.nodup_finRange k)
  -- 3. Sort `rawEvs` by step index!
  let sorted := sortTimedEvs rawEvs
  have hsorted_len : (sorted.map Prod.snd).length = exclRemEv pairs := by
    rw [List.length_map, sortTimedEvs_length, hraw_len]
  have hsorted_pw : sorted.Pairwise (fun a b => a.1 ≤ b.1) := sortTimedEvs_pairwise rawEvs
  have hsorted_nd : sorted.Nodup := sortTimedEvs_nodup hraw_nd
  have hsorted_valid : validEvSeq (exclInitPM pairs) (fun _ => false) (sorted.map Prod.snd) := by
    apply sorted_timed_evs_valid pickStep dropStep sorted
    · intro i hi
      rw [mem_sortTimedEvs, hraw_mem_p] at hi
      exact (hspec i).1 hi
    · exact hsorted_pw
    · exact hsorted_nd
    · intro j hj; cases hj
    · intro i; rw [mem_sortTimedEvs]; exact hraw_mem_p i
    · intro i; dsimp only [sorted]; rw [mem_sortTimedEvs]; exact ⟨fun _ => rfl, fun _ => hraw_mem_d i⟩
    · intro x hx; rw [mem_sortTimedEvs] at hx; exact hraw_only x hx
  -- 4. Combine DP lower bound with `sorted_visits_cost_le_costMove`!
  have hdp := exclTspLB_le_validEvSeq M (truckFullPot M s ti) pairs (sorted.map Prod.snd) hsorted_len hsorted_valid
  let visits : List (Nat × Fin I.numLocs) := sorted.map (fun x => (x.1, exclEvLoc pairs x.2))
  have hvis_pw : visits.Pairwise (fun a b => a.1 ≤ b.1) := by
    dsimp only [visits]; rw [List.pairwise_map]; exact hsorted_pw
  have hvis_loc : ∀ v ∈ visits, (stateAt s π v.1).truckLoc ti = .atLoc v.2 := by
    intro v hv_mem; dsimp only [visits] at hv_mem
    rw [List.mem_map] at hv_mem
    rcases hv_mem with ⟨x, hx, rfl⟩
    rw [mem_sortTimedEvs] at hx
    rcases hraw_only x hx with ⟨i, rfl⟩ | ⟨i, rfl⟩
    · have hpm_f : exclInitPM pairs i = false := (hraw_mem_p i).mp hx
      cases hopt : (pairs i).1 with
      | none => simp [exclInitPM, hopt] at hpm_f
      | some l =>
        have hloc_ev : exclEvLoc pairs (.pickup i) = l := by simp [exclEvLoc, exclLoc, hopt]
        rw [hloc_ev]
        exact (hspec i).2.2 l hopt
    · have hloc_ev : exclEvLoc pairs (.deliver i) = (pairs i).2 := by simp [exclEvLoc, exclLoc]
      rw [hloc_ev]
      exact (hspec i).2.1
  have hvis_le := sorted_visits_cost_le_costMove M ti visits.length visits rfl hv hp hvis_pw hvis_loc
  have htail_eq : ∀ (cur : Fin I.numLocs) (ls : List (Nat × ExclEv k)),
      evTailCost M pairs cur (ls.map Prod.snd) =
      visitsTailCost M cur (ls.map (fun x => (x.1, exclEvLoc pairs x.2))) := by
    intro cur ls
    induction ls generalizing cur with
    | nil => rfl
    | cons x xs ihx => simp [evTailCost, visitsTailCost, ihx]
  have hseq_eq : ∀ (ls : List (Nat × ExclEv k)),
      evSeqCost M (truckFullPot M s ti) pairs (ls.map Prod.snd) =
      visitsPathCost M s ti (ls.map (fun x => (x.1, exclEvLoc pairs x.2))) := by
    intro ls
    cases ls with
    | nil => rfl
    | cons x xs => simp [evSeqCost, visitsPathCost, htail_eq]
  rw [hseq_eq sorted] at hdp
  exact Nat.le_trans hdp hvis_le

end IslandLogistics

