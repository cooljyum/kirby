#include "Framework.h"
#include "MainScene.h"

MainScene::MainScene()
{
	bg1 = new Image(L"Kirby_Resources/Map/BG1.bmp");
	bg1->SetPos(bg1->Half());

	bg2 = new Image(L"Kirby_Resources/Map/BG2.bmp");
	bg2->SetPos(bg2->Half());

	kirby = new Kirby();
	kirby->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));

	CAM->SetTarget(kirby);
	CAM->SetOffset(CENTER_X, 550.0f);
	CAM->SetMapRect(bg1);

	DataManager::Get()->LoadData("Kirby_Resources/Monster/MonsterData.csv", 1);
	FOR(DataManager::Get()->GetMapSize())
	{
		MonsterManager::Get()->SpawnMonsters(DataManager::Get()->GetMapData(i));
		MonsterManager::Get()->SetTarget(kirby);
	}

	Texture* grass1Tex = Texture::Add(L"Kirby_Resources/Map/Grass1.bmp", 1, 4, true);
	MapItemManager::Get()->Add("Grass1", 10, grass1Tex, 0.3f);
	MapItemManager::Get()->Play("Grass1", { 548.0f, 450.0f});

	Texture* grass2Tex = Texture::Add(L"Kirby_Resources/Map/Grass2.bmp", 1, 4, true);
	MapItemManager::Get()->Add("Grass2", 10, grass2Tex, 0.3f);
	MapItemManager::Get()->Play("Grass2", { 2090.0f, 290.0f });

	//kirby->SetPos({ 3000.0f, 380.0f });
	Texture* doorTex = Texture::Add(L"Kirby_Resources/Map/Door.bmp",1,1,true);
	MapItemManager::Get()->Add("Door", 10, doorTex);
	MapItemManager::Get()->Play("Door", { 3350.0f, 380.0f });

	MapItemManager::Get()->Play("Grass1", { 3000.0f, 400.0f });

	Texture* dossDoorEffTex = Texture::Add(L"Kirby_Resources/Map/BossDoorEffect.bmp", 5, 1, true);
	EffectManager::Get()->Add("BossDoorEffect", 10, dossDoorEffTex, 1.0f, true);
	EffectManager::Get()->Play("BossDoorEffect", { 3348.0f, 320.0f });

	Texture* m = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
	EffectManager::Get()->Add("m", 10, m, 1.0f, true);
	//EffectManager::Get()->Play("m", { 1450.0f, 470.0f });
	//EffectManager::Get()->Play("m", { 2700.0f, 430.0f });
	//EffectManager::Get()->Play("m", { 3000.0f, 420.0f });
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
	MapItemManager::Get()->Update();
}

void MainScene::Render(HDC hdc)
{
	bg1->CamRender(hdc);
	MapItemManager::Get()->Render(hdc);
	bg2->CamRender(hdc);

	kirby->Render(hdc);

	MonsterManager::Get()->Render(hdc);

	EffectManager::Get()->Render(hdc);
}
