// Lean compiler output
// Module: Ferries
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
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_countActions___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_applyAction(lean_object*, lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_ferryCount(lean_object*, lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* l_List_range(lean_object*);
lean_object* lean_array_to_list(lean_object*);
lean_object* l_List_foldl___at___00Array_appendList_spec__0___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(lean_object*, lean_object*);
lean_object* l_List_finRange(lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoard___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoard___redArg___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoard(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoard___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembark___redArg(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembark___redArg___boxed(lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembark(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembark___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBoard(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBoard___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryDisembark(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryDisembark___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBD(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBD___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerrySail(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerrySail___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckBoard(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckBoard___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckDisembark(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckDisembark___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardCount(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkCount(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferryBDCount(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferrySailCount(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailAB___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailBA___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedCutSailAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedCutSailBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertAsc(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortAsc(lean_object*);
static const lean_array_object lp_island__logistics__proof_IslandLogistics_sumTake___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_sumTake___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_sumTake___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sumTake(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg___boxed(lean_object**);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___boxed(lean_object**);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__2(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1___boxed(lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDMin(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsAB___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsBA___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___redArg(uint8_t, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter(lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstDisembarkSide(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstDisembarkSide___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoardOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_ferryMinSails_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_ferryMinSails_spec__1(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferryMinSails(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potB(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potD(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isInterSail___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isInterSail___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isInterSail(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isInterSail___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedInterSailCount(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepLoadedInterSail(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailOut(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailOut___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailIn(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailIn___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailOut(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailOut___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailIn(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailIn___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoard___redArg(lean_object* v_x_1_){
_start:
{
if (lean_obj_tag(v_x_1_) == 3)
{
uint8_t v___x_2_; 
v___x_2_ = 1;
return v___x_2_;
}
else
{
uint8_t v___x_3_; 
v___x_3_ = 0;
return v___x_3_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoard___redArg___boxed(lean_object* v_x_4_){
_start:
{
uint8_t v_res_5_; lean_object* v_r_6_; 
v_res_5_ = lp_island__logistics__proof_IslandLogistics_isBoard___redArg(v_x_4_);
lean_dec_ref(v_x_4_);
v_r_6_ = lean_box(v_res_5_);
return v_r_6_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoard(lean_object* v_I_7_, lean_object* v_x_8_){
_start:
{
uint8_t v___x_9_; 
v___x_9_ = lp_island__logistics__proof_IslandLogistics_isBoard___redArg(v_x_8_);
return v___x_9_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoard___boxed(lean_object* v_I_10_, lean_object* v_x_11_){
_start:
{
uint8_t v_res_12_; lean_object* v_r_13_; 
v_res_12_ = lp_island__logistics__proof_IslandLogistics_isBoard(v_I_10_, v_x_11_);
lean_dec_ref(v_x_11_);
lean_dec_ref(v_I_10_);
v_r_13_ = lean_box(v_res_12_);
return v_r_13_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembark___redArg(lean_object* v_x_14_){
_start:
{
if (lean_obj_tag(v_x_14_) == 4)
{
uint8_t v___x_15_; 
v___x_15_ = 1;
return v___x_15_;
}
else
{
uint8_t v___x_16_; 
v___x_16_ = 0;
return v___x_16_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembark___redArg___boxed(lean_object* v_x_17_){
_start:
{
uint8_t v_res_18_; lean_object* v_r_19_; 
v_res_18_ = lp_island__logistics__proof_IslandLogistics_isDisembark___redArg(v_x_17_);
lean_dec_ref(v_x_17_);
v_r_19_ = lean_box(v_res_18_);
return v_r_19_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembark(lean_object* v_I_20_, lean_object* v_x_21_){
_start:
{
uint8_t v___x_22_; 
v___x_22_ = lp_island__logistics__proof_IslandLogistics_isDisembark___redArg(v_x_21_);
return v___x_22_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembark___boxed(lean_object* v_I_23_, lean_object* v_x_24_){
_start:
{
uint8_t v_res_25_; lean_object* v_r_26_; 
v_res_25_ = lp_island__logistics__proof_IslandLogistics_isDisembark(v_I_23_, v_x_24_);
lean_dec_ref(v_x_24_);
lean_dec_ref(v_I_23_);
v_r_26_ = lean_box(v_res_25_);
return v_r_26_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg(lean_object* v_f_27_, lean_object* v_x_28_){
_start:
{
if (lean_obj_tag(v_x_28_) == 3)
{
lean_object* v_f_29_; uint8_t v___x_30_; 
v_f_29_ = lean_ctor_get(v_x_28_, 1);
v___x_30_ = lean_nat_dec_eq(v_f_29_, v_f_27_);
return v___x_30_;
}
else
{
uint8_t v___x_31_; 
v___x_31_ = 0;
return v___x_31_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg___boxed(lean_object* v_f_32_, lean_object* v_x_33_){
_start:
{
uint8_t v_res_34_; lean_object* v_r_35_; 
v_res_34_ = lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg(v_f_32_, v_x_33_);
lean_dec_ref(v_x_33_);
lean_dec(v_f_32_);
v_r_35_ = lean_box(v_res_34_);
return v_r_35_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBoard(lean_object* v_I_36_, lean_object* v_f_37_, lean_object* v_x_38_){
_start:
{
uint8_t v___x_39_; 
v___x_39_ = lp_island__logistics__proof_IslandLogistics_isFerryBoard___redArg(v_f_37_, v_x_38_);
return v___x_39_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBoard___boxed(lean_object* v_I_40_, lean_object* v_f_41_, lean_object* v_x_42_){
_start:
{
uint8_t v_res_43_; lean_object* v_r_44_; 
v_res_43_ = lp_island__logistics__proof_IslandLogistics_isFerryBoard(v_I_40_, v_f_41_, v_x_42_);
lean_dec_ref(v_x_42_);
lean_dec(v_f_41_);
lean_dec_ref(v_I_40_);
v_r_44_ = lean_box(v_res_43_);
return v_r_44_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg(lean_object* v_f_45_, lean_object* v_x_46_){
_start:
{
if (lean_obj_tag(v_x_46_) == 4)
{
lean_object* v_f_47_; uint8_t v___x_48_; 
v_f_47_ = lean_ctor_get(v_x_46_, 1);
v___x_48_ = lean_nat_dec_eq(v_f_47_, v_f_45_);
return v___x_48_;
}
else
{
uint8_t v___x_49_; 
v___x_49_ = 0;
return v___x_49_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg___boxed(lean_object* v_f_50_, lean_object* v_x_51_){
_start:
{
uint8_t v_res_52_; lean_object* v_r_53_; 
v_res_52_ = lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg(v_f_50_, v_x_51_);
lean_dec_ref(v_x_51_);
lean_dec(v_f_50_);
v_r_53_ = lean_box(v_res_52_);
return v_r_53_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryDisembark(lean_object* v_I_54_, lean_object* v_f_55_, lean_object* v_x_56_){
_start:
{
uint8_t v___x_57_; 
v___x_57_ = lp_island__logistics__proof_IslandLogistics_isFerryDisembark___redArg(v_f_55_, v_x_56_);
return v___x_57_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryDisembark___boxed(lean_object* v_I_58_, lean_object* v_f_59_, lean_object* v_x_60_){
_start:
{
uint8_t v_res_61_; lean_object* v_r_62_; 
v_res_61_ = lp_island__logistics__proof_IslandLogistics_isFerryDisembark(v_I_58_, v_f_59_, v_x_60_);
lean_dec_ref(v_x_60_);
lean_dec(v_f_59_);
lean_dec_ref(v_I_58_);
v_r_62_ = lean_box(v_res_61_);
return v_r_62_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg(lean_object* v_f_63_, lean_object* v_x_64_){
_start:
{
switch(lean_obj_tag(v_x_64_))
{
case 3:
{
lean_object* v_f_65_; uint8_t v___x_66_; 
v_f_65_ = lean_ctor_get(v_x_64_, 1);
v___x_66_ = lean_nat_dec_eq(v_f_65_, v_f_63_);
return v___x_66_;
}
case 4:
{
lean_object* v_f_67_; uint8_t v___x_68_; 
v_f_67_ = lean_ctor_get(v_x_64_, 1);
v___x_68_ = lean_nat_dec_eq(v_f_67_, v_f_63_);
return v___x_68_;
}
default: 
{
uint8_t v___x_69_; 
v___x_69_ = 0;
return v___x_69_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg___boxed(lean_object* v_f_70_, lean_object* v_x_71_){
_start:
{
uint8_t v_res_72_; lean_object* v_r_73_; 
v_res_72_ = lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg(v_f_70_, v_x_71_);
lean_dec_ref(v_x_71_);
lean_dec(v_f_70_);
v_r_73_ = lean_box(v_res_72_);
return v_r_73_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerryBD(lean_object* v_I_74_, lean_object* v_f_75_, lean_object* v_x_76_){
_start:
{
uint8_t v___x_77_; 
v___x_77_ = lp_island__logistics__proof_IslandLogistics_isFerryBD___redArg(v_f_75_, v_x_76_);
return v___x_77_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerryBD___boxed(lean_object* v_I_78_, lean_object* v_f_79_, lean_object* v_x_80_){
_start:
{
uint8_t v_res_81_; lean_object* v_r_82_; 
v_res_81_ = lp_island__logistics__proof_IslandLogistics_isFerryBD(v_I_78_, v_f_79_, v_x_80_);
lean_dec_ref(v_x_80_);
lean_dec(v_f_79_);
lean_dec_ref(v_I_78_);
v_r_82_ = lean_box(v_res_81_);
return v_r_82_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg(lean_object* v_f_83_, lean_object* v_x_84_){
_start:
{
if (lean_obj_tag(v_x_84_) == 5)
{
lean_object* v_f_85_; uint8_t v___x_86_; 
v_f_85_ = lean_ctor_get(v_x_84_, 0);
v___x_86_ = lean_nat_dec_eq(v_f_85_, v_f_83_);
return v___x_86_;
}
else
{
uint8_t v___x_87_; 
v___x_87_ = 0;
return v___x_87_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg___boxed(lean_object* v_f_88_, lean_object* v_x_89_){
_start:
{
uint8_t v_res_90_; lean_object* v_r_91_; 
v_res_90_ = lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg(v_f_88_, v_x_89_);
lean_dec_ref(v_x_89_);
lean_dec(v_f_88_);
v_r_91_ = lean_box(v_res_90_);
return v_r_91_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isFerrySail(lean_object* v_I_92_, lean_object* v_f_93_, lean_object* v_x_94_){
_start:
{
uint8_t v___x_95_; 
v___x_95_ = lp_island__logistics__proof_IslandLogistics_isFerrySail___redArg(v_f_93_, v_x_94_);
return v___x_95_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isFerrySail___boxed(lean_object* v_I_96_, lean_object* v_f_97_, lean_object* v_x_98_){
_start:
{
uint8_t v_res_99_; lean_object* v_r_100_; 
v_res_99_ = lp_island__logistics__proof_IslandLogistics_isFerrySail(v_I_96_, v_f_97_, v_x_98_);
lean_dec_ref(v_x_98_);
lean_dec(v_f_97_);
lean_dec_ref(v_I_96_);
v_r_100_ = lean_box(v_res_99_);
return v_r_100_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg(lean_object* v_t_101_, lean_object* v_f_102_, lean_object* v_x_103_){
_start:
{
if (lean_obj_tag(v_x_103_) == 3)
{
lean_object* v_t_104_; lean_object* v_f_105_; uint8_t v___x_106_; 
v_t_104_ = lean_ctor_get(v_x_103_, 0);
v_f_105_ = lean_ctor_get(v_x_103_, 1);
v___x_106_ = lean_nat_dec_eq(v_t_104_, v_t_101_);
if (v___x_106_ == 0)
{
return v___x_106_;
}
else
{
uint8_t v___x_107_; 
v___x_107_ = lean_nat_dec_eq(v_f_105_, v_f_102_);
return v___x_107_;
}
}
else
{
uint8_t v___x_108_; 
v___x_108_ = 0;
return v___x_108_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg___boxed(lean_object* v_t_109_, lean_object* v_f_110_, lean_object* v_x_111_){
_start:
{
uint8_t v_res_112_; lean_object* v_r_113_; 
v_res_112_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg(v_t_109_, v_f_110_, v_x_111_);
lean_dec_ref(v_x_111_);
lean_dec(v_f_110_);
lean_dec(v_t_109_);
v_r_113_ = lean_box(v_res_112_);
return v_r_113_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard(lean_object* v_I_114_, lean_object* v_t_115_, lean_object* v_f_116_, lean_object* v_x_117_){
_start:
{
uint8_t v___x_118_; 
v___x_118_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___redArg(v_t_115_, v_f_116_, v_x_117_);
return v___x_118_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard___boxed(lean_object* v_I_119_, lean_object* v_t_120_, lean_object* v_f_121_, lean_object* v_x_122_){
_start:
{
uint8_t v_res_123_; lean_object* v_r_124_; 
v_res_123_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryBoard(v_I_119_, v_t_120_, v_f_121_, v_x_122_);
lean_dec_ref(v_x_122_);
lean_dec(v_f_121_);
lean_dec(v_t_120_);
lean_dec_ref(v_I_119_);
v_r_124_ = lean_box(v_res_123_);
return v_r_124_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg(lean_object* v_t_125_, lean_object* v_f_126_, lean_object* v_x_127_){
_start:
{
if (lean_obj_tag(v_x_127_) == 4)
{
lean_object* v_t_128_; lean_object* v_f_129_; uint8_t v___x_130_; 
v_t_128_ = lean_ctor_get(v_x_127_, 0);
v_f_129_ = lean_ctor_get(v_x_127_, 1);
v___x_130_ = lean_nat_dec_eq(v_t_128_, v_t_125_);
if (v___x_130_ == 0)
{
return v___x_130_;
}
else
{
uint8_t v___x_131_; 
v___x_131_ = lean_nat_dec_eq(v_f_129_, v_f_126_);
return v___x_131_;
}
}
else
{
uint8_t v___x_132_; 
v___x_132_ = 0;
return v___x_132_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg___boxed(lean_object* v_t_133_, lean_object* v_f_134_, lean_object* v_x_135_){
_start:
{
uint8_t v_res_136_; lean_object* v_r_137_; 
v_res_136_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg(v_t_133_, v_f_134_, v_x_135_);
lean_dec_ref(v_x_135_);
lean_dec(v_f_134_);
lean_dec(v_t_133_);
v_r_137_ = lean_box(v_res_136_);
return v_r_137_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark(lean_object* v_I_138_, lean_object* v_t_139_, lean_object* v_f_140_, lean_object* v_x_141_){
_start:
{
uint8_t v___x_142_; 
v___x_142_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___redArg(v_t_139_, v_f_140_, v_x_141_);
return v___x_142_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark___boxed(lean_object* v_I_143_, lean_object* v_t_144_, lean_object* v_f_145_, lean_object* v_x_146_){
_start:
{
uint8_t v_res_147_; lean_object* v_r_148_; 
v_res_147_ = lp_island__logistics__proof_IslandLogistics_isTruckFerryDisembark(v_I_143_, v_t_144_, v_f_145_, v_x_146_);
lean_dec_ref(v_x_146_);
lean_dec(v_f_145_);
lean_dec(v_t_144_);
lean_dec_ref(v_I_143_);
v_r_148_ = lean_box(v_res_147_);
return v_r_148_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg(lean_object* v_t_149_, lean_object* v_x_150_){
_start:
{
if (lean_obj_tag(v_x_150_) == 3)
{
lean_object* v_t_151_; uint8_t v___x_152_; 
v_t_151_ = lean_ctor_get(v_x_150_, 0);
v___x_152_ = lean_nat_dec_eq(v_t_151_, v_t_149_);
return v___x_152_;
}
else
{
uint8_t v___x_153_; 
v___x_153_ = 0;
return v___x_153_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg___boxed(lean_object* v_t_154_, lean_object* v_x_155_){
_start:
{
uint8_t v_res_156_; lean_object* v_r_157_; 
v_res_156_ = lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg(v_t_154_, v_x_155_);
lean_dec_ref(v_x_155_);
lean_dec(v_t_154_);
v_r_157_ = lean_box(v_res_156_);
return v_r_157_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckBoard(lean_object* v_I_158_, lean_object* v_t_159_, lean_object* v_x_160_){
_start:
{
uint8_t v___x_161_; 
v___x_161_ = lp_island__logistics__proof_IslandLogistics_isTruckBoard___redArg(v_t_159_, v_x_160_);
return v___x_161_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckBoard___boxed(lean_object* v_I_162_, lean_object* v_t_163_, lean_object* v_x_164_){
_start:
{
uint8_t v_res_165_; lean_object* v_r_166_; 
v_res_165_ = lp_island__logistics__proof_IslandLogistics_isTruckBoard(v_I_162_, v_t_163_, v_x_164_);
lean_dec_ref(v_x_164_);
lean_dec(v_t_163_);
lean_dec_ref(v_I_162_);
v_r_166_ = lean_box(v_res_165_);
return v_r_166_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg(lean_object* v_t_167_, lean_object* v_x_168_){
_start:
{
if (lean_obj_tag(v_x_168_) == 4)
{
lean_object* v_t_169_; uint8_t v___x_170_; 
v_t_169_ = lean_ctor_get(v_x_168_, 0);
v___x_170_ = lean_nat_dec_eq(v_t_169_, v_t_167_);
return v___x_170_;
}
else
{
uint8_t v___x_171_; 
v___x_171_ = 0;
return v___x_171_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg___boxed(lean_object* v_t_172_, lean_object* v_x_173_){
_start:
{
uint8_t v_res_174_; lean_object* v_r_175_; 
v_res_174_ = lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg(v_t_172_, v_x_173_);
lean_dec_ref(v_x_173_);
lean_dec(v_t_172_);
v_r_175_ = lean_box(v_res_174_);
return v_r_175_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckDisembark(lean_object* v_I_176_, lean_object* v_t_177_, lean_object* v_x_178_){
_start:
{
uint8_t v___x_179_; 
v___x_179_ = lp_island__logistics__proof_IslandLogistics_isTruckDisembark___redArg(v_t_177_, v_x_178_);
return v___x_179_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckDisembark___boxed(lean_object* v_I_180_, lean_object* v_t_181_, lean_object* v_x_182_){
_start:
{
uint8_t v_res_183_; lean_object* v_r_184_; 
v_res_183_ = lp_island__logistics__proof_IslandLogistics_isTruckDisembark(v_I_180_, v_t_181_, v_x_182_);
lean_dec_ref(v_x_182_);
lean_dec(v_t_181_);
lean_dec_ref(v_I_180_);
v_r_184_ = lean_box(v_res_183_);
return v_r_184_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardCount(lean_object* v_I_185_, lean_object* v_00_u03c0_186_){
_start:
{
lean_object* v___x_187_; lean_object* v___x_188_; 
v___x_187_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isBoard___boxed), 2, 1);
lean_closure_set(v___x_187_, 0, v_I_185_);
v___x_188_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_187_, v_00_u03c0_186_);
return v___x_188_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkCount(lean_object* v_I_189_, lean_object* v_00_u03c0_190_){
_start:
{
lean_object* v___x_191_; lean_object* v___x_192_; 
v___x_191_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isDisembark___boxed), 2, 1);
lean_closure_set(v___x_191_, 0, v_I_189_);
v___x_192_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_191_, v_00_u03c0_190_);
return v___x_192_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferryBDCount(lean_object* v_I_193_, lean_object* v_f_194_, lean_object* v_00_u03c0_195_){
_start:
{
lean_object* v___x_196_; lean_object* v___x_197_; 
v___x_196_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isFerryBD___boxed), 3, 2);
lean_closure_set(v___x_196_, 0, v_I_193_);
lean_closure_set(v___x_196_, 1, v_f_194_);
v___x_197_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_196_, v_00_u03c0_195_);
return v___x_197_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferrySailCount(lean_object* v_I_198_, lean_object* v_f_199_, lean_object* v_00_u03c0_200_){
_start:
{
lean_object* v___x_201_; lean_object* v___x_202_; 
v___x_201_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isFerrySail___boxed), 3, 2);
lean_closure_set(v___x_201_, 0, v_I_198_);
lean_closure_set(v___x_201_, 1, v_f_199_);
v___x_202_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_201_, v_00_u03c0_200_);
return v___x_202_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter___redArg(lean_object* v_x_203_, lean_object* v_h__1_204_, lean_object* v_h__2_205_){
_start:
{
if (lean_obj_tag(v_x_203_) == 3)
{
lean_object* v_t_206_; lean_object* v_f_207_; lean_object* v___x_208_; 
lean_dec(v_h__2_205_);
v_t_206_ = lean_ctor_get(v_x_203_, 0);
lean_inc(v_t_206_);
v_f_207_ = lean_ctor_get(v_x_203_, 1);
lean_inc(v_f_207_);
lean_dec_ref_known(v_x_203_, 2);
v___x_208_ = lean_apply_2(v_h__1_204_, v_t_206_, v_f_207_);
return v___x_208_;
}
else
{
lean_object* v___x_209_; 
lean_dec(v_h__1_204_);
v___x_209_ = lean_apply_2(v_h__2_205_, v_x_203_, lean_box(0));
return v___x_209_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter(lean_object* v_I_210_, lean_object* v_motive_211_, lean_object* v_x_212_, lean_object* v_h__1_213_, lean_object* v_h__2_214_){
_start:
{
if (lean_obj_tag(v_x_212_) == 3)
{
lean_object* v_t_215_; lean_object* v_f_216_; lean_object* v___x_217_; 
lean_dec(v_h__2_214_);
v_t_215_ = lean_ctor_get(v_x_212_, 0);
lean_inc(v_t_215_);
v_f_216_ = lean_ctor_get(v_x_212_, 1);
lean_inc(v_f_216_);
lean_dec_ref_known(v_x_212_, 2);
v___x_217_ = lean_apply_2(v_h__1_213_, v_t_215_, v_f_216_);
return v___x_217_;
}
else
{
lean_object* v___x_218_; 
lean_dec(v_h__1_213_);
v___x_218_ = lean_apply_2(v_h__2_214_, v_x_212_, lean_box(0));
return v___x_218_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter___boxed(lean_object* v_I_219_, lean_object* v_motive_220_, lean_object* v_x_221_, lean_object* v_h__1_222_, lean_object* v_h__2_223_){
_start:
{
lean_object* v_res_224_; 
v_res_224_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isBoard_match__1_splitter(v_I_219_, v_motive_220_, v_x_221_, v_h__1_222_, v_h__2_223_);
lean_dec_ref(v_I_219_);
return v_res_224_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter___redArg(lean_object* v_x_225_, lean_object* v_h__1_226_, lean_object* v_h__2_227_){
_start:
{
if (lean_obj_tag(v_x_225_) == 4)
{
lean_object* v_t_228_; lean_object* v_f_229_; lean_object* v___x_230_; 
lean_dec(v_h__2_227_);
v_t_228_ = lean_ctor_get(v_x_225_, 0);
lean_inc(v_t_228_);
v_f_229_ = lean_ctor_get(v_x_225_, 1);
lean_inc(v_f_229_);
lean_dec_ref_known(v_x_225_, 2);
v___x_230_ = lean_apply_2(v_h__1_226_, v_t_228_, v_f_229_);
return v___x_230_;
}
else
{
lean_object* v___x_231_; 
lean_dec(v_h__1_226_);
v___x_231_ = lean_apply_2(v_h__2_227_, v_x_225_, lean_box(0));
return v___x_231_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter(lean_object* v_I_232_, lean_object* v_motive_233_, lean_object* v_x_234_, lean_object* v_h__1_235_, lean_object* v_h__2_236_){
_start:
{
if (lean_obj_tag(v_x_234_) == 4)
{
lean_object* v_t_237_; lean_object* v_f_238_; lean_object* v___x_239_; 
lean_dec(v_h__2_236_);
v_t_237_ = lean_ctor_get(v_x_234_, 0);
lean_inc(v_t_237_);
v_f_238_ = lean_ctor_get(v_x_234_, 1);
lean_inc(v_f_238_);
lean_dec_ref_known(v_x_234_, 2);
v___x_239_ = lean_apply_2(v_h__1_235_, v_t_237_, v_f_238_);
return v___x_239_;
}
else
{
lean_object* v___x_240_; 
lean_dec(v_h__1_235_);
v___x_240_ = lean_apply_2(v_h__2_236_, v_x_234_, lean_box(0));
return v___x_240_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter___boxed(lean_object* v_I_241_, lean_object* v_motive_242_, lean_object* v_x_243_, lean_object* v_h__1_244_, lean_object* v_h__2_245_){
_start:
{
lean_object* v_res_246_; 
v_res_246_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isDisembark_match__1_splitter(v_I_241_, v_motive_242_, v_x_243_, v_h__1_244_, v_h__2_245_);
lean_dec_ref(v_I_241_);
return v_res_246_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter___redArg(lean_object* v_x_247_, lean_object* v_h__1_248_, lean_object* v_h__2_249_, lean_object* v_h__3_250_){
_start:
{
switch(lean_obj_tag(v_x_247_))
{
case 3:
{
lean_object* v_t_251_; lean_object* v_f_252_; lean_object* v___x_253_; 
lean_dec(v_h__3_250_);
lean_dec(v_h__2_249_);
v_t_251_ = lean_ctor_get(v_x_247_, 0);
lean_inc(v_t_251_);
v_f_252_ = lean_ctor_get(v_x_247_, 1);
lean_inc(v_f_252_);
lean_dec_ref_known(v_x_247_, 2);
v___x_253_ = lean_apply_2(v_h__1_248_, v_t_251_, v_f_252_);
return v___x_253_;
}
case 4:
{
lean_object* v_t_254_; lean_object* v_f_255_; lean_object* v___x_256_; 
lean_dec(v_h__3_250_);
lean_dec(v_h__1_248_);
v_t_254_ = lean_ctor_get(v_x_247_, 0);
lean_inc(v_t_254_);
v_f_255_ = lean_ctor_get(v_x_247_, 1);
lean_inc(v_f_255_);
lean_dec_ref_known(v_x_247_, 2);
v___x_256_ = lean_apply_2(v_h__2_249_, v_t_254_, v_f_255_);
return v___x_256_;
}
default: 
{
lean_object* v___x_257_; 
lean_dec(v_h__2_249_);
lean_dec(v_h__1_248_);
v___x_257_ = lean_apply_3(v_h__3_250_, v_x_247_, lean_box(0), lean_box(0));
return v___x_257_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter(lean_object* v_I_258_, lean_object* v_motive_259_, lean_object* v_x_260_, lean_object* v_h__1_261_, lean_object* v_h__2_262_, lean_object* v_h__3_263_){
_start:
{
switch(lean_obj_tag(v_x_260_))
{
case 3:
{
lean_object* v_t_264_; lean_object* v_f_265_; lean_object* v___x_266_; 
lean_dec(v_h__3_263_);
lean_dec(v_h__2_262_);
v_t_264_ = lean_ctor_get(v_x_260_, 0);
lean_inc(v_t_264_);
v_f_265_ = lean_ctor_get(v_x_260_, 1);
lean_inc(v_f_265_);
lean_dec_ref_known(v_x_260_, 2);
v___x_266_ = lean_apply_2(v_h__1_261_, v_t_264_, v_f_265_);
return v___x_266_;
}
case 4:
{
lean_object* v_t_267_; lean_object* v_f_268_; lean_object* v___x_269_; 
lean_dec(v_h__3_263_);
lean_dec(v_h__1_261_);
v_t_267_ = lean_ctor_get(v_x_260_, 0);
lean_inc(v_t_267_);
v_f_268_ = lean_ctor_get(v_x_260_, 1);
lean_inc(v_f_268_);
lean_dec_ref_known(v_x_260_, 2);
v___x_269_ = lean_apply_2(v_h__2_262_, v_t_267_, v_f_268_);
return v___x_269_;
}
default: 
{
lean_object* v___x_270_; 
lean_dec(v_h__2_262_);
lean_dec(v_h__1_261_);
v___x_270_ = lean_apply_3(v_h__3_263_, v_x_260_, lean_box(0), lean_box(0));
return v___x_270_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter___boxed(lean_object* v_I_271_, lean_object* v_motive_272_, lean_object* v_x_273_, lean_object* v_h__1_274_, lean_object* v_h__2_275_, lean_object* v_h__3_276_){
_start:
{
lean_object* v_res_277_; 
v_res_277_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerryBD_match__1_splitter(v_I_271_, v_motive_272_, v_x_273_, v_h__1_274_, v_h__2_275_, v_h__3_276_);
lean_dec_ref(v_I_271_);
return v_res_277_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter___redArg(lean_object* v_x_278_, lean_object* v_h__1_279_, lean_object* v_h__2_280_, lean_object* v_h__3_281_){
_start:
{
switch(lean_obj_tag(v_x_278_))
{
case 3:
{
lean_object* v_t_282_; lean_object* v_f_283_; lean_object* v___x_284_; 
lean_dec(v_h__3_281_);
lean_dec(v_h__2_280_);
v_t_282_ = lean_ctor_get(v_x_278_, 0);
lean_inc(v_t_282_);
v_f_283_ = lean_ctor_get(v_x_278_, 1);
lean_inc(v_f_283_);
lean_dec_ref_known(v_x_278_, 2);
v___x_284_ = lean_apply_2(v_h__1_279_, v_t_282_, v_f_283_);
return v___x_284_;
}
case 4:
{
lean_object* v_t_285_; lean_object* v_f_286_; lean_object* v___x_287_; 
lean_dec(v_h__3_281_);
lean_dec(v_h__1_279_);
v_t_285_ = lean_ctor_get(v_x_278_, 0);
lean_inc(v_t_285_);
v_f_286_ = lean_ctor_get(v_x_278_, 1);
lean_inc(v_f_286_);
lean_dec_ref_known(v_x_278_, 2);
v___x_287_ = lean_apply_2(v_h__2_280_, v_t_285_, v_f_286_);
return v___x_287_;
}
default: 
{
lean_object* v___x_288_; 
lean_dec(v_h__2_280_);
lean_dec(v_h__1_279_);
v___x_288_ = lean_apply_3(v_h__3_281_, v_x_278_, lean_box(0), lean_box(0));
return v___x_288_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter(lean_object* v_I_289_, lean_object* v_motive_290_, lean_object* v_x_291_, lean_object* v_h__1_292_, lean_object* v_h__2_293_, lean_object* v_h__3_294_){
_start:
{
switch(lean_obj_tag(v_x_291_))
{
case 3:
{
lean_object* v_t_295_; lean_object* v_f_296_; lean_object* v___x_297_; 
lean_dec(v_h__3_294_);
lean_dec(v_h__2_293_);
v_t_295_ = lean_ctor_get(v_x_291_, 0);
lean_inc(v_t_295_);
v_f_296_ = lean_ctor_get(v_x_291_, 1);
lean_inc(v_f_296_);
lean_dec_ref_known(v_x_291_, 2);
v___x_297_ = lean_apply_2(v_h__1_292_, v_t_295_, v_f_296_);
return v___x_297_;
}
case 4:
{
lean_object* v_t_298_; lean_object* v_f_299_; lean_object* v___x_300_; 
lean_dec(v_h__3_294_);
lean_dec(v_h__1_292_);
v_t_298_ = lean_ctor_get(v_x_291_, 0);
lean_inc(v_t_298_);
v_f_299_ = lean_ctor_get(v_x_291_, 1);
lean_inc(v_f_299_);
lean_dec_ref_known(v_x_291_, 2);
v___x_300_ = lean_apply_2(v_h__2_293_, v_t_298_, v_f_299_);
return v___x_300_;
}
default: 
{
lean_object* v___x_301_; 
lean_dec(v_h__2_293_);
lean_dec(v_h__1_292_);
v___x_301_ = lean_apply_3(v_h__3_294_, v_x_291_, lean_box(0), lean_box(0));
return v___x_301_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter___boxed(lean_object* v_I_302_, lean_object* v_motive_303_, lean_object* v_x_304_, lean_object* v_h__1_305_, lean_object* v_h__2_306_, lean_object* v_h__3_307_){
_start:
{
lean_object* v_res_308_; 
v_res_308_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCostBD_match__1_splitter(v_I_302_, v_motive_303_, v_x_304_, v_h__1_305_, v_h__2_306_, v_h__3_307_);
lean_dec_ref(v_I_302_);
return v_res_308_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter___redArg(lean_object* v_x_309_, lean_object* v_h__1_310_, lean_object* v_h__2_311_){
_start:
{
if (lean_obj_tag(v_x_309_) == 5)
{
lean_object* v_f_312_; lean_object* v_u_313_; lean_object* v_v_314_; lean_object* v___x_315_; 
lean_dec(v_h__2_311_);
v_f_312_ = lean_ctor_get(v_x_309_, 0);
lean_inc(v_f_312_);
v_u_313_ = lean_ctor_get(v_x_309_, 1);
lean_inc(v_u_313_);
v_v_314_ = lean_ctor_get(v_x_309_, 2);
lean_inc(v_v_314_);
lean_dec_ref_known(v_x_309_, 3);
v___x_315_ = lean_apply_3(v_h__1_310_, v_f_312_, v_u_313_, v_v_314_);
return v___x_315_;
}
else
{
lean_object* v___x_316_; 
lean_dec(v_h__1_310_);
v___x_316_ = lean_apply_2(v_h__2_311_, v_x_309_, lean_box(0));
return v___x_316_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter(lean_object* v_I_317_, lean_object* v_motive_318_, lean_object* v_x_319_, lean_object* v_h__1_320_, lean_object* v_h__2_321_){
_start:
{
if (lean_obj_tag(v_x_319_) == 5)
{
lean_object* v_f_322_; lean_object* v_u_323_; lean_object* v_v_324_; lean_object* v___x_325_; 
lean_dec(v_h__2_321_);
v_f_322_ = lean_ctor_get(v_x_319_, 0);
lean_inc(v_f_322_);
v_u_323_ = lean_ctor_get(v_x_319_, 1);
lean_inc(v_u_323_);
v_v_324_ = lean_ctor_get(v_x_319_, 2);
lean_inc(v_v_324_);
lean_dec_ref_known(v_x_319_, 3);
v___x_325_ = lean_apply_3(v_h__1_320_, v_f_322_, v_u_323_, v_v_324_);
return v___x_325_;
}
else
{
lean_object* v___x_326_; 
lean_dec(v_h__1_320_);
v___x_326_ = lean_apply_2(v_h__2_321_, v_x_319_, lean_box(0));
return v___x_326_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter___boxed(lean_object* v_I_327_, lean_object* v_motive_328_, lean_object* v_x_329_, lean_object* v_h__1_330_, lean_object* v_h__2_331_){
_start:
{
lean_object* v_res_332_; 
v_res_332_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_isFerrySail_match__1_splitter(v_I_327_, v_motive_328_, v_x_329_, v_h__1_330_, v_h__2_331_);
lean_dec_ref(v_I_327_);
return v_res_332_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter___redArg(lean_object* v_x_333_, lean_object* v_h__1_334_, lean_object* v_h__2_335_){
_start:
{
if (lean_obj_tag(v_x_333_) == 5)
{
lean_object* v_f_336_; lean_object* v_u_337_; lean_object* v_v_338_; lean_object* v___x_339_; 
lean_dec(v_h__2_335_);
v_f_336_ = lean_ctor_get(v_x_333_, 0);
lean_inc(v_f_336_);
v_u_337_ = lean_ctor_get(v_x_333_, 1);
lean_inc(v_u_337_);
v_v_338_ = lean_ctor_get(v_x_333_, 2);
lean_inc(v_v_338_);
lean_dec_ref_known(v_x_333_, 3);
v___x_339_ = lean_apply_3(v_h__1_334_, v_f_336_, v_u_337_, v_v_338_);
return v___x_339_;
}
else
{
lean_object* v___x_340_; 
lean_dec(v_h__1_334_);
v___x_340_ = lean_apply_2(v_h__2_335_, v_x_333_, lean_box(0));
return v___x_340_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter(lean_object* v_I_341_, lean_object* v_motive_342_, lean_object* v_x_343_, lean_object* v_h__1_344_, lean_object* v_h__2_345_){
_start:
{
if (lean_obj_tag(v_x_343_) == 5)
{
lean_object* v_f_346_; lean_object* v_u_347_; lean_object* v_v_348_; lean_object* v___x_349_; 
lean_dec(v_h__2_345_);
v_f_346_ = lean_ctor_get(v_x_343_, 0);
lean_inc(v_f_346_);
v_u_347_ = lean_ctor_get(v_x_343_, 1);
lean_inc(v_u_347_);
v_v_348_ = lean_ctor_get(v_x_343_, 2);
lean_inc(v_v_348_);
lean_dec_ref_known(v_x_343_, 3);
v___x_349_ = lean_apply_3(v_h__1_344_, v_f_346_, v_u_347_, v_v_348_);
return v___x_349_;
}
else
{
lean_object* v___x_350_; 
lean_dec(v_h__1_344_);
v___x_350_ = lean_apply_2(v_h__2_345_, v_x_343_, lean_box(0));
return v___x_350_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter___boxed(lean_object* v_I_351_, lean_object* v_motive_352_, lean_object* v_x_353_, lean_object* v_h__1_354_, lean_object* v_h__2_355_){
_start:
{
lean_object* v_res_356_; 
v_res_356_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_actionCost_match__1_splitter(v_I_351_, v_motive_352_, v_x_353_, v_h__1_354_, v_h__2_355_);
lean_dec_ref(v_I_351_);
return v_res_356_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg(lean_object* v_G_357_, lean_object* v_fi_358_, lean_object* v_inH_359_, lean_object* v_x_360_){
_start:
{
if (lean_obj_tag(v_x_360_) == 5)
{
lean_object* v_f_361_; lean_object* v_u_362_; lean_object* v_v_363_; uint8_t v___x_364_; 
v_f_361_ = lean_ctor_get(v_x_360_, 0);
lean_inc(v_f_361_);
v_u_362_ = lean_ctor_get(v_x_360_, 1);
lean_inc(v_u_362_);
v_v_363_ = lean_ctor_get(v_x_360_, 2);
lean_inc(v_v_363_);
lean_dec_ref_known(v_x_360_, 3);
v___x_364_ = lean_nat_dec_eq(v_f_361_, v_fi_358_);
lean_dec(v_f_361_);
if (v___x_364_ == 0)
{
lean_dec(v_v_363_);
lean_dec(v_u_362_);
lean_dec_ref(v_inH_359_);
lean_dec_ref(v_G_357_);
return v___x_364_;
}
else
{
lean_object* v_islandOf_365_; lean_object* v___x_366_; lean_object* v___x_367_; uint8_t v___x_368_; 
v_islandOf_365_ = lean_ctor_get(v_G_357_, 1);
lean_inc_ref_n(v_islandOf_365_, 2);
lean_dec_ref(v_G_357_);
v___x_366_ = lean_apply_1(v_islandOf_365_, v_u_362_);
lean_inc_ref(v_inH_359_);
v___x_367_ = lean_apply_1(v_inH_359_, v___x_366_);
v___x_368_ = lean_unbox(v___x_367_);
if (v___x_368_ == 0)
{
uint8_t v___x_369_; 
lean_dec_ref(v_islandOf_365_);
lean_dec(v_v_363_);
lean_dec_ref(v_inH_359_);
v___x_369_ = lean_unbox(v___x_367_);
return v___x_369_;
}
else
{
lean_object* v___x_370_; lean_object* v___x_371_; uint8_t v___x_372_; 
v___x_370_ = lean_apply_1(v_islandOf_365_, v_v_363_);
v___x_371_ = lean_apply_1(v_inH_359_, v___x_370_);
v___x_372_ = lean_unbox(v___x_371_);
if (v___x_372_ == 0)
{
uint8_t v___x_373_; 
v___x_373_ = lean_unbox(v___x_367_);
return v___x_373_;
}
else
{
uint8_t v___x_374_; 
v___x_374_ = 0;
return v___x_374_;
}
}
}
}
else
{
uint8_t v___x_375_; 
lean_dec_ref(v_x_360_);
lean_dec_ref(v_inH_359_);
lean_dec_ref(v_G_357_);
v___x_375_ = 0;
return v___x_375_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg___boxed(lean_object* v_G_376_, lean_object* v_fi_377_, lean_object* v_inH_378_, lean_object* v_x_379_){
_start:
{
uint8_t v_res_380_; lean_object* v_r_381_; 
v_res_380_ = lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg(v_G_376_, v_fi_377_, v_inH_378_, v_x_379_);
lean_dec(v_fi_377_);
v_r_381_ = lean_box(v_res_380_);
return v_r_381_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailAB(lean_object* v_I_382_, lean_object* v_G_383_, lean_object* v_fi_384_, lean_object* v_inH_385_, lean_object* v_x_386_){
_start:
{
uint8_t v___x_387_; 
v___x_387_ = lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg(v_G_383_, v_fi_384_, v_inH_385_, v_x_386_);
return v___x_387_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailAB___boxed(lean_object* v_I_388_, lean_object* v_G_389_, lean_object* v_fi_390_, lean_object* v_inH_391_, lean_object* v_x_392_){
_start:
{
uint8_t v_res_393_; lean_object* v_r_394_; 
v_res_393_ = lp_island__logistics__proof_IslandLogistics_isCutSailAB(v_I_388_, v_G_389_, v_fi_390_, v_inH_391_, v_x_392_);
lean_dec(v_fi_390_);
lean_dec_ref(v_I_388_);
v_r_394_ = lean_box(v_res_393_);
return v_r_394_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg(lean_object* v_G_395_, lean_object* v_fi_396_, lean_object* v_inH_397_, lean_object* v_x_398_){
_start:
{
if (lean_obj_tag(v_x_398_) == 5)
{
lean_object* v_f_399_; lean_object* v_u_400_; lean_object* v_v_401_; uint8_t v___x_402_; 
v_f_399_ = lean_ctor_get(v_x_398_, 0);
lean_inc(v_f_399_);
v_u_400_ = lean_ctor_get(v_x_398_, 1);
lean_inc(v_u_400_);
v_v_401_ = lean_ctor_get(v_x_398_, 2);
lean_inc(v_v_401_);
lean_dec_ref_known(v_x_398_, 3);
v___x_402_ = lean_nat_dec_eq(v_f_399_, v_fi_396_);
lean_dec(v_f_399_);
if (v___x_402_ == 0)
{
lean_dec(v_v_401_);
lean_dec(v_u_400_);
lean_dec_ref(v_inH_397_);
lean_dec_ref(v_G_395_);
return v___x_402_;
}
else
{
lean_object* v_islandOf_403_; lean_object* v___x_404_; lean_object* v___x_405_; uint8_t v___x_406_; 
v_islandOf_403_ = lean_ctor_get(v_G_395_, 1);
lean_inc_ref_n(v_islandOf_403_, 2);
lean_dec_ref(v_G_395_);
v___x_404_ = lean_apply_1(v_islandOf_403_, v_u_400_);
lean_inc_ref(v_inH_397_);
v___x_405_ = lean_apply_1(v_inH_397_, v___x_404_);
v___x_406_ = lean_unbox(v___x_405_);
if (v___x_406_ == 0)
{
lean_object* v___x_407_; lean_object* v___x_408_; uint8_t v___x_409_; 
v___x_407_ = lean_apply_1(v_islandOf_403_, v_v_401_);
v___x_408_ = lean_apply_1(v_inH_397_, v___x_407_);
v___x_409_ = lean_unbox(v___x_408_);
return v___x_409_;
}
else
{
uint8_t v___x_410_; 
lean_dec_ref(v_islandOf_403_);
lean_dec(v_v_401_);
lean_dec_ref(v_inH_397_);
v___x_410_ = 0;
return v___x_410_;
}
}
}
else
{
uint8_t v___x_411_; 
lean_dec_ref(v_x_398_);
lean_dec_ref(v_inH_397_);
lean_dec_ref(v_G_395_);
v___x_411_ = 0;
return v___x_411_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg___boxed(lean_object* v_G_412_, lean_object* v_fi_413_, lean_object* v_inH_414_, lean_object* v_x_415_){
_start:
{
uint8_t v_res_416_; lean_object* v_r_417_; 
v_res_416_ = lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg(v_G_412_, v_fi_413_, v_inH_414_, v_x_415_);
lean_dec(v_fi_413_);
v_r_417_ = lean_box(v_res_416_);
return v_r_417_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isCutSailBA(lean_object* v_I_418_, lean_object* v_G_419_, lean_object* v_fi_420_, lean_object* v_inH_421_, lean_object* v_x_422_){
_start:
{
uint8_t v___x_423_; 
v___x_423_ = lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg(v_G_419_, v_fi_420_, v_inH_421_, v_x_422_);
return v___x_423_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isCutSailBA___boxed(lean_object* v_I_424_, lean_object* v_G_425_, lean_object* v_fi_426_, lean_object* v_inH_427_, lean_object* v_x_428_){
_start:
{
uint8_t v_res_429_; lean_object* v_r_430_; 
v_res_429_ = lp_island__logistics__proof_IslandLogistics_isCutSailBA(v_I_424_, v_G_425_, v_fi_426_, v_inH_427_, v_x_428_);
lean_dec(v_fi_426_);
lean_dec_ref(v_I_424_);
v_r_430_ = lean_box(v_res_429_);
return v_r_430_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedCutSailAB(lean_object* v_I_431_, lean_object* v_G_432_, lean_object* v_fi_433_, lean_object* v_inH_434_, lean_object* v_x_435_, lean_object* v_x_436_){
_start:
{
if (lean_obj_tag(v_x_436_) == 0)
{
lean_object* v___x_437_; 
lean_dec_ref(v_x_435_);
lean_dec_ref(v_inH_434_);
lean_dec(v_fi_433_);
lean_dec_ref(v_G_432_);
lean_dec_ref(v_I_431_);
v___x_437_ = lean_unsigned_to_nat(0u);
return v___x_437_;
}
else
{
lean_object* v_head_438_; lean_object* v_tail_439_; lean_object* v___y_441_; uint8_t v___x_447_; 
v_head_438_ = lean_ctor_get(v_x_436_, 0);
lean_inc_n(v_head_438_, 2);
v_tail_439_ = lean_ctor_get(v_x_436_, 1);
lean_inc(v_tail_439_);
lean_dec_ref_known(v_x_436_, 2);
lean_inc_ref(v_inH_434_);
lean_inc_ref(v_G_432_);
v___x_447_ = lp_island__logistics__proof_IslandLogistics_isCutSailAB___redArg(v_G_432_, v_fi_433_, v_inH_434_, v_head_438_);
if (v___x_447_ == 0)
{
goto v___jp_445_;
}
else
{
lean_object* v___x_448_; lean_object* v___x_449_; uint8_t v___x_450_; 
v___x_448_ = lean_unsigned_to_nat(0u);
lean_inc(v_fi_433_);
lean_inc_ref(v_x_435_);
lean_inc_ref(v_I_431_);
v___x_449_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_431_, v_x_435_, v_fi_433_);
v___x_450_ = lean_nat_dec_lt(v___x_448_, v___x_449_);
lean_dec(v___x_449_);
if (v___x_450_ == 0)
{
goto v___jp_445_;
}
else
{
lean_object* v___x_451_; 
v___x_451_ = lean_unsigned_to_nat(1u);
v___y_441_ = v___x_451_;
goto v___jp_440_;
}
}
v___jp_440_:
{
lean_object* v___x_442_; lean_object* v___x_443_; lean_object* v___x_444_; 
lean_inc_ref(v_I_431_);
v___x_442_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_431_, v_x_435_, v_head_438_);
v___x_443_ = lp_island__logistics__proof_IslandLogistics_loadedCutSailAB(v_I_431_, v_G_432_, v_fi_433_, v_inH_434_, v___x_442_, v_tail_439_);
v___x_444_ = lean_nat_add(v___y_441_, v___x_443_);
lean_dec(v___x_443_);
return v___x_444_;
}
v___jp_445_:
{
lean_object* v___x_446_; 
v___x_446_ = lean_unsigned_to_nat(0u);
v___y_441_ = v___x_446_;
goto v___jp_440_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedCutSailBA(lean_object* v_I_452_, lean_object* v_G_453_, lean_object* v_fi_454_, lean_object* v_inH_455_, lean_object* v_x_456_, lean_object* v_x_457_){
_start:
{
if (lean_obj_tag(v_x_457_) == 0)
{
lean_object* v___x_458_; 
lean_dec_ref(v_x_456_);
lean_dec_ref(v_inH_455_);
lean_dec(v_fi_454_);
lean_dec_ref(v_G_453_);
lean_dec_ref(v_I_452_);
v___x_458_ = lean_unsigned_to_nat(0u);
return v___x_458_;
}
else
{
lean_object* v_head_459_; lean_object* v_tail_460_; lean_object* v___y_462_; uint8_t v___x_468_; 
v_head_459_ = lean_ctor_get(v_x_457_, 0);
lean_inc_n(v_head_459_, 2);
v_tail_460_ = lean_ctor_get(v_x_457_, 1);
lean_inc(v_tail_460_);
lean_dec_ref_known(v_x_457_, 2);
lean_inc_ref(v_inH_455_);
lean_inc_ref(v_G_453_);
v___x_468_ = lp_island__logistics__proof_IslandLogistics_isCutSailBA___redArg(v_G_453_, v_fi_454_, v_inH_455_, v_head_459_);
if (v___x_468_ == 0)
{
goto v___jp_466_;
}
else
{
lean_object* v___x_469_; lean_object* v___x_470_; uint8_t v___x_471_; 
v___x_469_ = lean_unsigned_to_nat(0u);
lean_inc(v_fi_454_);
lean_inc_ref(v_x_456_);
lean_inc_ref(v_I_452_);
v___x_470_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_452_, v_x_456_, v_fi_454_);
v___x_471_ = lean_nat_dec_lt(v___x_469_, v___x_470_);
lean_dec(v___x_470_);
if (v___x_471_ == 0)
{
goto v___jp_466_;
}
else
{
lean_object* v___x_472_; 
v___x_472_ = lean_unsigned_to_nat(1u);
v___y_462_ = v___x_472_;
goto v___jp_461_;
}
}
v___jp_461_:
{
lean_object* v___x_463_; lean_object* v___x_464_; lean_object* v___x_465_; 
lean_inc_ref(v_I_452_);
v___x_463_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_452_, v_x_456_, v_head_459_);
v___x_464_ = lp_island__logistics__proof_IslandLogistics_loadedCutSailBA(v_I_452_, v_G_453_, v_fi_454_, v_inH_455_, v___x_463_, v_tail_460_);
v___x_465_ = lean_nat_add(v___y_462_, v___x_464_);
lean_dec(v___x_464_);
return v___x_465_;
}
v___jp_466_:
{
lean_object* v___x_467_; 
v___x_467_ = lean_unsigned_to_nat(0u);
v___y_462_ = v___x_467_;
goto v___jp_461_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object* v_x_473_, lean_object* v_h__1_474_, lean_object* v_h__2_475_){
_start:
{
if (lean_obj_tag(v_x_473_) == 0)
{
lean_object* v_l_476_; lean_object* v___x_477_; 
lean_dec(v_h__2_475_);
v_l_476_ = lean_ctor_get(v_x_473_, 0);
lean_inc(v_l_476_);
lean_dec_ref_known(v_x_473_, 1);
v___x_477_ = lean_apply_1(v_h__1_474_, v_l_476_);
return v___x_477_;
}
else
{
lean_object* v_f_478_; lean_object* v___x_479_; 
lean_dec(v_h__1_474_);
v_f_478_ = lean_ctor_get(v_x_473_, 0);
lean_inc(v_f_478_);
lean_dec_ref_known(v_x_473_, 1);
v___x_479_ = lean_apply_1(v_h__2_475_, v_f_478_);
return v___x_479_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object* v_I_480_, lean_object* v_motive_481_, lean_object* v_x_482_, lean_object* v_h__1_483_, lean_object* v_h__2_484_){
_start:
{
if (lean_obj_tag(v_x_482_) == 0)
{
lean_object* v_l_485_; lean_object* v___x_486_; 
lean_dec(v_h__2_484_);
v_l_485_ = lean_ctor_get(v_x_482_, 0);
lean_inc(v_l_485_);
lean_dec_ref_known(v_x_482_, 1);
v___x_486_ = lean_apply_1(v_h__1_483_, v_l_485_);
return v___x_486_;
}
else
{
lean_object* v_f_487_; lean_object* v___x_488_; 
lean_dec(v_h__1_483_);
v_f_487_ = lean_ctor_get(v_x_482_, 0);
lean_inc(v_f_487_);
lean_dec_ref_known(v_x_482_, 1);
v___x_488_ = lean_apply_1(v_h__2_484_, v_f_487_);
return v___x_488_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object* v_I_489_, lean_object* v_motive_490_, lean_object* v_x_491_, lean_object* v_h__1_492_, lean_object* v_h__2_493_){
_start:
{
lean_object* v_res_494_; 
v_res_494_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(v_I_489_, v_motive_490_, v_x_491_, v_h__1_492_, v_h__2_493_);
lean_dec_ref(v_I_489_);
return v_res_494_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter___redArg(lean_object* v_x_495_, lean_object* v_h__1_496_, lean_object* v_h__2_497_){
_start:
{
if (lean_obj_tag(v_x_495_) == 0)
{
lean_object* v_l_498_; lean_object* v___x_499_; 
lean_dec(v_h__2_497_);
v_l_498_ = lean_ctor_get(v_x_495_, 0);
lean_inc(v_l_498_);
lean_dec_ref_known(v_x_495_, 1);
v___x_499_ = lean_apply_1(v_h__1_496_, v_l_498_);
return v___x_499_;
}
else
{
lean_object* v_t_500_; lean_object* v___x_501_; 
lean_dec(v_h__1_496_);
v_t_500_ = lean_ctor_get(v_x_495_, 0);
lean_inc(v_t_500_);
lean_dec_ref_known(v_x_495_, 1);
v___x_501_ = lean_apply_1(v_h__2_497_, v_t_500_);
return v___x_501_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter(lean_object* v_I_502_, lean_object* v_motive_503_, lean_object* v_x_504_, lean_object* v_h__1_505_, lean_object* v_h__2_506_){
_start:
{
if (lean_obj_tag(v_x_504_) == 0)
{
lean_object* v_l_507_; lean_object* v___x_508_; 
lean_dec(v_h__2_506_);
v_l_507_ = lean_ctor_get(v_x_504_, 0);
lean_inc(v_l_507_);
lean_dec_ref_known(v_x_504_, 1);
v___x_508_ = lean_apply_1(v_h__1_505_, v_l_507_);
return v___x_508_;
}
else
{
lean_object* v_t_509_; lean_object* v___x_510_; 
lean_dec(v_h__1_505_);
v_t_509_ = lean_ctor_get(v_x_504_, 0);
lean_inc(v_t_509_);
lean_dec_ref_known(v_x_504_, 1);
v___x_510_ = lean_apply_1(v_h__2_506_, v_t_509_);
return v___x_510_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter___boxed(lean_object* v_I_511_, lean_object* v_motive_512_, lean_object* v_x_513_, lean_object* v_h__1_514_, lean_object* v_h__2_515_){
_start:
{
lean_object* v_res_516_; 
v_res_516_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_cutFerry__step__bounds_match__1_splitter(v_I_511_, v_motive_512_, v_x_513_, v_h__1_514_, v_h__2_515_);
lean_dec_ref(v_I_511_);
return v_res_516_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object* v_x_517_, lean_object* v_h__1_518_, lean_object* v_h__2_519_){
_start:
{
if (lean_obj_tag(v_x_517_) == 0)
{
lean_object* v_l_520_; lean_object* v___x_521_; 
lean_dec(v_h__2_519_);
v_l_520_ = lean_ctor_get(v_x_517_, 0);
lean_inc(v_l_520_);
lean_dec_ref_known(v_x_517_, 1);
v___x_521_ = lean_apply_1(v_h__1_518_, v_l_520_);
return v___x_521_;
}
else
{
lean_object* v_t_522_; lean_object* v___x_523_; 
lean_dec(v_h__1_518_);
v_t_522_ = lean_ctor_get(v_x_517_, 0);
lean_inc(v_t_522_);
lean_dec_ref_known(v_x_517_, 1);
v___x_523_ = lean_apply_1(v_h__2_519_, v_t_522_);
return v___x_523_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object* v_I_524_, lean_object* v_motive_525_, lean_object* v_x_526_, lean_object* v_h__1_527_, lean_object* v_h__2_528_){
_start:
{
if (lean_obj_tag(v_x_526_) == 0)
{
lean_object* v_l_529_; lean_object* v___x_530_; 
lean_dec(v_h__2_528_);
v_l_529_ = lean_ctor_get(v_x_526_, 0);
lean_inc(v_l_529_);
lean_dec_ref_known(v_x_526_, 1);
v___x_530_ = lean_apply_1(v_h__1_527_, v_l_529_);
return v___x_530_;
}
else
{
lean_object* v_t_531_; lean_object* v___x_532_; 
lean_dec(v_h__1_527_);
v_t_531_ = lean_ctor_get(v_x_526_, 0);
lean_inc(v_t_531_);
lean_dec_ref_known(v_x_526_, 1);
v___x_532_ = lean_apply_1(v_h__2_528_, v_t_531_);
return v___x_532_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object* v_I_533_, lean_object* v_motive_534_, lean_object* v_x_535_, lean_object* v_h__1_536_, lean_object* v_h__2_537_){
_start:
{
lean_object* v_res_538_; 
v_res_538_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_planPkgCrossAB_match__1_splitter(v_I_533_, v_motive_534_, v_x_535_, v_h__1_536_, v_h__2_537_);
lean_dec_ref(v_I_533_);
return v_res_538_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertAsc(lean_object* v_x_539_, lean_object* v_x_540_){
_start:
{
if (lean_obj_tag(v_x_540_) == 0)
{
lean_object* v___x_541_; 
v___x_541_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_541_, 0, v_x_539_);
lean_ctor_set(v___x_541_, 1, v_x_540_);
return v___x_541_;
}
else
{
lean_object* v_head_542_; lean_object* v_tail_543_; uint8_t v___x_544_; 
v_head_542_ = lean_ctor_get(v_x_540_, 0);
v_tail_543_ = lean_ctor_get(v_x_540_, 1);
v___x_544_ = lean_nat_dec_le(v_x_539_, v_head_542_);
if (v___x_544_ == 0)
{
lean_object* v___x_546_; uint8_t v_isShared_547_; uint8_t v_isSharedCheck_552_; 
lean_inc(v_tail_543_);
lean_inc(v_head_542_);
v_isSharedCheck_552_ = !lean_is_exclusive(v_x_540_);
if (v_isSharedCheck_552_ == 0)
{
lean_object* v_unused_553_; lean_object* v_unused_554_; 
v_unused_553_ = lean_ctor_get(v_x_540_, 1);
lean_dec(v_unused_553_);
v_unused_554_ = lean_ctor_get(v_x_540_, 0);
lean_dec(v_unused_554_);
v___x_546_ = v_x_540_;
v_isShared_547_ = v_isSharedCheck_552_;
goto v_resetjp_545_;
}
else
{
lean_dec(v_x_540_);
v___x_546_ = lean_box(0);
v_isShared_547_ = v_isSharedCheck_552_;
goto v_resetjp_545_;
}
v_resetjp_545_:
{
lean_object* v___x_548_; lean_object* v___x_550_; 
v___x_548_ = lp_island__logistics__proof_IslandLogistics_insertAsc(v_x_539_, v_tail_543_);
if (v_isShared_547_ == 0)
{
lean_ctor_set(v___x_546_, 1, v___x_548_);
v___x_550_ = v___x_546_;
goto v_reusejp_549_;
}
else
{
lean_object* v_reuseFailAlloc_551_; 
v_reuseFailAlloc_551_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_551_, 0, v_head_542_);
lean_ctor_set(v_reuseFailAlloc_551_, 1, v___x_548_);
v___x_550_ = v_reuseFailAlloc_551_;
goto v_reusejp_549_;
}
v_reusejp_549_:
{
return v___x_550_;
}
}
}
else
{
lean_object* v___x_555_; 
v___x_555_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_555_, 0, v_x_539_);
lean_ctor_set(v___x_555_, 1, v_x_540_);
return v___x_555_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortAsc(lean_object* v_x_556_){
_start:
{
if (lean_obj_tag(v_x_556_) == 0)
{
return v_x_556_;
}
else
{
lean_object* v_head_557_; lean_object* v_tail_558_; lean_object* v___x_559_; lean_object* v___x_560_; 
v_head_557_ = lean_ctor_get(v_x_556_, 0);
lean_inc(v_head_557_);
v_tail_558_ = lean_ctor_get(v_x_556_, 1);
lean_inc(v_tail_558_);
lean_dec_ref_known(v_x_556_, 2);
v___x_559_ = lp_island__logistics__proof_IslandLogistics_sortAsc(v_tail_558_);
v___x_560_ = lp_island__logistics__proof_IslandLogistics_insertAsc(v_head_557_, v___x_559_);
return v___x_560_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sumTake(lean_object* v_k_563_, lean_object* v_l_564_){
_start:
{
lean_object* v___x_565_; lean_object* v___x_566_; lean_object* v___x_567_; 
v___x_565_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_sumTake___closed__0));
lean_inc(v_l_564_);
v___x_566_ = l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(v_l_564_, v_l_564_, v_k_563_, v___x_565_);
lean_dec(v_l_564_);
v___x_567_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_566_);
lean_dec(v___x_566_);
return v___x_567_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg(lean_object* v_w__cur_568_, lean_object* v_w__opp_569_, lean_object* v_h__cur_570_, lean_object* v_h__opp_571_, lean_object* v_m__cur_572_, lean_object* v_m__opp_573_, lean_object* v_c__cur_574_, lean_object* v_c__opp_575_, lean_object* v_cap_576_, uint8_t v_need__cur__b_577_, uint8_t v_need__opp__b_578_, lean_object* v_ab__c_579_, lean_object* v_k__gnd__cur_580_, lean_object* v_ab__stay_581_, lean_object* v_empty__caps_582_, lean_object* v_stay__vals_583_, lean_object* v_z_584_, lean_object* v_x_585_){
_start:
{
lean_object* v_cz_586_; lean_object* v_max__x_587_; lean_object* v___x_588_; lean_object* v_k__carry_589_; lean_object* v_extra__opp_590_; lean_object* v___x_591_; lean_object* v___x_592_; lean_object* v___x_593_; lean_object* v___x_594_; lean_object* v_fst_595_; lean_object* v_snd_596_; lean_object* v___y_598_; lean_object* v___x_605_; uint8_t v___x_606_; 
lean_inc(v_z_584_);
v_cz_586_ = lp_island__logistics__proof_IslandLogistics_sumTake(v_z_584_, v_empty__caps_582_);
v_max__x_587_ = lean_nat_sub(v_ab__c_579_, v_z_584_);
v___x_588_ = lean_nat_sub(v_max__x_587_, v_ab__stay_581_);
v_k__carry_589_ = lean_nat_sub(v_x_585_, v___x_588_);
lean_dec(v___x_588_);
v_extra__opp_590_ = lp_island__logistics__proof_IslandLogistics_sumTake(v_k__carry_589_, v_stay__vals_583_);
v___x_591_ = lean_nat_add(v_w__opp_569_, v_extra__opp_590_);
lean_dec(v_extra__opp_590_);
v___x_592_ = lean_nat_sub(v_m__cur_572_, v_z_584_);
lean_dec(v_z_584_);
v___x_593_ = lean_nat_sub(v_c__cur_574_, v_cz_586_);
lean_dec(v_cz_586_);
v___x_594_ = lp_island__logistics__proof_IslandLogistics_fluxLB(v_w__cur_568_, v___x_591_, v_h__cur_570_, v_h__opp_571_, v_need__cur__b_577_, v_need__opp__b_578_, v___x_592_, v_m__opp_573_, v___x_593_, v_c__opp_575_, v_cap_576_);
lean_dec(v___x_593_);
lean_dec(v___x_592_);
lean_dec(v___x_591_);
v_fst_595_ = lean_ctor_get(v___x_594_, 0);
lean_inc(v_fst_595_);
v_snd_596_ = lean_ctor_get(v___x_594_, 1);
lean_inc(v_snd_596_);
lean_dec_ref(v___x_594_);
v___x_605_ = lean_nat_add(v_x_585_, v_k__gnd__cur_580_);
v___x_606_ = lean_nat_dec_le(v_fst_595_, v___x_605_);
if (v___x_606_ == 0)
{
lean_dec(v___x_605_);
v___y_598_ = v_fst_595_;
goto v___jp_597_;
}
else
{
lean_dec(v_fst_595_);
v___y_598_ = v___x_605_;
goto v___jp_597_;
}
v___jp_597_:
{
lean_object* v___x_599_; lean_object* v___x_600_; lean_object* v___x_601_; lean_object* v___x_602_; lean_object* v___x_603_; lean_object* v___x_604_; 
v___x_599_ = lean_nat_sub(v_max__x_587_, v_x_585_);
lean_dec(v_max__x_587_);
v___x_600_ = lean_unsigned_to_nat(2u);
v___x_601_ = lean_nat_add(v___y_598_, v_snd_596_);
lean_dec(v_snd_596_);
lean_dec(v___y_598_);
v___x_602_ = lean_nat_mul(v___x_600_, v___x_601_);
lean_dec(v___x_601_);
v___x_603_ = lean_nat_add(v___x_599_, v___x_602_);
lean_dec(v___x_602_);
lean_dec(v___x_599_);
v___x_604_ = lean_nat_sub(v___x_603_, v_x_585_);
lean_dec(v___x_603_);
return v___x_604_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg___boxed(lean_object** _args){
lean_object* v_w__cur_607_ = _args[0];
lean_object* v_w__opp_608_ = _args[1];
lean_object* v_h__cur_609_ = _args[2];
lean_object* v_h__opp_610_ = _args[3];
lean_object* v_m__cur_611_ = _args[4];
lean_object* v_m__opp_612_ = _args[5];
lean_object* v_c__cur_613_ = _args[6];
lean_object* v_c__opp_614_ = _args[7];
lean_object* v_cap_615_ = _args[8];
lean_object* v_need__cur__b_616_ = _args[9];
lean_object* v_need__opp__b_617_ = _args[10];
lean_object* v_ab__c_618_ = _args[11];
lean_object* v_k__gnd__cur_619_ = _args[12];
lean_object* v_ab__stay_620_ = _args[13];
lean_object* v_empty__caps_621_ = _args[14];
lean_object* v_stay__vals_622_ = _args[15];
lean_object* v_z_623_ = _args[16];
lean_object* v_x_624_ = _args[17];
_start:
{
uint8_t v_need__cur__b_boxed_625_; uint8_t v_need__opp__b_boxed_626_; lean_object* v_res_627_; 
v_need__cur__b_boxed_625_ = lean_unbox(v_need__cur__b_616_);
v_need__opp__b_boxed_626_ = lean_unbox(v_need__opp__b_617_);
v_res_627_ = lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg(v_w__cur_607_, v_w__opp_608_, v_h__cur_609_, v_h__opp_610_, v_m__cur_611_, v_m__opp_612_, v_c__cur_613_, v_c__opp_614_, v_cap_615_, v_need__cur__b_boxed_625_, v_need__opp__b_boxed_626_, v_ab__c_618_, v_k__gnd__cur_619_, v_ab__stay_620_, v_empty__caps_621_, v_stay__vals_622_, v_z_623_, v_x_624_);
lean_dec(v_x_624_);
lean_dec(v_ab__stay_620_);
lean_dec(v_k__gnd__cur_619_);
lean_dec(v_ab__c_618_);
lean_dec(v_cap_615_);
lean_dec(v_c__opp_614_);
lean_dec(v_c__cur_613_);
lean_dec(v_m__opp_612_);
lean_dec(v_m__cur_611_);
lean_dec(v_w__opp_608_);
lean_dec(v_w__cur_607_);
return v_res_627_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand(lean_object* v_w__cur_628_, lean_object* v_w__opp_629_, lean_object* v_h__cur_630_, lean_object* v_h__opp_631_, lean_object* v_need__cur_632_, lean_object* v_need__opp_633_, lean_object* v_m__cur_634_, lean_object* v_m__opp_635_, lean_object* v_c__cur_636_, lean_object* v_c__opp_637_, lean_object* v_cap_638_, uint8_t v_need__cur__b_639_, uint8_t v_need__opp__b_640_, lean_object* v_ab__c_641_, lean_object* v_k__gnd__cur_642_, lean_object* v_ab__stay_643_, lean_object* v_empty__caps_644_, lean_object* v_stay__vals_645_, lean_object* v_z_646_, lean_object* v_x_647_){
_start:
{
lean_object* v___x_648_; 
v___x_648_ = lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___redArg(v_w__cur_628_, v_w__opp_629_, v_h__cur_630_, v_h__opp_631_, v_m__cur_634_, v_m__opp_635_, v_c__cur_636_, v_c__opp_637_, v_cap_638_, v_need__cur__b_639_, v_need__opp__b_640_, v_ab__c_641_, v_k__gnd__cur_642_, v_ab__stay_643_, v_empty__caps_644_, v_stay__vals_645_, v_z_646_, v_x_647_);
return v___x_648_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDCand___boxed(lean_object** _args){
lean_object* v_w__cur_649_ = _args[0];
lean_object* v_w__opp_650_ = _args[1];
lean_object* v_h__cur_651_ = _args[2];
lean_object* v_h__opp_652_ = _args[3];
lean_object* v_need__cur_653_ = _args[4];
lean_object* v_need__opp_654_ = _args[5];
lean_object* v_m__cur_655_ = _args[6];
lean_object* v_m__opp_656_ = _args[7];
lean_object* v_c__cur_657_ = _args[8];
lean_object* v_c__opp_658_ = _args[9];
lean_object* v_cap_659_ = _args[10];
lean_object* v_need__cur__b_660_ = _args[11];
lean_object* v_need__opp__b_661_ = _args[12];
lean_object* v_ab__c_662_ = _args[13];
lean_object* v_k__gnd__cur_663_ = _args[14];
lean_object* v_ab__stay_664_ = _args[15];
lean_object* v_empty__caps_665_ = _args[16];
lean_object* v_stay__vals_666_ = _args[17];
lean_object* v_z_667_ = _args[18];
lean_object* v_x_668_ = _args[19];
_start:
{
uint8_t v_need__cur__b_boxed_669_; uint8_t v_need__opp__b_boxed_670_; lean_object* v_res_671_; 
v_need__cur__b_boxed_669_ = lean_unbox(v_need__cur__b_660_);
v_need__opp__b_boxed_670_ = lean_unbox(v_need__opp__b_661_);
v_res_671_ = lp_island__logistics__proof_IslandLogistics_cutFerryBDCand(v_w__cur_649_, v_w__opp_650_, v_h__cur_651_, v_h__opp_652_, v_need__cur_653_, v_need__opp_654_, v_m__cur_655_, v_m__opp_656_, v_c__cur_657_, v_c__opp_658_, v_cap_659_, v_need__cur__b_boxed_669_, v_need__opp__b_boxed_670_, v_ab__c_662_, v_k__gnd__cur_663_, v_ab__stay_664_, v_empty__caps_665_, v_stay__vals_666_, v_z_667_, v_x_668_);
lean_dec(v_x_668_);
lean_dec(v_ab__stay_664_);
lean_dec(v_k__gnd__cur_663_);
lean_dec(v_ab__c_662_);
lean_dec(v_cap_659_);
lean_dec(v_c__opp_658_);
lean_dec(v_c__cur_657_);
lean_dec(v_m__opp_656_);
lean_dec(v_m__cur_655_);
lean_dec(v_need__opp_654_);
lean_dec(v_need__cur_653_);
lean_dec(v_w__opp_650_);
lean_dec(v_w__cur_649_);
return v_res_671_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__2(lean_object* v_cand_672_, lean_object* v_a_673_, lean_object* v_a_674_){
_start:
{
if (lean_obj_tag(v_a_673_) == 0)
{
lean_object* v___x_675_; 
lean_dec_ref(v_cand_672_);
v___x_675_ = l_List_reverse___redArg(v_a_674_);
return v___x_675_;
}
else
{
lean_object* v_head_676_; lean_object* v_tail_677_; lean_object* v___x_679_; uint8_t v_isShared_680_; uint8_t v_isSharedCheck_688_; 
v_head_676_ = lean_ctor_get(v_a_673_, 0);
v_tail_677_ = lean_ctor_get(v_a_673_, 1);
v_isSharedCheck_688_ = !lean_is_exclusive(v_a_673_);
if (v_isSharedCheck_688_ == 0)
{
v___x_679_ = v_a_673_;
v_isShared_680_ = v_isSharedCheck_688_;
goto v_resetjp_678_;
}
else
{
lean_inc(v_tail_677_);
lean_inc(v_head_676_);
lean_dec(v_a_673_);
v___x_679_ = lean_box(0);
v_isShared_680_ = v_isSharedCheck_688_;
goto v_resetjp_678_;
}
v_resetjp_678_:
{
lean_object* v_fst_681_; lean_object* v_snd_682_; lean_object* v___x_683_; lean_object* v___x_685_; 
v_fst_681_ = lean_ctor_get(v_head_676_, 0);
lean_inc(v_fst_681_);
v_snd_682_ = lean_ctor_get(v_head_676_, 1);
lean_inc(v_snd_682_);
lean_dec(v_head_676_);
lean_inc_ref(v_cand_672_);
v___x_683_ = lean_apply_2(v_cand_672_, v_fst_681_, v_snd_682_);
if (v_isShared_680_ == 0)
{
lean_ctor_set(v___x_679_, 1, v_a_674_);
lean_ctor_set(v___x_679_, 0, v___x_683_);
v___x_685_ = v___x_679_;
goto v_reusejp_684_;
}
else
{
lean_object* v_reuseFailAlloc_687_; 
v_reuseFailAlloc_687_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_687_, 0, v___x_683_);
lean_ctor_set(v_reuseFailAlloc_687_, 1, v_a_674_);
v___x_685_ = v_reuseFailAlloc_687_;
goto v_reusejp_684_;
}
v_reusejp_684_:
{
v_a_673_ = v_tail_677_;
v_a_674_ = v___x_685_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__0(lean_object* v_z_689_, lean_object* v_a_690_, lean_object* v_a_691_){
_start:
{
if (lean_obj_tag(v_a_690_) == 0)
{
lean_object* v___x_692_; 
lean_dec(v_z_689_);
v___x_692_ = l_List_reverse___redArg(v_a_691_);
return v___x_692_;
}
else
{
lean_object* v_head_693_; lean_object* v_tail_694_; lean_object* v___x_696_; uint8_t v_isShared_697_; uint8_t v_isSharedCheck_703_; 
v_head_693_ = lean_ctor_get(v_a_690_, 0);
v_tail_694_ = lean_ctor_get(v_a_690_, 1);
v_isSharedCheck_703_ = !lean_is_exclusive(v_a_690_);
if (v_isSharedCheck_703_ == 0)
{
v___x_696_ = v_a_690_;
v_isShared_697_ = v_isSharedCheck_703_;
goto v_resetjp_695_;
}
else
{
lean_inc(v_tail_694_);
lean_inc(v_head_693_);
lean_dec(v_a_690_);
v___x_696_ = lean_box(0);
v_isShared_697_ = v_isSharedCheck_703_;
goto v_resetjp_695_;
}
v_resetjp_695_:
{
lean_object* v___x_698_; lean_object* v___x_700_; 
lean_inc(v_z_689_);
v___x_698_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_698_, 0, v_z_689_);
lean_ctor_set(v___x_698_, 1, v_head_693_);
if (v_isShared_697_ == 0)
{
lean_ctor_set(v___x_696_, 1, v_a_691_);
lean_ctor_set(v___x_696_, 0, v___x_698_);
v___x_700_ = v___x_696_;
goto v_reusejp_699_;
}
else
{
lean_object* v_reuseFailAlloc_702_; 
v_reuseFailAlloc_702_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_702_, 0, v___x_698_);
lean_ctor_set(v_reuseFailAlloc_702_, 1, v_a_691_);
v___x_700_ = v_reuseFailAlloc_702_;
goto v_reusejp_699_;
}
v_reusejp_699_:
{
v_a_690_ = v_tail_694_;
v_a_691_ = v___x_700_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1(lean_object* v_ab__c_704_, lean_object* v_a_705_, lean_object* v_a_706_){
_start:
{
if (lean_obj_tag(v_a_705_) == 0)
{
lean_object* v___x_707_; 
v___x_707_ = lean_array_to_list(v_a_706_);
return v___x_707_;
}
else
{
lean_object* v_head_708_; lean_object* v_tail_709_; lean_object* v___x_710_; lean_object* v___x_711_; lean_object* v___x_712_; lean_object* v___x_713_; lean_object* v___x_714_; lean_object* v___x_715_; lean_object* v___x_716_; 
v_head_708_ = lean_ctor_get(v_a_705_, 0);
lean_inc(v_head_708_);
v_tail_709_ = lean_ctor_get(v_a_705_, 1);
lean_inc(v_tail_709_);
lean_dec_ref_known(v_a_705_, 2);
v___x_710_ = lean_nat_sub(v_ab__c_704_, v_head_708_);
v___x_711_ = lean_unsigned_to_nat(1u);
v___x_712_ = lean_nat_add(v___x_710_, v___x_711_);
lean_dec(v___x_710_);
v___x_713_ = l_List_range(v___x_712_);
v___x_714_ = lean_box(0);
v___x_715_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__0(v_head_708_, v___x_713_, v___x_714_);
v___x_716_ = l_List_foldl___at___00Array_appendList_spec__0___redArg(v_a_706_, v___x_715_);
v_a_705_ = v_tail_709_;
v_a_706_ = v___x_716_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1___boxed(lean_object* v_ab__c_718_, lean_object* v_a_719_, lean_object* v_a_720_){
_start:
{
lean_object* v_res_721_; 
v_res_721_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1(v_ab__c_718_, v_a_719_, v_a_720_);
lean_dec(v_ab__c_718_);
return v_res_721_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDMin(lean_object* v_cand_724_, lean_object* v_ab__empty_725_, lean_object* v_ab__c_726_){
_start:
{
lean_object* v___x_727_; lean_object* v___x_728_; lean_object* v___x_729_; lean_object* v___x_730_; lean_object* v___x_731_; lean_object* v_pairs_732_; lean_object* v___x_733_; lean_object* v___x_734_; 
v___x_727_ = lean_unsigned_to_nat(1u);
v___x_728_ = lean_nat_add(v_ab__empty_725_, v___x_727_);
v___x_729_ = l_List_range(v___x_728_);
v___x_730_ = lean_unsigned_to_nat(0u);
v___x_731_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___closed__0));
v_pairs_732_ = lp_island__logistics__proof___private_Init_Data_List_Impl_0__List_flatMapTR_go___at___00IslandLogistics_cutFerryBDMin_spec__1(v_ab__c_726_, v___x_729_, v___x_731_);
v___x_733_ = lean_box(0);
v___x_734_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_cutFerryBDMin_spec__2(v_cand_724_, v_pairs_732_, v___x_733_);
if (lean_obj_tag(v___x_734_) == 0)
{
return v___x_730_;
}
else
{
lean_object* v_head_735_; lean_object* v_tail_736_; lean_object* v___x_737_; 
v_head_735_ = lean_ctor_get(v___x_734_, 0);
lean_inc(v_head_735_);
v_tail_736_ = lean_ctor_get(v___x_734_, 1);
lean_inc(v_tail_736_);
lean_dec_ref_known(v___x_734_, 2);
v___x_737_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(v_head_735_, v_tail_736_);
lean_dec(v_tail_736_);
lean_dec(v_head_735_);
return v___x_737_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_cutFerryBDMin___boxed(lean_object* v_cand_738_, lean_object* v_ab__empty_739_, lean_object* v_ab__c_740_){
_start:
{
lean_object* v_res_741_; 
v_res_741_ = lp_island__logistics__proof_IslandLogistics_cutFerryBDMin(v_cand_738_, v_ab__empty_739_, v_ab__c_740_);
lean_dec(v_ab__c_740_);
lean_dec(v_ab__empty_739_);
return v_res_741_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsAB(lean_object* v_I_742_, lean_object* v_G_743_, lean_object* v_fi_744_, lean_object* v_curSide_745_, lean_object* v_t_746_, uint8_t v_x_747_, lean_object* v_x_748_, lean_object* v_x_749_){
_start:
{
if (lean_obj_tag(v_x_749_) == 0)
{
lean_object* v___x_750_; 
lean_dec_ref(v_x_748_);
lean_dec_ref(v_curSide_745_);
lean_dec(v_fi_744_);
lean_dec_ref(v_G_743_);
lean_dec_ref(v_I_742_);
v___x_750_ = lean_unsigned_to_nat(0u);
return v___x_750_;
}
else
{
lean_object* v_head_751_; lean_object* v_tail_752_; 
v_head_751_ = lean_ctor_get(v_x_749_, 0);
lean_inc(v_head_751_);
v_tail_752_ = lean_ctor_get(v_x_749_, 1);
lean_inc(v_tail_752_);
lean_dec_ref_known(v_x_749_, 2);
if (lean_obj_tag(v_head_751_) == 4)
{
lean_object* v_t_756_; lean_object* v_f_757_; uint8_t v___x_758_; 
v_t_756_ = lean_ctor_get(v_head_751_, 0);
v_f_757_ = lean_ctor_get(v_head_751_, 1);
v___x_758_ = lean_nat_dec_eq(v_t_756_, v_t_746_);
if (v___x_758_ == 0)
{
goto v___jp_753_;
}
else
{
uint8_t v___x_759_; 
v___x_759_ = lean_nat_dec_eq(v_f_757_, v_fi_744_);
if (v___x_759_ == 0)
{
goto v___jp_753_;
}
else
{
lean_object* v_islandOf_760_; lean_object* v_ferryLoc_761_; lean_object* v___x_762_; lean_object* v___x_763_; lean_object* v_newSide_764_; lean_object* v___y_766_; 
v_islandOf_760_ = lean_ctor_get(v_G_743_, 1);
v_ferryLoc_761_ = lean_ctor_get(v_x_748_, 1);
lean_inc_ref(v_ferryLoc_761_);
lean_inc(v_fi_744_);
v___x_762_ = lean_apply_1(v_ferryLoc_761_, v_fi_744_);
lean_inc_ref(v_islandOf_760_);
v___x_763_ = lean_apply_1(v_islandOf_760_, v___x_762_);
lean_inc_ref(v_curSide_745_);
v_newSide_764_ = lean_apply_1(v_curSide_745_, v___x_763_);
if (v_x_747_ == 0)
{
goto v___jp_771_;
}
else
{
uint8_t v___x_773_; 
v___x_773_ = lean_unbox(v_newSide_764_);
if (v___x_773_ == 0)
{
lean_object* v___x_774_; 
v___x_774_ = lean_unsigned_to_nat(1u);
v___y_766_ = v___x_774_;
goto v___jp_765_;
}
else
{
goto v___jp_771_;
}
}
v___jp_765_:
{
lean_object* v___x_767_; uint8_t v___x_768_; lean_object* v___x_769_; lean_object* v___x_770_; 
lean_inc_ref(v_I_742_);
v___x_767_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_742_, v_x_748_, v_head_751_);
v___x_768_ = lean_unbox(v_newSide_764_);
v___x_769_ = lp_island__logistics__proof_IslandLogistics_frozenFlipsAB(v_I_742_, v_G_743_, v_fi_744_, v_curSide_745_, v_t_746_, v___x_768_, v___x_767_, v_tail_752_);
v___x_770_ = lean_nat_add(v___y_766_, v___x_769_);
lean_dec(v___x_769_);
return v___x_770_;
}
v___jp_771_:
{
lean_object* v___x_772_; 
v___x_772_ = lean_unsigned_to_nat(0u);
v___y_766_ = v___x_772_;
goto v___jp_765_;
}
}
}
}
else
{
lean_object* v___x_775_; 
lean_inc_ref(v_I_742_);
v___x_775_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_742_, v_x_748_, v_head_751_);
v_x_748_ = v___x_775_;
v_x_749_ = v_tail_752_;
goto _start;
}
v___jp_753_:
{
lean_object* v___x_754_; 
lean_inc_ref(v_I_742_);
v___x_754_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_742_, v_x_748_, v_head_751_);
v_x_748_ = v___x_754_;
v_x_749_ = v_tail_752_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsAB___boxed(lean_object* v_I_777_, lean_object* v_G_778_, lean_object* v_fi_779_, lean_object* v_curSide_780_, lean_object* v_t_781_, lean_object* v_x_782_, lean_object* v_x_783_, lean_object* v_x_784_){
_start:
{
uint8_t v_x_270__boxed_785_; lean_object* v_res_786_; 
v_x_270__boxed_785_ = lean_unbox(v_x_782_);
v_res_786_ = lp_island__logistics__proof_IslandLogistics_frozenFlipsAB(v_I_777_, v_G_778_, v_fi_779_, v_curSide_780_, v_t_781_, v_x_270__boxed_785_, v_x_783_, v_x_784_);
lean_dec(v_t_781_);
return v_res_786_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsBA(lean_object* v_I_787_, lean_object* v_G_788_, lean_object* v_fi_789_, lean_object* v_curSide_790_, lean_object* v_t_791_, uint8_t v_x_792_, lean_object* v_x_793_, lean_object* v_x_794_){
_start:
{
if (lean_obj_tag(v_x_794_) == 0)
{
lean_object* v___x_795_; 
lean_dec_ref(v_x_793_);
lean_dec_ref(v_curSide_790_);
lean_dec(v_fi_789_);
lean_dec_ref(v_G_788_);
lean_dec_ref(v_I_787_);
v___x_795_ = lean_unsigned_to_nat(0u);
return v___x_795_;
}
else
{
lean_object* v_head_796_; lean_object* v_tail_797_; 
v_head_796_ = lean_ctor_get(v_x_794_, 0);
lean_inc(v_head_796_);
v_tail_797_ = lean_ctor_get(v_x_794_, 1);
lean_inc(v_tail_797_);
lean_dec_ref_known(v_x_794_, 2);
if (lean_obj_tag(v_head_796_) == 4)
{
lean_object* v_t_801_; lean_object* v_f_802_; uint8_t v___x_803_; 
v_t_801_ = lean_ctor_get(v_head_796_, 0);
v_f_802_ = lean_ctor_get(v_head_796_, 1);
v___x_803_ = lean_nat_dec_eq(v_t_801_, v_t_791_);
if (v___x_803_ == 0)
{
goto v___jp_798_;
}
else
{
uint8_t v___x_804_; 
v___x_804_ = lean_nat_dec_eq(v_f_802_, v_fi_789_);
if (v___x_804_ == 0)
{
goto v___jp_798_;
}
else
{
lean_object* v_islandOf_805_; lean_object* v_ferryLoc_806_; lean_object* v___x_807_; lean_object* v___x_808_; lean_object* v_newSide_809_; lean_object* v___y_811_; 
v_islandOf_805_ = lean_ctor_get(v_G_788_, 1);
v_ferryLoc_806_ = lean_ctor_get(v_x_793_, 1);
lean_inc_ref(v_ferryLoc_806_);
lean_inc(v_fi_789_);
v___x_807_ = lean_apply_1(v_ferryLoc_806_, v_fi_789_);
lean_inc_ref(v_islandOf_805_);
v___x_808_ = lean_apply_1(v_islandOf_805_, v___x_807_);
lean_inc_ref(v_curSide_790_);
v_newSide_809_ = lean_apply_1(v_curSide_790_, v___x_808_);
if (v_x_792_ == 0)
{
uint8_t v___x_818_; 
v___x_818_ = lean_unbox(v_newSide_809_);
if (v___x_818_ == 0)
{
goto v___jp_816_;
}
else
{
lean_object* v___x_819_; 
v___x_819_ = lean_unsigned_to_nat(1u);
v___y_811_ = v___x_819_;
goto v___jp_810_;
}
}
else
{
goto v___jp_816_;
}
v___jp_810_:
{
lean_object* v___x_812_; uint8_t v___x_813_; lean_object* v___x_814_; lean_object* v___x_815_; 
lean_inc_ref(v_I_787_);
v___x_812_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_787_, v_x_793_, v_head_796_);
v___x_813_ = lean_unbox(v_newSide_809_);
v___x_814_ = lp_island__logistics__proof_IslandLogistics_frozenFlipsBA(v_I_787_, v_G_788_, v_fi_789_, v_curSide_790_, v_t_791_, v___x_813_, v___x_812_, v_tail_797_);
v___x_815_ = lean_nat_add(v___y_811_, v___x_814_);
lean_dec(v___x_814_);
return v___x_815_;
}
v___jp_816_:
{
lean_object* v___x_817_; 
v___x_817_ = lean_unsigned_to_nat(0u);
v___y_811_ = v___x_817_;
goto v___jp_810_;
}
}
}
}
else
{
lean_object* v___x_820_; 
lean_inc_ref(v_I_787_);
v___x_820_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_787_, v_x_793_, v_head_796_);
v_x_793_ = v___x_820_;
v_x_794_ = v_tail_797_;
goto _start;
}
v___jp_798_:
{
lean_object* v___x_799_; 
lean_inc_ref(v_I_787_);
v___x_799_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_787_, v_x_793_, v_head_796_);
v_x_793_ = v___x_799_;
v_x_794_ = v_tail_797_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_frozenFlipsBA___boxed(lean_object* v_I_822_, lean_object* v_G_823_, lean_object* v_fi_824_, lean_object* v_curSide_825_, lean_object* v_t_826_, lean_object* v_x_827_, lean_object* v_x_828_, lean_object* v_x_829_){
_start:
{
uint8_t v_x_268__boxed_830_; lean_object* v_res_831_; 
v_x_268__boxed_830_ = lean_unbox(v_x_827_);
v_res_831_ = lp_island__logistics__proof_IslandLogistics_frozenFlipsBA(v_I_822_, v_G_823_, v_fi_824_, v_curSide_825_, v_t_826_, v_x_268__boxed_830_, v_x_828_, v_x_829_);
lean_dec(v_t_826_);
return v_res_831_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___redArg(uint8_t v_x_832_, lean_object* v_x_833_, lean_object* v_x_834_, lean_object* v_h__1_835_, lean_object* v_h__2_836_){
_start:
{
if (lean_obj_tag(v_x_834_) == 0)
{
lean_object* v___x_837_; lean_object* v___x_838_; 
lean_dec(v_h__2_836_);
v___x_837_ = lean_box(v_x_832_);
v___x_838_ = lean_apply_2(v_h__1_835_, v___x_837_, v_x_833_);
return v___x_838_;
}
else
{
lean_object* v_head_839_; lean_object* v_tail_840_; lean_object* v___x_841_; lean_object* v___x_842_; 
lean_dec(v_h__1_835_);
v_head_839_ = lean_ctor_get(v_x_834_, 0);
lean_inc(v_head_839_);
v_tail_840_ = lean_ctor_get(v_x_834_, 1);
lean_inc(v_tail_840_);
lean_dec_ref_known(v_x_834_, 2);
v___x_841_ = lean_box(v_x_832_);
v___x_842_ = lean_apply_4(v_h__2_836_, v___x_841_, v_x_833_, v_head_839_, v_tail_840_);
return v___x_842_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___redArg___boxed(lean_object* v_x_843_, lean_object* v_x_844_, lean_object* v_x_845_, lean_object* v_h__1_846_, lean_object* v_h__2_847_){
_start:
{
uint8_t v_x_28__boxed_848_; lean_object* v_res_849_; 
v_x_28__boxed_848_ = lean_unbox(v_x_843_);
v_res_849_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___redArg(v_x_28__boxed_848_, v_x_844_, v_x_845_, v_h__1_846_, v_h__2_847_);
return v_res_849_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter(lean_object* v_I_850_, lean_object* v_motive_851_, uint8_t v_x_852_, lean_object* v_x_853_, lean_object* v_x_854_, lean_object* v_h__1_855_, lean_object* v_h__2_856_){
_start:
{
if (lean_obj_tag(v_x_854_) == 0)
{
lean_object* v___x_857_; lean_object* v___x_858_; 
lean_dec(v_h__2_856_);
v___x_857_ = lean_box(v_x_852_);
v___x_858_ = lean_apply_2(v_h__1_855_, v___x_857_, v_x_853_);
return v___x_858_;
}
else
{
lean_object* v_head_859_; lean_object* v_tail_860_; lean_object* v___x_861_; lean_object* v___x_862_; 
lean_dec(v_h__1_855_);
v_head_859_ = lean_ctor_get(v_x_854_, 0);
lean_inc(v_head_859_);
v_tail_860_ = lean_ctor_get(v_x_854_, 1);
lean_inc(v_tail_860_);
lean_dec_ref_known(v_x_854_, 2);
v___x_861_ = lean_box(v_x_852_);
v___x_862_ = lean_apply_4(v_h__2_856_, v___x_861_, v_x_853_, v_head_859_, v_tail_860_);
return v___x_862_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter___boxed(lean_object* v_I_863_, lean_object* v_motive_864_, lean_object* v_x_865_, lean_object* v_x_866_, lean_object* v_x_867_, lean_object* v_h__1_868_, lean_object* v_h__2_869_){
_start:
{
uint8_t v_x_49__boxed_870_; lean_object* v_res_871_; 
v_x_49__boxed_870_ = lean_unbox(v_x_865_);
v_res_871_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_frozenFlipsAB_match__1_splitter(v_I_863_, v_motive_864_, v_x_49__boxed_870_, v_x_866_, v_x_867_, v_h__1_868_, v_h__2_869_);
lean_dec_ref(v_I_863_);
return v_res_871_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstDisembarkSide(lean_object* v_I_872_, lean_object* v_G_873_, lean_object* v_fi_874_, lean_object* v_curSide_875_, lean_object* v_t_876_, lean_object* v_x_877_, lean_object* v_x_878_){
_start:
{
if (lean_obj_tag(v_x_878_) == 0)
{
lean_object* v___x_879_; 
lean_dec_ref(v_x_877_);
lean_dec_ref(v_curSide_875_);
lean_dec(v_fi_874_);
lean_dec_ref(v_G_873_);
lean_dec_ref(v_I_872_);
v___x_879_ = lean_box(0);
return v___x_879_;
}
else
{
lean_object* v_head_880_; lean_object* v_tail_881_; 
v_head_880_ = lean_ctor_get(v_x_878_, 0);
lean_inc(v_head_880_);
v_tail_881_ = lean_ctor_get(v_x_878_, 1);
lean_inc(v_tail_881_);
lean_dec_ref_known(v_x_878_, 2);
if (lean_obj_tag(v_head_880_) == 4)
{
lean_object* v_t_885_; lean_object* v_f_886_; uint8_t v___x_887_; 
v_t_885_ = lean_ctor_get(v_head_880_, 0);
v_f_886_ = lean_ctor_get(v_head_880_, 1);
v___x_887_ = lean_nat_dec_eq(v_t_885_, v_t_876_);
if (v___x_887_ == 0)
{
goto v___jp_882_;
}
else
{
uint8_t v___x_888_; 
v___x_888_ = lean_nat_dec_eq(v_f_886_, v_fi_874_);
if (v___x_888_ == 0)
{
goto v___jp_882_;
}
else
{
lean_object* v_islandOf_889_; lean_object* v_ferryLoc_890_; lean_object* v___x_891_; lean_object* v___x_892_; lean_object* v___x_893_; lean_object* v___x_894_; 
lean_dec_ref_known(v_head_880_, 2);
lean_dec(v_tail_881_);
lean_dec_ref(v_I_872_);
v_islandOf_889_ = lean_ctor_get(v_G_873_, 1);
lean_inc_ref(v_islandOf_889_);
lean_dec_ref(v_G_873_);
v_ferryLoc_890_ = lean_ctor_get(v_x_877_, 1);
lean_inc_ref(v_ferryLoc_890_);
lean_dec_ref(v_x_877_);
v___x_891_ = lean_apply_1(v_ferryLoc_890_, v_fi_874_);
v___x_892_ = lean_apply_1(v_islandOf_889_, v___x_891_);
v___x_893_ = lean_apply_1(v_curSide_875_, v___x_892_);
v___x_894_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_894_, 0, v___x_893_);
return v___x_894_;
}
}
}
else
{
lean_object* v___x_895_; 
lean_inc_ref(v_I_872_);
v___x_895_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_872_, v_x_877_, v_head_880_);
v_x_877_ = v___x_895_;
v_x_878_ = v_tail_881_;
goto _start;
}
v___jp_882_:
{
lean_object* v___x_883_; 
lean_inc_ref(v_I_872_);
v___x_883_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_872_, v_x_877_, v_head_880_);
v_x_877_ = v___x_883_;
v_x_878_ = v_tail_881_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstDisembarkSide___boxed(lean_object* v_I_897_, lean_object* v_G_898_, lean_object* v_fi_899_, lean_object* v_curSide_900_, lean_object* v_t_901_, lean_object* v_x_902_, lean_object* v_x_903_){
_start:
{
lean_object* v_res_904_; 
v_res_904_ = lp_island__logistics__proof_IslandLogistics_firstDisembarkSide(v_I_897_, v_G_898_, v_fi_899_, v_curSide_900_, v_t_901_, v_x_902_, v_x_903_);
lean_dec(v_t_901_);
return v_res_904_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter___redArg(lean_object* v_x_905_, lean_object* v_x_906_, lean_object* v_h__1_907_, lean_object* v_h__2_908_){
_start:
{
if (lean_obj_tag(v_x_906_) == 0)
{
lean_object* v___x_909_; 
lean_dec(v_h__2_908_);
v___x_909_ = lean_apply_1(v_h__1_907_, v_x_905_);
return v___x_909_;
}
else
{
lean_object* v_head_910_; lean_object* v_tail_911_; lean_object* v___x_912_; 
lean_dec(v_h__1_907_);
v_head_910_ = lean_ctor_get(v_x_906_, 0);
lean_inc(v_head_910_);
v_tail_911_ = lean_ctor_get(v_x_906_, 1);
lean_inc(v_tail_911_);
lean_dec_ref_known(v_x_906_, 2);
v___x_912_ = lean_apply_3(v_h__2_908_, v_x_905_, v_head_910_, v_tail_911_);
return v___x_912_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter(lean_object* v_I_913_, lean_object* v_motive_914_, lean_object* v_x_915_, lean_object* v_x_916_, lean_object* v_h__1_917_, lean_object* v_h__2_918_){
_start:
{
if (lean_obj_tag(v_x_916_) == 0)
{
lean_object* v___x_919_; 
lean_dec(v_h__2_918_);
v___x_919_ = lean_apply_1(v_h__1_917_, v_x_915_);
return v___x_919_;
}
else
{
lean_object* v_head_920_; lean_object* v_tail_921_; lean_object* v___x_922_; 
lean_dec(v_h__1_917_);
v_head_920_ = lean_ctor_get(v_x_916_, 0);
lean_inc(v_head_920_);
v_tail_921_ = lean_ctor_get(v_x_916_, 1);
lean_inc(v_tail_921_);
lean_dec_ref_known(v_x_916_, 2);
v___x_922_ = lean_apply_3(v_h__2_918_, v_x_915_, v_head_920_, v_tail_921_);
return v___x_922_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter___boxed(lean_object* v_I_923_, lean_object* v_motive_924_, lean_object* v_x_925_, lean_object* v_x_926_, lean_object* v_h__1_927_, lean_object* v_h__2_928_){
_start:
{
lean_object* v_res_929_; 
v_res_929_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedCutSailAB_match__1_splitter(v_I_923_, v_motive_924_, v_x_925_, v_x_926_, v_h__1_927_, v_h__2_928_);
lean_dec_ref(v_I_923_);
return v_res_929_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg(lean_object* v_G_930_, lean_object* v_isl_931_, lean_object* v_s_932_, lean_object* v_x_933_){
_start:
{
if (lean_obj_tag(v_x_933_) == 3)
{
lean_object* v_f_934_; lean_object* v_islandOf_935_; lean_object* v_ferryLoc_936_; lean_object* v___x_937_; lean_object* v___x_938_; uint8_t v___x_939_; 
v_f_934_ = lean_ctor_get(v_x_933_, 1);
lean_inc(v_f_934_);
lean_dec_ref_known(v_x_933_, 2);
v_islandOf_935_ = lean_ctor_get(v_G_930_, 1);
lean_inc_ref(v_islandOf_935_);
lean_dec_ref(v_G_930_);
v_ferryLoc_936_ = lean_ctor_get(v_s_932_, 1);
lean_inc_ref(v_ferryLoc_936_);
lean_dec_ref(v_s_932_);
v___x_937_ = lean_apply_1(v_ferryLoc_936_, v_f_934_);
v___x_938_ = lean_apply_1(v_islandOf_935_, v___x_937_);
v___x_939_ = lean_nat_dec_eq(v___x_938_, v_isl_931_);
lean_dec(v___x_938_);
return v___x_939_;
}
else
{
uint8_t v___x_940_; 
lean_dec_ref(v_x_933_);
lean_dec_ref(v_s_932_);
lean_dec_ref(v_G_930_);
v___x_940_ = 0;
return v___x_940_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg___boxed(lean_object* v_G_941_, lean_object* v_isl_942_, lean_object* v_s_943_, lean_object* v_x_944_){
_start:
{
uint8_t v_res_945_; lean_object* v_r_946_; 
v_res_945_ = lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg(v_G_941_, v_isl_942_, v_s_943_, v_x_944_);
lean_dec(v_isl_942_);
v_r_946_ = lean_box(v_res_945_);
return v_r_946_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isBoardOnIsl(lean_object* v_I_947_, lean_object* v_G_948_, lean_object* v_isl_949_, lean_object* v_s_950_, lean_object* v_x_951_){
_start:
{
uint8_t v___x_952_; 
v___x_952_ = lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg(v_G_948_, v_isl_949_, v_s_950_, v_x_951_);
return v___x_952_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___boxed(lean_object* v_I_953_, lean_object* v_G_954_, lean_object* v_isl_955_, lean_object* v_s_956_, lean_object* v_x_957_){
_start:
{
uint8_t v_res_958_; lean_object* v_r_959_; 
v_res_958_ = lp_island__logistics__proof_IslandLogistics_isBoardOnIsl(v_I_953_, v_G_954_, v_isl_955_, v_s_956_, v_x_957_);
lean_dec(v_isl_955_);
lean_dec_ref(v_I_953_);
v_r_959_ = lean_box(v_res_958_);
return v_r_959_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg(lean_object* v_G_960_, lean_object* v_isl_961_, lean_object* v_s_962_, lean_object* v_x_963_){
_start:
{
if (lean_obj_tag(v_x_963_) == 4)
{
lean_object* v_f_964_; lean_object* v_islandOf_965_; lean_object* v_ferryLoc_966_; lean_object* v___x_967_; lean_object* v___x_968_; uint8_t v___x_969_; 
v_f_964_ = lean_ctor_get(v_x_963_, 1);
lean_inc(v_f_964_);
lean_dec_ref_known(v_x_963_, 2);
v_islandOf_965_ = lean_ctor_get(v_G_960_, 1);
lean_inc_ref(v_islandOf_965_);
lean_dec_ref(v_G_960_);
v_ferryLoc_966_ = lean_ctor_get(v_s_962_, 1);
lean_inc_ref(v_ferryLoc_966_);
lean_dec_ref(v_s_962_);
v___x_967_ = lean_apply_1(v_ferryLoc_966_, v_f_964_);
v___x_968_ = lean_apply_1(v_islandOf_965_, v___x_967_);
v___x_969_ = lean_nat_dec_eq(v___x_968_, v_isl_961_);
lean_dec(v___x_968_);
return v___x_969_;
}
else
{
uint8_t v___x_970_; 
lean_dec_ref(v_x_963_);
lean_dec_ref(v_s_962_);
lean_dec_ref(v_G_960_);
v___x_970_ = 0;
return v___x_970_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg___boxed(lean_object* v_G_971_, lean_object* v_isl_972_, lean_object* v_s_973_, lean_object* v_x_974_){
_start:
{
uint8_t v_res_975_; lean_object* v_r_976_; 
v_res_975_ = lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg(v_G_971_, v_isl_972_, v_s_973_, v_x_974_);
lean_dec(v_isl_972_);
v_r_976_ = lean_box(v_res_975_);
return v_r_976_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl(lean_object* v_I_977_, lean_object* v_G_978_, lean_object* v_isl_979_, lean_object* v_s_980_, lean_object* v_x_981_){
_start:
{
uint8_t v___x_982_; 
v___x_982_ = lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg(v_G_978_, v_isl_979_, v_s_980_, v_x_981_);
return v___x_982_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___boxed(lean_object* v_I_983_, lean_object* v_G_984_, lean_object* v_isl_985_, lean_object* v_s_986_, lean_object* v_x_987_){
_start:
{
uint8_t v_res_988_; lean_object* v_r_989_; 
v_res_988_ = lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl(v_I_983_, v_G_984_, v_isl_985_, v_s_986_, v_x_987_);
lean_dec(v_isl_985_);
lean_dec_ref(v_I_983_);
v_r_989_ = lean_box(v_res_988_);
return v_r_989_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardOnIsl(lean_object* v_I_990_, lean_object* v_G_991_, lean_object* v_isl_992_, lean_object* v_x_993_, lean_object* v_x_994_){
_start:
{
if (lean_obj_tag(v_x_994_) == 0)
{
lean_object* v___x_995_; 
lean_dec_ref(v_x_993_);
lean_dec_ref(v_G_991_);
lean_dec_ref(v_I_990_);
v___x_995_ = lean_unsigned_to_nat(0u);
return v___x_995_;
}
else
{
lean_object* v_head_996_; lean_object* v_tail_997_; lean_object* v___y_999_; uint8_t v___x_1003_; 
v_head_996_ = lean_ctor_get(v_x_994_, 0);
lean_inc_n(v_head_996_, 2);
v_tail_997_ = lean_ctor_get(v_x_994_, 1);
lean_inc(v_tail_997_);
lean_dec_ref_known(v_x_994_, 2);
lean_inc_ref(v_x_993_);
lean_inc_ref(v_G_991_);
v___x_1003_ = lp_island__logistics__proof_IslandLogistics_isBoardOnIsl___redArg(v_G_991_, v_isl_992_, v_x_993_, v_head_996_);
if (v___x_1003_ == 0)
{
lean_object* v___x_1004_; 
v___x_1004_ = lean_unsigned_to_nat(0u);
v___y_999_ = v___x_1004_;
goto v___jp_998_;
}
else
{
lean_object* v___x_1005_; 
v___x_1005_ = lean_unsigned_to_nat(1u);
v___y_999_ = v___x_1005_;
goto v___jp_998_;
}
v___jp_998_:
{
lean_object* v___x_1000_; lean_object* v___x_1001_; lean_object* v___x_1002_; 
lean_inc_ref(v_I_990_);
v___x_1000_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_990_, v_x_993_, v_head_996_);
v___x_1001_ = lp_island__logistics__proof_IslandLogistics_boardOnIsl(v_I_990_, v_G_991_, v_isl_992_, v___x_1000_, v_tail_997_);
v___x_1002_ = lean_nat_add(v___y_999_, v___x_1001_);
lean_dec(v___x_1001_);
return v___x_1002_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_boardOnIsl___boxed(lean_object* v_I_1006_, lean_object* v_G_1007_, lean_object* v_isl_1008_, lean_object* v_x_1009_, lean_object* v_x_1010_){
_start:
{
lean_object* v_res_1011_; 
v_res_1011_ = lp_island__logistics__proof_IslandLogistics_boardOnIsl(v_I_1006_, v_G_1007_, v_isl_1008_, v_x_1009_, v_x_1010_);
lean_dec(v_isl_1008_);
return v_res_1011_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkOnIsl(lean_object* v_I_1012_, lean_object* v_G_1013_, lean_object* v_isl_1014_, lean_object* v_x_1015_, lean_object* v_x_1016_){
_start:
{
if (lean_obj_tag(v_x_1016_) == 0)
{
lean_object* v___x_1017_; 
lean_dec_ref(v_x_1015_);
lean_dec_ref(v_G_1013_);
lean_dec_ref(v_I_1012_);
v___x_1017_ = lean_unsigned_to_nat(0u);
return v___x_1017_;
}
else
{
lean_object* v_head_1018_; lean_object* v_tail_1019_; lean_object* v___y_1021_; uint8_t v___x_1025_; 
v_head_1018_ = lean_ctor_get(v_x_1016_, 0);
lean_inc_n(v_head_1018_, 2);
v_tail_1019_ = lean_ctor_get(v_x_1016_, 1);
lean_inc(v_tail_1019_);
lean_dec_ref_known(v_x_1016_, 2);
lean_inc_ref(v_x_1015_);
lean_inc_ref(v_G_1013_);
v___x_1025_ = lp_island__logistics__proof_IslandLogistics_isDisembarkOnIsl___redArg(v_G_1013_, v_isl_1014_, v_x_1015_, v_head_1018_);
if (v___x_1025_ == 0)
{
lean_object* v___x_1026_; 
v___x_1026_ = lean_unsigned_to_nat(0u);
v___y_1021_ = v___x_1026_;
goto v___jp_1020_;
}
else
{
lean_object* v___x_1027_; 
v___x_1027_ = lean_unsigned_to_nat(1u);
v___y_1021_ = v___x_1027_;
goto v___jp_1020_;
}
v___jp_1020_:
{
lean_object* v___x_1022_; lean_object* v___x_1023_; lean_object* v___x_1024_; 
lean_inc_ref(v_I_1012_);
v___x_1022_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1012_, v_x_1015_, v_head_1018_);
v___x_1023_ = lp_island__logistics__proof_IslandLogistics_disembarkOnIsl(v_I_1012_, v_G_1013_, v_isl_1014_, v___x_1022_, v_tail_1019_);
v___x_1024_ = lean_nat_add(v___y_1021_, v___x_1023_);
lean_dec(v___x_1023_);
return v___x_1024_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_disembarkOnIsl___boxed(lean_object* v_I_1028_, lean_object* v_G_1029_, lean_object* v_isl_1030_, lean_object* v_x_1031_, lean_object* v_x_1032_){
_start:
{
lean_object* v_res_1033_; 
v_res_1033_ = lp_island__logistics__proof_IslandLogistics_disembarkOnIsl(v_I_1028_, v_G_1029_, v_isl_1030_, v_x_1031_, v_x_1032_);
lean_dec(v_isl_1030_);
return v_res_1033_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl(lean_object* v_I_1034_, lean_object* v_G_1035_, lean_object* v_isl_1036_, lean_object* v_t_1037_, lean_object* v_x_1038_, lean_object* v_x_1039_){
_start:
{
if (lean_obj_tag(v_x_1039_) == 0)
{
lean_object* v___x_1040_; 
lean_dec_ref(v_x_1038_);
lean_dec_ref(v_G_1035_);
lean_dec_ref(v_I_1034_);
v___x_1040_ = lean_unsigned_to_nat(0u);
return v___x_1040_;
}
else
{
lean_object* v_head_1041_; lean_object* v_tail_1042_; lean_object* v___y_1044_; 
v_head_1041_ = lean_ctor_get(v_x_1039_, 0);
lean_inc(v_head_1041_);
v_tail_1042_ = lean_ctor_get(v_x_1039_, 1);
lean_inc(v_tail_1042_);
lean_dec_ref_known(v_x_1039_, 2);
if (lean_obj_tag(v_head_1041_) == 3)
{
lean_object* v_t_1048_; lean_object* v_f_1049_; uint8_t v___x_1050_; 
v_t_1048_ = lean_ctor_get(v_head_1041_, 0);
v_f_1049_ = lean_ctor_get(v_head_1041_, 1);
v___x_1050_ = lean_nat_dec_eq(v_t_1048_, v_t_1037_);
if (v___x_1050_ == 0)
{
lean_object* v___x_1051_; 
v___x_1051_ = lean_unsigned_to_nat(0u);
v___y_1044_ = v___x_1051_;
goto v___jp_1043_;
}
else
{
lean_object* v_islandOf_1052_; lean_object* v_ferryLoc_1053_; lean_object* v___x_1054_; lean_object* v___x_1055_; uint8_t v___x_1056_; 
v_islandOf_1052_ = lean_ctor_get(v_G_1035_, 1);
v_ferryLoc_1053_ = lean_ctor_get(v_x_1038_, 1);
lean_inc_ref(v_ferryLoc_1053_);
lean_inc(v_f_1049_);
v___x_1054_ = lean_apply_1(v_ferryLoc_1053_, v_f_1049_);
lean_inc_ref(v_islandOf_1052_);
v___x_1055_ = lean_apply_1(v_islandOf_1052_, v___x_1054_);
v___x_1056_ = lean_nat_dec_eq(v___x_1055_, v_isl_1036_);
lean_dec(v___x_1055_);
if (v___x_1056_ == 0)
{
lean_object* v___x_1057_; 
v___x_1057_ = lean_unsigned_to_nat(0u);
v___y_1044_ = v___x_1057_;
goto v___jp_1043_;
}
else
{
lean_object* v___x_1058_; 
v___x_1058_ = lean_unsigned_to_nat(1u);
v___y_1044_ = v___x_1058_;
goto v___jp_1043_;
}
}
}
else
{
lean_object* v___x_1059_; 
v___x_1059_ = lean_unsigned_to_nat(0u);
v___y_1044_ = v___x_1059_;
goto v___jp_1043_;
}
v___jp_1043_:
{
lean_object* v___x_1045_; lean_object* v___x_1046_; lean_object* v___x_1047_; 
lean_inc_ref(v_I_1034_);
v___x_1045_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1034_, v_x_1038_, v_head_1041_);
v___x_1046_ = lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl(v_I_1034_, v_G_1035_, v_isl_1036_, v_t_1037_, v___x_1045_, v_tail_1042_);
v___x_1047_ = lean_nat_add(v___y_1044_, v___x_1046_);
lean_dec(v___x_1046_);
return v___x_1047_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl___boxed(lean_object* v_I_1060_, lean_object* v_G_1061_, lean_object* v_isl_1062_, lean_object* v_t_1063_, lean_object* v_x_1064_, lean_object* v_x_1065_){
_start:
{
lean_object* v_res_1066_; 
v_res_1066_ = lp_island__logistics__proof_IslandLogistics_truckBoardOnIsl(v_I_1060_, v_G_1061_, v_isl_1062_, v_t_1063_, v_x_1064_, v_x_1065_);
lean_dec(v_t_1063_);
lean_dec(v_isl_1062_);
return v_res_1066_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl(lean_object* v_I_1067_, lean_object* v_G_1068_, lean_object* v_isl_1069_, lean_object* v_t_1070_, lean_object* v_x_1071_, lean_object* v_x_1072_){
_start:
{
if (lean_obj_tag(v_x_1072_) == 0)
{
lean_object* v___x_1073_; 
lean_dec_ref(v_x_1071_);
lean_dec_ref(v_G_1068_);
lean_dec_ref(v_I_1067_);
v___x_1073_ = lean_unsigned_to_nat(0u);
return v___x_1073_;
}
else
{
lean_object* v_head_1074_; lean_object* v_tail_1075_; lean_object* v___y_1077_; 
v_head_1074_ = lean_ctor_get(v_x_1072_, 0);
lean_inc(v_head_1074_);
v_tail_1075_ = lean_ctor_get(v_x_1072_, 1);
lean_inc(v_tail_1075_);
lean_dec_ref_known(v_x_1072_, 2);
if (lean_obj_tag(v_head_1074_) == 4)
{
lean_object* v_t_1081_; lean_object* v_f_1082_; uint8_t v___x_1083_; 
v_t_1081_ = lean_ctor_get(v_head_1074_, 0);
v_f_1082_ = lean_ctor_get(v_head_1074_, 1);
v___x_1083_ = lean_nat_dec_eq(v_t_1081_, v_t_1070_);
if (v___x_1083_ == 0)
{
lean_object* v___x_1084_; 
v___x_1084_ = lean_unsigned_to_nat(0u);
v___y_1077_ = v___x_1084_;
goto v___jp_1076_;
}
else
{
lean_object* v_islandOf_1085_; lean_object* v_ferryLoc_1086_; lean_object* v___x_1087_; lean_object* v___x_1088_; uint8_t v___x_1089_; 
v_islandOf_1085_ = lean_ctor_get(v_G_1068_, 1);
v_ferryLoc_1086_ = lean_ctor_get(v_x_1071_, 1);
lean_inc_ref(v_ferryLoc_1086_);
lean_inc(v_f_1082_);
v___x_1087_ = lean_apply_1(v_ferryLoc_1086_, v_f_1082_);
lean_inc_ref(v_islandOf_1085_);
v___x_1088_ = lean_apply_1(v_islandOf_1085_, v___x_1087_);
v___x_1089_ = lean_nat_dec_eq(v___x_1088_, v_isl_1069_);
lean_dec(v___x_1088_);
if (v___x_1089_ == 0)
{
lean_object* v___x_1090_; 
v___x_1090_ = lean_unsigned_to_nat(0u);
v___y_1077_ = v___x_1090_;
goto v___jp_1076_;
}
else
{
lean_object* v___x_1091_; 
v___x_1091_ = lean_unsigned_to_nat(1u);
v___y_1077_ = v___x_1091_;
goto v___jp_1076_;
}
}
}
else
{
lean_object* v___x_1092_; 
v___x_1092_ = lean_unsigned_to_nat(0u);
v___y_1077_ = v___x_1092_;
goto v___jp_1076_;
}
v___jp_1076_:
{
lean_object* v___x_1078_; lean_object* v___x_1079_; lean_object* v___x_1080_; 
lean_inc_ref(v_I_1067_);
v___x_1078_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1067_, v_x_1071_, v_head_1074_);
v___x_1079_ = lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl(v_I_1067_, v_G_1068_, v_isl_1069_, v_t_1070_, v___x_1078_, v_tail_1075_);
v___x_1080_ = lean_nat_add(v___y_1077_, v___x_1079_);
lean_dec(v___x_1079_);
return v___x_1080_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl___boxed(lean_object* v_I_1093_, lean_object* v_G_1094_, lean_object* v_isl_1095_, lean_object* v_t_1096_, lean_object* v_x_1097_, lean_object* v_x_1098_){
_start:
{
lean_object* v_res_1099_; 
v_res_1099_ = lp_island__logistics__proof_IslandLogistics_truckDisembarkOnIsl(v_I_1093_, v_G_1094_, v_isl_1095_, v_t_1096_, v_x_1097_, v_x_1098_);
lean_dec(v_t_1096_);
lean_dec(v_isl_1095_);
return v_res_1099_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_ferryMinSails_spec__0(lean_object* v_I_1100_, lean_object* v_f_1101_, lean_object* v_a_1102_, lean_object* v_a_1103_){
_start:
{
if (lean_obj_tag(v_a_1102_) == 0)
{
lean_object* v___x_1104_; 
lean_dec(v_f_1101_);
lean_dec_ref(v_I_1100_);
v___x_1104_ = l_List_reverse___redArg(v_a_1103_);
return v___x_1104_;
}
else
{
lean_object* v_head_1105_; lean_object* v_tail_1106_; lean_object* v___x_1108_; uint8_t v_isShared_1109_; uint8_t v_isSharedCheck_1118_; 
v_head_1105_ = lean_ctor_get(v_a_1102_, 0);
v_tail_1106_ = lean_ctor_get(v_a_1102_, 1);
v_isSharedCheck_1118_ = !lean_is_exclusive(v_a_1102_);
if (v_isSharedCheck_1118_ == 0)
{
v___x_1108_ = v_a_1102_;
v_isShared_1109_ = v_isSharedCheck_1118_;
goto v_resetjp_1107_;
}
else
{
lean_inc(v_tail_1106_);
lean_inc(v_head_1105_);
lean_dec(v_a_1102_);
v___x_1108_ = lean_box(0);
v_isShared_1109_ = v_isSharedCheck_1118_;
goto v_resetjp_1107_;
}
v_resetjp_1107_:
{
lean_object* v_ferryServed_1110_; lean_object* v___x_1111_; uint8_t v___x_1112_; 
v_ferryServed_1110_ = lean_ctor_get(v_I_1100_, 7);
lean_inc_ref(v_ferryServed_1110_);
lean_inc(v_head_1105_);
lean_inc(v_f_1101_);
v___x_1111_ = lean_apply_2(v_ferryServed_1110_, v_f_1101_, v_head_1105_);
v___x_1112_ = lean_unbox(v___x_1111_);
if (v___x_1112_ == 0)
{
lean_del_object(v___x_1108_);
lean_dec(v_head_1105_);
v_a_1102_ = v_tail_1106_;
goto _start;
}
else
{
lean_object* v___x_1115_; 
if (v_isShared_1109_ == 0)
{
lean_ctor_set(v___x_1108_, 1, v_a_1103_);
v___x_1115_ = v___x_1108_;
goto v_reusejp_1114_;
}
else
{
lean_object* v_reuseFailAlloc_1117_; 
v_reuseFailAlloc_1117_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1117_, 0, v_head_1105_);
lean_ctor_set(v_reuseFailAlloc_1117_, 1, v_a_1103_);
v___x_1115_ = v_reuseFailAlloc_1117_;
goto v_reusejp_1114_;
}
v_reusejp_1114_:
{
v_a_1102_ = v_tail_1106_;
v_a_1103_ = v___x_1115_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_ferryMinSails_spec__1(lean_object* v_G_1119_, lean_object* v_g_1120_, lean_object* v_a_1121_, lean_object* v_a_1122_){
_start:
{
if (lean_obj_tag(v_a_1121_) == 0)
{
lean_object* v___x_1123_; 
lean_dec(v_g_1120_);
lean_dec_ref(v_G_1119_);
v___x_1123_ = l_List_reverse___redArg(v_a_1122_);
return v___x_1123_;
}
else
{
lean_object* v_head_1124_; lean_object* v_tail_1125_; lean_object* v___x_1127_; uint8_t v_isShared_1128_; uint8_t v_isSharedCheck_1137_; 
v_head_1124_ = lean_ctor_get(v_a_1121_, 0);
v_tail_1125_ = lean_ctor_get(v_a_1121_, 1);
v_isSharedCheck_1137_ = !lean_is_exclusive(v_a_1121_);
if (v_isSharedCheck_1137_ == 0)
{
v___x_1127_ = v_a_1121_;
v_isShared_1128_ = v_isSharedCheck_1137_;
goto v_resetjp_1126_;
}
else
{
lean_inc(v_tail_1125_);
lean_inc(v_head_1124_);
lean_dec(v_a_1121_);
v___x_1127_ = lean_box(0);
v_isShared_1128_ = v_isSharedCheck_1137_;
goto v_resetjp_1126_;
}
v_resetjp_1126_:
{
lean_object* v_islandOf_1129_; lean_object* v_minSails_1130_; lean_object* v___x_1131_; lean_object* v___x_1132_; lean_object* v___x_1134_; 
v_islandOf_1129_ = lean_ctor_get(v_G_1119_, 1);
v_minSails_1130_ = lean_ctor_get(v_G_1119_, 2);
lean_inc_ref(v_islandOf_1129_);
v___x_1131_ = lean_apply_1(v_islandOf_1129_, v_head_1124_);
lean_inc_ref(v_minSails_1130_);
lean_inc(v_g_1120_);
v___x_1132_ = lean_apply_2(v_minSails_1130_, v___x_1131_, v_g_1120_);
if (v_isShared_1128_ == 0)
{
lean_ctor_set(v___x_1127_, 1, v_a_1122_);
lean_ctor_set(v___x_1127_, 0, v___x_1132_);
v___x_1134_ = v___x_1127_;
goto v_reusejp_1133_;
}
else
{
lean_object* v_reuseFailAlloc_1136_; 
v_reuseFailAlloc_1136_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1136_, 0, v___x_1132_);
lean_ctor_set(v_reuseFailAlloc_1136_, 1, v_a_1122_);
v___x_1134_ = v_reuseFailAlloc_1136_;
goto v_reusejp_1133_;
}
v_reusejp_1133_:
{
v_a_1121_ = v_tail_1125_;
v_a_1122_ = v___x_1134_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ferryMinSails(lean_object* v_I_1138_, lean_object* v_G_1139_, lean_object* v_f_1140_, lean_object* v_g_1141_){
_start:
{
lean_object* v_numLocs_1142_; lean_object* v___x_1143_; lean_object* v___x_1144_; lean_object* v___x_1145_; lean_object* v___x_1146_; 
v_numLocs_1142_ = lean_ctor_get(v_I_1138_, 0);
lean_inc(v_numLocs_1142_);
v___x_1143_ = l_List_finRange(v_numLocs_1142_);
v___x_1144_ = lean_box(0);
v___x_1145_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_ferryMinSails_spec__0(v_I_1138_, v_f_1140_, v___x_1143_, v___x_1144_);
v___x_1146_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_ferryMinSails_spec__1(v_G_1139_, v_g_1141_, v___x_1145_, v___x_1144_);
if (lean_obj_tag(v___x_1146_) == 0)
{
lean_object* v___x_1147_; 
v___x_1147_ = lean_unsigned_to_nat(0u);
return v___x_1147_;
}
else
{
lean_object* v_head_1148_; lean_object* v_tail_1149_; lean_object* v___x_1150_; 
v_head_1148_ = lean_ctor_get(v___x_1146_, 0);
lean_inc(v_head_1148_);
v_tail_1149_ = lean_ctor_get(v___x_1146_, 1);
lean_inc(v_tail_1149_);
lean_dec_ref_known(v___x_1146_, 2);
v___x_1150_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(v_head_1148_, v_tail_1149_);
lean_dec(v_tail_1149_);
lean_dec(v_head_1148_);
return v___x_1150_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potB(lean_object* v_I_1151_, lean_object* v_G_1152_, lean_object* v_s_1153_, lean_object* v_p_1154_){
_start:
{
lean_object* v___x_1155_; 
lean_inc(v_p_1154_);
lean_inc_ref(v_s_1153_);
v___x_1155_ = lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(v_s_1153_, v_p_1154_);
if (lean_obj_tag(v___x_1155_) == 0)
{
lean_object* v_islandOf_1156_; lean_object* v_minSails_1157_; lean_object* v_pkgGoal_1158_; lean_object* v___x_1159_; lean_object* v___x_1160_; lean_object* v___x_1161_; lean_object* v___x_1162_; lean_object* v___x_1163_; 
v_islandOf_1156_ = lean_ctor_get(v_G_1152_, 1);
lean_inc_ref_n(v_islandOf_1156_, 2);
v_minSails_1157_ = lean_ctor_get(v_G_1152_, 2);
lean_inc_ref(v_minSails_1157_);
lean_dec_ref(v_G_1152_);
v_pkgGoal_1158_ = lean_ctor_get(v_I_1151_, 10);
lean_inc_ref(v_pkgGoal_1158_);
lean_dec_ref(v_I_1151_);
lean_inc(v_p_1154_);
v___x_1159_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_1153_, v_p_1154_);
v___x_1160_ = lean_apply_1(v_islandOf_1156_, v___x_1159_);
v___x_1161_ = lean_apply_1(v_pkgGoal_1158_, v_p_1154_);
v___x_1162_ = lean_apply_1(v_islandOf_1156_, v___x_1161_);
v___x_1163_ = lean_apply_2(v_minSails_1157_, v___x_1160_, v___x_1162_);
return v___x_1163_;
}
else
{
lean_object* v_val_1164_; lean_object* v_islandOf_1165_; lean_object* v_pkgGoal_1166_; lean_object* v___x_1167_; lean_object* v___x_1168_; lean_object* v___x_1169_; 
lean_dec_ref(v_s_1153_);
v_val_1164_ = lean_ctor_get(v___x_1155_, 0);
lean_inc(v_val_1164_);
lean_dec_ref_known(v___x_1155_, 1);
v_islandOf_1165_ = lean_ctor_get(v_G_1152_, 1);
v_pkgGoal_1166_ = lean_ctor_get(v_I_1151_, 10);
lean_inc_ref(v_pkgGoal_1166_);
v___x_1167_ = lean_apply_1(v_pkgGoal_1166_, v_p_1154_);
lean_inc_ref(v_islandOf_1165_);
v___x_1168_ = lean_apply_1(v_islandOf_1165_, v___x_1167_);
v___x_1169_ = lp_island__logistics__proof_IslandLogistics_ferryMinSails(v_I_1151_, v_G_1152_, v_val_1164_, v___x_1168_);
return v___x_1169_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_potD(lean_object* v_I_1170_, lean_object* v_G_1171_, lean_object* v_s_1172_, lean_object* v_p_1173_){
_start:
{
lean_object* v___x_1174_; 
lean_inc(v_p_1173_);
lean_inc_ref(v_s_1172_);
v___x_1174_ = lp_island__logistics__proof_IslandLogistics_State_pkgOnFerry___redArg(v_s_1172_, v_p_1173_);
if (lean_obj_tag(v___x_1174_) == 0)
{
lean_object* v_islandOf_1175_; lean_object* v_minSails_1176_; lean_object* v_pkgGoal_1177_; lean_object* v___x_1178_; lean_object* v___x_1179_; lean_object* v___x_1180_; lean_object* v___x_1181_; lean_object* v___x_1182_; 
v_islandOf_1175_ = lean_ctor_get(v_G_1171_, 1);
lean_inc_ref_n(v_islandOf_1175_, 2);
v_minSails_1176_ = lean_ctor_get(v_G_1171_, 2);
lean_inc_ref(v_minSails_1176_);
lean_dec_ref(v_G_1171_);
v_pkgGoal_1177_ = lean_ctor_get(v_I_1170_, 10);
lean_inc_ref(v_pkgGoal_1177_);
lean_dec_ref(v_I_1170_);
lean_inc(v_p_1173_);
v___x_1178_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_1172_, v_p_1173_);
v___x_1179_ = lean_apply_1(v_islandOf_1175_, v___x_1178_);
v___x_1180_ = lean_apply_1(v_pkgGoal_1177_, v_p_1173_);
v___x_1181_ = lean_apply_1(v_islandOf_1175_, v___x_1180_);
v___x_1182_ = lean_apply_2(v_minSails_1176_, v___x_1179_, v___x_1181_);
return v___x_1182_;
}
else
{
lean_object* v_val_1183_; lean_object* v_islandOf_1184_; lean_object* v_pkgGoal_1185_; lean_object* v___x_1186_; lean_object* v___x_1187_; lean_object* v___x_1188_; lean_object* v___x_1189_; lean_object* v___x_1190_; 
lean_dec_ref(v_s_1172_);
v_val_1183_ = lean_ctor_get(v___x_1174_, 0);
lean_inc(v_val_1183_);
lean_dec_ref_known(v___x_1174_, 1);
v_islandOf_1184_ = lean_ctor_get(v_G_1171_, 1);
v_pkgGoal_1185_ = lean_ctor_get(v_I_1170_, 10);
v___x_1186_ = lean_unsigned_to_nat(1u);
lean_inc_ref(v_pkgGoal_1185_);
v___x_1187_ = lean_apply_1(v_pkgGoal_1185_, v_p_1173_);
lean_inc_ref(v_islandOf_1184_);
v___x_1188_ = lean_apply_1(v_islandOf_1184_, v___x_1187_);
v___x_1189_ = lp_island__logistics__proof_IslandLogistics_ferryMinSails(v_I_1170_, v_G_1171_, v_val_1183_, v___x_1188_);
v___x_1190_ = lean_nat_add(v___x_1186_, v___x_1189_);
lean_dec(v___x_1189_);
return v___x_1190_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter___redArg(lean_object* v_x_1191_, lean_object* v_h__1_1192_, lean_object* v_h__2_1193_){
_start:
{
if (lean_obj_tag(v_x_1191_) == 0)
{
lean_object* v___x_1194_; lean_object* v___x_1195_; 
lean_dec(v_h__2_1193_);
v___x_1194_ = lean_box(0);
v___x_1195_ = lean_apply_1(v_h__1_1192_, v___x_1194_);
return v___x_1195_;
}
else
{
lean_object* v_val_1196_; lean_object* v___x_1197_; 
lean_dec(v_h__1_1192_);
v_val_1196_ = lean_ctor_get(v_x_1191_, 0);
lean_inc(v_val_1196_);
lean_dec_ref_known(v_x_1191_, 1);
v___x_1197_ = lean_apply_1(v_h__2_1193_, v_val_1196_);
return v___x_1197_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter(lean_object* v_I_1198_, lean_object* v_motive_1199_, lean_object* v_x_1200_, lean_object* v_h__1_1201_, lean_object* v_h__2_1202_){
_start:
{
if (lean_obj_tag(v_x_1200_) == 0)
{
lean_object* v___x_1203_; lean_object* v___x_1204_; 
lean_dec(v_h__2_1202_);
v___x_1203_ = lean_box(0);
v___x_1204_ = lean_apply_1(v_h__1_1201_, v___x_1203_);
return v___x_1204_;
}
else
{
lean_object* v_val_1205_; lean_object* v___x_1206_; 
lean_dec(v_h__1_1201_);
v_val_1205_ = lean_ctor_get(v_x_1200_, 0);
lean_inc(v_val_1205_);
lean_dec_ref_known(v_x_1200_, 1);
v___x_1206_ = lean_apply_1(v_h__2_1202_, v_val_1205_);
return v___x_1206_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter___boxed(lean_object* v_I_1207_, lean_object* v_motive_1208_, lean_object* v_x_1209_, lean_object* v_h__1_1210_, lean_object* v_h__2_1211_){
_start:
{
lean_object* v_res_1212_; 
v_res_1212_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_potB_match__1_splitter(v_I_1207_, v_motive_1208_, v_x_1209_, v_h__1_1210_, v_h__2_1211_);
lean_dec_ref(v_I_1207_);
return v_res_1212_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___redArg(lean_object* v_x_1213_, lean_object* v_h__1_1214_, lean_object* v_h__2_1215_){
_start:
{
if (lean_obj_tag(v_x_1213_) == 0)
{
lean_object* v_l_1216_; lean_object* v___x_1217_; 
lean_dec(v_h__2_1215_);
v_l_1216_ = lean_ctor_get(v_x_1213_, 0);
lean_inc(v_l_1216_);
lean_dec_ref_known(v_x_1213_, 1);
v___x_1217_ = lean_apply_1(v_h__1_1214_, v_l_1216_);
return v___x_1217_;
}
else
{
lean_object* v_t_1218_; lean_object* v___x_1219_; 
lean_dec(v_h__1_1214_);
v_t_1218_ = lean_ctor_get(v_x_1213_, 0);
lean_inc(v_t_1218_);
lean_dec_ref_known(v_x_1213_, 1);
v___x_1219_ = lean_apply_1(v_h__2_1215_, v_t_1218_);
return v___x_1219_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(lean_object* v_I_1220_, lean_object* v_motive_1221_, lean_object* v_x_1222_, lean_object* v_h__1_1223_, lean_object* v_h__2_1224_){
_start:
{
if (lean_obj_tag(v_x_1222_) == 0)
{
lean_object* v_l_1225_; lean_object* v___x_1226_; 
lean_dec(v_h__2_1224_);
v_l_1225_ = lean_ctor_get(v_x_1222_, 0);
lean_inc(v_l_1225_);
lean_dec_ref_known(v_x_1222_, 1);
v___x_1226_ = lean_apply_1(v_h__1_1223_, v_l_1225_);
return v___x_1226_;
}
else
{
lean_object* v_t_1227_; lean_object* v___x_1228_; 
lean_dec(v_h__1_1223_);
v_t_1227_ = lean_ctor_get(v_x_1222_, 0);
lean_inc(v_t_1227_);
lean_dec_ref_known(v_x_1222_, 1);
v___x_1228_ = lean_apply_1(v_h__2_1224_, v_t_1227_);
return v___x_1228_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___boxed(lean_object* v_I_1229_, lean_object* v_motive_1230_, lean_object* v_x_1231_, lean_object* v_h__1_1232_, lean_object* v_h__2_1233_){
_start:
{
lean_object* v_res_1234_; 
v_res_1234_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(v_I_1229_, v_motive_1230_, v_x_1231_, v_h__1_1232_, v_h__2_1233_);
lean_dec_ref(v_I_1229_);
return v_res_1234_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isInterSail___redArg(lean_object* v_G_1235_, lean_object* v_x_1236_){
_start:
{
if (lean_obj_tag(v_x_1236_) == 5)
{
lean_object* v_u_1237_; lean_object* v_v_1238_; lean_object* v_islandOf_1239_; lean_object* v___x_1240_; lean_object* v___x_1241_; uint8_t v___x_1242_; 
v_u_1237_ = lean_ctor_get(v_x_1236_, 1);
lean_inc(v_u_1237_);
v_v_1238_ = lean_ctor_get(v_x_1236_, 2);
lean_inc(v_v_1238_);
lean_dec_ref_known(v_x_1236_, 3);
v_islandOf_1239_ = lean_ctor_get(v_G_1235_, 1);
lean_inc_ref_n(v_islandOf_1239_, 2);
lean_dec_ref(v_G_1235_);
v___x_1240_ = lean_apply_1(v_islandOf_1239_, v_u_1237_);
v___x_1241_ = lean_apply_1(v_islandOf_1239_, v_v_1238_);
v___x_1242_ = lean_nat_dec_eq(v___x_1240_, v___x_1241_);
lean_dec(v___x_1241_);
lean_dec(v___x_1240_);
if (v___x_1242_ == 0)
{
uint8_t v___x_1243_; 
v___x_1243_ = 1;
return v___x_1243_;
}
else
{
uint8_t v___x_1244_; 
v___x_1244_ = 0;
return v___x_1244_;
}
}
else
{
uint8_t v___x_1245_; 
lean_dec_ref(v_x_1236_);
lean_dec_ref(v_G_1235_);
v___x_1245_ = 0;
return v___x_1245_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isInterSail___redArg___boxed(lean_object* v_G_1246_, lean_object* v_x_1247_){
_start:
{
uint8_t v_res_1248_; lean_object* v_r_1249_; 
v_res_1248_ = lp_island__logistics__proof_IslandLogistics_isInterSail___redArg(v_G_1246_, v_x_1247_);
v_r_1249_ = lean_box(v_res_1248_);
return v_r_1249_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isInterSail(lean_object* v_I_1250_, lean_object* v_G_1251_, lean_object* v_x_1252_){
_start:
{
uint8_t v___x_1253_; 
v___x_1253_ = lp_island__logistics__proof_IslandLogistics_isInterSail___redArg(v_G_1251_, v_x_1252_);
return v___x_1253_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isInterSail___boxed(lean_object* v_I_1254_, lean_object* v_G_1255_, lean_object* v_x_1256_){
_start:
{
uint8_t v_res_1257_; lean_object* v_r_1258_; 
v_res_1257_ = lp_island__logistics__proof_IslandLogistics_isInterSail(v_I_1254_, v_G_1255_, v_x_1256_);
lean_dec_ref(v_I_1254_);
v_r_1258_ = lean_box(v_res_1257_);
return v_r_1258_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedInterSailCount(lean_object* v_I_1259_, lean_object* v_G_1260_, lean_object* v_x_1261_, lean_object* v_x_1262_){
_start:
{
if (lean_obj_tag(v_x_1262_) == 0)
{
lean_object* v___x_1263_; 
lean_dec_ref(v_x_1261_);
lean_dec_ref(v_G_1260_);
lean_dec_ref(v_I_1259_);
v___x_1263_ = lean_unsigned_to_nat(0u);
return v___x_1263_;
}
else
{
lean_object* v_head_1264_; lean_object* v_tail_1265_; lean_object* v___y_1267_; 
v_head_1264_ = lean_ctor_get(v_x_1262_, 0);
lean_inc(v_head_1264_);
v_tail_1265_ = lean_ctor_get(v_x_1262_, 1);
lean_inc(v_tail_1265_);
lean_dec_ref_known(v_x_1262_, 2);
if (lean_obj_tag(v_head_1264_) == 5)
{
lean_object* v_f_1271_; lean_object* v_u_1272_; lean_object* v_v_1273_; lean_object* v_islandOf_1274_; lean_object* v___x_1275_; lean_object* v___x_1276_; uint8_t v___x_1277_; 
v_f_1271_ = lean_ctor_get(v_head_1264_, 0);
v_u_1272_ = lean_ctor_get(v_head_1264_, 1);
v_v_1273_ = lean_ctor_get(v_head_1264_, 2);
v_islandOf_1274_ = lean_ctor_get(v_G_1260_, 1);
lean_inc_ref_n(v_islandOf_1274_, 2);
lean_inc(v_u_1272_);
v___x_1275_ = lean_apply_1(v_islandOf_1274_, v_u_1272_);
lean_inc(v_v_1273_);
v___x_1276_ = lean_apply_1(v_islandOf_1274_, v_v_1273_);
v___x_1277_ = lean_nat_dec_eq(v___x_1275_, v___x_1276_);
lean_dec(v___x_1276_);
lean_dec(v___x_1275_);
if (v___x_1277_ == 0)
{
lean_object* v___x_1278_; lean_object* v___x_1279_; uint8_t v___x_1280_; 
v___x_1278_ = lean_unsigned_to_nat(0u);
lean_inc(v_f_1271_);
lean_inc_ref(v_x_1261_);
lean_inc_ref(v_I_1259_);
v___x_1279_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_1259_, v_x_1261_, v_f_1271_);
v___x_1280_ = lean_nat_dec_lt(v___x_1278_, v___x_1279_);
lean_dec(v___x_1279_);
if (v___x_1280_ == 0)
{
v___y_1267_ = v___x_1278_;
goto v___jp_1266_;
}
else
{
lean_object* v___x_1281_; 
v___x_1281_ = lean_unsigned_to_nat(1u);
v___y_1267_ = v___x_1281_;
goto v___jp_1266_;
}
}
else
{
lean_object* v___x_1282_; 
v___x_1282_ = lean_unsigned_to_nat(0u);
v___y_1267_ = v___x_1282_;
goto v___jp_1266_;
}
}
else
{
lean_object* v___x_1283_; 
v___x_1283_ = lean_unsigned_to_nat(0u);
v___y_1267_ = v___x_1283_;
goto v___jp_1266_;
}
v___jp_1266_:
{
lean_object* v___x_1268_; lean_object* v___x_1269_; lean_object* v___x_1270_; 
lean_inc_ref(v_I_1259_);
v___x_1268_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1259_, v_x_1261_, v_head_1264_);
v___x_1269_ = lp_island__logistics__proof_IslandLogistics_loadedInterSailCount(v_I_1259_, v_G_1260_, v___x_1268_, v_tail_1265_);
v___x_1270_ = lean_nat_add(v___y_1267_, v___x_1269_);
lean_dec(v___x_1269_);
return v___x_1270_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepLoadedInterSail(lean_object* v_I_1284_, lean_object* v_G_1285_, lean_object* v_s_1286_, lean_object* v_x_1287_){
_start:
{
if (lean_obj_tag(v_x_1287_) == 5)
{
lean_object* v_f_1288_; lean_object* v_u_1289_; lean_object* v_v_1290_; lean_object* v_islandOf_1291_; lean_object* v___x_1292_; lean_object* v___x_1293_; uint8_t v___x_1294_; 
v_f_1288_ = lean_ctor_get(v_x_1287_, 0);
lean_inc(v_f_1288_);
v_u_1289_ = lean_ctor_get(v_x_1287_, 1);
lean_inc(v_u_1289_);
v_v_1290_ = lean_ctor_get(v_x_1287_, 2);
lean_inc(v_v_1290_);
lean_dec_ref_known(v_x_1287_, 3);
v_islandOf_1291_ = lean_ctor_get(v_G_1285_, 1);
lean_inc_ref_n(v_islandOf_1291_, 2);
lean_dec_ref(v_G_1285_);
v___x_1292_ = lean_apply_1(v_islandOf_1291_, v_u_1289_);
v___x_1293_ = lean_apply_1(v_islandOf_1291_, v_v_1290_);
v___x_1294_ = lean_nat_dec_eq(v___x_1292_, v___x_1293_);
lean_dec(v___x_1293_);
lean_dec(v___x_1292_);
if (v___x_1294_ == 0)
{
lean_object* v___x_1295_; lean_object* v___x_1296_; uint8_t v___x_1297_; 
v___x_1295_ = lean_unsigned_to_nat(0u);
v___x_1296_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_1284_, v_s_1286_, v_f_1288_);
v___x_1297_ = lean_nat_dec_lt(v___x_1295_, v___x_1296_);
lean_dec(v___x_1296_);
if (v___x_1297_ == 0)
{
return v___x_1295_;
}
else
{
lean_object* v___x_1298_; 
v___x_1298_ = lean_unsigned_to_nat(1u);
return v___x_1298_;
}
}
else
{
lean_object* v___x_1299_; 
lean_dec(v_f_1288_);
lean_dec_ref(v_s_1286_);
lean_dec_ref(v_I_1284_);
v___x_1299_ = lean_unsigned_to_nat(0u);
return v___x_1299_;
}
}
else
{
lean_object* v___x_1300_; 
lean_dec_ref(v_x_1287_);
lean_dec_ref(v_s_1286_);
lean_dec_ref(v_G_1285_);
lean_dec_ref(v_I_1284_);
v___x_1300_ = lean_unsigned_to_nat(0u);
return v___x_1300_;
}
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg(lean_object* v_G_1301_, lean_object* v_isl_1302_, lean_object* v_f_1303_, lean_object* v_x_1304_){
_start:
{
if (lean_obj_tag(v_x_1304_) == 5)
{
lean_object* v_f_1305_; lean_object* v_u_1306_; lean_object* v_v_1307_; uint8_t v___x_1308_; 
v_f_1305_ = lean_ctor_get(v_x_1304_, 0);
lean_inc(v_f_1305_);
v_u_1306_ = lean_ctor_get(v_x_1304_, 1);
lean_inc(v_u_1306_);
v_v_1307_ = lean_ctor_get(v_x_1304_, 2);
lean_inc(v_v_1307_);
lean_dec_ref_known(v_x_1304_, 3);
v___x_1308_ = lean_nat_dec_eq(v_f_1305_, v_f_1303_);
lean_dec(v_f_1305_);
if (v___x_1308_ == 0)
{
lean_dec(v_v_1307_);
lean_dec(v_u_1306_);
lean_dec_ref(v_G_1301_);
return v___x_1308_;
}
else
{
lean_object* v_islandOf_1309_; lean_object* v___x_1310_; uint8_t v___x_1311_; 
v_islandOf_1309_ = lean_ctor_get(v_G_1301_, 1);
lean_inc_ref_n(v_islandOf_1309_, 2);
lean_dec_ref(v_G_1301_);
v___x_1310_ = lean_apply_1(v_islandOf_1309_, v_u_1306_);
v___x_1311_ = lean_nat_dec_eq(v___x_1310_, v_isl_1302_);
lean_dec(v___x_1310_);
if (v___x_1311_ == 0)
{
lean_dec_ref(v_islandOf_1309_);
lean_dec(v_v_1307_);
return v___x_1311_;
}
else
{
lean_object* v___x_1312_; uint8_t v___x_1313_; 
v___x_1312_ = lean_apply_1(v_islandOf_1309_, v_v_1307_);
v___x_1313_ = lean_nat_dec_eq(v___x_1312_, v_isl_1302_);
lean_dec(v___x_1312_);
if (v___x_1313_ == 0)
{
return v___x_1311_;
}
else
{
uint8_t v___x_1314_; 
v___x_1314_ = 0;
return v___x_1314_;
}
}
}
}
else
{
uint8_t v___x_1315_; 
lean_dec_ref(v_x_1304_);
lean_dec_ref(v_G_1301_);
v___x_1315_ = 0;
return v___x_1315_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg___boxed(lean_object* v_G_1316_, lean_object* v_isl_1317_, lean_object* v_f_1318_, lean_object* v_x_1319_){
_start:
{
uint8_t v_res_1320_; lean_object* v_r_1321_; 
v_res_1320_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg(v_G_1316_, v_isl_1317_, v_f_1318_, v_x_1319_);
lean_dec(v_f_1318_);
lean_dec(v_isl_1317_);
v_r_1321_ = lean_box(v_res_1320_);
return v_r_1321_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut(lean_object* v_I_1322_, lean_object* v_G_1323_, lean_object* v_isl_1324_, lean_object* v_f_1325_, lean_object* v_x_1326_){
_start:
{
uint8_t v___x_1327_; 
v___x_1327_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___redArg(v_G_1323_, v_isl_1324_, v_f_1325_, v_x_1326_);
return v___x_1327_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut___boxed(lean_object* v_I_1328_, lean_object* v_G_1329_, lean_object* v_isl_1330_, lean_object* v_f_1331_, lean_object* v_x_1332_){
_start:
{
uint8_t v_res_1333_; lean_object* v_r_1334_; 
v_res_1333_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailOut(v_I_1328_, v_G_1329_, v_isl_1330_, v_f_1331_, v_x_1332_);
lean_dec(v_f_1331_);
lean_dec(v_isl_1330_);
lean_dec_ref(v_I_1328_);
v_r_1334_ = lean_box(v_res_1333_);
return v_r_1334_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg(lean_object* v_G_1335_, lean_object* v_isl_1336_, lean_object* v_f_1337_, lean_object* v_x_1338_){
_start:
{
if (lean_obj_tag(v_x_1338_) == 5)
{
lean_object* v_f_1339_; lean_object* v_u_1340_; lean_object* v_v_1341_; uint8_t v___x_1342_; 
v_f_1339_ = lean_ctor_get(v_x_1338_, 0);
lean_inc(v_f_1339_);
v_u_1340_ = lean_ctor_get(v_x_1338_, 1);
lean_inc(v_u_1340_);
v_v_1341_ = lean_ctor_get(v_x_1338_, 2);
lean_inc(v_v_1341_);
lean_dec_ref_known(v_x_1338_, 3);
v___x_1342_ = lean_nat_dec_eq(v_f_1339_, v_f_1337_);
lean_dec(v_f_1339_);
if (v___x_1342_ == 0)
{
lean_dec(v_v_1341_);
lean_dec(v_u_1340_);
lean_dec_ref(v_G_1335_);
return v___x_1342_;
}
else
{
lean_object* v_islandOf_1343_; lean_object* v___x_1344_; uint8_t v___x_1345_; 
v_islandOf_1343_ = lean_ctor_get(v_G_1335_, 1);
lean_inc_ref_n(v_islandOf_1343_, 2);
lean_dec_ref(v_G_1335_);
v___x_1344_ = lean_apply_1(v_islandOf_1343_, v_u_1340_);
v___x_1345_ = lean_nat_dec_eq(v___x_1344_, v_isl_1336_);
lean_dec(v___x_1344_);
if (v___x_1345_ == 0)
{
lean_object* v___x_1346_; uint8_t v___x_1347_; 
v___x_1346_ = lean_apply_1(v_islandOf_1343_, v_v_1341_);
v___x_1347_ = lean_nat_dec_eq(v___x_1346_, v_isl_1336_);
lean_dec(v___x_1346_);
return v___x_1347_;
}
else
{
uint8_t v___x_1348_; 
lean_dec_ref(v_islandOf_1343_);
lean_dec(v_v_1341_);
v___x_1348_ = 0;
return v___x_1348_;
}
}
}
else
{
uint8_t v___x_1349_; 
lean_dec_ref(v_x_1338_);
lean_dec_ref(v_G_1335_);
v___x_1349_ = 0;
return v___x_1349_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg___boxed(lean_object* v_G_1350_, lean_object* v_isl_1351_, lean_object* v_f_1352_, lean_object* v_x_1353_){
_start:
{
uint8_t v_res_1354_; lean_object* v_r_1355_; 
v_res_1354_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg(v_G_1350_, v_isl_1351_, v_f_1352_, v_x_1353_);
lean_dec(v_f_1352_);
lean_dec(v_isl_1351_);
v_r_1355_ = lean_box(v_res_1354_);
return v_r_1355_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn(lean_object* v_I_1356_, lean_object* v_G_1357_, lean_object* v_isl_1358_, lean_object* v_f_1359_, lean_object* v_x_1360_){
_start:
{
uint8_t v___x_1361_; 
v___x_1361_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___redArg(v_G_1357_, v_isl_1358_, v_f_1359_, v_x_1360_);
return v___x_1361_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn___boxed(lean_object* v_I_1362_, lean_object* v_G_1363_, lean_object* v_isl_1364_, lean_object* v_f_1365_, lean_object* v_x_1366_){
_start:
{
uint8_t v_res_1367_; lean_object* v_r_1368_; 
v_res_1367_ = lp_island__logistics__proof_IslandLogistics_isIslFerrySailIn(v_I_1362_, v_G_1363_, v_isl_1364_, v_f_1365_, v_x_1366_);
lean_dec(v_f_1365_);
lean_dec(v_isl_1364_);
lean_dec_ref(v_I_1362_);
v_r_1368_ = lean_box(v_res_1367_);
return v_r_1368_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg(lean_object* v_G_1369_, lean_object* v_isl_1370_, lean_object* v_x_1371_){
_start:
{
if (lean_obj_tag(v_x_1371_) == 5)
{
lean_object* v_u_1372_; lean_object* v_v_1373_; lean_object* v_islandOf_1374_; lean_object* v___x_1375_; uint8_t v___x_1376_; 
v_u_1372_ = lean_ctor_get(v_x_1371_, 1);
lean_inc(v_u_1372_);
v_v_1373_ = lean_ctor_get(v_x_1371_, 2);
lean_inc(v_v_1373_);
lean_dec_ref_known(v_x_1371_, 3);
v_islandOf_1374_ = lean_ctor_get(v_G_1369_, 1);
lean_inc_ref_n(v_islandOf_1374_, 2);
lean_dec_ref(v_G_1369_);
v___x_1375_ = lean_apply_1(v_islandOf_1374_, v_u_1372_);
v___x_1376_ = lean_nat_dec_eq(v___x_1375_, v_isl_1370_);
lean_dec(v___x_1375_);
if (v___x_1376_ == 0)
{
lean_dec_ref(v_islandOf_1374_);
lean_dec(v_v_1373_);
return v___x_1376_;
}
else
{
lean_object* v___x_1377_; uint8_t v___x_1378_; 
v___x_1377_ = lean_apply_1(v_islandOf_1374_, v_v_1373_);
v___x_1378_ = lean_nat_dec_eq(v___x_1377_, v_isl_1370_);
lean_dec(v___x_1377_);
if (v___x_1378_ == 0)
{
return v___x_1376_;
}
else
{
uint8_t v___x_1379_; 
v___x_1379_ = 0;
return v___x_1379_;
}
}
}
else
{
uint8_t v___x_1380_; 
lean_dec_ref(v_x_1371_);
lean_dec_ref(v_G_1369_);
v___x_1380_ = 0;
return v___x_1380_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg___boxed(lean_object* v_G_1381_, lean_object* v_isl_1382_, lean_object* v_x_1383_){
_start:
{
uint8_t v_res_1384_; lean_object* v_r_1385_; 
v_res_1384_ = lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg(v_G_1381_, v_isl_1382_, v_x_1383_);
lean_dec(v_isl_1382_);
v_r_1385_ = lean_box(v_res_1384_);
return v_r_1385_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailOut(lean_object* v_I_1386_, lean_object* v_G_1387_, lean_object* v_isl_1388_, lean_object* v_x_1389_){
_start:
{
uint8_t v___x_1390_; 
v___x_1390_ = lp_island__logistics__proof_IslandLogistics_isIslSailOut___redArg(v_G_1387_, v_isl_1388_, v_x_1389_);
return v___x_1390_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailOut___boxed(lean_object* v_I_1391_, lean_object* v_G_1392_, lean_object* v_isl_1393_, lean_object* v_x_1394_){
_start:
{
uint8_t v_res_1395_; lean_object* v_r_1396_; 
v_res_1395_ = lp_island__logistics__proof_IslandLogistics_isIslSailOut(v_I_1391_, v_G_1392_, v_isl_1393_, v_x_1394_);
lean_dec(v_isl_1393_);
lean_dec_ref(v_I_1391_);
v_r_1396_ = lean_box(v_res_1395_);
return v_r_1396_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg(lean_object* v_G_1397_, lean_object* v_isl_1398_, lean_object* v_x_1399_){
_start:
{
if (lean_obj_tag(v_x_1399_) == 5)
{
lean_object* v_u_1400_; lean_object* v_v_1401_; lean_object* v_islandOf_1402_; lean_object* v___x_1403_; uint8_t v___x_1404_; 
v_u_1400_ = lean_ctor_get(v_x_1399_, 1);
lean_inc(v_u_1400_);
v_v_1401_ = lean_ctor_get(v_x_1399_, 2);
lean_inc(v_v_1401_);
lean_dec_ref_known(v_x_1399_, 3);
v_islandOf_1402_ = lean_ctor_get(v_G_1397_, 1);
lean_inc_ref_n(v_islandOf_1402_, 2);
lean_dec_ref(v_G_1397_);
v___x_1403_ = lean_apply_1(v_islandOf_1402_, v_u_1400_);
v___x_1404_ = lean_nat_dec_eq(v___x_1403_, v_isl_1398_);
lean_dec(v___x_1403_);
if (v___x_1404_ == 0)
{
lean_object* v___x_1405_; uint8_t v___x_1406_; 
v___x_1405_ = lean_apply_1(v_islandOf_1402_, v_v_1401_);
v___x_1406_ = lean_nat_dec_eq(v___x_1405_, v_isl_1398_);
lean_dec(v___x_1405_);
return v___x_1406_;
}
else
{
uint8_t v___x_1407_; 
lean_dec_ref(v_islandOf_1402_);
lean_dec(v_v_1401_);
v___x_1407_ = 0;
return v___x_1407_;
}
}
else
{
uint8_t v___x_1408_; 
lean_dec_ref(v_x_1399_);
lean_dec_ref(v_G_1397_);
v___x_1408_ = 0;
return v___x_1408_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg___boxed(lean_object* v_G_1409_, lean_object* v_isl_1410_, lean_object* v_x_1411_){
_start:
{
uint8_t v_res_1412_; lean_object* v_r_1413_; 
v_res_1412_ = lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg(v_G_1409_, v_isl_1410_, v_x_1411_);
lean_dec(v_isl_1410_);
v_r_1413_ = lean_box(v_res_1412_);
return v_r_1413_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isIslSailIn(lean_object* v_I_1414_, lean_object* v_G_1415_, lean_object* v_isl_1416_, lean_object* v_x_1417_){
_start:
{
uint8_t v___x_1418_; 
v___x_1418_ = lp_island__logistics__proof_IslandLogistics_isIslSailIn___redArg(v_G_1415_, v_isl_1416_, v_x_1417_);
return v___x_1418_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isIslSailIn___boxed(lean_object* v_I_1419_, lean_object* v_G_1420_, lean_object* v_isl_1421_, lean_object* v_x_1422_){
_start:
{
uint8_t v_res_1423_; lean_object* v_r_1424_; 
v_res_1423_ = lp_island__logistics__proof_IslandLogistics_isIslSailIn(v_I_1419_, v_G_1420_, v_isl_1421_, v_x_1422_);
lean_dec(v_isl_1421_);
lean_dec_ref(v_I_1419_);
v_r_1424_ = lean_box(v_res_1423_);
return v_r_1424_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailOut(lean_object* v_I_1425_, lean_object* v_G_1426_, lean_object* v_isl_1427_, lean_object* v_s_1428_, lean_object* v_x_1429_){
_start:
{
if (lean_obj_tag(v_x_1429_) == 0)
{
lean_object* v___x_1430_; 
lean_dec_ref(v_s_1428_);
lean_dec_ref(v_G_1426_);
lean_dec_ref(v_I_1425_);
v___x_1430_ = lean_unsigned_to_nat(0u);
return v___x_1430_;
}
else
{
lean_object* v_head_1431_; lean_object* v_tail_1432_; lean_object* v___y_1434_; 
v_head_1431_ = lean_ctor_get(v_x_1429_, 0);
lean_inc(v_head_1431_);
v_tail_1432_ = lean_ctor_get(v_x_1429_, 1);
lean_inc(v_tail_1432_);
lean_dec_ref_known(v_x_1429_, 2);
if (lean_obj_tag(v_head_1431_) == 5)
{
lean_object* v_f_1440_; lean_object* v_u_1441_; lean_object* v_v_1442_; lean_object* v_islandOf_1443_; lean_object* v___x_1444_; uint8_t v___x_1445_; 
v_f_1440_ = lean_ctor_get(v_head_1431_, 0);
v_u_1441_ = lean_ctor_get(v_head_1431_, 1);
v_v_1442_ = lean_ctor_get(v_head_1431_, 2);
v_islandOf_1443_ = lean_ctor_get(v_G_1426_, 1);
lean_inc_ref(v_islandOf_1443_);
lean_inc(v_u_1441_);
v___x_1444_ = lean_apply_1(v_islandOf_1443_, v_u_1441_);
v___x_1445_ = lean_nat_dec_eq(v___x_1444_, v_isl_1427_);
lean_dec(v___x_1444_);
if (v___x_1445_ == 0)
{
lean_object* v___x_1446_; 
v___x_1446_ = lean_unsigned_to_nat(0u);
v___y_1434_ = v___x_1446_;
goto v___jp_1433_;
}
else
{
lean_object* v___x_1447_; uint8_t v___x_1448_; 
lean_inc_ref(v_islandOf_1443_);
lean_inc(v_v_1442_);
v___x_1447_ = lean_apply_1(v_islandOf_1443_, v_v_1442_);
v___x_1448_ = lean_nat_dec_eq(v___x_1447_, v_isl_1427_);
lean_dec(v___x_1447_);
if (v___x_1448_ == 0)
{
lean_object* v___x_1449_; lean_object* v___x_1450_; uint8_t v___x_1451_; 
v___x_1449_ = lean_unsigned_to_nat(0u);
lean_inc(v_f_1440_);
lean_inc_ref(v_s_1428_);
lean_inc_ref(v_I_1425_);
v___x_1450_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_1425_, v_s_1428_, v_f_1440_);
v___x_1451_ = lean_nat_dec_lt(v___x_1449_, v___x_1450_);
lean_dec(v___x_1450_);
if (v___x_1451_ == 0)
{
goto v___jp_1438_;
}
else
{
lean_object* v___x_1452_; 
v___x_1452_ = lean_unsigned_to_nat(1u);
v___y_1434_ = v___x_1452_;
goto v___jp_1433_;
}
}
else
{
goto v___jp_1438_;
}
}
}
else
{
lean_object* v___x_1453_; 
v___x_1453_ = lean_unsigned_to_nat(0u);
v___y_1434_ = v___x_1453_;
goto v___jp_1433_;
}
v___jp_1433_:
{
lean_object* v___x_1435_; lean_object* v___x_1436_; lean_object* v___x_1437_; 
lean_inc_ref(v_I_1425_);
v___x_1435_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1425_, v_s_1428_, v_head_1431_);
v___x_1436_ = lp_island__logistics__proof_IslandLogistics_loadedIslSailOut(v_I_1425_, v_G_1426_, v_isl_1427_, v___x_1435_, v_tail_1432_);
v___x_1437_ = lean_nat_add(v___y_1434_, v___x_1436_);
lean_dec(v___x_1436_);
return v___x_1437_;
}
v___jp_1438_:
{
lean_object* v___x_1439_; 
v___x_1439_ = lean_unsigned_to_nat(0u);
v___y_1434_ = v___x_1439_;
goto v___jp_1433_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailOut___boxed(lean_object* v_I_1454_, lean_object* v_G_1455_, lean_object* v_isl_1456_, lean_object* v_s_1457_, lean_object* v_x_1458_){
_start:
{
lean_object* v_res_1459_; 
v_res_1459_ = lp_island__logistics__proof_IslandLogistics_loadedIslSailOut(v_I_1454_, v_G_1455_, v_isl_1456_, v_s_1457_, v_x_1458_);
lean_dec(v_isl_1456_);
return v_res_1459_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailIn(lean_object* v_I_1460_, lean_object* v_G_1461_, lean_object* v_isl_1462_, lean_object* v_s_1463_, lean_object* v_x_1464_){
_start:
{
if (lean_obj_tag(v_x_1464_) == 0)
{
lean_object* v___x_1465_; 
lean_dec_ref(v_s_1463_);
lean_dec_ref(v_G_1461_);
lean_dec_ref(v_I_1460_);
v___x_1465_ = lean_unsigned_to_nat(0u);
return v___x_1465_;
}
else
{
lean_object* v_head_1466_; lean_object* v_tail_1467_; lean_object* v___y_1469_; 
v_head_1466_ = lean_ctor_get(v_x_1464_, 0);
lean_inc(v_head_1466_);
v_tail_1467_ = lean_ctor_get(v_x_1464_, 1);
lean_inc(v_tail_1467_);
lean_dec_ref_known(v_x_1464_, 2);
if (lean_obj_tag(v_head_1466_) == 5)
{
lean_object* v_f_1475_; lean_object* v_u_1476_; lean_object* v_v_1477_; lean_object* v_islandOf_1478_; lean_object* v___x_1479_; uint8_t v___x_1480_; 
v_f_1475_ = lean_ctor_get(v_head_1466_, 0);
v_u_1476_ = lean_ctor_get(v_head_1466_, 1);
v_v_1477_ = lean_ctor_get(v_head_1466_, 2);
v_islandOf_1478_ = lean_ctor_get(v_G_1461_, 1);
lean_inc_ref(v_islandOf_1478_);
lean_inc(v_u_1476_);
v___x_1479_ = lean_apply_1(v_islandOf_1478_, v_u_1476_);
v___x_1480_ = lean_nat_dec_eq(v___x_1479_, v_isl_1462_);
lean_dec(v___x_1479_);
if (v___x_1480_ == 0)
{
lean_object* v___x_1481_; uint8_t v___x_1482_; 
lean_inc_ref(v_islandOf_1478_);
lean_inc(v_v_1477_);
v___x_1481_ = lean_apply_1(v_islandOf_1478_, v_v_1477_);
v___x_1482_ = lean_nat_dec_eq(v___x_1481_, v_isl_1462_);
lean_dec(v___x_1481_);
if (v___x_1482_ == 0)
{
goto v___jp_1473_;
}
else
{
lean_object* v___x_1483_; lean_object* v___x_1484_; uint8_t v___x_1485_; 
v___x_1483_ = lean_unsigned_to_nat(0u);
lean_inc(v_f_1475_);
lean_inc_ref(v_s_1463_);
lean_inc_ref(v_I_1460_);
v___x_1484_ = lp_island__logistics__proof_IslandLogistics_State_ferryCount(v_I_1460_, v_s_1463_, v_f_1475_);
v___x_1485_ = lean_nat_dec_lt(v___x_1483_, v___x_1484_);
lean_dec(v___x_1484_);
if (v___x_1485_ == 0)
{
goto v___jp_1473_;
}
else
{
lean_object* v___x_1486_; 
v___x_1486_ = lean_unsigned_to_nat(1u);
v___y_1469_ = v___x_1486_;
goto v___jp_1468_;
}
}
}
else
{
lean_object* v___x_1487_; 
v___x_1487_ = lean_unsigned_to_nat(0u);
v___y_1469_ = v___x_1487_;
goto v___jp_1468_;
}
}
else
{
lean_object* v___x_1488_; 
v___x_1488_ = lean_unsigned_to_nat(0u);
v___y_1469_ = v___x_1488_;
goto v___jp_1468_;
}
v___jp_1468_:
{
lean_object* v___x_1470_; lean_object* v___x_1471_; lean_object* v___x_1472_; 
lean_inc_ref(v_I_1460_);
v___x_1470_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_1460_, v_s_1463_, v_head_1466_);
v___x_1471_ = lp_island__logistics__proof_IslandLogistics_loadedIslSailIn(v_I_1460_, v_G_1461_, v_isl_1462_, v___x_1470_, v_tail_1467_);
v___x_1472_ = lean_nat_add(v___y_1469_, v___x_1471_);
lean_dec(v___x_1471_);
return v___x_1472_;
}
v___jp_1473_:
{
lean_object* v___x_1474_; 
v___x_1474_ = lean_unsigned_to_nat(0u);
v___y_1469_ = v___x_1474_;
goto v___jp_1468_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_loadedIslSailIn___boxed(lean_object* v_I_1489_, lean_object* v_G_1490_, lean_object* v_isl_1491_, lean_object* v_s_1492_, lean_object* v_x_1493_){
_start:
{
lean_object* v_res_1494_; 
v_res_1494_ = lp_island__logistics__proof_IslandLogistics_loadedIslSailIn(v_I_1489_, v_G_1490_, v_isl_1491_, v_s_1492_, v_x_1493_);
lean_dec(v_isl_1491_);
return v_res_1494_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter___redArg(lean_object* v_x_1495_, lean_object* v_h__1_1496_, lean_object* v_h__2_1497_){
_start:
{
if (lean_obj_tag(v_x_1495_) == 0)
{
lean_object* v___x_1498_; lean_object* v___x_1499_; 
lean_dec(v_h__2_1497_);
v___x_1498_ = lean_box(0);
v___x_1499_ = lean_apply_1(v_h__1_1496_, v___x_1498_);
return v___x_1499_;
}
else
{
lean_object* v_head_1500_; lean_object* v_tail_1501_; lean_object* v___x_1502_; 
lean_dec(v_h__1_1496_);
v_head_1500_ = lean_ctor_get(v_x_1495_, 0);
lean_inc(v_head_1500_);
v_tail_1501_ = lean_ctor_get(v_x_1495_, 1);
lean_inc(v_tail_1501_);
lean_dec_ref_known(v_x_1495_, 2);
v___x_1502_ = lean_apply_2(v_h__2_1497_, v_head_1500_, v_tail_1501_);
return v___x_1502_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter(lean_object* v_I_1503_, lean_object* v_motive_1504_, lean_object* v_x_1505_, lean_object* v_h__1_1506_, lean_object* v_h__2_1507_){
_start:
{
if (lean_obj_tag(v_x_1505_) == 0)
{
lean_object* v___x_1508_; lean_object* v___x_1509_; 
lean_dec(v_h__2_1507_);
v___x_1508_ = lean_box(0);
v___x_1509_ = lean_apply_1(v_h__1_1506_, v___x_1508_);
return v___x_1509_;
}
else
{
lean_object* v_head_1510_; lean_object* v_tail_1511_; lean_object* v___x_1512_; 
lean_dec(v_h__1_1506_);
v_head_1510_ = lean_ctor_get(v_x_1505_, 0);
lean_inc(v_head_1510_);
v_tail_1511_ = lean_ctor_get(v_x_1505_, 1);
lean_inc(v_tail_1511_);
lean_dec_ref_known(v_x_1505_, 2);
v___x_1512_ = lean_apply_2(v_h__2_1507_, v_head_1510_, v_tail_1511_);
return v___x_1512_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter___boxed(lean_object* v_I_1513_, lean_object* v_motive_1514_, lean_object* v_x_1515_, lean_object* v_h__1_1516_, lean_object* v_h__2_1517_){
_start:
{
lean_object* v_res_1518_; 
v_res_1518_ = lp_island__logistics__proof___private_Ferries_0__IslandLogistics_loadedIslSailOut_match__1_splitter(v_I_1513_, v_motive_1514_, v_x_1515_, v_h__1_1516_, v_h__2_1517_);
lean_dec_ref(v_I_1513_);
return v_res_1518_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin);
lean_object* initialize_island__logistics__proof_PackingAndFlux(uint8_t builtin);
lean_object* initialize_island__logistics__proof_BridgesAndCycles(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_Ferries(uint8_t builtin) {
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
