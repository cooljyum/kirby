#include "Framework.h"

KirbyAttack::KirbyAttack(Rect* owner, int state) : Action(owner)
{
	if (state == 0)
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(30, 34);
		AddAnimation(RIGHT)->SetPart(30, 34);

		SetState(RIGHT);

		collider = new Rect(Vector2(), { 200, 100 });
		collider->SetActive(false);

		GetAnimation(LEFT)->SetSpeed(2.3f);
		GetAnimation(RIGHT)->SetSpeed(2.3f);
	}
	else if (state == 1)
	{
		leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
		rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

		SetTexture(rightTexture);

		AddAnimation(LEFT)->SetPart(34, 30);
		AddAnimation(RIGHT)->SetPart(34, 30);

		SetState(RIGHT);

		collider = new Rect(Vector2(), { 200, 100 });
		collider->SetActive(false);

		GetAnimation(LEFT)->SetSpeed(2.0f);
		GetAnimation(RIGHT)->SetSpeed(2.0f);
	}
}

KirbyAttack::~KirbyAttack()
{
	delete collider;
}

void KirbyAttack::Render(HDC hdc)
{
	Image::CamRender(hdc, animations[curState]->GetFrame());
	collider->CamRender(hdc);
}

void KirbyAttack::Update()
{
	Action::Update();
}

void KirbyAttack::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	Vector2 pos = owner->GetPos();
	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	collider->SetPos({ pos.x + direction.x * 100.0f , pos.y });
	collider->SetActive(true);
}


