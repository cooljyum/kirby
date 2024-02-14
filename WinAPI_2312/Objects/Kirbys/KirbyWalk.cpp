#include "Framework.h"

KirbyWalk::KirbyWalk(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(6, 15, true);
	AddAnimation(RIGHT)->SetPart(6, 15, true);

	SetState(RIGHT);
}

KirbyWalk::~KirbyWalk()
{
}

void KirbyWalk::Update()
{
	Control();

	Action::Update();

	Push();
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

	//landHeight = landTexture->GetPixelHeight(owner->GetPos());

	//if (owner->Bottom() > landHeight)
	{
		//owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
	}
}

void KirbyWalk::Push()
{
	float right = landTexture->GetPixelRIght(owner);

	if (right < 0) return;

	Vector2 ownerPos = owner->GetPos();
	ownerPos.x = right - owner->Half().x;
	owner->SetPos(ownerPos);
}
