#if !defined  HAVE_PERMRAND_NCM2_H__
#define       HAVE_PERMRAND_NCM2_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"
#include "aux0/rand-idx.h"

template <typename Type>
void random_permute_ncm2(Type *x, ulong n, ulong r, ulong *tf=nullptr)
// Apply random permutation with number of cycles == r mod 2
// ncm2 := Number of Cycles Modulo 2
// Must have n>=2.
{
    if ( n<=1 )  return;  // OK only if r==1

    ulong *f = tf;
    if ( tf==nullptr )  f = new ulong[n];

    for (ulong j=0; j<n-1; ++j)  f[j] = rand_idx(j+2);

    ulong z = 1;  // number cycles in factorial number
    for (ulong j=0; j<n-1; ++j)  z += (f[j] == 0);
    z &= 1;  // mod 2
    if ( z!=r )  f[0] = 1 - f[0];  // adjust num cycles mod 2

    rfact2perm_swp_apply(f, n, x);

    if ( tf==nullptr )  delete [] f;
}
// -------------------------


inline void random_ncm2_permutation(ulong *p, ulong n, ulong r, ulong *tf=nullptr)
// Generate a random permutation with number of cycles == r mod 2
// ncm2 := Number of Cycles Modulo 2
// Must have n>=2.
{
#if 1
    for (ulong k=0; k<n; ++k)  p[k] = k;  // identity
    random_permute_ncm2(p, n, r, tf);

#else
    if ( n<=1 )
    {
        if ( n==1 )  p[0] = 0;  // OK only if r==1
        return;
    }

    ulong *f = tf;
    if ( tf==nullptr )  f = new ulong[n];

    for (ulong j=0; j<n-1; ++j)  f[j] = rand_idx(j+2);

    ulong z = 1;  // number cycles in factorial number
    for (ulong j=0; j<n-1; ++j)  z += (f[j] == 0);
    z &= 1;  // mod 2
    if ( z!=r )  f[0] = 1 - f[0];  // adjust num cycles mod 2

    rfact2perm_swp(f, n, p);

    if ( tf==nullptr )  delete [] f;
#endif
}
// -------------------------


#endif  // !defined HAVE_PERMRAND_NCM2_H__
