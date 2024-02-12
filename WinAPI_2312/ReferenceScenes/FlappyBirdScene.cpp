#include "Framework.h"
#include "FlappyBirdScene.h"

FlappyBirdScene::FlappyBirdScene()
{	
	SetBackground();

	kirby = new Kirby();

	JellyManager::Get();
}

FlappyBirdScene::~FlappyBirdScene()
{
	//for (Background* background : backgrounds)
	for (pair<string, Background*> background : backgrounds)
		delete background.second;

	delete kirby;

	JellyManager::Delete();
}

void FlappyBirdScene::Update()
{
	//Vector2 pos = image->GetPos();
	//pos.x -= 100 * DELTA;
	//image->SetPos(pos);
	//image->Translate(Vector2::Left() * 100 * DELTA);

	//for (Background* background : backgrounds)
	for (pair<string, Background*> background : backgrounds)
		background.second->Update();

	kirby->Update();

	JellyManager::Get()->Update();
	//JellyManager::Get()->IsCollision(kirby);

	if (backgrounds["Pipe"]->IsCollision(kirby))
	{
		MessageBox(hWnd, L"Collision", L"GameOver", MB_OK);
		DestroyWindow(hWnd);
	}	
}

void FlappyBirdScene::Render(HDC hdc)
{
	//for (Background* background : backgrounds)
	for (pair<string, Background*> background : backgrounds)
		background.second->Render(hdc);

	kirby->Render(hdc);

	JellyManager::Get()->Render(hdc);
}

void FlappyBirdScene::SetBackground()
{
	Background* backBG = new Background(50.0f, CENTER);

	backBG->AddObject(new Image(L"Textures/Back1.bmp"));
	backBG->AddObject(new Image(L"Textures/Back2.bmp"));
	backBG->AddObject(new Image(L"Textures/Back3.bmp"));
	backBG->AddObject(new Image(L"Textures/Back4.bmp"));

	backBG->SetStartPos();

	//backgrounds.push_back(backBG);
	backgrounds["Back"] = backBG;

	//Texture* landTexture = new Texture(L"Textures/land.bmp");
	Vector2 startPos;
	//startPos.x = landTexture->GetSize().x * 0.5f;
	//startPos.y = SCREEN_HEIGHT - landTexture->GetSize().y * 0.5f;
	//Background* land = new Background(100.0f, startPos);
	//FOR(3)
	//	land->AddObject(new Image(landTexture));
	//
	//land->SetStartPos();
	//
	////backgrounds.push_back(land);
	//backgrounds["Land"] = land;

	Texture* cloudTexture = new Texture(L"Textures/cloud.bmp", 1, 1, true);

	startPos.x = cloudTexture->GetSize().x * 0.5f;
	startPos.y = cloudTexture->GetSize().y * 0.5f + 100;

	Background* cloud = new Background(100.0f, startPos, Vector2(0, -50), Vector2(200, 50));

	FOR(5)
		cloud->AddObject(new Image(cloudTexture));

	cloud->SetStartPos();

	//backgrounds.push_back(cloud);
	backgrounds["Cloud"] = cloud;

	Texture* pipeUpTexture = new Texture(L"Textures/PipeUp.bmp", 1, 1, true);
	Texture* pipeDownTexture = new Texture(L"Textures/PipeDown.bmp", 1, 1, true);

	startPos.x = SCREEN_WIDTH;
	startPos.y = SCREEN_HEIGHT;

	float setInterval = 300.0f;
	float maxInterval = pipeUpTexture->GetSize().y * 0.5f - 100.0f;
	float minInterval = maxInterval - (startPos.y - setInterval) + 100.0f;

	Background* pipe = new Background(200.0f, startPos,
		Vector2(400, minInterval), Vector2(400, maxInterval), true, setInterval);;

	FOR(5)
	{
		pipe->AddObject(new Image(pipeUpTexture));
		pipe->AddObject(new Image(pipeDownTexture));
	}

	pipe->SetStartPos();

	backgrounds["Pipe"] = pipe;
}
