#include "Framework.h"
#include <Scenes/EndScene.h>

KirbyDie::KirbyDie(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Enter_Left.bmp", 10, 5);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Enter_Right.bmp", 10, 5);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(9, 9);
	AddAnimation(RIGHT)->SetPart(9, 9);

	SetState(RIGHT);
}


KirbyDie::~KirbyDie()
{
}

void KirbyDie::Start(bool isRight)
{
	SOUND->Play("Die", 0.5f);

	SetTex(isRight);
	SetState(isRight, true);

	velocity = { 0, JUMP_POWER };

	CAM->SetTarget(nullptr);
	owner->SetActive(false);
}

void KirbyDie::Update()
{
	Action::Update();

	velocity.y += GRAVITY * DELTA;

	if (dieStayTime > DIE_STAY_TIME)
	{
		EndScene::isEnd = false;
		SCENE->ChangeScene("End");
	}
	dieStayTime += DELTA;
}
