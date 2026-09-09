/*
 * File: spectrogram.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "spectrogram.h"
#include "bsxfun.h"
#include "computeDFT.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "getSTFTColumns.h"
#include "pspectrogram.h"
#include "rt_nonfinite.h"
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                double varargin_4
 *                emxArray_creal_T *varargout_1
 *                double varargout_2[513]
 *                double varargout_3_data[]
 *                int varargout_3_size[2]
 * Return Type  : void
 */
void spectrogram(const emxArray_real_T *x, double varargin_4,
                 emxArray_creal_T *varargout_1, double varargout_2[513],
                 double varargout_3_data[], int varargout_3_size[2])
{
  emxArray_creal_T *b_y1;
  emxArray_real_T b_x;
  emxArray_real_T *r;
  emxArray_real_T *xin;
  double f[1024];
  int c_x;
  int eint;
  frexp(x->size[1], &eint);
  b_x = *x;
  c_x = x->size[1];
  b_x.size = &c_x;
  b_x.numDimensions = 1;
  emxInit_real_T(&xin, 2);
  getSTFTColumns(&b_x, x->size[1], varargin_4, xin, varargout_3_data,
                 varargout_3_size);
  emxInit_real_T(&r, 2);
  bsxfun(xin, r);
  emxFree_real_T(&xin);
  emxInit_creal_T(&b_y1, 2);
  computeDFT(r, varargin_4, b_y1, f);
  emxFree_real_T(&r);
  formatSpectrogram(b_y1, varargin_4, varargout_1, varargout_2);
  emxFree_creal_T(&b_y1);
}

/*
 * File trailer for spectrogram.c
 *
 * [EOF]
 */
