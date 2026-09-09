/*
 * File: genTriangleLogic.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Aug-2026 22:16:07
 */

/* Include Files */
#include "genTriangleLogic.h"
#include "abs.h"
#include "colon.h"
#include "genTriangleLogic_emxutil.h"
#include "genTriangleLogic_types.h"
#include "minOrMax.h"
#include "rt_nonfinite.h"
#include "sawtooth.h"
#include "rt_nonfinite.h"
#include <emmintrin.h>
#include <math.h>

/* Function Definitions */
/*
 * hack to allow memory size of t and x to grow
 *
 * Arguments    : double A
 *                double f
 *                double duration
 *                double Fs
 *                emxArray_real_T *t
 *                emxArray_real_T *x
 *                double *samples
 *                double *cycles
 * Return Type  : void
 */
void genTriangleLogic(double A, double f, double duration, double Fs,
                      emxArray_real_T *t, emxArray_real_T *x, double *samples,
                      double *cycles)
{
  __m128d r;
  emxArray_real_T *b;
  emxArray_real_T *b_t;
  emxArray_real_T *r1;
  double dv[2];
  double d;
  double *a_data;
  double *t_data;
  double *x_data;
  int i;
  int loop_ub;
  int scalarLB;
  int vectorUB;
  /*  SImple matlab function script to generate Triangle Wave */
  /*  We're using the time vector t to generate enough slots, one for each */
  /*  sample based on the frequency and duration */
  d = 1.0 / Fs;
  emxInit_real_T(&b_t, 2);
  x_data = b_t->data;
  if (rtIsNaN(d) || rtIsNaN(duration)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    x_data = b_t->data;
    x_data[0] = rtNaN;
  } else if ((d == 0.0) || ((duration > 0.0) && (d < 0.0)) ||
             ((duration < 0.0) && (d > 0.0))) {
    b_t->size[0] = 1;
    b_t->size[1] = 0;
  } else if (rtIsInf(duration) && rtIsInf(d)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    x_data = b_t->data;
    x_data[0] = rtNaN;
  } else if (rtIsInf(d)) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    b_t->size[1] = 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    x_data = b_t->data;
    x_data[0] = 0.0;
  } else if (floor(d) == d) {
    scalarLB = b_t->size[0] * b_t->size[1];
    b_t->size[0] = 1;
    loop_ub = (int)(duration / d);
    b_t->size[1] = loop_ub + 1;
    emxEnsureCapacity_real_T(b_t, scalarLB);
    x_data = b_t->data;
    scalarLB = ((loop_ub + 1) / 2) << 1;
    vectorUB = scalarLB - 2;
    for (i = 0; i <= vectorUB; i += 2) {
      dv[0] = i;
      dv[1] = i + 1;
      r = _mm_loadu_pd(&dv[0]);
      _mm_storeu_pd(&x_data[i], _mm_mul_pd(_mm_set1_pd(d), r));
    }
    for (i = scalarLB; i <= loop_ub; i++) {
      x_data[i] = d * (double)i;
    }
  } else {
    eml_float_colon(d, duration, b_t);
    x_data = b_t->data;
  }
  if (b_t->size[1] - 1 < 1) {
    loop_ub = 0;
  } else {
    loop_ub = b_t->size[1] - 1;
  }
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = loop_ub;
  emxEnsureCapacity_real_T(t, scalarLB);
  t_data = t->data;
  /*  now we simply use to sawtooth function to generate a wave with w =
   * 2*pi*f*t and at half interval(where A is the amplitude)  */
  d = 6.283185307179586 * f;
  emxInit_real_T(&t, 2);
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  t->size[1] = loop_ub;
  emxEnsureCapacity_real_T(t, scalarLB);
  a_data = t->data;
  scalarLB = (loop_ub / 2) << 1;
  vectorUB = scalarLB - 2;
  for (i = 0; i <= vectorUB; i += 2) {
    r = _mm_loadu_pd(&x_data[i]);
    _mm_storeu_pd(&t_data[i], r);
    _mm_storeu_pd(&a_data[i], _mm_mul_pd(_mm_set1_pd(d), r));
  }
  for (i = scalarLB; i < loop_ub; i++) {
    double b_d;
    b_d = x_data[i];
    t_data[i] = b_d;
    a_data[i] = d * b_d;
  }
  emxFree_real_T(&b_t);
  emxInit_real_T(&b, 2);
  sawtooth(t, b);
  t_data = b->data;
  /*  Normalize the wave to ensure it fits within the amplitude range */
  scalarLB = t->size[0] * t->size[1];
  t->size[0] = 1;
  loop_ub = b->size[1];
  t->size[1] = b->size[1];
  emxEnsureCapacity_real_T(t, scalarLB);
  a_data = t->data;
  vectorUB = (b->size[1] / 2) << 1;
  scalarLB = vectorUB - 2;
  for (i = 0; i <= scalarLB; i += 2) {
    _mm_storeu_pd(&a_data[i],
                  _mm_mul_pd(_mm_set1_pd(A), _mm_loadu_pd(&t_data[i])));
  }
  for (i = vectorUB; i < loop_ub; i++) {
    a_data[i] = A * t_data[i];
  }
  emxInit_real_T(&r1, 2);
  b_abs(t, r1);
  emxFree_real_T(&t);
  d = maximum(r1);
  emxFree_real_T(&r1);
  scalarLB = x->size[0] * x->size[1];
  x->size[0] = 1;
  x->size[1] = b->size[1];
  emxEnsureCapacity_real_T(x, scalarLB);
  x_data = x->data;
  scalarLB = vectorUB - 2;
  for (i = 0; i <= scalarLB; i += 2) {
    _mm_storeu_pd(&x_data[i], _mm_div_pd(_mm_mul_pd(_mm_set1_pd(A),
                                                    _mm_loadu_pd(&t_data[i])),
                                         _mm_set1_pd(d)));
  }
  for (i = vectorUB; i < loop_ub; i++) {
    x_data[i] = A * t_data[i] / d;
  }
  emxFree_real_T(&b);
  /*  take samples from first to cycles for initial plotting */
  d = 2.0 * Fs / f;
  if (fabs(d) < 4.503599627370496E+15) {
    if (d >= 0.5) {
      d = floor(d + 0.5);
    } else if (d > -0.5) {
      d *= 0.0;
    } else {
      d = ceil(d - 0.5);
    }
  }
  d = fmin(d, x->size[1]);
  *samples = d;
  *cycles = 2.0;
}

/*
 * File trailer for genTriangleLogic.c
 *
 * [EOF]
 */
