#if !defined  HAVE_MSET_KPERM_LEX_H__
#define       HAVE_MSET_KPERM_LEX_H__
// This file is part of the FXT library.
// Copyright (C) 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/mset-perm-lex.h"
#include "comb/comb-print.h"
#include "aux0/swap.h"
#include "fxttypes.h"


class mset_kperm_lex : public mset_perm_lex
// k-permutations of a multiset in lexicographic order.
{
protected:
    ulong plen_;  // length of prefix

    mset_kperm_lex(const mset_kperm_lex&) = delete;
    mset_kperm_lex & operator = (const mset_kperm_lex&) = delete;

public:
    explicit mset_kperm_lex(const ulong *r, ulong k, ulong plen)
        : mset_perm_lex(r, k)
    {
        if ( plen > num_parts() )  plen = num_parts();
        plen_ = plen;
    }

    ~mset_kperm_lex()  { ; }

private:
    void reverse_suffix()
    {
        ulong j = plen_,  i = n_ - 1;
        while ( j < i )
        {
            swap2(ms_[j], ms_[i]);
            ++j;
            --i;
        }
    }

public:
    ulong next()
    // Return position of leftmost change,
    // return n with last permutation.
    {
        reverse_suffix();
        return mset_perm_lex::next();
    }

    void print(const char *bla, bool dfz=false)  const
    { print_vec(bla, data(), plen_, dfz); }

    void print_suffix(const char *bla, bool dfz=false)  const
    { print_vec(bla, data()+plen_, n_ - plen_, dfz); }
};
// -------------------------


#endif  // !defined HAVE_MSET_KPERM_LEX_H__
