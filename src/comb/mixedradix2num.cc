// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

ulong
mixedradix2num(const ulong *x, const ulong *m1, ulong n)
// Convert n-digit mixed radix number in x[] to (unsigned) integer.
// Radices minus one (that is, "nines") must be given in m1[].
{
    ulong r = 0;
    ulong p = 1;  // multiplier

    for (ulong k=0; k<n; ++k)
    {
        const ulong t = x[k];
        r += p * t;
        p *= m1[k] + 1;  // nines are given
    }

    return r;
}
// -------------------------

void
num2mixedradix(ulong N, ulong *x, const ulong *m1, ulong n)
// Convert N to n-digit mixed radix number in x[].
// Radices minus one (that is, "nines") must be given in m1[].
{
    for (ulong k=0; k<n; ++k)
    {
        const ulong t = m1[k] + 1;  // nines are given
        x[k] = N % t;
        N /= t;
    }
}
// -------------------------
