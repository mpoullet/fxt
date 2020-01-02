#if !defined  HAVE_BITARRAY2D_H__
#define       HAVE_BITARRAY2D_H__
// This file is part of the FXT library.
// Copyright (C) 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"

//#define  BITARRAY2D_ASSERTS   // define to catch access beyond size
#ifdef BITARRAY2D_ASSERTS
#include "jjassert.h"
#endif

#include "ds/bitarray.h"


class bitarray2d
// Two-dimensional bit-array.
{
protected:
    bitarray **rowp_; // pointers to rows
    ulong *f_;        // pointer to data
    ulong dy_, dx_;   // #rows, #cols

    ulong num_bits_;  // number of elements

    bitarray2d(const bitarray2d&) = delete;
    bitarray2d & operator = (const bitarray2d&) = delete;

public:
    static bool use_asm_q()
    {
        return bitarray::use_asm_q();
    }


    explicit bitarray2d(ulong dx, ulong dy)
    {
        dy_ = dy;
        dx_ = dx;
        num_bits_ = dy_ * dx_;

        const ulong row_len = dx_ / BITS_PER_LONG + ( dx_ % BITS_PER_LONG != 0 );
        const ulong num_words = dy_ * row_len;
        f_ = new ulong[ num_words ];

        // setup row-pointers:
        rowp_ = new bitarray*[dy_];
        for (ulong i=0; i<dy_; ++i)
            rowp_[i] = new bitarray( dx_, f_ + i * row_len );

    }

    ~bitarray2d()
    {
        for (ulong i=0; i<dy_; ++i)  delete rowp_[i];
        delete [] rowp_;
        delete [] f_;
    }

    ulong dy()  const  { return dy_; }
    ulong dx()  const  { return dx_; }

    ulong num_bits()  const  { return num_bits_; }

    ulong test(ulong x, ulong y)  const
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        return rowp_[y]->test(x);
    }

    void set(ulong x, ulong y)
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        rowp_[y]->set(x);
    }

    void clear(ulong x, ulong y)
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        rowp_[y]->clear(x);
    }

    void change(ulong x, ulong y)
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        rowp_[y]->change(x);
    }

    ulong test_set(ulong x, ulong y)
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        return rowp_[y]->test_set(x);
    }

    ulong test_clear(ulong x, ulong y)
    // Test whether n-th bit is set and clear it.
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        return rowp_[y]->test_clear(x);
    }

    ulong test_change(ulong x, ulong y)
    // Test whether n-th bit is set and toggle it.
    {
#ifdef  BITARRAY2D_ASSERTS
        jjassert( x < dx_ );
        jjassert( y < dy_ );
#endif
        return rowp_[y]->test_change(x);
    }

public:
    bool is_off(ulong x, ulong y)  const
    {
        if ( x >= dx_ )  return true;
        if ( y >= dy_ )  return true;
        return false;
    }

public:
    void clear_all()
    // Clear all bits.
    {
        for (ulong r=0; r< dy_; ++r)  rowp_[r]->clear_all();
    }

    void set_all()
    // Set all bits.
    {
        for (ulong r=0; r< dy_; ++r)  rowp_[r]->set_all();
    }

    ulong count_ones()  const
    // Return the number of set bits.
    {
        ulong s = 0;
        for (ulong r=0; r< dy_; ++r)  s += rowp_[r]->count_ones();
        return s;
    }

    ulong count_zeros()  const
    // Return the number of clear bits.
    { return  num_bits_ - count_ones(); }

    bool all_set_q()  const
    // Return whether all bits are set.
    {
        for (ulong r=0; r< dy_; ++r)
            if ( ! rowp_[r]->all_set_q() )  return false;
        return true;
    }

    ulong all_clear_q()  const
    // Return whether all bits are clear.
    {
        for (ulong r=0; r< dy_; ++r)
            if ( ! rowp_[r]->all_clear_q() )  return false;
        return true;
    }

    // ds/bitarray2d.cc:
    void dump_bits()  const;
};
// -------------------------



#endif // !defined HAVE_BITARRAY2D_H__
