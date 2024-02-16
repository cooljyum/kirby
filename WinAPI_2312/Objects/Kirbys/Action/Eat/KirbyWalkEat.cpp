#include "Framework.h"

KirbyWalkEat::KirbyWalkEat(Rect* owner) : KirbyWalk(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(44, 56, true);
	AddAnimation(RIGHT)->SetPart(44, 56, true);

	SetState(RIGHT);

	SetIsRun(false);
}

KirbyWalkEat::~KirbyWalkEat()
{
}
