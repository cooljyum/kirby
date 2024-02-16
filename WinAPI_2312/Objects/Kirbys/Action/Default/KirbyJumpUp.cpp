#include "KirbyJumpUp.h"
#include "Framework.h"

KirbyJumpUp::KirbyJumpUp(Rect* owner) : KirbyJump(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(78, 78);//JumpUpLeft
	AddAnimation(RIGHT)->SetPart(78, 78);//JumpUpRight

}

KirbyJumpUp::~KirbyJumpUp()
{
}

void KirbyJumpUp::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	velocity = { 0, JUMP_POWER };
	//SetJumpCount(jumpcoun);
}


void KirbyJumpUp::Jump()
{
	KirbyJump::Jump();
	

	if (velocity.y >= 0)
	{
		Kirby* kirby = (Kirby*)owner;
		kirby->SetAction(Kirby::JUMPDOWN, curState);
	}
}

