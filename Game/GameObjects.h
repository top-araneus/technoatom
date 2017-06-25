#ifndef GAMEOBJECTS_H
#define GAMEOBJECTS_H
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
    void              SetRefCoords(LinearVector<int>& ref_coords)
    {
      ref_coords_ = ref_coords;
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
    virtual void DrawHUD() {}
    virtual void SetXp(int xp) {}
    virtual int GetXp() {}
  protected:
    LinearVector<char> GiveDirection();
    void GoToPlaceIfEmpty(LinearVector<int> coords);
    bool InMap(LinearVector<int> new_coords)
    {
      return (new_coords.x_ >= 0 && new_coords.x_ < kTilesAtLine && new_coords.y_ >= 0 && new_coords.y_ < kTilesAtLine);
    }
    int                         hp_;
    int                         cooldown_; //!< cooldown will be in milliseconds
    LinearVector<double>        velocity_;               //set
    LinearVector<int>           ref_coords_;             //get
    LinearVector<int>           grid_coords_;            //get
    LinearVector<char>          direction_;
    unsigned char               num_of_frames_;          //get
    unsigned char               current_frame_;          //set, get
    unsigned char               num_of_state_;
    unsigned char               current_state_;          //set, get
    unsigned char               object_code_;            //get
    unsigned char               frames_per_second_;
    time_t                      time_last_frame_changing_;
    int                         applied_damage_;
    time_t                      attack_ending_time_ = 0; //get, set
    time_t                      damage_ending_time_ = 0; //get, set
    bool                        in_attack_ = false;      //get, set
    bool                        under_attack_ = false;   //get, set
    Texture                     texture_;
    RenderWindow*               window_;
    LinearVector<int>           sprite_size_; //!< width and height of sprite
    std::vector<GameObject*> *map_; //! TODO: weak_ptr
    ReferenceFrame*             ref_frame_;
    GameObject*                 aim_of_interact_;        //get, set
};


LinearVector<char> GameObject::GiveDirection()
{
  return LinearVector<char>(1,-1);
}

void GameObject::DecreaseHp(int damage)
{
  hp_ -= damage;
}

void GameObject::Move()
{
  if(velocity_ != LinearVector<double>(0,0))
  {
    LinearVector<double> ort = velocity_.GetNorm();
    LinearVector<int> where_to;
    where_to.x_ = ref_coords_.x_ + velocity_.x_;
    where_to.y_ = ref_coords_.y_ + velocity_.y_;
    LinearVector<int> new_cell = GetCellFromCoords(where_to);
    if(InMap(new_cell))
    {
      GoToPlaceIfEmpty(where_to);
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

void GameObject::GoToPlaceIfEmpty(LinearVector<int> coords)
{
  bool check = true;
  for(int i = 0; i < (*map_).size(); ++i)
  {
    if((*map_)[i]->GetRefCoords().GetDistance(coords) <= kEnemyWidth && this != (*map_)[i])
    {
      check = false;
    }
  }
  if(check)
  {
    ref_coords_ = coords;
  }

}

class Player: public GameObject
{
  public:
    Player(RenderWindow& window, std::vector<GameObject*>& pMap, const LinearVector<int> spriteSize, Texture& texture,
      LinearVector<int> gridCoords, ReferenceFrame& refFrame, const int numOfFrames, const int numOfStates);
    ~Player();
    virtual void Draw();
    virtual void Interact();
    virtual void NextFrame(char step = 1);
    void DrawHUD();
    virtual void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }
    int GetXp(){
      return xp_;
    }
    void SetXp(int xp){
      xp_ = xp;
    }
    virtual void Move()
    {
      GameObject::Move();
    }

  private:
    int xp_;                 //get, set
    bool next_sprite_right = true;
};

Player::Player(RenderWindow& window, std::vector<GameObject*>& pMap, const LinearVector<int> spriteSize, Texture& texture,
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
  object_code_ = kPlayerId;
  time_last_frame_changing_ = clock();
  frames_per_second_ = kFramesPerSec;
  SetXp(0);
  void Shoot(LinearVector<double>& direction);
}

Player::~Player()
{
   std::for_each((*map_).begin(), (*map_).end(),
                 [](GameObject* obj)->void
                 {
                  if(obj->GetObjectCode() == kEnemyId)
                  {
                    obj->SetAimOfInteract(nullptr);
                  }
                 });
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
  //DrawHUD();
  window_->draw(player_sprite);
}

void Player::Interact()
{
  if (aim_of_interact_ != nullptr)
  {
    if (aim_of_interact_->GetObjectCode() == kEnemyId)
    {
      if (aim_of_interact_->GetRefCoords().GetDistance(GetRefCoords()) <= kRangeOfPlayerAttack)
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

void Player::DrawHUD()
{
  std::string hp = std::string("Health: ") + std::to_string(hp_);
  std::string xp = std::string("Points: ") + std::to_string(xp_);
  sf::Font font;
  font.loadFromFile("fonts/font.ttf");

  sf::Text hp_text(hp, font);
  hp_text.setCharacterSize(40);
  hp_text.setColor(sf::Color::Green);
  hp_text.setPosition(kWindowWidth - 300, 10);
  window_->draw(hp_text);

  sf::Text xp_text(xp, font);
  xp_text.setCharacterSize(40);
  xp_text.setColor(sf::Color::Red);
  xp_text.setPosition(50, 10);
  window_->draw(xp_text);
}


class Enemy: public GameObject
{
  public:
    Enemy(RenderWindow& window, std::vector<GameObject*>& pMap, LinearVector<int> spriteSize, Texture& texture,
         LinearVector<int> gridCoords, ReferenceFrame& refFrame, int numOfFrames, int numOfStates);
    ~Enemy();
    virtual void Draw();
    virtual void Interact();
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

Enemy::Enemy(RenderWindow& window, std::vector<GameObject*>& pMap, LinearVector<int> spriteSize, Texture& texture,
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
  object_code_ = kEnemyId;
  aim_of_interact_ = nullptr;
  time_last_frame_changing_ = clock();
  frames_per_second_ = kFramesPerSec;
  alu_ = new ALU(kEnemyProgram);
}

Enemy::~Enemy()
{
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
    if (aim_of_interact_->GetRefCoords().GetDistance(ref_coords_) <= kRangeOfEnemyAttack)
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



void Enemy::Scan()
{
  for(int i = 0; i < (*map_).size(); i++)
  {
    if((*map_)[i]->GetObjectCode() == kPlayerId)
    {
      if((*map_)[i]->GetRefCoords().GetDistance(ref_coords_) <= kRangeOfVision)
      {
        aim_of_interact_ = (*map_)[i];
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


class Bullet: public GameObject
{
  public:
    Bullet(RenderWindow& window, std::vector<GameObject*>& pMap, LinearVector<int> spriteSize, Texture& texture,
         LinearVector<int> gridCoords, ReferenceFrame& refFrame, int numOfFrames, int numOfStates);
    ~Bullet();
    virtual void Draw();
    virtual void Interact();
    void Scan();
    virtual void Move();
    virtual void DecreaseHp(int damage)
    {
      GameObject::DecreaseHp(damage);
    }
    virtual void NextFrame(char step = 1)
    {
      GameObject::NextFrame(step);
    }
};

Bullet::Bullet(RenderWindow& window, std::vector<GameObject*>& pMap, LinearVector<int> spriteSize, Texture& texture,
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
  hp_ = 1000;
  object_code_ = kBulletId;
  aim_of_interact_ = nullptr;
  time_last_frame_changing_ = clock();
  frames_per_second_ = kFramesPerSec;
}

Bullet::~Bullet()
{
  aim_of_interact_ = nullptr;
}

void Bullet::Draw()
{
    Sprite bullet_sprite;
    bullet_sprite.setTexture(texture_);
    bullet_sprite.setTextureRect(IntRect(current_frame_ * sprite_size_.x_, current_state_ * sprite_size_.y_,
                    sprite_size_.x_, sprite_size_.y_));
    bullet_sprite.setOrigin(Vector2f(sprite_size_.x_ / 2, sprite_size_.y_ - kCellHeight / 2));
    bullet_sprite.setPosition(ref_frame_->GetX() + ref_coords_.x_, ref_frame_->GetY() + ref_coords_.y_);
    window_->draw(bullet_sprite);
}

void Bullet::Interact()
{
  LinearVector<int> cell = GetCellFromCoords(ref_coords_);
  if(InMap(cell)){
    if (aim_of_interact_ == nullptr)
    {
      Scan();
    }
    if (aim_of_interact_ != nullptr)
    {
        aim_of_interact_->SetUnderAttack(true);
        aim_of_interact_->SetDamageEndingTime(clock() + kEnemyCoolDown);
        aim_of_interact_->DecreaseHp(applied_damage_);
        hp_ = 0;
    }
  }
  else{
    hp_ = 0;
  }
}

void Bullet::Scan()
{
  for(int i = 0; i < (*map_).size(); i++)
  {
    if((*map_)[i]->GetObjectCode() == kEnemyId)
    {
      if((*map_)[i]->GetRefCoords().GetDistance(ref_coords_) <= kEnemyWidth)
      {
        aim_of_interact_ = (*map_)[i];
      }
    }
  }
}

void Bullet::Move()
{
    ref_coords_.x_ = ref_coords_.x_ + velocity_.x_;
    ref_coords_.y_ = ref_coords_.y_ + velocity_.y_;
}



#endif
