/*
 * File: sawtooth.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Aug-2026 22:16:07
 */

/* Include Files */
#include "sawtooth.h"
#include "genTriangleLogic_emxutil.h"
#include "genTriangleLogic_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <float.h>
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *t
 *                emxArray_real_T *y
 * Return Type  : void
 */
void sawtooth(const emxArray_real_T *t, emxArray_real_T *y)
{
  const double *t_data;
  double *y_data;
  int i;
  int idx;
  int loop_ub;
  t_data = t->data;
  loop_ub = t->size[1];
  i = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = t->size[1];
  emxEnsureCapacity_real_T(y, i);
  y_data = y->data;
  for (idx = 0; idx < loop_ub; idx++) {
    double d;
    double varargout_1;
    d = t_data[idx];
    if (rtIsNaN(d) || rtIsInf(d)) {
      varargout_1 = rtNaN;
    } else {
      varargout_1 = fabs(d / 6.283185307179586);
      if (!(fabs(varargout_1 - floor(varargout_1 + 0.5)) >
            DBL_EPSILON * varargout_1)) {
        varargout_1 = 0.0 * d;
      } else {
        varargout_1 = fmod(d, 6.283185307179586);
      }
    }
    varargout_1 *= 0.15915494309189535;
    if (varargout_1 > 0.0) {
      if (varargout_1 > 0.5) {
        y_data[idx] = (((-(double)(d < 0.0) - varargout_1) + 1.0) - 0.25) * 4.0;
      } else {
        y_data[idx] = (((double)(d < 0.0) + varargout_1) - 0.25) * 4.0;
      }
    } else if (varargout_1 < 0.0) {
      if (varargout_1 < -0.5) {
        y_data[idx] = (((double)(d < 0.0) + varargout_1) - 0.25) * 4.0;
      } else {
        y_data[idx] = (((-(double)(d < 0.0) - varargout_1) + 1.0) - 0.25) * 4.0;
      }
    } else {
      y_data[idx] = (varargout_1 - 0.25) * 4.0;
    }
  }
}

/*
 * File trailer for sawtooth.c
 *
 * [EOF]
 */
