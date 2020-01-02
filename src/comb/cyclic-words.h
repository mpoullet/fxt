#if !defined  HAVE_CYCLIC_WORDS_H__
#define       HAVE_CYCLIC_WORDS_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"  // ulong
//#include "jjassert.h"


template <typename Type>
ulong cyclic_lex_min_idx(const Type *W, ulong n)
// Return index i such that the word W, read (cyclically) starting at i,
// is the lexicographically minimal cyclic shift of W.
// In other words:
// among all rotations of W, the one shifted by i letters (to the left) is lex-min.
//.
// Orignal code taken from https://stackoverflow.com/questions/3459509/
// Cleaned up and optimized.
{
    // Let A and B the words starting at respectively i and j.
    ulong i = 0;  // start of the best lex-min cyclic shift found so far (A)
    ulong j = 1;  // start of the cyclic shift we are testing against (B)
    ulong k = 0;  // offset in both A and B where letters are read
    // (the strings match for their first k letters)

    while( j + k < 2 * n )
    {
        ulong ik = i + k;  // mod n
        ulong jk = j + k;  // mod n
        if ( ik >= n )  ik -= n;
        if ( jk >= n )  jk -= n;
        const Type & a = W[ ik ];  // the letter in A
        const Type & b = W[ jk ];  // the letter in B

        if ( a > b )
        {
            i = j;
            ++j;
            k = 0;
        }
        else if ( a < b )
        {
            j += k + 1;
            k = 0;
        }
        else  // ( a == b )
        {
            const ulong p = j - i;

            if ( k != p )
            {
                ++k;
            }
            else  // ( k==p )
            {
                j += p;
                k = 0;
            }
        }
    }

    return i;
}
// -------------------------


template <typename Type>
bool is_cyclic_lex_min(const Type *W, ulong n)
// Return whether W[] is the minimum among all its cyclic rotations.
// Equivalently, whether 0 === cyclic_lex_min_idx(W, n),
//   but faster on average.
{
    // Let A and B the words starting at respectively i and j.
    ulong i = 0;  // start of the best lex-min cyclic shift found so far (A)
    ulong j = 1;  // start of the cyclic shift we are testing against (B)
    ulong k = 0;  // offset in both A and B where letters are read
    // (the strings match for their first k letters)

    while( j + k < 2 * n )
    {
        ulong ik = i + k;  // mod n
        ulong jk = j + k;  // mod n
        if ( ik >= n )  ik -= n;
        if ( jk >= n )  jk -= n;
        const Type & a = W[ ik ];  // the letter in A
        const Type & b = W[ jk ];  // the letter in B

        if ( a > b )
        {
            return false;
        }
        else if ( a < b )
        {
            j += k + 1;
            k = 0;
        }
        else  // ( a == b )
        {
            const ulong p = j - i;

            if ( k != p )
            {
                ++k;
            }
            else  // ( k==p )
            {
                j += p;
                k = 0;
            }
        }
    }

    return true;
}
// -------------------------


template <typename Type>
ulong cyclic_lex_min_word(const Type *W, ulong n, Type *M)
// Return index i as in cyclic_lex_min_idx(W, n) and
// write the cyclic lex-min word to M.
// Must have W != M.
{
    const ulong i = cyclic_lex_min_idx(W, n);
    ulong r = i;  // read position
    ulong w = 0;  // write position
    while ( r < n )  { M[w] = W[r];  ++w;  ++r; }
    r = 0;
    while ( w < n )  { M[w] = W[r];  ++w;  ++r; }
    return i;
}
// -------------------------


template <typename Type>
bool cyclic_equal_p(const Type * A, const Type * B, ulong n)
// Return whether the words A and B are equal up to cyclic shift.
//
// Algorithm from pp. 363ff, Section 15.4,
// "Cyclic equality of words, and Lyndon factorization"
// in
//   Maxime Crochemore, Wojciech Rytter, Text Algorithms,
//   Oxford University Press, 1994.
//
// This implementation avoids duplicating the words at start.
{
    ulong na = 0,  nb = 0;
    while ( na < n && nb < n )
    {
        ulong k = 0;
        ulong nak = na,  nbk = nb; // na + k and nb + k  (mod n)
        while ( k < n )
        {
            if ( A[nak] == B[nbk] )
            {
                ++k;
                ++nak;  if ( nak >= n )  { nak -= n; }
                ++nbk;  if ( nbk >= n )  { nbk -= n; }
            }
            else  break;
        }

        if ( k == n )  return true;

        if ( A[nak] > B[nbk] )  na += k + 1;  // both work, > or <
        else                    nb += k + 1;
    }

    return false;
}
// -------------------------


template <typename Type>
int cyclic_compare(const Type * A, ulong ai, const Type * B, ulong bi, ulong n)
// Compare A[ai, ai+1, ...] and B[bi, bi+1, ...] cyclically (indices taken mod n).
// Return  +1 if A[] > B[],  -1 if A[] < B[],  otherwise (A[]==B[]) 0.
{
    for (ulong j=0; j<n; ++j)
    {
        if ( A[ai] > B[bi] )  return +1;
        if ( A[ai] < B[bi] )  return -1;

        ai += 1;
        if ( ai >= n )  { ai -= n; }
        bi += 1;
        if ( bi >= n )  { bi -= n; }
    }

    return 0;
}
// -------------------------


template <typename Type>
int cyclic_compare_min(const Type * A, const Type * B, ulong n)
// Compare the cyclic minima of the words A[] and B[]:
// Let ai and bi be the indices returned by cyclic_lex_min_idx()
//   for A[] and B[] respectively.
// Compare A[ai, ai+1, ...] and B[bi, bi+1, ...] cyclically (indices taken mod n).
// Return  +1 if A[] > B[],  -1 if A[] < B[],  otherwise (A[]==B[]) return 0.
{
#if 1
    // Faster variant, derived from cyclic_equal_p()
    // Avoids calls to cyclic_lex_min_idx()
    // Must have n >= 1

    // if ( n==0 )  return 0;  // take care of case n == 0
    ulong na = 0,  nb = 0;
    ulong nak = 0, nbk = 0;
    while ( na < n && nb < n )
    {
        ulong k = 0;
        nak = na,  nbk = nb; // na + k and nb + k  (mod n)
        while ( k < n )
        {
            if ( A[nak] == B[nbk] )
            {
                ++k;
                ++nak;  if ( nak >= n )  { nak -= n; }
                ++nbk;  if ( nbk >= n )  { nbk -= n; }
            }
            else  break;
        }

        if ( k == n )  return 0;  // same

        if ( A[nak] > B[nbk] )   na += k + 1;
        else                     nb += k + 1;
    }

//    jjassert( nak < n  );
//    jjassert( nak < n  );
//    jjassert( A[nak] != B[nbk] );
    return ( A[nak] > B[nbk] ? +1 : -1 );

#else

    const ulong ai = cyclic_lex_min_idx(A, n);
    const ulong bi = cyclic_lex_min_idx(B, n);
    return  cyclic_compare(A, ai, B, bi, n);
#endif
}
// -------------------------


#endif // !defined HAVE_CYCLIC_WORDS_H__
