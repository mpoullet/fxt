#if !defined HAVE_MIXEDRADIX_REV_H__
#define      HAVE_MIXEDRADIX_REV_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix-aux.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"



class mixedradix_rev
// Mixed radix counting.
// Digits in reversed order as in class mixedradix.
{
protected:
    ulong *a_;  // digits
    ulong *m1_;  // nines (radix minus one) for each digit
    ulong n_;   // Number of digits
    ulong j_;   // leftmost position of last change

private:  // have pointer data
    mixedradix_rev(const mixedradix_rev&) = delete;
    mixedradix_rev & operator = (const mixedradix_rev&) = delete;

public:
    explicit mixedradix_rev(ulong n, ulong mm, const ulong *m = nullptr)
    {
        n_ = n;

        a_ = new ulong[n_+1+(n_==0)];
        m1_ = new ulong[n_+1+(n_==0)];

        a_[0] = 1;   // sentinel: !=0, and !=m1[n]
        m1_[0] = 2;  // sentinel

        mixedradix_init(n_, mm, m, m1_+1);

        first();
    }

    ~mixedradix_rev()
    {
        delete [] m1_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_ + 1; }
    const ulong * nines()  const  { return m1_; }
    ulong num_digits()  const  { return n_; }

    void first()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = 0;
        j_ = 0;
    }

    void last()
    {
        for (ulong k=1; k<=n_; ++k)  a_[k] = m1_[k];
        j_ = 0;
    }


    bool next()  // increment
    {
        ulong j = n_;
        while ( a_[j]==m1_[j] )  { a_[j]=0;  --j; }  // can read sentinels
        j_ = j;

        if ( j==0 )  return false;  // current is last

        ++a_[j];
        return true;
    }

    bool prev()  // decrement
    {
        ulong j = n_;
        while ( a_[j]==0 )  { a_[j]=m1_[j];  --j; }  // can read sentinels
        j_ = j;

        if ( j==0 )  return false;  // current is first

        --a_[j];
        return true;
    }

    ulong pos()  const  { return j_; }  // position of last change

    void print(const char *bla, bool dfz=false)  const
    // If dfz is true then Dots are printed For Zeros.
    { print_mixedradix(bla, data(), n_, dfz); }

    void print_nines(const char *bla)  const
    { print_mixedradix(bla, m1_+1, n_, false); }

    ulong to_num()  const
    // Return (integer) value of mixed radix number.
    { return mixedradix2num(data(), m1_, n_); }

    bool OK()  const
    {
        if ( ! is_mixedradix_num(data(), n_, m1_) )  return false;
        return true;
    }
};
// -------------------------


#endif  // !defined HAVE_MIXEDRADIX_REV_H__
