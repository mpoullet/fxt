#if !defined  HAVE_CHECK_KPERMGEN_H__
#define       HAVE_CHECK_KPERMGEN_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2012, 2014, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/fact2perm.h"  // perm2ffact()
#include "comb/fact2num.h"  // ffact2num()
#include "ds/bitarray.h"
#include "aux0/factorial.h"  // ffactpow()

#include "fxttypes.h"

//#include "jjassert.h"


class check_kpermgen
// Checking validity of list of k-permutations.
{
public:
    const ulong *x_;
    ulong N_;
    ulong n_;
    ulong k_;
    ulong *a_;  // for mixed radix numbers
    ulong *r_;  // for reversed permutations
    bitarray B;

private:  // have pointer data
    check_kpermgen(const check_kpermgen&) = delete;
    check_kpermgen & operator = (const check_kpermgen&) = delete;

public:
    explicit check_kpermgen(ulong n, ulong k)
        :
        x_(nullptr),
        N_(ffactpow(n, k)),
        n_(n),
        k_(k),
        a_(new ulong[n_]),
        r_(new ulong[n_]),
        B(ffactpow(n, k))
    {
    }

    ~check_kpermgen()
    {
        delete [] a_;
        delete [] r_;
    }

    void first(const ulong *x)
    {
        B.clear_all();
        x_ = x;
    }

    bool is_repeat()
    // Mark permutation as seen.
    // Return true if permutation is a repeat.
    {
        perm2ffact(x_, n_, a_);
        for (ulong j=k_; j<n_; ++j)  a_[j] = 0;  // ignore tail
        const ulong w = ffact2num(a_, n_-1);
//        jjassert( w < N_ );
        const bool q = B.test_set(w);
        return q;
    }

    bool is_repeat_rev()
    // Mark reversed permutation as seen.
    // Return true if reversed permutation is a repeat.
    {
        for (ulong i=0, j=k_-1;  i<n_;  ++i, --j)  r_[i] = x_[j];
        perm2ffact(r_, n_, a_);
        for (ulong j=k_; j<n_; ++j)  a_[j] = 0;  // ignore tail
        const ulong w = ffact2num(a_, n_-1);
        const bool q = B.test_set(w);
        return q;
    }

    bool have_all()  const
    {  return B.all_set_q();  }
};
// -------------------------


#endif  // !defined HAVE_CHECK_KPERMGEN_H__
