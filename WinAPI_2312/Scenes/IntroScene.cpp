#include "Framework.h"
#include "IntroScene.h"

IntroScene::IntroScene()
{
}

IntroScene::~IntroScene()
{
	FOR(intros.size())
		delete intros[i];

	delete startSelect;
	delete controlSelect;
	delete control;
}

void IntroScene::Update()
{
	//F2 누를시 Start로 전환 //테스트용 및 스킵용 
	if (KEY->Down(VK_F2))
		SCENE->ChangeScene("Start");

	//인트로 프레임 끝나면 시작 화면 
	if (cnt >= intros.size()) 
	{
		if (!openControl) 
		{
			if (KEY->Down('A'))
			{
				controlSelect->SetActive(true);
				startSelect->SetActive(false);
				isStart = false;
			}

			if (KEY->Down('D'))
			{
				startSelect->SetActive(true); 
				controlSelect->SetActive(false);
				isStart = true;
			}
			
			if (KEY->Down(VK_RETURN))
			{
				if (isStart)
					SCENE->ChangeScene("Start");
				else 
				{
					openControl = true;
					control->SetActive(true);
				}
			}
		}
		else 
		{
			if (KEY->Down('X'))
			{
				control->SetActive(false);
				openControl = false;
			}
		}
			
		return;
	}

	//스페이스 누를 시 프레임 빠르게 재생
	if (KEY->Press(VK_RETURN))
		frameTime = FAST_FRAME_TIME;
	else
		frameTime = BASIC_FRAME_TIME;

	//프레임 재생
	if (time > frameTime)
	{
		if (cnt == intros.size() - 1)
		{
			startSelect->SetActive(true);
		}

		if(cnt != 0) intros[cnt - 1]->SetActive(false);
		
		intros[cnt]->SetActive(true);
		cnt += 1;
		time -= frameTime;
	}

	time += DELTA;
}

void IntroScene::Render(HDC hdc)
{
	FOR(intros.size())
		intros[i]->Render(hdc);

	startSelect->Render(hdc);
	controlSelect->Render(hdc);
	control->Render(hdc);
}

void IntroScene::CreateIntroFrame()
{
	//Opening Setting
	for (int i = 1; i <= 150; ++i) {
		wstring filePath = L"Kirby_Resources/UI/Opening/opening (" + std::to_wstring(i) + L").bmp";
		intros.push_back(new Image(filePath));
	}
	intros.push_back(new Image(L"Kirby_Resources/UI/Title.bmp"));

	FOR(intros.size())
	{
		intros[i]->SetActive(false);
		intros[i]->SetPos(intros[i]->Half());
	}

	intros[0]->SetActive(true);

	//Start Setting
	startSelect = new Image(L"Kirby_Resources/UI/StartSelect.bmp");
	startSelect->SetPos(startSelect->Half());
	startSelect->SetActive(false);

	controlSelect = new Image(L"Kirby_Resources/UI/ControlSelect.bmp");
	controlSelect->SetPos(controlSelect->Half());
	controlSelect->SetActive(false);

	control = new Image(L"Kirby_Resources/UI/Control.bmp");
	control->SetPos(control->Half());
	control->SetActive(false);

}
