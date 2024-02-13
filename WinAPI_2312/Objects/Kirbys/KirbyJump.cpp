#include "Framework.h"

KirbyJump::KirbyJump(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(START_L)->SetPart(29, 25);//JumpUpLeft
	AddAnimation(START_R)->SetPart(29, 25);//JumpUpRight
	AddAnimation(LAND_L)->SetPart(25, 29);//JumpLandLeft
	AddAnimation(LAND_R)->SetPart(25, 29);//JumpLandRight

	//GetAnimation(LAND_L)->SetSpeed(5.0f);
	//GetAnimation(LAND_R)->SetSpeed(5.0f);
}

KirbyJump::~KirbyJump()
{
}

void KirbyJump::Update()
{
	Jump();

	Action::Update();
}

void KirbyJump::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	velocity = {};
	jumpCount = 1;
}

void KirbyJump::End()
{
}

void KirbyJump::Jump()
{
//	if (curState == LAND_R) return;
//	if (curState == LAND_L) return;

	if (jumpCount <= MAX_JUMP && KEY->Down('W'))
	{
		velocity.y = JUMP_POWER;
		jumpCount++;

		SetState(curState, true);
	}

	velocity.y += GRAVITY * DELTA;

	/*landHeight = landTexture->GetPixelHeight(owner->GetPos());

	if (owner->Bottom() > landHeight)
	{
		velocity.y = 0.0f;
		curState ? SetState(LAND_R) : SetState(LAND_L);
	}*/
}

void KirbyJump::Move()
{
}

