#if !defined  HAVE_CHECK_MIXEDRADIX_H__
#define       HAVE_CHECK_MIXEDRADIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/bitarray.h"
#include "fxttypes.h"


class check_mixedradix
// Checking validity of list of mixed radix numbers.
{
public:
    const ulong * m1_;
    const ulong * x_;
    const ulong n_;
    bitarray B;

private:  // have pointer data (read-only, however)
    check_mixedradix(const check_mixedradix&) = delete;
    check_mixedradix & operator = (const check_mixedradix&) = delete;

    ulong product_p1()  const
    {
        ulong pr = 1;
        for (ulong j=0; j<n_; ++j)  pr *=  m1_[j] + 1;
        return pr;
    }

public:
    explicit check_mixedradix(const ulong *m1, ulong n)
        :
        m1_(m1),
        x_(nullptr),
        n_(n),
        B( product_p1() )
    {
    }

    ~check_mixedradix()  {;}

    void first(const ulong *x)
    {
        B.clear_all();
        x_ = x;
    }

    bool is_repeat()
    // Mark number as seen.
    // Return true if permutation is a repeat.
    {
        ulong w = mixedradix2num(x_, m1_, n_);
        bool q = B.test_set(w);
        return q;
    }

    bool all_seen()  const
    // Return whether all numbers have been seen.
    {
        return  B.all_set_q();
    }
};
// -------------------------


#endif  // !defined HAVE_CHECK_MIXEDRADIX_H__
