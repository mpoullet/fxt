#if !defined HAVE_VECTOR_H__
#define      HAVE_VECTOR_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "aux1/copy.h"  // acopy()

#include "fxttypes.h"

// note: todo: insert compatibility checks with binary vector-operations


template <typename Type>
class vector
// Very simple vector class.
// Deprecated, usage is strongly discouraged.
{
public:
    ulong n_;  // #elems
    Type *f_;  // pointer to data

public:
    explicit vector(ulong n)
        : n_(n)
    {
        f_ = new Type[n_];
    }

    explicit vector(const vector<Type> &m)
    {
        f_ = new Type[n_];
        acopy(m.f_, f_, n_);
    }

    ~vector()
    {
        delete [] f_;
    }

    vector<Type> & operator =(const vector<Type> &m)
    {
        copy(m, *this);
        return *this;
    }

    vector<Type> & operator += (const vector<Type> &h)
    {
        for (ulong j=0; j<n_; ++j)  f_[j] += h.f_[j];
        return *this;
    }

    vector<Type> & operator -= (const vector<Type> &h)
    {
        for (ulong j=0; j<n_; ++j)  f_[j] -= h.f_[j];
        return *this;
    }

    vector<Type> & operator *= (const Type & i)
    {
        for (ulong j=0; j<n_; ++j)  f_[j] *= i;
        return *this;
    }
};
// -------------------------





#endif  // !defined HAVE_VECTOR_H__
