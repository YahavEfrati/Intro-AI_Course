// Lean compiler output
// Module: Domain
// Imports: public import Init public meta import Init
#include <lean/lean.h>
#if defined(__clang__)
#pragma clang diagnostic ignored "-Wunused-parameter"
#pragma clang diagnostic ignored "-Wunused-label"
#elif defined(__GNUC__) && !defined(__CLANG__)
#pragma GCC diagnostic ignored "-Wunused-parameter"
#pragma GCC diagnostic ignored "-Wunused-label"
#pragma GCC diagnostic ignored "-Wunused-but-set-variable"
#endif
#ifdef __cplusplus
extern "C" {
#endif
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* l_List_finRange(lean_object*);
lean_object* lean_array_mk(lean_object*);
lean_object* lean_array_get_size(lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
size_t lean_usize_of_nat(lean_object*);
uint8_t lean_usize_dec_eq(size_t, size_t);
size_t lean_usize_sub(size_t, size_t);
lean_object* lean_array_uget_borrowed(lean_object*, size_t);
lean_object* lean_obj_tag_nat(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0(lean_object*, lean_object*, size_t, size_t, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldrTR___at___00IslandLogistics_finSum_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgIsGround(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgDelivered___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckLoad___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckLoad(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_ferryCount___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_ferryCount(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planCost(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planCost___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costLU(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costLU___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costDrive(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costDrive___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costBD(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costBD___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costSail(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costSail___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_sailCount_spec__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyAction(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0(lean_object* v_f_1_, lean_object* v_as_2_, size_t v_i_3_, size_t v_stop_4_, lean_object* v_b_5_){
_start:
{
uint8_t v___x_6_; 
v___x_6_ = lean_usize_dec_eq(v_i_3_, v_stop_4_);
if (v___x_6_ == 0)
{
size_t v___x_7_; size_t v___x_8_; lean_object* v___x_9_; lean_object* v___x_10_; lean_object* v___x_11_; 
v___x_7_ = ((size_t)1ULL);
v___x_8_ = lean_usize_sub(v_i_3_, v___x_7_);
v___x_9_ = lean_array_uget_borrowed(v_as_2_, v___x_8_);
lean_inc_ref(v_f_1_);
lean_inc(v___x_9_);
v___x_10_ = lean_apply_1(v_f_1_, v___x_9_);
v___x_11_ = lean_nat_add(v___x_10_, v_b_5_);
lean_dec(v_b_5_);
lean_dec(v___x_10_);
v_i_3_ = v___x_8_;
v_b_5_ = v___x_11_;
goto _start;
}
else
{
lean_dec_ref(v_f_1_);
return v_b_5_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0___boxed(lean_object* v_f_13_, lean_object* v_as_14_, lean_object* v_i_15_, lean_object* v_stop_16_, lean_object* v_b_17_){
_start:
{
size_t v_i_boxed_18_; size_t v_stop_boxed_19_; lean_object* v_res_20_; 
v_i_boxed_18_ = lean_unbox_usize(v_i_15_);
lean_dec(v_i_15_);
v_stop_boxed_19_ = lean_unbox_usize(v_stop_16_);
lean_dec(v_stop_16_);
v_res_20_ = lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0(v_f_13_, v_as_14_, v_i_boxed_18_, v_stop_boxed_19_, v_b_17_);
lean_dec_ref(v_as_14_);
return v_res_20_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldrTR___at___00IslandLogistics_finSum_spec__0(lean_object* v_f_21_, lean_object* v_init_22_, lean_object* v_l_23_){
_start:
{
lean_object* v___x_24_; lean_object* v___x_25_; lean_object* v___x_26_; uint8_t v___x_27_; 
v___x_24_ = lean_array_mk(v_l_23_);
v___x_25_ = lean_array_get_size(v___x_24_);
v___x_26_ = lean_unsigned_to_nat(0u);
v___x_27_ = lean_nat_dec_lt(v___x_26_, v___x_25_);
if (v___x_27_ == 0)
{
lean_dec_ref(v___x_24_);
lean_dec_ref(v_f_21_);
return v_init_22_;
}
else
{
size_t v___x_28_; size_t v___x_29_; lean_object* v___x_30_; 
v___x_28_ = lean_usize_of_nat(v___x_25_);
v___x_29_ = ((size_t)0ULL);
v___x_30_ = lp_island__logistics__proof___private_Init_Data_Array_Basic_0__Array_foldrMUnsafe_fold___at___00List_foldrTR___at___00IslandLogistics_finSum_spec__0_spec__0(v_f_21_, v___x_24_, v___x_28_, v___x_29_, v_init_22_);
lean_dec_ref(v___x_24_);
return v___x_30_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object* v_n_31_, lean_object* v_f_32_){
_start:
{
lean_object* v___x_33_; lean_object* v___x_34_; lean_object* v___x_35_; 
v___x_33_ = lean_unsigned_to_nat(0u);
v___x_34_ = l_List_finRange(v_n_31_);
v___x_35_ = lp_island__logistics__proof_List_foldrTR___at___00IslandLogistics_finSum_spec__0(v_f_32_, v___x_33_, v___x_34_);
return v___x_35_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___redArg(lean_object* v_x_36_){
_start:
{
lean_object* v___x_37_; 
v___x_37_ = lean_obj_tag_nat(v_x_36_);
return v___x_37_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___redArg___boxed(lean_object* v_x_38_){
_start:
{
lean_object* v_res_39_; 
v_res_39_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___redArg(v_x_38_);
lean_dec_ref(v_x_38_);
return v_res_39_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl(lean_object* v_I_40_, lean_object* v_x_41_){
_start:
{
lean_object* v___x_42_; 
v___x_42_ = lean_obj_tag_nat(v_x_41_);
return v___x_42_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl___boxed(lean_object* v_I_43_, lean_object* v_x_44_){
_start:
{
lean_object* v_res_45_; 
v_res_45_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorIdx___impl(v_I_43_, v_x_44_);
lean_dec_ref(v_x_44_);
lean_dec_ref(v_I_43_);
return v_res_45_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(lean_object* v_t_46_, lean_object* v_k_47_){
_start:
{
lean_object* v_l_48_; lean_object* v___x_49_; 
v_l_48_ = lean_ctor_get(v_t_46_, 0);
lean_inc(v_l_48_);
lean_dec_ref(v_t_46_);
v___x_49_ = lean_apply_1(v_k_47_, v_l_48_);
return v___x_49_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim(lean_object* v_I_50_, lean_object* v_motive_51_, lean_object* v_ctorIdx_52_, lean_object* v_t_53_, lean_object* v_h_54_, lean_object* v_k_55_){
_start:
{
lean_object* v___x_56_; 
v___x_56_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(v_t_53_, v_k_55_);
return v___x_56_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___boxed(lean_object* v_I_57_, lean_object* v_motive_58_, lean_object* v_ctorIdx_59_, lean_object* v_t_60_, lean_object* v_h_61_, lean_object* v_k_62_){
_start:
{
lean_object* v_res_63_; 
v_res_63_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim(v_I_57_, v_motive_58_, v_ctorIdx_59_, v_t_60_, v_h_61_, v_k_62_);
lean_dec(v_ctorIdx_59_);
lean_dec_ref(v_I_57_);
return v_res_63_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim___redArg(lean_object* v_t_64_, lean_object* v_atLoc_65_){
_start:
{
lean_object* v___x_66_; 
v___x_66_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(v_t_64_, v_atLoc_65_);
return v___x_66_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim(lean_object* v_I_67_, lean_object* v_motive_68_, lean_object* v_t_69_, lean_object* v_h_70_, lean_object* v_atLoc_71_){
_start:
{
lean_object* v___x_72_; 
v___x_72_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(v_t_69_, v_atLoc_71_);
return v___x_72_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim___boxed(lean_object* v_I_73_, lean_object* v_motive_74_, lean_object* v_t_75_, lean_object* v_h_76_, lean_object* v_atLoc_77_){
_start:
{
lean_object* v_res_78_; 
v_res_78_ = lp_island__logistics__proof_IslandLogistics_TruckPos_atLoc_elim(v_I_73_, v_motive_74_, v_t_75_, v_h_76_, v_atLoc_77_);
lean_dec_ref(v_I_73_);
return v_res_78_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim___redArg(lean_object* v_t_79_, lean_object* v_onFerry_80_){
_start:
{
lean_object* v___x_81_; 
v___x_81_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(v_t_79_, v_onFerry_80_);
return v___x_81_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim(lean_object* v_I_82_, lean_object* v_motive_83_, lean_object* v_t_84_, lean_object* v_h_85_, lean_object* v_onFerry_86_){
_start:
{
lean_object* v___x_87_; 
v___x_87_ = lp_island__logistics__proof_IslandLogistics_TruckPos_ctorElim___redArg(v_t_84_, v_onFerry_86_);
return v___x_87_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim___boxed(lean_object* v_I_88_, lean_object* v_motive_89_, lean_object* v_t_90_, lean_object* v_h_91_, lean_object* v_onFerry_92_){
_start:
{
lean_object* v_res_93_; 
v_res_93_ = lp_island__logistics__proof_IslandLogistics_TruckPos_onFerry_elim(v_I_88_, v_motive_89_, v_t_90_, v_h_91_, v_onFerry_92_);
lean_dec_ref(v_I_88_);
return v_res_93_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(lean_object* v_x_94_, lean_object* v_x_95_){
_start:
{
if (lean_obj_tag(v_x_94_) == 0)
{
if (lean_obj_tag(v_x_95_) == 0)
{
lean_object* v_l_96_; lean_object* v_l_97_; uint8_t v___x_98_; 
v_l_96_ = lean_ctor_get(v_x_94_, 0);
v_l_97_ = lean_ctor_get(v_x_95_, 0);
v___x_98_ = lean_nat_dec_eq(v_l_96_, v_l_97_);
return v___x_98_;
}
else
{
uint8_t v___x_99_; 
v___x_99_ = 0;
return v___x_99_;
}
}
else
{
if (lean_obj_tag(v_x_95_) == 0)
{
uint8_t v___x_100_; 
v___x_100_ = 0;
return v___x_100_;
}
else
{
lean_object* v_f_101_; lean_object* v_f_102_; uint8_t v___x_103_; 
v_f_101_ = lean_ctor_get(v_x_94_, 0);
v_f_102_ = lean_ctor_get(v_x_95_, 0);
v___x_103_ = lean_nat_dec_eq(v_f_101_, v_f_102_);
return v___x_103_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg___boxed(lean_object* v_x_104_, lean_object* v_x_105_){
_start:
{
uint8_t v_res_106_; lean_object* v_r_107_; 
v_res_106_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(v_x_104_, v_x_105_);
lean_dec_ref(v_x_105_);
lean_dec_ref(v_x_104_);
v_r_107_ = lean_box(v_res_106_);
return v_r_107_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq(lean_object* v_I_108_, lean_object* v_x_109_, lean_object* v_x_110_){
_start:
{
uint8_t v___x_111_; 
v___x_111_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(v_x_109_, v_x_110_);
return v___x_111_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___boxed(lean_object* v_I_112_, lean_object* v_x_113_, lean_object* v_x_114_){
_start:
{
uint8_t v_res_115_; lean_object* v_r_116_; 
v_res_115_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq(v_I_112_, v_x_113_, v_x_114_);
lean_dec_ref(v_x_114_);
lean_dec_ref(v_x_113_);
lean_dec_ref(v_I_112_);
v_r_116_ = lean_box(v_res_115_);
return v_r_116_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___redArg(lean_object* v_x_117_, lean_object* v_x_118_){
_start:
{
uint8_t v___x_119_; 
v___x_119_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(v_x_117_, v_x_118_);
return v___x_119_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___redArg___boxed(lean_object* v_x_120_, lean_object* v_x_121_){
_start:
{
uint8_t v_res_122_; lean_object* v_r_123_; 
v_res_122_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___redArg(v_x_120_, v_x_121_);
lean_dec_ref(v_x_121_);
lean_dec_ref(v_x_120_);
v_r_123_ = lean_box(v_res_122_);
return v_r_123_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos(lean_object* v_I_124_, lean_object* v_x_125_, lean_object* v_x_126_){
_start:
{
uint8_t v___x_127_; 
v___x_127_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(v_x_125_, v_x_126_);
return v___x_127_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos___boxed(lean_object* v_I_128_, lean_object* v_x_129_, lean_object* v_x_130_){
_start:
{
uint8_t v_res_131_; lean_object* v_r_132_; 
v_res_131_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos(v_I_128_, v_x_129_, v_x_130_);
lean_dec_ref(v_x_130_);
lean_dec_ref(v_x_129_);
lean_dec_ref(v_I_128_);
v_r_132_ = lean_box(v_res_131_);
return v_r_132_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___redArg(lean_object* v_x_133_){
_start:
{
lean_object* v___x_134_; 
v___x_134_ = lean_obj_tag_nat(v_x_133_);
return v___x_134_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___redArg___boxed(lean_object* v_x_135_){
_start:
{
lean_object* v_res_136_; 
v_res_136_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___redArg(v_x_135_);
lean_dec_ref(v_x_135_);
return v_res_136_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl(lean_object* v_I_137_, lean_object* v_x_138_){
_start:
{
lean_object* v___x_139_; 
v___x_139_ = lean_obj_tag_nat(v_x_138_);
return v___x_139_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl___boxed(lean_object* v_I_140_, lean_object* v_x_141_){
_start:
{
lean_object* v_res_142_; 
v_res_142_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorIdx___impl(v_I_140_, v_x_141_);
lean_dec_ref(v_x_141_);
lean_dec_ref(v_I_140_);
return v_res_142_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(lean_object* v_t_143_, lean_object* v_k_144_){
_start:
{
lean_object* v_l_145_; lean_object* v___x_146_; 
v_l_145_ = lean_ctor_get(v_t_143_, 0);
lean_inc(v_l_145_);
lean_dec_ref(v_t_143_);
v___x_146_ = lean_apply_1(v_k_144_, v_l_145_);
return v___x_146_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim(lean_object* v_I_147_, lean_object* v_motive_148_, lean_object* v_ctorIdx_149_, lean_object* v_t_150_, lean_object* v_h_151_, lean_object* v_k_152_){
_start:
{
lean_object* v___x_153_; 
v___x_153_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(v_t_150_, v_k_152_);
return v___x_153_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___boxed(lean_object* v_I_154_, lean_object* v_motive_155_, lean_object* v_ctorIdx_156_, lean_object* v_t_157_, lean_object* v_h_158_, lean_object* v_k_159_){
_start:
{
lean_object* v_res_160_; 
v_res_160_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim(v_I_154_, v_motive_155_, v_ctorIdx_156_, v_t_157_, v_h_158_, v_k_159_);
lean_dec(v_ctorIdx_156_);
lean_dec_ref(v_I_154_);
return v_res_160_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim___redArg(lean_object* v_t_161_, lean_object* v_atLoc_162_){
_start:
{
lean_object* v___x_163_; 
v___x_163_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(v_t_161_, v_atLoc_162_);
return v___x_163_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim(lean_object* v_I_164_, lean_object* v_motive_165_, lean_object* v_t_166_, lean_object* v_h_167_, lean_object* v_atLoc_168_){
_start:
{
lean_object* v___x_169_; 
v___x_169_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(v_t_166_, v_atLoc_168_);
return v___x_169_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim___boxed(lean_object* v_I_170_, lean_object* v_motive_171_, lean_object* v_t_172_, lean_object* v_h_173_, lean_object* v_atLoc_174_){
_start:
{
lean_object* v_res_175_; 
v_res_175_ = lp_island__logistics__proof_IslandLogistics_PkgPos_atLoc_elim(v_I_170_, v_motive_171_, v_t_172_, v_h_173_, v_atLoc_174_);
lean_dec_ref(v_I_170_);
return v_res_175_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim___redArg(lean_object* v_t_176_, lean_object* v_inTruck_177_){
_start:
{
lean_object* v___x_178_; 
v___x_178_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(v_t_176_, v_inTruck_177_);
return v___x_178_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim(lean_object* v_I_179_, lean_object* v_motive_180_, lean_object* v_t_181_, lean_object* v_h_182_, lean_object* v_inTruck_183_){
_start:
{
lean_object* v___x_184_; 
v___x_184_ = lp_island__logistics__proof_IslandLogistics_PkgPos_ctorElim___redArg(v_t_181_, v_inTruck_183_);
return v___x_184_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim___boxed(lean_object* v_I_185_, lean_object* v_motive_186_, lean_object* v_t_187_, lean_object* v_h_188_, lean_object* v_inTruck_189_){
_start:
{
lean_object* v_res_190_; 
v_res_190_ = lp_island__logistics__proof_IslandLogistics_PkgPos_inTruck_elim(v_I_185_, v_motive_186_, v_t_187_, v_h_188_, v_inTruck_189_);
lean_dec_ref(v_I_185_);
return v_res_190_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(lean_object* v_x_191_, lean_object* v_x_192_){
_start:
{
if (lean_obj_tag(v_x_191_) == 0)
{
if (lean_obj_tag(v_x_192_) == 0)
{
lean_object* v_l_193_; lean_object* v_l_194_; uint8_t v___x_195_; 
v_l_193_ = lean_ctor_get(v_x_191_, 0);
v_l_194_ = lean_ctor_get(v_x_192_, 0);
v___x_195_ = lean_nat_dec_eq(v_l_193_, v_l_194_);
return v___x_195_;
}
else
{
uint8_t v___x_196_; 
v___x_196_ = 0;
return v___x_196_;
}
}
else
{
if (lean_obj_tag(v_x_192_) == 0)
{
uint8_t v___x_197_; 
v___x_197_ = 0;
return v___x_197_;
}
else
{
lean_object* v_t_198_; lean_object* v_t_199_; uint8_t v___x_200_; 
v_t_198_ = lean_ctor_get(v_x_191_, 0);
v_t_199_ = lean_ctor_get(v_x_192_, 0);
v___x_200_ = lean_nat_dec_eq(v_t_198_, v_t_199_);
return v___x_200_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg___boxed(lean_object* v_x_201_, lean_object* v_x_202_){
_start:
{
uint8_t v_res_203_; lean_object* v_r_204_; 
v_res_203_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v_x_201_, v_x_202_);
lean_dec_ref(v_x_202_);
lean_dec_ref(v_x_201_);
v_r_204_ = lean_box(v_res_203_);
return v_r_204_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq(lean_object* v_I_205_, lean_object* v_x_206_, lean_object* v_x_207_){
_start:
{
uint8_t v___x_208_; 
v___x_208_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v_x_206_, v_x_207_);
return v___x_208_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___boxed(lean_object* v_I_209_, lean_object* v_x_210_, lean_object* v_x_211_){
_start:
{
uint8_t v_res_212_; lean_object* v_r_213_; 
v_res_212_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq(v_I_209_, v_x_210_, v_x_211_);
lean_dec_ref(v_x_211_);
lean_dec_ref(v_x_210_);
lean_dec_ref(v_I_209_);
v_r_213_ = lean_box(v_res_212_);
return v_r_213_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___redArg(lean_object* v_x_214_, lean_object* v_x_215_){
_start:
{
uint8_t v___x_216_; 
v___x_216_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v_x_214_, v_x_215_);
return v___x_216_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___redArg___boxed(lean_object* v_x_217_, lean_object* v_x_218_){
_start:
{
uint8_t v_res_219_; lean_object* v_r_220_; 
v_res_219_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___redArg(v_x_217_, v_x_218_);
lean_dec_ref(v_x_218_);
lean_dec_ref(v_x_217_);
v_r_220_ = lean_box(v_res_219_);
return v_r_220_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos(lean_object* v_I_221_, lean_object* v_x_222_, lean_object* v_x_223_){
_start:
{
uint8_t v___x_224_; 
v___x_224_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v_x_222_, v_x_223_);
return v___x_224_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos___boxed(lean_object* v_I_225_, lean_object* v_x_226_, lean_object* v_x_227_){
_start:
{
uint8_t v_res_228_; lean_object* v_r_229_; 
v_res_228_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos(v_I_225_, v_x_226_, v_x_227_);
lean_dec_ref(v_x_227_);
lean_dec_ref(v_x_226_);
lean_dec_ref(v_I_225_);
v_r_229_ = lean_box(v_res_228_);
return v_r_229_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(lean_object* v_s_230_, lean_object* v_t_231_){
_start:
{
lean_object* v_truckLoc_232_; lean_object* v_ferryLoc_233_; lean_object* v___x_234_; 
v_truckLoc_232_ = lean_ctor_get(v_s_230_, 0);
lean_inc_ref(v_truckLoc_232_);
v_ferryLoc_233_ = lean_ctor_get(v_s_230_, 1);
lean_inc_ref(v_ferryLoc_233_);
lean_dec_ref(v_s_230_);
v___x_234_ = lean_apply_1(v_truckLoc_232_, v_t_231_);
if (lean_obj_tag(v___x_234_) == 0)
{
lean_object* v_l_235_; 
lean_dec_ref(v_ferryLoc_233_);
v_l_235_ = lean_ctor_get(v___x_234_, 0);
lean_inc(v_l_235_);
lean_dec_ref_known(v___x_234_, 1);
return v_l_235_;
}
else
{
lean_object* v_f_236_; lean_object* v___x_237_; 
v_f_236_ = lean_ctor_get(v___x_234_, 0);
lean_inc(v_f_236_);
lean_dec_ref_known(v___x_234_, 1);
v___x_237_ = lean_apply_1(v_ferryLoc_233_, v_f_236_);
return v___x_237_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc(lean_object* v_I_238_, lean_object* v_s_239_, lean_object* v_t_240_){
_start:
{
lean_object* v___x_241_; 
v___x_241_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_239_, v_t_240_);
return v___x_241_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___boxed(lean_object* v_I_242_, lean_object* v_s_243_, lean_object* v_t_244_){
_start:
{
lean_object* v_res_245_; 
v_res_245_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc(v_I_242_, v_s_243_, v_t_244_);
lean_dec_ref(v_I_242_);
return v_res_245_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(lean_object* v_s_246_, lean_object* v_t_247_){
_start:
{
lean_object* v_truckLoc_248_; lean_object* v___x_249_; 
v_truckLoc_248_ = lean_ctor_get(v_s_246_, 0);
lean_inc_ref(v_truckLoc_248_);
lean_dec_ref(v_s_246_);
v___x_249_ = lean_apply_1(v_truckLoc_248_, v_t_247_);
if (lean_obj_tag(v___x_249_) == 0)
{
lean_object* v___x_250_; 
lean_dec_ref_known(v___x_249_, 1);
v___x_250_ = lean_box(0);
return v___x_250_;
}
else
{
lean_object* v_f_251_; lean_object* v___x_253_; uint8_t v_isShared_254_; uint8_t v_isSharedCheck_258_; 
v_f_251_ = lean_ctor_get(v___x_249_, 0);
v_isSharedCheck_258_ = !lean_is_exclusive(v___x_249_);
if (v_isSharedCheck_258_ == 0)
{
v___x_253_ = v___x_249_;
v_isShared_254_ = v_isSharedCheck_258_;
goto v_resetjp_252_;
}
else
{
lean_inc(v_f_251_);
lean_dec(v___x_249_);
v___x_253_ = lean_box(0);
v_isShared_254_ = v_isSharedCheck_258_;
goto v_resetjp_252_;
}
v_resetjp_252_:
{
lean_object* v___x_256_; 
if (v_isShared_254_ == 0)
{
v___x_256_ = v___x_253_;
goto v_reusejp_255_;
}
else
{
lean_object* v_reuseFailAlloc_257_; 
v_reuseFailAlloc_257_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_257_, 0, v_f_251_);
v___x_256_ = v_reuseFailAlloc_257_;
goto v_reusejp_255_;
}
v_reusejp_255_:
{
return v___x_256_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry(lean_object* v_I_259_, lean_object* v_s_260_, lean_object* v_t_261_){
_start:
{
lean_object* v___x_262_; 
v___x_262_ = lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(v_s_260_, v_t_261_);
return v___x_262_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___boxed(lean_object* v_I_263_, lean_object* v_s_264_, lean_object* v_t_265_){
_start:
{
lean_object* v_res_266_; 
v_res_266_ = lp_island__logistics__proof_IslandLogistics_State_truckOnFerry(v_I_263_, v_s_264_, v_t_265_);
lean_dec_ref(v_I_263_);
return v_res_266_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(lean_object* v_s_267_, lean_object* v_p_268_){
_start:
{
lean_object* v_pkgLoc_269_; lean_object* v___x_270_; 
v_pkgLoc_269_ = lean_ctor_get(v_s_267_, 2);
lean_inc_ref(v_pkgLoc_269_);
v___x_270_ = lean_apply_1(v_pkgLoc_269_, v_p_268_);
if (lean_obj_tag(v___x_270_) == 0)
{
lean_object* v_l_271_; 
lean_dec_ref(v_s_267_);
v_l_271_ = lean_ctor_get(v___x_270_, 0);
lean_inc(v_l_271_);
lean_dec_ref_known(v___x_270_, 1);
return v_l_271_;
}
else
{
lean_object* v_t_272_; lean_object* v___x_273_; 
v_t_272_ = lean_ctor_get(v___x_270_, 0);
lean_inc(v_t_272_);
lean_dec_ref_known(v___x_270_, 1);
v___x_273_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_267_, v_t_272_);
return v___x_273_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc(lean_object* v_I_274_, lean_object* v_s_275_, lean_object* v_p_276_){
_start:
{
lean_object* v___x_277_; 
v___x_277_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_275_, v_p_276_);
return v___x_277_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___boxed(lean_object* v_I_278_, lean_object* v_s_279_, lean_object* v_p_280_){
_start:
{
lean_object* v_res_281_; 
v_res_281_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc(v_I_278_, v_s_279_, v_p_280_);
lean_dec_ref(v_I_278_);
return v_res_281_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(lean_object* v_s_282_, lean_object* v_p_283_){
_start:
{
lean_object* v_pkgLoc_284_; lean_object* v___x_285_; 
v_pkgLoc_284_ = lean_ctor_get(v_s_282_, 2);
lean_inc_ref(v_pkgLoc_284_);
v___x_285_ = lean_apply_1(v_pkgLoc_284_, v_p_283_);
if (lean_obj_tag(v___x_285_) == 0)
{
lean_object* v___x_286_; 
lean_dec_ref_known(v___x_285_, 1);
lean_dec_ref(v_s_282_);
v___x_286_ = lean_box(0);
return v___x_286_;
}
else
{
lean_object* v_t_287_; lean_object* v___x_288_; 
v_t_287_ = lean_ctor_get(v___x_285_, 0);
lean_inc(v_t_287_);
lean_dec_ref_known(v___x_285_, 1);
v___x_288_ = lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(v_s_282_, v_t_287_);
return v___x_288_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry(lean_object* v_I_289_, lean_object* v_s_290_, lean_object* v_p_291_){
_start:
{
lean_object* v___x_292_; 
v___x_292_ = lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(v_s_290_, v_p_291_);
return v___x_292_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___boxed(lean_object* v_I_293_, lean_object* v_s_294_, lean_object* v_p_295_){
_start:
{
lean_object* v_res_296_; 
v_res_296_ = lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry(v_I_293_, v_s_294_, v_p_295_);
lean_dec_ref(v_I_293_);
return v_res_296_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(lean_object* v_s_297_, lean_object* v_p_298_){
_start:
{
lean_object* v_pkgLoc_299_; lean_object* v___x_300_; 
v_pkgLoc_299_ = lean_ctor_get(v_s_297_, 2);
lean_inc_ref(v_pkgLoc_299_);
lean_dec_ref(v_s_297_);
v___x_300_ = lean_apply_1(v_pkgLoc_299_, v_p_298_);
if (lean_obj_tag(v___x_300_) == 0)
{
uint8_t v___x_301_; 
lean_dec_ref_known(v___x_300_, 1);
v___x_301_ = 1;
return v___x_301_;
}
else
{
uint8_t v___x_302_; 
lean_dec_ref_known(v___x_300_, 1);
v___x_302_ = 0;
return v___x_302_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg___boxed(lean_object* v_s_303_, lean_object* v_p_304_){
_start:
{
uint8_t v_res_305_; lean_object* v_r_306_; 
v_res_305_ = lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(v_s_303_, v_p_304_);
v_r_306_ = lean_box(v_res_305_);
return v_r_306_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgIsGround(lean_object* v_I_307_, lean_object* v_s_308_, lean_object* v_p_309_){
_start:
{
uint8_t v___x_310_; 
v___x_310_ = lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(v_s_308_, v_p_309_);
return v___x_310_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___boxed(lean_object* v_I_311_, lean_object* v_s_312_, lean_object* v_p_313_){
_start:
{
uint8_t v_res_314_; lean_object* v_r_315_; 
v_res_314_ = lp_island__logistics__proof_IslandLogistics_State_pkgIsGround(v_I_311_, v_s_312_, v_p_313_);
lean_dec_ref(v_I_311_);
v_r_315_ = lean_box(v_res_314_);
return v_r_315_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(lean_object* v_I_316_, lean_object* v_s_317_, lean_object* v_p_318_){
_start:
{
lean_object* v_pkgLoc_319_; lean_object* v_pkgGoal_320_; lean_object* v___x_321_; lean_object* v___x_322_; lean_object* v___x_323_; uint8_t v___x_324_; 
v_pkgLoc_319_ = lean_ctor_get(v_s_317_, 2);
lean_inc_ref(v_pkgLoc_319_);
lean_dec_ref(v_s_317_);
v_pkgGoal_320_ = lean_ctor_get(v_I_316_, 10);
lean_inc_ref(v_pkgGoal_320_);
lean_dec_ref(v_I_316_);
lean_inc(v_p_318_);
v___x_321_ = lean_apply_1(v_pkgLoc_319_, v_p_318_);
v___x_322_ = lean_apply_1(v_pkgGoal_320_, v_p_318_);
v___x_323_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_323_, 0, v___x_322_);
v___x_324_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v___x_321_, v___x_323_);
lean_dec_ref_known(v___x_323_, 1);
lean_dec_ref(v___x_321_);
return v___x_324_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgDelivered___boxed(lean_object* v_I_325_, lean_object* v_s_326_, lean_object* v_p_327_){
_start:
{
uint8_t v_res_328_; lean_object* v_r_329_; 
v_res_328_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_325_, v_s_326_, v_p_327_);
v_r_329_ = lean_box(v_res_328_);
return v_r_329_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckLoad___lam__0(lean_object* v_s_330_, lean_object* v_t_331_, lean_object* v_pkgWeight_332_, lean_object* v_p_333_){
_start:
{
lean_object* v_pkgLoc_334_; lean_object* v___x_335_; lean_object* v___x_336_; uint8_t v___x_337_; 
v_pkgLoc_334_ = lean_ctor_get(v_s_330_, 2);
lean_inc_ref(v_pkgLoc_334_);
lean_dec_ref(v_s_330_);
lean_inc(v_p_333_);
v___x_335_ = lean_apply_1(v_pkgLoc_334_, v_p_333_);
v___x_336_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_336_, 0, v_t_331_);
v___x_337_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v___x_335_, v___x_336_);
lean_dec_ref_known(v___x_336_, 1);
lean_dec_ref(v___x_335_);
if (v___x_337_ == 0)
{
lean_object* v___x_338_; 
lean_dec(v_p_333_);
lean_dec_ref(v_pkgWeight_332_);
v___x_338_ = lean_unsigned_to_nat(0u);
return v___x_338_;
}
else
{
lean_object* v___x_339_; 
v___x_339_ = lean_apply_1(v_pkgWeight_332_, v_p_333_);
return v___x_339_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_truckLoad(lean_object* v_I_340_, lean_object* v_s_341_, lean_object* v_t_342_){
_start:
{
lean_object* v_numPkgs_343_; lean_object* v_pkgWeight_344_; lean_object* v___f_345_; lean_object* v___x_346_; 
v_numPkgs_343_ = lean_ctor_get(v_I_340_, 8);
lean_inc(v_numPkgs_343_);
v_pkgWeight_344_ = lean_ctor_get(v_I_340_, 9);
lean_inc_ref(v_pkgWeight_344_);
lean_dec_ref(v_I_340_);
v___f_345_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_State_truckLoad___lam__0), 4, 3);
lean_closure_set(v___f_345_, 0, v_s_341_);
lean_closure_set(v___f_345_, 1, v_t_342_);
lean_closure_set(v___f_345_, 2, v_pkgWeight_344_);
v___x_346_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_343_, v___f_345_);
return v___x_346_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_ferryCount___lam__0(lean_object* v_s_347_, lean_object* v_f_348_, lean_object* v_t_349_){
_start:
{
lean_object* v_truckLoc_350_; lean_object* v___x_351_; lean_object* v___x_352_; uint8_t v___x_353_; 
v_truckLoc_350_ = lean_ctor_get(v_s_347_, 0);
lean_inc_ref(v_truckLoc_350_);
lean_dec_ref(v_s_347_);
v___x_351_ = lean_apply_1(v_truckLoc_350_, v_t_349_);
v___x_352_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_352_, 0, v_f_348_);
v___x_353_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqTruckPos_decEq___redArg(v___x_351_, v___x_352_);
lean_dec_ref_known(v___x_352_, 1);
lean_dec_ref(v___x_351_);
if (v___x_353_ == 0)
{
lean_object* v___x_354_; 
v___x_354_ = lean_unsigned_to_nat(0u);
return v___x_354_;
}
else
{
lean_object* v___x_355_; 
v___x_355_ = lean_unsigned_to_nat(1u);
return v___x_355_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_State_ferryCount(lean_object* v_I_356_, lean_object* v_s_357_, lean_object* v_f_358_){
_start:
{
lean_object* v_numTrucks_359_; lean_object* v___f_360_; lean_object* v___x_361_; 
v_numTrucks_359_ = lean_ctor_get(v_I_356_, 3);
lean_inc(v_numTrucks_359_);
lean_dec_ref(v_I_356_);
v___f_360_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_State_ferryCount___lam__0), 3, 2);
lean_closure_set(v___f_360_, 0, v_s_357_);
lean_closure_set(v___f_360_, 1, v_f_358_);
v___x_361_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_359_, v___f_360_);
return v___x_361_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___redArg(lean_object* v_f_362_, lean_object* v_k_363_, lean_object* v_v_364_, lean_object* v_i_365_){
_start:
{
uint8_t v___x_366_; 
v___x_366_ = lean_nat_dec_eq(v_i_365_, v_k_363_);
if (v___x_366_ == 0)
{
lean_object* v___x_367_; 
v___x_367_ = lean_apply_1(v_f_362_, v_i_365_);
return v___x_367_;
}
else
{
lean_dec(v_i_365_);
lean_dec(v_f_362_);
lean_inc(v_v_364_);
return v_v_364_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___redArg___boxed(lean_object* v_f_368_, lean_object* v_k_369_, lean_object* v_v_370_, lean_object* v_i_371_){
_start:
{
lean_object* v_res_372_; 
v_res_372_ = lp_island__logistics__proof_IslandLogistics_updateFn___redArg(v_f_368_, v_k_369_, v_v_370_, v_i_371_);
lean_dec(v_v_370_);
lean_dec(v_k_369_);
return v_res_372_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn(lean_object* v_00_u03b1_373_, lean_object* v_n_374_, lean_object* v_f_375_, lean_object* v_k_376_, lean_object* v_v_377_, lean_object* v_i_378_){
_start:
{
lean_object* v___x_379_; 
v___x_379_ = lp_island__logistics__proof_IslandLogistics_updateFn___redArg(v_f_375_, v_k_376_, v_v_377_, v_i_378_);
return v___x_379_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_updateFn___boxed(lean_object* v_00_u03b1_380_, lean_object* v_n_381_, lean_object* v_f_382_, lean_object* v_k_383_, lean_object* v_v_384_, lean_object* v_i_385_){
_start:
{
lean_object* v_res_386_; 
v_res_386_ = lp_island__logistics__proof_IslandLogistics_updateFn(v_00_u03b1_380_, v_n_381_, v_f_382_, v_k_383_, v_v_384_, v_i_385_);
lean_dec(v_v_384_);
lean_dec(v_k_383_);
lean_dec(v_n_381_);
return v_res_386_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___redArg(lean_object* v_x_387_){
_start:
{
lean_object* v___x_388_; 
v___x_388_ = lean_obj_tag_nat(v_x_387_);
return v___x_388_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___redArg___boxed(lean_object* v_x_389_){
_start:
{
lean_object* v_res_390_; 
v_res_390_ = lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___redArg(v_x_389_);
lean_dec_ref(v_x_389_);
return v_res_390_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl(lean_object* v_I_391_, lean_object* v_x_392_){
_start:
{
lean_object* v___x_393_; 
v___x_393_ = lean_obj_tag_nat(v_x_392_);
return v___x_393_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl___boxed(lean_object* v_I_394_, lean_object* v_x_395_){
_start:
{
lean_object* v_res_396_; 
v_res_396_ = lp_island__logistics__proof_IslandLogistics_Action_ctorIdx___impl(v_I_394_, v_x_395_);
lean_dec_ref(v_x_395_);
lean_dec_ref(v_I_394_);
return v_res_396_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(lean_object* v_t_397_, lean_object* v_k_398_){
_start:
{
switch(lean_obj_tag(v_t_397_))
{
case 0:
{
lean_object* v_t_399_; lean_object* v_u_400_; lean_object* v_v_401_; lean_object* v___x_402_; 
v_t_399_ = lean_ctor_get(v_t_397_, 0);
lean_inc(v_t_399_);
v_u_400_ = lean_ctor_get(v_t_397_, 1);
lean_inc(v_u_400_);
v_v_401_ = lean_ctor_get(v_t_397_, 2);
lean_inc(v_v_401_);
lean_dec_ref_known(v_t_397_, 3);
v___x_402_ = lean_apply_3(v_k_398_, v_t_399_, v_u_400_, v_v_401_);
return v___x_402_;
}
case 5:
{
lean_object* v_f_403_; lean_object* v_u_404_; lean_object* v_v_405_; lean_object* v___x_406_; 
v_f_403_ = lean_ctor_get(v_t_397_, 0);
lean_inc(v_f_403_);
v_u_404_ = lean_ctor_get(v_t_397_, 1);
lean_inc(v_u_404_);
v_v_405_ = lean_ctor_get(v_t_397_, 2);
lean_inc(v_v_405_);
lean_dec_ref_known(v_t_397_, 3);
v___x_406_ = lean_apply_3(v_k_398_, v_f_403_, v_u_404_, v_v_405_);
return v___x_406_;
}
default: 
{
lean_object* v_p_407_; lean_object* v_t_408_; lean_object* v___x_409_; 
v_p_407_ = lean_ctor_get(v_t_397_, 0);
lean_inc(v_p_407_);
v_t_408_ = lean_ctor_get(v_t_397_, 1);
lean_inc(v_t_408_);
lean_dec_ref(v_t_397_);
v___x_409_ = lean_apply_2(v_k_398_, v_p_407_, v_t_408_);
return v___x_409_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim(lean_object* v_I_410_, lean_object* v_motive_411_, lean_object* v_ctorIdx_412_, lean_object* v_t_413_, lean_object* v_h_414_, lean_object* v_k_415_){
_start:
{
lean_object* v___x_416_; 
v___x_416_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_413_, v_k_415_);
return v___x_416_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_ctorElim___boxed(lean_object* v_I_417_, lean_object* v_motive_418_, lean_object* v_ctorIdx_419_, lean_object* v_t_420_, lean_object* v_h_421_, lean_object* v_k_422_){
_start:
{
lean_object* v_res_423_; 
v_res_423_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim(v_I_417_, v_motive_418_, v_ctorIdx_419_, v_t_420_, v_h_421_, v_k_422_);
lean_dec(v_ctorIdx_419_);
lean_dec_ref(v_I_417_);
return v_res_423_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim___redArg(lean_object* v_t_424_, lean_object* v_drive_425_){
_start:
{
lean_object* v___x_426_; 
v___x_426_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_424_, v_drive_425_);
return v___x_426_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim(lean_object* v_I_427_, lean_object* v_motive_428_, lean_object* v_t_429_, lean_object* v_h_430_, lean_object* v_drive_431_){
_start:
{
lean_object* v___x_432_; 
v___x_432_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_429_, v_drive_431_);
return v___x_432_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_drive_elim___boxed(lean_object* v_I_433_, lean_object* v_motive_434_, lean_object* v_t_435_, lean_object* v_h_436_, lean_object* v_drive_437_){
_start:
{
lean_object* v_res_438_; 
v_res_438_ = lp_island__logistics__proof_IslandLogistics_Action_drive_elim(v_I_433_, v_motive_434_, v_t_435_, v_h_436_, v_drive_437_);
lean_dec_ref(v_I_433_);
return v_res_438_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim___redArg(lean_object* v_t_439_, lean_object* v_load_440_){
_start:
{
lean_object* v___x_441_; 
v___x_441_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_439_, v_load_440_);
return v___x_441_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim(lean_object* v_I_442_, lean_object* v_motive_443_, lean_object* v_t_444_, lean_object* v_h_445_, lean_object* v_load_446_){
_start:
{
lean_object* v___x_447_; 
v___x_447_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_444_, v_load_446_);
return v___x_447_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_load_elim___boxed(lean_object* v_I_448_, lean_object* v_motive_449_, lean_object* v_t_450_, lean_object* v_h_451_, lean_object* v_load_452_){
_start:
{
lean_object* v_res_453_; 
v_res_453_ = lp_island__logistics__proof_IslandLogistics_Action_load_elim(v_I_448_, v_motive_449_, v_t_450_, v_h_451_, v_load_452_);
lean_dec_ref(v_I_448_);
return v_res_453_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim___redArg(lean_object* v_t_454_, lean_object* v_unload_455_){
_start:
{
lean_object* v___x_456_; 
v___x_456_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_454_, v_unload_455_);
return v___x_456_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim(lean_object* v_I_457_, lean_object* v_motive_458_, lean_object* v_t_459_, lean_object* v_h_460_, lean_object* v_unload_461_){
_start:
{
lean_object* v___x_462_; 
v___x_462_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_459_, v_unload_461_);
return v___x_462_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_unload_elim___boxed(lean_object* v_I_463_, lean_object* v_motive_464_, lean_object* v_t_465_, lean_object* v_h_466_, lean_object* v_unload_467_){
_start:
{
lean_object* v_res_468_; 
v_res_468_ = lp_island__logistics__proof_IslandLogistics_Action_unload_elim(v_I_463_, v_motive_464_, v_t_465_, v_h_466_, v_unload_467_);
lean_dec_ref(v_I_463_);
return v_res_468_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim___redArg(lean_object* v_t_469_, lean_object* v_board_470_){
_start:
{
lean_object* v___x_471_; 
v___x_471_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_469_, v_board_470_);
return v___x_471_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim(lean_object* v_I_472_, lean_object* v_motive_473_, lean_object* v_t_474_, lean_object* v_h_475_, lean_object* v_board_476_){
_start:
{
lean_object* v___x_477_; 
v___x_477_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_474_, v_board_476_);
return v___x_477_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_board_elim___boxed(lean_object* v_I_478_, lean_object* v_motive_479_, lean_object* v_t_480_, lean_object* v_h_481_, lean_object* v_board_482_){
_start:
{
lean_object* v_res_483_; 
v_res_483_ = lp_island__logistics__proof_IslandLogistics_Action_board_elim(v_I_478_, v_motive_479_, v_t_480_, v_h_481_, v_board_482_);
lean_dec_ref(v_I_478_);
return v_res_483_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim___redArg(lean_object* v_t_484_, lean_object* v_disembark_485_){
_start:
{
lean_object* v___x_486_; 
v___x_486_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_484_, v_disembark_485_);
return v___x_486_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim(lean_object* v_I_487_, lean_object* v_motive_488_, lean_object* v_t_489_, lean_object* v_h_490_, lean_object* v_disembark_491_){
_start:
{
lean_object* v___x_492_; 
v___x_492_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_489_, v_disembark_491_);
return v___x_492_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_disembark_elim___boxed(lean_object* v_I_493_, lean_object* v_motive_494_, lean_object* v_t_495_, lean_object* v_h_496_, lean_object* v_disembark_497_){
_start:
{
lean_object* v_res_498_; 
v_res_498_ = lp_island__logistics__proof_IslandLogistics_Action_disembark_elim(v_I_493_, v_motive_494_, v_t_495_, v_h_496_, v_disembark_497_);
lean_dec_ref(v_I_493_);
return v_res_498_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim___redArg(lean_object* v_t_499_, lean_object* v_sail_500_){
_start:
{
lean_object* v___x_501_; 
v___x_501_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_499_, v_sail_500_);
return v___x_501_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim(lean_object* v_I_502_, lean_object* v_motive_503_, lean_object* v_t_504_, lean_object* v_h_505_, lean_object* v_sail_506_){
_start:
{
lean_object* v___x_507_; 
v___x_507_ = lp_island__logistics__proof_IslandLogistics_Action_ctorElim___redArg(v_t_504_, v_sail_506_);
return v___x_507_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_Action_sail_elim___boxed(lean_object* v_I_508_, lean_object* v_motive_509_, lean_object* v_t_510_, lean_object* v_h_511_, lean_object* v_sail_512_){
_start:
{
lean_object* v_res_513_; 
v_res_513_ = lp_island__logistics__proof_IslandLogistics_Action_sail_elim(v_I_508_, v_motive_509_, v_t_510_, v_h_511_, v_sail_512_);
lean_dec_ref(v_I_508_);
return v_res_513_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(lean_object* v_x_514_, lean_object* v_x_515_){
_start:
{
switch(lean_obj_tag(v_x_514_))
{
case 0:
{
if (lean_obj_tag(v_x_515_) == 0)
{
lean_object* v_t_516_; lean_object* v_u_517_; lean_object* v_v_518_; lean_object* v_t_519_; lean_object* v_u_520_; lean_object* v_v_521_; uint8_t v___x_522_; 
v_t_516_ = lean_ctor_get(v_x_514_, 0);
v_u_517_ = lean_ctor_get(v_x_514_, 1);
v_v_518_ = lean_ctor_get(v_x_514_, 2);
v_t_519_ = lean_ctor_get(v_x_515_, 0);
v_u_520_ = lean_ctor_get(v_x_515_, 1);
v_v_521_ = lean_ctor_get(v_x_515_, 2);
v___x_522_ = lean_nat_dec_eq(v_t_516_, v_t_519_);
if (v___x_522_ == 0)
{
return v___x_522_;
}
else
{
uint8_t v___x_523_; 
v___x_523_ = lean_nat_dec_eq(v_u_517_, v_u_520_);
if (v___x_523_ == 0)
{
return v___x_523_;
}
else
{
uint8_t v___x_524_; 
v___x_524_ = lean_nat_dec_eq(v_v_518_, v_v_521_);
return v___x_524_;
}
}
}
else
{
uint8_t v___x_525_; 
v___x_525_ = 0;
return v___x_525_;
}
}
case 1:
{
if (lean_obj_tag(v_x_515_) == 1)
{
lean_object* v_p_526_; lean_object* v_t_527_; lean_object* v_p_528_; lean_object* v_t_529_; uint8_t v___x_530_; 
v_p_526_ = lean_ctor_get(v_x_514_, 0);
v_t_527_ = lean_ctor_get(v_x_514_, 1);
v_p_528_ = lean_ctor_get(v_x_515_, 0);
v_t_529_ = lean_ctor_get(v_x_515_, 1);
v___x_530_ = lean_nat_dec_eq(v_p_526_, v_p_528_);
if (v___x_530_ == 0)
{
return v___x_530_;
}
else
{
uint8_t v___x_531_; 
v___x_531_ = lean_nat_dec_eq(v_t_527_, v_t_529_);
return v___x_531_;
}
}
else
{
uint8_t v___x_532_; 
v___x_532_ = 0;
return v___x_532_;
}
}
case 2:
{
if (lean_obj_tag(v_x_515_) == 2)
{
lean_object* v_p_533_; lean_object* v_t_534_; lean_object* v_p_535_; lean_object* v_t_536_; uint8_t v___x_537_; 
v_p_533_ = lean_ctor_get(v_x_514_, 0);
v_t_534_ = lean_ctor_get(v_x_514_, 1);
v_p_535_ = lean_ctor_get(v_x_515_, 0);
v_t_536_ = lean_ctor_get(v_x_515_, 1);
v___x_537_ = lean_nat_dec_eq(v_p_533_, v_p_535_);
if (v___x_537_ == 0)
{
return v___x_537_;
}
else
{
uint8_t v___x_538_; 
v___x_538_ = lean_nat_dec_eq(v_t_534_, v_t_536_);
return v___x_538_;
}
}
else
{
uint8_t v___x_539_; 
v___x_539_ = 0;
return v___x_539_;
}
}
case 3:
{
if (lean_obj_tag(v_x_515_) == 3)
{
lean_object* v_t_540_; lean_object* v_f_541_; lean_object* v_t_542_; lean_object* v_f_543_; uint8_t v___x_544_; 
v_t_540_ = lean_ctor_get(v_x_514_, 0);
v_f_541_ = lean_ctor_get(v_x_514_, 1);
v_t_542_ = lean_ctor_get(v_x_515_, 0);
v_f_543_ = lean_ctor_get(v_x_515_, 1);
v___x_544_ = lean_nat_dec_eq(v_t_540_, v_t_542_);
if (v___x_544_ == 0)
{
return v___x_544_;
}
else
{
uint8_t v___x_545_; 
v___x_545_ = lean_nat_dec_eq(v_f_541_, v_f_543_);
return v___x_545_;
}
}
else
{
uint8_t v___x_546_; 
v___x_546_ = 0;
return v___x_546_;
}
}
case 4:
{
if (lean_obj_tag(v_x_515_) == 4)
{
lean_object* v_t_547_; lean_object* v_f_548_; lean_object* v_t_549_; lean_object* v_f_550_; uint8_t v___x_551_; 
v_t_547_ = lean_ctor_get(v_x_514_, 0);
v_f_548_ = lean_ctor_get(v_x_514_, 1);
v_t_549_ = lean_ctor_get(v_x_515_, 0);
v_f_550_ = lean_ctor_get(v_x_515_, 1);
v___x_551_ = lean_nat_dec_eq(v_t_547_, v_t_549_);
if (v___x_551_ == 0)
{
return v___x_551_;
}
else
{
uint8_t v___x_552_; 
v___x_552_ = lean_nat_dec_eq(v_f_548_, v_f_550_);
return v___x_552_;
}
}
else
{
uint8_t v___x_553_; 
v___x_553_ = 0;
return v___x_553_;
}
}
default: 
{
if (lean_obj_tag(v_x_515_) == 5)
{
lean_object* v_f_554_; lean_object* v_u_555_; lean_object* v_v_556_; lean_object* v_f_557_; lean_object* v_u_558_; lean_object* v_v_559_; uint8_t v___x_560_; 
v_f_554_ = lean_ctor_get(v_x_514_, 0);
v_u_555_ = lean_ctor_get(v_x_514_, 1);
v_v_556_ = lean_ctor_get(v_x_514_, 2);
v_f_557_ = lean_ctor_get(v_x_515_, 0);
v_u_558_ = lean_ctor_get(v_x_515_, 1);
v_v_559_ = lean_ctor_get(v_x_515_, 2);
v___x_560_ = lean_nat_dec_eq(v_f_554_, v_f_557_);
if (v___x_560_ == 0)
{
return v___x_560_;
}
else
{
uint8_t v___x_561_; 
v___x_561_ = lean_nat_dec_eq(v_u_555_, v_u_558_);
if (v___x_561_ == 0)
{
return v___x_561_;
}
else
{
uint8_t v___x_562_; 
v___x_562_ = lean_nat_dec_eq(v_v_556_, v_v_559_);
return v___x_562_;
}
}
}
else
{
uint8_t v___x_563_; 
v___x_563_ = 0;
return v___x_563_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg___boxed(lean_object* v_x_564_, lean_object* v_x_565_){
_start:
{
uint8_t v_res_566_; lean_object* v_r_567_; 
v_res_566_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(v_x_564_, v_x_565_);
lean_dec_ref(v_x_565_);
lean_dec_ref(v_x_564_);
v_r_567_ = lean_box(v_res_566_);
return v_r_567_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq(lean_object* v_I_568_, lean_object* v_x_569_, lean_object* v_x_570_){
_start:
{
uint8_t v___x_571_; 
v___x_571_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(v_x_569_, v_x_570_);
return v___x_571_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___boxed(lean_object* v_I_572_, lean_object* v_x_573_, lean_object* v_x_574_){
_start:
{
uint8_t v_res_575_; lean_object* v_r_576_; 
v_res_575_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq(v_I_572_, v_x_573_, v_x_574_);
lean_dec_ref(v_x_574_);
lean_dec_ref(v_x_573_);
lean_dec_ref(v_I_572_);
v_r_576_ = lean_box(v_res_575_);
return v_r_576_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___redArg(lean_object* v_x_577_, lean_object* v_x_578_){
_start:
{
uint8_t v___x_579_; 
v___x_579_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(v_x_577_, v_x_578_);
return v___x_579_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___redArg___boxed(lean_object* v_x_580_, lean_object* v_x_581_){
_start:
{
uint8_t v_res_582_; lean_object* v_r_583_; 
v_res_582_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___redArg(v_x_580_, v_x_581_);
lean_dec_ref(v_x_581_);
lean_dec_ref(v_x_580_);
v_r_583_ = lean_box(v_res_582_);
return v_r_583_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqAction(lean_object* v_I_584_, lean_object* v_x_585_, lean_object* v_x_586_){
_start:
{
uint8_t v___x_587_; 
v___x_587_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction_decEq___redArg(v_x_585_, v_x_586_);
return v___x_587_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqAction___boxed(lean_object* v_I_588_, lean_object* v_x_589_, lean_object* v_x_590_){
_start:
{
uint8_t v_res_591_; lean_object* v_r_592_; 
v_res_591_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqAction(v_I_588_, v_x_589_, v_x_590_);
lean_dec_ref(v_x_590_);
lean_dec_ref(v_x_589_);
lean_dec_ref(v_I_588_);
v_r_592_ = lean_box(v_res_591_);
return v_r_592_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___redArg(lean_object* v_x_593_){
_start:
{
if (lean_obj_tag(v_x_593_) == 5)
{
lean_object* v___x_594_; 
v___x_594_ = lean_unsigned_to_nat(3u);
return v___x_594_;
}
else
{
lean_object* v___x_595_; 
v___x_595_ = lean_unsigned_to_nat(1u);
return v___x_595_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___redArg___boxed(lean_object* v_x_596_){
_start:
{
lean_object* v_res_597_; 
v_res_597_ = lp_island__logistics__proof_IslandLogistics_actionCost___redArg(v_x_596_);
lean_dec_ref(v_x_596_);
return v_res_597_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost(lean_object* v_I_598_, lean_object* v_x_599_){
_start:
{
lean_object* v___x_600_; 
v___x_600_ = lp_island__logistics__proof_IslandLogistics_actionCost___redArg(v_x_599_);
return v___x_600_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCost___boxed(lean_object* v_I_601_, lean_object* v_x_602_){
_start:
{
lean_object* v_res_603_; 
v_res_603_ = lp_island__logistics__proof_IslandLogistics_actionCost(v_I_601_, v_x_602_);
lean_dec_ref(v_x_602_);
lean_dec_ref(v_I_601_);
return v_res_603_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg(lean_object* v_x_604_){
_start:
{
switch(lean_obj_tag(v_x_604_))
{
case 1:
{
lean_object* v___x_605_; 
v___x_605_ = lean_unsigned_to_nat(1u);
return v___x_605_;
}
case 2:
{
lean_object* v___x_606_; 
v___x_606_ = lean_unsigned_to_nat(1u);
return v___x_606_;
}
default: 
{
lean_object* v___x_607_; 
v___x_607_ = lean_unsigned_to_nat(0u);
return v___x_607_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg___boxed(lean_object* v_x_608_){
_start:
{
lean_object* v_res_609_; 
v_res_609_ = lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg(v_x_608_);
lean_dec_ref(v_x_608_);
return v_res_609_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU(lean_object* v_I_610_, lean_object* v_x_611_){
_start:
{
lean_object* v___x_612_; 
v___x_612_ = lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg(v_x_611_);
return v___x_612_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostLU___boxed(lean_object* v_I_613_, lean_object* v_x_614_){
_start:
{
lean_object* v_res_615_; 
v_res_615_ = lp_island__logistics__proof_IslandLogistics_actionCostLU(v_I_613_, v_x_614_);
lean_dec_ref(v_x_614_);
lean_dec_ref(v_I_613_);
return v_res_615_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg(lean_object* v_x_616_){
_start:
{
if (lean_obj_tag(v_x_616_) == 0)
{
lean_object* v___x_617_; 
v___x_617_ = lean_unsigned_to_nat(1u);
return v___x_617_;
}
else
{
lean_object* v___x_618_; 
v___x_618_ = lean_unsigned_to_nat(0u);
return v___x_618_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg___boxed(lean_object* v_x_619_){
_start:
{
lean_object* v_res_620_; 
v_res_620_ = lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg(v_x_619_);
lean_dec_ref(v_x_619_);
return v_res_620_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive(lean_object* v_I_621_, lean_object* v_x_622_){
_start:
{
lean_object* v___x_623_; 
v___x_623_ = lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg(v_x_622_);
return v___x_623_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostDrive___boxed(lean_object* v_I_624_, lean_object* v_x_625_){
_start:
{
lean_object* v_res_626_; 
v_res_626_ = lp_island__logistics__proof_IslandLogistics_actionCostDrive(v_I_624_, v_x_625_);
lean_dec_ref(v_x_625_);
lean_dec_ref(v_I_624_);
return v_res_626_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg(lean_object* v_x_627_){
_start:
{
switch(lean_obj_tag(v_x_627_))
{
case 3:
{
lean_object* v___x_628_; 
v___x_628_ = lean_unsigned_to_nat(1u);
return v___x_628_;
}
case 4:
{
lean_object* v___x_629_; 
v___x_629_ = lean_unsigned_to_nat(1u);
return v___x_629_;
}
default: 
{
lean_object* v___x_630_; 
v___x_630_ = lean_unsigned_to_nat(0u);
return v___x_630_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg___boxed(lean_object* v_x_631_){
_start:
{
lean_object* v_res_632_; 
v_res_632_ = lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg(v_x_631_);
lean_dec_ref(v_x_631_);
return v_res_632_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD(lean_object* v_I_633_, lean_object* v_x_634_){
_start:
{
lean_object* v___x_635_; 
v___x_635_ = lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg(v_x_634_);
return v___x_635_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostBD___boxed(lean_object* v_I_636_, lean_object* v_x_637_){
_start:
{
lean_object* v_res_638_; 
v_res_638_ = lp_island__logistics__proof_IslandLogistics_actionCostBD(v_I_636_, v_x_637_);
lean_dec_ref(v_x_637_);
lean_dec_ref(v_I_636_);
return v_res_638_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg(lean_object* v_x_639_){
_start:
{
if (lean_obj_tag(v_x_639_) == 5)
{
lean_object* v___x_640_; 
v___x_640_ = lean_unsigned_to_nat(3u);
return v___x_640_;
}
else
{
lean_object* v___x_641_; 
v___x_641_ = lean_unsigned_to_nat(0u);
return v___x_641_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg___boxed(lean_object* v_x_642_){
_start:
{
lean_object* v_res_643_; 
v_res_643_ = lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg(v_x_642_);
lean_dec_ref(v_x_642_);
return v_res_643_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail(lean_object* v_I_644_, lean_object* v_x_645_){
_start:
{
lean_object* v___x_646_; 
v___x_646_ = lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg(v_x_645_);
return v___x_646_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_actionCostSail___boxed(lean_object* v_I_647_, lean_object* v_x_648_){
_start:
{
lean_object* v_res_649_; 
v_res_649_ = lp_island__logistics__proof_IslandLogistics_actionCostSail(v_I_647_, v_x_648_);
lean_dec_ref(v_x_648_);
lean_dec_ref(v_I_647_);
return v_res_649_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1(lean_object* v_init_650_, lean_object* v_x_651_){
_start:
{
if (lean_obj_tag(v_x_651_) == 0)
{
lean_inc(v_init_650_);
return v_init_650_;
}
else
{
lean_object* v_head_652_; lean_object* v_tail_653_; lean_object* v___x_654_; lean_object* v___x_655_; 
v_head_652_ = lean_ctor_get(v_x_651_, 0);
v_tail_653_ = lean_ctor_get(v_x_651_, 1);
v___x_654_ = lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1(v_init_650_, v_tail_653_);
v___x_655_ = lean_nat_add(v_head_652_, v___x_654_);
lean_dec(v___x_654_);
return v___x_655_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1___boxed(lean_object* v_init_656_, lean_object* v_x_657_){
_start:
{
lean_object* v_res_658_; 
v_res_658_ = lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1(v_init_656_, v_x_657_);
lean_dec(v_x_657_);
lean_dec(v_init_656_);
return v_res_658_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(lean_object* v_l_659_){
_start:
{
lean_object* v___x_660_; lean_object* v___x_661_; 
v___x_660_ = lean_unsigned_to_nat(0u);
v___x_661_ = lp_island__logistics__proof_List_foldr___at___00List_sum___at___00IslandLogistics_planCost_spec__1_spec__1(v___x_660_, v_l_659_);
return v___x_661_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1___boxed(lean_object* v_l_662_){
_start:
{
lean_object* v_res_663_; 
v_res_663_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v_l_662_);
lean_dec(v_l_662_);
return v_res_663_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___redArg(lean_object* v_a_664_, lean_object* v_a_665_){
_start:
{
if (lean_obj_tag(v_a_664_) == 0)
{
lean_object* v___x_666_; 
v___x_666_ = l_List_reverse___redArg(v_a_665_);
return v___x_666_;
}
else
{
lean_object* v_head_667_; lean_object* v_tail_668_; lean_object* v___x_670_; uint8_t v_isShared_671_; uint8_t v_isSharedCheck_677_; 
v_head_667_ = lean_ctor_get(v_a_664_, 0);
v_tail_668_ = lean_ctor_get(v_a_664_, 1);
v_isSharedCheck_677_ = !lean_is_exclusive(v_a_664_);
if (v_isSharedCheck_677_ == 0)
{
v___x_670_ = v_a_664_;
v_isShared_671_ = v_isSharedCheck_677_;
goto v_resetjp_669_;
}
else
{
lean_inc(v_tail_668_);
lean_inc(v_head_667_);
lean_dec(v_a_664_);
v___x_670_ = lean_box(0);
v_isShared_671_ = v_isSharedCheck_677_;
goto v_resetjp_669_;
}
v_resetjp_669_:
{
lean_object* v___x_672_; lean_object* v___x_674_; 
v___x_672_ = lp_island__logistics__proof_IslandLogistics_actionCost___redArg(v_head_667_);
lean_dec(v_head_667_);
if (v_isShared_671_ == 0)
{
lean_ctor_set(v___x_670_, 1, v_a_665_);
lean_ctor_set(v___x_670_, 0, v___x_672_);
v___x_674_ = v___x_670_;
goto v_reusejp_673_;
}
else
{
lean_object* v_reuseFailAlloc_676_; 
v_reuseFailAlloc_676_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_676_, 0, v___x_672_);
lean_ctor_set(v_reuseFailAlloc_676_, 1, v_a_665_);
v___x_674_ = v_reuseFailAlloc_676_;
goto v_reusejp_673_;
}
v_reusejp_673_:
{
v_a_664_ = v_tail_668_;
v_a_665_ = v___x_674_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planCost(lean_object* v_I_678_, lean_object* v_00_u03c0_679_){
_start:
{
lean_object* v___x_680_; lean_object* v___x_681_; lean_object* v___x_682_; 
v___x_680_ = lean_box(0);
v___x_681_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___redArg(v_00_u03c0_679_, v___x_680_);
v___x_682_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_681_);
lean_dec(v___x_681_);
return v___x_682_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planCost___boxed(lean_object* v_I_683_, lean_object* v_00_u03c0_684_){
_start:
{
lean_object* v_res_685_; 
v_res_685_ = lp_island__logistics__proof_IslandLogistics_planCost(v_I_683_, v_00_u03c0_684_);
lean_dec_ref(v_I_683_);
return v_res_685_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0(lean_object* v_I_686_, lean_object* v_a_687_, lean_object* v_a_688_){
_start:
{
lean_object* v___x_689_; 
v___x_689_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___redArg(v_a_687_, v_a_688_);
return v___x_689_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0___boxed(lean_object* v_I_690_, lean_object* v_a_691_, lean_object* v_a_692_){
_start:
{
lean_object* v_res_693_; 
v_res_693_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_planCost_spec__0(v_I_690_, v_a_691_, v_a_692_);
lean_dec_ref(v_I_690_);
return v_res_693_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___redArg(lean_object* v_a_694_, lean_object* v_a_695_){
_start:
{
if (lean_obj_tag(v_a_694_) == 0)
{
lean_object* v___x_696_; 
v___x_696_ = l_List_reverse___redArg(v_a_695_);
return v___x_696_;
}
else
{
lean_object* v_head_697_; lean_object* v_tail_698_; lean_object* v___x_700_; uint8_t v_isShared_701_; uint8_t v_isSharedCheck_707_; 
v_head_697_ = lean_ctor_get(v_a_694_, 0);
v_tail_698_ = lean_ctor_get(v_a_694_, 1);
v_isSharedCheck_707_ = !lean_is_exclusive(v_a_694_);
if (v_isSharedCheck_707_ == 0)
{
v___x_700_ = v_a_694_;
v_isShared_701_ = v_isSharedCheck_707_;
goto v_resetjp_699_;
}
else
{
lean_inc(v_tail_698_);
lean_inc(v_head_697_);
lean_dec(v_a_694_);
v___x_700_ = lean_box(0);
v_isShared_701_ = v_isSharedCheck_707_;
goto v_resetjp_699_;
}
v_resetjp_699_:
{
lean_object* v___x_702_; lean_object* v___x_704_; 
v___x_702_ = lp_island__logistics__proof_IslandLogistics_actionCostLU___redArg(v_head_697_);
lean_dec(v_head_697_);
if (v_isShared_701_ == 0)
{
lean_ctor_set(v___x_700_, 1, v_a_695_);
lean_ctor_set(v___x_700_, 0, v___x_702_);
v___x_704_ = v___x_700_;
goto v_reusejp_703_;
}
else
{
lean_object* v_reuseFailAlloc_706_; 
v_reuseFailAlloc_706_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_706_, 0, v___x_702_);
lean_ctor_set(v_reuseFailAlloc_706_, 1, v_a_695_);
v___x_704_ = v_reuseFailAlloc_706_;
goto v_reusejp_703_;
}
v_reusejp_703_:
{
v_a_694_ = v_tail_698_;
v_a_695_ = v___x_704_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costLU(lean_object* v_I_708_, lean_object* v_00_u03c0_709_){
_start:
{
lean_object* v___x_710_; lean_object* v___x_711_; lean_object* v___x_712_; 
v___x_710_ = lean_box(0);
v___x_711_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___redArg(v_00_u03c0_709_, v___x_710_);
v___x_712_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_711_);
lean_dec(v___x_711_);
return v___x_712_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costLU___boxed(lean_object* v_I_713_, lean_object* v_00_u03c0_714_){
_start:
{
lean_object* v_res_715_; 
v_res_715_ = lp_island__logistics__proof_IslandLogistics_costLU(v_I_713_, v_00_u03c0_714_);
lean_dec_ref(v_I_713_);
return v_res_715_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0(lean_object* v_I_716_, lean_object* v_a_717_, lean_object* v_a_718_){
_start:
{
lean_object* v___x_719_; 
v___x_719_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___redArg(v_a_717_, v_a_718_);
return v___x_719_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0___boxed(lean_object* v_I_720_, lean_object* v_a_721_, lean_object* v_a_722_){
_start:
{
lean_object* v_res_723_; 
v_res_723_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costLU_spec__0(v_I_720_, v_a_721_, v_a_722_);
lean_dec_ref(v_I_720_);
return v_res_723_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___redArg(lean_object* v_a_724_, lean_object* v_a_725_){
_start:
{
if (lean_obj_tag(v_a_724_) == 0)
{
lean_object* v___x_726_; 
v___x_726_ = l_List_reverse___redArg(v_a_725_);
return v___x_726_;
}
else
{
lean_object* v_head_727_; lean_object* v_tail_728_; lean_object* v___x_730_; uint8_t v_isShared_731_; uint8_t v_isSharedCheck_737_; 
v_head_727_ = lean_ctor_get(v_a_724_, 0);
v_tail_728_ = lean_ctor_get(v_a_724_, 1);
v_isSharedCheck_737_ = !lean_is_exclusive(v_a_724_);
if (v_isSharedCheck_737_ == 0)
{
v___x_730_ = v_a_724_;
v_isShared_731_ = v_isSharedCheck_737_;
goto v_resetjp_729_;
}
else
{
lean_inc(v_tail_728_);
lean_inc(v_head_727_);
lean_dec(v_a_724_);
v___x_730_ = lean_box(0);
v_isShared_731_ = v_isSharedCheck_737_;
goto v_resetjp_729_;
}
v_resetjp_729_:
{
lean_object* v___x_732_; lean_object* v___x_734_; 
v___x_732_ = lp_island__logistics__proof_IslandLogistics_actionCostDrive___redArg(v_head_727_);
lean_dec(v_head_727_);
if (v_isShared_731_ == 0)
{
lean_ctor_set(v___x_730_, 1, v_a_725_);
lean_ctor_set(v___x_730_, 0, v___x_732_);
v___x_734_ = v___x_730_;
goto v_reusejp_733_;
}
else
{
lean_object* v_reuseFailAlloc_736_; 
v_reuseFailAlloc_736_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_736_, 0, v___x_732_);
lean_ctor_set(v_reuseFailAlloc_736_, 1, v_a_725_);
v___x_734_ = v_reuseFailAlloc_736_;
goto v_reusejp_733_;
}
v_reusejp_733_:
{
v_a_724_ = v_tail_728_;
v_a_725_ = v___x_734_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costDrive(lean_object* v_I_738_, lean_object* v_00_u03c0_739_){
_start:
{
lean_object* v___x_740_; lean_object* v___x_741_; lean_object* v___x_742_; 
v___x_740_ = lean_box(0);
v___x_741_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___redArg(v_00_u03c0_739_, v___x_740_);
v___x_742_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_741_);
lean_dec(v___x_741_);
return v___x_742_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costDrive___boxed(lean_object* v_I_743_, lean_object* v_00_u03c0_744_){
_start:
{
lean_object* v_res_745_; 
v_res_745_ = lp_island__logistics__proof_IslandLogistics_costDrive(v_I_743_, v_00_u03c0_744_);
lean_dec_ref(v_I_743_);
return v_res_745_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0(lean_object* v_I_746_, lean_object* v_a_747_, lean_object* v_a_748_){
_start:
{
lean_object* v___x_749_; 
v___x_749_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___redArg(v_a_747_, v_a_748_);
return v___x_749_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0___boxed(lean_object* v_I_750_, lean_object* v_a_751_, lean_object* v_a_752_){
_start:
{
lean_object* v_res_753_; 
v_res_753_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costDrive_spec__0(v_I_750_, v_a_751_, v_a_752_);
lean_dec_ref(v_I_750_);
return v_res_753_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___redArg(lean_object* v_a_754_, lean_object* v_a_755_){
_start:
{
if (lean_obj_tag(v_a_754_) == 0)
{
lean_object* v___x_756_; 
v___x_756_ = l_List_reverse___redArg(v_a_755_);
return v___x_756_;
}
else
{
lean_object* v_head_757_; lean_object* v_tail_758_; lean_object* v___x_760_; uint8_t v_isShared_761_; uint8_t v_isSharedCheck_767_; 
v_head_757_ = lean_ctor_get(v_a_754_, 0);
v_tail_758_ = lean_ctor_get(v_a_754_, 1);
v_isSharedCheck_767_ = !lean_is_exclusive(v_a_754_);
if (v_isSharedCheck_767_ == 0)
{
v___x_760_ = v_a_754_;
v_isShared_761_ = v_isSharedCheck_767_;
goto v_resetjp_759_;
}
else
{
lean_inc(v_tail_758_);
lean_inc(v_head_757_);
lean_dec(v_a_754_);
v___x_760_ = lean_box(0);
v_isShared_761_ = v_isSharedCheck_767_;
goto v_resetjp_759_;
}
v_resetjp_759_:
{
lean_object* v___x_762_; lean_object* v___x_764_; 
v___x_762_ = lp_island__logistics__proof_IslandLogistics_actionCostBD___redArg(v_head_757_);
lean_dec(v_head_757_);
if (v_isShared_761_ == 0)
{
lean_ctor_set(v___x_760_, 1, v_a_755_);
lean_ctor_set(v___x_760_, 0, v___x_762_);
v___x_764_ = v___x_760_;
goto v_reusejp_763_;
}
else
{
lean_object* v_reuseFailAlloc_766_; 
v_reuseFailAlloc_766_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_766_, 0, v___x_762_);
lean_ctor_set(v_reuseFailAlloc_766_, 1, v_a_755_);
v___x_764_ = v_reuseFailAlloc_766_;
goto v_reusejp_763_;
}
v_reusejp_763_:
{
v_a_754_ = v_tail_758_;
v_a_755_ = v___x_764_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costBD(lean_object* v_I_768_, lean_object* v_00_u03c0_769_){
_start:
{
lean_object* v___x_770_; lean_object* v___x_771_; lean_object* v___x_772_; 
v___x_770_ = lean_box(0);
v___x_771_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___redArg(v_00_u03c0_769_, v___x_770_);
v___x_772_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_771_);
lean_dec(v___x_771_);
return v___x_772_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costBD___boxed(lean_object* v_I_773_, lean_object* v_00_u03c0_774_){
_start:
{
lean_object* v_res_775_; 
v_res_775_ = lp_island__logistics__proof_IslandLogistics_costBD(v_I_773_, v_00_u03c0_774_);
lean_dec_ref(v_I_773_);
return v_res_775_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0(lean_object* v_I_776_, lean_object* v_a_777_, lean_object* v_a_778_){
_start:
{
lean_object* v___x_779_; 
v___x_779_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___redArg(v_a_777_, v_a_778_);
return v___x_779_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0___boxed(lean_object* v_I_780_, lean_object* v_a_781_, lean_object* v_a_782_){
_start:
{
lean_object* v_res_783_; 
v_res_783_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costBD_spec__0(v_I_780_, v_a_781_, v_a_782_);
lean_dec_ref(v_I_780_);
return v_res_783_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___redArg(lean_object* v_a_784_, lean_object* v_a_785_){
_start:
{
if (lean_obj_tag(v_a_784_) == 0)
{
lean_object* v___x_786_; 
v___x_786_ = l_List_reverse___redArg(v_a_785_);
return v___x_786_;
}
else
{
lean_object* v_head_787_; lean_object* v_tail_788_; lean_object* v___x_790_; uint8_t v_isShared_791_; uint8_t v_isSharedCheck_797_; 
v_head_787_ = lean_ctor_get(v_a_784_, 0);
v_tail_788_ = lean_ctor_get(v_a_784_, 1);
v_isSharedCheck_797_ = !lean_is_exclusive(v_a_784_);
if (v_isSharedCheck_797_ == 0)
{
v___x_790_ = v_a_784_;
v_isShared_791_ = v_isSharedCheck_797_;
goto v_resetjp_789_;
}
else
{
lean_inc(v_tail_788_);
lean_inc(v_head_787_);
lean_dec(v_a_784_);
v___x_790_ = lean_box(0);
v_isShared_791_ = v_isSharedCheck_797_;
goto v_resetjp_789_;
}
v_resetjp_789_:
{
lean_object* v___x_792_; lean_object* v___x_794_; 
v___x_792_ = lp_island__logistics__proof_IslandLogistics_actionCostSail___redArg(v_head_787_);
lean_dec(v_head_787_);
if (v_isShared_791_ == 0)
{
lean_ctor_set(v___x_790_, 1, v_a_785_);
lean_ctor_set(v___x_790_, 0, v___x_792_);
v___x_794_ = v___x_790_;
goto v_reusejp_793_;
}
else
{
lean_object* v_reuseFailAlloc_796_; 
v_reuseFailAlloc_796_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_796_, 0, v___x_792_);
lean_ctor_set(v_reuseFailAlloc_796_, 1, v_a_785_);
v___x_794_ = v_reuseFailAlloc_796_;
goto v_reusejp_793_;
}
v_reusejp_793_:
{
v_a_784_ = v_tail_788_;
v_a_785_ = v___x_794_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costSail(lean_object* v_I_798_, lean_object* v_00_u03c0_799_){
_start:
{
lean_object* v___x_800_; lean_object* v___x_801_; lean_object* v___x_802_; 
v___x_800_ = lean_box(0);
v___x_801_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___redArg(v_00_u03c0_799_, v___x_800_);
v___x_802_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_801_);
lean_dec(v___x_801_);
return v___x_802_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costSail___boxed(lean_object* v_I_803_, lean_object* v_00_u03c0_804_){
_start:
{
lean_object* v_res_805_; 
v_res_805_ = lp_island__logistics__proof_IslandLogistics_costSail(v_I_803_, v_00_u03c0_804_);
lean_dec_ref(v_I_803_);
return v_res_805_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0(lean_object* v_I_806_, lean_object* v_a_807_, lean_object* v_a_808_){
_start:
{
lean_object* v___x_809_; 
v___x_809_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___redArg(v_a_807_, v_a_808_);
return v___x_809_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0___boxed(lean_object* v_I_810_, lean_object* v_a_811_, lean_object* v_a_812_){
_start:
{
lean_object* v_res_813_; 
v_res_813_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_costSail_spec__0(v_I_810_, v_a_811_, v_a_812_);
lean_dec_ref(v_I_810_);
return v_res_813_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_sailCount_spec__0(lean_object* v_a_814_, lean_object* v_a_815_){
_start:
{
if (lean_obj_tag(v_a_814_) == 0)
{
lean_object* v___x_816_; 
v___x_816_ = l_List_reverse___redArg(v_a_815_);
return v___x_816_;
}
else
{
lean_object* v_head_817_; lean_object* v_tail_818_; lean_object* v___x_820_; uint8_t v_isShared_821_; uint8_t v_isSharedCheck_830_; 
v_head_817_ = lean_ctor_get(v_a_814_, 0);
v_tail_818_ = lean_ctor_get(v_a_814_, 1);
v_isSharedCheck_830_ = !lean_is_exclusive(v_a_814_);
if (v_isSharedCheck_830_ == 0)
{
v___x_820_ = v_a_814_;
v_isShared_821_ = v_isSharedCheck_830_;
goto v_resetjp_819_;
}
else
{
lean_inc(v_tail_818_);
lean_inc(v_head_817_);
lean_dec(v_a_814_);
v___x_820_ = lean_box(0);
v_isShared_821_ = v_isSharedCheck_830_;
goto v_resetjp_819_;
}
v_resetjp_819_:
{
lean_object* v___y_823_; 
if (lean_obj_tag(v_head_817_) == 5)
{
lean_object* v___x_828_; 
lean_dec_ref_known(v_head_817_, 3);
v___x_828_ = lean_unsigned_to_nat(1u);
v___y_823_ = v___x_828_;
goto v___jp_822_;
}
else
{
lean_object* v___x_829_; 
lean_dec(v_head_817_);
v___x_829_ = lean_unsigned_to_nat(0u);
v___y_823_ = v___x_829_;
goto v___jp_822_;
}
v___jp_822_:
{
lean_object* v___x_825_; 
if (v_isShared_821_ == 0)
{
lean_ctor_set(v___x_820_, 1, v_a_815_);
lean_ctor_set(v___x_820_, 0, v___y_823_);
v___x_825_ = v___x_820_;
goto v_reusejp_824_;
}
else
{
lean_object* v_reuseFailAlloc_827_; 
v_reuseFailAlloc_827_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_827_, 0, v___y_823_);
lean_ctor_set(v_reuseFailAlloc_827_, 1, v_a_815_);
v___x_825_ = v_reuseFailAlloc_827_;
goto v_reusejp_824_;
}
v_reusejp_824_:
{
v_a_814_ = v_tail_818_;
v_a_815_ = v___x_825_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount___redArg(lean_object* v_00_u03c0_831_){
_start:
{
lean_object* v___x_832_; lean_object* v___x_833_; lean_object* v___x_834_; 
v___x_832_ = lean_box(0);
v___x_833_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_sailCount_spec__0(v_00_u03c0_831_, v___x_832_);
v___x_834_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_833_);
lean_dec(v___x_833_);
return v___x_834_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount(lean_object* v_I_835_, lean_object* v_00_u03c0_836_){
_start:
{
lean_object* v___x_837_; 
v___x_837_ = lp_island__logistics__proof_IslandLogistics_sailCount___redArg(v_00_u03c0_836_);
return v___x_837_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sailCount___boxed(lean_object* v_I_838_, lean_object* v_00_u03c0_839_){
_start:
{
lean_object* v_res_840_; 
v_res_840_ = lp_island__logistics__proof_IslandLogistics_sailCount(v_I_838_, v_00_u03c0_839_);
lean_dec_ref(v_I_838_);
return v_res_840_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter___redArg(lean_object* v_x_841_, lean_object* v_h__1_842_, lean_object* v_h__2_843_){
_start:
{
if (lean_obj_tag(v_x_841_) == 5)
{
lean_object* v_f_844_; lean_object* v_u_845_; lean_object* v_v_846_; lean_object* v___x_847_; 
lean_dec(v_h__2_843_);
v_f_844_ = lean_ctor_get(v_x_841_, 0);
lean_inc(v_f_844_);
v_u_845_ = lean_ctor_get(v_x_841_, 1);
lean_inc(v_u_845_);
v_v_846_ = lean_ctor_get(v_x_841_, 2);
lean_inc(v_v_846_);
lean_dec_ref_known(v_x_841_, 3);
v___x_847_ = lean_apply_3(v_h__1_842_, v_f_844_, v_u_845_, v_v_846_);
return v___x_847_;
}
else
{
lean_object* v___x_848_; 
lean_dec(v_h__1_842_);
v___x_848_ = lean_apply_2(v_h__2_843_, v_x_841_, lean_box(0));
return v___x_848_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter(lean_object* v_I_849_, lean_object* v_motive_850_, lean_object* v_x_851_, lean_object* v_h__1_852_, lean_object* v_h__2_853_){
_start:
{
if (lean_obj_tag(v_x_851_) == 5)
{
lean_object* v_f_854_; lean_object* v_u_855_; lean_object* v_v_856_; lean_object* v___x_857_; 
lean_dec(v_h__2_853_);
v_f_854_ = lean_ctor_get(v_x_851_, 0);
lean_inc(v_f_854_);
v_u_855_ = lean_ctor_get(v_x_851_, 1);
lean_inc(v_u_855_);
v_v_856_ = lean_ctor_get(v_x_851_, 2);
lean_inc(v_v_856_);
lean_dec_ref_known(v_x_851_, 3);
v___x_857_ = lean_apply_3(v_h__1_852_, v_f_854_, v_u_855_, v_v_856_);
return v___x_857_;
}
else
{
lean_object* v___x_858_; 
lean_dec(v_h__1_852_);
v___x_858_ = lean_apply_2(v_h__2_853_, v_x_851_, lean_box(0));
return v___x_858_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter___boxed(lean_object* v_I_859_, lean_object* v_motive_860_, lean_object* v_x_861_, lean_object* v_h__1_862_, lean_object* v_h__2_863_){
_start:
{
lean_object* v_res_864_; 
v_res_864_ = lp_island__logistics__proof___private_Domain_0__IslandLogistics_actionCost_match__1_splitter(v_I_859_, v_motive_860_, v_x_861_, v_h__1_862_, v_h__2_863_);
lean_dec_ref(v_I_859_);
return v_res_864_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyAction(lean_object* v_I_865_, lean_object* v_s_866_, lean_object* v_x_867_){
_start:
{
switch(lean_obj_tag(v_x_867_))
{
case 0:
{
lean_object* v_t_868_; lean_object* v_v_869_; lean_object* v_numTrucks_870_; lean_object* v_truckLoc_871_; lean_object* v_ferryLoc_872_; lean_object* v_pkgLoc_873_; lean_object* v___x_875_; uint8_t v_isShared_876_; uint8_t v_isSharedCheck_882_; 
v_t_868_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_t_868_);
v_v_869_ = lean_ctor_get(v_x_867_, 2);
lean_inc(v_v_869_);
lean_dec_ref_known(v_x_867_, 3);
v_numTrucks_870_ = lean_ctor_get(v_I_865_, 3);
lean_inc(v_numTrucks_870_);
lean_dec_ref(v_I_865_);
v_truckLoc_871_ = lean_ctor_get(v_s_866_, 0);
v_ferryLoc_872_ = lean_ctor_get(v_s_866_, 1);
v_pkgLoc_873_ = lean_ctor_get(v_s_866_, 2);
v_isSharedCheck_882_ = !lean_is_exclusive(v_s_866_);
if (v_isSharedCheck_882_ == 0)
{
v___x_875_ = v_s_866_;
v_isShared_876_ = v_isSharedCheck_882_;
goto v_resetjp_874_;
}
else
{
lean_inc(v_pkgLoc_873_);
lean_inc(v_ferryLoc_872_);
lean_inc(v_truckLoc_871_);
lean_dec(v_s_866_);
v___x_875_ = lean_box(0);
v_isShared_876_ = v_isSharedCheck_882_;
goto v_resetjp_874_;
}
v_resetjp_874_:
{
lean_object* v___x_877_; lean_object* v___x_878_; lean_object* v___x_880_; 
v___x_877_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_877_, 0, v_v_869_);
v___x_878_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_878_, 0, lean_box(0));
lean_closure_set(v___x_878_, 1, v_numTrucks_870_);
lean_closure_set(v___x_878_, 2, v_truckLoc_871_);
lean_closure_set(v___x_878_, 3, v_t_868_);
lean_closure_set(v___x_878_, 4, v___x_877_);
if (v_isShared_876_ == 0)
{
lean_ctor_set(v___x_875_, 0, v___x_878_);
v___x_880_ = v___x_875_;
goto v_reusejp_879_;
}
else
{
lean_object* v_reuseFailAlloc_881_; 
v_reuseFailAlloc_881_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_881_, 0, v___x_878_);
lean_ctor_set(v_reuseFailAlloc_881_, 1, v_ferryLoc_872_);
lean_ctor_set(v_reuseFailAlloc_881_, 2, v_pkgLoc_873_);
v___x_880_ = v_reuseFailAlloc_881_;
goto v_reusejp_879_;
}
v_reusejp_879_:
{
return v___x_880_;
}
}
}
case 1:
{
lean_object* v_p_883_; lean_object* v_t_884_; lean_object* v_truckLoc_885_; lean_object* v_ferryLoc_886_; lean_object* v_pkgLoc_887_; lean_object* v___x_889_; uint8_t v_isShared_890_; uint8_t v_isSharedCheck_897_; 
v_p_883_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_p_883_);
v_t_884_ = lean_ctor_get(v_x_867_, 1);
lean_inc(v_t_884_);
lean_dec_ref_known(v_x_867_, 2);
v_truckLoc_885_ = lean_ctor_get(v_s_866_, 0);
v_ferryLoc_886_ = lean_ctor_get(v_s_866_, 1);
v_pkgLoc_887_ = lean_ctor_get(v_s_866_, 2);
v_isSharedCheck_897_ = !lean_is_exclusive(v_s_866_);
if (v_isSharedCheck_897_ == 0)
{
v___x_889_ = v_s_866_;
v_isShared_890_ = v_isSharedCheck_897_;
goto v_resetjp_888_;
}
else
{
lean_inc(v_pkgLoc_887_);
lean_inc(v_ferryLoc_886_);
lean_inc(v_truckLoc_885_);
lean_dec(v_s_866_);
v___x_889_ = lean_box(0);
v_isShared_890_ = v_isSharedCheck_897_;
goto v_resetjp_888_;
}
v_resetjp_888_:
{
lean_object* v_numPkgs_891_; lean_object* v___x_892_; lean_object* v___x_893_; lean_object* v___x_895_; 
v_numPkgs_891_ = lean_ctor_get(v_I_865_, 8);
lean_inc(v_numPkgs_891_);
lean_dec_ref(v_I_865_);
v___x_892_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_892_, 0, v_t_884_);
v___x_893_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_893_, 0, lean_box(0));
lean_closure_set(v___x_893_, 1, v_numPkgs_891_);
lean_closure_set(v___x_893_, 2, v_pkgLoc_887_);
lean_closure_set(v___x_893_, 3, v_p_883_);
lean_closure_set(v___x_893_, 4, v___x_892_);
if (v_isShared_890_ == 0)
{
lean_ctor_set(v___x_889_, 2, v___x_893_);
v___x_895_ = v___x_889_;
goto v_reusejp_894_;
}
else
{
lean_object* v_reuseFailAlloc_896_; 
v_reuseFailAlloc_896_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_896_, 0, v_truckLoc_885_);
lean_ctor_set(v_reuseFailAlloc_896_, 1, v_ferryLoc_886_);
lean_ctor_set(v_reuseFailAlloc_896_, 2, v___x_893_);
v___x_895_ = v_reuseFailAlloc_896_;
goto v_reusejp_894_;
}
v_reusejp_894_:
{
return v___x_895_;
}
}
}
case 2:
{
lean_object* v_p_898_; lean_object* v_t_899_; lean_object* v_truckLoc_900_; lean_object* v_ferryLoc_901_; lean_object* v_pkgLoc_902_; lean_object* v_numPkgs_903_; lean_object* v___x_904_; lean_object* v___x_905_; lean_object* v___x_906_; lean_object* v___x_907_; 
v_p_898_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_p_898_);
v_t_899_ = lean_ctor_get(v_x_867_, 1);
lean_inc(v_t_899_);
lean_dec_ref_known(v_x_867_, 2);
v_truckLoc_900_ = lean_ctor_get(v_s_866_, 0);
lean_inc_ref(v_truckLoc_900_);
v_ferryLoc_901_ = lean_ctor_get(v_s_866_, 1);
lean_inc_ref(v_ferryLoc_901_);
v_pkgLoc_902_ = lean_ctor_get(v_s_866_, 2);
lean_inc_ref(v_pkgLoc_902_);
v_numPkgs_903_ = lean_ctor_get(v_I_865_, 8);
lean_inc(v_numPkgs_903_);
lean_dec_ref(v_I_865_);
v___x_904_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_866_, v_t_899_);
v___x_905_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_905_, 0, v___x_904_);
v___x_906_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_906_, 0, lean_box(0));
lean_closure_set(v___x_906_, 1, v_numPkgs_903_);
lean_closure_set(v___x_906_, 2, v_pkgLoc_902_);
lean_closure_set(v___x_906_, 3, v_p_898_);
lean_closure_set(v___x_906_, 4, v___x_905_);
v___x_907_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v___x_907_, 0, v_truckLoc_900_);
lean_ctor_set(v___x_907_, 1, v_ferryLoc_901_);
lean_ctor_set(v___x_907_, 2, v___x_906_);
return v___x_907_;
}
case 3:
{
lean_object* v_t_908_; lean_object* v_f_909_; lean_object* v_numTrucks_910_; lean_object* v_truckLoc_911_; lean_object* v_ferryLoc_912_; lean_object* v_pkgLoc_913_; lean_object* v___x_915_; uint8_t v_isShared_916_; uint8_t v_isSharedCheck_922_; 
v_t_908_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_t_908_);
v_f_909_ = lean_ctor_get(v_x_867_, 1);
lean_inc(v_f_909_);
lean_dec_ref_known(v_x_867_, 2);
v_numTrucks_910_ = lean_ctor_get(v_I_865_, 3);
lean_inc(v_numTrucks_910_);
lean_dec_ref(v_I_865_);
v_truckLoc_911_ = lean_ctor_get(v_s_866_, 0);
v_ferryLoc_912_ = lean_ctor_get(v_s_866_, 1);
v_pkgLoc_913_ = lean_ctor_get(v_s_866_, 2);
v_isSharedCheck_922_ = !lean_is_exclusive(v_s_866_);
if (v_isSharedCheck_922_ == 0)
{
v___x_915_ = v_s_866_;
v_isShared_916_ = v_isSharedCheck_922_;
goto v_resetjp_914_;
}
else
{
lean_inc(v_pkgLoc_913_);
lean_inc(v_ferryLoc_912_);
lean_inc(v_truckLoc_911_);
lean_dec(v_s_866_);
v___x_915_ = lean_box(0);
v_isShared_916_ = v_isSharedCheck_922_;
goto v_resetjp_914_;
}
v_resetjp_914_:
{
lean_object* v___x_917_; lean_object* v___x_918_; lean_object* v___x_920_; 
v___x_917_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_917_, 0, v_f_909_);
v___x_918_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_918_, 0, lean_box(0));
lean_closure_set(v___x_918_, 1, v_numTrucks_910_);
lean_closure_set(v___x_918_, 2, v_truckLoc_911_);
lean_closure_set(v___x_918_, 3, v_t_908_);
lean_closure_set(v___x_918_, 4, v___x_917_);
if (v_isShared_916_ == 0)
{
lean_ctor_set(v___x_915_, 0, v___x_918_);
v___x_920_ = v___x_915_;
goto v_reusejp_919_;
}
else
{
lean_object* v_reuseFailAlloc_921_; 
v_reuseFailAlloc_921_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_921_, 0, v___x_918_);
lean_ctor_set(v_reuseFailAlloc_921_, 1, v_ferryLoc_912_);
lean_ctor_set(v_reuseFailAlloc_921_, 2, v_pkgLoc_913_);
v___x_920_ = v_reuseFailAlloc_921_;
goto v_reusejp_919_;
}
v_reusejp_919_:
{
return v___x_920_;
}
}
}
case 4:
{
lean_object* v_t_923_; lean_object* v_f_924_; lean_object* v_numTrucks_925_; lean_object* v_truckLoc_926_; lean_object* v_ferryLoc_927_; lean_object* v_pkgLoc_928_; lean_object* v___x_930_; uint8_t v_isShared_931_; uint8_t v_isSharedCheck_938_; 
v_t_923_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_t_923_);
v_f_924_ = lean_ctor_get(v_x_867_, 1);
lean_inc(v_f_924_);
lean_dec_ref_known(v_x_867_, 2);
v_numTrucks_925_ = lean_ctor_get(v_I_865_, 3);
lean_inc(v_numTrucks_925_);
lean_dec_ref(v_I_865_);
v_truckLoc_926_ = lean_ctor_get(v_s_866_, 0);
v_ferryLoc_927_ = lean_ctor_get(v_s_866_, 1);
v_pkgLoc_928_ = lean_ctor_get(v_s_866_, 2);
v_isSharedCheck_938_ = !lean_is_exclusive(v_s_866_);
if (v_isSharedCheck_938_ == 0)
{
v___x_930_ = v_s_866_;
v_isShared_931_ = v_isSharedCheck_938_;
goto v_resetjp_929_;
}
else
{
lean_inc(v_pkgLoc_928_);
lean_inc(v_ferryLoc_927_);
lean_inc(v_truckLoc_926_);
lean_dec(v_s_866_);
v___x_930_ = lean_box(0);
v_isShared_931_ = v_isSharedCheck_938_;
goto v_resetjp_929_;
}
v_resetjp_929_:
{
lean_object* v___x_932_; lean_object* v___x_933_; lean_object* v___x_934_; lean_object* v___x_936_; 
lean_inc_ref(v_ferryLoc_927_);
v___x_932_ = lean_apply_1(v_ferryLoc_927_, v_f_924_);
v___x_933_ = lean_alloc_ctor(0, 1, 0);
lean_ctor_set(v___x_933_, 0, v___x_932_);
v___x_934_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_934_, 0, lean_box(0));
lean_closure_set(v___x_934_, 1, v_numTrucks_925_);
lean_closure_set(v___x_934_, 2, v_truckLoc_926_);
lean_closure_set(v___x_934_, 3, v_t_923_);
lean_closure_set(v___x_934_, 4, v___x_933_);
if (v_isShared_931_ == 0)
{
lean_ctor_set(v___x_930_, 0, v___x_934_);
v___x_936_ = v___x_930_;
goto v_reusejp_935_;
}
else
{
lean_object* v_reuseFailAlloc_937_; 
v_reuseFailAlloc_937_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_937_, 0, v___x_934_);
lean_ctor_set(v_reuseFailAlloc_937_, 1, v_ferryLoc_927_);
lean_ctor_set(v_reuseFailAlloc_937_, 2, v_pkgLoc_928_);
v___x_936_ = v_reuseFailAlloc_937_;
goto v_reusejp_935_;
}
v_reusejp_935_:
{
return v___x_936_;
}
}
}
default: 
{
lean_object* v_f_939_; lean_object* v_v_940_; lean_object* v_truckLoc_941_; lean_object* v_ferryLoc_942_; lean_object* v_pkgLoc_943_; lean_object* v___x_945_; uint8_t v_isShared_946_; uint8_t v_isSharedCheck_952_; 
v_f_939_ = lean_ctor_get(v_x_867_, 0);
lean_inc(v_f_939_);
v_v_940_ = lean_ctor_get(v_x_867_, 2);
lean_inc(v_v_940_);
lean_dec_ref_known(v_x_867_, 3);
v_truckLoc_941_ = lean_ctor_get(v_s_866_, 0);
v_ferryLoc_942_ = lean_ctor_get(v_s_866_, 1);
v_pkgLoc_943_ = lean_ctor_get(v_s_866_, 2);
v_isSharedCheck_952_ = !lean_is_exclusive(v_s_866_);
if (v_isSharedCheck_952_ == 0)
{
v___x_945_ = v_s_866_;
v_isShared_946_ = v_isSharedCheck_952_;
goto v_resetjp_944_;
}
else
{
lean_inc(v_pkgLoc_943_);
lean_inc(v_ferryLoc_942_);
lean_inc(v_truckLoc_941_);
lean_dec(v_s_866_);
v___x_945_ = lean_box(0);
v_isShared_946_ = v_isSharedCheck_952_;
goto v_resetjp_944_;
}
v_resetjp_944_:
{
lean_object* v_numFerries_947_; lean_object* v___x_948_; lean_object* v___x_950_; 
v_numFerries_947_ = lean_ctor_get(v_I_865_, 5);
lean_inc(v_numFerries_947_);
lean_dec_ref(v_I_865_);
v___x_948_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_updateFn___boxed), 6, 5);
lean_closure_set(v___x_948_, 0, lean_box(0));
lean_closure_set(v___x_948_, 1, v_numFerries_947_);
lean_closure_set(v___x_948_, 2, v_ferryLoc_942_);
lean_closure_set(v___x_948_, 3, v_f_939_);
lean_closure_set(v___x_948_, 4, v_v_940_);
if (v_isShared_946_ == 0)
{
lean_ctor_set(v___x_945_, 1, v___x_948_);
v___x_950_ = v___x_945_;
goto v_reusejp_949_;
}
else
{
lean_object* v_reuseFailAlloc_951_; 
v_reuseFailAlloc_951_ = lean_alloc_ctor(0, 3, 0);
lean_ctor_set(v_reuseFailAlloc_951_, 0, v_truckLoc_941_);
lean_ctor_set(v_reuseFailAlloc_951_, 1, v___x_948_);
lean_ctor_set(v_reuseFailAlloc_951_, 2, v_pkgLoc_943_);
v___x_950_ = v_reuseFailAlloc_951_;
goto v_reusejp_949_;
}
v_reusejp_949_:
{
return v___x_950_;
}
}
}
}
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin) {
lean_object * res;
if (_G_initialized) return lean_io_result_mk_ok(lean_box(0));
_G_initialized = true;
lean_initialize_runtime_module();
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_Init(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
