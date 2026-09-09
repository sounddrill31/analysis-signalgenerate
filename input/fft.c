/*
 * File: fft.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

/* Include Files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const double x[945176]
 *                creal_T y[945176]
 * Return Type  : void
 */
void fft(const double x[945176], creal_T y[945176])
{
  static double costab[1048577];
  static double sintab[1048577];
  static double sintabinv[1048577];
  static double costab1q[524289];
  double b_sintabinv_tmp;
  double sintabinv_tmp;
  int b_k;
  int c_k;
  int k;
  costab1q[0] = 1.0;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (k = 0; k < 262144; k++) {
    costab1q[k + 1] = cos(2.996056226339143E-6 * ((double)k + 1.0));
  }
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (b_k = 0; b_k < 262143; b_k++) {
    costab1q[b_k + 262145] =
        sin(2.996056226339143E-6 * (524288.0 - ((double)b_k + 262145.0)));
  }
  costab1q[524288] = 0.0;
  costab[0] = 1.0;
  sintab[0] = 0.0;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        sintabinv_tmp, b_sintabinv_tmp)

  for (c_k = 0; c_k < 524288; c_k++) {
    sintabinv_tmp = costab1q[524287 - c_k];
    sintabinv[c_k + 1] = sintabinv_tmp;
    b_sintabinv_tmp = costab1q[c_k + 1];
    sintabinv[c_k + 524289] = b_sintabinv_tmp;
    costab[c_k + 1] = b_sintabinv_tmp;
    sintab[c_k + 1] = -sintabinv_tmp;
    costab[c_k + 524289] = -sintabinv_tmp;
    sintab[c_k + 524289] = -b_sintabinv_tmp;
  }
  c_FFTImplementationCallback_dob(x, costab, sintab, sintabinv, y);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
