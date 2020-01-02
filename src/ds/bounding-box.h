#if !defined HAVE_BOUNDING_BOX_H__
#define      HAVE_BOUNDING_BOX_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/point2d.h"

#include <iostream>


template <typename Type>
class bounding_box
// 2-dimensional bounding box that can grow to contain
// coordinates given in the update() method.
{
public:
    typedef point2d<Type> Pnt;

protected:
    Type ix_, ax_;  // min-x, max-x
    Type iy_, ay_;  // min-y, max-y

public:
    void reset( const Pnt & P )
    {
        ix_ = P.x();  ax_ = P.x();
        iy_ = P.y();  ay_ = P.y();
    }

    explicit bounding_box( const Pnt & P )
    { reset( P ); }

    explicit bounding_box( const Pnt & P, const Pnt & Q )
    { reset( P );  update( Q ); }

    void update( const Pnt & P )
    // Enlarge bounding_box to contain P if needed.
    {
        Type x = P.x(), y = P.y();
        if ( x < ix_ )  ix_ = x;
        if ( x > ax_ )  ax_ = x;
        if ( y < iy_ )  iy_ = y;
        if ( y > ay_ )  ay_ = y;
    }

    Type delta_x()  const  { return ax_ - ix_; }  // width
    Type delta_y()  const  { return ay_ - iy_; }  // height

    Type min_x()  const  { return ix_; }
    Type min_y()  const  { return iy_; }
    Type max_x()  const  { return ax_; }
    Type max_y()  const  { return ay_; }

    Pnt min_point()  const  { return Pnt( ix_, iy_ ); }
    Pnt max_point()  const  { return Pnt( ax_, ay_ ); }

    Pnt mid_point()  const
    {
        const Pnt Pi = min_point(),  Pa = max_point();
        return ::mid_point( Pi, Pa );
    }

//    Type max_extent()  const
//    {
//        const double dx = delta_x(),  dy = delta_y();
//        return ( dx > dy ? dx : dy );
//    }

    bool inside_q( const Pnt & P )
    {
        if ( ix_ > P.x() )  return false;
        if ( iy_ > P.y() )  return false;
        if ( ax_ < P.x() )  return false;
        if ( ay_ < P.y() )  return false;
        return true;
    }
};
// -------------------------


template <typename Type>
inline std::ostream & operator << (std::ostream & os, const bounding_box<Type> &B)
{
    os << " BB[" << B.min_point() << " , " << B.max_point() << "]";
    return os;
}
// -------------------------



#endif  // !defined HAVE_BOUNDING_BOX_H__
