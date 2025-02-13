#include "Framework.h"

#include "Scenes/IntroScene.h"
#include "Scenes/MainScene.h"
#include "Scenes/BossScene.h"
#include "Scenes/EndScene.h"


GameManager::GameManager()
{
	hdc = GetDC(hWnd);

	backDC = CreateCompatibleDC(hdc);
	backBitmap = CreateCompatibleBitmap(hdc, SCREEN_WIDTH, SCREEN_HEIGHT);
	SelectObject(backDC, backBitmap);	

	SetBkMode(backDC, TRANSPARENT);

	Create();
	
	SCENE->Add("Intro", new IntroScene());
	SCENE->Add("Start", new MainScene()); 
	SCENE->Add("Boss", new BossScene());
	SCENE->Add("End", new EndScene());

	SCENE->ChangeScene("Intro");
}

GameManager::~GameManager()
{
	Delete();
}

void GameManager::Update()
{
	Keyboard::Get()->Update();
	Timer::Get()->Update();

	if (KEY->Down(VK_F3))
		Rect::OnDraw();

	SOUND->Update();
	SCENE->Update();

	CAM->Update();

	InvalidateRect(hWnd, nullptr, false);

}

void GameManager::Render()
{
	PatBlt(backDC, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, WHITENESS);

	SCENE->Render(backDC);

	Timer::Get()->Render(backDC);

	BitBlt(hdc, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT,
		backDC, 0, 0, SRCCOPY);
}

void GameManager::Create()
{
	Keyboard::Get();
	Timer::Get();
	Rect::CreatePens();
	Camera::Get();
}

void GameManager::Delete()
{
	Keyboard::Delete();
	Timer::Delete();
	Rect::DeletePens();
	Texture::Delete();
	SceneManager::Delete();
	Camera::Delete();
}
