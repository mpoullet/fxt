#if !defined  HAVE_LYNDON_FACTORIZATION_H__
#define       HAVE_LYNDON_FACTORIZATION_H__
// This file is part of the FXT library.
// Copyright (C) 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

template <typename Type>
inline ulong lyndon_factorization(const Type * W, ulong n, ulong * F)
// Standard (Chen, Fox, Lyndon)-factorization of the word W.
//
// Return the number of factors and write to F[] the positions
// beyond the ends of the factors.
//
// Algorithm as in
// Jean-Pierre Duval, "Factorizing words over an ordered alphabet",
// Journal of Algorithms, vol. 4, no. 4, pp. 363-381, (December-1983).
//
// Code adapted from JavaScript by Lloyd Allison, see
//   http://www.allisons.org/ll/AlgDS/Strings/Factors/
{
    ulong m = 0;  // number of factors found
    ulong k = 0;
    while ( k < n )
    {
        ulong i = k;
        ulong j = k + 1;
        while ( true )
        {
            if ( j < n )
            {
                const Type & Wi = W[i];
                const Type & Wj = W[j];
                if( Wi < Wj )
                {
                    i = k;
                    j = j+1;
                    continue;
                }
                else if( Wi == Wj )
                {
                    i = i+1;
                    j = j+1;
                    continue;
                }
            }

            { // here we have (j >= n) || (Wi > Wj)
                const ulong p = j - i;
                do
                {
                    k += p;
                    F[ m++ ] = k;
                }
                while ( k <= i );

                break;
            }
        }
    }

    return m;
}
// -------------------------

template <typename Type>
ulong max_lyndon_prefix_len(const Type *W, ulong n)
// Return the length of the maximal prefix of the word W that is a
// Lyndon word.
// The code is a specialization of lyndon_factorization(W, n, F)
// returning just when the first entry in F would have been made.
{
    ulong k = 0;
    while ( k < n )
    {
        ulong i = k;
        ulong j = k + 1;

        while ( true )
        {
            if( j < n )
            {
                const Type & Wi = W[i];
                const Type & Wj = W[j];
                if( Wi < Wj )  // str[k..i) < str[k+1,j)
                {
                    i = k;
                    j = j+1;
                    continue;
                }
                else if( Wi == Wj )  // str[k..i) <= str[k+1,j)
                {
                    i = i+1;
                    j = j+1;
                    continue;
                }
            }

            { // here we have (j >= n) || (Wi > Wj)
                const ulong p = j - i;
                return  k + p;
            }
        }
    }
    return 0; // unreached
}
// -------------------------

template <typename Type>
inline bool is_lyndon_word(const Type *W, ulong n)
// Return whether the word W is a Lyndon word.
{
    return ( n == max_lyndon_prefix_len(W, n) );
}
// -------------------------


#endif // !defined HAVE_LYNDON_FACTORIZATION_H__
