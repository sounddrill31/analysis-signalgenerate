/*
 * File: genAnalysisLogic_internal_types.h
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 17:33:27
 */

#ifndef GENANALYSISLOGIC_INTERNAL_TYPES_H
#define GENANALYSISLOGIC_INTERNAL_TYPES_H

/* Include Files */
#include "genAnalysisLogic_types.h"
#include "rtwtypes.h"

/* Type Definitions */
#ifndef typedef_cell_wrap_2
#define typedef_cell_wrap_2
typedef struct {
  unsigned int f1[8];
} cell_wrap_2;
#endif /* typedef_cell_wrap_2 */

#ifndef c_typedef_c_dsp_internal_codege
#define c_typedef_c_dsp_internal_codege
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  cell_wrap_2 inputVarSize[1];
  double Cache[1025];
  int CumulativeOverrun;
  int CumulativeUnderrun;
  int ReadPointer;
  int WritePointer;
} c_dsp_internal_codegen_AsyncBuf;
#endif /* c_typedef_c_dsp_internal_codege */

#ifndef typedef_dsp_AsyncBuffer
#define typedef_dsp_AsyncBuffer
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  c_dsp_internal_codegen_AsyncBuf pBuffer;
} dsp_AsyncBuffer;
#endif /* typedef_dsp_AsyncBuffer */

#ifndef c_typedef_dsp_internal_codegen_
#define c_typedef_dsp_internal_codegen_
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  int isInitialized;
  boolean_T isSetupComplete;
  boolean_T TunablePropsChanged;
  cell_wrap_2 inputVarSize[1];
  double Window[1024];
  dsp_AsyncBuffer pBuff;
  double pWindow[1024];
} dsp_internal_codegen_STFTSysObj;
#endif /* c_typedef_dsp_internal_codegen_ */

#ifndef typedef_dsp_STFT
#define typedef_dsp_STFT
typedef struct {
  boolean_T matlabCodegenIsDeleted;
  dsp_internal_codegen_STFTSysObj pObj;
} dsp_STFT;
#endif /* typedef_dsp_STFT */

#endif
/*
 * File trailer for genAnalysisLogic_internal_types.h
 *
 * [EOF]
 */
