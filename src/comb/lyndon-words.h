#if !defined  HAVE_LYNDON_WORDS_H__
#define       HAVE_LYNDON_WORDS_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

class lyndon_words
// Lyndon words up to length n.
// Duval's algorithm.
{
protected:
    ulong * W { nullptr };  // words in W[1..n], W[0] is a sentinel
    ulong n;  // max number of letters
    ulong z;  // last (largest) letter
    ulong a;  // first (smallest) letter
    ulong ii;  // value returned by next() (or next_at())
    bool * Q { nullptr };  // Q[k]: whether k divides n

public:
    lyndon_words(ulong tn, ulong ta, ulong tz)
        :
        n(tn), z(tz), a(ta)
    {
        if ( a > z )  // oops
        { ulong t = a;  a = z;  z = t; }

        W = new ulong[ n + 1 ];
        W[0] = ! z;  // sentinel, any value != z

        Q = new bool[ n + 1 ];
        Q[ 0 ] = true;  // unused, except for n == 0
        for (ulong j=1; j<=n; ++j)  Q[ j ] = ( 0 == (n % j) );

        first();
    }

    ~lyndon_words()
    {
        delete [] W;
        delete [] Q;
    }

    const ulong * data_0()  const  { return W + 1; }  // zero-based
    const ulong * data_1()  const  { return W; }      // one-based

    bool is_necklace()  const
    // Return whether necklace (or Lyndon word) for length n.
    { return Q[ii]; }

    bool is_lyndon_word()  const
    // Return whether Lyndon word of length n.
    { return ( ii == n ); }

    ulong first()
    {
        for (ulong j=1; j<=n; ++j)  W[j] = a;
        ii = ( n != 0 );
        return ii;
    }

    ulong next_at(ulong i)
    // Compute next word with (at least) positions starting
    //   at position i (one-based) are changed.
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
//        ulong i = n;
        while ( W[i] == z )  --i;  // may read sentinel W[0]
        ii = i;
        if ( i == 0 )  return 0;   // current is last
        W[i] += 1;
        for (ulong j=1; j<=n-i; ++j)  W[i+j] = W[j];
        return i;
    }

    ulong next()
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
        return next_at(n);
    }
};
// -------------------------


#endif // !defined HAVE_LYNDON_WORDS_H__
