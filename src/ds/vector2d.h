#if !defined HAVE_VECTOR2D_H__
#define      HAVE_VECTOR2D_H__
// This file is part of the FXT library.
// Copyright (C) 2017, 2018 Joerg Arndt
// License: GNU General Public License version 3 or later,
// see the file COPYING.txt in the main directory.


#include "fxttypes.h"

#include <iostream>


template <typename Type>
class vector2d
// 2-dimensional vector with basic operations.
{
protected:
    Type x_, y_;

private:
    constexpr vector2d() = default;   // default constructor for ...
public:
    static vector2d * new_array(ulong n)  { return new vector2d[n]; }

public:
    explicit constexpr vector2d(const Type & tx, const Type & ty)
        : x_(tx), y_(ty)
    { ; }


    Type x()  const  { return x_; }
    Type y()  const  { return y_; }

    vector2d & operator += (const vector2d & V) { x_ += V.x_,  y_ += V.y_;  return *this; }
    vector2d & operator -= (const vector2d & V) { x_ -= V.x_,  y_ -= V.y_;  return *this; }

    vector2d & operator *= (const Type & s) { x_ *= s,  y_ *= s;  return *this; }

    vector2d operator + (const vector2d & V)  const { return vector2d( x_ + V.x_,  y_ + V.y_ ); }
    vector2d operator - (const vector2d & V)  const { return vector2d( x_ - V.x_,  y_ - V.y_ ); }

    vector2d operator - ()  const { return vector2d( -x_,  -y_ ); }
    vector2d operator + ()  const { return vector2d( +x_,  +y_ ); }

    bool operator == (const vector2d & V) const { return ( x_ == V.x_ && y_ == V.y_); }
    bool operator != (const vector2d & V) const { return ( x_ != V.x_ || y_ != V.y_); }

    Type norm_sqr()  const  { return x_ * x_ + y_ * y_; }
    Type norm_L1()  const
    {
        Type N = 0;
        N += ( x_ > 0 ? +x_ : -x_ );
        N += ( y_ > 0 ? +y_ : -y_ );
        return N;
    }
};
// -------------------------


template <typename Type>
inline vector2d<Type> operator *(const Type &a, const vector2d<Type> &V)
// Product scalar * vector.
{
    return vector2d<Type>( a * V.x(), a * V.y() );
}
// -------------------------


template <typename Type>
inline Type outer_z_left(const vector2d<Type> &V, const vector2d<Type> &W)
// Return z-coordinate of cross product for 3D vectors
// [V.x(), V.y(), 0] and [W.x(), W.y(), 0]
// for left handed coordinates.
{
    return  V.y() * W.x() - V.x() * W.y();
}
// -------------------------

template <typename Type>
inline Type outer_z_right(const vector2d<Type> &V, const vector2d<Type> &W)
// Return z-coordinate of cross product for 3D vectors
// [V.x(), V.y(), 0] and [W.x(), W.y(), 0]
// for right handed coordinates.
{
    return  V.x() * W.y() - V.y() * W.x();
}
// -------------------------


template <typename Type>
inline Type operator *(const vector2d<Type> &V, const vector2d<Type> &W)
// Scalar Product.
{
    return  V.x() * W.x() + V.y() * W.y();
}
// -------------------------

template <typename Type>
inline std::ostream & operator << (std::ostream & os, const vector2d<Type> &V)
{
    os << "[" << V.x() << ", " << V.y() << "]";
    return os;
}
// -------------------------


#endif  // !defined HAVE_VECTOR2D_H__
