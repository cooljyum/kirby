#include "Framework.h"

KirbyJumpEnd::KirbyJumpEnd(Rect* owner, int state) : KirbyJump(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);

	if (state == 0)
	{
		AddAnimation(LEFT)->SetPart(77, 67);
		AddAnimation(RIGHT)->SetPart(77, 67);
	}
	else if (state == 1)
	{
		AddAnimation(LEFT)->SetPart(59, 64);
		AddAnimation(RIGHT)->SetPart(59, 64);
	}
	GetAnimation(LEFT)->SetSpeed(2.3f);
	GetAnimation(RIGHT)->SetSpeed(2.3f);
}

KirbyJumpEnd::~KirbyJumpEnd()
{
}

void KirbyJumpEnd::End()
{
	owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
}

void KirbyJumpEnd::Jump()
{
	velocity.y += GRAVITY * DELTA;

	landHeight = landTexture->GetPixelHeight(owner->GetPos());

	if (owner->Bottom() > landHeight)
	{
		velocity.y = 0.0f;
		SetJumpCount(0);
		owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
		curState ? SetState(RIGHT) : SetState(LEFT);

		Kirby* kirby = (Kirby*)owner;
		kirby->SetIdle();
	}
}
