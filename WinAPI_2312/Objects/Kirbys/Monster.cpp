#include "Framework.h"

Monster::Monster()
{
	CreateTexture();
	CreateAnimation();

	animations[IDLE][isRight]->Play();

	traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
	traceRange->SetColor(BLUE);
	attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
	attackRange->SetColor(RED);
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
	SetActionState();
	DoAction();
	//vector<Rect*>::iterator iter = hitColliders.begin();
	//
	//for (; iter != hitColliders.end(); )
	//{
	//	if ((*iter)->IsCollision(this))
	//		iter++;
	//	else
	//		iter = hitColliders.erase(iter);
	//}

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
}

void Monster::Render(HDC hdc)
{
	traceRange->CamRender(hdc);
	attackRange->CamRender(hdc);

	Image::CamRender(hdc, animations[curState][isRight]->GetFrame());
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
}

void Monster::CreateTexture()
{
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Left.bmp", 5, 2, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/WaddleDee_Right.bmp", 5, 2, true);

	SetTexture(leftTexture);

}

void Monster::CreateAnimation()
{
	animations.resize(END);

	//Idle
	//L
	animations[IDLE].push_back(new Animation(maxFrame));
	animations[IDLE].back()->SetPart(2, 2, true);
	//R
	animations[IDLE].push_back(new Animation(maxFrame));
	animations[IDLE].back()->SetPart(2, 2, true);

	//Move
	//L
	animations[MOVE].push_back(new Animation(maxFrame));
	animations[MOVE].back()->SetPart(4, 1, true);
	//R
	animations[MOVE].push_back(new Animation(maxFrame));
	animations[MOVE].back()->SetPart(4, 1, true);

	//Attack
	//L
	animations[ATTACK].push_back(new Animation(maxFrame));
	animations[ATTACK].back()->SetPart(5, 9);
	animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	//R		   
	animations[ATTACK].push_back(new Animation(maxFrame));
	animations[ATTACK].back()->SetPart(5, 9);
	animations[ATTACK].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	
	//Hit
	//L
	animations[HIT].push_back(new Animation(maxFrame));
	animations[HIT].back()->SetPart(9, 9);
	animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));
	//R		   
	animations[HIT].push_back(new Animation(maxFrame));
	animations[HIT].back()->SetPart(9, 9);
	animations[HIT].back()->SetEndEvent(bind(&Monster::SetIdle, this));

	//Dead
	//L
	animations[DEAD].push_back(new Animation(maxFrame));
	animations[DEAD].back()->SetPart(9, 9);
	//R		   
	animations[DEAD].push_back(new Animation(maxFrame));
	animations[DEAD].back()->SetPart(9, 9);
}

void Monster::SetAnimation(AnimationState state)
{
	if (curState == state) return;

	curState = state;
	isRight ? SetTexture(rightTexture) : SetTexture(leftTexture);
	animations[state][isRight]->Play();
}

void Monster::DoAction()
{
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
	velocity = {};

	SetDirectionState();

	SetAnimation(ATTACK);
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
