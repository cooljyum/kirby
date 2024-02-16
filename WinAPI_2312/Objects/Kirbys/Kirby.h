#pragma once

class Kirby : public Character
{
public:
	//커비 모드 상태
	enum ModeState
	{
		DEFAULT, EAT , FLY
	};

	//커비 액션 상태들
	enum ActionState
	{
		IDLE, WALK, SIT, ATTACK, JUMPUP, JUMPDOWN
	};

public :
	Kirby();
	~Kirby();

	void Update();
	void Render(HDC hdc);

	void SetLandTexture(Texture* texture);

	void Move();
	void Control();
	void Attack();

	void CreateActions();
	void CreateModeAction(ModeState mode);

	void SetIdle();

	void SetMode(ModeState state) { curModeState = state; }
	void SetAction(ActionState state, bool isRight);
	

	Vector2 GetOffset() { return imageOffset; }
	
	ActionState GetActionState() { return curActionState; }


private:
	map<ModeState, vector<Action*>> actions;

	ModeState curModeState = EAT;
	ActionState curActionState = IDLE;

	bool isRight = true;
};