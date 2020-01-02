#if !defined HAVE_POINT3D_H__
#define      HAVE_POINT3D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018, 2019 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "ds/vector3d.h"
#include "fxttypes.h"

#include <iostream>


template <typename Type>
class point3d
// Point in 3 dimensions with basic operations.
{
    typedef vector3d<Type> vec3d;

protected:
    Type x_, y_, z_;

private:
    constexpr point3d() = default;  // default constructor for ...
public:
    static point3d * new_array(ulong n)  { return new point3d[n]; }

public:
    explicit constexpr point3d(const Type & tx, const Type & ty, const Type & tz)
        : x_(tx), y_(ty), z_(tz)
    { ; }
    // Concession to programmer's reality:
    explicit constexpr point3d(const vec3d & V)
        : x_(V.x()), y_(V.y()), z_(V.z())
    { ; }

    Type x()  const  { return x_; }
    Type y()  const  { return y_; }
    Type z()  const  { return z_; }

    // point +- vector ==> point
    point3d & operator += (const vec3d & V) { x_ += V.x(),  y_ += V.y(),  z_ += V.z();  return *this; }
    point3d & operator -= (const vec3d & V) { x_ -= V.x(),  y_ -= V.y();  z_ -= V.z();  return *this; }

    // unary minus;
    point3d operator - ()  const  { return point3d( -x_, -y_, -z_ ); }

    point3d operator + (const vec3d & V)  const { return point3d( x_ + V.x(),  y_ + V.y(),  z_ + V.z() ); }
    point3d operator - (const vec3d & V)  const { return point3d( x_ - V.x(),  y_ - V.y(),  z_ - V.z() ); }

    // point - point ==> vector
    vec3d operator - (const point3d & P)  const { return vec3d( x_ - P.x_,  y_ - P.y_,  z_ - P.z_ ); }
    // point + point ==> verboten

    bool operator == (const point3d & P) const { return ( x_ == P.x_ && y_ == P.y_ && z_ == P.z_ ); }
    bool operator != (const point3d & P) const { return ( x_ != P.x_ || y_ != P.y_ || z_ != P.z_ ); }

    // Concession to programmer's reality:
    vec3d as_vector()  const  {  return vec3d( x_, y_, z_ ); }

    // The following with respect to origin (0, 0):
    point3d zoom( Type sc )  const { return point3d( sc * x_, sc * y_, sc * z_ ); }
};
// -------------------------


template <typename Type>
inline std::ostream & operator << (std::ostream & os, const point3d<Type> &P)
{
    os << "(" << P.x() << ", " << P.y() << ", " << P.z() << ")";
    return os;
}
// -------------------------

inline point3d<double> mid_point(const point3d<double> & P, const point3d<double> & Q)
{
    return point3d<double>( 0.5 * (P.x() + Q.x()) , 0.5 * (P.y() + Q.y()) , 0.5 * (P.z() + Q.z()) );
}
// -------------------------

inline point3d<float> mid_point(const point3d<float> & P, const point3d<float> & Q)
{
    return point3d<float>( 0.5f * (P.x() + Q.x()) , 0.5f * (P.y() + Q.y()) , 0.5f * (P.z() + Q.z()) );
}
// -------------------------

inline point3d<long double> mid_point(const point3d<long double> & P, const point3d<long double> & Q)
{
    return point3d<long double>( 0.5L * (P.x() + Q.x()) , 0.5L * (P.y() + Q.y()) , 0.5L * (P.z() + Q.z()) );
}
// -------------------------


template <typename Type>
inline point3d<Type> mid_point(const point3d<Type> & P, const point3d<Type> & Q)
{
//    std::cout << "mid_point<int_type>" << std::endl;
    return point3d<Type>( (P.x() + Q.x()) / 2 , (P.y() + Q.y()) / 2 , (P.z() + Q.z()) / 2 );
}
// -------------------------



#endif  // !defined HAVE_POINT3D_H__
