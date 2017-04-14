#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include <../../../stack/stack/smart_ptr.h>
class GameObject
{
    public:
        virtual void Draw() = 0;
        virtual void Interact() = 0;
    private:
        LinearVector<int> refCoords_;
        LinearVector<double> velocity_;
        unsigned char numOfFrames_;
        unsigned char curFrame_;
        unsigned char numOfState_;
        unsigned char curState_;
        Texture texture_;
        LinearVector<unsigned char> spriteSize_; //!< width and height of sprites is in tile count
        static Unique_ptr<Array<Unique_ptr<GameObject>>> map_;
};


#endif
