#include "Framework.h"

KirbyWalk::KirbyWalk(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(15, 10, true, true);
	AddAnimation(RIGHT)->SetPart(10, 15, true, true);

	SetState(RIGHT);
}

KirbyWalk::~KirbyWalk()
{
}

void KirbyWalk::Update()
{
	Control();

	Action::Update();
}

void KirbyWalk::Control()
{
	if (KEY->Press('A'))
	{
		velocity.x = -MOVE_SPEED;
		SetState(LEFT);
		SetTex(false);
	}
	else if (KEY->Press('D'))
	{
		velocity.x = +MOVE_SPEED;
		SetState(RIGHT);
		SetTex(true);
	}

	Vector2 pos = owner->GetPos();
	//pos.y = landTexture->GetPixelHeight(pos) - owner->Half().y;
	owner->SetPos(pos);
}
