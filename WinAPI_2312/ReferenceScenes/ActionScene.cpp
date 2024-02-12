#include "Framework.h"
#include "ActionScene.h"

ActionScene::ActionScene()
{
	SOUND->Add("BGM2", "Sounds/drumloop.wav", true);

	robot = new Robot();
	slime = new Slime();
	slime->SetPos(CENTER_X + 200, CENTER_Y);
	slime->SetTarget(robot);
}

ActionScene::~ActionScene()
{
	delete robot;
}

void ActionScene::Update()
{
	if (KEY->Down(VK_F3))
		SCENE->ChangeScene("Start");

	robot->Update();
	slime->Update();
}

void ActionScene::Render(HDC hdc)
{
	robot->Render(hdc);
	slime->Render(hdc);
}

void ActionScene::Start()
{
	SOUND->Play("BGM2");
}
