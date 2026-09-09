/*
 * File: genAnalysisLogic_terminate.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

/* Include Files */
#include "genAnalysisLogic_terminate.h"
#include "genAnalysisLogic_data.h"
#include "rt_nonfinite.h"
#include "omp.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_terminate(void)
{
  omp_destroy_nest_lock(&genAnalysisLogic_nestLockGlobal);
  isInitialized_genAnalysisLogic = false;
}

/*
 * File trailer for genAnalysisLogic_terminate.c
 *
 * [EOF]
 */
