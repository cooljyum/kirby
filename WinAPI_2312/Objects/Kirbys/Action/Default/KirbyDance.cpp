#include "Framework.h"

KirbyDance::KirbyDance(Rect* owner) : Action(owner)
{
	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/KirbyDance.bmp", 10, 6);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/KirbyDance.bmp", 10, 6);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(53, 0);
	AddAnimation(RIGHT)->SetPart(53, 0);

	SetState(RIGHT);

	GetAnimation(LEFT)->SetSpeed(2.0f);
	GetAnimation(RIGHT)->SetSpeed(2.0f);
	clearUI = new Image(L"Kirby_Resources/UI/ClearUI.bmp");
}


KirbyDance::~KirbyDance()
{
}

void KirbyDance::Render(HDC hdc)
{
	Action::Render(hdc);
	clearUI->Render(hdc);
}

void KirbyDance::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	clearUI->SetActive(true);
	clearUI->SetPos({ this->GetPos().x,this->GetPos().y + 100.0f });

	EffectManager::Get()->Play("StarEffect", this->GetPos());
}

void KirbyDance::End()
{
	clearUI->SetActive(false);
}
