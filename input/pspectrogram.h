/*
 * File: pspectrogram.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

#ifndef PSPECTROGRAM_H
#define PSPECTROGRAM_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void formatSpectrogram(const creal_T y[1889280], double Fs,
                       creal_T yout[946485], double fout[513]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for pspectrogram.h
 *
 * [EOF]
 */
