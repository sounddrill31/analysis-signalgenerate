/*
 * File: pspectrogram.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "pspectrogram.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_creal_T *y
 *                double Fs
 *                emxArray_creal_T *yout
 *                double fout[513]
 * Return Type  : void
 */
void formatSpectrogram(const emxArray_creal_T *y, double Fs,
                       emxArray_creal_T *yout, double fout[513])
{
  const creal_T *y_data;
  creal_T *yout_data;
  double w1[1024];
  double dv[2];
  double Fs1;
  double freq_res;
  int i;
  int i2;
  int loop_ub;
  y_data = y->data;
  if (rtIsNaN(Fs)) {
    Fs1 = 6.283185307179586;
  } else {
    Fs1 = Fs;
  }
  freq_res = Fs1 / 1024.0;
  for (i = 0; i <= 1022; i += 2) {
    __m128d r;
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&w1[i], _mm_mul_pd(_mm_set1_pd(freq_res), r));
  }
  int i1;
  w1[512] = Fs1 / 2.0;
  w1[1023] = Fs1 - freq_res;
  memcpy(&fout[0], &w1[0], 513U * sizeof(double));
  i1 = yout->size[0] * yout->size[1];
  yout->size[0] = 513;
  loop_ub = y->size[1];
  yout->size[1] = y->size[1];
  emxEnsureCapacity_creal_T(yout, i1);
  yout_data = yout->data;
  for (i = 0; i < loop_ub; i++) {
    for (i2 = 0; i2 < 513; i2++) {
      yout_data[i2 + 513 * i] = y_data[i2 + 1024 * i];
    }
  }
}

/*
 * File trailer for pspectrogram.c
 *
 * [EOF]
 */
