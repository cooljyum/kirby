#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	bg = new Image(L"Kirby_Resources/Map/BackGround1.bmp");
	bg->SetPos(CENTER);

	stage1 = new Image(L"Kirby_Resources/Map/Stage1.bmp",1,1,true, WHITE);
	stage1->SetPos(CENTER);

	kirby = new Kirby();
	kirby->SetPos(CENTER);
}

MainScene::~MainScene()
{
	delete bg;
	delete stage1;
	delete kirby;
}

void MainScene::Update()
{
	kirby->Update();
}

void MainScene::Render(HDC hdc)
{
	bg->Render(hdc);
	stage1->Render(hdc);
	kirby->Render(hdc);
}
