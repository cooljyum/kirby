#include "Framework.h"

KirbyJumpDownEat::KirbyJumpDownEat(Rect* owner) : KirbyJumpDown(owner)
{
	Texture* leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	Texture* rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetLeftTexture(leftTexture);
	SetRightTexture(rightTexture);

	SetTexture(rightTexture);


	AddAnimation(LEFT)->SetPart(59, 64);
	AddAnimation(RIGHT)->SetPart(59, 64);
	
	GetAnimation(LEFT)->SetSpeed(2.3f);
	GetAnimation(RIGHT)->SetSpeed(2.3f);
}

KirbyJumpDownEat::~KirbyJumpDownEat()
{
}
