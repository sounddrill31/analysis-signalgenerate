/*
 * File: computeDFT.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
 */

/* Include Files */
#include "computeDFT.h"
#include "FFTImplementationCallback.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 * Arguments    : double varargin_1
 *                emxArray_creal_T *Xx
 *                double f[1024]
 * Return Type  : void
 */
void computeDFT(double varargin_1, emxArray_creal_T *Xx, double f[1024])
{
  double dv[2];
  double Fs1;
  double freq_res;
  int i;
  int i1;
  i = Xx->size[0];
  Xx->size[0] = 31744;
  emxEnsureCapacity_creal_T(Xx, i);
  d_FFTImplementationCallback_doH(Xx);
  if (rtIsNaN(varargin_1)) {
    Fs1 = 6.283185307179586;
  } else {
    Fs1 = varargin_1;
  }
  freq_res = Fs1 / 1024.0;
  for (i1 = 0; i1 <= 1022; i1 += 2) {
    __m128d r;
    dv[0] = i1;
    dv[1] = (double)i1 + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&f[i1], _mm_mul_pd(_mm_set1_pd(freq_res), r));
  }
  f[512] = Fs1 / 2.0;
  f[1023] = Fs1 - freq_res;
}

/*
 * File trailer for computeDFT.c
 *
 * [EOF]
 */
