#if !defined HAVE_PEANO_NDIM_H__
#define      HAVE_PEANO_NDIM_H__
// This file is part of the FXT library.
// Copyright (C) 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "comb/mixedradix-gray.h"

//#include "jjassert.h"
//#include "fxtio.h"

#include "fxttypes.h"


class peano_ndim
// n-dimensional Peano curve
{
public:
    // Any odd number >= 3 can be used for any track in MR.
    // Here we use the same for all tracks:
    static constexpr ulong rad = 3;

public:
    mixedradix_gray MR;

    ulong nd; // number of dimensions
    ulong it; // iterate of curve
    long * pnt { nullptr };  // nd-dimensional point

    ulong * j_mod_nd { nullptr };  // lookup for fast mod
    // almost doubles performance

public:
    peano_ndim(ulong nd_, ulong it_)
        : MR( nd_ * it_, rad )
    {
        nd = nd_;
        it = it_;

        pnt = new long[ nd ];

        const ulong n = MR.num_digits();
        j_mod_nd = new ulong[ n ];
        for (ulong j=0; j < n; ++j)
            j_mod_nd[j] = j % nd;

        first();
    }

    ~peano_ndim()
    {
        delete [] pnt;
        delete [] j_mod_nd;
    }

    const long * point()  const  { return pnt; }

    void first()
    {
        MR.first();
        for (ulong j=0; j < nd; ++j)  pnt[j] = 0;
    }

    ulong edge_length()  const
    // Return r such that the traversed cube will
    // have coordinates componenwise < [ r, r , ..., r ].
    // r == rad ** it
    {
        ulong r = 1;
        for (ulong j = 0; j < it; ++j)  r *= rad;
        return r;
    }

    ulong num_points()  const
    // return number of points == r ** nd where r = edge_length()
    {
        ulong np = 1;
        const ulong r = edge_length();
        for (ulong j = 0; j < nd; ++j)  np *= r;
        return np;
    }

#if 0  // not OK
    long calc_dir( ulong coord_idx )  const
    // TEST:
    // We know which coordinate changes by one unit.
    // Can we find out whether it changes by +1 or =-1 ?
    {
        const ulong * A = MR.data();
        ulong par = 0;
        ulong j = MR.n_ - nd + coord_idx;
        jjassert ( j >= MR.pos() );
        while ( j != MR.pos() )
        {
            const ulong gd = A[j];
            par ^= ( gd & 1UL );  // change parity on odd digits
            j -= nd;
        }
        const long m_dir = ( MR.dir() == +1 );
        return ( par ==0 ? +m_dir : -m_dir );
    }
#endif

    long calc_coord( ulong  coord_idx )  const
    // Return new digit d computed by interpreting the digits
    // [ coord_idx, coord_idx + nd, coord_idx + 2 * nd, ..., coord_idx ]
    // as a (Gray coded) base-rad number.
    {
        // Can we optimize this one?
        // calc_dir() above is a failed attempt to do so.

        const ulong * A = MR.data();
        ulong par = 0;
        ulong j = MR.num_digits() - nd + coord_idx;

        ulong d = 0;  // new digit
        do
        {
            const ulong gd = A[j];
            const ulong ad = ( par ? (rad - 1) - gd : gd );
            d *= rad;
            d += ad;

            par ^= ( gd & 1UL );  // change parity on odd digits

            j -= nd;
        }
        while ( (long)j >= 0 );

        return d;
    }

    bool next( ulong & coord_idx, long & dir )
    // coord_idx: 0 for x, 1 for y, 2 for z, etc.
    // dir: +1 or -1 according to move.
    {
        if ( ! MR.next() )  return false;

//        coord_idx = MR.pos() % nd;  // expensive
        coord_idx = j_mod_nd[ MR.pos() ];  // much better

        const long d0 = pnt[ coord_idx ];  // old digit

        const long d = calc_coord( coord_idx );
        dir = d - d0;

#if 0  // TEST, not ok
        jjassert( calc_dir( coord_idx ) == dir );
#endif
        pnt[ coord_idx ] = d;

        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_PEANO_NDIM_H__
