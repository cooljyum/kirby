#pragma once

class Monster : public Character
{
public:
	enum AnimationState
	{
		IDLE, MOVE, ATTACK, HIT, DEAD, INHALED, END
	};

	enum class ActionState
	{
		PATROL, TRACE, ATTACK, HIT, DEAD
	};

protected:
	const float GRAVITY = 980.0f;

private:
	const Vector2 SIZE = { 70.0f, 70.0f };

	const float PATROL_RANGE = 200.0f;
	const float TRACE_RANGE = 400.0f;
	const float ATTACK_RANGE = 100.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;
	const float HIT_DAMAGE_SPEED = 200.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float ATTACK_STAY_TIME = 2.0f;
	const float DIE_STAY_TIME = 0.0f;

public:
	Monster( int x = 0, int y = 0, int hp = 100 );
	~Monster();

	void Update();
	virtual void Render(HDC hdc);

	void SetTarget(Character* target) { this->target = target; }
	void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	void SetLandTexture(Texture* texture) { this->landTexture = texture; }
	
	AnimationState GetState() { return curState; }

	void InHaled();
	void Hit();

	void SetAllActive(bool isActive); 

protected:
	void SetActionState();

	void SetIdle();

	virtual void Collision();

	virtual void CreateTexture();
	virtual void CreateAnimation();

	void SetAnimation(AnimationState state);

	void DoAction();

	//Action 
	void Patrol();
	void Trace();

	//virtual Fun
	virtual void Attack();
	virtual void Die();

	void SetDirectionState(); 

	void SetDestPos();

protected:
	bool isRight = false, isStay = true;

	Vector2 velocity, destPos;
	Vector2 offset = { 0, 35 };

	float stayTime = 0.0f;
	float stayAttackTime = 0.0f;
	float stayDieTime = 0.0f;

	AnimationState curState = IDLE;
	ActionState actionState = ActionState::PATROL;

	vector<vector<Animation*>> animations;

	Texture* leftTexture;
	Texture* rightTexture;
	Texture* landTexture;

	vector<Rect*> hitColliders;

	Character* target;

	Rect* traceRange;
	Rect* attackRange;

	Rect* attackCollider;

	Image* image;
};