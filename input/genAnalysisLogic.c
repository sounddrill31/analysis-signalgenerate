/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
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
 * Arguments    : double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *freq
 *                emxArray_real_T *fftMagnitude
 *                double stftTime[31]
 *                double stftFreq[513]
 *                emxArray_real_T *stftMagnitude
 * Return Type  : void
 */
void genAnalysisLogic(double Fs, emxArray_real_T *t, emxArray_real_T *freq,
                      emxArray_real_T *fftMagnitude, double stftTime[31],
                      double stftFreq[513], emxArray_real_T *stftMagnitude)
{
  emxArray_creal_T *r1;
  emxArray_creal_T *stftData;
  emxArray_real_T *r;
  creal_T *r2;
  double dv[2];
  double *fftMagnitude_data;
  double *freq_data;
  double *stftMagnitude_data;
  double *t_data;
  int i;
  int k;
  emxInit_real_T(&r, 1);
  i = r->size[0];
  r->size[0] = 16384;
  emxEnsureCapacity_real_T(r, i);
  emxInit_creal_T(&r1);
  i = r1->size[0];
  r1->size[0] = 16384;
  emxEnsureCapacity_creal_T(r1, i);
  emxInit_creal_T(&stftData);
  i = stftData->size[0];
  stftData->size[0] = 15903;
  emxEnsureCapacity_creal_T(stftData, i);
  i = stftMagnitude->size[0];
  stftMagnitude->size[0] = 15903;
  emxEnsureCapacity_real_T(stftMagnitude, i);
  stftMagnitude_data = stftMagnitude->data;
  i = fftMagnitude->size[0];
  fftMagnitude->size[0] = 8193;
  emxEnsureCapacity_real_T(fftMagnitude, i);
  fftMagnitude_data = fftMagnitude->data;
  i = freq->size[0];
  freq->size[0] = 8193;
  emxEnsureCapacity_real_T(freq, i);
  freq_data = freq->data;
  i = t->size[0];
  t->size[0] = 16384;
  emxEnsureCapacity_real_T(t, i);
  t_data = t->data;
  /*  Simple matlab function for Audio Signal Analysis */
  /*  Frequency domain operations */
  /*  Calculate FFT */
  /*  Two-sided magnitude spectrum */
  /*  Single-sided magnitude spectrum */
  fft(r1);
  r2 = r1->data;
  for (k = 0; k < 16384; k++) {
    double ai;
    double im;
    double re;
    t_data[k] = (double)k / Fs;
    im = r2[k].re;
    ai = r2[k].im;
    if (ai == 0.0) {
      re = im / 16384.0;
      im = 0.0;
    } else if (im == 0.0) {
      re = 0.0;
      im = ai / 16384.0;
    } else {
      re = im / 16384.0;
      im = ai / 16384.0;
    }
    r2[k].re = re;
    r2[k].im = im;
  }
  b_abs(r1, r);
  t_data = r->data;
  emxFree_creal_T(&r1);
  for (k = 0; k < 8193; k++) {
    fftMagnitude_data[k] = t_data[k];
  }
  emxFree_real_T(&r);
  /*  Double the magnitude except DC and Nyquist components */
  for (k = 0; k <= 8188; k += 2) {
    _mm_storeu_pd(
        &fftMagnitude_data[k + 1],
        _mm_mul_pd(_mm_set1_pd(2.0), _mm_loadu_pd(&fftMagnitude_data[k + 1])));
  }
  fftMagnitude_data[8191] *= 2.0;
  /*  Frequency axis */
  for (k = 0; k <= 8190; k += 2) {
    __m128d r3;
    dv[0] = k;
    dv[1] = (double)k + 1.0;
    r3 = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&freq_data[k], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r3),
                                            _mm_set1_pd(16384.0)));
  }
  freq_data[8192] = Fs * 8192.0 / 16384.0;
  /* Short Time Fourier Transform Chart */
  /*  Window length */
  /*  50% overlap */
  /*  Calculate STFT */
  spectrogram(Fs, stftData, stftFreq, stftTime);
  emxFree_creal_T(&stftData);
  /*  Magnitude of STFT */
  for (k = 0; k < 15903; k++) {
    stftMagnitude_data[k] = 0.0;
  }
}

/*
 * File trailer for genAnalysisLogic.c
 *
 * [EOF]
 */
