#include "Framework.h"

KirbyJump::KirbyJump(Rect* owner, int state) : Action(owner)
{
	if (state == 0)
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(START_L)->SetPart(78, 78);//JumpUpLeft
		AddAnimation(START_R)->SetPart(78, 78);//JumpUpRight
		AddAnimation(LAND_L)->SetPart(77, 71);//JumpLandLeft
		AddAnimation(LAND_R)->SetPart(77, 67);//JumpLandRight

		GetAnimation(LAND_L)->SetSpeed(2.3f);
		GetAnimation(LAND_R)->SetSpeed(2.3f);
	}
	else if (state == 1)
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(START_L)->SetPart(78, 78);//JumpUpLeft
		AddAnimation(START_R)->SetPart(78, 78);//JumpUpRight
		AddAnimation(LAND_L)->SetPart(77, 71);//JumpLandLeft
		AddAnimation(LAND_R)->SetPart(77, 67);//JumpLandRight

		GetAnimation(LAND_L)->SetSpeed(2.3f);
		GetAnimation(LAND_R)->SetSpeed(2.3f);
	}
}

KirbyJump::~KirbyJump()
{
}

void KirbyJump::Update()
{
	Jump();
	Move();

	Action::Update();
}

void KirbyJump::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	velocity = {};
	velocity.y = JUMP_POWER;
	jumpCount = 1;
	landHeight = landTexture->GetPixelHeight(owner->GetPos());
	owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
}

void KirbyJump::End()
{
	owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
}

void KirbyJump::Jump()
{
	if (curState == LAND_R) return;
	if (curState == LAND_L) return;
	
	if (jumpCount <= MAX_JUMP && KEY->Down('W') && owner->GetPos().y > owner->GetSize().y)
	{
		velocity.y = JUMP_POWER;

		jumpCount++;
		
	}

	velocity.y += GRAVITY * DELTA;

	landHeight = landTexture->GetPixelHeight(owner->GetPos());

	if (owner->Bottom() > landHeight)
	{
		velocity.y = 0.0f;
		jumpCount = 0;

		curState ? SetState(LAND_R) : SetState(LAND_L);
	}
}

void KirbyJump::Move()
{
	if (curState == LAND_R) return;
	if (curState == LAND_L) return;

	if (KEY->Press('A'))
	{
		velocity.x = -MOVE_SPEED;
		//SetState(LEFT, false, false);
		SetTex(false);
	}
	else if (KEY->Press('D'))
	{
		velocity.x = +MOVE_SPEED;
		//SetState(RIGHT, false, false);
		SetTex(true);
	}
	else 
	{
		velocity.x = 0.0f;
	}
}

