/*
 * Copyright 2015-2025 The MathWorks, Inc.
 * All Rights Reserved.
 */

#ifndef POLYFUN_POLYGON_BOOLEAN_H
#define POLYFUN_POLYGON_BOOLEAN_H

/**
 * This file is to support codegen, copied from emlrt.h
 * This file is published to (matlabroot)/extern/include
 */

#if defined(_MSC_VER)
# pragma once
#endif
#if defined(__GNUC__) && (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ > 3))
# pragma once
#endif

/*
 * Only define EXTERN_C if it hasn't been defined already. This allows
 * individual modules to have more control over managing their exports.
 */
#ifndef EXTERN_C

#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C extern
#endif

#endif

#ifndef POLYFUN_MODULE_API
#define POLYFUN_MODULE_API
#endif

EXTERN_C POLYFUN_MODULE_API 
void polyBoolean_c(double *x1, double *y1, int *size1,
                   double *x2, double *y2, int *size2,
                   double *input_scale_p, int *op_type,
                   double *rx, double *ry, int *rn,
                   double *pPgon, double *pCon, double *pIdx);
#endif
