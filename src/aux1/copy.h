#if !defined HAVE_COPY_H__
#define      HAVE_COPY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2013, 2016, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"
#include "complextype.h"
#include <cstring>  // memcpy(), memset()


template <typename Type>
inline void memzero(Type *dst, ulong n)
// Set array (memory) to zero (bytes).
{
    memset(dst, 0, n * sizeof(Type));
}
// -------------------------


template <typename Type>
inline void fill(Type *dst, ulong n, Type v)
// Fill array with value v
{
    if ( n&1 ) { *dst++ = v; }
    n >>= 1;
    if ( n&1 ) { *dst++ = v;  *dst++ = v; }
    n >>= 1;
    while ( n-- )
    {
        dst[0] = v;
        dst[1] = v;
        dst[2] = v;
        dst[3] = v;
        dst += 4;
    }
}
// -------------------------


template <typename Type>
inline void null(Type *dst, ulong n)
// Set array to zero.
// If the element zero consists of zero bytes only,
// then prefer memzero().
{
    const Type z(0);
    fill(dst, n, z);
}
// -------------------------

// Types where zero is binary zero:
inline void null(Complex *dst, ulong n)  { memzero(dst, n); }
inline void null(double *dst, ulong n)  { memzero(dst, n); }
inline void null(float *dst, ulong n)  { memzero(dst, n); }
inline void null(ulong *dst, ulong n)  { memzero(dst, n); }
inline void null(long *dst, ulong n)  { memzero(dst, n); }
inline void null(int *dst, ulong n)  { memzero(dst, n); }
inline void null(uint *dst, ulong n)  { memzero(dst, n); }
inline void null(char *dst, ulong n)  { memzero(dst, n); }


template <typename Type>
inline void memcopy(const Type *src, Type *dst, ulong n)
// Copy array (memory) src[] to dst[]
{
    memcpy(dst, src, n*sizeof(Type));
}
// -------------------------

template <typename Type>
inline void acopy(const Type *src, Type *dst, ulong n)
// Copy array src[] to dst[]
// Named acopy() to avoid conflict with std::copy()
{
    if ( n&1 ) { *dst++ = *src++; }
    n >>= 1;
    if ( n&1 ) { *dst++ = *src++;  *dst++ = *src++; }
    n >>= 1;
    while ( n-- )
    {
        dst[0] = src[0];
        dst[1] = src[1];
        dst[2] = src[2];
        dst[3] = src[3];
        dst += 4;
        src += 4;
    }
}
// -------------------------

// Types where copy is memory copy:
inline void acopy(const Complex *src, Complex *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const double *src, double *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const float *src, float *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const ulong *src, ulong *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const long *src, long *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const int *src, int *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const uint *src, uint *dst, ulong n) { memcopy(src, dst, n); }
inline void acopy(const char *src, char *dst, ulong n) { memcopy(src, dst, n); }


template <typename Type1, typename Type2>
inline void copy_cast(const Type1 *src, Type2 *dst, ulong n)
// Copy array src[] to dst[]
{
    for (ulong k=0; k<n; ++k)  dst[k] = (Type2)src[k];  // jjcast
}
// -------------------------


template <typename Type1, typename Type2>
inline void copy0(const Type1 *src, ulong ns,
                  Type2 *dst, ulong nd)
// Copy as much as makes sense, fill rest with zeros
// from src[] (length ns) to dst[] (length nd).
{
    ulong k = 0;
    ulong n = ( nd<ns ? nd : ns );  // == min(nd, ns);
//    for (k=0; k<n; ++k)  dst[k] = (Type2)src[k];
//    for (  ; k<nd; ++k)  dst[k] = (Type2)0;
    copy_cast(src, dst, n);
    if ( k<nd )  null(dst+n, nd-n);
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
    ulong k = 0;
    while ( s<n )  dst[k++] = src[s++];

    s = 0;
    while ( k<n )  dst[k++] = src[s++];
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
inline void swap(Type *f, Type *g, ulong n)
// Swap arrays
{
    for (ulong k=0; k<n; ++k)
    {
        Type t = f[k];  f[k] = g[k];  g[k] = t;
    }
}
// -------------------------


template <typename Type>
inline void set_seq(Type *dst, ulong n, Type start=0, Type step=1)
// Fill array with sequence
//   start, start+step, start+2*step, ...
{
    for (ulong k=0; k<n; ++k)
    {
        dst[k] = start;
        start += step;
    }
}
// -------------------------



#endif  // !defined HAVE_COPY_H__
