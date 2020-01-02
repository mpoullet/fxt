#if !defined  HAVE_CENTERED_ARRAY2D_H__
#define       HAVE_CENTERED_ARRAY2D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/vector2d.h"
#include "ds/point2d.h"
#include "ds/array2d.h"
#include "fxttypes.h"


//#define CENTERED_ARRAY2D_ASSERTS  // define to catch access beyond size
#ifdef CENTERED_ARRAY2D_ASSERTS
#include "jjassert.h"
#endif


template <typename Type>
class centered_array2d
// Centered 2-dimensional array from array2d<Type>,
// using point2d<long> or vector2d<long> for coordinates.
// Valid cells are in the range [ +-k , +-k ].
{
public:
    typedef point2d<long> Pnt;
    typedef vector2d<long> Vec;

private:
    long k;
    array2d<Type> A;

public:
    explicit centered_array2d(ulong ck)
        : k( (long)ck ),
          A( (ulong)(2*k + 1),  (ulong)(2*k + 1) )
    { ; }

    ~centered_array2d()  {;}

    const Type & operator [] (const Vec & V)  const
    {
#ifdef CENTERED_ARRAY2D_ASSERTS
        jjassert( V.x() <= +k );
        jjassert( V.x() >= -k );
        jjassert( V.y() <= +k );
        jjassert( V.y() >= -k );
#endif
        return  A[ (ulong)( V.x() + k ) ][ (ulong)( V.y() + k ) ];
    }

    Type & operator [] (const Vec & V)
    {
#ifdef CENTERED_ARRAY2D_ASSERTS
        jjassert( V.x() <= +k );
        jjassert( V.x() >= -k );
        jjassert( V.y() <= +k );
        jjassert( V.y() >= -k );
#endif
        return  A[ (ulong)( V.x() + k ) ][ (ulong)( V.y() + k ) ];
    }

    const Type & operator [] (const Pnt & P)  const
    {
        return  operator [] ( P.as_vector() );
    }

    Type & operator [] (const Pnt & P)
    {
        return  operator [] ( P.as_vector() );
    }

    bool is_off(const Vec & V)  const
    {
        if ( V.x() > +k )  return true;
        if ( V.x() < -k )  return true;
        if ( V.y() > +k )  return true;
        if ( V.y() < -k )  return true;
        return false;
    }

    bool is_off(const Pnt & P)  const
    {
        return is_off( P.as_vector() );
    }

    ulong num_elem()  const  { return A.num_elem(); }

    void null()  { A.null(); }
    void fill(const Type & v)  { A.fill(v); }

    ulong get_k()  const  { return (ulong)k; }
};
// -------------------------


#endif // !defined HAVE_CENTERED_ARRAY2D_H__
