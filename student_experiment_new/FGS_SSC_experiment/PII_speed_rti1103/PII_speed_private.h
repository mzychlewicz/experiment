/*
 * PII_speed_private.h
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
#ifndef RTW_HEADER_PII_speed_private_h_
#define RTW_HEADER_PII_speed_private_h_
#include "rtwtypes.h"
#ifndef __RTWTYPES_H__
#error This file requires rtwtypes.h to be included
#else
#ifdef TMWTYPES_PREVIOUSLY_INCLUDED
#error This file requires rtwtypes.h to be included before tmwtypes.h
#else

/* Check for inclusion of an incorrect version of rtwtypes.h */
#ifndef RTWTYPES_ID_C08S16I32L32N32F1
#error This code was generated with a different "rtwtypes.h" than the file included
#endif                                 /* RTWTYPES_ID_C08S16I32L32N32F1 */
#endif                                 /* TMWTYPES_PREVIOUSLY_INCLUDED */
#endif                                 /* __RTWTYPES_H__ */

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

extern int slaveDSPPwmStopFlagCh1;
real_T rt_TDelayInterpolate(
  real_T tMinusDelay,                  /* tMinusDelay = currentSimTime - delay */
  real_T tStart,
  real_T *tBuf,
  real_T *uBuf,
  int_T bufSz,
  int_T *lastIdx,
  int_T oldestIdx,
  int_T newIdx,
  real_T initOutput,
  boolean_T discrete,
  boolean_T minorStepAndTAtLastMajorOutput)
  ;
extern void PII_speed_IfActionSubsystem3(real_T rtu_x, real_T *rty_Out1,
  rtB_IfActionSubsystem3_PII_spee *localB, real_T rtp_a, real_T rtp_b);
extern void PII_speed_IfActionSubsystem2(real_T rtu_x, real_T *rty_Out1,
  rtB_IfActionSubsystem2_PII_spee *localB, real_T rtp_b, real_T rtp_c);
extern void PII_speed_IfActionSubsystem3_c(real_T rtu_x, real_T *rty_Out1,
  rtB_IfActionSubsystem3_PII_sp_g *localB, real_T rtp_a, real_T rtp_b);
extern void PII_speed_IfActionSubsystem2_o(real_T rtu_x, real_T *rty_Out1,
  rtB_IfActionSubsystem2_PII_sp_i *localB, real_T rtp_b, real_T rtp_c);

/* private model entry point functions */
extern void PII_speed_derivatives(void);

#endif                                 /* RTW_HEADER_PII_speed_private_h_ */
