/*
 * File: genAnalysisLogic_emxutil.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 15:36:09
 */

#ifndef GENANALYSISLOGIC_EMXUTIL_H
#define GENANALYSISLOGIC_EMXUTIL_H

/* Include Files */
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"
#include <stddef.h>
#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif

/* Function Declarations */
extern void emxEnsureCapacity_creal_T(emxArray_creal_T *emxArray, int oldNumel);

extern void emxEnsureCapacity_real_T(emxArray_real_T *emxArray, int oldNumel);

extern void emxFree_creal_T(emxArray_creal_T **pEmxArray);

extern void emxFree_real_T(emxArray_real_T **pEmxArray);

extern void emxInit_creal_T(emxArray_creal_T **pEmxArray);

extern void emxInit_real_T(emxArray_real_T **pEmxArray, int numDimensions);

#ifdef __cplusplus
}
#endif

#endif
/*
 * File trailer for genAnalysisLogic_emxutil.h
 *
 * [EOF]
 */
