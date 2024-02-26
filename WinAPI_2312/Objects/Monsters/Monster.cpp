#include "Framework.h"

Monster::Monster(int x, int y, int hp) : Character()
{
	//HpBar Set
	this->CreateHpBar(Texture::Add(L"Kirby_Resources/UI/MonsterHP.bmp")
		, Texture::Add(L"Kirby_Resources/UI/MonsterHPBottom.bmp")
		, { 600.0f,550.0f });

	//Init Set
	SetSize(SIZE);
	SetPos(x, y - Half().y);
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
	attackCollider = new Rect(Vector2(), Vector2(50, 50));
	attackCollider->SetColor(RED);
	attackCollider->SetActive(false);
}

Monster::~Monster()
{
	delete hpBar;

	for (vector<Animation*> animationArray : animations)
	{
		delete animationArray[0];
		delete animationArray[1];
	}
}

void Monster::Update()
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
	attackCollider->SetPos(pos + direction * 50.0f - Vector2{0.0f, attackCollider->Half().y});

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

	if (this->Left() < 0.0f)
	{
		this->SetPos({ this->Half().x ,this->GetPos().y });
		return;
	}

}

void Monster::Render(HDC hdc)
{
	CamRender(hdc);
	traceRange->CamRender(hdc);
	attackRange->CamRender(hdc);
	attackCollider->CamRender(hdc);

	image->CamRender(hdc, animations[curState][isRight]->GetFrame());
	
	hpBar->Render(hdc);
}

void Monster::InHaled()
{
	SetAnimation(INHALED);
}

void Monster::Hit() 
{
	SetAnimation(HIT);
	actionState = ActionState::HIT;
}

void Monster::SetActionState()
{
	if (actionState == ActionState::HIT) return;

	if (attackRange->IsCollision(target))
	{
		actionState = ActionState::ATTACK;
	}
	else if (traceRange->IsCollision(target))
	{
		actionState = ActionState::TRACE;
	}
	else
	{
		actionState = ActionState::PATROL;
	}
}

void Monster::SetIdle()
{
	SetAnimation(IDLE);
	actionState = ActionState::PATROL;
}

void Monster::Collision()
{
	if (curState == HIT)
		return;

	if (KirbyStarBullet::IsBulletsCollision(this))
	{
		this->DamageHp(8);

		MonsterManager::Get()->SetOffAllHpBar();
		this->SetActiveHpBar(true);

		SetAnimation(HIT);
		actionState = ActionState::HIT;
	}

	if (attackCollider->IsCollision(target)) {
		target->DamageHp(1);

		//Attack Collider Setting false
		attackCollider->SetActive(false);
	}

	//hit target
	for (Rect* collider : hitColliders)
	{
		if (collider == target)
			return;
	}

	//Check Die
	if (IsDie()) 
		Die();
}

void Monster::CreateTexture()
{
	//Tex Set
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);

	//Image Set
	image = new Image(rightTexture);
	image->SetTexture(rightTexture);
}

void Monster::CreateAnimation()
{
	//ANi Resize
	animations.resize(END);

	//Idle
	//L
	animations[IDLE].push_back(new Animation(leftTexture->GetFrame()));
	animations[IDLE].back()->SetPart(2, 2, true);
	//R
	animations[IDLE].push_back(new Animation(rightTexture->GetFrame()));
	animations[IDLE].back()->SetPart(2, 2, true);

	//Move
	//L
	animations[MOVE].push_back(new Animation(leftTexture->GetFrame()));
	animations[MOVE].back()->SetPart(4, 1, true);
	//R
	animations[MOVE].push_back(new Animation(rightTexture->GetFrame()));
	animations[MOVE].back()->SetPart(4, 1, true);

	//Attack
	//L
	animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(5, 9);
	animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	//R		   
	animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(5, 9);
	animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	
	//Hit
	//L
	animations[HIT].push_back(new Animation(leftTexture->GetFrame()));
	animations[HIT].back()->SetPart(9, 9);
	animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	//R		   
	animations[HIT].push_back(new Animation(rightTexture->GetFrame()));
	animations[HIT].back()->SetPart(9, 9);
	animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));

	//Dead
	//L
	animations[DEAD].push_back(new Animation(leftTexture->GetFrame()));
	animations[DEAD].back()->SetPart(9, 9);
	//R		   
	animations[DEAD].push_back(new Animation(rightTexture->GetFrame()));
	animations[DEAD].back()->SetPart(9, 9);

	//InHaled //Monster 
	//L
	animations[INHALED].push_back(new Animation(leftTexture->GetFrame()));
	animations[INHALED].back()->SetPart(9, 9);
	//R		   
	animations[INHALED].push_back(new Animation(rightTexture->GetFrame()));
	animations[INHALED].back()->SetPart(9, 9);
}

void Monster::SetAnimation(AnimationState state)
{
	if (curState == state) return;

	curState = state;
	isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
	animations[state][isRight]->Play();
}

void Monster::DoAction()
{
	if ( curState == INHALED ) return;

	switch (actionState)
	{
	case Monster::ActionState::PATROL:
		Patrol();
		break;
	case Monster::ActionState::TRACE:
		Trace();
		break;
	case Monster::ActionState::ATTACK:
		Attack();
		break;
	}
}

void Monster::Patrol()
{
	this->SetActiveHpBar(false);

	//Bottom Check Map Land
	if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
	{
		velocity.y = 0.0f;
		this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
	}

	//Check IsStay
	if (isStay)
	{
		velocity = {};

		stayTime += DELTA;

		if (stayTime > PATROL_STAY_TIME) 
		{
			stayTime = 0.0f;
			isStay = false;
			SetDestPos(); //Auto destPos Set
		}

		SetAnimation(IDLE);

		return;
	}

	//Move follow destPos
	Vector2 direction = destPos - pos;

	velocity = direction.Normalized() * PATROL_SPEED;

	if (direction.Magnitude() < 1.0f)
		isStay = true;

	//Tex, Ani Setting follow direction
	velocity.x < 0 ? isRight = false : isRight = true;
	isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
	SetAnimation(MOVE);
}

void Monster::Trace()
{ 
	this->SetActiveHpBar(true);

	//Target Follow Move
	velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED ).x;

	SetDirectionState();

	SetAnimation(MOVE);
}

void Monster::Attack()
{
	if (stayAttackTime <= 0)
	{
		//Attack
		stayAttackTime = ATTACK_STAY_TIME;

		attackCollider->SetActive(true);
		
		velocity = {};

		SetDirectionState();

		SetAnimation(ATTACK);
	}
	stayAttackTime -= DELTA;
	
}

void Monster::Die()
{
	//Die
	SetAnimation(DEAD);

	stayDieTime += DELTA;
	if (stayDieTime > DIE_STAY_TIME)
	{
		SOUND->Play("MonsterDie");
		stayDieTime = 0.0f;
		SetAllActive(false);
	}
}

void Monster::SetDirectionState()
{
	//Set IsRight follow Target
	bool isCurRight = target->GetPos().x > pos.x;

	if (isCurRight != isRight)
	{
		isRight = isCurRight;
		SetAnimation(IDLE);
	}
}

void Monster::SetDestPos() 
{
	//Patrol Distance Set
	float distance = Random(-PATROL_RANGE, +PATROL_RANGE);

	destPos = pos + Vector2::Right() * distance;

	if (destPos.x > SCREEN_WIDTH - Half().x)
		destPos.x = SCREEN_WIDTH - Half().x;
	if (destPos.x < Half().x)
		destPos.x = Half().x;

	isRight = distance > 0.0f;
}

void Monster::SetAllActive(bool isActive)
{
	//All Rect Active
	this->SetActive(isActive);
	this->image->SetActive(isActive);
	this->traceRange->SetActive(isActive);
	this->attackRange->SetActive(isActive);
	this->SetActiveHpBar(isActive);
}
