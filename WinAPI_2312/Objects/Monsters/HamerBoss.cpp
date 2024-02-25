#include "Framework.h"

HamerBoss::HamerBoss(int x, int y, int hp) : Monster()
{
	//HpBar Set
	this->CreateHpBar(Texture::Add(L"Kirby_Resources/UI/MonsterHP.bmp")
		, Texture::Add(L"Kirby_Resources/UI/MonsterHPBottom.bmp")
		, { 600.0f,550.0f }, true);
	this->SetActiveHpBar(true);

	//Init Set
	SetSize(SIZE);
	SetPos(x, y);
	SetHp(hp);

	//Tex, Ani Set
	CreateTexture();
	CreateAnimation();

	//Ani Init Setting
	animations[IDLE][isRight]->Play();

	//Range Set
	//Trace Range Rect
	traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
	traceRange->SetColor(YELLOW);

	//Attack Range Rect
	attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
	attackRange->SetColor(BLUE);

	//Attack Collider
	attackCollider = new Rect(Vector2(), Vector2(300, 300));
	attackCollider->SetColor(RED);
	attackCollider->SetActive(false);

	//Boss Fun - BossBullet
	//Bullet Create
	BossBullet::CreateBullets();

}

void HamerBoss::Update()
{
	//Check Active 
	if (!IsActive()) return;

	//Action State Set & Play
	SetActionState();
	DoAction();

	//HitColliders Erase (When Anymore No Collision )
	for (int i = 0; i < hitColliders.size(); i++)
	{
		if (!hitColliders[i]->IsCollision(this))
		{
			hitColliders.erase(hitColliders.begin() + i);
			break;
		}
	}

	//Check Collision 
	Collision();

	//Move follow velocity
	Translate(velocity * DELTA);

	//curState Ani Update
	animations[curState][isRight]->Update();

	//Rects follow this
	//Range Rect
	traceRange->SetPos(pos);
	attackRange->SetPos(pos);
	//Collider Rect
	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();

	//AttackCollider Pos
	attackCollider->SetPos(pos + direction * 100.0f );

	//image follow this
	image->SetPos(pos + offset);

	//Gravity Setting
	velocity.y += GRAVITY * DELTA;

	//Bottom Check Map Land
	if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
	{
		velocity.y = 0.0f;
		this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
	}

	//Boss Fun - BossBullet
	//BossBullet 
	BossBullet::UpdateBullets();
	
	//Monster
	MonsterManager::Get()->Update();

	//AttackColliderStay Check
	if (attackCollider->IsActive()) 
	{
		if (attackColliderTime >= DELTA) 
		{
			attackColliderTime -= DELTA;
			attackCollider->SetActive(false);
		}
		else
			attackColliderTime += DELTA;
	}
}

void HamerBoss::Render(HDC hdc)
{
	Monster::Render(hdc);
	MonsterManager::Get()->Render(hdc);

	//Boss Fun - BossBullet
	BossBullet::RenderBullets(hdc);

	hpBar->Render(hdc);
}

void HamerBoss::Collision()
{
	if (curState == HIT)
		return;

	//target Star Bullet & this collision
	if (KirbyStarBullet::IsBulletsCollision(this))
	{
		this->DamageHp(DAMAGE_STAR);
		SetAnimation(HIT);
		actionState = ActionState::HIT;
	}

	//AttackCollider & target collision
	if (attackCollider->IsCollision(target)) {
		target->DamageHp(ATTACK_STAR);
		attackCollider->SetActive(false);
	}

	//hit target
	for (Rect* collider : hitColliders)
	{
		if (collider == target)
			return;
	}

	//Die Check
	if (IsDie())
		Die();
}

void HamerBoss::CreateTexture()
{
	//Tex Set
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Left.bmp", 5, 4, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Right.bmp", 5, 4, true);

	//Image Set
	image = new Image(rightTexture);
	image->SetTexture(rightTexture);
}

void HamerBoss::CreateAnimation()
{
	//Clear
	animations.clear();

	//ANi Resize
	animations.resize(END);

	//Idle
	//L
	animations[IDLE].push_back(new Animation(leftTexture->GetFrame()));
	animations[IDLE].back()->SetPart(0, 3, true);
	//R
	animations[IDLE].push_back(new Animation(rightTexture->GetFrame()));
	animations[IDLE].back()->SetPart(0, 3, true);

	//Move
	//L
	animations[MOVE].push_back(new Animation(leftTexture->GetFrame()));
	animations[MOVE].back()->SetPart(4, 7, true);
	//R
	animations[MOVE].push_back(new Animation(rightTexture->GetFrame()));
	animations[MOVE].back()->SetPart(4, 7, true);

	//Attack //Boss±â´É 
	//L
	animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()->SetEndEvent([this]() { AttackEnd(false); });
	animations[ATTACK].back()->SetSpeed(0.5f);

	//R		   
	animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()->SetEndEvent([this]() { AttackEnd(true); });
	animations[ATTACK].back()->SetSpeed(0.5f);

	//Hit
	//L
	animations[HIT].push_back(new Animation(leftTexture->GetFrame()));
	animations[HIT].back()->SetPart(16, 16);
	animations[HIT].back()->SetEndEvent(bind(&HamerBoss::SetIdle, this));
	//R		   
	animations[HIT].push_back(new Animation(rightTexture->GetFrame()));
	animations[HIT].back()->SetPart(16, 16);
	animations[HIT].back()->SetEndEvent(bind(&HamerBoss::SetIdle, this));

	//Dead
	//L
	animations[DEAD].push_back(new Animation(leftTexture->GetFrame()));
	animations[DEAD].back()->SetPart(17, 19);
	animations[DEAD].back()->SetEndEvent([this]() { TreasureSpawn(); });

	//R		   
	animations[DEAD].push_back(new Animation(rightTexture->GetFrame()));
	animations[DEAD].back()->SetPart(17, 19);
	animations[DEAD].back()->SetEndEvent([this]() { TreasureSpawn(); });
}

void HamerBoss::Attack()
{
	if (stayAttackTime <= 0)
	{
		stayAttackTime = ATTACK_STAY_TIME;

		velocity = { 0, -JUMP_POWER }; //Boss different Monster

		SetDirectionState();

		SetAnimation(ATTACK);

	}
	stayAttackTime -= DELTA;
}

void HamerBoss::Die()
{
	//Die
	SetAnimation(DEAD);

	velocity = {};

	stayDieTime += DELTA;
	if (stayDieTime > DIE_STAY_TIME)
	{
		SOUND->Play("BossDie", 0.5f);
		stayDieTime = 0.0f;
		SetAllActive(false);
	}
}

void HamerBoss::MonsterSpawn()
{
	//Boss can spawn monsters
	MonsterManager::Get()->Spawn(pos.x, pos.y);
	MonsterManager::Get()->SetTarget(target);
	MonsterManager::Get()->SetLandTexture(landTexture);
}

void HamerBoss::TreasureSpawn()
{
	//Boss can spawn monsters if boss die
	MapItemManager::Get()->Play("Treasure", { this->GetPos().x, this->GetPos().y + TREASURE_OFFSET_Y });
	EffectManager::Get()->Play("TreasureEffect", { this->GetPos().x, this->GetPos().y + TREASURE_OFFSET_Y });
}

void HamerBoss::AttackEnd(bool isRight)
{
	SOUND->Play("BossAttack", 0.5f);
	attackCollider->SetActive(true);

	int randomNumber = rand() % 5;
	if (!randomNumber)
		MonsterSpawn();
	else
	{
		BossBullet::init();
		BossBullet::Shot(attackCollider->GetPos() + (isRight ? Vector2{ 150.0f, 0 } : Vector2{ -150.0f, 0 }), isRight);
	}

	SetIdle();
}
