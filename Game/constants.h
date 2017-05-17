#ifndef CONSTANTS_H
#define CONSTANTS_H

//!window
const int               kCellWidth = 128;
const int               kCellHeight = 64;
const int               kTilesAtLine = 30;
const int               kFrameRate = 70;
const int               kFramesPerSec = 10;
const int               kWindowWidth = 1920;//GetSystemMetrics(SM_CXSCREEN);
const int               kWindowHeight = 1080;//GetSystemMetrics(SM_CYSCREEN);

//!engine
const time_t            kTactTime = 25;

//!camera
const int               kCameraVelocity = 10;
const int               kWindowMargin = 100;

//!id
const unsigned char     kEnemyId = 148;
const unsigned char     kPlayerId = 161;

//!player
const int               kPlayerVelocity = 7;
const time_t            kPlayerCoolDown = 25;
const int               kRangeOfPlayerAttack = 3;
const int               kPlayerHp = 100;
const LinearVector<int> kStandartSpriteSizeOfPlayer = LinearVector<int>(160,192);
const unsigned char     kNumOfPlayerStates = 1;
const unsigned char     kNumOfPlayerFrames = 4;
const char*             kPathToPlayerTexture = "images/cilindr.png";

//!enemy
const int               kEnemyVelocity = 4;
const LinearVector<int> kStandartSpriteSizeOfEnemy = LinearVector<int>(128,138);
const int               kRangeOfEnemyAttack = 1;
const unsigned char     kNumOfEnemyFrames = 1;
const unsigned char     kNumOfEnemyStates = 1;
const char*             kPathToEnemyTexture = "images/cub.png";
const int               kRangeOfVision = 4;
const time_t            kEnemyCoolDown = 500;
const int               kEnemyDamage = 5;
const int               kEnemyHp = 15;

//!ALU
const std::string       kEnemyProgram("pursuit80.bin");

#endif // CONSTANTS_H
