#include "Framework.h"

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
	if (curActionState == JUMP || curActionState == SIT || curActionState == ATTACK) return;
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
	if (KEY->Down('W'))
	{
		SetAction(JUMP, isRight);
	}

	if (KEY->Down('S') && curActionState != JUMP) {
		SetAction(SIT, isRight);
	}

	if (KEY->Up('S') && curActionState == SIT) {
		SetIdle();
	}
}

void Kirby::Attack()
{
	if (curActionState == JUMP || curActionState == SIT || curActionState == ATTACK) return;
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
	actions[mode].push_back(new KirbyIdle(this, mode));
	actions[mode].push_back(new KirbyWalk(this, mode));
	actions[mode].push_back(new KirbySit(this, mode));
	actions[mode].push_back(new KirbyJump(this, mode));
	actions[mode].push_back(new KirbyAttack(this, mode));

	actions[mode][JUMP]->GetAnimation(2)->SetEndEvent(bind(&Kirby::SetIdle, this));
	actions[mode][JUMP]->GetAnimation(3)->SetEndEvent(bind(&Kirby::SetIdle, this));

	
	actions[mode][ATTACK]->GetAnimation(0)->SetEndEvent([this]() {
		SetIdle();
		if (curModeState == EAT || curModeState == FLY) SetMode(DEFAULT);
		});

	actions[mode][ATTACK]->GetAnimation(1)->SetEndEvent([this]() {
		SetIdle();
		if (curModeState == EAT || curModeState == FLY) SetMode(DEFAULT);
		});

	actions[mode][SIT]->GetAnimation(0)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) { SetIdle(); SetMode(DEFAULT); }
		});

	actions[mode][SIT]->GetAnimation(1)->SetEndEvent([this]() {
		if (curModeState == EAT || curModeState == FLY) { SetIdle(); SetMode(DEFAULT); }
		});
}

void Kirby::SetIdle()
{
	SetAction(IDLE, isRight);
}

void Kirby::SetAction(ActionState state, bool isRight)
{
	if (curActionState == state)
		return;

	actions[curModeState][curActionState]->End();
	curActionState = state;
	actions[curModeState][state]->Start(isRight);
}