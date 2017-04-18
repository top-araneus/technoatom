using namespace std;
#include <SFML/Graphics.hpp>
using namespace sf;
#include <iostream>
#include <../utils/print.h>
#include <../ALU/ALU/alu.h>
#include <../stack/stack/stack.h>
#include <../stack/stack/smart_ptr.h>
#include <refpoint.h>
#include <GameObjects.h>

int main()
{
	RenderWindow window(sf::VideoMode(800, 600), "Lev hodit po trave");
    ReferenceFrame mainFrame(0,0,800,600);

        print("frame width: /#, frame height: /#", mainFrame.size_.x_, mainFrame.size_.y_);
    Texture grass;
    grass.loadFromFile("images/grass.png");

    Sprite grassSprite;
    grassSprite.setTexture(grass);
    grassSprite.setTextureRect(IntRect(0, 0, 128, 128));
	grassSprite.setPosition(mainFrame.GetX(), mainFrame.GetY());


	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(250, 250);

	float CurrentFrame = 0;//хранит текущий кадр
	Clock clock;

	while (window.isOpen())
	{

        grassSprite.setPosition(mainFrame.GetX(), mainFrame.GetY());
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
            if ((int)(time*800) % 10 == 0)
                {
			mainFrame.SetX(mainFrame.GetX()-2);
			herosprite.setPosition(herosprite.getPosition().x - 2, herosprite.getPosition().y);
                }
		}

		if (Keyboard::isKeyPressed(Keyboard::Right)) {
                if ((int)(time*800) % 10 == 0)
                {
			mainFrame.SetX(mainFrame.GetX()+2);
			herosprite.setPosition(herosprite.getPosition().x + 2, herosprite.getPosition().y);
                }

		}


		if (Keyboard::isKeyPressed(Keyboard::Up)) {
                if ((int)(time*800) % 10 == 0)
                {
			mainFrame.SetY(mainFrame.GetY()-2);
			herosprite.setPosition(herosprite.getPosition().x, herosprite.getPosition().y - 2);
                }
		}

		if (Keyboard::isKeyPressed(Keyboard::Down)) {
                if ((int)(time*800) % 10 == 0)
                {
			mainFrame.SetY(mainFrame.GetY()+2);
			herosprite.setPosition(herosprite.getPosition().x, herosprite.getPosition().y + 2);
                }
		}
		///////////////////////////////////////////Управление персонажем с анимацией////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::A)) { //если нажата клавиша стрелка влево или англ буква А
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(-0.1*time, 0);//происходит само движение персонажа влево
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96

			herosprite.move(0.1*time, 0);//происходит само движение персонажа вправо

		}


		if (Keyboard::isKeyPressed(Keyboard::W)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, -0.1*time);//происходит само движение персонажа вверх
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			CurrentFrame += 0.005*time; //служит для прохождения по "кадрам". переменная доходит до трех суммируя произведение времени и скорости. изменив 0.005 можно изменить скорость анимации
			if (CurrentFrame > 3) CurrentFrame -= 3; //проходимся по кадрам с первого по третий включительно. если пришли к третьему кадру - откидываемся назад.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //проходимся по координатам Х. получается 96,96*2,96*3 и опять 96
			herosprite.move(0, 0.1*time);//происходит само движение персонажа вниз
		}

		window.clear();

		while (grassSprite.getPosition().y < mainFrame.GetY()+mainFrame.size_.y_)
        {
            while (grassSprite.getPosition().x < mainFrame.GetX()+mainFrame.size_.x_)
            {
                window.draw(grassSprite);
                grassSprite.setPosition(grassSprite.getPosition().x+128, grassSprite.getPosition().y);
            }
            grassSprite.setPosition(mainFrame.GetX(), grassSprite.getPosition().y+128);
        }
       // window.draw(grassSprite);
		window.draw(herosprite);
		window.display();
	}

	return 0;
}
