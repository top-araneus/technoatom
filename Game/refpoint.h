#ifndef REFPOINT_H
#define REFPOINT_H
#include <math.h>
template <typename CoordType>
class LinearVector
{
    public:
        CoordType x_;
        CoordType y_;
        LinearVector();
        LinearVector(CoordType x, CoordType y);
        LinearVector(LinearVector& that);
        LinearVector(LinearVector&& that);
        LinearVector& operator=(LinearVector& that);
        LinearVector& operator=(LinearVector&& that);
        LinearVector& operator-(LinearVector& that) const;
        LinearVector& operator+(LinearVector& that) const;
        bool operator==(LinearVector& that) const;
        bool operator!=(LinearVector& that) const;
        bool operator==(LinearVector&& that) const;
        bool operator!=(LinearVector&& that) const;
        operator sf::Vector2f();
        double GetAbs();
};

template <typename CoordType>
LinearVector<CoordType>::LinearVector()
{
    x_ = 0;
    y_ = 0;
}

template <typename CoordType>
LinearVector<CoordType>::LinearVector(CoordType x, CoordType y)
{
    x_ = x;
    y_ = y;
}

template <typename CoordType>
LinearVector<CoordType>::LinearVector(LinearVector& that)
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
LinearVector<CoordType>& LinearVector<CoordType>::operator=(LinearVector<CoordType>& that)
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
LinearVector<CoordType>& LinearVector<CoordType>::operator-(LinearVector<CoordType>& that) const
{
    LinearVector<CoordType> res = LinearVector<CoordType>(x_, y_);
    res.x_ = res.x_ - that.x_;
    res.y_ = res.y_ - that.y_;
    return res;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator+(LinearVector<CoordType>& that) const
{
    LinearVector<CoordType> res = LinearVector<CoordType>(x_, y_);
    res.x_ = res.x_ + that.x_;
    res.y_ = res.y_ + that.y_;
    return res;
}

template <typename CoordType>
double LinearVector<CoordType>::GetAbs()
{
    return sqrt(x_*x_ + y_*y_);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator==(LinearVector& that) const
{
    return (x_ == that.x_ && y_ == that.y_);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator!=(LinearVector& that) const
{
    return !((*this) == that);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator==(LinearVector&& that) const
{
    return (x_ == that.x_ && y_ == that.y_);
}

template <typename CoordType>
bool LinearVector<CoordType>::operator!=(LinearVector&& that) const
{
    return !((*this) == that);
}

template <typename CoordType>
LinearVector<CoordType>::operator sf::Vector2f()
{
    sf::Vector2f result;
    result.x = this->x_;
    result.y = this->y_;
    return result;
}

class ReferenceFrame
{
private:
    LinearVector<int> coords_;
public:
    LinearVector<int> size_;
    ReferenceFrame()
    {
        coords_ = LinearVector<int>(0,0);
        size_ = LinearVector<int>(800,600);
    }
    ReferenceFrame(int x, int y, int width, int height)
    {
        coords_ = LinearVector<int>(x,y);
        size_ = LinearVector<int>(width, height);
    }
    void SetX(int x)
    {
        coords_.x_ = x;
    }
    void SetY(int y)
    {
        coords_.y_ = y;
    }

    int GetX()
    {
        return coords_.x_;
    }
    int GetY()
    {
        return coords_.y_;
    }
};

#endif
