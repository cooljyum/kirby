#include "Framework.h"

KirbyAttackEat::KirbyAttackEat(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(34, 30);
	AddAnimation(RIGHT)->SetPart(34, 30);

	SetState(RIGHT);

	GetAnimation(LEFT)->SetSpeed(2.0f);
	GetAnimation(RIGHT)->SetSpeed(2.0f);
}

KirbyAttackEat::~KirbyAttackEat()
{
}

void KirbyAttackEat::Start(bool isRight)
{
	Action::Start(isRight);
	SetTex(isRight);
	SetState(isRight, true);

	KirbtStarBullet::Shot(owner->GetPos(), isRight);
}
