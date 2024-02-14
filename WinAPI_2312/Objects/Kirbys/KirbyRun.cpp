#include "Framework.h"

KirbyRun::KirbyRun(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(23, 16, true, true);
	AddAnimation(RIGHT)->SetPart(23, 16, true, true);

	SetState(RIGHT);
}

KirbyRun::~KirbyRun()
{
}

void KirbyRun::Update()
{
	Control();

	Action::Update();
}

void KirbyRun::Control()
{
	if (KEY->Press('A'))
	{
		velocity.x = -RUN_SPEED;
		SetState(LEFT);
		SetTex(false);
	}
	else if (KEY->Press('D'))
	{
		velocity.x = +RUN_SPEED;
		SetState(RIGHT);
		SetTex(true);
	}

	Vector2 pos = owner->GetPos();
	pos.y = landTexture->GetPixelHeight(pos) - owner->Half().y;
	owner->SetPos(pos);
}
