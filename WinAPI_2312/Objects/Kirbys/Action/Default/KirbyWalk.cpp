#include "Framework.h"

KirbyWalk::KirbyWalk(Rect* owner) : Action(owner)
{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(6, 15, true);
		AddAnimation(RIGHT)->SetPart(6, 15, true);

		SetState(RIGHT);
		SetSpeed(250.0f);
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
		(KEY->Press(VK_SHIFT) && isRun) ? velocity.x = - speed * 2 : velocity.x = -speed;
		SetState(LEFT);
		SetTex(false);
		Push(false);
	}
	else if (KEY->Press('D'))
	{
		(KEY->Press(VK_SHIFT) && isRun)? velocity.x = + speed * 2 :  velocity.x = +speed;
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
