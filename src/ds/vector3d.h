#if !defined HAVE_VECTOR3D_H__
#define      HAVE_VECTOR3D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#include <iostream>


template <typename Type>
class vector3d
// 3-dimensional vector with basic operations.
{
protected:
    Type x_, y_, z_;

private:
    constexpr vector3d() = default;  // default constructor for ...
public:
    static vector3d * new_array(ulong n)  { return new vector3d[n]; }

public:
    explicit constexpr vector3d(const Type & tx, const Type & ty, const Type & tz)
        : x_(tx), y_(ty), z_(tz)
    { ; }


    Type x()  const  { return x_; }
    Type y()  const  { return y_; }
    Type z()  const  { return z_; }

    vector3d & operator += (const vector3d & V) { x_ += V.x_,  y_ += V.y_;  z_ += V.z_;  return *this; }
    vector3d & operator -= (const vector3d & V) { x_ -= V.x_,  y_ -= V.y_;  z_ -= V.z_;  return *this; }

    vector3d & operator *= (const Type & s) { x_ *= s,  y_ *= s;  z_ *= s;  return *this; }

    vector3d operator + (const vector3d & V)  const { return vector3d( x_ + V.x_,  y_ + V.y_,  z_ + V.z_ ); }
    vector3d operator - (const vector3d & V)  const { return vector3d( x_ - V.x_,  y_ - V.y_,  z_ - V.z_  ); }

    vector3d operator - ()  const { return vector3d( -x_,  -y_, -z_ ); }
    vector3d operator + ()  const { return vector3d( +x_,  +y_, +z_ ); }

    bool operator == (const vector3d & V) const { return ( x_ == V.x_ && y_ == V.y_ && z_ == V.z_); }
    bool operator != (const vector3d & V) const { return ( x_ != V.x_ || y_ != V.y_ || z_ != V.z_); }

    Type norm_sqr()  const  { return x_ * x_ + y_ * y_ + z_ * z_; }
    Type norm_L1()  const
    {
        Type N = 0;
        N += ( x_ > 0 ? +x_ : -x_ );
        N += ( y_ > 0 ? +y_ : -y_ );
        N += ( z_ > 0 ? +z_ : -z_ );
        return N;
    }
};
// -------------------------


template <typename Type>
inline vector3d<Type> operator *(const Type &a, const vector3d<Type> &V)
// Product scalar * vector.
{
    return vector3d<Type>( a * V.x(), a * V.y(), a * V.z() );
}
// -------------------------

template <typename Type>
inline Type operator *(const vector3d<Type> &V, const vector3d<Type> &W)
// Scalar Product.
{
    return  V.x() * W.x() + V.y() * W.y() + V.z() * W.z();
}
// -------------------------


template <typename Type>
inline vector3d<Type> outer_left(const vector3d<Type> &V, const vector3d<Type> &W)
// Return cross product for left handed coordinates.
{
    return vector3d<Type>(
                          V.z() * W.y() - V.y() * W.z(),
                          V.x() * W.z() - V.z() * W.x(),
                          V.y() * W.x() - V.x() * W.y());
}
// -------------------------

template <typename Type>
inline vector3d<Type> outer_right(const vector3d<Type> &V, const vector3d<Type> &W)
// Return cross product for right handed coordinates.
{
    return vector3d<Type>(
                          V.y() * W.z() - V.z() * W.y(),
                          V.z() * W.x() - V.x() * W.z(),
                          V.x() * W.y() - V.y() * W.x());
}
// -------------------------


template <typename Type>
inline std::ostream & operator << (std::ostream & os, const vector3d<Type> &V)
{
    os << "[" << V.x() << ", " << V.y() << ", " << V.z() << "]";
    return os;
}
// -------------------------


#endif  // !defined HAVE_VECTOR3D_H__
