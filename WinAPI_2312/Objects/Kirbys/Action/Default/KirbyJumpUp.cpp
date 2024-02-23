#include "KirbyJumpUp.h"
#include "Framework.h"

KirbyJumpUp::KirbyJumpUp(Rect* owner) : KirbyJump(owner)
{
	//Tex, ANi Set
	//Tex
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);

	//Ani
	AddAnimation(LEFT)->SetPart(78, 78);
	AddAnimation(RIGHT)->SetPart(78, 78);
}

KirbyJumpUp::~KirbyJumpUp()
{
}

void KirbyJumpUp::Start(bool isRight)
{
	//Tex Setting
	SetTex(isRight);
	SetState(isRight, true);

	//Jump
	//ScreenHight Check
	if (owner->GetPos().y > owner->GetSize().y) 
		velocity = { 0, JUMP_POWER };
}


void KirbyJumpUp::Jump()
{
	KirbyJump::Jump();
	
	//올라가다 떨어질때
	if (velocity.y >= 0)
	{
		//Downcasting
		Kirby* kirby = (Kirby*)owner;
		kirby->SetAction(Kirby::JUMPDOWN, curState);
	}
}

