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
    ReferenceFrame mainFrame(-((TILES_AT_LINE + 1) * CellWidth / 4),-((TILES_AT_LINE + 1) * CellHeight / 4),800,600);

        print("frame width: /#, frame height: /#", mainFrame.size_.x_, mainFrame.size_.y_);
  /*  Texture grass;
    grass.loadFromFile("images/grass.png");
*/
    Texture isograss;
    isograss.loadFromFile("images/isograss.png");
    Sprite isosprite;
    isosprite.setTexture(isograss);
    isosprite.setTextureRect(IntRect(0,0,CellWidth,CellHeight));
    isosprite.setPosition(mainFrame.GetX(), mainFrame.GetY());
    /*
    Sprite grassSprite;
    grassSprite.setTexture(grass);
    grassSprite.setTextureRect(IntRect(0, 0, 128, 128));
	grassSprite.setPosition(mainFrame.GetX(), mainFrame.GetY());*/


	Texture herotexture;
	herotexture.loadFromFile("images/hero.png");

	Sprite herosprite;
	herosprite.setTexture(herotexture);
	herosprite.setTextureRect(IntRect(0, 192, 96, 96));
	herosprite.setPosition(250, 250);

	float CurrentFrame = 0;//������ ������� ����
	Clock clock;

	while (window.isOpen())
	{

        isosprite.setPosition(mainFrame.GetX(), mainFrame.GetY() + (CellHeight / 2) * TILES_AT_LINE);
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

		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::Left)) { //���� ������ ������� ������� ����� ��� ���� ����� �
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
		///////////////////////////////////////////���������� ���������� � ���������////////////////////////////////////////////////////////////////////////
		if (Keyboard::isKeyPressed(Keyboard::A)) { //���� ������ ������� ������� ����� ��� ���� ����� �
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 96, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(-0.1*time, 0);//���������� ���� �������� ��������� �����
		}

		if (Keyboard::isKeyPressed(Keyboard::D)) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 192, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96

			herosprite.move(0.1*time, 0);//���������� ���� �������� ��������� ������

		}


		if (Keyboard::isKeyPressed(Keyboard::W)) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 288, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(0, -0.1*time);//���������� ���� �������� ��������� �����
		}

		if (Keyboard::isKeyPressed(Keyboard::S)) {
			CurrentFrame += 0.005*time; //������ ��� ����������� �� "������". ���������� ������� �� ���� �������� ������������ ������� � ��������. ������� 0.005 ����� �������� �������� ��������
			if (CurrentFrame > 3) CurrentFrame -= 3; //���������� �� ������ � ������� �� ������ ������������. ���� ������ � �������� ����� - ������������ �����.
			herosprite.setTextureRect(IntRect(96 * int(CurrentFrame), 0, 96, 96)); //���������� �� ����������� �. ���������� 96,96*2,96*3 � ����� 96
			herosprite.move(0, 0.1*time);//���������� ���� �������� ��������� ����
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

        for (int i=0; i<TILES_AT_LINE; ++i)
        {
            for (int j=0; j<TILES_AT_LINE; ++j)
                {
                    window.draw(isosprite);
                    isosprite.setPosition(isosprite.getPosition().x + CellWidth / 2, isosprite.getPosition().y - CellHeight / 2);
                }
            isosprite.setPosition(mainFrame.GetX() + (CellWidth / 2) * i, mainFrame.GetY() + (CellHeight / 2) * (TILES_AT_LINE + i));
        }
       // window.draw(grassSprite);
		window.draw(herosprite);
		window.display();
	}

	return 0;
}