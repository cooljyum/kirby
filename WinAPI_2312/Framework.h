#pragma once

#include "targetver.h"
#define WIN32_LEAN_AND_MEAN

#define WIN_START_X 100
#define WIN_START_Y 0

#define SCREEN_WIDTH 1740
#define SCREEN_HEIGHT 720

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
#define CAM Camera::Get()

#define FOR(n) for(int i = 0 ; i < n ; i++)

#include <windows.h>
#include <string>
#include <vector>
#include <list>
#include <map>
#include <unordered_map>
#include <functional>
#include <fstream>
#include <assert.h>

using namespace std;

//Framework Header

#include "Math/Vector2.h"
#include "Math/Math.h"

#include "Utilities/Utility.h"
#include "Utilities/Singleton.h"
#include "Utilities/Keyboard.h"
#include "Utilities/Timer.h"

#include "Render/Texture.h"
#include "Render/Animation.h"
#include "Render/Camera.h"

//Object Header

#include "Objects/Basic/Rect.h"
#include "Objects/Basic/Image.h"
#include "Objects/Basic/Action.h"

#include "Objects/UI/ProgressBar.h"


#include "Objects/Character.h"


#include "Objects/Kirbys/KirbyIdle.h"
#include "Objects/Kirbys/KirbyWalk.h"
#include "Objects/Kirbys/KirbyRun.h"
#include "Objects/Kirbys/KirbyJump.h"
#include "Objects/Kirbys/KirbySit.h"
#include "Objects/Kirbys/Kirby.h"

//Scene
#include "Scenes/Scene.h"
#include "Manager/SceneManager.h"
#include "Manager/GameManager.h"

extern HWND hWnd;
extern Vector2 mousePos;
extern HINSTANCE hInst;