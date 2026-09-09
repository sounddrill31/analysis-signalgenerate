/*
 * File: minOrMax.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Aug-2026 22:16:07
 */

/* Include Files */
#include "minOrMax.h"
#include "genTriangleLogic_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 * Return Type  : double
 */
double maximum(const emxArray_real_T *x)
{
  const double *x_data;
  double ex;
  int b_k;
  int last;
  x_data = x->data;
  last = x->size[1];
  if (x->size[1] <= 2) {
    if (x->size[1] == 1) {
      ex = x_data[0];
    } else {
      ex = x_data[x->size[1] - 1];
      if (!(x_data[0] < ex) && (!rtIsNaN(x_data[0]) || rtIsNaN(ex))) {
        ex = x_data[0];
      }
    }
  } else {
    int idx;
    if (!rtIsNaN(x_data[0])) {
      idx = 1;
    } else {
      int k;
      boolean_T exitg1;
      idx = 0;
      k = 2;
      exitg1 = false;
      while (!exitg1 && (k <= last)) {
        if (!rtIsNaN(x_data[k - 1])) {
          idx = k;
          exitg1 = true;
        } else {
          k++;
        }
      }
    }
    if (idx == 0) {
      ex = x_data[0];
    } else {
      ex = x_data[idx - 1];
      for (b_k = idx + 1; b_k <= last; b_k++) {
        double d;
        d = x_data[b_k - 1];
        if (ex < d) {
          ex = d;
        }
      }
    }
  }
  return ex;
}

/*
 * File trailer for minOrMax.c
 *
 * [EOF]
 */
