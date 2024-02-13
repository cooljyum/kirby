#include "Framework.h"

Kirby::Kirby() : Character()
{
	CreateActions();
}

Kirby::~Kirby()
{
}

void Kirby::Update()
{
	actions[curState]->Update();
	Move();
	Control();
}

void Kirby::Render(HDC hdc)
{
	Rect::Render(hdc);
	actions[curState]->Render(hdc);

}

void Kirby::Move()
{
	if (curState == JUMP || curState == SIT) return;
	bool isMove = false;
	bool isRun = false;

	if (KEY->Press('D'))
	{
		isMove = true;
		isRight = true;
		if (KEY->Press(VK_SHIFT)) 
		{
			isRun = true;
		}
	}
	if (KEY->Press('A'))
	{
		isMove = true;
		isRight = false;
		if (KEY->Press(VK_SHIFT))
		{
			isRun = true;
		}
	}

	isMove ? isRun ? SetAction(RUN, isRight) : SetAction(WALK, isRight) : SetIdle();
}

void Kirby::Control()
{
	if (KEY->Down('W'))
	{
		SetAction(JUMP, isRight);
	}
	if (KEY->Down('S'))
		SetAction(SIT, isRight);
}

void Kirby::CreateActions()
{
	actions.push_back(new KirbyIdle(this));
	actions.push_back(new KirbyWalk(this));
	actions.push_back(new KirbyRun(this));
	actions.push_back(new KirbyJump(this));
	actions.push_back(new KirbySit(this));

	actions[SIT]->GetAnimation(0)->SetEndEvent(bind(&Kirby::SetIdle, this));
	actions[SIT]->GetAnimation(1)->SetEndEvent(bind(&Kirby::SetIdle, this));
}

void Kirby::SetIdle()
{
	SetAction(IDLE, isRight);
}

void Kirby::SetAction(ActionState state, bool isRight)
{
	if (curState == state)
		return;

	actions[curState]->End();
	curState = state;
	actions[state]->Start(isRight);
}

