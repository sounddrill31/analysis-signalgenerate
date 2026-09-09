/*
 * File: fft.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "fft.h"
#include "FFTImplementationCallback.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"

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
  emxArray_real_T *sintab;
  emxArray_real_T *sintabinv;
  creal_T *yCol_data;
  creal_T *y_data;
  int c_x;
  int d_x;
  int i;
  if (x->size[1] == 0) {
    y->size[0] = 1;
    y->size[1] = 0;
  } else {
    int N2blue;
    int pmax;
    boolean_T useRadix2;
    useRadix2 =
        (((unsigned int)x->size[1] & (unsigned int)(x->size[1] - 1)) == 0U);
    N2blue = 1;
    if (useRadix2) {
      pmax = x->size[1];
    } else {
      N2blue = (x->size[1] + x->size[1]) - 1;
      pmax = 31;
      if (N2blue <= 1) {
        pmax = 0;
      } else {
        int pmin;
        boolean_T exitg1;
        pmin = 0;
        exitg1 = false;
        while (!exitg1 && (pmax - pmin > 1)) {
          int k;
          int pow2p;
          k = (pmin + pmax) >> 1;
          pow2p = 1 << k;
          if (pow2p == N2blue) {
            pmax = k;
            exitg1 = true;
          } else if (pow2p > N2blue) {
            pmax = k;
          } else {
            pmin = k;
          }
        }
      }
      N2blue = 1 << pmax;
      pmax = N2blue;
    }
    emxInit_real_T(&costab, 2);
    emxInit_real_T(&sintab, 2);
    emxInit_real_T(&sintabinv, 2);
    c_FFTImplementationCallback_gen(pmax, useRadix2, costab, sintab, sintabinv);
    emxInit_creal_T(&yCol, 1);
    if (useRadix2) {
      b_x = *x;
      d_x = x->size[1];
      b_x.size = &d_x;
      b_x.numDimensions = 1;
      c_FFTImplementationCallback_r2b(&b_x, x->size[1], costab, sintab, yCol);
      yCol_data = yCol->data;
    } else {
      b_x = *x;
      c_x = x->size[1];
      b_x.size = &c_x;
      b_x.numDimensions = 1;
      c_FFTImplementationCallback_dob(&b_x, N2blue, x->size[1], costab, sintab,
                                      sintabinv, yCol);
      yCol_data = yCol->data;
    }
    emxFree_real_T(&sintabinv);
    emxFree_real_T(&sintab);
    emxFree_real_T(&costab);
    N2blue = y->size[0] * y->size[1];
    y->size[0] = 1;
    pmax = x->size[1];
    y->size[1] = x->size[1];
    emxEnsureCapacity_creal_T(y, N2blue);
    y_data = y->data;
    for (i = 0; i < pmax; i++) {
      y_data[i] = yCol_data[i];
    }
    emxFree_creal_T(&yCol);
  }
}

/*
 * File trailer for fft.c
 *
 * [EOF]
 */
