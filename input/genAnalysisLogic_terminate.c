/*
 * File: genAnalysisLogic_terminate.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
 */

/* Include Files */
#include "genAnalysisLogic_terminate.h"
#include "genAnalysisLogic.h"
#include "genAnalysisLogic_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_terminate(void)
{
  genAnalysisLogic_delete();
  isInitialized_genAnalysisLogic = false;
}

/*
 * File trailer for genAnalysisLogic_terminate.c
 *
 * [EOF]
 */
