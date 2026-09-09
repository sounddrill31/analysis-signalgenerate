/*
 * File: _coder_genAnalysisLogic_mex.c
 *
 * MATLAB Coder version            : 26.1
 * C/C++ source code generated on  : 09-Sep-2026 16:05:27
 */

/* Include Files */
#include "_coder_genAnalysisLogic_mex.h"
#include "_coder_genAnalysisLogic_api.h"

/* Function Definitions */
/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[]
 *                int32_T nrhs
 *                const mxArray *prhs[]
 * Return Type  : void
 */
void mexFunction(int32_T nlhs, mxArray *plhs[], int32_T nrhs,
                 const mxArray *prhs[])
{
  mexAtExit(&genAnalysisLogic_atexit);
  genAnalysisLogic_initialize();
  unsafe_genAnalysisLogic_mexFunction(nlhs, plhs, nrhs, prhs);
  genAnalysisLogic_terminate();
}

/*
 * Arguments    : void
 * Return Type  : emlrtCTX
 */
emlrtCTX mexFunctionCreateRootTLS(void)
{
  emlrtCreateRootTLSR2022a(&emlrtRootTLSGlobal, &emlrtContextGlobal, NULL, 1,
                           NULL, "UTF-8", true);
  return emlrtRootTLSGlobal;
}

/*
 * Arguments    : int32_T nlhs
 *                mxArray *plhs[6]
 *                int32_T nrhs
 *                const mxArray *prhs[2]
 * Return Type  : void
 */
void unsafe_genAnalysisLogic_mexFunction(int32_T nlhs, mxArray *plhs[6],
                                         int32_T nrhs, const mxArray *prhs[2])
{
  emlrtStack st = {
      NULL, /* site */
      NULL, /* tls */
      NULL  /* prev */
  };
  const mxArray *outputs[6];
  int32_T i;
  st.tls = emlrtRootTLSGlobal;
  /* Check for proper number of arguments. */
  if (nrhs != 2) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:WrongNumberOfInputs", 5, 12, 2, 4,
                        16, "genAnalysisLogic");
  }
  if (nlhs > 6) {
    emlrtErrMsgIdAndTxt(&st, "EMLRT:runTime:TooManyOutputArguments", 3, 4, 16,
                        "genAnalysisLogic");
  }
  /* Call the function. */
  genAnalysisLogic_api(prhs, nlhs, outputs);
  /* Copy over outputs to the caller. */
  if (nlhs < 1) {
    i = 1;
  } else {
    i = nlhs;
  }
  emlrtReturnArrays(i, &plhs[0], &outputs[0]);
}

/*
 * File trailer for _coder_genAnalysisLogic_mex.c
 *
 * [EOF]
 */
