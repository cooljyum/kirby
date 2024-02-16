#include "Framework.h"

KirbyAttackEat::KirbyAttackEat(Rect* owner) : KirbyAttack(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(34, 30);
	AddAnimation(RIGHT)->SetPart(34, 30);

	SetState(RIGHT);

	collider = new Rect(Vector2(), { 200, 100 });
	collider->SetActive(false);

	GetAnimation(LEFT)->SetSpeed(2.0f);
	GetAnimation(RIGHT)->SetSpeed(2.0f);
}

KirbyAttackEat::~KirbyAttackEat()
{
}
