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
  Engine engine;
	for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
  {
      if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5) || (i/kTilesAtLine == kTilesAtLine-5)  || (i%kTilesAtLine == kTilesAtLine-5) )
      {
        Factory::CreateCharacter(kEnemyId, LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), engine);
      }
  }

  GameObject* cilik = Factory::CreateCharacter(kPlayerId, LinearVector<int>(14,16), engine);
	while (engine.GetWindow().isOpen())
	{
    sf::Event event;
    while (engine.GetWindow().pollEvent(event))
    {
      if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        engine.GetWindow().close();
    }
    engine.GetWindow().clear();/*
      engine.Control(*cilik);
      engine.MoveAll();
      engine.DrawGround();
      engine.InteractAll();
      engine.ChangeAllFrames();
      engine.DrawAll();*/
    engine.Tact(*cilik);
    engine.GetWindow().display();
  }
	return 0;
}

