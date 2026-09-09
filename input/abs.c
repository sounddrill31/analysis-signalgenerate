/*
 * File: abs.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

/* Include Files */
#include "abs.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T x[945176]
 *                double y[945176]
 * Return Type  : void
 */
void b_abs(const creal_T x[945176], double y[945176])
{
  double a;
  double b;
  int k;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(b, a)

  for (k = 0; k < 945176; k++) {
    a = fabs(x[k].re);
    b = fabs(x[k].im);
    if (a < b) {
      a /= b;
      y[k] = b * sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      y[k] = a * sqrt(b * b + 1.0);
    } else if (rtIsNaN(b)) {
      y[k] = rtNaN;
    } else {
      y[k] = a * 1.4142135623730951;
    }
  }
}

/*
 * Arguments    : const creal_T x[946485]
 *                double y[946485]
 * Return Type  : void
 */
void c_abs(const creal_T x[946485], double y[946485])
{
  double a;
  double b;
  int k;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(b, a)

  for (k = 0; k < 946485; k++) {
    a = fabs(x[k].re);
    b = fabs(x[k].im);
    if (a < b) {
      a /= b;
      y[k] = b * sqrt(a * a + 1.0);
    } else if (a > b) {
      b /= a;
      y[k] = a * sqrt(b * b + 1.0);
    } else if (rtIsNaN(b)) {
      y[k] = rtNaN;
    } else {
      y[k] = a * 1.4142135623730951;
    }
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
