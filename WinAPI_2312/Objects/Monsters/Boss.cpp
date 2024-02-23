#include "Framework.h"

//Boss::Boss() : Character()
//{
//	SetSize(SIZE);
//
//	CreateTexture();
//	CreateAnimation();
//
//	animations[IDLE][isRight]->Play();
//
//	traceRange = new Rect(Vector2(), Vector2(TRACE_RANGE, TRACE_RANGE));
//	traceRange->SetColor(YELLOW);
//	
//	attackRange = new Rect(Vector2(), Vector2(ATTACK_RANGE, ATTACK_RANGE));
//	attackRange->SetColor(BLUE);
//	
//	attackCollider = new Rect(Vector2(), Vector2(200, 200));
//	attackCollider->SetColor(RED);
//	attackCollider->SetActive(true);
//	
//	startPos = pos.y;
//
//	BossBullet::CreateBullets();
//}

Boss::Boss(int x, int y, int hp) : Character()
{
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
	attackCollider = new Rect(Vector2(), Vector2(200, 200));
	attackCollider->SetColor(RED);
	attackCollider->SetActive(true);

	//Boss기능
	//Bullet Create
	BossBullet::CreateBullets();
}

Boss::~Boss()
{
	for (vector<Animation*> animationArray : animations)
	{
		delete animationArray[0];
		delete animationArray[1];
	}
	BossBullet::Delete();
}

void Boss::Update()
{
	//Attack Collider Setting false
	attackCollider->SetActive(false);

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
	//이거 체크체크체크체크체크체크체크체크체ㅡ케츠케츠
	attackCollider->SetPos(pos + direction * 50.0f - Vector2{ 0.0f, attackCollider->Half().y });
	//attackCollider->SetPos(pos + direction * 100.0f);

	//image follow this
	image->SetPos(pos+ offset);

	//Gravity Setting
	velocity.y += GRAVITY * DELTA;

	//Bottom Check Map Land
	if (this->Bottom() > landTexture->GetPixelHeight(this->GetPos()))
	{
		velocity.y = 0.0f;
		this->SetPos({ this->GetPos().x, landTexture->GetPixelHeight(this->GetPos()) - this->Half().y });
	}

	//Boss기능
	//BossBullet 
	BossBullet::UpdateBullets();
}

void Boss::Render(HDC hdc)
{
	CamRender(hdc);
	traceRange->CamRender(hdc);
	attackRange->CamRender(hdc);
	attackCollider->CamRender(hdc);

	image->CamRender(hdc, animations[curState][isRight]->GetFrame());

	//Boss기능
	BossBullet::RenderBullets(hdc);
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

	if (this->IsCollision(target)) // 보스기능
	{
		//어허 이거 고쳐야함 !?
		Kirby* kirby = (Kirby*)target;
		if (kirby->GetActionState() == Kirby::ATTACK)
		{
			this->Die();
			kirby->SetMode(Kirby::EAT);
			kirby->SetIdle();
		}
	}

	//쓸모x //안쓸거 같은데요
	//Rect* collider = Kirby::AttackCollision(this);

	//if (collider != nullptr)
	//{
	//	//잠시 막아둠요
	//	//velocity.x = ((target->GetPos() - pos).Normalized() * HIT_DAMAGE_SPEED).x;
	//	//velocity = velocity.Normalized() * HIT_DAMAGE_SPEED;
	//}
	// 
	//Check Die
	if (IsDie())
		Die();
}

void Boss::CreateTexture()
{
	//Boss랑 Monster랑 texture가 다릅니다~
	//Tex Set
	leftTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Left.bmp", 5, 4, true);
	rightTexture = Texture::Add(L"Kirby_Resources/Monster/Boss/Hammer_Right.bmp", 5, 4, true);

	//Image Set
	image = new Image(rightTexture);
	image->SetTexture(rightTexture);

}

void Boss::CreateAnimation()
{
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

	//Attack //Boss기능 
	//L
	animations[ATTACK].push_back(new Animation(leftTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()->SetEndEvent([this]() {
		attackCollider->SetActive(true);  
		SetIdle(); 
		BossBullet::init();
		BossBullet::Shot(attackCollider->GetPos() + Vector2{ -150.0f,0}, isRight);
		//BossBullet::Shot(attackCollider->GetPos() + Vector2{ -0.0f,0 }, isRight);
		});
	animations[ATTACK].back()->SetSpeed(0.5f);

	//R		   
	animations[ATTACK].push_back(new Animation(rightTexture->GetFrame()));
	animations[ATTACK].back()->SetPart(8, 13);
	animations[ATTACK].back()-> SetEndEvent([this]() {
		attackCollider->SetActive(true);  
		SetIdle(); 
		BossBullet::init();
		BossBullet::Shot(attackCollider->GetPos() + Vector2{ 150.0f,0 }, isRight);
		//BossBullet::Shot(attackCollider->GetPos() + Vector2{ 50.0f,0 }, isRight);
		});
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
	//	velocity = {};
		break;
	}
}

void Boss::Patrol()
{
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

void Boss::Trace()
{
	//Target Follow Move
	velocity.x = ((target->GetPos() - pos).Normalized() * TRACE_SPEED).x;

	SetDirectionState();

	SetAnimation(MOVE);
}

void Boss::Attack()
{
	if (stayAttackTime <= 0)
	{
		stayAttackTime = ATTACK_STAY_TIME;
		
		//Check 필요할뜻
		velocity = {};

		velocity = { 0, -500.0f }; //Boss이게 다름 

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
	//Set IsRight follow Target
	bool isCurRight = target->GetPos().x > pos.x;

	if (isCurRight != isRight)
	{
		isRight = isCurRight;
		SetAnimation(IDLE);
	}
}

void Boss::SetDestPos()
{
	//Patrol 때 거리 설정 
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
	//All Rect Active
	this->SetActive(isActive);
	this->image->SetActive(isActive);
	this->traceRange->SetActive(isActive);
	this->attackRange->SetActive(isActive);
}
