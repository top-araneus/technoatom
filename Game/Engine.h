#ifndef ENGINE_H
#define ENGINE_H

#include "GameObjects.h"
using namespace sf;
class Engine
{
public:
    Engine(RenderWindow* window)
    {
        window_ = window;
        mainFrame_ = ReferenceFrame(-((TILES_AT_LINE + 1) * CellWidth / 4),-((TILES_AT_LINE + 1) * CellHeight / 4),800,600);
        map_ = InitializeMap();
        ground_ = InitializeGround();
        groundTexture_.loadFromFile("images/debuggrid.png");
        numOfGrounds_ = groundTexture_.getSize().x / CellWidth;
        groundSprite_.setTexture(groundTexture_);
        groundSprite_.setTextureRect(IntRect(0, 0, CellWidth, CellHeight));
       // groundSprite_.setOrigin(CellWidth/2, CellHeight/2);
    }
    ~Engine()
    {

    }

    MapType InitializeMap()
    {
        //Unique_ptr<MapType> mapArray = new MapType(TILES_AT_LINE);
        MapType mapArray(TILES_AT_LINE);
        for(int i=0; i<TILES_AT_LINE; ++i)
        {
            mapArray[i] = Array<GameObject*>(TILES_AT_LINE);
            for (int j=0; j<TILES_AT_LINE; ++j)
            {
                mapArray[i][j] = nullptr;
            }
        }
        return mapArray;
    }

    Array<Array<unsigned char>> InitializeGround()
    {
        Array<Array<unsigned char>> groundArray(TILES_AT_LINE);
        for(int i=0; i<TILES_AT_LINE; ++i)
        {
            groundArray[i] = Array<unsigned char>(TILES_AT_LINE);
            for (int j=0; j<TILES_AT_LINE; ++j)
            {
                groundArray[i][j] = rand()%2;
            }
        }
        return groundArray;
    }

    void DrawGround()
    {
        for (int i=0; i<TILES_AT_LINE; ++i)
        {
            groundSprite_.setPosition(mainFrame_.GetX() + (CellWidth / 2) * i, mainFrame_.GetY() + (CellHeight / 2) * (TILES_AT_LINE + i));
            for (int j=0; j<TILES_AT_LINE; ++j)
                {
                    groundSprite_.setTextureRect(IntRect(CellWidth*ground_[i][j],0,CellWidth, CellHeight));
                    window_->draw(groundSprite_);
                    groundSprite_.setPosition(groundSprite_.getPosition().x + CellWidth / 2, groundSprite_.getPosition().y - CellHeight / 2);
                }
        }
    }

    void DrawObjects()
    {
        int i=0;
        int cnt=TILES_AT_LINE-1;
        int j = cnt;
        while (j>=0)
        {
            while (j<TILES_AT_LINE)
            {
                if (map_[i][j] != nullptr)
                    map_[i][j]->Draw();
                i++;
                j++;
            }
            i=0;
            cnt--;
            j = cnt;
        }
        cnt = 1;
        i = 1;
        j = 0;
        while (i<TILES_AT_LINE)
        {
            int endNum = i;
            while (j<TILES_AT_LINE-endNum)
            {
                if (map_[i][j] != nullptr)
                    map_[i][j]->Draw();
                i++;
                j++;
            }
            j=0;
            cnt++;
            i = cnt;
        }
     }

    void MoveObjects()
    {

        for (int i=0; i<TILES_AT_LINE; ++i)
        {
            for (int j=0; j<TILES_AT_LINE; ++j)
                {
                    if (map_[i][j] != nullptr)
                        map_[i][j]->Move();
                }
        }
    }

     void AddObject(GameObject* obj)
     {
         map_[obj->GetGridCoords().x_][obj->GetGridCoords().y_] = obj;
     }

    MapType& getMap()
    {
        return map_;
    }

    ReferenceFrame& getFrame()
    {
        return mainFrame_;
    }
    private:
        MapType map_;
        Array<Array<unsigned char>> ground_;
        Texture groundTexture_;
        Sprite groundSprite_;
        int numOfGrounds_;
        ReferenceFrame mainFrame_;
        RenderWindow* window_;
};

#endif // ENGINE_H
