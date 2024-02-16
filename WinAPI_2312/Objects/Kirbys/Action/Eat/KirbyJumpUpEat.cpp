#include "Framework.h"

KirbyJumpUpEat::KirbyJumpUpEat(Rect* owner) : KirbyJumpUp(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(56, 58, true);//JumpUpLeft
	AddAnimation(RIGHT)->SetPart(58, 58, true);//JumpUpRight
}

KirbyJumpUpEat::~KirbyJumpUpEat()
{
}
