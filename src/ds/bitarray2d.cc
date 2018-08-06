// This file is part of the FXT library.
// Copyright (C) 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "ds/bitarray2d.h"

#include "fxtio.h"
#include "fxttypes.h"


void
bitarray2d::dump_bits()  const
{
    for (ulong y=0; y< dy_; ++y)
    {
        const bitarray * R = rowp_[y];
#if 1
        R->dump_bits( false );
#else
        for (ulong x=0; x<dx__; ++y)
            cout << ( R->test(x) ? '1' : '.' );
#endif
        cout << endl;
    }
}
// -------------------------
