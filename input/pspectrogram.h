/*
 * File: pspectrogram.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
 */

#ifndef PSPECTROGRAM_H
#define PSPECTROGRAM_H

/* Include Files */
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void formatSpectrogram(const emxArray_creal_T *y, double Fs,
                       emxArray_creal_T *yout, double fout[513]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for pspectrogram.h
 *
 * [EOF]
 */
