#include "Framework.h"
#include "BossScene.h"

BossScene::BossScene()
{
	bg1 = new Image(L"Kirby_Resources/Map/BossStageBg.bmp");
	bg1->SetPos(bg1->Half());

	kirby = new Kirby();
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/BossStageLand.bmp"));

	//CAM->SetTarget(kirby);
	//CAM->SetOffset(CENTER_X, 550.0f);

	//CAM->SetMapRect(bg1);

	boss = new Boss();
	boss->SetTarget(kirby);
	boss->SetPos({ CENTER_X, kirby->Bottom()});
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
