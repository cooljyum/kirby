#pragma once

class Monster : public Image
{
private:
	enum AnimationState
	{
		IDLE, MOVE, ATTACK, HIT, DEAD, END
	};

	enum class ActionState
	{
		PATROL, TRACE, ATTACK, HIT, DEAD
	};

	const float TRACE_RANGE = 400.0f;
	const float ATTACK_RANGE = 150.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float PATROL_RANGE = 200.0f;

public:
	Monster();
	~Monster();

	void Update();
	void Render(HDC hdc);

	void SetTarget(Rect* target) { this->target = target; }

private:
	void SetActionState();

	void SetIdle();

	void Collision();

	void CreateTexture();
	void CreateAnimation();

	void SetAnimation(AnimationState state);

private:
	void DoAction();

	void Patrol();
	void Trace();
	void Attack();
	void SetDirectionState();

	void SetDestPos();

private:
	bool isRight = false, isStay = true;
	Vector2 velocity, destPos;
	float stayTime = 0.0f;

	AnimationState curState = IDLE;
	ActionState actionState = ActionState::PATROL;

	vector<vector<Animation*>> animations;

	Texture* leftTexture;
	Texture* rightTexture;

	vector<Rect*> hitColliders;
	Rect* target;

	Rect* traceRange;
	Rect* attackRange;

	Vector2 offset = {0,-20};
};