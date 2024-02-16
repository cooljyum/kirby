#include "Framework.h"


vector<Rect*> Kirby::colliders;

Kirby::Kirby() : Character()
{
	size = { 100, 100 };
	CreateActions();
	
}

Kirby::~Kirby()
{
}

void Kirby::Update()
{
	actions[curModeState][curActionState]->Update();
	
	Move();
	Control();
	Attack();
}

void Kirby::Render(HDC hdc)
{
	Rect::CamRender(hdc);
	actions[curModeState][curActionState]->Render(hdc);
}

void Kirby::SetLandTexture(Texture* texture)
{
	float landHeight = texture->GetPixelHeight(GetPos());
	SetPos({ GetPos().x, landHeight - Half().y });

	for (const pair<ModeState, vector<Action*>>& actionList : actions) 
		for (Action* action : actionList.second) 
			action->SetLandTexture(texture);
		
	
}

void Kirby::Move()
{
	if (curActionState == JUMPUP || curActionState == JUMPDOWN || curActionState == SIT || curActionState == ATTACK) return;
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

	isMove ?  SetAction(WALK, isRight) : SetIdle();
}

void Kirby::Control()
{
	if (KEY->Down('W') && curActionState != JUMPUP && curActionState != JUMPDOWN)
	{
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
		//if (curModeState == EAT || curModeState == FLY) { SetMode(DEFAULT); }
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
		actions[mode].push_back(new KirbyAttack(this));
		actions[mode].push_back(new KirbyJumpUp(this));
		actions[mode].push_back(new KirbyJumpDown(this));
	}
	
	if (mode == EAT) 
	{ 
		actions[mode].push_back(new KirbyIdleEat(this)); 
		actions[mode].push_back(new KirbyWalkEat(this));
		actions[mode].push_back(new KirbySitEat(this));
		actions[mode].push_back(new KirbyAttackEat(this));
		actions[mode].push_back(new KirbyJumpUpEat(this));
		actions[mode].push_back(new KirbyJumpDownEat(this));
	}

	
	actions[mode][ATTACK]->GetAnimation(0)->SetEndEvent([this]() {
		SetIdle();
		if (curModeState == EAT || curModeState == FLY) SetMode(DEFAULT);
		});

	actions[mode][ATTACK]->GetAnimation(1)->SetEndEvent([this]() {
		SetIdle();
		if (curModeState == EAT || curModeState == FLY) SetMode(DEFAULT);
		});

	actions[mode][SIT]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) { SetMode(DEFAULT); SetIdle();
		}});

	actions[mode][SIT]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) {  SetMode(DEFAULT); SetIdle();
		}});
}

void Kirby::SetIdle()
{
	SetAction(IDLE, isRight);
}

void Kirby::SetAction(ActionState state, bool isRight, bool isForce)
{
	if (!isForce && curActionState == state)
		return;

	actions[curModeState][curActionState]->End();
	curActionState = state;
	actions[curModeState][state]->Start(isRight);
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
