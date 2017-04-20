#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include <../stack/stack/smart_ptr.h>

const int CellWidth = 64;
const int CellHeight = 32;
const int TILES_AT_LINE = 50;
class GameObject
{
    public:
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        virtual void Move() = 0;
        GameObject();
        virtual ~GameObject() = 0;
    protected:
        LinearVector<int> refCoords_;
        LinearVector<int> cellCenter_;
        LinearVector<int> gridCoords_;
        unsigned char numOfFrames_;
        unsigned char curFrame_;
        unsigned char numOfState_;
        unsigned char curState_;
        Texture texture_;
        LinearVector<unsigned char> spriteSize_; //!< width and height of sprites is in tile count
        static Unique_ptr<Array<Array<Unique_ptr<GameObject>>>> map_;
        static Unique_ptr<ReferenceFrame> refFrame_;
};

class StaticObject :public GameObject
{
    public:
        StaticObject(LinearVector<int> refCoords)
        {
            refCoords_ = refCoords;
        }
        virtual ~StaticObject() = 0;
        virtual void Draw()  override = 0;
        virtual void Interact() override = 0;
        virtual void Move() override = 0;

};

class MovingObject :public GameObject
{
    protected:
        LinearVector<int> velocity_;
    public:
        MovingObject(LinearVector<int> refCoords)
        {
            refCoords_ = refCoords;
            velocity_ = LinearVector<int>(0,0);
        }
        MovingObject(LinearVector<int> refCoords, LinearVector<int> velocity)
        {
            refCoords_ = refCoords;
            velocity_ = velocity;
        }
        virtual ~MovingObject();
        virtual void Draw() override = 0;
        virtual void Interact() override = 0;
        virtual void Move()
        {
            if(velocity_ != LinearVector<int>(0,0))
            {
                if(velocity_.x_ + refCoords_.x_ > 0 &&
                   velocity_.x_ + refCoords_.x_ < refFrame_->size_.x_ &&
                   velocity_.y_ + refCoords_.y_ > 0 &&
                   velocity_.y_ + refCoords_.y_ < refFrame_->size_.y_)
                   {    //!Нужно много проверок, проверки занятости клетки, проверки выхода за границу клетки

                       LinearVector<int> tmp = refCoords_ + velocity_;

                        if (tmp.x_ > cellCenter_.x_)
                        {
                            if ((tmp.y_ - cellCenter_.y_) < -0.5 * (tmp.x_ - (cellCenter_.x_ + CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                if (gridCoords_.y_ % 2 == 1)
                                {
                                    newCell.x_ += 1;
                                }
                                newCell.y_ -= 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }

                                //вылез за границу справа вверху
                            }
                            else if ((tmp.y_ - cellCenter_.y_) > 0.5 * (tmp.x_ - (cellCenter_.x_ + CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                if (gridCoords_.y_ % 2 == 1)
                                {
                                    newCell.x_ += 1;
                                }
                                newCell.y_ += 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                //вылез за границу справа внизу
                            }
                            else if ((tmp.y_ == cellCenter_.y_) && (tmp.x_ > (cellCenter_.x_ + CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                    newCell.x_ += 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                    //вылез за границу строго справа
                            }
                        }
                        else if (tmp.x_ < cellCenter_.x_)
                        {
                            if ((tmp.y_ - cellCenter_.y_) < -0.5 * (tmp.x_ - (cellCenter_.x_ - CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                if (gridCoords_.y_ % 2 == 0)
                                {
                                    newCell.x_ -= 1;
                                }
                                newCell.y_ -= 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                //вылез за границу слева внизу
                            }
                            else if ((tmp.y_ - cellCenter_.y_) > 0.5 * (tmp.x_ - (cellCenter_.x_ - CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                if (gridCoords_.y_ % 2 == 0)
                                {
                                    newCell.x_ -= 1;
                                }
                                newCell.y_ += 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                //вылез за границу слева вверху
                            }
                            else if ((tmp.y_ == cellCenter_.y_) && (tmp.x_ < (cellCenter_.x_-CellWidth / 2)))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                    newCell.x_ -= 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                    //вылез за границу строго слева
                            }
                        }
                        else if (tmp.x_ == cellCenter_.x_)
                        {

                            if ((tmp.y_ - cellCenter_.y_) > CellHeight / 2)
                            {
                                LinearVector<int> newCell = gridCoords_;
                                    newCell.y_ += 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                //вылез за границу внизу
                            }
                            else if ((tmp.y_ - cellCenter_.y_) < -(CellHeight / 2))
                            {
                                LinearVector<int> newCell = gridCoords_;
                                    newCell.y_ -= 1;

                                if (newCell.y_ < 0 || newCell.x_ < 0) //! TODO: ограничение размера шириной и длиной карты в клетках
                                {
                                    //нельзя! не пущать!
                                }
                                else if ((*map_)[newCell.x_][newCell.y_] == nullptr)
                                {
                                    gridCoords_ = newCell;
                                    refCoords_ = tmp;
                                }
                                //вылез за границу вверху
                            }
                        }

                        refCoords_ = refCoords_ + velocity_;
                   }
            }
        }
};

#endif
