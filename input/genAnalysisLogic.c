/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 13:49:20
 */

/* Include Files */
#include "genAnalysisLogic.h"
#include "abs.h"
#include "fft.h"
#include "genAnalysisLogic_data.h"
#include "genAnalysisLogic_initialize.h"
#include "rt_nonfinite.h"
#include "spectrogram.h"
#include "omp.h"
#include <emmintrin.h>
#include <string.h>

/* Function Definitions */
/*
 * Time domain operations
 *  Create time vector corresponding to the input samples
 *
 * Arguments    : const double x[945176]
 *                double Fs
 *                double t[945176]
 *                double freq[472589]
 *                double fftMagnitude[472589]
 *                double stftTime[1845]
 *                double stftFreq[513]
 *                double stftMagnitude[946485]
 * Return Type  : void
 */
void genAnalysisLogic(const double x[945176], double Fs, double t[945176],
                      double freq[472589], double fftMagnitude[472589],
                      double stftTime[1845], double stftFreq[513],
                      double stftMagnitude[946485])
{
  static creal_T stftData[946485];
  static creal_T dcv[945176];
  static double dv[945176];
  static double dv1[472587];
  static const int offsets[4] = {0, 1, 2, 3};
  static int iv[472587];
  __m128d r;
  double dv2[2];
  double ai;
  double im;
  double re;
  int i;
  int i1;
  if (!isInitialized_genAnalysisLogic) {
    genAnalysisLogic_initialize();
  }
  /*  Simple matlab function for Audio Signal Analysis */
  /*  Frequency domain operations */
  /*  Calculate FFT */
  /*  Two-sided magnitude spectrum */
  /*  Single-sided magnitude spectrum */
  fft(x, dcv);
#pragma omp parallel for num_threads(omp_get_max_threads()) private(im, ai, re)

  for (i = 0; i < 945176; i++) {
    t[i] = (double)i / Fs;
    im = dcv[i].re;
    ai = dcv[i].im;
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
    dcv[i].re = re;
    dcv[i].im = im;
  }
  b_abs(dcv, dv);
  memcpy(&fftMagnitude[0], &dv[0], 472589U * sizeof(double));
  /*  Double the magnitude except DC and Nyquist components */
  r = _mm_set1_pd(2.0);
  for (i1 = 0; i1 <= 472580; i1 += 4) {
    __m128d r1;
    __m128d r2;
    _mm_storeu_si128(
        (__m128i *)&iv[i1],
        _mm_add_epi32(_mm_set1_epi32(i1 + 2),
                      _mm_loadu_si128((const __m128i *)&offsets[0])));
    r1 = _mm_loadu_pd(&fftMagnitude[i1 + 1]);
    r2 = _mm_loadu_pd(&fftMagnitude[i1 + 3]);
    _mm_storeu_pd(&dv1[i1], _mm_mul_pd(r, r1));
    _mm_storeu_pd(&dv1[i1 + 2], _mm_mul_pd(r, r2));
  }
  iv[472584] = 472586;
  dv1[472584] = 2.0 * fftMagnitude[472585];
  iv[472585] = 472587;
  dv1[472585] = 2.0 * fftMagnitude[472586];
  iv[472586] = 472588;
  dv1[472586] = 2.0 * fftMagnitude[472587];
  for (i1 = 0; i1 < 472587; i1++) {
    fftMagnitude[iv[i1] - 1] = dv1[i1];
  }
  /*  Frequency axis */
  for (i1 = 0; i1 <= 472586; i1 += 2) {
    dv2[0] = i1;
    dv2[1] = (double)i1 + 1.0;
    r = _mm_loadu_pd(&dv2[0]);
    _mm_storeu_pd(&freq[i1], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r),
                                        _mm_set1_pd(945176.0)));
  }
  freq[472588] = Fs * 472588.0 / 945176.0;
  /*  ============================================================ */
  /*  SHORT-TIME FOURIER TRANSFORM */
  /*  ============================================================ */
  /*  Window length */
  /*  50% overlap */
  /*  Calculate STFT */
  spectrogram(x, Fs, stftData, stftFreq, stftTime);
  /*  Magnitude of STFT */
  c_abs(stftData, stftMagnitude);
}

/*
 * File trailer for genAnalysisLogic.c
 *
 * [EOF]
 */
