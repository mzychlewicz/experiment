/* Include files */

#include "PII_speed_sfun.h"
#include "c1_PII_speed.h"

/* Type Definitions */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */
int32_T _sfEvent_;
uint32_T _PII_speedMachineNumber_;
real_T _sfTime_;

/* Function Declarations */

/* Function Definitions */
void PII_speed_initializer(void)
{
  _sfEvent_ = CALL_EVENT;
}

void PII_speed_terminator(void)
{
}

/* SFunction Glue Code */
unsigned int sf_PII_speed_method_dispatcher(SimStruct *simstructPtr, unsigned
  int chartFileNumber, const char* specsCksum, int_T method, void *data)
{
  if (chartFileNumber==1) {
    c1_PII_speed_method_dispatcher(simstructPtr, method, data);
    return 1;
  }

  return 0;
}

unsigned int sf_PII_speed_process_check_sum_call( int nlhs, mxArray * plhs[],
  int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[20];
  if (nrhs<1 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the checksum */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"sf_get_check_sum"))
    return 0;
  plhs[0] = mxCreateDoubleMatrix( 1,4,mxREAL);
  if (nrhs>1 && mxIsChar(prhs[1])) {
    mxGetString(prhs[1], commandName,sizeof(commandName)/sizeof(char));
    commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
    if (!strcmp(commandName,"machine")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(239856614U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1182721406U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(819434684U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(664010674U);
    } else if (!strcmp(commandName,"exportedFcn")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0U);
    } else if (!strcmp(commandName,"makefile")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(2952896346U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(3804250792U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4220254610U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3536995612U);
    } else if (nrhs==3 && !strcmp(commandName,"chart")) {
      unsigned int chartFileNumber;
      chartFileNumber = (unsigned int)mxGetScalar(prhs[2]);
      switch (chartFileNumber) {
       case 1:
        {
          extern void sf_c1_PII_speed_get_check_sum(mxArray *plhs[]);
          sf_c1_PII_speed_get_check_sum(plhs);
          break;
        }

       default:
        ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(0.0);
        ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(0.0);
      }
    } else if (!strcmp(commandName,"target")) {
      ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3164472282U);
      ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(2172149039U);
      ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(3846579528U);
      ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(1884100239U);
    } else {
      return 0;
    }
  } else {
    ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(3919200538U);
    ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(778575110U);
    ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(4081147500U);
    ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(3445104452U);
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_PII_speed_autoinheritance_info( int nlhs, mxArray * plhs[], int
  nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[32];
  if (nrhs<2 || !mxIsChar(prhs[0]) )
    return 0;

  /* Possible call to get the autoinheritance_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_autoinheritance_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern mxArray *sf_c1_PII_speed_get_autoinheritance_info(void);
        plhs[0] = sf_c1_PII_speed_get_autoinheritance_info();
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

unsigned int sf_PII_speed_get_eml_resolved_functions_info( int nlhs, mxArray *
  plhs[], int nrhs, const mxArray * prhs[] )
{

#ifdef MATLAB_MEX_FILE

  char commandName[64];
  if (nrhs<2 || !mxIsChar(prhs[0]))
    return 0;

  /* Possible call to get the get_eml_resolved_functions_info */
  mxGetString(prhs[0], commandName,sizeof(commandName)/sizeof(char));
  commandName[(sizeof(commandName)/sizeof(char)-1)] = '\0';
  if (strcmp(commandName,"get_eml_resolved_functions_info"))
    return 0;

  {
    unsigned int chartFileNumber;
    chartFileNumber = (unsigned int)mxGetScalar(prhs[1]);
    switch (chartFileNumber) {
     case 1:
      {
        extern const mxArray *sf_c1_PII_speed_get_eml_resolved_functions_info
          (void);
        mxArray *persistentMxArray = (mxArray *)
          sf_c1_PII_speed_get_eml_resolved_functions_info();
        plhs[0] = mxDuplicateArray(persistentMxArray);
        mxDestroyArray(persistentMxArray);
        break;
      }

     default:
      plhs[0] = mxCreateDoubleMatrix(0,0,mxREAL);
    }
  }

  return 1;

#else

  return 0;

#endif

}

void PII_speed_debug_initialize(void)
{
  _PII_speedMachineNumber_ = sf_debug_initialize_machine("PII_speed","sfun",0,1,
    0,0,0);
  sf_debug_set_machine_event_thresholds(_PII_speedMachineNumber_,0,0);
  sf_debug_set_machine_data_thresholds(_PII_speedMachineNumber_,0);
}

void PII_speed_register_exported_symbols(SimStruct* S)
{
}
