using namespace std;
bool in_death = false;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <SFML/System/Clock.hpp>
using namespace sf;
#include "constants.h"
#include <iostream>
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refframe.h>
#include <GameObjects.h>
#include <Engine.h>

int main()
{
	RenderWindow window(sf::VideoMode(kWindowWidth, kWindowHeight), "Cyberpunk Universe", sf::Style::Close);

    Engine engine(&window);
    window.setFramerateLimit(kFrameRate);
    window.setVerticalSyncEnabled(true);


	Texture cilinder_texture;
	cilinder_texture.loadFromFile("images/cilindr.png");
	Texture cube_texture;
	cube_texture.loadFromFile("images/cub.png");


	Array<Enemy*> gops(kTilesAtLine*kTilesAtLine);
	for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
    {
        if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5) || (i/kTilesAtLine == kTilesAtLine-5)  || (i%kTilesAtLine == kTilesAtLine-5) )
        {
          gops[i] = new Enemy(&window, &(engine.getMap()), LinearVector<int>(128,192), cube_texture,
             LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), &(engine.getFrame()), 2, 1);

        engine.AddObject(gops[i]);}
        else gops[i] = nullptr;
    }
    Player cilik(&window, &(engine.getMap()), LinearVector<int>(128,192), cilinder_texture,
             LinearVector<int>(14,16), &(engine.getFrame()), 2, 1);
    engine.AddObject(&cilik);

    Enemy kubik(&window, &(engine.getMap()), LinearVector<int>(128,192), cube_texture,
             LinearVector<int>(16,14), &(engine.getFrame()), 2, 1);
    engine.AddObject(&kubik);

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{
        int cnt = 0;
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

        if (Keyboard::isKeyPressed(Keyboard::A))
        {
			cilik.SetVelocity(LinearVector<int>(-kPlayerVelocity, 0));
			CurrentFrame += 0.0025*time;
			cilik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
			cilik.SetVelocity(LinearVector<int>(kPlayerVelocity, 0));
			CurrentFrame += 0.0025*time;
			cilik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
			cilik.SetVelocity(LinearVector<int>(0, -kPlayerVelocity));
			CurrentFrame += 0.0025*time;
			cilik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
			cilik.SetVelocity(LinearVector<int>(0, kPlayerVelocity));
			CurrentFrame += 0.0025*time;
			cilik.SetFrame((int)CurrentFrame % 2);
        }
        else
        {
			cilik.SetVelocity(LinearVector<int>(0, 0));
			cilik.SetFrame(0);
        }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { //если нажата клавиша стрелка влево или англ буква А
            engine.getFrame().SetX(engine.getFrame().GetX()-kCameraVelocity);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			engine.getFrame().SetX(engine.getFrame().GetX()+kCameraVelocity);

		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			engine.getFrame().SetY(engine.getFrame().GetY()-kCameraVelocity);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			engine.getFrame().SetY(engine.getFrame().GetY()+kCameraVelocity);
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

		window.clear();
        engine.MoveAll();
        engine.DrawGround();

    engine.InteractAll();
    engine.DrawAll();
		window.display();
	}
	return 0;
}

