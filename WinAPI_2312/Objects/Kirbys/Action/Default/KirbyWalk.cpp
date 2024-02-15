#include "Framework.h"

KirbyWalk::KirbyWalk(Rect* owner, int state) : Action(owner)
{
	if (state == 0) {
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(6, 15, true);
		AddAnimation(RIGHT)->SetPart(6, 15, true);

		SetState(RIGHT);
	}
	else if (state == 1) 
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(44, 56, true);
		AddAnimation(RIGHT)->SetPart(44, 56, true);

		SetState(RIGHT);
	}
}

KirbyWalk::~KirbyWalk()
{
}

void KirbyWalk::Update()
{
	Control();

	Action::Update();
}

void KirbyWalk::End()
{
	owner->SetPos({ owner->GetPos().x,  owner->GetPos().y });
}

void KirbyWalk::Control()
{
	if (KEY->Press('A'))
	{
		(KEY->Press(VK_SHIFT)) ? velocity.x = -RUN_SPEED : velocity.x = -MOVE_SPEED;
		SetState(LEFT);
		SetTex(false);
		Push(false);
	}
	else if (KEY->Press('D'))
	{
		(KEY->Press(VK_SHIFT))? velocity.x = +RUN_SPEED :  velocity.x = +MOVE_SPEED;
		SetState(RIGHT);
		SetTex(true);
		Push(true);
	}

	landHeight = landTexture->GetPixelHeight(owner->GetPos());

	if (owner->Bottom() < landHeight)
	{
		velocity.y += GRAVITY * DELTA / 3;
	}
	else if (owner->Bottom() > landHeight)
	{
		owner->SetPos({ owner->GetPos().x, landHeight - owner->Half().y });
	}
}

void KirbyWalk::Push(bool isRight)
{
	float offset = isRight ? landTexture->GetPixelRight(owner) : landTexture->GetPixelLeft(owner);

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