#include "Framework.h"
#include "PixelCollisionScene.h"

PixelCollisionScene::PixelCollisionScene()
{
	SOUND->Add("Jump", "Sounds/Jump.wav");
	SOUND->Add("Exp", "Sounds/Explosion.wav");
	SOUND->Add("BGM1", "Sounds/singing.wav", true);

	bg = new Image(L"Textures/Running/bg1.bmp");
	mountain = new Image(L"Textures/Running/bg4.bmp", 1, 1, true, WHITE);

	bg->SetPos(CENTER);
	mountain->SetPos(CENTER);

	robot = new Robot();
	robot->SetLandTexture(mountain->GetTexture());

	RobotBullet::SetLandTexture(mountain->GetTexture());
}

PixelCollisionScene::~PixelCollisionScene()
{
	delete bg;
	delete mountain;

	delete robot;
}

void PixelCollisionScene::Update()
{
	if (KEY->Down('1'))
		SCENE->ChangeScene("Action");

	robot->Update();
}

void PixelCollisionScene::Render(HDC hdc)
{
	bg->Render(hdc);
	mountain->Render(hdc);

	robot->Render(hdc);
}

void PixelCollisionScene::Start()
{
	SOUND->Play("BGM1");
}

void PixelCollisionScene::End()
{
	SOUND->Stop("BGM1");
}
