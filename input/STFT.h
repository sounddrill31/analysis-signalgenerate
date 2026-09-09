/*
 * File: STFT.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:49:41
 */

#ifndef STFT_H
#define STFT_H

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
void STFT_STFT(dsp_STFT *obj);

void STFT_step(dsp_STFT *obj, const emxArray_real_T *u, emxArray_creal_T *y);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for STFT.h
 *
 * [EOF]
 */
