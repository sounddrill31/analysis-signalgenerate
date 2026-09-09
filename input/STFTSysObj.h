/*
 * File: STFTSysObj.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 03:03:38
 */

#ifndef STFTSYSOBJ_H
#define STFTSYSOBJ_H

/* Include Files */
#include "genAnalysisLogic_internal_types.h"
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void binary_expand_op(double in1[1024], const emxArray_real_T *in2,
                      const dsp_STFT *in3);

void handle_matlabCodegenDestructor(dsp_internal_codegen_STFTSysObj *obj);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for STFTSysObj.h
 *
 * [EOF]
 */
