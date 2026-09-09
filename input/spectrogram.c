/*
 * File: spectrogram.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
 */

/* Include Files */
#include "spectrogram.h"
#include "computeDFT.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "pspectrogram.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>

/* Function Definitions */
/*
 * Arguments    : double varargin_4
 *                emxArray_creal_T *varargout_1
 *                double varargout_2[513]
 *                double varargout_3[31]
 * Return Type  : void
 */
void spectrogram(double varargin_4, emxArray_creal_T *varargout_1,
                 double varargout_2[513], double varargout_3[31])
{
  __m128d r;
  emxArray_creal_T *b_y1;
  double f[1024];
  double dv[2];
  int i;
  int i1;
  emxInit_creal_T(&b_y1);
  i = b_y1->size[0];
  b_y1->size[0] = 31744;
  emxEnsureCapacity_creal_T(b_y1, i);
  i = varargout_1->size[0];
  varargout_1->size[0] = 15903;
  emxEnsureCapacity_creal_T(varargout_1, i);
  computeDFT(varargin_4, b_y1, f);
  formatSpectrogram(b_y1, varargin_4, varargout_1, varargout_2);
  emxFree_creal_T(&b_y1);
  r = _mm_set1_pd(512.0);
  for (i1 = 0; i1 <= 28; i1 += 2) {
    __m128d r1;
    dv[0] = i1;
    dv[1] = (double)i1 + 1.0;
    r1 = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&varargout_3[i1], _mm_div_pd(_mm_add_pd(_mm_mul_pd(r, r1), r),
                                               _mm_set1_pd(varargin_4)));
  }
  varargout_3[30] = 15872.0 / varargin_4;
}

/*
 * File trailer for spectrogram.c
 *
 * [EOF]
 */
