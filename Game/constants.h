#ifndef CONSTANTS_H
#define CONSTANTS_H

//!window
const int               kCellWidth = 128;
const int               kCellHeight = 64;
const int               kTilesAtLine = 30;
const int               kFrameRate = 70;
const int               kFramesPerSec = 10;
const int               kWindowWidth = GetSystemMetrics(SM_CXSCREEN);
const int               kWindowHeight = GetSystemMetrics(SM_CYSCREEN);

//!engine
const time_t            kTactTime = 25;

//!camera
const int               kCameraVelocity = 10;
const int               kWindowMargin = 100;

//!id
const unsigned char     kEnemyId = 148;
const unsigned char     kPlayerId = 161;
const unsigned char     kBulletId = 184;

//!player
const int               kPlayerVelocity = 7;
const time_t            kPlayerCoolDown = 100;
const int               kRangeOfPlayerAttack = 128;
const int               kPlayerHp = 100;
const int               kXpStep = 10;
const LinearVector<int> kStandartSpriteSizeOfPlayer = LinearVector<int>(160,192);
const unsigned char     kNumOfPlayerStates = 1;
const unsigned char     kNumOfPlayerFrames = 4;
const char*             kPathToPlayerTexture = "images/cilindr.png";
const unsigned char     kPlayerWidth = 64;

//!enemy
const int               kEnemyVelocity = 4;
const LinearVector<int> kStandartSpriteSizeOfEnemy = LinearVector<int>(128,138);
const int               kRangeOfEnemyAttack = 100;
const unsigned char     kNumOfEnemyFrames = 1;
const unsigned char     kNumOfEnemyStates = 1;
const char*             kPathToEnemyTexture = "images/cub.png";
const int               kRangeOfVision = 256;
const time_t            kEnemyCoolDown = 500;
const int               kEnemyDamage = 5;
const int               kEnemyHp = 20;
const unsigned char     kEnemyWidth = 64;

//!bullet
const char*             kPathToBulletTexture = "images/bullet.png";
const int               kBulletVelocity = 30;
const LinearVector<int> kStandartSpriteSizeOfBullet = LinearVector<int>(16,16);
const unsigned char     kNumOfBulletFrames = 1;
const unsigned char     kNumOfBulletStates = 1;
const time_t            kShootCoolDown = 400;

//!ALU
const std::string       kEnemyProgram("pursuit80.bin");

//!Resources
const std::string       kFontPath("fonts/font.ttf");

//!Dialog windows
const time_t            kDebugCoolDown = 100;
const sf::Color         kDialogWindowColor = sf::Color(192,128,0,192);
const sf::Color         kButtonColor = sf::Color(255,64,64,255);
const sf::Color         kTextColor = sf::Color(255,255,255,255);
const LinearVector<int> kMenuConstraints = LinearVector<int>(350, 200);
const LinearVector<int> kMenuCoords = LinearVector<int>(kWindowWidth/2 - kMenuConstraints.x_/2,
                                                        kWindowHeight/3 - kMenuConstraints.y_/2);
const int               kDialogsMaxNumber = 20;
const int               kDialogElemsMaxNumber = 20;
#endif // CONSTANTS_H
