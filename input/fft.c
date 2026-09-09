/*
 * File: fft.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 16:05:27
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
 * Arguments    : const emxArray_real_T *x
 *                emxArray_creal_T *y
 * Return Type  : void
 */
void fft(const emxArray_real_T *x, emxArray_creal_T *y)
{
  emxArray_creal_T *yCol;
  emxArray_real_T b_x;
  emxArray_real_T *costab;
  emxArray_real_T *costab1q;
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *yCol_data;
  creal_T *y_data;
  const double *x_data;
  double *costab1q_data;
  double *costab_data;
  double *sintab_data;
  double *sintabinv_data;
  int c_x;
  int d_x;
  int k;
  x_data = x->data;
  if (x->size[1] == 0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    double e;
    int b_n;
    int b_n2;
    int n;
    int n2;
    int nd2;
    boolean_T useRadix2;
    useRadix2 =
        (((unsigned int)x->size[1] & (unsigned int)(x->size[1] - 1)) == 0U);
    n = 1;
    if (useRadix2) {
      nd2 = x->size[1];
    } else {
      n2 = (x->size[1] + x->size[1]) - 1;
      nd2 = 31;
      if (n2 <= 1) {
        nd2 = 0;
      } else {
        boolean_T exitg1;
        n = 0;
        exitg1 = false;
        while (!exitg1 && (nd2 - n > 1)) {
          b_n2 = (n + nd2) >> 1;
          b_n = 1 << b_n2;
          if (b_n == n2) {
            nd2 = b_n2;
            exitg1 = true;
          } else if (b_n > n2) {
            nd2 = b_n2;
          } else {
            n = b_n2;
          }
        }
      }
      if (nd2 >= 0) {
        if (nd2 <= 31) {
          n = 1 << nd2;
        } else {
          n = 0;
        }
      } else {
        n = 0;
      }
      nd2 = n;
    }
    e = 6.283185307179586 / (double)nd2;
    n2 = nd2 / 2 / 2;
    emxInit_real_T(&costab1q, 2);
    nd2 = costab1q->size[0] * costab1q->size[1];
    costab1q->size[0] = 1;
    costab1q->size[1] = n2 + 1;
    emxEnsureCapacity_real_T(costab1q, nd2);
    costab1q_data = costab1q->data;
    costab1q_data[0] = 1.0;
    nd2 = n2 / 2;
    for (k = 0; k < nd2; k++) {
      costab1q_data[k + 1] = cos(e * ((double)k + 1.0));
    }
    for (k = nd2 + 1; k < n2; k++) {
      costab1q_data[k] = sin(e * (double)(n2 - k));
    }
    costab1q_data[n2] = 0.0;
    emxInit_creal_T(&yCol, 1);
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    if (!useRadix2) {
      b_n = costab1q->size[1] - 1;
      n2 = (costab1q->size[1] - 1) << 1;
      nd2 = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(costab, nd2);
      costab_data = costab->data;
      nd2 = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(sintab, nd2);
      sintab_data = sintab->data;
      costab_data[0] = 1.0;
      sintab_data[0] = 0.0;
      nd2 = sintabinv->size[0] * sintabinv->size[1];
      sintabinv->size[0] = 1;
      sintabinv->size[1] = n2 + 1;
      emxEnsureCapacity_real_T(sintabinv, nd2);
      sintabinv_data = sintabinv->data;
      for (k = 0; k < b_n; k++) {
        sintabinv_data[k + 1] = costab1q_data[(b_n - k) - 1];
      }
      nd2 = costab1q->size[1];
      for (k = nd2; k <= n2; k++) {
        sintabinv_data[k] = costab1q_data[k - b_n];
      }
      for (k = 0; k < b_n; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(b_n - k) - 1];
      }
      for (k = nd2; k <= n2; k++) {
        costab_data[k] = -costab1q_data[n2 - k];
        sintab_data[k] = -costab1q_data[k - b_n];
      }
      b_x = *x;
      d_x = x->size[1];
      b_x.size = &d_x;
      b_x.numDimensions = 1;
      c_FFTImplementationCallback_dob(&b_x, n, x->size[1], costab, sintab,
                                      sintabinv, yCol);
      yCol_data = yCol->data;
    } else {
      n = costab1q->size[1] - 1;
      b_n2 = (costab1q->size[1] - 1) << 1;
      nd2 = costab->size[0] * costab->size[1];
      costab->size[0] = 1;
      costab->size[1] = b_n2 + 1;
      emxEnsureCapacity_real_T(costab, nd2);
      costab_data = costab->data;
      nd2 = sintab->size[0] * sintab->size[1];
      sintab->size[0] = 1;
      sintab->size[1] = b_n2 + 1;
      emxEnsureCapacity_real_T(sintab, nd2);
      sintab_data = sintab->data;
      costab_data[0] = 1.0;
      sintab_data[0] = 0.0;
      for (k = 0; k < n; k++) {
        costab_data[k + 1] = costab1q_data[k + 1];
        sintab_data[k + 1] = -costab1q_data[(n - k) - 1];
      }
      nd2 = costab1q->size[1];
      for (k = nd2; k <= b_n2; k++) {
        costab_data[k] = -costab1q_data[b_n2 - k];
        sintab_data[k] = -costab1q_data[k - n];
      }
      nd2 = yCol->size[0];
      yCol->size[0] = x->size[1];
      emxEnsureCapacity_creal_T(yCol, nd2);
      yCol_data = yCol->data;
      if (x->size[1] != 1) {
        b_x = *x;
        c_x = x->size[1];
        b_x.size = &c_x;
        b_x.numDimensions = 1;
        c_FFTImplementationCallback_doH(&b_x, yCol, x->size[1], costab, sintab);
        yCol_data = yCol->data;
      } else {
        yCol_data[0].re = x_data[0];
        yCol_data[0].im = 0.0;
      }
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
    emxFree_real_T(&costab1q);
    nd2 = y->size[0] * y->size[1];
    y->size[0] = 1;
    n2 = x->size[1];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, nd2);
    y_data = y->data;
    for (k = 0; k < n2; k++) {
      y_data[k] = yCol_data[k];
    }
    emxFree_creal_T(&yCol);
  }
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
