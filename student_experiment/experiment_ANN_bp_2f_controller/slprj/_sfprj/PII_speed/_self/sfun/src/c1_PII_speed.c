/* Include files */

#include "blascompat32.h"
#include "PII_speed_sfun.h"
#include "c1_PII_speed.h"
#include "mwmathutil.h"
#define CHARTINSTANCE_CHARTNUMBER      (chartInstance->chartNumber)
#define CHARTINSTANCE_INSTANCENUMBER   (chartInstance->instanceNumber)
#include "PII_speed_sfun_debug_macros.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
static const char *c1_debug_family_names[24] = { "nv", "j", "i", "k", "nargin",
  "nargout", "u", "sys", "waga1", "nhn", "init_nn_output", "number_of_weights",
  "init_state", "w1", "w2", "dw1", "dw2", "jv", "dj", "ipj", "dk", "kv", "sm",
  "opk" };

/* Function Declarations */
static void initialize_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void initialize_params_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance);
static void enable_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void disable_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void c1_update_debugger_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance);
static void set_sim_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance, const mxArray *c1_st);
static void finalize_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void sf_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void c1_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance);
static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber);
static void c1_eml_scalar_eg(SFc1_PII_speedInstanceStruct *chartInstance);
static real_T c1_ceval_xdot(SFc1_PII_speedInstanceStruct *chartInstance, int32_T
  c1_n, real_T c1_x[3], int32_T c1_ix0, int32_T c1_incx, real_T c1_y[3], int32_T
  c1_iy0, int32_T c1_incy);
static void c1_b_eml_scalar_eg(SFc1_PII_speedInstanceStruct *chartInstance);
static real_T c1_b_ceval_xdot(SFc1_PII_speedInstanceStruct *chartInstance,
  int32_T c1_n, real_T c1_x_data[8], int32_T c1_x_sizes[2], int32_T c1_ix0,
  int32_T c1_incx, real_T c1_y_data[8], int32_T c1_y_sizes[1], int32_T c1_iy0,
  int32_T c1_incy);
static const mxArray *c1_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_b_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_c_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_d_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_e_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2]);
static const mxArray *c1_f_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[49], int32_T c1_u_sizes[2]);
static const mxArray *c1_g_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[49], int32_T c1_u_sizes[2]);
static const mxArray *c1_h_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2]);
static const mxArray *c1_i_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[21], int32_T c1_u_sizes[2]);
static const mxArray *c1_j_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2]);
static const mxArray *c1_k_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[21], int32_T c1_u_sizes[2]);
static const mxArray *c1_l_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_m_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_n_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_o_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_p_sf_marshall(void *chartInstanceVoid, void *c1_u);
static const mxArray *c1_q_sf_marshall(void *chartInstanceVoid, void *c1_u);
static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[44]);
static const mxArray *c1_r_sf_marshall(void *chartInstanceVoid, void *c1_u);
static real_T c1_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_sys, const char_T *c1_name);
static void c1_b_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dj, const char_T *c1_name, real_T c1_y_data[49], int32_T
  c1_y_sizes[2]);
static real_T c1_c_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_dk, const char_T *c1_name);
static void c1_d_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dw1, const char_T *c1_name, real_T c1_y_data[21], int32_T
  c1_y_sizes[2]);
static void c1_e_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dw2, const char_T *c1_name, real_T c1_y_data[8], int32_T
  c1_y_sizes[2]);
static real_T c1_f_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_init_nn_output, const char_T *c1_name);
static void c1_g_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_init_state, const char_T *c1_name, real_T c1_y[30]);
static void c1_h_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_ipj, const char_T *c1_name, real_T c1_y_data[8], int32_T
  c1_y_sizes[2]);
static void c1_i_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_jv, const char_T *c1_name, real_T c1_y_data[49], int32_T
  c1_y_sizes[2]);
static real_T c1_j_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_kv, const char_T *c1_name);
static real_T c1_k_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_nhn, const char_T *c1_name);
static real_T c1_l_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_number_of_weights, const char_T *c1_name);
static real_T c1_m_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_opk, const char_T *c1_name);
static real_T c1_n_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_sm, const char_T *c1_name);
static void c1_o_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_w1, const char_T *c1_name, real_T c1_y_data[21], int32_T
  c1_y_sizes[2]);
static void c1_p_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_w2, const char_T *c1_name, real_T c1_y_data[8], int32_T
  c1_y_sizes[2]);
static uint8_T c1_q_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_PII_speed, const char_T *c1_name);
static void init_dsm_address_info(SFc1_PII_speedInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
  chartInstance->c1_w1_sizes[0] = 0;
  chartInstance->c1_w1_sizes[1] = 0;
  chartInstance->c1_w2_sizes[0] = 0;
  chartInstance->c1_w2_sizes[1] = 0;
  chartInstance->c1_dw1_sizes[0] = 0;
  chartInstance->c1_dw1_sizes[1] = 0;
  chartInstance->c1_dw2_sizes[0] = 0;
  chartInstance->c1_dw2_sizes[1] = 0;
  chartInstance->c1_jv_sizes[0] = 0;
  chartInstance->c1_jv_sizes[1] = 0;
  chartInstance->c1_dj_sizes[0] = 0;
  chartInstance->c1_dj_sizes[1] = 0;
  chartInstance->c1_ipj_sizes[0] = 0;
  chartInstance->c1_ipj_sizes[1] = 0;
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  chartInstance->c1_nhn_not_empty = FALSE;
  chartInstance->c1_init_nn_output_not_empty = FALSE;
  chartInstance->c1_number_of_weights_not_empty = FALSE;
  chartInstance->c1_init_state_not_empty = FALSE;
  chartInstance->c1_w1_not_empty = FALSE;
  chartInstance->c1_w2_not_empty = FALSE;
  chartInstance->c1_dw1_not_empty = FALSE;
  chartInstance->c1_dw2_not_empty = FALSE;
  chartInstance->c1_jv_not_empty = FALSE;
  chartInstance->c1_dj_not_empty = FALSE;
  chartInstance->c1_ipj_not_empty = FALSE;
  chartInstance->c1_dk_not_empty = FALSE;
  chartInstance->c1_kv_not_empty = FALSE;
  chartInstance->c1_sm_not_empty = FALSE;
  chartInstance->c1_opk_not_empty = FALSE;
  chartInstance->c1_is_active_c1_PII_speed = 0U;
}

static void initialize_params_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance)
{
}

static void enable_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void disable_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
}

static void c1_update_debugger_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance)
{
}

static const mxArray *get_sim_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance)
{
  const mxArray *c1_st = NULL;
  const mxArray *c1_y = NULL;
  real_T c1_hoistedGlobal;
  real_T c1_u;
  const mxArray *c1_b_y = NULL;
  real_T c1_b_hoistedGlobal;
  real_T c1_b_u;
  const mxArray *c1_c_y = NULL;
  int32_T c1_hoistedGlobal_sizes[2];
  int32_T c1_c_hoistedGlobal;
  int32_T c1_d_hoistedGlobal;
  int32_T c1_loop_ub;
  int32_T c1_i0;
  real_T c1_hoistedGlobal_data[49];
  int32_T c1_u_sizes[2];
  int32_T c1_c_u;
  int32_T c1_d_u;
  int32_T c1_b_loop_ub;
  int32_T c1_i1;
  real_T c1_u_data[49];
  const mxArray *c1_d_y = NULL;
  real_T c1_e_hoistedGlobal;
  real_T c1_e_u;
  const mxArray *c1_e_y = NULL;
  int32_T c1_b_hoistedGlobal_sizes[2];
  int32_T c1_f_hoistedGlobal;
  int32_T c1_g_hoistedGlobal;
  int32_T c1_c_loop_ub;
  int32_T c1_i2;
  real_T c1_b_hoistedGlobal_data[21];
  int32_T c1_b_u_sizes[2];
  int32_T c1_f_u;
  int32_T c1_g_u;
  int32_T c1_d_loop_ub;
  int32_T c1_i3;
  real_T c1_b_u_data[21];
  const mxArray *c1_f_y = NULL;
  int32_T c1_c_hoistedGlobal_sizes[2];
  int32_T c1_h_hoistedGlobal;
  int32_T c1_i_hoistedGlobal;
  int32_T c1_e_loop_ub;
  int32_T c1_i4;
  real_T c1_c_hoistedGlobal_data[8];
  int32_T c1_c_u_sizes[2];
  int32_T c1_h_u;
  int32_T c1_i_u;
  int32_T c1_f_loop_ub;
  int32_T c1_i5;
  real_T c1_c_u_data[8];
  const mxArray *c1_g_y = NULL;
  real_T c1_j_hoistedGlobal;
  real_T c1_j_u;
  const mxArray *c1_h_y = NULL;
  int32_T c1_i6;
  real_T c1_k_hoistedGlobal[30];
  int32_T c1_i7;
  real_T c1_k_u[30];
  const mxArray *c1_i_y = NULL;
  int32_T c1_d_hoistedGlobal_sizes[2];
  int32_T c1_l_hoistedGlobal;
  int32_T c1_m_hoistedGlobal;
  int32_T c1_g_loop_ub;
  int32_T c1_i8;
  real_T c1_d_hoistedGlobal_data[8];
  int32_T c1_d_u_sizes[2];
  int32_T c1_l_u;
  int32_T c1_m_u;
  int32_T c1_h_loop_ub;
  int32_T c1_i9;
  real_T c1_d_u_data[8];
  const mxArray *c1_j_y = NULL;
  int32_T c1_e_hoistedGlobal_sizes[2];
  int32_T c1_n_hoistedGlobal;
  int32_T c1_o_hoistedGlobal;
  int32_T c1_i_loop_ub;
  int32_T c1_i10;
  real_T c1_e_hoistedGlobal_data[49];
  int32_T c1_e_u_sizes[2];
  int32_T c1_n_u;
  int32_T c1_o_u;
  int32_T c1_j_loop_ub;
  int32_T c1_i11;
  real_T c1_e_u_data[49];
  const mxArray *c1_k_y = NULL;
  real_T c1_p_hoistedGlobal;
  real_T c1_p_u;
  const mxArray *c1_l_y = NULL;
  real_T c1_q_hoistedGlobal;
  real_T c1_q_u;
  const mxArray *c1_m_y = NULL;
  real_T c1_r_hoistedGlobal;
  real_T c1_r_u;
  const mxArray *c1_n_y = NULL;
  real_T c1_s_hoistedGlobal;
  real_T c1_s_u;
  const mxArray *c1_o_y = NULL;
  real_T c1_t_hoistedGlobal;
  real_T c1_t_u;
  const mxArray *c1_p_y = NULL;
  int32_T c1_f_hoistedGlobal_sizes[2];
  int32_T c1_u_hoistedGlobal;
  int32_T c1_v_hoistedGlobal;
  int32_T c1_k_loop_ub;
  int32_T c1_i12;
  real_T c1_f_hoistedGlobal_data[21];
  int32_T c1_f_u_sizes[2];
  int32_T c1_u_u;
  int32_T c1_v_u;
  int32_T c1_l_loop_ub;
  int32_T c1_i13;
  real_T c1_f_u_data[21];
  const mxArray *c1_q_y = NULL;
  int32_T c1_g_hoistedGlobal_sizes[2];
  int32_T c1_w_hoistedGlobal;
  int32_T c1_x_hoistedGlobal;
  int32_T c1_m_loop_ub;
  int32_T c1_i14;
  real_T c1_g_hoistedGlobal_data[8];
  int32_T c1_g_u_sizes[2];
  int32_T c1_w_u;
  int32_T c1_x_u;
  int32_T c1_n_loop_ub;
  int32_T c1_i15;
  real_T c1_g_u_data[8];
  const mxArray *c1_r_y = NULL;
  uint8_T c1_y_hoistedGlobal;
  uint8_T c1_y_u;
  const mxArray *c1_s_y = NULL;
  real_T *c1_sys;
  real_T *c1_waga1;
  c1_waga1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_sys = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_st = NULL;
  c1_y = NULL;
  sf_mex_assign(&c1_y, sf_mex_createcellarray(18));
  c1_hoistedGlobal = *c1_sys;
  c1_u = c1_hoistedGlobal;
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 0, c1_b_y);
  c1_b_hoistedGlobal = *c1_waga1;
  c1_b_u = c1_b_hoistedGlobal;
  c1_c_y = NULL;
  sf_mex_assign(&c1_c_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 1, c1_c_y);
  c1_hoistedGlobal_sizes[0] = 7;
  c1_hoistedGlobal_sizes[1] = 7;
  c1_c_hoistedGlobal = c1_hoistedGlobal_sizes[0];
  c1_d_hoistedGlobal = c1_hoistedGlobal_sizes[1];
  c1_loop_ub = chartInstance->c1_dj_sizes[0] * chartInstance->c1_dj_sizes[1] - 1;
  for (c1_i0 = 0; c1_i0 <= c1_loop_ub; c1_i0 = c1_i0 + 1) {
    c1_hoistedGlobal_data[c1_i0] = chartInstance->c1_dj_data[c1_i0];
  }

  c1_u_sizes[0] = 7;
  c1_u_sizes[1] = 7;
  c1_c_u = c1_u_sizes[0];
  c1_d_u = c1_u_sizes[1];
  c1_b_loop_ub = c1_hoistedGlobal_sizes[0] * c1_hoistedGlobal_sizes[1] - 1;
  for (c1_i1 = 0; c1_i1 <= c1_b_loop_ub; c1_i1 = c1_i1 + 1) {
    c1_u_data[c1_i1] = c1_hoistedGlobal_data[c1_i1];
  }

  c1_d_y = NULL;
  if (!chartInstance->c1_dj_not_empty) {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_d_y, sf_mex_create("y", &c1_u_data, 0, 0U, 1U, 0U, 2,
      c1_u_sizes[0], c1_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 2, c1_d_y);
  c1_e_hoistedGlobal = chartInstance->c1_dk;
  c1_e_u = c1_e_hoistedGlobal;
  c1_e_y = NULL;
  if (!chartInstance->c1_dk_not_empty) {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_e_y, sf_mex_create("y", &c1_e_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 3, c1_e_y);
  c1_b_hoistedGlobal_sizes[0] = 7;
  c1_b_hoistedGlobal_sizes[1] = 3;
  c1_f_hoistedGlobal = c1_b_hoistedGlobal_sizes[0];
  c1_g_hoistedGlobal = c1_b_hoistedGlobal_sizes[1];
  c1_c_loop_ub = chartInstance->c1_dw1_sizes[0] * chartInstance->c1_dw1_sizes[1]
    - 1;
  for (c1_i2 = 0; c1_i2 <= c1_c_loop_ub; c1_i2 = c1_i2 + 1) {
    c1_b_hoistedGlobal_data[c1_i2] = chartInstance->c1_dw1_data[c1_i2];
  }

  c1_b_u_sizes[0] = 7;
  c1_b_u_sizes[1] = 3;
  c1_f_u = c1_b_u_sizes[0];
  c1_g_u = c1_b_u_sizes[1];
  c1_d_loop_ub = c1_b_hoistedGlobal_sizes[0] * c1_b_hoistedGlobal_sizes[1] - 1;
  for (c1_i3 = 0; c1_i3 <= c1_d_loop_ub; c1_i3 = c1_i3 + 1) {
    c1_b_u_data[c1_i3] = c1_b_hoistedGlobal_data[c1_i3];
  }

  c1_f_y = NULL;
  if (!chartInstance->c1_dw1_not_empty) {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_f_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 4, c1_f_y);
  c1_c_hoistedGlobal_sizes[0] = 1;
  c1_c_hoistedGlobal_sizes[1] = 8;
  c1_h_hoistedGlobal = c1_c_hoistedGlobal_sizes[0];
  c1_i_hoistedGlobal = c1_c_hoistedGlobal_sizes[1];
  c1_e_loop_ub = chartInstance->c1_dw2_sizes[0] * chartInstance->c1_dw2_sizes[1]
    - 1;
  for (c1_i4 = 0; c1_i4 <= c1_e_loop_ub; c1_i4 = c1_i4 + 1) {
    c1_c_hoistedGlobal_data[c1_i4] = chartInstance->c1_dw2_data[c1_i4];
  }

  c1_c_u_sizes[0] = 1;
  c1_c_u_sizes[1] = 8;
  c1_h_u = c1_c_u_sizes[0];
  c1_i_u = c1_c_u_sizes[1];
  c1_f_loop_ub = c1_c_hoistedGlobal_sizes[0] * c1_c_hoistedGlobal_sizes[1] - 1;
  for (c1_i5 = 0; c1_i5 <= c1_f_loop_ub; c1_i5 = c1_i5 + 1) {
    c1_c_u_data[c1_i5] = c1_c_hoistedGlobal_data[c1_i5];
  }

  c1_g_y = NULL;
  if (!chartInstance->c1_dw2_not_empty) {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_g_y, sf_mex_create("y", &c1_c_u_data, 0, 0U, 1U, 0U, 2,
      c1_c_u_sizes[0], c1_c_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 5, c1_g_y);
  c1_j_hoistedGlobal = chartInstance->c1_init_nn_output;
  c1_j_u = c1_j_hoistedGlobal;
  c1_h_y = NULL;
  if (!chartInstance->c1_init_nn_output_not_empty) {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_h_y, sf_mex_create("y", &c1_j_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 6, c1_h_y);
  for (c1_i6 = 0; c1_i6 < 30; c1_i6 = c1_i6 + 1) {
    c1_k_hoistedGlobal[c1_i6] = chartInstance->c1_init_state[c1_i6];
  }

  for (c1_i7 = 0; c1_i7 < 30; c1_i7 = c1_i7 + 1) {
    c1_k_u[c1_i7] = c1_k_hoistedGlobal[c1_i7];
  }

  c1_i_y = NULL;
  if (!chartInstance->c1_init_state_not_empty) {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_i_y, sf_mex_create("y", &c1_k_u, 0, 0U, 1U, 0U, 1, 30));
  }

  sf_mex_setcell(c1_y, 7, c1_i_y);
  c1_d_hoistedGlobal_sizes[0] = 1;
  c1_d_hoistedGlobal_sizes[1] = 8;
  c1_l_hoistedGlobal = c1_d_hoistedGlobal_sizes[0];
  c1_m_hoistedGlobal = c1_d_hoistedGlobal_sizes[1];
  c1_g_loop_ub = chartInstance->c1_ipj_sizes[0] * chartInstance->c1_ipj_sizes[1]
    - 1;
  for (c1_i8 = 0; c1_i8 <= c1_g_loop_ub; c1_i8 = c1_i8 + 1) {
    c1_d_hoistedGlobal_data[c1_i8] = chartInstance->c1_ipj_data[c1_i8];
  }

  c1_d_u_sizes[0] = 1;
  c1_d_u_sizes[1] = 8;
  c1_l_u = c1_d_u_sizes[0];
  c1_m_u = c1_d_u_sizes[1];
  c1_h_loop_ub = c1_d_hoistedGlobal_sizes[0] * c1_d_hoistedGlobal_sizes[1] - 1;
  for (c1_i9 = 0; c1_i9 <= c1_h_loop_ub; c1_i9 = c1_i9 + 1) {
    c1_d_u_data[c1_i9] = c1_d_hoistedGlobal_data[c1_i9];
  }

  c1_j_y = NULL;
  if (!chartInstance->c1_ipj_not_empty) {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_j_y, sf_mex_create("y", &c1_d_u_data, 0, 0U, 1U, 0U, 2,
      c1_d_u_sizes[0], c1_d_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 8, c1_j_y);
  c1_e_hoistedGlobal_sizes[0] = 7;
  c1_e_hoistedGlobal_sizes[1] = 7;
  c1_n_hoistedGlobal = c1_e_hoistedGlobal_sizes[0];
  c1_o_hoistedGlobal = c1_e_hoistedGlobal_sizes[1];
  c1_i_loop_ub = chartInstance->c1_jv_sizes[0] * chartInstance->c1_jv_sizes[1] -
    1;
  for (c1_i10 = 0; c1_i10 <= c1_i_loop_ub; c1_i10 = c1_i10 + 1) {
    c1_e_hoistedGlobal_data[c1_i10] = chartInstance->c1_jv_data[c1_i10];
  }

  c1_e_u_sizes[0] = 7;
  c1_e_u_sizes[1] = 7;
  c1_n_u = c1_e_u_sizes[0];
  c1_o_u = c1_e_u_sizes[1];
  c1_j_loop_ub = c1_e_hoistedGlobal_sizes[0] * c1_e_hoistedGlobal_sizes[1] - 1;
  for (c1_i11 = 0; c1_i11 <= c1_j_loop_ub; c1_i11 = c1_i11 + 1) {
    c1_e_u_data[c1_i11] = c1_e_hoistedGlobal_data[c1_i11];
  }

  c1_k_y = NULL;
  if (!chartInstance->c1_jv_not_empty) {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_k_y, sf_mex_create("y", &c1_e_u_data, 0, 0U, 1U, 0U, 2,
      c1_e_u_sizes[0], c1_e_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 9, c1_k_y);
  c1_p_hoistedGlobal = chartInstance->c1_kv;
  c1_p_u = c1_p_hoistedGlobal;
  c1_l_y = NULL;
  if (!chartInstance->c1_kv_not_empty) {
    sf_mex_assign(&c1_l_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_l_y, sf_mex_create("y", &c1_p_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 10, c1_l_y);
  c1_q_hoistedGlobal = chartInstance->c1_nhn;
  c1_q_u = c1_q_hoistedGlobal;
  c1_m_y = NULL;
  if (!chartInstance->c1_nhn_not_empty) {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_m_y, sf_mex_create("y", &c1_q_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 11, c1_m_y);
  c1_r_hoistedGlobal = chartInstance->c1_number_of_weights;
  c1_r_u = c1_r_hoistedGlobal;
  c1_n_y = NULL;
  if (!chartInstance->c1_number_of_weights_not_empty) {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_n_y, sf_mex_create("y", &c1_r_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 12, c1_n_y);
  c1_s_hoistedGlobal = chartInstance->c1_opk;
  c1_s_u = c1_s_hoistedGlobal;
  c1_o_y = NULL;
  if (!chartInstance->c1_opk_not_empty) {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_o_y, sf_mex_create("y", &c1_s_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 13, c1_o_y);
  c1_t_hoistedGlobal = chartInstance->c1_sm;
  c1_t_u = c1_t_hoistedGlobal;
  c1_p_y = NULL;
  if (!chartInstance->c1_sm_not_empty) {
    sf_mex_assign(&c1_p_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_p_y, sf_mex_create("y", &c1_t_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_setcell(c1_y, 14, c1_p_y);
  c1_f_hoistedGlobal_sizes[0] = 7;
  c1_f_hoistedGlobal_sizes[1] = 3;
  c1_u_hoistedGlobal = c1_f_hoistedGlobal_sizes[0];
  c1_v_hoistedGlobal = c1_f_hoistedGlobal_sizes[1];
  c1_k_loop_ub = chartInstance->c1_w1_sizes[0] * chartInstance->c1_w1_sizes[1] -
    1;
  for (c1_i12 = 0; c1_i12 <= c1_k_loop_ub; c1_i12 = c1_i12 + 1) {
    c1_f_hoistedGlobal_data[c1_i12] = chartInstance->c1_w1_data[c1_i12];
  }

  c1_f_u_sizes[0] = 7;
  c1_f_u_sizes[1] = 3;
  c1_u_u = c1_f_u_sizes[0];
  c1_v_u = c1_f_u_sizes[1];
  c1_l_loop_ub = c1_f_hoistedGlobal_sizes[0] * c1_f_hoistedGlobal_sizes[1] - 1;
  for (c1_i13 = 0; c1_i13 <= c1_l_loop_ub; c1_i13 = c1_i13 + 1) {
    c1_f_u_data[c1_i13] = c1_f_hoistedGlobal_data[c1_i13];
  }

  c1_q_y = NULL;
  if (!chartInstance->c1_w1_not_empty) {
    sf_mex_assign(&c1_q_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_q_y, sf_mex_create("y", &c1_f_u_data, 0, 0U, 1U, 0U, 2,
      c1_f_u_sizes[0], c1_f_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 15, c1_q_y);
  c1_g_hoistedGlobal_sizes[0] = 1;
  c1_g_hoistedGlobal_sizes[1] = 8;
  c1_w_hoistedGlobal = c1_g_hoistedGlobal_sizes[0];
  c1_x_hoistedGlobal = c1_g_hoistedGlobal_sizes[1];
  c1_m_loop_ub = chartInstance->c1_w2_sizes[0] * chartInstance->c1_w2_sizes[1] -
    1;
  for (c1_i14 = 0; c1_i14 <= c1_m_loop_ub; c1_i14 = c1_i14 + 1) {
    c1_g_hoistedGlobal_data[c1_i14] = chartInstance->c1_w2_data[c1_i14];
  }

  c1_g_u_sizes[0] = 1;
  c1_g_u_sizes[1] = 8;
  c1_w_u = c1_g_u_sizes[0];
  c1_x_u = c1_g_u_sizes[1];
  c1_n_loop_ub = c1_g_hoistedGlobal_sizes[0] * c1_g_hoistedGlobal_sizes[1] - 1;
  for (c1_i15 = 0; c1_i15 <= c1_n_loop_ub; c1_i15 = c1_i15 + 1) {
    c1_g_u_data[c1_i15] = c1_g_hoistedGlobal_data[c1_i15];
  }

  c1_r_y = NULL;
  if (!chartInstance->c1_w2_not_empty) {
    sf_mex_assign(&c1_r_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_r_y, sf_mex_create("y", &c1_g_u_data, 0, 0U, 1U, 0U, 2,
      c1_g_u_sizes[0], c1_g_u_sizes[1]));
  }

  sf_mex_setcell(c1_y, 16, c1_r_y);
  c1_y_hoistedGlobal = chartInstance->c1_is_active_c1_PII_speed;
  c1_y_u = c1_y_hoistedGlobal;
  c1_s_y = NULL;
  sf_mex_assign(&c1_s_y, sf_mex_create("y", &c1_y_u, 3, 0U, 0U, 0U, 0));
  sf_mex_setcell(c1_y, 17, c1_s_y);
  sf_mex_assign(&c1_st, c1_y);
  return c1_st;
}

static void set_sim_state_c1_PII_speed(SFc1_PII_speedInstanceStruct
  *chartInstance, const mxArray *c1_st)
{
  const mxArray *c1_u;
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[49];
  int32_T c1_i16;
  int32_T c1_i17;
  int32_T c1_loop_ub;
  int32_T c1_i18;
  int32_T c1_b_tmp_sizes[2];
  real_T c1_b_tmp_data[21];
  int32_T c1_i19;
  int32_T c1_i20;
  int32_T c1_b_loop_ub;
  int32_T c1_i21;
  int32_T c1_c_tmp_sizes[2];
  real_T c1_c_tmp_data[8];
  int32_T c1_i22;
  int32_T c1_i23;
  int32_T c1_c_loop_ub;
  int32_T c1_i24;
  real_T c1_dv0[30];
  int32_T c1_i25;
  int32_T c1_d_tmp_sizes[2];
  real_T c1_d_tmp_data[8];
  int32_T c1_i26;
  int32_T c1_i27;
  int32_T c1_d_loop_ub;
  int32_T c1_i28;
  int32_T c1_e_tmp_sizes[2];
  real_T c1_e_tmp_data[49];
  int32_T c1_i29;
  int32_T c1_i30;
  int32_T c1_e_loop_ub;
  int32_T c1_i31;
  int32_T c1_f_tmp_sizes[2];
  real_T c1_f_tmp_data[21];
  int32_T c1_i32;
  int32_T c1_i33;
  int32_T c1_f_loop_ub;
  int32_T c1_i34;
  int32_T c1_g_tmp_sizes[2];
  real_T c1_g_tmp_data[8];
  int32_T c1_i35;
  int32_T c1_i36;
  int32_T c1_g_loop_ub;
  int32_T c1_i37;
  real_T *c1_sys;
  real_T *c1_waga1;
  c1_waga1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_sys = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  chartInstance->c1_doneDoubleBufferReInit = TRUE;
  c1_u = sf_mex_dup(c1_st);
  *c1_sys = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 0)),
    "sys");
  *c1_waga1 = c1_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u,
    1)), "waga1");
  c1_b_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 2)), "dj",
                        c1_tmp_data, c1_tmp_sizes);
  chartInstance->c1_dj_sizes[0] = 7;
  chartInstance->c1_dj_sizes[1] = 7;
  c1_i16 = chartInstance->c1_dj_sizes[0];
  c1_i17 = chartInstance->c1_dj_sizes[1];
  c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
  for (c1_i18 = 0; c1_i18 <= c1_loop_ub; c1_i18 = c1_i18 + 1) {
    chartInstance->c1_dj_data[c1_i18] = c1_tmp_data[c1_i18];
  }

  chartInstance->c1_dk = c1_c_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 3)), "dk");
  c1_d_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 4)),
                        "dw1", c1_b_tmp_data, c1_b_tmp_sizes);
  chartInstance->c1_dw1_sizes[0] = 7;
  chartInstance->c1_dw1_sizes[1] = 3;
  c1_i19 = chartInstance->c1_dw1_sizes[0];
  c1_i20 = chartInstance->c1_dw1_sizes[1];
  c1_b_loop_ub = c1_b_tmp_sizes[0] * c1_b_tmp_sizes[1] - 1;
  for (c1_i21 = 0; c1_i21 <= c1_b_loop_ub; c1_i21 = c1_i21 + 1) {
    chartInstance->c1_dw1_data[c1_i21] = c1_b_tmp_data[c1_i21];
  }

  c1_e_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 5)),
                        "dw2", c1_c_tmp_data, c1_c_tmp_sizes);
  chartInstance->c1_dw2_sizes[0] = 1;
  chartInstance->c1_dw2_sizes[1] = 8;
  c1_i22 = chartInstance->c1_dw2_sizes[0];
  c1_i23 = chartInstance->c1_dw2_sizes[1];
  c1_c_loop_ub = c1_c_tmp_sizes[0] * c1_c_tmp_sizes[1] - 1;
  for (c1_i24 = 0; c1_i24 <= c1_c_loop_ub; c1_i24 = c1_i24 + 1) {
    chartInstance->c1_dw2_data[c1_i24] = c1_c_tmp_data[c1_i24];
  }

  chartInstance->c1_init_nn_output = c1_f_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 6)), "init_nn_output");
  c1_g_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 7)),
                        "init_state", c1_dv0);
  for (c1_i25 = 0; c1_i25 < 30; c1_i25 = c1_i25 + 1) {
    chartInstance->c1_init_state[c1_i25] = c1_dv0[c1_i25];
  }

  c1_h_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 8)),
                        "ipj", c1_d_tmp_data, c1_d_tmp_sizes);
  chartInstance->c1_ipj_sizes[0] = 1;
  chartInstance->c1_ipj_sizes[1] = 8;
  c1_i26 = chartInstance->c1_ipj_sizes[0];
  c1_i27 = chartInstance->c1_ipj_sizes[1];
  c1_d_loop_ub = c1_d_tmp_sizes[0] * c1_d_tmp_sizes[1] - 1;
  for (c1_i28 = 0; c1_i28 <= c1_d_loop_ub; c1_i28 = c1_i28 + 1) {
    chartInstance->c1_ipj_data[c1_i28] = c1_d_tmp_data[c1_i28];
  }

  c1_i_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 9)), "jv",
                        c1_e_tmp_data, c1_e_tmp_sizes);
  chartInstance->c1_jv_sizes[0] = 7;
  chartInstance->c1_jv_sizes[1] = 7;
  c1_i29 = chartInstance->c1_jv_sizes[0];
  c1_i30 = chartInstance->c1_jv_sizes[1];
  c1_e_loop_ub = c1_e_tmp_sizes[0] * c1_e_tmp_sizes[1] - 1;
  for (c1_i31 = 0; c1_i31 <= c1_e_loop_ub; c1_i31 = c1_i31 + 1) {
    chartInstance->c1_jv_data[c1_i31] = c1_e_tmp_data[c1_i31];
  }

  chartInstance->c1_kv = c1_j_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 10)), "kv");
  chartInstance->c1_nhn = c1_k_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 11)), "nhn");
  chartInstance->c1_number_of_weights = c1_l_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 12)), "number_of_weights"
    );
  chartInstance->c1_opk = c1_m_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 13)), "opk");
  chartInstance->c1_sm = c1_n_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c1_u, 14)), "sm");
  c1_o_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 15)),
                        "w1", c1_f_tmp_data, c1_f_tmp_sizes);
  chartInstance->c1_w1_sizes[0] = 7;
  chartInstance->c1_w1_sizes[1] = 3;
  c1_i32 = chartInstance->c1_w1_sizes[0];
  c1_i33 = chartInstance->c1_w1_sizes[1];
  c1_f_loop_ub = c1_f_tmp_sizes[0] * c1_f_tmp_sizes[1] - 1;
  for (c1_i34 = 0; c1_i34 <= c1_f_loop_ub; c1_i34 = c1_i34 + 1) {
    chartInstance->c1_w1_data[c1_i34] = c1_f_tmp_data[c1_i34];
  }

  c1_p_emlrt_marshallIn(chartInstance, sf_mex_dup(sf_mex_getcell(c1_u, 16)),
                        "w2", c1_g_tmp_data, c1_g_tmp_sizes);
  chartInstance->c1_w2_sizes[0] = 1;
  chartInstance->c1_w2_sizes[1] = 8;
  c1_i35 = chartInstance->c1_w2_sizes[0];
  c1_i36 = chartInstance->c1_w2_sizes[1];
  c1_g_loop_ub = c1_g_tmp_sizes[0] * c1_g_tmp_sizes[1] - 1;
  for (c1_i37 = 0; c1_i37 <= c1_g_loop_ub; c1_i37 = c1_i37 + 1) {
    chartInstance->c1_w2_data[c1_i37] = c1_g_tmp_data[c1_i37];
  }

  chartInstance->c1_is_active_c1_PII_speed = c1_q_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c1_u, 17)),
    "is_active_c1_PII_speed");
  sf_mex_destroy(&c1_u);
  c1_update_debugger_state_c1_PII_speed(chartInstance);
  sf_mex_destroy(&c1_st);
}

static void finalize_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
}

static void sf_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
  int32_T c1_i38;
  int32_T c1_previousEvent;
  real_T *c1_sys;
  real_T *c1_waga1;
  real_T (*c1_u)[9];
  c1_waga1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_sys = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _sfTime_ = (real_T)ssGetT(chartInstance->S);
  _SFD_CC_CALL(CHART_ENTER_SFUNCTION_TAG,0);
  for (c1_i38 = 0; c1_i38 < 9; c1_i38 = c1_i38 + 1) {
    _SFD_DATA_RANGE_CHECK((*c1_u)[c1_i38], 0U);
  }

  _SFD_DATA_RANGE_CHECK(*c1_sys, 1U);
  _SFD_DATA_RANGE_CHECK(*c1_waga1, 2U);
  c1_previousEvent = _sfEvent_;
  _sfEvent_ = CALL_EVENT;
  c1_c1_PII_speed(chartInstance);
  _sfEvent_ = c1_previousEvent;
  sf_debug_check_for_state_inconsistency(_PII_speedMachineNumber_,
    chartInstance->chartNumber, chartInstance->instanceNumber);
}

static void c1_c1_PII_speed(SFc1_PII_speedInstanceStruct *chartInstance)
{
  int32_T c1_i39;
  real_T c1_hoistedGlobal[9];
  int32_T c1_i40;
  real_T c1_u[9];
  uint32_T c1_debug_family_var_map[24];
  static const char *c1_sv0[24] = { "nv", "j", "i", "k", "nargin", "nargout",
    "u", "sys", "waga1", "nhn", "init_nn_output",
    "number_of_weights", "init_state", "w1", "w2", "dw1", "dw2", "jv", "dj",
    "ipj", "dk", "kv", "sm",
    "opk" };

  real_T c1_nv;
  real_T c1_j;
  real_T c1_i;
  real_T c1_k;
  real_T c1_nargin = 1.0;
  real_T c1_nargout = 2.0;
  real_T c1_sys;
  real_T c1_waga1;
  int32_T c1_i41;
  static real_T c1_dv1[30] = { 0.0312, 0.3886, -0.2363, -0.2652, 0.3397, -0.0045,
    -0.3476, -0.2692, 0.158, 0.0629, -0.2082, 0.1223,
    0.2159, -0.2193, -0.0877, -0.1378, 0.2814, -0.3645, 0.4021, -0.2104, -0.0004,
    0.2836, 0.1771, -0.3502,
    0.1966, -0.371, 0.4459, 0.3864, 0.015, 0.1794 };

  int32_T c1_i42;
  int32_T c1_i43;
  int32_T c1_i44;
  int32_T c1_i45;
  int32_T c1_i46;
  int32_T c1_i47;
  int32_T c1_i48;
  int32_T c1_i49;
  int32_T c1_i50;
  int32_T c1_i51;
  int32_T c1_i52;
  int32_T c1_i53;
  int32_T c1_i54;
  int32_T c1_i55;
  int32_T c1_i56;
  int32_T c1_i57;
  int32_T c1_i58;
  int32_T c1_i59;
  int32_T c1_i60;
  int32_T c1_i61;
  int32_T c1_i62;
  real_T c1_loop_ub;
  real_T c1_b_j;
  real_T c1_b_i;
  real_T c1_b_loop_ub;
  real_T c1_c_j;
  real_T c1_c_loop_ub;
  real_T c1_d_j;
  int32_T c1_hoistedGlobal_sizes[2];
  int32_T c1_b_hoistedGlobal;
  int32_T c1_c_hoistedGlobal;
  int32_T c1_d_loop_ub;
  int32_T c1_i63;
  real_T c1_hoistedGlobal_data[21];
  int32_T c1_e_j;
  int32_T c1_i64;
  real_T c1_a[3];
  real_T c1_b[3];
  int32_T c1_i65;
  real_T c1_x[3];
  int32_T c1_i66;
  real_T c1_y[3];
  int32_T c1_i67;
  real_T c1_b_x[3];
  int32_T c1_i68;
  real_T c1_b_y[3];
  int32_T c1_i69;
  real_T c1_c_x[3];
  int32_T c1_i70;
  real_T c1_c_y[3];
  int32_T c1_i71;
  real_T c1_d_x[3];
  int32_T c1_i72;
  real_T c1_d_y[3];
  real_T c1_e_y;
  int32_T c1_b_hoistedGlobal_sizes[2];
  int32_T c1_d_hoistedGlobal;
  int32_T c1_e_hoistedGlobal;
  int32_T c1_e_loop_ub;
  int32_T c1_i73;
  real_T c1_b_hoistedGlobal_data[49];
  real_T c1_b_b;
  real_T c1_f_y;
  real_T c1_e_x;
  real_T c1_f_x;
  real_T c1_g_x;
  int32_T c1_tmp_sizes[1];
  int32_T c1_i74;
  int32_T c1_tmp_data[8];
  int32_T c1_c_hoistedGlobal_sizes[2];
  int32_T c1_f_hoistedGlobal;
  int32_T c1_g_hoistedGlobal;
  int32_T c1_f_loop_ub;
  int32_T c1_i75;
  real_T c1_c_hoistedGlobal_data[8];
  int32_T c1_d_hoistedGlobal_sizes[2];
  int32_T c1_h_hoistedGlobal;
  int32_T c1_i_hoistedGlobal;
  int32_T c1_g_loop_ub;
  int32_T c1_i76;
  real_T c1_d_hoistedGlobal_data[8];
  int32_T c1_a_sizes[2];
  int32_T c1_i77;
  real_T c1_a_data[8];
  int32_T c1_b_sizes[1];
  int32_T c1_h_loop_ub;
  int32_T c1_i78;
  real_T c1_b_data[8];
  int32_T c1_x_sizes[2];
  int32_T c1_h_x;
  int32_T c1_i_x;
  int32_T c1_i_loop_ub;
  int32_T c1_i79;
  real_T c1_x_data[8];
  int32_T c1_y_sizes[1];
  int32_T c1_i80;
  real_T c1_y_data[8];
  int32_T c1_b_x_sizes[2];
  int32_T c1_j_x;
  int32_T c1_k_x;
  int32_T c1_j_loop_ub;
  int32_T c1_i81;
  real_T c1_b_x_data[8];
  int32_T c1_b_y_sizes[1];
  int32_T c1_i82;
  real_T c1_b_y_data[8];
  int32_T c1_c_x_sizes[2];
  int32_T c1_l_x;
  int32_T c1_m_x;
  int32_T c1_k_loop_ub;
  int32_T c1_i83;
  real_T c1_c_x_data[8];
  int32_T c1_c_y_sizes[1];
  int32_T c1_i84;
  real_T c1_c_y_data[8];
  int32_T c1_d_x_sizes[2];
  int32_T c1_n_x;
  int32_T c1_o_x;
  int32_T c1_l_loop_ub;
  int32_T c1_i85;
  real_T c1_d_x_data[8];
  int32_T c1_d_y_sizes[1];
  int32_T c1_i86;
  real_T c1_d_y_data[8];
  real_T c1_g_y;
  real_T c1_j_hoistedGlobal;
  real_T c1_c_b;
  real_T c1_h_y;
  real_T c1_p_x;
  real_T c1_q_x;
  real_T c1_f_j;
  real_T c1_b_a;
  real_T c1_i_y;
  real_T c1_k_hoistedGlobal;
  real_T c1_l_hoistedGlobal;
  real_T c1_c_a;
  real_T c1_d_b;
  real_T c1_j_y;
  real_T c1_d_a;
  real_T c1_e_b;
  real_T c1_m_hoistedGlobal;
  real_T c1_e_a;
  real_T c1_f_b;
  real_T c1_k_y;
  int32_T c1_e_hoistedGlobal_sizes[2];
  int32_T c1_n_hoistedGlobal;
  int32_T c1_o_hoistedGlobal;
  int32_T c1_m_loop_ub;
  int32_T c1_i87;
  real_T c1_e_hoistedGlobal_data[8];
  real_T c1_f_a;
  real_T c1_g_b;
  real_T c1_l_y;
  real_T c1_g_j;
  real_T c1_p_hoistedGlobal;
  int32_T c1_f_hoistedGlobal_sizes[2];
  int32_T c1_q_hoistedGlobal;
  int32_T c1_r_hoistedGlobal;
  int32_T c1_n_loop_ub;
  int32_T c1_i88;
  real_T c1_f_hoistedGlobal_data[8];
  real_T c1_g_a;
  real_T c1_h_b;
  real_T c1_m_y;
  real_T c1_s_hoistedGlobal;
  real_T c1_h_a;
  real_T c1_n_y;
  int32_T c1_g_hoistedGlobal_sizes[2];
  int32_T c1_t_hoistedGlobal;
  int32_T c1_u_hoistedGlobal;
  int32_T c1_o_loop_ub;
  int32_T c1_i89;
  real_T c1_g_hoistedGlobal_data[8];
  int32_T c1_h_hoistedGlobal_sizes[2];
  int32_T c1_v_hoistedGlobal;
  int32_T c1_w_hoistedGlobal;
  int32_T c1_p_loop_ub;
  int32_T c1_i90;
  real_T c1_h_hoistedGlobal_data[8];
  real_T c1_i_a;
  real_T c1_i_b;
  real_T c1_o_y;
  real_T c1_j_a;
  real_T c1_j_b;
  real_T c1_h_j;
  real_T c1_c_i;
  int32_T c1_i_hoistedGlobal_sizes[2];
  int32_T c1_x_hoistedGlobal;
  int32_T c1_y_hoistedGlobal;
  int32_T c1_q_loop_ub;
  int32_T c1_i91;
  real_T c1_i_hoistedGlobal_data[49];
  real_T c1_k_a;
  real_T c1_k_b;
  real_T c1_p_y;
  real_T c1_l_a;
  real_T c1_l_b;
  real_T c1_q_y;
  real_T c1_i_j;
  real_T c1_d_i;
  real_T *c1_b_sys;
  real_T *c1_b_waga1;
  real_T (*c1_b_u)[9];
  c1_b_waga1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
  c1_b_sys = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
  c1_b_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
  _SFD_CC_CALL(CHART_ENTER_DURING_FUNCTION_TAG,0);
  for (c1_i39 = 0; c1_i39 < 9; c1_i39 = c1_i39 + 1) {
    c1_hoistedGlobal[c1_i39] = (*c1_b_u)[c1_i39];
  }

  for (c1_i40 = 0; c1_i40 < 9; c1_i40 = c1_i40 + 1) {
    c1_u[c1_i40] = c1_hoistedGlobal[c1_i40];
  }

  sf_debug_symbol_scope_push_eml(0U, 24U, 24U, c1_sv0, c1_debug_family_var_map);
  sf_debug_symbol_scope_add_eml(&c1_nv, c1_p_sf_marshall, 0U);
  sf_debug_symbol_scope_add_eml(&c1_j, c1_p_sf_marshall, 1U);
  sf_debug_symbol_scope_add_eml(&c1_i, c1_p_sf_marshall, 2U);
  sf_debug_symbol_scope_add_eml(&c1_k, c1_p_sf_marshall, 3U);
  sf_debug_symbol_scope_add_eml(&c1_nargin, c1_p_sf_marshall, 4U);
  sf_debug_symbol_scope_add_eml(&c1_nargout, c1_p_sf_marshall, 5U);
  sf_debug_symbol_scope_add_eml(&c1_u, c1_q_sf_marshall, 6U);
  sf_debug_symbol_scope_add_eml(&c1_sys, c1_p_sf_marshall, 7U);
  sf_debug_symbol_scope_add_eml(&c1_waga1, c1_p_sf_marshall, 8U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_nhn, c1_o_sf_marshall, 9U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_init_nn_output,
    c1_n_sf_marshall, 10U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_number_of_weights,
    c1_m_sf_marshall, 11U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_init_state, c1_l_sf_marshall,
    12U);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_w1_data, (const int32_T *)
    &chartInstance->c1_w1_sizes, NULL, 1, (void *)
    c1_k_sf_marshall, 13);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_w2_data, (const int32_T *)
    &chartInstance->c1_w2_sizes, NULL, 1, (void *)
    c1_j_sf_marshall, 14);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_dw1_data, (const int32_T *)
    &chartInstance->c1_dw1_sizes, NULL, 1, (void *)
    c1_i_sf_marshall, 15);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_dw2_data, (const int32_T *)
    &chartInstance->c1_dw2_sizes, NULL, 1, (void *)
    c1_h_sf_marshall, 16);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_jv_data, (const int32_T *)
    &chartInstance->c1_jv_sizes, NULL, 1, (void *)
    c1_g_sf_marshall, 17);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_dj_data, (const int32_T *)
    &chartInstance->c1_dj_sizes, NULL, 1, (void *)
    c1_f_sf_marshall, 18);
  sf_debug_symbol_scope_add_eml_dyn(&chartInstance->c1_ipj_data, (const int32_T *)
    &chartInstance->c1_ipj_sizes, NULL, 1, (void *)
    c1_e_sf_marshall, 19);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_dk, c1_d_sf_marshall, 20U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_kv, c1_c_sf_marshall, 21U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_sm, c1_b_sf_marshall, 22U);
  sf_debug_symbol_scope_add_eml(&chartInstance->c1_opk, c1_sf_marshall, 23U);
  CV_EML_FCN(0, 0);
  _SFD_EML_CALL(0,5);
  chartInstance->c1_nhn = 7.0;
  chartInstance->c1_nhn_not_empty = TRUE;

  /* liczba neuronow warstwy ukrytej */
  _SFD_EML_CALL(0,6);
  chartInstance->c1_init_nn_output = 0.0;
  chartInstance->c1_init_nn_output_not_empty = TRUE;

  /* wartosc poczatkowa sieci neuronowej */
  _SFD_EML_CALL(0,7);
  chartInstance->c1_number_of_weights = 29.0;
  chartInstance->c1_number_of_weights_not_empty = TRUE;

  /*  init_state=rand(number_of_weights+1,1)-0.5; */
  _SFD_EML_CALL(0,11);
  for (c1_i41 = 0; c1_i41 < 30; c1_i41 = c1_i41 + 1) {
    chartInstance->c1_init_state[c1_i41] = c1_dv1[c1_i41];
  }

  chartInstance->c1_init_state_not_empty = TRUE;
  _SFD_EML_CALL(0,43);
  chartInstance->c1_init_state[29] = 0.0;
  _SFD_EML_CALL(0,46);
  if (CV_EML_IF(0, 0, !chartInstance->c1_w1_not_empty)) {
    /*  if (u(10)==0) */
    _SFD_EML_CALL(0,48);
    chartInstance->c1_w1_sizes[0] = 7;
    chartInstance->c1_w1_sizes[1] = 3;
    c1_i42 = chartInstance->c1_w1_sizes[0];
    c1_i43 = chartInstance->c1_w1_sizes[1];
    for (c1_i44 = 0; c1_i44 < 21; c1_i44 = c1_i44 + 1) {
      chartInstance->c1_w1_data[c1_i44] = 0.0;
    }

    chartInstance->c1_w1_not_empty = TRUE;
    _SFD_EML_CALL(0,49);
    chartInstance->c1_w2_sizes[0] = 1;
    chartInstance->c1_w2_sizes[1] = 8;
    c1_i45 = chartInstance->c1_w2_sizes[0];
    c1_i46 = chartInstance->c1_w2_sizes[1];
    for (c1_i47 = 0; c1_i47 < 8; c1_i47 = c1_i47 + 1) {
      chartInstance->c1_w2_data[c1_i47] = 0.0;
    }

    chartInstance->c1_w2_not_empty = TRUE;
    _SFD_EML_CALL(0,50);
    chartInstance->c1_dw1_sizes[0] = 7;
    chartInstance->c1_dw1_sizes[1] = 3;
    c1_i48 = chartInstance->c1_dw1_sizes[0];
    c1_i49 = chartInstance->c1_dw1_sizes[1];
    for (c1_i50 = 0; c1_i50 < 21; c1_i50 = c1_i50 + 1) {
      chartInstance->c1_dw1_data[c1_i50] = 0.0;
    }

    chartInstance->c1_dw1_not_empty = TRUE;
    _SFD_EML_CALL(0,51);
    chartInstance->c1_dw2_sizes[0] = 1;
    chartInstance->c1_dw2_sizes[1] = 8;
    c1_i51 = chartInstance->c1_dw2_sizes[0];
    c1_i52 = chartInstance->c1_dw2_sizes[1];
    for (c1_i53 = 0; c1_i53 < 8; c1_i53 = c1_i53 + 1) {
      chartInstance->c1_dw2_data[c1_i53] = 0.0;
    }

    chartInstance->c1_dw2_not_empty = TRUE;
    _SFD_EML_CALL(0,52);
    chartInstance->c1_jv_sizes[0] = 7;
    chartInstance->c1_jv_sizes[1] = 7;
    c1_i54 = chartInstance->c1_jv_sizes[0];
    c1_i55 = chartInstance->c1_jv_sizes[1];
    for (c1_i56 = 0; c1_i56 < 49; c1_i56 = c1_i56 + 1) {
      chartInstance->c1_jv_data[c1_i56] = 0.0;
    }

    chartInstance->c1_jv_not_empty = TRUE;
    _SFD_EML_CALL(0,53);
    chartInstance->c1_dj_sizes[0] = 7;
    chartInstance->c1_dj_sizes[1] = 7;
    c1_i57 = chartInstance->c1_dj_sizes[0];
    c1_i58 = chartInstance->c1_dj_sizes[1];
    for (c1_i59 = 0; c1_i59 < 49; c1_i59 = c1_i59 + 1) {
      chartInstance->c1_dj_data[c1_i59] = 0.0;
    }

    chartInstance->c1_dj_not_empty = TRUE;
    _SFD_EML_CALL(0,54);
    chartInstance->c1_ipj_sizes[0] = 1;
    chartInstance->c1_ipj_sizes[1] = 8;
    c1_i60 = chartInstance->c1_ipj_sizes[0];
    c1_i61 = chartInstance->c1_ipj_sizes[1];
    for (c1_i62 = 0; c1_i62 < 8; c1_i62 = c1_i62 + 1) {
      chartInstance->c1_ipj_data[c1_i62] = 0.0;
    }

    chartInstance->c1_ipj_not_empty = TRUE;
    _SFD_EML_CALL(0,55);
    chartInstance->c1_dk = 0.0;
    chartInstance->c1_dk_not_empty = TRUE;
    _SFD_EML_CALL(0,56);
    chartInstance->c1_kv = 0.0;
    chartInstance->c1_kv_not_empty = TRUE;
    _SFD_EML_CALL(0,57);
    chartInstance->c1_sm = 0.0;
    chartInstance->c1_sm_not_empty = TRUE;
    _SFD_EML_CALL(0,58);
    chartInstance->c1_opk = 0.0;
    chartInstance->c1_opk_not_empty = TRUE;
    _SFD_EML_CALL(0,59);
    c1_nv = 0.0;
    c1_j = 1.0;
    c1_loop_ub = c1_u[6];
    c1_b_j = 1.0;
    while (c1_b_j <= c1_loop_ub) {
      c1_j = c1_b_j;
      CV_EML_FOR(0, 0, 1);
      c1_i = 1.0;
      c1_b_i = 1.0;
      while (c1_b_i <= 3.0) {
        c1_i = c1_b_i;
        CV_EML_FOR(0, 1, 1);
        _SFD_EML_CALL(0,62);
        c1_nv = c1_nv + 1.0;
        _SFD_EML_CALL(0,63);
        chartInstance->c1_w1_data[(_SFD_EML_ARRAY_BOUNDS_CHECK("w1", (int32_T)
          c1_j, 1, 7, 1, 0) - 1) + chartInstance->c1_w1_sizes[0] * ((
          int32_T)c1_i - 1)] = chartInstance->
          c1_init_state[_SFD_EML_ARRAY_BOUNDS_CHECK("init_state", (int32_T)c1_nv,
          1, 30, 1, 0) - 1];
        c1_b_i = c1_b_i + 1.0;
        sf_mex_listen_for_ctrl_c(chartInstance->S);
      }

      CV_EML_FOR(0, 1, 0);
      c1_b_j = c1_b_j + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 0, 0);
    _SFD_EML_CALL(0,66);
    c1_k = 1.0;
    c1_j = 1.0;
    c1_b_loop_ub = c1_u[6] + 1.0;
    c1_c_j = 1.0;
    while (c1_c_j <= c1_b_loop_ub) {
      c1_j = c1_c_j;
      CV_EML_FOR(0, 2, 1);
      _SFD_EML_CALL(0,68);
      c1_nv = c1_nv + 1.0;
      _SFD_EML_CALL(0,69);
      chartInstance->c1_w2_data[chartInstance->c1_w2_sizes[0] *
        (_SFD_EML_ARRAY_BOUNDS_CHECK("w2", (int32_T)c1_j, 1, 8, 2, 0) - 1)] =
        chartInstance->c1_init_state[_SFD_EML_ARRAY_BOUNDS_CHECK("init_state",
        (int32_T)c1_nv, 1, 30, 1, 0) - 1];
      c1_c_j = c1_c_j + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 2, 0);
  }

  c1_j = 1.0;
  c1_c_loop_ub = c1_u[6];
  c1_d_j = 1.0;
  while (c1_d_j <= c1_c_loop_ub) {
    c1_j = c1_d_j;
    CV_EML_FOR(0, 3, 1);
    _SFD_EML_CALL(0,75);
    c1_hoistedGlobal_sizes[0] = 7;
    c1_hoistedGlobal_sizes[1] = 3;
    c1_b_hoistedGlobal = c1_hoistedGlobal_sizes[0];
    c1_c_hoistedGlobal = c1_hoistedGlobal_sizes[1];
    c1_d_loop_ub = chartInstance->c1_w1_sizes[0] * chartInstance->c1_w1_sizes[1]
      - 1;
    for (c1_i63 = 0; c1_i63 <= c1_d_loop_ub; c1_i63 = c1_i63 + 1) {
      c1_hoistedGlobal_data[c1_i63] = chartInstance->c1_w1_data[c1_i63];
    }

    c1_e_j = _SFD_EML_ARRAY_BOUNDS_CHECK("w1", (int32_T)c1_j, 1, 7, 1, 0) - 1;
    for (c1_i64 = 0; c1_i64 < 3; c1_i64 = c1_i64 + 1) {
      c1_a[c1_i64] = c1_hoistedGlobal_data[c1_e_j + c1_hoistedGlobal_sizes[0] *
        c1_i64];
    }

    c1_b[0] = c1_u[0];
    c1_b[1] = c1_u[1];
    c1_b[2] = c1_u[2];
    c1_eml_scalar_eg(chartInstance);
    for (c1_i65 = 0; c1_i65 < 3; c1_i65 = c1_i65 + 1) {
      c1_x[c1_i65] = c1_a[c1_i65];
    }

    for (c1_i66 = 0; c1_i66 < 3; c1_i66 = c1_i66 + 1) {
      c1_y[c1_i66] = c1_b[c1_i66];
    }

    for (c1_i67 = 0; c1_i67 < 3; c1_i67 = c1_i67 + 1) {
      c1_b_x[c1_i67] = c1_x[c1_i67];
    }

    for (c1_i68 = 0; c1_i68 < 3; c1_i68 = c1_i68 + 1) {
      c1_b_y[c1_i68] = c1_y[c1_i68];
    }

    for (c1_i69 = 0; c1_i69 < 3; c1_i69 = c1_i69 + 1) {
      c1_c_x[c1_i69] = c1_b_x[c1_i69];
    }

    for (c1_i70 = 0; c1_i70 < 3; c1_i70 = c1_i70 + 1) {
      c1_c_y[c1_i70] = c1_b_y[c1_i70];
    }

    for (c1_i71 = 0; c1_i71 < 3; c1_i71 = c1_i71 + 1) {
      c1_d_x[c1_i71] = c1_c_x[c1_i71];
    }

    for (c1_i72 = 0; c1_i72 < 3; c1_i72 = c1_i72 + 1) {
      c1_d_y[c1_i72] = c1_c_y[c1_i72];
    }

    c1_e_y = c1_ceval_xdot(chartInstance, 3, c1_d_x, 1, 1, c1_d_y, 1, 1);
    chartInstance->c1_jv_data[_SFD_EML_ARRAY_BOUNDS_CHECK("jv", (int32_T)c1_j, 1,
      49, 1, 0) - 1] = c1_e_y;

    /* u(1)=K1*e ,u(2)=K2*de/dt */
    /* u(3)=1 is bias unity */
    _SFD_EML_CALL(0,77);
    c1_b_hoistedGlobal_sizes[0] = 7;
    c1_b_hoistedGlobal_sizes[1] = 7;
    c1_d_hoistedGlobal = c1_b_hoistedGlobal_sizes[0];
    c1_e_hoistedGlobal = c1_b_hoistedGlobal_sizes[1];
    c1_e_loop_ub = chartInstance->c1_jv_sizes[0] * chartInstance->c1_jv_sizes[1]
      - 1;
    for (c1_i73 = 0; c1_i73 <= c1_e_loop_ub; c1_i73 = c1_i73 + 1) {
      c1_b_hoistedGlobal_data[c1_i73] = chartInstance->c1_jv_data[c1_i73];
    }

    c1_b_b = c1_b_hoistedGlobal_data[(int32_T)c1_j - 1];
    c1_f_y = 0.5 * c1_b_b;
    c1_e_x = c1_f_y;
    c1_f_x = c1_e_x;
    c1_g_x = c1_f_x;
    c1_f_x = c1_g_x;
    c1_f_x = muDoubleScalarTanh(c1_f_x);
    chartInstance->c1_ipj_data[(int32_T)c1_j - 1] = c1_f_x;

    /* outputs of hidden layer */
    c1_d_j = c1_d_j + 1.0;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 3, 0);
  _SFD_EML_CALL(0,80);
  chartInstance->c1_ipj_data[_SFD_EML_ARRAY_BOUNDS_CHECK("ipj", (int32_T)
    _SFD_INTEGER_CHECK("", c1_u[6] + 1.0), 1, 8, 1, 0) - 1] =
    c1_u[5];
  _SFD_EML_CALL(0,81);
  c1_tmp_sizes[0] = 8;
  for (c1_i74 = 0; c1_i74 < 8; c1_i74 = c1_i74 + 1) {
    c1_tmp_data[c1_i74] = 1 + c1_i74;
  }

  c1_c_hoistedGlobal_sizes[0] = 1;
  c1_c_hoistedGlobal_sizes[1] = 8;
  c1_f_hoistedGlobal = c1_c_hoistedGlobal_sizes[0];
  c1_g_hoistedGlobal = c1_c_hoistedGlobal_sizes[1];
  c1_f_loop_ub = chartInstance->c1_w2_sizes[0] * chartInstance->c1_w2_sizes[1] -
    1;
  for (c1_i75 = 0; c1_i75 <= c1_f_loop_ub; c1_i75 = c1_i75 + 1) {
    c1_c_hoistedGlobal_data[c1_i75] = chartInstance->c1_w2_data[c1_i75];
  }

  c1_d_hoistedGlobal_sizes[0] = 1;
  c1_d_hoistedGlobal_sizes[1] = 8;
  c1_h_hoistedGlobal = c1_d_hoistedGlobal_sizes[0];
  c1_i_hoistedGlobal = c1_d_hoistedGlobal_sizes[1];
  c1_g_loop_ub = chartInstance->c1_ipj_sizes[0] * chartInstance->c1_ipj_sizes[1]
    - 1;
  for (c1_i76 = 0; c1_i76 <= c1_g_loop_ub; c1_i76 = c1_i76 + 1) {
    c1_d_hoistedGlobal_data[c1_i76] = chartInstance->c1_ipj_data[c1_i76];
  }

  c1_a_sizes[0] = 1;
  c1_a_sizes[1] = 8;
  for (c1_i77 = 0; c1_i77 < 8; c1_i77 = c1_i77 + 1) {
    c1_a_data[c1_a_sizes[0] * c1_i77] =
      c1_c_hoistedGlobal_data[c1_c_hoistedGlobal_sizes[0] * (c1_tmp_data[c1_i77]
      - 1)];
  }

  c1_b_sizes[0] = c1_d_hoistedGlobal_sizes[1];
  c1_h_loop_ub = c1_d_hoistedGlobal_sizes[1] - 1;
  for (c1_i78 = 0; c1_i78 <= c1_h_loop_ub; c1_i78 = c1_i78 + 1) {
    c1_b_data[c1_i78] = c1_d_hoistedGlobal_data[c1_i78];
  }

  c1_b_eml_scalar_eg(chartInstance);
  c1_x_sizes[0] = 1;
  c1_x_sizes[1] = 8;
  c1_h_x = c1_x_sizes[0];
  c1_i_x = c1_x_sizes[1];
  c1_i_loop_ub = c1_a_sizes[0] * c1_a_sizes[1] - 1;
  for (c1_i79 = 0; c1_i79 <= c1_i_loop_ub; c1_i79 = c1_i79 + 1) {
    c1_x_data[c1_i79] = c1_a_data[c1_i79];
  }

  c1_y_sizes[0] = 8;
  for (c1_i80 = 0; c1_i80 < 8; c1_i80 = c1_i80 + 1) {
    c1_y_data[c1_i80] = c1_b_data[c1_i80];
  }

  c1_b_x_sizes[0] = 1;
  c1_b_x_sizes[1] = 8;
  c1_j_x = c1_b_x_sizes[0];
  c1_k_x = c1_b_x_sizes[1];
  c1_j_loop_ub = c1_x_sizes[0] * c1_x_sizes[1] - 1;
  for (c1_i81 = 0; c1_i81 <= c1_j_loop_ub; c1_i81 = c1_i81 + 1) {
    c1_b_x_data[c1_i81] = c1_x_data[c1_i81];
  }

  c1_b_y_sizes[0] = 8;
  for (c1_i82 = 0; c1_i82 < 8; c1_i82 = c1_i82 + 1) {
    c1_b_y_data[c1_i82] = c1_y_data[c1_i82];
  }

  c1_c_x_sizes[0] = 1;
  c1_c_x_sizes[1] = 8;
  c1_l_x = c1_c_x_sizes[0];
  c1_m_x = c1_c_x_sizes[1];
  c1_k_loop_ub = c1_b_x_sizes[0] * c1_b_x_sizes[1] - 1;
  for (c1_i83 = 0; c1_i83 <= c1_k_loop_ub; c1_i83 = c1_i83 + 1) {
    c1_c_x_data[c1_i83] = c1_b_x_data[c1_i83];
  }

  c1_c_y_sizes[0] = 8;
  for (c1_i84 = 0; c1_i84 < 8; c1_i84 = c1_i84 + 1) {
    c1_c_y_data[c1_i84] = c1_b_y_data[c1_i84];
  }

  c1_d_x_sizes[0] = 1;
  c1_d_x_sizes[1] = 8;
  c1_n_x = c1_d_x_sizes[0];
  c1_o_x = c1_d_x_sizes[1];
  c1_l_loop_ub = c1_c_x_sizes[0] * c1_c_x_sizes[1] - 1;
  for (c1_i85 = 0; c1_i85 <= c1_l_loop_ub; c1_i85 = c1_i85 + 1) {
    c1_d_x_data[c1_i85] = c1_c_x_data[c1_i85];
  }

  c1_d_y_sizes[0] = 8;
  for (c1_i86 = 0; c1_i86 < 8; c1_i86 = c1_i86 + 1) {
    c1_d_y_data[c1_i86] = c1_c_y_data[c1_i86];
  }

  c1_g_y = c1_b_ceval_xdot(chartInstance, 8, c1_d_x_data, c1_d_x_sizes, 1, 1,
    c1_d_y_data, c1_d_y_sizes, 1, 1);
  chartInstance->c1_kv = c1_g_y;
  _SFD_EML_CALL(0,82);
  c1_j_hoistedGlobal = chartInstance->c1_kv;
  c1_c_b = c1_j_hoistedGlobal;
  c1_h_y = 0.5 * c1_c_b;
  c1_p_x = c1_h_y;
  chartInstance->c1_opk = c1_p_x;
  c1_q_x = chartInstance->c1_opk;
  chartInstance->c1_opk = c1_q_x;
  chartInstance->c1_opk = muDoubleScalarTanh(chartInstance->c1_opk);

  /* output of output layer */
  c1_j = 1.0;
  c1_f_j = 1.0;
  while (c1_f_j <= 7.0) {
    c1_j = c1_f_j;
    CV_EML_FOR(0, 4, 1);
    _SFD_EML_CALL(0,88);
    c1_b_a = c1_u[3] + c1_u[4];
    c1_i_y = c1_b_a * 0.5;
    c1_k_hoistedGlobal = chartInstance->c1_opk;
    c1_l_hoistedGlobal = chartInstance->c1_opk;
    c1_c_a = c1_k_hoistedGlobal;
    c1_d_b = c1_l_hoistedGlobal;
    c1_j_y = c1_c_a * c1_d_b;
    c1_d_a = c1_i_y;
    c1_e_b = 1.0 - c1_j_y;
    chartInstance->c1_dk = c1_d_a * c1_e_b;

    /* %%delta adaptation law, dk means delta K,u(4)=K3*e ,u(5)=K4*de/dt */
    _SFD_EML_CALL(0,90);
    c1_m_hoistedGlobal = chartInstance->c1_dk;
    c1_e_a = c1_u[8];
    c1_f_b = c1_m_hoistedGlobal;
    c1_k_y = c1_e_a * c1_f_b;
    c1_e_hoistedGlobal_sizes[0] = 1;
    c1_e_hoistedGlobal_sizes[1] = 8;
    c1_n_hoistedGlobal = c1_e_hoistedGlobal_sizes[0];
    c1_o_hoistedGlobal = c1_e_hoistedGlobal_sizes[1];
    c1_m_loop_ub = chartInstance->c1_ipj_sizes[0] * chartInstance->c1_ipj_sizes
      [1] - 1;
    for (c1_i87 = 0; c1_i87 <= c1_m_loop_ub; c1_i87 = c1_i87 + 1) {
      c1_e_hoistedGlobal_data[c1_i87] = chartInstance->c1_ipj_data[c1_i87];
    }

    c1_f_a = c1_k_y;
    c1_g_b = c1_e_hoistedGlobal_data[(int32_T)c1_j - 1];
    c1_l_y = c1_f_a * c1_g_b;
    chartInstance->c1_dw2_data[chartInstance->c1_dw2_sizes[0] * ((int32_T)c1_j -
      1)] = c1_l_y;

    /* dw2 is weight update quantity for W2 */
    c1_f_j = c1_f_j + 1.0;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 4, 0);

  /* %%%%%%%%%%%%% */
  c1_j = 1.0;
  c1_g_j = 1.0;
  while (c1_g_j <= 7.0) {
    c1_j = c1_g_j;
    CV_EML_FOR(0, 5, 1);
    _SFD_EML_CALL(0,96);
    chartInstance->c1_sm = 0.0;
    _SFD_EML_CALL(0,97);
    c1_p_hoistedGlobal = chartInstance->c1_dk;
    c1_f_hoistedGlobal_sizes[0] = 1;
    c1_f_hoistedGlobal_sizes[1] = 8;
    c1_q_hoistedGlobal = c1_f_hoistedGlobal_sizes[0];
    c1_r_hoistedGlobal = c1_f_hoistedGlobal_sizes[1];
    c1_n_loop_ub = chartInstance->c1_w2_sizes[0] * chartInstance->c1_w2_sizes[1]
      - 1;
    for (c1_i88 = 0; c1_i88 <= c1_n_loop_ub; c1_i88 = c1_i88 + 1) {
      c1_f_hoistedGlobal_data[c1_i88] = chartInstance->c1_w2_data[c1_i88];
    }

    c1_g_a = c1_p_hoistedGlobal;
    c1_h_b = c1_f_hoistedGlobal_data[c1_f_hoistedGlobal_sizes[0] * ((int32_T)
      c1_j - 1)];
    c1_m_y = c1_g_a * c1_h_b;
    chartInstance->c1_sm = c1_m_y;
    _SFD_EML_CALL(0,98);
    c1_s_hoistedGlobal = chartInstance->c1_sm;
    c1_h_a = c1_s_hoistedGlobal;
    c1_n_y = c1_h_a * 0.5;
    c1_g_hoistedGlobal_sizes[0] = 1;
    c1_g_hoistedGlobal_sizes[1] = 8;
    c1_t_hoistedGlobal = c1_g_hoistedGlobal_sizes[0];
    c1_u_hoistedGlobal = c1_g_hoistedGlobal_sizes[1];
    c1_o_loop_ub = chartInstance->c1_ipj_sizes[0] * chartInstance->c1_ipj_sizes
      [1] - 1;
    for (c1_i89 = 0; c1_i89 <= c1_o_loop_ub; c1_i89 = c1_i89 + 1) {
      c1_g_hoistedGlobal_data[c1_i89] = chartInstance->c1_ipj_data[c1_i89];
    }

    c1_h_hoistedGlobal_sizes[0] = 1;
    c1_h_hoistedGlobal_sizes[1] = 8;
    c1_v_hoistedGlobal = c1_h_hoistedGlobal_sizes[0];
    c1_w_hoistedGlobal = c1_h_hoistedGlobal_sizes[1];
    c1_p_loop_ub = chartInstance->c1_ipj_sizes[0] * chartInstance->c1_ipj_sizes
      [1] - 1;
    for (c1_i90 = 0; c1_i90 <= c1_p_loop_ub; c1_i90 = c1_i90 + 1) {
      c1_h_hoistedGlobal_data[c1_i90] = chartInstance->c1_ipj_data[c1_i90];
    }

    c1_i_a = c1_g_hoistedGlobal_data[(int32_T)c1_j - 1];
    c1_i_b = c1_h_hoistedGlobal_data[(int32_T)c1_j - 1];
    c1_o_y = c1_i_a * c1_i_b;
    c1_j_a = c1_n_y;
    c1_j_b = 1.0 - c1_o_y;
    chartInstance->c1_sm = c1_j_a * c1_j_b;
    _SFD_EML_CALL(0,99);
    chartInstance->c1_dj_data[(int32_T)c1_j - 1] = chartInstance->c1_sm;

    /* back propogation, dj means delta J */
    c1_g_j = c1_g_j + 1.0;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 5, 0);
  c1_j = 1.0;
  c1_h_j = 1.0;
  while (c1_h_j <= 7.0) {
    c1_j = c1_h_j;
    CV_EML_FOR(0, 6, 1);
    c1_i = 1.0;
    c1_c_i = 1.0;
    while (c1_c_i <= 3.0) {
      c1_i = c1_c_i;
      CV_EML_FOR(0, 7, 1);
      _SFD_EML_CALL(0,103);
      c1_i_hoistedGlobal_sizes[0] = 7;
      c1_i_hoistedGlobal_sizes[1] = 7;
      c1_x_hoistedGlobal = c1_i_hoistedGlobal_sizes[0];
      c1_y_hoistedGlobal = c1_i_hoistedGlobal_sizes[1];
      c1_q_loop_ub = chartInstance->c1_dj_sizes[0] * chartInstance->c1_dj_sizes
        [1] - 1;
      for (c1_i91 = 0; c1_i91 <= c1_q_loop_ub; c1_i91 = c1_i91 + 1) {
        c1_i_hoistedGlobal_data[c1_i91] = chartInstance->c1_dj_data[c1_i91];
      }

      c1_k_a = c1_u[8];
      c1_k_b = c1_i_hoistedGlobal_data[(int32_T)c1_j - 1];
      c1_p_y = c1_k_a * c1_k_b;
      c1_l_a = c1_p_y;
      c1_l_b = c1_u[(int32_T)c1_i - 1];
      c1_q_y = c1_l_a * c1_l_b;
      chartInstance->c1_dw1_data[((int32_T)c1_j - 1) +
        chartInstance->c1_dw1_sizes[0] * ((int32_T)c1_i - 1)] = c1_q_y;

      /* dw1 is weight update quantity for W1 */
      c1_c_i = c1_c_i + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 7, 0);
    c1_h_j = c1_h_j + 1.0;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 6, 0);
  c1_j = 1.0;
  c1_i_j = 1.0;
  while (c1_i_j <= 7.0) {
    c1_j = c1_i_j;
    CV_EML_FOR(0, 8, 1);
    _SFD_EML_CALL(0,107);
    chartInstance->c1_w2_data[chartInstance->c1_w2_sizes[0] * ((int32_T)c1_j - 1)]
      = chartInstance->c1_w2_data[chartInstance->
      c1_w2_sizes[0] * ((int32_T)c1_j - 1)] + chartInstance->
      c1_dw2_data[chartInstance->c1_dw2_sizes[0] * ((int32_T)c1_j - 1)];

    /* weight update */
    c1_i = 1.0;
    c1_d_i = 1.0;
    while (c1_d_i <= 3.0) {
      c1_i = c1_d_i;
      CV_EML_FOR(0, 9, 1);
      _SFD_EML_CALL(0,109);
      chartInstance->c1_w1_data[((int32_T)c1_j - 1) + chartInstance->
        c1_w1_sizes[0] * ((int32_T)c1_i - 1)] = chartInstance->c1_w1_data[((
        int32_T)c1_j - 1) + chartInstance->c1_w1_sizes[0] * ((int32_T)c1_i - 1)]
        + chartInstance->c1_dw1_data[((int32_T)c1_j - 1) +
        chartInstance->c1_dw1_sizes[0] * ((int32_T)c1_i - 1)];

      /* weight update */
      c1_d_i = c1_d_i + 1.0;
      sf_mex_listen_for_ctrl_c(chartInstance->S);
    }

    CV_EML_FOR(0, 9, 0);
    c1_i_j = c1_i_j + 1.0;
    sf_mex_listen_for_ctrl_c(chartInstance->S);
  }

  CV_EML_FOR(0, 8, 0);

  /*   */
  /*  %%%%%%%%%%%%%%%%%%%%%%%%% */
  /*   */
  /*  nv=0; */
  /*  for j=1:u(7) */
  /*  for i=1:3 */
  /*  nv=nv+1; */
  /*  x(nv)=w1(j,i); %assign w1(1)-w1(15) to x(1)-x(15) */
  /*  end */
  /*  k=1; */
  /*  for j=1:u(7) */
  /*  nv=nv+1; */
  /*  x(nv)=w2(k,j); %assign w2(1)-w2(5) to x(16)-x(20) */
  /*  end */
  /*  x(u(8)+1)=opk(1); %assign output of neural network to x(21) */
  /*  sys=x; %Assign state variable x to sys */
  _SFD_EML_CALL(0,131);
  c1_sys = chartInstance->c1_opk;
  _SFD_EML_CALL(0,132);
  c1_waga1 = chartInstance->c1_w1_data[0];
  _SFD_EML_CALL(0,-132);
  sf_debug_symbol_scope_pop();
  *c1_b_sys = c1_sys;
  *c1_b_waga1 = c1_waga1;
  _SFD_CC_CALL(EXIT_OUT_OF_FUNCTION_TAG,0);
}

static void init_script_number_translation(uint32_T c1_machineNumber, uint32_T
  c1_chartNumber)
{
}

static void c1_eml_scalar_eg(SFc1_PII_speedInstanceStruct *chartInstance)
{
}

static real_T c1_ceval_xdot(SFc1_PII_speedInstanceStruct *chartInstance, int32_T
  c1_n, real_T c1_x[3], int32_T c1_ix0, int32_T
  c1_incx, real_T c1_y[3], int32_T c1_iy0, int32_T c1_incy)
{
  return ddot32(&c1_n, &c1_x[0], &c1_incx, &c1_y[0], &c1_incy);
}

static void c1_b_eml_scalar_eg(SFc1_PII_speedInstanceStruct *chartInstance)
{
}

static real_T c1_b_ceval_xdot(SFc1_PII_speedInstanceStruct *chartInstance,
  int32_T c1_n, real_T c1_x_data[8], int32_T c1_x_sizes[2]
  , int32_T c1_ix0, int32_T c1_incx, real_T c1_y_data[8], int32_T c1_y_sizes[1],
  int32_T c1_iy0, int32_T c1_incy)
{
  return ddot32(&c1_n, &c1_x_data[0], &c1_incx, &c1_y_data[0], &c1_incy);
}

static const mxArray *c1_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_opk_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_b_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_sm_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_c_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_kv_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_d_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_dk_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_e_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i92;
  real_T c1_b_u_data[8];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 1;
  c1_b_u_sizes[1] = 8;
  for (c1_i92 = 0; c1_i92 < 8; c1_i92 = c1_i92 + 1) {
    c1_b_u_data[c1_b_u_sizes[0] * c1_i92] = c1_u_data[c1_u_sizes[0] * c1_i92];
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_ipj_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_f_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[49], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i93;
  int32_T c1_i94;
  real_T c1_b_u_data[49];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 7;
  c1_b_u_sizes[1] = 7;
  for (c1_i93 = 0; c1_i93 < 7; c1_i93 = c1_i93 + 1) {
    for (c1_i94 = 0; c1_i94 < 7; c1_i94 = c1_i94 + 1) {
      c1_b_u_data[c1_i94 + c1_b_u_sizes[0] * c1_i93] = c1_u_data[c1_i94 +
        c1_u_sizes[0] * c1_i93];
    }
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_dj_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_g_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[49], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i95;
  int32_T c1_i96;
  real_T c1_b_u_data[49];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 7;
  c1_b_u_sizes[1] = 7;
  for (c1_i95 = 0; c1_i95 < 7; c1_i95 = c1_i95 + 1) {
    for (c1_i96 = 0; c1_i96 < 7; c1_i96 = c1_i96 + 1) {
      c1_b_u_data[c1_i96 + c1_b_u_sizes[0] * c1_i95] = c1_u_data[c1_i96 +
        c1_u_sizes[0] * c1_i95];
    }
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_jv_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_h_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i97;
  real_T c1_b_u_data[8];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 1;
  c1_b_u_sizes[1] = 8;
  for (c1_i97 = 0; c1_i97 < 8; c1_i97 = c1_i97 + 1) {
    c1_b_u_data[c1_b_u_sizes[0] * c1_i97] = c1_u_data[c1_u_sizes[0] * c1_i97];
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_dw2_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_i_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[21], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i98;
  int32_T c1_i99;
  real_T c1_b_u_data[21];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 7;
  c1_b_u_sizes[1] = 3;
  for (c1_i98 = 0; c1_i98 < 3; c1_i98 = c1_i98 + 1) {
    for (c1_i99 = 0; c1_i99 < 7; c1_i99 = c1_i99 + 1) {
      c1_b_u_data[c1_i99 + c1_b_u_sizes[0] * c1_i98] = c1_u_data[c1_i99 +
        c1_u_sizes[0] * c1_i98];
    }
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_dw1_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_j_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[8], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i100;
  real_T c1_b_u_data[8];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 1;
  c1_b_u_sizes[1] = 8;
  for (c1_i100 = 0; c1_i100 < 8; c1_i100 = c1_i100 + 1) {
    c1_b_u_data[c1_b_u_sizes[0] * c1_i100] = c1_u_data[c1_u_sizes[0] * c1_i100];
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_w2_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_k_sf_marshall(void *chartInstanceVoid, real_T
  c1_u_data[21], int32_T c1_u_sizes[2])
{
  const mxArray *c1_y = NULL;
  int32_T c1_b_u_sizes[2];
  int32_T c1_i101;
  int32_T c1_i102;
  real_T c1_b_u_data[21];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u_sizes[0] = 7;
  c1_b_u_sizes[1] = 3;
  for (c1_i101 = 0; c1_i101 < 3; c1_i101 = c1_i101 + 1) {
    for (c1_i102 = 0; c1_i102 < 7; c1_i102 = c1_i102 + 1) {
      c1_b_u_data[c1_i102 + c1_b_u_sizes[0] * c1_i101] = c1_u_data[c1_i102 +
        c1_u_sizes[0] * c1_i101];
    }
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_w1_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u_data, 0, 0U, 1U, 0U, 2,
      c1_b_u_sizes[0], c1_b_u_sizes[1]));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_l_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  int32_T c1_i103;
  real_T c1_b_u[30];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  for (c1_i103 = 0; c1_i103 < 30; c1_i103 = c1_i103 + 1) {
    c1_b_u[c1_i103] = (*((real_T (*)[30])c1_u))[c1_i103];
  }

  c1_b_y = NULL;
  if (!chartInstance->c1_init_state_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 1U, 0U, 1, 30));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_m_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_number_of_weights_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_n_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_init_nn_output_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_o_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  if (!chartInstance->c1_nhn_not_empty) {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", NULL, 0, 0U, 1U, 0U, 2, 0, 0));
  } else {
    sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  }

  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_p_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  real_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((real_T *)c1_u);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static const mxArray *c1_q_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  int32_T c1_i104;
  real_T c1_b_u[9];
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  for (c1_i104 = 0; c1_i104 < 9; c1_i104 = c1_i104 + 1) {
    c1_b_u[c1_i104] = (*((real_T (*)[9])c1_u))[c1_i104];
  }

  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 0, 0U, 1U, 0U, 1, 9));
  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

const mxArray *sf_c1_PII_speed_get_eml_resolved_functions_info(void)
{
  const mxArray *c1_nameCaptureInfo = NULL;
  c1_ResolvedFunctionInfo c1_info[44];
  const mxArray *c1_m0 = NULL;
  int32_T c1_i105;
  c1_ResolvedFunctionInfo *c1_r0;
  c1_nameCaptureInfo = NULL;
  c1_info_helper(c1_info);
  sf_mex_assign(&c1_m0, sf_mex_createstruct("nameCaptureInfo", 1, 44));
  for (c1_i105 = 0; c1_i105 < 44; c1_i105 = c1_i105 + 1) {
    c1_r0 = &c1_info[c1_i105];
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->context, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->context)), "context",
                    "nameCaptureInfo", c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->name, 15, 0U,
      0U, 0U, 2, 1, strlen(c1_r0->name)), "name",
                    "nameCaptureInfo", c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->dominantType,
      15, 0U, 0U, 0U, 2, 1, strlen(c1_r0->dominantType)),
                    "dominantType", "nameCaptureInfo", c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", c1_r0->resolved, 15,
      0U, 0U, 0U, 2, 1, strlen(c1_r0->resolved)), "resolved"
                    , "nameCaptureInfo", c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileLength,
      7, 0U, 0U, 0U, 0), "fileLength", "nameCaptureInfo",
                    c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTime1, 7,
      0U, 0U, 0U, 0), "fileTime1", "nameCaptureInfo",
                    c1_i105);
    sf_mex_addfield(c1_m0, sf_mex_create("nameCaptureInfo", &c1_r0->fileTime2, 7,
      0U, 0U, 0U, 0), "fileTime2", "nameCaptureInfo",
                    c1_i105);
  }

  sf_mex_assign(&c1_nameCaptureInfo, c1_m0);
  return c1_nameCaptureInfo;
}

static void c1_info_helper(c1_ResolvedFunctionInfo c1_info[44])
{
  c1_info[0].context = "";
  c1_info[0].name = "mtimes";
  c1_info[0].dominantType = "double";
  c1_info[0].resolved = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[0].fileLength = 3425U;
  c1_info[0].fileTime1 = 1250672766U;
  c1_info[0].fileTime2 = 0U;
  c1_info[1].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[1].name = "nargin";
  c1_info[1].dominantType = "";
  c1_info[1].resolved = "[B]nargin";
  c1_info[1].fileLength = 0U;
  c1_info[1].fileTime1 = 0U;
  c1_info[1].fileTime2 = 0U;
  c1_info[2].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[2].name = "gt";
  c1_info[2].dominantType = "double";
  c1_info[2].resolved = "[B]gt";
  c1_info[2].fileLength = 0U;
  c1_info[2].fileTime1 = 0U;
  c1_info[2].fileTime2 = 0U;
  c1_info[3].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[3].name = "isa";
  c1_info[3].dominantType = "double";
  c1_info[3].resolved = "[B]isa";
  c1_info[3].fileLength = 0U;
  c1_info[3].fileTime1 = 0U;
  c1_info[3].fileTime2 = 0U;
  c1_info[4].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[4].name = "isinteger";
  c1_info[4].dominantType = "double";
  c1_info[4].resolved = "[B]isinteger";
  c1_info[4].fileLength = 0U;
  c1_info[4].fileTime1 = 0U;
  c1_info[4].fileTime2 = 0U;
  c1_info[5].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[5].name = "isscalar";
  c1_info[5].dominantType = "double";
  c1_info[5].resolved = "[B]isscalar";
  c1_info[5].fileLength = 0U;
  c1_info[5].fileTime1 = 0U;
  c1_info[5].fileTime2 = 0U;
  c1_info[6].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[6].name = "strcmp";
  c1_info[6].dominantType = "char";
  c1_info[6].resolved = "[B]strcmp";
  c1_info[6].fileLength = 0U;
  c1_info[6].fileTime1 = 0U;
  c1_info[6].fileTime2 = 0U;
  c1_info[7].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[7].name = "size";
  c1_info[7].dominantType = "double";
  c1_info[7].resolved = "[B]size";
  c1_info[7].fileLength = 0U;
  c1_info[7].fileTime1 = 0U;
  c1_info[7].fileTime2 = 0U;
  c1_info[8].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[8].name = "eq";
  c1_info[8].dominantType = "double";
  c1_info[8].resolved = "[B]eq";
  c1_info[8].fileLength = 0U;
  c1_info[8].fileTime1 = 0U;
  c1_info[8].fileTime2 = 0U;
  c1_info[9].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[9].name = "class";
  c1_info[9].dominantType = "double";
  c1_info[9].resolved = "[B]class";
  c1_info[9].fileLength = 0U;
  c1_info[9].fileTime1 = 0U;
  c1_info[9].fileTime2 = 0U;
  c1_info[10].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[10].name = "not";
  c1_info[10].dominantType = "logical";
  c1_info[10].resolved = "[B]not";
  c1_info[10].fileLength = 0U;
  c1_info[10].fileTime1 = 0U;
  c1_info[10].fileTime2 = 0U;
  c1_info[11].context = "";
  c1_info[11].name = "plus";
  c1_info[11].dominantType = "double";
  c1_info[11].resolved = "[B]plus";
  c1_info[11].fileLength = 0U;
  c1_info[11].fileTime1 = 0U;
  c1_info[11].fileTime2 = 0U;
  c1_info[12].context = "";
  c1_info[12].name = "uminus";
  c1_info[12].dominantType = "double";
  c1_info[12].resolved = "[B]uminus";
  c1_info[12].fileLength = 0U;
  c1_info[12].fileTime1 = 0U;
  c1_info[12].fileTime2 = 0U;
  c1_info[13].context = "";
  c1_info[13].name = "zeros";
  c1_info[13].dominantType = "double";
  c1_info[13].resolved = "[B]zeros";
  c1_info[13].fileLength = 0U;
  c1_info[13].fileTime1 = 0U;
  c1_info[13].fileTime2 = 0U;
  c1_info[14].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[14].name = "ndims";
  c1_info[14].dominantType = "double";
  c1_info[14].resolved = "[B]ndims";
  c1_info[14].fileLength = 0U;
  c1_info[14].fileTime1 = 0U;
  c1_info[14].fileTime2 = 0U;
  c1_info[15].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[15].name = "le";
  c1_info[15].dominantType = "double";
  c1_info[15].resolved = "[B]le";
  c1_info[15].fileLength = 0U;
  c1_info[15].fileTime1 = 0U;
  c1_info[15].fileTime2 = 0U;
  c1_info[16].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[16].name = "isreal";
  c1_info[16].dominantType = "double";
  c1_info[16].resolved = "[B]isreal";
  c1_info[16].fileLength = 0U;
  c1_info[16].fileTime1 = 0U;
  c1_info[16].fileTime2 = 0U;
  c1_info[17].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[17].name = "ne";
  c1_info[17].dominantType = "logical";
  c1_info[17].resolved = "[B]ne";
  c1_info[17].fileLength = 0U;
  c1_info[17].fileTime1 = 0U;
  c1_info[17].fileTime2 = 0U;
  c1_info[18].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[18].name = "eml_index_class";
  c1_info[18].dominantType = "";
  c1_info[18].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_class.m";
  c1_info[18].fileLength = 909U;
  c1_info[18].fileTime1 = 1192466782U;
  c1_info[18].fileTime2 = 0U;
  c1_info[19].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[19].name = "ones";
  c1_info[19].dominantType = "char";
  c1_info[19].resolved = "[B]ones";
  c1_info[19].fileLength = 0U;
  c1_info[19].fileTime1 = 0U;
  c1_info[19].fileTime2 = 0U;
  c1_info[20].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[20].name = "cast";
  c1_info[20].dominantType = "double";
  c1_info[20].resolved = "[B]cast";
  c1_info[20].fileLength = 0U;
  c1_info[20].fileTime1 = 0U;
  c1_info[20].fileTime2 = 0U;
  c1_info[21].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[21].name = "eml_scalar_eg";
  c1_info[21].dominantType = "double";
  c1_info[21].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[21].fileLength = 3068U;
  c1_info[21].fileTime1 = 1240262010U;
  c1_info[21].fileTime2 = 0U;
  c1_info[22].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m/any_enums";
  c1_info[22].name = "false";
  c1_info[22].dominantType = "";
  c1_info[22].resolved = "[B]false";
  c1_info[22].fileLength = 0U;
  c1_info[22].fileTime1 = 0U;
  c1_info[22].fileTime2 = 0U;
  c1_info[23].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_scalar_eg.m";
  c1_info[23].name = "isstruct";
  c1_info[23].dominantType = "double";
  c1_info[23].resolved = "[B]isstruct";
  c1_info[23].fileLength = 0U;
  c1_info[23].fileTime1 = 0U;
  c1_info[23].fileTime2 = 0U;
  c1_info[24].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[24].name = "isempty";
  c1_info[24].dominantType = "double";
  c1_info[24].resolved = "[B]isempty";
  c1_info[24].fileLength = 0U;
  c1_info[24].fileTime1 = 0U;
  c1_info[24].fileTime2 = 0U;
  c1_info[25].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/ops/mtimes.m";
  c1_info[25].name = "eml_xdotu";
  c1_info[25].dominantType = "int32";
  c1_info[25].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c1_info[25].fileLength = 1453U;
  c1_info[25].fileTime1 = 1209330850U;
  c1_info[25].fileTime2 = 0U;
  c1_info[26].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdotu.m";
  c1_info[26].name = "eml_xdot";
  c1_info[26].dominantType = "int32";
  c1_info[26].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/eml_xdot.m";
  c1_info[26].fileLength = 1330U;
  c1_info[26].fileTime1 = 1209330848U;
  c1_info[26].fileTime2 = 0U;
  c1_info[27].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/external/eml_blas_xdot.m";
  c1_info[27].name = "eml_refblas_xdot";
  c1_info[27].dominantType = "int32";
  c1_info[27].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[27].fileLength = 343U;
  c1_info[27].fileTime1 = 1211216042U;
  c1_info[27].fileTime2 = 0U;
  c1_info[28].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdot.m";
  c1_info[28].name = "eml_refblas_xdotx";
  c1_info[28].dominantType = "int32";
  c1_info[28].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[28].fileLength = 1605U;
  c1_info[28].fileTime1 = 1236257278U;
  c1_info[28].fileTime2 = 0U;
  c1_info[29].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[29].name = "ischar";
  c1_info[29].dominantType = "char";
  c1_info[29].resolved = "[B]ischar";
  c1_info[29].fileLength = 0U;
  c1_info[29].fileTime1 = 0U;
  c1_info[29].fileTime2 = 0U;
  c1_info[30].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[30].name = "isequal";
  c1_info[30].dominantType = "char";
  c1_info[30].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[30].fileLength = 180U;
  c1_info[30].fileTime1 = 1226577270U;
  c1_info[30].fileTime2 = 0U;
  c1_info[31].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/elmat/isequal.m";
  c1_info[31].name = "eml_isequal_core";
  c1_info[31].dominantType = "char";
  c1_info[31].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[31].fileLength = 4192U;
  c1_info[31].fileTime1 = 1257783382U;
  c1_info[31].fileTime2 = 0U;
  c1_info[32].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[32].name = "ge";
  c1_info[32].dominantType = "double";
  c1_info[32].resolved = "[B]ge";
  c1_info[32].fileLength = 0U;
  c1_info[32].fileTime1 = 0U;
  c1_info[32].fileTime2 = 0U;
  c1_info[33].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[33].name = "islogical";
  c1_info[33].dominantType = "logical";
  c1_info[33].resolved = "[B]islogical";
  c1_info[33].fileLength = 0U;
  c1_info[33].fileTime1 = 0U;
  c1_info[33].fileTime2 = 0U;
  c1_info[34].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[34].name = "minus";
  c1_info[34].dominantType = "double";
  c1_info[34].resolved = "[B]minus";
  c1_info[34].fileLength = 0U;
  c1_info[34].fileTime1 = 0U;
  c1_info[34].fileTime2 = 0U;
  c1_info[35].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m";
  c1_info[35].name = "isnumeric";
  c1_info[35].dominantType = "char";
  c1_info[35].resolved = "[B]isnumeric";
  c1_info[35].fileLength = 0U;
  c1_info[35].fileTime1 = 0U;
  c1_info[35].fileTime2 = 0U;
  c1_info[36].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_isequal_core.m/same_size";
  c1_info[36].name = "true";
  c1_info[36].dominantType = "";
  c1_info[36].resolved = "[B]true";
  c1_info[36].fileLength = 0U;
  c1_info[36].fileTime1 = 0U;
  c1_info[36].fileTime2 = 0U;
  c1_info[37].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[37].name = "lt";
  c1_info[37].dominantType = "int32";
  c1_info[37].resolved = "[B]lt";
  c1_info[37].fileLength = 0U;
  c1_info[37].fileTime1 = 0U;
  c1_info[37].fileTime2 = 0U;
  c1_info[38].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[38].name = "times";
  c1_info[38].dominantType = "double";
  c1_info[38].resolved = "[B]times";
  c1_info[38].fileLength = 0U;
  c1_info[38].fileTime1 = 0U;
  c1_info[38].fileTime2 = 0U;
  c1_info[39].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[39].name = "eml_index_minus";
  c1_info[39].dominantType = "int32";
  c1_info[39].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_minus.m";
  c1_info[39].fileLength = 277U;
  c1_info[39].fileTime1 = 1192466784U;
  c1_info[39].fileTime2 = 0U;
  c1_info[40].context =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/blas/refblas/eml_refblas_xdotx.m";
  c1_info[40].name = "eml_index_plus";
  c1_info[40].dominantType = "int32";
  c1_info[40].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/eml/eml_index_plus.m";
  c1_info[40].fileLength = 272U;
  c1_info[40].fileTime1 = 1192466784U;
  c1_info[40].fileTime2 = 0U;
  c1_info[41].context = "";
  c1_info[41].name = "tanh";
  c1_info[41].dominantType = "double";
  c1_info[41].resolved = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/elfun/tanh.m";
  c1_info[41].fileLength = 327U;
  c1_info[41].fileTime1 = 1203448048U;
  c1_info[41].fileTime2 = 0U;
  c1_info[42].context = "[ILX]$matlabroot$/toolbox/eml/lib/matlab/elfun/tanh.m";
  c1_info[42].name = "eml_scalar_tanh";
  c1_info[42].dominantType = "double";
  c1_info[42].resolved =
    "[ILX]$matlabroot$/toolbox/eml/lib/matlab/elfun/eml_scalar_tanh.m";
  c1_info[42].fileLength = 475U;
  c1_info[42].fileTime1 = 1203448018U;
  c1_info[42].fileTime2 = 0U;
  c1_info[43].context = "";
  c1_info[43].name = "ctranspose";
  c1_info[43].dominantType = "double";
  c1_info[43].resolved = "[B]ctranspose";
  c1_info[43].fileLength = 0U;
  c1_info[43].fileTime1 = 0U;
  c1_info[43].fileTime2 = 0U;
}

static const mxArray *c1_r_sf_marshall(void *chartInstanceVoid, void *c1_u)
{
  const mxArray *c1_y = NULL;
  boolean_T c1_b_u;
  const mxArray *c1_b_y = NULL;
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)chartInstanceVoid;
  c1_y = NULL;
  c1_b_u = *((boolean_T *)c1_u);
  c1_b_y = NULL;
  sf_mex_assign(&c1_b_y, sf_mex_create("y", &c1_b_u, 11, 0U, 0U, 0U, 0));
  sf_mex_assign(&c1_y, c1_b_y);
  return c1_y;
}

static real_T c1_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_sys, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d0;
  sf_mex_import(c1_name, sf_mex_dup(c1_sys), &c1_d0, 1, 0, 0U, 0, 0U, 0);
  c1_y = c1_d0;
  sf_mex_destroy(&c1_sys);
  return c1_y;
}

static void c1_b_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dj, const char_T *c1_name, real_T
  c1_y_data[49], int32_T c1_y_sizes[2])
{
  int32_T c1_i106;
  uint32_T c1_uv0[2];
  int32_T c1_i107;
  boolean_T c1_bv0[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[49];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i108;
  for (c1_i106 = 0; c1_i106 < 2; c1_i106 = c1_i106 + 1) {
    c1_uv0[c1_i106] = 7U;
  }

  if (mxIsEmpty(c1_dj)) {
    chartInstance->c1_dj_not_empty = FALSE;
  } else {
    chartInstance->c1_dj_not_empty = TRUE;
    for (c1_i107 = 0; c1_i107 < 2; c1_i107 = c1_i107 + 1) {
      c1_bv0[c1_i107] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_dj), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv0, &c1_uv0, &c1_tmp_sizes);
    c1_y_sizes[0] = 7;
    c1_y_sizes[1] = 7;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i108 = 0; c1_i108 <= c1_loop_ub; c1_i108 = c1_i108 + 1) {
      c1_y_data[c1_i108] = c1_tmp_data[c1_i108];
    }
  }

  sf_mex_destroy(&c1_dj);
}

static real_T c1_c_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_dk, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d1;
  if (mxIsEmpty(c1_b_dk)) {
    chartInstance->c1_dk_not_empty = FALSE;
  } else {
    chartInstance->c1_dk_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_dk), &c1_d1, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d1;
  }

  sf_mex_destroy(&c1_b_dk);
  return c1_y;
}

static void c1_d_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dw1, const char_T *c1_name, real_T
  c1_y_data[21], int32_T c1_y_sizes[2])
{
  int32_T c1_i109;
  static uint32_T c1_uv1[2] = { 7U, 3U };

  uint32_T c1_uv2[2];
  int32_T c1_i110;
  boolean_T c1_bv1[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[21];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i111;
  for (c1_i109 = 0; c1_i109 < 2; c1_i109 = c1_i109 + 1) {
    c1_uv2[c1_i109] = c1_uv1[c1_i109];
  }

  if (mxIsEmpty(c1_dw1)) {
    chartInstance->c1_dw1_not_empty = FALSE;
  } else {
    chartInstance->c1_dw1_not_empty = TRUE;
    for (c1_i110 = 0; c1_i110 < 2; c1_i110 = c1_i110 + 1) {
      c1_bv1[c1_i110] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_dw1), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv1, &c1_uv2, &c1_tmp_sizes);
    c1_y_sizes[0] = 7;
    c1_y_sizes[1] = 3;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i111 = 0; c1_i111 <= c1_loop_ub; c1_i111 = c1_i111 + 1) {
      c1_y_data[c1_i111] = c1_tmp_data[c1_i111];
    }
  }

  sf_mex_destroy(&c1_dw1);
}

static void c1_e_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_dw2, const char_T *c1_name, real_T
  c1_y_data[8], int32_T c1_y_sizes[2])
{
  int32_T c1_i112;
  uint32_T c1_uv3[2];
  int32_T c1_i113;
  boolean_T c1_bv2[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[8];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i114;
  for (c1_i112 = 0; c1_i112 < 2; c1_i112 = c1_i112 + 1) {
    c1_uv3[c1_i112] = 1U + 7U * (uint32_T)c1_i112;
  }

  if (mxIsEmpty(c1_dw2)) {
    chartInstance->c1_dw2_not_empty = FALSE;
  } else {
    chartInstance->c1_dw2_not_empty = TRUE;
    for (c1_i113 = 0; c1_i113 < 2; c1_i113 = c1_i113 + 1) {
      c1_bv2[c1_i113] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_dw2), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv2, &c1_uv3, &c1_tmp_sizes);
    c1_y_sizes[0] = 1;
    c1_y_sizes[1] = 8;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i114 = 0; c1_i114 <= c1_loop_ub; c1_i114 = c1_i114 + 1) {
      c1_y_data[c1_i114] = c1_tmp_data[c1_i114];
    }
  }

  sf_mex_destroy(&c1_dw2);
}

static real_T c1_f_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_init_nn_output, const char_T *
  c1_name)
{
  real_T c1_y;
  real_T c1_d2;
  if (mxIsEmpty(c1_b_init_nn_output)) {
    chartInstance->c1_init_nn_output_not_empty = FALSE;
  } else {
    chartInstance->c1_init_nn_output_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_init_nn_output), &c1_d2, 1, 0, 0U, 0,
                  0U, 0);
    c1_y = c1_d2;
  }

  sf_mex_destroy(&c1_b_init_nn_output);
  return c1_y;
}

static void c1_g_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_init_state, const char_T *c1_name
  , real_T c1_y[30])
{
  real_T c1_dv2[30];
  int32_T c1_i115;
  if (mxIsEmpty(c1_b_init_state)) {
    chartInstance->c1_init_state_not_empty = FALSE;
  } else {
    chartInstance->c1_init_state_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_init_state), &c1_dv2, 1, 0, 0U, 1, 0U,
                  1, 30);
    for (c1_i115 = 0; c1_i115 < 30; c1_i115 = c1_i115 + 1) {
      c1_y[c1_i115] = c1_dv2[c1_i115];
    }
  }

  sf_mex_destroy(&c1_b_init_state);
}

static void c1_h_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_ipj, const char_T *c1_name, real_T
  c1_y_data[8], int32_T c1_y_sizes[2])
{
  int32_T c1_i116;
  uint32_T c1_uv4[2];
  int32_T c1_i117;
  boolean_T c1_bv3[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[8];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i118;
  for (c1_i116 = 0; c1_i116 < 2; c1_i116 = c1_i116 + 1) {
    c1_uv4[c1_i116] = 1U + 7U * (uint32_T)c1_i116;
  }

  if (mxIsEmpty(c1_ipj)) {
    chartInstance->c1_ipj_not_empty = FALSE;
  } else {
    chartInstance->c1_ipj_not_empty = TRUE;
    for (c1_i117 = 0; c1_i117 < 2; c1_i117 = c1_i117 + 1) {
      c1_bv3[c1_i117] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_ipj), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv3, &c1_uv4, &c1_tmp_sizes);
    c1_y_sizes[0] = 1;
    c1_y_sizes[1] = 8;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i118 = 0; c1_i118 <= c1_loop_ub; c1_i118 = c1_i118 + 1) {
      c1_y_data[c1_i118] = c1_tmp_data[c1_i118];
    }
  }

  sf_mex_destroy(&c1_ipj);
}

static void c1_i_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_jv, const char_T *c1_name, real_T
  c1_y_data[49], int32_T c1_y_sizes[2])
{
  int32_T c1_i119;
  uint32_T c1_uv5[2];
  int32_T c1_i120;
  boolean_T c1_bv4[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[49];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i121;
  for (c1_i119 = 0; c1_i119 < 2; c1_i119 = c1_i119 + 1) {
    c1_uv5[c1_i119] = 7U;
  }

  if (mxIsEmpty(c1_jv)) {
    chartInstance->c1_jv_not_empty = FALSE;
  } else {
    chartInstance->c1_jv_not_empty = TRUE;
    for (c1_i120 = 0; c1_i120 < 2; c1_i120 = c1_i120 + 1) {
      c1_bv4[c1_i120] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_jv), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv4, &c1_uv5, &c1_tmp_sizes);
    c1_y_sizes[0] = 7;
    c1_y_sizes[1] = 7;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i121 = 0; c1_i121 <= c1_loop_ub; c1_i121 = c1_i121 + 1) {
      c1_y_data[c1_i121] = c1_tmp_data[c1_i121];
    }
  }

  sf_mex_destroy(&c1_jv);
}

static real_T c1_j_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_kv, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d3;
  if (mxIsEmpty(c1_b_kv)) {
    chartInstance->c1_kv_not_empty = FALSE;
  } else {
    chartInstance->c1_kv_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_kv), &c1_d3, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d3;
  }

  sf_mex_destroy(&c1_b_kv);
  return c1_y;
}

static real_T c1_k_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_nhn, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d4;
  if (mxIsEmpty(c1_b_nhn)) {
    chartInstance->c1_nhn_not_empty = FALSE;
  } else {
    chartInstance->c1_nhn_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_nhn), &c1_d4, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d4;
  }

  sf_mex_destroy(&c1_b_nhn);
  return c1_y;
}

static real_T c1_l_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_number_of_weights, const char_T
  *c1_name)
{
  real_T c1_y;
  real_T c1_d5;
  if (mxIsEmpty(c1_b_number_of_weights)) {
    chartInstance->c1_number_of_weights_not_empty = FALSE;
  } else {
    chartInstance->c1_number_of_weights_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_number_of_weights), &c1_d5, 1, 0, 0U,
                  0, 0U, 0);
    c1_y = c1_d5;
  }

  sf_mex_destroy(&c1_b_number_of_weights);
  return c1_y;
}

static real_T c1_m_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_opk, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d6;
  if (mxIsEmpty(c1_b_opk)) {
    chartInstance->c1_opk_not_empty = FALSE;
  } else {
    chartInstance->c1_opk_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_opk), &c1_d6, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d6;
  }

  sf_mex_destroy(&c1_b_opk);
  return c1_y;
}

static real_T c1_n_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_sm, const char_T *c1_name)
{
  real_T c1_y;
  real_T c1_d7;
  if (mxIsEmpty(c1_b_sm)) {
    chartInstance->c1_sm_not_empty = FALSE;
  } else {
    chartInstance->c1_sm_not_empty = TRUE;
    sf_mex_import(c1_name, sf_mex_dup(c1_b_sm), &c1_d7, 1, 0, 0U, 0, 0U, 0);
    c1_y = c1_d7;
  }

  sf_mex_destroy(&c1_b_sm);
  return c1_y;
}

static void c1_o_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_w1, const char_T *c1_name, real_T
  c1_y_data[21], int32_T c1_y_sizes[2])
{
  int32_T c1_i122;
  static uint32_T c1_uv6[2] = { 7U, 3U };

  uint32_T c1_uv7[2];
  int32_T c1_i123;
  boolean_T c1_bv5[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[21];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i124;
  for (c1_i122 = 0; c1_i122 < 2; c1_i122 = c1_i122 + 1) {
    c1_uv7[c1_i122] = c1_uv6[c1_i122];
  }

  if (mxIsEmpty(c1_w1)) {
    chartInstance->c1_w1_not_empty = FALSE;
  } else {
    chartInstance->c1_w1_not_empty = TRUE;
    for (c1_i123 = 0; c1_i123 < 2; c1_i123 = c1_i123 + 1) {
      c1_bv5[c1_i123] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_w1), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv5, &c1_uv7, &c1_tmp_sizes);
    c1_y_sizes[0] = 7;
    c1_y_sizes[1] = 3;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i124 = 0; c1_i124 <= c1_loop_ub; c1_i124 = c1_i124 + 1) {
      c1_y_data[c1_i124] = c1_tmp_data[c1_i124];
    }
  }

  sf_mex_destroy(&c1_w1);
}

static void c1_p_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_w2, const char_T *c1_name, real_T
  c1_y_data[8], int32_T c1_y_sizes[2])
{
  int32_T c1_i125;
  uint32_T c1_uv8[2];
  int32_T c1_i126;
  boolean_T c1_bv6[2];
  int32_T c1_tmp_sizes[2];
  real_T c1_tmp_data[8];
  int32_T c1_y;
  int32_T c1_b_y;
  int32_T c1_loop_ub;
  int32_T c1_i127;
  for (c1_i125 = 0; c1_i125 < 2; c1_i125 = c1_i125 + 1) {
    c1_uv8[c1_i125] = 1U + 7U * (uint32_T)c1_i125;
  }

  if (mxIsEmpty(c1_w2)) {
    chartInstance->c1_w2_not_empty = FALSE;
  } else {
    chartInstance->c1_w2_not_empty = TRUE;
    for (c1_i126 = 0; c1_i126 < 2; c1_i126 = c1_i126 + 1) {
      c1_bv6[c1_i126] = FALSE;
    }

    sf_mex_import_vs(c1_name, sf_mex_dup(c1_w2), &c1_tmp_data, 1, 0, 0U, 1, 0U,
                     2, c1_bv6, &c1_uv8, &c1_tmp_sizes);
    c1_y_sizes[0] = 1;
    c1_y_sizes[1] = 8;
    c1_y = c1_y_sizes[0];
    c1_b_y = c1_y_sizes[1];
    c1_loop_ub = c1_tmp_sizes[0] * c1_tmp_sizes[1] - 1;
    for (c1_i127 = 0; c1_i127 <= c1_loop_ub; c1_i127 = c1_i127 + 1) {
      c1_y_data[c1_i127] = c1_tmp_data[c1_i127];
    }
  }

  sf_mex_destroy(&c1_w2);
}

static uint8_T c1_q_emlrt_marshallIn(SFc1_PII_speedInstanceStruct *chartInstance,
  const mxArray *c1_b_is_active_c1_PII_speed, const
  char_T *c1_name)
{
  uint8_T c1_y;
  uint8_T c1_u0;
  sf_mex_import(c1_name, sf_mex_dup(c1_b_is_active_c1_PII_speed), &c1_u0, 1, 3,
                0U, 0, 0U, 0);
  c1_y = c1_u0;
  sf_mex_destroy(&c1_b_is_active_c1_PII_speed);
  return c1_y;
}

static void init_dsm_address_info(SFc1_PII_speedInstanceStruct *chartInstance)
{
}

/* SFunction Glue Code */
void sf_c1_PII_speed_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2428191207U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1085292187U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3032008271U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1400070496U);
}

mxArray *sf_c1_PII_speed_get_autoinheritance_info(void)
{
  const char *autoinheritanceFields[] = { "checksum", "inputs", "parameters",
    "outputs" };

  mxArray *mxAutoinheritanceInfo = mxCreateStructMatrix(1,1,4,
    autoinheritanceFields);

  {
    mxArray *mxChecksum = mxCreateDoubleMatrix(4,1,mxREAL);
    double *pr = mxGetPr(mxChecksum);
    pr[0] = (double)(2188945444U);
    pr[1] = (double)(3251584971U);
    pr[2] = (double)(3725357888U);
    pr[3] = (double)(2595665663U);
    mxSetField(mxAutoinheritanceInfo,0,"checksum",mxChecksum);
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,1,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(9);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"inputs",mxData);
  }

  {
    mxSetField(mxAutoinheritanceInfo,0,"parameters",mxCreateDoubleMatrix(0,0,
                mxREAL));
  }

  {
    const char *dataFields[] = { "size", "type", "complexity" };

    mxArray *mxData = mxCreateStructMatrix(1,2,3,dataFields);

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,0,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,0,"type",mxType);
    }

    mxSetField(mxData,0,"complexity",mxCreateDoubleScalar(0));

    {
      mxArray *mxSize = mxCreateDoubleMatrix(1,2,mxREAL);
      double *pr = mxGetPr(mxSize);
      pr[0] = (double)(1);
      pr[1] = (double)(1);
      mxSetField(mxData,1,"size",mxSize);
    }

    {
      const char *typeFields[] = { "base", "fixpt" };

      mxArray *mxType = mxCreateStructMatrix(1,1,2,typeFields);
      mxSetField(mxType,0,"base",mxCreateDoubleScalar(10));
      mxSetField(mxType,0,"fixpt",mxCreateDoubleMatrix(0,0,mxREAL));
      mxSetField(mxData,1,"type",mxType);
    }

    mxSetField(mxData,1,"complexity",mxCreateDoubleScalar(0));
    mxSetField(mxAutoinheritanceInfo,0,"outputs",mxData);
  }

  return(mxAutoinheritanceInfo);
}

static mxArray *sf_get_sim_state_info_c1_PII_speed(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  const char *infoEncStr[] = {
    "100 S1x10'type','srcId','name','auxInfo'{{M[1],M[5],T\"sys\",},{M[1],M[12],T\"waga1\",},{M[4],M[0],T\"dj\",S'l','i','p'{{M1x2[140 142],M[0],}}},{M[4],M[0],T\"dk\",S'l','i','p'{{M1x2[134 136],M[0],}}},{M[4],M[0],T\"dw1\",S'l','i','p'{{M1x2[64 67],M[0],}}},{M[4],M[0],T\"dw2\",S'l','i','p'{{M1x2[68 71],M[0],}}},{M[4],M[0],T\"init_nn_output\",S'l','i','p'{{M1x2[76 90],M[0],}}},{M[4],M[0],T\"init_state\",S'l','i','p'{{M1x2[109 119],M[0],}}},{M[4],M[0],T\"ipj\",S'l','i','p'{{M1x2[123 126],M[0],}}},{M[4],M[0],T\"jv\",S'l','i','p'{{M1x2[120 122],M[0],}}}}",
    "100 S1x8'type','srcId','name','auxInfo'{{M[4],M[0],T\"kv\",S'l','i','p'{{M1x2[127 129],M[0],}}},{M[4],M[0],T\"nhn\",S'l','i','p'{{M1x2[72 75],M[0],}}},{M[4],M[0],T\"number_of_weights\",S'l','i','p'{{M1x2[91 108],M[0],}}},{M[4],M[0],T\"opk\",S'l','i','p'{{M1x2[130 133],M[0],}}},{M[4],M[0],T\"sm\",S'l','i','p'{{M1x2[137 139],M[0],}}},{M[4],M[0],T\"w1\",S'l','i','p'{{M1x2[58 60],M[0],}}},{M[4],M[0],T\"w2\",S'l','i','p'{{M1x2[61 63],M[0],}}},{M[8],M[0],T\"is_active_c1_PII_speed\",}}"
  };

  mxArray *mxVarInfo = sf_mex_decode_encoded_mx_struct_array(infoEncStr, 18, 10);
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c1_PII_speed_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static void chart_debug_initialization(SimStruct *S, unsigned int
  fullDebuggerInitialization)
{
  if (!sim_mode_is_rtw_gen(S)) {
    SFc1_PII_speedInstanceStruct *chartInstance;
    chartInstance = (SFc1_PII_speedInstanceStruct *) ((ChartInfoStruct *)
      (ssGetUserData(S)))->chartInstance;
    if (ssIsFirstInitCond(S) && fullDebuggerInitialization==1) {
      /* do this only if simulation is starting */
      {
        unsigned int chartAlreadyPresent;
        chartAlreadyPresent = sf_debug_initialize_chart(_PII_speedMachineNumber_,
          1,
          1,
          1,
          3,
          0,
          0,
          0,
          0,
          0,
          &(chartInstance->chartNumber),
          &(chartInstance->instanceNumber),
          ssGetPath(S),
          (void *)S);
        if (chartAlreadyPresent==0) {
          /* this is the first instance */
          init_script_number_translation(_PII_speedMachineNumber_,
            chartInstance->chartNumber);
          sf_debug_set_chart_disable_implicit_casting(_PII_speedMachineNumber_,
            chartInstance->chartNumber,1);
          sf_debug_set_chart_event_thresholds(_PII_speedMachineNumber_,
            chartInstance->chartNumber,
            0,
            0,
            0);

          {
            unsigned int dimVector[1];
            dimVector[0]= 9;
            _SFD_SET_DATA_PROPS(0,1,1,0,SF_DOUBLE,1,&(dimVector[0]),0,0,0,0.0,
                                1.0,0,"u",0,(MexFcnForType)c1_q_sf_marshall);
          }

          _SFD_SET_DATA_PROPS(1,2,0,1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,"sys",0,
                              (MexFcnForType)c1_p_sf_marshall);
          _SFD_SET_DATA_PROPS(2,2,0,1,SF_DOUBLE,0,NULL,0,0,0,0.0,1.0,0,"waga1",0,
                              (MexFcnForType)c1_p_sf_marshall);
          _SFD_STATE_INFO(0,0,2);
          _SFD_CH_SUBSTATE_COUNT(0);
          _SFD_CH_SUBSTATE_DECOMP(0);
        }

        _SFD_CV_INIT_CHART(0,0,0,0);

        {
          _SFD_CV_INIT_STATE(0,0,0,0,0,0,NULL,NULL);
        }

        _SFD_CV_INIT_TRANS(0,0,NULL,NULL,0,NULL);

        /* Initialization of EML Model Coverage */
        _SFD_CV_INIT_EML(0,1,1,0,0,10,0,0,0);
        _SFD_CV_INIT_EML_FCN(0,0,"eML_blk_kernel",0,-1,2190);
        _SFD_CV_INIT_EML_IF(0,0,726,742,-1,1078);
        _SFD_CV_INIT_EML_FOR(0,0,953,966,1016);
        _SFD_CV_INIT_EML_FOR(0,1,966,976,1012);
        _SFD_CV_INIT_EML_FOR(0,2,1022,1037,1073);
        _SFD_CV_INIT_EML_FOR(0,3,1080,1093,1225);
        _SFD_CV_INIT_EML_FOR(0,4,1311,1323,1488);
        _SFD_CV_INIT_EML_FOR(0,5,1506,1518,1620);
        _SFD_CV_INIT_EML_FOR(0,6,1621,1633,1714);
        _SFD_CV_INIT_EML_FOR(0,7,1633,1643,1710);
        _SFD_CV_INIT_EML_FOR(0,8,1715,1727,1826);
        _SFD_CV_INIT_EML_FOR(0,9,1768,1778,1822);
        _SFD_TRANS_COV_WTS(0,0,0,1,0);
        if (chartAlreadyPresent==0) {
          _SFD_TRANS_COV_MAPS(0,
                              0,NULL,NULL,
                              0,NULL,NULL,
                              1,NULL,NULL,
                              0,NULL,NULL);
        }

        {
          real_T (*c1_u)[9];
          real_T *c1_sys;
          real_T *c1_waga1;
          c1_waga1 = (real_T *)ssGetOutputPortSignal(chartInstance->S, 2);
          c1_sys = (real_T *)ssGetOutputPortSignal(chartInstance->S, 1);
          c1_u = (real_T (*)[9])ssGetInputPortSignal(chartInstance->S, 0);
          _SFD_SET_DATA_VALUE_PTR(0U, c1_u);
          _SFD_SET_DATA_VALUE_PTR(1U, c1_sys);
          _SFD_SET_DATA_VALUE_PTR(2U, c1_waga1);
        }
      }
    } else {
      sf_debug_reset_current_state_configuration(_PII_speedMachineNumber_,
        chartInstance->chartNumber,chartInstance->instanceNumber);
    }
  }
}

static void sf_opaque_initialize_c1_PII_speed(void *chartInstanceVar)
{
  chart_debug_initialization(((SFc1_PII_speedInstanceStruct*) chartInstanceVar
    )->S,0);
  initialize_params_c1_PII_speed((SFc1_PII_speedInstanceStruct*)
    chartInstanceVar);
  initialize_c1_PII_speed((SFc1_PII_speedInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c1_PII_speed(void *chartInstanceVar)
{
  enable_c1_PII_speed((SFc1_PII_speedInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c1_PII_speed(void *chartInstanceVar)
{
  disable_c1_PII_speed((SFc1_PII_speedInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c1_PII_speed(void *chartInstanceVar)
{
  sf_c1_PII_speed((SFc1_PII_speedInstanceStruct*) chartInstanceVar);
}

static mxArray* sf_internal_get_sim_state_c1_PII_speed(SimStruct* S)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_raw2high");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = (mxArray*) get_sim_state_c1_PII_speed((SFc1_PII_speedInstanceStruct*)
    chartInfo->chartInstance);         /* raw sim ctx */
  prhs[3] = sf_get_sim_state_info_c1_PII_speed();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_raw2high'.\n");
  }

  return plhs[0];
}

static void sf_internal_set_sim_state_c1_PII_speed(SimStruct* S, const mxArray
  *st)
{
  ChartInfoStruct *chartInfo = (ChartInfoStruct*) ssGetUserData(S);
  mxArray *plhs[1] = { NULL };

  mxArray *prhs[4];
  int mxError = 0;
  prhs[0] = mxCreateString("chart_simctx_high2raw");
  prhs[1] = mxCreateDoubleScalar(ssGetSFuncBlockHandle(S));
  prhs[2] = mxDuplicateArray(st);      /* high level simctx */
  prhs[3] = (mxArray*) sf_get_sim_state_info_c1_PII_speed();/* state var info */
  mxError = sf_mex_call_matlab(1, plhs, 4, prhs, "sfprivate");
  mxDestroyArray(prhs[0]);
  mxDestroyArray(prhs[1]);
  mxDestroyArray(prhs[2]);
  mxDestroyArray(prhs[3]);
  if (mxError || plhs[0] == NULL) {
    sf_mex_error_message("Stateflow Internal Error: \nError calling 'chart_simctx_high2raw'.\n");
  }

  set_sim_state_c1_PII_speed((SFc1_PII_speedInstanceStruct*)
    chartInfo->chartInstance, mxDuplicateArray(plhs[0]));
  mxDestroyArray(plhs[0]);
}

static mxArray* sf_opaque_get_sim_state_c1_PII_speed(SimStruct* S)
{
  return sf_internal_get_sim_state_c1_PII_speed(S);
}

static void sf_opaque_set_sim_state_c1_PII_speed(SimStruct* S, const mxArray *st)
{
  sf_internal_set_sim_state_c1_PII_speed(S, st);
}

static void sf_opaque_terminate_c1_PII_speed(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc1_PII_speedInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
    }

    finalize_c1_PII_speed((SFc1_PII_speedInstanceStruct*) chartInstanceVar);
    free((void *)chartInstanceVar);
    ssSetUserData(S,NULL);
  }
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c1_PII_speed(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  if (sf_machine_global_initializer_called()) {
    initialize_params_c1_PII_speed((SFc1_PII_speedInstanceStruct*)
      (((ChartInfoStruct *)ssGetUserData(S))->chartInstance));
  }
}

static void mdlSetWorkWidths_c1_PII_speed(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
    int_T chartIsInlinable =
      (int_T)sf_is_chart_inlinable("PII_speed","PII_speed",1);
    ssSetStateflowIsInlinable(S,chartIsInlinable);
    ssSetRTWCG(S,sf_rtw_info_uint_prop("PII_speed","PII_speed",1,"RTWCG"));
    ssSetEnableFcnIsTrivial(S,1);
    ssSetDisableFcnIsTrivial(S,1);
    ssSetNotMultipleInlinable(S,sf_rtw_info_uint_prop("PII_speed","PII_speed",1,
      "gatewayCannotBeInlinedMultipleTimes"));
    if (chartIsInlinable) {
      ssSetInputPortOptimOpts(S, 0, SS_REUSABLE_AND_LOCAL);
      sf_mark_chart_expressionable_inputs(S,"PII_speed","PII_speed",1,1);
      sf_mark_chart_reusable_outputs(S,"PII_speed","PII_speed",1,2);
    }

    sf_set_rtw_dwork_info(S,"PII_speed","PII_speed",1);
    ssSetHasSubFunctions(S,!(chartIsInlinable));
    ssSetOptions(S,ssGetOptions(S)|SS_OPTION_WORKS_WITH_CODE_REUSE);
  }

  ssSetChecksum0(S,(1997142126U));
  ssSetChecksum1(S,(1857245644U));
  ssSetChecksum2(S,(3425560296U));
  ssSetChecksum3(S,(261117282U));
  ssSetmdlDerivatives(S, NULL);
  ssSetExplicitFCSSCtrl(S,1);
}

static void mdlRTW_c1_PII_speed(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    sf_write_symbol_mapping(S, "PII_speed", "PII_speed",1);
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlStart_c1_PII_speed(SimStruct *S)
{
  SFc1_PII_speedInstanceStruct *chartInstance;
  chartInstance = (SFc1_PII_speedInstanceStruct *)malloc(sizeof
    (SFc1_PII_speedInstanceStruct));
  memset(chartInstance, 0, sizeof(SFc1_PII_speedInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c1_PII_speed;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c1_PII_speed;
  chartInstance->chartInfo.terminateChart = sf_opaque_terminate_c1_PII_speed;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c1_PII_speed;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c1_PII_speed;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c1_PII_speed;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c1_PII_speed;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c1_PII_speed;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c1_PII_speed;
  chartInstance->chartInfo.mdlStart = mdlStart_c1_PII_speed;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c1_PII_speed;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->S = S;
  ssSetUserData(S,(void *)(&(chartInstance->chartInfo)));/* register the chart instance with simstruct */
  if (!sim_mode_is_rtw_gen(S)) {
    init_dsm_address_info(chartInstance);
  }

  chart_debug_initialization(S,1);
}

void c1_PII_speed_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_START:
    mdlStart_c1_PII_speed(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c1_PII_speed(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c1_PII_speed(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c1_PII_speed_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
