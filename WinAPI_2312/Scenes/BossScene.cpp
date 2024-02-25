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

	Texture* treasureTex = Texture::Add(L"Kirby_Resources/Item/Item.bmp", 5, 7, true);
	MapItemManager::Get()->Add( "Treasure", 10, treasureTex ,1.0f, false, 15, 15 );
}

BossScene::~BossScene()
{
	delete bg1;
	delete kirby;
	delete boss;

	MapItemManager::Delete();
}

void BossScene::Update()
{
	kirby->Update();
	//boss->Update();

	MapItemManager::Get()->Update();
}

void BossScene::Render(HDC hdc)
{
	bg1->Render(hdc);
	kirby->Render(hdc);
	//boss->Render(hdc);

	MapItemManager::Get()->Render(hdc);
}

void BossScene::Start()
{
	CreateSound();
	//SOUND->Play("BossBgm");

	MapItemManager::Get()->AllActive(false);

	MapItemManager::Get()->Play("Treasure", { 100.0f, 300.0f });

	//Cam Init
	CAM->SetPos(0, 0);
	CAM->SetTarget(nullptr);
}

void BossScene::CreateSound()
{
	SOUND->Add("BossBgm", "Kirby_Resources/Sound/BossBgm.mp3", true);
}
