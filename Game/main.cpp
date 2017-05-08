

using namespace std;
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
#include <GameObjects.h>
#include <Engine.h>

int main()
{
	RenderWindow window(sf::VideoMode(1024, 768), "Cyberpunk Universe");
    Engine engine(&window);
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);


	Texture goptexture;
	goptexture.loadFromFile("images/debughero.png");



	Texture kisatexture;
	kisatexture.loadFromFile("images/kisa.png");


	Array<Player*> gops(kTilesAtLine*kTilesAtLine);
	for (int i=0; i<kTilesAtLine*kTilesAtLine; ++i)
    {
        if ((i/kTilesAtLine == 5) || (i%kTilesAtLine == 5))
        {gops[i] = new Player(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(i/kTilesAtLine,i%kTilesAtLine), &(engine.getFrame()), 2, 1);

        engine.AddObject(gops[i]);}
        else gops[i] = nullptr;
    }
    Player gopnik(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(7,2), &(engine.getFrame()), 2, 1);
    engine.AddObject(&gopnik);

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
			gopnik.SetVelocity(LinearVector<int>(-6, 0));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::D))
        {
			gopnik.SetVelocity(LinearVector<int>(6, 0));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::W))
        {
			gopnik.SetVelocity(LinearVector<int>(0, -6));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::S))
        {
			gopnik.SetVelocity(LinearVector<int>(0, 6));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else
        {
			gopnik.SetVelocity(LinearVector<int>(0, 0));
			gopnik.SetFrame(0);
        }
		if (Keyboard::isKeyPressed(Keyboard::Left)) { //если нажата клавиша стрелка влево или англ буква А
            engine.getFrame().SetX(engine.getFrame().GetX()-10);
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
			engine.getFrame().SetX(engine.getFrame().GetX()+10);

		}

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
			engine.getFrame().SetY(engine.getFrame().GetY()-10);
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
			engine.getFrame().SetY(engine.getFrame().GetY()+10);
		}


		window.clear();
        engine.MoveAll();
        engine.DrawGround();
        //player.Draw();
        for (int i=0; i<kTilesAtLine; ++i)
            for (int j=0; j<kTilesAtLine; ++j)
                if (!(engine.getMap()[i][j] == nullptr ))
                    engine.getMap()[i][j]->Draw();

        engine.DrawAll();

		window.display();
	}
	return 0;
}
