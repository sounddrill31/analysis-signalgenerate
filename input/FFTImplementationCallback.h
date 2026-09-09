/*
 * File: FFTImplementationCallback.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

#ifndef FFTIMPLEMENTATIONCALLBACK_H
#define FFTIMPLEMENTATIONCALLBACK_H

/* Include Files */
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
void c_FFTImplementationCallback_dob(const double x[945176],
                                     const double costab[1048577],
                                     const double sintab[1048577],
                                     const double sintabinv[1048577],
                                     creal_T y[945176]);

void f_FFTImplementationCallback_r2b(const double x[1889280],
                                     creal_T y[1889280]);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for FFTImplementationCallback.h
 *
 * [EOF]
 */
