/*
 * File: main.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
 */

/*************************************************************************/
/* This automatically generated example C main file shows how to call    */
/* entry-point functions that MATLAB Coder generated. You must customize */
/* this file for your application. Do not modify this file directly.     */
/* Instead, make a copy of this file, modify it, and integrate it into   */
/* your development environment.                                         */
/*                                                                       */
/* This file initializes entry-point function arguments to a default     */
/* size and value before calling the entry-point functions. It does      */
/* not store or use any values returned from the entry-point functions.  */
/* If necessary, it does pre-allocate memory for returned values.        */
/* You can use this file as a starting point for a main function that    */
/* you can deploy in your application.                                   */
/*                                                                       */
/* After you copy the file, and before you deploy it, you must make the  */
/* following changes:                                                    */
/* * For variable-size function arguments, change the example sizes to   */
/* the sizes that your application requires.                             */
/* * Change the example values of function arguments to the values that  */
/* your application requires.                                            */
/* * If the entry-point functions return values, store these values or   */
/* otherwise use them as required by your application.                   */
/*                                                                       */
/*************************************************************************/

/* Include Files */
#include "main.h"
#include "genAnalysisLogic.h"
#include "genAnalysisLogic_emxAPI.h"
#include "genAnalysisLogic_initialize.h"
#include "genAnalysisLogic_terminate.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"

/* Function Declarations */
static double argInit_real_T(void);

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : double
 */
static double argInit_real_T(void)
{
  return 0.0;
}

/*
 * Arguments    : int argc
 *                char **argv
 * Return Type  : int
 */
int main(int argc, char **argv)
{
  (void)argc;
  (void)argv;
  /* Initialize the application.
You do not need to do this more than one time. */
  genAnalysisLogic_initialize();
  /* Invoke the entry-point functions.
You can call entry-point functions multiple times. */
  main_genAnalysisLogic();
  /* Terminate the application.
You do not need to do this more than one time. */
  genAnalysisLogic_terminate();
  return 0;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void main_genAnalysisLogic(void)
{
  emxArray_real_T *fftMagnitude;
  emxArray_real_T *freq;
  emxArray_real_T *stftMagnitude;
  emxArray_real_T *t;
  double stftFreq[513];
  double stftTime[32];
  /* Initialize function 'genAnalysisLogic' input arguments. */
  /* Call the entry-point 'genAnalysisLogic'. */
  emxInitArray_real_T(&t, 1);
  emxInitArray_real_T(&freq, 1);
  emxInitArray_real_T(&fftMagnitude, 1);
  emxInitArray_real_T(&stftMagnitude, 1);
  genAnalysisLogic(argInit_real_T(), t, freq, fftMagnitude, stftTime, stftFreq,
                   stftMagnitude);
  emxDestroyArray_real_T(t);
  emxDestroyArray_real_T(freq);
  emxDestroyArray_real_T(fftMagnitude);
  emxDestroyArray_real_T(stftMagnitude);
}

/*
 * File trailer for main.c
 *
 * [EOF]
 */
