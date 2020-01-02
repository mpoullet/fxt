#if !defined HAVE_POINT2D_H__
#define      HAVE_POINT2D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/vector2d.h"
#include "fxttypes.h"

#include <iostream>


template <typename Type>
class point2d
// Point in 2 dimensions with basic operations.
{
    typedef vector2d<Type> vec2d;

protected:
    Type x_, y_;

private:
    constexpr point2d() = default;  // default constructor for ...
public:
    static point2d * new_array(ulong n)  { return new point2d[n]; }

public:
    explicit constexpr point2d(const Type & tx, const Type & ty)
        : x_(tx), y_(ty)
    { ; }

    // Concession to programmer's reality:
    explicit constexpr point2d(const vec2d & V)
        : x_(V.x()), y_(V.y())
    { ; }

    Type x()  const  { return x_; }
    Type y()  const  { return y_; }

    // unary minus;
    point2d operator - ()  const  { return point2d( -x_, -y_ ); }

    // point +- vector ==> point
    point2d & operator += (const vec2d & V) { x_ += V.x(),  y_ += V.y();  return *this; }
    point2d & operator -= (const vec2d & V) { x_ -= V.x(),  y_ -= V.y();  return *this; }

    point2d operator + (const vec2d & V)  const { return point2d( x_ + V.x(),  y_ + V.y() ); }
    point2d operator - (const vec2d & V)  const { return point2d( x_ - V.x(),  y_ - V.y() ); }

    // point - point ==> vector
    vec2d operator - (const point2d & P)  const { return vec2d( x_ - P.x_,  y_ - P.y_ ); }
    // point + point ==> verboten

    bool operator == (const point2d & P) const { return ( x_ == P.x_ && y_ == P.y_ ); }
    bool operator != (const point2d & P) const { return ( x_ != P.x_ || y_ != P.y_ ); }

    // Concession to programmer's reality:
    vec2d as_vector()  const  {  return vec2d( x_, y_ ); }

    // The following with respect to origin (0, 0):
    point2d zoom( Type sc )  const { return point2d( sc * x_, sc * y_ ); }
};
// -------------------------


template <typename Type>
inline std::ostream & operator << (std::ostream & os, const point2d<Type> &P)
{
    os << "(" << P.x() << ", " << P.y() << ")";
    return os;
}
// -------------------------

inline point2d<double> mid_point(const point2d<double> & P, const point2d<double> & Q)
{
    return point2d<double>( 0.5 * (P.x() + Q.x()) , 0.5 * (P.y() + Q.y()) );
}
// -------------------------

inline point2d<float> mid_point(const point2d<float> & P, const point2d<float> & Q)
{
    return point2d<float>( 0.5f * (P.x() + Q.x()) , 0.5f * (P.y() + Q.y()) );
}
// -------------------------

inline point2d<long double> mid_point(const point2d<long double> & P, const point2d<long double> & Q)
{
    return point2d<long double>( 0.5L * (P.x() + Q.x()) , 0.5L * (P.y() + Q.y()) );
}
// -------------------------


template <typename Type>
inline point2d<Type> mid_point(const point2d<Type> & P, const point2d<Type> & Q)
{
//    std::cout << "mid_point<int_type>" << std::endl;
    return point2d<Type>( (P.x() + Q.x()) / 2 , (P.y() + Q.y()) / 2 );
}
// -------------------------



#endif  // !defined HAVE_POINT2D_H__
