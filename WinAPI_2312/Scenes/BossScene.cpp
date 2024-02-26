#include "Framework.h"
#include "BossScene.h"
#include "MainScene.h"

BossScene::BossScene()
{
	CreateSound();

	//Bg Setting
	bg1 = new Image(L"Kirby_Resources/Map/BossStageBg.bmp");
	bg1->SetPos(bg1->Half());

	//Kirby Setting
	kirby = new Kirby();
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/BossStageLand.bmp"));

	//Boss Setting
	boss = new HamerBoss(CENTER_X, kirby->Bottom(), 200);
	boss->SetTarget(kirby);
	boss->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/BossStageLand.bmp"));
	boss->SetHitAudioKey("BossHit");

	Texture* treasureTex = Texture::Add(L"Kirby_Resources/Item/Item.bmp", 5, 7, true);
	MapItemManager::Get()->Add( "Treasure", 1, treasureTex ,1.0f, false, 15, 15 );

	MapItemManager::Get()->Add("TreasureOpen", 1, treasureTex, 1.0f, false, 16, 16);

	Texture* effTex = Texture::Add(L"Kirby_Resources/Effect/Effect.bmp", 10, 6, true);
	EffectManager::Get()->Add("TreasureEffect", 1, effTex, 1.0f, false , 14, 19);

	Texture* starEffect = Texture::Add(L"Kirby_Resources/Effect/Effect_Right.bmp", 10, 6, true);
	EffectManager::Get()->Add("StarEffect", 1, starEffect, 1.0f, false, 51, 59);
	
} 

BossScene::~BossScene()
{
	delete bg1;
	delete kirby;
	delete boss;

	MapItemManager::Delete();
	EffectManager::Delete();
}

void BossScene::Update()
{
	kirby->Update();
	boss->Update();

	MapItemManager::Get()->Update();
	EffectManager::Get()->Update();

	//if(!SOUND->IsPlaySound("BossBgm")) SOUND->Play("BossBgm", 0.7f);
}

void BossScene::Render(HDC hdc)
{
	bg1->Render(hdc);

	boss->Render(hdc);

	MapItemManager::Get()->Render(hdc);

	kirby->Render(hdc);

	EffectManager::Get()->Render(hdc);
}

void BossScene::Start()
{
	SOUND->Stop("StartBgm");
	SOUND->Stop("BGM1");
	SOUND->Play("BossBgm", 0.7f);

	MonsterManager::Get()->AllActive(false);
	MapItemManager::Get()->AllActive(false);

	//Cam Init
	CAM->SetPos(0, 0);
	CAM->SetTarget(nullptr);

	kirby->SetHp(MainScene::kirbyHpSave, false);
}

void BossScene::End()
{
	SOUND->Stop("BossBgm");
}

void BossScene::CreateSound()
{
	SOUND->Add("BossBgm", "Kirby_Resources/Sound/BossBgm.mp3", true);
	SOUND->Add("BossDie", "Kirby_Resources/Sound/BossDie.wav");
	SOUND->Add("BossHit", "Kirby_Resources/Sound/BossHit.wav");
	SOUND->Add("BossAttack", "Kirby_Resources/Sound/BossAttack.wav");

	SOUND->Add("KirbyEndDance", "Kirby_Resources/Sound/Ending.mp3");
}
