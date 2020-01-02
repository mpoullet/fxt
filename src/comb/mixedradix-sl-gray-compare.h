#if !defined  HAVE_MIXEDRADIX_SL_GRAY_COMPARE_H__
#define       HAVE_MIXEDRADIX_SL_GRAY_COMPARE_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

template <typename Type>
inline int mixedradix_sl_gray_compare(const Type *a, const Type *b, ulong n,
                                      const ulong *m1)
// Compare a[] and b[] with respect to SL-Gray order.
// Return +1 if a[] >> b[], -1 if a[] << b[], 0 if a[]==b[].
// m1[] must be the array of nines.
{
    ulong ea = 0;  // last index such that a[ea-1] != 0
    for (ulong j=0; j<n; ++j)
        if ( a[j] != 0 )  ea = j + 1;

    ulong eb = 0;  // last index such that b[eb-1] != 0
    for (ulong j=0; j<n; ++j)
        if ( b[j] != 0 )  eb = j + 1;

    bool d = false;
    const ulong m = (ea < eb ? ea : eb);  // min(ea, eb)
    for (ulong j=0; j<m; ++j)
    {
        const ulong aj = a[j],  bj = b[j];

        if ( aj != bj )
        {
            int q;
            if ( aj < bj )
            {
                if ( j == ea-1 )  q = -1;
                else              q = +1;
            }
            else  // bj < aj
            {
                if ( j == eb-1 )  q = +1;
                else              q = -1;
            }

            if ( d )  q = -q;

            return q;
        }

        if ( j != m - 1 ) // only if not at end
        {
            // Switch d if parity(digit) != parity(nine)
            // (equivalently  parity(digit) == parity(radix) ).
            const ulong ap = aj & 1UL;
            const ulong mp = m1[j] & 1UL;
            if ( ap != mp )  d = !d;
        }
    }

    if ( ea == eb )  return 0;

    int q = ( ea > eb ? +1 : -1 );

    if ( d )  q = -q;

    return q;
}
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_SL_GRAY_COMPARE_H__
