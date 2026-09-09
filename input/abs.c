/*
 * File: abs.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 03:30:33
 */

/* Include Files */
#include "abs.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T x[513]
 *                double y[513]
 * Return Type  : void
 */
void b_abs(const creal_T x[513], double y[513])
{
  int k;
  for (k = 0; k < 513; k++) {
    double a;
    double b;
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
