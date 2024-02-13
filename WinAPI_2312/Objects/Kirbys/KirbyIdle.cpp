#include "Framework.h"

KirbyIdle::KirbyIdle(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(0, 1, true, true);
	AddAnimation(RIGHT)->SetPart(0, 1, true, true);
	
	SetState(RIGHT);
}

KirbyIdle::~KirbyIdle()
{
}
