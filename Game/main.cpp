using namespace std;
bool in_death = false;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;
#include <iostream>
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refframe.h>
#include "constants.h"
#include <GameObjects.h>
#include <Engine.h>
#include "factory.h"

int main()
{
	RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cyberpunk Universe", sf::Style::Close);

  Engine engine(&window);
  window.setFramerateLimit(kFrameRate);
  window.setVerticalSyncEnabled(true);


	/*Texture cilinder_texture;
	cilinder_texture.loadFromFile("images/cilindr.png");*/
	Texture cube_texture;
	cube_texture.loadFromFile("images/cub.png");


	Array<Enemy*> gops(kTilesAtLine*kTilesAtLine);
	for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
  {
      if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5) || (i/kTilesAtLine == kTilesAtLine-5)  || (i%kTilesAtLine == kTilesAtLine-5) )
      {
        gops[i] = new Enemy(&window, &(engine.getMap()), LinearVector<int>(128,138), cube_texture,
           LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), &(engine.getFrame()), 1, 1);

      engine.AddObject(gops[i]);}
      else gops[i] = nullptr;
  }

 /* Player cilik(&window, &(engine.getMap()), LinearVector<int>(128,192), cilinder_texture,
              LinearVector<int>(14,16), &(engine.getFrame()), 4, 1);
  engine.AddObject(&cilik);*/
  GameObject* cilik = Factory::CreateCharacter(kPlayerId, LinearVector<int>(14,16), engine);
  Enemy kubik(&window, &(engine.getMap()), LinearVector<int>(128,138), cube_texture,
              LinearVector<int>(16,14), &(engine.getFrame()), 1, 1);
  engine.AddObject(&kubik);

	//float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{

      sf::Event event;
      while (window.pollEvent(event))
      {
        if (event.type == sf::Event::Closed)
          window.close();
      }
      /*  int cnt = 0;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;*/




		window.clear();

  if (in_death)
  {
      window.draw(engine.GetGameOver());
  }
  else
  {
    engine.Control(*cilik);
    engine.MoveAll();
    engine.DrawGround();

    engine.InteractAll();
    engine.ChangeAllFrames();
    engine.DrawAll();
  }
  window.display();
	}
	return 0;
}

