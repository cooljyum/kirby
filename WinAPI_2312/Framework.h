#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 100
#define WIN_START_Y 0

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define CENTER_X (SCREEN_WIDTH * 0.5f)
#define CENTER_Y (SCREEN_HEIGHT * 0.5f)

#define CENTER Vector2(CENTER_X, CENTER_Y)

#define PI 3.141592f

#define RED RGB(255, 0, 0)
#define GREEN RGB(0, 255, 0)
#define BLUE RGB(0, 0, 255)
#define YELLOW RGB(255, 255, 0)
#define CYAN RGB(0, 255, 255)
#define MAGENTA RGB(255, 0, 255)
#define WHITE RGB(255, 255, 255)
#define BLACK RGB(0, 0, 0)

#define KEY Keyboard::Get()
#define DELTA Timer::Get()->GetElapsedTime()
#define SCENE SceneManager::Get()
#define SOUND Audio::Get()
#define CAM Camera::Get()

#define FOR(n) for(int i = 0 ; i < n ; i++)

#include <windows.h>
#include <string>r
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <assert.h>

#include "Libraries/FMOD/fmod.hpp"
#pragma comment(lib, "Libraries/fmod_vc.lib")

using namespace std;

//Framework Header

#include "Math/Vector2.h"
#include "Math/Math.h"

#include "Utilities/Utility.h"
#include "Utilities/Singleton.h"
#include "Utilities/Keyboard.h"
#include "Utilities/Timer.h"
#include "Utilities/Audio.h"

#include "Render/Texture.h"
#include "Render/Animation.h"
#include "Render/Camera.h"

//Object Header

#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Image.h"
#include "Objects/Basic/Action.h"
#include "Objects/Basic/Effect.h"
#include "Objects/Basic/EffectManager.h"

#include "Objects/UI/ProgressBar.h"


#include "Objects/Character.h"

//Kirbys

//MapItems
#include "Objects/Map/MapItem.h"
#include "Objects/Map/MapItemManager.h"


//Monsters
#include "Objects/Monsters/Monster.h"
#include "Objects/Monsters/MonsterManager.h"
#include "Objects/Monsters/BossBullet.h"
#include "Objects/Monsters/HamerBoss.h"

//Kirbys
//------------ Action
//Default
#include "Objects/Kirbys/Action/Default/KirbyIdle.h"
#include "Objects/Kirbys/Action/Default/KirbyWalk.h"
#include "Objects/Kirbys/Action/Default/KirbyJump.h"
#include "Objects/Kirbys/Action/Default/KirbyJumpUp.h"
#include "Objects/Kirbys/Action/Default/KirbyJumpDown.h"
#include "Objects/Kirbys/Action/Default/KirbySit.h"
#include "Objects/Kirbys/Action/Default/KirbyInhole.h"
#include "Objects/Kirbys/Action/Default/KirbyHit.h"
#include "Objects/Kirbys/Action/Default/KirbyDie.h"

//Eat
#include "Objects/Kirbys/Action/Eat/KirbyIdleEat.h"
#include "Objects/Kirbys/Action/Eat/KirbyWalkEat.h"
#include "Objects/Kirbys/Action/Eat/KirbyJumpUpEat.h"
#include "Objects/Kirbys/Action/Eat/KirbyJumpDownEat.h"
#include "Objects/Kirbys/Action/Eat/KirbySitEat.h"
#include "Objects/Kirbys/Action/Eat/KirbyAttackEat.h"
//------------ Action End

#include "Objects/Kirbys/KirbyStarBullet.h"
#include "Objects/Kirbys/Kirby.h"

//Scene
#include "Manager/DataManager.h"
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"



extern HWND hWnd;
extern Vector2 mousePos;
extern HINSTANCE hInst;