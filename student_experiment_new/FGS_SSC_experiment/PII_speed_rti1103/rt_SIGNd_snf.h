/*
 * rt_SIGNd_snf.h
 *
 * Real-Time Workshop code generation for Simulink model "PII_speed.mdl".
 *
 * Model version              : 1.189
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Thu Jan 21 14:32:49 2016
 *
 * Target selection: rti1103.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_rt_SIGNd_snf_h_
#define RTW_HEADER_rt_SIGNd_snf_h_
#include "rt_nonfinite.h"
#define rt_SIGNd_snf(a)                ( ((a) < 0.0) ? -1.0 : ((a) > 0.0) ? 1.0 : ((a) == 0.0) ? 0.0 : (rtNaN) )
#endif                                 /* RTW_HEADER_rt_SIGNd_snf_h_ */
