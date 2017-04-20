#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include <../stack/stack/smart_ptr.h>
#include <../utils/print.h>
using namespace sf;
const int CellWidth = 128;
const int CellHeight = 64;
const int TILES_AT_LINE = 50;
class GameObject
{
    public:
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        virtual void Move() = 0;
        GameObject() { }
        virtual ~GameObject() { }
        unsigned char GetCode()
        {
            return objectCode_;
        }
        void SetFrame(unsigned char frame)
        {
            curFrame_ = frame % numOfFrames_;
        }
    protected:
        LinearVector<int> refCoords_;
        LinearVector<int> cellCenter_;
        LinearVector<int> gridCoords_;
        unsigned char numOfFrames_;
        unsigned char curFrame_;
        unsigned char numOfState_;
        unsigned char curState_;
        unsigned char objectCode_;
        Texture texture_;
        RenderWindow* window_;
        LinearVector<int> spriteSize_; //!< width and height of sprite
        Unique_ptr<Array<Array<Unique_ptr<GameObject>>>> map_;
        Unique_ptr<ReferenceFrame> refFrame_;
        LinearVector<int> GetCoordsFromCell(LinearVector<int> cell)
        {
            print("Frame: /# /# \n", refFrame_->GetX(), refFrame_->GetY());
            LinearVector<int> result;
            result.x_ = cell.x_ * CellWidth / 2 + cell.y_ * CellWidth / 2 + CellWidth / 2;
            result.y_ = TILES_AT_LINE * CellHeight / 2 + cell.x_ * CellHeight / 2 - cell.y_ * CellHeight / 2 + CellHeight / 2;
            print("Lion: /# /# \n", result.x_, result.y_);
            return result;
        }
};

class StaticObject :public GameObject
{
    public:
        StaticObject(LinearVector<int> refCoords)
        {
            refCoords_ = refCoords;
        }
        virtual ~StaticObject() = 0;
        virtual void Draw()= 0;
        virtual void Interact() = 0;
        virtual void Move() = 0;

};

class MovingObject :public GameObject
{
    protected:
        LinearVector<int> velocity_;
        void GoToCellIfEmpty(LinearVector<int> cell, LinearVector<int> coords)
        {
            if ((*map_)[cell.x_][cell.y_] == nullptr)
            {
                gridCoords_ = cell;
                refCoords_ = coords;
            }
        }
        bool InMap(LinearVector<int> newCoords)
        {
            return (!(newCoords.y_ < 0 || newCoords.x_ < 0 || newCoords.y_ >= TILES_AT_LINE || newCoords.x_  >= TILES_AT_LINE));
        }
    public:
        MovingObject(){ }
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
        virtual ~MovingObject() { }
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        virtual void Move()
        {
            if(velocity_ != LinearVector<int>(0,0))
            {
                LinearVector<int> tmp = refCoords_ + velocity_;
                if(tmp.x_ > 0 && tmp.x_ < refFrame_->size_.x_
                && tmp.y_ > 0 && tmp.y_ < refFrame_->size_.y_)
                   {
                        LinearVector<int> newCell = gridCoords_;
                        //!< ������ �������� � ����� ������ �� ������ ������
                        if (tmp.x_ > cellCenter_.x_)
                        {
                            //!< ����� �� ������� ������ ������
                            if ((tmp.y_ - cellCenter_.y_) < -0.5 * (tmp.x_ - (cellCenter_.x_ + CellWidth / 2)))
                            {
                                newCell.y_ += 1;
                                //!< �� �������� �� ���� �����
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            //!< ����� �� ������� ������ �����
                            else if ((tmp.y_ - cellCenter_.y_) > 0.5 * (tmp.x_ - (cellCenter_.x_ + CellWidth / 2)))
                            {
                                newCell.x_ += 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            //!< ����� �� ������� ������ ������
                            else if ((tmp.y_ == cellCenter_.y_) && (tmp.x_ > (cellCenter_.x_ + CellWidth / 2)))
                            {
                                newCell.x_ += 1;
                                newCell.y_ += 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            else
                            {
                                refCoords_ = tmp;
                            }
                        }
                        //!< ������ �������� � ����� ����� �� ������ ������
                        else if (tmp.x_ < cellCenter_.x_)
                        {
                            //!< ����� �� ������� ����� �����
                            if ((tmp.y_ - cellCenter_.y_) < -0.5 * (tmp.x_ - (cellCenter_.x_ - CellWidth / 2)))
                            {
                                newCell.y_ -= 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            //!< ����� �� ������� ����� ������
                            else if ((tmp.y_ - cellCenter_.y_) > 0.5 * (tmp.x_ - (cellCenter_.x_ - CellWidth / 2)))
                            {
                                newCell.x_ -= 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            //!< ����� �� ������� ����� ������
                            else if ((tmp.y_ == cellCenter_.y_) && (tmp.x_ < (cellCenter_.x_-CellWidth / 2)))
                            {
                                newCell.x_ -= 1;
                                newCell.y_ -= 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            else
                            {
                                refCoords_ = tmp;
                            }
                        }
                        //!< ������ �������� ����� ��� ���� �� ������ ������
                        else if (tmp.x_ == cellCenter_.x_)
                        {
                            //!< ����� �� ������� �����
                            if ((tmp.y_ - cellCenter_.y_) > CellHeight / 2)
                            {
                                newCell.x_ += 1;
                                newCell.y_ -= 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            //!< ����� �� ������� ������
                            else if ((tmp.y_ - cellCenter_.y_) < -(CellHeight / 2))
                            {
                                newCell.x_ -= 1;
                                newCell.y_ += 1;
                                if (InMap(newCell))
                                {
                                    GoToCellIfEmpty(newCell, tmp);
                                }
                            }
                            else
                            {
                                refCoords_ = tmp;
                            }
                        }
                   }
            }
        }

};

class Immortal: public MovingObject
{
    public:
    virtual void Draw() = 0;
    virtual void Interact() = 0;
    virtual void Move();
    Immortal();
    virtual ~Immortal();
};


//!< TODO: ammo actions
class Ammo: public Immortal
{
    public:
    virtual void Draw();
    virtual void Interact();
    virtual void Move();
    Ammo();
    ~Ammo();
};

//!<TODO: citizen features and inventory
class Citizen: public Immortal
{
    public:
    virtual void Draw();
    virtual void Interact();
    virtual void Move();
    Citizen();
    ~Citizen();
};

//!<TODO: merchant features and inventory
class Merchant: public Immortal
{
    public:
    virtual void Draw();
    virtual void Interact();
    virtual void Move();
    Merchant();
    ~Merchant();
};


class Mortal: public MovingObject
{
    public:
        virtual void Draw()=0;
        virtual void Interact()=0;
        virtual void Move()=0;
        Mortal() { }
        virtual ~Mortal()=0;
        void ChangeHp(int diff)
        {
            hp_ += diff;
            if (!(CheckAlive()))
            {
                delete this;
            }
        }
    protected:
        int hp_;
        int cooldown_; //!< cooldown will be in milliseconds
        bool CheckAlive()
        {
            return (hp_ > 0);
        }
};

Mortal::~Mortal() { }

class Player: public Mortal
{
    public:
        void Draw()
        {
            Sprite playerSprite;
            playerSprite.setTexture(texture_);
            playerSprite.setTextureRect(IntRect(curFrame_ * spriteSize_.x_, curState_ * spriteSize_.y_,
                                                (curFrame_ + 1) * spriteSize_.x_, (curState_ + 1) * spriteSize_.y_));
            playerSprite.setOrigin(Vector2f(spriteSize_.x_ / 2, spriteSize_.y_ - CellHeight / 2));
            playerSprite.setPosition(refFrame_->GetX() + refCoords_.x_, refFrame_->GetY() + refCoords_.y_);
            //curState_ = (curState_+1)%numOfState_;
            window_->draw(playerSprite);
        }
        void Interact() { }
        void Move() { }
        Player();
        Player(RenderWindow* window, LinearVector<int> spriteSize, Texture& texture, LinearVector<int> gridCoords, ReferenceFrame* refFrame)
        {
            window_ = window;
            refFrame_ = refFrame;
            spriteSize_ = spriteSize;
            texture_ = texture;
            gridCoords_ = gridCoords;
            refCoords_ = GetCoordsFromCell(gridCoords);
            cellCenter_ = refCoords_;
            numOfFrames_ = 1;
            curFrame_ = 0;
            numOfState_ = 1;
            curState_ = 0;
            objectCode_ = 0;
        }
        Player(RenderWindow* window, LinearVector<int> spriteSize, Texture& texture, LinearVector<int> gridCoords, ReferenceFrame* refFrame, int numOfFrames, int numOfStates)
        {
            window_ = window;
            refFrame_ = refFrame;
            spriteSize_ = spriteSize;
            texture_ = texture;
            gridCoords_ = gridCoords;
            refCoords_ = GetCoordsFromCell(gridCoords);
            cellCenter_ = refCoords_;
            numOfFrames_ = numOfFrames;
            curFrame_ = 0;
            numOfState_ = numOfStates;
            curState_ = 0;
            objectCode_ = 0;
        }
        ~Player() { }
};
#endif
