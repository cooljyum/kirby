#pragma once

class Kirby : public Character
{
public:
	//Ŀ�� ��� ����
	enum ModeState
	{
		BASIC, FLY //,ITEM(�߰� ����?)
	};

	//Ŀ�� �׼� ���µ�
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

	void SetIdle();

	void SetAction(ActionState state, bool isRight);

	Vector2 GetOffset() { return imageOffset; }

private:
	vector<Action*> actions;

	ActionState curState = IDLE;

	bool isRight = true;

	//bool isRun = false;


};