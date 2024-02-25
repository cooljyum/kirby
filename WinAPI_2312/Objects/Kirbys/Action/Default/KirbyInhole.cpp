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

	isRight ? EffectManager::Get()->Play("KirbyInhaleEffectR", { owner->GetPos().x + 100.0f, owner->GetPos().y + 50.0f })
		: EffectManager::Get()->Play("KirbyInhaleEffectL", { owner->GetPos().x - 100.0f, owner->GetPos().y + 50.0f }) ;
	
	//�ٿ� ĳ����
	Kirby* kirby = (Kirby*)owner; 

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
			SOUND->Stop("Attack");

			//������  
			//Monster�� �ٷ� Die
			monster->DamageHp(monster->GetHp()); 
			monster->SetAllActive(false);

			//Kirby�� Mode ���� //SetIdle
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();

			Kirby::isEatBullet = true;
		}
	}

	//Boss 
	BossBullet* BossBullet = BossBullet::Collision(collider);	

	//������ Bullet�̶� Inhole Collider�� ������ 
	if (BossBullet != nullptr)
	{
		Vector2 monVelocity;
		monVelocity.x = ((owner->GetPos() - BossBullet->GetPos()).Normalized() ).x;
		monVelocity = monVelocity.Normalized();
		BossBullet->SetVelocity(monVelocity);

		if (owner->IsCollision(BossBullet))
		{
			SOUND->Stop("Attack");

			BossBullet->SetActive(false);

			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();
			Kirby::isEatBullet = true;
		}
	}

	//FŰ�� ���� InHole False
	if (KEY->Up('F'))
	{
		SOUND->Stop("Attack");

		kirby->SetIdle();		
	}
}

void KirbyInhole::Start(bool isRight)
{
	SOUND->Play("Attack");

	//Tex Setting
	SetTex(isRight);
	SetState(isRight, true);

	//InHole Collider Setting
	Vector2 pos = owner->GetPos();
	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	collider->SetPos({ pos.x + direction.x * 100.0f , pos.y });
	collider->SetActive(true);

	this->isRight = isRight;
}



