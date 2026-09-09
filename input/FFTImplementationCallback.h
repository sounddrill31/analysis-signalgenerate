/*
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_doH(emxArray_creal_T *y,
                                     const emxArray_real_T *costab,
                                     const emxArray_real_T *sintab);

void d_FFTImplementationCallback_doH(const double x[1024], creal_T y[1024]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
