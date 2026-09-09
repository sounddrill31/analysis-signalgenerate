/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:13:58
 */

/* Include Files */
#include "genAnalysisLogic.h"
#include "abs.h"
#include "fft.h"
#include "genAnalysisLogic_data.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_initialize.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "spectrogram.h"
#include "omp.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
/*
 * force dynamic arrays
 *
 * Arguments    : const emxArray_real_T *x
 *                double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *freq
 *                emxArray_real_T *fftMagnitude
 *                double stftTime_data[]
 *                int stftTime_size[2]
 *                double stftFreq[513]
 *                emxArray_real_T *stftMagnitude
 * Return Type  : void
 */
void genAnalysisLogic(const emxArray_real_T *x, double Fs, emxArray_real_T *t,
                      emxArray_real_T *freq, emxArray_real_T *fftMagnitude,
                      double stftTime_data[], int stftTime_size[2],
                      double stftFreq[513], emxArray_real_T *stftMagnitude)
{
  emxArray_creal_T *X;
  emxArray_creal_T *b_X;
  emxArray_creal_T *stftData;
  creal_T b_x;
  creal_T *X_data;
  creal_T *b_X_data;
  double dv[2];
  double b_ai;
  double b_ar;
  double *fftMagnitude_data;
  double *t_data;
  int i;
  int i1;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  int x_tmp;
  if (!isInitialized_genAnalysisLogic) {
    genAnalysisLogic_initialize();
  }
  /*  Simple matlab function for Audio Signal Analysis */
  /*  Time domain operations */
  /*  Create time vector corresponding to the input samples */
  if (x->size[1] - 1 < 0) {
    t->size[1] = 0;
  } else {
    scalarLB = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = x->size[1];
    emxEnsureCapacity_real_T(t, scalarLB);
    t_data = t->data;
    scalarLB = x->size[1] - 1;
    for (i = 0; i <= scalarLB; i++) {
      t_data[i] = i;
    }
  }
  loop_ub = t->size[1];
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity_real_T(t, scalarLB);
  t_data = t->data;
  scalarLB = (t->size[1] / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    _mm_storeu_pd(&t_data[i],
                  _mm_div_pd(_mm_loadu_pd(&t_data[i]), _mm_set1_pd(Fs)));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    t_data[i] /= Fs;
  }
  /*  Frequency domain operations */
  /*  Calculate FFT */
  emxInit_creal_T(&X, 2);
  fft(x, X);
  X_data = X->data;
  /*  Two-sided magnitude spectrum */
  x_tmp = x->size[1];
  b_x.re = x->size[1];
  emxInit_creal_T(&b_X, 2);
  scalarLB = b_X->size[0] * b_X->size[1];
  b_X->size[0] = 1;
  vectorUB = X->size[1];
  b_X->size[1] = X->size[1];
  emxEnsureCapacity_creal_T(b_X, scalarLB);
  b_X_data = b_X->data;
  scalarLB = X->size[1];
  if (X->size[1] < 1600) {
    for (i1 = 0; i1 < vectorUB; i1++) {
      double ai;
      double ar;
      ar = X_data[i1].re;
      ai = X_data[i1].im;
      if (ai == 0.0) {
        b_X_data[i1].re = ar / b_x.re;
        b_X_data[i1].im = 0.0;
      } else if (ar == 0.0) {
        b_X_data[i1].re = 0.0;
        b_X_data[i1].im = ai / b_x.re;
      } else {
        b_X_data[i1].re = ar / b_x.re;
        b_X_data[i1].im = ai / b_x.re;
      }
    }
  } else {
#pragma omp parallel for num_threads(omp_get_max_threads()) private(b_ar, b_ai)

    for (i1 = 0; i1 < scalarLB; i1++) {
      b_ar = X_data[i1].re;
      b_ai = X_data[i1].im;
      if (b_ai == 0.0) {
        b_X_data[i1].re = b_ar / b_x.re;
        b_X_data[i1].im = 0.0;
      } else if (b_ar == 0.0) {
        b_X_data[i1].re = 0.0;
        b_X_data[i1].im = b_ai / b_x.re;
      } else {
        b_X_data[i1].re = b_ar / b_x.re;
        b_X_data[i1].im = b_ai / b_x.re;
      }
    }
  }
  emxFree_creal_T(&X);
  emxInit_real_T(&t, 2);
  b_abs(b_X, t);
  t_data = t->data;
  emxFree_creal_T(&b_X);
  /*  Single-sided magnitude spectrum */
  loop_ub = (int)floor((double)x->size[1] / 2.0);
  scalarLB = fftMagnitude->size[0] * fftMagnitude->size[1];
  fftMagnitude->size[0] = 1;
  fftMagnitude->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(fftMagnitude, scalarLB);
  fftMagnitude_data = fftMagnitude->data;
  for (i = 0; i <= loop_ub; i++) {
    fftMagnitude_data[i] = t_data[i];
  }
  /*  Double the magnitude except DC and Nyquist components */
  if (loop_ub + 1 > 2) {
    scalarLB = ((loop_ub - 1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      _mm_storeu_pd(&fftMagnitude_data[i + 1],
                    _mm_mul_pd(_mm_set1_pd(2.0), _mm_loadu_pd(&t_data[i + 1])));
    }
    for (i = scalarLB; i <= loop_ub - 2; i++) {
      fftMagnitude_data[i + 1] = 2.0 * t_data[i + 1];
    }
  }
  emxFree_real_T(&t);
  /*  Frequency axis */
  scalarLB = freq->size[0] * freq->size[1];
  freq->size[0] = 1;
  freq->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(freq, scalarLB);
  t_data = freq->data;
  scalarLB = ((loop_ub + 1) / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    __m128d r;
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&t_data[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r),
                                         _mm_set1_pd(x_tmp)));
  }
  for (i = scalarLB; i <= loop_ub; i++) {
    t_data[i] = Fs * (double)i / (double)x_tmp;
  }
  /* Short Time Fourier Transform Chart */
  /*  Window length */
  /*  50% overlap */
  /*  Calculate STFT */
  emxInit_creal_T(&stftData, 2);
  spectrogram(x, Fs, stftData, stftFreq, stftTime_data, stftTime_size);
  /*  Magnitude of STFT */
  c_abs(stftData, stftMagnitude);
  emxFree_creal_T(&stftData);
}

/*
 * File trailer for genAnalysisLogic.c
 *
 * [EOF]
 */
