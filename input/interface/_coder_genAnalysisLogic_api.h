/*
 * File: _coder_genAnalysisLogic_api.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:34:56
 */

#ifndef _CODER_GENANALYSISLOGIC_API_H
#define _CODER_GENANALYSISLOGIC_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  real_T *data;
  int32_T *size;
  int32_T allocatedSize;
  int32_T numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void genAnalysisLogic(const emxArray_real_T *x, real_T Fs, emxArray_real_T *t,
                      emxArray_real_T *freq, emxArray_real_T *fftMagnitude,
                      real_T stftTime[1845], real_T stftFreq[513],
                      emxArray_real_T *stftMagnitude);

void genAnalysisLogic_api(const mxArray *const prhs[2], int32_T nlhs,
                          const mxArray *plhs[6]);

void genAnalysisLogic_atexit(void);

void genAnalysisLogic_initialize(void);

void genAnalysisLogic_terminate(void);

void genAnalysisLogic_xil_shutdown(void);

void genAnalysisLogic_xil_terminate(void);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for _coder_genAnalysisLogic_api.h
 *
 * [EOF]
 */
