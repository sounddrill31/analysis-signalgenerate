/* Copyright 2024 The MathWorks, Inc. */
#ifndef SPATIALMATH_CPP_UTILS_SPEC_HPP
#define SPATIALMATH_CPP_UTILS_SPEC_HPP


#ifdef BUILDING_SPATIALMATH_CPP_UTILS
#include "package.h"
#include "tmwtypes.h"
#define SPATIALMATH_CPP_UTILS_API DLL_EXPORT_SYM

#else

#if defined(MATLAB_MEX_FILE) || defined(BUILDING_UNITTEST)
#include "tmwtypes.h"
#else
#include "rtwtypes.h"
#endif // defined(MATLAB_MEX_FILE) || defined(BUILDING_UNITTEST)

#ifndef SPATIALMATH_CPP_UTILS_API
#define SPATIALMATH_CPP_UTILS_API
#endif // SPATIALMATH_CPP_UTILS_API

#endif // BUILDING_SPATIALMATH_CPP_UTILS

#ifndef EXTERN_C
#ifdef __cplusplus
#define EXTERN_C extern "C"
#else
#define EXTERN_C
#endif
#endif

#endif // SPATIALMATH_CPP_UTILS_SPEC_HPP

// EOF
