#if !defined HAVE_COPY_H__
#define      HAVE_COPY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2016, 2017, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#include <algorithm>  // std::fill
#include <numeric>  // std::iota


template <typename Type>
inline void fill(Type *dst, ulong n, Type v)
// Fill array with value v
{
    std::fill( dst, dst + n, v );
}
// -------------------------


template <typename Type>
inline void null(Type *dst, ulong n)
// Set array to zero.
{
    std::fill( dst, dst + n, Type(0) );
}
// -------------------------


template <typename Type>
inline void acopy(const Type *src, Type *dst, ulong n)
// Copy array src[] to dst[]
// Named acopy() to avoid conflict with std::copy()
{
    std::copy( src, src + n, dst );
}
// -------------------------


template <typename Type>
inline void copy_cyclic(const Type *src, Type *dst, ulong n, ulong s)
// Copy array src[] to dst[]
// starting from position s in src[]
// wrap around end of src[]  (src[n-1])
//
// src[] is assumed to be of length n
// dst[] must be of length n at least
//
// Equivalent to:  { acopy(src, dst, n); rotate_right(dst, n, s); }
{
    std::rotate_copy( src, src + s, src + n, dst );
//    ulong k = 0;
//    while ( s<n )  dst[k++] = src[s++];
//    s = 0;
//    while ( k<n )  dst[k++] = src[s++];
}
// -------------------------


template <typename Type>
inline void skip_copy(const Type *src, Type *dst, ulong n, ulong d)
// Copy n elements from src[] at positions
//   [0],[d],[2d],[3d],...,[(n-1)*d]
//   to dst[0, 1, ..., n-1]
{
    for (ulong k=0, j=0; j<n; k+=d, j++)  dst[j] = src[k];
}
// -------------------------


template <typename Type>
inline void skip_copy_back(const Type *src, Type *dst, ulong n, ulong d)
// Copy n elements from src[0, 1, ..., n-1]
//   to dst[] at positions
//   [0],[d],[2d],[3d],...,[(n-1)*d]
{
    for (ulong k=0, j=0; j<n; k+=d, j++)  dst[k] = src[j];
}
// -------------------------


template <typename Type>
inline void set_seq(Type *dst, ulong n, Type start=0)
// Fill array with sequence
//   start, start+1, start+1, ...
{
    std::iota( dst, dst + n, start );
}
// -------------------------



#endif  // !defined HAVE_COPY_H__
