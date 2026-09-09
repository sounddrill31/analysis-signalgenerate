/*
 * File: genAnalysisLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
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

/* Variable Definitions */
static dsp_STFT stftObj;

static boolean_T stftObj_not_empty;

/* Function Definitions */
/*
 * Time domain operations
 *  Create time vector corresponding to the input samples
 *
 * Arguments    : double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *freq
 *                emxArray_real_T *fftMagnitude
 *                double stftTime[32]
 *                double stftFreq[513]
 *                emxArray_real_T *stftMagnitude
 * Return Type  : void
 */
void genAnalysisLogic(double Fs, emxArray_real_T *t, emxArray_real_T *freq,
                      emxArray_real_T *fftMagnitude, double stftTime[32],
                      double stftFreq[513], emxArray_real_T *stftMagnitude)
{
  __m128d r3;
  emxArray_creal_T *r1;
  emxArray_real_T *r;
  creal_T stftFrame_data[513];
  creal_T *r2;
  double tmp_data[513];
  double dv[2];
  double *fftMagnitude_data;
  double *freq_data;
  double *stftMagnitude_data;
  double *t_data;
  int endIdx;
  int i;
  int k;
  if (!isInitialized_genAnalysisLogic) {
    genAnalysisLogic_initialize();
  }
  emxInit_real_T(&r, 1);
  endIdx = r->size[0];
  r->size[0] = 16384;
  emxEnsureCapacity_real_T(r, endIdx);
  emxInit_creal_T(&r1);
  endIdx = r1->size[0];
  r1->size[0] = 16384;
  emxEnsureCapacity_creal_T(r1, endIdx);
  endIdx = stftMagnitude->size[0];
  stftMagnitude->size[0] = 16416;
  emxEnsureCapacity_real_T(stftMagnitude, endIdx);
  stftMagnitude_data = stftMagnitude->data;
  endIdx = fftMagnitude->size[0];
  fftMagnitude->size[0] = 8193;
  emxEnsureCapacity_real_T(fftMagnitude, endIdx);
  fftMagnitude_data = fftMagnitude->data;
  endIdx = freq->size[0];
  freq->size[0] = 8193;
  emxEnsureCapacity_real_T(freq, endIdx);
  freq_data = freq->data;
  endIdx = t->size[0];
  t->size[0] = 16384;
  emxEnsureCapacity_real_T(t, endIdx);
  t_data = t->data;
  /*  Simple matlab function for Audio Signal Analysis */
  /*  Frequency domain operations */
  /*  Calculate FFT */
  /*  Two-sided magnitude spectrum */
  /*  Single-sided magnitude spectrum */
  fft(r1);
  r2 = r1->data;
  for (i = 0; i < 16384; i++) {
    double ai;
    double im;
    double re;
    t_data[i] = (double)i / Fs;
    im = r2[i].re;
    ai = r2[i].im;
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
    r2[i].re = re;
    r2[i].im = im;
  }
  b_abs(r1, r);
  t_data = r->data;
  emxFree_creal_T(&r1);
  for (i = 0; i < 8193; i++) {
    fftMagnitude_data[i] = t_data[i];
  }
  emxFree_real_T(&r);
  /*  Double the magnitude except DC and Nyquist components */
  for (i = 0; i <= 8188; i += 2) {
    _mm_storeu_pd(
        &fftMagnitude_data[i + 1],
        _mm_mul_pd(_mm_set1_pd(2.0), _mm_loadu_pd(&fftMagnitude_data[i + 1])));
  }
  fftMagnitude_data[8191] *= 2.0;
  /*  Frequency axis */
  for (i = 0; i <= 8190; i += 2) {
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r3 = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&freq_data[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r3),
                                            _mm_set1_pd(16384.0)));
  }
  freq_data[8192] = Fs * 8192.0 / 16384.0;
  /* Short Time Fourier Transform Chart */
  /*  each hop carries 512 samples */
  if (!stftObj_not_empty) {
    STFT_STFT(&stftObj);
    stftObj_not_empty = true;
  }
  /*  513 */
  for (i = 0; i <= 510; i += 2) {
    dv[0] = i;
    dv[1] = (double)i + 1.0;
    r3 = _mm_loadu_pd(&dv[0]);
    _mm_storeu_pd(&stftFreq[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(Fs), r3),
                                           _mm_set1_pd(1024.0)));
  }
  stftFreq[512] = Fs * 512.0 / 1024.0;
  /*  populate the audio stream 512 samples at a time */
  emxInit_real_T(&stftMagnitude, 1);
  for (k = 0; k < 32; k++) {
    int loop_ub;
    int startIdx;
    startIdx = k << 9;
    endIdx = (k + 1) << 9;
    /*  Extract the 512-sample chunk */
    if (startIdx + 1 > endIdx) {
      loop_ub = 0;
      endIdx = 0;
    } else {
      loop_ub = startIdx;
    }
    loop_ub = endIdx - loop_ub;
    endIdx = stftMagnitude->size[0];
    stftMagnitude->size[0] = loop_ub;
    emxEnsureCapacity_real_T(stftMagnitude, endIdx);
    t_data = stftMagnitude->data;
    for (i = 0; i < loop_ub; i++) {
      t_data[i] = 0.0;
    }
    int stftFrame_size[2];
    int tmp_size[2];
    STFT_step(&stftObj, stftMagnitude, stftFrame_data, stftFrame_size);
    /*  Store the results */
    c_abs(stftFrame_data, stftFrame_size, tmp_data, tmp_size);
    for (i = 0; i < 513; i++) {
      stftMagnitude_data[i + 513 * k] = tmp_data[i];
    }
    stftTime[k] = (((double)startIdx + 1.0) + 512.0) / Fs;
  }
  emxFree_real_T(&stftMagnitude);
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
