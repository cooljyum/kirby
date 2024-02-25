#include "Framework.h"

KirbyJump::~KirbyJump()
{
}

void KirbyJump::Update()
{
	Action::Update();

	//Control 
	Jump();
	Move();

	Push(curState == RIGHT ? true : false);
}

void KirbyJump::Start(bool isRight)
{
	//Tex Setting
	SetTex(isRight);
	SetState(isRight, true);

	//Velocity Init
	velocity = {};
}

void KirbyJump::Jump()
{
	//Velocity GRAVITY Setting
	velocity.y += GRAVITY * DELTA;

	//Possible Repeat Jump
	if (KEY->Down('W'))
	{
		SOUND->Play("Fly");
		Kirby* kirby = (Kirby*)owner;

		//When double jumping
		//Change mode
		kirby->SetMode(Kirby::EAT);				
		kirby->SetAction(Kirby::JUMPUP, curState, true);		
	}
}

void KirbyJump::Move()
{

	//Can Move While Jump
	if (KEY->Press('A')) //L
	{
		velocity.x = -speed;
		SetState(LEFT, false, false);
		SetTex(false);
	}
	else if (KEY->Press('D')) //R
	{
		velocity.x = +speed;
		SetState(RIGHT, false, false);
		SetTex(true);
	}
	else //No Move
	{
		velocity.x = 0.0f;
	}
}

void KirbyJump::Push(bool isRight)
{
	//Check the side push the map
	float offset = isRight? landTexture->GetPixelRight(owner) : landTexture->GetPixelLeft(owner);

	//No Push
	if (offset < 0)
		return;

	//Push
	//Can't Move Process
	Vector2 ownerPos = owner->GetPos();
	if (isRight)
		ownerPos.x = Lerp(owner->GetPos().x, offset - owner->Half().x, 5.0f * DELTA);
	else
		ownerPos.x = Lerp(owner->GetPos().x, offset + owner->Half().x, 5.0f * DELTA);
	owner->SetPos(ownerPos);
}

