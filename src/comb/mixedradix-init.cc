// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


void
mixedradix_init(ulong n, ulong mm, const ulong *m, ulong *m1)
// Auxiliary function used to initialize vector of nines in mixed radix classes.
{
    if ( m != nullptr )  // all radices given
    {
        for (ulong k=0; k<n; ++k)
        {
            m1[k] = (m[k] >= 2 ? m[k] - 1 : 1);  // avoid hang with radix < 2
        }
    }
    else
    {
        if ( mm>1 )  // use mm as radix for all digits:
            for (ulong k=0; k<n; ++k)  m1[k] = mm - 1;
        else
        {
            if ( mm==0 )  // falling factorial base
                for (ulong k=0; k<n; ++k)  m1[k] = n - k;
            else  // rising factorial base
                for (ulong k=0; k<n; ++k)  m1[k] = k + 1;
        }
    }
}
// -------------------------

