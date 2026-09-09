/*
 * File: AsyncBufferSysObj.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 03:03:38
 */

/* Include Files */
#include "AsyncBufferSysObj.h"
#include "genAnalysisLogic_internal_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : c_dsp_internal_codegen_AsyncBuf *obj
 * Return Type  : void
 */
void b_handle_matlabCodegenDestructo(c_dsp_internal_codegen_AsyncBuf *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete) {
        obj->ReadPointer = 1;
        obj->WritePointer = 2;
        obj->CumulativeOverrun = 0;
        obj->CumulativeUnderrun = 0;
      }
    }
  }
}

/*
 * File trailer for AsyncBufferSysObj.c
 *
 * [EOF]
 */
