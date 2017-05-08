#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include "Transformation.h"
#include <../stack/stack/smart_ptr.h>
#include <../utils/print.h>

using namespace sf;

class GameObject
{
    public:
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        virtual void Move() = 0;
        virtual void DecreaseHp(int diff)=0;
        GameObject() { }
        virtual ~GameObject() { }
        unsigned char GetCode()
        {
            return object_code_;
        }
        void SetFrame(unsigned char frame)
        {
            current_frame_ = frame % num_of_frames_;
        }
        void SetState(unsigned char state)
        {
            current_state_ = state;
        }
        void SetDamageEndingTime(time_t time)
        {
            damage_ending_time_ = time;
        }
        void SetAttackEndingTime(time_t time)
        {
            attack_ending_time_ = time;
        }
        void SetAimOfInteract(GameObject* aim)
        {
            aim_of_interact_ = aim;
        }
        GameObject* GetAimOfInteract()
        {
            return aim_of_interact_;
        }
        time_t GetDamageEndingTime()
        {
            return damage_ending_time_;
        }
        time_t GetAttackEndingTime()
        {
            return attack_ending_time_;
        }
        LinearVector<int> GetGridCoords()
        {
            return grid_coords_;
        }
        int GetObjectCode()
        {
            return object_code_;
        }
        void SetInAttack(bool value)
        {
            in_attack_ = value;
        }
        void SetUnderAttack(bool value)
        {
            under_attack_ = value;
        }
        bool GetInAttack()
        {
            return in_attack_;
        }
        bool GetUnderAttack()
        {
            return under_attack_;
        }
    protected:
        LinearVector<char> GiveDirection();
        LinearVector<int> ref_coords_;
        LinearVector<int> cell_center_;
        LinearVector<int> grid_coords_; //get
        LinearVector<char> direction_;
        unsigned char num_of_frames_;
        unsigned char current_frame_; //set
        unsigned char num_of_state_;
        unsigned char current_state_; //set
        unsigned char object_code_; //get
        int applied_damage_;
        time_t attack_ending_time_ = 0; //get, set
        time_t damage_ending_time_ = 0; //get, set
        bool in_attack_ = false; //get, set
        bool under_attack_ = false; //get, set
        const time_t kCoolDown = 250;
        const int kEnemyId = 1488;
        Texture texture_;
        RenderWindow* window_;
        LinearVector<int> sprite_size_; //!< width and height of sprite
        Array<Array<GameObject*>>* map_; //! TODO: weak_ptr
        Unique_ptr<ReferenceFrame> ref_frame_;
        GameObject* aim_of_interact_; //set, get

};

LinearVector<char> GameObject::GiveDirection()
{
    return LinearVector<char>(1,-1);
}

typedef Array<Array<GameObject*>> SurfaceType;
SurfaceType InitializeMap()
{
    //Unique_ptr<SurfaceType> mapArray = new SurfaceType(kTilesAtLine);
    SurfaceType mapArray(kTilesAtLine);
    for (int i=0; i<kTilesAtLine; ++i)
    {
        mapArray[i] = Array<GameObject*>(kTilesAtLine);
        for (int j=0; j<kTilesAtLine; ++j)
        {
            mapArray[i][j] = nullptr;
        }
    }
    return mapArray;
}

class StaticObject :public GameObject
{
    public:
        StaticObject(LinearVector<int> refCoords)
        {
            ref_coords_ = refCoords;
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
        void GoToCellIfEmpty(LinearVector<int> oldCell, LinearVector<int> cell, LinearVector<int> coords)
        {
            if ((oldCell != cell) && InMap(cell))
            {
                if ((*map_)[cell.x_][cell.y_] == nullptr)
                {
                    grid_coords_ = cell;
                    ref_coords_ = coords;
                    cell_center_ = GetCoordsFromCell(grid_coords_);
                    (*map_)[cell.x_][cell.y_] = this;
                    (*map_)[oldCell.x_][oldCell.y_] = nullptr;
                }
            }
            else
            {
                ref_coords_ = coords;
            }
        }
        bool InMap(LinearVector<int> newCoords)
        {
            return (!(newCoords.y_ < 0 || newCoords.x_ < 0 || newCoords.y_ >= kTilesAtLine || newCoords.x_  >= kTilesAtLine));
        }
    public:
        MovingObject(){ }
        MovingObject(LinearVector<int> refCoords)
        {
            ref_coords_ = refCoords;
            velocity_ = LinearVector<int>(0,0);
        }
        MovingObject(LinearVector<int> refCoords, LinearVector<int> velocity)
        {
            ref_coords_ = refCoords;
            velocity_ = velocity;
        }
        void SetVelocity(LinearVector<int> velocity)
        {
            velocity_ = velocity;
        }
        virtual ~MovingObject() { }
        virtual void Draw() = 0;
        virtual void Interact() = 0;
        virtual void Move()
        {
            if(velocity_ != LinearVector<int>(0,0))
            {
                LinearVector<int> tmp;
                tmp.x_ = ref_coords_.x_ + velocity_.x_;
                tmp.y_ = ref_coords_.y_ + velocity_.y_;
               // print("refcoords: /# /# \n", ref_coords_.x_, ref_coords_.y_);
                //print("gridcoords: /# /# \n", grid_coords_.x_, grid_coords_.y_);
                LinearVector<int> newCell = GetCellFromCoords(tmp);
                LinearVector<int> oldCell = grid_coords_;
                GoToCellIfEmpty(oldCell, newCell, tmp);
                //print("New cell: /# /# \n", newCell.x_, newCell.y_);
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
        void DecreaseHp(int damage)
        {
            hp_ -= damage;
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
        //using MovingObject::Move;
        void Draw()
        {
            Sprite playerSprite;
            playerSprite.setTexture(texture_);
            playerSprite.setTextureRect(IntRect(current_frame_ * sprite_size_.x_, current_state_ * sprite_size_.y_,
                                                sprite_size_.x_, sprite_size_.y_));
            playerSprite.setOrigin(Vector2f(sprite_size_.x_ / 2, sprite_size_.y_ - kCellHeight / 2));
            playerSprite.setPosition(ref_frame_->GetX() + ref_coords_.x_, ref_frame_->GetY() + ref_coords_.y_);
            //current_state_ = (current_state_+1)%num_of_state_;
            window_->draw(playerSprite);
        }
        void Interact()
        {
            if (aim_of_interact_ != nullptr)
            {
                if (aim_of_interact_->GetObjectCode() == kEnemyId)
                {
                    if (clock() >= attack_ending_time_)
                    {
                        attack_ending_time_ = clock() + kCoolDown;
                        aim_of_interact_->DecreaseHp(applied_damage_);
                        aim_of_interact_->SetUnderAttack(true);
                        aim_of_interact_->SetDamageEndingTime(clock() + kCoolDown);
                    }
                }
            }
        }

        void Move()
        {
            MovingObject::Move();
        }

        void DecreaseHp(int damage)
        {
            Mortal::DecreaseHp(damage);
        }

        Player();
        Player(RenderWindow* window, SurfaceType* pMap, LinearVector<int> spriteSize, Texture& texture,
               LinearVector<int> gridCoords, ReferenceFrame* refFrame)
        {
            window_ = window;
            ref_frame_ = refFrame;
            sprite_size_ = spriteSize;
            texture_ = texture;
            grid_coords_ = gridCoords;
            ref_coords_ = GetCoordsFromCell(gridCoords);
            cell_center_ = ref_coords_;
            num_of_frames_ = 1;
            current_frame_ = 0;
            num_of_state_ = 1;
            current_state_ = 0;
            object_code_ = 0;
            applied_damage_ = 5;
            map_ = pMap;
            velocity_ = LinearVector<int>(0,0);
            direction_ = GiveDirection();
            aim_of_interact_ = nullptr;
        }
        Player(RenderWindow* window, SurfaceType* pMap, LinearVector<int> spriteSize, Texture& texture,
               LinearVector<int> gridCoords, ReferenceFrame* refFrame, int numOfFrames, int numOfStates)
        {
            window_ = window;
            ref_frame_ = refFrame;
            sprite_size_ = spriteSize;
            texture_ = texture;
            grid_coords_ = gridCoords;
            ref_coords_ = GetCoordsFromCell(gridCoords);
            cell_center_ = ref_coords_;
            num_of_frames_ = numOfFrames;
            current_frame_ = 0;
            num_of_state_ = numOfStates;
            current_state_ = 0;
            object_code_ = 0;
            applied_damage_ = 5;
            map_ = pMap;
            velocity_ = LinearVector<int>(0,0);
            direction_ = GiveDirection();
            aim_of_interact_ = nullptr;
        }
        ~Player() {
            (*map_)[grid_coords_.x_][grid_coords_.y_] = nullptr;
            aim_of_interact_ = nullptr;
     }
};
#endif
