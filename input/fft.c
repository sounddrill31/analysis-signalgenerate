/*
 * File: fft.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
 */

/* Include Files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : emxArray_creal_T *y
 * Return Type  : void
 */
void fft(emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *sintab;
  double costab1q[4097];
  double *costab_data;
  double *sintab_data;
  int i;
  int k;
  emxInit_real_T(&sintab, 1);
  i = sintab->size[0];
  sintab->size[0] = 8193;
  emxEnsureCapacity_real_T(sintab, i);
  sintab_data = sintab->data;
  emxInit_real_T(&costab, 1);
  i = costab->size[0];
  costab->size[0] = 8193;
  emxEnsureCapacity_real_T(costab, i);
  costab_data = costab->data;
  i = y->size[0];
  y->size[0] = 16384;
  emxEnsureCapacity_creal_T(y, i);
  costab1q[0] = 1.0;
  for (k = 0; k < 2048; k++) {
    costab1q[k + 1] = cos(0.0003834951969714103 * ((double)k + 1.0));
  }
  for (k = 0; k < 2047; k++) {
    costab1q[k + 2049] =
        sin(0.0003834951969714103 * (4096.0 - ((double)k + 2049.0)));
  }
  costab1q[4096] = 0.0;
  costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
  for (k = 0; k < 4096; k++) {
    double costab_tmp;
    double sintab_tmp;
    costab_tmp = costab1q[k + 1];
    costab_data[k + 1] = costab_tmp;
    sintab_tmp = -costab1q[4095 - k];
    sintab_data[k + 1] = sintab_tmp;
    costab_data[k + 4097] = sintab_tmp;
    sintab_data[k + 4097] = -costab_tmp;
  }
  c_FFTImplementationCallback_doH(y, costab, sintab);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
