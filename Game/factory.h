#ifndef FACTORY_H
#define FACTORY_H
#include "GameObjects.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
class Factory
{
  public:
    static GameObject* CreateCharacter(int object_code, LinearVector<int> gridCoords, Engine& engine)
    {
      if(object_code == kPlayerId)
      {
        Texture player_texture;
        player_texture.loadFromFile("images/cilindr.png");
        Player* result = new Player(&(engine.GetWindow()), &(engine.getMap()), LinearVector<int>(128,192), player_texture,
                                    gridCoords, &(engine.getFrame()), kNumOfPlayerFrames, kNumOfPlayerStates);
        engine.AddObject(result);
        return result;
      }
    }
};

#endif
