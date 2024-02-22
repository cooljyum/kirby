#include "Framework.h"


vector<Rect*> Kirby::colliders;

Kirby::Kirby() : Character()
{
	size = { 70, 70 };
	CreateActions();
	KirbyStarBullet::CreateBullets();
}

Kirby::~Kirby()
{
	KirbyStarBullet::Delete();
}

void Kirby::Update()
{
	actions[curModeState][curActionState]->Update();
	
	Collision();
	Move();
	Control();
	Attack();

	KirbyStarBullet::UpdateBullets();


	MapItemManager::Get()->Play("BossDoorEffect", GetPos());
}

void Kirby::Render(HDC hdc)
{
	Rect::CamRender(hdc);
	actions[curModeState][curActionState]->Render(hdc);

	string str = "Kirby Hp : " + to_string(hp);

	TextOutA(hdc, CENTER_X, 20, str.c_str(), str.size());

	KirbyStarBullet::RenderBullets(hdc);

}

void Kirby::SetLandTexture(Texture* texture)
{
	float landHeight = texture->GetPixelHeight(GetPos());
	SetPos({ GetPos().x, landHeight - Half().y });

	for (const pair<ModeState, vector<Action*>>& actionList : actions) 
		for (Action* action : actionList.second) 
			action->SetLandTexture(texture);
		
	KirbyStarBullet::SetLandTexture(texture);
}

void Kirby::Move()
{
	
	bool isMove = false;
	bool isRun = false;

	if (KEY->Press('D'))
	{
		isMove = true;
		isRight = true;
	}
	if (KEY->Press('A'))
	{
		isMove = true;
		isRight = false;
	}

	if (curActionState == JUMPUP || curActionState == JUMPDOWN || curActionState == SIT || curActionState == ATTACK || curActionState == HIT) return;
	isMove ?  SetAction(WALK, isRight) : SetIdle();
}

void Kirby::Control()
{
	if (KEY->Down('W') && curActionState != JUMPUP && curActionState != JUMPDOWN)
	{
		SOUND->Play("Jump");
		SetAction(JUMPUP, isRight);
	}

	if (KEY->Down('S') && curActionState != JUMPUP && curActionState != JUMPDOWN) 
	{
		SetAction(SIT, isRight);
	}
	
	if (KEY->Down('S') && curActionState != JUMPUP && curActionState != JUMPDOWN)
	{
		SetAction(SIT, isRight);
	}

	if (KEY->Up('S') && curActionState == SIT && curModeState == DEFAULT) {
		SetIdle();
	}
}

void Kirby::Attack()
{
	if (curActionState == JUMPUP || curActionState == JUMPDOWN || curActionState == SIT || curActionState == ATTACK) return;
	if (KEY->Down('F'))
	{
		SetAction(ATTACK, isRight);
	}
	
}

void Kirby::Hit()
{
	SetAction(Kirby::HIT, isRight);
	isHit = false;

}

void Kirby::CreateActions()
{
	CreateModeAction(DEFAULT);
	CreateModeAction(EAT);
}

void Kirby::CreateModeAction(ModeState mode)
{
	if (mode == DEFAULT) 
	{ 
		actions[mode].push_back(new KirbyIdle(this));
		actions[mode].push_back(new KirbyWalk(this));
		actions[mode].push_back(new KirbySit(this));
		actions[mode].push_back(new KirbyInhole(this));
		actions[mode].push_back(new KirbyJumpUp(this));
		actions[mode].push_back(new KirbyJumpDown(this));
		actions[mode].push_back(new KirbyHit(this));
	}
	
	if (mode == EAT) 
	{ 
		actions[mode].push_back(new KirbyIdleEat(this)); 
		actions[mode].push_back(new KirbyWalkEat(this));
		actions[mode].push_back(new KirbySitEat(this));
		actions[mode].push_back(new KirbyAttackEat(this));
		actions[mode].push_back(new KirbyJumpUpEat(this));
		actions[mode].push_back(new KirbyJumpDownEat(this));
		actions[mode].push_back(new KirbyHit(this));
	}

	actions[mode][HIT]->GetAnimation(0)->SetEndEvent([this]() {
			SetMode(DEFAULT); SetIdle();
		});

	actions[mode][HIT]->GetAnimation(1)->SetEndEvent([this]() {
			SetMode(DEFAULT); SetIdle();
		});
	
	actions[mode][ATTACK]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) {
			SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][ATTACK]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) {
			SetMode(DEFAULT); SetIdle();
		}});

	
	actions[mode][SIT]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) { 
			SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][SIT]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) {  
			SetMode(DEFAULT); SetIdle();
		}});

	//actions[mode][JUMPDOWN]->GetAnimation(0)->SetEndEvent([this]() {
	//	if (!isHit) 
	//		SetIdle(); 
	//	else 
	//		//SetAction(HIT, isRight);
	//	isHit = false;
	//	});

	//actions[mode][JUMPDOWN]->GetAnimation(1)->SetEndEvent([this]() {
	//	if (!isHit) 
	//		SetIdle(); 
	//	else 
	//		SetAction(HIT, isRight);
	//	isHit = false;
	//	});

}

void Kirby::SetIdle()
{
	if (curModeState == DEFAULT) SetAction(IDLE, isRight);
	if (curActionState == IDLE) return;
	SetAction(IDLE, isRight,true);
}

void Kirby::SetAction(ActionState state, bool isRight, bool isForce)
{
	if (!isForce && curActionState == state)
		return;

	actions[curModeState][curActionState]->End();
	curActionState = state;
	actions[curModeState][state]->Start(isRight);

}

void Kirby::Collision()
{
	MapItem* door = MapItemManager::Get()->Collision("Door", this);
	if (door != nullptr)
	{
		if (KEY->Down('W')) 
		{
			SCENE->ChangeScene("Boss");
		}
	}
	
	if (invincibilityTime <= 0.0f) 
	{
		Monster* monster = MonsterManager::Get()->Collision(this);
		if (monster != nullptr)
		{
			if (monster->GetState() == Monster::HIT) return;

			monster->DamageHp(1);
			Vector2 direction = isRight ? Vector2::Right() : Vector2::Left(); 
			Vector2 velocity = { direction.x * 800.0f,0.0f };
			monster->Hit();
			monster->SetVelocity(velocity);
			
			
			DamageHp(10);
			//isHit = true;
			//SetAction(HIT, isRight);
			
			//invincibilityTime = INVINCIBILITY_TIME; //
		
		}
	}
	else
		invincibilityTime -= DELTA;
}

void Kirby::AddCollider(Rect* collider)
{
	colliders.push_back(collider);
}

Rect* Kirby::AttackCollision(Rect* rect)
{
	for (Rect* collider : colliders)
	{
		if (collider->IsCollision(rect))
			return collider;
	}

	return nullptr;
}
