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
	actions[curState]->Update();
	
	Move();
	Control();
	Attack();


}

void Kirby::Render(HDC hdc)
{
	Rect::CamRender(hdc);
	actions[curState]->Render(hdc);

}

void Kirby::SetLandTexture(Texture* texture)
{
	for (Action* action : actions)
		action->SetLandTexture(texture);
}

void Kirby::Move()
{
	if (curState == JUMP || curState == SIT || curState == ATTACK) return;
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

	if (KEY->Down('S') && curState != JUMP) {
		SetAction(SIT, isRight);
	}

	if (KEY->Up('S') && curState == SIT) {
		SetIdle();
	}
}

void Kirby::Attack()
{
	if (KEY->Down('F'))
	{
		SetAction(ATTACK, isRight);
	}
}

void Kirby::CreateActions()
{
	actions.push_back(new KirbyIdle(this));
	actions.push_back(new KirbyWalk(this));
	actions.push_back(new KirbyRun(this));
	actions.push_back(new KirbyJump(this));
	actions.push_back(new KirbySit(this));
	actions.push_back(new KirbyAttack(this));

	actions[JUMP]->GetAnimation(2)->SetEndEvent(bind(&Kirby::SetIdle, this));
	actions[JUMP]->GetAnimation(3)->SetEndEvent(bind(&Kirby::SetIdle, this));

	actions[ATTACK]->GetAnimation(0)->SetEndEvent(bind(&Kirby::SetIdle, this));
	actions[ATTACK]->GetAnimation(1)->SetEndEvent(bind(&Kirby::SetIdle, this));
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