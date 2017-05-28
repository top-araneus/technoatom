#ifndef ENGINE_H
#define ENGINE_H

#include "GameObjects.h"
#include "dialogmanager.h"
using namespace sf;

typedef Array<Array<unsigned char>> GroundType;
typedef Array<Array<GameObject*>> AirType;  //TODO: make weak_ptr

class Engine
{
  public:
    LinearVector<char> GiveDirection();
    Engine();
    ~Engine();
    SurfaceType InitializeMap();
    Array<Array<unsigned char>> InitializeGround();
    void DrawGround();
    void DrawAll();
    void MoveAll();
    void InteractAll();
    void ChangeAllFrames();
    void Control();
    void ClearDead();
    void Tact();
    void InitializationOfSurface();
    void AddObject(GameObject& obj)
    {
      surface_[obj.GetGridCoords().x_][obj.GetGridCoords().y_] = &obj;
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
    time_t          GetLastTime() {
      return last_time_change;
    }
    void            SetLastTime() {
      last_time_change = clock();
    }
DialogWindow* dialog; //! REMOVE AFTER TEST
  private:
    SurfaceType     surface_;         //get
    GroundType      ground_;
    AirType         air_;
    Texture         ground_texture_;
    Sprite          ground_sprite_;
    int             num_of_grounds_;
    ReferenceFrame  frame_;           //get
    RenderWindow*   window_;          //get
    Font            font_;
    Text            game_over_;       //get
    time_t          last_time_change; //get, set
    bool            is_game_over_;
    GameObject*     player_;
    DialogManager*   dialog_manager_;
    class Factory
    {
      public:
        static GameObject* CreateCharacter(const int object_code, const LinearVector<int>& grid_coords, Engine& engine)
        {
          if(object_code == kPlayerId)
          {
            Texture player_texture;
            player_texture.loadFromFile(kPathToPlayerTexture);
            Player* result = new Player(engine.GetWindow(), engine.GetMap(), kStandartSpriteSizeOfPlayer, player_texture,
                                        grid_coords, engine.GetFrame(), kNumOfPlayerFrames, kNumOfPlayerStates);
            engine.AddObject(*result);
            return result;
          }
          else if(object_code == kEnemyId)
          {
            Texture enemy_texture;
            enemy_texture.loadFromFile(kPathToEnemyTexture);
            Enemy* result = new Enemy(engine.GetWindow(), engine.GetMap(), kStandartSpriteSizeOfEnemy, enemy_texture,
                                        grid_coords, engine.GetFrame(), kNumOfEnemyFrames, kNumOfEnemyStates);
            engine.AddObject(*result);
            return result;
          }
          else
          {
            print("Object: /# is not created", object_code);
            return nullptr;
          }
        }
    };
};

Engine::Engine()
{
	RenderWindow* window = new RenderWindow(sf::VideoMode(kWindowWidth, kWindowHeight), "Cyberpunk Universe", sf::Style::Fullscreen);
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
  font_.loadFromFile(kFontPath);
  game_over_ = Text("GAME OVER", font_, 48);
  game_over_.setColor(Color(255,0,0));
  game_over_.setPosition(kWindowWidth/2 - 100, kWindowHeight/2);
  is_game_over_ = false;
  SetLastTime();
  dialog_manager_ = new DialogManager(window_);
  /*DialogWindow* */dialog = dialog_manager_->AddDialog(LinearVector<int>(300,300), LinearVector<int>(300,300));
  dialog->SetVisible(true);
  dialog->AddButton(LinearVector<int>(100,50), LinearVector<int>(100,100), "Hello!");
  DialogWindow* dialog2 = dialog_manager_->AddDialog(LinearVector<int>(600,300), LinearVector<int>(700,400));
  dialog2->SetVisible(true);
  dialog2->AddButton(LinearVector<int>(200,100), LinearVector<int>(100,100), "World!");
}

Engine::~Engine()
{
  delete(window_);
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

  dialog_manager_->DrawDialogs();
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


void Engine::ClearDead()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      if (surface_[i][j] != nullptr)
      {
        if (!(surface_[i][j]->CheckAlive()))
        {
          if (surface_[i][j]->GetObjectCode() == kPlayerId)
          {
            is_game_over_ = true;
         }
          delete surface_[i][j];
          surface_[i][j] = nullptr;
        }
      }
    }
  }
}


void Engine::Control()
{
  LinearVector<double> new_velocity(0,0);
  if (Keyboard::isKeyPressed(Keyboard::A)) {
      new_velocity.x_ -= 1;
  }
  if (Keyboard::isKeyPressed(Keyboard::D)) {

      new_velocity.x_ += 1;
  }
  if (Keyboard::isKeyPressed(Keyboard::W)) {
    new_velocity.y_ -= 1;
  }
  if (Keyboard::isKeyPressed(Keyboard::S)) {
    new_velocity.y_ += 1;
  }
  new_velocity = new_velocity.GetNorm();
  new_velocity.x_ *= kPlayerVelocity;
  new_velocity.y_ *= kPlayerVelocity;
  player_->SetVelocity(new_velocity);
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
    LinearVector<int> cell_coords = GetCellFromCoords(coords);
    if (cell_coords.x_ >= 0 && cell_coords.y_ >= 0 && cell_coords.x_ < kTilesAtLine && cell_coords.y_ < kTilesAtLine)
    {
      player_->SetAimOfInteract(GetMap()[cell_coords.x_][cell_coords.y_]);
      player_->Interact();
      player_->SetAimOfInteract(nullptr);
    }
  }
  if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
  {
    dialog->GetButtons()[0]->OnClick();
  }
}

void Engine::Tact()
{
  if (is_game_over_) {
    window_->draw(GetGameOver());
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    {
      InitializationOfSurface();
      is_game_over_ = false;
    }
  }
  else {
    Control();
    if ((clock() - GetLastTime()) > kTactTime)
    {
      MoveAll();
    }
    DrawGround();
    InteractAll();
    if ((clock() - GetLastTime()) > kTactTime)
    {
      ChangeAllFrames();
      SetLastTime();
    }
    ClearDead();
    DrawAll();
  }
}

void Engine::InitializationOfSurface()
{
  for (int i = 0; i < kTilesAtLine; ++i)
  {
    for (int j = 0; j < kTilesAtLine; ++j)
    {
      delete surface_[i][j];
      surface_[i][j] = nullptr;
    }
  }
  for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
  {
    if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5) || (i/kTilesAtLine == kTilesAtLine-5)  || (i%kTilesAtLine == kTilesAtLine-5) )
    {
      Factory::CreateCharacter(kEnemyId, LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), *this);
    }
  }
  player_ = Factory::CreateCharacter(kPlayerId, LinearVector<int>(14,16), *this);
}
#endif // ENGINE_H
