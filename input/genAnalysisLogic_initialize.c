/*
 * File: genAnalysisLogic_initialize.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:49:41
 */

/* Include Files */
#include "genAnalysisLogic_initialize.h"
#include "genAnalysisLogic.h"
#include "genAnalysisLogic_data.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_initialize(void)
{
  genAnalysisLogic_new();
  genAnalysisLogic_init();
  isInitialized_genAnalysisLogic = true;
}

/*
 * File trailer for genAnalysisLogic_initialize.c
 *
 * [EOF]
 */
