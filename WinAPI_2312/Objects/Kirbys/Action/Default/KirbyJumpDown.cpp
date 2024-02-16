#include "Framework.h"

KirbyJumpDown::KirbyJumpDown(Rect* owner) : KirbyJump(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);


	AddAnimation(LEFT)->SetPart(77, 67);
	AddAnimation(RIGHT)->SetPart(77, 67);

	GetAnimation(LEFT)->SetSpeed(2.3f);
	GetAnimation(RIGHT)->SetSpeed(2.3f);
}

KirbyJumpDown::~KirbyJumpDown()
{
}

void KirbyJumpDown::Jump()
{
	KirbyJump::Jump();
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
