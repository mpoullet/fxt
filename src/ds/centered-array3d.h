#if !defined  HAVE_CENTERED_ARRAY3D_H__
#define       HAVE_CENTERED_ARRAY3D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/vector3d.h"
#include "ds/point3d.h"
#include "ds/array3d.h"
#include "fxttypes.h"


//#define CENTERED_ARRAY2D_ASSERTS  // define to catch access beyond size
#ifdef CENTERED_ARRAY2D_ASSERTS
#include "jjassert.h"
#endif


template <typename Type>
class centered_array3d
// Centered 2-dimensional array from array3d<Type>,
// using point3d<long> or vector3d<long> for coordinates.
// Valid cells are in the range [ +-k , +-k , +-k ].
{
public:
    typedef point3d<long> Pnt;
    typedef vector3d<long> Vec;

private:
    long k;
    array3d<Type> A;

public:
    explicit centered_array3d(ulong ck)
        : k( (long)ck ),
          A( (ulong)(2*k + 1),  (ulong)(2*k + 1), (ulong)(2*k + 1) )
    { ; }

    ~centered_array3d()  {;}

    const Type & operator [] (const Vec & V)  const
    {
#ifdef CENTERED_ARRAY3D_ASSERTS
        jjassert( V.x() <= +k );
        jjassert( V.x() >= -k );
        jjassert( V.y() <= +k );
        jjassert( V.y() >= -k );
        jjassert( V.z() <= +k );
        jjassert( V.z() >= -k );
#endif
        return  A[ (ulong)( V.x() + k ) ][ (ulong)( V.y() + k ) ][ (ulong)( V.z() + k ) ];
    }

    Type & operator [] (const Vec & V)
    {
#ifdef CENTERED_ARRAY3D_ASSERTS
        jjassert( V.x() <= +k );
        jjassert( V.x() >= -k );
        jjassert( V.y() <= +k );
        jjassert( V.y() >= -k );
        jjassert( V.z() <= +k );
        jjassert( V.z() >= -k );
#endif
        return  A[ (ulong)( V.x() + k ) ][ (ulong)( V.y() + k ) ][ (ulong)( V.z() + k ) ];
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
        if ( V.z() > +k )  return true;
        if ( V.z() < -k )  return true;
        return false;
    }

    bool is_off(const Pnt & P)  const
    {
        return is_off( P.as_vector() );
    }

    ulong num_elem()  const  { return A.num_elem(); }

    void null()  { A.null(); }
    void fill(const Type & V)  { A.fill(V); }

    ulong get_k()  const  { return (ulong)k; }
};
// -------------------------


#endif // !defined HAVE_CENTERED_ARRAY3D_H__
