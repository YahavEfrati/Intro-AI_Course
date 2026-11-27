// Lean compiler output
// Module: PackingAndFlux
// Imports: public import Init public meta import Init public import Domain
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
lean_object* lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(lean_object*);
uint8_t lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(lean_object*, lean_object*, lean_object*);
uint8_t lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
lean_object* lean_nat_div(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(lean_object*, lean_object*);
lean_object* l_List_appendTR___redArg(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_applyAction(lean_object*, lean_object*, lean_object*);
lean_object* lean_mk_empty_array_with_capacity(lean_object*);
lean_object* l_List_finRange(lean_object*);
lean_object* lean_nat_gcd(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object*, lean_object*);
lean_object* l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ceilDiv(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ceilDiv___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_subsetWeight___lam__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_subsetWeight(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2___boxed(lean_object*, lean_object*, lean_object*);
static const lean_ctor_object lp_island__logistics__proof_IslandLogistics_reachableSumsList___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_ctor_object) + sizeof(void*)*2 + 0, .m_other = 2, .m_tag = 1}, .m_objs = {((lean_object*)(((size_t)(0) << 1) | 1)),((lean_object*)(((size_t)(0) << 1) | 1))}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_reachableSumsList___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_reachableSumsList___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reachableSumsList(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reachableSumsList___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listMax(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listMax___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_effCap_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_effCap(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_effCap___boxed(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listGcd(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listGcd___boxed(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_undelivGcd_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_undelivGcd(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_initWGcd(lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_dynEffCap(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_maxDynEffCap(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertDesc(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortDesc(lean_object*);
static const lean_array_object lp_island__logistics__proof_IslandLogistics_topKSum___closed__0_value = {.m_header = {.m_rc = 0, .m_cs_sz = sizeof(lean_array_object) + sizeof(void*)*0, .m_other = 0, .m_tag = 246}, .m_size = 0, .m_capacity = 0, .m_data = {}};
static const lean_object* lp_island__logistics__proof_IslandLogistics_topKSum___closed__0 = (const lean_object*)&lp_island__logistics__proof_IslandLogistics_topKSum___closed__0_value;
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_topKSum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_maxFerryWeight(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_packLB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_packLB___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_countActions_spec__0(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions___redArg(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions___boxed(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB(lean_object*, lean_object*, lean_object*, lean_object*, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCrossAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCrossBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryAB___lam__0(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planPkgCrossAB(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planPkgCrossBA(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ceilDiv(lean_object* v_a_1_, lean_object* v_cap_2_){
_start:
{
lean_object* v___x_3_; uint8_t v___x_4_; 
v___x_3_ = lean_unsigned_to_nat(0u);
v___x_4_ = lean_nat_dec_lt(v___x_3_, v_a_1_);
if (v___x_4_ == 0)
{
return v___x_3_;
}
else
{
lean_object* v___x_5_; lean_object* v___x_6_; lean_object* v___x_7_; lean_object* v___x_8_; 
v___x_5_ = lean_unsigned_to_nat(1u);
v___x_6_ = lean_nat_sub(v_cap_2_, v___x_5_);
v___x_7_ = lean_nat_add(v_a_1_, v___x_6_);
lean_dec(v___x_6_);
v___x_8_ = lean_nat_div(v___x_7_, v_cap_2_);
lean_dec(v___x_7_);
return v___x_8_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_ceilDiv___boxed(lean_object* v_a_9_, lean_object* v_cap_10_){
_start:
{
lean_object* v_res_11_; 
v_res_11_ = lp_island__logistics__proof_IslandLogistics_ceilDiv(v_a_9_, v_cap_10_);
lean_dec(v_cap_10_);
lean_dec(v_a_9_);
return v_res_11_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_subsetWeight___lam__0(lean_object* v_mask_12_, lean_object* v_w_13_, lean_object* v_i_14_){
_start:
{
lean_object* v___x_15_; uint8_t v___x_16_; 
lean_inc(v_i_14_);
v___x_15_ = lean_apply_1(v_mask_12_, v_i_14_);
v___x_16_ = lean_unbox(v___x_15_);
if (v___x_16_ == 0)
{
lean_object* v___x_17_; 
lean_dec(v_i_14_);
lean_dec_ref(v_w_13_);
v___x_17_ = lean_unsigned_to_nat(0u);
return v___x_17_;
}
else
{
lean_object* v___x_18_; 
v___x_18_ = lean_apply_1(v_w_13_, v_i_14_);
return v___x_18_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_subsetWeight(lean_object* v_n_19_, lean_object* v_w_20_, lean_object* v_mask_21_){
_start:
{
lean_object* v___f_22_; lean_object* v___x_23_; 
v___f_22_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_subsetWeight___lam__0), 3, 2);
lean_closure_set(v___f_22_, 0, v_mask_21_);
lean_closure_set(v___f_22_, 1, v_w_20_);
v___x_23_ = lp_island__logistics__proof_IslandLogistics_finSum(v_n_19_, v___f_22_);
return v___x_23_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1(lean_object* v_cap_24_, lean_object* v_a_25_, lean_object* v_a_26_){
_start:
{
if (lean_obj_tag(v_a_25_) == 0)
{
lean_object* v___x_27_; 
v___x_27_ = l_List_reverse___redArg(v_a_26_);
return v___x_27_;
}
else
{
lean_object* v_head_28_; lean_object* v_tail_29_; lean_object* v___x_31_; uint8_t v_isShared_32_; uint8_t v_isSharedCheck_39_; 
v_head_28_ = lean_ctor_get(v_a_25_, 0);
v_tail_29_ = lean_ctor_get(v_a_25_, 1);
v_isSharedCheck_39_ = !lean_is_exclusive(v_a_25_);
if (v_isSharedCheck_39_ == 0)
{
v___x_31_ = v_a_25_;
v_isShared_32_ = v_isSharedCheck_39_;
goto v_resetjp_30_;
}
else
{
lean_inc(v_tail_29_);
lean_inc(v_head_28_);
lean_dec(v_a_25_);
v___x_31_ = lean_box(0);
v_isShared_32_ = v_isSharedCheck_39_;
goto v_resetjp_30_;
}
v_resetjp_30_:
{
uint8_t v___x_33_; 
v___x_33_ = lean_nat_dec_le(v_head_28_, v_cap_24_);
if (v___x_33_ == 0)
{
lean_del_object(v___x_31_);
lean_dec(v_head_28_);
v_a_25_ = v_tail_29_;
goto _start;
}
else
{
lean_object* v___x_36_; 
if (v_isShared_32_ == 0)
{
lean_ctor_set(v___x_31_, 1, v_a_26_);
v___x_36_ = v___x_31_;
goto v_reusejp_35_;
}
else
{
lean_object* v_reuseFailAlloc_38_; 
v_reuseFailAlloc_38_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_38_, 0, v_head_28_);
lean_ctor_set(v_reuseFailAlloc_38_, 1, v_a_26_);
v___x_36_ = v_reuseFailAlloc_38_;
goto v_reusejp_35_;
}
v_reusejp_35_:
{
v_a_25_ = v_tail_29_;
v_a_26_ = v___x_36_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1___boxed(lean_object* v_cap_40_, lean_object* v_a_41_, lean_object* v_a_42_){
_start:
{
lean_object* v_res_43_; 
v_res_43_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1(v_cap_40_, v_a_41_, v_a_42_);
lean_dec(v_cap_40_);
return v_res_43_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0(lean_object* v_w_44_, lean_object* v_a_45_, lean_object* v_a_46_){
_start:
{
if (lean_obj_tag(v_a_45_) == 0)
{
lean_object* v___x_47_; 
v___x_47_ = l_List_reverse___redArg(v_a_46_);
return v___x_47_;
}
else
{
lean_object* v_head_48_; lean_object* v_tail_49_; lean_object* v___x_51_; uint8_t v_isShared_52_; uint8_t v_isSharedCheck_58_; 
v_head_48_ = lean_ctor_get(v_a_45_, 0);
v_tail_49_ = lean_ctor_get(v_a_45_, 1);
v_isSharedCheck_58_ = !lean_is_exclusive(v_a_45_);
if (v_isSharedCheck_58_ == 0)
{
v___x_51_ = v_a_45_;
v_isShared_52_ = v_isSharedCheck_58_;
goto v_resetjp_50_;
}
else
{
lean_inc(v_tail_49_);
lean_inc(v_head_48_);
lean_dec(v_a_45_);
v___x_51_ = lean_box(0);
v_isShared_52_ = v_isSharedCheck_58_;
goto v_resetjp_50_;
}
v_resetjp_50_:
{
lean_object* v___x_53_; lean_object* v___x_55_; 
v___x_53_ = lean_nat_add(v_head_48_, v_w_44_);
lean_dec(v_head_48_);
if (v_isShared_52_ == 0)
{
lean_ctor_set(v___x_51_, 1, v_a_46_);
lean_ctor_set(v___x_51_, 0, v___x_53_);
v___x_55_ = v___x_51_;
goto v_reusejp_54_;
}
else
{
lean_object* v_reuseFailAlloc_57_; 
v_reuseFailAlloc_57_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_57_, 0, v___x_53_);
lean_ctor_set(v_reuseFailAlloc_57_, 1, v_a_46_);
v___x_55_ = v_reuseFailAlloc_57_;
goto v_reusejp_54_;
}
v_reusejp_54_:
{
v_a_45_ = v_tail_49_;
v_a_46_ = v___x_55_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0___boxed(lean_object* v_w_59_, lean_object* v_a_60_, lean_object* v_a_61_){
_start:
{
lean_object* v_res_62_; 
v_res_62_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0(v_w_59_, v_a_60_, v_a_61_);
lean_dec(v_w_59_);
return v_res_62_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2(lean_object* v_cap_63_, lean_object* v_x_64_, lean_object* v_x_65_){
_start:
{
if (lean_obj_tag(v_x_65_) == 0)
{
return v_x_64_;
}
else
{
lean_object* v_head_66_; lean_object* v_tail_67_; lean_object* v___x_68_; uint8_t v___x_69_; 
v_head_66_ = lean_ctor_get(v_x_65_, 0);
v_tail_67_ = lean_ctor_get(v_x_65_, 1);
v___x_68_ = lean_unsigned_to_nat(0u);
v___x_69_ = lean_nat_dec_lt(v___x_68_, v_head_66_);
if (v___x_69_ == 0)
{
v_x_65_ = v_tail_67_;
goto _start;
}
else
{
uint8_t v___x_71_; 
v___x_71_ = lean_nat_dec_le(v_head_66_, v_cap_63_);
if (v___x_71_ == 0)
{
v_x_65_ = v_tail_67_;
goto _start;
}
else
{
lean_object* v___x_73_; lean_object* v___x_74_; lean_object* v___x_75_; lean_object* v___x_76_; 
v___x_73_ = lean_box(0);
lean_inc(v_x_64_);
v___x_74_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_reachableSumsList_spec__0(v_head_66_, v_x_64_, v___x_73_);
v___x_75_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_reachableSumsList_spec__1(v_cap_63_, v___x_74_, v___x_73_);
v___x_76_ = l_List_appendTR___redArg(v_x_64_, v___x_75_);
v_x_64_ = v___x_76_;
v_x_65_ = v_tail_67_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2___boxed(lean_object* v_cap_78_, lean_object* v_x_79_, lean_object* v_x_80_){
_start:
{
lean_object* v_res_81_; 
v_res_81_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2(v_cap_78_, v_x_79_, v_x_80_);
lean_dec(v_x_80_);
lean_dec(v_cap_78_);
return v_res_81_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reachableSumsList(lean_object* v_ws_85_, lean_object* v_cap_86_){
_start:
{
lean_object* v___x_87_; lean_object* v___x_88_; 
v___x_87_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_reachableSumsList___closed__0));
v___x_88_ = lp_island__logistics__proof_List_foldl___at___00IslandLogistics_reachableSumsList_spec__2(v_cap_86_, v___x_87_, v_ws_85_);
return v___x_88_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_reachableSumsList___boxed(lean_object* v_ws_89_, lean_object* v_cap_90_){
_start:
{
lean_object* v_res_91_; 
v_res_91_ = lp_island__logistics__proof_IslandLogistics_reachableSumsList(v_ws_89_, v_cap_90_);
lean_dec(v_cap_90_);
lean_dec(v_ws_89_);
return v_res_91_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listMax(lean_object* v_x_92_){
_start:
{
if (lean_obj_tag(v_x_92_) == 0)
{
lean_object* v___x_93_; 
v___x_93_ = lean_unsigned_to_nat(0u);
return v___x_93_;
}
else
{
lean_object* v_head_94_; lean_object* v_tail_95_; lean_object* v___x_96_; uint8_t v___x_97_; 
v_head_94_ = lean_ctor_get(v_x_92_, 0);
v_tail_95_ = lean_ctor_get(v_x_92_, 1);
v___x_96_ = lp_island__logistics__proof_IslandLogistics_listMax(v_tail_95_);
v___x_97_ = lean_nat_dec_le(v_head_94_, v___x_96_);
if (v___x_97_ == 0)
{
lean_dec(v___x_96_);
lean_inc(v_head_94_);
return v_head_94_;
}
else
{
return v___x_96_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listMax___boxed(lean_object* v_x_98_){
_start:
{
lean_object* v_res_99_; 
v_res_99_ = lp_island__logistics__proof_IslandLogistics_listMax(v_x_98_);
lean_dec(v_x_98_);
return v_res_99_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_effCap_spec__0(lean_object* v___x_100_, lean_object* v_a_101_, lean_object* v_a_102_){
_start:
{
if (lean_obj_tag(v_a_101_) == 0)
{
lean_object* v___x_103_; 
lean_dec_ref(v___x_100_);
v___x_103_ = l_List_reverse___redArg(v_a_102_);
return v___x_103_;
}
else
{
lean_object* v_head_104_; lean_object* v_tail_105_; lean_object* v___x_107_; uint8_t v_isShared_108_; uint8_t v_isSharedCheck_114_; 
v_head_104_ = lean_ctor_get(v_a_101_, 0);
v_tail_105_ = lean_ctor_get(v_a_101_, 1);
v_isSharedCheck_114_ = !lean_is_exclusive(v_a_101_);
if (v_isSharedCheck_114_ == 0)
{
v___x_107_ = v_a_101_;
v_isShared_108_ = v_isSharedCheck_114_;
goto v_resetjp_106_;
}
else
{
lean_inc(v_tail_105_);
lean_inc(v_head_104_);
lean_dec(v_a_101_);
v___x_107_ = lean_box(0);
v_isShared_108_ = v_isSharedCheck_114_;
goto v_resetjp_106_;
}
v_resetjp_106_:
{
lean_object* v___x_109_; lean_object* v___x_111_; 
lean_inc_ref(v___x_100_);
v___x_109_ = lean_apply_1(v___x_100_, v_head_104_);
if (v_isShared_108_ == 0)
{
lean_ctor_set(v___x_107_, 1, v_a_102_);
lean_ctor_set(v___x_107_, 0, v___x_109_);
v___x_111_ = v___x_107_;
goto v_reusejp_110_;
}
else
{
lean_object* v_reuseFailAlloc_113_; 
v_reuseFailAlloc_113_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_113_, 0, v___x_109_);
lean_ctor_set(v_reuseFailAlloc_113_, 1, v_a_102_);
v___x_111_ = v_reuseFailAlloc_113_;
goto v_reusejp_110_;
}
v_reusejp_110_:
{
v_a_101_ = v_tail_105_;
v_a_102_ = v___x_111_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_effCap(lean_object* v_I_115_, lean_object* v_c_116_){
_start:
{
lean_object* v_numPkgs_117_; lean_object* v_pkgWeight_118_; lean_object* v___x_119_; lean_object* v___x_120_; lean_object* v___x_121_; lean_object* v___x_122_; lean_object* v___x_123_; 
v_numPkgs_117_ = lean_ctor_get(v_I_115_, 8);
lean_inc(v_numPkgs_117_);
v_pkgWeight_118_ = lean_ctor_get(v_I_115_, 9);
lean_inc_ref(v_pkgWeight_118_);
lean_dec_ref(v_I_115_);
v___x_119_ = l_List_finRange(v_numPkgs_117_);
v___x_120_ = lean_box(0);
v___x_121_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_effCap_spec__0(v_pkgWeight_118_, v___x_119_, v___x_120_);
v___x_122_ = lp_island__logistics__proof_IslandLogistics_reachableSumsList(v___x_121_, v_c_116_);
lean_dec(v___x_121_);
v___x_123_ = lp_island__logistics__proof_IslandLogistics_listMax(v___x_122_);
lean_dec(v___x_122_);
return v___x_123_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_effCap___boxed(lean_object* v_I_124_, lean_object* v_c_125_){
_start:
{
lean_object* v_res_126_; 
v_res_126_ = lp_island__logistics__proof_IslandLogistics_effCap(v_I_124_, v_c_125_);
lean_dec(v_c_125_);
return v_res_126_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listGcd(lean_object* v_x_127_){
_start:
{
if (lean_obj_tag(v_x_127_) == 0)
{
lean_object* v___x_128_; 
v___x_128_ = lean_unsigned_to_nat(0u);
return v___x_128_;
}
else
{
lean_object* v_head_129_; lean_object* v_tail_130_; lean_object* v___x_131_; lean_object* v___x_132_; 
v_head_129_ = lean_ctor_get(v_x_127_, 0);
v_tail_130_ = lean_ctor_get(v_x_127_, 1);
v___x_131_ = lp_island__logistics__proof_IslandLogistics_listGcd(v_tail_130_);
v___x_132_ = lean_nat_gcd(v_head_129_, v___x_131_);
lean_dec(v___x_131_);
return v___x_132_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_listGcd___boxed(lean_object* v_x_133_){
_start:
{
lean_object* v_res_134_; 
v_res_134_ = lp_island__logistics__proof_IslandLogistics_listGcd(v_x_133_);
lean_dec(v_x_133_);
return v_res_134_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_undelivGcd_spec__0(lean_object* v_I_135_, lean_object* v_s_136_, lean_object* v_a_137_, lean_object* v_a_138_){
_start:
{
if (lean_obj_tag(v_a_137_) == 0)
{
lean_object* v___x_139_; 
lean_dec_ref(v_s_136_);
lean_dec_ref(v_I_135_);
v___x_139_ = l_List_reverse___redArg(v_a_138_);
return v___x_139_;
}
else
{
lean_object* v_head_140_; lean_object* v_tail_141_; lean_object* v___x_143_; uint8_t v_isShared_144_; uint8_t v_isSharedCheck_151_; 
v_head_140_ = lean_ctor_get(v_a_137_, 0);
v_tail_141_ = lean_ctor_get(v_a_137_, 1);
v_isSharedCheck_151_ = !lean_is_exclusive(v_a_137_);
if (v_isSharedCheck_151_ == 0)
{
v___x_143_ = v_a_137_;
v_isShared_144_ = v_isSharedCheck_151_;
goto v_resetjp_142_;
}
else
{
lean_inc(v_tail_141_);
lean_inc(v_head_140_);
lean_dec(v_a_137_);
v___x_143_ = lean_box(0);
v_isShared_144_ = v_isSharedCheck_151_;
goto v_resetjp_142_;
}
v_resetjp_142_:
{
uint8_t v___x_145_; 
lean_inc(v_head_140_);
lean_inc_ref(v_s_136_);
lean_inc_ref(v_I_135_);
v___x_145_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_135_, v_s_136_, v_head_140_);
if (v___x_145_ == 0)
{
lean_object* v___x_147_; 
if (v_isShared_144_ == 0)
{
lean_ctor_set(v___x_143_, 1, v_a_138_);
v___x_147_ = v___x_143_;
goto v_reusejp_146_;
}
else
{
lean_object* v_reuseFailAlloc_149_; 
v_reuseFailAlloc_149_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_149_, 0, v_head_140_);
lean_ctor_set(v_reuseFailAlloc_149_, 1, v_a_138_);
v___x_147_ = v_reuseFailAlloc_149_;
goto v_reusejp_146_;
}
v_reusejp_146_:
{
v_a_137_ = v_tail_141_;
v_a_138_ = v___x_147_;
goto _start;
}
}
else
{
lean_del_object(v___x_143_);
lean_dec(v_head_140_);
v_a_137_ = v_tail_141_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_undelivGcd(lean_object* v_I_152_, lean_object* v_s_153_){
_start:
{
lean_object* v_numPkgs_154_; lean_object* v_pkgWeight_155_; lean_object* v___x_156_; lean_object* v___x_157_; lean_object* v___x_158_; lean_object* v___x_159_; lean_object* v___x_160_; 
v_numPkgs_154_ = lean_ctor_get(v_I_152_, 8);
v_pkgWeight_155_ = lean_ctor_get(v_I_152_, 9);
lean_inc_ref(v_pkgWeight_155_);
lean_inc(v_numPkgs_154_);
v___x_156_ = l_List_finRange(v_numPkgs_154_);
v___x_157_ = lean_box(0);
v___x_158_ = lp_island__logistics__proof_List_filterTR_loop___at___00IslandLogistics_undelivGcd_spec__0(v_I_152_, v_s_153_, v___x_156_, v___x_157_);
v___x_159_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_effCap_spec__0(v_pkgWeight_155_, v___x_158_, v___x_157_);
v___x_160_ = lp_island__logistics__proof_IslandLogistics_listGcd(v___x_159_);
lean_dec(v___x_159_);
return v___x_160_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_initWGcd(lean_object* v_I_161_){
_start:
{
lean_object* v_numPkgs_162_; lean_object* v_pkgWeight_163_; lean_object* v___x_164_; lean_object* v___x_165_; lean_object* v___x_166_; lean_object* v___x_167_; 
v_numPkgs_162_ = lean_ctor_get(v_I_161_, 8);
lean_inc(v_numPkgs_162_);
v_pkgWeight_163_ = lean_ctor_get(v_I_161_, 9);
lean_inc_ref(v_pkgWeight_163_);
lean_dec_ref(v_I_161_);
v___x_164_ = l_List_finRange(v_numPkgs_162_);
v___x_165_ = lean_box(0);
v___x_166_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_effCap_spec__0(v_pkgWeight_163_, v___x_164_, v___x_165_);
v___x_167_ = lp_island__logistics__proof_IslandLogistics_listGcd(v___x_166_);
lean_dec(v___x_166_);
return v___x_167_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_dynEffCap(lean_object* v_I_168_, lean_object* v_s_169_, lean_object* v_t_170_){
_start:
{
lean_object* v_truckCap_171_; lean_object* v___x_172_; lean_object* v_base_173_; lean_object* v_g_174_; lean_object* v___x_175_; uint8_t v___x_176_; 
v_truckCap_171_ = lean_ctor_get(v_I_168_, 4);
lean_inc_ref(v_truckCap_171_);
v___x_172_ = lean_apply_1(v_truckCap_171_, v_t_170_);
lean_inc_ref_n(v_I_168_, 2);
v_base_173_ = lp_island__logistics__proof_IslandLogistics_effCap(v_I_168_, v___x_172_);
lean_dec(v___x_172_);
v_g_174_ = lp_island__logistics__proof_IslandLogistics_undelivGcd(v_I_168_, v_s_169_);
v___x_175_ = lp_island__logistics__proof_IslandLogistics_initWGcd(v_I_168_);
v___x_176_ = lean_nat_dec_lt(v___x_175_, v_g_174_);
lean_dec(v___x_175_);
if (v___x_176_ == 0)
{
lean_dec(v_g_174_);
return v_base_173_;
}
else
{
lean_object* v___x_177_; lean_object* v___x_178_; 
v___x_177_ = lean_nat_div(v_base_173_, v_g_174_);
lean_dec(v_base_173_);
v___x_178_ = lean_nat_mul(v___x_177_, v_g_174_);
lean_dec(v_g_174_);
lean_dec(v___x_177_);
return v___x_178_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(lean_object* v_I_179_, lean_object* v_s_180_, lean_object* v_a_181_, lean_object* v_a_182_){
_start:
{
if (lean_obj_tag(v_a_181_) == 0)
{
lean_object* v___x_183_; 
lean_dec_ref(v_s_180_);
lean_dec_ref(v_I_179_);
v___x_183_ = l_List_reverse___redArg(v_a_182_);
return v___x_183_;
}
else
{
lean_object* v_head_184_; lean_object* v_tail_185_; lean_object* v___x_187_; uint8_t v_isShared_188_; uint8_t v_isSharedCheck_194_; 
v_head_184_ = lean_ctor_get(v_a_181_, 0);
v_tail_185_ = lean_ctor_get(v_a_181_, 1);
v_isSharedCheck_194_ = !lean_is_exclusive(v_a_181_);
if (v_isSharedCheck_194_ == 0)
{
v___x_187_ = v_a_181_;
v_isShared_188_ = v_isSharedCheck_194_;
goto v_resetjp_186_;
}
else
{
lean_inc(v_tail_185_);
lean_inc(v_head_184_);
lean_dec(v_a_181_);
v___x_187_ = lean_box(0);
v_isShared_188_ = v_isSharedCheck_194_;
goto v_resetjp_186_;
}
v_resetjp_186_:
{
lean_object* v___x_189_; lean_object* v___x_191_; 
lean_inc_ref(v_s_180_);
lean_inc_ref(v_I_179_);
v___x_189_ = lp_island__logistics__proof_IslandLogistics_dynEffCap(v_I_179_, v_s_180_, v_head_184_);
if (v_isShared_188_ == 0)
{
lean_ctor_set(v___x_187_, 1, v_a_182_);
lean_ctor_set(v___x_187_, 0, v___x_189_);
v___x_191_ = v___x_187_;
goto v_reusejp_190_;
}
else
{
lean_object* v_reuseFailAlloc_193_; 
v_reuseFailAlloc_193_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_193_, 0, v___x_189_);
lean_ctor_set(v_reuseFailAlloc_193_, 1, v_a_182_);
v___x_191_ = v_reuseFailAlloc_193_;
goto v_reusejp_190_;
}
v_reusejp_190_:
{
v_a_181_ = v_tail_185_;
v_a_182_ = v___x_191_;
goto _start;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_maxDynEffCap(lean_object* v_I_195_, lean_object* v_s_196_){
_start:
{
lean_object* v_numTrucks_197_; lean_object* v___x_198_; lean_object* v___x_199_; lean_object* v___x_200_; lean_object* v___x_201_; 
v_numTrucks_197_ = lean_ctor_get(v_I_195_, 3);
lean_inc(v_numTrucks_197_);
v___x_198_ = l_List_finRange(v_numTrucks_197_);
v___x_199_ = lean_box(0);
v___x_200_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(v_I_195_, v_s_196_, v___x_198_, v___x_199_);
v___x_201_ = lp_island__logistics__proof_IslandLogistics_listMax(v___x_200_);
lean_dec(v___x_200_);
return v___x_201_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_insertDesc(lean_object* v_x_202_, lean_object* v_x_203_){
_start:
{
if (lean_obj_tag(v_x_203_) == 0)
{
lean_object* v___x_204_; 
v___x_204_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_204_, 0, v_x_202_);
lean_ctor_set(v___x_204_, 1, v_x_203_);
return v___x_204_;
}
else
{
lean_object* v_head_205_; lean_object* v_tail_206_; uint8_t v___x_207_; 
v_head_205_ = lean_ctor_get(v_x_203_, 0);
v_tail_206_ = lean_ctor_get(v_x_203_, 1);
v___x_207_ = lean_nat_dec_le(v_head_205_, v_x_202_);
if (v___x_207_ == 0)
{
lean_object* v___x_209_; uint8_t v_isShared_210_; uint8_t v_isSharedCheck_215_; 
lean_inc(v_tail_206_);
lean_inc(v_head_205_);
v_isSharedCheck_215_ = !lean_is_exclusive(v_x_203_);
if (v_isSharedCheck_215_ == 0)
{
lean_object* v_unused_216_; lean_object* v_unused_217_; 
v_unused_216_ = lean_ctor_get(v_x_203_, 1);
lean_dec(v_unused_216_);
v_unused_217_ = lean_ctor_get(v_x_203_, 0);
lean_dec(v_unused_217_);
v___x_209_ = v_x_203_;
v_isShared_210_ = v_isSharedCheck_215_;
goto v_resetjp_208_;
}
else
{
lean_dec(v_x_203_);
v___x_209_ = lean_box(0);
v_isShared_210_ = v_isSharedCheck_215_;
goto v_resetjp_208_;
}
v_resetjp_208_:
{
lean_object* v___x_211_; lean_object* v___x_213_; 
v___x_211_ = lp_island__logistics__proof_IslandLogistics_insertDesc(v_x_202_, v_tail_206_);
if (v_isShared_210_ == 0)
{
lean_ctor_set(v___x_209_, 1, v___x_211_);
v___x_213_ = v___x_209_;
goto v_reusejp_212_;
}
else
{
lean_object* v_reuseFailAlloc_214_; 
v_reuseFailAlloc_214_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_214_, 0, v_head_205_);
lean_ctor_set(v_reuseFailAlloc_214_, 1, v___x_211_);
v___x_213_ = v_reuseFailAlloc_214_;
goto v_reusejp_212_;
}
v_reusejp_212_:
{
return v___x_213_;
}
}
}
else
{
lean_object* v___x_218_; 
v___x_218_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v___x_218_, 0, v_x_202_);
lean_ctor_set(v___x_218_, 1, v_x_203_);
return v___x_218_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_sortDesc(lean_object* v_x_219_){
_start:
{
if (lean_obj_tag(v_x_219_) == 0)
{
return v_x_219_;
}
else
{
lean_object* v_head_220_; lean_object* v_tail_221_; lean_object* v___x_222_; lean_object* v___x_223_; 
v_head_220_ = lean_ctor_get(v_x_219_, 0);
lean_inc(v_head_220_);
v_tail_221_ = lean_ctor_get(v_x_219_, 1);
lean_inc(v_tail_221_);
lean_dec_ref_known(v_x_219_, 2);
v___x_222_ = lp_island__logistics__proof_IslandLogistics_sortDesc(v_tail_221_);
v___x_223_ = lp_island__logistics__proof_IslandLogistics_insertDesc(v_head_220_, v___x_222_);
return v___x_223_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_topKSum(lean_object* v_xs_226_, lean_object* v_k_227_){
_start:
{
lean_object* v___x_228_; lean_object* v___x_229_; lean_object* v___x_230_; lean_object* v___x_231_; 
v___x_228_ = lp_island__logistics__proof_IslandLogistics_sortDesc(v_xs_226_);
v___x_229_ = ((lean_object*)(lp_island__logistics__proof_IslandLogistics_topKSum___closed__0));
lean_inc(v___x_228_);
v___x_230_ = l___private_Init_Data_List_Impl_0__List_takeTR_go___redArg(v___x_228_, v___x_228_, v_k_227_, v___x_229_);
lean_dec(v___x_228_);
v___x_231_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_230_);
lean_dec(v___x_230_);
return v___x_231_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_maxFerryWeight(lean_object* v_I_232_, lean_object* v_s_233_, lean_object* v_f_234_){
_start:
{
lean_object* v_numTrucks_235_; lean_object* v_ferryCap_236_; lean_object* v___x_237_; lean_object* v___x_238_; lean_object* v___x_239_; lean_object* v___x_240_; uint8_t v___x_241_; 
v_numTrucks_235_ = lean_ctor_get(v_I_232_, 3);
lean_inc_n(v_numTrucks_235_, 2);
v_ferryCap_236_ = lean_ctor_get(v_I_232_, 6);
lean_inc_ref(v_ferryCap_236_);
v___x_237_ = l_List_finRange(v_numTrucks_235_);
v___x_238_ = lean_box(0);
v___x_239_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_maxDynEffCap_spec__0(v_I_232_, v_s_233_, v___x_237_, v___x_238_);
v___x_240_ = lean_apply_1(v_ferryCap_236_, v_f_234_);
v___x_241_ = lean_nat_dec_le(v___x_240_, v_numTrucks_235_);
if (v___x_241_ == 0)
{
lean_object* v___x_242_; 
lean_dec(v___x_240_);
v___x_242_ = lp_island__logistics__proof_IslandLogistics_topKSum(v___x_239_, v_numTrucks_235_);
return v___x_242_;
}
else
{
lean_object* v___x_243_; 
lean_dec(v_numTrucks_235_);
v___x_243_ = lp_island__logistics__proof_IslandLogistics_topKSum(v___x_239_, v___x_240_);
return v___x_243_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___redArg(lean_object* v_x_244_, lean_object* v_h__1_245_, lean_object* v_h__2_246_){
_start:
{
if (lean_obj_tag(v_x_244_) == 0)
{
lean_object* v_l_247_; lean_object* v___x_248_; 
lean_dec(v_h__2_246_);
v_l_247_ = lean_ctor_get(v_x_244_, 0);
lean_inc(v_l_247_);
lean_dec_ref_known(v_x_244_, 1);
v___x_248_ = lean_apply_1(v_h__1_245_, v_l_247_);
return v___x_248_;
}
else
{
lean_object* v_f_249_; lean_object* v___x_250_; 
lean_dec(v_h__1_245_);
v_f_249_ = lean_ctor_get(v_x_244_, 0);
lean_inc(v_f_249_);
lean_dec_ref_known(v_x_244_, 1);
v___x_250_ = lean_apply_1(v_h__2_246_, v_f_249_);
return v___x_250_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(lean_object* v_I_251_, lean_object* v_motive_252_, lean_object* v_x_253_, lean_object* v_h__1_254_, lean_object* v_h__2_255_){
_start:
{
if (lean_obj_tag(v_x_253_) == 0)
{
lean_object* v_l_256_; lean_object* v___x_257_; 
lean_dec(v_h__2_255_);
v_l_256_ = lean_ctor_get(v_x_253_, 0);
lean_inc(v_l_256_);
lean_dec_ref_known(v_x_253_, 1);
v___x_257_ = lean_apply_1(v_h__1_254_, v_l_256_);
return v___x_257_;
}
else
{
lean_object* v_f_258_; lean_object* v___x_259_; 
lean_dec(v_h__1_254_);
v_f_258_ = lean_ctor_get(v_x_253_, 0);
lean_inc(v_f_258_);
lean_dec_ref_known(v_x_253_, 1);
v___x_259_ = lean_apply_1(v_h__2_255_, v_f_258_);
return v___x_259_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter___boxed(lean_object* v_I_260_, lean_object* v_motive_261_, lean_object* v_x_262_, lean_object* v_h__1_263_, lean_object* v_h__2_264_){
_start:
{
lean_object* v_res_265_; 
v_res_265_ = lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_truckPhysLoc_match__1_splitter(v_I_260_, v_motive_261_, v_x_262_, v_h__1_263_, v_h__2_264_);
lean_dec_ref(v_I_260_);
return v_res_265_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_packLB(lean_object* v_heavy__d_266_, lean_object* v_min__hw_267_, lean_object* v_light__wd_268_, lean_object* v_total__wd_269_, lean_object* v_cap_270_){
_start:
{
lean_object* v___y_272_; lean_object* v___y_273_; lean_object* v___x_276_; lean_object* v_cm1_277_; lean_object* v___x_278_; lean_object* v___y_280_; uint8_t v___x_288_; 
v___x_276_ = lean_unsigned_to_nat(1u);
v_cm1_277_ = lean_nat_sub(v_cap_270_, v___x_276_);
v___x_278_ = lean_unsigned_to_nat(0u);
v___x_288_ = lean_nat_dec_lt(v___x_278_, v_total__wd_269_);
if (v___x_288_ == 0)
{
v___y_280_ = v___x_278_;
goto v___jp_279_;
}
else
{
lean_object* v___x_289_; lean_object* v___x_290_; 
v___x_289_ = lean_nat_add(v_total__wd_269_, v_cm1_277_);
v___x_290_ = lean_nat_div(v___x_289_, v_cap_270_);
lean_dec(v___x_289_);
v___y_280_ = v___x_290_;
goto v___jp_279_;
}
v___jp_271_:
{
lean_object* v_cand_274_; uint8_t v___x_275_; 
v_cand_274_ = lean_nat_add(v_heavy__d_266_, v___y_273_);
lean_dec(v___y_273_);
v___x_275_ = lean_nat_dec_lt(v___y_272_, v_cand_274_);
if (v___x_275_ == 0)
{
lean_dec(v_cand_274_);
return v___y_272_;
}
else
{
lean_dec(v___y_272_);
return v_cand_274_;
}
}
v___jp_279_:
{
uint8_t v___x_281_; 
v___x_281_ = lean_nat_dec_lt(v___x_278_, v_heavy__d_266_);
if (v___x_281_ == 0)
{
lean_dec(v_cm1_277_);
return v___y_280_;
}
else
{
lean_object* v___x_282_; lean_object* v___x_283_; lean_object* v_rem_284_; uint8_t v___x_285_; 
v___x_282_ = lean_nat_sub(v_cap_270_, v_min__hw_267_);
v___x_283_ = lean_nat_mul(v___x_282_, v_heavy__d_266_);
lean_dec(v___x_282_);
v_rem_284_ = lean_nat_sub(v_light__wd_268_, v___x_283_);
lean_dec(v___x_283_);
v___x_285_ = lean_nat_dec_lt(v___x_278_, v_rem_284_);
if (v___x_285_ == 0)
{
lean_dec(v_rem_284_);
lean_dec(v_cm1_277_);
v___y_272_ = v___y_280_;
v___y_273_ = v___x_278_;
goto v___jp_271_;
}
else
{
lean_object* v___x_286_; lean_object* v___x_287_; 
v___x_286_ = lean_nat_add(v_rem_284_, v_cm1_277_);
lean_dec(v_cm1_277_);
lean_dec(v_rem_284_);
v___x_287_ = lean_nat_div(v___x_286_, v_cap_270_);
lean_dec(v___x_286_);
v___y_272_ = v___y_280_;
v___y_273_ = v___x_287_;
goto v___jp_271_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_packLB___boxed(lean_object* v_heavy__d_291_, lean_object* v_min__hw_292_, lean_object* v_light__wd_293_, lean_object* v_total__wd_294_, lean_object* v_cap_295_){
_start:
{
lean_object* v_res_296_; 
v_res_296_ = lp_island__logistics__proof_IslandLogistics_packLB(v_heavy__d_291_, v_min__hw_292_, v_light__wd_293_, v_total__wd_294_, v_cap_295_);
lean_dec(v_cap_295_);
lean_dec(v_total__wd_294_);
lean_dec(v_light__wd_293_);
lean_dec(v_min__hw_292_);
lean_dec(v_heavy__d_291_);
return v_res_296_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_countActions_spec__0(lean_object* v_pred_297_, lean_object* v_a_298_, lean_object* v_a_299_){
_start:
{
if (lean_obj_tag(v_a_298_) == 0)
{
lean_object* v___x_300_; 
lean_dec_ref(v_pred_297_);
v___x_300_ = l_List_reverse___redArg(v_a_299_);
return v___x_300_;
}
else
{
lean_object* v_head_301_; lean_object* v_tail_302_; lean_object* v___x_304_; uint8_t v_isShared_305_; uint8_t v_isSharedCheck_316_; 
v_head_301_ = lean_ctor_get(v_a_298_, 0);
v_tail_302_ = lean_ctor_get(v_a_298_, 1);
v_isSharedCheck_316_ = !lean_is_exclusive(v_a_298_);
if (v_isSharedCheck_316_ == 0)
{
v___x_304_ = v_a_298_;
v_isShared_305_ = v_isSharedCheck_316_;
goto v_resetjp_303_;
}
else
{
lean_inc(v_tail_302_);
lean_inc(v_head_301_);
lean_dec(v_a_298_);
v___x_304_ = lean_box(0);
v_isShared_305_ = v_isSharedCheck_316_;
goto v_resetjp_303_;
}
v_resetjp_303_:
{
lean_object* v___y_307_; lean_object* v___x_312_; uint8_t v___x_313_; 
lean_inc_ref(v_pred_297_);
v___x_312_ = lean_apply_1(v_pred_297_, v_head_301_);
v___x_313_ = lean_unbox(v___x_312_);
if (v___x_313_ == 0)
{
lean_object* v___x_314_; 
v___x_314_ = lean_unsigned_to_nat(0u);
v___y_307_ = v___x_314_;
goto v___jp_306_;
}
else
{
lean_object* v___x_315_; 
v___x_315_ = lean_unsigned_to_nat(1u);
v___y_307_ = v___x_315_;
goto v___jp_306_;
}
v___jp_306_:
{
lean_object* v___x_309_; 
if (v_isShared_305_ == 0)
{
lean_ctor_set(v___x_304_, 1, v_a_299_);
lean_ctor_set(v___x_304_, 0, v___y_307_);
v___x_309_ = v___x_304_;
goto v_reusejp_308_;
}
else
{
lean_object* v_reuseFailAlloc_311_; 
v_reuseFailAlloc_311_ = lean_alloc_ctor(1, 2, 0);
lean_ctor_set(v_reuseFailAlloc_311_, 0, v___y_307_);
lean_ctor_set(v_reuseFailAlloc_311_, 1, v_a_299_);
v___x_309_ = v_reuseFailAlloc_311_;
goto v_reusejp_308_;
}
v_reusejp_308_:
{
v_a_298_ = v_tail_302_;
v_a_299_ = v___x_309_;
goto _start;
}
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions___redArg(lean_object* v_pred_317_, lean_object* v_00_u03c0_318_){
_start:
{
lean_object* v___x_319_; lean_object* v___x_320_; lean_object* v___x_321_; 
v___x_319_ = lean_box(0);
v___x_320_ = lp_island__logistics__proof_List_mapTR_loop___at___00IslandLogistics_countActions_spec__0(v_pred_317_, v_00_u03c0_318_, v___x_319_);
v___x_321_ = lp_island__logistics__proof_List_sum___at___00IslandLogistics_planCost_spec__1(v___x_320_);
lean_dec(v___x_320_);
return v___x_321_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions(lean_object* v_I_322_, lean_object* v_pred_323_, lean_object* v_00_u03c0_324_){
_start:
{
lean_object* v___x_325_; 
v___x_325_ = lp_island__logistics__proof_IslandLogistics_countActions___redArg(v_pred_323_, v_00_u03c0_324_);
return v___x_325_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_countActions___boxed(lean_object* v_I_326_, lean_object* v_pred_327_, lean_object* v_00_u03c0_328_){
_start:
{
lean_object* v_res_329_; 
v_res_329_ = lp_island__logistics__proof_IslandLogistics_countActions(v_I_326_, v_pred_327_, v_00_u03c0_328_);
lean_dec_ref(v_I_326_);
return v_res_329_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB(lean_object* v_w__ab_330_, lean_object* v_w__ba_331_, lean_object* v_h__ab_332_, lean_object* v_h__ba_333_, uint8_t v_need__ab_334_, uint8_t v_need__ba_335_, lean_object* v_m__a_336_, lean_object* v_m__b_337_, lean_object* v_c__a_338_, lean_object* v_c__b_339_, lean_object* v_cap_340_){
_start:
{
lean_object* v___x_341_; lean_object* v_cm1_342_; lean_object* v___y_344_; lean_object* v___y_345_; lean_object* v___y_355_; lean_object* v___y_356_; lean_object* v___y_357_; lean_object* v___y_361_; lean_object* v___y_362_; lean_object* v___y_363_; lean_object* v___y_370_; lean_object* v___y_371_; lean_object* v___y_375_; lean_object* v___y_376_; lean_object* v___y_379_; lean_object* v___y_380_; lean_object* v___x_382_; lean_object* v___y_384_; lean_object* v___y_389_; lean_object* v___y_392_; uint8_t v___x_394_; 
v___x_341_ = lean_unsigned_to_nat(1u);
v_cm1_342_ = lean_nat_sub(v_cap_340_, v___x_341_);
v___x_382_ = lean_unsigned_to_nat(0u);
v___x_394_ = lean_nat_dec_lt(v___x_382_, v_w__ab_330_);
if (v___x_394_ == 0)
{
v___y_392_ = v___x_382_;
goto v___jp_391_;
}
else
{
lean_object* v___x_395_; lean_object* v___x_396_; 
v___x_395_ = lean_nat_add(v_w__ab_330_, v_cm1_342_);
v___x_396_ = lean_nat_div(v___x_395_, v_cap_340_);
lean_dec(v___x_395_);
v___y_392_ = v___x_396_;
goto v___jp_391_;
}
v___jp_343_:
{
uint8_t v___x_346_; 
v___x_346_ = lean_nat_dec_lt(v_c__a_338_, v_w__ab_330_);
if (v___x_346_ == 0)
{
lean_object* v___x_347_; 
lean_dec(v_cm1_342_);
v___x_347_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_347_, 0, v___y_344_);
lean_ctor_set(v___x_347_, 1, v___y_345_);
return v___x_347_;
}
else
{
lean_object* v___x_348_; lean_object* v___x_349_; lean_object* v_cw_350_; uint8_t v___x_351_; 
v___x_348_ = lean_nat_sub(v_w__ab_330_, v_c__a_338_);
v___x_349_ = lean_nat_add(v___x_348_, v_cm1_342_);
lean_dec(v_cm1_342_);
lean_dec(v___x_348_);
v_cw_350_ = lean_nat_div(v___x_349_, v_cap_340_);
lean_dec(v___x_349_);
v___x_351_ = lean_nat_dec_lt(v___y_345_, v_cw_350_);
if (v___x_351_ == 0)
{
lean_object* v___x_352_; 
lean_dec(v_cw_350_);
v___x_352_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_352_, 0, v___y_344_);
lean_ctor_set(v___x_352_, 1, v___y_345_);
return v___x_352_;
}
else
{
lean_object* v___x_353_; 
lean_dec(v___y_345_);
v___x_353_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_353_, 0, v___y_344_);
lean_ctor_set(v___x_353_, 1, v_cw_350_);
return v___x_353_;
}
}
}
v___jp_354_:
{
lean_object* v___x_358_; uint8_t v___x_359_; 
v___x_358_ = lean_nat_sub(v___y_356_, v_m__a_336_);
lean_dec(v___y_356_);
v___x_359_ = lean_nat_dec_lt(v___y_355_, v___x_358_);
if (v___x_359_ == 0)
{
lean_dec(v___x_358_);
v___y_344_ = v___y_357_;
v___y_345_ = v___y_355_;
goto v___jp_343_;
}
else
{
lean_dec(v___y_355_);
v___y_344_ = v___y_357_;
v___y_345_ = v___x_358_;
goto v___jp_343_;
}
}
v___jp_360_:
{
uint8_t v___x_364_; 
v___x_364_ = lean_nat_dec_lt(v_c__b_339_, v_w__ba_331_);
if (v___x_364_ == 0)
{
v___y_355_ = v___y_361_;
v___y_356_ = v___y_362_;
v___y_357_ = v___y_363_;
goto v___jp_354_;
}
else
{
lean_object* v___x_365_; lean_object* v___x_366_; lean_object* v_cw_367_; uint8_t v___x_368_; 
v___x_365_ = lean_nat_sub(v_w__ba_331_, v_c__b_339_);
v___x_366_ = lean_nat_add(v___x_365_, v_cm1_342_);
lean_dec(v___x_365_);
v_cw_367_ = lean_nat_div(v___x_366_, v_cap_340_);
lean_dec(v___x_366_);
v___x_368_ = lean_nat_dec_lt(v___y_363_, v_cw_367_);
if (v___x_368_ == 0)
{
lean_dec(v_cw_367_);
v___y_355_ = v___y_361_;
v___y_356_ = v___y_362_;
v___y_357_ = v___y_363_;
goto v___jp_354_;
}
else
{
lean_dec(v___y_363_);
v___y_355_ = v___y_361_;
v___y_356_ = v___y_362_;
v___y_357_ = v_cw_367_;
goto v___jp_354_;
}
}
}
v___jp_369_:
{
lean_object* v___x_372_; uint8_t v___x_373_; 
v___x_372_ = lean_nat_sub(v___y_371_, v_m__b_337_);
v___x_373_ = lean_nat_dec_lt(v___y_370_, v___x_372_);
if (v___x_373_ == 0)
{
lean_dec(v___x_372_);
lean_inc(v___y_370_);
v___y_361_ = v___y_371_;
v___y_362_ = v___y_370_;
v___y_363_ = v___y_370_;
goto v___jp_360_;
}
else
{
v___y_361_ = v___y_371_;
v___y_362_ = v___y_370_;
v___y_363_ = v___x_372_;
goto v___jp_360_;
}
}
v___jp_374_:
{
if (v_need__ba_335_ == 0)
{
v___y_370_ = v___y_375_;
v___y_371_ = v___y_376_;
goto v___jp_369_;
}
else
{
uint8_t v___x_377_; 
v___x_377_ = lean_nat_dec_lt(v___y_376_, v___x_341_);
if (v___x_377_ == 0)
{
v___y_370_ = v___y_375_;
v___y_371_ = v___y_376_;
goto v___jp_369_;
}
else
{
lean_dec(v___y_376_);
v___y_370_ = v___y_375_;
v___y_371_ = v___x_341_;
goto v___jp_369_;
}
}
}
v___jp_378_:
{
uint8_t v___x_381_; 
v___x_381_ = lean_nat_dec_lt(v___y_380_, v_h__ba_333_);
if (v___x_381_ == 0)
{
lean_dec(v_h__ba_333_);
v___y_375_ = v___y_379_;
v___y_376_ = v___y_380_;
goto v___jp_374_;
}
else
{
lean_dec(v___y_380_);
v___y_375_ = v___y_379_;
v___y_376_ = v_h__ba_333_;
goto v___jp_374_;
}
}
v___jp_383_:
{
uint8_t v___x_385_; 
v___x_385_ = lean_nat_dec_lt(v___x_382_, v_w__ba_331_);
if (v___x_385_ == 0)
{
v___y_379_ = v___y_384_;
v___y_380_ = v___x_382_;
goto v___jp_378_;
}
else
{
lean_object* v___x_386_; lean_object* v___x_387_; 
v___x_386_ = lean_nat_add(v_w__ba_331_, v_cm1_342_);
v___x_387_ = lean_nat_div(v___x_386_, v_cap_340_);
lean_dec(v___x_386_);
v___y_379_ = v___y_384_;
v___y_380_ = v___x_387_;
goto v___jp_378_;
}
}
v___jp_388_:
{
if (v_need__ab_334_ == 0)
{
v___y_384_ = v___y_389_;
goto v___jp_383_;
}
else
{
uint8_t v___x_390_; 
v___x_390_ = lean_nat_dec_lt(v___y_389_, v___x_341_);
if (v___x_390_ == 0)
{
v___y_384_ = v___y_389_;
goto v___jp_383_;
}
else
{
lean_dec(v___y_389_);
v___y_384_ = v___x_341_;
goto v___jp_383_;
}
}
}
v___jp_391_:
{
uint8_t v___x_393_; 
v___x_393_ = lean_nat_dec_lt(v___y_392_, v_h__ab_332_);
if (v___x_393_ == 0)
{
lean_dec(v_h__ab_332_);
v___y_389_ = v___y_392_;
goto v___jp_388_;
}
else
{
lean_dec(v___y_392_);
v___y_389_ = v_h__ab_332_;
goto v___jp_388_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_fluxLB___boxed(lean_object* v_w__ab_397_, lean_object* v_w__ba_398_, lean_object* v_h__ab_399_, lean_object* v_h__ba_400_, lean_object* v_need__ab_401_, lean_object* v_need__ba_402_, lean_object* v_m__a_403_, lean_object* v_m__b_404_, lean_object* v_c__a_405_, lean_object* v_c__b_406_, lean_object* v_cap_407_){
_start:
{
uint8_t v_need__ab_boxed_408_; uint8_t v_need__ba_boxed_409_; lean_object* v_res_410_; 
v_need__ab_boxed_408_ = lean_unbox(v_need__ab_401_);
v_need__ba_boxed_409_ = lean_unbox(v_need__ba_402_);
v_res_410_ = lp_island__logistics__proof_IslandLogistics_fluxLB(v_w__ab_397_, v_w__ba_398_, v_h__ab_399_, v_h__ba_400_, v_need__ab_boxed_408_, v_need__ba_boxed_409_, v_m__a_403_, v_m__b_404_, v_c__a_405_, v_c__b_406_, v_cap_407_);
lean_dec(v_cap_407_);
lean_dec(v_c__b_406_);
lean_dec(v_c__a_405_);
lean_dec(v_m__b_404_);
lean_dec(v_m__a_403_);
lean_dec(v_w__ba_398_);
lean_dec(v_w__ab_397_);
return v_res_410_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(lean_object* v_inComp_411_, lean_object* v_inA_412_, lean_object* v_s_u2081_413_, lean_object* v_s_u2082_414_, lean_object* v_t_415_){
_start:
{
lean_object* v___x_416_; lean_object* v___x_417_; uint8_t v___x_418_; 
lean_inc(v_t_415_);
v___x_416_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_u2081_413_, v_t_415_);
lean_inc(v___x_416_);
v___x_417_ = lean_apply_1(v_inComp_411_, v___x_416_);
v___x_418_ = lean_unbox(v___x_417_);
if (v___x_418_ == 0)
{
lean_object* v___x_419_; 
lean_dec(v___x_416_);
lean_dec(v_t_415_);
lean_dec_ref(v_s_u2082_414_);
lean_dec_ref(v_inA_412_);
v___x_419_ = lean_unsigned_to_nat(0u);
return v___x_419_;
}
else
{
lean_object* v___x_420_; uint8_t v___x_421_; 
lean_inc_ref(v_inA_412_);
v___x_420_ = lean_apply_1(v_inA_412_, v___x_416_);
v___x_421_ = lean_unbox(v___x_420_);
if (v___x_421_ == 0)
{
lean_object* v___x_422_; 
lean_dec(v_t_415_);
lean_dec_ref(v_s_u2082_414_);
lean_dec_ref(v_inA_412_);
v___x_422_ = lean_unsigned_to_nat(0u);
return v___x_422_;
}
else
{
lean_object* v___x_423_; lean_object* v___x_424_; uint8_t v___x_425_; 
v___x_423_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_u2082_414_, v_t_415_);
v___x_424_ = lean_apply_1(v_inA_412_, v___x_423_);
v___x_425_ = lean_unbox(v___x_424_);
if (v___x_425_ == 0)
{
lean_object* v___x_426_; 
v___x_426_ = lean_unsigned_to_nat(1u);
return v___x_426_;
}
else
{
lean_object* v___x_427_; 
v___x_427_ = lean_unsigned_to_nat(0u);
return v___x_427_;
}
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB(lean_object* v_I_428_, lean_object* v_inComp_429_, lean_object* v_inA_430_, lean_object* v_s_u2081_431_, lean_object* v_s_u2082_432_, lean_object* v_t_433_){
_start:
{
lean_object* v___x_434_; 
v___x_434_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(v_inComp_429_, v_inA_430_, v_s_u2081_431_, v_s_u2082_432_, v_t_433_);
return v___x_434_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___boxed(lean_object* v_I_435_, lean_object* v_inComp_436_, lean_object* v_inA_437_, lean_object* v_s_u2081_438_, lean_object* v_s_u2082_439_, lean_object* v_t_440_){
_start:
{
lean_object* v_res_441_; 
v_res_441_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB(v_I_435_, v_inComp_436_, v_inA_437_, v_s_u2081_438_, v_s_u2082_439_, v_t_440_);
lean_dec_ref(v_I_435_);
return v_res_441_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(lean_object* v_inComp_442_, lean_object* v_inA_443_, lean_object* v_s_u2081_444_, lean_object* v_s_u2082_445_, lean_object* v_t_446_){
_start:
{
lean_object* v___x_447_; lean_object* v___x_448_; uint8_t v___x_449_; 
lean_inc(v_t_446_);
v___x_447_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_u2081_444_, v_t_446_);
lean_inc(v___x_447_);
v___x_448_ = lean_apply_1(v_inComp_442_, v___x_447_);
v___x_449_ = lean_unbox(v___x_448_);
if (v___x_449_ == 0)
{
lean_object* v___x_450_; 
lean_dec(v___x_447_);
lean_dec(v_t_446_);
lean_dec_ref(v_s_u2082_445_);
lean_dec_ref(v_inA_443_);
v___x_450_ = lean_unsigned_to_nat(0u);
return v___x_450_;
}
else
{
lean_object* v___x_451_; uint8_t v___x_452_; 
lean_inc_ref(v_inA_443_);
v___x_451_ = lean_apply_1(v_inA_443_, v___x_447_);
v___x_452_ = lean_unbox(v___x_451_);
if (v___x_452_ == 0)
{
lean_object* v___x_453_; lean_object* v___x_454_; uint8_t v___x_455_; 
v___x_453_ = lp_island__logistics__proof_IslandLogistics_State_truckPhysLoc___redArg(v_s_u2082_445_, v_t_446_);
v___x_454_ = lean_apply_1(v_inA_443_, v___x_453_);
v___x_455_ = lean_unbox(v___x_454_);
if (v___x_455_ == 0)
{
lean_object* v___x_456_; 
v___x_456_ = lean_unsigned_to_nat(0u);
return v___x_456_;
}
else
{
lean_object* v___x_457_; 
v___x_457_ = lean_unsigned_to_nat(1u);
return v___x_457_;
}
}
else
{
lean_object* v___x_458_; 
lean_dec(v_t_446_);
lean_dec_ref(v_s_u2082_445_);
lean_dec_ref(v_inA_443_);
v___x_458_ = lean_unsigned_to_nat(0u);
return v___x_458_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA(lean_object* v_I_459_, lean_object* v_inComp_460_, lean_object* v_inA_461_, lean_object* v_s_u2081_462_, lean_object* v_s_u2082_463_, lean_object* v_t_464_){
_start:
{
lean_object* v___x_465_; 
v___x_465_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(v_inComp_460_, v_inA_461_, v_s_u2081_462_, v_s_u2082_463_, v_t_464_);
return v___x_465_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___boxed(lean_object* v_I_466_, lean_object* v_inComp_467_, lean_object* v_inA_468_, lean_object* v_s_u2081_469_, lean_object* v_s_u2082_470_, lean_object* v_t_471_){
_start:
{
lean_object* v_res_472_; 
v_res_472_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA(v_I_466_, v_inComp_467_, v_inA_468_, v_s_u2081_469_, v_s_u2082_470_, v_t_471_);
lean_dec_ref(v_I_466_);
return v_res_472_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCrossAB(lean_object* v_I_473_, lean_object* v_inComp_474_, lean_object* v_inA_475_, lean_object* v_x_476_, lean_object* v_x_477_, lean_object* v_x_478_){
_start:
{
if (lean_obj_tag(v_x_477_) == 0)
{
lean_object* v___x_479_; 
lean_dec(v_x_478_);
lean_dec_ref(v_x_476_);
lean_dec_ref(v_inA_475_);
lean_dec_ref(v_inComp_474_);
lean_dec_ref(v_I_473_);
v___x_479_ = lean_unsigned_to_nat(0u);
return v___x_479_;
}
else
{
lean_object* v_head_480_; lean_object* v_tail_481_; lean_object* v_sm_482_; lean_object* v___x_483_; lean_object* v___x_484_; lean_object* v___x_485_; 
v_head_480_ = lean_ctor_get(v_x_477_, 0);
lean_inc(v_head_480_);
v_tail_481_ = lean_ctor_get(v_x_477_, 1);
lean_inc(v_tail_481_);
lean_dec_ref_known(v_x_477_, 2);
lean_inc_ref(v_x_476_);
lean_inc_ref(v_I_473_);
v_sm_482_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_473_, v_x_476_, v_head_480_);
lean_inc(v_x_478_);
lean_inc_ref(v_sm_482_);
lean_inc_ref(v_inA_475_);
lean_inc_ref(v_inComp_474_);
v___x_483_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(v_inComp_474_, v_inA_475_, v_x_476_, v_sm_482_, v_x_478_);
v___x_484_ = lp_island__logistics__proof_IslandLogistics_planTruckCrossAB(v_I_473_, v_inComp_474_, v_inA_475_, v_sm_482_, v_tail_481_, v_x_478_);
v___x_485_ = lean_nat_add(v___x_483_, v___x_484_);
lean_dec(v___x_484_);
lean_dec(v___x_483_);
return v___x_485_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCrossBA(lean_object* v_I_486_, lean_object* v_inComp_487_, lean_object* v_inA_488_, lean_object* v_x_489_, lean_object* v_x_490_, lean_object* v_x_491_){
_start:
{
if (lean_obj_tag(v_x_490_) == 0)
{
lean_object* v___x_492_; 
lean_dec(v_x_491_);
lean_dec_ref(v_x_489_);
lean_dec_ref(v_inA_488_);
lean_dec_ref(v_inComp_487_);
lean_dec_ref(v_I_486_);
v___x_492_ = lean_unsigned_to_nat(0u);
return v___x_492_;
}
else
{
lean_object* v_head_493_; lean_object* v_tail_494_; lean_object* v_sm_495_; lean_object* v___x_496_; lean_object* v___x_497_; lean_object* v___x_498_; 
v_head_493_ = lean_ctor_get(v_x_490_, 0);
lean_inc(v_head_493_);
v_tail_494_ = lean_ctor_get(v_x_490_, 1);
lean_inc(v_tail_494_);
lean_dec_ref_known(v_x_490_, 2);
lean_inc_ref(v_x_489_);
lean_inc_ref(v_I_486_);
v_sm_495_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_486_, v_x_489_, v_head_493_);
lean_inc(v_x_491_);
lean_inc_ref(v_sm_495_);
lean_inc_ref(v_inA_488_);
lean_inc_ref(v_inComp_487_);
v___x_496_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(v_inComp_487_, v_inA_488_, v_x_489_, v_sm_495_, v_x_491_);
v___x_497_ = lp_island__logistics__proof_IslandLogistics_planTruckCrossBA(v_I_486_, v_inComp_487_, v_inA_488_, v_sm_495_, v_tail_494_, v_x_491_);
v___x_498_ = lean_nat_add(v___x_496_, v___x_497_);
lean_dec(v___x_497_);
lean_dec(v___x_496_);
return v___x_498_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryAB___lam__0(lean_object* v_I_499_, lean_object* v_s__root_500_, lean_object* v_x_501_, lean_object* v_x_502_, lean_object* v_pkgWeight_503_, lean_object* v_p_504_){
_start:
{
uint8_t v___x_505_; 
lean_inc(v_p_504_);
v___x_505_ = lp_island__logistics__proof_IslandLogistics_State_pkgDelivered(v_I_499_, v_s__root_500_, v_p_504_);
if (v___x_505_ == 0)
{
lean_object* v_pkgLoc_506_; lean_object* v___x_507_; lean_object* v___x_508_; uint8_t v___x_509_; 
v_pkgLoc_506_ = lean_ctor_get(v_x_501_, 2);
lean_inc_ref(v_pkgLoc_506_);
lean_dec_ref(v_x_501_);
lean_inc(v_p_504_);
v___x_507_ = lean_apply_1(v_pkgLoc_506_, v_p_504_);
v___x_508_ = lean_alloc_ctor(1, 1, 0);
lean_ctor_set(v___x_508_, 0, v_x_502_);
v___x_509_ = lp_island__logistics__proof_IslandLogistics_instDecidableEqPkgPos_decEq___redArg(v___x_507_, v___x_508_);
lean_dec_ref_known(v___x_508_, 1);
lean_dec_ref(v___x_507_);
if (v___x_509_ == 0)
{
lean_object* v___x_510_; 
lean_dec(v_p_504_);
lean_dec_ref(v_pkgWeight_503_);
v___x_510_ = lean_unsigned_to_nat(0u);
return v___x_510_;
}
else
{
lean_object* v___x_511_; 
v___x_511_ = lean_apply_1(v_pkgWeight_503_, v_p_504_);
return v___x_511_;
}
}
else
{
lean_object* v___x_512_; 
lean_dec(v_p_504_);
lean_dec_ref(v_pkgWeight_503_);
lean_dec(v_x_502_);
lean_dec_ref(v_x_501_);
v___x_512_ = lean_unsigned_to_nat(0u);
return v___x_512_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryAB(lean_object* v_I_513_, lean_object* v_s__root_514_, lean_object* v_inComp_515_, lean_object* v_inA_516_, lean_object* v_x_517_, lean_object* v_x_518_, lean_object* v_x_519_){
_start:
{
if (lean_obj_tag(v_x_518_) == 0)
{
lean_object* v___x_520_; 
lean_dec(v_x_519_);
lean_dec_ref(v_x_517_);
lean_dec_ref(v_inA_516_);
lean_dec_ref(v_inComp_515_);
lean_dec_ref(v_s__root_514_);
lean_dec_ref(v_I_513_);
v___x_520_ = lean_unsigned_to_nat(0u);
return v___x_520_;
}
else
{
lean_object* v_head_521_; lean_object* v_tail_522_; lean_object* v_sm_523_; lean_object* v___y_525_; lean_object* v___x_528_; lean_object* v___x_529_; uint8_t v___x_530_; 
v_head_521_ = lean_ctor_get(v_x_518_, 0);
lean_inc(v_head_521_);
v_tail_522_ = lean_ctor_get(v_x_518_, 1);
lean_inc(v_tail_522_);
lean_dec_ref_known(v_x_518_, 2);
lean_inc_ref_n(v_x_517_, 2);
lean_inc_ref(v_I_513_);
v_sm_523_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_513_, v_x_517_, v_head_521_);
lean_inc(v_x_519_);
lean_inc_ref(v_sm_523_);
lean_inc_ref(v_inA_516_);
lean_inc_ref(v_inComp_515_);
v___x_528_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(v_inComp_515_, v_inA_516_, v_x_517_, v_sm_523_, v_x_519_);
v___x_529_ = lean_unsigned_to_nat(1u);
v___x_530_ = lean_nat_dec_eq(v___x_528_, v___x_529_);
lean_dec(v___x_528_);
if (v___x_530_ == 0)
{
lean_object* v___x_531_; 
lean_dec_ref(v_x_517_);
v___x_531_ = lean_unsigned_to_nat(0u);
v___y_525_ = v___x_531_;
goto v___jp_524_;
}
else
{
lean_object* v_numPkgs_532_; lean_object* v_pkgWeight_533_; lean_object* v___f_534_; lean_object* v___x_535_; 
v_numPkgs_532_ = lean_ctor_get(v_I_513_, 8);
v_pkgWeight_533_ = lean_ctor_get(v_I_513_, 9);
lean_inc_ref(v_pkgWeight_533_);
lean_inc(v_x_519_);
lean_inc_ref(v_s__root_514_);
lean_inc_ref(v_I_513_);
v___f_534_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_planTruckCarryAB___lam__0), 6, 5);
lean_closure_set(v___f_534_, 0, v_I_513_);
lean_closure_set(v___f_534_, 1, v_s__root_514_);
lean_closure_set(v___f_534_, 2, v_x_517_);
lean_closure_set(v___f_534_, 3, v_x_519_);
lean_closure_set(v___f_534_, 4, v_pkgWeight_533_);
lean_inc(v_numPkgs_532_);
v___x_535_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_532_, v___f_534_);
v___y_525_ = v___x_535_;
goto v___jp_524_;
}
v___jp_524_:
{
lean_object* v___x_526_; lean_object* v___x_527_; 
v___x_526_ = lp_island__logistics__proof_IslandLogistics_planTruckCarryAB(v_I_513_, v_s__root_514_, v_inComp_515_, v_inA_516_, v_sm_523_, v_tail_522_, v_x_519_);
v___x_527_ = lean_nat_add(v___y_525_, v___x_526_);
lean_dec(v___x_526_);
lean_dec(v___y_525_);
return v___x_527_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planTruckCarryBA(lean_object* v_I_536_, lean_object* v_s__root_537_, lean_object* v_inComp_538_, lean_object* v_inA_539_, lean_object* v_x_540_, lean_object* v_x_541_, lean_object* v_x_542_){
_start:
{
if (lean_obj_tag(v_x_541_) == 0)
{
lean_object* v___x_543_; 
lean_dec(v_x_542_);
lean_dec_ref(v_x_540_);
lean_dec_ref(v_inA_539_);
lean_dec_ref(v_inComp_538_);
lean_dec_ref(v_s__root_537_);
lean_dec_ref(v_I_536_);
v___x_543_ = lean_unsigned_to_nat(0u);
return v___x_543_;
}
else
{
lean_object* v_head_544_; lean_object* v_tail_545_; lean_object* v_sm_546_; lean_object* v___y_548_; lean_object* v___x_551_; lean_object* v___x_552_; uint8_t v___x_553_; 
v_head_544_ = lean_ctor_get(v_x_541_, 0);
lean_inc(v_head_544_);
v_tail_545_ = lean_ctor_get(v_x_541_, 1);
lean_inc(v_tail_545_);
lean_dec_ref_known(v_x_541_, 2);
lean_inc_ref_n(v_x_540_, 2);
lean_inc_ref(v_I_536_);
v_sm_546_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_536_, v_x_540_, v_head_544_);
lean_inc(v_x_542_);
lean_inc_ref(v_sm_546_);
lean_inc_ref(v_inA_539_);
lean_inc_ref(v_inComp_538_);
v___x_551_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(v_inComp_538_, v_inA_539_, v_x_540_, v_sm_546_, v_x_542_);
v___x_552_ = lean_unsigned_to_nat(1u);
v___x_553_ = lean_nat_dec_eq(v___x_551_, v___x_552_);
lean_dec(v___x_551_);
if (v___x_553_ == 0)
{
lean_object* v___x_554_; 
lean_dec_ref(v_x_540_);
v___x_554_ = lean_unsigned_to_nat(0u);
v___y_548_ = v___x_554_;
goto v___jp_547_;
}
else
{
lean_object* v_numPkgs_555_; lean_object* v_pkgWeight_556_; lean_object* v___f_557_; lean_object* v___x_558_; 
v_numPkgs_555_ = lean_ctor_get(v_I_536_, 8);
v_pkgWeight_556_ = lean_ctor_get(v_I_536_, 9);
lean_inc_ref(v_pkgWeight_556_);
lean_inc(v_x_542_);
lean_inc_ref(v_s__root_537_);
lean_inc_ref(v_I_536_);
v___f_557_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_planTruckCarryAB___lam__0), 6, 5);
lean_closure_set(v___f_557_, 0, v_I_536_);
lean_closure_set(v___f_557_, 1, v_s__root_537_);
lean_closure_set(v___f_557_, 2, v_x_540_);
lean_closure_set(v___f_557_, 3, v_x_542_);
lean_closure_set(v___f_557_, 4, v_pkgWeight_556_);
lean_inc(v_numPkgs_555_);
v___x_558_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numPkgs_555_, v___f_557_);
v___y_548_ = v___x_558_;
goto v___jp_547_;
}
v___jp_547_:
{
lean_object* v___x_549_; lean_object* v___x_550_; 
v___x_549_ = lp_island__logistics__proof_IslandLogistics_planTruckCarryBA(v_I_536_, v_s__root_537_, v_inComp_538_, v_inA_539_, v_sm_546_, v_tail_545_, v_x_542_);
v___x_550_ = lean_nat_add(v___y_548_, v___x_549_);
lean_dec(v___x_549_);
lean_dec(v___y_548_);
return v___x_550_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planPkgCrossAB(lean_object* v_I_559_, lean_object* v_inComp_560_, lean_object* v_inA_561_, lean_object* v_x_562_, lean_object* v_x_563_, lean_object* v_x_564_){
_start:
{
if (lean_obj_tag(v_x_563_) == 0)
{
lean_object* v___x_565_; 
lean_dec(v_x_564_);
lean_dec_ref(v_x_562_);
lean_dec_ref(v_inA_561_);
lean_dec_ref(v_inComp_560_);
lean_dec_ref(v_I_559_);
v___x_565_ = lean_unsigned_to_nat(0u);
return v___x_565_;
}
else
{
lean_object* v_head_566_; lean_object* v_tail_567_; lean_object* v_pkgLoc_568_; lean_object* v_sm_569_; lean_object* v___y_571_; lean_object* v___x_574_; 
v_head_566_ = lean_ctor_get(v_x_563_, 0);
lean_inc(v_head_566_);
v_tail_567_ = lean_ctor_get(v_x_563_, 1);
lean_inc(v_tail_567_);
lean_dec_ref_known(v_x_563_, 2);
v_pkgLoc_568_ = lean_ctor_get(v_x_562_, 2);
lean_inc_ref(v_x_562_);
lean_inc_ref(v_I_559_);
v_sm_569_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_559_, v_x_562_, v_head_566_);
lean_inc_ref(v_pkgLoc_568_);
lean_inc(v_x_564_);
v___x_574_ = lean_apply_1(v_pkgLoc_568_, v_x_564_);
if (lean_obj_tag(v___x_574_) == 0)
{
lean_object* v___x_575_; 
lean_dec_ref_known(v___x_574_, 1);
lean_dec_ref(v_x_562_);
v___x_575_ = lean_unsigned_to_nat(0u);
v___y_571_ = v___x_575_;
goto v___jp_570_;
}
else
{
lean_object* v_t_576_; lean_object* v___x_577_; 
v_t_576_ = lean_ctor_get(v___x_574_, 0);
lean_inc(v_t_576_);
lean_dec_ref_known(v___x_574_, 1);
lean_inc_ref(v_sm_569_);
lean_inc_ref(v_inA_561_);
lean_inc_ref(v_inComp_560_);
v___x_577_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossAB___redArg(v_inComp_560_, v_inA_561_, v_x_562_, v_sm_569_, v_t_576_);
v___y_571_ = v___x_577_;
goto v___jp_570_;
}
v___jp_570_:
{
lean_object* v___x_572_; lean_object* v___x_573_; 
v___x_572_ = lp_island__logistics__proof_IslandLogistics_planPkgCrossAB(v_I_559_, v_inComp_560_, v_inA_561_, v_sm_569_, v_tail_567_, v_x_564_);
v___x_573_ = lean_nat_add(v___y_571_, v___x_572_);
lean_dec(v___x_572_);
lean_dec(v___y_571_);
return v___x_573_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_planPkgCrossBA(lean_object* v_I_578_, lean_object* v_inComp_579_, lean_object* v_inA_580_, lean_object* v_x_581_, lean_object* v_x_582_, lean_object* v_x_583_){
_start:
{
if (lean_obj_tag(v_x_582_) == 0)
{
lean_object* v___x_584_; 
lean_dec(v_x_583_);
lean_dec_ref(v_x_581_);
lean_dec_ref(v_inA_580_);
lean_dec_ref(v_inComp_579_);
lean_dec_ref(v_I_578_);
v___x_584_ = lean_unsigned_to_nat(0u);
return v___x_584_;
}
else
{
lean_object* v_head_585_; lean_object* v_tail_586_; lean_object* v_pkgLoc_587_; lean_object* v_sm_588_; lean_object* v___y_590_; lean_object* v___x_593_; 
v_head_585_ = lean_ctor_get(v_x_582_, 0);
lean_inc(v_head_585_);
v_tail_586_ = lean_ctor_get(v_x_582_, 1);
lean_inc(v_tail_586_);
lean_dec_ref_known(v_x_582_, 2);
v_pkgLoc_587_ = lean_ctor_get(v_x_581_, 2);
lean_inc_ref(v_x_581_);
lean_inc_ref(v_I_578_);
v_sm_588_ = lp_island__logistics__proof_IslandLogistics_applyAction(v_I_578_, v_x_581_, v_head_585_);
lean_inc_ref(v_pkgLoc_587_);
lean_inc(v_x_583_);
v___x_593_ = lean_apply_1(v_pkgLoc_587_, v_x_583_);
if (lean_obj_tag(v___x_593_) == 0)
{
lean_object* v___x_594_; 
lean_dec_ref_known(v___x_593_, 1);
lean_dec_ref(v_x_581_);
v___x_594_ = lean_unsigned_to_nat(0u);
v___y_590_ = v___x_594_;
goto v___jp_589_;
}
else
{
lean_object* v_t_595_; lean_object* v___x_596_; 
v_t_595_ = lean_ctor_get(v___x_593_, 0);
lean_inc(v_t_595_);
lean_dec_ref_known(v___x_593_, 1);
lean_inc_ref(v_sm_588_);
lean_inc_ref(v_inA_580_);
lean_inc_ref(v_inComp_579_);
v___x_596_ = lp_island__logistics__proof_IslandLogistics_stepTruckCrossBA___redArg(v_inComp_579_, v_inA_580_, v_x_581_, v_sm_588_, v_t_595_);
v___y_590_ = v___x_596_;
goto v___jp_589_;
}
v___jp_589_:
{
lean_object* v___x_591_; lean_object* v___x_592_; 
v___x_591_ = lp_island__logistics__proof_IslandLogistics_planPkgCrossBA(v_I_578_, v_inComp_579_, v_inA_580_, v_sm_588_, v_tail_586_, v_x_583_);
v___x_592_ = lean_nat_add(v___y_590_, v___x_591_);
lean_dec(v___x_591_);
lean_dec(v___y_590_);
return v___x_592_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___redArg(lean_object* v_x_597_, lean_object* v_h__1_598_, lean_object* v_h__2_599_){
_start:
{
if (lean_obj_tag(v_x_597_) == 0)
{
lean_object* v_l_600_; lean_object* v___x_601_; 
lean_dec(v_h__2_599_);
v_l_600_ = lean_ctor_get(v_x_597_, 0);
lean_inc(v_l_600_);
lean_dec_ref_known(v_x_597_, 1);
v___x_601_ = lean_apply_1(v_h__1_598_, v_l_600_);
return v___x_601_;
}
else
{
lean_object* v_t_602_; lean_object* v___x_603_; 
lean_dec(v_h__1_598_);
v_t_602_ = lean_ctor_get(v_x_597_, 0);
lean_inc(v_t_602_);
lean_dec_ref_known(v_x_597_, 1);
v___x_603_ = lean_apply_1(v_h__2_599_, v_t_602_);
return v___x_603_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(lean_object* v_I_604_, lean_object* v_motive_605_, lean_object* v_x_606_, lean_object* v_h__1_607_, lean_object* v_h__2_608_){
_start:
{
if (lean_obj_tag(v_x_606_) == 0)
{
lean_object* v_l_609_; lean_object* v___x_610_; 
lean_dec(v_h__2_608_);
v_l_609_ = lean_ctor_get(v_x_606_, 0);
lean_inc(v_l_609_);
lean_dec_ref_known(v_x_606_, 1);
v___x_610_ = lean_apply_1(v_h__1_607_, v_l_609_);
return v___x_610_;
}
else
{
lean_object* v_t_611_; lean_object* v___x_612_; 
lean_dec(v_h__1_607_);
v_t_611_ = lean_ctor_get(v_x_606_, 0);
lean_inc(v_t_611_);
lean_dec_ref_known(v_x_606_, 1);
v___x_612_ = lean_apply_1(v_h__2_608_, v_t_611_);
return v___x_612_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter___boxed(lean_object* v_I_613_, lean_object* v_motive_614_, lean_object* v_x_615_, lean_object* v_h__1_616_, lean_object* v_h__2_617_){
_start:
{
lean_object* v_res_618_; 
v_res_618_ = lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_State_pkgPhysLoc_match__1_splitter(v_I_613_, v_motive_614_, v_x_615_, v_h__1_616_, v_h__2_617_);
lean_dec_ref(v_I_613_);
return v_res_618_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter___redArg(lean_object* v_x_619_, lean_object* v_h__1_620_, lean_object* v_h__2_621_){
_start:
{
if (lean_obj_tag(v_x_619_) == 0)
{
lean_object* v_l_622_; lean_object* v___x_623_; 
lean_dec(v_h__2_621_);
v_l_622_ = lean_ctor_get(v_x_619_, 0);
lean_inc(v_l_622_);
lean_dec_ref_known(v_x_619_, 1);
v___x_623_ = lean_apply_1(v_h__1_620_, v_l_622_);
return v___x_623_;
}
else
{
lean_object* v_t_624_; lean_object* v___x_625_; 
lean_dec(v_h__1_620_);
v_t_624_ = lean_ctor_get(v_x_619_, 0);
lean_inc(v_t_624_);
lean_dec_ref_known(v_x_619_, 1);
v___x_625_ = lean_apply_1(v_h__2_621_, v_t_624_);
return v___x_625_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter(lean_object* v_I_626_, lean_object* v_motive_627_, lean_object* v_x_628_, lean_object* v_h__1_629_, lean_object* v_h__2_630_){
_start:
{
if (lean_obj_tag(v_x_628_) == 0)
{
lean_object* v_l_631_; lean_object* v___x_632_; 
lean_dec(v_h__2_630_);
v_l_631_ = lean_ctor_get(v_x_628_, 0);
lean_inc(v_l_631_);
lean_dec_ref_known(v_x_628_, 1);
v___x_632_ = lean_apply_1(v_h__1_629_, v_l_631_);
return v___x_632_;
}
else
{
lean_object* v_t_633_; lean_object* v___x_634_; 
lean_dec(v_h__1_629_);
v_t_633_ = lean_ctor_get(v_x_628_, 0);
lean_inc(v_t_633_);
lean_dec_ref_known(v_x_628_, 1);
v___x_634_ = lean_apply_1(v_h__2_630_, v_t_633_);
return v___x_634_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter___boxed(lean_object* v_I_635_, lean_object* v_motive_636_, lean_object* v_x_637_, lean_object* v_h__1_638_, lean_object* v_h__2_639_){
_start:
{
lean_object* v_res_640_; 
v_res_640_ = lp_island__logistics__proof___private_PackingAndFlux_0__IslandLogistics_planPkgCrossAB_match__1_splitter(v_I_635_, v_motive_636_, v_x_637_, v_h__1_638_, v_h__2_639_);
lean_dec_ref(v_I_635_);
return v_res_640_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_PackingAndFlux(uint8_t builtin) {
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
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
