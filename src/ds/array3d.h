#if !defined HAVE_ARRAY3D_H__
#define      HAVE_ARRAY3D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.




//#define PARANOIA  // define to enable for this file
#ifdef PARANOIA
#define  ARRAY3D_ASSERTS  // define to catch access beyond size
#endif  // PARANOIA

//#define  ARRAY3D_ASSERTS   // define to catch access beyond size
#ifdef ARRAY3D_ASSERTS
#define ARRAY2D_ASSERTS
#include "jjassert.h"
#endif

#include "ds/array2d.h"

#include "fxttypes.h"


template <typename Type>
class array3d
// Three-dimensional array.
{
protected:
    array2d<Type> **arxp_;    // pointers to array2d at coordinate x
    Type *f_;        // pointer to data
    ulong nx_, ny_, nz_;  // dimensions
    bool myfq_;      // whether f_ was allocated by constructor

    ulong num_elem_;  // number of elements

private:  // have pointer data
    array3d(const array3d&) = delete;
    array3d & operator = (const array3d&) = delete;

public:
    explicit array3d(ulong nx, ulong ny, ulong nz, Type *f=nullptr)
    {
        nx_ = nx;
        ny_ = ny;
        nz_ = nz;
        num_elem_ = nx_ * ny_ * nz_;

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

        // setup pointers:
        arxp_ = new array2d<Type> * [nx_];
        const ulong na = ny_ * nz_;  // number of cells in each array2d
        for (ulong i=0; i<nx_; ++i)
            arxp_[i] = new array2d<Type>( nx_, ny_, f_ + i * na );

    }

    ~array3d()
    {
        for (ulong i=0; i<nx_; ++i)
            delete arxp_[i];
        delete [] arxp_;
        if ( myfq_ )  delete [] f_;
    }

    ulong num_x()  const  { return nx_; }
    ulong num_y()  const  { return ny_; }
    ulong num_z()  const  { return nz_; }

    ulong num_elem()  const  { return num_elem_; }

    const array3d<Type> & operator [] (ulong x)  const
    {
#ifdef  ARRAY3D_ASSERTS
        jjassert( x < nx_ );
#endif
        return * arxp_[x];
    }

    array2d<Type> & operator [] (ulong x)
    {
#ifdef  ARRAY3D_ASSERTS
        jjassert( x < nx_ );
#endif
        return * arxp_[x];
    }

public:
    bool is_off(ulong x, ulong y, ulong z)  const
    {
        if ( x >= nx_ )  return true;
        if ( y >= ny_ )  return true;
        if ( z >= nz_ )  return true;
        return false;
    }

public:
    void null()
    {
        for (ulong j=0; j< num_elem_; ++j)  f_[j] = 0;
    }

    void fill(const Type & v)
    {
        for (ulong j=0; j< num_elem_; ++j)  f_[j] = v;
    }
};
// -------------------------



#endif  // !defined HAVE_ARRAY3D_H__
