/*
 * File: genAnalysisLogic.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 04:14:33
 */

#ifndef GENANALYSISLOGIC_H
#define GENANALYSISLOGIC_H

/* Include Files */
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void genAnalysisLogic(const emxArray_real_T *x, double Fs,
                             emxArray_real_T *t, double freq[513],
                             double fftMagnitude[513],
                             emxArray_real_T *stftTime, double stftFreq[513],
                             emxArray_real_T *stftMagnitude);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for genAnalysisLogic.h
 *
 * [EOF]
 */
