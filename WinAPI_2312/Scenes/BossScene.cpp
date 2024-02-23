#include "Framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	//Bg Setting
	bg1 = new Image(L"Kirby_Resources/Map/BossStageBg.bmp");
	bg1->SetPos(bg1->Half());

	//Kirby Setting
	kirby = new Kirby();
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/BossStageLand.bmp"));

	//Boss Setting
	boss = new Boss(CENTER_X, kirby->Bottom(), 1000);
	boss->SetTarget(kirby);
	boss->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/BossStageLand.bmp"));
}

BossScene::~BossScene()
{
	delete bg1;
	delete kirby;
	delete boss;
}

void BossScene::Update()
{
	kirby->Update();
	boss->Update();
}

void BossScene::Render(HDC hdc)
{
	bg1->Render(hdc);
	kirby->Render(hdc);
	boss->Render(hdc);
}

void BossScene::Start()
{
	//Cam Init
	CAM->SetPos(0, 0);
	CAM->SetTarget(nullptr);
}