#if !defined  HAVE_MIXEDRADIX_SUBSET_LEX_RANK_H__
#define       HAVE_MIXEDRADIX_SUBSET_LEX_RANK_H__
// This file is part of the FXT library.
// Copyright (C) 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


class mixedradix_subset_lex_rank
// Ranking and unranking function for subset-lex order.
{
protected:
    const ulong * A;   // digits
    const ulong * m1;  // nines
    const ulong n;     // number of digits
    ulong * Jmp {nullptr};  // jump sizes

    mixedradix_subset_lex_rank(const mixedradix_subset_lex_rank &) = delete;
    mixedradix_subset_lex_rank & operator=(const mixedradix_subset_lex_rank &) = delete;

public:
    mixedradix_subset_lex_rank( const ulong *tA,  // digits
                                ulong tn,         // number of digits
                                const ulong *tm1  // nines
                                )
        : A( tA ),
          m1( tm1 ),
          n( tn )
    {
        Jmp = new ulong[n];
        for (ulong j=0; j < n; ++j)
        {
            ulong p = 1;  // product of all radices from index j+1 to end
            for (ulong k=j+1; k < n; ++k)  p *= ( 1 + m1[k] );
            Jmp[j] = p - 1;
        }
    }

    ~mixedradix_subset_lex_rank()
    {
        delete [] Jmp;
    }

    ulong rank()  const
    {
        // last index e such that A[e] != 0,
        // e == 0 also for the all-zero word:
        ulong e = 0;
        for (ulong j=0; j<n; ++j)
            if ( A[j] != 0 )  e = j;

//        if ( e == 0 )  return A[0];  // OK, but not needed

        ulong r = 0;
        ulong j = 0;  // track
        while ( true )
        {
            const ulong & aj = A[j];
            const ulong & nine = m1[j];
            const ulong & jmp = Jmp[j];

            if ( j == e )  // on last non-zero digit
            {
                // forward (digits increasing, fast)
                r += aj;

                break;  // and return r
            }
            else  // not on last track
            {
                // forward (digits decreasing, slow)
                r += nine;
                r += jmp * ( nine - aj );
            }

            ++j;
        }

        return r;
    }

    ulong unrank(ulong r, ulong *B)  const
    // Return index of last non-zero digit, 0 also for the all-zero word.
    {
        ulong j = 0;  // track
        while ( j < n )
        {
            const ulong & nine = m1[j];

            if ( r <= nine )  // on last non-zero digit
            {
                // forward (digits increasing, fast)
                B[j] = r;
                break;
            }
            else  // not on last track
            {
                // forward (digits decreasing, slow)
                r -= nine;
                const ulong & jmp = Jmp[j];
                ulong d = nine;  // new digit

                while ( r > jmp )
                {
                    r -= jmp;
                    d -= 1;
                }

                B[j] = d;
            }

            ++j;
        }

        const ulong tr = j;
        while ( ++j < n )  { B[j] = 0; }
        return tr;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_SUBSET_LEX_RANK_H__
