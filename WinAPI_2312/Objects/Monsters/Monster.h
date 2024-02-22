#pragma once

class Monster : public Character
{
public:
	enum AnimationState
	{
		IDLE, MOVE, ATTACK, HIT, DEAD, INHALED, END
	};
private:
	enum class ActionState
	{
		PATROL, TRACE, ATTACK, HIT, DEAD
	};

	const float TRACE_RANGE = 400.0f;
	const float ATTACK_RANGE = 100.0f;

	const float PATROL_SPEED = 50.0f;
	const float TRACE_SPEED = 50.0f;
	const float HIT_DAMAGE_SPEED = 200.0f;

	const float PATROL_STAY_TIME = 1.0f;
	const float ATTACK_STAY_TIME = 2.0f;
	const float PATROL_RANGE = 200.0f;

public:
	Monster(int type, int x, int y, int hp);
	~Monster();

	void Update();
	void Render(HDC hdc);

	void SetTarget(Character* target) { this->target = target; }
	void SetVelocity(Vector2 velocity) { this->velocity = velocity; }
	AnimationState GetState() { return curState; }

	void InHaled();
	void Hit();

private:
	void SetActionState();

	void SetIdle();

	void Collision();

	void CreateTexture();
	void CreateAnimation();

	void SetAnimation(AnimationState state);

private:
	void DoAction(); // AnimationState ���� Action �Լ� ȣ��

	//Action �Լ���
	void Patrol();
	void Trace();
	void Attack();
	void Die();

	void SetDirectionState(); //Target ���� IsRight����

	void SetDestPos(); //Patrol �Ҷ� �Ÿ�����

	void SetAllActive(bool isActive); //������� ��� Rect Ű�� ��

	

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

	Vector2 offset = { 0, 35 };
};