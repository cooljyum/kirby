#pragma once

class Kirby : public Character
{
public:
	//커비 모드 상태
	enum ModeState
	{
		BASIC, BIG , FLY//,ITEM(추가 가능?)
	};

	//커비 액션 상태들
	enum ActionState
	{
		IDLE, WALK, SIT, JUMP, ATTACK
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

	void SetAction(ActionState state, bool isRight);

	Vector2 GetOffset() { return imageOffset; }

private:
	map<ModeState, vector<Action*>> actions;

	ModeState curModeState = BIG;
	ActionState curActionState = IDLE;

	bool isRight = true;

	//bool isRun = false;


};