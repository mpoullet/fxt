#if !defined HAVE_MIXEDRADIX_SL_GRAY_H__
#define      HAVE_MIXEDRADIX_SL_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2015, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix-sl-gray-rank.h"

#include "comb/mixedradix-aux.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_sl_gray
// Mixed radix numbers in a minimal-change order
// related so subset-lex order ("SL-Gray" order).
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
protected:
    ulong n_;    // Number of digits (n kinds of elements in multiset, n>=1)
    ulong tr_;   // aux: current track, index of last non-zero digit, 0 also for all-zero word
    ulong * a_;   // digits of mixed radix number (multiplicity of kind k in subset).
    ulong * d_;   // directions (either +1 or -1)
    ulong * m1_;  // nines (radix minus one) for each digit (multiplicity of kind k in superset).

    ulong j_;    // position of last change; returned by pos()
    int dm_;     // direction of last change; returned by dir()

    mixedradix_sl_gray_rank * RU { nullptr };  // rank and unrank functions

private:  // have pointer data
    mixedradix_sl_gray(const mixedradix_sl_gray&) = delete;
    mixedradix_sl_gray & operator = (const mixedradix_sl_gray&) = delete;

public:
    explicit mixedradix_sl_gray(ulong n, ulong mm, const ulong *m = nullptr)
    // Must have n>=1
    {
        n_ = n;
        a_ = new ulong[n_+2];  // all with sentinels at both ends
        d_ = new ulong[n_+2];
        m1_ = new ulong[n_+2];

        // sentinels on the right:
        a_[n_+1] = +1;   // != 0
        m1_[n_+1] = +1;  // same as a_[n+1]
        d_[n_+1] = +1;   // positive

        // sentinels on the left:
        a_[0] = +2;    // >= +2
        m1_[0] = +2;  //  same as a_[0]
        d_[0] = 0;    // zero

        ++a_;  ++d_;  ++m1_;  // nota bene

        mixedradix_init(n_, mm, m, m1_);

        RU = new mixedradix_sl_gray_rank( data(), num_digits(), nines() );

        first();
    }

    ~mixedradix_sl_gray()
    {
        --a_;  --d_;  --m1_;
        delete [] a_;
        delete [] d_;
        delete [] m1_;
        delete RU;
    }

    const ulong * data()  const  { return a_; }
    const ulong * nines()  const  { return m1_; }
    const ulong * directions()  const  { return d_; }
    ulong num_digits()  const  { return n_; }
    ulong track()  const  { return tr_; }  // index of rightmost non-zero digit
    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }   // direction of last change

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  d_[k] = +1;
        tr_ = 0;

        j_ = 0;  // arbitrary
        dm_ = -1;  // arbitrary
    }


    bool next()
    // Generate next.
    // Return false if current was last.
    // Loopless if all radices are even and >= 4 because all
    // successive changes are at a distance of at most 2 (two-close
    // Gray code), also for radix 2 as the Gray code is three-close.
    {
        ulong j = tr_;
        const ulong dj = d_[j];
        const ulong a1 = a_[j] + dj;  // a[j] +- 1

//        if ( (a1 != 0) && (a1 <= m1_[j]) )  // easy case
        if ( a1 - 1 < m1_[j] )  // easy case (optimized)
        {
            a_[j] = a1;
            j_ = j;  // record position of change
            dm_ = (int)dj;  // record direction of change
            return true;
        }

        d_[j] = -dj;  // change direction

        if ( dj == +1 )  // so a_[j] == m1_[j] == nine
        {
            // Try to move track right with a[j] == nine:
            const ulong j1 = j + 1;
            if ( a_[j1] == 0 )  // can read high sentinel
            {
                a_[j1] = +1;
                tr_ = j1;
                j_ = j1;  // record position of change
                dm_ = +1;  // record direction of change
                return true;
            }
        }
        else  // here dj == -1, so a_[j] == 1
        {
            if ( (long)j <= 0 )  return false;  // current is last

            // Try to move track left with a[j] == 1:
            const ulong j1 = j - 1;
            if ( a_[j1] == m1_[j1] )  // can read low sentinel when n_ == 1
            {
                a_[j] = 0;
                d_[j1] = -1UL;
                tr_ = j1;
                j_ = j1;  // record position of change
                dm_ = -1;  // record direction of change
                return true;
            }
        }

        // find first changeable track to the left:
        --j;
        while ( a_[j] + d_[j] > m1_[j] )  // may read low sentinels
        {
            d_[j] = -d_[j];  // change direction
            --j;
        }

        if ( (long)j < 0 )  return false;  // current is last

        // Change digit left but keep track:
        a_[j] += d_[j];

        j_ = j;  // record position of change
        dm_ = (int)d_[j];  // record direction of change

        return true;
    }

//    void last()
//    {
//        ulong e = 1;  // rank of last number
//        for (ulong j=0; j<n_; ++j)  e *= (m1_[j] + 1);
//        e -= 1;
//        unrank( e );
//    }

//    bool prev()
//    // Generate previous.
//    // Return false if current was first.
//    {  // Same as next() but direction d[] negated
//    }

    ulong card()  const
    // Cardinality of current subset (sum of digits).
    {
        ulong s = 0;
        for (ulong j=0; j<n_; ++j)  s += a_[j];
        return s;
    }

    ulong rank()  const
    {
        return RU->rank();
    }

    void unrank(ulong r)
    // Invalidates pos() and dir()
    {
        tr_ = RU->unrank( r, a_ );
    }

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;

        const ulong rk = RU->rank();
        ulong B[n_];
        RU->unrank( rk, B );
        for (ulong j=0; j<n_; ++j)
            if ( data()[j] != B[j] )
                return false;

        return true;
    }
};
// -------------------------



#endif  // !defined HAVE_MIXEDRADIX_SL_GRAY_H__
