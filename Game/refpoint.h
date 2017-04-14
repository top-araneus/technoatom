#ifndef REFPOINT_H
#define REFPOINT_H

template <typename CoordType>
class LinearVector
{
    public:
        CoordType x_;
        CoordType y_;
        LinearVector();
        LinearVector(CoordType x, CoordType y);
        LinearVector& operator=(LinearVector& that);
        LinearVector& operator=(LinearVector&& that);
        LinearVector& operator-(LinearVector& that) const;
        LinearVector& operator+(LinearVector& that) const;
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
    LinearVector<CoordType> v = LinearVector<CoordType>(x_, y_);
    v.x_ = v.x_ - that.x_;
    v.y_ = v.y_ - that.y_;
    return v;
}

template <typename CoordType>
LinearVector<CoordType>& LinearVector<CoordType>::operator+(LinearVector<CoordType>& that) const
{
    LinearVector<CoordType> v = LinearVector<CoordType>(x_, y_);
    v.x_ = v.x_ + that.x_;
    v.y_ = v.y_ + that.y_;
    return v;
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
