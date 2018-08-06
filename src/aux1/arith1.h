#if !defined HAVE_ARITH1_H__
#define      HAVE_ARITH1_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"


template <typename Type>
inline void negate(Type *f, ulong n)
// negate every element of f[]
{
    for (ulong j=0; j<n; ++j)  f[j] = -f[j];
}
// -------------------------

template <typename Type>
inline void multiply_val(Type *f, ulong n, Type s)
// f[] *= s
{
    for (ulong j=0; j<n; ++j)  f[j] *= s;
}
// -------------------------

template <typename Type>
inline void add(Type *f, ulong n, const Type *g)
// f[] += g[] element-wise
{
    for (ulong j=0; j<n; ++j)  f[j] += g[j];
}
// -------------------------

template <typename Type>
inline void subtract(Type *f, ulong n, const Type *g)
// f[] -= g[] element-wise
{
    for (ulong j=0; j<n; ++j)  f[j] -= g[j];
}
// -------------------------


template <typename Type>
inline void multiply(Type *f, ulong n, const Type *g)
//  f[] *= g[] element-wise
{
    for (ulong j=0; j<n; ++j)  f[j] *= g[j];
}
// -------------------------


#endif  // !defined HAVE_ARITH1_H__
