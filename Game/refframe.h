#ifndef ref_frame_H
#define ref_frame_H
#include "linearvector.h"

class ReferenceFrame
{
  public:
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

  void SetX(int x) {
    coords_.x_ = x;
  }
  void SetY(int y) {
    coords_.y_ = y;
  }
  int  GetX() {
    return coords_.x_;
  }
  int  GetY() {
    return coords_.y_;
  }
  LinearVector<int> GetCoords() {
    return coords_;
  }

  LinearVector<int> size_;

  private:
  LinearVector<int> coords_;
};

#endif

