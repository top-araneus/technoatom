#ifndef LINEARVECTOR_H
#define LINEARVECTOR_H

#include <math.h>
template <typename CoordType>
class LinearVector
{
  public:
    LinearVector();
    LinearVector(const CoordType& x, const CoordType& y);
    LinearVector(const LinearVector& that);
    LinearVector(LinearVector&& that);
    LinearVector& operator=(const LinearVector& that);
    LinearVector& operator=(LinearVector&& that);
    LinearVector& operator-(const LinearVector& that) const;
    LinearVector& operator+(LinearVector&& that) const;
    LinearVector& operator+(const LinearVector& that) const;
    bool operator==(const LinearVector& that) const;
    bool operator!=(const LinearVector& that) const;
    bool operator==(const LinearVector&& that) const;
    bool operator!=(const LinearVector&& that) const;
    operator sf::Vector2f();
    double GetAbs() const;
    LinearVector<double> GetNorm() const;

    CoordType x_;
    CoordType y_;
};

template <typename CoordType>
LinearVector<CoordType>::LinearVector()
{
  x_ = 0;
  y_ = 0;
}

template <typename CoordType>
LinearVector<CoordType>::LinearVector(const CoordType& x, const CoordType& y)
{
  x_ = x;
  y_ = y;
}

template <typename CoordType>
LinearVector<CoordType>::LinearVector(const LinearVector& that)
{
  x_ = that.x_;
  y_ = that.y_;
}

template <typename CoordType>
LinearVector<CoordType>::LinearVector(LinearVector&& that)
{
  x_ = that.x_;
  y_ = that.y_;
}



template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator=(const LinearVector<CoordType>& that)
{
  if (this != &that)
  {
    x_ = that.x_;
    y_ = that.y_;
  }
  return *this;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator=(LinearVector<CoordType>&& that)
{
  x_ = that.x_;
  y_ = that.y_;
  return *this;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator-(const LinearVector<CoordType>& that) const
{
  auto res = LinearVector<CoordType>(x_, y_);
  res.x_ = res.x_ - that.x_;
  res.y_ = res.y_ - that.y_;
  return res;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator+(LinearVector<CoordType>&& that) const
{
  //auto res = LinearVector<CoordType>(x_, y_);
  that.x_ = x_ + that.x_;
  that.y_ = y_ + that.y_;
 // int x = 0;    // MAGIC BUT DOESN'T WORK WITHOUT THIS STRING
  return that;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator+(const LinearVector<CoordType>& that) const
{
  auto res = LinearVector<CoordType>(x_, y_);
  res.x_ = res.x_ + that.x_;
  res.y_ = res.y_ + that.y_;
  return res;
}

template <typename CoordType>
double LinearVector<CoordType>::GetAbs() const
{
  return sqrt(x_*x_ + y_*y_);
}


template <typename CoordType>
LinearVector<double> LinearVector<CoordType>::GetNorm() const
{
  if (GetAbs() != 0)
    return LinearVector<double>(x_ / GetAbs(), y_ / GetAbs());
  else
    return LinearVector<double>(0,0);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator==(const LinearVector& that) const
{
  return (x_ == that.x_ && y_ == that.y_);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator!=(const LinearVector& that) const
{
  return !(*this == that);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator==(const LinearVector&& that) const
{
  return (x_ == that.x_ && y_ == that.y_);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator!=(const LinearVector&& that) const
{
  return !(*this == that);
}

template <typename CoordType>
LinearVector<CoordType>::operator sf::Vector2f()
{
  sf::Vector2f result;
  result.x = this->x_;
  result.y = this->y_;
  return result;
}

#endif // LINEARVECTOR_H
