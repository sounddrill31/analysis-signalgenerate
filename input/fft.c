/*
 * File: fft.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:22:23
 */

/* Include Files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, emxArray_creal_T *y)
{
  emxArray_real_T *costab;
  emxArray_real_T *costab1q;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  double b_sintabinv_tmp;
  double sintabinv_tmp;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int b_k;
  int c_k;
  int i;
  int k;
  emxInit_real_T(&costab1q, 1);
  i = costab1q->size[0];
  costab1q->size[0] = 524289;
  emxEnsureCapacity_real_T(costab1q, i);
  costab1q_data = costab1q->data;
  emxInit_real_T(&sintabinv, 1);
  i = sintabinv->size[0];
  sintabinv->size[0] = 1048577;
  emxEnsureCapacity_real_T(sintabinv, i);
  sintabinv_data = sintabinv->data;
  emxInit_real_T(&sintab, 1);
  i = sintab->size[0];
  sintab->size[0] = 1048577;
  emxEnsureCapacity_real_T(sintab, i);
  sintab_data = sintab->data;
  emxInit_real_T(&costab, 1);
  i = costab->size[0];
  costab->size[0] = 1048577;
  emxEnsureCapacity_real_T(costab, i);
  costab_data = costab->data;
  i = y->size[0];
  y->size[0] = 945176;
  emxEnsureCapacity_creal_T(y, i);
  costab1q_data[0] = 1.0;
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (k = 0; k < 262144; k++) {
    costab1q_data[k + 1] = cos(2.996056226339143E-6 * ((double)k + 1.0));
  }
#pragma omp parallel for num_threads(omp_get_max_threads())

  for (b_k = 0; b_k < 262143; b_k++) {
    costab1q_data[b_k + 262145] =
        sin(2.996056226339143E-6 * (524288.0 - ((double)b_k + 262145.0)));
  }
  costab1q_data[524288] = 0.0;
  costab_data[0] = 1.0;
  sintab_data[0] = 0.0;
#pragma omp parallel for num_threads(omp_get_max_threads()) private(           \
        sintabinv_tmp, b_sintabinv_tmp)

  for (c_k = 0; c_k < 524288; c_k++) {
    sintabinv_tmp = costab1q_data[524287 - c_k];
    sintabinv_data[c_k + 1] = sintabinv_tmp;
    b_sintabinv_tmp = costab1q_data[c_k + 1];
    sintabinv_data[c_k + 524289] = b_sintabinv_tmp;
    costab_data[c_k + 1] = b_sintabinv_tmp;
    sintab_data[c_k + 1] = -sintabinv_tmp;
    costab_data[c_k + 524289] = -sintabinv_tmp;
    sintab_data[c_k + 524289] = -b_sintabinv_tmp;
  }
  emxFree_real_T(&costab1q);
  c_FFTImplementationCallback_dob(x, costab, sintab, sintabinv, y);
  emxFree_real_T(&sintabinv);
  emxFree_real_T(&sintab);
  emxFree_real_T(&costab);
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
