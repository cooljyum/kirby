#include "Framework.h"

KirbyIdleEat::KirbyIdleEat(Rect* owner) : KirbyIdle(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(42, 43, true, true);
	AddAnimation(RIGHT)->SetPart(42, 43, true, true);

	SetState(RIGHT);

	GetAnimation(LEFT)->SetSpeed(0.8f);
	GetAnimation(RIGHT)->SetSpeed(0.8f);
}

KirbyIdleEat::~KirbyIdleEat()
{
}
