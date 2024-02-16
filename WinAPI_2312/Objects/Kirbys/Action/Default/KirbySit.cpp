#include "Framework.h"

KirbySit::KirbySit(Rect* owner) : Action(owner)
{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(2, 3, true, true);
		AddAnimation(RIGHT)->SetPart(2, 3, true, true);

		SetState(RIGHT);

		GetAnimation(LEFT)->SetSpeed(0.3f);
		GetAnimation(RIGHT)->SetSpeed(0.3f);
}

KirbySit::~KirbySit()
{
}

void KirbySit::Update()
{
	Action::Update();
}

void KirbySit::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);
}
