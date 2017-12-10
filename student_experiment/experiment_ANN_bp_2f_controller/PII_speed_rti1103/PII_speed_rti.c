/*********************** dSPACE target specific file *************************

   Include file PII_speed_rti.c:

   Definition of functions and variables for the system I/O and for
   the hardware and software interrupts used.

   RTI1103 6.9 (02-May-2012)
   Thu Dec 17 12:35:22 2015

   (c) Copyright 2006, dSPACE GmbH. All rights reserved.

 *****************************************************************************/

#if !(defined(__RTI_SIMENGINE__) || defined(RTIMP_FRAME))
# error This file may be included only by the RTI(-MP) simulation engine.
#endif

/* Include the model header file. */
#include "PII_speed.h"
#include "PII_speed_private.h"

/* Defines for block output and parameter structure existence */
#define RTI_rtB_STRUCTURE_EXISTS       1
#define RTI_rtP_STRUCTURE_EXISTS       1
#define RTB_STRUCTURE_NAME             PII_speed_B
#define RTP_STRUCTURE_NAME             PII_speed_P

/* dSPACE generated includes for header files */
#include <brtenv.h>
#include <rtkernel.h>
#include <rti_assert.h>
#include <rtidefineddatatypes.h>
#include <def1103.h>
#include <slvdsp1103.h>
#include <rti_slv1103.h>

/****** Definitions: task functions for timer tasks *********************/

/* Timer Task 1. (Base rate). */
static void rti_TIMERA(rtk_p_task_control_block task)
{
  /* Task entry code BEGIN */
  /* -- None. -- */
  /* Task entry code END */

  /* Task code. */
  baseRateService(task);

  /* Task exit code BEGIN */
  /* -- None. -- */
  /* Task exit code END */
}

/* ===== Declarations of RTI blocks ======================================== */

/* flag = UNDEF */
int slaveDSPPwmStopFlagCh1 = 2;

/* dSPACE Test-Automation Stimulus Engine */
#define TA_STIMULUS_ENGINE_ENABLE      0

/* ===== Definition of interface functions for simulation engine =========== */
#ifdef MULTITASKING
# define dsIsSampleHit(RTM,sti)        rtmGetSampleHitPtr(RTM)[sti]
#else
# define dsIsSampleHit(RTM,sti)        rtmIsSampleHit(RTM,sti,0)
#endif

#if defined(_INLINE)
# define __INLINE                      static inline
#else
# define __INLINE                      static
#endif

static void rti_mdl_initialize_host_services(void)
{
  {
    ts_timestamp_type ts = { 0, 0 };

    host_service(1, &ts);
  }
}

static void rti_mdl_initialize_io_boards(void)
{
  /* Registering of RTI products and modules at VCM */
  {
    vcm_module_register(VCM_MID_RTI1103, (void *) 0,
                        VCM_TXT_RTI1103, 6, 9, 0,
                        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);

    {
      vcm_module_descriptor_type* msg_mod_ptr;
      msg_mod_ptr = vcm_module_register(VCM_MID_MATLAB, (void *) 0,
        VCM_TXT_MATLAB, 7, 10, 0,
        VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_SIMULINK, msg_mod_ptr,
                          VCM_TXT_SIMULINK, 7, 5, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
      vcm_module_register(VCM_MID_RTW, msg_mod_ptr,
                          VCM_TXT_RTW, 7, 5, 0,
                          VCM_VERSION_RELEASE, 0, 0, 0, VCM_CTRL_NO_ST);
    }
  }

  /* dSPACE I/O Board DS1103 #1 */
  /* Initialize master - slave DSP communication */
  ds1103_slave_dsp_communication_init();

  /* Initialize automatic index generation */
  rti_slv1103_init_fcn_index();

  /* Initialize slave DSP error level */
  rti_slv1103_error_level = 0;
  ds1103_slave_dsp_pwm_init(0, 1.0/ 12000, 0.5, SLVDSP1103_PWM_MODE_SYM,
    SLVDSP1103_PWM_POL_HIGH, SLVDSP1103_PWM_CH1_MSK);
  ds1103_slave_dsp_pwm_output_set(0, SLVDSP1103_PWM_CH1_MSK,
    SLVDSP1103_PWM_TTL_LOW);
  ds1103_slave_dsp_pwm_duty_write_register(0, &rti_slv1103_fcn_index[6], 1);
  ds1103_slave_dsp_pwm_init(0, 1.0/ 12000, 0.5, SLVDSP1103_PWM_MODE_SYM,
    SLVDSP1103_PWM_POL_HIGH, SLVDSP1103_PWM_CH2_MSK);
  ds1103_slave_dsp_pwm_start(0, SLVDSP1103_PWM_CH2_MSK);
  rti_slv1103_taskqueue_error_check(0);
  ds1103_slave_dsp_pwm_duty_write_register(0, &rti_slv1103_fcn_index[7], 2);

  /* dSPACE I/O Board DS1103 #1 Unit:ENC_SETUP */
  ds1103_inc_init(1, DS1103_INC_CH1_RS422);
  ds1103_inc_init(2, DS1103_INC_CH2_RS422);
  ds1103_inc_init(3, DS1103_INC_CH3_RS422);
  ds1103_inc_init(4, DS1103_INC_CH4_RS422);
  ds1103_inc_init(5, DS1103_INC_CH5_RS422);
  ds1103_inc_init(6, DS1103_INC_CH6_RS422|DS1103_INC_CH6_32BIT);
  ds1103_inc_init(7, DS1103_INC_CH7_VPP|DS1103_INC_CH7_22BIT);

  /* Initialization of Master ADC units */
  ds1103_adc_trigger_setup(7, DS1103_TRIGGER_DISABLE);

  /* Initialization of Master MUXADC units */
  /* Initialization of Master EncSetup units  */
  ds1103_inc_trigger_setup(1,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(2,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(3,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(4,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(5,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(6,DS1103_TRIGGER_DISABLE);
  ds1103_inc_trigger_setup(7,DS1103_TRIGGER_DISABLE);
}

/* Function rti_mdl_slave_load() is empty */
#define rti_mdl_slave_load()

/* Function rti_mdl_rtk_initialize() is empty */
#define rti_mdl_rtk_initialize()

static void rti_mdl_initialize_io_units(void)
{
  /* dSPACE I/O Board DS1103 #1 Unit:BIT_IO */
  ds1103_bit_io_init(DS1103_DIO1_OUT);

  /* dSPACE I/O Board DS1103 #1 Unit:BIT_IO Group:BIT_OUT */
  ds1103_bit_io_clear(DS1103_DIO0_CLEAR|DS1103_DIO1_CLEAR|DS1103_DIO4_CLEAR);

  /* dSPACE I/O Board DS1103 #1 Unit:PWM */
  ds1103_slave_dsp_pwm_output_set(0, SLVDSP1103_PWM_CH1_MSK,
    SLVDSP1103_PWM_TTL_LOW);

  /* flag = UNDEF */
  slaveDSPPwmStopFlagCh1 = 2;
  rti_slv1103_taskqueue_error[0] = ds1103_slave_dsp_pwm_duty_write(0,
    rti_slv1103_fcn_index[7], 0.5);
  rti_slv1103_taskqueue_error_check(0);
  ds1103_slave_dsp_pwm_start(0, SLVDSP1103_PWM_CH2_MSK);
  rti_slv1103_taskqueue_error_check(0);
}

/* Function rti_mdl_acknowledge_interrupts() is empty */
#define rti_mdl_acknowledge_interrupts()

/* Function rti_mdl_timetables_register() is empty */
#define rti_mdl_timetables_register()

/* Function rti_mdl_timesync_simstate() is empty */
#define rti_mdl_timesync_simstate()

/* Function rti_mdl_timesync_baserate() is empty */
#define rti_mdl_timesync_baserate()

static void rti_mdl_background(void)
{
  /* dSPACE I/O Board DS1103 #1 */
  /* Check master - slave dsp communication */
  rti_slv1103_taskqueue_error_all_check();
}

__INLINE void rti_mdl_sample_input(void)
{
  /* Calls for sample time: [0.0002, 0.0] */
  if (dsIsSampleHit(PII_speed_M, 2)) {
    /* dSPACE I/O Board DS1103 #1 Unit:MultiAdc */
    {
      Float64 pvalues[20];
      ds1103_adc_multi_conv_read(DS1103_ADC_CHANNEL19, pvalues);
      PII_speed_B.SFunction = pvalues[18];
    }
  }

  /* Calls for sample time: [0.001, 0.0] */
  if (dsIsSampleHit(PII_speed_M, 3)) {
    /* dSPACE I/O Board DS1103 #1 Unit:ENC_POS Group:DPOS */
    PII_speed_B.SFunction2 = (real_T) ds1103_inc_delta_position_read(1,
      DS1103_INC_LINE_SUBDIV_4);
    PII_speed_B.SFunction2_d = (real_T) ds1103_inc_delta_position_read(2,
      DS1103_INC_LINE_SUBDIV_4);
  }
}

static void rti_mdl_daq_service()
{
  /* dSPACE Host Service */
  host_service(1, rtk_current_task_absolute_time_ptr_get());
}

#undef __INLINE

/****** [EOF] ****************************************************************/
