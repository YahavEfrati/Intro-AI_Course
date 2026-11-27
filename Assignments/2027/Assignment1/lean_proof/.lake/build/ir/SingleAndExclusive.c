// Lean compiler output
// Module: SingleAndExclusive
// Imports: public import Init public meta import Init public import Domain public import PackingAndFlux public import BridgesAndCycles
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
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_array_to_list(lean_object*);
lean_object* lean_array_push(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* l_List_finRange(lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* l_List_foldl___at___00Array_appendList_spec__0___redArg(lean_object*, lean_object*);
uint8_t l___private_Init_Data_Nat_Lemmas_0__Nat_allLTTR_loop___redArg(lean_object*, lean_object*, lean_object*);
uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(lean_object*, lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(lean_object*, lean_object*);
lean_object* lean_obj_tag_nat(lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_costDrive(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_costBD(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_costSail(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_maxDynEffCap(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_packLB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgLUPot(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hLU___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hLU(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isPkgLU(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isPkgLU___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckAct(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckAct___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potNS(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costMove(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costMove___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_exclInitPM(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitPM___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(lean_object*, lean_object*, uint8_t);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_setBit___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_setBit___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_setBit(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_setBit___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0(uint8_t, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0___boxed(lean_object*, lean_object*);
static const lean_closure_object lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___closed__0 = (const lean_object*)&lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitLayer(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0 = (const lean_object*)&lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclStepLayer(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclStepLayer___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclIterLayers(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclIterLayers___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclTspLB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_validEvStep___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_validEvStep___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_validEvStep(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_validEvStep___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvPM(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvPM___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvDM(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvDM___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgLUPot(lean_object* v_I_1_, lean_object* v_s_2_, lean_object* v_p_3_){
_start:
{
uint8_t v___x_4_; 
lean_inc(v_p_3_);
lean_inc_ref(v_s_2_);
v___x_4_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_1_, v_s_2_, v_p_3_);
if (v___x_4_ == 0)
{
lean_object* v_pkgLoc_5_; lean_object* v___x_6_; 
v_pkgLoc_5_ = lean_ctor_get(v_s_2_, 2);
lean_inc_ref(v_pkgLoc_5_);
lean_dec_ref(v_s_2_);
v___x_6_ = lean_apply_1(v_pkgLoc_5_, v_p_3_);
if (lean_obj_tag(v___x_6_) == 0)
{
lean_object* v___x_7_; 
lean_dec_ref_known(v___x_6_, 1);
v___x_7_ = lean_unsigned_to_nat(2u);
return v___x_7_;
}
else
{
lean_object* v___x_8_; 
lean_dec_ref_known(v___x_6_, 1);
v___x_8_ = lean_unsigned_to_nat(1u);
return v___x_8_;
}
}
else
{
lean_object* v___x_9_; 
lean_dec(v_p_3_);
lean_dec_ref(v_s_2_);
v___x_9_ = lean_unsigned_to_nat(0u);
return v___x_9_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hLU___lam__0(lean_object* v_I_10_, lean_object* v_s_11_, lean_object* v_p_12_){
_start:
{
lean_object* v___x_13_; 
v___x_13_ = lp_island__logistics__proof_IslandLogistics_pkgLUPot(v_I_10_, v_s_11_, v_p_12_);
return v___x_13_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hLU(lean_object* v_I_14_, lean_object* v_s_15_){
_start:
{
lean_object* v_numPkgs_16_; lean_object* v___f_17_; lean_object* v___x_18_; 
v_numPkgs_16_ = lean_ctor_get(v_I_14_, 8);
lean_inc(v_numPkgs_16_);
v___f_17_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_hLU___lam__0), 3, 2);
lean_closure_set(v___f_17_, 0, v_I_14_);
lean_closure_set(v___f_17_, 1, v_s_15_);
v___x_18_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_16_, v___f_17_);
return v___x_18_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg(lean_object* v_p_19_, lean_object* v_x_20_){
_start:
{
switch(lean_obj_tag(v_x_20_))
{
case 1:
{
lean_object* v_p_21_; uint8_t v___x_22_; 
v_p_21_ = lean_ctor_get(v_x_20_, 0);
v___x_22_ = lean_nat_dec_eq(v_p_21_, v_p_19_);
return v___x_22_;
}
case 2:
{
lean_object* v_p_23_; uint8_t v___x_24_; 
v_p_23_ = lean_ctor_get(v_x_20_, 0);
v___x_24_ = lean_nat_dec_eq(v_p_23_, v_p_19_);
return v___x_24_;
}
default: 
{
uint8_t v___x_25_; 
v___x_25_ = 0;
return v___x_25_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg___boxed(lean_object* v_p_26_, lean_object* v_x_27_){
_start:
{
uint8_t v_res_28_; lean_object* v_r_29_; 
v_res_28_ = lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg(v_p_26_, v_x_27_);
lean_dec_ref(v_x_27_);
lean_dec(v_p_26_);
v_r_29_ = lean_box(v_res_28_);
return v_r_29_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isPkgLU(lean_object* v_I_30_, lean_object* v_p_31_, lean_object* v_x_32_){
_start:
{
uint8_t v___x_33_; 
v___x_33_ = lp_island__logistics__proof_IslandLogistics_isPkgLU___redArg(v_p_31_, v_x_32_);
return v___x_33_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isPkgLU___boxed(lean_object* v_I_34_, lean_object* v_p_35_, lean_object* v_x_36_){
_start:
{
uint8_t v_res_37_; lean_object* v_r_38_; 
v_res_37_ = lp_island__logistics__proof_IslandLogistics_isPkgLU(v_I_34_, v_p_35_, v_x_36_);
lean_dec_ref(v_x_36_);
lean_dec(v_p_35_);
lean_dec_ref(v_I_34_);
v_r_38_ = lean_box(v_res_37_);
return v_r_38_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter___redArg(lean_object* v_x_39_, lean_object* v_h__1_40_, lean_object* v_h__2_41_, lean_object* v_h__3_42_){
_start:
{
switch(lean_obj_tag(v_x_39_))
{
case 1:
{
lean_object* v_p_43_; lean_object* v_t_44_; lean_object* v___x_45_; 
lean_dec(v_h__3_42_);
lean_dec(v_h__2_41_);
v_p_43_ = lean_ctor_get(v_x_39_, 0);
lean_inc(v_p_43_);
v_t_44_ = lean_ctor_get(v_x_39_, 1);
lean_inc(v_t_44_);
lean_dec_ref_known(v_x_39_, 2);
v___x_45_ = lean_apply_2(v_h__1_40_, v_p_43_, v_t_44_);
return v___x_45_;
}
case 2:
{
lean_object* v_p_46_; lean_object* v_t_47_; lean_object* v___x_48_; 
lean_dec(v_h__3_42_);
lean_dec(v_h__1_40_);
v_p_46_ = lean_ctor_get(v_x_39_, 0);
lean_inc(v_p_46_);
v_t_47_ = lean_ctor_get(v_x_39_, 1);
lean_inc(v_t_47_);
lean_dec_ref_known(v_x_39_, 2);
v___x_48_ = lean_apply_2(v_h__2_41_, v_p_46_, v_t_47_);
return v___x_48_;
}
default: 
{
lean_object* v___x_49_; 
lean_dec(v_h__2_41_);
lean_dec(v_h__1_40_);
v___x_49_ = lean_apply_3(v_h__3_42_, v_x_39_, lean_box(0), lean_box(0));
return v___x_49_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter(lean_object* v_I_50_, lean_object* v_motive_51_, lean_object* v_x_52_, lean_object* v_h__1_53_, lean_object* v_h__2_54_, lean_object* v_h__3_55_){
_start:
{
switch(lean_obj_tag(v_x_52_))
{
case 1:
{
lean_object* v_p_56_; lean_object* v_t_57_; lean_object* v___x_58_; 
lean_dec(v_h__3_55_);
lean_dec(v_h__2_54_);
v_p_56_ = lean_ctor_get(v_x_52_, 0);
lean_inc(v_p_56_);
v_t_57_ = lean_ctor_get(v_x_52_, 1);
lean_inc(v_t_57_);
lean_dec_ref_known(v_x_52_, 2);
v___x_58_ = lean_apply_2(v_h__1_53_, v_p_56_, v_t_57_);
return v___x_58_;
}
case 2:
{
lean_object* v_p_59_; lean_object* v_t_60_; lean_object* v___x_61_; 
lean_dec(v_h__3_55_);
lean_dec(v_h__1_53_);
v_p_59_ = lean_ctor_get(v_x_52_, 0);
lean_inc(v_p_59_);
v_t_60_ = lean_ctor_get(v_x_52_, 1);
lean_inc(v_t_60_);
lean_dec_ref_known(v_x_52_, 2);
v___x_61_ = lean_apply_2(v_h__2_54_, v_p_59_, v_t_60_);
return v___x_61_;
}
default: 
{
lean_object* v___x_62_; 
lean_dec(v_h__2_54_);
lean_dec(v_h__1_53_);
v___x_62_ = lean_apply_3(v_h__3_55_, v_x_52_, lean_box(0), lean_box(0));
return v___x_62_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter___boxed(lean_object* v_I_63_, lean_object* v_motive_64_, lean_object* v_x_65_, lean_object* v_h__1_66_, lean_object* v_h__2_67_, lean_object* v_h__3_68_){
_start:
{
lean_object* v_res_69_; 
v_res_69_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isPkgLU_match__1_splitter(v_I_63_, v_motive_64_, v_x_65_, v_h__1_66_, v_h__2_67_, v_h__3_68_);
lean_dec_ref(v_I_63_);
return v_res_69_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter___redArg(lean_object* v_x_70_, lean_object* v_h__1_71_, lean_object* v_h__2_72_){
_start:
{
if (lean_obj_tag(v_x_70_) == 0)
{
lean_object* v_l_73_; lean_object* v___x_74_; 
lean_dec(v_h__1_71_);
v_l_73_ = lean_ctor_get(v_x_70_, 0);
lean_inc(v_l_73_);
lean_dec_ref_known(v_x_70_, 1);
v___x_74_ = lean_apply_1(v_h__2_72_, v_l_73_);
return v___x_74_;
}
else
{
lean_object* v_t_75_; lean_object* v___x_76_; 
lean_dec(v_h__2_72_);
v_t_75_ = lean_ctor_get(v_x_70_, 0);
lean_inc(v_t_75_);
lean_dec_ref_known(v_x_70_, 1);
v___x_76_ = lean_apply_1(v_h__1_71_, v_t_75_);
return v___x_76_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter(lean_object* v_I_77_, lean_object* v_motive_78_, lean_object* v_x_79_, lean_object* v_h__1_80_, lean_object* v_h__2_81_){
_start:
{
if (lean_obj_tag(v_x_79_) == 0)
{
lean_object* v_l_82_; lean_object* v___x_83_; 
lean_dec(v_h__1_80_);
v_l_82_ = lean_ctor_get(v_x_79_, 0);
lean_inc(v_l_82_);
lean_dec_ref_known(v_x_79_, 1);
v___x_83_ = lean_apply_1(v_h__2_81_, v_l_82_);
return v___x_83_;
}
else
{
lean_object* v_t_84_; lean_object* v___x_85_; 
lean_dec(v_h__2_81_);
v_t_84_ = lean_ctor_get(v_x_79_, 0);
lean_inc(v_t_84_);
lean_dec_ref_known(v_x_79_, 1);
v___x_85_ = lean_apply_1(v_h__1_80_, v_t_84_);
return v___x_85_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter___boxed(lean_object* v_I_86_, lean_object* v_motive_87_, lean_object* v_x_88_, lean_object* v_h__1_89_, lean_object* v_h__2_90_){
_start:
{
lean_object* v_res_91_; 
v_res_91_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_pkgLUPot_match__1_splitter(v_I_86_, v_motive_87_, v_x_88_, v_h__1_89_, v_h__2_90_);
lean_dec_ref(v_I_86_);
return v_res_91_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter___redArg(lean_object* v_x_92_, lean_object* v_h__1_93_, lean_object* v_h__2_94_, lean_object* v_h__3_95_){
_start:
{
switch(lean_obj_tag(v_x_92_))
{
case 1:
{
lean_object* v_p_96_; lean_object* v_t_97_; lean_object* v___x_98_; 
lean_dec(v_h__3_95_);
lean_dec(v_h__2_94_);
v_p_96_ = lean_ctor_get(v_x_92_, 0);
lean_inc(v_p_96_);
v_t_97_ = lean_ctor_get(v_x_92_, 1);
lean_inc(v_t_97_);
lean_dec_ref_known(v_x_92_, 2);
v___x_98_ = lean_apply_2(v_h__1_93_, v_p_96_, v_t_97_);
return v___x_98_;
}
case 2:
{
lean_object* v_p_99_; lean_object* v_t_100_; lean_object* v___x_101_; 
lean_dec(v_h__3_95_);
lean_dec(v_h__1_93_);
v_p_99_ = lean_ctor_get(v_x_92_, 0);
lean_inc(v_p_99_);
v_t_100_ = lean_ctor_get(v_x_92_, 1);
lean_inc(v_t_100_);
lean_dec_ref_known(v_x_92_, 2);
v___x_101_ = lean_apply_2(v_h__2_94_, v_p_99_, v_t_100_);
return v___x_101_;
}
default: 
{
lean_object* v___x_102_; 
lean_dec(v_h__2_94_);
lean_dec(v_h__1_93_);
v___x_102_ = lean_apply_3(v_h__3_95_, v_x_92_, lean_box(0), lean_box(0));
return v___x_102_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter(lean_object* v_I_103_, lean_object* v_motive_104_, lean_object* v_x_105_, lean_object* v_h__1_106_, lean_object* v_h__2_107_, lean_object* v_h__3_108_){
_start:
{
switch(lean_obj_tag(v_x_105_))
{
case 1:
{
lean_object* v_p_109_; lean_object* v_t_110_; lean_object* v___x_111_; 
lean_dec(v_h__3_108_);
lean_dec(v_h__2_107_);
v_p_109_ = lean_ctor_get(v_x_105_, 0);
lean_inc(v_p_109_);
v_t_110_ = lean_ctor_get(v_x_105_, 1);
lean_inc(v_t_110_);
lean_dec_ref_known(v_x_105_, 2);
v___x_111_ = lean_apply_2(v_h__1_106_, v_p_109_, v_t_110_);
return v___x_111_;
}
case 2:
{
lean_object* v_p_112_; lean_object* v_t_113_; lean_object* v___x_114_; 
lean_dec(v_h__3_108_);
lean_dec(v_h__1_106_);
v_p_112_ = lean_ctor_get(v_x_105_, 0);
lean_inc(v_p_112_);
v_t_113_ = lean_ctor_get(v_x_105_, 1);
lean_inc(v_t_113_);
lean_dec_ref_known(v_x_105_, 2);
v___x_114_ = lean_apply_2(v_h__2_107_, v_p_112_, v_t_113_);
return v___x_114_;
}
default: 
{
lean_object* v___x_115_; 
lean_dec(v_h__2_107_);
lean_dec(v_h__1_106_);
v___x_115_ = lean_apply_3(v_h__3_108_, v_x_105_, lean_box(0), lean_box(0));
return v___x_115_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter___boxed(lean_object* v_I_116_, lean_object* v_motive_117_, lean_object* v_x_118_, lean_object* v_h__1_119_, lean_object* v_h__2_120_, lean_object* v_h__3_121_){
_start:
{
lean_object* v_res_122_; 
v_res_122_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostLU_match__1_splitter(v_I_116_, v_motive_117_, v_x_118_, v_h__1_119_, v_h__2_120_, v_h__3_121_);
lean_dec_ref(v_I_116_);
return v_res_122_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg(lean_object* v_x_123_){
_start:
{
switch(lean_obj_tag(v_x_123_))
{
case 0:
{
uint8_t v___x_124_; 
v___x_124_ = 1;
return v___x_124_;
}
case 3:
{
uint8_t v___x_125_; 
v___x_125_ = 1;
return v___x_125_;
}
case 4:
{
uint8_t v___x_126_; 
v___x_126_ = 1;
return v___x_126_;
}
default: 
{
uint8_t v___x_127_; 
v___x_127_ = 0;
return v___x_127_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg___boxed(lean_object* v_x_128_){
_start:
{
uint8_t v_res_129_; lean_object* v_r_130_; 
v_res_129_ = lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg(v_x_128_);
lean_dec_ref(v_x_128_);
v_r_130_ = lean_box(v_res_129_);
return v_r_130_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckAct(lean_object* v_I_131_, lean_object* v_x_132_){
_start:
{
uint8_t v___x_133_; 
v___x_133_ = lp_island__logistics__proof_IslandLogistics_isTruckAct___redArg(v_x_132_);
return v___x_133_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckAct___boxed(lean_object* v_I_134_, lean_object* v_x_135_){
_start:
{
uint8_t v_res_136_; lean_object* v_r_137_; 
v_res_136_ = lp_island__logistics__proof_IslandLogistics_isTruckAct(v_I_134_, v_x_135_);
lean_dec_ref(v_x_135_);
lean_dec_ref(v_I_134_);
v_r_137_ = lean_box(v_res_136_);
return v_r_137_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter___redArg(lean_object* v_x_138_, lean_object* v_h__1_139_, lean_object* v_h__2_140_, lean_object* v_h__3_141_, lean_object* v_h__4_142_){
_start:
{
switch(lean_obj_tag(v_x_138_))
{
case 0:
{
lean_object* v_t_143_; lean_object* v_u_144_; lean_object* v_v_145_; lean_object* v___x_146_; 
lean_dec(v_h__4_142_);
lean_dec(v_h__3_141_);
lean_dec(v_h__2_140_);
v_t_143_ = lean_ctor_get(v_x_138_, 0);
lean_inc(v_t_143_);
v_u_144_ = lean_ctor_get(v_x_138_, 1);
lean_inc(v_u_144_);
v_v_145_ = lean_ctor_get(v_x_138_, 2);
lean_inc(v_v_145_);
lean_dec_ref_known(v_x_138_, 3);
v___x_146_ = lean_apply_3(v_h__1_139_, v_t_143_, v_u_144_, v_v_145_);
return v___x_146_;
}
case 3:
{
lean_object* v_t_147_; lean_object* v_f_148_; lean_object* v___x_149_; 
lean_dec(v_h__4_142_);
lean_dec(v_h__3_141_);
lean_dec(v_h__1_139_);
v_t_147_ = lean_ctor_get(v_x_138_, 0);
lean_inc(v_t_147_);
v_f_148_ = lean_ctor_get(v_x_138_, 1);
lean_inc(v_f_148_);
lean_dec_ref_known(v_x_138_, 2);
v___x_149_ = lean_apply_2(v_h__2_140_, v_t_147_, v_f_148_);
return v___x_149_;
}
case 4:
{
lean_object* v_t_150_; lean_object* v_f_151_; lean_object* v___x_152_; 
lean_dec(v_h__4_142_);
lean_dec(v_h__2_140_);
lean_dec(v_h__1_139_);
v_t_150_ = lean_ctor_get(v_x_138_, 0);
lean_inc(v_t_150_);
v_f_151_ = lean_ctor_get(v_x_138_, 1);
lean_inc(v_f_151_);
lean_dec_ref_known(v_x_138_, 2);
v___x_152_ = lean_apply_2(v_h__3_141_, v_t_150_, v_f_151_);
return v___x_152_;
}
default: 
{
lean_object* v___x_153_; 
lean_dec(v_h__3_141_);
lean_dec(v_h__2_140_);
lean_dec(v_h__1_139_);
v___x_153_ = lean_apply_4(v_h__4_142_, v_x_138_, lean_box(0), lean_box(0), lean_box(0));
return v___x_153_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter(lean_object* v_I_154_, lean_object* v_motive_155_, lean_object* v_x_156_, lean_object* v_h__1_157_, lean_object* v_h__2_158_, lean_object* v_h__3_159_, lean_object* v_h__4_160_){
_start:
{
switch(lean_obj_tag(v_x_156_))
{
case 0:
{
lean_object* v_t_161_; lean_object* v_u_162_; lean_object* v_v_163_; lean_object* v___x_164_; 
lean_dec(v_h__4_160_);
lean_dec(v_h__3_159_);
lean_dec(v_h__2_158_);
v_t_161_ = lean_ctor_get(v_x_156_, 0);
lean_inc(v_t_161_);
v_u_162_ = lean_ctor_get(v_x_156_, 1);
lean_inc(v_u_162_);
v_v_163_ = lean_ctor_get(v_x_156_, 2);
lean_inc(v_v_163_);
lean_dec_ref_known(v_x_156_, 3);
v___x_164_ = lean_apply_3(v_h__1_157_, v_t_161_, v_u_162_, v_v_163_);
return v___x_164_;
}
case 3:
{
lean_object* v_t_165_; lean_object* v_f_166_; lean_object* v___x_167_; 
lean_dec(v_h__4_160_);
lean_dec(v_h__3_159_);
lean_dec(v_h__1_157_);
v_t_165_ = lean_ctor_get(v_x_156_, 0);
lean_inc(v_t_165_);
v_f_166_ = lean_ctor_get(v_x_156_, 1);
lean_inc(v_f_166_);
lean_dec_ref_known(v_x_156_, 2);
v___x_167_ = lean_apply_2(v_h__2_158_, v_t_165_, v_f_166_);
return v___x_167_;
}
case 4:
{
lean_object* v_t_168_; lean_object* v_f_169_; lean_object* v___x_170_; 
lean_dec(v_h__4_160_);
lean_dec(v_h__2_158_);
lean_dec(v_h__1_157_);
v_t_168_ = lean_ctor_get(v_x_156_, 0);
lean_inc(v_t_168_);
v_f_169_ = lean_ctor_get(v_x_156_, 1);
lean_inc(v_f_169_);
lean_dec_ref_known(v_x_156_, 2);
v___x_170_ = lean_apply_2(v_h__3_159_, v_t_168_, v_f_169_);
return v___x_170_;
}
default: 
{
lean_object* v___x_171_; 
lean_dec(v_h__3_159_);
lean_dec(v_h__2_158_);
lean_dec(v_h__1_157_);
v___x_171_ = lean_apply_4(v_h__4_160_, v_x_156_, lean_box(0), lean_box(0), lean_box(0));
return v___x_171_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter___boxed(lean_object* v_I_172_, lean_object* v_motive_173_, lean_object* v_x_174_, lean_object* v_h__1_175_, lean_object* v_h__2_176_, lean_object* v_h__3_177_, lean_object* v_h__4_178_){
_start:
{
lean_object* v_res_179_; 
v_res_179_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_isTruckAct_match__1_splitter(v_I_172_, v_motive_173_, v_x_174_, v_h__1_175_, v_h__2_176_, v_h__3_177_, v_h__4_178_);
lean_dec_ref(v_I_172_);
return v_res_179_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter___redArg(lean_object* v_x_180_, lean_object* v_h__1_181_, lean_object* v_h__2_182_, lean_object* v_h__3_183_){
_start:
{
switch(lean_obj_tag(v_x_180_))
{
case 3:
{
lean_object* v_t_184_; lean_object* v_f_185_; lean_object* v___x_186_; 
lean_dec(v_h__3_183_);
lean_dec(v_h__2_182_);
v_t_184_ = lean_ctor_get(v_x_180_, 0);
lean_inc(v_t_184_);
v_f_185_ = lean_ctor_get(v_x_180_, 1);
lean_inc(v_f_185_);
lean_dec_ref_known(v_x_180_, 2);
v___x_186_ = lean_apply_2(v_h__1_181_, v_t_184_, v_f_185_);
return v___x_186_;
}
case 4:
{
lean_object* v_t_187_; lean_object* v_f_188_; lean_object* v___x_189_; 
lean_dec(v_h__3_183_);
lean_dec(v_h__1_181_);
v_t_187_ = lean_ctor_get(v_x_180_, 0);
lean_inc(v_t_187_);
v_f_188_ = lean_ctor_get(v_x_180_, 1);
lean_inc(v_f_188_);
lean_dec_ref_known(v_x_180_, 2);
v___x_189_ = lean_apply_2(v_h__2_182_, v_t_187_, v_f_188_);
return v___x_189_;
}
default: 
{
lean_object* v___x_190_; 
lean_dec(v_h__2_182_);
lean_dec(v_h__1_181_);
v___x_190_ = lean_apply_3(v_h__3_183_, v_x_180_, lean_box(0), lean_box(0));
return v___x_190_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter(lean_object* v_I_191_, lean_object* v_motive_192_, lean_object* v_x_193_, lean_object* v_h__1_194_, lean_object* v_h__2_195_, lean_object* v_h__3_196_){
_start:
{
switch(lean_obj_tag(v_x_193_))
{
case 3:
{
lean_object* v_t_197_; lean_object* v_f_198_; lean_object* v___x_199_; 
lean_dec(v_h__3_196_);
lean_dec(v_h__2_195_);
v_t_197_ = lean_ctor_get(v_x_193_, 0);
lean_inc(v_t_197_);
v_f_198_ = lean_ctor_get(v_x_193_, 1);
lean_inc(v_f_198_);
lean_dec_ref_known(v_x_193_, 2);
v___x_199_ = lean_apply_2(v_h__1_194_, v_t_197_, v_f_198_);
return v___x_199_;
}
case 4:
{
lean_object* v_t_200_; lean_object* v_f_201_; lean_object* v___x_202_; 
lean_dec(v_h__3_196_);
lean_dec(v_h__1_194_);
v_t_200_ = lean_ctor_get(v_x_193_, 0);
lean_inc(v_t_200_);
v_f_201_ = lean_ctor_get(v_x_193_, 1);
lean_inc(v_f_201_);
lean_dec_ref_known(v_x_193_, 2);
v___x_202_ = lean_apply_2(v_h__2_195_, v_t_200_, v_f_201_);
return v___x_202_;
}
default: 
{
lean_object* v___x_203_; 
lean_dec(v_h__2_195_);
lean_dec(v_h__1_194_);
v___x_203_ = lean_apply_3(v_h__3_196_, v_x_193_, lean_box(0), lean_box(0));
return v___x_203_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter___boxed(lean_object* v_I_204_, lean_object* v_motive_205_, lean_object* v_x_206_, lean_object* v_h__1_207_, lean_object* v_h__2_208_, lean_object* v_h__3_209_){
_start:
{
lean_object* v_res_210_; 
v_res_210_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_actionCostBD_match__1_splitter(v_I_204_, v_motive_205_, v_x_206_, v_h__1_207_, v_h__2_208_, v_h__3_209_);
lean_dec_ref(v_I_204_);
return v_res_210_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potNS(lean_object* v_I_211_, lean_object* v_M_212_, lean_object* v_s_213_, lean_object* v_p_214_){
_start:
{
lean_object* v___x_215_; 
lean_inc(v_p_214_);
lean_inc_ref(v_s_213_);
v___x_215_ = lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(v_s_213_, v_p_214_);
if (lean_obj_tag(v___x_215_) == 0)
{
lean_object* v_distNS_216_; lean_object* v_pkgGoal_217_; lean_object* v___x_218_; lean_object* v___x_219_; lean_object* v___x_220_; 
v_distNS_216_ = lean_ctor_get(v_M_212_, 0);
lean_inc_ref(v_distNS_216_);
lean_dec_ref(v_M_212_);
v_pkgGoal_217_ = lean_ctor_get(v_I_211_, 10);
lean_inc_ref(v_pkgGoal_217_);
lean_dec_ref(v_I_211_);
lean_inc(v_p_214_);
v___x_218_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_213_, v_p_214_);
v___x_219_ = lean_apply_1(v_pkgGoal_217_, v_p_214_);
v___x_220_ = lean_apply_2(v_distNS_216_, v___x_218_, v___x_219_);
return v___x_220_;
}
else
{
lean_object* v_val_221_; lean_object* v_ferryNS_222_; lean_object* v_pkgGoal_223_; lean_object* v___x_224_; lean_object* v___x_225_; 
lean_dec_ref(v_s_213_);
v_val_221_ = lean_ctor_get(v___x_215_, 0);
lean_inc(v_val_221_);
lean_dec_ref_known(v___x_215_, 1);
v_ferryNS_222_ = lean_ctor_get(v_M_212_, 1);
lean_inc_ref(v_ferryNS_222_);
lean_dec_ref(v_M_212_);
v_pkgGoal_223_ = lean_ctor_get(v_I_211_, 10);
lean_inc_ref(v_pkgGoal_223_);
lean_dec_ref(v_I_211_);
v___x_224_ = lean_apply_1(v_pkgGoal_223_, v_p_214_);
v___x_225_ = lean_apply_2(v_ferryNS_222_, v_val_221_, v___x_224_);
return v___x_225_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__0(lean_object* v_I_226_, lean_object* v_s_227_, lean_object* v_pkgWeight_228_, lean_object* v_M_229_, lean_object* v_p_230_){
_start:
{
uint8_t v___x_231_; 
lean_inc(v_p_230_);
lean_inc_ref(v_s_227_);
lean_inc_ref(v_I_226_);
v___x_231_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_226_, v_s_227_, v_p_230_);
if (v___x_231_ == 0)
{
lean_object* v___x_232_; lean_object* v___x_233_; lean_object* v___x_234_; 
lean_inc(v_p_230_);
v___x_232_ = lean_apply_1(v_pkgWeight_228_, v_p_230_);
v___x_233_ = lp_island__logistics__proof_IslandLogistics_potNS(v_I_226_, v_M_229_, v_s_227_, v_p_230_);
v___x_234_ = lean_nat_mul(v___x_232_, v___x_233_);
lean_dec(v___x_233_);
lean_dec(v___x_232_);
return v___x_234_;
}
else
{
lean_object* v___x_235_; 
lean_dec(v_p_230_);
lean_dec_ref(v_M_229_);
lean_dec_ref(v_pkgWeight_228_);
lean_dec_ref(v_s_227_);
lean_dec_ref(v_I_226_);
v___x_235_ = lean_unsigned_to_nat(0u);
return v___x_235_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1(lean_object* v_I_236_, lean_object* v_s_237_, lean_object* v_cap_238_, lean_object* v_pkgWeight_239_, lean_object* v_M_240_, lean_object* v_p_241_){
_start:
{
uint8_t v___x_242_; 
lean_inc(v_p_241_);
lean_inc_ref(v_s_237_);
lean_inc_ref(v_I_236_);
v___x_242_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_236_, v_s_237_, v_p_241_);
if (v___x_242_ == 0)
{
lean_object* v___x_243_; lean_object* v___x_244_; lean_object* v___x_245_; uint8_t v___x_246_; 
v___x_243_ = lean_unsigned_to_nat(1u);
v___x_244_ = lean_nat_shiftr(v_cap_238_, v___x_243_);
lean_inc(v_p_241_);
v___x_245_ = lean_apply_1(v_pkgWeight_239_, v_p_241_);
v___x_246_ = lean_nat_dec_lt(v___x_244_, v___x_245_);
lean_dec(v___x_245_);
lean_dec(v___x_244_);
if (v___x_246_ == 0)
{
lean_object* v___x_247_; 
lean_dec(v_p_241_);
lean_dec_ref(v_M_240_);
lean_dec_ref(v_s_237_);
lean_dec_ref(v_I_236_);
v___x_247_ = lean_unsigned_to_nat(0u);
return v___x_247_;
}
else
{
lean_object* v___x_248_; 
v___x_248_ = lp_island__logistics__proof_IslandLogistics_potNS(v_I_236_, v_M_240_, v_s_237_, v_p_241_);
return v___x_248_;
}
}
else
{
lean_object* v___x_249_; 
lean_dec(v_p_241_);
lean_dec_ref(v_M_240_);
lean_dec_ref(v_pkgWeight_239_);
lean_dec_ref(v_s_237_);
lean_dec_ref(v_I_236_);
v___x_249_ = lean_unsigned_to_nat(0u);
return v___x_249_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1___boxed(lean_object* v_I_250_, lean_object* v_s_251_, lean_object* v_cap_252_, lean_object* v_pkgWeight_253_, lean_object* v_M_254_, lean_object* v_p_255_){
_start:
{
lean_object* v_res_256_; 
v_res_256_ = lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1(v_I_250_, v_s_251_, v_cap_252_, v_pkgWeight_253_, v_M_254_, v_p_255_);
lean_dec(v_cap_252_);
return v_res_256_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2(lean_object* v_I_257_, lean_object* v_s_258_, lean_object* v_pkgWeight_259_, lean_object* v_cap_260_, lean_object* v_M_261_, lean_object* v_p_262_){
_start:
{
uint8_t v___x_263_; 
lean_inc(v_p_262_);
lean_inc_ref(v_s_258_);
lean_inc_ref(v_I_257_);
v___x_263_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_257_, v_s_258_, v_p_262_);
if (v___x_263_ == 0)
{
lean_object* v___x_264_; lean_object* v___x_265_; lean_object* v___x_266_; uint8_t v___x_267_; 
lean_inc(v_p_262_);
v___x_264_ = lean_apply_1(v_pkgWeight_259_, v_p_262_);
v___x_265_ = lean_unsigned_to_nat(1u);
v___x_266_ = lean_nat_shiftr(v_cap_260_, v___x_265_);
v___x_267_ = lean_nat_dec_le(v___x_264_, v___x_266_);
lean_dec(v___x_266_);
if (v___x_267_ == 0)
{
lean_object* v___x_268_; 
lean_dec(v___x_264_);
lean_dec(v_p_262_);
lean_dec_ref(v_M_261_);
lean_dec_ref(v_s_258_);
lean_dec_ref(v_I_257_);
v___x_268_ = lean_unsigned_to_nat(0u);
return v___x_268_;
}
else
{
lean_object* v___x_269_; lean_object* v___x_270_; 
v___x_269_ = lp_island__logistics__proof_IslandLogistics_potNS(v_I_257_, v_M_261_, v_s_258_, v_p_262_);
v___x_270_ = lean_nat_mul(v___x_264_, v___x_269_);
lean_dec(v___x_269_);
lean_dec(v___x_264_);
return v___x_270_;
}
}
else
{
lean_object* v___x_271_; 
lean_dec(v_p_262_);
lean_dec_ref(v_M_261_);
lean_dec_ref(v_pkgWeight_259_);
lean_dec_ref(v_s_258_);
lean_dec_ref(v_I_257_);
v___x_271_ = lean_unsigned_to_nat(0u);
return v___x_271_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2___boxed(lean_object* v_I_272_, lean_object* v_s_273_, lean_object* v_pkgWeight_274_, lean_object* v_cap_275_, lean_object* v_M_276_, lean_object* v_p_277_){
_start:
{
lean_object* v_res_278_; 
v_res_278_ = lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2(v_I_272_, v_s_273_, v_pkgWeight_274_, v_cap_275_, v_M_276_, v_p_277_);
lean_dec(v_cap_275_);
return v_res_278_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck(lean_object* v_I_279_, lean_object* v_M_280_, lean_object* v_s_281_, lean_object* v_min__hw_282_){
_start:
{
lean_object* v_numPkgs_283_; lean_object* v_pkgWeight_284_; lean_object* v___f_285_; lean_object* v_cap_286_; lean_object* v___f_287_; lean_object* v___f_288_; lean_object* v_hd_289_; lean_object* v_lwd_290_; lean_object* v_twd_291_; lean_object* v___x_292_; 
v_numPkgs_283_ = lean_ctor_get(v_I_279_, 8);
lean_inc_n(v_numPkgs_283_, 3);
v_pkgWeight_284_ = lean_ctor_get(v_I_279_, 9);
lean_inc_ref_n(v_pkgWeight_284_, 3);
lean_inc_ref_n(v_M_280_, 2);
lean_inc_ref_n(v_s_281_, 3);
lean_inc_ref_n(v_I_279_, 3);
v___f_285_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__0), 5, 4);
lean_closure_set(v___f_285_, 0, v_I_279_);
lean_closure_set(v___f_285_, 1, v_s_281_);
lean_closure_set(v___f_285_, 2, v_pkgWeight_284_);
lean_closure_set(v___f_285_, 3, v_M_280_);
v_cap_286_ = lp_island__logistics__proof_IslandLogistics_maxDynEffCap(v_I_279_, v_s_281_);
lean_inc_n(v_cap_286_, 2);
v___f_287_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__1___boxed), 6, 5);
lean_closure_set(v___f_287_, 0, v_I_279_);
lean_closure_set(v___f_287_, 1, v_s_281_);
lean_closure_set(v___f_287_, 2, v_cap_286_);
lean_closure_set(v___f_287_, 3, v_pkgWeight_284_);
lean_closure_set(v___f_287_, 4, v_M_280_);
v___f_288_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_hPackTruck___lam__2___boxed), 6, 5);
lean_closure_set(v___f_288_, 0, v_I_279_);
lean_closure_set(v___f_288_, 1, v_s_281_);
lean_closure_set(v___f_288_, 2, v_pkgWeight_284_);
lean_closure_set(v___f_288_, 3, v_cap_286_);
lean_closure_set(v___f_288_, 4, v_M_280_);
v_hd_289_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_283_, v___f_287_);
v_lwd_290_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_283_, v___f_288_);
v_twd_291_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_283_, v___f_285_);
v___x_292_ = lp_island__logistics__proof_IslandLogistics_packLB(v_hd_289_, v_min__hw_282_, v_lwd_290_, v_twd_291_, v_cap_286_);
lean_dec(v_cap_286_);
lean_dec(v_twd_291_);
lean_dec(v_lwd_290_);
lean_dec(v_hd_289_);
return v___x_292_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hPackTruck___boxed(lean_object* v_I_293_, lean_object* v_M_294_, lean_object* v_s_295_, lean_object* v_min__hw_296_){
_start:
{
lean_object* v_res_297_; 
v_res_297_ = lp_island__logistics__proof_IslandLogistics_hPackTruck(v_I_293_, v_M_294_, v_s_295_, v_min__hw_296_);
lean_dec(v_min__hw_296_);
return v_res_297_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object* v_x_298_, lean_object* v_h__1_299_, lean_object* v_h__2_300_){
_start:
{
if (lean_obj_tag(v_x_298_) == 0)
{
lean_object* v_l_301_; lean_object* v___x_302_; 
lean_dec(v_h__2_300_);
v_l_301_ = lean_ctor_get(v_x_298_, 0);
lean_inc(v_l_301_);
lean_dec_ref_known(v_x_298_, 1);
v___x_302_ = lean_apply_1(v_h__1_299_, v_l_301_);
return v___x_302_;
}
else
{
lean_object* v_f_303_; lean_object* v___x_304_; 
lean_dec(v_h__1_299_);
v_f_303_ = lean_ctor_get(v_x_298_, 0);
lean_inc(v_f_303_);
lean_dec_ref_known(v_x_298_, 1);
v___x_304_ = lean_apply_1(v_h__2_300_, v_f_303_);
return v___x_304_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object* v_I_305_, lean_object* v_motive_306_, lean_object* v_x_307_, lean_object* v_h__1_308_, lean_object* v_h__2_309_){
_start:
{
if (lean_obj_tag(v_x_307_) == 0)
{
lean_object* v_l_310_; lean_object* v___x_311_; 
lean_dec(v_h__2_309_);
v_l_310_ = lean_ctor_get(v_x_307_, 0);
lean_inc(v_l_310_);
lean_dec_ref_known(v_x_307_, 1);
v___x_311_ = lean_apply_1(v_h__1_308_, v_l_310_);
return v___x_311_;
}
else
{
lean_object* v_f_312_; lean_object* v___x_313_; 
lean_dec(v_h__1_308_);
v_f_312_ = lean_ctor_get(v_x_307_, 0);
lean_inc(v_f_312_);
lean_dec_ref_known(v_x_307_, 1);
v___x_313_ = lean_apply_1(v_h__2_309_, v_f_312_);
return v___x_313_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object* v_I_314_, lean_object* v_motive_315_, lean_object* v_x_316_, lean_object* v_h__1_317_, lean_object* v_h__2_318_){
_start:
{
lean_object* v_res_319_; 
v_res_319_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(v_I_314_, v_motive_315_, v_x_316_, v_h__1_317_, v_h__2_318_);
lean_dec_ref(v_I_314_);
return v_res_319_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter___redArg(lean_object* v_x_320_, lean_object* v_h__1_321_, lean_object* v_h__2_322_){
_start:
{
if (lean_obj_tag(v_x_320_) == 0)
{
lean_object* v___x_323_; lean_object* v___x_324_; 
lean_dec(v_h__2_322_);
v___x_323_ = lean_box(0);
v___x_324_ = lean_apply_1(v_h__1_321_, v___x_323_);
return v___x_324_;
}
else
{
lean_object* v_val_325_; lean_object* v___x_326_; 
lean_dec(v_h__1_321_);
v_val_325_ = lean_ctor_get(v_x_320_, 0);
lean_inc(v_val_325_);
lean_dec_ref_known(v_x_320_, 1);
v___x_326_ = lean_apply_1(v_h__2_322_, v_val_325_);
return v___x_326_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter(lean_object* v_I_327_, lean_object* v_motive_328_, lean_object* v_x_329_, lean_object* v_h__1_330_, lean_object* v_h__2_331_){
_start:
{
if (lean_obj_tag(v_x_329_) == 0)
{
lean_object* v___x_332_; lean_object* v___x_333_; 
lean_dec(v_h__2_331_);
v___x_332_ = lean_box(0);
v___x_333_ = lean_apply_1(v_h__1_330_, v___x_332_);
return v___x_333_;
}
else
{
lean_object* v_val_334_; lean_object* v___x_335_; 
lean_dec(v_h__1_330_);
v_val_334_ = lean_ctor_get(v_x_329_, 0);
lean_inc(v_val_334_);
lean_dec_ref_known(v_x_329_, 1);
v___x_335_ = lean_apply_1(v_h__2_331_, v_val_334_);
return v___x_335_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter___boxed(lean_object* v_I_336_, lean_object* v_motive_337_, lean_object* v_x_338_, lean_object* v_h__1_339_, lean_object* v_h__2_340_){
_start:
{
lean_object* v_res_341_; 
v_res_341_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_potNS_match__1_splitter(v_I_336_, v_motive_337_, v_x_338_, v_h__1_339_, v_h__2_340_);
lean_dec_ref(v_I_336_);
return v_res_341_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costMove(lean_object* v_I_342_, lean_object* v_00_u03c0_343_){
_start:
{
lean_object* v___x_344_; lean_object* v___x_345_; lean_object* v___x_346_; lean_object* v___x_347_; lean_object* v___x_348_; 
lean_inc_n(v_00_u03c0_343_, 2);
v___x_344_ = lp_island__logistics__proof_IslandLogistics_costDrive(v_I_342_, v_00_u03c0_343_);
v___x_345_ = lp_island__logistics__proof_IslandLogistics_costBD(v_I_342_, v_00_u03c0_343_);
v___x_346_ = lean_nat_add(v___x_344_, v___x_345_);
lean_dec(v___x_345_);
lean_dec(v___x_344_);
v___x_347_ = lp_island__logistics__proof_IslandLogistics_costSail(v_I_342_, v_00_u03c0_343_);
v___x_348_ = lean_nat_add(v___x_346_, v___x_347_);
lean_dec(v___x_347_);
lean_dec(v___x_346_);
return v___x_348_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costMove___boxed(lean_object* v_I_349_, lean_object* v_00_u03c0_350_){
_start:
{
lean_object* v_res_351_; 
v_res_351_ = lp_island__logistics__proof_IslandLogistics_costMove(v_I_349_, v_00_u03c0_350_);
lean_dec_ref(v_I_349_);
return v_res_351_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg(lean_object* v_x_352_){
_start:
{
switch(lean_obj_tag(v_x_352_))
{
case 1:
{
lean_object* v___x_353_; 
v___x_353_ = lean_unsigned_to_nat(0u);
return v___x_353_;
}
case 2:
{
lean_object* v___x_354_; 
v___x_354_ = lean_unsigned_to_nat(0u);
return v___x_354_;
}
case 5:
{
lean_object* v___x_355_; 
v___x_355_ = lean_unsigned_to_nat(3u);
return v___x_355_;
}
default: 
{
lean_object* v___x_356_; 
v___x_356_ = lean_unsigned_to_nat(1u);
return v___x_356_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg___boxed(lean_object* v_x_357_){
_start:
{
lean_object* v_res_358_; 
v_res_358_ = lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg(v_x_357_);
lean_dec_ref(v_x_357_);
return v_res_358_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost(lean_object* v_I_359_, lean_object* v_x_360_){
_start:
{
lean_object* v___x_361_; 
v___x_361_ = lp_island__logistics__proof_IslandLogistics_stepMoveCost___redArg(v_x_360_);
return v___x_361_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepMoveCost___boxed(lean_object* v_I_362_, lean_object* v_x_363_){
_start:
{
lean_object* v_res_364_; 
v_res_364_ = lp_island__logistics__proof_IslandLogistics_stepMoveCost(v_I_362_, v_x_363_);
lean_dec_ref(v_x_363_);
lean_dec_ref(v_I_362_);
return v_res_364_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot___redArg(lean_object* v_M_365_, lean_object* v_s_366_, lean_object* v_t_367_, lean_object* v_g_368_){
_start:
{
lean_object* v_truckLoc_369_; lean_object* v_ferryLoc_370_; lean_object* v___x_371_; 
v_truckLoc_369_ = lean_ctor_get(v_s_366_, 0);
lean_inc_ref(v_truckLoc_369_);
v_ferryLoc_370_ = lean_ctor_get(v_s_366_, 1);
lean_inc_ref(v_ferryLoc_370_);
lean_dec_ref(v_s_366_);
v___x_371_ = lean_apply_1(v_truckLoc_369_, v_t_367_);
if (lean_obj_tag(v___x_371_) == 0)
{
lean_object* v_l_372_; lean_object* v_distFull_373_; lean_object* v___x_374_; 
lean_dec_ref(v_ferryLoc_370_);
v_l_372_ = lean_ctor_get(v___x_371_, 0);
lean_inc(v_l_372_);
lean_dec_ref_known(v___x_371_, 1);
v_distFull_373_ = lean_ctor_get(v_M_365_, 0);
lean_inc_ref(v_distFull_373_);
lean_dec_ref(v_M_365_);
v___x_374_ = lean_apply_2(v_distFull_373_, v_l_372_, v_g_368_);
return v___x_374_;
}
else
{
lean_object* v_f_375_; lean_object* v_ferryFull_376_; lean_object* v___x_377_; lean_object* v___x_378_; 
v_f_375_ = lean_ctor_get(v___x_371_, 0);
lean_inc_n(v_f_375_, 2);
lean_dec_ref_known(v___x_371_, 1);
v_ferryFull_376_ = lean_ctor_get(v_M_365_, 1);
lean_inc_ref(v_ferryFull_376_);
lean_dec_ref(v_M_365_);
v___x_377_ = lean_apply_1(v_ferryLoc_370_, v_f_375_);
v___x_378_ = lean_apply_3(v_ferryFull_376_, v_f_375_, v___x_377_, v_g_368_);
return v___x_378_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot(lean_object* v_I_379_, lean_object* v_M_380_, lean_object* v_s_381_, lean_object* v_t_382_, lean_object* v_g_383_){
_start:
{
lean_object* v___x_384_; 
v___x_384_ = lp_island__logistics__proof_IslandLogistics_truckFullPot___redArg(v_M_380_, v_s_381_, v_t_382_, v_g_383_);
return v___x_384_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckFullPot___boxed(lean_object* v_I_385_, lean_object* v_M_386_, lean_object* v_s_387_, lean_object* v_t_388_, lean_object* v_g_389_){
_start:
{
lean_object* v_res_390_; 
v_res_390_ = lp_island__logistics__proof_IslandLogistics_truckFullPot(v_I_385_, v_M_386_, v_s_387_, v_t_388_, v_g_389_);
lean_dec_ref(v_I_385_);
return v_res_390_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot___redArg(lean_object* v_M_391_, lean_object* v_s_392_, lean_object* v_p_393_, lean_object* v_g_394_){
_start:
{
lean_object* v_pkgLoc_395_; lean_object* v___x_396_; 
v_pkgLoc_395_ = lean_ctor_get(v_s_392_, 2);
lean_inc_ref(v_pkgLoc_395_);
v___x_396_ = lean_apply_1(v_pkgLoc_395_, v_p_393_);
if (lean_obj_tag(v___x_396_) == 0)
{
lean_object* v_l_397_; lean_object* v_distFull_398_; lean_object* v___x_399_; 
lean_dec_ref(v_s_392_);
v_l_397_ = lean_ctor_get(v___x_396_, 0);
lean_inc(v_l_397_);
lean_dec_ref_known(v___x_396_, 1);
v_distFull_398_ = lean_ctor_get(v_M_391_, 0);
lean_inc_ref(v_distFull_398_);
lean_dec_ref(v_M_391_);
v___x_399_ = lean_apply_2(v_distFull_398_, v_l_397_, v_g_394_);
return v___x_399_;
}
else
{
lean_object* v_t_400_; lean_object* v___x_401_; 
v_t_400_ = lean_ctor_get(v___x_396_, 0);
lean_inc(v_t_400_);
lean_dec_ref_known(v___x_396_, 1);
v___x_401_ = lp_island__logistics__proof_IslandLogistics_truckFullPot___redArg(v_M_391_, v_s_392_, v_t_400_, v_g_394_);
return v___x_401_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot(lean_object* v_I_402_, lean_object* v_M_403_, lean_object* v_s_404_, lean_object* v_p_405_, lean_object* v_g_406_){
_start:
{
lean_object* v___x_407_; 
v___x_407_ = lp_island__logistics__proof_IslandLogistics_pkgFullPot___redArg(v_M_403_, v_s_404_, v_p_405_, v_g_406_);
return v___x_407_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pkgFullPot___boxed(lean_object* v_I_408_, lean_object* v_M_409_, lean_object* v_s_410_, lean_object* v_p_411_, lean_object* v_g_412_){
_start:
{
lean_object* v_res_413_; 
v_res_413_ = lp_island__logistics__proof_IslandLogistics_pkgFullPot(v_I_408_, v_M_409_, v_s_410_, v_p_411_, v_g_412_);
lean_dec_ref(v_I_408_);
return v_res_413_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter___redArg(lean_object* v_x_414_, lean_object* v_h__1_415_, lean_object* v_h__2_416_){
_start:
{
if (lean_obj_tag(v_x_414_) == 0)
{
lean_object* v_l_417_; lean_object* v___x_418_; 
lean_dec(v_h__2_416_);
v_l_417_ = lean_ctor_get(v_x_414_, 0);
lean_inc(v_l_417_);
lean_dec_ref_known(v_x_414_, 1);
v___x_418_ = lean_apply_1(v_h__1_415_, v_l_417_);
return v___x_418_;
}
else
{
lean_object* v_f_419_; lean_object* v___x_420_; 
lean_dec(v_h__1_415_);
v_f_419_ = lean_ctor_get(v_x_414_, 0);
lean_inc(v_f_419_);
lean_dec_ref_known(v_x_414_, 1);
v___x_420_ = lean_apply_1(v_h__2_416_, v_f_419_);
return v___x_420_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter(lean_object* v_I_421_, lean_object* v_motive_422_, lean_object* v_x_423_, lean_object* v_h__1_424_, lean_object* v_h__2_425_){
_start:
{
if (lean_obj_tag(v_x_423_) == 0)
{
lean_object* v_l_426_; lean_object* v___x_427_; 
lean_dec(v_h__2_425_);
v_l_426_ = lean_ctor_get(v_x_423_, 0);
lean_inc(v_l_426_);
lean_dec_ref_known(v_x_423_, 1);
v___x_427_ = lean_apply_1(v_h__1_424_, v_l_426_);
return v___x_427_;
}
else
{
lean_object* v_f_428_; lean_object* v___x_429_; 
lean_dec(v_h__1_424_);
v_f_428_ = lean_ctor_get(v_x_423_, 0);
lean_inc(v_f_428_);
lean_dec_ref_known(v_x_423_, 1);
v___x_429_ = lean_apply_1(v_h__2_425_, v_f_428_);
return v___x_429_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter___boxed(lean_object* v_I_430_, lean_object* v_motive_431_, lean_object* v_x_432_, lean_object* v_h__1_433_, lean_object* v_h__2_434_){
_start:
{
lean_object* v_res_435_; 
v_res_435_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_truckFullPot_match__1_splitter(v_I_430_, v_motive_431_, v_x_432_, v_h__1_433_, v_h__2_434_);
lean_dec_ref(v_I_430_);
return v_res_435_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___redArg(lean_object* v_x_436_){
_start:
{
lean_object* v___x_437_; 
v___x_437_ = lean_obj_tag_nat(v_x_436_);
return v___x_437_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___redArg___boxed(lean_object* v_x_438_){
_start:
{
lean_object* v_res_439_; 
v_res_439_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___redArg(v_x_438_);
lean_dec_ref(v_x_438_);
return v_res_439_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl(lean_object* v_k_440_, lean_object* v_x_441_){
_start:
{
lean_object* v___x_442_; 
v___x_442_ = lean_obj_tag_nat(v_x_441_);
return v___x_442_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl___boxed(lean_object* v_k_443_, lean_object* v_x_444_){
_start:
{
lean_object* v_res_445_; 
v_res_445_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorIdx___impl(v_k_443_, v_x_444_);
lean_dec_ref(v_x_444_);
lean_dec(v_k_443_);
return v_res_445_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(lean_object* v_t_446_, lean_object* v_k_447_){
_start:
{
lean_object* v_i_448_; lean_object* v___x_449_; 
v_i_448_ = lean_ctor_get(v_t_446_, 0);
lean_inc(v_i_448_);
lean_dec_ref(v_t_446_);
v___x_449_ = lean_apply_1(v_k_447_, v_i_448_);
return v___x_449_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim(lean_object* v_k_450_, lean_object* v_motive_451_, lean_object* v_ctorIdx_452_, lean_object* v_t_453_, lean_object* v_h_454_, lean_object* v_k_455_){
_start:
{
lean_object* v___x_456_; 
v___x_456_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(v_t_453_, v_k_455_);
return v___x_456_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___boxed(lean_object* v_k_457_, lean_object* v_motive_458_, lean_object* v_ctorIdx_459_, lean_object* v_t_460_, lean_object* v_h_461_, lean_object* v_k_462_){
_start:
{
lean_object* v_res_463_; 
v_res_463_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim(v_k_457_, v_motive_458_, v_ctorIdx_459_, v_t_460_, v_h_461_, v_k_462_);
lean_dec(v_ctorIdx_459_);
lean_dec(v_k_457_);
return v_res_463_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim___redArg(lean_object* v_t_464_, lean_object* v_pickup_465_){
_start:
{
lean_object* v___x_466_; 
v___x_466_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(v_t_464_, v_pickup_465_);
return v___x_466_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim(lean_object* v_k_467_, lean_object* v_motive_468_, lean_object* v_t_469_, lean_object* v_h_470_, lean_object* v_pickup_471_){
_start:
{
lean_object* v___x_472_; 
v___x_472_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(v_t_469_, v_pickup_471_);
return v___x_472_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim___boxed(lean_object* v_k_473_, lean_object* v_motive_474_, lean_object* v_t_475_, lean_object* v_h_476_, lean_object* v_pickup_477_){
_start:
{
lean_object* v_res_478_; 
v_res_478_ = lp_island__logistics__proof_IslandLogistics_ExclEv_pickup_elim(v_k_473_, v_motive_474_, v_t_475_, v_h_476_, v_pickup_477_);
lean_dec(v_k_473_);
return v_res_478_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim___redArg(lean_object* v_t_479_, lean_object* v_deliver_480_){
_start:
{
lean_object* v___x_481_; 
v___x_481_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(v_t_479_, v_deliver_480_);
return v___x_481_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim(lean_object* v_k_482_, lean_object* v_motive_483_, lean_object* v_t_484_, lean_object* v_h_485_, lean_object* v_deliver_486_){
_start:
{
lean_object* v___x_487_; 
v___x_487_ = lp_island__logistics__proof_IslandLogistics_ExclEv_ctorElim___redArg(v_t_484_, v_deliver_486_);
return v___x_487_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim___boxed(lean_object* v_k_488_, lean_object* v_motive_489_, lean_object* v_t_490_, lean_object* v_h_491_, lean_object* v_deliver_492_){
_start:
{
lean_object* v_res_493_; 
v_res_493_ = lp_island__logistics__proof_IslandLogistics_ExclEv_deliver_elim(v_k_488_, v_motive_489_, v_t_490_, v_h_491_, v_deliver_492_);
lean_dec(v_k_488_);
return v_res_493_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(lean_object* v_x_494_, lean_object* v_x_495_){
_start:
{
if (lean_obj_tag(v_x_494_) == 0)
{
if (lean_obj_tag(v_x_495_) == 0)
{
lean_object* v_i_496_; lean_object* v_i_497_; uint8_t v___x_498_; 
v_i_496_ = lean_ctor_get(v_x_494_, 0);
v_i_497_ = lean_ctor_get(v_x_495_, 0);
v___x_498_ = lean_nat_dec_eq(v_i_496_, v_i_497_);
return v___x_498_;
}
else
{
uint8_t v___x_499_; 
v___x_499_ = 0;
return v___x_499_;
}
}
else
{
if (lean_obj_tag(v_x_495_) == 0)
{
uint8_t v___x_500_; 
v___x_500_ = 0;
return v___x_500_;
}
else
{
lean_object* v_i_501_; lean_object* v_i_502_; uint8_t v___x_503_; 
v_i_501_ = lean_ctor_get(v_x_494_, 0);
v_i_502_ = lean_ctor_get(v_x_495_, 0);
v___x_503_ = lean_nat_dec_eq(v_i_501_, v_i_502_);
return v___x_503_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg___boxed(lean_object* v_x_504_, lean_object* v_x_505_){
_start:
{
uint8_t v_res_506_; lean_object* v_r_507_; 
v_res_506_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(v_x_504_, v_x_505_);
lean_dec_ref(v_x_505_);
lean_dec_ref(v_x_504_);
v_r_507_ = lean_box(v_res_506_);
return v_r_507_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq(lean_object* v_k_508_, lean_object* v_x_509_, lean_object* v_x_510_){
_start:
{
uint8_t v___x_511_; 
v___x_511_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(v_x_509_, v_x_510_);
return v___x_511_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___boxed(lean_object* v_k_512_, lean_object* v_x_513_, lean_object* v_x_514_){
_start:
{
uint8_t v_res_515_; lean_object* v_r_516_; 
v_res_515_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq(v_k_512_, v_x_513_, v_x_514_);
lean_dec_ref(v_x_514_);
lean_dec_ref(v_x_513_);
lean_dec(v_k_512_);
v_r_516_ = lean_box(v_res_515_);
return v_r_516_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___redArg(lean_object* v_x_517_, lean_object* v_x_518_){
_start:
{
uint8_t v___x_519_; 
v___x_519_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(v_x_517_, v_x_518_);
return v___x_519_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___redArg___boxed(lean_object* v_x_520_, lean_object* v_x_521_){
_start:
{
uint8_t v_res_522_; lean_object* v_r_523_; 
v_res_522_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___redArg(v_x_520_, v_x_521_);
lean_dec_ref(v_x_521_);
lean_dec_ref(v_x_520_);
v_r_523_ = lean_box(v_res_522_);
return v_r_523_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv(lean_object* v_k_524_, lean_object* v_x_525_, lean_object* v_x_526_){
_start:
{
uint8_t v___x_527_; 
v___x_527_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv_decEq___redArg(v_x_525_, v_x_526_);
return v___x_527_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv___boxed(lean_object* v_k_528_, lean_object* v_x_529_, lean_object* v_x_530_){
_start:
{
uint8_t v_res_531_; lean_object* v_r_532_; 
v_res_531_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqExclEv(v_k_528_, v_x_529_, v_x_530_);
lean_dec_ref(v_x_530_);
lean_dec_ref(v_x_529_);
lean_dec(v_k_528_);
v_r_532_ = lean_box(v_res_531_);
return v_r_532_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg(lean_object* v_pairs_533_, lean_object* v_i_534_){
_start:
{
lean_object* v___x_535_; lean_object* v_fst_536_; 
v___x_535_ = lean_apply_1(v_pairs_533_, v_i_534_);
v_fst_536_ = lean_ctor_get(v___x_535_, 0);
lean_inc(v_fst_536_);
lean_dec_ref(v___x_535_);
if (lean_obj_tag(v_fst_536_) == 0)
{
uint8_t v___x_537_; 
v___x_537_ = 1;
return v___x_537_;
}
else
{
uint8_t v___x_538_; 
lean_dec_ref_known(v_fst_536_, 1);
v___x_538_ = 0;
return v___x_538_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg___boxed(lean_object* v_pairs_539_, lean_object* v_i_540_){
_start:
{
uint8_t v_res_541_; lean_object* v_r_542_; 
v_res_541_ = lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg(v_pairs_539_, v_i_540_);
v_r_542_ = lean_box(v_res_541_);
return v_r_542_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_exclInitPM(lean_object* v_I_543_, lean_object* v_k_544_, lean_object* v_pairs_545_, lean_object* v_i_546_){
_start:
{
uint8_t v___x_547_; 
v___x_547_ = lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg(v_pairs_545_, v_i_546_);
return v___x_547_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitPM___boxed(lean_object* v_I_548_, lean_object* v_k_549_, lean_object* v_pairs_550_, lean_object* v_i_551_){
_start:
{
uint8_t v_res_552_; lean_object* v_r_553_; 
v_res_552_ = lp_island__logistics__proof_IslandLogistics_exclInitPM(v_I_548_, v_k_549_, v_pairs_550_, v_i_551_);
lean_dec(v_k_549_);
lean_dec_ref(v_I_548_);
v_r_553_ = lean_box(v_res_552_);
return v_r_553_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg___lam__0(lean_object* v_pairs_554_, lean_object* v_i_555_){
_start:
{
lean_object* v___x_556_; lean_object* v_fst_557_; 
v___x_556_ = lean_apply_1(v_pairs_554_, v_i_555_);
v_fst_557_ = lean_ctor_get(v___x_556_, 0);
lean_inc(v_fst_557_);
lean_dec_ref(v___x_556_);
if (lean_obj_tag(v_fst_557_) == 0)
{
lean_object* v___x_558_; 
v___x_558_ = lean_unsigned_to_nat(1u);
return v___x_558_;
}
else
{
lean_object* v___x_559_; 
lean_dec_ref_known(v_fst_557_, 1);
v___x_559_ = lean_unsigned_to_nat(2u);
return v___x_559_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg(lean_object* v_k_560_, lean_object* v_pairs_561_){
_start:
{
lean_object* v___f_562_; lean_object* v___x_563_; 
v___f_562_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg___lam__0), 2, 1);
lean_closure_set(v___f_562_, 0, v_pairs_561_);
v___x_563_ = lp_island__logistics__proof_IslandLogistics_finSum(v_k_560_, v___f_562_);
return v___x_563_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv(lean_object* v_I_564_, lean_object* v_k_565_, lean_object* v_pairs_566_){
_start:
{
lean_object* v___x_567_; 
v___x_567_ = lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg(v_k_565_, v_pairs_566_);
return v___x_567_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclRemEv___boxed(lean_object* v_I_568_, lean_object* v_k_569_, lean_object* v_pairs_570_){
_start:
{
lean_object* v_res_571_; 
v_res_571_ = lp_island__logistics__proof_IslandLogistics_exclRemEv(v_I_568_, v_k_569_, v_pairs_570_);
lean_dec_ref(v_I_568_);
return v_res_571_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(lean_object* v_pairs_572_, lean_object* v_i_573_, uint8_t v_picked_574_){
_start:
{
if (v_picked_574_ == 0)
{
lean_object* v___x_575_; lean_object* v_fst_576_; 
v___x_575_ = lean_apply_1(v_pairs_572_, v_i_573_);
v_fst_576_ = lean_ctor_get(v___x_575_, 0);
lean_inc(v_fst_576_);
if (lean_obj_tag(v_fst_576_) == 0)
{
lean_object* v_snd_577_; 
v_snd_577_ = lean_ctor_get(v___x_575_, 1);
lean_inc(v_snd_577_);
lean_dec_ref(v___x_575_);
return v_snd_577_;
}
else
{
lean_object* v_val_578_; 
lean_dec_ref(v___x_575_);
v_val_578_ = lean_ctor_get(v_fst_576_, 0);
lean_inc(v_val_578_);
lean_dec_ref_known(v_fst_576_, 1);
return v_val_578_;
}
}
else
{
lean_object* v___x_579_; lean_object* v_snd_580_; 
v___x_579_ = lean_apply_1(v_pairs_572_, v_i_573_);
v_snd_580_ = lean_ctor_get(v___x_579_, 1);
lean_inc(v_snd_580_);
lean_dec_ref(v___x_579_);
return v_snd_580_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___redArg___boxed(lean_object* v_pairs_581_, lean_object* v_i_582_, lean_object* v_picked_583_){
_start:
{
uint8_t v_picked_boxed_584_; lean_object* v_res_585_; 
v_picked_boxed_584_ = lean_unbox(v_picked_583_);
v_res_585_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_581_, v_i_582_, v_picked_boxed_584_);
return v_res_585_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc(lean_object* v_I_586_, lean_object* v_k_587_, lean_object* v_pairs_588_, lean_object* v_i_589_, uint8_t v_picked_590_){
_start:
{
lean_object* v___x_591_; 
v___x_591_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_588_, v_i_589_, v_picked_590_);
return v___x_591_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLoc___boxed(lean_object* v_I_592_, lean_object* v_k_593_, lean_object* v_pairs_594_, lean_object* v_i_595_, lean_object* v_picked_596_){
_start:
{
uint8_t v_picked_boxed_597_; lean_object* v_res_598_; 
v_picked_boxed_597_ = lean_unbox(v_picked_596_);
v_res_598_ = lp_island__logistics__proof_IslandLogistics_exclLoc(v_I_592_, v_k_593_, v_pairs_594_, v_i_595_, v_picked_boxed_597_);
lean_dec(v_k_593_);
lean_dec_ref(v_I_592_);
return v_res_598_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc___redArg(lean_object* v_pairs_599_, lean_object* v_x_600_){
_start:
{
if (lean_obj_tag(v_x_600_) == 0)
{
lean_object* v_i_601_; uint8_t v___x_602_; lean_object* v___x_603_; 
v_i_601_ = lean_ctor_get(v_x_600_, 0);
lean_inc(v_i_601_);
lean_dec_ref_known(v_x_600_, 1);
v___x_602_ = 0;
v___x_603_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_599_, v_i_601_, v___x_602_);
return v___x_603_;
}
else
{
lean_object* v_i_604_; uint8_t v___x_605_; lean_object* v___x_606_; 
v_i_604_ = lean_ctor_get(v_x_600_, 0);
lean_inc(v_i_604_);
lean_dec_ref_known(v_x_600_, 1);
v___x_605_ = 1;
v___x_606_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_599_, v_i_604_, v___x_605_);
return v___x_606_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc(lean_object* v_I_607_, lean_object* v_k_608_, lean_object* v_pairs_609_, lean_object* v_x_610_){
_start:
{
lean_object* v___x_611_; 
v___x_611_ = lp_island__logistics__proof_IslandLogistics_exclEvLoc___redArg(v_pairs_609_, v_x_610_);
return v___x_611_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclEvLoc___boxed(lean_object* v_I_612_, lean_object* v_k_613_, lean_object* v_pairs_614_, lean_object* v_x_615_){
_start:
{
lean_object* v_res_616_; 
v_res_616_ = lp_island__logistics__proof_IslandLogistics_exclEvLoc(v_I_612_, v_k_613_, v_pairs_614_, v_x_615_);
lean_dec(v_k_613_);
lean_dec_ref(v_I_612_);
return v_res_616_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_setBit___redArg(lean_object* v_m_617_, lean_object* v_i_618_, lean_object* v_j_619_){
_start:
{
uint8_t v___x_620_; 
v___x_620_ = lean_nat_dec_eq(v_j_619_, v_i_618_);
if (v___x_620_ == 0)
{
lean_object* v___x_621_; uint8_t v___x_622_; 
v___x_621_ = lean_apply_1(v_m_617_, v_j_619_);
v___x_622_ = lean_unbox(v___x_621_);
return v___x_622_;
}
else
{
lean_dec(v_j_619_);
lean_dec_ref(v_m_617_);
return v___x_620_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_setBit___redArg___boxed(lean_object* v_m_623_, lean_object* v_i_624_, lean_object* v_j_625_){
_start:
{
uint8_t v_res_626_; lean_object* v_r_627_; 
v_res_626_ = lp_island__logistics__proof_IslandLogistics_setBit___redArg(v_m_623_, v_i_624_, v_j_625_);
lean_dec(v_i_624_);
v_r_627_ = lean_box(v_res_626_);
return v_r_627_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_setBit(lean_object* v_k_628_, lean_object* v_m_629_, lean_object* v_i_630_, lean_object* v_j_631_){
_start:
{
uint8_t v___x_632_; 
v___x_632_ = lp_island__logistics__proof_IslandLogistics_setBit___redArg(v_m_629_, v_i_630_, v_j_631_);
return v___x_632_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_setBit___boxed(lean_object* v_k_633_, lean_object* v_m_634_, lean_object* v_i_635_, lean_object* v_j_636_){
_start:
{
uint8_t v_res_637_; lean_object* v_r_638_; 
v_res_637_ = lp_island__logistics__proof_IslandLogistics_setBit(v_k_633_, v_m_634_, v_i_635_, v_j_636_);
lean_dec(v_i_635_);
lean_dec(v_k_633_);
v_r_638_ = lean_box(v_res_637_);
return v_r_638_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0(lean_object* v_a_639_, lean_object* v_b_640_, lean_object* v_i_641_, lean_object* v_h_642_){
_start:
{
lean_object* v_pm_643_; lean_object* v_pm_644_; lean_object* v___x_645_; lean_object* v___x_646_; uint8_t v___x_647_; 
v_pm_643_ = lean_ctor_get(v_a_639_, 0);
lean_inc_ref(v_pm_643_);
lean_dec_ref(v_a_639_);
v_pm_644_ = lean_ctor_get(v_b_640_, 0);
lean_inc_ref(v_pm_644_);
lean_dec_ref(v_b_640_);
lean_inc(v_i_641_);
v___x_645_ = lean_apply_1(v_pm_643_, v_i_641_);
v___x_646_ = lean_apply_1(v_pm_644_, v_i_641_);
v___x_647_ = lean_unbox(v___x_646_);
if (v___x_647_ == 0)
{
uint8_t v___x_648_; 
v___x_648_ = lean_unbox(v___x_645_);
if (v___x_648_ == 0)
{
uint8_t v___x_649_; 
v___x_649_ = 1;
return v___x_649_;
}
else
{
uint8_t v___x_650_; 
v___x_650_ = lean_unbox(v___x_646_);
return v___x_650_;
}
}
else
{
uint8_t v___x_651_; 
v___x_651_ = lean_unbox(v___x_645_);
return v___x_651_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0___boxed(lean_object* v_a_652_, lean_object* v_b_653_, lean_object* v_i_654_, lean_object* v_h_655_){
_start:
{
uint8_t v_res_656_; lean_object* v_r_657_; 
v_res_656_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0(v_a_652_, v_b_653_, v_i_654_, v_h_655_);
v_r_657_ = lean_box(v_res_656_);
return v_r_657_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1(lean_object* v_a_658_, lean_object* v_b_659_, uint8_t v___x_660_, lean_object* v_i_661_, lean_object* v_h_662_){
_start:
{
lean_object* v_dm_663_; lean_object* v_dm_664_; lean_object* v___x_665_; lean_object* v___x_666_; uint8_t v___x_667_; 
v_dm_663_ = lean_ctor_get(v_a_658_, 1);
lean_inc_ref(v_dm_663_);
lean_dec_ref(v_a_658_);
v_dm_664_ = lean_ctor_get(v_b_659_, 1);
lean_inc_ref(v_dm_664_);
lean_dec_ref(v_b_659_);
lean_inc(v_i_661_);
v___x_665_ = lean_apply_1(v_dm_663_, v_i_661_);
v___x_666_ = lean_apply_1(v_dm_664_, v_i_661_);
v___x_667_ = lean_unbox(v___x_666_);
if (v___x_667_ == 0)
{
uint8_t v___x_668_; 
v___x_668_ = lean_unbox(v___x_665_);
if (v___x_668_ == 0)
{
return v___x_660_;
}
else
{
uint8_t v___x_669_; 
v___x_669_ = lean_unbox(v___x_666_);
return v___x_669_;
}
}
else
{
uint8_t v___x_670_; 
v___x_670_ = lean_unbox(v___x_665_);
return v___x_670_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1___boxed(lean_object* v_a_671_, lean_object* v_b_672_, lean_object* v___x_673_, lean_object* v_i_674_, lean_object* v_h_675_){
_start:
{
uint8_t v___x_186__boxed_676_; uint8_t v_res_677_; lean_object* v_r_678_; 
v___x_186__boxed_676_ = lean_unbox(v___x_673_);
v_res_677_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1(v_a_671_, v_b_672_, v___x_186__boxed_676_, v_i_674_, v_h_675_);
v_r_678_ = lean_box(v_res_677_);
return v_r_678_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg(lean_object* v_k_679_, lean_object* v_a_680_, lean_object* v_b_681_){
_start:
{
lean_object* v___f_682_; uint8_t v___x_683_; 
lean_inc_ref(v_b_681_);
lean_inc_ref(v_a_680_);
v___f_682_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__0___boxed), 4, 2);
lean_closure_set(v___f_682_, 0, v_a_680_);
lean_closure_set(v___f_682_, 1, v_b_681_);
lean_inc(v_k_679_);
v___x_683_ = l___private_Init_Data_Nat_Lemmas_0__Nat_allLTTR_loop___redArg(v_k_679_, v___f_682_, v_k_679_);
if (v___x_683_ == 0)
{
lean_dec_ref(v_b_681_);
lean_dec_ref(v_a_680_);
lean_dec(v_k_679_);
return v___x_683_;
}
else
{
lean_object* v___x_684_; lean_object* v___f_685_; uint8_t v___x_686_; 
v___x_684_ = lean_box(v___x_683_);
lean_inc_ref(v_b_681_);
lean_inc_ref(v_a_680_);
v___f_685_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___lam__1___boxed), 5, 3);
lean_closure_set(v___f_685_, 0, v_a_680_);
lean_closure_set(v___f_685_, 1, v_b_681_);
lean_closure_set(v___f_685_, 2, v___x_684_);
lean_inc(v_k_679_);
v___x_686_ = l___private_Init_Data_Nat_Lemmas_0__Nat_allLTTR_loop___redArg(v_k_679_, v___f_685_, v_k_679_);
lean_dec(v_k_679_);
if (v___x_686_ == 0)
{
lean_dec_ref(v_b_681_);
lean_dec_ref(v_a_680_);
return v___x_686_;
}
else
{
lean_object* v_cur_687_; lean_object* v_cur_688_; uint8_t v___x_689_; 
v_cur_687_ = lean_ctor_get(v_a_680_, 2);
lean_inc(v_cur_687_);
lean_dec_ref(v_a_680_);
v_cur_688_ = lean_ctor_get(v_b_681_, 2);
lean_inc(v_cur_688_);
lean_dec_ref(v_b_681_);
v___x_689_ = lean_nat_dec_eq(v_cur_687_, v_cur_688_);
lean_dec(v_cur_688_);
lean_dec(v_cur_687_);
return v___x_689_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg___boxed(lean_object* v_k_690_, lean_object* v_a_691_, lean_object* v_b_692_){
_start:
{
uint8_t v_res_693_; lean_object* v_r_694_; 
v_res_693_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg(v_k_690_, v_a_691_, v_b_692_);
v_r_694_ = lean_box(v_res_693_);
return v_r_694_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey(lean_object* v_I_695_, lean_object* v_k_696_, lean_object* v_a_697_, lean_object* v_b_698_){
_start:
{
uint8_t v___x_699_; 
v___x_699_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg(v_k_696_, v_a_697_, v_b_698_);
return v___x_699_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___boxed(lean_object* v_I_700_, lean_object* v_k_701_, lean_object* v_a_702_, lean_object* v_b_703_){
_start:
{
uint8_t v_res_704_; lean_object* v_r_705_; 
v_res_704_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey(v_I_700_, v_k_701_, v_a_702_, v_b_703_);
lean_dec_ref(v_I_700_);
v_r_705_ = lean_box(v_res_704_);
return v_r_705_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert___redArg(lean_object* v_k_706_, lean_object* v_st_707_, lean_object* v_x_708_){
_start:
{
if (lean_obj_tag(v_x_708_) == 0)
{
lean_object* v___x_709_; 
lean_dec(v_k_706_);
v___x_709_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_709_, 0, v_st_707_);
lean_ctor_set(v___x_709_, 1, v_x_708_);
return v___x_709_;
}
else
{
lean_object* v_head_710_; lean_object* v_tail_711_; uint8_t v___x_712_; 
v_head_710_ = lean_ctor_get(v_x_708_, 0);
v_tail_711_ = lean_ctor_get(v_x_708_, 1);
lean_inc_ref(v_st_707_);
lean_inc(v_head_710_);
lean_inc(v_k_706_);
v___x_712_ = lp_island__logistics__proof_IslandLogistics_instDecidableSameDPKey___redArg(v_k_706_, v_head_710_, v_st_707_);
if (v___x_712_ == 0)
{
lean_object* v___x_714_; uint8_t v_isShared_715_; uint8_t v_isSharedCheck_720_; 
lean_inc(v_tail_711_);
lean_inc(v_head_710_);
v_isSharedCheck_720_ = !lean_is_exclusive(v_x_708_);
if (v_isSharedCheck_720_ == 0)
{
lean_object* v_unused_721_; lean_object* v_unused_722_; 
v_unused_721_ = lean_ctor_get(v_x_708_, 1);
lean_dec(v_unused_721_);
v_unused_722_ = lean_ctor_get(v_x_708_, 0);
lean_dec(v_unused_722_);
v___x_714_ = v_x_708_;
v_isShared_715_ = v_isSharedCheck_720_;
goto v_resetjp_713_;
}
else
{
lean_dec(v_x_708_);
v___x_714_ = lean_box(0);
v_isShared_715_ = v_isSharedCheck_720_;
goto v_resetjp_713_;
}
v_resetjp_713_:
{
lean_object* v___x_716_; lean_object* v___x_718_; 
v___x_716_ = lp_island__logistics__proof_IslandLogistics_exclDedupInsert___redArg(v_k_706_, v_st_707_, v_tail_711_);
if (v_isShared_715_ == 0)
{
lean_ctor_set(v___x_714_, 1, v___x_716_);
v___x_718_ = v___x_714_;
goto v_reusejp_717_;
}
else
{
lean_object* v_reuseFailAlloc_719_; 
v_reuseFailAlloc_719_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_719_, 0, v_head_710_);
lean_ctor_set(v_reuseFailAlloc_719_, 1, v___x_716_);
v___x_718_ = v_reuseFailAlloc_719_;
goto v_reusejp_717_;
}
v_reusejp_717_:
{
return v___x_718_;
}
}
}
else
{
lean_object* v_cost_723_; lean_object* v_cost_724_; uint8_t v___x_725_; 
lean_dec(v_k_706_);
v_cost_723_ = lean_ctor_get(v_st_707_, 3);
v_cost_724_ = lean_ctor_get(v_head_710_, 3);
v___x_725_ = lean_nat_dec_lt(v_cost_723_, v_cost_724_);
if (v___x_725_ == 0)
{
lean_dec_ref(v_st_707_);
return v_x_708_;
}
else
{
lean_object* v___x_727_; uint8_t v_isShared_728_; uint8_t v_isSharedCheck_732_; 
lean_inc(v_tail_711_);
v_isSharedCheck_732_ = !lean_is_exclusive(v_x_708_);
if (v_isSharedCheck_732_ == 0)
{
lean_object* v_unused_733_; lean_object* v_unused_734_; 
v_unused_733_ = lean_ctor_get(v_x_708_, 1);
lean_dec(v_unused_733_);
v_unused_734_ = lean_ctor_get(v_x_708_, 0);
lean_dec(v_unused_734_);
v___x_727_ = v_x_708_;
v_isShared_728_ = v_isSharedCheck_732_;
goto v_resetjp_726_;
}
else
{
lean_dec(v_x_708_);
v___x_727_ = lean_box(0);
v_isShared_728_ = v_isSharedCheck_732_;
goto v_resetjp_726_;
}
v_resetjp_726_:
{
lean_object* v___x_730_; 
if (v_isShared_728_ == 0)
{
lean_ctor_set(v___x_727_, 0, v_st_707_);
v___x_730_ = v___x_727_;
goto v_reusejp_729_;
}
else
{
lean_object* v_reuseFailAlloc_731_; 
v_reuseFailAlloc_731_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_731_, 0, v_st_707_);
lean_ctor_set(v_reuseFailAlloc_731_, 1, v_tail_711_);
v___x_730_ = v_reuseFailAlloc_731_;
goto v_reusejp_729_;
}
v_reusejp_729_:
{
return v___x_730_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert(lean_object* v_I_735_, lean_object* v_k_736_, lean_object* v_st_737_, lean_object* v_x_738_){
_start:
{
lean_object* v___x_739_; 
v___x_739_ = lp_island__logistics__proof_IslandLogistics_exclDedupInsert___redArg(v_k_736_, v_st_737_, v_x_738_);
return v___x_739_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupInsert___boxed(lean_object* v_I_740_, lean_object* v_k_741_, lean_object* v_st_742_, lean_object* v_x_743_){
_start:
{
lean_object* v_res_744_; 
v_res_744_ = lp_island__logistics__proof_IslandLogistics_exclDedupInsert(v_I_740_, v_k_741_, v_st_742_, v_x_743_);
lean_dec_ref(v_I_740_);
return v_res_744_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter___redArg(lean_object* v_x_745_, lean_object* v_h__1_746_, lean_object* v_h__2_747_){
_start:
{
if (lean_obj_tag(v_x_745_) == 0)
{
lean_object* v___x_748_; lean_object* v___x_749_; 
lean_dec(v_h__2_747_);
v___x_748_ = lean_box(0);
v___x_749_ = lean_apply_1(v_h__1_746_, v___x_748_);
return v___x_749_;
}
else
{
lean_object* v_head_750_; lean_object* v_tail_751_; lean_object* v___x_752_; 
lean_dec(v_h__1_746_);
v_head_750_ = lean_ctor_get(v_x_745_, 0);
lean_inc(v_head_750_);
v_tail_751_ = lean_ctor_get(v_x_745_, 1);
lean_inc(v_tail_751_);
lean_dec_ref_known(v_x_745_, 2);
v___x_752_ = lean_apply_2(v_h__2_747_, v_head_750_, v_tail_751_);
return v___x_752_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter(lean_object* v_I_753_, lean_object* v_k_754_, lean_object* v_motive_755_, lean_object* v_x_756_, lean_object* v_h__1_757_, lean_object* v_h__2_758_){
_start:
{
if (lean_obj_tag(v_x_756_) == 0)
{
lean_object* v___x_759_; lean_object* v___x_760_; 
lean_dec(v_h__2_758_);
v___x_759_ = lean_box(0);
v___x_760_ = lean_apply_1(v_h__1_757_, v___x_759_);
return v___x_760_;
}
else
{
lean_object* v_head_761_; lean_object* v_tail_762_; lean_object* v___x_763_; 
lean_dec(v_h__1_757_);
v_head_761_ = lean_ctor_get(v_x_756_, 0);
lean_inc(v_head_761_);
v_tail_762_ = lean_ctor_get(v_x_756_, 1);
lean_inc(v_tail_762_);
lean_dec_ref_known(v_x_756_, 2);
v___x_763_ = lean_apply_2(v_h__2_758_, v_head_761_, v_tail_762_);
return v___x_763_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter___boxed(lean_object* v_I_764_, lean_object* v_k_765_, lean_object* v_motive_766_, lean_object* v_x_767_, lean_object* v_h__1_768_, lean_object* v_h__2_769_){
_start:
{
lean_object* v_res_770_; 
v_res_770_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclDedupInsert_match__1_splitter(v_I_764_, v_k_765_, v_motive_766_, v_x_767_, v_h__1_768_, v_h__2_769_);
lean_dec(v_k_765_);
lean_dec_ref(v_I_764_);
return v_res_770_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(lean_object* v_k_771_, lean_object* v_x_772_){
_start:
{
if (lean_obj_tag(v_x_772_) == 0)
{
lean_dec(v_k_771_);
return v_x_772_;
}
else
{
lean_object* v_head_773_; lean_object* v_tail_774_; lean_object* v___x_775_; lean_object* v___x_776_; 
v_head_773_ = lean_ctor_get(v_x_772_, 0);
lean_inc(v_head_773_);
v_tail_774_ = lean_ctor_get(v_x_772_, 1);
lean_inc(v_tail_774_);
lean_dec_ref_known(v_x_772_, 2);
lean_inc(v_k_771_);
v___x_775_ = lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(v_k_771_, v_tail_774_);
v___x_776_ = lp_island__logistics__proof_IslandLogistics_exclDedupInsert___redArg(v_k_771_, v_head_773_, v___x_775_);
return v___x_776_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList(lean_object* v_I_777_, lean_object* v_k_778_, lean_object* v_x_779_){
_start:
{
lean_object* v___x_780_; 
v___x_780_ = lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(v_k_778_, v_x_779_);
return v___x_780_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclDedupList___boxed(lean_object* v_I_781_, lean_object* v_k_782_, lean_object* v_x_783_){
_start:
{
lean_object* v_res_784_; 
v_res_784_ = lp_island__logistics__proof_IslandLogistics_exclDedupList(v_I_781_, v_k_782_, v_x_783_);
lean_dec_ref(v_I_781_);
return v_res_784_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1(lean_object* v_x_785_){
_start:
{
uint8_t v___x_786_; 
v___x_786_ = 0;
return v___x_786_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1___boxed(lean_object* v_x_787_){
_start:
{
uint8_t v_res_788_; lean_object* v_r_789_; 
v_res_788_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__1(v_x_787_);
lean_dec(v_x_787_);
v_r_789_ = lean_box(v_res_788_);
return v_r_789_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0(uint8_t v_picked_790_, lean_object* v_x_791_){
_start:
{
return v_picked_790_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0___boxed(lean_object* v_picked_792_, lean_object* v_x_793_){
_start:
{
uint8_t v_picked_boxed_794_; uint8_t v_res_795_; lean_object* v_r_796_; 
v_picked_boxed_794_ = lean_unbox(v_picked_792_);
v_res_795_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0(v_picked_boxed_794_, v_x_793_);
lean_dec(v_x_793_);
v_r_796_ = lean_box(v_res_795_);
return v_r_796_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0(lean_object* v_I_798_, lean_object* v_k_799_, lean_object* v_pairs_800_, lean_object* v_startRow_801_, lean_object* v_a_802_, lean_object* v_a_803_){
_start:
{
if (lean_obj_tag(v_a_802_) == 0)
{
lean_object* v___x_804_; 
lean_dec_ref(v_startRow_801_);
lean_dec_ref(v_pairs_800_);
lean_dec(v_k_799_);
lean_dec_ref(v_I_798_);
v___x_804_ = l_List_reverse___redArg(v_a_803_);
return v___x_804_;
}
else
{
lean_object* v_head_805_; lean_object* v_tail_806_; lean_object* v___x_808_; uint8_t v_isShared_809_; uint8_t v_isSharedCheck_827_; 
v_head_805_ = lean_ctor_get(v_a_802_, 0);
v_tail_806_ = lean_ctor_get(v_a_802_, 1);
v_isSharedCheck_827_ = !lean_is_exclusive(v_a_802_);
if (v_isSharedCheck_827_ == 0)
{
v___x_808_ = v_a_802_;
v_isShared_809_ = v_isSharedCheck_827_;
goto v_resetjp_807_;
}
else
{
lean_inc(v_tail_806_);
lean_inc(v_head_805_);
lean_dec(v_a_802_);
v___x_808_ = lean_box(0);
v_isShared_809_ = v_isSharedCheck_827_;
goto v_resetjp_807_;
}
v_resetjp_807_:
{
lean_object* v___y_811_; lean_object* v_ipm_816_; uint8_t v_picked_817_; lean_object* v_loc_818_; lean_object* v_d_819_; 
lean_inc_ref_n(v_pairs_800_, 3);
lean_inc(v_k_799_);
lean_inc_ref(v_I_798_);
v_ipm_816_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_exclInitPM___boxed), 4, 3);
lean_closure_set(v_ipm_816_, 0, v_I_798_);
lean_closure_set(v_ipm_816_, 1, v_k_799_);
lean_closure_set(v_ipm_816_, 2, v_pairs_800_);
lean_inc_n(v_head_805_, 2);
v_picked_817_ = lp_island__logistics__proof_IslandLogistics_exclInitPM___redArg(v_pairs_800_, v_head_805_);
v_loc_818_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_800_, v_head_805_, v_picked_817_);
lean_inc_ref(v_startRow_801_);
lean_inc(v_loc_818_);
v_d_819_ = lean_apply_1(v_startRow_801_, v_loc_818_);
if (v_picked_817_ == 0)
{
lean_object* v___x_820_; lean_object* v___f_821_; lean_object* v___x_822_; lean_object* v___x_823_; 
v___x_820_ = lean_box(v_picked_817_);
v___f_821_ = lean_alloc_closure((void*)(lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___lam__0___boxed), 2, 1);
lean_closure_set(v___f_821_, 0, v___x_820_);
lean_inc(v_k_799_);
v___x_822_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_setBit___boxed), 4, 3);
lean_closure_set(v___x_822_, 0, v_k_799_);
lean_closure_set(v___x_822_, 1, v_ipm_816_);
lean_closure_set(v___x_822_, 2, v_head_805_);
v___x_823_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_823_, 0, v___x_822_);
lean_ctor_set(v___x_823_, 1, v___f_821_);
lean_ctor_set(v___x_823_, 2, v_loc_818_);
lean_ctor_set(v___x_823_, 3, v_d_819_);
v___y_811_ = v___x_823_;
goto v___jp_810_;
}
else
{
lean_object* v___f_824_; lean_object* v___x_825_; lean_object* v___x_826_; 
v___f_824_ = ((lean_object*)(lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0___closed__0));
lean_inc(v_k_799_);
v___x_825_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_setBit___boxed), 4, 3);
lean_closure_set(v___x_825_, 0, v_k_799_);
lean_closure_set(v___x_825_, 1, v___f_824_);
lean_closure_set(v___x_825_, 2, v_head_805_);
v___x_826_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_826_, 0, v_ipm_816_);
lean_ctor_set(v___x_826_, 1, v___x_825_);
lean_ctor_set(v___x_826_, 2, v_loc_818_);
lean_ctor_set(v___x_826_, 3, v_d_819_);
v___y_811_ = v___x_826_;
goto v___jp_810_;
}
v___jp_810_:
{
lean_object* v___x_813_; 
if (v_isShared_809_ == 0)
{
lean_ctor_set(v___x_808_, 1, v_a_803_);
lean_ctor_set(v___x_808_, 0, v___y_811_);
v___x_813_ = v___x_808_;
goto v_reusejp_812_;
}
else
{
lean_object* v_reuseFailAlloc_815_; 
v_reuseFailAlloc_815_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_815_, 0, v___y_811_);
lean_ctor_set(v_reuseFailAlloc_815_, 1, v_a_803_);
v___x_813_ = v_reuseFailAlloc_815_;
goto v_reusejp_812_;
}
v_reusejp_812_:
{
v_a_802_ = v_tail_806_;
v_a_803_ = v___x_813_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclInitLayer(lean_object* v_I_828_, lean_object* v_k_829_, lean_object* v_startRow_830_, lean_object* v_pairs_831_){
_start:
{
lean_object* v___x_832_; lean_object* v___x_833_; lean_object* v_raw_834_; lean_object* v___x_835_; 
lean_inc_n(v_k_829_, 2);
v___x_832_ = l_List_finRange(v_k_829_);
v___x_833_ = lean_box(0);
v_raw_834_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_exclInitLayer_spec__0(v_I_828_, v_k_829_, v_pairs_831_, v_startRow_830_, v___x_832_, v___x_833_);
v___x_835_ = lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(v_k_829_, v_raw_834_);
return v___x_835_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___redArg(lean_object* v_st_836_, lean_object* v_k_837_, lean_object* v_pairs_838_, lean_object* v_M_839_, lean_object* v_a_840_, lean_object* v_a_841_){
_start:
{
if (lean_obj_tag(v_a_840_) == 0)
{
lean_object* v___x_842_; 
lean_dec_ref(v_M_839_);
lean_dec_ref(v_pairs_838_);
lean_dec(v_k_837_);
lean_dec_ref(v_st_836_);
v___x_842_ = lean_array_to_list(v_a_841_);
return v___x_842_;
}
else
{
lean_object* v_head_843_; lean_object* v_tail_844_; lean_object* v_val_846_; lean_object* v_pm_849_; lean_object* v_dm_850_; lean_object* v_cur_851_; lean_object* v_cost_852_; lean_object* v___x_853_; uint8_t v___x_854_; 
v_head_843_ = lean_ctor_get(v_a_840_, 0);
lean_inc_n(v_head_843_, 2);
v_tail_844_ = lean_ctor_get(v_a_840_, 1);
lean_inc(v_tail_844_);
lean_dec_ref_known(v_a_840_, 2);
v_pm_849_ = lean_ctor_get(v_st_836_, 0);
v_dm_850_ = lean_ctor_get(v_st_836_, 1);
v_cur_851_ = lean_ctor_get(v_st_836_, 2);
v_cost_852_ = lean_ctor_get(v_st_836_, 3);
lean_inc_ref(v_dm_850_);
v___x_853_ = lean_apply_1(v_dm_850_, v_head_843_);
v___x_854_ = lean_unbox(v___x_853_);
if (v___x_854_ == 0)
{
lean_object* v_distFull_855_; lean_object* v_picked_856_; uint8_t v___x_857_; lean_object* v_loc_858_; lean_object* v___x_859_; lean_object* v_nc_860_; uint8_t v___x_861_; 
v_distFull_855_ = lean_ctor_get(v_M_839_, 0);
lean_inc_ref(v_pm_849_);
lean_inc_n(v_head_843_, 2);
v_picked_856_ = lean_apply_1(v_pm_849_, v_head_843_);
v___x_857_ = lean_unbox(v_picked_856_);
lean_inc_ref(v_pairs_838_);
v_loc_858_ = lp_island__logistics__proof_IslandLogistics_exclLoc___redArg(v_pairs_838_, v_head_843_, v___x_857_);
lean_inc_ref(v_distFull_855_);
lean_inc(v_loc_858_);
lean_inc(v_cur_851_);
v___x_859_ = lean_apply_2(v_distFull_855_, v_cur_851_, v_loc_858_);
v_nc_860_ = lean_nat_add(v_cost_852_, v___x_859_);
lean_dec(v___x_859_);
v___x_861_ = lean_unbox(v_picked_856_);
if (v___x_861_ == 0)
{
lean_object* v___x_862_; lean_object* v___x_863_; 
lean_inc_ref(v_pm_849_);
lean_inc(v_k_837_);
v___x_862_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_setBit___boxed), 4, 3);
lean_closure_set(v___x_862_, 0, v_k_837_);
lean_closure_set(v___x_862_, 1, v_pm_849_);
lean_closure_set(v___x_862_, 2, v_head_843_);
lean_inc_ref(v_dm_850_);
v___x_863_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_863_, 0, v___x_862_);
lean_ctor_set(v___x_863_, 1, v_dm_850_);
lean_ctor_set(v___x_863_, 2, v_loc_858_);
lean_ctor_set(v___x_863_, 3, v_nc_860_);
v_val_846_ = v___x_863_;
goto v___jp_845_;
}
else
{
lean_object* v___x_864_; lean_object* v___x_865_; 
lean_inc_ref(v_dm_850_);
lean_inc(v_k_837_);
v___x_864_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_setBit___boxed), 4, 3);
lean_closure_set(v___x_864_, 0, v_k_837_);
lean_closure_set(v___x_864_, 1, v_dm_850_);
lean_closure_set(v___x_864_, 2, v_head_843_);
lean_inc_ref(v_pm_849_);
v___x_865_ = lean_alloc_ctor(0, 4, 0);
lean_ctor_set(v___x_865_, 0, v_pm_849_);
lean_ctor_set(v___x_865_, 1, v___x_864_);
lean_ctor_set(v___x_865_, 2, v_loc_858_);
lean_ctor_set(v___x_865_, 3, v_nc_860_);
v_val_846_ = v___x_865_;
goto v___jp_845_;
}
}
else
{
lean_dec(v_head_843_);
v_a_840_ = v_tail_844_;
goto _start;
}
v___jp_845_:
{
lean_object* v___x_847_; 
v___x_847_ = lean_array_push(v_a_841_, v_val_846_);
v_a_840_ = v_tail_844_;
v_a_841_ = v___x_847_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1(lean_object* v_k_869_, lean_object* v_I_870_, lean_object* v_pairs_871_, lean_object* v_M_872_, lean_object* v_a_873_, lean_object* v_a_874_){
_start:
{
if (lean_obj_tag(v_a_873_) == 0)
{
lean_object* v___x_875_; 
lean_dec_ref(v_M_872_);
lean_dec_ref(v_pairs_871_);
lean_dec(v_k_869_);
v___x_875_ = lean_array_to_list(v_a_874_);
return v___x_875_;
}
else
{
lean_object* v_head_876_; lean_object* v_tail_877_; lean_object* v___x_878_; lean_object* v___x_879_; lean_object* v___x_880_; lean_object* v___x_881_; 
v_head_876_ = lean_ctor_get(v_a_873_, 0);
lean_inc(v_head_876_);
v_tail_877_ = lean_ctor_get(v_a_873_, 1);
lean_inc(v_tail_877_);
lean_dec_ref_known(v_a_873_, 2);
lean_inc_n(v_k_869_, 2);
v___x_878_ = l_List_finRange(v_k_869_);
v___x_879_ = ((lean_object*)(lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0));
lean_inc_ref(v_M_872_);
lean_inc_ref(v_pairs_871_);
v___x_880_ = lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___redArg(v_head_876_, v_k_869_, v_pairs_871_, v_M_872_, v___x_878_, v___x_879_);
v___x_881_ = l_List_foldl___at___00Array_appendList_spec__0___redArg(v_a_874_, v___x_880_);
v_a_873_ = v_tail_877_;
v_a_874_ = v___x_881_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___boxed(lean_object* v_k_883_, lean_object* v_I_884_, lean_object* v_pairs_885_, lean_object* v_M_886_, lean_object* v_a_887_, lean_object* v_a_888_){
_start:
{
lean_object* v_res_889_; 
v_res_889_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1(v_k_883_, v_I_884_, v_pairs_885_, v_M_886_, v_a_887_, v_a_888_);
lean_dec_ref(v_I_884_);
return v_res_889_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1(lean_object* v_I_890_, lean_object* v_k_891_, lean_object* v_pairs_892_, lean_object* v_M_893_, lean_object* v_a_894_, lean_object* v_a_895_){
_start:
{
if (lean_obj_tag(v_a_894_) == 0)
{
lean_object* v___x_896_; 
lean_dec_ref(v_M_893_);
lean_dec_ref(v_pairs_892_);
lean_dec(v_k_891_);
v___x_896_ = lean_array_to_list(v_a_895_);
return v___x_896_;
}
else
{
lean_object* v_head_897_; lean_object* v_tail_898_; lean_object* v___x_899_; lean_object* v___x_900_; lean_object* v___x_901_; lean_object* v___x_902_; lean_object* v___x_903_; 
v_head_897_ = lean_ctor_get(v_a_894_, 0);
lean_inc(v_head_897_);
v_tail_898_ = lean_ctor_get(v_a_894_, 1);
lean_inc(v_tail_898_);
lean_dec_ref_known(v_a_894_, 2);
lean_inc_n(v_k_891_, 2);
v___x_899_ = l_List_finRange(v_k_891_);
v___x_900_ = ((lean_object*)(lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0));
lean_inc_ref(v_M_893_);
lean_inc_ref(v_pairs_892_);
v___x_901_ = lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___redArg(v_head_897_, v_k_891_, v_pairs_892_, v_M_893_, v___x_899_, v___x_900_);
v___x_902_ = l_List_foldl___at___00Array_appendList_spec__0___redArg(v_a_895_, v___x_901_);
v___x_903_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1(v_k_891_, v_I_890_, v_pairs_892_, v_M_893_, v_tail_898_, v___x_902_);
return v___x_903_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1___boxed(lean_object* v_I_904_, lean_object* v_k_905_, lean_object* v_pairs_906_, lean_object* v_M_907_, lean_object* v_a_908_, lean_object* v_a_909_){
_start:
{
lean_object* v_res_910_; 
v_res_910_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1(v_I_904_, v_k_905_, v_pairs_906_, v_M_907_, v_a_908_, v_a_909_);
lean_dec_ref(v_I_904_);
return v_res_910_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclStepLayer(lean_object* v_I_911_, lean_object* v_M_912_, lean_object* v_k_913_, lean_object* v_pairs_914_, lean_object* v_layer_915_){
_start:
{
lean_object* v___x_916_; lean_object* v_raw_917_; lean_object* v___x_918_; 
v___x_916_ = ((lean_object*)(lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00__private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1_spec__1___closed__0));
lean_inc(v_k_913_);
v_raw_917_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_exclStepLayer_spec__1(v_I_911_, v_k_913_, v_pairs_914_, v_M_912_, v_layer_915_, v___x_916_);
v___x_918_ = lp_island__logistics__proof_IslandLogistics_exclDedupList___redArg(v_k_913_, v_raw_917_);
return v___x_918_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclStepLayer___boxed(lean_object* v_I_919_, lean_object* v_M_920_, lean_object* v_k_921_, lean_object* v_pairs_922_, lean_object* v_layer_923_){
_start:
{
lean_object* v_res_924_; 
v_res_924_ = lp_island__logistics__proof_IslandLogistics_exclStepLayer(v_I_919_, v_M_920_, v_k_921_, v_pairs_922_, v_layer_923_);
lean_dec_ref(v_I_919_);
return v_res_924_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0(lean_object* v_st_925_, lean_object* v_I_926_, lean_object* v_k_927_, lean_object* v_pairs_928_, lean_object* v_M_929_, lean_object* v_a_930_, lean_object* v_a_931_){
_start:
{
lean_object* v___x_932_; 
v___x_932_ = lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___redArg(v_st_925_, v_k_927_, v_pairs_928_, v_M_929_, v_a_930_, v_a_931_);
return v___x_932_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0___boxed(lean_object* v_st_933_, lean_object* v_I_934_, lean_object* v_k_935_, lean_object* v_pairs_936_, lean_object* v_M_937_, lean_object* v_a_938_, lean_object* v_a_939_){
_start:
{
lean_object* v_res_940_; 
v_res_940_ = lp_island__logistics__proof_List_filterMapTR_go___at___00IslandLogistics_exclStepLayer_spec__0(v_st_933_, v_I_934_, v_k_935_, v_pairs_936_, v_M_937_, v_a_938_, v_a_939_);
lean_dec_ref(v_I_934_);
return v_res_940_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclIterLayers(lean_object* v_I_941_, lean_object* v_M_942_, lean_object* v_k_943_, lean_object* v_pairs_944_, lean_object* v_x_945_, lean_object* v_x_946_){
_start:
{
lean_object* v_zero_947_; uint8_t v_isZero_948_; 
v_zero_947_ = lean_unsigned_to_nat(0u);
v_isZero_948_ = lean_nat_dec_eq(v_x_945_, v_zero_947_);
if (v_isZero_948_ == 1)
{
lean_dec(v_x_945_);
lean_dec_ref(v_pairs_944_);
lean_dec(v_k_943_);
lean_dec_ref(v_M_942_);
return v_x_946_;
}
else
{
lean_object* v_one_949_; lean_object* v_n_950_; lean_object* v___x_951_; 
v_one_949_ = lean_unsigned_to_nat(1u);
v_n_950_ = lean_nat_sub(v_x_945_, v_one_949_);
lean_dec(v_x_945_);
lean_inc_ref(v_pairs_944_);
lean_inc(v_k_943_);
lean_inc_ref(v_M_942_);
v___x_951_ = lp_island__logistics__proof_IslandLogistics_exclStepLayer(v_I_941_, v_M_942_, v_k_943_, v_pairs_944_, v_x_946_);
v_x_945_ = v_n_950_;
v_x_946_ = v___x_951_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclIterLayers___boxed(lean_object* v_I_953_, lean_object* v_M_954_, lean_object* v_k_955_, lean_object* v_pairs_956_, lean_object* v_x_957_, lean_object* v_x_958_){
_start:
{
lean_object* v_res_959_; 
v_res_959_ = lp_island__logistics__proof_IslandLogistics_exclIterLayers(v_I_953_, v_M_954_, v_k_955_, v_pairs_956_, v_x_957_, v_x_958_);
lean_dec_ref(v_I_953_);
return v_res_959_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(lean_object* v_x_960_){
_start:
{
if (lean_obj_tag(v_x_960_) == 0)
{
lean_object* v___x_961_; 
v___x_961_ = lean_unsigned_to_nat(0u);
return v___x_961_;
}
else
{
lean_object* v_tail_962_; 
v_tail_962_ = lean_ctor_get(v_x_960_, 1);
if (lean_obj_tag(v_tail_962_) == 0)
{
lean_object* v_head_963_; lean_object* v_cost_964_; 
v_head_963_ = lean_ctor_get(v_x_960_, 0);
v_cost_964_ = lean_ctor_get(v_head_963_, 3);
lean_inc(v_cost_964_);
return v_cost_964_;
}
else
{
lean_object* v_head_965_; lean_object* v_cost_966_; lean_object* v___x_967_; uint8_t v___x_968_; 
v_head_965_ = lean_ctor_get(v_x_960_, 0);
v_cost_966_ = lean_ctor_get(v_head_965_, 3);
v___x_967_ = lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(v_tail_962_);
v___x_968_ = lean_nat_dec_le(v_cost_966_, v___x_967_);
if (v___x_968_ == 0)
{
return v___x_967_;
}
else
{
lean_dec(v___x_967_);
lean_inc(v_cost_966_);
return v_cost_966_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg___boxed(lean_object* v_x_969_){
_start:
{
lean_object* v_res_970_; 
v_res_970_ = lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(v_x_969_);
lean_dec(v_x_969_);
return v_res_970_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin(lean_object* v_I_971_, lean_object* v_k_972_, lean_object* v_x_973_){
_start:
{
lean_object* v___x_974_; 
v___x_974_ = lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(v_x_973_);
return v___x_974_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclLayerMin___boxed(lean_object* v_I_975_, lean_object* v_k_976_, lean_object* v_x_977_){
_start:
{
lean_object* v_res_978_; 
v_res_978_ = lp_island__logistics__proof_IslandLogistics_exclLayerMin(v_I_975_, v_k_976_, v_x_977_);
lean_dec(v_x_977_);
lean_dec(v_k_976_);
lean_dec_ref(v_I_975_);
return v_res_978_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter___redArg(lean_object* v_x_979_, lean_object* v_h__1_980_, lean_object* v_h__2_981_, lean_object* v_h__3_982_){
_start:
{
if (lean_obj_tag(v_x_979_) == 0)
{
lean_object* v___x_983_; lean_object* v___x_984_; 
lean_dec(v_h__3_982_);
lean_dec(v_h__2_981_);
v___x_983_ = lean_box(0);
v___x_984_ = lean_apply_1(v_h__1_980_, v___x_983_);
return v___x_984_;
}
else
{
lean_object* v_tail_985_; 
lean_dec(v_h__1_980_);
v_tail_985_ = lean_ctor_get(v_x_979_, 1);
if (lean_obj_tag(v_tail_985_) == 0)
{
lean_object* v_head_986_; lean_object* v___x_987_; 
lean_dec(v_h__3_982_);
v_head_986_ = lean_ctor_get(v_x_979_, 0);
lean_inc(v_head_986_);
lean_dec_ref_known(v_x_979_, 2);
v___x_987_ = lean_apply_1(v_h__2_981_, v_head_986_);
return v___x_987_;
}
else
{
lean_object* v_head_988_; lean_object* v___x_989_; 
lean_inc(v_tail_985_);
lean_dec(v_h__2_981_);
v_head_988_ = lean_ctor_get(v_x_979_, 0);
lean_inc(v_head_988_);
lean_dec_ref_known(v_x_979_, 2);
v___x_989_ = lean_apply_3(v_h__3_982_, v_head_988_, v_tail_985_, lean_box(0));
return v___x_989_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter(lean_object* v_I_990_, lean_object* v_k_991_, lean_object* v_motive_992_, lean_object* v_x_993_, lean_object* v_h__1_994_, lean_object* v_h__2_995_, lean_object* v_h__3_996_){
_start:
{
if (lean_obj_tag(v_x_993_) == 0)
{
lean_object* v___x_997_; lean_object* v___x_998_; 
lean_dec(v_h__3_996_);
lean_dec(v_h__2_995_);
v___x_997_ = lean_box(0);
v___x_998_ = lean_apply_1(v_h__1_994_, v___x_997_);
return v___x_998_;
}
else
{
lean_object* v_tail_999_; 
lean_dec(v_h__1_994_);
v_tail_999_ = lean_ctor_get(v_x_993_, 1);
if (lean_obj_tag(v_tail_999_) == 0)
{
lean_object* v_head_1000_; lean_object* v___x_1001_; 
lean_dec(v_h__3_996_);
v_head_1000_ = lean_ctor_get(v_x_993_, 0);
lean_inc(v_head_1000_);
lean_dec_ref_known(v_x_993_, 2);
v___x_1001_ = lean_apply_1(v_h__2_995_, v_head_1000_);
return v___x_1001_;
}
else
{
lean_object* v_head_1002_; lean_object* v___x_1003_; 
lean_inc(v_tail_999_);
lean_dec(v_h__2_995_);
v_head_1002_ = lean_ctor_get(v_x_993_, 0);
lean_inc(v_head_1002_);
lean_dec_ref_known(v_x_993_, 2);
v___x_1003_ = lean_apply_3(v_h__3_996_, v_head_1002_, v_tail_999_, lean_box(0));
return v___x_1003_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter___boxed(lean_object* v_I_1004_, lean_object* v_k_1005_, lean_object* v_motive_1006_, lean_object* v_x_1007_, lean_object* v_h__1_1008_, lean_object* v_h__2_1009_, lean_object* v_h__3_1010_){
_start:
{
lean_object* v_res_1011_; 
v_res_1011_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_exclLayerMin_match__1_splitter(v_I_1004_, v_k_1005_, v_motive_1006_, v_x_1007_, v_h__1_1008_, v_h__2_1009_, v_h__3_1010_);
lean_dec(v_k_1005_);
lean_dec_ref(v_I_1004_);
return v_res_1011_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_exclTspLB(lean_object* v_I_1012_, lean_object* v_M_1013_, lean_object* v_k_1014_, lean_object* v_startRow_1015_, lean_object* v_pairs_1016_){
_start:
{
lean_object* v_rev_1017_; lean_object* v___x_1018_; uint8_t v___x_1019_; 
lean_inc_ref(v_pairs_1016_);
lean_inc(v_k_1014_);
v_rev_1017_ = lp_island__logistics__proof_IslandLogistics_exclRemEv___redArg(v_k_1014_, v_pairs_1016_);
v___x_1018_ = lean_unsigned_to_nat(0u);
v___x_1019_ = lean_nat_dec_eq(v_rev_1017_, v___x_1018_);
if (v___x_1019_ == 0)
{
lean_object* v___x_1020_; lean_object* v___x_1021_; lean_object* v___x_1022_; lean_object* v___x_1023_; lean_object* v___x_1024_; 
v___x_1020_ = lean_unsigned_to_nat(1u);
v___x_1021_ = lean_nat_sub(v_rev_1017_, v___x_1020_);
lean_dec(v_rev_1017_);
lean_inc_ref(v_pairs_1016_);
lean_inc(v_k_1014_);
lean_inc_ref(v_I_1012_);
v___x_1022_ = lp_island__logistics__proof_IslandLogistics_exclInitLayer(v_I_1012_, v_k_1014_, v_startRow_1015_, v_pairs_1016_);
v___x_1023_ = lp_island__logistics__proof_IslandLogistics_exclIterLayers(v_I_1012_, v_M_1013_, v_k_1014_, v_pairs_1016_, v___x_1021_, v___x_1022_);
lean_dec_ref(v_I_1012_);
v___x_1024_ = lp_island__logistics__proof_IslandLogistics_exclLayerMin___redArg(v___x_1023_);
lean_dec(v___x_1023_);
return v___x_1024_;
}
else
{
lean_dec(v_rev_1017_);
lean_dec_ref(v_pairs_1016_);
lean_dec_ref(v_startRow_1015_);
lean_dec(v_k_1014_);
lean_dec_ref(v_M_1013_);
lean_dec_ref(v_I_1012_);
return v___x_1018_;
}
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_validEvStep___redArg(lean_object* v_pm_1025_, lean_object* v_dm_1026_, lean_object* v_x_1027_){
_start:
{
if (lean_obj_tag(v_x_1027_) == 0)
{
lean_object* v_i_1028_; lean_object* v___x_1029_; uint8_t v___x_1030_; 
v_i_1028_ = lean_ctor_get(v_x_1027_, 0);
lean_inc_n(v_i_1028_, 2);
lean_dec_ref_known(v_x_1027_, 1);
v___x_1029_ = lean_apply_1(v_dm_1026_, v_i_1028_);
v___x_1030_ = lean_unbox(v___x_1029_);
if (v___x_1030_ == 0)
{
lean_object* v___x_1031_; uint8_t v___x_1032_; 
v___x_1031_ = lean_apply_1(v_pm_1025_, v_i_1028_);
v___x_1032_ = lean_unbox(v___x_1031_);
if (v___x_1032_ == 0)
{
uint8_t v___x_1033_; 
v___x_1033_ = 1;
return v___x_1033_;
}
else
{
uint8_t v___x_1034_; 
v___x_1034_ = lean_unbox(v___x_1029_);
return v___x_1034_;
}
}
else
{
uint8_t v___x_1035_; 
lean_dec(v_i_1028_);
lean_dec_ref(v_pm_1025_);
v___x_1035_ = 0;
return v___x_1035_;
}
}
else
{
lean_object* v_i_1036_; lean_object* v___x_1037_; uint8_t v___x_1038_; 
v_i_1036_ = lean_ctor_get(v_x_1027_, 0);
lean_inc_n(v_i_1036_, 2);
lean_dec_ref_known(v_x_1027_, 1);
v___x_1037_ = lean_apply_1(v_dm_1026_, v_i_1036_);
v___x_1038_ = lean_unbox(v___x_1037_);
if (v___x_1038_ == 0)
{
lean_object* v___x_1039_; uint8_t v___x_1040_; 
v___x_1039_ = lean_apply_1(v_pm_1025_, v_i_1036_);
v___x_1040_ = lean_unbox(v___x_1039_);
return v___x_1040_;
}
else
{
uint8_t v___x_1041_; 
lean_dec(v_i_1036_);
lean_dec_ref(v_pm_1025_);
v___x_1041_ = 0;
return v___x_1041_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_validEvStep___redArg___boxed(lean_object* v_pm_1042_, lean_object* v_dm_1043_, lean_object* v_x_1044_){
_start:
{
uint8_t v_res_1045_; lean_object* v_r_1046_; 
v_res_1045_ = lp_island__logistics__proof_IslandLogistics_validEvStep___redArg(v_pm_1042_, v_dm_1043_, v_x_1044_);
v_r_1046_ = lean_box(v_res_1045_);
return v_r_1046_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_validEvStep(lean_object* v_k_1047_, lean_object* v_pm_1048_, lean_object* v_dm_1049_, lean_object* v_x_1050_){
_start:
{
uint8_t v___x_1051_; 
v___x_1051_ = lp_island__logistics__proof_IslandLogistics_validEvStep___redArg(v_pm_1048_, v_dm_1049_, v_x_1050_);
return v___x_1051_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_validEvStep___boxed(lean_object* v_k_1052_, lean_object* v_pm_1053_, lean_object* v_dm_1054_, lean_object* v_x_1055_){
_start:
{
uint8_t v_res_1056_; lean_object* v_r_1057_; 
v_res_1056_ = lp_island__logistics__proof_IslandLogistics_validEvStep(v_k_1052_, v_pm_1053_, v_dm_1054_, v_x_1055_);
lean_dec(v_k_1052_);
v_r_1057_ = lean_box(v_res_1056_);
return v_r_1057_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg(lean_object* v_pm_1058_, lean_object* v_x_1059_, lean_object* v_a_1060_){
_start:
{
if (lean_obj_tag(v_x_1059_) == 0)
{
lean_object* v_i_1061_; uint8_t v___x_1062_; 
v_i_1061_ = lean_ctor_get(v_x_1059_, 0);
v___x_1062_ = lp_island__logistics__proof_IslandLogistics_setBit___redArg(v_pm_1058_, v_i_1061_, v_a_1060_);
return v___x_1062_;
}
else
{
lean_object* v___x_1063_; uint8_t v___x_1064_; 
v___x_1063_ = lean_apply_1(v_pm_1058_, v_a_1060_);
v___x_1064_ = lean_unbox(v___x_1063_);
return v___x_1064_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg___boxed(lean_object* v_pm_1065_, lean_object* v_x_1066_, lean_object* v_a_1067_){
_start:
{
uint8_t v_res_1068_; lean_object* v_r_1069_; 
v_res_1068_ = lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg(v_pm_1065_, v_x_1066_, v_a_1067_);
lean_dec_ref(v_x_1066_);
v_r_1069_ = lean_box(v_res_1068_);
return v_r_1069_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvPM(lean_object* v_k_1070_, lean_object* v_pm_1071_, lean_object* v_x_1072_, lean_object* v_a_1073_){
_start:
{
uint8_t v___x_1074_; 
v___x_1074_ = lp_island__logistics__proof_IslandLogistics_applyEvPM___redArg(v_pm_1071_, v_x_1072_, v_a_1073_);
return v___x_1074_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvPM___boxed(lean_object* v_k_1075_, lean_object* v_pm_1076_, lean_object* v_x_1077_, lean_object* v_a_1078_){
_start:
{
uint8_t v_res_1079_; lean_object* v_r_1080_; 
v_res_1079_ = lp_island__logistics__proof_IslandLogistics_applyEvPM(v_k_1075_, v_pm_1076_, v_x_1077_, v_a_1078_);
lean_dec_ref(v_x_1077_);
lean_dec(v_k_1075_);
v_r_1080_ = lean_box(v_res_1079_);
return v_r_1080_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg(lean_object* v_dm_1081_, lean_object* v_x_1082_, lean_object* v_a_1083_){
_start:
{
if (lean_obj_tag(v_x_1082_) == 0)
{
lean_object* v___x_1084_; uint8_t v___x_1085_; 
v___x_1084_ = lean_apply_1(v_dm_1081_, v_a_1083_);
v___x_1085_ = lean_unbox(v___x_1084_);
return v___x_1085_;
}
else
{
lean_object* v_i_1086_; uint8_t v___x_1087_; 
v_i_1086_ = lean_ctor_get(v_x_1082_, 0);
v___x_1087_ = lp_island__logistics__proof_IslandLogistics_setBit___redArg(v_dm_1081_, v_i_1086_, v_a_1083_);
return v___x_1087_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg___boxed(lean_object* v_dm_1088_, lean_object* v_x_1089_, lean_object* v_a_1090_){
_start:
{
uint8_t v_res_1091_; lean_object* v_r_1092_; 
v_res_1091_ = lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg(v_dm_1088_, v_x_1089_, v_a_1090_);
lean_dec_ref(v_x_1089_);
v_r_1092_ = lean_box(v_res_1091_);
return v_r_1092_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_applyEvDM(lean_object* v_k_1093_, lean_object* v_dm_1094_, lean_object* v_x_1095_, lean_object* v_a_1096_){
_start:
{
uint8_t v___x_1097_; 
v___x_1097_ = lp_island__logistics__proof_IslandLogistics_applyEvDM___redArg(v_dm_1094_, v_x_1095_, v_a_1096_);
return v___x_1097_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_applyEvDM___boxed(lean_object* v_k_1098_, lean_object* v_dm_1099_, lean_object* v_x_1100_, lean_object* v_a_1101_){
_start:
{
uint8_t v_res_1102_; lean_object* v_r_1103_; 
v_res_1102_ = lp_island__logistics__proof_IslandLogistics_applyEvDM(v_k_1098_, v_dm_1099_, v_x_1100_, v_a_1101_);
lean_dec_ref(v_x_1100_);
lean_dec(v_k_1098_);
v_r_1103_ = lean_box(v_res_1102_);
return v_r_1103_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost___redArg(lean_object* v_M_1104_, lean_object* v_pairs_1105_, lean_object* v_cur_1106_, lean_object* v_x_1107_){
_start:
{
if (lean_obj_tag(v_x_1107_) == 0)
{
lean_object* v___x_1108_; 
lean_dec(v_cur_1106_);
lean_dec_ref(v_pairs_1105_);
lean_dec_ref(v_M_1104_);
v___x_1108_ = lean_unsigned_to_nat(0u);
return v___x_1108_;
}
else
{
lean_object* v_head_1109_; lean_object* v_tail_1110_; lean_object* v_distFull_1111_; lean_object* v___x_1112_; lean_object* v___x_1113_; lean_object* v___x_1114_; lean_object* v___x_1115_; 
v_head_1109_ = lean_ctor_get(v_x_1107_, 0);
lean_inc(v_head_1109_);
v_tail_1110_ = lean_ctor_get(v_x_1107_, 1);
lean_inc(v_tail_1110_);
lean_dec_ref_known(v_x_1107_, 2);
v_distFull_1111_ = lean_ctor_get(v_M_1104_, 0);
lean_inc_ref(v_pairs_1105_);
v___x_1112_ = lp_island__logistics__proof_IslandLogistics_exclEvLoc___redArg(v_pairs_1105_, v_head_1109_);
lean_inc_ref(v_distFull_1111_);
lean_inc(v___x_1112_);
v___x_1113_ = lean_apply_2(v_distFull_1111_, v_cur_1106_, v___x_1112_);
v___x_1114_ = lp_island__logistics__proof_IslandLogistics_evTailCost___redArg(v_M_1104_, v_pairs_1105_, v___x_1112_, v_tail_1110_);
v___x_1115_ = lean_nat_add(v___x_1113_, v___x_1114_);
lean_dec(v___x_1114_);
lean_dec(v___x_1113_);
return v___x_1115_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost(lean_object* v_I_1116_, lean_object* v_M_1117_, lean_object* v_k_1118_, lean_object* v_pairs_1119_, lean_object* v_cur_1120_, lean_object* v_x_1121_){
_start:
{
lean_object* v___x_1122_; 
v___x_1122_ = lp_island__logistics__proof_IslandLogistics_evTailCost___redArg(v_M_1117_, v_pairs_1119_, v_cur_1120_, v_x_1121_);
return v___x_1122_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evTailCost___boxed(lean_object* v_I_1123_, lean_object* v_M_1124_, lean_object* v_k_1125_, lean_object* v_pairs_1126_, lean_object* v_cur_1127_, lean_object* v_x_1128_){
_start:
{
lean_object* v_res_1129_; 
v_res_1129_ = lp_island__logistics__proof_IslandLogistics_evTailCost(v_I_1123_, v_M_1124_, v_k_1125_, v_pairs_1126_, v_cur_1127_, v_x_1128_);
lean_dec(v_k_1125_);
lean_dec_ref(v_I_1123_);
return v_res_1129_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost___redArg(lean_object* v_M_1130_, lean_object* v_startRow_1131_, lean_object* v_pairs_1132_, lean_object* v_x_1133_){
_start:
{
if (lean_obj_tag(v_x_1133_) == 0)
{
lean_object* v___x_1134_; 
lean_dec_ref(v_pairs_1132_);
lean_dec_ref(v_startRow_1131_);
lean_dec_ref(v_M_1130_);
v___x_1134_ = lean_unsigned_to_nat(0u);
return v___x_1134_;
}
else
{
lean_object* v_head_1135_; lean_object* v_tail_1136_; lean_object* v___x_1137_; lean_object* v___x_1138_; lean_object* v___x_1139_; lean_object* v___x_1140_; 
v_head_1135_ = lean_ctor_get(v_x_1133_, 0);
lean_inc(v_head_1135_);
v_tail_1136_ = lean_ctor_get(v_x_1133_, 1);
lean_inc(v_tail_1136_);
lean_dec_ref_known(v_x_1133_, 2);
lean_inc_ref(v_pairs_1132_);
v___x_1137_ = lp_island__logistics__proof_IslandLogistics_exclEvLoc___redArg(v_pairs_1132_, v_head_1135_);
lean_inc(v___x_1137_);
v___x_1138_ = lean_apply_1(v_startRow_1131_, v___x_1137_);
v___x_1139_ = lp_island__logistics__proof_IslandLogistics_evTailCost___redArg(v_M_1130_, v_pairs_1132_, v___x_1137_, v_tail_1136_);
v___x_1140_ = lean_nat_add(v___x_1138_, v___x_1139_);
lean_dec(v___x_1139_);
lean_dec(v___x_1138_);
return v___x_1140_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost(lean_object* v_I_1141_, lean_object* v_M_1142_, lean_object* v_k_1143_, lean_object* v_startRow_1144_, lean_object* v_pairs_1145_, lean_object* v_x_1146_){
_start:
{
lean_object* v___x_1147_; 
v___x_1147_ = lp_island__logistics__proof_IslandLogistics_evSeqCost___redArg(v_M_1142_, v_startRow_1144_, v_pairs_1145_, v_x_1146_);
return v___x_1147_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evSeqCost___boxed(lean_object* v_I_1148_, lean_object* v_M_1149_, lean_object* v_k_1150_, lean_object* v_startRow_1151_, lean_object* v_pairs_1152_, lean_object* v_x_1153_){
_start:
{
lean_object* v_res_1154_; 
v_res_1154_ = lp_island__logistics__proof_IslandLogistics_evSeqCost(v_I_1148_, v_M_1149_, v_k_1150_, v_startRow_1151_, v_pairs_1152_, v_x_1153_);
lean_dec(v_k_1150_);
lean_dec_ref(v_I_1148_);
return v_res_1154_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost___redArg(lean_object* v_M_1155_, lean_object* v_cur_1156_, lean_object* v_x_1157_){
_start:
{
if (lean_obj_tag(v_x_1157_) == 0)
{
lean_object* v___x_1158_; 
lean_dec(v_cur_1156_);
lean_dec_ref(v_M_1155_);
v___x_1158_ = lean_unsigned_to_nat(0u);
return v___x_1158_;
}
else
{
lean_object* v_head_1159_; lean_object* v_tail_1160_; lean_object* v_snd_1161_; lean_object* v_distFull_1162_; lean_object* v___x_1163_; lean_object* v___x_1164_; lean_object* v___x_1165_; 
v_head_1159_ = lean_ctor_get(v_x_1157_, 0);
lean_inc(v_head_1159_);
v_tail_1160_ = lean_ctor_get(v_x_1157_, 1);
lean_inc(v_tail_1160_);
lean_dec_ref_known(v_x_1157_, 2);
v_snd_1161_ = lean_ctor_get(v_head_1159_, 1);
lean_inc_n(v_snd_1161_, 2);
lean_dec(v_head_1159_);
v_distFull_1162_ = lean_ctor_get(v_M_1155_, 0);
lean_inc_ref(v_distFull_1162_);
v___x_1163_ = lean_apply_2(v_distFull_1162_, v_cur_1156_, v_snd_1161_);
v___x_1164_ = lp_island__logistics__proof_IslandLogistics_visitsTailCost___redArg(v_M_1155_, v_snd_1161_, v_tail_1160_);
v___x_1165_ = lean_nat_add(v___x_1163_, v___x_1164_);
lean_dec(v___x_1164_);
lean_dec(v___x_1163_);
return v___x_1165_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost(lean_object* v_I_1166_, lean_object* v_M_1167_, lean_object* v_cur_1168_, lean_object* v_x_1169_){
_start:
{
lean_object* v___x_1170_; 
v___x_1170_ = lp_island__logistics__proof_IslandLogistics_visitsTailCost___redArg(v_M_1167_, v_cur_1168_, v_x_1169_);
return v___x_1170_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsTailCost___boxed(lean_object* v_I_1171_, lean_object* v_M_1172_, lean_object* v_cur_1173_, lean_object* v_x_1174_){
_start:
{
lean_object* v_res_1175_; 
v_res_1175_ = lp_island__logistics__proof_IslandLogistics_visitsTailCost(v_I_1171_, v_M_1172_, v_cur_1173_, v_x_1174_);
lean_dec_ref(v_I_1171_);
return v_res_1175_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost___redArg(lean_object* v_M_1176_, lean_object* v_s_1177_, lean_object* v_ti_1178_, lean_object* v_x_1179_){
_start:
{
if (lean_obj_tag(v_x_1179_) == 0)
{
lean_object* v___x_1180_; 
lean_dec(v_ti_1178_);
lean_dec_ref(v_s_1177_);
lean_dec_ref(v_M_1176_);
v___x_1180_ = lean_unsigned_to_nat(0u);
return v___x_1180_;
}
else
{
lean_object* v_head_1181_; lean_object* v_tail_1182_; lean_object* v_snd_1183_; lean_object* v___x_1184_; lean_object* v___x_1185_; lean_object* v___x_1186_; 
v_head_1181_ = lean_ctor_get(v_x_1179_, 0);
lean_inc(v_head_1181_);
v_tail_1182_ = lean_ctor_get(v_x_1179_, 1);
lean_inc(v_tail_1182_);
lean_dec_ref_known(v_x_1179_, 2);
v_snd_1183_ = lean_ctor_get(v_head_1181_, 1);
lean_inc_n(v_snd_1183_, 2);
lean_dec(v_head_1181_);
lean_inc_ref(v_M_1176_);
v___x_1184_ = lp_island__logistics__proof_IslandLogistics_truckFullPot___redArg(v_M_1176_, v_s_1177_, v_ti_1178_, v_snd_1183_);
v___x_1185_ = lp_island__logistics__proof_IslandLogistics_visitsTailCost___redArg(v_M_1176_, v_snd_1183_, v_tail_1182_);
v___x_1186_ = lean_nat_add(v___x_1184_, v___x_1185_);
lean_dec(v___x_1185_);
lean_dec(v___x_1184_);
return v___x_1186_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost(lean_object* v_I_1187_, lean_object* v_M_1188_, lean_object* v_s_1189_, lean_object* v_ti_1190_, lean_object* v_x_1191_){
_start:
{
lean_object* v___x_1192_; 
v___x_1192_ = lp_island__logistics__proof_IslandLogistics_visitsPathCost___redArg(v_M_1188_, v_s_1189_, v_ti_1190_, v_x_1191_);
return v___x_1192_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_visitsPathCost___boxed(lean_object* v_I_1193_, lean_object* v_M_1194_, lean_object* v_s_1195_, lean_object* v_ti_1196_, lean_object* v_x_1197_){
_start:
{
lean_object* v_res_1198_; 
v_res_1198_ = lp_island__logistics__proof_IslandLogistics_visitsPathCost(v_I_1193_, v_M_1194_, v_s_1195_, v_ti_1196_, v_x_1197_);
lean_dec_ref(v_I_1193_);
return v_res_1198_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv___redArg(lean_object* v_x_1199_, lean_object* v_x_1200_){
_start:
{
if (lean_obj_tag(v_x_1200_) == 0)
{
lean_object* v___x_1201_; 
v___x_1201_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_1201_, 0, v_x_1199_);
lean_ctor_set(v___x_1201_, 1, v_x_1200_);
return v___x_1201_;
}
else
{
lean_object* v_head_1202_; lean_object* v_tail_1203_; lean_object* v_fst_1204_; lean_object* v_fst_1205_; uint8_t v___x_1206_; 
v_head_1202_ = lean_ctor_get(v_x_1200_, 0);
lean_inc(v_head_1202_);
v_tail_1203_ = lean_ctor_get(v_x_1200_, 1);
v_fst_1204_ = lean_ctor_get(v_x_1199_, 0);
v_fst_1205_ = lean_ctor_get(v_head_1202_, 0);
v___x_1206_ = lean_nat_dec_le(v_fst_1204_, v_fst_1205_);
if (v___x_1206_ == 0)
{
lean_object* v___x_1208_; uint8_t v_isShared_1209_; uint8_t v_isSharedCheck_1214_; 
lean_inc(v_tail_1203_);
v_isSharedCheck_1214_ = !lean_is_exclusive(v_x_1200_);
if (v_isSharedCheck_1214_ == 0)
{
lean_object* v_unused_1215_; lean_object* v_unused_1216_; 
v_unused_1215_ = lean_ctor_get(v_x_1200_, 1);
lean_dec(v_unused_1215_);
v_unused_1216_ = lean_ctor_get(v_x_1200_, 0);
lean_dec(v_unused_1216_);
v___x_1208_ = v_x_1200_;
v_isShared_1209_ = v_isSharedCheck_1214_;
goto v_resetjp_1207_;
}
else
{
lean_dec(v_x_1200_);
v___x_1208_ = lean_box(0);
v_isShared_1209_ = v_isSharedCheck_1214_;
goto v_resetjp_1207_;
}
v_resetjp_1207_:
{
lean_object* v___x_1210_; lean_object* v___x_1212_; 
v___x_1210_ = lp_island__logistics__proof_IslandLogistics_insertTimedEv___redArg(v_x_1199_, v_tail_1203_);
if (v_isShared_1209_ == 0)
{
lean_ctor_set(v___x_1208_, 1, v___x_1210_);
v___x_1212_ = v___x_1208_;
goto v_reusejp_1211_;
}
else
{
lean_object* v_reuseFailAlloc_1213_; 
v_reuseFailAlloc_1213_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1213_, 0, v_head_1202_);
lean_ctor_set(v_reuseFailAlloc_1213_, 1, v___x_1210_);
v___x_1212_ = v_reuseFailAlloc_1213_;
goto v_reusejp_1211_;
}
v_reusejp_1211_:
{
return v___x_1212_;
}
}
}
else
{
lean_object* v___x_1218_; uint8_t v_isShared_1219_; uint8_t v_isSharedCheck_1223_; 
v_isSharedCheck_1223_ = !lean_is_exclusive(v_head_1202_);
if (v_isSharedCheck_1223_ == 0)
{
lean_object* v_unused_1224_; lean_object* v_unused_1225_; 
v_unused_1224_ = lean_ctor_get(v_head_1202_, 1);
lean_dec(v_unused_1224_);
v_unused_1225_ = lean_ctor_get(v_head_1202_, 0);
lean_dec(v_unused_1225_);
v___x_1218_ = v_head_1202_;
v_isShared_1219_ = v_isSharedCheck_1223_;
goto v_resetjp_1217_;
}
else
{
lean_dec(v_head_1202_);
v___x_1218_ = lean_box(0);
v_isShared_1219_ = v_isSharedCheck_1223_;
goto v_resetjp_1217_;
}
v_resetjp_1217_:
{
lean_object* v___x_1221_; 
if (v_isShared_1219_ == 0)
{
lean_ctor_set_tag(v___x_1218_, 1);
lean_ctor_set(v___x_1218_, 1, v_x_1200_);
lean_ctor_set(v___x_1218_, 0, v_x_1199_);
v___x_1221_ = v___x_1218_;
goto v_reusejp_1220_;
}
else
{
lean_object* v_reuseFailAlloc_1222_; 
v_reuseFailAlloc_1222_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1222_, 0, v_x_1199_);
lean_ctor_set(v_reuseFailAlloc_1222_, 1, v_x_1200_);
v___x_1221_ = v_reuseFailAlloc_1222_;
goto v_reusejp_1220_;
}
v_reusejp_1220_:
{
return v___x_1221_;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv(lean_object* v_k_1226_, lean_object* v_x_1227_, lean_object* v_x_1228_){
_start:
{
lean_object* v___x_1229_; 
v___x_1229_ = lp_island__logistics__proof_IslandLogistics_insertTimedEv___redArg(v_x_1227_, v_x_1228_);
return v___x_1229_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertTimedEv___boxed(lean_object* v_k_1230_, lean_object* v_x_1231_, lean_object* v_x_1232_){
_start:
{
lean_object* v_res_1233_; 
v_res_1233_ = lp_island__logistics__proof_IslandLogistics_insertTimedEv(v_k_1230_, v_x_1231_, v_x_1232_);
lean_dec(v_k_1230_);
return v_res_1233_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs___redArg(lean_object* v_x_1234_){
_start:
{
if (lean_obj_tag(v_x_1234_) == 0)
{
return v_x_1234_;
}
else
{
lean_object* v_head_1235_; lean_object* v_tail_1236_; lean_object* v___x_1237_; lean_object* v___x_1238_; 
v_head_1235_ = lean_ctor_get(v_x_1234_, 0);
lean_inc(v_head_1235_);
v_tail_1236_ = lean_ctor_get(v_x_1234_, 1);
lean_inc(v_tail_1236_);
lean_dec_ref_known(v_x_1234_, 2);
v___x_1237_ = lp_island__logistics__proof_IslandLogistics_sortTimedEvs___redArg(v_tail_1236_);
v___x_1238_ = lp_island__logistics__proof_IslandLogistics_insertTimedEv___redArg(v_head_1235_, v___x_1237_);
return v___x_1238_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs(lean_object* v_k_1239_, lean_object* v_x_1240_){
_start:
{
lean_object* v___x_1241_; 
v___x_1241_ = lp_island__logistics__proof_IslandLogistics_sortTimedEvs___redArg(v_x_1240_);
return v___x_1241_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortTimedEvs___boxed(lean_object* v_k_1242_, lean_object* v_x_1243_){
_start:
{
lean_object* v_res_1244_; 
v_res_1244_ = lp_island__logistics__proof_IslandLogistics_sortTimedEvs(v_k_1242_, v_x_1243_);
lean_dec(v_k_1242_);
return v_res_1244_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter___redArg(lean_object* v_x_1245_, lean_object* v_h__1_1246_, lean_object* v_h__2_1247_){
_start:
{
if (lean_obj_tag(v_x_1245_) == 0)
{
lean_object* v___x_1248_; lean_object* v___x_1249_; 
lean_dec(v_h__2_1247_);
v___x_1248_ = lean_box(0);
v___x_1249_ = lean_apply_1(v_h__1_1246_, v___x_1248_);
return v___x_1249_;
}
else
{
lean_object* v_head_1250_; lean_object* v_tail_1251_; lean_object* v___x_1252_; 
lean_dec(v_h__1_1246_);
v_head_1250_ = lean_ctor_get(v_x_1245_, 0);
lean_inc(v_head_1250_);
v_tail_1251_ = lean_ctor_get(v_x_1245_, 1);
lean_inc(v_tail_1251_);
lean_dec_ref_known(v_x_1245_, 2);
v___x_1252_ = lean_apply_2(v_h__2_1247_, v_head_1250_, v_tail_1251_);
return v___x_1252_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter(lean_object* v_k_1253_, lean_object* v_motive_1254_, lean_object* v_x_1255_, lean_object* v_h__1_1256_, lean_object* v_h__2_1257_){
_start:
{
if (lean_obj_tag(v_x_1255_) == 0)
{
lean_object* v___x_1258_; lean_object* v___x_1259_; 
lean_dec(v_h__2_1257_);
v___x_1258_ = lean_box(0);
v___x_1259_ = lean_apply_1(v_h__1_1256_, v___x_1258_);
return v___x_1259_;
}
else
{
lean_object* v_head_1260_; lean_object* v_tail_1261_; lean_object* v___x_1262_; 
lean_dec(v_h__1_1256_);
v_head_1260_ = lean_ctor_get(v_x_1255_, 0);
lean_inc(v_head_1260_);
v_tail_1261_ = lean_ctor_get(v_x_1255_, 1);
lean_inc(v_tail_1261_);
lean_dec_ref_known(v_x_1255_, 2);
v___x_1262_ = lean_apply_2(v_h__2_1257_, v_head_1260_, v_tail_1261_);
return v___x_1262_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter___boxed(lean_object* v_k_1263_, lean_object* v_motive_1264_, lean_object* v_x_1265_, lean_object* v_h__1_1266_, lean_object* v_h__2_1267_){
_start:
{
lean_object* v_res_1268_; 
v_res_1268_ = lp_island__logistics__proof___private_SingleAndExclusive_0__IslandLogistics_insertTimedEv_match__1_splitter(v_k_1263_, v_motive_1264_, v_x_1265_, v_h__1_1266_, v_h__2_1267_);
lean_dec(v_k_1263_);
return v_res_1268_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin);
lean_object* initialize_island__logistics__proof_PackingAndFlux(uint8_t builtin);
lean_object* initialize_island__logistics__proof_BridgesAndCycles(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_SingleAndExclusive(uint8_t builtin) {
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
res = initialize_island__logistics__proof_Domain(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_island__logistics__proof_PackingAndFlux(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_island__logistics__proof_BridgesAndCycles(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
