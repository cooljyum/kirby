#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	//Bg Setting
	bg1 = new Image(L"Kirby_Resources/Map/BG1.bmp");
	bg1->SetPos(bg1->Half());

	bg2 = new Image(L"Kirby_Resources/Map/BG2.bmp");
	bg2->SetPos(bg2->Half());

	//Kirby Setting 
	kirby = new Kirby();
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));
	kirby->SetPos({ kirby->GetPos().x + KIRBY_START_OFFSET, kirby->GetPos().y });
	kirby->SetHitAudioKey("Hit");

	//Camera Setting
	CAM->SetTarget(kirby);
	CAM->SetOffset(CENTER_X, 550.0f);
	CAM->SetMapRect(bg1);

	//Load monster data from a CSV file
	DataManager::Get()->LoadData("Kirby_Resources/Monster/MonsterData.csv", 1);
	FOR(DataManager::Get()->GetMapSize())
	{
		MonsterManager::Get()->SpawnMonsters(DataManager::Get()->GetMapData(i));
		MonsterManager::Get()->SetTarget(kirby);
		MonsterManager::Get()->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));
	}

	//MapItem Setting
	Texture* grass1Tex = Texture::Add(L"Kirby_Resources/Map/Grass1.bmp", 1, 4, true);
	MapItemManager::Get()->Add("Grass1", 10, grass1Tex, 0.3f);
	MapItemManager::Get()->Play("Grass1", { 548.0f, 450.0f});

	Texture* grass2Tex = Texture::Add(L"Kirby_Resources/Map/Grass2.bmp", 1, 4, true);
	MapItemManager::Get()->Add("Grass2", 10, grass2Tex, 0.3f);
	MapItemManager::Get()->Play("Grass2", { 2090.0f, 290.0f });

	//kirby->SetPos({ 3000.0f, 380.0f }); //위치 테스트용  //쓸모 x
	Texture* doorTex = Texture::Add(L"Kirby_Resources/Map/Door.bmp",1,1,true);
	MapItemManager::Get()->Add("Door", 10, doorTex);
	MapItemManager::Get()->Play("Door", { 3350.0f, 380.0f });

	MapItemManager::Get()->Play("Grass1", { 3000.0f, 400.0f });

	//MapItem Effect Setting
	Texture* dossDoorEffTex = Texture::Add(L"Kirby_Resources/Map/BossDoorEffect.bmp", 5, 1, true);
	EffectManager::Get()->Add("BossDoorEffect", 10, dossDoorEffTex, 1.0f, true);
	EffectManager::Get()->Play("BossDoorEffect", { 3348.0f, 320.0f });

	//Effect Setting
	Texture* kirbyStarEffTex = Texture::Add(L"Kirby_Resources/Effect/Effect_Right.bmp", 10, 6, true);
	EffectManager::Get()->Add("KirbyStarEffect", 50, kirbyStarEffTex, 1.0f, false, 14, 16);

	Texture* kirbyInhaleEffTexLeft = Texture::Add(L"Kirby_Resources/Effect/Effect_Inhale_Left.bmp", 5, 1, true);
	EffectManager::Get()->Add("KirbyInhaleEffectL", 1, kirbyInhaleEffTexLeft, 1.0f, false, 0, 1);

	Texture* kirbyInhaleEffTexRight = Texture::Add(L"Kirby_Resources/Effect/Effect_Inhale_Right.bmp", 5, 1, true);
	EffectManager::Get()->Add("KirbyInhaleEffectR", 1, kirbyInhaleEffTexRight, 1.0f, false, 0, 1);

	Texture* kirbyBreathEffTexLeft = Texture::Add(L"Kirby_Resources/Effect/Effect_Left.bmp", 10, 6, true);
	EffectManager::Get()->Add("KirbyBreathEffectL", 1, kirbyBreathEffTexLeft, 1.5f, false, 0, 5);

	Texture* kirbyBreathEffTexRight = Texture::Add(L"Kirby_Resources/Effect/Effect_Right.bmp", 10, 6, true);
	EffectManager::Get()->Add("KirbyBreathEffectR", 1, kirbyBreathEffTexRight, 1.5f, false, 0, 5);

	//Sound Setting
	CreateSound();
}

MainScene::~MainScene()
{
	delete bg1;
	delete bg2;
	delete kirby;
	MapItemManager::Delete();
	MonsterManager::Delete();
	EffectManager::Delete();
}

void MainScene::Update()
{
	kirby->Update();

	MonsterManager::Get()->Update();
	MapItemManager::Get()->Update();
	EffectManager::Get()->Update();
}

void MainScene::Render(HDC hdc)
{
	//Render 순서 중요
	bg1->CamRender(hdc);

	MapItemManager::Get()->Render(hdc);

	bg2->CamRender(hdc);

	MonsterManager::Get()->Render(hdc);

	kirby->Render(hdc);

	EffectManager::Get()->Render(hdc);
}

void MainScene::CreateSound()
{
	//Audip
	//Bgm
	SOUND->Add("BGM1", "Kirby_Resources/Sound/Stage1BGM.wav", true);

	//Kirby
	SOUND->Add("Jump", "Kirby_Resources/Sound/Jump.wav");
	SOUND->Add("Fly", "Kirby_Resources/Sound/Fly.wav");
	SOUND->Add("Attack", "Kirby_Resources/Sound/Attack.mp3");
	SOUND->Add("Hit", "Kirby_Resources/Sound/Hit.wav");
	SOUND->Add("Die", "Kirby_Resources/Sound/Die.wav");
	SOUND->Add("StarBullet", "Kirby_Resources/Sound/StarBullet.wav");
	SOUND->Add("Breath", "Kirby_Resources/Sound/Breath.wav");

	//Monster
	SOUND->Add("MonsterDie", "Kirby_Resources/Sound/MonsterDie.wav");

	//MapItem
	SOUND->Add("Door", "Kirby_Resources/Sound/Door.wav");

}

void MainScene::Start()
{
	SOUND->Play("BGM1", 0.2f);

	//MapItem
	MapItemManager::Get()->Play("BossDoorEffect", { 3348.0f, 320.0f });
}

void MainScene::End()
{
	SOUND->Stop("BGM1");
}
