#include "KirbyJumpUp.h"
#include "Framework.h"

KirbyJumpUp::KirbyJumpUp(Rect* owner, int state) : KirbyJump(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);

	if (state == 0)
	{
		AddAnimation(LEFT)->SetPart(78, 78);//JumpUpLeft
		AddAnimation(RIGHT)->SetPart(78, 78);//JumpUpRight
	}
	else if (state == 1)
	{
		AddAnimation(LEFT)->SetPart(56, 58, true);//JumpUpLeft
		AddAnimation(RIGHT)->SetPart(58, 58, true);//JumpUpRight
	}
}

KirbyJumpUp::~KirbyJumpUp()
{
}

void KirbyJumpUp::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	velocity = { 0, JUMP_POWER };
	SetJumpCount(1);
}


void KirbyJumpUp::Jump()
{
	KirbyJump::Jump();
	

	if (velocity.y >= 0)
	{
		Kirby* kirby = (Kirby*)owner;
		kirby->SetAction(Kirby::JUMPEND, curState);
	}
}

