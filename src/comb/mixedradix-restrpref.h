#if !defined HAVE_MIXEDRADIX_RESTRPREF_H__
#define      HAVE_MIXEDRADIX_RESTRPREF_H__
// This file is part of the FXT library.
// Copyright (C) 2012, 2013, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mixedradix-aux.h"
#include "comb/is-mixedradix-num.h"
#include "comb/comb-print.h"

#include "fxttypes.h"


class mixedradix_restrpref
// Mixed radix counting with restricted prefixes.
{
protected:
    ulong *a_;   // digits
    ulong *m1_;  // nines (radix minus one) for each digit
    ulong n_;    // number of digits
    ulong j_;    // position of last change
    bool vld_;   // whether current word is valid

    typedef bool (* cond_func)(const ulong*, ulong);
    cond_func cond { nullptr };  // condition function

private:  // have pointer data
    mixedradix_restrpref(const mixedradix_restrpref&) = delete;
    mixedradix_restrpref & operator = (const mixedradix_restrpref&) = delete;

public:
    explicit mixedradix_restrpref(ulong n, ulong mm, const ulong *m)
    // cond_func cond must be supplied with call to first().
    {
        n_ = n;

        a_ = new ulong[n_+1];
        m1_ = new ulong[n_+1];

        a_[0] = 1;   // sentinel: !=0, and !=m1[n]
        m1_[0] = 0;  // sentinel
        ++a_;  // nota bene
        ++m1_;  // nota bene

        mixedradix_init(n_, mm, m, m1_);
    }

    ~mixedradix_restrpref()
    {
        --a_;
        --m1_;
        delete [] m1_;
        delete [] a_;
    }

    const ulong * data()  const  { return a_; }
    const ulong * nines()  const  { return m1_; }
    ulong num_digits()  const  { return n_; }

    bool valid()  const { return  vld_; }


    void first( cond_func cnd )
    // Try to generate first word.
    // Whether this was successful is returned by valid().
    {
        cond = cnd;

        vld_ = true;
        j_ = 0;

        if ( n_ == 0 )  { return; }

        for (ulong j=0; j<n_; ++j)  a_[j] = 0;

        ulong j = 0;
        do  // try for each position
        {
            ulong d = a_[j];
            for ( ; d<=m1_[j]; ++d)  // try for each digit
            {
                a_[j] = d;
                if ( cond(a_, j) )  break;  // found allowed digit
            }

            if ( d > m1_[j] )  // no digit allowed
            {
                if ( j==0 )  // no valid word exists
                {
                    vld_ = false;
                    return;
                }
                else  // one level down
                {
                    a_[j] = 0;
                    --j;
                    a_[j] += 1;
                }
            }
            else  // one level up
            {
                ++j;
            }
        }
        while ( j != n_ );

    }


    bool next()
    {
        ulong j = n_ - 1;
        // scan over nines:
        while ( a_[j]==m1_[j] )  { a_[j]=0;  --j; }  // can read sentinels

        if ( j+1 == 0 )  // current is last
        {
            vld_=false;
            return false;
        }

        j_ = j;
        ++a_[j];

        do  // try for each position
        {
            ulong d;
            for (d=a_[j]; d<=m1_[j]; ++d)  // try for each digit
            {
                a_[j] = d;
                if ( cond(a_, j) )  break;  // digit d is allowed
            }

            if ( d <= m1_[j] )  // digit d is allowed
            {
                ++j;  // one level up
            }
            else  // ( d > m1_[j] )  // no digit allowed
            {
                if ( j==0 )   // current is last
                {
                    vld_ = false;
                    return false;
                }

                a_[j] = 0;

                --j;  // one level down
                j_ = j;
                ++a_[j];
            }
        }
        while ( j != n_ );

        return true;
    }


    ulong pos()  const  { return j_; }  // position of last change

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



#endif  // !defined HAVE_MIXEDRADIX_RESTRPREF_H__
