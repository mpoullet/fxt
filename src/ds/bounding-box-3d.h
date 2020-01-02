#if !defined  HAVE_BOUNDING_BOX_3D_H__
#define       HAVE_BOUNDING_BOX_3D_H__
// This file is part of the FXT library.
// Copyright (C) 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/point3d.h"

#include <iostream>


template <typename Type>
class bounding_box_3d
// 3-dimensional bounding box that can grow to contain
// coordinates given in the update() method.
{
public:
    typedef point3d<Type> Pnt;

protected:
    Type ix_, ax_;  // min-x, max-x
    Type iy_, ay_;  // min-y, max-y
    Type iz_, az_;  // min-z, max-z

public:
    void reset( const Pnt & P )
    {
        ix_ = P.x();  ax_ = P.x();
        iy_ = P.y();  ay_ = P.y();
        iz_ = P.z();  az_ = P.z();
    }

    explicit bounding_box_3d( const Pnt & P )
    { reset( P ); }

    explicit bounding_box_3d( const Pnt & P, const Pnt & Q )
    { reset( P );  update( Q ); }

    void update( const Pnt & P )
    // Enlarge bounding_box_3d to contain P if needed.
    {
        Type x = P.x(), y = P.y(), z = P.z();
        if ( x < ix_ )  ix_ = x;
        if ( x > ax_ )  ax_ = x;
        if ( y < iy_ )  iy_ = y;
        if ( y > ay_ )  ay_ = y;
        if ( z < iz_ )  iz_ = z;
        if ( z > az_ )  az_ = z;
    }

    Type delta_x()  const  { return ax_ - ix_; }  // width
    Type delta_y()  const  { return ay_ - iy_; }  // height
    Type delta_z()  const  { return az_ - iz_; }  // depth

    Type min_x()  const  { return ix_; }
    Type min_y()  const  { return iy_; }
    Type min_z()  const  { return iz_; }
    Type max_x()  const  { return ax_; }
    Type max_y()  const  { return ay_; }
    Type max_z()  const  { return az_; }

    Pnt min_point()  const  { return Pnt( ix_, iy_, iz_ ); }
    Pnt max_point()  const  { return Pnt( ax_, ay_, az_ ); }

    Pnt mid_point()  const
    {
        const Pnt Pi = min_point(),  Pa = max_point();
        return ::mid_point( Pi, Pa );
    }

//    Type max_extent()  const
//    {
//    }

    bool inside_q( const Pnt & P )
    {
        if ( ix_ > P.x() )  return false;
        if ( iy_ > P.y() )  return false;
        if ( iz_ > P.z() )  return false;
        if ( ax_ < P.x() )  return false;
        if ( ay_ < P.y() )  return false;
        if ( az_ < P.z() )  return false;
        return true;
    }
};
// -------------------------


template <typename Type>
inline std::ostream & operator << (std::ostream & os, const bounding_box_3d<Type> &B)
{
    os << " BB[" << B.min_point() << " , " << B.max_point() << "]";
    return os;
}
// -------------------------


#endif // !defined HAVE_BOUNDING_BOX_3D_H__
