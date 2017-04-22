

using namespace std;
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
using namespace sf;
#include <iostream>
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refpoint.h>
#include <GameObjects.h>
#include <Engine.h>

int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Proekt Lev Protiv");
    Engine engine(&window);
    //ReferenceFrame mainFrame(-((TILES_AT_LINE + 1) * CellWidth / 4),-((TILES_AT_LINE + 1) * CellHeight / 4),800,600);
    window.setFramerateLimit(30);
    window.setVerticalSyncEnabled(true);
        //print("frame width: /#, frame height: /#", engine.getFrame().size_.x_, engine.getFrame().size_.y_);
  /*  Texture grass;
    grass.loadFromFile("images/grass.png");
*/


    //MapType mapArray = InitializeMap();

    Music backgroundMusic;
    backgroundMusic.openFromFile("sound/mishka.mp3");
    backgroundMusic.setLoop(true);
    backgroundMusic.play();
/*
    Texture isograss;
    isograss.loadFromFile("images/grass2.png");
    Sprite isosprite;
    isosprite.setTexture(isograss);
    isosprite.setTextureRect(IntRect(0,0,CellWidth,CellHeight));
    isosprite.setPosition(mainFrame.GetX(), mainFrame.GetY());*/
    /*
    Sprite grassSprite;
    grassSprite.setTexture(grass);
    grassSprite.setTextureRect(IntRect(0, 0, 128, 128));
	grassSprite.setPosition(mainFrame.GetX(), mainFrame.GetY());*/


	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Texture goptexture;
	goptexture.loadFromFile("images/gopnik1.png");



	Texture kisatexture;
	kisatexture.loadFromFile("images/kisa.png");

/*	Player kisa(&window,  &(engine.getMap()), LinearVector<int>(128,64), kisatexture,
             LinearVector<int>(1,0), &(engine.getFrame()), 1, 1);
	Player player(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(0,1), &(engine.getFrame()), 2, 1);
	Player kisa2(&window,  &(engine.getMap()), LinearVector<int>(128,64), kisatexture,
             LinearVector<int>(2,7), &(engine.getFrame()), 1, 1);
	Player player2(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(7,2), &(engine.getFrame()), 2, 1);
	Player kisa3(&window,  &(engine.getMap()), LinearVector<int>(128,64), kisatexture,
             LinearVector<int>(7,9), &(engine.getFrame()), 1, 1);
	Player player3(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(9,7), &(engine.getFrame()), 2, 1);

	engine.AddObject(&kisa);
	engine.AddObject(&player);
	engine.AddObject(&kisa2);
	engine.AddObject(&player2);
	engine.AddObject(&kisa3);
	engine.AddObject(&player3);*/

	Array<Player*> gops(TILES_AT_LINE*TILES_AT_LINE);
	for (int i=0; i<TILES_AT_LINE*TILES_AT_LINE; ++i)
    {
        if ((i/TILES_AT_LINE == 5) || (i%TILES_AT_LINE == 5))
        {gops[i] = new Player(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(i/TILES_AT_LINE,i%TILES_AT_LINE), &(engine.getFrame()), 2, 1);

        engine.AddObject(gops[i]);}
        else gops[i] = nullptr;
    }
    Player gopnik(&window, &(engine.getMap()), LinearVector<int>(128,192), goptexture,
             LinearVector<int>(7,2), &(engine.getFrame()), 2, 1);
    engine.AddObject(&gopnik);
	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(250, 250);

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{
        int cnt = 0;
        //isosprite.setPosition(engine.getFrame().GetX(), engine.getFrame().GetY() + (CellHeight / 2) * TILES_AT_LINE);
        //grassSprite.setPosition(mainFrame.GetX(), mainFrame.GetY()+16*10);
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time = time / 800;


		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) { //если нажата клавиша стрелка влево или англ буква А
          /*  if ((int)(time*800) % 30 == 0)
                {*/
            engine.getFrame().SetX(engine.getFrame().GetX()-5);
			herosprite.setPosition(herosprite.getPosition().x - 5, herosprite.getPosition().y);
           /*     }*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
          /*      if ((int)(time*800) % 20 == 0)
                {*/
			engine.getFrame().SetX(engine.getFrame().GetX()+5);
			herosprite.setPosition(herosprite.getPosition().x + 5, herosprite.getPosition().y);
             /*   }*/

		}
        if (Keyboard::isKeyPressed(Keyboard::H))
        {
			gopnik.SetVelocity(LinearVector<int>(-3, 0));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::K))
        {
			gopnik.SetVelocity(LinearVector<int>(3, 0));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::U))
        {
			gopnik.SetVelocity(LinearVector<int>(0, -3));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else if (Keyboard::isKeyPressed(Keyboard::J))
        {
			gopnik.SetVelocity(LinearVector<int>(0, 3));
			CurrentFrame += 0.0025*time;
			gopnik.SetFrame((int)CurrentFrame % 2);
        }
        else
        {
			gopnik.SetVelocity(LinearVector<int>(0, 0));
			gopnik.SetFrame(0);
        }

		if (Keyboard::isKeyPressed(Keyboard::Up)) {
            /*    if ((int)(time*800) % 20 == 0)
                {*/
			engine.getFrame().SetY(engine.getFrame().GetY()-5);
			herosprite.setPosition(herosprite.getPosition().x, herosprite.getPosition().y - 5);
             /*   }*/
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
             /*   if ((int)(time*800) % 20 == 0)
                {*/
			engine.getFrame().SetY(engine.getFrame().GetY()+5);
			herosprite.setPosition(herosprite.getPosition().x, herosprite.getPosition().y + 5);
            /*    }*/
		}
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::A)) { //если нажата клавиша стрелка влево или англ буква А
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			//if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * (int(CurrentFrame)%3), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//происходит само движение персонажа влево
			//mainFrame.SetX(-((TILES_AT_LINE + 1) * CellWidth / 4)+herosprite.getPosition().x-0.1*time);
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			//if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * (int(CurrentFrame)%3), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

			herosprite.move(0.1*time, 0);//происходит само движение персонажа вправо
			//mainFrame.SetX(-((TILES_AT_LINE + 1) * CellWidth / 4)+herosprite.getPosition().x+0.1*time);

		}


		if (Keyboard::isKeyPressed(Keyboard::W)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			//if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * (int(CurrentFrame)%3), 288, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, -0.1*time);//происходит само движение персонажа вверх
			//mainFrame.SetY(-((TILES_AT_LINE + 1) * CellHeight / 4)+herosprite.getPosition().y-0.1*time);
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			//if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * (int(CurrentFrame)%3), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, 0.1*time);//происходит само движение персонажа вниз
			//mainFrame.SetY(-((TILES_AT_LINE + 1) * CellHeight / 4)+herosprite.getPosition().y+0.1*time);
		}

		window.clear();
/*
		while (grassSprite.getPosition().y < mainFrame.GetY()+mainFrame.size_.y_)
        {
            while (grassSprite.getPosition().x < mainFrame.GetX()+mainFrame.size_.x_)
            {
                window.draw(grassSprite);
                grassSprite.setPosition(grassSprite.getPosition().x+128, grassSprite.getPosition().y);
            }
            grassSprite.setPosition(mainFrame.GetX(), grassSprite.getPosition().y+128);
        }*/
        engine.MoveObjects();
        engine.DrawGround();

  /*      for (int i=0; i<TILES_AT_LINE; ++i)
        {
            isosprite.setPosition(mainFrame.GetX() + (CellWidth / 2) * i, mainFrame.GetY() + (CellHeight / 2) * (TILES_AT_LINE + i));
            for (int j=0; j<TILES_AT_LINE; ++j)
                {
                    window.draw(isosprite);
                    isosprite.setPosition(isosprite.getPosition().x + CellWidth / 2, isosprite.getPosition().y - CellHeight / 2);
                }
        }*/
       // window.draw(grassSprite);
		window.draw(herosprite);
        //player.Draw();
        for (int i=0; i<TILES_AT_LINE; ++i)
            for (int j=0; j<TILES_AT_LINE; ++j)
                if (!(engine.getMap()[i][j] == nullptr ))
                    engine.getMap()[i][j]->Draw();

        engine.DrawObjects();
	//	if (Keyboard::isKeyPressed(Keyboard::K)) {


   /*     for (int i=0; i<TILES_AT_LINE*TILES_AT_LINE; ++i)
        {
            if (gops[i] != nullptr)
                gops[i]->SetFrame((int)CurrentFrame % 2);
        }*/

		window.display();
	}
	return 0;
}
