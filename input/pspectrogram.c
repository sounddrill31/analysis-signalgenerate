/*
 * File: pspectrogram.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:34:56
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
  int i1;
  int i2;
  y_data = y->data;
  i = yout->size[0];
  yout->size[0] = 946485;
  emxEnsureCapacity_creal_T(yout, i);
  yout_data = yout->data;
  if (rtIsNaN(Fs)) {
    Fs1 = 6.283185307179586;
  } else {
    Fs1 = Fs;
  }
  freq_res = Fs1 / 1024.0;
  for (i1 = 0; i1 <= 1022; i1 += 2) {
    __m128d r;
    dv[0] = i1;
    dv[1] = (double)i1 + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&w1[i1], _mm_mul_pd(_mm_set1_pd(freq_res), r));
  }
  w1[512] = Fs1 / 2.0;
  w1[1023] = Fs1 - freq_res;
  memcpy(&fout[0], &w1[0], 513U * sizeof(double));
  for (i1 = 0; i1 < 1845; i1++) {
    for (i2 = 0; i2 < 513; i2++) {
      yout_data[i2 + 513 * i1] = y_data[i2 + (i1 << 10)];
    }
  }
}

/*
 * File trailer for pspectrogram.c
 *
 * [EOF]
 */
