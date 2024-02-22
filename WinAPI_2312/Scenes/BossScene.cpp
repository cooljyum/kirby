#include "Framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	bg1 = new Image(L"Kirby_Resources/Map/BossStage1.bmp");
	bg1->SetPos(bg1->Half());

	bg2 = new Image(L"Kirby_Resources/Map/BossStage2.bmp");
	bg2->SetPos(bg2->Half());

	kirby = new Kirby();
	kirby->SetPos(CENTER);
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));

	CAM->SetTarget(kirby);
	CAM->SetOffset(CENTER_X, 550.0f);

	CAM->SetMapRect(bg1);

	boss = new Boss();
	boss->SetPos(SCREEN_WIDTH, kirby->Bottom());
	boss->SetTarget(kirby);
	boss->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));
}

BossScene::~BossScene()
{
	delete bg1;
	delete bg2;
	delete kirby;
	delete boss;
}

void BossScene::Update()
{
	kirby->Update();
	boss->Update();


	if (KEY->Down(VK_F3))
		SCENE->ChangeScene("Action");
}

void BossScene::Render(HDC hdc)
{
	bg1->CamRender(hdc);
	bg2->CamRender(hdc);
	kirby->Render(hdc);
	boss->Render(hdc);
}
