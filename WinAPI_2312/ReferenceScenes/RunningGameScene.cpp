#include "Framework.h"
#include "RunningGameScene.h"

RunningGameScene::RunningGameScene()
{
	DataManager::Get()->LoadData("Textdata/MapData1.csv", 1);
	DataManager::Get()->LoadData("Textdata/MapData2.csv", 2);
	DataManager::Get()->LoadData("Textdata/MapData3.csv", 3);
	DataManager::Get()->LoadData("Textdata/MapData4.csv", 4);
	DataManager::Get()->LoadData("Textdata/MapData5.csv", 5);

	

	//basicCookie = new BasicCookie();
	//angelCookie = new AngelCookie();

	//cookie = basicCookie;
	//
	//cookie = angelCookie;

	
}

RunningGameScene::~RunningGameScene()
{
	DataManager::Delete();	
}

void RunningGameScene::Update()
{
	for (Background* bg : backgrounds)
		bg->Update();

	MapManager::Get()->Update();
	MapManager::Get()->IsJellyCollision(cookie);

	cookie->Update();

	if (KEY->Down(VK_F3))
		SCENE->ChangeScene("Action");
}

void RunningGameScene::Render(HDC hdc)
{
	for (Background* bg : backgrounds)
		bg->Render(hdc);

	MapManager::Get()->Render(hdc);

	cookie->Render(hdc);
}

void RunningGameScene::Start()
{
	cookie = new Cookie();

	MapManager::Get();
	CreateBG();
}

void RunningGameScene::End()
{
	delete cookie;

	for (Background* bg : backgrounds)
		delete bg;

	backgrounds.clear();

	MapManager::Delete();
}

void RunningGameScene::CreateBG()
{
	Background* background = new Background(0.1f, CENTER);

	background->AddObject(new Image(L"Textures/Running/bg1.bmp"));
	background->AddObject(new Image(L"Textures/Running/bg1.bmp"));

	background->SetStartPos();

	backgrounds.push_back(background);

	background = new Background(0.15f, CENTER);

	background->AddObject(new Image(L"Textures/Running/bg3.bmp", 1, 1, true, WHITE));
	background->AddObject(new Image(L"Textures/Running/bg3.bmp", 1, 1, true, WHITE));

	background->SetStartPos();

	backgrounds.push_back(background);

	background = new Background(0.2f, CENTER);

	background->AddObject(new Image(L"Textures/Running/bg4.bmp", 1, 1, true, WHITE));
	background->AddObject(new Image(L"Textures/Running/bg4.bmp", 1, 1, true, WHITE));

	background->SetStartPos();

	backgrounds.push_back(background);
}
