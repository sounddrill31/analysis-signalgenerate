/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 10-Sep-2026 03:03:38
 */

/* Include Files */
#include "genAnalysisLogic.h"
#include "AsyncBufferSysObj.h"
#include "STFT.h"
#include "STFTSysObj.h"
#include "abs.h"
#include "fft.h"
#include "genAnalysisLogic_data.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_initialize.h"
#include "genAnalysisLogic_internal_types.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>

/* Variable Definitions */
static dsp_STFT stftObj;

static boolean_T stftObj_not_empty;

/* Function Definitions */
/*
 * Time domain operations
 *  Create time vector corresponding to the input samples
 *
 * Arguments    : const emxArray_real_T *x
 *                double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *freq
 *                emxArray_real_T *fftMagnitude
 *                emxArray_real_T *stftTime
 *                double stftFreq[513]
 *                emxArray_real_T *stftMagnitude
 * Return Type  : void
 */
void genAnalysisLogic(const emxArray_real_T *x, double Fs, emxArray_real_T *t,
                      emxArray_real_T *freq, emxArray_real_T *fftMagnitude,
                      emxArray_real_T *stftTime, double stftFreq[513],
                      emxArray_real_T *stftMagnitude)
{
  __m128d r;
  emxArray_creal_T *X;
  emxArray_creal_T *b_X;
  emxArray_creal_T *stftFrame;
  emxArray_real_T *P2;
  creal_T *X_data;
  creal_T *b_X_data;
  double dv[2];
  const double *x_data;
  double *fftMagnitude_data;
  double *stftTime_data;
  double *t_data;
  int endIdx;
  int i;
  int k;
  int loop_ub;
  int numFrames;
  int vectorUB;
  int x_re;
  if (!isInitialized_genAnalysisLogic) {
    genAnalysisLogic_initialize();
  }
  x_data = x->data;
  /*  Simple matlab function for Audio Signal Analysis */
  if (x->size[1] - 1 < 0) {
    t->size[1] = 0;
  } else {
    endIdx = t->size[0] * t->size[1];
    t->size[0] = 1;
    t->size[1] = x->size[1];
    emxEnsureCapacity_real_T(t, endIdx);
    t_data = t->data;
    endIdx = x->size[1] - 1;
    for (i = 0; i <= endIdx; i++) {
      t_data[i] = i;
    }
  }
  loop_ub = t->size[1];
  endIdx = t->size[0] * t->size[1];
  t->size[0] = 1;
  emxEnsureCapacity_real_T(t, endIdx);
  t_data = t->data;
  endIdx = (t->size[1] / 2) << 1;
  vectorUB = endIdx - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    _mm_storeu_pd(&t_data[i],
                  _mm_div_pd(_mm_loadu_pd(&t_data[i]), _mm_set1_pd(Fs)));
  }
  for (i = endIdx; i < loop_ub; i++) {
    t_data[i] /= Fs;
  }
  /*  Frequency domain operations */
  /*  Calculate FFT */
  emxInit_creal_T(&X, 2);
  fft(x, X);
  X_data = X->data;
  /*  Two-sided magnitude spectrum */
  x_re = x->size[1];
  emxInit_creal_T(&b_X, 2);
  endIdx = b_X->size[0] * b_X->size[1];
  b_X->size[0] = 1;
  vectorUB = X->size[1];
  b_X->size[1] = X->size[1];
  emxEnsureCapacity_creal_T(b_X, endIdx);
  b_X_data = b_X->data;
  for (i = 0; i < vectorUB; i++) {
    double ai;
    double ar;
    ar = X_data[i].re;
    ai = X_data[i].im;
    if (ai == 0.0) {
      b_X_data[i].re = ar / (double)x_re;
      b_X_data[i].im = 0.0;
    } else if (ar == 0.0) {
      b_X_data[i].re = 0.0;
      b_X_data[i].im = ai / (double)x_re;
    } else {
      b_X_data[i].re = ar / (double)x_re;
      b_X_data[i].im = ai / (double)x_re;
    }
  }
  emxFree_creal_T(&X);
  emxInit_real_T(&P2, 2);
  b_abs(b_X, P2);
  t_data = P2->data;
  emxFree_creal_T(&b_X);
  /*  Single-sided magnitude spectrum */
  loop_ub = (int)floor((double)x->size[1] / 2.0);
  endIdx = fftMagnitude->size[0] * fftMagnitude->size[1];
  fftMagnitude->size[0] = 1;
  fftMagnitude->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(fftMagnitude, endIdx);
  fftMagnitude_data = fftMagnitude->data;
  for (i = 0; i <= loop_ub; i++) {
    fftMagnitude_data[i] = t_data[i];
  }
  /*  Double the magnitude except DC and Nyquist components */
  if (loop_ub + 1 > 2) {
    endIdx = ((loop_ub - 1) / 2) << 1;
    vectorUB = endIdx - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      _mm_storeu_pd(&fftMagnitude_data[i + 1],
                    _mm_mul_pd(_mm_set1_pd(2.0), _mm_loadu_pd(&t_data[i + 1])));
    }
    for (i = endIdx; i <= loop_ub - 2; i++) {
      fftMagnitude_data[i + 1] = 2.0 * t_data[i + 1];
    }
  }
  emxFree_real_T(&P2);
  /*  Frequency axis */
  endIdx = freq->size[0] * freq->size[1];
  freq->size[0] = 1;
  freq->size[1] = loop_ub + 1;
  emxEnsureCapacity_real_T(freq, endIdx);
  t_data = freq->data;
  endIdx = ((loop_ub + 1) / 2) << 1;
  vectorUB = endIdx - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&t_data[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r),
                                         _mm_set1_pd(x_re)));
  }
  for (i = endIdx; i <= loop_ub; i++) {
    t_data[i] = Fs * (double)i / (double)x_re;
  }
  /* Short Time Fourier Transform Chart */
  /*  each hop carries 512 samples */
  if (!stftObj_not_empty) {
    STFT_STFT(&stftObj);
    stftObj_not_empty = true;
  }
  numFrames = (int)floor((double)x->size[1] / 512.0);
  /*  513 */
  endIdx = stftMagnitude->size[0] * stftMagnitude->size[1];
  stftMagnitude->size[0] = 513;
  stftMagnitude->size[1] = numFrames;
  emxEnsureCapacity_real_T(stftMagnitude, endIdx);
  fftMagnitude_data = stftMagnitude->data;
  endIdx = 513 * numFrames;
  for (i = 0; i < endIdx; i++) {
    fftMagnitude_data[i] = 0.0;
  }
  endIdx = stftTime->size[0] * stftTime->size[1];
  stftTime->size[0] = 1;
  stftTime->size[1] = numFrames;
  emxEnsureCapacity_real_T(stftTime, endIdx);
  stftTime_data = stftTime->data;
  for (i = 0; i <= 510; i += 2) {
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&stftFreq[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r),
                                           _mm_set1_pd(1024.0)));
  }
  stftFreq[512] = Fs * 512.0 / 1024.0;
  /*  populate the audio stream 512 samples at a time */
  emxInit_creal_T(&stftFrame, 2);
  emxInit_real_T(&t, 2);
  emxInit_real_T(&fftMagnitude, 1);
  for (k = 0; k < numFrames; k++) {
    int startIdx;
    startIdx = k << 9;
    endIdx = (k + 1) << 9;
    /*  Extract the 512-sample chunk */
    if (startIdx + 1 > endIdx) {
      x_re = 0;
      endIdx = 0;
    } else {
      x_re = startIdx;
    }
    loop_ub = endIdx - x_re;
    vectorUB = fftMagnitude->size[0];
    fftMagnitude->size[0] = loop_ub;
    emxEnsureCapacity_real_T(fftMagnitude, vectorUB);
    t_data = fftMagnitude->data;
    for (i = 0; i < loop_ub; i++) {
      t_data[i] = x_data[x_re + i];
    }
    STFT_step(&stftObj, fftMagnitude, stftFrame);
    /*  Store the results */
    c_abs(stftFrame, t);
    t_data = t->data;
    for (i = 0; i < 513; i++) {
      fftMagnitude_data[i + 513 * k] = t_data[i];
    }
    stftTime_data[k] = (((double)startIdx + 1.0) + 512.0) / Fs;
  }
  emxFree_real_T(&fftMagnitude);
  emxFree_real_T(&t);
  emxFree_creal_T(&stftFrame);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_delete(void)
{
  if (!stftObj.matlabCodegenIsDeleted) {
    stftObj.matlabCodegenIsDeleted = true;
  }
  handle_matlabCodegenDestructor(&stftObj.pObj);
  if (!stftObj.pObj.pBuff.matlabCodegenIsDeleted) {
    stftObj.pObj.pBuff.matlabCodegenIsDeleted = true;
  }
  b_handle_matlabCodegenDestructo(&stftObj.pObj.pBuff.pBuffer);
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_init(void)
{
  stftObj_not_empty = false;
}

/*
 * Arguments    : void
 * Return Type  : void
 */
void genAnalysisLogic_new(void)
{
  stftObj.pObj.pBuff.pBuffer.matlabCodegenIsDeleted = true;
  stftObj.pObj.pBuff.matlabCodegenIsDeleted = true;
  stftObj.pObj.matlabCodegenIsDeleted = true;
  stftObj.matlabCodegenIsDeleted = true;
}

/*
 * File trailer for genAnalysisLogic.c
 *
 * [EOF]
 */
