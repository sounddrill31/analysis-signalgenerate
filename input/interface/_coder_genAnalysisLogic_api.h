/*
 * File: _coder_genAnalysisLogic_api.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

#ifndef _CODER_GENANALYSISLOGIC_API_H
#define _CODER_GENANALYSISLOGIC_API_H

/* Include Files */
#include "emlrt.h"
#include "mex.h"
#include "tmwtypes.h"
#include <string.h>

/* Variable Declarations */
extern emlrtCTX emlrtRootTLSGlobal;
extern emlrtContext emlrtContextGlobal;

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void genAnalysisLogic(const real_T x[945176], real_T Fs, real_T t[945176],
                      real_T freq[472589], real_T fftMagnitude[472589],
                      real_T stftTime[1845], real_T stftFreq[513],
                      real_T stftMagnitude[946485]);

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
