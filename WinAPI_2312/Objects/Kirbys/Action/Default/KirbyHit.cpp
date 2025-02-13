#include "Framework.h"

KirbyHit::KirbyHit(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Hit_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Hit_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	int arr[] = { 9, 8, 9, 8, 9, 8};
	AddAnimation(LEFT)->SetArray(arr, 6);
	int arr_[] = { 0, 1, 0, 1, 0, 1 };
	AddAnimation(RIGHT)->SetArray(arr_, 6);

	SetState(RIGHT);
}


KirbyHit::~KirbyHit()
{
}

void KirbyHit::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);
}
