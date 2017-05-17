#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
#include "refpoint.h"
#include "transformation.h"
#include <../stack/stack/smart_ptr.h>
#include <../utils/print.h>
#include "../ALU/ALU/alu.h"
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
      velocity_ = LinearVector<double>(0,0);
    }
    GameObject(LinearVector<int> refCoords, LinearVector<double> velocity)
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
    void              SetVelocity(LinearVector<double> velocity) {
      velocity_ = velocity;
    }
    bool CheckAlive() {
      return (hp_ > 0);
    }
    virtual void NextFrame(char step = 1);
    void DecreaseHp(int damage);
    bool CheckCellsNear(LinearVector<int> where_to, bool is_right);

  protected:
    LinearVector<char> GiveDirection();
    void GoToCellIfEmpty(LinearVector<int> oldCell, LinearVector<int> cell, LinearVector<int> coords);
    bool InMap(LinearVector<int> new_coords)
    {
      return (new_coords.x_ >= 0 && new_coords.x_ < kTilesAtLine && new_coords.y_ >= 0 && new_coords.y_ < kTilesAtLine);
    }
    int hp_;
    int cooldown_; //!< cooldown will be in milliseconds
    LinearVector<double> velocity_; //set
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
    ReferenceFrame* ref_frame_;
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
}

bool GameObject::CheckCellsNear(LinearVector<int> where_to, bool is_right)
{
    LinearVector<double> right_ort = LinearVector<double>(1,0);
    LinearVector<double> left_ort = LinearVector<double>(-1,0);
    if (is_right) {
        where_to.x_ = roundl(ref_coords_.x_ + velocity_.x_ + 0.5 * sprite_size_.x_ * right_ort.x_);
        where_to.y_ = roundl(ref_coords_.y_ + velocity_.y_);
    }
    else {
      where_to.x_ = roundl(ref_coords_.x_ + velocity_.x_ + 0.5 * sprite_size_.x_ * left_ort.x_);
      where_to.y_ = roundl(ref_coords_.y_ + velocity_.y_);
    }
    LinearVector<int> new_cell = GetCellFromCoords(where_to);
    if(InMap(new_cell))
    {
      if((*map_)[new_cell.x_][new_cell.y_] != this && (*map_)[new_cell.x_][new_cell.y_] != nullptr)
      {
        return false;
      }
      else
      {
        return true;
      }
    }

}

void GameObject::Move()
{
  if(velocity_ != LinearVector<double>(0,0))
  {
    //LinearVector<double> ort = LinearVector<double>(1,0);
    LinearVector<int> where_to;
    where_to.x_ = roundl(ref_coords_.x_ + velocity_.x_/* + 0.5 * sprite_size_.x_ * ort.x_*/);
    where_to.y_ = roundl(ref_coords_.y_ + velocity_.y_);
    LinearVector<int> new_cell = GetCellFromCoords(where_to);
    if (CheckCellsNear(where_to, true) && CheckCellsNear(where_to, false) )
    {
        new_cell = GetCellFromCoords(where_to);
        LinearVector<int> old_cell = grid_coords_;
        if(InMap(new_cell))
        {
          GoToCellIfEmpty(old_cell, new_cell, where_to);
        }
    }
   /* if(InMap(new_cell))
      {
      if((*map_)[new_cell.x_][new_cell.y_] == nullptr)
      {
        where_to.x_ = roundl(ref_coords_.x_ + velocity_.x_);
        where_to.y_ = roundl(ref_coords_.y_ + velocity_.y_);
        new_cell = GetCellFromCoords(where_to);
        LinearVector<int> old_cell = grid_coords_;
      }
      else if (((*map_)[new_cell.x_][new_cell.y_]->GetObjectCode()) == kPlayerCode)
      {
        where_to.x_ = roundl(ref_coords_.x_ + velocity_.x_);
        where_to.y_ = roundl(ref_coords_.y_ + velocity_.y_);
        new_cell = GetCellFromCoords(where_to);
        LinearVector<int> old_cell = grid_coords_;
        GoToCellIfEmpty(old_cell, new_cell, where_to);
      }

      if(InMap(new_cell))
      {
        GoToCellIfEmpty(old_cell, new_cell, where_to);
      }
    }*/



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

void GameObject::GoToCellIfEmpty(LinearVector<int> old_cell, LinearVector<int> cell, LinearVector<int> coords)
{
  if ((old_cell != cell))
  {
    if ((*map_)[cell.x_][cell.y_] == nullptr)
    {
      grid_coords_ = cell;
      ref_coords_ = coords;
      (*map_)[cell.x_][cell.y_] = this;
      (*map_)[old_cell.x_][old_cell.y_] = nullptr;
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
    Player(RenderWindow& window, SurfaceType& pMap, const LinearVector<int> spriteSize, Texture& texture,
      LinearVector<int> gridCoords, ReferenceFrame& refFrame, const int numOfFrames, const int numOfStates);
    ~Player();
    virtual void Draw();
    virtual void Interact();
    virtual void NextFrame(char step = 1);
    void DrawHp();
    virtual void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }
    virtual void Move()
    {
      GameObject::Move();
    }

  private:
    bool next_sprite_right = true;
};

Player::Player(RenderWindow& window, SurfaceType& pMap, const LinearVector<int> spriteSize, Texture& texture,
          LinearVector<int> gridCoords, ReferenceFrame& refFrame, const int numOfFrames, const int numOfStates)
{
  window_ = &window;
  ref_frame_ = &refFrame;
  sprite_size_ = spriteSize;
  texture_ = texture;
  grid_coords_ = gridCoords;
  ref_coords_ = GetCoordsFromCell(gridCoords);
  num_of_frames_ = numOfFrames;
  current_frame_ = 0;
  num_of_state_ = numOfStates;
  current_state_ = 0;
  applied_damage_ = 5;
  map_ = &pMap;
  velocity_ = LinearVector<double>(0,0);
  direction_ = GiveDirection();
  aim_of_interact_ = nullptr;
  hp_ = kPlayerHp;
  object_code_ = kPlayerCode;
  time_last_frame_changing_ = clock();
  frames_per_second_ = kFramesPerSec;
}

Player::~Player()
{
   for(int i = 0; i < kTilesAtLine; i++)
   {
     for(int j = 0; j < kTilesAtLine; j++)
     {
     if((*map_)[i][j])
     {
       if((*map_)[i][j]->GetObjectCode() == kEnemyCode)
       {
       (*map_)[i][j]->SetAimOfInteract(nullptr);
       }
     }
     }
   }
   (*map_)[grid_coords_.x_][grid_coords_.y_] = nullptr;
   in_death = true;
}

void Player::Draw()
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

void Player::Interact()
{
  if (aim_of_interact_ != nullptr)
  {
    if (aim_of_interact_->GetObjectCode() == kEnemyCode)
    {
      if (aim_of_interact_->GetGridCoords().GetDistance(GetGridCoords()) <= kRangeOfPlayerAttack)
      {
        if (clock() >= attack_ending_time_)
        {
          attack_ending_time_ = clock() + kPlayerCoolDown;
          aim_of_interact_->DecreaseHp(applied_damage_);
          aim_of_interact_->SetUnderAttack(true);
          aim_of_interact_->SetDamageEndingTime(clock() + kPlayerCoolDown);
        }
      }
    }
  }
}

void Player::NextFrame(char step)
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

void Player::DrawHp()
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


class Enemy: public GameObject
{
  public:
    Enemy(RenderWindow& window, SurfaceType& pMap, LinearVector<int> spriteSize, Texture& texture,
         LinearVector<int> gridCoords, ReferenceFrame& refFrame, int numOfFrames, int numOfStates);
    ~Enemy();
    virtual void Draw();
    virtual void Interact();
    void CheckCellAndSetAim(LinearVector<int> coords);
    void Scan();
    void HandleALU();
    virtual void Move()
    {
      GameObject::Move();
    }
    virtual void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }
    virtual void NextFrame(char step = 1)
    {
      GameObject::NextFrame(step);
    }
  protected:
    ALU* alu_;
};

Enemy::Enemy(RenderWindow& window, SurfaceType& pMap, LinearVector<int> spriteSize, Texture& texture,
     LinearVector<int> gridCoords, ReferenceFrame& refFrame, int numOfFrames, int numOfStates)
{
  window_ = &window;
  ref_frame_ = &refFrame;
  sprite_size_ = spriteSize;
  texture_ = texture;
  grid_coords_ = gridCoords;
  ref_coords_ = GetCoordsFromCell(gridCoords);
  num_of_frames_ = numOfFrames;
  current_frame_ = 0;
  num_of_state_ = numOfStates;
  current_state_ = 0;
  applied_damage_ = kEnemyDamage;
  map_ = &pMap;
  velocity_ = LinearVector<double>(0,0);
  direction_ = GiveDirection();
  hp_ = kEnemyHp;
  object_code_ = kEnemyCode;
  aim_of_interact_ = nullptr;
  time_last_frame_changing_ = clock();
  frames_per_second_ = kFramesPerSec;
  alu_ = new ALU(kEnemyProgram);
}

Enemy::~Enemy()
{
  (*map_)[grid_coords_.x_][grid_coords_.y_] = nullptr;
  aim_of_interact_ = nullptr;
  delete alu_;
}

void Enemy::Draw()
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

void Enemy::Interact()
{
  if (aim_of_interact_ == nullptr)
  {
    Scan();
  }
  if (aim_of_interact_ != nullptr)
  {
    if (aim_of_interact_->GetGridCoords().GetDistance(GetGridCoords()) <= kRangeOfEnemyAttack)
    {
      velocity_ = LinearVector<double>(0,0);
      if (clock() >= attack_ending_time_)
      {
        attack_ending_time_ = clock() + kEnemyCoolDown;
        aim_of_interact_->SetUnderAttack(true);
        aim_of_interact_->SetDamageEndingTime(clock() + kEnemyCoolDown);
        aim_of_interact_->DecreaseHp(applied_damage_);
      }
    }
    else
    {
     HandleALU();
    }
  }
}

void Enemy::CheckCellAndSetAim(LinearVector<int> coords)
{
  if(coords.x_ >= 0 && coords.x_ < kTilesAtLine && coords.y_ >= 0 && coords.y_ < kTilesAtLine)
  {
    if((*map_)[coords.x_][coords.y_] != nullptr)
    {
      if((*map_)[coords.x_][coords.y_]->GetObjectCode() == kPlayerCode)
      {
        aim_of_interact_ = (*map_)[coords.x_][coords.y_];
      }
    }
  }
}

void Enemy::Scan()
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

void Enemy::HandleALU()
{
  if (aim_of_interact_ != nullptr)
  {
    alu_->Execute(aim_of_interact_->GetRefCoords().y_, aim_of_interact_->GetRefCoords().x_, GetRefCoords().y_, GetRefCoords().x_);
    velocity_.x_ = roundl((alu_->GetRegister(0))*kEnemyVelocity);
    velocity_.y_ = roundl((alu_->GetRegister(1))*kEnemyVelocity);
    if (velocity_.GetAbs() == 0)
    {
      aim_of_interact_ = nullptr;
    }
  }
}

#endif
