// Lean compiler output
// Module: Main
// Imports: public import Init public meta import Init public import Domain public import PackingAndFlux public import BridgesAndCycles public import Ferries public import SingleAndExclusive
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
lean_object* lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(lean_object*, lean_object*);
uint8_t l_Option_decidableEqNone___redArg(lean_object*);
lean_object* lean_nat_mul(lean_object*, lean_object*);
uint8_t lean_nat_dec_le(lean_object*, lean_object*);
uint8_t lean_nat_dec_lt(lean_object*, lean_object*);
uint8_t lean_nat_dec_eq(lean_object*, lean_object*);
lean_object* lean_nat_add(lean_object*, lean_object*);
lean_object* lean_nat_sub(lean_object*, lean_object*);
lean_object* lp_island__logistics__proof_IslandLogistics_finSum(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hAstarCombine(uint8_t, uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hAstarCombine___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_aboardTruckCount___lam__0(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_aboardTruckCount(lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evalIslandFerriesCombine(uint8_t, uint8_t, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evalIslandFerriesCombine___boxed(lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*, lean_object*);
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hAstarCombine(uint8_t v_goalReached_1_, uint8_t v_noTruckOrCap_2_, uint8_t v_earlyReturnLU_3_, lean_object* v_h__lu_4_, lean_object* v_h__drive_5_, lean_object* v_h__bd_6_, lean_object* v_h__pack__truck_7_, lean_object* v_h__sail_8_, lean_object* v_h__excl_9_, lean_object* v_h__single_10_, lean_object* v_max__single__ub_11_){
_start:
{
lean_object* v___y_13_; lean_object* v___y_20_; 
if (v_goalReached_1_ == 0)
{
if (v_noTruckOrCap_2_ == 0)
{
if (v_earlyReturnLU_3_ == 0)
{
lean_object* v___x_23_; uint8_t v___x_24_; 
v___x_23_ = lean_nat_add(v_h__drive_5_, v_h__bd_6_);
v___x_24_ = lean_nat_dec_le(v___x_23_, v_h__pack__truck_7_);
if (v___x_24_ == 0)
{
lean_dec(v_h__pack__truck_7_);
v___y_20_ = v___x_23_;
goto v___jp_19_;
}
else
{
lean_dec(v___x_23_);
v___y_20_ = v_h__pack__truck_7_;
goto v___jp_19_;
}
}
else
{
lean_dec(v_h__excl_9_);
lean_dec(v_h__pack__truck_7_);
lean_inc(v_h__lu_4_);
return v_h__lu_4_;
}
}
else
{
lean_dec(v_h__excl_9_);
lean_dec(v_h__pack__truck_7_);
lean_inc(v_h__lu_4_);
return v_h__lu_4_;
}
}
else
{
lean_object* v___x_25_; 
lean_dec(v_h__excl_9_);
lean_dec(v_h__pack__truck_7_);
v___x_25_ = lean_unsigned_to_nat(0u);
return v___x_25_;
}
v___jp_12_:
{
uint8_t v___x_14_; 
v___x_14_ = lean_nat_dec_lt(v___y_13_, v_max__single__ub_11_);
if (v___x_14_ == 0)
{
lean_object* v___x_15_; 
v___x_15_ = lean_nat_add(v_h__lu_4_, v___y_13_);
lean_dec(v___y_13_);
return v___x_15_;
}
else
{
uint8_t v___x_16_; 
v___x_16_ = lean_nat_dec_le(v___y_13_, v_h__single_10_);
if (v___x_16_ == 0)
{
lean_object* v___x_17_; 
v___x_17_ = lean_nat_add(v_h__lu_4_, v___y_13_);
lean_dec(v___y_13_);
return v___x_17_;
}
else
{
lean_object* v___x_18_; 
lean_dec(v___y_13_);
v___x_18_ = lean_nat_add(v_h__lu_4_, v_h__single_10_);
return v___x_18_;
}
}
}
v___jp_19_:
{
lean_object* v___x_21_; uint8_t v___x_22_; 
v___x_21_ = lean_nat_add(v___y_20_, v_h__sail_8_);
lean_dec(v___y_20_);
v___x_22_ = lean_nat_dec_le(v___x_21_, v_h__excl_9_);
if (v___x_22_ == 0)
{
lean_dec(v_h__excl_9_);
v___y_13_ = v___x_21_;
goto v___jp_12_;
}
else
{
lean_dec(v___x_21_);
v___y_13_ = v_h__excl_9_;
goto v___jp_12_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_hAstarCombine___boxed(lean_object* v_goalReached_26_, lean_object* v_noTruckOrCap_27_, lean_object* v_earlyReturnLU_28_, lean_object* v_h__lu_29_, lean_object* v_h__drive_30_, lean_object* v_h__bd_31_, lean_object* v_h__pack__truck_32_, lean_object* v_h__sail_33_, lean_object* v_h__excl_34_, lean_object* v_h__single_35_, lean_object* v_max__single__ub_36_){
_start:
{
uint8_t v_goalReached_boxed_37_; uint8_t v_noTruckOrCap_boxed_38_; uint8_t v_earlyReturnLU_boxed_39_; lean_object* v_res_40_; 
v_goalReached_boxed_37_ = lean_unbox(v_goalReached_26_);
v_noTruckOrCap_boxed_38_ = lean_unbox(v_noTruckOrCap_27_);
v_earlyReturnLU_boxed_39_ = lean_unbox(v_earlyReturnLU_28_);
v_res_40_ = lp_island__logistics__proof_IslandLogistics_hAstarCombine(v_goalReached_boxed_37_, v_noTruckOrCap_boxed_38_, v_earlyReturnLU_boxed_39_, v_h__lu_29_, v_h__drive_30_, v_h__bd_31_, v_h__pack__truck_32_, v_h__sail_33_, v_h__excl_34_, v_h__single_35_, v_max__single__ub_36_);
lean_dec(v_max__single__ub_36_);
lean_dec(v_h__single_35_);
lean_dec(v_h__sail_33_);
lean_dec(v_h__bd_31_);
lean_dec(v_h__drive_30_);
lean_dec(v_h__lu_29_);
return v_res_40_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_aboardTruckCount___lam__0(lean_object* v_s_41_, lean_object* v_t_42_){
_start:
{
lean_object* v___x_43_; uint8_t v___x_44_; 
v___x_43_ = lp_island__logistics__proof_IslandLogistics_State_truckOnFerry___redArg(v_s_41_, v_t_42_);
v___x_44_ = l_Option_decidableEqNone___redArg(v___x_43_);
lean_dec(v___x_43_);
if (v___x_44_ == 0)
{
lean_object* v___x_45_; 
v___x_45_ = lean_unsigned_to_nat(1u);
return v___x_45_;
}
else
{
lean_object* v___x_46_; 
v___x_46_ = lean_unsigned_to_nat(0u);
return v___x_46_;
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_aboardTruckCount(lean_object* v_I_47_, lean_object* v_s_48_){
_start:
{
lean_object* v_numTrucks_49_; lean_object* v___f_50_; lean_object* v___x_51_; 
v_numTrucks_49_ = lean_ctor_get(v_I_47_, 3);
lean_inc(v_numTrucks_49_);
lean_dec_ref(v_I_47_);
v___f_50_ = lean_alloc_closure((void*)(lp_island__logistics__proof_IslandLogistics_aboardTruckCount___lam__0), 2, 1);
lean_closure_set(v___f_50_, 0, v_s_48_);
v___x_51_ = lp_island__logistics__proof_IslandLogistics_finSum(v_numTrucks_49_, v___f_50_);
return v___x_51_;
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evalIslandFerriesCombine(uint8_t v_diam__one_52_, uint8_t v_need__pos_53_, lean_object* v_n__ab_54_, lean_object* v_b1_55_, lean_object* v_d1_56_, lean_object* v_b2_57_, lean_object* v_d2_58_, lean_object* v_bd__c_59_, lean_object* v_sum__so_60_, lean_object* v_sum__si_61_, lean_object* v_b4_62_, lean_object* v_b5_63_, lean_object* v_sum__req__i_64_, lean_object* v_b3_65_, lean_object* v_b7_66_){
_start:
{
lean_object* v___y_68_; lean_object* v___y_69_; lean_object* v___y_74_; lean_object* v___y_75_; lean_object* v___y_76_; lean_object* v___y_79_; lean_object* v___y_80_; lean_object* v___y_83_; lean_object* v___y_84_; lean_object* v___y_87_; lean_object* v___y_88_; lean_object* v___y_95_; lean_object* v___y_96_; lean_object* v___y_97_; lean_object* v___y_100_; lean_object* v___y_101_; lean_object* v___y_104_; lean_object* v___y_107_; lean_object* v___y_108_; lean_object* v___y_112_; lean_object* v___y_113_; lean_object* v___y_117_; 
if (v_diam__one_52_ == 0)
{
uint8_t v___x_119_; 
v___x_119_ = lean_nat_dec_le(v_d1_56_, v_d2_58_);
if (v___x_119_ == 0)
{
v___y_117_ = v_d1_56_;
goto v___jp_116_;
}
else
{
v___y_117_ = v_d2_58_;
goto v___jp_116_;
}
}
else
{
v___y_117_ = v_d1_56_;
goto v___jp_116_;
}
v___jp_67_:
{
lean_object* v___x_70_; lean_object* v___x_71_; lean_object* v___x_72_; 
v___x_70_ = lean_unsigned_to_nat(3u);
v___x_71_ = lean_nat_mul(v___x_70_, v___y_69_);
lean_dec(v___y_69_);
v___x_72_ = lean_alloc_ctor(0, 2, 0);
lean_ctor_set(v___x_72_, 0, v___y_68_);
lean_ctor_set(v___x_72_, 1, v___x_71_);
return v___x_72_;
}
v___jp_73_:
{
uint8_t v___x_77_; 
v___x_77_ = lean_nat_dec_le(v___y_74_, v___y_76_);
if (v___x_77_ == 0)
{
lean_dec(v___y_76_);
v___y_68_ = v___y_75_;
v___y_69_ = v___y_74_;
goto v___jp_67_;
}
else
{
lean_dec(v___y_74_);
v___y_68_ = v___y_75_;
v___y_69_ = v___y_76_;
goto v___jp_67_;
}
}
v___jp_78_:
{
uint8_t v___x_81_; 
v___x_81_ = lean_nat_dec_le(v_b3_65_, v_b7_66_);
if (v___x_81_ == 0)
{
lean_dec(v_b7_66_);
v___y_74_ = v___y_80_;
v___y_75_ = v___y_79_;
v___y_76_ = v_b3_65_;
goto v___jp_73_;
}
else
{
lean_dec(v_b3_65_);
v___y_74_ = v___y_80_;
v___y_75_ = v___y_79_;
v___y_76_ = v_b7_66_;
goto v___jp_73_;
}
}
v___jp_82_:
{
uint8_t v___x_85_; 
v___x_85_ = lean_nat_dec_le(v___y_84_, v_sum__req__i_64_);
if (v___x_85_ == 0)
{
lean_dec(v_sum__req__i_64_);
v___y_79_ = v___y_83_;
v___y_80_ = v___y_84_;
goto v___jp_78_;
}
else
{
lean_dec(v___y_84_);
v___y_79_ = v___y_83_;
v___y_80_ = v_sum__req__i_64_;
goto v___jp_78_;
}
}
v___jp_86_:
{
lean_object* v___x_89_; uint8_t v___x_90_; 
v___x_89_ = lean_unsigned_to_nat(0u);
v___x_90_ = lean_nat_dec_lt(v___x_89_, v___y_88_);
if (v___x_90_ == 0)
{
v___y_83_ = v___y_87_;
v___y_84_ = v___y_88_;
goto v___jp_82_;
}
else
{
uint8_t v___x_91_; 
v___x_91_ = lean_nat_dec_eq(v_n__ab_54_, v___x_89_);
if (v___x_91_ == 0)
{
v___y_83_ = v___y_87_;
v___y_84_ = v___y_88_;
goto v___jp_82_;
}
else
{
if (v_need__pos_53_ == 0)
{
v___y_83_ = v___y_87_;
v___y_84_ = v___y_88_;
goto v___jp_82_;
}
else
{
lean_object* v___x_92_; lean_object* v___x_93_; 
v___x_92_ = lean_unsigned_to_nat(1u);
v___x_93_ = lean_nat_add(v___y_88_, v___x_92_);
lean_dec(v___y_88_);
v___y_83_ = v___y_87_;
v___y_84_ = v___x_93_;
goto v___jp_82_;
}
}
}
}
v___jp_94_:
{
uint8_t v___x_98_; 
v___x_98_ = lean_nat_dec_le(v___y_95_, v___y_97_);
if (v___x_98_ == 0)
{
lean_dec(v___y_97_);
v___y_87_ = v___y_96_;
v___y_88_ = v___y_95_;
goto v___jp_86_;
}
else
{
lean_dec(v___y_95_);
v___y_87_ = v___y_96_;
v___y_88_ = v___y_97_;
goto v___jp_86_;
}
}
v___jp_99_:
{
if (v_diam__one_52_ == 0)
{
uint8_t v___x_102_; 
v___x_102_ = lean_nat_dec_le(v_b4_62_, v_b5_63_);
if (v___x_102_ == 0)
{
lean_dec(v_b5_63_);
v___y_95_ = v___y_101_;
v___y_96_ = v___y_100_;
v___y_97_ = v_b4_62_;
goto v___jp_94_;
}
else
{
lean_dec(v_b4_62_);
v___y_95_ = v___y_101_;
v___y_96_ = v___y_100_;
v___y_97_ = v_b5_63_;
goto v___jp_94_;
}
}
else
{
lean_dec(v_b5_63_);
lean_dec(v_b4_62_);
v___y_87_ = v___y_100_;
v___y_88_ = v___y_101_;
goto v___jp_86_;
}
}
v___jp_103_:
{
uint8_t v___x_105_; 
v___x_105_ = lean_nat_dec_le(v_sum__so_60_, v_sum__si_61_);
if (v___x_105_ == 0)
{
lean_dec(v_sum__si_61_);
v___y_100_ = v___y_104_;
v___y_101_ = v_sum__so_60_;
goto v___jp_99_;
}
else
{
lean_dec(v_sum__so_60_);
v___y_100_ = v___y_104_;
v___y_101_ = v_sum__si_61_;
goto v___jp_99_;
}
}
v___jp_106_:
{
lean_object* v___x_109_; uint8_t v___x_110_; 
v___x_109_ = lean_nat_add(v___y_108_, v___y_107_);
lean_dec(v___y_108_);
v___x_110_ = lean_nat_dec_le(v___x_109_, v_bd__c_59_);
if (v___x_110_ == 0)
{
lean_dec(v_bd__c_59_);
v___y_104_ = v___x_109_;
goto v___jp_103_;
}
else
{
lean_dec(v___x_109_);
v___y_104_ = v_bd__c_59_;
goto v___jp_103_;
}
}
v___jp_111_:
{
lean_object* v___x_114_; uint8_t v___x_115_; 
v___x_114_ = lean_nat_sub(v___y_112_, v_n__ab_54_);
v___x_115_ = lean_nat_dec_le(v___y_113_, v___x_114_);
if (v___x_115_ == 0)
{
lean_dec(v___x_114_);
v___y_107_ = v___y_112_;
v___y_108_ = v___y_113_;
goto v___jp_106_;
}
else
{
lean_dec(v___y_113_);
v___y_107_ = v___y_112_;
v___y_108_ = v___x_114_;
goto v___jp_106_;
}
}
v___jp_116_:
{
if (v_diam__one_52_ == 0)
{
uint8_t v___x_118_; 
v___x_118_ = lean_nat_dec_le(v_b1_55_, v_b2_57_);
if (v___x_118_ == 0)
{
lean_dec(v_b2_57_);
v___y_112_ = v___y_117_;
v___y_113_ = v_b1_55_;
goto v___jp_111_;
}
else
{
lean_dec(v_b1_55_);
v___y_112_ = v___y_117_;
v___y_113_ = v_b2_57_;
goto v___jp_111_;
}
}
else
{
lean_dec(v_b2_57_);
v___y_112_ = v___y_117_;
v___y_113_ = v_b1_55_;
goto v___jp_111_;
}
}
}
}
LEAN_EXPORT lean_object* lp_island__logistics__proof_IslandLogistics_evalIslandFerriesCombine___boxed(lean_object* v_diam__one_120_, lean_object* v_need__pos_121_, lean_object* v_n__ab_122_, lean_object* v_b1_123_, lean_object* v_d1_124_, lean_object* v_b2_125_, lean_object* v_d2_126_, lean_object* v_bd__c_127_, lean_object* v_sum__so_128_, lean_object* v_sum__si_129_, lean_object* v_b4_130_, lean_object* v_b5_131_, lean_object* v_sum__req__i_132_, lean_object* v_b3_133_, lean_object* v_b7_134_){
_start:
{
uint8_t v_diam__one_boxed_135_; uint8_t v_need__pos_boxed_136_; lean_object* v_res_137_; 
v_diam__one_boxed_135_ = lean_unbox(v_diam__one_120_);
v_need__pos_boxed_136_ = lean_unbox(v_need__pos_121_);
v_res_137_ = lp_island__logistics__proof_IslandLogistics_evalIslandFerriesCombine(v_diam__one_boxed_135_, v_need__pos_boxed_136_, v_n__ab_122_, v_b1_123_, v_d1_124_, v_b2_125_, v_d2_126_, v_bd__c_127_, v_sum__so_128_, v_sum__si_129_, v_b4_130_, v_b5_131_, v_sum__req__i_132_, v_b3_133_, v_b7_134_);
lean_dec(v_d2_126_);
lean_dec(v_d1_124_);
lean_dec(v_n__ab_122_);
return v_res_137_;
}
}
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_Init(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Domain(uint8_t builtin);
lean_object* initialize_island__logistics__proof_PackingAndFlux(uint8_t builtin);
lean_object* initialize_island__logistics__proof_BridgesAndCycles(uint8_t builtin);
lean_object* initialize_island__logistics__proof_Ferries(uint8_t builtin);
lean_object* initialize_island__logistics__proof_SingleAndExclusive(uint8_t builtin);
void lean_initialize_runtime_module();
static bool _G_initialized = false;
LEAN_EXPORT lean_object* initialize_island__logistics__proof_Main(uint8_t builtin) {
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
res = initialize_island__logistics__proof_Ferries(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
res = initialize_island__logistics__proof_SingleAndExclusive(builtin);
if (lean_io_result_is_error(res)) return res;
lean_dec_ref(res);
return lean_io_result_mk_ok(lean_box(0));
}
#ifdef __cplusplus
}
#endif
