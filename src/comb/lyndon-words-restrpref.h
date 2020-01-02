#if !defined  HAVE_LYNDON_WORDS_RESTRPREF_H__
#define       HAVE_LYNDON_WORDS_RESTRPREF_H__
// This file is part of the FXT library.
// Copyright (C) 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/lyndon-words.h"

#include "fxttypes.h"
#include "fxtio.h"

class lyndon_words_restrpref : private lyndon_words
// Lyndon words up to length n with restricted prefixes.
{
protected:
    typedef bool (* cond_func)(const ulong*, ulong);
    cond_func cond { nullptr };  // condition function, one-based(!)

    ulong cidx;  // index of leftmost change

public:
    using lyndon_words::data_0;
    using lyndon_words::data_1;
    using lyndon_words::is_necklace;
    using lyndon_words::is_lyndon_word;
    // but not using next()

    lyndon_words_restrpref(ulong tn, ulong ta, ulong tz)
        : lyndon_words( tn, ta, tz )
    {
    }

    ~lyndon_words_restrpref()  {;}

    ulong change_idx()  const { return cidx; }

    ulong first( cond_func cnd )
    {
        cond = cnd;

        cidx = 1;

        lyndon_words::first();

        const ulong * x1 = data_1();
        for (ulong i = 1; i <= n; ++i)  // check digits
            if ( ! cond( x1, i ) )
                return try_next_at( i );

        return ii;
    }

protected:
    ulong try_next_at( ulong k )
    // Compute next word with (at least) positions starting
    //   at position i (one-based) are changed.
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
        const ulong * x1 = data_1();

    redo:
        lyndon_words::next_at( k );
        if ( ii < cidx )  cidx = ii;

        if ( ii == 0 )  return 0;

        for (ulong i = ii; i <= n; ++i)
        {
            if ( ! cond( x1, i )  )  // check digits
            {
                k = i;
                goto redo;
            }
        }

        return ii;
    }

public:
    ulong next_any()
    // Next pre-necklace.
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
        cidx = n;
        return try_next_at( n );
    }

    ulong next_necklace()
    // Next pre-necklace.
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
        cidx = n;
        do
        {
            try_next_at( n );
            if ( ii == 0 )  return 0;
        }
        while ( ! is_necklace() );
        return ii;
    }

    ulong next_lyndon_word()
    // Next pre-necklace.
    // Return position (one-based) of leftmost change.
    // Preserved prefix is 0 ... i - 1 (zero-based) or 1 ... i (one-based).
    // Return zero with last element.
    {
        cidx = n;
        do
        {
            try_next_at( n );
            if ( ii == 0 )  return 0;
        }
        while ( ! is_lyndon_word() );
        return ii;
    }
};
// -------------------------


#endif // !defined HAVE_LYNDON_WORDS_RESTRPREF_H__
