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
    void Control(RenderWindow& window, Player& cilik, Engine& engine);
    void AddObject(GameObject* obj)
    {
      surface_[obj->GetGridCoords().x_][obj->GetGridCoords().y_] = obj;
    }

    SurfaceType& getMap()
    {
      return surface_;
    }

    ReferenceFrame& getFrame()
    {
      return frame_;
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
};

Engine::Engine(RenderWindow* window)
{
  window_ = window;
  frame_ = ReferenceFrame(-((kTilesAtLine + 1) * kCellWidth / 4), -((kTilesAtLine + 1) * kCellHeight / 4), 800, 600);
  surface_ = InitializeMap();
  ground_ = InitializeGround();
  ground_texture_.loadFromFile("images/debuggrid.png");
  num_of_grounds_ = ground_texture_.getSize().x / kCellWidth;
  ground_sprite_.setTexture(ground_texture_);
  ground_sprite_.setTextureRect(IntRect(0, 0, kCellWidth, kCellHeight));
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

// TODO: perspective for ground drawing
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
     // print("took /# /#\n", cell_coords.x_, cell_coords.y_);
      if (surface_[cell_coords.x_][cell_coords.y_] != nullptr)
      {
        surface_[cell_coords.x_][cell_coords.y_]->Draw();
   //     print("drawn /# /#\n", cell_coords.x_, cell_coords.y_);
      }
      cell_coords = cell_coords + LinearVector<int>(1,1);
  //    print("new /# /#\n", cell_coords.x_, cell_coords.y_);
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
   //   print("took /# /#\n", cell_coords.x_, cell_coords.y_);
      if (surface_[cell_coords.x_][cell_coords.y_] != nullptr)
      {

        surface_[cell_coords.x_][cell_coords.y_]->Draw();
    //    print("drawn /# /#\n", cell_coords.x_, cell_coords.y_);
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
           // surface_[i][j]->SetAimOfInteract(nullptr);

          }

          surface_[i][j]->Interact();
        }

      }
  }
}
  void Engine::Control(RenderWindow& window, Player& cilik, Engine& engine)
  {
    		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
			cilik.SetVelocity(LinearVector<int>(-kPlayerVelocity, 0));
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
			cilik.SetVelocity(LinearVector<int>(kPlayerVelocity, 0));
        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
			cilik.SetVelocity(LinearVector<int>(0, -kPlayerVelocity));
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
			cilik.SetVelocity(LinearVector<int>(0, kPlayerVelocity));
        }
        else
        {
			cilik.SetVelocity(LinearVector<int>(0, 0));
        }
		if (Keyboard::isKeyPressed(Keyboard::Right) || sf::Mouse::getPosition(window).x > kWindowWidth-kWindowMargin)
    {
      if (sf::Mouse::getPosition(window).x > kWindowWidth-kWindowMargin/2)
      {
        engine.getFrame().SetX(engine.getFrame().GetX()-2*kCameraVelocity);
      }
      else
      {
        engine.getFrame().SetX(engine.getFrame().GetX()-kCameraVelocity);
      }
		}

		if (Keyboard::isKeyPressed(Keyboard::Left) || sf::Mouse::getPosition(window).x < kWindowMargin)
		{
      if (sf::Mouse::getPosition(window).x < kWindowMargin/2)
      {
        engine.getFrame().SetX(engine.getFrame().GetX()+2*kCameraVelocity);
      }
      else
      {
        engine.getFrame().SetX(engine.getFrame().GetX()+kCameraVelocity);
      }
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) || sf::Mouse::getPosition(window).y > kWindowHeight-kWindowMargin)
    {
      if (sf::Mouse::getPosition(window).y > kWindowHeight-kWindowMargin/2)
      {
        engine.getFrame().SetY(engine.getFrame().GetY()-2*kCameraVelocity);
      }
      else
      {
        engine.getFrame().SetY(engine.getFrame().GetY()-kCameraVelocity);
      }
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) || sf::Mouse::getPosition(window).y < kWindowMargin)
    {
      if (sf::Mouse::getPosition(window).y < kWindowMargin/2)
      {
        engine.getFrame().SetY(engine.getFrame().GetY()+2*kCameraVelocity);
      }
      else
      {
        engine.getFrame().SetY(engine.getFrame().GetY()+kCameraVelocity);
      }
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Right))
    {
       LinearVector<int> coords = LinearVector<int>(sf::Mouse::getPosition(window).x - engine.getFrame().GetX(),
                                                    sf::Mouse::getPosition(window).y - engine.getFrame().GetY());
       print("coords: /# /#\n", coords.x_, coords.y_);
       LinearVector<int> cell_coords = GetCellFromCoords(coords);
       print("cell: /# /#\n", cell_coords.x_, cell_coords.y_);
       if (cell_coords.x_ >= 0 && cell_coords.y_ >= 0 && cell_coords.x_ < kTilesAtLine && cell_coords.y_ < kTilesAtLine)
       {
         cilik.SetAimOfInteract(engine.getMap()[cell_coords.x_][cell_coords.y_]);
         if (engine.getMap()[cell_coords.x_][cell_coords.y_])
          print("id: /# /#\n", engine.getMap()[cell_coords.x_][cell_coords.y_]->GetObjectCode(), kEnemyId);
         cilik.Interact();
         cilik.SetAimOfInteract(nullptr);
       }
    }
  }

#endif // ENGINE_H
