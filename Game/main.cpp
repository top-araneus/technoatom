using namespace std;
bool in_death = false;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;
#include <iostream>
#include <sstream>
#include <windows.h>
#include "delegates.h"
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refframe.h>
#include "constants.h"
#include "sounds.h"
#include <gameobjects.h>
#include <engine.h>
#include "factory.h"

int main()
{
  Engine engine;
	engine.InitializationOfSurface();
	while (engine.GetWindow().isOpen())
	{
    sf::Event event;
    while (engine.GetWindow().pollEvent(event))
    {
      engine.SetEvent(event);
      /*if (event.type == sf::Event::Closed || Keyboard::isKeyPressed(Keyboard::Escape))
        engine.GetWindow().close();*/
    }
    engine.GetWindow().clear();
    engine.Tact();
    engine.GetWindow().display();
  }
	return 0;
}

