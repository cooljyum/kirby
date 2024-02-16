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
}

void KirbyJump::Jump()
{
	velocity.y += GRAVITY * DELTA;

	int jumpCount = GetJumpCount();

	if (jumpCount <= MAX_JUMP && KEY->Down('W') && owner->GetPos().y > owner->GetSize().y)
	{
		Kirby* kirby = (Kirby*)owner;

		if (kirby->GetActionState() == Kirby::JUMPDOWN) 
		{
			velocity.y = 0;
			kirby->SetMode(Kirby::EAT);
			kirby->SetAction(Kirby::JUMPUP, curState);
		}
		else 
		{
			velocity.y = JUMP_POWER;
			kirby->SetMode(Kirby::EAT);
			kirby->SetAction(Kirby::IDLE, curState); //크흡 ㅎㅎㅎ질문.. 이거 좀 별론거 같긴 한데.. 잘되긴한데..
			kirby->SetAction(Kirby::JUMPUP, curState);
			SetJumpCount(jumpCount++);
		}
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

