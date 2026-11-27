// Lean compiler output
// Module: BridgesAndCycles
// Imports: public import Init public meta import Init public import Domain public import PackingAndFlux
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
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* l_List_finRange(lean_object*);
lean_object* l_List_reverse___redArg(lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_listMax(lean_object*);
uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(lean_object*, lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(lean_object*, lean_object*);
lean_object* lean_nat_shiftr(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_dynEffCap(lean_object*, lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object*, lean_object*);
uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_countActions___redArg(lean_object*, lean_object*);
lean_object* l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_applyAction(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isEdgeDrive(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isEdgeDrive___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeDriveCount(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_compMaxEffCap(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1(lean_object*, lean_object*, lean_object*, uint8_t, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 0}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_stateAt_spec__0(lean_object*, lean_object*, lean_object*);
static const lean_array_object lp_island__logistics__proof_IslandLogistics_stateAt___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_stateAt___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_stateAt___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stateAt(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costNonBridgeDrive(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_primStep___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep___lam__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep___lam__1(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_primStep_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primLoop(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primLoop___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_primMST___lam__0(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primMST___lam__0___boxed(lean_object*);
static const lean_closure_object lp_island__logistics__proof_IslandLogistics_primMST___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_closure_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 245}, .m_fun = (void*)lp_island__logistics__proof_IslandLogistics_primMST___lam__0___boxed, .m_arity = 1, .m_num_fixed = 0, .m_objs = {} };
static const lean_object* lp_island__logistics__proof_IslandLogistics_primMST___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_primMST___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primMST(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeWeight(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*1 + 0, .m_other = 1, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckNBDrive(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___boxed(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_minTruckNBDist(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg(lean_object* v_u_1_, lean_object* v_v_2_, lean_object* v_x_3_){
_start:
{
if (lean_obj_tag(v_x_3_) == 0)
{
lean_object* v_u_4_; lean_object* v_v_5_; uint8_t v___x_9_; 
v_u_4_ = lean_ctor_get(v_x_3_, 1);
v_v_5_ = lean_ctor_get(v_x_3_, 2);
v___x_9_ = lean_nat_dec_eq(v_u_4_, v_u_1_);
if (v___x_9_ == 0)
{
goto v___jp_6_;
}
else
{
uint8_t v___x_10_; 
v___x_10_ = lean_nat_dec_eq(v_v_5_, v_v_2_);
if (v___x_10_ == 0)
{
goto v___jp_6_;
}
else
{
return v___x_10_;
}
}
v___jp_6_:
{
uint8_t v___x_7_; 
v___x_7_ = lean_nat_dec_eq(v_u_4_, v_v_2_);
if (v___x_7_ == 0)
{
return v___x_7_;
}
else
{
uint8_t v___x_8_; 
v___x_8_ = lean_nat_dec_eq(v_v_5_, v_u_1_);
return v___x_8_;
}
}
}
else
{
uint8_t v___x_11_; 
v___x_11_ = 0;
return v___x_11_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg___boxed(lean_object* v_u_12_, lean_object* v_v_13_, lean_object* v_x_14_){
_start:
{
uint8_t v_res_15_; lean_object* v_r_16_; 
v_res_15_ = lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg(v_u_12_, v_v_13_, v_x_14_);
lean_dec_ref(v_x_14_);
lean_dec(v_v_13_);
lean_dec(v_u_12_);
v_r_16_ = lean_box(v_res_15_);
return v_r_16_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isEdgeDrive(lean_object* v_I_17_, lean_object* v_u_18_, lean_object* v_v_19_, lean_object* v_x_20_){
_start:
{
uint8_t v___x_21_; 
v___x_21_ = lp_island__logistics__proof_IslandLogistics_isEdgeDrive___redArg(v_u_18_, v_v_19_, v_x_20_);
return v___x_21_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isEdgeDrive___boxed(lean_object* v_I_22_, lean_object* v_u_23_, lean_object* v_v_24_, lean_object* v_x_25_){
_start:
{
uint8_t v_res_26_; lean_object* v_r_27_; 
v_res_26_ = lp_island__logistics__proof_IslandLogistics_isEdgeDrive(v_I_22_, v_u_23_, v_v_24_, v_x_25_);
lean_dec_ref(v_x_25_);
lean_dec(v_v_24_);
lean_dec(v_u_23_);
lean_dec_ref(v_I_22_);
v_r_27_ = lean_box(v_res_26_);
return v_r_27_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg(lean_object* v_u_28_, lean_object* v_v_29_, lean_object* v_x_30_){
_start:
{
if (lean_obj_tag(v_x_30_) == 0)
{
lean_object* v_u_31_; lean_object* v_v_32_; uint8_t v___x_33_; 
v_u_31_ = lean_ctor_get(v_x_30_, 1);
v_v_32_ = lean_ctor_get(v_x_30_, 2);
v___x_33_ = lean_nat_dec_eq(v_u_31_, v_u_28_);
if (v___x_33_ == 0)
{
return v___x_33_;
}
else
{
uint8_t v___x_34_; 
v___x_34_ = lean_nat_dec_eq(v_v_32_, v_v_29_);
return v___x_34_;
}
}
else
{
uint8_t v___x_35_; 
v___x_35_ = 0;
return v___x_35_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg___boxed(lean_object* v_u_36_, lean_object* v_v_37_, lean_object* v_x_38_){
_start:
{
uint8_t v_res_39_; lean_object* v_r_40_; 
v_res_39_ = lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg(v_u_36_, v_v_37_, v_x_38_);
lean_dec_ref(v_x_38_);
lean_dec(v_v_37_);
lean_dec(v_u_36_);
v_r_40_ = lean_box(v_res_39_);
return v_r_40_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive(lean_object* v_I_41_, lean_object* v_u_42_, lean_object* v_v_43_, lean_object* v_x_44_){
_start:
{
uint8_t v___x_45_; 
v___x_45_ = lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___redArg(v_u_42_, v_v_43_, v_x_44_);
return v___x_45_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive___boxed(lean_object* v_I_46_, lean_object* v_u_47_, lean_object* v_v_48_, lean_object* v_x_49_){
_start:
{
uint8_t v_res_50_; lean_object* v_r_51_; 
v_res_50_ = lp_island__logistics__proof_IslandLogistics_isDirEdgeDrive(v_I_46_, v_u_47_, v_v_48_, v_x_49_);
lean_dec_ref(v_x_49_);
lean_dec(v_v_48_);
lean_dec(v_u_47_);
lean_dec_ref(v_I_46_);
v_r_51_ = lean_box(v_res_50_);
return v_r_51_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeDriveCount(lean_object* v_I_52_, lean_object* v_u_53_, lean_object* v_v_54_, lean_object* v_00_u03c0_55_){
_start:
{
lean_object* v___x_56_; lean_object* v___x_57_; 
v___x_56_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isEdgeDrive___boxed), 4, 3);
lean_closure_set(v___x_56_, 0, v_I_52_);
lean_closure_set(v___x_56_, 1, v_u_53_);
lean_closure_set(v___x_56_, 2, v_v_54_);
v___x_57_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_56_, v_00_u03c0_55_);
return v___x_57_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object* v_x_58_, lean_object* v_h__1_59_, lean_object* v_h__2_60_){
_start:
{
if (lean_obj_tag(v_x_58_) == 0)
{
lean_object* v_l_61_; lean_object* v___x_62_; 
lean_dec(v_h__2_60_);
v_l_61_ = lean_ctor_get(v_x_58_, 0);
lean_inc(v_l_61_);
lean_dec_ref_known(v_x_58_, 1);
v___x_62_ = lean_apply_1(v_h__1_59_, v_l_61_);
return v___x_62_;
}
else
{
lean_object* v_f_63_; lean_object* v___x_64_; 
lean_dec(v_h__1_59_);
v_f_63_ = lean_ctor_get(v_x_58_, 0);
lean_inc(v_f_63_);
lean_dec_ref_known(v_x_58_, 1);
v___x_64_ = lean_apply_1(v_h__2_60_, v_f_63_);
return v___x_64_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object* v_I_65_, lean_object* v_motive_66_, lean_object* v_x_67_, lean_object* v_h__1_68_, lean_object* v_h__2_69_){
_start:
{
if (lean_obj_tag(v_x_67_) == 0)
{
lean_object* v_l_70_; lean_object* v___x_71_; 
lean_dec(v_h__2_69_);
v_l_70_ = lean_ctor_get(v_x_67_, 0);
lean_inc(v_l_70_);
lean_dec_ref_known(v_x_67_, 1);
v___x_71_ = lean_apply_1(v_h__1_68_, v_l_70_);
return v___x_71_;
}
else
{
lean_object* v_f_72_; lean_object* v___x_73_; 
lean_dec(v_h__1_68_);
v_f_72_ = lean_ctor_get(v_x_67_, 0);
lean_inc(v_f_72_);
lean_dec_ref_known(v_x_67_, 1);
v___x_73_ = lean_apply_1(v_h__2_69_, v_f_72_);
return v___x_73_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object* v_I_74_, lean_object* v_motive_75_, lean_object* v_x_76_, lean_object* v_h__1_77_, lean_object* v_h__2_78_){
_start:
{
lean_object* v_res_79_; 
v_res_79_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(v_I_74_, v_motive_75_, v_x_76_, v_h__1_77_, v_h__2_78_);
lean_dec_ref(v_I_74_);
return v_res_79_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter___redArg(lean_object* v_x_80_, lean_object* v_h__1_81_, lean_object* v_h__2_82_){
_start:
{
if (lean_obj_tag(v_x_80_) == 0)
{
lean_object* v_t_83_; lean_object* v_u_84_; lean_object* v_v_85_; lean_object* v___x_86_; 
lean_dec(v_h__2_82_);
v_t_83_ = lean_ctor_get(v_x_80_, 0);
lean_inc(v_t_83_);
v_u_84_ = lean_ctor_get(v_x_80_, 1);
lean_inc(v_u_84_);
v_v_85_ = lean_ctor_get(v_x_80_, 2);
lean_inc(v_v_85_);
lean_dec_ref_known(v_x_80_, 3);
v___x_86_ = lean_apply_3(v_h__1_81_, v_t_83_, v_u_84_, v_v_85_);
return v___x_86_;
}
else
{
lean_object* v___x_87_; 
lean_dec(v_h__1_81_);
v___x_87_ = lean_apply_2(v_h__2_82_, v_x_80_, lean_box(0));
return v___x_87_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter(lean_object* v_I_88_, lean_object* v_motive_89_, lean_object* v_x_90_, lean_object* v_h__1_91_, lean_object* v_h__2_92_){
_start:
{
if (lean_obj_tag(v_x_90_) == 0)
{
lean_object* v_t_93_; lean_object* v_u_94_; lean_object* v_v_95_; lean_object* v___x_96_; 
lean_dec(v_h__2_92_);
v_t_93_ = lean_ctor_get(v_x_90_, 0);
lean_inc(v_t_93_);
v_u_94_ = lean_ctor_get(v_x_90_, 1);
lean_inc(v_u_94_);
v_v_95_ = lean_ctor_get(v_x_90_, 2);
lean_inc(v_v_95_);
lean_dec_ref_known(v_x_90_, 3);
v___x_96_ = lean_apply_3(v_h__1_91_, v_t_93_, v_u_94_, v_v_95_);
return v___x_96_;
}
else
{
lean_object* v___x_97_; 
lean_dec(v_h__1_91_);
v___x_97_ = lean_apply_2(v_h__2_92_, v_x_90_, lean_box(0));
return v___x_97_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter___boxed(lean_object* v_I_98_, lean_object* v_motive_99_, lean_object* v_x_100_, lean_object* v_h__1_101_, lean_object* v_h__2_102_){
_start:
{
lean_object* v_res_103_; 
v_res_103_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_isEdgeDrive_match__1_splitter(v_I_98_, v_motive_99_, v_x_100_, v_h__1_101_, v_h__2_102_);
lean_dec_ref(v_I_98_);
return v_res_103_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___redArg(lean_object* v_s_104_, lean_object* v_inComp_105_, lean_object* v_a_106_, lean_object* v_a_107_){
_start:
{
if (lean_obj_tag(v_a_106_) == 0)
{
lean_object* v___x_108_; 
lean_dec_ref(v_inComp_105_);
lean_dec_ref(v_s_104_);
v___x_108_ = l_List_reverse___redArg(v_a_107_);
return v___x_108_;
}
else
{
lean_object* v_head_109_; lean_object* v_tail_110_; lean_object* v___x_112_; uint8_t v_isShared_113_; uint8_t v_isSharedCheck_122_; 
v_head_109_ = lean_ctor_get(v_a_106_, 0);
v_tail_110_ = lean_ctor_get(v_a_106_, 1);
v_isSharedCheck_122_ = !lean_is_exclusive(v_a_106_);
if (v_isSharedCheck_122_ == 0)
{
v___x_112_ = v_a_106_;
v_isShared_113_ = v_isSharedCheck_122_;
goto v_resetjp_111_;
}
else
{
lean_inc(v_tail_110_);
lean_inc(v_head_109_);
lean_dec(v_a_106_);
v___x_112_ = lean_box(0);
v_isShared_113_ = v_isSharedCheck_122_;
goto v_resetjp_111_;
}
v_resetjp_111_:
{
lean_object* v___x_114_; lean_object* v___x_115_; uint8_t v___x_116_; 
lean_inc(v_head_109_);
lean_inc_ref(v_s_104_);
v___x_114_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_104_, v_head_109_);
lean_inc_ref(v_inComp_105_);
v___x_115_ = lean_apply_1(v_inComp_105_, v___x_114_);
v___x_116_ = lean_unbox(v___x_115_);
if (v___x_116_ == 0)
{
lean_del_object(v___x_112_);
lean_dec(v_head_109_);
v_a_106_ = v_tail_110_;
goto _start;
}
else
{
lean_object* v___x_119_; 
if (v_isShared_113_ == 0)
{
lean_ctor_set(v___x_112_, 1, v_a_107_);
v___x_119_ = v___x_112_;
goto v_reusejp_118_;
}
else
{
lean_object* v_reuseFailAlloc_121_; 
v_reuseFailAlloc_121_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_121_, 0, v_head_109_);
lean_ctor_set(v_reuseFailAlloc_121_, 1, v_a_107_);
v___x_119_ = v_reuseFailAlloc_121_;
goto v_reusejp_118_;
}
v_reusejp_118_:
{
v_a_106_ = v_tail_110_;
v_a_107_ = v___x_119_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_compMaxEffCap(lean_object* v_I_123_, lean_object* v_s_124_, lean_object* v_inComp_125_){
_start:
{
lean_object* v_numTrucks_126_; lean_object* v___x_127_; lean_object* v___x_128_; lean_object* v___x_129_; lean_object* v___x_130_; lean_object* v___x_131_; 
v_numTrucks_126_ = lean_ctor_get(v_I_123_, 3);
lean_inc(v_numTrucks_126_);
v___x_127_ = l_List_finRange(v_numTrucks_126_);
v___x_128_ = lean_box(0);
lean_inc_ref(v_s_124_);
v___x_129_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___redArg(v_s_124_, v_inComp_125_, v___x_127_, v___x_128_);
v___x_130_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(v_I_123_, v_s_124_, v___x_129_, v___x_128_);
v___x_131_ = lp_island__logistics__proof_IslandLogistics_listMax(v___x_130_);
lean_dec(v___x_130_);
return v___x_131_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0(lean_object* v_I_132_, lean_object* v_s_133_, lean_object* v_inComp_134_, lean_object* v_a_135_, lean_object* v_a_136_){
_start:
{
lean_object* v___x_137_; 
v___x_137_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___redArg(v_s_133_, v_inComp_134_, v_a_135_, v_a_136_);
return v___x_137_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0___boxed(lean_object* v_I_138_, lean_object* v_s_139_, lean_object* v_inComp_140_, lean_object* v_a_141_, lean_object* v_a_142_){
_start:
{
lean_object* v_res_143_; 
v_res_143_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_compMaxEffCap_spec__0(v_I_138_, v_s_139_, v_inComp_140_, v_a_141_, v_a_142_);
lean_dec_ref(v_I_138_);
return v_res_143_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0(lean_object* v_s_144_, lean_object* v_inA_145_, lean_object* v_t_146_){
_start:
{
lean_object* v___x_147_; lean_object* v___x_148_; uint8_t v___x_149_; 
v___x_147_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_144_, v_t_146_);
v___x_148_ = lean_apply_1(v_inA_145_, v___x_147_);
v___x_149_ = lean_unbox(v___x_148_);
return v___x_149_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0___boxed(lean_object* v_s_150_, lean_object* v_inA_151_, lean_object* v_t_152_){
_start:
{
uint8_t v_res_153_; lean_object* v_r_154_; 
v_res_153_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0(v_s_150_, v_inA_151_, v_t_152_);
v_r_154_ = lean_box(v_res_153_);
return v_r_154_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1(lean_object* v_s_155_, lean_object* v_inComp_156_, lean_object* v_t_157_){
_start:
{
lean_object* v___x_158_; lean_object* v___x_159_; uint8_t v___x_160_; 
v___x_158_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_155_, v_t_157_);
v___x_159_ = lean_apply_1(v_inComp_156_, v___x_158_);
v___x_160_ = lean_unbox(v___x_159_);
return v___x_160_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1___boxed(lean_object* v_s_161_, lean_object* v_inComp_162_, lean_object* v_t_163_){
_start:
{
uint8_t v_res_164_; lean_object* v_r_165_; 
v_res_164_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1(v_s_161_, v_inComp_162_, v_t_163_);
v_r_165_ = lean_box(v_res_164_);
return v_r_165_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2(lean_object* v_I_166_, lean_object* v_s_167_, lean_object* v_inComp_168_, lean_object* v___x_169_, lean_object* v_inA_170_, lean_object* v_pkgGoal_171_, lean_object* v_c__cap_172_, lean_object* v_pkgWeight_173_, lean_object* v_p_174_){
_start:
{
uint8_t v___x_175_; 
lean_inc(v_p_174_);
lean_inc_ref(v_s_167_);
v___x_175_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_166_, v_s_167_, v_p_174_);
if (v___x_175_ == 0)
{
lean_object* v___x_176_; lean_object* v___x_177_; uint8_t v___x_178_; 
lean_inc(v_p_174_);
v___x_176_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_167_, v_p_174_);
lean_inc(v___x_176_);
v___x_177_ = lean_apply_1(v_inComp_168_, v___x_176_);
v___x_178_ = lean_unbox(v___x_177_);
if (v___x_178_ == 0)
{
lean_dec(v___x_176_);
lean_dec(v_p_174_);
lean_dec_ref(v_pkgWeight_173_);
lean_dec_ref(v_pkgGoal_171_);
lean_dec_ref(v_inA_170_);
lean_inc(v___x_169_);
return v___x_169_;
}
else
{
lean_object* v___x_179_; uint8_t v___x_180_; 
lean_inc_ref(v_inA_170_);
v___x_179_ = lean_apply_1(v_inA_170_, v___x_176_);
v___x_180_ = lean_unbox(v___x_179_);
if (v___x_180_ == 0)
{
lean_object* v___x_181_; lean_object* v___x_182_; uint8_t v___x_183_; 
lean_inc(v_p_174_);
v___x_181_ = lean_apply_1(v_pkgGoal_171_, v_p_174_);
v___x_182_ = lean_apply_1(v_inA_170_, v___x_181_);
v___x_183_ = lean_unbox(v___x_182_);
if (v___x_183_ == 0)
{
lean_dec(v_p_174_);
lean_dec_ref(v_pkgWeight_173_);
lean_inc(v___x_169_);
return v___x_169_;
}
else
{
lean_object* v___x_184_; lean_object* v___x_185_; lean_object* v___x_186_; uint8_t v___x_187_; 
v___x_184_ = lean_unsigned_to_nat(1u);
v___x_185_ = lean_nat_shiftr(v_c__cap_172_, v___x_184_);
v___x_186_ = lean_apply_1(v_pkgWeight_173_, v_p_174_);
v___x_187_ = lean_nat_dec_lt(v___x_185_, v___x_186_);
lean_dec(v___x_186_);
lean_dec(v___x_185_);
if (v___x_187_ == 0)
{
lean_inc(v___x_169_);
return v___x_169_;
}
else
{
return v___x_184_;
}
}
}
else
{
lean_dec(v_p_174_);
lean_dec_ref(v_pkgWeight_173_);
lean_dec_ref(v_pkgGoal_171_);
lean_dec_ref(v_inA_170_);
lean_inc(v___x_169_);
return v___x_169_;
}
}
}
else
{
lean_dec(v_p_174_);
lean_dec_ref(v_pkgWeight_173_);
lean_dec_ref(v_pkgGoal_171_);
lean_dec_ref(v_inA_170_);
lean_dec_ref(v_inComp_168_);
lean_dec_ref(v_s_167_);
lean_inc(v___x_169_);
return v___x_169_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2___boxed(lean_object* v_I_188_, lean_object* v_s_189_, lean_object* v_inComp_190_, lean_object* v___x_191_, lean_object* v_inA_192_, lean_object* v_pkgGoal_193_, lean_object* v_c__cap_194_, lean_object* v_pkgWeight_195_, lean_object* v_p_196_){
_start:
{
lean_object* v_res_197_; 
v_res_197_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2(v_I_188_, v_s_189_, v_inComp_190_, v___x_191_, v_inA_192_, v_pkgGoal_193_, v_c__cap_194_, v_pkgWeight_195_, v_p_196_);
lean_dec(v_c__cap_194_);
lean_dec(v___x_191_);
return v_res_197_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3(lean_object* v_I_198_, lean_object* v_s_199_, lean_object* v_inComp_200_, lean_object* v___x_201_, lean_object* v_inA_202_, lean_object* v_pkgGoal_203_, lean_object* v_c__cap_204_, lean_object* v_pkgWeight_205_, lean_object* v_p_206_){
_start:
{
uint8_t v___x_207_; 
lean_inc(v_p_206_);
lean_inc_ref(v_s_199_);
v___x_207_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_198_, v_s_199_, v_p_206_);
if (v___x_207_ == 0)
{
lean_object* v___x_208_; lean_object* v___x_209_; uint8_t v___x_210_; 
lean_inc(v_p_206_);
v___x_208_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_199_, v_p_206_);
lean_inc(v___x_208_);
v___x_209_ = lean_apply_1(v_inComp_200_, v___x_208_);
v___x_210_ = lean_unbox(v___x_209_);
if (v___x_210_ == 0)
{
lean_dec(v___x_208_);
lean_dec(v_p_206_);
lean_dec_ref(v_pkgWeight_205_);
lean_dec_ref(v_pkgGoal_203_);
lean_dec_ref(v_inA_202_);
lean_inc(v___x_201_);
return v___x_201_;
}
else
{
lean_object* v___x_211_; uint8_t v___x_212_; 
lean_inc_ref(v_inA_202_);
v___x_211_ = lean_apply_1(v_inA_202_, v___x_208_);
v___x_212_ = lean_unbox(v___x_211_);
if (v___x_212_ == 0)
{
lean_dec(v_p_206_);
lean_dec_ref(v_pkgWeight_205_);
lean_dec_ref(v_pkgGoal_203_);
lean_dec_ref(v_inA_202_);
lean_inc(v___x_201_);
return v___x_201_;
}
else
{
lean_object* v___x_213_; lean_object* v___x_214_; uint8_t v___x_215_; 
lean_inc(v_p_206_);
v___x_213_ = lean_apply_1(v_pkgGoal_203_, v_p_206_);
v___x_214_ = lean_apply_1(v_inA_202_, v___x_213_);
v___x_215_ = lean_unbox(v___x_214_);
if (v___x_215_ == 0)
{
lean_object* v___x_216_; lean_object* v___x_217_; lean_object* v___x_218_; uint8_t v___x_219_; 
v___x_216_ = lean_unsigned_to_nat(1u);
v___x_217_ = lean_nat_shiftr(v_c__cap_204_, v___x_216_);
v___x_218_ = lean_apply_1(v_pkgWeight_205_, v_p_206_);
v___x_219_ = lean_nat_dec_lt(v___x_217_, v___x_218_);
lean_dec(v___x_218_);
lean_dec(v___x_217_);
if (v___x_219_ == 0)
{
lean_inc(v___x_201_);
return v___x_201_;
}
else
{
return v___x_216_;
}
}
else
{
lean_dec(v_p_206_);
lean_dec_ref(v_pkgWeight_205_);
lean_inc(v___x_201_);
return v___x_201_;
}
}
}
}
else
{
lean_dec(v_p_206_);
lean_dec_ref(v_pkgWeight_205_);
lean_dec_ref(v_pkgGoal_203_);
lean_dec_ref(v_inA_202_);
lean_dec_ref(v_inComp_200_);
lean_dec_ref(v_s_199_);
lean_inc(v___x_201_);
return v___x_201_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3___boxed(lean_object* v_I_220_, lean_object* v_s_221_, lean_object* v_inComp_222_, lean_object* v___x_223_, lean_object* v_inA_224_, lean_object* v_pkgGoal_225_, lean_object* v_c__cap_226_, lean_object* v_pkgWeight_227_, lean_object* v_p_228_){
_start:
{
lean_object* v_res_229_; 
v_res_229_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3(v_I_220_, v_s_221_, v_inComp_222_, v___x_223_, v_inA_224_, v_pkgGoal_225_, v_c__cap_226_, v_pkgWeight_227_, v_p_228_);
lean_dec(v_c__cap_226_);
lean_dec(v___x_223_);
return v_res_229_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4(lean_object* v_I_230_, lean_object* v_s_231_, lean_object* v_inComp_232_, lean_object* v___x_233_, lean_object* v_inA_234_, lean_object* v_pkgGoal_235_, lean_object* v_pkgWeight_236_, lean_object* v_p_237_){
_start:
{
uint8_t v___x_238_; 
lean_inc(v_p_237_);
lean_inc_ref(v_s_231_);
v___x_238_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_230_, v_s_231_, v_p_237_);
if (v___x_238_ == 0)
{
lean_object* v___x_239_; lean_object* v___x_240_; uint8_t v___x_241_; 
lean_inc(v_p_237_);
v___x_239_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_231_, v_p_237_);
lean_inc(v___x_239_);
v___x_240_ = lean_apply_1(v_inComp_232_, v___x_239_);
v___x_241_ = lean_unbox(v___x_240_);
if (v___x_241_ == 0)
{
lean_dec(v___x_239_);
lean_dec(v_p_237_);
lean_dec_ref(v_pkgWeight_236_);
lean_dec_ref(v_pkgGoal_235_);
lean_dec_ref(v_inA_234_);
lean_inc(v___x_233_);
return v___x_233_;
}
else
{
lean_object* v___x_242_; uint8_t v___x_243_; 
lean_inc_ref(v_inA_234_);
v___x_242_ = lean_apply_1(v_inA_234_, v___x_239_);
v___x_243_ = lean_unbox(v___x_242_);
if (v___x_243_ == 0)
{
lean_object* v___x_244_; lean_object* v___x_245_; uint8_t v___x_246_; 
lean_inc(v_p_237_);
v___x_244_ = lean_apply_1(v_pkgGoal_235_, v_p_237_);
v___x_245_ = lean_apply_1(v_inA_234_, v___x_244_);
v___x_246_ = lean_unbox(v___x_245_);
if (v___x_246_ == 0)
{
lean_dec(v_p_237_);
lean_dec_ref(v_pkgWeight_236_);
lean_inc(v___x_233_);
return v___x_233_;
}
else
{
lean_object* v___x_247_; 
v___x_247_ = lean_apply_1(v_pkgWeight_236_, v_p_237_);
return v___x_247_;
}
}
else
{
lean_dec(v_p_237_);
lean_dec_ref(v_pkgWeight_236_);
lean_dec_ref(v_pkgGoal_235_);
lean_dec_ref(v_inA_234_);
lean_inc(v___x_233_);
return v___x_233_;
}
}
}
else
{
lean_dec(v_p_237_);
lean_dec_ref(v_pkgWeight_236_);
lean_dec_ref(v_pkgGoal_235_);
lean_dec_ref(v_inA_234_);
lean_dec_ref(v_inComp_232_);
lean_dec_ref(v_s_231_);
lean_inc(v___x_233_);
return v___x_233_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4___boxed(lean_object* v_I_248_, lean_object* v_s_249_, lean_object* v_inComp_250_, lean_object* v___x_251_, lean_object* v_inA_252_, lean_object* v_pkgGoal_253_, lean_object* v_pkgWeight_254_, lean_object* v_p_255_){
_start:
{
lean_object* v_res_256_; 
v_res_256_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4(v_I_248_, v_s_249_, v_inComp_250_, v___x_251_, v_inA_252_, v_pkgGoal_253_, v_pkgWeight_254_, v_p_255_);
lean_dec(v___x_251_);
return v_res_256_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5(lean_object* v_I_257_, lean_object* v_s_258_, lean_object* v_inComp_259_, lean_object* v___x_260_, lean_object* v_inA_261_, lean_object* v_pkgGoal_262_, lean_object* v_pkgWeight_263_, lean_object* v_p_264_){
_start:
{
uint8_t v___x_265_; 
lean_inc(v_p_264_);
lean_inc_ref(v_s_258_);
v___x_265_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_257_, v_s_258_, v_p_264_);
if (v___x_265_ == 0)
{
lean_object* v___x_266_; lean_object* v___x_267_; uint8_t v___x_268_; 
lean_inc(v_p_264_);
v___x_266_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_258_, v_p_264_);
lean_inc(v___x_266_);
v___x_267_ = lean_apply_1(v_inComp_259_, v___x_266_);
v___x_268_ = lean_unbox(v___x_267_);
if (v___x_268_ == 0)
{
lean_dec(v___x_266_);
lean_dec(v_p_264_);
lean_dec_ref(v_pkgWeight_263_);
lean_dec_ref(v_pkgGoal_262_);
lean_dec_ref(v_inA_261_);
lean_inc(v___x_260_);
return v___x_260_;
}
else
{
lean_object* v___x_269_; uint8_t v___x_270_; 
lean_inc_ref(v_inA_261_);
v___x_269_ = lean_apply_1(v_inA_261_, v___x_266_);
v___x_270_ = lean_unbox(v___x_269_);
if (v___x_270_ == 0)
{
lean_dec(v_p_264_);
lean_dec_ref(v_pkgWeight_263_);
lean_dec_ref(v_pkgGoal_262_);
lean_dec_ref(v_inA_261_);
lean_inc(v___x_260_);
return v___x_260_;
}
else
{
lean_object* v___x_271_; lean_object* v___x_272_; uint8_t v___x_273_; 
lean_inc(v_p_264_);
v___x_271_ = lean_apply_1(v_pkgGoal_262_, v_p_264_);
v___x_272_ = lean_apply_1(v_inA_261_, v___x_271_);
v___x_273_ = lean_unbox(v___x_272_);
if (v___x_273_ == 0)
{
lean_object* v___x_274_; 
v___x_274_ = lean_apply_1(v_pkgWeight_263_, v_p_264_);
return v___x_274_;
}
else
{
lean_dec(v_p_264_);
lean_dec_ref(v_pkgWeight_263_);
lean_inc(v___x_260_);
return v___x_260_;
}
}
}
}
else
{
lean_dec(v_p_264_);
lean_dec_ref(v_pkgWeight_263_);
lean_dec_ref(v_pkgGoal_262_);
lean_dec_ref(v_inA_261_);
lean_dec_ref(v_inComp_259_);
lean_dec_ref(v_s_258_);
lean_inc(v___x_260_);
return v___x_260_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5___boxed(lean_object* v_I_275_, lean_object* v_s_276_, lean_object* v_inComp_277_, lean_object* v___x_278_, lean_object* v_inA_279_, lean_object* v_pkgGoal_280_, lean_object* v_pkgWeight_281_, lean_object* v_p_282_){
_start:
{
lean_object* v_res_283_; 
v_res_283_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5(v_I_275_, v_s_276_, v_inComp_277_, v___x_278_, v_inA_279_, v_pkgGoal_280_, v_pkgWeight_281_, v_p_282_);
lean_dec(v___x_278_);
return v_res_283_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6(lean_object* v_tIn_284_, lean_object* v___x_285_, lean_object* v_tSide_286_, lean_object* v_I_287_, lean_object* v_s_288_, lean_object* v_t_289_){
_start:
{
lean_object* v___x_290_; uint8_t v___x_291_; 
lean_inc(v_t_289_);
v___x_290_ = lean_apply_1(v_tIn_284_, v_t_289_);
v___x_291_ = lean_unbox(v___x_290_);
if (v___x_291_ == 0)
{
lean_dec(v_t_289_);
lean_dec_ref(v_s_288_);
lean_dec_ref(v_I_287_);
lean_dec_ref(v_tSide_286_);
lean_inc(v___x_285_);
return v___x_285_;
}
else
{
lean_object* v___x_292_; uint8_t v___x_293_; 
lean_inc(v_t_289_);
v___x_292_ = lean_apply_1(v_tSide_286_, v_t_289_);
v___x_293_ = lean_unbox(v___x_292_);
if (v___x_293_ == 0)
{
lean_object* v___x_294_; 
v___x_294_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_287_, v_s_288_, v_t_289_);
return v___x_294_;
}
else
{
lean_dec(v_t_289_);
lean_dec_ref(v_s_288_);
lean_dec_ref(v_I_287_);
lean_inc(v___x_285_);
return v___x_285_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6___boxed(lean_object* v_tIn_295_, lean_object* v___x_296_, lean_object* v_tSide_297_, lean_object* v_I_298_, lean_object* v_s_299_, lean_object* v_t_300_){
_start:
{
lean_object* v_res_301_; 
v_res_301_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6(v_tIn_295_, v___x_296_, v_tSide_297_, v_I_298_, v_s_299_, v_t_300_);
lean_dec(v___x_296_);
return v_res_301_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7(lean_object* v_tIn_302_, lean_object* v___x_303_, lean_object* v_tSide_304_, lean_object* v_I_305_, lean_object* v_s_306_, lean_object* v_t_307_){
_start:
{
lean_object* v___x_308_; uint8_t v___x_309_; 
lean_inc(v_t_307_);
v___x_308_ = lean_apply_1(v_tIn_302_, v_t_307_);
v___x_309_ = lean_unbox(v___x_308_);
if (v___x_309_ == 0)
{
lean_dec(v_t_307_);
lean_dec_ref(v_s_306_);
lean_dec_ref(v_I_305_);
lean_dec_ref(v_tSide_304_);
lean_inc(v___x_303_);
return v___x_303_;
}
else
{
lean_object* v___x_310_; uint8_t v___x_311_; 
lean_inc(v_t_307_);
v___x_310_ = lean_apply_1(v_tSide_304_, v_t_307_);
v___x_311_ = lean_unbox(v___x_310_);
if (v___x_311_ == 0)
{
lean_dec(v_t_307_);
lean_dec_ref(v_s_306_);
lean_dec_ref(v_I_305_);
lean_inc(v___x_303_);
return v___x_303_;
}
else
{
lean_object* v___x_312_; 
v___x_312_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_305_, v_s_306_, v_t_307_);
return v___x_312_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7___boxed(lean_object* v_tIn_313_, lean_object* v___x_314_, lean_object* v_tSide_315_, lean_object* v_I_316_, lean_object* v_s_317_, lean_object* v_t_318_){
_start:
{
lean_object* v_res_319_; 
v_res_319_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7(v_tIn_313_, v___x_314_, v_tSide_315_, v_I_316_, v_s_317_, v_t_318_);
lean_dec(v___x_314_);
return v_res_319_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8(lean_object* v_tIn_320_, lean_object* v___x_321_, lean_object* v_tSide_322_, lean_object* v_t_323_){
_start:
{
lean_object* v___x_324_; uint8_t v___x_325_; 
lean_inc(v_t_323_);
v___x_324_ = lean_apply_1(v_tIn_320_, v_t_323_);
v___x_325_ = lean_unbox(v___x_324_);
if (v___x_325_ == 0)
{
lean_dec(v_t_323_);
lean_dec_ref(v_tSide_322_);
lean_inc(v___x_321_);
return v___x_321_;
}
else
{
lean_object* v___x_326_; uint8_t v___x_327_; 
v___x_326_ = lean_apply_1(v_tSide_322_, v_t_323_);
v___x_327_ = lean_unbox(v___x_326_);
if (v___x_327_ == 0)
{
lean_object* v___x_328_; 
v___x_328_ = lean_unsigned_to_nat(1u);
return v___x_328_;
}
else
{
lean_inc(v___x_321_);
return v___x_321_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8___boxed(lean_object* v_tIn_329_, lean_object* v___x_330_, lean_object* v_tSide_331_, lean_object* v_t_332_){
_start:
{
lean_object* v_res_333_; 
v_res_333_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8(v_tIn_329_, v___x_330_, v_tSide_331_, v_t_332_);
lean_dec(v___x_330_);
return v_res_333_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9(lean_object* v_tIn_334_, lean_object* v___x_335_, lean_object* v_tSide_336_, lean_object* v_t_337_){
_start:
{
lean_object* v___x_338_; uint8_t v___x_339_; 
lean_inc(v_t_337_);
v___x_338_ = lean_apply_1(v_tIn_334_, v_t_337_);
v___x_339_ = lean_unbox(v___x_338_);
if (v___x_339_ == 0)
{
lean_dec(v_t_337_);
lean_dec_ref(v_tSide_336_);
lean_inc(v___x_335_);
return v___x_335_;
}
else
{
lean_object* v___x_340_; uint8_t v___x_341_; 
v___x_340_ = lean_apply_1(v_tSide_336_, v_t_337_);
v___x_341_ = lean_unbox(v___x_340_);
if (v___x_341_ == 0)
{
lean_inc(v___x_335_);
return v___x_335_;
}
else
{
lean_object* v___x_342_; 
v___x_342_ = lean_unsigned_to_nat(1u);
return v___x_342_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9___boxed(lean_object* v_tIn_343_, lean_object* v___x_344_, lean_object* v_tSide_345_, lean_object* v_t_346_){
_start:
{
lean_object* v_res_347_; 
v_res_347_ = lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9(v_tIn_343_, v___x_344_, v_tSide_345_, v_t_346_);
lean_dec(v___x_344_);
return v_res_347_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0(lean_object* v_I_348_, lean_object* v_s_349_, lean_object* v___x_350_, uint8_t v___x_351_, lean_object* v_b_352_, lean_object* v_p_353_, lean_object* v_x_354_){
_start:
{
if (lean_obj_tag(v_x_354_) == 0)
{
uint8_t v___x_355_; 
lean_dec(v_p_353_);
lean_dec_ref(v_b_352_);
lean_dec_ref(v___x_350_);
lean_dec_ref(v_s_349_);
lean_dec_ref(v_I_348_);
v___x_355_ = 1;
return v___x_355_;
}
else
{
lean_object* v_head_356_; lean_object* v_tail_357_; uint8_t v___y_359_; lean_object* v___x_361_; lean_object* v___x_362_; uint8_t v___x_363_; 
v_head_356_ = lean_ctor_get(v_x_354_, 0);
lean_inc_n(v_head_356_, 2);
v_tail_357_ = lean_ctor_get(v_x_354_, 1);
lean_inc(v_tail_357_);
lean_dec_ref_known(v_x_354_, 2);
lean_inc_ref(v_s_349_);
v___x_361_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_349_, v_head_356_);
lean_inc_ref(v___x_350_);
lean_inc(v___x_361_);
v___x_362_ = lean_apply_1(v___x_350_, v___x_361_);
v___x_363_ = lean_unbox(v___x_362_);
if (v___x_363_ == 0)
{
lean_dec(v___x_361_);
lean_dec(v_head_356_);
v___y_359_ = v___x_351_;
goto v___jp_358_;
}
else
{
lean_object* v_inA_364_; lean_object* v___x_365_; uint8_t v___x_366_; 
v_inA_364_ = lean_ctor_get(v_b_352_, 3);
lean_inc_ref(v_inA_364_);
v___x_365_ = lean_apply_1(v_inA_364_, v___x_361_);
v___x_366_ = lean_unbox(v___x_365_);
if (v___x_366_ == 0)
{
lean_dec(v_head_356_);
v___y_359_ = v___x_351_;
goto v___jp_358_;
}
else
{
lean_object* v_pkgWeight_367_; lean_object* v___x_368_; lean_object* v___x_369_; uint8_t v___x_370_; 
v_pkgWeight_367_ = lean_ctor_get(v_I_348_, 9);
lean_inc_ref(v_s_349_);
lean_inc_ref(v_I_348_);
v___x_368_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_348_, v_s_349_, v_head_356_);
lean_inc_ref(v_pkgWeight_367_);
lean_inc(v_p_353_);
v___x_369_ = lean_apply_1(v_pkgWeight_367_, v_p_353_);
v___x_370_ = lean_nat_dec_lt(v___x_368_, v___x_369_);
lean_dec(v___x_369_);
lean_dec(v___x_368_);
v___y_359_ = v___x_370_;
goto v___jp_358_;
}
}
v___jp_358_:
{
if (v___y_359_ == 0)
{
lean_dec(v_tail_357_);
lean_dec(v_p_353_);
lean_dec_ref(v_b_352_);
lean_dec_ref(v___x_350_);
lean_dec_ref(v_s_349_);
lean_dec_ref(v_I_348_);
return v___y_359_;
}
else
{
v_x_354_ = v_tail_357_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0___boxed(lean_object* v_I_371_, lean_object* v_s_372_, lean_object* v___x_373_, lean_object* v___x_374_, lean_object* v_b_375_, lean_object* v_p_376_, lean_object* v_x_377_){
_start:
{
uint8_t v___x_2059__boxed_378_; uint8_t v_res_379_; lean_object* v_r_380_; 
v___x_2059__boxed_378_ = lean_unbox(v___x_374_);
v_res_379_ = lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0(v_I_371_, v_s_372_, v___x_373_, v___x_2059__boxed_378_, v_b_375_, v_p_376_, v_x_377_);
v_r_380_ = lean_box(v_res_379_);
return v_r_380_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0(lean_object* v_I_381_, lean_object* v_s_382_, lean_object* v___x_383_, uint8_t v___x_384_, lean_object* v_b_385_, lean_object* v_p_386_, lean_object* v_x_387_){
_start:
{
if (lean_obj_tag(v_x_387_) == 0)
{
uint8_t v___x_388_; 
lean_dec(v_p_386_);
lean_dec_ref(v_b_385_);
lean_dec_ref(v___x_383_);
lean_dec_ref(v_s_382_);
lean_dec_ref(v_I_381_);
v___x_388_ = 1;
return v___x_388_;
}
else
{
lean_object* v_head_389_; lean_object* v_tail_390_; uint8_t v___y_392_; lean_object* v___x_394_; lean_object* v___x_395_; uint8_t v___x_396_; 
v_head_389_ = lean_ctor_get(v_x_387_, 0);
lean_inc_n(v_head_389_, 2);
v_tail_390_ = lean_ctor_get(v_x_387_, 1);
lean_inc(v_tail_390_);
lean_dec_ref_known(v_x_387_, 2);
lean_inc_ref(v_s_382_);
v___x_394_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_382_, v_head_389_);
lean_inc_ref(v___x_383_);
lean_inc(v___x_394_);
v___x_395_ = lean_apply_1(v___x_383_, v___x_394_);
v___x_396_ = lean_unbox(v___x_395_);
if (v___x_396_ == 0)
{
lean_dec(v___x_394_);
lean_dec(v_head_389_);
v___y_392_ = v___x_384_;
goto v___jp_391_;
}
else
{
lean_object* v_inA_397_; lean_object* v___x_398_; uint8_t v___x_399_; 
v_inA_397_ = lean_ctor_get(v_b_385_, 3);
lean_inc_ref(v_inA_397_);
v___x_398_ = lean_apply_1(v_inA_397_, v___x_394_);
v___x_399_ = lean_unbox(v___x_398_);
if (v___x_399_ == 0)
{
lean_dec(v_head_389_);
v___y_392_ = v___x_384_;
goto v___jp_391_;
}
else
{
lean_object* v_pkgWeight_400_; lean_object* v___x_401_; lean_object* v___x_402_; uint8_t v___x_403_; 
v_pkgWeight_400_ = lean_ctor_get(v_I_381_, 9);
lean_inc_ref(v_s_382_);
lean_inc_ref(v_I_381_);
v___x_401_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_381_, v_s_382_, v_head_389_);
lean_inc_ref(v_pkgWeight_400_);
lean_inc(v_p_386_);
v___x_402_ = lean_apply_1(v_pkgWeight_400_, v_p_386_);
v___x_403_ = lean_nat_dec_lt(v___x_401_, v___x_402_);
lean_dec(v___x_402_);
lean_dec(v___x_401_);
v___y_392_ = v___x_403_;
goto v___jp_391_;
}
}
v___jp_391_:
{
if (v___y_392_ == 0)
{
lean_dec(v_tail_390_);
lean_dec(v_p_386_);
lean_dec_ref(v_b_385_);
lean_dec_ref(v___x_383_);
lean_dec_ref(v_s_382_);
lean_dec_ref(v_I_381_);
return v___y_392_;
}
else
{
uint8_t v___x_393_; 
v___x_393_ = lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0_spec__0(v_I_381_, v_s_382_, v___x_383_, v___x_384_, v_b_385_, v_p_386_, v_tail_390_);
return v___x_393_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0___boxed(lean_object* v_I_404_, lean_object* v_s_405_, lean_object* v___x_406_, lean_object* v___x_407_, lean_object* v_b_408_, lean_object* v_p_409_, lean_object* v_x_410_){
_start:
{
uint8_t v___x_2096__boxed_411_; uint8_t v_res_412_; lean_object* v_r_413_; 
v___x_2096__boxed_411_ = lean_unbox(v___x_407_);
v_res_412_ = lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0(v_I_404_, v_s_405_, v___x_406_, v___x_2096__boxed_411_, v_b_408_, v_p_409_, v_x_410_);
v_r_413_ = lean_box(v_res_412_);
return v_r_413_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3(lean_object* v_I_414_, lean_object* v_s_415_, lean_object* v_c__cap_416_, lean_object* v___x_417_, lean_object* v_b_418_, lean_object* v___x_419_, lean_object* v_x_420_){
_start:
{
if (lean_obj_tag(v_x_420_) == 0)
{
uint8_t v___x_421_; 
lean_dec(v___x_419_);
lean_dec_ref(v_b_418_);
lean_dec_ref(v___x_417_);
lean_dec_ref(v_s_415_);
lean_dec_ref(v_I_414_);
v___x_421_ = 0;
return v___x_421_;
}
else
{
lean_object* v_head_422_; lean_object* v_tail_423_; uint8_t v___y_425_; lean_object* v___x_427_; uint8_t v___x_428_; uint8_t v___x_429_; 
v_head_422_ = lean_ctor_get(v_x_420_, 0);
lean_inc_n(v_head_422_, 2);
v_tail_423_ = lean_ctor_get(v_x_420_, 1);
lean_inc(v_tail_423_);
lean_dec_ref_known(v_x_420_, 2);
v___x_427_ = lean_unsigned_to_nat(0u);
v___x_428_ = lean_nat_dec_eq(v_c__cap_416_, v___x_427_);
lean_inc_ref(v_s_415_);
lean_inc_ref(v_I_414_);
v___x_429_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_414_, v_s_415_, v_head_422_);
if (v___x_429_ == 0)
{
uint8_t v___x_430_; 
lean_inc(v_head_422_);
lean_inc_ref(v_s_415_);
v___x_430_ = lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(v_s_415_, v_head_422_);
if (v___x_430_ == 0)
{
lean_dec(v_head_422_);
v___y_425_ = v___x_428_;
goto v___jp_424_;
}
else
{
lean_object* v___x_431_; lean_object* v___x_432_; uint8_t v___x_433_; 
lean_inc(v_head_422_);
lean_inc_ref(v_s_415_);
v___x_431_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_415_, v_head_422_);
lean_inc_ref(v___x_417_);
lean_inc(v___x_431_);
v___x_432_ = lean_apply_1(v___x_417_, v___x_431_);
v___x_433_ = lean_unbox(v___x_432_);
if (v___x_433_ == 0)
{
lean_dec(v___x_431_);
lean_dec(v_head_422_);
v___y_425_ = v___x_428_;
goto v___jp_424_;
}
else
{
lean_object* v_inA_434_; lean_object* v___x_435_; uint8_t v___x_436_; 
v_inA_434_ = lean_ctor_get(v_b_418_, 3);
lean_inc_ref(v_inA_434_);
v___x_435_ = lean_apply_1(v_inA_434_, v___x_431_);
v___x_436_ = lean_unbox(v___x_435_);
if (v___x_436_ == 0)
{
lean_dec(v_head_422_);
v___y_425_ = v___x_428_;
goto v___jp_424_;
}
else
{
lean_object* v___x_437_; uint8_t v___x_438_; uint8_t v___x_439_; 
lean_inc(v___x_419_);
v___x_437_ = l_List_finRange(v___x_419_);
v___x_438_ = lean_unbox(v___x_435_);
lean_inc_ref(v_b_418_);
lean_inc_ref(v___x_417_);
lean_inc_ref(v_s_415_);
lean_inc_ref(v_I_414_);
v___x_439_ = lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__0(v_I_414_, v_s_415_, v___x_417_, v___x_438_, v_b_418_, v_head_422_, v___x_437_);
v___y_425_ = v___x_439_;
goto v___jp_424_;
}
}
}
}
else
{
lean_dec(v_head_422_);
v___y_425_ = v___x_428_;
goto v___jp_424_;
}
v___jp_424_:
{
if (v___y_425_ == 0)
{
v_x_420_ = v_tail_423_;
goto _start;
}
else
{
lean_dec(v_tail_423_);
lean_dec(v___x_419_);
lean_dec_ref(v_b_418_);
lean_dec_ref(v___x_417_);
lean_dec_ref(v_s_415_);
lean_dec_ref(v_I_414_);
return v___y_425_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3___boxed(lean_object* v_I_440_, lean_object* v_s_441_, lean_object* v_c__cap_442_, lean_object* v___x_443_, lean_object* v_b_444_, lean_object* v___x_445_, lean_object* v_x_446_){
_start:
{
uint8_t v_res_447_; lean_object* v_r_448_; 
v_res_447_ = lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3(v_I_440_, v_s_441_, v_c__cap_442_, v___x_443_, v_b_444_, v___x_445_, v_x_446_);
lean_dec(v_c__cap_442_);
v_r_448_ = lean_box(v_res_447_);
return v_r_448_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2(lean_object* v_I_449_, lean_object* v_s_450_, lean_object* v___x_451_, uint8_t v___x_452_, lean_object* v_b_453_, lean_object* v_p_454_, lean_object* v_x_455_){
_start:
{
if (lean_obj_tag(v_x_455_) == 0)
{
uint8_t v___x_456_; 
lean_dec(v_p_454_);
lean_dec_ref(v_b_453_);
lean_dec_ref(v___x_451_);
lean_dec_ref(v_s_450_);
lean_dec_ref(v_I_449_);
v___x_456_ = 1;
return v___x_456_;
}
else
{
lean_object* v_head_457_; lean_object* v_tail_458_; uint8_t v___y_460_; lean_object* v___x_462_; lean_object* v___x_463_; uint8_t v___x_464_; 
v_head_457_ = lean_ctor_get(v_x_455_, 0);
lean_inc_n(v_head_457_, 2);
v_tail_458_ = lean_ctor_get(v_x_455_, 1);
lean_inc(v_tail_458_);
lean_dec_ref_known(v_x_455_, 2);
lean_inc_ref(v_s_450_);
v___x_462_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_450_, v_head_457_);
lean_inc_ref(v___x_451_);
lean_inc(v___x_462_);
v___x_463_ = lean_apply_1(v___x_451_, v___x_462_);
v___x_464_ = lean_unbox(v___x_463_);
if (v___x_464_ == 0)
{
lean_dec(v___x_462_);
lean_dec(v_head_457_);
v___y_460_ = v___x_452_;
goto v___jp_459_;
}
else
{
lean_object* v_inA_465_; lean_object* v___x_466_; uint8_t v___x_467_; 
v_inA_465_ = lean_ctor_get(v_b_453_, 3);
lean_inc_ref(v_inA_465_);
v___x_466_ = lean_apply_1(v_inA_465_, v___x_462_);
v___x_467_ = lean_unbox(v___x_466_);
if (v___x_467_ == 0)
{
lean_object* v_pkgWeight_468_; lean_object* v___x_469_; lean_object* v___x_470_; uint8_t v___x_471_; 
v_pkgWeight_468_ = lean_ctor_get(v_I_449_, 9);
lean_inc_ref(v_s_450_);
lean_inc_ref(v_I_449_);
v___x_469_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_449_, v_s_450_, v_head_457_);
lean_inc_ref(v_pkgWeight_468_);
lean_inc(v_p_454_);
v___x_470_ = lean_apply_1(v_pkgWeight_468_, v_p_454_);
v___x_471_ = lean_nat_dec_lt(v___x_469_, v___x_470_);
lean_dec(v___x_470_);
lean_dec(v___x_469_);
v___y_460_ = v___x_471_;
goto v___jp_459_;
}
else
{
lean_dec(v_head_457_);
v___y_460_ = v___x_452_;
goto v___jp_459_;
}
}
v___jp_459_:
{
if (v___y_460_ == 0)
{
lean_dec(v_tail_458_);
lean_dec(v_p_454_);
lean_dec_ref(v_b_453_);
lean_dec_ref(v___x_451_);
lean_dec_ref(v_s_450_);
lean_dec_ref(v_I_449_);
return v___y_460_;
}
else
{
v_x_455_ = v_tail_458_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2___boxed(lean_object* v_I_472_, lean_object* v_s_473_, lean_object* v___x_474_, lean_object* v___x_475_, lean_object* v_b_476_, lean_object* v_p_477_, lean_object* v_x_478_){
_start:
{
uint8_t v___x_2178__boxed_479_; uint8_t v_res_480_; lean_object* v_r_481_; 
v___x_2178__boxed_479_ = lean_unbox(v___x_475_);
v_res_480_ = lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2(v_I_472_, v_s_473_, v___x_474_, v___x_2178__boxed_479_, v_b_476_, v_p_477_, v_x_478_);
v_r_481_ = lean_box(v_res_480_);
return v_r_481_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1(lean_object* v_I_482_, lean_object* v_s_483_, lean_object* v___x_484_, uint8_t v___x_485_, lean_object* v_b_486_, lean_object* v_p_487_, lean_object* v_x_488_){
_start:
{
if (lean_obj_tag(v_x_488_) == 0)
{
uint8_t v___x_489_; 
lean_dec(v_p_487_);
lean_dec_ref(v_b_486_);
lean_dec_ref(v___x_484_);
lean_dec_ref(v_s_483_);
lean_dec_ref(v_I_482_);
v___x_489_ = 1;
return v___x_489_;
}
else
{
lean_object* v_head_490_; lean_object* v_tail_491_; uint8_t v___y_493_; lean_object* v___x_495_; lean_object* v___x_496_; uint8_t v___x_497_; 
v_head_490_ = lean_ctor_get(v_x_488_, 0);
lean_inc_n(v_head_490_, 2);
v_tail_491_ = lean_ctor_get(v_x_488_, 1);
lean_inc(v_tail_491_);
lean_dec_ref_known(v_x_488_, 2);
lean_inc_ref(v_s_483_);
v___x_495_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_483_, v_head_490_);
lean_inc_ref(v___x_484_);
lean_inc(v___x_495_);
v___x_496_ = lean_apply_1(v___x_484_, v___x_495_);
v___x_497_ = lean_unbox(v___x_496_);
if (v___x_497_ == 0)
{
lean_dec(v___x_495_);
lean_dec(v_head_490_);
v___y_493_ = v___x_485_;
goto v___jp_492_;
}
else
{
lean_object* v_inA_498_; lean_object* v___x_499_; uint8_t v___x_500_; 
v_inA_498_ = lean_ctor_get(v_b_486_, 3);
lean_inc_ref(v_inA_498_);
v___x_499_ = lean_apply_1(v_inA_498_, v___x_495_);
v___x_500_ = lean_unbox(v___x_499_);
if (v___x_500_ == 0)
{
lean_object* v_pkgWeight_501_; lean_object* v___x_502_; lean_object* v___x_503_; uint8_t v___x_504_; 
v_pkgWeight_501_ = lean_ctor_get(v_I_482_, 9);
lean_inc_ref(v_s_483_);
lean_inc_ref(v_I_482_);
v___x_502_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_482_, v_s_483_, v_head_490_);
lean_inc_ref(v_pkgWeight_501_);
lean_inc(v_p_487_);
v___x_503_ = lean_apply_1(v_pkgWeight_501_, v_p_487_);
v___x_504_ = lean_nat_dec_lt(v___x_502_, v___x_503_);
lean_dec(v___x_503_);
lean_dec(v___x_502_);
v___y_493_ = v___x_504_;
goto v___jp_492_;
}
else
{
lean_dec(v_head_490_);
v___y_493_ = v___x_485_;
goto v___jp_492_;
}
}
v___jp_492_:
{
if (v___y_493_ == 0)
{
lean_dec(v_tail_491_);
lean_dec(v_p_487_);
lean_dec_ref(v_b_486_);
lean_dec_ref(v___x_484_);
lean_dec_ref(v_s_483_);
lean_dec_ref(v_I_482_);
return v___y_493_;
}
else
{
uint8_t v___x_494_; 
v___x_494_ = lp_island__logistics__proof_List_all___at___00List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1_spec__2(v_I_482_, v_s_483_, v___x_484_, v___x_485_, v_b_486_, v_p_487_, v_tail_491_);
return v___x_494_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1___boxed(lean_object* v_I_505_, lean_object* v_s_506_, lean_object* v___x_507_, lean_object* v___x_508_, lean_object* v_b_509_, lean_object* v_p_510_, lean_object* v_x_511_){
_start:
{
uint8_t v___x_2215__boxed_512_; uint8_t v_res_513_; lean_object* v_r_514_; 
v___x_2215__boxed_512_ = lean_unbox(v___x_508_);
v_res_513_ = lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1(v_I_505_, v_s_506_, v___x_507_, v___x_2215__boxed_512_, v_b_509_, v_p_510_, v_x_511_);
v_r_514_ = lean_box(v_res_513_);
return v_r_514_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2(lean_object* v_I_515_, lean_object* v_s_516_, lean_object* v_c__cap_517_, lean_object* v___x_518_, lean_object* v_b_519_, lean_object* v___x_520_, lean_object* v_x_521_){
_start:
{
if (lean_obj_tag(v_x_521_) == 0)
{
uint8_t v___x_522_; 
lean_dec(v___x_520_);
lean_dec_ref(v_b_519_);
lean_dec_ref(v___x_518_);
lean_dec_ref(v_s_516_);
lean_dec_ref(v_I_515_);
v___x_522_ = 0;
return v___x_522_;
}
else
{
lean_object* v_head_523_; lean_object* v_tail_524_; uint8_t v___y_526_; lean_object* v___x_528_; uint8_t v___x_529_; uint8_t v___x_530_; 
v_head_523_ = lean_ctor_get(v_x_521_, 0);
lean_inc_n(v_head_523_, 2);
v_tail_524_ = lean_ctor_get(v_x_521_, 1);
lean_inc(v_tail_524_);
lean_dec_ref_known(v_x_521_, 2);
v___x_528_ = lean_unsigned_to_nat(0u);
v___x_529_ = lean_nat_dec_eq(v_c__cap_517_, v___x_528_);
lean_inc_ref(v_s_516_);
lean_inc_ref(v_I_515_);
v___x_530_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_515_, v_s_516_, v_head_523_);
if (v___x_530_ == 0)
{
uint8_t v___x_531_; 
lean_inc(v_head_523_);
lean_inc_ref(v_s_516_);
v___x_531_ = lp_island__logistics__proof_IslandLogistics_State_pkgIsGround___redArg(v_s_516_, v_head_523_);
if (v___x_531_ == 0)
{
lean_dec(v_head_523_);
v___y_526_ = v___x_529_;
goto v___jp_525_;
}
else
{
lean_object* v___x_532_; lean_object* v___x_533_; uint8_t v___x_534_; 
lean_inc(v_head_523_);
lean_inc_ref(v_s_516_);
v___x_532_ = lp_island__logistics__proof_IslandLogistics_State_pkgPhysLoc___redArg(v_s_516_, v_head_523_);
lean_inc_ref(v___x_518_);
lean_inc(v___x_532_);
v___x_533_ = lean_apply_1(v___x_518_, v___x_532_);
v___x_534_ = lean_unbox(v___x_533_);
if (v___x_534_ == 0)
{
lean_dec(v___x_532_);
lean_dec(v_head_523_);
v___y_526_ = v___x_529_;
goto v___jp_525_;
}
else
{
lean_object* v_inA_535_; lean_object* v___x_536_; uint8_t v___x_537_; 
v_inA_535_ = lean_ctor_get(v_b_519_, 3);
lean_inc_ref(v_inA_535_);
v___x_536_ = lean_apply_1(v_inA_535_, v___x_532_);
v___x_537_ = lean_unbox(v___x_536_);
if (v___x_537_ == 0)
{
lean_object* v___x_538_; uint8_t v___x_539_; uint8_t v___x_540_; 
lean_inc(v___x_520_);
v___x_538_ = l_List_finRange(v___x_520_);
v___x_539_ = lean_unbox(v___x_533_);
lean_inc_ref(v_b_519_);
lean_inc_ref(v___x_518_);
lean_inc_ref(v_s_516_);
lean_inc_ref(v_I_515_);
v___x_540_ = lp_island__logistics__proof_List_all___at___00IslandLogistics_bridgeEdgeFlux_spec__1(v_I_515_, v_s_516_, v___x_518_, v___x_539_, v_b_519_, v_head_523_, v___x_538_);
v___y_526_ = v___x_540_;
goto v___jp_525_;
}
else
{
lean_dec(v_head_523_);
v___y_526_ = v___x_529_;
goto v___jp_525_;
}
}
}
}
else
{
lean_dec(v_head_523_);
v___y_526_ = v___x_529_;
goto v___jp_525_;
}
v___jp_525_:
{
if (v___y_526_ == 0)
{
v_x_521_ = v_tail_524_;
goto _start;
}
else
{
lean_dec(v_tail_524_);
lean_dec(v___x_520_);
lean_dec_ref(v_b_519_);
lean_dec_ref(v___x_518_);
lean_dec_ref(v_s_516_);
lean_dec_ref(v_I_515_);
return v___y_526_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2___boxed(lean_object* v_I_541_, lean_object* v_s_542_, lean_object* v_c__cap_543_, lean_object* v___x_544_, lean_object* v_b_545_, lean_object* v___x_546_, lean_object* v_x_547_){
_start:
{
uint8_t v_res_548_; lean_object* v_r_549_; 
v_res_548_ = lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2(v_I_541_, v_s_542_, v_c__cap_543_, v___x_544_, v_b_545_, v___x_546_, v_x_547_);
lean_dec(v_c__cap_543_);
v_r_549_ = lean_box(v_res_548_);
return v_r_549_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux(lean_object* v_I_552_, lean_object* v_s_553_, lean_object* v_b_554_){
_start:
{
lean_object* v_inComp_555_; lean_object* v_inA_556_; lean_object* v_c__cap_557_; lean_object* v___x_558_; uint8_t v___x_559_; 
v_inComp_555_ = lean_ctor_get(v_b_554_, 2);
lean_inc_ref_n(v_inComp_555_, 2);
v_inA_556_ = lean_ctor_get(v_b_554_, 3);
lean_inc_ref(v_s_553_);
lean_inc_ref(v_I_552_);
v_c__cap_557_ = lp_island__logistics__proof_IslandLogistics_compMaxEffCap(v_I_552_, v_s_553_, v_inComp_555_);
v___x_558_ = lean_unsigned_to_nat(0u);
v___x_559_ = lean_nat_dec_eq(v_c__cap_557_, v___x_558_);
if (v___x_559_ == 0)
{
lean_object* v_numTrucks_560_; lean_object* v_numPkgs_561_; lean_object* v_pkgWeight_562_; lean_object* v_pkgGoal_563_; lean_object* v_tSide_564_; lean_object* v_tIn_565_; lean_object* v___f_566_; lean_object* v___f_567_; lean_object* v___f_568_; lean_object* v___f_569_; lean_object* v___f_570_; lean_object* v___f_571_; lean_object* v___f_572_; lean_object* v___f_573_; lean_object* v_m__a_574_; lean_object* v_m__b_575_; lean_object* v_c__a_576_; lean_object* v_c__b_577_; lean_object* v_w__ab_578_; lean_object* v_w__ba_579_; lean_object* v_h__ab_580_; lean_object* v_h__ba_581_; lean_object* v___x_582_; uint8_t v_need__ab_583_; uint8_t v_need__ba_584_; lean_object* v___x_585_; 
v_numTrucks_560_ = lean_ctor_get(v_I_552_, 3);
lean_inc_n(v_numTrucks_560_, 6);
v_numPkgs_561_ = lean_ctor_get(v_I_552_, 8);
v_pkgWeight_562_ = lean_ctor_get(v_I_552_, 9);
v_pkgGoal_563_ = lean_ctor_get(v_I_552_, 10);
lean_inc_ref_n(v_inA_556_, 5);
lean_inc_ref_n(v_s_553_, 9);
v_tSide_564_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__0___boxed), 3, 2);
lean_closure_set(v_tSide_564_, 0, v_s_553_);
lean_closure_set(v_tSide_564_, 1, v_inA_556_);
lean_inc_ref_n(v_inComp_555_, 6);
v_tIn_565_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__1___boxed), 3, 2);
lean_closure_set(v_tIn_565_, 0, v_s_553_);
lean_closure_set(v_tIn_565_, 1, v_inComp_555_);
lean_inc_ref_n(v_pkgWeight_562_, 4);
lean_inc_n(v_c__cap_557_, 2);
lean_inc_ref_n(v_pkgGoal_563_, 4);
lean_inc_ref_n(v_I_552_, 7);
v___f_566_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__2___boxed), 9, 8);
lean_closure_set(v___f_566_, 0, v_I_552_);
lean_closure_set(v___f_566_, 1, v_s_553_);
lean_closure_set(v___f_566_, 2, v_inComp_555_);
lean_closure_set(v___f_566_, 3, v___x_558_);
lean_closure_set(v___f_566_, 4, v_inA_556_);
lean_closure_set(v___f_566_, 5, v_pkgGoal_563_);
lean_closure_set(v___f_566_, 6, v_c__cap_557_);
lean_closure_set(v___f_566_, 7, v_pkgWeight_562_);
v___f_567_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__3___boxed), 9, 8);
lean_closure_set(v___f_567_, 0, v_I_552_);
lean_closure_set(v___f_567_, 1, v_s_553_);
lean_closure_set(v___f_567_, 2, v_inComp_555_);
lean_closure_set(v___f_567_, 3, v___x_558_);
lean_closure_set(v___f_567_, 4, v_inA_556_);
lean_closure_set(v___f_567_, 5, v_pkgGoal_563_);
lean_closure_set(v___f_567_, 6, v_c__cap_557_);
lean_closure_set(v___f_567_, 7, v_pkgWeight_562_);
v___f_568_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__4___boxed), 8, 7);
lean_closure_set(v___f_568_, 0, v_I_552_);
lean_closure_set(v___f_568_, 1, v_s_553_);
lean_closure_set(v___f_568_, 2, v_inComp_555_);
lean_closure_set(v___f_568_, 3, v___x_558_);
lean_closure_set(v___f_568_, 4, v_inA_556_);
lean_closure_set(v___f_568_, 5, v_pkgGoal_563_);
lean_closure_set(v___f_568_, 6, v_pkgWeight_562_);
v___f_569_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__5___boxed), 8, 7);
lean_closure_set(v___f_569_, 0, v_I_552_);
lean_closure_set(v___f_569_, 1, v_s_553_);
lean_closure_set(v___f_569_, 2, v_inComp_555_);
lean_closure_set(v___f_569_, 3, v___x_558_);
lean_closure_set(v___f_569_, 4, v_inA_556_);
lean_closure_set(v___f_569_, 5, v_pkgGoal_563_);
lean_closure_set(v___f_569_, 6, v_pkgWeight_562_);
lean_inc_ref_n(v_tSide_564_, 3);
lean_inc_ref_n(v_tIn_565_, 3);
v___f_570_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__6___boxed), 6, 5);
lean_closure_set(v___f_570_, 0, v_tIn_565_);
lean_closure_set(v___f_570_, 1, v___x_558_);
lean_closure_set(v___f_570_, 2, v_tSide_564_);
lean_closure_set(v___f_570_, 3, v_I_552_);
lean_closure_set(v___f_570_, 4, v_s_553_);
v___f_571_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__7___boxed), 6, 5);
lean_closure_set(v___f_571_, 0, v_tIn_565_);
lean_closure_set(v___f_571_, 1, v___x_558_);
lean_closure_set(v___f_571_, 2, v_tSide_564_);
lean_closure_set(v___f_571_, 3, v_I_552_);
lean_closure_set(v___f_571_, 4, v_s_553_);
v___f_572_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__8___boxed), 4, 3);
lean_closure_set(v___f_572_, 0, v_tIn_565_);
lean_closure_set(v___f_572_, 1, v___x_558_);
lean_closure_set(v___f_572_, 2, v_tSide_564_);
v___f_573_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___lam__9___boxed), 4, 3);
lean_closure_set(v___f_573_, 0, v_tIn_565_);
lean_closure_set(v___f_573_, 1, v___x_558_);
lean_closure_set(v___f_573_, 2, v_tSide_564_);
v_m__a_574_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_560_, v___f_573_);
v_m__b_575_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_560_, v___f_572_);
v_c__a_576_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_560_, v___f_571_);
v_c__b_577_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_560_, v___f_570_);
lean_inc_n(v_numPkgs_561_, 5);
v_w__ab_578_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_561_, v___f_569_);
v_w__ba_579_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_561_, v___f_568_);
v_h__ab_580_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_561_, v___f_567_);
v_h__ba_581_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_561_, v___f_566_);
v___x_582_ = l_List_finRange(v_numPkgs_561_);
lean_inc(v___x_582_);
lean_inc_ref(v_b_554_);
v_need__ab_583_ = lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__2(v_I_552_, v_s_553_, v_c__cap_557_, v_inComp_555_, v_b_554_, v_numTrucks_560_, v___x_582_);
v_need__ba_584_ = lp_island__logistics__proof_List_any___at___00IslandLogistics_bridgeEdgeFlux_spec__3(v_I_552_, v_s_553_, v_c__cap_557_, v_inComp_555_, v_b_554_, v_numTrucks_560_, v___x_582_);
v___x_585_ = lp_island__logistics__proof_IslandLogistics_fluxLB(v_w__ab_578_, v_w__ba_579_, v_h__ab_580_, v_h__ba_581_, v_need__ab_583_, v_need__ba_584_, v_m__a_574_, v_m__b_575_, v_c__a_576_, v_c__b_577_, v_c__cap_557_);
lean_dec(v_c__cap_557_);
lean_dec(v_c__b_577_);
lean_dec(v_c__a_576_);
lean_dec(v_m__b_575_);
lean_dec(v_m__a_574_);
lean_dec(v_w__ba_579_);
lean_dec(v_w__ab_578_);
return v___x_585_;
}
else
{
lean_object* v___x_586_; 
lean_dec(v_c__cap_557_);
lean_dec_ref(v_inComp_555_);
lean_dec_ref(v_b_554_);
lean_dec_ref(v_s_553_);
lean_dec_ref(v_I_552_);
v___x_586_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_bridgeEdgeFlux___closed__0));
return v___x_586_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_stateAt_spec__0(lean_object* v_I_587_, lean_object* v_x_588_, lean_object* v_x_589_){
_start:
{
if (lean_obj_tag(v_x_589_) == 0)
{
lean_dec_ref(v_I_587_);
return v_x_588_;
}
else
{
lean_object* v_head_590_; lean_object* v_tail_591_; lean_object* v___x_592_; 
v_head_590_ = lean_ctor_get(v_x_589_, 0);
lean_inc(v_head_590_);
v_tail_591_ = lean_ctor_get(v_x_589_, 1);
lean_inc(v_tail_591_);
lean_dec_ref_known(v_x_589_, 2);
lean_inc_ref(v_I_587_);
v___x_592_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_587_, v_x_588_, v_head_590_);
v_x_588_ = v___x_592_;
v_x_589_ = v_tail_591_;
goto _start;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stateAt(lean_object* v_I_596_, lean_object* v_s_597_, lean_object* v_00_u03c0_598_, lean_object* v_k_599_){
_start:
{
lean_object* v___x_600_; lean_object* v___x_601_; lean_object* v___x_602_; 
v___x_600_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_stateAt___closed__0));
lean_inc(v_00_u03c0_598_);
v___x_601_ = l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(v_00_u03c0_598_, v_00_u03c0_598_, v_k_599_, v___x_600_);
lean_dec(v_00_u03c0_598_);
v___x_602_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_stateAt_spec__0(v_I_596_, v_s_597_, v___x_601_);
return v___x_602_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep___redArg(lean_object* v_pred_603_, lean_object* v_x_604_){
_start:
{
if (lean_obj_tag(v_x_604_) == 0)
{
lean_object* v___x_605_; 
lean_dec_ref(v_pred_603_);
v___x_605_ = lean_unsigned_to_nat(0u);
return v___x_605_;
}
else
{
lean_object* v_head_606_; lean_object* v_tail_607_; lean_object* v___x_608_; uint8_t v___x_609_; 
v_head_606_ = lean_ctor_get(v_x_604_, 0);
lean_inc(v_head_606_);
v_tail_607_ = lean_ctor_get(v_x_604_, 1);
lean_inc(v_tail_607_);
lean_dec_ref_known(v_x_604_, 2);
lean_inc_ref(v_pred_603_);
v___x_608_ = lean_apply_1(v_pred_603_, v_head_606_);
v___x_609_ = lean_unbox(v___x_608_);
if (v___x_609_ == 0)
{
lean_object* v___x_610_; lean_object* v___x_611_; lean_object* v___x_612_; 
v___x_610_ = lean_unsigned_to_nat(1u);
v___x_611_ = lp_island__logistics__proof_IslandLogistics_firstStep___redArg(v_pred_603_, v_tail_607_);
v___x_612_ = lean_nat_add(v___x_610_, v___x_611_);
lean_dec(v___x_611_);
return v___x_612_;
}
else
{
lean_object* v___x_613_; 
lean_dec(v_tail_607_);
lean_dec_ref(v_pred_603_);
v___x_613_ = lean_unsigned_to_nat(0u);
return v___x_613_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep(lean_object* v_I_614_, lean_object* v_pred_615_, lean_object* v_x_616_){
_start:
{
lean_object* v___x_617_; 
v___x_617_ = lp_island__logistics__proof_IslandLogistics_firstStep___redArg(v_pred_615_, v_x_616_);
return v___x_617_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_firstStep___boxed(lean_object* v_I_618_, lean_object* v_pred_619_, lean_object* v_x_620_){
_start:
{
lean_object* v_res_621_; 
v_res_621_ = lp_island__logistics__proof_IslandLogistics_firstStep(v_I_618_, v_pred_619_, v_x_620_);
lean_dec_ref(v_I_618_);
return v_res_621_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object* v_x_622_, lean_object* v_h__1_623_, lean_object* v_h__2_624_){
_start:
{
if (lean_obj_tag(v_x_622_) == 0)
{
lean_object* v_l_625_; lean_object* v___x_626_; 
lean_dec(v_h__2_624_);
v_l_625_ = lean_ctor_get(v_x_622_, 0);
lean_inc(v_l_625_);
lean_dec_ref_known(v_x_622_, 1);
v___x_626_ = lean_apply_1(v_h__1_623_, v_l_625_);
return v___x_626_;
}
else
{
lean_object* v_t_627_; lean_object* v___x_628_; 
lean_dec(v_h__1_623_);
v_t_627_ = lean_ctor_get(v_x_622_, 0);
lean_inc(v_t_627_);
lean_dec_ref_known(v_x_622_, 1);
v___x_628_ = lean_apply_1(v_h__2_624_, v_t_627_);
return v___x_628_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object* v_I_629_, lean_object* v_motive_630_, lean_object* v_x_631_, lean_object* v_h__1_632_, lean_object* v_h__2_633_){
_start:
{
if (lean_obj_tag(v_x_631_) == 0)
{
lean_object* v_l_634_; lean_object* v___x_635_; 
lean_dec(v_h__2_633_);
v_l_634_ = lean_ctor_get(v_x_631_, 0);
lean_inc(v_l_634_);
lean_dec_ref_known(v_x_631_, 1);
v___x_635_ = lean_apply_1(v_h__1_632_, v_l_634_);
return v___x_635_;
}
else
{
lean_object* v_t_636_; lean_object* v___x_637_; 
lean_dec(v_h__1_632_);
v_t_636_ = lean_ctor_get(v_x_631_, 0);
lean_inc(v_t_636_);
lean_dec_ref_known(v_x_631_, 1);
v___x_637_ = lean_apply_1(v_h__2_633_, v_t_636_);
return v___x_637_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object* v_I_638_, lean_object* v_motive_639_, lean_object* v_x_640_, lean_object* v_h__1_641_, lean_object* v_h__2_642_){
_start:
{
lean_object* v_res_643_; 
v_res_643_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_planPkgCrossAB_match__1_splitter(v_I_638_, v_motive_639_, v_x_640_, v_h__1_641_, v_h__2_642_);
lean_dec_ref(v_I_638_);
return v_res_643_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg(lean_object* v_C_644_, lean_object* v_x_645_){
_start:
{
if (lean_obj_tag(v_x_645_) == 0)
{
lean_object* v_u_646_; lean_object* v_v_647_; lean_object* v_isBridge_648_; lean_object* v___x_649_; uint8_t v___x_650_; 
v_u_646_ = lean_ctor_get(v_x_645_, 1);
lean_inc(v_u_646_);
v_v_647_ = lean_ctor_get(v_x_645_, 2);
lean_inc(v_v_647_);
lean_dec_ref_known(v_x_645_, 3);
v_isBridge_648_ = lean_ctor_get(v_C_644_, 3);
lean_inc_ref(v_isBridge_648_);
lean_dec_ref(v_C_644_);
v___x_649_ = lean_apply_2(v_isBridge_648_, v_u_646_, v_v_647_);
v___x_650_ = lean_unbox(v___x_649_);
if (v___x_650_ == 0)
{
uint8_t v___x_651_; 
v___x_651_ = 1;
return v___x_651_;
}
else
{
uint8_t v___x_652_; 
v___x_652_ = 0;
return v___x_652_;
}
}
else
{
uint8_t v___x_653_; 
lean_dec_ref(v_x_645_);
lean_dec_ref(v_C_644_);
v___x_653_ = 0;
return v___x_653_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg___boxed(lean_object* v_C_654_, lean_object* v_x_655_){
_start:
{
uint8_t v_res_656_; lean_object* v_r_657_; 
v_res_656_ = lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg(v_C_654_, v_x_655_);
v_r_657_ = lean_box(v_res_656_);
return v_r_657_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive(lean_object* v_I_658_, lean_object* v_C_659_, lean_object* v_x_660_){
_start:
{
uint8_t v___x_661_; 
v___x_661_ = lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___redArg(v_C_659_, v_x_660_);
return v___x_661_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___boxed(lean_object* v_I_662_, lean_object* v_C_663_, lean_object* v_x_664_){
_start:
{
uint8_t v_res_665_; lean_object* v_r_666_; 
v_res_665_ = lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive(v_I_662_, v_C_663_, v_x_664_);
lean_dec_ref(v_I_662_);
v_r_666_ = lean_box(v_res_665_);
return v_r_666_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_costNonBridgeDrive(lean_object* v_I_667_, lean_object* v_C_668_, lean_object* v_00_u03c0_669_){
_start:
{
lean_object* v___x_670_; lean_object* v___x_671_; 
v___x_670_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_isNonBridgeDrive___boxed), 3, 2);
lean_closure_set(v___x_670_, 0, v_I_667_);
lean_closure_set(v___x_670_, 1, v_C_668_);
v___x_671_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v___x_670_, v_00_u03c0_669_);
return v___x_671_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_primStep___lam__0(lean_object* v_used_672_, lean_object* v_fst_673_, lean_object* v_i_674_){
_start:
{
lean_object* v___x_675_; uint8_t v___x_676_; 
lean_inc(v_i_674_);
v___x_675_ = lean_apply_1(v_used_672_, v_i_674_);
v___x_676_ = lean_unbox(v___x_675_);
if (v___x_676_ == 0)
{
uint8_t v___x_677_; 
v___x_677_ = lean_nat_dec_eq(v_i_674_, v_fst_673_);
lean_dec(v_i_674_);
return v___x_677_;
}
else
{
uint8_t v___x_678_; 
lean_dec(v_i_674_);
v___x_678_ = lean_unbox(v___x_675_);
return v___x_678_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep___lam__0___boxed(lean_object* v_used_679_, lean_object* v_fst_680_, lean_object* v_i_681_){
_start:
{
uint8_t v_res_682_; lean_object* v_r_683_; 
v_res_682_ = lp_island__logistics__proof_IslandLogistics_primStep___lam__0(v_used_679_, v_fst_680_, v_i_681_);
lean_dec(v_fst_680_);
v_r_683_ = lean_box(v_res_682_);
return v_r_683_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep___lam__1(lean_object* v_used_x27_684_, lean_object* v_minE_685_, lean_object* v_dist_686_, lean_object* v_fst_687_, lean_object* v_i_688_){
_start:
{
lean_object* v___x_689_; uint8_t v___x_690_; 
lean_inc(v_i_688_);
v___x_689_ = lean_apply_1(v_used_x27_684_, v_i_688_);
v___x_690_ = lean_unbox(v___x_689_);
if (v___x_690_ == 0)
{
lean_object* v___x_691_; lean_object* v___x_692_; uint8_t v___x_693_; 
lean_inc(v_i_688_);
v___x_691_ = lean_apply_1(v_minE_685_, v_i_688_);
v___x_692_ = lean_apply_2(v_dist_686_, v_fst_687_, v_i_688_);
v___x_693_ = lean_nat_dec_le(v___x_691_, v___x_692_);
if (v___x_693_ == 0)
{
lean_dec(v___x_691_);
return v___x_692_;
}
else
{
lean_dec(v___x_692_);
return v___x_691_;
}
}
else
{
lean_object* v___x_694_; 
lean_dec(v_fst_687_);
lean_dec_ref(v_dist_686_);
v___x_694_ = lean_apply_1(v_minE_685_, v_i_688_);
return v___x_694_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_primStep_spec__0(lean_object* v_used_695_, lean_object* v_minE_696_, lean_object* v_x_697_, lean_object* v_x_698_){
_start:
{
if (lean_obj_tag(v_x_698_) == 0)
{
lean_dec_ref(v_minE_696_);
lean_dec_ref(v_used_695_);
return v_x_697_;
}
else
{
lean_object* v_head_699_; lean_object* v_tail_700_; lean_object* v___x_702_; uint8_t v_isShared_703_; uint8_t v_isSharedCheck_735_; 
v_head_699_ = lean_ctor_get(v_x_698_, 0);
v_tail_700_ = lean_ctor_get(v_x_698_, 1);
v_isSharedCheck_735_ = !lean_is_exclusive(v_x_698_);
if (v_isSharedCheck_735_ == 0)
{
v___x_702_ = v_x_698_;
v_isShared_703_ = v_isSharedCheck_735_;
goto v_resetjp_701_;
}
else
{
lean_inc(v_tail_700_);
lean_inc(v_head_699_);
lean_dec(v_x_698_);
v___x_702_ = lean_box(0);
v_isShared_703_ = v_isSharedCheck_735_;
goto v_resetjp_701_;
}
v_resetjp_701_:
{
lean_object* v___x_704_; uint8_t v___x_705_; 
lean_inc_ref(v_used_695_);
lean_inc(v_head_699_);
v___x_704_ = lean_apply_1(v_used_695_, v_head_699_);
v___x_705_ = lean_unbox(v___x_704_);
if (v___x_705_ == 0)
{
if (lean_obj_tag(v_x_697_) == 0)
{
lean_object* v___x_706_; lean_object* v___x_708_; 
lean_inc_ref(v_minE_696_);
lean_inc(v_head_699_);
v___x_706_ = lean_apply_1(v_minE_696_, v_head_699_);
if (v_isShared_703_ == 0)
{
lean_ctor_set_tag(v___x_702_, 0);
lean_ctor_set(v___x_702_, 1, v___x_706_);
v___x_708_ = v___x_702_;
goto v_reusejp_707_;
}
else
{
lean_object* v_reuseFailAlloc_711_; 
v_reuseFailAlloc_711_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_711_, 0, v_head_699_);
lean_ctor_set(v_reuseFailAlloc_711_, 1, v___x_706_);
v___x_708_ = v_reuseFailAlloc_711_;
goto v_reusejp_707_;
}
v_reusejp_707_:
{
lean_object* v___x_709_; 
v___x_709_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_709_, 0, v___x_708_);
v_x_697_ = v___x_709_;
v_x_698_ = v_tail_700_;
goto _start;
}
}
else
{
lean_object* v_val_712_; lean_object* v_snd_713_; lean_object* v___x_715_; uint8_t v_isShared_716_; uint8_t v_isSharedCheck_732_; 
lean_del_object(v___x_702_);
v_val_712_ = lean_ctor_get(v_x_697_, 0);
lean_inc(v_val_712_);
v_snd_713_ = lean_ctor_get(v_val_712_, 1);
v_isSharedCheck_732_ = !lean_is_exclusive(v_val_712_);
if (v_isSharedCheck_732_ == 0)
{
lean_object* v_unused_733_; 
v_unused_733_ = lean_ctor_get(v_val_712_, 0);
lean_dec(v_unused_733_);
v___x_715_ = v_val_712_;
v_isShared_716_ = v_isSharedCheck_732_;
goto v_resetjp_714_;
}
else
{
lean_inc(v_snd_713_);
lean_dec(v_val_712_);
v___x_715_ = lean_box(0);
v_isShared_716_ = v_isSharedCheck_732_;
goto v_resetjp_714_;
}
v_resetjp_714_:
{
lean_object* v___x_717_; uint8_t v___x_718_; 
lean_inc_ref(v_minE_696_);
lean_inc(v_head_699_);
v___x_717_ = lean_apply_1(v_minE_696_, v_head_699_);
v___x_718_ = lean_nat_dec_lt(v___x_717_, v_snd_713_);
lean_dec(v_snd_713_);
if (v___x_718_ == 0)
{
lean_dec(v___x_717_);
lean_del_object(v___x_715_);
lean_dec(v_head_699_);
v_x_698_ = v_tail_700_;
goto _start;
}
else
{
lean_object* v___x_721_; uint8_t v_isShared_722_; uint8_t v_isSharedCheck_730_; 
v_isSharedCheck_730_ = !lean_is_exclusive(v_x_697_);
if (v_isSharedCheck_730_ == 0)
{
lean_object* v_unused_731_; 
v_unused_731_ = lean_ctor_get(v_x_697_, 0);
lean_dec(v_unused_731_);
v___x_721_ = v_x_697_;
v_isShared_722_ = v_isSharedCheck_730_;
goto v_resetjp_720_;
}
else
{
lean_dec(v_x_697_);
v___x_721_ = lean_box(0);
v_isShared_722_ = v_isSharedCheck_730_;
goto v_resetjp_720_;
}
v_resetjp_720_:
{
lean_object* v___x_724_; 
if (v_isShared_716_ == 0)
{
lean_ctor_set(v___x_715_, 1, v___x_717_);
lean_ctor_set(v___x_715_, 0, v_head_699_);
v___x_724_ = v___x_715_;
goto v_reusejp_723_;
}
else
{
lean_object* v_reuseFailAlloc_729_; 
v_reuseFailAlloc_729_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_729_, 0, v_head_699_);
lean_ctor_set(v_reuseFailAlloc_729_, 1, v___x_717_);
v___x_724_ = v_reuseFailAlloc_729_;
goto v_reusejp_723_;
}
v_reusejp_723_:
{
lean_object* v___x_726_; 
if (v_isShared_722_ == 0)
{
lean_ctor_set(v___x_721_, 0, v___x_724_);
v___x_726_ = v___x_721_;
goto v_reusejp_725_;
}
else
{
lean_object* v_reuseFailAlloc_728_; 
v_reuseFailAlloc_728_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_728_, 0, v___x_724_);
v___x_726_ = v_reuseFailAlloc_728_;
goto v_reusejp_725_;
}
v_reusejp_725_:
{
v_x_697_ = v___x_726_;
v_x_698_ = v_tail_700_;
goto _start;
}
}
}
}
}
}
}
else
{
lean_del_object(v___x_702_);
lean_dec(v_head_699_);
v_x_698_ = v_tail_700_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primStep(lean_object* v_m_736_, lean_object* v_dist_737_, lean_object* v_used_738_, lean_object* v_minE_739_){
_start:
{
lean_object* v___x_740_; lean_object* v___x_741_; lean_object* v_best_x3f_742_; 
v___x_740_ = lean_box(0);
v___x_741_ = l_List_finRange(v_m_736_);
lean_inc_ref(v_minE_739_);
lean_inc_ref(v_used_738_);
v_best_x3f_742_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_primStep_spec__0(v_used_738_, v_minE_739_, v___x_740_, v___x_741_);
if (lean_obj_tag(v_best_x3f_742_) == 0)
{
lean_object* v___x_743_; lean_object* v___x_744_; lean_object* v___x_745_; 
lean_dec_ref(v_dist_737_);
v___x_743_ = lean_unsigned_to_nat(0u);
v___x_744_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_744_, 0, v_minE_739_);
lean_ctor_set(v___x_744_, 1, v___x_743_);
v___x_745_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_745_, 0, v_used_738_);
lean_ctor_set(v___x_745_, 1, v___x_744_);
return v___x_745_;
}
else
{
lean_object* v_val_746_; lean_object* v_fst_747_; lean_object* v_snd_748_; lean_object* v___x_750_; uint8_t v_isShared_751_; uint8_t v_isSharedCheck_758_; 
v_val_746_ = lean_ctor_get(v_best_x3f_742_, 0);
lean_inc(v_val_746_);
lean_dec_ref_known(v_best_x3f_742_, 1);
v_fst_747_ = lean_ctor_get(v_val_746_, 0);
v_snd_748_ = lean_ctor_get(v_val_746_, 1);
v_isSharedCheck_758_ = !lean_is_exclusive(v_val_746_);
if (v_isSharedCheck_758_ == 0)
{
v___x_750_ = v_val_746_;
v_isShared_751_ = v_isSharedCheck_758_;
goto v_resetjp_749_;
}
else
{
lean_inc(v_snd_748_);
lean_inc(v_fst_747_);
lean_dec(v_val_746_);
v___x_750_ = lean_box(0);
v_isShared_751_ = v_isSharedCheck_758_;
goto v_resetjp_749_;
}
v_resetjp_749_:
{
lean_object* v_used_x27_752_; lean_object* v_minE_x27_753_; lean_object* v___x_755_; 
lean_inc(v_fst_747_);
v_used_x27_752_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_primStep___lam__0___boxed), 3, 2);
lean_closure_set(v_used_x27_752_, 0, v_used_738_);
lean_closure_set(v_used_x27_752_, 1, v_fst_747_);
lean_inc_ref(v_used_x27_752_);
v_minE_x27_753_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_primStep___lam__1), 5, 4);
lean_closure_set(v_minE_x27_753_, 0, v_used_x27_752_);
lean_closure_set(v_minE_x27_753_, 1, v_minE_739_);
lean_closure_set(v_minE_x27_753_, 2, v_dist_737_);
lean_closure_set(v_minE_x27_753_, 3, v_fst_747_);
if (v_isShared_751_ == 0)
{
lean_ctor_set(v___x_750_, 0, v_minE_x27_753_);
v___x_755_ = v___x_750_;
goto v_reusejp_754_;
}
else
{
lean_object* v_reuseFailAlloc_757_; 
v_reuseFailAlloc_757_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v_reuseFailAlloc_757_, 0, v_minE_x27_753_);
lean_ctor_set(v_reuseFailAlloc_757_, 1, v_snd_748_);
v___x_755_ = v_reuseFailAlloc_757_;
goto v_reusejp_754_;
}
v_reusejp_754_:
{
lean_object* v___x_756_; 
v___x_756_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_756_, 0, v_used_x27_752_);
lean_ctor_set(v___x_756_, 1, v___x_755_);
return v___x_756_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primLoop(lean_object* v_m_759_, lean_object* v_dist_760_, lean_object* v_x_761_, lean_object* v_x_762_, lean_object* v_x_763_){
_start:
{
lean_object* v_zero_764_; uint8_t v_isZero_765_; 
v_zero_764_ = lean_unsigned_to_nat(0u);
v_isZero_765_ = lean_nat_dec_eq(v_x_761_, v_zero_764_);
if (v_isZero_765_ == 1)
{
lean_dec_ref(v_x_763_);
lean_dec_ref(v_x_762_);
lean_dec_ref(v_dist_760_);
lean_dec(v_m_759_);
return v_zero_764_;
}
else
{
lean_object* v___x_766_; lean_object* v_snd_767_; lean_object* v_fst_768_; lean_object* v_fst_769_; lean_object* v_snd_770_; lean_object* v_one_771_; lean_object* v_n_772_; lean_object* v___x_773_; lean_object* v___x_774_; 
lean_inc_ref(v_dist_760_);
lean_inc(v_m_759_);
v___x_766_ = lp_island__logistics__proof_IslandLogistics_primStep(v_m_759_, v_dist_760_, v_x_762_, v_x_763_);
v_snd_767_ = lean_ctor_get(v___x_766_, 1);
lean_inc(v_snd_767_);
v_fst_768_ = lean_ctor_get(v___x_766_, 0);
lean_inc(v_fst_768_);
lean_dec_ref(v___x_766_);
v_fst_769_ = lean_ctor_get(v_snd_767_, 0);
lean_inc(v_fst_769_);
v_snd_770_ = lean_ctor_get(v_snd_767_, 1);
lean_inc(v_snd_770_);
lean_dec(v_snd_767_);
v_one_771_ = lean_unsigned_to_nat(1u);
v_n_772_ = lean_nat_sub(v_x_761_, v_one_771_);
v___x_773_ = lp_island__logistics__proof_IslandLogistics_primLoop(v_m_759_, v_dist_760_, v_n_772_, v_fst_768_, v_fst_769_);
lean_dec(v_n_772_);
v___x_774_ = lean_nat_add(v_snd_770_, v___x_773_);
lean_dec(v___x_773_);
lean_dec(v_snd_770_);
return v___x_774_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primLoop___boxed(lean_object* v_m_775_, lean_object* v_dist_776_, lean_object* v_x_777_, lean_object* v_x_778_, lean_object* v_x_779_){
_start:
{
lean_object* v_res_780_; 
v_res_780_ = lp_island__logistics__proof_IslandLogistics_primLoop(v_m_775_, v_dist_776_, v_x_777_, v_x_778_, v_x_779_);
lean_dec(v_x_777_);
return v_res_780_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_primMST___lam__0(lean_object* v_x_781_){
_start:
{
uint8_t v___x_782_; 
v___x_782_ = 0;
return v___x_782_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primMST___lam__0___boxed(lean_object* v_x_783_){
_start:
{
uint8_t v_res_784_; lean_object* v_r_785_; 
v_res_784_ = lp_island__logistics__proof_IslandLogistics_primMST___lam__0(v_x_783_);
lean_dec(v_x_783_);
v_r_785_ = lean_box(v_res_784_);
return v_r_785_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_primMST(lean_object* v_m_787_, lean_object* v_dist_788_, lean_object* v_rootDist_789_){
_start:
{
lean_object* v___f_790_; lean_object* v___x_791_; 
v___f_790_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_primMST___closed__0));
lean_inc(v_m_787_);
v___x_791_ = lp_island__logistics__proof_IslandLogistics_primLoop(v_m_787_, v_dist_788_, v_m_787_, v___f_790_, v_rootDist_789_);
lean_dec(v_m_787_);
return v___x_791_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___redArg(lean_object* v_dist_792_, lean_object* v_rootDist_793_, lean_object* v_par_794_, lean_object* v_v_795_){
_start:
{
lean_object* v___x_796_; 
lean_inc(v_v_795_);
v___x_796_ = lean_apply_1(v_par_794_, v_v_795_);
if (lean_obj_tag(v___x_796_) == 0)
{
lean_object* v___x_797_; 
lean_dec_ref(v_dist_792_);
v___x_797_ = lean_apply_1(v_rootDist_793_, v_v_795_);
return v___x_797_;
}
else
{
lean_object* v_val_798_; lean_object* v___x_799_; 
lean_dec_ref(v_rootDist_793_);
v_val_798_ = lean_ctor_get(v___x_796_, 0);
lean_inc(v_val_798_);
lean_dec_ref_known(v___x_796_, 1);
v___x_799_ = lean_apply_2(v_dist_792_, v_val_798_, v_v_795_);
return v___x_799_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight(lean_object* v_m_800_, lean_object* v_dist_801_, lean_object* v_rootDist_802_, lean_object* v_par_803_, lean_object* v_v_804_){
_start:
{
lean_object* v___x_805_; 
v___x_805_ = lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___redArg(v_dist_801_, v_rootDist_802_, v_par_803_, v_v_804_);
return v___x_805_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___boxed(lean_object* v_m_806_, lean_object* v_dist_807_, lean_object* v_rootDist_808_, lean_object* v_par_809_, lean_object* v_v_810_){
_start:
{
lean_object* v_res_811_; 
v_res_811_ = lp_island__logistics__proof_IslandLogistics_treeEdgeWeight(v_m_806_, v_dist_807_, v_rootDist_808_, v_par_809_, v_v_810_);
lean_dec(v_m_806_);
return v_res_811_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_treeWeight(lean_object* v_m_812_, lean_object* v_dist_813_, lean_object* v_rootDist_814_, lean_object* v_T_815_){
_start:
{
lean_object* v_par_816_; lean_object* v___x_817_; lean_object* v___x_818_; 
v_par_816_ = lean_ctor_get(v_T_815_, 0);
lean_inc_ref(v_par_816_);
lean_dec_ref(v_T_815_);
lean_inc(v_m_812_);
v___x_817_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_treeEdgeWeight___boxed), 5, 4);
lean_closure_set(v___x_817_, 0, v_m_812_);
lean_closure_set(v___x_817_, 1, v_dist_813_);
lean_closure_set(v___x_817_, 2, v_rootDist_814_);
lean_closure_set(v___x_817_, 3, v_par_816_);
v___x_818_ = lp_island__logistics__proof_IslandLogistics_finSum(v_m_812_, v___x_817_);
return v___x_818_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter___redArg(lean_object* v_acc_819_, lean_object* v_h__1_820_, lean_object* v_h__2_821_){
_start:
{
if (lean_obj_tag(v_acc_819_) == 0)
{
lean_object* v___x_822_; lean_object* v___x_823_; 
lean_dec(v_h__2_821_);
v___x_822_ = lean_box(0);
v___x_823_ = lean_apply_1(v_h__1_820_, v___x_822_);
return v___x_823_;
}
else
{
lean_object* v_val_824_; lean_object* v_fst_825_; lean_object* v_snd_826_; lean_object* v___x_827_; 
lean_dec(v_h__1_820_);
v_val_824_ = lean_ctor_get(v_acc_819_, 0);
lean_inc(v_val_824_);
lean_dec_ref_known(v_acc_819_, 1);
v_fst_825_ = lean_ctor_get(v_val_824_, 0);
lean_inc(v_fst_825_);
v_snd_826_ = lean_ctor_get(v_val_824_, 1);
lean_inc(v_snd_826_);
lean_dec(v_val_824_);
v___x_827_ = lean_apply_2(v_h__2_821_, v_fst_825_, v_snd_826_);
return v___x_827_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter(lean_object* v_m_828_, lean_object* v_motive_829_, lean_object* v_acc_830_, lean_object* v_h__1_831_, lean_object* v_h__2_832_){
_start:
{
if (lean_obj_tag(v_acc_830_) == 0)
{
lean_object* v___x_833_; lean_object* v___x_834_; 
lean_dec(v_h__2_832_);
v___x_833_ = lean_box(0);
v___x_834_ = lean_apply_1(v_h__1_831_, v___x_833_);
return v___x_834_;
}
else
{
lean_object* v_val_835_; lean_object* v_fst_836_; lean_object* v_snd_837_; lean_object* v___x_838_; 
lean_dec(v_h__1_831_);
v_val_835_ = lean_ctor_get(v_acc_830_, 0);
lean_inc(v_val_835_);
lean_dec_ref_known(v_acc_830_, 1);
v_fst_836_ = lean_ctor_get(v_val_835_, 0);
lean_inc(v_fst_836_);
v_snd_837_ = lean_ctor_get(v_val_835_, 1);
lean_inc(v_snd_837_);
lean_dec(v_val_835_);
v___x_838_ = lean_apply_2(v_h__2_832_, v_fst_836_, v_snd_837_);
return v___x_838_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter___boxed(lean_object* v_m_839_, lean_object* v_motive_840_, lean_object* v_acc_841_, lean_object* v_h__1_842_, lean_object* v_h__2_843_){
_start:
{
lean_object* v_res_844_; 
v_res_844_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_primStep_match__1_splitter(v_m_839_, v_motive_840_, v_acc_841_, v_h__1_842_, v_h__2_843_);
lean_dec(v_m_839_);
return v_res_844_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW___redArg(lean_object* v_dist_845_, lean_object* v_used_846_, lean_object* v_minE_847_, lean_object* v_par_848_, lean_object* v_v_849_){
_start:
{
lean_object* v___x_850_; uint8_t v___x_851_; 
lean_inc_ref(v_used_846_);
lean_inc(v_v_849_);
v___x_850_ = lean_apply_1(v_used_846_, v_v_849_);
v___x_851_ = lean_unbox(v___x_850_);
if (v___x_851_ == 0)
{
lean_object* v___x_852_; 
lean_inc(v_v_849_);
v___x_852_ = lean_apply_1(v_par_848_, v_v_849_);
if (lean_obj_tag(v___x_852_) == 0)
{
lean_object* v___x_853_; 
lean_dec_ref(v_used_846_);
lean_dec_ref(v_dist_845_);
v___x_853_ = lean_apply_1(v_minE_847_, v_v_849_);
return v___x_853_;
}
else
{
lean_object* v_val_854_; lean_object* v___x_855_; uint8_t v___x_856_; 
v_val_854_ = lean_ctor_get(v___x_852_, 0);
lean_inc_n(v_val_854_, 2);
lean_dec_ref_known(v___x_852_, 1);
v___x_855_ = lean_apply_1(v_used_846_, v_val_854_);
v___x_856_ = lean_unbox(v___x_855_);
if (v___x_856_ == 0)
{
lean_object* v___x_857_; 
lean_dec_ref(v_minE_847_);
v___x_857_ = lean_apply_2(v_dist_845_, v_val_854_, v_v_849_);
return v___x_857_;
}
else
{
lean_object* v___x_858_; 
lean_dec(v_val_854_);
lean_dec_ref(v_dist_845_);
v___x_858_ = lean_apply_1(v_minE_847_, v_v_849_);
return v___x_858_;
}
}
}
else
{
lean_object* v___x_859_; 
lean_dec(v_v_849_);
lean_dec_ref(v_par_848_);
lean_dec_ref(v_minE_847_);
lean_dec_ref(v_used_846_);
lean_dec_ref(v_dist_845_);
v___x_859_ = lean_unsigned_to_nat(0u);
return v___x_859_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW(lean_object* v_m_860_, lean_object* v_dist_861_, lean_object* v_used_862_, lean_object* v_minE_863_, lean_object* v_par_864_, lean_object* v_v_865_){
_start:
{
lean_object* v___x_866_; 
v___x_866_ = lp_island__logistics__proof_IslandLogistics_contractedEdgeW___redArg(v_dist_861_, v_used_862_, v_minE_863_, v_par_864_, v_v_865_);
return v___x_866_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_contractedEdgeW___boxed(lean_object* v_m_867_, lean_object* v_dist_868_, lean_object* v_used_869_, lean_object* v_minE_870_, lean_object* v_par_871_, lean_object* v_v_872_){
_start:
{
lean_object* v_res_873_; 
v_res_873_ = lp_island__logistics__proof_IslandLogistics_contractedEdgeW(v_m_867_, v_dist_868_, v_used_869_, v_minE_870_, v_par_871_, v_v_872_);
lean_dec(v_m_867_);
return v_res_873_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg(lean_object* v_T_874_, lean_object* v_used_875_, lean_object* v_x_876_, lean_object* v_x_877_){
_start:
{
lean_object* v_zero_878_; uint8_t v_isZero_879_; 
v_zero_878_ = lean_unsigned_to_nat(0u);
v_isZero_879_ = lean_nat_dec_eq(v_x_876_, v_zero_878_);
if (v_isZero_879_ == 1)
{
lean_object* v___x_880_; lean_object* v___x_881_; 
lean_dec_ref(v_used_875_);
lean_dec_ref(v_T_874_);
v___x_880_ = lean_box(0);
v___x_881_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_881_, 0, v_x_877_);
lean_ctor_set(v___x_881_, 1, v___x_880_);
return v___x_881_;
}
else
{
lean_object* v_par_882_; lean_object* v___x_883_; 
v_par_882_ = lean_ctor_get(v_T_874_, 0);
lean_inc_ref(v_par_882_);
lean_inc(v_x_877_);
v___x_883_ = lean_apply_1(v_par_882_, v_x_877_);
if (lean_obj_tag(v___x_883_) == 0)
{
lean_object* v___x_885_; uint8_t v_isShared_886_; uint8_t v_isSharedCheck_891_; 
lean_dec_ref(v_used_875_);
v_isSharedCheck_891_ = !lean_is_exclusive(v_T_874_);
if (v_isSharedCheck_891_ == 0)
{
lean_object* v_unused_892_; lean_object* v_unused_893_; 
v_unused_892_ = lean_ctor_get(v_T_874_, 1);
lean_dec(v_unused_892_);
v_unused_893_ = lean_ctor_get(v_T_874_, 0);
lean_dec(v_unused_893_);
v___x_885_ = v_T_874_;
v_isShared_886_ = v_isSharedCheck_891_;
goto v_resetjp_884_;
}
else
{
lean_dec(v_T_874_);
v___x_885_ = lean_box(0);
v_isShared_886_ = v_isSharedCheck_891_;
goto v_resetjp_884_;
}
v_resetjp_884_:
{
lean_object* v___x_887_; lean_object* v___x_889_; 
v___x_887_ = lean_box(0);
if (v_isShared_886_ == 0)
{
lean_ctor_set_tag(v___x_885_, 1);
lean_ctor_set(v___x_885_, 1, v___x_887_);
lean_ctor_set(v___x_885_, 0, v_x_877_);
v___x_889_ = v___x_885_;
goto v_reusejp_888_;
}
else
{
lean_object* v_reuseFailAlloc_890_; 
v_reuseFailAlloc_890_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_890_, 0, v_x_877_);
lean_ctor_set(v_reuseFailAlloc_890_, 1, v___x_887_);
v___x_889_ = v_reuseFailAlloc_890_;
goto v_reusejp_888_;
}
v_reusejp_888_:
{
return v___x_889_;
}
}
}
else
{
lean_object* v_val_894_; lean_object* v___x_895_; uint8_t v___x_896_; 
v_val_894_ = lean_ctor_get(v___x_883_, 0);
lean_inc_n(v_val_894_, 2);
lean_dec_ref_known(v___x_883_, 1);
lean_inc_ref(v_used_875_);
v___x_895_ = lean_apply_1(v_used_875_, v_val_894_);
v___x_896_ = lean_unbox(v___x_895_);
if (v___x_896_ == 0)
{
lean_object* v_one_897_; lean_object* v_n_898_; lean_object* v___x_899_; lean_object* v___x_900_; 
v_one_897_ = lean_unsigned_to_nat(1u);
v_n_898_ = lean_nat_sub(v_x_876_, v_one_897_);
v___x_899_ = lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg(v_T_874_, v_used_875_, v_n_898_, v_val_894_);
lean_dec(v_n_898_);
v___x_900_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_900_, 0, v_x_877_);
lean_ctor_set(v___x_900_, 1, v___x_899_);
return v___x_900_;
}
else
{
lean_object* v___x_902_; uint8_t v_isShared_903_; uint8_t v_isSharedCheck_908_; 
lean_dec(v_val_894_);
lean_dec_ref(v_used_875_);
v_isSharedCheck_908_ = !lean_is_exclusive(v_T_874_);
if (v_isSharedCheck_908_ == 0)
{
lean_object* v_unused_909_; lean_object* v_unused_910_; 
v_unused_909_ = lean_ctor_get(v_T_874_, 1);
lean_dec(v_unused_909_);
v_unused_910_ = lean_ctor_get(v_T_874_, 0);
lean_dec(v_unused_910_);
v___x_902_ = v_T_874_;
v_isShared_903_ = v_isSharedCheck_908_;
goto v_resetjp_901_;
}
else
{
lean_dec(v_T_874_);
v___x_902_ = lean_box(0);
v_isShared_903_ = v_isSharedCheck_908_;
goto v_resetjp_901_;
}
v_resetjp_901_:
{
lean_object* v___x_904_; lean_object* v___x_906_; 
v___x_904_ = lean_box(0);
if (v_isShared_903_ == 0)
{
lean_ctor_set_tag(v___x_902_, 1);
lean_ctor_set(v___x_902_, 1, v___x_904_);
lean_ctor_set(v___x_902_, 0, v_x_877_);
v___x_906_ = v___x_902_;
goto v_reusejp_905_;
}
else
{
lean_object* v_reuseFailAlloc_907_; 
v_reuseFailAlloc_907_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_907_, 0, v_x_877_);
lean_ctor_set(v_reuseFailAlloc_907_, 1, v___x_904_);
v___x_906_ = v_reuseFailAlloc_907_;
goto v_reusejp_905_;
}
v_reusejp_905_:
{
return v___x_906_;
}
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg___boxed(lean_object* v_T_911_, lean_object* v_used_912_, lean_object* v_x_913_, lean_object* v_x_914_){
_start:
{
lean_object* v_res_915_; 
v_res_915_ = lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg(v_T_911_, v_used_912_, v_x_913_, v_x_914_);
lean_dec(v_x_913_);
return v_res_915_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux(lean_object* v_m_916_, lean_object* v_T_917_, lean_object* v_used_918_, lean_object* v_x_919_, lean_object* v_x_920_){
_start:
{
lean_object* v___x_921_; 
v___x_921_ = lp_island__logistics__proof_IslandLogistics_traceToCutAux___redArg(v_T_917_, v_used_918_, v_x_919_, v_x_920_);
return v___x_921_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_traceToCutAux___boxed(lean_object* v_m_922_, lean_object* v_T_923_, lean_object* v_used_924_, lean_object* v_x_925_, lean_object* v_x_926_){
_start:
{
lean_object* v_res_927_; 
v_res_927_ = lp_island__logistics__proof_IslandLogistics_traceToCutAux(v_m_922_, v_T_923_, v_used_924_, v_x_925_, v_x_926_);
lean_dec(v_x_925_);
lean_dec(v_m_922_);
return v_res_927_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg(lean_object* v_par_928_, lean_object* v_x_929_, lean_object* v_a_930_){
_start:
{
if (lean_obj_tag(v_x_929_) == 0)
{
lean_object* v___x_931_; 
v___x_931_ = lean_apply_1(v_par_928_, v_a_930_);
return v___x_931_;
}
else
{
lean_object* v_tail_932_; 
v_tail_932_ = lean_ctor_get(v_x_929_, 1);
if (lean_obj_tag(v_tail_932_) == 0)
{
lean_object* v_head_933_; uint8_t v___x_934_; 
v_head_933_ = lean_ctor_get(v_x_929_, 0);
v___x_934_ = lean_nat_dec_eq(v_a_930_, v_head_933_);
if (v___x_934_ == 0)
{
lean_object* v___x_935_; 
v___x_935_ = lean_apply_1(v_par_928_, v_a_930_);
return v___x_935_;
}
else
{
lean_object* v___x_936_; 
lean_dec(v_a_930_);
lean_dec_ref(v_par_928_);
v___x_936_ = lean_box(0);
return v___x_936_;
}
}
else
{
lean_object* v_head_937_; lean_object* v_head_938_; uint8_t v___x_939_; 
v_head_937_ = lean_ctor_get(v_x_929_, 0);
v_head_938_ = lean_ctor_get(v_tail_932_, 0);
v___x_939_ = lean_nat_dec_eq(v_a_930_, v_head_938_);
if (v___x_939_ == 0)
{
uint8_t v___x_940_; 
v___x_940_ = lean_nat_dec_eq(v_a_930_, v_head_937_);
if (v___x_940_ == 0)
{
v_x_929_ = v_tail_932_;
goto _start;
}
else
{
lean_object* v___x_942_; 
lean_dec(v_a_930_);
lean_dec_ref(v_par_928_);
v___x_942_ = lean_box(0);
return v___x_942_;
}
}
else
{
lean_object* v___x_943_; 
lean_dec(v_a_930_);
lean_dec_ref(v_par_928_);
lean_inc(v_head_937_);
v___x_943_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_943_, 0, v_head_937_);
return v___x_943_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg___boxed(lean_object* v_par_944_, lean_object* v_x_945_, lean_object* v_a_946_){
_start:
{
lean_object* v_res_947_; 
v_res_947_ = lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg(v_par_944_, v_x_945_, v_a_946_);
lean_dec(v_x_945_);
return v_res_947_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar(lean_object* v_m_948_, lean_object* v_par_949_, lean_object* v_x_950_, lean_object* v_a_951_){
_start:
{
lean_object* v___x_952_; 
v___x_952_ = lp_island__logistics__proof_IslandLogistics_reversePathPar___redArg(v_par_949_, v_x_950_, v_a_951_);
return v___x_952_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reversePathPar___boxed(lean_object* v_m_953_, lean_object* v_par_954_, lean_object* v_x_955_, lean_object* v_a_956_){
_start:
{
lean_object* v_res_957_; 
v_res_957_ = lp_island__logistics__proof_IslandLogistics_reversePathPar(v_m_953_, v_par_954_, v_x_955_, v_a_956_);
lean_dec(v_x_955_);
lean_dec(v_m_953_);
return v_res_957_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter___redArg(lean_object* v_x_958_, lean_object* v_h__1_959_, lean_object* v_h__2_960_){
_start:
{
if (lean_obj_tag(v_x_958_) == 0)
{
lean_object* v___x_961_; lean_object* v___x_962_; 
lean_dec(v_h__2_960_);
v___x_961_ = lean_box(0);
v___x_962_ = lean_apply_1(v_h__1_959_, v___x_961_);
return v___x_962_;
}
else
{
lean_object* v_val_963_; lean_object* v___x_964_; 
lean_dec(v_h__1_959_);
v_val_963_ = lean_ctor_get(v_x_958_, 0);
lean_inc(v_val_963_);
lean_dec_ref_known(v_x_958_, 1);
v___x_964_ = lean_apply_1(v_h__2_960_, v_val_963_);
return v___x_964_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter(lean_object* v_m_965_, lean_object* v_motive_966_, lean_object* v_x_967_, lean_object* v_h__1_968_, lean_object* v_h__2_969_){
_start:
{
if (lean_obj_tag(v_x_967_) == 0)
{
lean_object* v___x_970_; lean_object* v___x_971_; 
lean_dec(v_h__2_969_);
v___x_970_ = lean_box(0);
v___x_971_ = lean_apply_1(v_h__1_968_, v___x_970_);
return v___x_971_;
}
else
{
lean_object* v_val_972_; lean_object* v___x_973_; 
lean_dec(v_h__1_968_);
v_val_972_ = lean_ctor_get(v_x_967_, 0);
lean_inc(v_val_972_);
lean_dec_ref_known(v_x_967_, 1);
v___x_973_ = lean_apply_1(v_h__2_969_, v_val_972_);
return v___x_973_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter___boxed(lean_object* v_m_974_, lean_object* v_motive_975_, lean_object* v_x_976_, lean_object* v_h__1_977_, lean_object* v_h__2_978_){
_start:
{
lean_object* v_res_979_; 
v_res_979_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_treeEdgeWeight_match__1_splitter(v_m_974_, v_motive_975_, v_x_976_, v_h__1_977_, v_h__2_978_);
lean_dec(v_m_974_);
return v_res_979_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___redArg(lean_object* v_v_982_, lean_object* v_x_983_){
_start:
{
if (lean_obj_tag(v_x_983_) == 0)
{
lean_object* v___x_984_; 
v___x_984_ = lean_box(0);
return v___x_984_;
}
else
{
lean_object* v_head_985_; lean_object* v_tail_986_; uint8_t v___x_987_; 
v_head_985_ = lean_ctor_get(v_x_983_, 0);
v_tail_986_ = lean_ctor_get(v_x_983_, 1);
v___x_987_ = lean_nat_dec_eq(v_v_982_, v_head_985_);
if (v___x_987_ == 0)
{
lean_object* v___x_988_; 
v___x_988_ = lp_island__logistics__proof_IslandLogistics_pathIndex___redArg(v_v_982_, v_tail_986_);
if (lean_obj_tag(v___x_988_) == 0)
{
return v___x_988_;
}
else
{
lean_object* v_val_989_; lean_object* v___x_991_; uint8_t v_isShared_992_; uint8_t v_isSharedCheck_998_; 
v_val_989_ = lean_ctor_get(v___x_988_, 0);
v_isSharedCheck_998_ = !lean_is_exclusive(v___x_988_);
if (v_isSharedCheck_998_ == 0)
{
v___x_991_ = v___x_988_;
v_isShared_992_ = v_isSharedCheck_998_;
goto v_resetjp_990_;
}
else
{
lean_inc(v_val_989_);
lean_dec(v___x_988_);
v___x_991_ = lean_box(0);
v_isShared_992_ = v_isSharedCheck_998_;
goto v_resetjp_990_;
}
v_resetjp_990_:
{
lean_object* v___x_993_; lean_object* v___x_994_; lean_object* v___x_996_; 
v___x_993_ = lean_unsigned_to_nat(1u);
v___x_994_ = lean_nat_add(v_val_989_, v___x_993_);
lean_dec(v_val_989_);
if (v_isShared_992_ == 0)
{
lean_ctor_set(v___x_991_, 0, v___x_994_);
v___x_996_ = v___x_991_;
goto v_reusejp_995_;
}
else
{
lean_object* v_reuseFailAlloc_997_; 
v_reuseFailAlloc_997_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v_reuseFailAlloc_997_, 0, v___x_994_);
v___x_996_ = v_reuseFailAlloc_997_;
goto v_reusejp_995_;
}
v_reusejp_995_:
{
return v___x_996_;
}
}
}
}
else
{
lean_object* v___x_999_; 
v___x_999_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___closed__0));
return v___x_999_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___redArg___boxed(lean_object* v_v_1000_, lean_object* v_x_1001_){
_start:
{
lean_object* v_res_1002_; 
v_res_1002_ = lp_island__logistics__proof_IslandLogistics_pathIndex___redArg(v_v_1000_, v_x_1001_);
lean_dec(v_x_1001_);
lean_dec(v_v_1000_);
return v_res_1002_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex(lean_object* v_m_1003_, lean_object* v_v_1004_, lean_object* v_x_1005_){
_start:
{
lean_object* v___x_1006_; 
v___x_1006_ = lp_island__logistics__proof_IslandLogistics_pathIndex___redArg(v_v_1004_, v_x_1005_);
return v___x_1006_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_pathIndex___boxed(lean_object* v_m_1007_, lean_object* v_v_1008_, lean_object* v_x_1009_){
_start:
{
lean_object* v_res_1010_; 
v_res_1010_ = lp_island__logistics__proof_IslandLogistics_pathIndex(v_m_1007_, v_v_1008_, v_x_1009_);
lean_dec(v_x_1009_);
lean_dec(v_v_1008_);
lean_dec(v_m_1007_);
return v_res_1010_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg(lean_object* v_C_1011_, lean_object* v_t_1012_, lean_object* v_x_1013_){
_start:
{
if (lean_obj_tag(v_x_1013_) == 0)
{
lean_object* v_t_1014_; lean_object* v_u_1015_; lean_object* v_v_1016_; uint8_t v___x_1017_; 
v_t_1014_ = lean_ctor_get(v_x_1013_, 0);
lean_inc(v_t_1014_);
v_u_1015_ = lean_ctor_get(v_x_1013_, 1);
lean_inc(v_u_1015_);
v_v_1016_ = lean_ctor_get(v_x_1013_, 2);
lean_inc(v_v_1016_);
lean_dec_ref_known(v_x_1013_, 3);
v___x_1017_ = lean_nat_dec_eq(v_t_1014_, v_t_1012_);
lean_dec(v_t_1014_);
if (v___x_1017_ == 0)
{
lean_dec(v_v_1016_);
lean_dec(v_u_1015_);
lean_dec_ref(v_C_1011_);
return v___x_1017_;
}
else
{
lean_object* v_isBridge_1018_; lean_object* v___x_1019_; uint8_t v___x_1020_; 
v_isBridge_1018_ = lean_ctor_get(v_C_1011_, 3);
lean_inc_ref(v_isBridge_1018_);
lean_dec_ref(v_C_1011_);
v___x_1019_ = lean_apply_2(v_isBridge_1018_, v_u_1015_, v_v_1016_);
v___x_1020_ = lean_unbox(v___x_1019_);
if (v___x_1020_ == 0)
{
return v___x_1017_;
}
else
{
uint8_t v___x_1021_; 
v___x_1021_ = 0;
return v___x_1021_;
}
}
}
else
{
uint8_t v___x_1022_; 
lean_dec_ref(v_x_1013_);
lean_dec_ref(v_C_1011_);
v___x_1022_ = 0;
return v___x_1022_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg___boxed(lean_object* v_C_1023_, lean_object* v_t_1024_, lean_object* v_x_1025_){
_start:
{
uint8_t v_res_1026_; lean_object* v_r_1027_; 
v_res_1026_ = lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg(v_C_1023_, v_t_1024_, v_x_1025_);
lean_dec(v_t_1024_);
v_r_1027_ = lean_box(v_res_1026_);
return v_r_1027_;
}
}
LEAN_EXPORT uint8_t lp_island__logistics__proof_IslandLogistics_isTruckNBDrive(lean_object* v_I_1028_, lean_object* v_C_1029_, lean_object* v_t_1030_, lean_object* v_x_1031_){
_start:
{
uint8_t v___x_1032_; 
v___x_1032_ = lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___redArg(v_C_1029_, v_t_1030_, v_x_1031_);
return v___x_1032_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_isTruckNBDrive___boxed(lean_object* v_I_1033_, lean_object* v_C_1034_, lean_object* v_t_1035_, lean_object* v_x_1036_){
_start:
{
uint8_t v_res_1037_; lean_object* v_r_1038_; 
v_res_1037_ = lp_island__logistics__proof_IslandLogistics_isTruckNBDrive(v_I_1033_, v_C_1034_, v_t_1035_, v_x_1036_);
lean_dec(v_t_1035_);
lean_dec_ref(v_I_1033_);
v_r_1038_ = lean_box(v_res_1037_);
return v_r_1038_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(lean_object* v_x_1039_, lean_object* v_x_1040_){
_start:
{
if (lean_obj_tag(v_x_1040_) == 0)
{
lean_inc(v_x_1039_);
return v_x_1039_;
}
else
{
lean_object* v_head_1041_; lean_object* v_tail_1042_; uint8_t v___x_1043_; 
v_head_1041_ = lean_ctor_get(v_x_1040_, 0);
v_tail_1042_ = lean_ctor_get(v_x_1040_, 1);
v___x_1043_ = lean_nat_dec_le(v_x_1039_, v_head_1041_);
if (v___x_1043_ == 0)
{
v_x_1039_ = v_head_1041_;
v_x_1040_ = v_tail_1042_;
goto _start;
}
else
{
v_x_1040_ = v_tail_1042_;
goto _start;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1___boxed(lean_object* v_x_1046_, lean_object* v_x_1047_){
_start:
{
lean_object* v_res_1048_; 
v_res_1048_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(v_x_1046_, v_x_1047_);
lean_dec(v_x_1047_);
lean_dec(v_x_1046_);
return v_res_1048_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___redArg(lean_object* v_C_1049_, lean_object* v_s_1050_, lean_object* v_r_1051_, lean_object* v_a_1052_, lean_object* v_a_1053_){
_start:
{
if (lean_obj_tag(v_a_1052_) == 0)
{
lean_object* v___x_1054_; 
lean_dec(v_r_1051_);
lean_dec_ref(v_s_1050_);
lean_dec_ref(v_C_1049_);
v___x_1054_ = l_List_reverse___redArg(v_a_1053_);
return v___x_1054_;
}
else
{
lean_object* v_head_1055_; lean_object* v_tail_1056_; lean_object* v___x_1058_; uint8_t v_isShared_1059_; uint8_t v_isSharedCheck_1069_; 
v_head_1055_ = lean_ctor_get(v_a_1052_, 0);
v_tail_1056_ = lean_ctor_get(v_a_1052_, 1);
v_isSharedCheck_1069_ = !lean_is_exclusive(v_a_1052_);
if (v_isSharedCheck_1069_ == 0)
{
v___x_1058_ = v_a_1052_;
v_isShared_1059_ = v_isSharedCheck_1069_;
goto v_resetjp_1057_;
}
else
{
lean_inc(v_tail_1056_);
lean_inc(v_head_1055_);
lean_dec(v_a_1052_);
v___x_1058_ = lean_box(0);
v_isShared_1059_ = v_isSharedCheck_1069_;
goto v_resetjp_1057_;
}
v_resetjp_1057_:
{
lean_object* v_nbId_1060_; lean_object* v_nbDist_1061_; lean_object* v___x_1062_; lean_object* v___x_1063_; lean_object* v___x_1064_; lean_object* v___x_1066_; 
v_nbId_1060_ = lean_ctor_get(v_C_1049_, 1);
v_nbDist_1061_ = lean_ctor_get(v_C_1049_, 2);
lean_inc_ref(v_s_1050_);
v___x_1062_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_1050_, v_head_1055_);
lean_inc_ref(v_nbId_1060_);
v___x_1063_ = lean_apply_1(v_nbId_1060_, v___x_1062_);
lean_inc_ref(v_nbDist_1061_);
lean_inc(v_r_1051_);
v___x_1064_ = lean_apply_2(v_nbDist_1061_, v___x_1063_, v_r_1051_);
if (v_isShared_1059_ == 0)
{
lean_ctor_set(v___x_1058_, 1, v_a_1053_);
lean_ctor_set(v___x_1058_, 0, v___x_1064_);
v___x_1066_ = v___x_1058_;
goto v_reusejp_1065_;
}
else
{
lean_object* v_reuseFailAlloc_1068_; 
v_reuseFailAlloc_1068_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_1068_, 0, v___x_1064_);
lean_ctor_set(v_reuseFailAlloc_1068_, 1, v_a_1053_);
v___x_1066_ = v_reuseFailAlloc_1068_;
goto v_reusejp_1065_;
}
v_reusejp_1065_:
{
v_a_1052_ = v_tail_1056_;
v_a_1053_ = v___x_1066_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_minTruckNBDist(lean_object* v_I_1070_, lean_object* v_C_1071_, lean_object* v_s_1072_, lean_object* v_r_1073_){
_start:
{
lean_object* v_numTrucks_1074_; lean_object* v___x_1075_; lean_object* v___x_1076_; lean_object* v___x_1077_; 
v_numTrucks_1074_ = lean_ctor_get(v_I_1070_, 3);
lean_inc(v_numTrucks_1074_);
lean_dec_ref(v_I_1070_);
v___x_1075_ = l_List_finRange(v_numTrucks_1074_);
v___x_1076_ = lean_box(0);
v___x_1077_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___redArg(v_C_1071_, v_s_1072_, v_r_1073_, v___x_1075_, v___x_1076_);
if (lean_obj_tag(v___x_1077_) == 0)
{
lean_object* v___x_1078_; 
v___x_1078_ = lean_unsigned_to_nat(0u);
return v___x_1078_;
}
else
{
lean_object* v_head_1079_; lean_object* v_tail_1080_; lean_object* v___x_1081_; 
v_head_1079_ = lean_ctor_get(v___x_1077_, 0);
lean_inc(v_head_1079_);
v_tail_1080_ = lean_ctor_get(v___x_1077_, 1);
lean_inc(v_tail_1080_);
lean_dec_ref_known(v___x_1077_, 2);
v___x_1081_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_minTruckNBDist_spec__1(v_head_1079_, v_tail_1080_);
lean_dec(v_tail_1080_);
lean_dec(v_head_1079_);
return v___x_1081_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0(lean_object* v_C_1082_, lean_object* v_I_1083_, lean_object* v_s_1084_, lean_object* v_r_1085_, lean_object* v_a_1086_, lean_object* v_a_1087_){
_start:
{
lean_object* v___x_1088_; 
v___x_1088_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___redArg(v_C_1082_, v_s_1084_, v_r_1085_, v_a_1086_, v_a_1087_);
return v___x_1088_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0___boxed(lean_object* v_C_1089_, lean_object* v_I_1090_, lean_object* v_s_1091_, lean_object* v_r_1092_, lean_object* v_a_1093_, lean_object* v_a_1094_){
_start:
{
lean_object* v_res_1095_; 
v_res_1095_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_minTruckNBDist_spec__0(v_C_1089_, v_I_1090_, v_s_1091_, v_r_1092_, v_a_1093_, v_a_1094_);
lean_dec_ref(v_I_1090_);
return v_res_1095_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter___redArg(lean_object* v_x_1096_, lean_object* v_h__1_1097_, lean_object* v_h__2_1098_){
_start:
{
if (lean_obj_tag(v_x_1096_) == 0)
{
lean_object* v_t_1099_; lean_object* v_u_1100_; lean_object* v_v_1101_; lean_object* v___x_1102_; 
lean_dec(v_h__2_1098_);
v_t_1099_ = lean_ctor_get(v_x_1096_, 0);
lean_inc(v_t_1099_);
v_u_1100_ = lean_ctor_get(v_x_1096_, 1);
lean_inc(v_u_1100_);
v_v_1101_ = lean_ctor_get(v_x_1096_, 2);
lean_inc(v_v_1101_);
lean_dec_ref_known(v_x_1096_, 3);
v___x_1102_ = lean_apply_3(v_h__1_1097_, v_t_1099_, v_u_1100_, v_v_1101_);
return v___x_1102_;
}
else
{
lean_object* v___x_1103_; 
lean_dec(v_h__1_1097_);
v___x_1103_ = lean_apply_2(v_h__2_1098_, v_x_1096_, lean_box(0));
return v___x_1103_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter(lean_object* v_I_1104_, lean_object* v_motive_1105_, lean_object* v_x_1106_, lean_object* v_h__1_1107_, lean_object* v_h__2_1108_){
_start:
{
if (lean_obj_tag(v_x_1106_) == 0)
{
lean_object* v_t_1109_; lean_object* v_u_1110_; lean_object* v_v_1111_; lean_object* v___x_1112_; 
lean_dec(v_h__2_1108_);
v_t_1109_ = lean_ctor_get(v_x_1106_, 0);
lean_inc(v_t_1109_);
v_u_1110_ = lean_ctor_get(v_x_1106_, 1);
lean_inc(v_u_1110_);
v_v_1111_ = lean_ctor_get(v_x_1106_, 2);
lean_inc(v_v_1111_);
lean_dec_ref_known(v_x_1106_, 3);
v___x_1112_ = lean_apply_3(v_h__1_1107_, v_t_1109_, v_u_1110_, v_v_1111_);
return v___x_1112_;
}
else
{
lean_object* v___x_1113_; 
lean_dec(v_h__1_1107_);
v___x_1113_ = lean_apply_2(v_h__2_1108_, v_x_1106_, lean_box(0));
return v___x_1113_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter___boxed(lean_object* v_I_1114_, lean_object* v_motive_1115_, lean_object* v_x_1116_, lean_object* v_h__1_1117_, lean_object* v_h__2_1118_){
_start:
{
lean_object* v_res_1119_; 
v_res_1119_ = lp_island__logistics__proof___private_BridgesAndCycles_0__IslandLogistics_actionCostDrive_match__1_splitter(v_I_1114_, v_motive_1115_, v_x_1116_, v_h__1_1117_, v_h__2_1118_);
lean_dec_ref(v_I_1114_);
return v_res_1119_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin);
lean_object* initialize_island__logistics__proof_PackingAndFlux(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_BridgesAndCycles(uint8_t builtin) {
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
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
