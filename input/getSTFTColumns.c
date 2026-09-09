/*
 * File: getSTFTColumns.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "getSTFTColumns.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "omp.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
/*
 * Arguments    : const emxArray_real_T *x
 *                double nx
 *                double Fs
 *                emxArray_real_T *varargout_1
 *                double varargout_2_data[]
 *                int varargout_2_size[2]
 * Return Type  : void
 */
void getSTFTColumns(const emxArray_real_T *x, double nx, double Fs,
                    emxArray_real_T *varargout_1, double varargout_2_data[],
                    int varargout_2_size[2])
{
  const double *x_data;
  double nCol;
  double *varargout_1_data;
  double *y_data;
  int b_loop_ub;
  int i;
  int i1;
  int i2;
  int iCol;
  int loop_ub;
  int vectorUB;
  x_data = x->data;
  nCol = trunc((nx - 512.0) / 512.0);
  loop_ub = varargout_1->size[0] * varargout_1->size[1];
  varargout_1->size[0] = 1024;
  vectorUB = (int)nCol;
  varargout_1->size[1] = (int)nCol;
  emxEnsureCapacity_real_T(varargout_1, loop_ub);
  varargout_1_data = varargout_1->data;
  b_loop_ub = (int)nCol << 10;
  for (i = 0; i < b_loop_ub; i++) {
    varargout_1_data[i] = 0.0;
  }
  emxInit_real_T(&varargout_1, 2);
  y_data = varargout_1->data;
  if (nCol - 1.0 < 0.0) {
    varargout_1->size[0] = 1;
    varargout_1->size[1] = 0;
  } else {
    loop_ub = varargout_1->size[0] * varargout_1->size[1];
    varargout_1->size[0] = 1;
    varargout_1->size[1] = (int)(nCol - 1.0) + 1;
    emxEnsureCapacity_real_T(varargout_1, loop_ub);
    y_data = varargout_1->data;
    loop_ub = (int)(nCol - 1.0);
    for (i = 0; i <= loop_ub; i++) {
      y_data[i] = i;
    }
  }
  if (b_loop_ub < 1600) {
    for (iCol = 0; iCol < vectorUB; iCol++) {
      i1 = iCol << 9;
      for (i2 = 0; i2 < 1024; i2++) {
        varargout_1_data[i2 + 1024 * iCol] = x_data[i2 + i1];
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(i1, i2)

    for (iCol = 0; iCol < vectorUB; iCol++) {
      i1 = iCol << 9;
      for (i2 = 0; i2 < 1024; i2++) {
        varargout_1_data[i2 + 1024 * iCol] = x_data[i2 + i1];
      }
    }
  }
  varargout_2_size[0] = 1;
  loop_ub = varargout_1->size[1];
  varargout_2_size[1] = varargout_1->size[1];
  b_loop_ub = (varargout_1->size[1] / 2) << 1;
  vectorUB = b_loop_ub - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r;
    r = _mm_set1_pd(512.0);
    _mm_storeu_pd(
        &varargout_2_data[i],
        _mm_div_pd(_mm_add_pd(_mm_mul_pd(_mm_loadu_pd(&y_data[i]), r), r),
                   _mm_set1_pd(Fs)));
  }
  for (i = b_loop_ub; i < loop_ub; i++) {
    varargout_2_data[i] = (y_data[i] * 512.0 + 512.0) / Fs;
  }
  emxFree_real_T(&varargout_1);
}

/*
 * File trailer for getSTFTColumns.c
 *
 * [EOF]
 */
