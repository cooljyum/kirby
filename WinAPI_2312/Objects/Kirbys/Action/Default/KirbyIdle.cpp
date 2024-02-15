#include "Framework.h"

KirbyIdle::KirbyIdle(Rect* owner, int state) : Action(owner)
{
	if (state == 0)
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(0, 1, true, true);
		AddAnimation(RIGHT)->SetPart(0, 1, true, true);

		SetState(RIGHT);

		GetAnimation(LEFT)->SetSpeed(0.8f);
		GetAnimation(RIGHT)->SetSpeed(0.8f);
	}

}

KirbyIdle::~KirbyIdle()
{
}
