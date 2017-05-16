#ifndef FACTORY_H
#define FACTORY_H
#include "gameobjects.h"
#include <SFML/Graphics.hpp>
#include "constants.h"
class Factory
{
  public:
    static GameObject* CreateCharacter(const int object_code, const LinearVector<int>& grid_coords, Engine& engine)
    {
      if(object_code == kPlayerId)
      {
        Texture player_texture;
        player_texture.loadFromFile(kPathToPlayerTexture);
        Player* result = new Player(engine.GetWindow(), engine.GetMap(), kStandartSpriteSizeOfPlayer, player_texture,
                                    grid_coords, engine.GetFrame(), kNumOfPlayerFrames, kNumOfPlayerStates);
        engine.AddObject(*result);
        return result;
      }
      else if(object_code == kEnemyId)
      {
        Texture enemy_texture;
        enemy_texture.loadFromFile(kPathToEnemyTexture);
        Enemy* result = new Enemy(engine.GetWindow(), engine.GetMap(), kStandartSpriteSizeOfEnemy, enemy_texture,
                                    grid_coords, engine.GetFrame(), kNumOfEnemyFrames, kNumOfEnemyStates);
        engine.AddObject(*result);
        return result;
      }
      else
      {
        print("Object: /# is not created", object_code);
        return nullptr;
      }
    }
};

#endif
