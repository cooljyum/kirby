#include "Framework.h"

KirbyInhole::KirbyInhole(Rect* owner) : Action(owner)
{

	leftTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Left.bmp", 10, 14);
	rightTexture = Texture::Add(L"Kirby_Resources/Kirby/Default_Right.bmp", 10, 14);

	SetTexture(rightTexture);

	AddAnimation(LEFT)->SetPart(30, 34,true);
	AddAnimation(RIGHT)->SetPart(30, 34, true);

	SetState(RIGHT);

	collider = new Rect(Vector2(), { 200, 100 });
	collider->SetActive(false);

	GetAnimation(LEFT)->SetSpeed(2.3f);
	GetAnimation(RIGHT)->SetSpeed(2.3f);

	Kirby::AddCollider(collider);

}

KirbyInhole::~KirbyInhole()
{
	delete collider;
}

void KirbyInhole::Render(HDC hdc)
{
	Image::CamRender(hdc, animations[curState]->GetFrame());
	collider->CamRender(hdc);
}

void KirbyInhole::Update()
{
	Action::Update();
	Monster* monster = MonsterManager::Get()->Collision(collider);
	if (monster != nullptr) 
	{
		monster->SetPos(owner->GetPos());
	}

	if (KEY->Up('F'))
	{
		Kirby* kirby = (Kirby*)owner;
		kirby->SetIdle();		
	}
}

void KirbyInhole::Start(bool isRight)
{
	SetTex(isRight);
	SetState(isRight, true);

	Vector2 pos = owner->GetPos();
	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	collider->SetPos({ pos.x + direction.x * 100.0f , pos.y });
	collider->SetActive(true);
}



