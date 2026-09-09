/*
 * File: STFTSysObj.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 03:03:38
 */

/* Include Files */
#include "STFTSysObj.h"
#include "genAnalysisLogic_internal_types.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : double in1[1024]
 *                const emxArray_real_T *in2
 *                const dsp_STFT *in3
 * Return Type  : void
 */
void binary_expand_op(double in1[1024], const emxArray_real_T *in2,
                      const dsp_STFT *in3)
{
  const double *in2_data;
  int i;
  int stride_0_0;
  in2_data = in2->data;
  stride_0_0 = (in2->size[0] != 1);
  for (i = 0; i < 1024; i++) {
    in1[i] = in2_data[i * stride_0_0] * in3->pObj.pWindow[i];
  }
}

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
