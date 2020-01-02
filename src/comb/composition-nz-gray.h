#if !defined HAVE_COMPOSITION_NZ_GRAY_H__
#define      HAVE_COMPOSITION_NZ_GRAY_H__
// This file is part of the FXT library.
// Copyright (C) 2014, 2015, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "comb/composition-nz-rank.h"

#include "comb/is-composition-nz.h"

#include "comb/comb-print.h"
#include "comb/print-composition-aa.h"

#include "fxttypes.h"


class composition_nz_gray
// Compositions of n into positive parts.
// Gray code with moves of only one unit, all moves are one-close or
// two-close, two-close moves always cross a part =1 and all moves are
// at the end, involving the last element.
// Loopless algorithm.
// Same as class composition_nz_gray for odd n, reversed list for even n.
// First composition has one part for n odd, and two parts for n even.
// See Joerg Arndt, Subset-lex: did we miss an order?, (2014)
//   http://arxiv.org/abs/1405.6503
{
public:
    ulong *a_;  // composition: a[1] + a[2] + ... + a[m] = n
    ulong n_;   // compositions of n
    ulong m_;   // current composition has m parts

    composition_nz_gray(const composition_nz_gray&) = delete;
    composition_nz_gray & operator = (const composition_nz_gray&) = delete;

public:
    explicit composition_nz_gray(ulong n)
    {
        n_ = n;
        a_ = new ulong[n_+1+(n_==0)];
        a_[0] = 0;  // returned by last_part() when n==0
        a_[1] = 0;  // returned by first_part() when n==0
        first();
    }

    ~composition_nz_gray()
    {
        delete [] a_;
    }

    const ulong * data()  const  { return  a_ + 1; }

    ulong first_part()  const  { return a_[1]; }
    ulong last_part()  const  { return a_[m_]; }

    ulong num_parts()  const  {  return m_ - (n_==0); }


    void first()
    {
        a_[1] = (n_ ? n_ : 1 );
//        for (ulong k=2; k<=n_; ++k)  a_[k] = 0;
        m_ = 1;
    }

    void last()
    {
        if ( n_ <= 1 )
        {
            a_[1] = n_;
            m_ = n_;
        }
        else
        {
            a_[1] = 1;
            a_[2] = n_ - 1;
            m_ = 2;
        }
    }


protected:

    bool oddq(ulong x)  const  { return  0 != ( x & 1UL ); }
    bool evenq(ulong x)  const  { return  0 == ( x & 1UL ); }
    bool same_parity(ulong x, ulong y)  const
    { return  0 == ( ( x ^ y ) & 1UL ); }

    ulong par_to_dir_odd(ulong x)  const
    {
        if ( oddq(x) )  return +1;
        else            return -1UL;
    }

    ulong par_to_dir_even(ulong x)  const
    {
        if ( evenq(x) )  return +1;
        else             return -1UL;
    }

    ulong next_zgt1(bool qq)  // for Z > 1
    {
        const ulong z = a_[m_];
        const ulong y = a_[m_-1];

        if ( qq ) // same/different parity for next/prev
        {  // [*, Z ] --> [*, Z-1, 1 ]
            a_[m_] = z - 1;
            m_ += 1;
            a_[m_] = 1;
            return m_;
        }
        else  // different/same parity for next/prev
        {
            if ( y != 1 )  // Y > 1
            { // [*, Y, Z ] --> [*, Y+-1, Z-+1 ]
                const ulong dy = par_to_dir_even(y);
                a_[m_-1] = y + dy;
                a_[m_] = z - dy;
                return m_;
            }
            else  // Y == 1
            {
                const ulong x = a_[m_-2];

                if ( x != 1 )
                {  // [*, X, 1, Z ] --> [*, X+-1, 1, Z-+1 ]
                    const ulong dx = par_to_dir_odd(x);
                    a_[m_-2] = x + dx;
                    a_[m_] = z - dx;
                    return m_;
                }
                else  //  X == 1
                {  // [*, X, 1, Z ] --> [*, X+1, 1, Z-1 ]
                    a_[m_-2] = x + 1;
                    a_[m_] = z - 1;
                    return m_;
                }
            }
        }
    }

    ulong next_odd_zeq1()  // for Z == 1
    {
        const ulong y = a_[m_-1];
        const ulong dy = par_to_dir_odd(y);

        if ( dy == +1 )
        {  // [*, Y, 1 ] --> [*, Y+1 ]
            a_[m_-1] = y + 1;
            m_ -= 1;
            return m_;
        }
        else  // dy == -1
        {  // [*, Y, 1 ] --> [*, Y-1, 1, 1 ]
            a_[m_-1] = y - 1;
            m_ += 1;
            a_[m_] = 1;
            return m_;
        }
    }

    ulong next_even_zeq1()  // for Z == 1
    {
        ulong z = a_[m_];
        ulong y = a_[m_-1];

        if ( y != 1 )
        {  // [*, Y, Z] --> [*, Y+-1, Z-+1]
            const ulong dy = par_to_dir_even(y);
            y += dy;
            z -= dy;
            a_[m_-1] = y;
            a_[m_] = z;
            m_ -= (z==0);
            return m_;
        }
        else  // Y == 1
        { // [*, X, 1, Z] --> [*, X+-1, 1, Z-+1]
            ulong x = a_[m_-2];
            const ulong dx = par_to_dir_odd(x);
            x += dx;
            z -= dx;
            a_[m_-2] = x;
            a_[m_] = z;
            m_ -= (z==0);
            return m_;
        }
    }

public:

    ulong next()
    // Return number of parts in new composition,
    // return zero if current is last.
    // Loopless algorithm.
    {
        if ( m_ <= 2 )
            if ( a_[1] <= 1 )  return 0;  // current is last

        ulong z = a_[m_];
        if ( z != 1 )  return  next_zgt1( same_parity(n_, z) );
        else           return  ( oddq(n_) ? next_odd_zeq1() : next_even_zeq1() );
    }

    ulong prev()
    // Return number of parts in new composition,
    // return zero if current is first.
    // Loopless algorithm.
    {
        if ( m_ <= 1 )  return 0;  // current is last

        ulong z = a_[m_];
        if ( z != 1 )  return  next_zgt1( !same_parity(n_, z) );
        else           return  ( evenq(n_) ? next_odd_zeq1() : next_even_zeq1() );
    }


    ulong rank()  const
    // Return rank r of current composition, 0 <= r < 2**(n-1).
    { return  composition_nz_gray_rank(data(), num_parts(), n_); }

    ulong unrank(ulong r)
    // Return number of parts m of generated composition, 0 <= m <= n.
    { m_ = composition_nz_gray_unrank(r, a_+1, n_);  return m_; }


    bool OK()  const
    { return is_composition_nz(data(), num_parts(), n_); }

    void print(const char *bla)  const
    { print_vec(bla, data(), num_parts(), false); }

    void print_aa()  const  // ASCII art
    { print_composition_aa(data(), num_parts()); }
};
// -------------------------


#endif  // !defined HAVE_COMPOSITION_NZ_GRAY_H__
