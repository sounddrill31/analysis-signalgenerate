/*
 * File: colon.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:49:41
 */

/* Include Files */
#include "colon.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"

/* Function Definitions */
/*
 * Arguments    : int a
 *                int b
 *                emxArray_int32_T *y
 * Return Type  : void
 */
void b_eml_integer_colon_dispatcher(int a, int b, emxArray_int32_T *y)
{
  int k;
  int n;
  int yk;
  int *y_data;
  if (b < a) {
    n = 0;
  } else {
    unsigned int nm1;
    if ((a < 0) && (b >= 0)) {
      nm1 = (unsigned int)b - (unsigned int)a;
    } else {
      nm1 = (unsigned int)(b - a);
    }
    n = (int)nm1 + 1;
  }
  yk = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_int32_T(y, yk);
  y_data = y->data;
  if (n > 0) {
    y_data[0] = a;
    yk = a;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }
}

/*
 * Arguments    : int a
 *                emxArray_int32_T *y
 * Return Type  : void
 */
void eml_integer_colon_dispatcher(int a, emxArray_int32_T *y)
{
  int k;
  int n;
  int yk;
  int *y_data;
  if (a > 1025) {
    n = 0;
  } else {
    unsigned int nm1;
    if (a < 0) {
      nm1 = 1025U - (unsigned int)a;
    } else {
      nm1 = (unsigned int)(1025 - a);
    }
    n = (int)nm1 + 1;
  }
  yk = y->size[0] * y->size[1];
  y->size[0] = 1;
  y->size[1] = n;
  emxEnsureCapacity_int32_T(y, yk);
  y_data = y->data;
  if (n > 0) {
    y_data[0] = a;
    yk = a;
    for (k = 2; k <= n; k++) {
      yk++;
      y_data[k - 1] = yk;
    }
  }
}

/*
 * File trailer for colon.c
 *
 * [EOF]
 */
