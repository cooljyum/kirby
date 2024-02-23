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
	
	//�ٿ� ĳ����
	Kirby* kirby = (Kirby*)owner; // �̰� ������ �ϴ°� ������,,?


	//Monster
	Monster* monster = MonsterManager::Get()->Collision(collider);

	//���Ͷ� Inhole Collider�� ������ 
	if (monster != nullptr) 
	{
		//���͸� ����� ������ �ٰ����� ��
		Vector2 monVelocity;
		monVelocity.x = ((owner->GetPos() - monster->GetPos()).Normalized() * speed).x;
		monVelocity = monVelocity.Normalized() * speed;
		monster->SetVelocity(monVelocity);

		//���� Action����
		monster->InHaled();

		if (owner->IsCollision(monster))
		{
			//������  
			//Monster�� �ٷ� Die
			monster->DamageHp(monster->GetHp()); 
			monster->SetActive(false);

			//Kirby�� Mode ���� //SetIdle
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();
		}
	}

	//Boss 
	BossBullet* BossBullet = BossBullet::Collision(collider);	

	//������ Bullet�̶� Inhole Collider�� ������ 
	if (BossBullet != nullptr)
	{
		Vector2 monVelocity;
		monVelocity.x = ((owner->GetPos() - BossBullet->GetPos()).Normalized()).x;
		monVelocity = monVelocity.Normalized() * speed;

		BossBullet->SetVelocity(monVelocity);
		if (owner->IsCollision(BossBullet))
		{
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();
		}
	}

	//FŰ�� ���� InHole False
	if (KEY->Up('F'))
	{
		kirby->SetIdle();		
	}
}

void KirbyInhole::Start(bool isRight)
{
	//Tex Setting
	SetTex(isRight);
	SetState(isRight, true);

	//InHole Collider Setting
	Vector2 pos = owner->GetPos();
	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	collider->SetPos({ pos.x + direction.x * 100.0f , pos.y });
	collider->SetActive(true);
}



