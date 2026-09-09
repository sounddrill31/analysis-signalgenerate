/*
 * File: mean.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 04:14:33
 */

/* Include Files */
#include "mean.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                double y[513]
 * Return Type  : void
 */
void mean(const emxArray_real_T *x, double y[513])
{
  __m128d r;
  double bsum[513];
  const double *x_data;
  int b_xj;
  int ib;
  int xj;
  x_data = x->data;
  if (x->size[1] == 0) {
    memset(&y[0], 0, 513U * sizeof(double));
  } else {
    int firstBlockLength;
    int lastBlockLength;
    int nblocks;
    int xoffset;
    if (x->size[1] <= 1024) {
      firstBlockLength = x->size[1];
      lastBlockLength = 0;
      nblocks = 1;
    } else {
      firstBlockLength = 1024;
      nblocks = (int)((unsigned int)x->size[1] >> 10);
      lastBlockLength = x->size[1] - (nblocks << 10);
      if (lastBlockLength > 0) {
        nblocks++;
      } else {
        lastBlockLength = 1024;
      }
    }
    for (xj = 0; xj < 513; xj++) {
      y[xj] = x_data[xj];
    }
    for (xj = 2; xj <= firstBlockLength; xj++) {
      xoffset = (xj - 1) * 513;
      for (b_xj = 0; b_xj <= 510; b_xj += 2) {
        r = _mm_loadu_pd(&y[b_xj]);
        _mm_storeu_pd(&y[b_xj],
                      _mm_add_pd(r, _mm_loadu_pd(&x_data[xoffset + b_xj])));
      }
      y[512] += x_data[xoffset + 512];
    }
    for (ib = 2; ib <= nblocks; ib++) {
      int xblockoffset;
      xblockoffset = (ib - 1) * 525312;
      for (xj = 0; xj < 513; xj++) {
        bsum[xj] = x_data[xblockoffset + xj];
      }
      if (ib == nblocks) {
        firstBlockLength = lastBlockLength;
      } else {
        firstBlockLength = 1024;
      }
      for (xj = 2; xj <= firstBlockLength; xj++) {
        xoffset = xblockoffset + (xj - 1) * 513;
        for (b_xj = 0; b_xj <= 510; b_xj += 2) {
          r = _mm_loadu_pd(&bsum[b_xj]);
          _mm_storeu_pd(&bsum[b_xj],
                        _mm_add_pd(r, _mm_loadu_pd(&x_data[xoffset + b_xj])));
        }
        bsum[512] += x_data[xoffset + 512];
      }
      for (xj = 0; xj <= 510; xj += 2) {
        __m128d r1;
        r = _mm_loadu_pd(&y[xj]);
        r1 = _mm_loadu_pd(&bsum[xj]);
        _mm_storeu_pd(&y[xj], _mm_add_pd(r, r1));
      }
      y[512] += bsum[512];
    }
  }
  for (xj = 0; xj <= 510; xj += 2) {
    r = _mm_loadu_pd(&y[xj]);
    _mm_storeu_pd(&y[xj], _mm_div_pd(r, _mm_set1_pd(x->size[1])));
  }
  y[512] /= (double)x->size[1];
}

/*
 * File trailer for mean.c
 *
 * [EOF]
 */
