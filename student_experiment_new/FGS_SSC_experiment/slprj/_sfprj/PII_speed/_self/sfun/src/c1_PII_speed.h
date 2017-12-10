#ifndef __c1_PII_speed_h__
#define __c1_PII_speed_h__

/* Include files */
#include "sfc_sf.h"
#include "sfc_mex.h"
#include "rtwtypes.h"

/* Type Definitions */
typedef struct {
  const char *context;
  const char *name;
  const char *dominantType;
  const char *resolved;
  uint32_T fileLength;
  uint32_T fileTime1;
  uint32_T fileTime2;
} c1_ResolvedFunctionInfo;

typedef struct {
  real_T c1_dj_data[49];
  real_T c1_dk;
  real_T c1_dw1_data[21];
  real_T c1_dw2_data[8];
  real_T c1_init_nn_output;
  real_T c1_init_state[30];
  real_T c1_ipj_data[8];
  real_T c1_jv_data[49];
  real_T c1_kv;
  real_T c1_nhn;
  real_T c1_number_of_weights;
  real_T c1_opk;
  real_T c1_sm;
  real_T c1_w1_data[21];
  real_T c1_w2_data[8];
  SimStruct *S;
  int32_T c1_dj_sizes[2];
  int32_T c1_dw1_sizes[2];
  int32_T c1_dw2_sizes[2];
  int32_T c1_ipj_sizes[2];
  int32_T c1_jv_sizes[2];
  int32_T c1_w1_sizes[2];
  int32_T c1_w2_sizes[2];
  uint32_T chartNumber;
  uint32_T instanceNumber;
  boolean_T c1_dj_not_empty;
  boolean_T c1_dk_not_empty;
  boolean_T c1_doneDoubleBufferReInit;
  boolean_T c1_dw1_not_empty;
  boolean_T c1_dw2_not_empty;
  boolean_T c1_init_nn_output_not_empty;
  boolean_T c1_init_state_not_empty;
  boolean_T c1_ipj_not_empty;
  boolean_T c1_isStable;
  boolean_T c1_jv_not_empty;
  boolean_T c1_kv_not_empty;
  boolean_T c1_nhn_not_empty;
  boolean_T c1_number_of_weights_not_empty;
  boolean_T c1_opk_not_empty;
  boolean_T c1_sm_not_empty;
  boolean_T c1_w1_not_empty;
  boolean_T c1_w2_not_empty;
  uint8_T c1_is_active_c1_PII_speed;
  ChartInfoStruct chartInfo;
} SFc1_PII_speedInstanceStruct;

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c1_PII_speed_get_eml_resolved_functions_info(void);

/* Function Definitions */
extern void sf_c1_PII_speed_get_check_sum(mxArray *plhs[]);
extern void c1_PII_speed_method_dispatcher(SimStruct *S, int_T method, void
  *data);

#endif
