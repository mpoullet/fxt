#if !defined HAVE_MIXEDRADIX_GRAY_H__
#define      HAVE_MIXEDRADIX_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2013, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix-aux.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"
#include "restrict.h"


class mixedradix_gray
// Gray code for mixed radix numbers.
// CAT algorithm.
{
protected:
    ulong * restrict a_;  // mixed radix digits
    ulong * restrict m1_;  // radices (minus one)
    ulong * restrict d_;  // direction
    ulong n_;   // n_ digits
    ulong j_;   // position of last change
    int dm_;    // direction of last move

    mixedradix_gray(const mixedradix_gray&) = delete;
    mixedradix_gray & operator = (const mixedradix_gray&) = delete;

public:
    explicit mixedradix_gray(ulong n, ulong mm, const ulong *m = nullptr)
    {
        n_ = n;
        a_ = new ulong[n_+1];
        a_[n] = -1UL;  // sentinel
        d_ = new ulong[n_+1];
        d_[n_] = 0;    // sentinel
        m1_ = new ulong[n_+1];

        mixedradix_init(n_, mm, m, m1_);

        first();
    }

    ~mixedradix_gray()
    {
        delete [] d_;
        delete [] a_;
        delete [] m1_;
    }

    const ulong * data()  const { return a_; }
    const ulong * nines()  const  { return m1_; }
    const ulong * directions()  const  { return d_; }
    ulong num_digits()  const  { return n_; }

    void first()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  d_[k] = +1;
        j_ = n_;
        dm_ = 0;
    }

    void last()
    {
        for (ulong k=0; k<n_; ++k)  a_[k] = 0;
        for (ulong k=0; k<n_; ++k)  d_[k] = -1UL;

        // find position of last even radix:
        ulong z = 0;
        for (ulong i=0; i<n_; ++i)  if ( m1_[i] & 1 )  z = i;
        while ( z<n_ )  // last even .. end:
        {
            a_[z] = m1_[z];
            d_[z] = +1;
            ++z;
        }

        j_ = 0;
        dm_ = -1;
    }

    bool next()
    {
        ulong j = 0;
        ulong dj;
        while ( (dj=d_[j]) )  // can read sentinel i[n]==0
        {
            ulong aj = a_[j] + dj;
            if ( aj>m1_[j] )  // =^= if ( (aj>m1_[j]) || ((long)aj<0) )
            {
                d_[j] = -dj;  // flip direction
            }
            else  // can update
            {
                a_[j] = aj;  // update digit
                dm_ = (int)dj;    // save for dir()
                j_ = j;      // save for pos()
                return true;
            }

            ++j;
        }
        return false;
    }

    bool prev()
    {
        ulong j = 0;
        ulong dj;
        while ( (dj=d_[j]) )  // can read sentinel i[n]==0
        {
            ulong aj = a_[j] - dj;
            if ( aj>m1_[j] )  // =^= if ( (aj>m1_[j]) || ((long)aj<0) )
            {
                d_[j] = -dj;  // flip direction
            }
            else  // can update
            {
                a_[j] = aj;  // update digit
                dm_ = (int)dj;    // save for dir()
                j_ = j;      // save for pos()
                return true;
            }

            ++j;
        }
        return false;
    }

    ulong pos()  const  { return j_; }  // position of last change
    int dir()  const  { return dm_; }   // direction of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, a_, n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(a_, m1_, n_); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(a_, n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_GRAY_H__
