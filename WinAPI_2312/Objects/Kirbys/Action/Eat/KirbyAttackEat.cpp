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

	if (Kirby::isEatBullet)
	{
		KirbyStarBullet::Shot(owner->GetPos(), isRight);
		EffectManager::Get()->Play("KirbyStarEffect", { isRight ? owner->GetPos().x + 50.0f : owner->GetPos().x - 50.0f, owner->GetPos().y });
		Kirby::isEatBullet = false;
	}
	else 
	{
		SOUND->Play("Breath");
		isRight? EffectManager::Get()->Play("KirbyBreathEffectR", { owner->GetPos().x + 50.0f, owner->GetPos().y }):
			EffectManager::Get()->Play("KirbyBreathEffectL", { owner->GetPos().x - 50.0f, owner->GetPos().y });
	}
}
