#include "Framework.h"

Monster::Monster(int type, int x, int y, int hp) : Character()
{
	SetSize({ 70.0f, 70.0f });
	SetPos(x, y - Half().y);
	SetHp(hp);

	CreateTexture();
	CreateAnimation();

	animations[IDLE][isRight]->Play();

	traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
	traceRange->SetColor(YELLOW);
	attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
	attackRange->SetColor(BLUE);
	attackCollider = new Rect(Vector2(), Vector2(50, 50));
	attackCollider->SetColor(RED);
	attackCollider->SetActive(false);
	SetSize({ 70.0f, 70.0f });
}

Monster::~Monster()
{
	for (vector<Animation*> animationArray : animations)
	{
		delete animationArray[0];
		delete animationArray[1];
	}
}

void Monster::Update()
{
	attackCollider->SetActive(false);

	SetActionState();
	DoAction();

	for (int i = 0; i < hitColliders.size(); i++)
	{
		if (!hitColliders[i]->IsCollision(this))
		{
			hitColliders.erase(hitColliders.begin() + i);
			break;
		}
	}

	Collision();

	Translate(velocity * DELTA);

	animations[curState][isRight]->Update();
	traceRange->SetPos(pos );
	attackRange->SetPos(pos );

	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	attackCollider->SetPos(pos + direction * 50.0f - Vector2{0.0f, attackCollider->Half().y});

	image->SetPos(pos + offset);

}

void Monster::Render(HDC hdc)
{
	CamRender(hdc);
	traceRange->CamRender(hdc);
	attackRange->CamRender(hdc);
	attackCollider->CamRender(hdc);

	image->CamRender(hdc, animations[curState][isRight]->GetFrame());
}

void Monster::InHaled()
{
	SetAnimation(INHALED);
	velocity = {};
	
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
		this->DamageHp(100);
		SetAnimation(HIT);
		actionState = ActionState::HIT;
	}

	if (attackCollider->IsCollision(target)) {
		target->DamageHp(1);
	}

	//hit target
	for (Rect* collider : hitColliders)
	{
		if (collider == target)
			return;
	}

	if (this->IsCollision(target)) 
	{
		//Kirby* kirby = (Kirby*)target;
		//if(kirby->GetActionState() == Kirby::ATTACK )
		//{
		//	//this->Die();
		//	kirby->SetMode(Kirby::EAT);
		//	kirby->SetIdle();
		//}
		//else {
		//	target->DamageHp(10); // Attack·ÂÀ» ³ª´²Áà¾ßÇÔ..
		//	DamageHp(10);
		//	Vector2 direction = isRight ? Vector2::Left() : Vector2::Right();

		//	velocity = (direction * 1300.0f).Normalized() * HIT_DAMAGE_SPEED;
		//	hitColliders.push_back(target);
		//}
	}
	
	Rect* collider = Kirby::AttackCollision(this);

	if (collider != nullptr) 
	{
		//velocity.x = ((target->GetPos() - pos).Normalized() * HIT_DAMAGE_SPEED).x;
		//velocity = velocity.Normalized() * HIT_DAMAGE_SPEED;
	}

	if (IsDie()) 
		Die();
}

void Monster::CreateTexture()
{
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);

	image = new Image(rightTexture);

	image->SetTexture(rightTexture);

}

void Monster::CreateAnimation()
{
	animations.resize(END);

	//Idle
	//L

	rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);
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

	//L
	animations[INHALED].push_back(new Animation(leftTexture->GetFrame()));
	animations[INHALED].back()->SetPart(9, 9);
	//animations[INHALED].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	//R		   
	animations[INHALED].push_back(new Animation(rightTexture->GetFrame()));
	animations[INHALED].back()->SetPart(9, 9);
	//animations[INHALED].back()->SetEndEvent(bind(&Monster::SetIdle, this));

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
	case ActionState::HIT:
		//velocity = {};
		break;
	}
}

void Monster::Patrol()
{
	if (isStay)
	{
		velocity = {};

		stayTime += DELTA;

		if (stayTime > PATROL_STAY_TIME)
		{
			stayTime = 0.0f;
			isStay = false;
			SetDestPos();
		}

		SetAnimation(IDLE);
		return;
	}

	Vector2 direction = destPos - pos;

	velocity = direction.Normalized() * PATROL_SPEED;

	if (direction.Magnitude() < 1.0f)
		isStay = true;
	velocity.x < 0 ? isRight = false : isRight = true;
	isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
	SetAnimation(MOVE);
}

void Monster::Trace()
{
	velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED ).x;

	SetDirectionState();

	SetAnimation(MOVE);
}

void Monster::Attack()
{
	if (stayAttackTime <= 0)
	{
		attackCollider->SetActive(true);
		stayAttackTime = ATTACK_STAY_TIME;
		velocity = {};

		SetDirectionState();

		SetAnimation(ATTACK);
	}
	stayAttackTime -= DELTA;
	
}

void Monster::Die()
{
	this->SetAllActive(false);
	SetAnimation(DEAD);
}

void Monster::SetDirectionState()
{
	bool isCurRight = target->GetPos().x > pos.x;

	if (isCurRight != isRight)
	{
		isRight = isCurRight;
		SetAnimation(IDLE);
	}
}

void Monster::SetDestPos()
{
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
	this->SetActive(false); 
	this->image->SetActive(false); 
	this->traceRange->SetActive(false); 
	this->attackRange->SetActive(false);
}
