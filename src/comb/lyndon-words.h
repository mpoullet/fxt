#if !defined  HAVE_LYNDON_WORDS_H__
#define       HAVE_LYNDON_WORDS_H__
// This file is part of the FXT library.
// Copyright (C) 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

class lyndon_words
// All Lyndon words up to length n.
// Duval's algorithm.
{
protected:
    ulong* W;  // words in W[1..n], W[0] is a sentinel
    ulong n;  // max number of letters
    ulong z;  // last (largest) letter
    ulong a;  // first (smallest) letter

public:
    lyndon_words(ulong tn, ulong ta, ulong tz)
        : n(tn), z(tz), a(ta)
    {
        if ( a > z )  // oops
        { ulong t = a;  a = z;  z = t; }

        W = new ulong[n+1];
        W[0] = z ^ 1;  // sentinel, any value != z
        first();
    }

    ~lyndon_words()  { delete [] W; }

    const ulong * data()  const  { return W + 1; }

    ulong first()
    {
        for (ulong j=1; j<=n; ++j)  W[j] = a;
        return ( n != 0 );
    }

    ulong next()
    {
        ulong i = n;
        while ( W[i] == z )  --i;  // may read sentinel W[0]
        if ( i == 0 )  return 0;   // current is last
        W[i] += 1;
        for (ulong j=1; j<=n-i; ++j)  W[i+j] = W[j];
        return i;
    }
};
// -------------------------


#endif // !defined HAVE_LYNDON_WORDS_H__
