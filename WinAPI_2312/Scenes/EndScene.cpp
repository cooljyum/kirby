#include "Framework.h"
#include "EndScene.h"

bool EndScene::isEnd = true;

EndScene::EndScene()
{
	SOUND->Add("EndingBgm", "Kirby_Resources/Sound/Ending.mp3", true);
}

EndScene::~EndScene()
{
	FOR(endings.size())
		delete endings[i];

	delete endingImg;
	delete gameoverImg;
}

void EndScene::Update()
{
	//인트로 프레임 끝나면 시작 화면 
	if (isEnd)
	{
		//스페이스 누를 시 프레임 빠르게 재생
		if (KEY->Press(VK_RETURN))
			frameTime = FAST_FRAME_TIME;
		else
			frameTime = BASIC_FRAME_TIME;

		//프레임 재생
		if (time > frameTime)
		{
			if (cnt == endings.size())
			{
				endingImg->SetActive(true);
				CloseWindow();
				return;
			}

			if (cnt != 0) endings[cnt - 1]->SetActive(false);

			endings[cnt]->SetActive(true);
			cnt += 1;
			time -= frameTime;
		}
		time += DELTA;
	}
	else
	{
		gameoverImg->SetActive(true);
		CloseWindow();
	}
}

void EndScene::Render(HDC hdc)
{
	FOR(endings.size())
		endings[i]->Render(hdc);

	endingImg->Render(hdc);
	gameoverImg->Render(hdc);
}

void EndScene::Start()
{
	SOUND->Play("EndingBgm");
}

void EndScene::CreateIntroFrame()
{
	//Ending Setting
	for (int i = 1; i <= 11; ++i) 
	{
		wstring filePath = L"Kirby_Resources/UI/Ending/ending (" + std::to_wstring(i) + L").bmp";
		endings.push_back(new Image(filePath));
	}

	FOR(endings.size())
	{
		endings[i]->SetActive(false);
		endings[i]->SetPos(endings[i]->Half());
	}

	//End Setting
	endingImg = new Image(L"Kirby_Resources/UI/End.bmp");
	endingImg->SetPos(endingImg->Half());
	endingImg->SetActive(false);

	gameoverImg = new Image(L"Kirby_Resources/UI/Gameover.bmp");
	gameoverImg->SetPos(gameoverImg->Half());
	gameoverImg->SetActive(false);

	if (isEnd) endings[0]->SetActive(true);
}

void EndScene::CloseWindow()
{
	//창 완전히 끄기
	if (KEY->Down(VK_RETURN))
		DestroyWindow(hWnd);
}
