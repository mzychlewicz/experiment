/*
 * PII_speed.c
 *
 * Real-Time Workshop code generation for Simulink model "PII_speed.mdl".
 *
 * Model version              : 1.184
 * Real-Time Workshop version : 7.5  (R2010a)  25-Jan-2010
 * C source code generated on : Thu Dec 17 12:35:22 2015
 *
 * Target selection: rti1103.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Generic->Custom
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "PII_speed_trc_ptr.h"
#include "PII_speed.h"
#include "PII_speed_private.h"

/* Block signals (auto storage) */
BlockIO_PII_speed PII_speed_B;

/* Continuous states */
ContinuousStates_PII_speed PII_speed_X;

/* Block states (auto storage) */
D_Work_PII_speed PII_speed_DWork;

/* Previous zero-crossings (trigger) states */
PrevZCSigStates_PII_speed PII_speed_PrevZCSigState;

/* Real-time model */
RT_MODEL_PII_speed PII_speed_M_;
RT_MODEL_PII_speed *PII_speed_M = &PII_speed_M_;
static void rate_scheduler(void);

/*
 * Time delay interpolation routine
 *
 * The linear interpolation is performed using the formula:
 *
 *          (t2 - tMinusDelay)         (tMinusDelay - t1)
 * u(t)  =  ----------------- * u1  +  ------------------- * u2
 *              (t2 - t1)                  (t2 - t1)
 */
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
{
  int_T i;
  real_T yout, t1, t2, u1, u2;

  /*
   * If tMinusDelay is less than zero, should output initial value
   */
  if (tMinusDelay <= tStart)
    return initOutput;

  /* For fixed buffer extrapolation:
   * if tMinusDelay is small than the time at oldestIdx, if discrete, output
   * tailptr value,  else use tailptr and tailptr+1 value to extrapolate
   * It is also for fixed buffer. Note: The same condition can happen for transport delay block where
   * use tStart and and t[tail] other than using t[tail] and t[tail+1].
   * See below
   */
  if ((tMinusDelay <= tBuf[oldestIdx] ) ) {
    if (discrete) {
      return(uBuf[oldestIdx]);
    } else {
      int_T tempIdx= oldestIdx + 1;
      if (oldestIdx == bufSz-1)
        tempIdx = 0;
      t1= tBuf[oldestIdx];
      t2= tBuf[tempIdx];
      u1= uBuf[oldestIdx];
      u2= uBuf[tempIdx];
      if (t2 == t1) {
        if (tMinusDelay >= t2) {
          yout = u2;
        } else {
          yout = u1;
        }
      } else {
        real_T f1 = (t2-tMinusDelay) / (t2-t1);
        real_T f2 = 1.0 - f1;

        /*
         * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
         */
        yout = f1*u1 + f2*u2;
      }

      return yout;
    }
  }

  /*
   * When block does not have direct feedthrough, we use the table of
   * values to extrapolate off the end of the table for delays that are less
   * than 0 (less then step size).  This is not completely accurate.  The
   * chain of events is as follows for a given time t.  Major output - look
   * in table.  Update - add entry to table.  Now, if we call the output at
   * time t again, there is a new entry in the table. For very small delays,
   * this means that we will have a different answer from the previous call
   * to the output fcn at the same time t.  The following code prevents this
   * from happening.
   */
  if (minorStepAndTAtLastMajorOutput) {
    /* pretend that the new entry has not been added to table */
    if (newIdx != 0) {
      if (*lastIdx == newIdx) {
        (*lastIdx)--;
      }

      newIdx--;
    } else {
      if (*lastIdx == newIdx) {
        *lastIdx = bufSz-1;
      }

      newIdx = bufSz - 1;
    }
  }

  i = *lastIdx;
  if (tBuf[i] < tMinusDelay) {
    /* Look forward starting at last index */
    while (tBuf[i] < tMinusDelay) {
      /* May occur if the delay is less than step-size - extrapolate */
      if (i == newIdx)
        break;
      i = ( i < (bufSz-1) ) ? (i+1) : 0;/* move through buffer */
    }
  } else {
    /*
     * Look backwards starting at last index which can happen when the
     * delay time increases.
     */
    while (tBuf[i] >= tMinusDelay) {
      /*
       * Due to the entry condition at top of function, we
       * should never hit the end.
       */
      i = (i > 0) ? i-1 : (bufSz-1);   /* move through buffer */
    }

    i = ( i < (bufSz-1) ) ? (i+1) : 0;
  }

  *lastIdx = i;
  if (discrete) {
    /*
     * tempEps = 128 * eps;
     * localEps = max(tempEps, tempEps*fabs(tBuf[i]))/2;
     */
    double tempEps = (DBL_EPSILON) * 128.0;
    double localEps = tempEps * fabs(tBuf[i]);
    if (tempEps > localEps) {
      localEps = tempEps;
    }

    localEps = localEps / 2.0;
    if (tMinusDelay >= (tBuf[i] - localEps)) {
      yout = uBuf[i];
    } else {
      if (i == 0) {
        yout = uBuf[bufSz-1];
      } else {
        yout = uBuf[i-1];
      }
    }
  } else {
    if (i == 0) {
      t1 = tBuf[bufSz-1];
      u1 = uBuf[bufSz-1];
    } else {
      t1 = tBuf[i-1];
      u1 = uBuf[i-1];
    }

    t2 = tBuf[i];
    u2 = uBuf[i];
    if (t2 == t1) {
      if (tMinusDelay >= t2) {
        yout = u2;
      } else {
        yout = u1;
      }
    } else {
      real_T f1 = (t2-tMinusDelay) / (t2-t1);
      real_T f2 = 1.0 - f1;

      /*
       * Use Lagrange's interpolation formula.  Exact outputs at t1, t2.
       */
      yout = f1*u1 + f2*u2;
    }
  }

  return(yout);
}

/*
 * This function updates active task flag for each subrate.
 * The function must be called at model base rate, hence the
 * generated code self-manages all its subrates.
 */
static void rate_scheduler(void)
{
  /* Compute which subrates run during the next base time step.  Subrates
   * are an integer multiple of the base rate counter.  Therefore, the subtask
   * counter is reset when it reaches its limit (zero means run).
   */
  (PII_speed_M->Timing.TaskCounters.TID[2])++;
  if ((PII_speed_M->Timing.TaskCounters.TID[2]) > 1) {/* Sample time: [0.0002s, 0.0s] */
    PII_speed_M->Timing.TaskCounters.TID[2] = 0;
  }

  PII_speed_M->Timing.sampleHits[2] = (PII_speed_M->Timing.TaskCounters.TID[2] ==
    0);
  (PII_speed_M->Timing.TaskCounters.TID[3])++;
  if ((PII_speed_M->Timing.TaskCounters.TID[3]) > 9) {/* Sample time: [0.001s, 0.0s] */
    PII_speed_M->Timing.TaskCounters.TID[3] = 0;
  }

  PII_speed_M->Timing.sampleHits[3] = (PII_speed_M->Timing.TaskCounters.TID[3] ==
    0);
}

/*
 * This function updates continuous states using the ODE1 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE1_IntgData *id = (ODE1_IntgData *)rtsiGetSolverData(si);
  real_T *f0 = id->f[0];
  int_T i;
  int_T nXc = 8;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);
  rtsiSetdX(si, f0);
  PII_speed_derivatives();
  rtsiSetT(si, tnew);
  for (i = 0; i < nXc; i++) {
    *x += h * f0[i];
    x++;
  }

  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void PII_speed_output(int_T tid)
{
  real_T currentTime;
  ZCEventType zcEvent;
  if (rtmIsMajorTimeStep(PII_speed_M)) {
    /* set solver stop time */
    if (!(PII_speed_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&PII_speed_M->solverInfo,
                            ((PII_speed_M->Timing.clockTickH0 + 1) *
        PII_speed_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&PII_speed_M->solverInfo,
                            ((PII_speed_M->Timing.clockTick0 + 1) *
        PII_speed_M->Timing.stepSize0 + PII_speed_M->Timing.clockTickH0 *
        PII_speed_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(PII_speed_M)) {
    PII_speed_M->Timing.t[0] = rtsiGetT(&PII_speed_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (rti_commonblock): '<S2>/S-Function1' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* dSPACE I/O Board DS1103 #1 Unit:BIT_IO Group:BIT_OUT */
    if (PII_speed_P.en > 0) {
      ds1103_bit_io_set(DS1103_DIO0_SET);
    } else {
      ds1103_bit_io_clear(DS1103_DIO0_CLEAR);
    }
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S2>/S-Function2' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* dSPACE I/O Board DS1103 #1 Unit:BIT_IO Group:BIT_OUT */
    if (TRUE > 0) {
      ds1103_bit_io_set(DS1103_DIO1_SET);
    } else {
      ds1103_bit_io_clear(DS1103_DIO1_CLEAR);
    }

    /* S-Function (rti_commonblock): '<S2>/S-Function3' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S2>/S-Function4' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S2>/S-Function5' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* dSPACE I/O Board DS1103 #1 Unit:BIT_IO Group:BIT_OUT */
    if (TRUE > 0) {
      ds1103_bit_io_set(DS1103_DIO4_SET);
    } else {
      ds1103_bit_io_clear(DS1103_DIO4_CLEAR);
    }

    /* S-Function (rti_commonblock): '<S2>/S-Function6' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S2>/S-Function7' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S2>/S-Function8' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  /* Step: '<S7>/Obc_en' */
  currentTime = PII_speed_M->Timing.t[0];
  if (currentTime < 0.0) {
    PII_speed_B.Obc_en = 0.0;
  } else {
    PII_speed_B.Obc_en = PII_speed_P.obc_en;
  }

  /* TransportDelay: '<S7>/TD' */
  {
    real_T **uBuffer = (real_T**)&PII_speed_DWork.TD_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&PII_speed_DWork.TD_PWORK.TUbufferPtrs[1];
    real_T simTime = PII_speed_M->Timing.t[0];
    real_T tMinusDelay = simTime - PII_speed_P.obc_del;
    PII_speed_B.TD = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      PII_speed_DWork.TD_IWORK.CircularBufSize,
      &PII_speed_DWork.TD_IWORK.Last,
      PII_speed_DWork.TD_IWORK.Tail,
      PII_speed_DWork.TD_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Signum: '<S7>/Sign' */
  PII_speed_B.Sign = rt_SIGNd_snf(PII_speed_B.TD);

  /* TransportDelay: '<S7>/TD1' */
  {
    real_T **uBuffer = (real_T**)&PII_speed_DWork.TD1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&PII_speed_DWork.TD1_PWORK.TUbufferPtrs[1];
    real_T simTime = PII_speed_M->Timing.t[0];
    real_T tMinusDelay = simTime - PII_speed_P.obc_del2;
    PII_speed_B.TD1 = rt_TDelayInterpolate(
      tMinusDelay,
      0.0,
      *tBuffer,
      *uBuffer,
      PII_speed_DWork.TD1_IWORK.CircularBufSize,
      &PII_speed_DWork.TD1_IWORK.Last,
      PII_speed_DWork.TD1_IWORK.Tail,
      PII_speed_DWork.TD1_IWORK.Head,
      0.0,
      0,
      0);
  }

  /* Signum: '<S7>/Sign1' */
  PII_speed_B.Sign1 = rt_SIGNd_snf(PII_speed_B.TD1);

  /* Sum: '<S7>/Add' */
  PII_speed_B.Add = PII_speed_B.Sign - PII_speed_B.Sign1;

  /* SignalGenerator: '<Root>/SG' */
  currentTime = PII_speed_P.f * PII_speed_M->Timing.t[0];
  if (currentTime - floor(currentTime) >= 0.5) {
    PII_speed_B.SG = PII_speed_P.Amp;
  } else {
    PII_speed_B.SG = -PII_speed_P.Amp;
  }

  /* Abs: '<S7>/Abs' */
  PII_speed_B.Abs = fabs(PII_speed_B.SG);

  /* Lookup: '<S7>/Obc_poziom' */
  PII_speed_B.Obc_poziom = rt_Lookup((const real_T *)
    (&PII_speed_ConstP.Obc_poziom_XData[0]), 8, PII_speed_B.Abs, (const real_T *)
                                     (&PII_speed_ConstP.Obc_poziom_YData[0]));

  /* Product: '<S7>/Product' */
  PII_speed_B.Product = PII_speed_B.Obc_en * PII_speed_B.Add *
    PII_speed_B.Obc_poziom;

  /* Step: '<S7>/Obc_en1' */
  currentTime = PII_speed_M->Timing.t[0];
  if (currentTime < 0.0) {
    PII_speed_B.Obc_en1 = 0.0;
  } else {
    PII_speed_B.Obc_en1 = PII_speed_P.obc_en1;
  }

  /* Gain: '<Root>/Gain' */
  PII_speed_B.Gain[0] = 0.5 * PII_speed_B.Product;
  PII_speed_B.Gain[1] = 0.5 * PII_speed_B.Obc_en1;
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S6>/S-Function1' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* dSPACE I/O Board DS1103 #1 Unit:PWM */
    PII_speed_DWork.SFunction1_IWORK[0] = PII_speed_B.Gain[1];

    /* write the duty cycle down */
    ds1103_slave_dsp_pwm_duty_write(0, rti_slv1103_fcn_index[6],
      PII_speed_B.Gain[0]);

    /* set outputs to TTL-level or retrigger PWM generation */
    if (PII_speed_DWork.SFunction1_IWORK[0] == 1 ) {
      /*  if (flag == RUN)||(flag == UNDEF) */
      if ((slaveDSPPwmStopFlagCh1 == 1)||(slaveDSPPwmStopFlagCh1 == 2))/* PWM Stop signal from Input Port -> set outputs to TTL-level */
      {
        slaveDSPPwmStopFlagCh1 = 0;
        ds1103_slave_dsp_pwm_output_set(0, SLVDSP1103_PWM_CH1_MSK,
          SLVDSP1103_PWM_TTL_LOW);
      }
    } else if (PII_speed_DWork.SFunction1_IWORK[0] == 0 ) {
      /* PWM Stop signal disabled -> trigger PWM generation once */
      if ((slaveDSPPwmStopFlagCh1 == 0)||(slaveDSPPwmStopFlagCh1 == 2)) {
        slaveDSPPwmStopFlagCh1 = 1;
        ds1103_slave_dsp_pwm_start(0, SLVDSP1103_PWM_CH1_MSK);
      }
    }
  }

  /* Integrator: '<S9>/Integrator1'
   * About '<S9>/Integrator1':
   *  Limited Integrator
   */
  if (PII_speed_X.Integrator1_CSTATE >= 2.0 ) {
    PII_speed_X.Integrator1_CSTATE = 2.0;
  } else if (PII_speed_X.Integrator1_CSTATE <= (-2.0) ) {
    PII_speed_X.Integrator1_CSTATE = (-2.0);
  }

  PII_speed_B.Integrator1 = PII_speed_X.Integrator1_CSTATE;

  /* Saturate: '<Root>/Saturation' */
  currentTime = PII_speed_B.Integrator1;
  PII_speed_B.Saturation = rt_SATURATE(currentTime, -2.0, 2.0);
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[2] == 0) {
    /* S-Function (rti_commonblock): '<S1>/S-Function' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* Gain: '<Root>/norm_I' */
    PII_speed_B.norm_I = (-7.6645) * PII_speed_B.SFunction;

    /* Sum: '<Root>/prad22' incorporates:
     *  Constant: '<Root>/offset'
     */
    PII_speed_B.prad22 = PII_speed_P.offset + PII_speed_B.norm_I;

    /* Gain: '<Root>/prad_pom' */
    PII_speed_B.prad_pom = 1.0 * PII_speed_B.prad22;

    /* Gain: '<Root>/prad' */
    PII_speed_B.prad = (-1.0) * PII_speed_B.prad_pom;

    /* Sum: '<S11>/Sum1' */
    PII_speed_B.Sum1 = PII_speed_B.Saturation - PII_speed_B.prad;

    /* Gain: '<S11>/Kp' */
    PII_speed_B.Kp = PII_speed_P.kpi * PII_speed_B.Sum1;

    /* Logic: '<Root>/Logical Operator' incorporates:
     *  Constant: '<Root>/EN'
     */
    PII_speed_B.LogicalOperator = !PII_speed_P.en;
  }

  /* Integrator: '<S11>/Continous-time integrator'
   * About '<S11>/Continous-time integrator':
   *  Limited Integrator
   */
  if (rtmIsMajorTimeStep(PII_speed_M)) {
    ZCEventType zcEvent;
    zcEvent = ((ZCEventType) ((PII_speed_B.LogicalOperator !=
      (PII_speed_PrevZCSigState.Continoustimeintegrator_Reset_Z == POS_ZCSIG)) &&
                (PII_speed_PrevZCSigState.Continoustimeintegrator_Reset_Z !=
                 UNINITIALIZED_ZCSIG)));

    /* evaluate zero-crossings and the level of the reset signal */
    PII_speed_PrevZCSigState.Continoustimeintegrator_Reset_Z = (ZCSigState)
      PII_speed_B.LogicalOperator;
    if (zcEvent || PII_speed_B.LogicalOperator) {
      PII_speed_X.Continoustimeintegrator_CSTATE = 0.0;
    }
  }

  if (PII_speed_X.Continoustimeintegrator_CSTATE >= 0.52 ) {
    PII_speed_X.Continoustimeintegrator_CSTATE = 0.52;
  } else if (PII_speed_X.Continoustimeintegrator_CSTATE <= (-0.52) ) {
    PII_speed_X.Continoustimeintegrator_CSTATE = (-0.52);
  }

  PII_speed_B.Continoustimeintegrator =
    PII_speed_X.Continoustimeintegrator_CSTATE;
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[2] == 0) {
    /* Sum: '<S11>/Sum2' */
    PII_speed_B.Sum2 = PII_speed_B.Kp + PII_speed_B.Continoustimeintegrator;

    /* Saturate: '<S11>/Saturation' */
    currentTime = PII_speed_B.Sum2;
    PII_speed_B.Saturation_h = rt_SATURATE(currentTime, -0.52, 0.52);

    /* Sum: '<S11>/prad' incorporates:
     *  Constant: '<S11>/offset'
     */
    PII_speed_B.prad_p = 0.5 + PII_speed_B.Saturation_h;

    /* Gain: '<Root>/g' */
    PII_speed_B.g = PII_speed_P.g * PII_speed_B.prad_p;

    /* Sum: '<Root>/PWM' incorporates:
     *  Constant: '<Root>/nap'
     */
    PII_speed_B.PWM = PII_speed_P.nap + PII_speed_B.g;

    /* S-Function (rti_commonblock): '<S6>/S-Function2' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* dSPACE I/O Board DS1103 #1 Unit:PWM */
    ds1103_slave_dsp_pwm_duty_write(0, rti_slv1103_fcn_index[7], PII_speed_B.PWM);
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S6>/S-Function3' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S6>/S-Function4' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* HitCross: '<S12>/HC' */
    zcEvent = rt_ZCFcn(RISING_ZERO_CROSSING,
                       &PII_speed_PrevZCSigState.HC_Input_ZCE,
                       (PII_speed_B.SG - 0.0));
    if (PII_speed_DWork.HC_MODE == 0) {
      if (zcEvent != NO_ZCEVENT) {
        PII_speed_B.HC = !PII_speed_B.HC;
        PII_speed_DWork.HC_MODE = 1;
      } else {
        if (PII_speed_B.HC && (PII_speed_B.SG != 0.0)) {
          PII_speed_B.HC = FALSE;
        }
      }
    } else {
      if (PII_speed_B.SG != 0.0) {
        PII_speed_B.HC = FALSE;
      }

      PII_speed_DWork.HC_MODE = 0;
    }

    /* Logic: '<S12>/LO' incorporates:
     *  Constant: '<S12>/Start'
     */
    PII_speed_B.LO = (PII_speed_B.HC && (PII_speed_P.start != 0.0));

    /* Logic: '<S12>/LO3' incorporates:
     *  Constant: '<S12>/Start'
     */
    PII_speed_B.LO3 = !(PII_speed_P.start != 0.0);

    /* Memory: '<S17>/Memory' */
    PII_speed_B.Memory = PII_speed_DWork.Memory_PreviousInput;

    /* CombinatorialLogic: '<S17>/Logic' */
    {
      uint_T rowidx= 0;

      /* Compute the truth table row index corresponding to the input */
      rowidx = (rowidx << 1) + (uint_T)(PII_speed_B.LO != 0);
      rowidx = (rowidx << 1) + (uint_T)(PII_speed_B.LO3 != 0);
      rowidx = (rowidx << 1) + (uint_T)(PII_speed_B.Memory != 0);

      /* Copy the appropriate row of the table into the block output vector */
      PII_speed_B.Logic[0] = PII_speed_ConstP.Logic_table[rowidx];
      PII_speed_B.Logic[1] = PII_speed_ConstP.Logic_table[rowidx + 8];
    }
  }

  /* Switch: '<S12>/Switch' incorporates:
   *  Constant: '<S12>/S'
   */
  if (PII_speed_B.Logic[0]) {
    PII_speed_B.Switch = PII_speed_B.SG;
  } else {
    PII_speed_B.Switch = (real_T)FALSE;
  }

  /* Abs: '<Root>/Abs' */
  PII_speed_B.Abs_c = fabs(PII_speed_B.Switch);
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S3>/S-Function1' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* S-Function (rti_commonblock): '<S3>/S-Function2' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S4>/S-Function1' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* S-Function (rti_commonblock): '<S4>/S-Function2' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  /* Gain: '<S7>/Gain' */
  PII_speed_B.Gain_h = (-1.0) * PII_speed_B.Switch;
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* ZeroOrderHold: '<Root>/ZOH5' */
    PII_speed_B.ZOH5 = PII_speed_B.Switch;

    /* Gain: '<Root>/predkosc2' */
    PII_speed_B.predkosc2 = (-1.1494252873563218E-003) *
      PII_speed_B.SFunction2_d;

    /* Gain: '<Root>/omega2' */
    PII_speed_B.omega2 = (-1.0) * PII_speed_B.predkosc2;

    /* ZeroOrderHold: '<Root>/ZOH6' */
    PII_speed_B.ZOH6 = PII_speed_B.omega2;

    /* Sum: '<S9>/Add6' */
    PII_speed_B.Add6 = PII_speed_B.ZOH5 - PII_speed_B.ZOH6;

    /* Gain: '<S9>/Gain1' */
    PII_speed_B.Gain1 = 274.287104 * PII_speed_B.Add6;

    /* Gain: '<Root>/predkosc1' */
    PII_speed_B.predkosc1 = 1.1494252873563218E-003 * PII_speed_B.SFunction2;

    /* Gain: '<Root>/omega1' */
    PII_speed_B.omega1 = (-1.0) * PII_speed_B.predkosc1;

    /* ZeroOrderHold: '<Root>/ZOH1' */
    PII_speed_B.ZOH1 = PII_speed_B.omega1;

    /* Gain: '<S9>/Gain2' */
    PII_speed_B.Gain2 = 3.2480000000000004E+001 * PII_speed_B.ZOH1;
  }

  /* TransferFcn: '<S10>/Transfer Fcn1' */
  PII_speed_B.TransferFcn1 = 20.3*PII_speed_B.ZOH1;
  PII_speed_B.TransferFcn1 += (-2030.0)*PII_speed_X.TransferFcn1_CSTATE;

  /* TransferFcn: '<S10>/Transfer Fcn2' */
  PII_speed_B.TransferFcn2 = 100.0*PII_speed_X.TransferFcn2_CSTATE;

  /* Sum: '<S10>/ms_est' */
  PII_speed_B.ms_est = PII_speed_B.TransferFcn2 - PII_speed_B.TransferFcn1;
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* ZeroOrderHold: '<Root>/ZOH4' */
    PII_speed_B.ZOH4 = PII_speed_B.ms_est;

    /* Gain: '<S9>/Gain4' */
    PII_speed_B.Gain4 = 3.0668800000000007E+000 * PII_speed_B.ZOH4;

    /* Gain: '<S9>/Gain3' */
    PII_speed_B.Gain3 = (-5.0512896000000040E+000) * PII_speed_B.ZOH6;

    /* Sum: '<S9>/Add8' */
    PII_speed_B.Add8 = (PII_speed_B.Gain2 + PII_speed_B.Gain4) +
      PII_speed_B.Gain3;
  }

  /* Derivative: '<S9>/Derivative' */
  {
    real_T t = PII_speed_M->Timing.t[0];
    real_T timeStampA = PII_speed_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = PII_speed_DWork.Derivative_RWORK.TimeStampB;
    real_T *lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA >= t && timeStampB >= t) {
      PII_speed_B.Derivative = 0.0;
    } else {
      real_T deltaT;
      real_T lastTime = timeStampA;
      if (timeStampA < timeStampB) {
        if (timeStampB < t) {
          lastTime = timeStampB;
          lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeB;
        }
      } else if (timeStampA >= t) {
        lastTime = timeStampB;
        lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeB;
      }

      deltaT = t - lastTime;
      PII_speed_B.Derivative = (PII_speed_B.Add8 - *lastU++) / deltaT;
    }
  }

  /* Sum: '<S9>/Add2' */
  PII_speed_B.Add2 = PII_speed_B.Gain1 - PII_speed_B.Derivative;

  /* Integrator: '<S16>/Integrator2' */
  PII_speed_B.Integrator2 = PII_speed_X.Integrator2_CSTATE;
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* ZeroOrderHold: '<Root>/ZOH3' */
    PII_speed_B.ZOH3 = PII_speed_B.prad;
  }

  /* Integrator: '<S16>/Integrator1' */
  PII_speed_B.Integrator1_e = PII_speed_X.Integrator1_CSTATE_m;

  /* Sum: '<S16>/Add9' */
  PII_speed_B.Add9 = PII_speed_B.ZOH1 - PII_speed_B.Integrator1_e;

  /* Product: '<S16>/Product' incorporates:
   *  Constant: '<S16>/Constant'
   */
  PII_speed_B.Product_f = PII_speed_B.Add9 * 31.3884;

  /* Sum: '<S16>/  ' */
  PII_speed_B.u = (PII_speed_B.ZOH3 - PII_speed_B.Integrator2) +
    PII_speed_B.Product_f;

  /* Product: '<S16>/Product2' incorporates:
   *  Constant: '<S16>/Constant2'
   */
  PII_speed_B.Product2 = PII_speed_B.Add9 * 1.998748E+002;

  /* Integrator: '<S16>/Integrator4' */
  PII_speed_B.Integrator4 = PII_speed_X.Integrator4_CSTATE;

  /* Sum: '<S16>/  1' */
  PII_speed_B.u_m = PII_speed_B.Product2 - PII_speed_B.Integrator4;

  /* Integrator: '<S16>/Integrator3' */
  PII_speed_B.Integrator3 = PII_speed_X.Integrator3_CSTATE;

  /* Product: '<S16>/Product1' incorporates:
   *  Constant: '<S16>/Constant1'
   */
  PII_speed_B.Product1 = PII_speed_B.Add9 * (-15.6627);

  /* Sum: '<S16>/  2' */
  PII_speed_B.u_f = (PII_speed_B.Integrator1_e - PII_speed_B.Integrator3) +
    PII_speed_B.Product1;

  /* Sum: '<S16>/  3' */
  PII_speed_B.u_i = PII_speed_B.Integrator2 + PII_speed_B.u_m;

  /* Gain: '<S16>/1//T1' */
  PII_speed_B.T1 = 4.9261083743842358E+000 * PII_speed_B.u;

  /* Gain: '<S16>/1//T2' */
  PII_speed_B.T2 = 4.9261083743842358E+000 * PII_speed_B.u_i;

  /* Gain: '<S16>/1//Tc' */
  PII_speed_B.Tc = 3.8461538461538464E+002 * PII_speed_B.u_f;

  /* Product: '<S16>/Product3' incorporates:
   *  Constant: '<S16>/Constant3'
   */
  PII_speed_B.Product3 = PII_speed_B.Add9 * (-10744.0);
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[2] == 0) {
    /* Gain: '<S11>/KI' */
    PII_speed_B.KI = PII_speed_P.kii * PII_speed_B.Sum1;
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* S-Function (rti_commonblock): '<S5>/S-Function1' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function2' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function3' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function4' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function5' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function6' */
    /* This comment workarounds a Real-Time Workshop code generation problem */

    /* S-Function (rti_commonblock): '<S5>/S-Function7' */
    /* This comment workarounds a Real-Time Workshop code generation problem */
  }

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Model update function */
void PII_speed_update(int_T tid)
{
  /* Update for TransportDelay: '<S7>/TD' */
  {
    real_T **uBuffer = (real_T**)&PII_speed_DWork.TD_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&PII_speed_DWork.TD_PWORK.TUbufferPtrs[1];
    real_T simTime = PII_speed_M->Timing.t[0];
    PII_speed_DWork.TD_IWORK.Head = ((PII_speed_DWork.TD_IWORK.Head <
      (PII_speed_DWork.TD_IWORK.CircularBufSize-1)) ?
      (PII_speed_DWork.TD_IWORK.Head+1) : 0);
    if (PII_speed_DWork.TD_IWORK.Head == PII_speed_DWork.TD_IWORK.Tail) {
      PII_speed_DWork.TD_IWORK.Tail = ((PII_speed_DWork.TD_IWORK.Tail <
        (PII_speed_DWork.TD_IWORK.CircularBufSize-1)) ?
        (PII_speed_DWork.TD_IWORK.Tail+1) : 0);
    }

    (*tBuffer)[PII_speed_DWork.TD_IWORK.Head] = simTime;
    (*uBuffer)[PII_speed_DWork.TD_IWORK.Head] = PII_speed_B.Gain_h;
  }

  /* Update for TransportDelay: '<S7>/TD1' */
  {
    real_T **uBuffer = (real_T**)&PII_speed_DWork.TD1_PWORK.TUbufferPtrs[0];
    real_T **tBuffer = (real_T**)&PII_speed_DWork.TD1_PWORK.TUbufferPtrs[1];
    real_T simTime = PII_speed_M->Timing.t[0];
    PII_speed_DWork.TD1_IWORK.Head = ((PII_speed_DWork.TD1_IWORK.Head <
      (PII_speed_DWork.TD1_IWORK.CircularBufSize-1)) ?
      (PII_speed_DWork.TD1_IWORK.Head+1) : 0);
    if (PII_speed_DWork.TD1_IWORK.Head == PII_speed_DWork.TD1_IWORK.Tail) {
      PII_speed_DWork.TD1_IWORK.Tail = ((PII_speed_DWork.TD1_IWORK.Tail <
        (PII_speed_DWork.TD1_IWORK.CircularBufSize-1)) ?
        (PII_speed_DWork.TD1_IWORK.Tail+1) : 0);
    }

    (*tBuffer)[PII_speed_DWork.TD1_IWORK.Head] = simTime;
    (*uBuffer)[PII_speed_DWork.TD1_IWORK.Head] = PII_speed_B.TD;
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update for Memory: '<S17>/Memory' */
    PII_speed_DWork.Memory_PreviousInput = PII_speed_B.Logic[0];
  }

  /* Update for Derivative: '<S9>/Derivative' */
  {
    real_T timeStampA = PII_speed_DWork.Derivative_RWORK.TimeStampA;
    real_T timeStampB = PII_speed_DWork.Derivative_RWORK.TimeStampB;
    real_T* lastTime = &PII_speed_DWork.Derivative_RWORK.TimeStampA;
    real_T* lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeA;
    if (timeStampA != rtInf) {
      if (timeStampB == rtInf) {
        lastTime = &PII_speed_DWork.Derivative_RWORK.TimeStampB;
        lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeB;
      } else if (timeStampA >= timeStampB) {
        lastTime = &PII_speed_DWork.Derivative_RWORK.TimeStampB;
        lastU = &PII_speed_DWork.Derivative_RWORK.LastUAtTimeB;
      }
    }

    *lastTime = PII_speed_M->Timing.t[0];
    *lastU++ = PII_speed_B.Add8;
  }

  if (rtmIsMajorTimeStep(PII_speed_M)) {
    rt_ertODEUpdateContinuousStates(&PII_speed_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++PII_speed_M->Timing.clockTick0)) {
    ++PII_speed_M->Timing.clockTickH0;
  }

  PII_speed_M->Timing.t[0] = rtsiGetSolverStopTime(&PII_speed_M->solverInfo);
  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[1] == 0) {
    /* Update absolute timer for sample time: [0.0001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PII_speed_M->Timing.clockTick1)) {
      ++PII_speed_M->Timing.clockTickH1;
    }

    PII_speed_M->Timing.t[1] = PII_speed_M->Timing.clockTick1 *
      PII_speed_M->Timing.stepSize1 + PII_speed_M->Timing.clockTickH1 *
      PII_speed_M->Timing.stepSize1 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[2] == 0) {
    /* Update absolute timer for sample time: [0.0002s, 0.0s] */
    /* The "clockTick2" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick2"
     * and "Timing.stepSize2". Size of "clockTick2" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick2 and the high bits
     * Timing.clockTickH2. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PII_speed_M->Timing.clockTick2)) {
      ++PII_speed_M->Timing.clockTickH2;
    }

    PII_speed_M->Timing.t[2] = PII_speed_M->Timing.clockTick2 *
      PII_speed_M->Timing.stepSize2 + PII_speed_M->Timing.clockTickH2 *
      PII_speed_M->Timing.stepSize2 * 4294967296.0;
  }

  if (rtmIsMajorTimeStep(PII_speed_M) &&
      PII_speed_M->Timing.TaskCounters.TID[3] == 0) {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick3" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick3"
     * and "Timing.stepSize3". Size of "clockTick3" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick3 and the high bits
     * Timing.clockTickH3. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++PII_speed_M->Timing.clockTick3)) {
      ++PII_speed_M->Timing.clockTickH3;
    }

    PII_speed_M->Timing.t[3] = PII_speed_M->Timing.clockTick3 *
      PII_speed_M->Timing.stepSize3 + PII_speed_M->Timing.clockTickH3 *
      PII_speed_M->Timing.stepSize3 * 4294967296.0;
  }

  rate_scheduler();

  /* tid is required for a uniform function interface.
   * Argument tid is not used in the function. */
  UNUSED_PARAMETER(tid);
}

/* Derivatives for root system: '<Root>' */
void PII_speed_derivatives(void)
{
  /* Derivatives for Integrator: '<S9>/Integrator1' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( PII_speed_X.Integrator1_CSTATE <= (-2.0) );
    usat = ( PII_speed_X.Integrator1_CSTATE >= 2.0 );
    if ((!lsat && !usat) ||
        (lsat && (PII_speed_B.Add2 > 0)) ||
        (usat && (PII_speed_B.Add2 < 0)) ) {
      ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
        ->Integrator1_CSTATE = PII_speed_B.Add2;
    } else {
      /* in saturation */
      ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
        ->Integrator1_CSTATE = 0.0;
    }
  }

  /* Derivatives for Integrator: '<S11>/Continous-time integrator' */
  {
    boolean_T lsat;
    boolean_T usat;
    lsat = ( PII_speed_X.Continoustimeintegrator_CSTATE <= (-0.52) );
    usat = ( PII_speed_X.Continoustimeintegrator_CSTATE >= 0.52 );
    if (!PII_speed_B.LogicalOperator && ((!lsat && !usat) ||
         (lsat && (PII_speed_B.KI > 0)) ||
         (usat && (PII_speed_B.KI < 0))) ) {
      ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
        ->Continoustimeintegrator_CSTATE = PII_speed_B.KI;
    } else {
      /* in saturation or level reset is active */
      ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
        ->Continoustimeintegrator_CSTATE = 0.0;
    }
  }

  /* Derivatives for TransferFcn: '<S10>/Transfer Fcn1' */
  {
    ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
      ->TransferFcn1_CSTATE = PII_speed_B.ZOH1;
    ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
      ->TransferFcn1_CSTATE += (-100.0)*PII_speed_X.TransferFcn1_CSTATE;
  }

  /* Derivatives for TransferFcn: '<S10>/Transfer Fcn2' */
  {
    ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
      ->TransferFcn2_CSTATE = PII_speed_B.ZOH3;
    ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
      ->TransferFcn2_CSTATE += (-100.0)*PII_speed_X.TransferFcn2_CSTATE;
  }

  /* Derivatives for Integrator: '<S16>/Integrator2' */
  ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
    ->Integrator2_CSTATE = PII_speed_B.Tc;

  /* Derivatives for Integrator: '<S16>/Integrator1' */
  ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
    ->Integrator1_CSTATE_m = PII_speed_B.T1;

  /* Derivatives for Integrator: '<S16>/Integrator4' */
  ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
    ->Integrator4_CSTATE = PII_speed_B.Product3;

  /* Derivatives for Integrator: '<S16>/Integrator3' */
  ((StateDerivatives_PII_speed *) PII_speed_M->ModelData.derivs)
    ->Integrator3_CSTATE = PII_speed_B.T2;
}

/* Model initialize function */
void PII_speed_initialize(boolean_T firstTime)
{
  (void)firstTime;

  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)PII_speed_M, 0,
                sizeof(RT_MODEL_PII_speed));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&PII_speed_M->solverInfo,
                          &PII_speed_M->Timing.simTimeStep);
    rtsiSetTPtr(&PII_speed_M->solverInfo, &rtmGetTPtr(PII_speed_M));
    rtsiSetStepSizePtr(&PII_speed_M->solverInfo, &PII_speed_M->Timing.stepSize0);
    rtsiSetdXPtr(&PII_speed_M->solverInfo, &PII_speed_M->ModelData.derivs);
    rtsiSetContStatesPtr(&PII_speed_M->solverInfo,
                         &PII_speed_M->ModelData.contStates);
    rtsiSetNumContStatesPtr(&PII_speed_M->solverInfo,
      &PII_speed_M->Sizes.numContStates);
    rtsiSetErrorStatusPtr(&PII_speed_M->solverInfo, (&rtmGetErrorStatus
      (PII_speed_M)));
    rtsiSetRTModelPtr(&PII_speed_M->solverInfo, PII_speed_M);
  }

  rtsiSetSimTimeStep(&PII_speed_M->solverInfo, MAJOR_TIME_STEP);
  PII_speed_M->ModelData.intgData.f[0] = PII_speed_M->ModelData.odeF[0];
  PII_speed_M->ModelData.contStates = ((real_T *) &PII_speed_X);
  rtsiSetSolverData(&PII_speed_M->solverInfo, (void *)
                    &PII_speed_M->ModelData.intgData);
  rtsiSetSolverName(&PII_speed_M->solverInfo,"ode1");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = PII_speed_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;
    mdlTsMap[2] = 2;
    mdlTsMap[3] = 3;
    PII_speed_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    PII_speed_M->Timing.sampleTimes = (&PII_speed_M->Timing.sampleTimesArray[0]);
    PII_speed_M->Timing.offsetTimes = (&PII_speed_M->Timing.offsetTimesArray[0]);

    /* task periods */
    PII_speed_M->Timing.sampleTimes[0] = (0.0);
    PII_speed_M->Timing.sampleTimes[1] = (0.0001);
    PII_speed_M->Timing.sampleTimes[2] = (0.0002);
    PII_speed_M->Timing.sampleTimes[3] = (0.001);

    /* task offsets */
    PII_speed_M->Timing.offsetTimes[0] = (0.0);
    PII_speed_M->Timing.offsetTimes[1] = (0.0);
    PII_speed_M->Timing.offsetTimes[2] = (0.0);
    PII_speed_M->Timing.offsetTimes[3] = (0.0);
  }

  rtmSetTPtr(PII_speed_M, &PII_speed_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = PII_speed_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    mdlSampleHits[2] = 1;
    mdlSampleHits[3] = 1;
    PII_speed_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(PII_speed_M, -1);
  PII_speed_M->Timing.stepSize0 = 0.0001;
  PII_speed_M->Timing.stepSize1 = 0.0001;
  PII_speed_M->Timing.stepSize2 = 0.0002;
  PII_speed_M->Timing.stepSize3 = 0.001;
  PII_speed_M->solverInfoPtr = (&PII_speed_M->solverInfo);
  PII_speed_M->Timing.stepSize = (0.0001);
  rtsiSetFixedStepSize(&PII_speed_M->solverInfo, 0.0001);
  rtsiSetSolverMode(&PII_speed_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  PII_speed_M->ModelData.blockIO = ((void *) &PII_speed_B);
  (void) memset(((void *) &PII_speed_B), 0,
                sizeof(BlockIO_PII_speed));

  /* parameters */
  PII_speed_M->ModelData.defaultParam = ((real_T *)&PII_speed_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &PII_speed_X;
    PII_speed_M->ModelData.contStates = (x);
    (void) memset((void *)&PII_speed_X, 0,
                  sizeof(ContinuousStates_PII_speed));
  }

  /* states (dwork) */
  PII_speed_M->Work.dwork = ((void *) &PII_speed_DWork);
  (void) memset((void *)&PII_speed_DWork, 0,
                sizeof(D_Work_PII_speed));

  {
    /* user code (registration function declaration) */
    /*Call the macro that initializes the global TRC pointers
       inside the model initialization/registration function. */
    RTI_INIT_TRC_POINTERS();
  }

  PII_speed_PrevZCSigState.Continoustimeintegrator_Reset_Z = UNINITIALIZED_ZCSIG;
  PII_speed_PrevZCSigState.HC_Input_ZCE = UNINITIALIZED_ZCSIG;
}

/* Model terminate function */
void PII_speed_terminate(void)
{
  /* Terminate for S-Function (rti_commonblock): '<S6>/S-Function1' */

  /* dSPACE I/O Board DS1103 #1 Unit:PWM */
  ds1103_slave_dsp_pwm_output_set(0, SLVDSP1103_PWM_CH1_MSK,
    SLVDSP1103_PWM_TTL_LOW);

  /* flag = UNDEF */
  slaveDSPPwmStopFlagCh1 = 2;

  /* Terminate for S-Function (rti_commonblock): '<S6>/S-Function2' */

  /* dSPACE I/O Board DS1103 #1 Unit:PWM */
  ds1103_slave_dsp_pwm_duty_write(0, rti_slv1103_fcn_index[7], 0.5);
  ds1103_slave_dsp_pwm_start(0, SLVDSP1103_PWM_CH2_MSK);
}

/*========================================================================*
 * Start of GRT compatible call interface                                 *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  PII_speed_output(tid);
}

void MdlUpdate(int_T tid)
{
  PII_speed_update(tid);
}

void MdlInitializeSizes(void)
{
  PII_speed_M->Sizes.numContStates = (8);/* Number of continuous states */
  PII_speed_M->Sizes.numY = (0);       /* Number of model outputs */
  PII_speed_M->Sizes.numU = (0);       /* Number of model inputs */
  PII_speed_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  PII_speed_M->Sizes.numSampTimes = (4);/* Number of sample times */
  PII_speed_M->Sizes.numBlocks = (112);/* Number of blocks */
  PII_speed_M->Sizes.numBlockIO = (77);/* Number of block outputs */
  PII_speed_M->Sizes.numBlockPrms = (13);/* Sum of parameter "widths" */
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
  /* InitializeConditions for Integrator: '<S9>/Integrator1' */
  PII_speed_X.Integrator1_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S11>/Continous-time integrator' */
  PII_speed_X.Continoustimeintegrator_CSTATE = 0.0;

  /* InitializeConditions for Memory: '<S17>/Memory' */
  PII_speed_DWork.Memory_PreviousInput = FALSE;

  /* InitializeConditions for TransferFcn: '<S10>/Transfer Fcn1' */
  PII_speed_X.TransferFcn1_CSTATE = 0.0;

  /* InitializeConditions for TransferFcn: '<S10>/Transfer Fcn2' */
  PII_speed_X.TransferFcn2_CSTATE = 0.0;

  /* InitializeConditions for Derivative: '<S9>/Derivative' */
  PII_speed_DWork.Derivative_RWORK.TimeStampA = rtInf;
  PII_speed_DWork.Derivative_RWORK.TimeStampB = rtInf;

  /* InitializeConditions for Integrator: '<S16>/Integrator2' */
  PII_speed_X.Integrator2_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S16>/Integrator1' */
  PII_speed_X.Integrator1_CSTATE_m = 0.0;

  /* InitializeConditions for Integrator: '<S16>/Integrator4' */
  PII_speed_X.Integrator4_CSTATE = 0.0;

  /* InitializeConditions for Integrator: '<S16>/Integrator3' */
  PII_speed_X.Integrator3_CSTATE = 0.0;
}

void MdlStart(void)
{
  /* Start for TransportDelay: '<S7>/TD' */
  {
    real_T *pBuffer = &PII_speed_DWork.TD_RWORK.TUbufferArea[0];
    PII_speed_DWork.TD_IWORK.Tail = 0;
    PII_speed_DWork.TD_IWORK.Head = 0;
    PII_speed_DWork.TD_IWORK.Last = 0;
    PII_speed_DWork.TD_IWORK.CircularBufSize = 60000;
    pBuffer[0] = 0.0;
    pBuffer[60000] = PII_speed_M->Timing.t[0];
    PII_speed_DWork.TD_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    PII_speed_DWork.TD_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[60000];
  }

  /* Start for TransportDelay: '<S7>/TD1' */
  {
    real_T *pBuffer = &PII_speed_DWork.TD1_RWORK.TUbufferArea[0];
    PII_speed_DWork.TD1_IWORK.Tail = 0;
    PII_speed_DWork.TD1_IWORK.Head = 0;
    PII_speed_DWork.TD1_IWORK.Last = 0;
    PII_speed_DWork.TD1_IWORK.CircularBufSize = 60000;
    pBuffer[0] = 0.0;
    pBuffer[60000] = PII_speed_M->Timing.t[0];
    PII_speed_DWork.TD1_PWORK.TUbufferPtrs[0] = (void *) &pBuffer[0];
    PII_speed_DWork.TD1_PWORK.TUbufferPtrs[1] = (void *) &pBuffer[60000];
  }

  /* Start for S-Function (rti_commonblock): '<S6>/S-Function1' */

  /* dSPACE I/O Board DS1103 #1 Unit:PWM */
  PII_speed_DWork.SFunction1_IWORK[0] = 0;

  /* Start for S-Function (rti_commonblock): '<S6>/S-Function2' */

  /* dSPACE I/O Board DS1103 #1 Unit:PWM */
  PII_speed_DWork.SFunction2_IWORK[1] = 0;
  MdlInitialize();
}

void MdlTerminate(void)
{
  PII_speed_terminate();
}

RT_MODEL_PII_speed *PII_speed(void)
{
  PII_speed_initialize(1);
  return PII_speed_M;
}

/*========================================================================*
 * End of GRT compatible call interface                                   *
 *========================================================================*/
