#if !defined HAVE_MATRIX_H__
#define      HAVE_MATRIX_H__
// This file is part of the FXT library.
// Copyright (C) 2010, 2011, 2012, 2014, 2017 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/array2d.h"

#include "aux1/copy.h"
#include "aux2/transpose.h"

#include "jjassert.h"

#include "fxttypes.h"


template <typename Type>
class matrix : public array2d<Type>
// Very simple class for square matrix.
// Deprecated, usage is strongly discouraged.
{
    using array2d<Type>::f_;
    using array2d<Type>::nr_;
    using array2d<Type>::nc_;
    using array2d<Type>::rowp_;
    using array2d<Type>::null;
    using array2d<Type>::num_elem;

public:
    matrix(ulong n)
        : array2d<Type>(n, n)
    { ; }

    matrix(const matrix<Type> &m)
        : array2d<Type>(m.nr_, m.nc_)
    {
        *this = m;
    }

    ~matrix()  { }

    matrix<Type> & operator =(const matrix<Type> &m)
    {
        ::acopy(m.f_, f_, num_elem() );
        return *this;
    }

    void transpose()
    {
        ::transpose_square(rowp_, nr_);
    }


    bool is_diag(Type v)  const
    // Whether diagonal with diagonal entries ==v
    {
        for (ulong k=0; k<nr_; ++k)
            if (v != rowp_[k][k])  return false;

        for (ulong r=0; r<nr_; ++r)
            for (ulong c=0; c<nc_; ++c)
                if ( (c!=r) && (rowp_[r][c]!=0) )  return false;

        return true;
    }

    void set_diag(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] = v; }

    void unit(Type v=1)  { null();  set_diag( v ); }


    bool is_unitary(Type v)  const
    {
        if ( nr_ != nc_ )  return false;
        matrix<Type> T(*this);  T.transpose();
        T *= *this;
        return  T.is_diag(v);
    }


    bool kronecker(const matrix<Type> A, const matrix<Type> B)
    {
        ulong nra = A.nr_,  nca = A.nc_;
        ulong nrb = B.nr_,  ncb = B.nc_;
        if ( nra * nrb != nr_ )  return false;
        if ( nca * ncb != nc_ )  return false;
        for (ulong ra=0; ra<nra; ++ra)
        {
            ulong ro = ra * nrb;
            for (ulong ca=0; ca<nca; ++ca)
            {
                ulong co = ca * ncb;
                Type ea = A[ra][ca];
                for (ulong rb=0; rb<nrb; ++rb)
                {
                    ulong r = ro + rb;
                    for (ulong cb=0; cb<ncb; ++cb)
                    {
                        Type eb = B[rb][cb];
                        ulong c = co + cb;
                        Type p = ea * eb;
                        (*this)[r][c] = p;
                    }
                }
            }
        }
        return true;
    }

    void diag_add_val(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] += v; }

    void diag_subtract_val(Type v)
    { for (ulong k=0; k<nr_; ++k)  rowp_[k][k] -= v; }


    matrix<Type> & operator += (const matrix<Type> &h)
    { this->add(h);  return *this; }

    matrix<Type> & operator -= (const matrix<Type> &h)
    { this->subtract(h);  return *this; }

    matrix<Type> operator *(const matrix<Type> &B)  const
    {
//        jjassert( nr_ == B.nr_ );
        const matrix<Type> & A = *this;
        matrix<Type> R(nr_);
        for (ulong r=0; r<nr_; ++r)
        {
            for (ulong c=0; c<nc_; ++c)
            {
                Type s = 0;
                for (ulong k=0; k<nc_; ++k)
                    s += A[r][k] * B[k][c];
                R[r][c] = s;
            }
        }
        return R;
    }

    matrix<Type> & operator *=(const matrix<Type> &B)
    {
//        jjassert( nr_ == B.nr_ );
        matrix<Type> T(nr_);
        T = *this * B;
        *this = T;
        return *this;
    }
};
// -------------------------



#endif  // !defined HAVE_MATRIX_H__
