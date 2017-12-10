  /*********************** dSPACE target specific file *************************

   Header file PII_speed_trc_ptr.h:

   Declaration of function that initializes the global TRC pointers

   RTI1103 6.9 (02-May-2012)
   Thu Jan 21 14:32:49 2016

   (c) Copyright 2008, dSPACE GmbH. All rights reserved.

  *****************************************************************************/
  #ifndef RTI_HEADER_PII_speed_trc_ptr_h_
  #define RTI_HEADER_PII_speed_trc_ptr_h_
  /* Include the model header file. */
  #include "PII_speed.h"
  #include "PII_speed_private.h"

  #ifdef EXTERN_C
  #undef EXTERN_C
  #endif

  #ifdef __cplusplus
  #define EXTERN_C                       extern "C"
  #else
  #define EXTERN_C                       extern
  #endif

  /*
   *  Declare the global TRC pointers
   */
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_0;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_1;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_2;
              EXTERN_C volatile  boolean_T *p_PII_speed_B_boolean_T_3;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_4;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_5;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_6;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_7;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_8;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_9;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_10;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_11;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_12;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_13;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_14;
              EXTERN_C volatile  real_T *p_PII_speed_B_real_T_15;
              EXTERN_C volatile  real_T *p_PII_speed_P_real_T_0;
              EXTERN_C volatile  boolean_T *p_PII_speed_P_boolean_T_1;
              EXTERN_C volatile  real_T *p_PII_speed_DWork_real_T_0;
              EXTERN_C volatile  int_T *p_PII_speed_DWork_int_T_2;
              EXTERN_C volatile  int8_T *p_PII_speed_DWork_int8_T_3;
              EXTERN_C volatile  boolean_T *p_PII_speed_DWork_boolean_T_4;
              EXTERN_C volatile  real_T *p_PII_speed_X_real_T_0;

   #define RTI_INIT_TRC_POINTERS() \
              p_PII_speed_B_real_T_0 = &PII_speed_B.Obc_en;\
              p_PII_speed_B_real_T_1 = &PII_speed_B.SFunction2;\
              p_PII_speed_B_real_T_2 = &PII_speed_B.SFunction2_d;\
              p_PII_speed_B_boolean_T_3 = &PII_speed_B.LogicalOperator;\
              p_PII_speed_B_real_T_4 = &PII_speed_B.IfActionSubsystem2_d.cb;\
              p_PII_speed_B_real_T_5 = &PII_speed_B.IfActionSubsystem3_p.xa;\
              p_PII_speed_B_real_T_6 = &PII_speed_B.IfActionSubsystem2_f.cb;\
              p_PII_speed_B_real_T_7 = &PII_speed_B.IfActionSubsystem3_g.xa;\
              p_PII_speed_B_real_T_8 = &PII_speed_B.IfActionSubsystem2_g.cb;\
              p_PII_speed_B_real_T_9 = &PII_speed_B.IfActionSubsystem3_h.xa;\
              p_PII_speed_B_real_T_10 = &PII_speed_B.IfActionSubsystem2_j.cb;\
              p_PII_speed_B_real_T_11 = &PII_speed_B.IfActionSubsystem3_a.xa;\
              p_PII_speed_B_real_T_12 = &PII_speed_B.IfActionSubsystem2.cb;\
              p_PII_speed_B_real_T_13 = &PII_speed_B.IfActionSubsystem3.xa;\
              p_PII_speed_B_real_T_14 = &PII_speed_B.IfActionSubsystem2_n.cb;\
              p_PII_speed_B_real_T_15 = &PII_speed_B.IfActionSubsystem3_d.xa;\
              p_PII_speed_P_real_T_0 = &PII_speed_P.Amp;\
              p_PII_speed_P_boolean_T_1 = &PII_speed_P.en;\
              p_PII_speed_DWork_real_T_0 = &PII_speed_DWork.TD_RWORK.modelTStart;\
              p_PII_speed_DWork_int_T_2 = &PII_speed_DWork.TD_IWORK.Tail;\
              p_PII_speed_DWork_int8_T_3 = &PII_speed_DWork.If_ActiveSubsystem;\
              p_PII_speed_DWork_boolean_T_4 = &PII_speed_DWork.Memory_PreviousInput;\
              p_PII_speed_X_real_T_0 = &PII_speed_X.Integrator_CSTATE;\

   #endif                       /* RTI_HEADER_PII_speed_trc_ptr_h_ */
