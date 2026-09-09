/*
 * File: computeDFT.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *xin
 *                double varargin_1
 *                emxArray_creal_T *Xx
 *                double f[1024]
 * Return Type  : void
 */
void computeDFT(const emxArray_real_T *xin, double varargin_1,
                emxArray_creal_T *Xx, double f[1024])
{
  double dv[2];
  double Fs1;
  double freq_res;
  int i;
  if (xin->size[1] == 0) {
    Xx->size[0] = 1024;
    Xx->size[1] = 0;
  } else {
    g_FFTImplementationCallback_r2b(xin, Xx);
  }
  if (rtIsNaN(varargin_1)) {
    Fs1 = 6.283185307179586;
  } else {
    Fs1 = varargin_1;
  }
  freq_res = Fs1 / 1024.0;
  for (i = 0; i <= 1022; i += 2) {
    __m128d r;
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&f[i], _mm_mul_pd(_mm_set1_pd(freq_res), r));
  }
  f[512] = Fs1 / 2.0;
  f[1023] = Fs1 - freq_res;
}

/*
 * File trailer for computeDFT.c
 *
 * [EOF]
 */
