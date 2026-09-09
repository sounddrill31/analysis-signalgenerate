/*
 * File: genTriangleLogic_types.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 30-Aug-2026 22:16:07
 */

#ifndef GENTRIANGLELOGIC_TYPES_H
#define GENTRIANGLELOGIC_TYPES_H

/* Include Files */
#include "rtwtypes.h"

/* Type Definitions */
#ifndef struct_emxArray_real_T
#define struct_emxArray_real_T
struct emxArray_real_T {
  double *data;
  int *size;
  int allocatedSize;
  int numDimensions;
  boolean_T canFreeData;
};
#endif /* struct_emxArray_real_T */
#ifndef typedef_emxArray_real_T
#define typedef_emxArray_real_T
typedef struct emxArray_real_T emxArray_real_T;
#endif /* typedef_emxArray_real_T */

#endif
/*
 * File trailer for genTriangleLogic_types.h
 *
 * [EOF]
 */
