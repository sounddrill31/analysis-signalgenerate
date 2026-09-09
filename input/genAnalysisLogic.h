/*
 * File: genAnalysisLogic.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
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
extern void genAnalysisLogic(double Fs, emxArray_real_T *t,
                             emxArray_real_T *freq,
                             emxArray_real_T *fftMagnitude, double stftTime[31],
                             double stftFreq[513],
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
