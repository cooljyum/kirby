#pragma once

class Kirby : public Character
{
public:
	enum ActionState
	{
		IDLE, WALK, RUN, JUMP, SIT, ATTACK
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