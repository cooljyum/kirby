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

	//monster = new Monster();
	//monster->SetPos(SCREEN_WIDTH+500, kirby->Bottom());
	//monster->SetTarget(kirby);

	DataManager::Get()->LoadData("Kirby_Resources/Monster/MonsterData.csv", 1);
	FOR(DataManager::Get()->GetMapSize())
	{

		MonsterManager::Get()->SpawnMonsters(DataManager::Get()->GetMapData(i));
		MonsterManager::Get()->SetTarget(kirby);
		//monsterManager = new MonsterManager(DataManager::Get()->GetMapData(i));
		//monsterManager->SetTarget(kirby);
		//map->SetPos(Vector2::Right() * i * SCREEN_WIDTH);
		//maps.push_back(map);
	}
	boss = new Boss();
	boss->SetPos(SCREEN_WIDTH, kirby->Bottom());
	boss->SetTarget(kirby);
	boss->SetLandTexture(Texture::Add(L"Kirby_Resources/Map/Land.bmp"));
}

MainScene::~MainScene()
{
	delete bg1;
	delete bg2;
	delete kirby;
	delete boss;
	MonsterManager::Delete();
}

void MainScene::Update()
{
	kirby->Update();
	//monster->Update();
	boss->Update();
	//MonsterManager::Get()->Update();
}

void MainScene::Render(HDC hdc)
{
	bg1->CamRender(hdc);
	bg2->CamRender(hdc);
	kirby->Render(hdc);
	//monster->Render(hdc);
	boss->Render(hdc);

	//MonsterManager::Get()->Render(hdc);
}
