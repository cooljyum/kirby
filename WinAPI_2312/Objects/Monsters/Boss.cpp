#include "Framework.h"

Boss::Boss() : Character()
{
	CreateTexture();
	CreateAnimation();

	animations[IDLE][isRight]->Play();

	traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
	traceRange->SetColor(YELLOW);
	attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
	attackRange->SetColor(BLUE);
	attackCollider = new Rect(Vector2(), Vector2(40, 10));
	attackCollider->SetColor(RED);
	attackCollider->SetActive(false);
	SetSize({ 100.0f, 100.0f });
	startPos = pos.y;
}

Boss::Boss(int type, int x, int y, int hp)
{
	SetPos(x, y);
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
	SetSize({ 50.0f, 50.0f });
}

Boss::~Boss()
{
	for (vector<Animation*> animationArray : animations)
	{
		delete animationArray[0];
		delete animationArray[1];
	}
}

void Boss::Update()
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
	traceRange->SetPos(pos + offset);
	attackRange->SetPos(pos + offset);

	Vector2 direction = isRight ? Vector2::Right() : Vector2::Left();
	attackCollider->SetPos(pos + direction * 50.0f - Vector2{ 0.0f, attackCollider->Half().y });

	image->SetPos(pos+ offset);

	//velocity.x < 0 ? isRight = false : isRight = true;
	//isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);


	velocity.y += GRAVITY * DELTA;


	if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
	{
		velocity.y = 0.0f;
		this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
	}

}

void Boss::Render(HDC hdc)
{
	CamRender(hdc);
	traceRange->CamRender(hdc);
	attackRange->CamRender(hdc);
	attackCollider->CamRender(hdc);

	image->CamRender(hdc, animations[curState][isRight]->GetFrame());
}

void Boss::SetActionState()
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

void Boss::SetIdle()
{
	SetAnimation(IDLE);
	actionState = ActionState::PATROL;
}

void Boss::Collision()
{
	if (curState == HIT)
		return;

	if (KirbtStarBullet::IsBulletsCollision(this))
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
		Kirby* kirby = (Kirby*)target;
		if (kirby->GetActionState() == Kirby::ATTACK)
		{
			this->Die();
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();
			//키를 막거나 action이 바뀔때 bool 조건 하나 주면될거 같은데 혹시 전자 방법이 있을까요..?

		}
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

void Boss::CreateTexture()
{
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Left.bmp", 5, 4, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Right.bmp", 5, 4, true);

	image = new Image(rightTexture);

	image->SetTexture(rightTexture);

}

void Boss::CreateAnimation()
{
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

	//Attack
	//L
	animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()->SetEndEvent([this]() {SetIdle(); BossBullet::Shot(GetPos(), isRight); });
	animations[ATTACK].back()->SetSpeed(0.5f);
	//R		   
	animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()-> SetEndEvent([this]() {SetIdle(); BossBullet::Shot(GetPos(), isRight); });
	animations[ATTACK].back()->SetSpeed(0.5f);

	//Hit
	//L
	animations[HIT].push_back(new Animation(leftTexture->GetFrame()));
	animations[HIT].back()->SetPart(16, 16);
	animations[HIT].back()->SetEndEvent(bind(&Boss::SetIdle, this));
	//R		   
	animations[HIT].push_back(new Animation(rightTexture->GetFrame()));
	animations[HIT].back()->SetPart(16, 16);
	animations[HIT].back()->SetEndEvent(bind(&Boss::SetIdle, this));

	//Dead
	//L
	animations[DEAD].push_back(new Animation(leftTexture->GetFrame()));
	animations[DEAD].back()->SetPart(17, 19);


	//R		   
	animations[DEAD].push_back(new Animation(rightTexture->GetFrame()));
	animations[DEAD].back()->SetPart(17, 19);
	//animations[DEAD].back()->SetEndEvent(bind(&Boss::SetAllActive, this, false));

}

void Boss::SetAnimation(AnimationState state)
{
	if (curState == state) return;

	curState = state;
	isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
	animations[state][isRight]->Play();
}

void Boss::SetLandTexture(Texture* texture)
{
	landTexture = texture;
}

void Boss::DoAction()
{
	switch (actionState)
	{
	case Boss::ActionState::PATROL:
		Patrol();
		break;
	case Boss::ActionState::TRACE:
		Trace();
		break;
	case Boss::ActionState::ATTACK:
		Attack();
		break;
	case ActionState::HIT:
		velocity = {};
		break;
	}
}

void Boss::Patrol()
{
	velocity.x < 0 ? isRight = false : isRight = true;
	isRight ? image->SetTexture(rightTexture) : image->SetTexture(leftTexture);
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

	SetAnimation(MOVE);
}

void Boss::Trace()
{
	velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED).x;

	SetDirectionState();

	SetAnimation(MOVE);
}

void Boss::Attack()
{
	if (stayAttackTime <= 0)
	{
		attackCollider->SetActive(true);
		stayAttackTime = ATTACK_STAY_TIME;
		velocity = {};

		velocity = { 0, -500.0f };

	//	velocity.y += GRAVITY * DELTA;

		SetDirectionState();

		SetAnimation(ATTACK);

	}

	stayAttackTime -= DELTA;
}

void Boss::Die()
{
	SetAnimation(DEAD);
	stayDieTime += DELTA;

	if (stayDieTime > DIE_STAY_TIME)
	{
		stayDieTime = 0.0f;
		SetAllActive(false);
	}
}

void Boss::SetDirectionState()
{
	bool isCurRight = target->GetPos().x > pos.x;

	if (isCurRight != isRight)
	{
		isRight = isCurRight;
		SetAnimation(IDLE);
	}
}

void Boss::SetDestPos()
{
	float distance = Random(-PATROL_RANGE, +PATROL_RANGE);

	destPos = pos + Vector2::Right() * distance;

	if (destPos.x > SCREEN_WIDTH - Half().x)
		destPos.x = SCREEN_WIDTH - Half().x;
	if (destPos.x < Half().x)
		destPos.x = Half().x;

	isRight = distance > 0.0f;
}

void Boss::SetAllActive(bool isActive)
{
	this->SetActive(false);
	this->image->SetActive(false);
	this->traceRange->SetActive(false);
	this->attackRange->SetActive(false);
}
