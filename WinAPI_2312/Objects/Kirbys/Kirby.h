#pragma once

class Kirby : public Character
{
public:
	//Ŀ�� ��� ����
	enum ModeState
	{
		DEFAULT, EAT , FLY
	};

	//Ŀ�� �׼� ���µ�
	enum ActionState
	{
		IDLE, WALK, SIT, ATTACK, JUMP, JUMPEND
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

private:
	map<ModeState, vector<Action*>> actions;

	ModeState curModeState = DEFAULT;
	ActionState curActionState = IDLE;

	bool isRight = true;
};