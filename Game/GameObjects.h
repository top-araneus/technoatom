#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include "transformation.h"
#include <../stack/stack/smart_ptr.h>
#include <../utils/print.h>

using namespace sf;

class GameObject
{
  public:
    virtual void Draw() = 0;
    virtual void Interact() = 0;
    virtual void Move();
    GameObject() { }
    GameObject(LinearVector<int> refCoords)
    {
      ref_coords_ = refCoords;
      velocity_ = LinearVector<int>(0,0);
    }
    GameObject(LinearVector<int> refCoords, LinearVector<int> velocity)
    {
      ref_coords_ = refCoords;
      velocity_ = velocity;
    }
    virtual ~GameObject() { }
    void              SetFrame(unsigned char frame) {
      current_frame_ = frame % num_of_frames_;
    }
    unsigned char     GetFrame() {
      return current_frame_;
    }
    void              SetState(unsigned char state) {
      current_state_ = state;
    }
    unsigned char     GetState() {
      return current_state_;
    }
    unsigned char     GetNumOfFrames() {
      return num_of_frames_;
    }
    void              SetDamageEndingTime(time_t time) {
      damage_ending_time_ = time;
    }
    time_t            GetDamageEndingTime() {
      return damage_ending_time_;
    }
    void              SetAttackEndingTime(time_t time) {
      attack_ending_time_ = time;
    }
    time_t            GetAttackEndingTime() {
      return attack_ending_time_;
    }
    void              SetAimOfInteract(GameObject* aim) {
      aim_of_interact_ = aim;
    }
    GameObject*       GetAimOfInteract() {
      return aim_of_interact_;
    }
    LinearVector<int> GetGridCoords() {
      return grid_coords_;
    }
    LinearVector<int> GetRefCoords() {
      return ref_coords_;
    }
    unsigned char     GetObjectCode() {
      return object_code_;
    }
    void              SetInAttack(bool value) {
      in_attack_ = value;
    }
    bool              GetInAttack() {
      return in_attack_;
    }
    void              SetUnderAttack(bool value) {
      under_attack_ = value;
    }
    bool              GetUnderAttack() {
      return under_attack_;
    }
    void              SetVelocity(LinearVector<int> velocity) {
      velocity_ = velocity;
    }
    LinearVector<int> GetVelocity() {
      return velocity_;
    }
    virtual void NextFrame(char step = 1);
    void DecreaseHp(int damage);

  protected:
    bool CheckAlive()
    {
      return (hp_ > 0);
    }
    LinearVector<char> GiveDirection();
    void GoToCellIfEmpty(LinearVector<int> oldCell, LinearVector<int> cell, LinearVector<int> coords);
    bool InMap(LinearVector<int> new_coords)
    {
      return (new_coords.x_ >= 0 && new_coords.x_ < kTilesAtLine && new_coords.y_ >= 0 && new_coords.y_ < kTilesAtLine);
    }
    int hp_;
    int cooldown_; //!< cooldown will be in milliseconds
    LinearVector<int> velocity_; //set
    LinearVector<int> ref_coords_;  //get
    LinearVector<int> grid_coords_; //get
    LinearVector<char> direction_;
    unsigned char num_of_frames_; //get
    unsigned char current_frame_; //set, get
    unsigned char num_of_state_;
    unsigned char current_state_; //set, get
    unsigned char object_code_; //get
    unsigned char frames_per_second_;
    time_t time_last_frame_changing_;
    int applied_damage_;
    time_t attack_ending_time_ = 0; //get, set
    time_t damage_ending_time_ = 0; //get, set
    bool in_attack_ = false; //get, set
    bool under_attack_ = false; //get, set
    Texture texture_;
    RenderWindow* window_;
    LinearVector<int> sprite_size_; //!< width and height of sprite
    Array<Array<GameObject*>>* map_; //! TODO: weak_ptr
    Unique_ptr<ReferenceFrame> ref_frame_;
    GameObject* aim_of_interact_; //set, get

};

typedef Array<Array<GameObject*>> SurfaceType;

LinearVector<char> GameObject::GiveDirection()
{
  return LinearVector<char>(1,-1);
}

void GameObject::DecreaseHp(int damage)
{
  hp_ -= damage;
  if (!(CheckAlive()))
  {
    delete this;
  }
}

void GameObject::Move()
{
  if(velocity_ != LinearVector<int>(0,0))
  {
    LinearVector<int> tmp;
    tmp.x_ = ref_coords_.x_ + velocity_.x_;
    tmp.y_ = ref_coords_.y_ + velocity_.y_;
    LinearVector<int> newCell = GetCellFromCoords(tmp);
    LinearVector<int> oldCell = grid_coords_;
    if(InMap(newCell))
    {
      GoToCellIfEmpty(oldCell, newCell, tmp);
    }
  }
}

void GameObject::NextFrame(char step)
{
  if ((clock() - time_last_frame_changing_) >= CLOCKS_PER_SEC / frames_per_second_)
  {
    time_last_frame_changing_ = clock();
    unsigned char new_frame = (GetFrame() + step) % GetNumOfFrames();
    SetFrame(new_frame);
  }
}

void GameObject::GoToCellIfEmpty(LinearVector<int> oldCell, LinearVector<int> cell, LinearVector<int> coords)
{
  if ((oldCell != cell))
  {
    if ((*map_)[cell.x_][cell.y_] == nullptr)
    {
      grid_coords_ = cell;
      ref_coords_ = coords;
      (*map_)[cell.x_][cell.y_] = this;
      (*map_)[oldCell.x_][oldCell.y_] = nullptr;
    }
  }
  else
  {
    ref_coords_ = coords;
  }
}

class Player: public GameObject
{
  public:
    void Draw()
    {
      Sprite player_sprite;
      player_sprite.setTexture(texture_);
      player_sprite.setTextureRect(IntRect(current_frame_ * sprite_size_.x_, current_state_ * sprite_size_.y_,
                                          sprite_size_.x_, sprite_size_.y_));
      player_sprite.setOrigin(Vector2f(sprite_size_.x_ / 2, sprite_size_.y_ - kCellHeight / 2));
      player_sprite.setPosition(ref_frame_->GetX() + ref_coords_.x_, ref_frame_->GetY() + ref_coords_.y_);
      if (GetUnderAttack())
        player_sprite.setColor(sf::Color(255,128,128));
      else
        player_sprite.setColor(sf::Color(255,255,255));
      DrawHp();
      window_->draw(player_sprite);
    }
    void Interact()
    {
      if (aim_of_interact_ != nullptr)
      {
        if (aim_of_interact_->GetObjectCode() == kEnemyId)
        {
          if ((abs(aim_of_interact_->GetGridCoords().x_ - GetGridCoords().x_) <= 1)
            && (abs(aim_of_interact_->GetGridCoords().y_ - GetGridCoords().y_) <= 1))
          {
            if (clock() >= attack_ending_time_)
            {
              attack_ending_time_ = clock() + kPlayerCoolDown;
              aim_of_interact_->DecreaseHp(applied_damage_);
              aim_of_interact_->SetUnderAttack(true);
              aim_of_interact_->SetDamageEndingTime(clock() + kPlayerCoolDown);
            print("attacked: /# /#\n", aim_of_interact_->GetGridCoords().x_, aim_of_interact_->GetGridCoords().y_);
            }
            print("not time to attack: /# /#\n", aim_of_interact_->GetGridCoords().x_, aim_of_interact_->GetGridCoords().y_);
          }
          else
          {
            print("too far: /# /#\n", aim_of_interact_->GetGridCoords().x_, aim_of_interact_->GetGridCoords().y_);
          }
        }
      }
    }

    void Move()
    {
      GameObject::Move();
    }

    virtual void NextFrame(char step = 1)
    {
      if(next_sprite_right){
        if(GetFrame() == GetNumOfFrames()-1){
          next_sprite_right = false;
          GameObject::NextFrame(-1);
        }
        else{
          GameObject::NextFrame(1);
        }
      }
      else {
        if(GetFrame() == 0){
          next_sprite_right = true;
          GameObject::NextFrame(1);
        }
        else{
          GameObject::NextFrame(-1);
        }
      }

    }

    void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }
    void DrawHp()
    {
      std::string hp = std::to_string(hp_);
      sf::Font font;
      font.loadFromFile("fonts/font.ttf");

      sf::Text hp_text(hp, font);
      hp_text.setCharacterSize(40);
      hp_text.setColor(sf::Color::Green);
      hp_text.setPosition(kWindowWidth - 120, 10);
      window_->draw(hp_text);
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
      num_of_frames_ = 1;
      current_frame_ = 0;
      num_of_state_ = 1;
      current_state_ = 0;
      applied_damage_ = 5;
      map_ = pMap;
      velocity_ = LinearVector<int>(0,0);
      direction_ = GiveDirection();
      aim_of_interact_ = nullptr;
      hp_ = 1000;
      object_code_ = kPlayerId;
      time_last_frame_changing_ = clock();
      frames_per_second_ = kFramesPerSec;
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
      num_of_frames_ = numOfFrames;
      current_frame_ = 0;
      num_of_state_ = numOfStates;
      current_state_ = 0;
      applied_damage_ = 5;
      map_ = pMap;
      velocity_ = LinearVector<int>(0,0);
      direction_ = GiveDirection();
      aim_of_interact_ = nullptr;
      hp_ = kPlayerHp;
      object_code_ = kPlayerId;
      time_last_frame_changing_ = clock();
      frames_per_second_ = kFramesPerSec;
    }
    ~Player() {

       for(int i = 0; i < kTilesAtLine; i++)
       {
         for(int j = 0; j < kTilesAtLine; j++)
         {
         if((*map_)[i][j])
         {
           if((*map_)[i][j]->GetObjectCode() == kEnemyId)
           {
           (*map_)[i][j]->SetAimOfInteract(nullptr);
           }
         }
         }
       }
       (*map_)[grid_coords_.x_][grid_coords_.y_] = nullptr;
       in_death = true;
   }
  private:
    bool next_sprite_right = true;
};


class Enemy: public GameObject
{
  public:
    void Draw()
    {
      Sprite enemy_sprite;
      enemy_sprite.setTexture(texture_);
      enemy_sprite.setTextureRect(IntRect(current_frame_ * sprite_size_.x_, current_state_ * sprite_size_.y_,
                        sprite_size_.x_, sprite_size_.y_));
      enemy_sprite.setOrigin(Vector2f(sprite_size_.x_ / 2, sprite_size_.y_ - kCellHeight / 2));
      enemy_sprite.setPosition(ref_frame_->GetX() + ref_coords_.x_, ref_frame_->GetY() + ref_coords_.y_);
      if (GetUnderAttack())
        enemy_sprite.setColor(sf::Color(255,64,64));
      else
        enemy_sprite.setColor(sf::Color(255,255,255));
      window_->draw(enemy_sprite);
    }
    void Interact()
    {
      if (!aim_of_interact_)
      {
        Scan();
      }
      if (aim_of_interact_ != nullptr)
      {
        if ((abs(aim_of_interact_->GetGridCoords().x_ - GetGridCoords().x_) <= 1)
        && (abs(aim_of_interact_->GetGridCoords().y_ - GetGridCoords().y_) <= 1))
        {
          velocity_ = LinearVector<int>(0,0);
          if (clock() >= attack_ending_time_)
          {
            print("attacked: /# /#\n", aim_of_interact_->GetGridCoords().x_, aim_of_interact_->GetGridCoords().y_);
            attack_ending_time_ = clock() + kEnemyCoolDown;
            aim_of_interact_->SetUnderAttack(true);
            aim_of_interact_->SetDamageEndingTime(clock() + kEnemyCoolDown);
            aim_of_interact_->DecreaseHp(applied_damage_);
          }
        }
        else
        {
         double abs = Pythagor(aim_of_interact_->GetRefCoords().x_ - ref_coords_.x_, aim_of_interact_->GetRefCoords().y_ - ref_coords_.y_);
         LinearVector<double> tmp(kPlayerVelocity*(aim_of_interact_->GetRefCoords().x_ - ref_coords_.x_) / abs, kPlayerVelocity*(aim_of_interact_->GetRefCoords().y_ - ref_coords_.y_) / abs);
         velocity_.x_ = round(tmp.x_);
         velocity_.y_ = round(tmp.y_);
        }
      }
    }
    void CheckCellAndSetAim(LinearVector<int> coords)
    {
      if(coords.x_ >= 0 && coords.x_ < kTilesAtLine && coords.y_ >= 0 && coords.y_ < kTilesAtLine)
      {
        if((*map_)[coords.x_][coords.y_] != nullptr)
        {
          if((*map_)[coords.x_][coords.y_]->GetObjectCode() == kPlayerId)
          {
            aim_of_interact_ = (*map_)[coords.x_][coords.y_];
          }
        }
      }
    }
    void Scan()
    {
      for(int i = -kRangeOfVision; i <= kRangeOfVision; i++)
      {
        for(int j = -kRangeOfVision; j <= kRangeOfVision; j++)
        {
          if(i != 0 || j != 0)
          {
            CheckCellAndSetAim(LinearVector<int>(grid_coords_.x_ + i, grid_coords_.y_ + j));
          }
        }
      }
    }

    void Move()
    {
      GameObject::Move();
    }

    void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }

    Enemy();
    Enemy(RenderWindow* window, SurfaceType* pMap, LinearVector<int> spriteSize, Texture& texture,
         LinearVector<int> gridCoords, ReferenceFrame* refFrame)
    {
      window_ = window;
      ref_frame_ = refFrame;
      sprite_size_ = spriteSize;
      texture_ = texture;
      grid_coords_ = gridCoords;
      ref_coords_ = GetCoordsFromCell(gridCoords);
      num_of_frames_ = 1;
      current_frame_ = 0;
      num_of_state_ = 1;
      current_state_ = 0;
      applied_damage_ = 5;
      map_ = pMap;
      velocity_ = LinearVector<int>(0,0);
      direction_ = GiveDirection();
      hp_ = kEnemyHp;
      object_code_ = kEnemyId;
      aim_of_interact_ = nullptr;
      time_last_frame_changing_ = clock();
      frames_per_second_ = kFramesPerSec;
    }
    Enemy(RenderWindow* window, SurfaceType* pMap, LinearVector<int> spriteSize, Texture& texture,
         LinearVector<int> gridCoords, ReferenceFrame* refFrame, int numOfFrames, int numOfStates)
    {
      window_ = window;
      ref_frame_ = refFrame;
      sprite_size_ = spriteSize;
      texture_ = texture;
      grid_coords_ = gridCoords;
      ref_coords_ = GetCoordsFromCell(gridCoords);
      num_of_frames_ = numOfFrames;
      current_frame_ = 0;
      num_of_state_ = numOfStates;
      current_state_ = 0;
      applied_damage_ = 5;
      map_ = pMap;
      velocity_ = LinearVector<int>(0,0);
      direction_ = GiveDirection();
      hp_ = 15;
      object_code_ = kEnemyId;
      aim_of_interact_ = nullptr;
      time_last_frame_changing_ = clock();
      frames_per_second_ = kFramesPerSec;
    }
    ~Enemy() {
      (*map_)[grid_coords_.x_][grid_coords_.y_] = nullptr;
      aim_of_interact_ = nullptr;
   }

   virtual void NextFrame(char step = 1)
   {
     GameObject::NextFrame(step);
   }
};
#endif
