/*
 * File: pspectrogram.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

/* Include Files */
#include "pspectrogram.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const creal_T y[1889280]
 *                double Fs
 *                creal_T yout[946485]
 *                double fout[513]
 * Return Type  : void
 */
void formatSpectrogram(const creal_T y[1889280], double Fs,
                       creal_T yout[946485], double fout[513])
{
  double w1[1024];
  double dv[2];
  double Fs1;
  double freq_res;
  int i;
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
  w1[512] = Fs1 / 2.0;
  w1[1023] = Fs1 - freq_res;
  memcpy(&fout[0], &w1[0], 513U * sizeof(double));
  for (i = 0; i < 1845; i++) {
    memcpy(&yout[i * 513], &y[i * 1024], 513U * sizeof(creal_T));
  }
}

/*
 * File trailer for pspectrogram.c
 *
 * [EOF]
 */
