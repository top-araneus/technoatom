#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include <../../../stack/stack/smart_ptr.h>

const SizeOfCell;

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
        unsigned char numOfFrames_;
        unsigned char curFrame_;
        unsigned char numOfState_;
        unsigned char curState_;
        Texture texture_;
        LinearVector<unsigned char> spriteSize_; //!< width and height of sprites is in tile count
        static Unique_ptr<Array<Unique_ptr<GameObject>>> map_;
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
                   {
                        refCoords_ = refCoords_ + velocity_;
                   }
                                                                        //!Нужно много проверок, проверки занятости клетки, проверки выхода за границу клетки
            }
        }
};

#endif
