#pragma once

class Kirby : public Character
{
public:
	enum ActionState
	{
		IDLE, WALK, RUN, JUMP, SIT
	};

public :
	Kirby();
	~Kirby();

	void Update();
	void Render(HDC hdc);

	void SetLandTexture(Texture* texture);

	void Move();
	void Control();

	void CreateActions();

	void SetIdle();

	void SetAction(ActionState state, bool isRight);

private:
	vector<Action*> actions;

	ActionState curState = IDLE;

	bool isRight = true;

	//bool isRun = false;

};