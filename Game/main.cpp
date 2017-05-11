using namespace std;
bool in_death = false;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;
#include <iostream>
#include <windows.h>
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refframe.h>
#include "constants.h"
#include <gameobjects.h>
#include <engine.h>
#include "factory.h"

int main()
{
	RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cyberpunk Universe", sf::Style::Fullscreen);
  Engine engine(&window);
	Array<GameObject*> gops(kTilesAtLine*kTilesAtLine);
	for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
  {
      if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5) || (i/kTilesAtLine == kTilesAtLine-5)  || (i%kTilesAtLine == kTilesAtLine-5) )
      {
        gops[i] = Factory::CreateCharacter(kEnemyId, LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), engine);
      }
      else gops[i] = nullptr;
  }

  GameObject* cilik = Factory::CreateCharacter(kPlayerId, LinearVector<int>(14,16), engine);
	Clock clock;
	while (window.isOpen())
	{
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        window.close();
    }
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

