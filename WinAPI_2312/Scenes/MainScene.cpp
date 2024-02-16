#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	bg1 = new Image(L"Kirby_Resources/Map/BG1.bmp");
	bg1->SetPos(bg1->Half());

	bg2 = new Image(L"Kirby_Resources/Map/BG2.bmp");
	bg2->SetPos(bg2->Half());

	kirby = new Kirby();
	kirby->SetPos(CENTER);
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));

	CAM->SetTarget(kirby);
	CAM->SetOffset(CENTER_X, 550.0f);

	CAM->SetMapRect(bg1);

	monster = new Monster();
	monster->SetPos(SCREEN_WIDTH, kirby->Bottom());
	monster->SetTarget(kirby);

}

MainScene::~MainScene()
{
	delete bg1;
	delete bg2;
	delete kirby;
}

void MainScene::Update()
{
	kirby->Update();
	monster->Update();
}

void MainScene::Render(HDC hdc)
{
	bg1->CamRender(hdc);
	bg2->CamRender(hdc);
	kirby->Render(hdc);
	monster->Render(hdc);
}
