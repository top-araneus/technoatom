#ifndef TRANSFORMATION_H
#define TRANSFORMATION_H
#include "linearvector.h"
#include <math.h>
const int kCellWidth = 128;
const int kCellHeight = 64;
const int kTilesAtLine = 40;

double Pythagor(double x, double y)
{
  return sqrt(x*x + y*y);
}

LinearVector<int> GetCoordsFromCell(LinearVector<int> cell)
{
    LinearVector<int> result;
    result.x_ = cell.x_ * kCellWidth / 2 + cell.y_ * kCellWidth / 2 + kCellWidth / 2;
    result.y_ = kTilesAtLine * kCellHeight / 2 + cell.x_ * kCellHeight / 2 - cell.y_ * kCellHeight / 2 + kCellHeight / 2;
    return result;
}
LinearVector<int> GetCellFromCoords(LinearVector<int> coords)
{
    LinearVector<int> result(0,0);
    int tmp = kTilesAtLine*kCellHeight/2 + kCellHeight/2;
    if((coords.y_ - tmp ) >=0)
    {
        result.y_ = roundl((Pythagor(coords.x_ / 2.0, coords.x_ / 4.0) - Pythagor(coords.y_ - tmp, (coords.y_ - tmp) / 2.0)) / Pythagor(kCellWidth / 2, kCellHeight / 2 ) - 0.5);
        result.x_ = roundl((Pythagor(coords.y_ - tmp, (coords.y_ - tmp) / 2.0) + Pythagor(coords.x_ / 2.0, coords.x_ / 4.0)) / Pythagor(kCellWidth / 2, kCellHeight / 2 ) - 0.5);
    }
    else
    {
        result.y_ = roundl((Pythagor(coords.y_ - tmp, (coords.y_ - tmp) / 2.0) + Pythagor(coords.x_ / 2.0, coords.x_ / 4.0)) / Pythagor(kCellWidth / 2, kCellHeight / 2 ) - 0.5);
        result.x_ = roundl((Pythagor(coords.x_ / 2.0, coords.x_ / 4.0) - Pythagor(coords.y_ - tmp, (coords.y_ - tmp) / 2.0)) / Pythagor(kCellWidth / 2, kCellHeight / 2 ) - 0.5);
    }
    print("Got /# /#, calculated /# /#  center/#\n", coords.x_, coords.y_, result.x_, result.y_, tmp);
    return result;
}

#endif
