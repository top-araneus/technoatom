#ifndef ENGINE_H
#define ENGINE_H

#include "GameObjects.h"
#include "dialogmanager.h"
using namespace sf;

int clock1 = 1;
typedef Array<Array<unsigned char>> GroundType;
typedef Array<Array<GameObject*>> AirType;  //TODO: make weak_ptr

class Engine
{
  public:
    LinearVector<char> GiveDirection();
    Engine();
    ~Engine();
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
    void DebugCheck();
    void ChangeWindowText(DialogWindow* window); //! REMOVE AFTER TEST
    void Shoot();
    void RestartGame();
    void AddObject(GameObject& obj)
    {
      surface_.push_back(&obj);
    }

    std::vector<GameObject*>&    GetObjects() {
      return surface_;
    }
    ReferenceFrame& GetFrame() {
      return frame_;
    }
    RenderWindow&   GetWindow() {
      return *window_;
    }
    /*Text&           GetGameOver() {
      return game_over_;
    }*/
    time_t          GetLastTime() {
      return last_time_change;
    }
    SoundManager*          GetSoundManager() {
      return sound_manager_;
    }
    void            SetLastTime() {
      last_time_change = clock();
    }
    void            SetEvent(sf::Event event)
    {
      event_ = event;
    }
    void            PrintDebug()
    {
      debug_window_->GetTexts()[0]->setString(debug_stream_.str());
    }
    void            CloseWindow()
    {
      window_->close();
    }
DialogWindow* debug_window_;
DialogWindow* menu_window_;
int             enemies_count_;
  private:
    std::vector<GameObject*>     surface_;         //get
    GroundType      ground_;
    AirType         air_;
    Texture         ground_texture_;
    Sprite          ground_sprite_;
    int             num_of_grounds_;
    ReferenceFrame  frame_;           //get
    RenderWindow*   window_;          //get
    Font            font_;
    //Text            game_over_;       //get
    time_t          last_time_change; //get, set
    time_t          last_time_debug_;
    time_t          last_time_shoot_;
    bool            is_game_over_;
    GameObject*     player_;
    DialogManager*  dialog_manager_;
    sf::Event       event_;
    LinearVector<int> mouse_position_;
    LinearVector<int> starting_drag_;
    LinearVector<int> ending_drag_;
    bool            debug_visible_;
    std::ostringstream debug_stream_;
    bool            dragging_;
    SoundManager* sound_manager_; //get
    class Factory
    {
      public:
        static GameObject* CreateCharacter(const int object_code, const LinearVector<int>& grid_coords, Engine& engine)
        {
          if(object_code == kPlayerId)
          {
            Texture player_texture;
            player_texture.loadFromFile(kPathToPlayerTexture);
            Player* result = new Player(engine.GetWindow(), engine.GetObjects(), kStandartSpriteSizeOfPlayer, player_texture,
                                        grid_coords, engine.GetFrame(), kNumOfPlayerFrames, kNumOfPlayerStates, engine.GetSoundManager());
            engine.AddObject(*result);
            return result;
          }
          else if(object_code == kEnemyId)
          {
            ++(engine.enemies_count_);
            Texture enemy_texture;
            enemy_texture.loadFromFile(kPathToEnemyTexture);
            Enemy* result = new Enemy(engine.GetWindow(), engine.GetObjects(), kStandartSpriteSizeOfEnemy, enemy_texture,
                                        grid_coords, engine.GetFrame(), kNumOfEnemyFrames, kNumOfEnemyStates);
            engine.AddObject(*result);
            return result;
          }
          else if(object_code == kBulletId)
          {
            sf::Image bullet_image;
            bullet_image.loadFromFile(kPathToBulletTexture);
            bullet_image.createMaskFromColor(sf::Color::White);
            Texture bullet_texture;
            bullet_texture.loadFromImage(bullet_image);
            Bullet* result = new Bullet(engine.GetWindow(), engine.GetObjects(), kStandartSpriteSizeOfBullet, bullet_texture,
                                        grid_coords, engine.GetFrame(), kNumOfBulletFrames, kNumOfBulletStates);
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
    void CreateBullet(LinearVector<int>& direction, LinearVector<int> ref_coords)
    {
      GameObject* bullet = Factory::CreateCharacter(kBulletId, GetCellFromCoords(ref_coords), *this);
      bullet->SetRefCoords(ref_coords);
      LinearVector<double> velocity = direction.GetNorm();
      velocity.x_ = kBulletVelocity * velocity.x_;
      velocity.y_ = kBulletVelocity * velocity.y_;
      bullet->SetVelocity(velocity);
    }

};



Engine::Engine()
{
	RenderWindow* window = new RenderWindow(sf::VideoMode(kWindowWidth, kWindowHeight), "MOZEE MONTANA UBIVAET BIT"/*, sf::Style::Fullscreen*/);
  window_ = window;
  window_->setFramerateLimit(kFrameRate);
  //window_->setVerticalSyncEnabled(true);
  frame_ = ReferenceFrame(-((kTilesAtLine + 1) * kCellWidth / 4), -((kTilesAtLine + 1) * kCellHeight / 4), 800, 600);
  sound_manager_ = new SoundManager();
  ground_ = InitializeGround();
  ground_texture_.loadFromFile("images/debuggrid.png");
  num_of_grounds_ = ground_texture_.getSize().x / kCellWidth;
  ground_sprite_.setTexture(ground_texture_);
  ground_sprite_.setTextureRect(IntRect(0, 0, kCellWidth, kCellHeight));
  font_.loadFromFile(kFontPath);
  is_game_over_ = false;
  SetLastTime();
  last_time_debug_ = clock();
  last_time_shoot_ = clock();
  dialog_manager_ = new DialogManager(window_);
  debug_window_ = dialog_manager_->AddDialog(LinearVector<int>(300,300), LinearVector<int>(300,300));
  debug_window_->SetVisible(false);
  debug_window_->AddText(10, LinearVector<int>(10, 50), "");

  menu_window_ = dialog_manager_->AddMenu();
  menu_window_->GetTexts()[0]->setString(std::string("Menu"));
  menu_window_->SetVisible(false);
  menu_window_->GetButtons()[1]->OnClick.Connect(this, &Engine::RestartGame);
  menu_window_->GetButtons()[2]->OnClick.Connect(this, &Engine::CloseWindow);

  Button* button = debug_window_->AddButton(LinearVector<int>(70,30), LinearVector<int>(130,250), "Debug!");
  button->OnClick.Connect(this, &Engine::PrintDebug);
  mouse_position_ = sf::Mouse::getPosition();
  dragging_ = false;
  debug_visible_ = debug_window_->GetVisible();
}

Engine::~Engine()
{
  delete(window_);
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
  std::for_each(surface_.begin(), surface_.end(), [](GameObject* obj){ obj->NextFrame(); });
}

void Engine::DrawAll()
{
  std::sort(surface_.begin(), surface_.end(), [](GameObject* left, GameObject* right) { return(left->GetRefCoords().y_ < right->GetRefCoords().y_); });
  std::for_each(surface_.begin(), surface_.end(), [](GameObject* obj){ obj->Draw(); });


  dialog_manager_->DrawDialogs();
}

void Engine::MoveAll()
{
std::for_each(surface_.begin(), surface_.end(), [](GameObject* obj){ obj->Move(); });
}

void Engine::InteractAll()
{
  for(int i = 0; i < surface_.size(); ++i)
  {
    if ( clock() >= surface_[i]->GetDamageEndingTime())
    {
      surface_[i]->SetUnderAttack(false);
    }
    if (clock() >= surface_[i]->GetAttackEndingTime())
    {
      surface_[i]->SetInAttack(false);
    }
    if(surface_[i]->GetObjectCode() != kPlayerId)
    {
      surface_[i]->Interact();
    }
  }
}


void Engine::ClearDead()
{
  for(int i = 0; i < surface_.size(); i++)
  {
    if (!(surface_[i]->CheckAlive()))
    {
      if (surface_[i]->GetObjectCode() == kPlayerId)
      {
        is_game_over_ = true;
      }
      if (surface_[i]->GetObjectCode() == kEnemyId)
      {
        --enemies_count_;
        sound_manager_->kill_sound_.play();
        player_->SetXp(player_->GetXp() + kXpStep*(kEnemyHp/kEnemyDamage));
      }
      delete surface_[i];
      surface_.erase(surface_.begin() + i);
      i--;
    }
  }
}


void Engine::Control()
{
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    LinearVector<int> coords = LinearVector<int>(sf::Mouse::getPosition(*window_).x,
                                                  sf::Mouse::getPosition(*window_).y);
    dialog_manager_->ManageClicks(coords, false);
    if (!dragging_)
    {
      dragging_ = true;
      starting_drag_ = mouse_position_;
    }
    else
    {
      ending_drag_ = mouse_position_;
      dialog_manager_->ManageMoves(starting_drag_, ending_drag_);
      starting_drag_ = ending_drag_;
    }
  }
  else
  {
    LinearVector<int> coords = LinearVector<int>(sf::Mouse::getPosition(*window_).x,
                                                  sf::Mouse::getPosition(*window_).y);

    if (dragging_)
    {
      dragging_ = false;
    }
    dialog_manager_->ManageClicks(coords, true);
  }

  if (!is_game_over_)
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
      for(int i = 0; i < surface_.size(); ++i)
      {
        if(surface_[i]->GetObjectCode() == kEnemyId && surface_[i]->GetRefCoords().GetDistance(coords) <= kEnemyWidth)
        {
          player_->SetAimOfInteract(surface_[i]);
          player_->Interact();
          player_->SetAimOfInteract(nullptr);
        }
      }

    }
  }
  }
}

void Engine::Shoot()
{
  if (Keyboard::isKeyPressed(Keyboard::Space))
  {
      sound_manager_->range_sound_.play();
      LinearVector<int> coords = LinearVector<int>(sf::Mouse::getPosition(*window_).x - GetFrame().GetX(),
                                                  sf::Mouse::getPosition(*window_).y - GetFrame().GetY());
      LinearVector<int> player_coords = LinearVector<int>(player_->GetRefCoords().x_, player_->GetRefCoords().y_ - (kStandartSpriteSizeOfPlayer.y_ - 72) + player_->GetFrame()*32);
      LinearVector<int> direction = LinearVector<int>(coords.x_ - player_coords.x_, coords.y_ - player_coords.y_);
      this->CreateBullet(direction, player_coords);
  }
}

void Engine::DebugCheck()
{
  if (Keyboard::isKeyPressed(Keyboard::Tilde))
  {
    if (debug_visible_)
      debug_window_->SetVisible(false);
    else
      debug_window_->SetVisible(true);
  }
  else
  {
    debug_visible_ = debug_window_->GetVisible();
  }
  if (Keyboard::isKeyPressed(Keyboard::Escape))
  {
    menu_window_->SetVisible(true);
  }
}

void Engine::RestartGame()
{
  sound_manager_->bg_sound_.stop();
  sound_manager_->restart_sound_.play();
  menu_window_->GetTexts()[0]->setString(std::string("Menu"));
  InitializationOfSurface();
  is_game_over_ = false;
  menu_window_->SetVisible(false);
}


void Engine::Tact()
{
  if (debug_window_->GetVisible())
  {
    print(debug_stream_, "FPS: /#, clockdiff: /#\n", 1000/(1+clock()-clock1), clock()-clock1);
    if (clock() - last_time_debug_ > kDebugCoolDown)
    {
        last_time_debug_ = clock();
        PrintDebug();
        if (debug_stream_.str().length() > 200)
        {
          debug_stream_.str("");
        }
    }
  }
  mouse_position_ = sf::Mouse::getPosition(*window_);
  /*window_->pollEvent(event_);*/
  if (event_.type == sf::Event::Closed)
      window_->close();
  if (is_game_over_) {
      //!TODO: MENU WINDOW
    menu_window_->GetTexts()[0]->setString(std::string("Game over!"));
    menu_window_->SetVisible(true);
  }
  Control();
  if (!is_game_over_) {
  if ((clock() - last_time_shoot_) > kShootCoolDown)
  {
    Shoot();
    last_time_shoot_ = clock();
  }
  }
  DebugCheck();
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

  if (!is_game_over_) {
  player_->DrawHUD();
  }

  if (enemies_count_ == 0)
  {
    menu_window_->GetTexts()[0]->setString(std::string("You won!"));
    menu_window_->SetVisible(true);
    if (!is_game_over_)
    {
      is_game_over_ = true;
      sound_manager_->win_sound_.play();
    }
  }

clock1 = clock();
}

void Engine::InitializationOfSurface()
{
  enemies_count_ = 0;
  sound_manager_->bg_sound_.play();
  for(int i = 0; i < surface_.size(); ++i)
  {
    delete surface_[i];
    surface_.erase(surface_.begin() + i);
    i--;
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
