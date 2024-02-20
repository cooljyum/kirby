#pragma once

class Boss : public Character
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

	const float TRACE_RANGE = 700.0f;
	const float ATTACK_RANGE = 500.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;
	const float HIT_DAMAGE_SPEED = 200.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float ATTACK_STAY_TIME = 1.0f;
	const float PATROL_RANGE = 200.0f;

public:
	Boss();
	Boss(int type, int x, int y, int hp);
	~Boss();

	void Update();
	void Render(HDC hdc);

	void SetTarget(Character* target) { this->target = target; }

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
	void Die();
	void SetDirectionState();

	void SetDestPos();

	void SetAllActive(bool isActive);



private:
	Image* image;

	bool isRight = false, isStay = true;

	Vector2 velocity, destPos;

	float stayTime = 0.0f;
	float stayAttackTime = 0.0f;

	AnimationState curState = IDLE;
	ActionState actionState = ActionState::PATROL;

	vector<vector<Animation*>> animations;

	Texture* leftTexture;
	Texture* rightTexture;

	vector<Rect*> hitColliders;

	Character* target;

	Rect* traceRange;
	Rect* attackRange;

	Rect* attackCollider;

	Vector2 offset = { 0,-20 };
};