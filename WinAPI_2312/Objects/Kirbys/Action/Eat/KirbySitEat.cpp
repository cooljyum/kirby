#include "Framework.h"

KirbySitEat::KirbySitEat(Rect* owner) : KirbySit(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(64, 69);
	AddAnimation(RIGHT)->SetPart(64, 69);

	SetState(RIGHT);

	GetAnimation(LEFT)->SetSpeed(2.0f);
	GetAnimation(RIGHT)->SetSpeed(2.0f);
}

KirbySitEat::~KirbySitEat()
{
}
