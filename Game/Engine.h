#ifndef ENGINE_H
#define ENGINE_H

#include "GameObjects.h"
using namespace sf;

typedef Array<Array<unsigned char>> GroundType;
typedef Array<Array<GameObject*>> AirType;  //TODO: make weak_ptr

class Engine
{
  public:
  LinearVector<char> GiveDirection();
  Engine(RenderWindow* window);
  ~Engine() { }
  SurfaceType InitializeMap();
  Array<Array<unsigned char>> InitializeGround();
  void DrawGround();
  void DrawAll();
  void MoveAll();
  void InteractAll();
  void ChangeAllFrames();
  void Control(GameObject& player);
  void AddObject(GameObject* obj)
  {
    surface_[obj->GetGridCoords().x_][obj->GetGridCoords().y_] = obj;
  }

  SurfaceType&    GetMap() {
    return surface_;
  }
  ReferenceFrame& GetFrame() {
    return frame_;
  }
  RenderWindow&   GetWindow() {
    return *window_;
  }
  Text&           GetGameOver() {
    return game_over_;
  }
  private:
  SurfaceType surface_;
  GroundType ground_;
  AirType air_;
  Texture ground_texture_;
  Sprite ground_sprite_;
  int num_of_grounds_;
  ReferenceFrame frame_;
  RenderWindow* window_;
  Font font_;
  Text game_over_;
};

Engine::Engine(RenderWindow* window)
{
  window_ = window;
  window_->setFramerateLimit(kFrameRate);
  window_->setVerticalSyncEnabled(true);
  frame_ = ReferenceFrame(-((kTilesAtLine + 1) * kCellWidth / 4), -((kTilesAtLine + 1) * kCellHeight / 4), 800, 600);
  surface_ = InitializeMap();
  ground_ = InitializeGround();
  ground_texture_.loadFromFile("images/debuggrid.png");
  num_of_grounds_ = ground_texture_.getSize().x / kCellWidth;
  ground_sprite_.setTexture(ground_texture_);
  ground_sprite_.setTextureRect(IntRect(0, 0, kCellWidth, kCellHeight));
  font_.loadFromFile("fonts/font.ttf");
  game_over_ = Text("GAME OVER", font_, 48);
  game_over_.setColor(Color(255,0,0));
  game_over_.setPosition(kWindowWidth/2 - 100, kWindowHeight/2);
}

SurfaceType Engine::InitializeMap()
{
  SurfaceType map_array(kTilesAtLine);
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    map_array[i] = Array<GameObject*>(kTilesAtLine);
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      map_array[i][j] = nullptr;
    }
  }
  return map_array;
}

Array<Array<unsigned char>> Engine::InitializeGround()
{
  Array<Array<unsigned char>> ground_array(kTilesAtLine);
  srand(time(nullptr));
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    ground_array[i] = Array<unsigned char>(kTilesAtLine);
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      ground_array[i][j] = rand()%2;
    }
  }
  return ground_array;
}

void Engine::DrawGround()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    ground_sprite_.setPosition(frame_.GetX() + (kCellWidth / 2) * i, frame_.GetY() + (kCellHeight / 2) * (kTilesAtLine + i));
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      ground_sprite_.setTextureRect(IntRect(kCellWidth*ground_[i][j], 0, kCellWidth, kCellHeight));
      window_->draw(ground_sprite_);
      ground_sprite_.setPosition(ground_sprite_.getPosition().x + kCellWidth / 2, ground_sprite_.getPosition().y - kCellHeight / 2);
    }
  }
}

void Engine::ChangeAllFrames()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      if (surface_[i][j] != nullptr)
      {
        surface_[i][j]->NextFrame();
      }
    }
  }
}

void Engine::DrawAll()
{
  LinearVector<int> cell_coords (0, kTilesAtLine-1);
  int last_x_index = kTilesAtLine-1;
  while (cell_coords.y_ >= 0)
  {
    while (cell_coords.y_ < kTilesAtLine)
    {
      if (surface_[cell_coords.x_][cell_coords.y_] != nullptr)
      {
        surface_[cell_coords.x_][cell_coords.y_]->Draw();
      }
      cell_coords = cell_coords + LinearVector<int>(1,1);
    }
    last_x_index -= 1;
    cell_coords = LinearVector<int>(0, last_x_index);
  }
  cell_coords = LinearVector<int>(1, 0);
  last_x_index = 1;
  while (cell_coords.x_ < kTilesAtLine)
  {
    int last_y_index = kTilesAtLine - cell_coords.x_;
    while (cell_coords.y_ < last_y_index)
    {
      if (surface_[cell_coords.x_][cell_coords.y_] != nullptr)
      {
        surface_[cell_coords.x_][cell_coords.y_]->Draw();
      }
      cell_coords = cell_coords + LinearVector<int>(1, 1);
    }
    last_x_index += 1;
    cell_coords = LinearVector<int>(last_x_index, 0);
  }
}

void Engine::MoveAll()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      if (surface_[i][j] != nullptr)
        surface_[i][j]->Move();
    }
  }
}


void Engine::InteractAll()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      if (surface_[i][j] != nullptr)
      {
        if (clock() >= surface_[i][j]->GetDamageEndingTime())
        {
          surface_[i][j]->SetUnderAttack(false);
        }
        if (clock() >= surface_[i][j]->GetAttackEndingTime())
        {
          surface_[i][j]->SetInAttack(false);
        }

        surface_[i][j]->Interact();
      }
    }
  }
}

void Engine::Control(GameObject& player)
{

  if (Keyboard::isKeyPressed(Keyboard::A)) {
    player.SetVelocity(LinearVector<int>(-kPlayerVelocity, 0));
  }
  else if (Keyboard::isKeyPressed(Keyboard::D)) {
    player.SetVelocity(LinearVector<int>(kPlayerVelocity, 0));
  }
  else if (Keyboard::isKeyPressed(Keyboard::W)) {
    player.SetVelocity(LinearVector<int>(0, -kPlayerVelocity));
  }
  else if (Keyboard::isKeyPressed(Keyboard::S)) {
    player.SetVelocity(LinearVector<int>(0, kPlayerVelocity));
  }
  else
  {
    player.SetVelocity(LinearVector<int>(0, 0));
  }

  if (Keyboard::isKeyPressed(Keyboard::Right) || sf::Mouse::getPosition(*window_).x > kWindowWidth-kWindowMargin) {
    if (sf::Mouse::getPosition(*window_).x > kWindowWidth-kWindowMargin/2)
    {
      GetFrame().SetX(GetFrame().GetX()-2*kCameraVelocity);
    }
    else
    {
      GetFrame().SetX(GetFrame().GetX()-kCameraVelocity);
    }
  }
  if (Keyboard::isKeyPressed(Keyboard::Left) || sf::Mouse::getPosition(*window_).x < kWindowMargin) {
    if (sf::Mouse::getPosition(*window_).x < kWindowMargin/2)
    {
      GetFrame().SetX(GetFrame().GetX()+2*kCameraVelocity);
    }
    else
    {
      GetFrame().SetX(GetFrame().GetX()+kCameraVelocity);
    }
  }
  if (Keyboard::isKeyPressed(Keyboard::Down) || sf::Mouse::getPosition(*window_).y > kWindowHeight-kWindowMargin) {
    if (sf::Mouse::getPosition(*window_).y > kWindowHeight-kWindowMargin/2)
    {
      GetFrame().SetY(GetFrame().GetY()-2*kCameraVelocity);
    }
    else
    {
      GetFrame().SetY(GetFrame().GetY()-kCameraVelocity);
    }
  }
  if (Keyboard::isKeyPressed(Keyboard::Up) || sf::Mouse::getPosition(*window_).y < kWindowMargin) {
    if (sf::Mouse::getPosition(*window_).y < kWindowMargin/2)
    {
      GetFrame().SetY(GetFrame().GetY()+2*kCameraVelocity);
    }
    else
    {
      GetFrame().SetY(GetFrame().GetY()+kCameraVelocity);
    }
  }


  if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
  {
    LinearVector<int> coords = LinearVector<int>(sf::Mouse::getPosition(*window_).x - GetFrame().GetX(),
                                                  sf::Mouse::getPosition(*window_).y - GetFrame().GetY());
    print("coords: /# /#\n", coords.x_, coords.y_);
    LinearVector<int> cell_coords = GetCellFromCoords(coords);
    print("cell: /# /#\n", cell_coords.x_, cell_coords.y_);
    if (cell_coords.x_ >= 0 && cell_coords.y_ >= 0 && cell_coords.x_ < kTilesAtLine && cell_coords.y_ < kTilesAtLine)
    {
      player.SetAimOfInteract(GetMap()[cell_coords.x_][cell_coords.y_]);
      if (GetMap()[cell_coords.x_][cell_coords.y_])
      {
        print("id: /# /#\n", GetMap()[cell_coords.x_][cell_coords.y_]->GetObjectCode(), kEnemyId);
      }
      player.Interact();
      player.SetAimOfInteract(nullptr);
    }
  }
}

#endif // ENGINE_H
