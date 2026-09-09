/*
 * File: abs.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Aug-2026 22:16:07
 */

/* Include Files */
#include "abs.h"
#include "genTriangleLogic_emxutil.h"
#include "genTriangleLogic_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_real_T *y
 * Return Type  : void
 */
void b_abs(const emxArray_real_T *x, emxArray_real_T *y)
{
  const double *x_data;
  double *y_data;
  int i;
  int k;
  int nx;
  x_data = x->data;
  nx = x->size[1];
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = x->size[1];
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  for (k = 0; k < nx; k++) {
    y_data[k] = fabs(x_data[k]);
  }
}

/*
 * File trailer for abs.c
 *
 * [EOF]
 */
