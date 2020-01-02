#if !defined HAVE_ARRAY2D_H__
#define      HAVE_ARRAY2D_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014, 2016, 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.

#include "fxttypes.h"


//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#define  ARRAY2D_ASSERTS  // define to catch access beyond size
#endif  // PARANOIA

//#define  ARRAY2D_ASSERTS   // define to catch access beyond size
#ifdef ARRAY2D_ASSERTS
#include "jjassert.h"
#endif


template <typename Type>
class array2d
// Two-dimensional array.
{
protected:
    Type **rowp_;    // pointers to rows
    Type *f_;        // pointer to data
    ulong nr_, nc_;  // #rows, #cols
    bool myfq_;      // whether f_ was allocated by constructor

    ulong num_elem_;  // number of elements

    array2d(const array2d&) = delete;
    array2d & operator = (const array2d&) = delete;

public:
    explicit array2d(ulong nr, ulong nc, Type *f=nullptr)
    {
        nr_ = nr;
        nc_ = nc;
        num_elem_ = nr_ * nc_;

        if ( nullptr != f )  // data supplied
        {
            f_ = f;
            myfq_ = false;
        }
        else  // allocate own data
        {
            f_ = new Type[ num_elem_ ];
            myfq_ = true;
        }

        // setup row-pointers:
        rowp_ = new Type*[nr_];
        rowp_[0] = f_;
        for (ulong i=1; i<nr_; ++i)  rowp_[i] = rowp_[i-1] + nc_;
    }

    ~array2d()
    {
        delete [] rowp_;
        if ( myfq_ )  delete [] f_;
    }

    ulong num_rows()  const  { return nr_; }
    ulong num_cols()  const  { return nc_; }

    ulong num_elem()  const  { return num_elem_; }

    const Type * operator [] (ulong r)  const
    {
#ifdef  ARRAY2D_ASSERTS
        jjassert( r < nr_ );
#endif
        return rowp_[r];
    }

    Type * operator [] (ulong r)
    {
#ifdef  ARRAY2D_ASSERTS
        jjassert( r < nr_ );
#endif
        return rowp_[r];
    }

public:
    bool is_off(ulong r, ulong c)  const
    {
        if ( r >= nr_ )  return true;
        if ( c >= nc_ )  return true;
        return false;
    }

public:
    void null()
    {
        for (ulong j=0; j < num_elem_; ++j)  f_[j] = 0;
    }

    void fill(const Type & v)
    {
        for (ulong j=0; j < num_elem_; ++j)  f_[j] = v;
    }
};
// -------------------------



#endif  // !defined HAVE_ARRAY2D_H__
