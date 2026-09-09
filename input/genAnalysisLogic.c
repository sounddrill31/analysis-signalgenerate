/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 14:34:56
 */

/* Include Files */
#include "genAnalysisLogic.h"
#include "abs.h"
#include "fft.h"
#include "genAnalysisLogic_emxutil.h"
#include "genAnalysisLogic_types.h"
#include "rt_nonfinite.h"
#include "spectrogram.h"
#include <emmintrin.h>

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
 *                double stftTime[1845]
 *                double stftFreq[513]
 *                emxArray_real_T *stftMagnitude
 * Return Type  : void
 */
void genAnalysisLogic(const emxArray_real_T *x, double Fs, emxArray_real_T *t,
                      emxArray_real_T *freq, emxArray_real_T *fftMagnitude,
                      double stftTime[1845], double stftFreq[513],
                      emxArray_real_T *stftMagnitude)
{
  static const int offsets[4] = {0, 1, 2, 3};
  __m128d r7;
  emxArray_creal_T *r3;
  emxArray_creal_T *stftData;
  emxArray_int32_T *r4;
  emxArray_real_T *r;
  emxArray_real_T *r2;
  creal_T *r6;
  double dv[2];
  double *fftMagnitude_data;
  double *freq_data;
  double *r1;
  double *t_data;
  int i;
  int i1;
  int *r5;
  emxInit_real_T(&r, 1);
  i = r->size[0];
  r->size[0] = 472587;
  emxEnsureCapacity_real_T(r, i);
  r1 = r->data;
  emxInit_real_T(&r2, 1);
  i = r2->size[0];
  r2->size[0] = 945176;
  emxEnsureCapacity_real_T(r2, i);
  emxInit_creal_T(&r3);
  i = r3->size[0];
  r3->size[0] = 945176;
  emxEnsureCapacity_creal_T(r3, i);
  emxInit_int32_T(&r4);
  i = r4->size[0];
  r4->size[0] = 472587;
  emxEnsureCapacity_int32_T(r4, i);
  r5 = r4->data;
  emxInit_creal_T(&stftData);
  i = stftData->size[0];
  stftData->size[0] = 946485;
  emxEnsureCapacity_creal_T(stftData, i);
  i = stftMagnitude->size[0];
  stftMagnitude->size[0] = 946485;
  emxEnsureCapacity_real_T(stftMagnitude, i);
  i = fftMagnitude->size[0];
  fftMagnitude->size[0] = 472589;
  emxEnsureCapacity_real_T(fftMagnitude, i);
  fftMagnitude_data = fftMagnitude->data;
  i = freq->size[0];
  freq->size[0] = 472589;
  emxEnsureCapacity_real_T(freq, i);
  freq_data = freq->data;
  i = t->size[0];
  t->size[0] = 945176;
  emxEnsureCapacity_real_T(t, i);
  t_data = t->data;
  /*  Simple matlab function for Audio Signal Analysis */
  /*  Frequency domain operations */
  /*  Calculate FFT */
  /*  Two-sided magnitude spectrum */
  /*  Single-sided magnitude spectrum */
  fft(x, r3);
  r6 = r3->data;
  for (i1 = 0; i1 < 945176; i1++) {
    double ai;
    double im;
    double re;
    t_data[i1] = (double)i1 / Fs;
    im = r6[i1].re;
    ai = r6[i1].im;
    if (ai == 0.0) {
      re = im / 945176.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 945176.0;
    } else {
      re = im / 945176.0;
      im = ai / 945176.0;
    }
    r6[i1].re = re;
    r6[i1].im = im;
  }
  b_abs(r3, r2);
  t_data = r2->data;
  emxFree_creal_T(&r3);
  for (i1 = 0; i1 < 472589; i1++) {
    fftMagnitude_data[i1] = t_data[i1];
  }
  emxFree_real_T(&r2);
  /*  Double the magnitude except DC and Nyquist components */
  r7 = _mm_set1_pd(2.0);
  for (i1 = 0; i1 <= 472580; i1 += 4) {
    _mm_storeu_si128(
        (__m128i *)&r5[i1],
        _mm_add_epi32(_mm_set1_epi32(i1 + 2),
                      _mm_loadu_si128((const __m128i *)&offsets[0])));
    _mm_storeu_pd(&r1[i1],
                  _mm_mul_pd(r7, _mm_loadu_pd(&fftMagnitude_data[i1 + 1])));
    _mm_storeu_pd(&r1[i1 + 2],
                  _mm_mul_pd(r7, _mm_loadu_pd(&fftMagnitude_data[i1 + 3])));
  }
  r5[472584] = 472586;
  r1[472584] = 2.0 * fftMagnitude_data[472585];
  r5[472585] = 472587;
  r1[472585] = 2.0 * fftMagnitude_data[472586];
  r5[472586] = 472588;
  r1[472586] = 2.0 * fftMagnitude_data[472587];
  for (i1 = 0; i1 < 472587; i1++) {
    fftMagnitude_data[r5[i1] - 1] = r1[i1];
  }
  emxFree_real_T(&r);
  emxFree_int32_T(&r4);
  /*  Frequency axis */
  for (i1 = 0; i1 <= 472586; i1 += 2) {
    dv[0] = i1;
    dv[1] = (double)i1 + 1.0;
    r7 = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&freq_data[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r7),
                                             _mm_set1_pd(945176.0)));
  }
  freq_data[472588] = Fs * 472588.0 / 945176.0;
  /* Short Time Fourier Transform Chart */
  /*  Window length */
  /*  50% overlap */
  /*  Calculate STFT */
  spectrogram(x, Fs, stftData, stftFreq, stftTime);
  /*  Magnitude of STFT */
  c_abs(stftData, stftMagnitude);
  emxFree_creal_T(&stftData);
}

/*
 * File trailer for genAnalysisLogic.c
 *
 * [EOF]
 */
