#include "Framework.h"
int KirbyJump::jumpCount = 0;
KirbyJump::~KirbyJump()
{
}

void KirbyJump::Update()
{
	Jump();
	Move();
	Push(curState == RIGHT ? true : false);

	Action::Update();
}

void KirbyJump::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	jumpCount = 1;
	velocity = {};
}

void KirbyJump::Jump()
{
	velocity.y += GRAVITY * DELTA;

	if (KEY->Down('W'))
	{
		Kirby* kirby = (Kirby*)owner;

		kirby->SetMode(Kirby::EAT);				
		kirby->SetAction(Kirby::JUMPUP, curState, true);		
	}
}

void KirbyJump::Move()
{

	if (KEY->Press('A'))
	{
		velocity.x = -speed;
		SetState(LEFT, false, false);
		SetTex(false);
	}
	else if (KEY->Press('D'))
	{
		velocity.x = +speed;
		SetState(RIGHT, false, false);
		SetTex(true);
	}
	else 
	{
		velocity.x = 0.0f;
	}
}

void KirbyJump::Push(bool isRight)
{
	float offset = isRight? landTexture->GetPixelRight(owner) : landTexture->GetPixelLeft(owner);

	if (offset < 0)
		return;

	Vector2 ownerPos = owner->GetPos();
	if (isRight)
	{
		ownerPos.x = Lerp(owner->GetPos().x, offset - owner->Half().x, 5.0f * DELTA);
	}
	else
	{
		ownerPos.x = Lerp(owner->GetPos().x, offset + owner->Half().x, 5.0f * DELTA);
	}
	owner->SetPos(ownerPos);
}

