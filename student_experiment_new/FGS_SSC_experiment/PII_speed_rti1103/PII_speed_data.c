/*
 * PII_speed_data.c
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

#include "PII_speed.h"
#include "PII_speed_private.h"

/* Block parameters (auto storage) */
Parameters_PII_speed PII_speed_P = {
  0.0,                                 /* Variable: Amp
                                        * Referenced by: '<Root>/SG'
                                        */
  0.2,                                 /* Variable: f
                                        * Referenced by: '<Root>/SG'
                                        */
  1.0,                                 /* Variable: g
                                        * Referenced by: '<Root>/g'
                                        */
  660.0,                               /* Variable: kii
                                        * Referenced by: '<S11>/KI'
                                        */
  2.0,                                 /* Variable: kpi
                                        * Referenced by: '<S11>/Kp'
                                        */
  0.0,                                 /* Variable: nap
                                        * Referenced by: '<Root>/nap'
                                        */
  0.7,                                 /* Variable: obc_del
                                        * Referenced by: '<S7>/TD'
                                        */
  1.3,                                 /* Variable: obc_del2
                                        * Referenced by: '<S7>/TD1'
                                        */
  0.0,                                 /* Variable: obc_en
                                        * Referenced by: '<S7>/Obc_en'
                                        */
  0.0,                                 /* Variable: obc_en1
                                        * Referenced by: '<S7>/Obc_en1'
                                        */
  0.0,                                 /* Variable: offset
                                        * Referenced by: '<Root>/offset'
                                        */
  0.0,                                 /* Variable: start
                                        * Referenced by: '<S12>/Start'
                                        */
  0                                    /* Variable: en
                                        * Referenced by: '<Root>/EN'
                                        */
};

/* Constant parameters (auto storage) */
const ConstParam_PII_speed PII_speed_ConstP = {
  /* Expression: [0,0.25,0.3,0.4,0.5,0.6,0.75,1]
   * Referenced by: '<S7>/Obc_poziom'
   */
  { 0.0, 0.25, 0.3, 0.4, 0.5, 0.6, 0.75, 1.0 },

  /* Expression: [-1,-1,-0.78,-0.4,-0.3,-0.24,-0.18,-0.13]
   * Referenced by: '<S7>/Obc_poziom'
   */
  { -1.0, -1.0, -0.78, -0.4, -0.3, -0.24, -0.18, -0.13 },

  /* Computed Parameter: Logic_table
   * Referenced by: '<S57>/Logic'
   */
  { 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 1, 0, 0, 0, 0 }
};
