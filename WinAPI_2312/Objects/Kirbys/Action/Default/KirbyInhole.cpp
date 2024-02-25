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
	
	//다운 캐스팅
	Kirby* kirby = (Kirby*)owner; 

	//Monster
	Monster* monster = MonsterManager::Get()->Collision(collider);

	//몬스터랑 Inhole Collider랑 닿으면 
	if (monster != nullptr) 
	{
		//몬스터를 사용자 쪽으로 다가가게 함
		Vector2 monVelocity;
		monVelocity.x = ((owner->GetPos() - monster->GetPos()).Normalized() * speed).x;
		monVelocity = monVelocity.Normalized() * speed;
		monster->SetVelocity(monVelocity);

		//몬스터 Action설정
		monster->InHaled();

		if (owner->IsCollision(monster))
		{
			SOUND->Stop("Attack");

			//닿으면  
			//Monster는 바로 Die
			monster->DamageHp(monster->GetHp()); 
			monster->SetAllActive(false);

			//Kirby는 Mode 변경 //SetIdle
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();

			Kirby::isEatBullet = true;
		}
	}

	//Boss 
	BossBullet* BossBullet = BossBullet::Collision(collider);	

	//보스의 Bullet이랑 Inhole Collider랑 닿으면 
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

	//F키를 떼면 InHole False
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



