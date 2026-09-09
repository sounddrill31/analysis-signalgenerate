/*
 * File: STFTSysObj.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
 */

/* Include Files */
#include "STFTSysObj.h"
#include "genAnalysisLogic_internal_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : dsp_internal_codegen_STFTSysObj *obj
 * Return Type  : void
 */
void handle_matlabCodegenDestructor(dsp_internal_codegen_STFTSysObj *obj)
{
  if (!obj->matlabCodegenIsDeleted) {
    obj->matlabCodegenIsDeleted = true;
    if (obj->isInitialized == 1) {
      obj->isInitialized = 2;
      if (obj->isSetupComplete && (obj->pBuff.pBuffer.isInitialized == 1)) {
        obj->pBuff.pBuffer.isInitialized = 2;
        if (obj->pBuff.pBuffer.isSetupComplete) {
          obj->pBuff.pBuffer.ReadPointer = 1;
          obj->pBuff.pBuffer.WritePointer = 2;
          obj->pBuff.pBuffer.CumulativeOverrun = 0;
          obj->pBuff.pBuffer.CumulativeUnderrun = 0;
        }
      }
    }
  }
}

/*
 * File trailer for STFTSysObj.c
 *
 * [EOF]
 */
